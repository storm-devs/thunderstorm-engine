#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "entity_id.h"
#include "attributes.h"
#include "message.h"
#include "entity_state.h"
#include "assert.h"

#include "../Shared/net/Net_Defines.h"

//-------------------------------------------------------------------------------------------------
// Pop operation (from run stack) for object constructor perform engine code
// Push and Pop operation for object destructor perform engine code
// Return code for function dont have any meaning for core in this version of engine

#define ENGINE_VERSION_MAJOR		0x2
#define ENGINE_VERSION_MINOR		0x0

#define ENGINE_VERSION				(ENGINE_VERSION_MAJOR<<16)|(ENGINE_VERSION_MINOR)
#define MODULE_API_VERSION			0x0001
#define RUN_OK						0x0

// LayeR flags
#define LRFLAG_EXECUTE		0x1
#define LRFLAG_REALIZE		0x2
#define LRFLAG_SYS_MESSAGES	0x4
#define LRFLAG_FROZEN		0x8

class CORE;

//extern VSYSTEM_API * _VSYSTEM_API;
class VDX9RENDER;
class VGEOMETRY;
class COLLIDE;

class ENTITY 
{
friend CORE;
private: 
	ENTITY_ID Entity_ID;
	bool bServer, bFirstTestServer;
	VGEOMETRY * __pGeoService;
	VDX9RENDER * __pRenderService;
	COLLIDE * __pCollideService;
	uint32_t dwNetID;

public:
	ATTRIBUTES * AttributesPointer;
	ENTITY_ID GetID(){return Entity_ID;}
	ENTITY()
	{
		AttributesPointer = nullptr;
		//_VSYSTEM_API->SetEntityPointer(this);
		//Entity_ID = _VSYSTEM_API->GetEntityID();
		//_VSYSTEM_API->Push(Entity_ID.pointer,Entity_ID.class_code);

		__pGeoService = nullptr;
		__pRenderService = nullptr;
		__pCollideService = nullptr;
		bServer = false;
		bFirstTestServer = true;
		dwNetID = DST_INVALID;
	};
	virtual ~ENTITY()
	{
	//	_VSYSTEM_API->Pop(Entity_ID.pointer);
	};
	virtual void SetEntityID(ENTITY_ID & id) final {
		id.pointer = this; 
		Entity_ID = id;
	}
	virtual bool Init()											{return true;};
	virtual void Execute(uint32_t Delta_Time)						{};
	virtual void Realize(uint32_t Delta_Time)						{};
	virtual void ProcessMessage(uint32_t,uint32_t,uint32_t)				{};
	virtual uint32_t _cdecl ProcessMessage(MESSAGE & message)		{return 0;};
	virtual bool LoadState(ENTITY_STATE * state)				{return true;};
	virtual bool CreateState(ENTITY_STATE_GEN * state_gen)		{return true;};
	virtual uint32_t AttributeChanged(ATTRIBUTES *)				{return 0;};

	virtual void SetServer(bool bServer) { this->bServer = bServer; bFirstTestServer = false; };
	virtual bool IsServer() 
	{ 
		if (!bFirstTestServer) return bServer; 
		Assert(AttributesPointer);
		Assert(AttributesPointer->FindAClass(AttributesPointer, "Server"));
		bServer = AttributesPointer->GetAttributeAsDword("Server") != 0;
		bFirstTestServer = false;
		return bServer;
	};
	virtual bool IsClient() { return !IsServer(); };

	virtual uint32_t GetNetID() { return dwNetID; };
	virtual void SetNetID(uint32_t dwNetID) { this->dwNetID = dwNetID; };

	virtual void LostRender() {};
	virtual void RestoreRender() {};
};

#endif