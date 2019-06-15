#pragma once
#include "message.h"
#include "vmodule_api.h"
#include <cstdint>
#include <vector>
#include <chrono>

/* TODO: REMOVE THIS.... */
inline uint32_t MakeHashValue(const char* string)
{
	uint32_t hval = 0;

	while (*string != 0)
	{
		char v = *string++;
		if ('A' <= v && v <= 'Z') v += 'a' - 'A';

		hval = (hval << 4) + (unsigned long int)v;
		uint32_t g = hval & ((unsigned long int)0xf << (32 - 4));
		if (g != 0)
		{
			hval ^= g >> (32 - 8);
			hval ^= g;
		}
	}
	return hval;
}

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

	virtual bool Init() = 0;

	virtual void ProcessStage(Stage stage) = 0;

	virtual uint32_t ProcessMessage(MESSAGE & msg) = 0;

private:
	entid_t id_ = -1u;
};

using entptr_t = Entity *;

class EntityManager {
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
		const auto stamp = static_cast<stamp_t>(entity << 32);

		const auto entptr = entities_[index];

		//const auto entid = entptr->GetId();

		return entities_[index];
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

	/* typedefs */
	using index_t = uint32_t;
	using stamp_t = uint32_t;
	using entities_t = std::vector<entptr_t>;

	/* constants */
	const entities_t::size_type ENTITY_INITIAL_SIZE = 10240u;
	const entities_t::size_type INVALID_ENTITY_ID = 1u;

	/* members */
	entities_t entities_; /* entity container */

	/* static asserts */
	static_assert(sizeof entities_t::size_type == sizeof index_t); /* size_type equal exactly index_t */
	static_assert(sizeof std::chrono::milliseconds == sizeof stamp_t * 2); /* we are ok with half-precision */
};