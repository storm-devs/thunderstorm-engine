#pragma once
#include "message.h"
#include "vmodule_api.h"
#include <cstdint>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <map>

using entid_t = uint64_t;

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

	virtual ~Entity() = default;

	virtual bool Init() = 0;

	virtual void ProcessStage(Stage stage, uint32_t delta) = 0;

	virtual uint32_t ProcessMessage(MESSAGE & msg) = 0;

private:
	entid_t id_ = -1u;
};

using entptr_t = Entity *;

class EntityManager {
private:
	/* typedefs */
	using index_t = uint32_t;
	using stamp_t = uint32_t;

	using layer_t = std::multimap<index_t, entid_t>;

	using entities_t = std::vector<entptr_t>;
	using layers_t = std::unordered_map<std::string, layer_t>;

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
			return INVALID_ENTITY_ID;
		}
		const auto id = PushEntity(ptr);
		ptr->id_ = id;

		return id;
	}

	void EraseEntity(const entid_t entity) {
		const auto index = static_cast<index_t>(entity);
		//// TODO: entities_.at
		entities_[index]; // release
		entities_[index] = entities_[entities_.size() - 1];
		entities_.pop_back();
	}

	entptr_t GetEntity(const entid_t entity) {
		const auto index = static_cast<index_t>(entity);

		const auto entptr = entities_[index];

		/* check if valid */
		const auto entid = entptr->GetId();
		if (entity != entid) {
			return nullptr;
		}

		return entities_[index];
	}

	void AddEntityLayer(entid_t entity, std::string layer, index_t priority)
	{
		if (GetEntity(entity) == nullptr)
			return; /* ~!@ */

		auto & targetLayer = layers_[std::move(layer)];
		targetLayer.insert(std::make_pair(priority, entity));
	}

	void ClearEntityLayer(entid_t entity, std::string layer)
	{
		/* TODO: NEED TO OPTIMIZE */
		if (GetEntity(entity) == nullptr)
			return; /* ~!@ */

		auto & targetLayer = layers_[std::move(layer)];
	}

private:
	EntityManager()
	{
		entities_.reserve(ENTITY_INITIAL_SIZE);
	}

	entid_t PushEntity(entptr_t ptr) {
		const auto size = entities_.size();
		/* double the space */
		if (size == entities_.capacity()) {
			entities_.reserve(size * 2);
		}
		/* push ptr */
		entities_.push_back(ptr);

		/* calculating stamp */
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

		/* assembling entity id */
		const stamp_t stamp = ms.count();
		const index_t index = size;
		return static_cast<entid_t>(stamp) << 32 | index;
	}

	/* constants */
	static const entities_t::size_type ENTITY_INITIAL_SIZE = 10240u;
public:
	static const entid_t INVALID_ENTITY_ID = 1u;
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
	return id != EntityManager::INVALID_ENTITY_ID;
}
