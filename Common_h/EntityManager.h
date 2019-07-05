#pragma once
#include <cstdint>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <map>
#include "message.h"
#include "vmodule_api.h"

/* Entity base class */
class Entity {
	friend class EntityManager;
public:
	enum class Stage : uint_fast8_t {
		EXECUTE,
		REALIZE,
		LOST_RENDER,
		RESTORE_RENDER
	};

	void* AttributesPointer = nullptr; // TODO: CHANGE!

	[[nodiscard]] 
	entid_t GetId() const 
	{
		return id_;
	}

	Entity(const Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(const Entity&) = delete;
	virtual ~Entity() = default;

	virtual bool Init() = 0;
	virtual void ProcessStage(Stage stage, uint32_t delta) = 0;
	virtual uint32_t ProcessMessage(MESSAGE & msg) = 0;

private:
	entid_t id_ = -1u;
};

using entptr_t = Entity *;
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
	static const entid_t INVALID_entid_t = 1u;
	enum class LayerFlags : uint_fast8_t {
		ACTIVE,
		EXECUTE,
		REALIZE,
	};

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

		/* CREATE ENTITY */
		auto* ptr = static_cast<Entity*>(pClass->CreateClass());
		if (ptr == nullptr)	{
			throw std::exception("CreateClass returned nullptr");
		}

		/* INIT ENTITY */
		if (!ptr->Init()) {
			return INVALID_entid_t;
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

				if (hash == 0 || entData->hash == hash) {
					return entData->id;
				}
			}
			return INVALID_entid_t;
		};
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
		return generator<false>(targetLayer->first, hash);
	}

	auto GetEntityIdWalker(const std::string& layer) {
		const auto targetLayer = layers_.find(layer);
		return generator<false>(targetLayer->first);
	}

	/* matreshka */
	template <LayerFlags...Flags>
	auto GetLayerWalker() {
		return [this, it = std::begin(layers_)]() mutable {
			for (; it != std::end(layers_); ++it) {
				if((checkLayerFlag(*it, Flags) & ...)) {
					return GetEntityIdWalker(it->first);
				}
			}
			GetEntityIdWalker({});
		};
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


	static auto constexpr checkLayerFlag(const layer_with_flags_t& layer, LayerFlags flag)
	{
		return static_cast<bool>(layer.second & (1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag)));
	}

	auto constexpr checkLayerFlag(const std::string& layer, LayerFlags flag)
	{
		return checkLayerFlag(layers_.at(layer), flag);
	}

	void constexpr setLayerFlag(const std::string& layer, LayerFlags flag)
	{
		layers_.at(layer).second |= (1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
	}

	void constexpr clearLayerFlag(const std::string& layer, LayerFlags flag)
	{
		layers_.at(layer).second &= ~(1u << static_cast<std::underlying_type_t<decltype(flag)>>(flag));
	}

private:
	EntityManager()
	{
		entities_.reserve(ENTITY_INITIAL_SIZE);
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
	static const entities_t::size_type ENTITY_INITIAL_SIZE = 10240u;
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
	return id != EntityManager::INVALID_entid_t;
}