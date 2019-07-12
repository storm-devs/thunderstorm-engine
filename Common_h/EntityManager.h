#pragma once
#include <cstdint>
#include <vector>
#include <chrono>
#include <set>
#include <algorithm>
#include "Entity.h"
#include "vmodule_api.h"
#include "../Shared/layers.h"

class EntityManager final {
	/* typedefs */
	using entid_index_t = uint32_t; /* 16 bits are enough tho' */
	using entid_stamp_t = uint32_t;

	using priority_t = uint32_t;

	using entity_index_t = uint16_t;

	using hash_t = uint32_t;

public: // TODO: this is a workaround. i need to implement specific iterator returning only id
	/* entity structure */
	struct EntityInternalData {
		using layer_mask_t = uint32_t;

		bool deleted;
		layer_mask_t mask;
		priority_t priorities[max_layers_num];
		entptr_t ptr;
		entid_t id;
		hash_t hash;
	};

public:
	using layer_index_t = uint8_t;

	/* layer structure */
	struct Layer
	{
		enum Type : uint8_t {
			common,
			execute,
			realize
		};

		std::array<std::pair<priority_t, entid_t>, max_ent_in_layer> entities;
		entity_index_t actual_size;
		Type type;
		bool frozen;
	};

private:
	/* static constexpr array of layers */
	static inline std::array<Layer, max_layers_num> layers_;

	/* static constexpr array of entities and actual size */
	static inline std::pair<std::array<EntityInternalData, max_ent_num>, entity_index_t> entities_;

	/* stack for indices of erased entities: static constexpr array and top counter */
	static inline std::pair<std::array<entity_index_t, max_ent_num>, entity_index_t> freeIndices_;

public:
	using EntityVector = const std::vector<entid_t>;
	using LayerIterators = std::pair<decltype(Layer::entities)::const_iterator, decltype(Layer::entities)::const_iterator>;
	using AllEntIterators = std::pair<decltype(entities_.first)::const_iterator, decltype(entities_.first)::const_iterator>;

	/* fully static constexpr class */
	EntityManager() = delete;

	static auto GetClassCode(const entid_t id) {
		const auto& entData = GetEntityData(id);

		return entData.hash;
	}

	/* layer functioning is fully static constexpr */
	static void AddToLayer(const layer_index_t index, const entid_t id, const priority_t priority) {
		assert(index < max_layers_num); // valid index
		assert(entities_.first[static_cast<entid_index_t>(id)].mask & (1 << index)); // mask shall be set

		auto& layer = layers_[index];
		auto& arr = layer.entities;
		auto& size = layer.actual_size;

		assert(size < max_ent_in_layer);

		// TODO: investigate if duplicate check is needed

		const auto targetIdx = std::upper_bound(std::begin(arr), std::begin(arr) + size, std::pair<priority_t, entid_t>{ priority, {} },
			[](auto& lhs, auto& rhs) { return lhs.first < rhs.first; }) - std::begin(arr);

		// if this is not last element
		if (targetIdx != size) {
			// shift array
			for (auto i = size; i < targetIdx; --i) {
				arr[i] = arr[i - 1];
			}
		}

		arr[targetIdx] = { priority, id };
		++size;
	}

	static void RemoveFromLayer(const layer_index_t index, const entid_t id) {
		const auto& entData = GetEntityData(id);
		return RemoveFromLayer(index, id, entData.priorities[index]);
	}

	static void RemoveFromLayer(const layer_index_t index, const entid_t id, const priority_t priority) {
		assert(index < max_layers_num);

		auto& layer = layers_[index];
		auto& arr = layer.entities;
		auto& size = layer.actual_size;

		const auto lowerIdx = std::lower_bound(std::begin(arr), std::begin(arr) + size,  std::pair<priority_t, entid_t>{ priority, {} },
			[](auto& lhs, auto& rhs) { return lhs.first < rhs.first; }) - std::begin(arr);

		assert(lowerIdx < size); // is this ok?

		for (auto i = lowerIdx; i < size && arr[i].first == priority; ++i) {
			if (arr[i].second == id) {
				// shift array
				for (auto j = i; j < size; ++j) {
					arr[i] = arr[i + 1];
				}
			}
		}
	}

	static entid_t CreateEntity(const char* name, ATTRIBUTES* attr = nullptr)
	{
		/* FIND VMA */
		const auto hash = MakeHashValue(name);
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
		const auto id = PushEntity(ptr, hash);
		ptr->data_.id = id;
		ptr->AttributesPointer = attr;

		// then init
		if (!ptr->Init()) {
			// mark as deleted if fail 
			const auto index = static_cast<entid_index_t>(id);
			auto& entityData = entities_.first[index];
			entityData.deleted = true;
			return invalid_entity;
		}

		// return entid_t if success
		return id;
	}

	static void _erase(const EntityInternalData & data) {
		auto mask = data.mask;

		// remove from layers
		for(unsigned i = 0; i < sizeof(mask) * 8; ++i) {
			if ((mask >> i) & 1) {
				RemoveFromLayer(i, data.id, data.priorities[i]);
			}
		}

		delete data.ptr;
	}

