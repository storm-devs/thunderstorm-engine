#pragma once
#include <cstdint>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <map>
#include "Entity.h"
#include "vmodule_api.h"
#include "Layer.h"

using index_t = uint32_t;
/* ALPHA v0.0000001*/
struct EntityData
{
	bool deleted;
	uint32_t hash; // temporary kostil'
	entid_t id;
	entptr_t ptr;
	std::vector<std::pair<std::string, index_t>> layers; // !@# TODO: use custom allocator
	const char* name;
};

class EntityManager {
public:
	static const entid_t INVALID_ENTITY = 0ull;

private:
	/* typedefs */
	using stamp_t = uint32_t;

	using flags_t = uint32_t;
	using layer_t = std::multimap<index_t, entid_t>;

	using entities_t = std::vector<EntityData>;
	using layer_with_flags_t = std::pair<layer_t, flags_t>;
	using layers_t = std::unordered_map<std::string, layer_with_flags_t>;

public:
	/* meyers singleton */
	static EntityManager & GetInstance()
	{
		static EntityManager instance;
		return instance;
	}

	entid_t CreateEntity(const char* name, ATTRIBUTES* attr = nullptr)
	{
		/* FIND VMA */
		const long hash = MakeHashValue(name);
		if (hash == 0) {
			throw std::exception("null hash");
		}
		VMA* pClass = nullptr;
		for (const auto &c : _pModuleClassRoot) {
			if (c->GetHash() == hash && _stricmp(name, c->GetName()) == 0) {
				pClass = c;
				break;
			}
		}
		if (pClass == nullptr) {
			throw std::exception("invalid entity name");
		}

		/* CREATE Entity */
		auto* ptr = static_cast<Entity*>(pClass->CreateClass());
		if (ptr == nullptr)	{
			throw std::exception("CreateClass returned nullptr");
		}

		/* INIT Entity */
		// set id first
		const auto id = PushEntity(ptr, name);
		ptr->id_ = id;
		ptr->AttributesPointer = attr;

		// then init
		if (!ptr->Init()) {
			// mark as deleted if fail 
			const auto index = static_cast<index_t>(id);
			entities_[index].deleted = false;
			return INVALID_ENTITY;
		}
		// why so? cuz fuck yourself

		return id;
	}

	void _erase(const EntityData & data) {
		for (auto &[name, _] : data.layers) {
			RemoveFromLayer(data.id, name); // TODO: optimize
		}
		free((void*)data.name);
		delete data.ptr;
	}

	void EraseEntity(const entid_t entity) {
		const auto & entData = GetEntityData(entity);
		if (entData.ptr == nullptr)
			return;

		const auto index = static_cast<index_t>(entity);
		// TODO: entities_.at

		// validate 
		if (entData.ptr->GetId() != entity) 
			return; /* already replaced by another entity */

		entities_[index].deleted = true;
		/*_erase(entities_[index]); // release
		
		entities_[index] = entities_[entities_.size() - 1];
		entities_.pop_back();*/
	}

	void EraseAll()	{
		/*for(auto entity : entities_) {
			_erase(entity); // release
		}
		entities_.clear();*/
		for (auto & entity : entities_) {
			entity.deleted = true;
		}
	}

	/* assemble requested walker (generator) */
	template <bool IsEntData, typename Iterable>
	constexpr auto generator(Iterable& iterable, long hash = 0) {
		return[this, hash, &iterable, it = std::begin(iterable)]() mutable {
			for (; it != std::end(iterable); ++it)
			{
				EntityData* entData;

				if constexpr (IsEntData) {
					entData = &*it;
				}
				else {
					auto [priority, entid] = *it;
					entData = &GetEntityData(entid);
				}

				if (entData->id == INVALID_ENTITY)
					continue; /* YES THIS IS OK TOO */

				if (hash == 0 || entData->hash == hash) {
					++it;
					return entData->id;
				}
			}
			return INVALID_ENTITY;
		};
	}

	entptr_t GetEntity(const entid_t entity) {
		const auto &entData = GetEntityData(entity);
		return entData.deleted ? nullptr : entData.ptr;
	}

	auto GetEntityIdWalker() {
		return generator<true>(entities_);
	}

	auto GetEntityIdWalker(long hash) {
		return generator<true>(entities_, hash);
	}

	auto GetEntityIdWalker(long hash, const std::string& layer) -> walker_t {

		const auto &targetLayer = layers_.find(layer);
		if (targetLayer == std::end(layers_))
			return [] {return INVALID_ENTITY; };

		return generator<false>(targetLayer->second.first, hash);
	}

	auto GetEntityIdWalker(const std::string& layer) -> walker_t {
		const auto& targetLayer = layers_.find(layer);
		if (targetLayer == std::end(layers_))
			return [] {return INVALID_ENTITY; };

		return generator<false>(targetLayer->second.first);
	}

