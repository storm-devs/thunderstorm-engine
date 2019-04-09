#ifndef _VAPI_H_
#define _VAPI_H_


#ifndef _XBOX 
#include <Windows.h>
#else
#include <xtl.h>
#endif

#include "entity.h"
#include "vfile_service.h"
#include "vidwalker.h"
#include "controls.h"
#include "s_import_func.h"

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

	VFILE_SERVICE * fio;
	CONTROLS * Controls;

//------------------------------------------------------------------------------------------------
// API functions : (virtual API)

	// common programm control
	
	// shutdown core, delete all objects and close programm
	virtual void Exit()= 0;
	// restart core
	virtual void Reset()= 0;
	// return application handle
	virtual HWND GetAppHWND()= 0;
	virtual HINSTANCE GetAppInstance()= 0;
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
	virtual uint32_t SetExceptions(uint32_t _flags)= 0;
	// AND operation with core exceptions mask inversion, return current mask state
	virtual uint32_t ClrExceptions(uint32_t _flags)= 0;

	// work with objects classes
	
	// converting class name to static code (constant until next restart)
	virtual uint32_t Class_Name2Code(char * class_name)= 0;
	// find first entity with pointed class
	virtual bool FindClass(ENTITY_ID * id_PTR, char * class_name, uint32_t class_code)= 0;
	// continue searching process, started by FindClass(...) function
	virtual bool FindClassNext(ENTITY_ID * id_PTR)= 0;


	// service managment

	// return service object pointer; 
	virtual void * CreateService(char * service_name)= 0;
	// free service (unload module)
	virtual void FreeService(char * service_name)= 0;
	

	// entity managment
	
	// compare two entity ids, return true if ids is identical
	virtual bool CompareID(ENTITY_ID * ida_PTR,ENTITY_ID * idb_PTR)= 0;
	// return true if entity with that id exist
	virtual bool ValidateEntity(ENTITY_ID * id_PTR)= 0;
	// create entity with class type "class_name"; if id_PTR no null - fill this structure with entity id
	virtual bool CreateEntity(ENTITY_ID * id_PTR, char * class_name)= 0;
	// delete entity; this function can be called even if programm control still in this object
	virtual bool DeleteEntity(ENTITY_ID entity_id)= 0;
	// return entity object pointer, if this entity exist
	virtual ENTITY * GetEntityPointer(ENTITY_ID * id_PTR)= 0;
	
	// find first entity id, depending on layer configuration
	virtual bool GetEntity(ENTITY_ID * id_PTR)= 0;
	// continue enumerating entities; process started by GetEntity(...)
	virtual bool GetEntityNext(ENTITY_ID * id_PTR)= 0;
	// if layer_name isnt null, functions GetEntity and GetEntityNext work with entity in pointed layer, otherwise - with all entities
	virtual bool SetEntityScanLayer(char * layer_name)= 0;

	virtual ATTRIBUTES * Entity_GetAttributeClass(ENTITY_ID * id_PTR, char * name)=0;
	virtual char *	Entity_GetAttribute(ENTITY_ID * id_PTR, char * name)=0;
	virtual uint32_t	Entity_GetAttributeAsDword(ENTITY_ID * id_PTR, char * name, uint32_t def = 0)=0;
	virtual FLOAT	Entity_GetAttributeAsFloat(ENTITY_ID * id_PTR, char * name, FLOAT def = 0)=0;
	virtual BOOL	Entity_SetAttribute(ENTITY_ID * id_PTR, char * name, char * attribute)=0;
	virtual BOOL	Entity_SetAttributeUseDword(ENTITY_ID * id_PTR, char * name, uint32_t val)=0;
	virtual BOOL	Entity_SetAttributeUseFloat(ENTITY_ID * id_PTR, char * name, FLOAT val)=0;
	virtual void	Entity_SetAttributePointer(ENTITY_ID * id_PTR, ATTRIBUTES * pA)=0;
	//virtual uint32_t	Entity_AttributeChanged(ENTITY_ID * id_PTR, ATTRIBUTES * pA)=0;
	virtual ATTRIBUTES * Entity_GetAttributePointer(ENTITY_ID * id_PTR)=0;
	// messeges system

	// send message to an object
	virtual uint32_t _cdecl Send_Message(ENTITY_ID Destination,char * Format,...)= 0;
	
	// layer managment 
	
	// create layer with name pointed by layer_name; layer may be ordered
	virtual bool LayerCreate(char * layer_name, bool ordered, bool fail_if_exist)= 0;
	// delete layer (no objects will be deleted)
	virtual void LayerSTORM_DELETE(char * layer_name)= 0;
	// set flags to layer
	virtual void LayerSetFlags(char * layer_name, uint32_t flags)= 0;
	// clear flags for layer
	virtual void LayerClrFlags(char * layer_name, uint32_t flags)= 0;
	// get current flags configuration
	virtual uint32_t LayerGetFlags(char * layer_name)= 0;
	// insert object into layer list
	virtual bool LayerAdd(const char * layer_name, ENTITY_ID eid, uint32_t priority)= 0;
	// remove object from layer list
	virtual void LayerDel(const char * layer_name, ENTITY_ID eid)= 0;
	// delete layer content, delete all objects referenced in this layer; layer doesn't deleted
	virtual bool LayerDeleteContent(char * layer_name)= 0;
	// set layer sleeping time, layer will skip execution till this time
	virtual void LayerSetSleep(char * layer_name,uint32_t sleep_time_ms)= 0;
	// on/off execute
	virtual void LayerSetExecute(char * layer_name, bool on)= 0;
	// on/off realize
	virtual void LayerSetRealize(char * layer_name, bool on)= 0;
	// get id walker object
	virtual VIDWALKER * LayerGetWalker(char * layer_name)= 0;
		


	// save core state
	virtual bool SaveState(char * file_name)= 0;
	// force core to load state file at the start of next game loop, return false if no state file
	virtual bool InitiateStateLoading(char * file_name)= 0;

	// return current fps
	virtual uint32_t EngineFps()= 0;
	// set timer
	virtual uint32_t SetTimer(uint32_t elapse,ENTITY_ID)= 0;
	// set fixed delta time mode, (-1) - off
	virtual void SetDeltaTime(long delta_time)= 0;
	// on/off system messages
	virtual void SystemMessages(ENTITY_ID eid, bool on)= 0;
	// return time delta from prevoius frame
	virtual uint32_t GetDeltaTime()= 0;

	// return key state for predefined game keys
	virtual float GetKeyState(uint32_t key_code, uint32_t * value = nullptr)= 0;
	// declare event
	virtual VDATA * _cdecl Event(char * Event_name, char * Format = nullptr,...)= 0;

	virtual uint32_t _cdecl PostEvent(char * Event_name, uint32_t post_time, char * Format,...)= 0;
	// execute script
	virtual void Execute(char * name)=0;

	virtual uint32_t GetRDeltaTime()= 0;

	virtual void * GetSaveData(char * file_name, long & data_size)= 0;
	virtual bool SetSaveData(char * file_name, void * data_ptr, long data_size)= 0;

	virtual uint32_t SetScriptFunction(IFUNCINFO * pFuncInfo)= 0;
	virtual void DeleteScriptFunction(uint32_t nFuncHandle)= 0;

	virtual char * EngineIniFileName()=0;
	virtual uint32_t AttributeName2Code(const char * pAttributeName)=0;

	virtual void * GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex = nullptr)=0;
	virtual void SetNetActive(bool bActive) = 0;

	virtual void _cdecl BTrace(const char * Format,...) = 0;		// Trace with beep
	virtual bool IsNetActive() const = 0;
};


#endif