#pragma once
#include <cstdint>
#include "message.h"

using entid_t = uint64_t;

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

	Entity() = default;
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