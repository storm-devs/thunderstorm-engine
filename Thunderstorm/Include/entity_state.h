#ifndef _ENTITY_STATE_H_
#define _ENTITY_STATE_H_

#include <cstdint>

#ifndef _XBOX
#include <Windows.h>
#else
#include <xtl.h>
#endif

class ENTITY_STATE_GEN
{
public:
	ENTITY_STATE_GEN()
	{
	};

	virtual ~ENTITY_STATE_GEN()
	{
	};

	virtual void _cdecl SetState(const char* Format,...)
	{
	};
};

class ENTITY_STATE
{
public:
	ENTITY_STATE()
	{
	};

	virtual ~ENTITY_STATE()
	{
	};
	virtual uint8_t Byte() { return 0; };
	virtual uint16_t Word() { return 0; };
	virtual long Long() { return 0; };
	virtual uint32_t Dword() { return 0; };
	virtual float Float() { return 0; };
	virtual double Double() { return 0; };
	virtual char* Pointer() { return nullptr; };

	virtual void String(uint32_t buffer_size, char* buffer)
	{
	};

	virtual void MemoryBlock(uint32_t memsize, char* buffer)
	{
	};

	virtual void Struct(uint32_t sizeofstruct, char* s)
	{
	};
};

#endif
