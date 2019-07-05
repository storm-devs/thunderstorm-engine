#pragma once
#include <Windows.h>
#include "vfile_service.h"
#include "controls.h"
#include "s_import_func.h"
#include <functional>
#include "entity.h"

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
	// return pointer to user data
	virtual void * GetUserData(long * data_size)= 0;
	// copy into system user data
	virtual void * SetUserData(void * ud_PTR,long data_size)= 0;
	// set time scale; affect on std entity functions DeltaTime parameter
	virtual void  SetTimeScale(float _scale)= 0;
	// get curretn value of time scale; default 1.0f
	virtual float GetTimeScale()= 0;
	// write message to system log file
	virtual void _cdecl Trace(const char * Format,...)= 0;
	// OR operation with core exceptions mask, return current mask state

	// work with objects classes
	
	// converting class name to static code (constant until next restart)
	virtual uint32_t Class_Name2Code(char * class_name)= 0;
	// find first entity with pointed class
	virtual std::function<entid_t()> GetEntityIdWalker(const char* class_name, uint32_t class_code);
	virtual std::function<entid_t()> GetEntityIdWalker(const char* class_name, uint32_t class_code, const char* layer);
	// service managment

	// return service object pointer; 
	virtual void *CreateService(char * service_name)= 0;
	

	// entity managment
	
	// compare two entity ids, return true if ids is identical
	virtual bool CompareID(entid_t * ida_PTR,entid_t * idb_PTR)= 0;
	// create entity with class type "class_name"; if id_PTR no null - fill this structure with entity id
	virtual entid_t CreateEntity(char * name)= 0;
	// delete entity; this function can be called even if programm control still in this object
	virtual bool DeleteEntity(entid_t entid_t)= 0;
	// return entity object pointer, if this entity exist
	virtual entptr_t GetEntityPointer(entid_t id_PTR)= 0;

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
	virtual uint32_t _cdecl Send_Message(entid_t Destination,char * Format,...)= 0;
	
	// layer managment 
	
	// create layer with name pointed by layer_name; layer may be ordered
	virtual bool LayerCreate(char * layer_name, bool ordered, bool fail_if_exist)= 0;
	// delete layer (no objects will be deleted)
	virtual void LayerDelete(char * layer_name)= 0;
	// set flags to layer
	virtual void LayerSetFlags(char * layer_name, uint32_t flags)= 0;
	// clear flags for layer
	virtual void LayerClrFlags(char * layer_name, uint32_t flags)= 0;
	// get current flags configuration
	virtual uint32_t LayerGetFlags(char * layer_name)= 0;
	// insert object into layer list
	virtual bool LayerAdd(const char * layer_name, entid_t eid, uint32_t priority)= 0;
	// remove object from layer list
	virtual void LayerDel(const char * layer_name, entid_t eid)= 0;
	// delete layer content, delete all objects referenced in this layer; layer doesn't deleted
	virtual bool LayerDeleteContent(char * layer_name)= 0;
	// on/off execute
	virtual void LayerSetExecute(char * layer_name, bool on)= 0;
	// on/off realize
	virtual void LayerSetRealize(char * layer_name, bool on)= 0;
	// get id walker object
	virtual std::function<entid_t()> LayerGetWalker(char * layer_name)= 0;

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
	virtual VDATA * _cdecl Event(char * Event_name, char * Format = nullptr,...)= 0;

	virtual uint32_t _cdecl PostEvent(char * Event_name, uint32_t post_time, char * Format,...)= 0;

	virtual uint32_t GetRDeltaTime()= 0;

	virtual void * GetSaveData(char * file_name, long & data_size)= 0;
	virtual bool SetSaveData(char * file_name, void * data_ptr, long data_size)= 0;

	virtual uint32_t SetScriptFunction(IFUNCINFO * pFuncInfo)= 0;
	virtual void DeleteScriptFunction(uint32_t nFuncHandle)= 0;

	virtual char * EngineIniFileName()=0;
	virtual uint32_t AttributeName2Code(const char * pAttributeName)=0;

	virtual void * GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex = nullptr)=0;
};