	static void EraseEntity(const entid_t entity) {
		const auto & entData = GetEntityData(entity);
		if (entData.ptr == nullptr)
			return;
	
		// validate 
		if (entData.ptr->GetId() != entity) 
			return; /* already replaced by another entity */

		const auto index = static_cast<entid_index_t>(entity);
		entities_.first[index].deleted = true;
	}

	static constexpr void EraseAll()	{
		for (auto & entity : entities_.first) {
			entity.deleted = true;
		}
	}

	static entptr_t GetEntityPointer(const entid_t entity) {
		const auto &entData = GetEntityData(entity);
		return entData.deleted ? nullptr : entData.ptr;
	}

	static auto GetEntityIdVector(const Layer::Type type) -> EntityVector {
		std::vector<entid_t> result;
		result.reserve(max_ent_num); // TODO: investigate memory consumption

		for (auto it = std::begin(layers_); it != std::end(layers_); ++it) {
			if (it->frozen)
				continue;

			if (it->type == type) {
				const auto end = std::begin(it->entities) + it->actual_size;
				for (const auto ent_it = std::begin(it->entities); ent_it != end; ++it)
					result.push_back(ent_it->second);
			}
		}

		return result;
	}

	// TODO: hash...
	static auto GetEntityIdVector(const char * name) -> EntityVector {
		return GetEntityIdVector(MakeHashValue(name));
	}

	static auto GetEntityIdVector(const uint32_t hash) -> EntityVector {
		std::vector<entid_t> result;
		result.reserve(max_ent_num); // TODO: investigate memory consumption

		const auto& arr = entities_.first;
		const auto size = entities_.second;

		for (auto it = std::begin(arr); it != std::begin(arr) + size; ++it) {
			if (it->hash == hash && !it->deleted) {
				result.push_back(it->id);
			}
		}

		return result;
	}

	static constexpr auto GetEntityIdIterators(const layer_index_t index) -> LayerIterators {
		assert(index < max_layers_num);

		auto& layer = layers_[index];

		return std::pair { std::begin(layer.entities), std::begin(layer.entities) + layer.actual_size };
	}

	/* this is (temporary) workaround solution */
	static constexpr auto GetEntityIdIterators() -> AllEntIterators{
		return std::pair{ std::begin(entities_.first), std::begin(entities_.first) + entities_.second };
	}

	static constexpr auto GetEntityId(const char * name) -> entid_t {
		return GetEntityId(MakeHashValue(name));
	}

	static constexpr auto GetEntityId(const uint32_t hash) -> entid_t {
		const auto& arr = entities_.first;
		const auto size = entities_.second;

		for (auto it = std::begin(arr); it != std::begin(arr) + size; ++it) {
			if (it->hash == hash && !it->deleted) {
				return it->id;
			}
		}

		return invalid_entity;
	}

	static constexpr auto GetLayerType(const layer_index_t index)
	{
		assert(index < max_layers_num);

		return layers_[index].type;
	}

	static constexpr void SetLayerType(const layer_index_t index, const Layer::Type type)
	{
		assert(index < max_layers_num);

		layers_[index].type = type;
	}

	static constexpr void SetLayerFrozen(const layer_index_t index, const bool freeze) {
		assert(index < max_layers_num);

		layers_[index].frozen = freeze;
	}

	static constexpr void PushFreeIndex(entity_index_t index) {
		auto& stack = freeIndices_.first;
		auto& top = freeIndices_.second;
		
		assert(top < max_ent_num);

		stack[top++] = index;
	}

	/* new lifecycle is started at the end of each frame. it's time to cleanup */
	static constexpr void NewLifecycle()
	{
		auto & arr = entities_.first;
		const auto size = entities_.second;
		for (const auto & entityData : arr) {
			if (entityData.deleted)
			{
				const auto index = static_cast<entid_index_t>(entityData.id);
				if (index >= size)
					continue;

				_erase(arr[index]); // release
				arr[index] = {}; // erase entity data
				PushFreeIndex(index); // push free index to stack instead of shifting
			}
		}

	}

	static EntityInternalData& GetEntityData(const entid_t entity) {
		static EntityInternalData null;

		const auto index = static_cast<entid_index_t>(entity);

		if (index >= entities_.second) /* calm down it's ok... */
			return null;

		auto & data = entities_.first[index];

		if (data.ptr == nullptr)
			return null; /* THIS IS ALSO FUCKING OK */

		/* check if valid */
		const auto entid = data.ptr->GetId();
		if (entity != entid) {
			return null;
		}

		return data;
	}

	static constexpr entid_t PushEntity(entptr_t ptr, hash_t hash) {
		auto& arr = entities_.first;
		auto& size = entities_.second;

		assert(size < max_ent_num);

		auto& stack = freeIndices_.first;
		auto& top = freeIndices_.second;

		/* check if free indices available */
		entid_index_t idx = top != 0 ? stack[--top] : size;

		/* calculate stamp */
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

		/* assemble entity id */
		const entid_stamp_t stamp = ms.count();
		const entid_t id = static_cast<entid_t>(stamp) << 32 | idx;

		/* push entity data */
		arr[idx] = { {}, {}, {}, ptr, id, hash };
		++size;
		
		return id;
	}

	/* static constexpr asserts */
	static_assert(sizeof std::chrono::milliseconds == sizeof entid_stamp_t * 2); /* we are ok with half-precision */
};