	auto GetLayerWalker(const LayerFlags flag, bool includeFrozen = false) {
		return[this, flag, includeFrozen, it = std::begin(layers_)]() mutable->walker_t  {
			for (; it != std::end(layers_); ++it) {
				if (!includeFrozen && checkLayerFlag(it->second, LayerFlags::FROZEN))
					continue;

				if (checkLayerFlag(it->second, flag)) {
					return GetEntityIdWalker(it++->first); // TODO: optimize
				}
			}
			return { nullptr };
		};
	}

	void AddToLayer(entid_t entity, const std::string & layer, index_t priority)
	{
		auto & entData = GetEntityData(entity);
		if (entData.ptr == nullptr)
			return; /* this is probably also ok... */

		/* add to layer */
		auto & targetLayer = layers_[layer];
		targetLayer.first.insert(std::make_pair(priority, entity)); /* ~!@ TODO: duplicates*/

		/* write down layer data into entity data */
		entData.layers.emplace_back(layer, priority);
	}

	void RemoveFromLayer(entid_t entity, const std::string & layer)
	{
		auto & entData = GetEntityData(entity);
		if (entData.ptr == nullptr)
			return; /* this is probably also ok... */

		auto & targetLayer = layers_[layer];
		for (auto it = std::begin(entData.layers); it != std::end(entData.layers); ++it) {
			auto [layer_hash, priority] = *it;

			/* fast erase from layer */
			if (layer_hash == layer) {
				const auto rangeIt = targetLayer.first.equal_range(priority);
				for(auto it = rangeIt.first; it != rangeIt.second; ++it) {
					if(it->second == entity) {
						targetLayer.first.erase(it);
						break; /* should be exactly one */
					}
				}
			}

			/* now erase this it from entity data */
			entData.layers.erase(it);
			break;
		}
	}

	// временный костыль
	uint32_t GetClassCode(entid_t entity){
		const auto & entData = GetEntityData(entity);
		return entData.hash;
	}

	static auto constexpr checkLayerFlag(const layer_with_flags_t& layer, LayerFlags flag) -> bool
	{
		return static_cast<bool>(layer.second & (1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag)));
	}

	auto checkLayerFlag(const std::string& layer, LayerFlags flag)
	{
		return checkLayerFlag(layers_[layer], flag);
		//return checkLayerFlag(layers_.at(layer), flag);
	}

	void setLayerFlag(const std::string& layer, LayerFlags flag)
	{
		layers_[layer].second |= (1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
	//	layers_.at(layer).second |= (1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
	}

	void clearLayerFlag(const std::string& layer, LayerFlags flag)
	{
		layers_[layer].second &= ~(1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
		//layers_.at(layer).second &= ~(1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
	}

	void NewLifecycle()
	{
		for (const auto & entity : entities_) {
			if (entity.deleted)
			{
				const auto index = static_cast<index_t>(entity.id);
				if (index >= entities_.size())
					continue;

				_erase(entities_[index]); // release

				entities_[index] = {};//entities_[entities_.size() - 1];
				freeIndices.push_back(index);
				//entities_.pop_back();
			}
		}

	}

private:
	EntityManager()
	{
		entities_.reserve(Entity_INITIAL_SIZE);
	}

	EntityData& GetEntityData(const entid_t entity) {
		static EntityData null;

		const auto index = static_cast<index_t>(entity);

		if (index >= entities_.size()) /* calm down it's ok... */
			return null;

		const auto entptr = entities_[index];

		if (entptr.ptr == nullptr)
			return null; /* THIS IS ALSO FUCKING OK */

		/* check if valid */
		const auto entid = entptr.ptr->GetId();
		if (entity != entid) {
			return null;
		}

		return entities_[index];
	}

	entid_t PushEntity(entptr_t ptr, const char * name) {
		index_t idx;
		if(!freeIndices.empty()) {
			idx = freeIndices.back();
			freeIndices.pop_back();
		}
		else {
			idx = entities_.size();
			/* double the space */
			if (idx == entities_.capacity()) {
				entities_.reserve(idx * 2);
			}
		}

		/* calculating stamp */
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

		/* assembling entity id */
		const stamp_t stamp = ms.count();
		const entid_t id = static_cast<entid_t>(stamp) << 32 | idx;

		/* push ptr */
		if (idx == entities_.size())
			entities_.push_back({ false, MakeHashValue(name), id, ptr, {}, _strdup(name) });
		else
			entities_[idx] = { false, MakeHashValue(name), id, ptr, {}, _strdup(name) };

		return id;
	}

	/* constants */
	static const entities_t::size_type Entity_INITIAL_SIZE = 10240u;
private:
	/* members */
	entities_t entities_; /* entity container */
	layers_t layers_; /* layers container */

	std::vector<index_t> freeIndices;

	/* static asserts */
	static_assert(sizeof entities_t::size_type == sizeof index_t); /* size_type equal exactly index_t */
	static_assert(sizeof std::chrono::milliseconds == sizeof stamp_t * 2); /* we are ok with half-precision */
};


inline bool EntityFound(entid_t id)
{
	return id != EntityManager::INVALID_ENTITY;
}