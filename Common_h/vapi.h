#pragma once
#include <Windows.h>
#include <functional>
#include "controls.h"
#include "s_import_func.h"
#include "Walker.h"
#include "vdata.h"
#include "Layer.h"

//class Entity;
//using entid_t = uint64_t;
//using entptr_t = Entity *;

struct MSTATE
{
	unsigned long nBlocksNum;
	unsigned long nMemorySize;
};

class VAPI
{
public:
	VAPI(){};
	virtual ~VAPI(){};

	CONTROLS * Controls;

//------------------------------------------------------------------------------------------------
// API functions : (virtual API)
	// shutdown core, delete all objects and close programm
	virtual void Exit() = 0;
	// return application handle
	virtual HWND GetAppHWND() = 0;
	virtual HINSTANCE GetAppInstance() = 0;
	// set time scale; affect on std entity functions DeltaTime parameter
	virtual void  SetTimeScale(float _scale)= 0;
	// get curretn value of time scale; default 1.0f
	virtual float GetTimeScale()= 0;
	// write message to system log file
	virtual void Trace(const char * Format,...)= 0;
	// OR operation with core exceptions mask, return current mask state

	// work with objects classes
	
	// converting class name to static code (constant until next restart)
	virtual uint32_t Class_Name2Code(char * class_name)= 0;
	// find first entity with pointed class
	virtual walker_t GetEntityIdWalker(const char* class_name, uint32_t class_code = 0) = 0;
	virtual walker_t GetEntityIdWalker(const char* class_name, const char* layer, uint32_t class_code = 0) = 0;
	// service managment

	// return service object pointer; 
	virtual void *CreateService(char * service_name)= 0;
	

	// entity managment
	
	// create entity with class type "class_name"; if id_PTR no null - fill this structure with entity id
	virtual entid_t CreateEntity(char* name, ATTRIBUTES* attr = nullptr) = 0;

	virtual void EraseEntity(entid_t id) = 0;

	// return entity object pointer, if this entity exist
	virtual entptr_t GetEntityPointer(entid_t id_PTR)= 0;

	virtual uint32_t GetEntityClassCode(entid_t entity) = 0;

	virtual ATTRIBUTES * Entity_GetAttributeClass(entid_t id_PTR, char * name)=0;
	virtual char *	Entity_GetAttribute(entid_t id_PTR, char * name)=0;
	virtual uint32_t	Entity_GetAttributeAsDword(entid_t id_PTR, char * name, uint32_t def = 0)=0;
	virtual FLOAT	Entity_GetAttributeAsFloat(entid_t id_PTR, char * name, FLOAT def = 0)=0;
	virtual BOOL	Entity_SetAttribute(entid_t id_PTR, char * name, char * attribute)=0;
	virtual BOOL	Entity_SetAttributeUseDword(entid_t id_PTR, char * name, uint32_t val)=0;
	virtual BOOL	Entity_SetAttributeUseFloat(entid_t id_PTR, char * name, FLOAT val)=0;
	virtual void	Entity_SetAttributePointer(entid_t id_PTR, ATTRIBUTES * pA)=0;
	//virtual uint32_t	Entity_AttributeChanged(entid_t id_PTR, ATTRIBUTES * pA)=0;
	virtual ATTRIBUTES * Entity_GetAttributePointer(entid_t id_PTR)=0;
	// messeges system

	// send message to an object
	virtual uint32_t Send_Message(entid_t Destination,char * Format,...)= 0;
	
	// layer managment 

	// STUB
	virtual bool LayerCreate(char* layer_name, bool ordered, bool fail_if_exist) { return true; }


	// set flags to layer
	virtual bool LayerCheck(char* layer_name, LayerFlags flag) = 0;
	// get current flags configuration
	virtual void LayerAdd(const char * layer_name, entid_t eid, uint32_t priority)= 0;
	// remove object from layer list
	virtual void LayerDel(const char * layer_name, entid_t eid)= 0;
	// on/off execute
	virtual void LayerSetExecute(char * layer_name, bool on)= 0;
	// on/off realize
	virtual void LayerSetRealize(char * layer_name, bool on)= 0;
	// on/off freeze
	virtual void LayerSetFreeze(char* layer_name, bool on) = 0;
	// get id walker object
	virtual walker_t LayerGetWalker(char * layer_name = nullptr)= 0;

	// save core state
	virtual bool SaveState(char * file_name)= 0;
	// force core to load state file at the start of next game loop, return false if no state file
	virtual bool InitiateStateLoading(char * file_name)= 0;

	// return current fps
	virtual uint32_t EngineFps()= 0;
	// set fixed delta time mode, (-1) - off
	virtual void SetDeltaTime(long delta_time)= 0;
	// return time delta from prevoius frame
	virtual uint32_t GetDeltaTime()= 0;

	// declare event
	virtual VDATA * Event(char * Event_name, char * Format = nullptr,...)= 0;

	virtual uint32_t PostEvent(char * Event_name, uint32_t post_time, char * Format,...)= 0;

	virtual uint32_t GetRDeltaTime()= 0;

	virtual void * GetSaveData(char * file_name, long & data_size)= 0;
	virtual bool SetSaveData(char * file_name, void * data_ptr, long data_size)= 0;

	virtual uint32_t SetScriptFunction(IFUNCINFO * pFuncInfo)= 0;
	virtual void DeleteScriptFunction(uint32_t nFuncHandle)= 0;

	virtual char * EngineIniFileName()=0;
	virtual uint32_t AttributeName2Code(const char * pAttributeName)=0;

	virtual void * GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex = nullptr)=0;
};