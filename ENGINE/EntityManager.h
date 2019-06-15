#pragma once
#include "../Common_h/message.h"
#include <cstdint>
#include <vector>
#include <chrono>

using entid_t = uint64_t;

class Entity {
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

	virtual void ProcessMessage(MESSAGE & msg) = 0;

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

	entid_t CreateEntity(const char* ent) {
		entptr_t ptr = nullptr; //////// TODO:
		return CreateEntity(ptr);
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

	entid_t CreateEntity(entptr_t ptr) {
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

	/* members */
	entities_t entities_; /* entity container */

	/* static asserts */
	static_assert(sizeof entities_t::size_type == sizeof index_t); /* size_type equal exactly index_t */
	static_assert(sizeof std::chrono::milliseconds == sizeof stamp_t * 2); /* we are ok with half-precision */
};