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
	long hash;
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

	entid_t CreateEntity(const char* name)
	{
		/* FIND VMA */
		const long hash = MakeHashValue(name);
		if (hash == 0) {
			throw std::exception("null hash");
		}
		VMA* pClass = nullptr;
		for (const auto c : _pModuleClassRoot) {
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
		if (!ptr->Init()) {
			return INVALID_ENTITY;
		}
		const auto id = PushEntity(ptr, name);
		ptr->id_ = id;

		return id;
	}

	void _erase(const EntityData & data) {
		for (auto [name, _] : data.layers) {
			RemoveFromLayer(data.id, name);
		}
		delete data.ptr;
	}

	void EraseEntity(const entid_t entity) {
		const auto index = static_cast<index_t>(entity);
		//// TODO: entities_.at
		_erase(entities_[index]); // release
		
		entities_[index] = entities_[entities_.size() - 1];
		entities_.pop_back();
	}

	void EraseAll()	{
		for(auto entity : entities_) {
			_erase(entity); // release
		}
		entities_.clear();
	}

	/* assemble requested walker (generator) */
	template <bool IsEntData, typename Iterable>
	constexpr auto&& generator(Iterable& iterable, long hash = 0) {
		return std::move([this, hash, &iterable, it = std::begin(iterable)]() mutable {
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

				if (hash == 0 || entData->hash == hash) {
					return entData->id;
				}
			}
			return INVALID_ENTITY;
		});
	}

	entptr_t GetEntity(const entid_t entity) {
		return GetEntityData(entity).ptr;
	}

	auto GetEntityIdWalker() {
		return generator<true>(entities_);
	}

	auto GetEntityIdWalker(long hash) {
		return generator<true>(entities_, hash);
	}

	auto GetEntityIdWalker(long hash, const std::string& layer) {

		const auto targetLayer = layers_.find(layer);
		return generator<false>(targetLayer->second, hash);
	}

	auto GetEntityIdWalker(const std::string& layer) {
		const auto targetLayer = layers_.find(layer);
		return generator<false>(targetLayer->first);
	}

	/* matreshka */
	template <LayerFlags...Flags>
	auto&& GetLayerWalker() {
		return std::move([this, it = std::begin(layers_)]() mutable {
			for (; it != std::end(layers_); ++it) {
				if((checkLayerFlag(*it, Flags) & ...)) {
					return GetEntityIdWalker(it->first);
				}
			}
			GetEntityIdWalker({});
		});
	}

	void AddToLayer(entid_t entity, std::string layer, index_t priority)
	{
		auto entData = GetEntityData(entity);
		if (entData.ptr == nullptr) {
			throw std::exception(); /* ~!@ */
		}

		/* add to layer */
		auto & targetLayer = layers_[std::move(layer)];
		targetLayer.first.insert(std::make_pair(priority, entity)); /* ~!@ TODO: duplicates*/

		/* write down layer data into entity data */
		entData.layers.emplace_back(layer, priority);
	}

	void RemoveFromLayer(entid_t entity, const std::string & layer)
	{
		auto entData = GetEntityData(entity);
		if (entData.ptr == nullptr) {
			throw std::exception(); /* ~!@ */
		}
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
		const auto entData = GetEntityData(entity);
		return entData.hash;
	}

	static auto constexpr checkLayerFlag(const layer_with_flags_t& layer, LayerFlags flag)
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

private:
	EntityManager()
	{
		entities_.reserve(Entity_INITIAL_SIZE);
	}

	EntityData& GetEntityData(const entid_t entity) {
		static EntityData null;

		const auto index = static_cast<index_t>(entity);

		const auto entptr = entities_[index];

		/* check if valid */
		const auto entid = entptr.ptr->GetId();
		if (entity != entid) {
			return null;
		}

		return entities_[index];
	}

	entid_t PushEntity(entptr_t ptr, const char * name) {
		const auto size = entities_.size();
		/* double the space */
		if (size == entities_.capacity()) {
			entities_.reserve(size * 2);
		}

		/* calculating stamp */
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

		/* assembling entity id */
		const stamp_t stamp = ms.count();
		const index_t index = size;
		const entid_t id = static_cast<entid_t>(stamp) << 32 | index;

		/* push ptr */
		entities_.push_back({ MakeHashValue(name), id, ptr, {}, name });

		return id;
	}

	/* constants */
	static const entities_t::size_type Entity_INITIAL_SIZE = 10240u;
private:
	/* members */
	entities_t entities_; /* entity container */
	layers_t layers_; /* layers container */

	/* static asserts */
	static_assert(sizeof entities_t::size_type == sizeof index_t); /* size_type equal exactly index_t */
	static_assert(sizeof std::chrono::milliseconds == sizeof stamp_t * 2); /* we are ok with half-precision */
};


inline bool EntityFound(entid_t id)
{
	return id != EntityManager::INVALID_ENTITY;
}