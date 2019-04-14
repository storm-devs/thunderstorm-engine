#ifndef _CORE_H_
#define _CORE_H_


#ifndef _XBOX
#include <windows.h>
#else
#include <xtl.h>
#endif

#include "../../common_h/vapi.h"
//#include "..\..\common_h\input.h"

#include "c_atom.h"
#include "fsdata_list.h"
#include "layer.h"
#include "timer.h"
#include "services_list.h"
#include "layer_service.h"
#include "compiler.h"
#include <vector>
//#include "program.h"

#define ENGINE_SCRIPT_VERSION		54128

typedef struct {
	UINT iMsg; WPARAM wParam; LPARAM lParam;
} SYSTEM_MESSAGE;

#define SYSTEM_MESSAGE_STACK_SIZE		32

#define INVALID_LAYER_CODE				0xffffffff

typedef struct
{
	uint32_t engine_version;
	uint32_t Atoms_max_orbit;
	uint32_t Atoms_min_free_orbit;
	uint32_t Atoms_number;
	uint32_t Atoms_space;
	ENTITY_CREATION_TIME Creation_Time;

} CORE_STATE;

class CORE : public VAPI
{
public:
	CORE();
	~CORE();
	

	void __declspec(dllexport) __cdecl InitBase();
	void ReleaseBase();

	void CleanUp();
	void Set_Hwnd(HWND _hwnd) {App_Hwnd = _hwnd;};
	bool __declspec(dllexport) __cdecl Initialize();
	bool LoadCoreState(CORE_STATE cs);
	void ResetCore();
	bool Run();
	void ProcessSystemMessage(UINT iMsg,WPARAM wParam,LPARAM lParam);
	bool __declspec(dllexport) __cdecl LoadClassesTable();
	bool __declspec(dllexport) __cdecl CreateAtomsTable(uint32_t _space);
	C_ATOM * CreateAtom(uint32_t class_code);
	bool DeleteAtom(C_ATOM * atom_PTR);
	void ReleaseAtoms();
	//bool CreateEntity(ENTITY_ID * id_PTR, char * class_name);
	void CheckMemoryLeak_Classes();
	//bool CompareID(ENTITY_ID * ida_PTR,ENTITY_ID * idb_PTR);
	void TraceCurrent();
	bool Convert_Pointer2ID(void * _entity_pointer,ENTITY_ID * id_PTR);

	void ProcessDeleteList();
	void ProcessExecute();
	void ProcessRealize();
	void ProcessSystemMessagesBuffer();
	void ProcessRootObjectCreation();
	void ProcessStateLoading();
	void ProcessRunStart(uint32_t section_code);
	void ProcessRunEnd(uint32_t section_code);


	bool InitObject(ENTITY_ID entity_id);
	bool EraseEntity(ENTITY_ID entity_id);
	bool MarkEntityAsDeleted(ENTITY_ID entity_id);
	bool MarkEntityAsDeleted(void *);
	//ENTITY * GetEntityPointer(ENTITY_ID * entity_id);
	void CreationTimeInc();
	void RestoreEntity(ENTITY_ID entity_id, ATOM_STATE atom_state);
	C_ATOM * FitAtom(ENTITY_ID entity_id, ATOM_STATE atom_state);
	

	void FitLayer(uint32_t pos,char * layer_name,LAYER_STATE ls);
	//void EraseLayer(uint32_t dwcode);
	void ReleaseLayers();
	bool LayerCreate(char * layer_name, bool ordered, bool fail_if_exist, bool system, uint32_t system_flags);
	
	uint32_t GetLayerIndex(char * layer_name);
	//bool  VerifyLayer(char * layer_name);
	//bool  CreateLayer(char * layer_name, bool ordered);
	//void  DeleteLayer(char * layer_name);
	//void  SetLayerFlags(char * layer_name, uint32_t flags);
	//uint32_t GetLayerFlags(char * layer_name);
	//bool  AssignObjectToLayer(char * layer_name, ENTITY_ID eid, uint32_t priority);
	//void  RemoveObjectFromLayer(char * layer_name, ENTITY_ID eid);
	//bool  DeleteLayerContent(char * layer_name);
	void ValidateApiCalls();
	void CheckAutoExceptions(uint32_t xflag);
	void LayerDel(const char * layer_name, ENTITY_ID eid,bool system);
	bool LayerAdd(const char * layer_name, ENTITY_ID eid, uint32_t priority, bool system);
	void ReleaseServices();
	void __declspec(dllexport) __cdecl ProcessEngineIniFile();

	C_ATOM * GetAtom(ENTITY_ID * id_PTR);

	bool bAppActive;
	bool Memory_Leak_flag;			// true if core detected memory leak
	bool Reset_flag;
	bool Root_flag;
	bool Exit_flag;					// true if the program closing 
	bool Initialized;				// initialized flag (false at startup or after Reset())
	bool bEngineIniProcessed;
	HWND App_Hwnd;					// application handle
	char gstring[_MAX_PATH];		// general purpose string 
	bool State_loading;
	bool bEnableTimeScale;
	
	SERVICES_LIST Services_List;	// list for subsequent calls RunStart/RunEnd service functions
	
	HINSTANCE hInstance;

	CORE_STATE CoreState;
	char * State_file_name;

	std::vector<C_ATOM*> Atoms_PTR;
	uint32_t Atom_Search_Position;		// first version
	uint32_t Atom_Search_Class_Code;	// first version
	uint32_t Atom_Get_Position;		// first version
	uint32_t Scan_Layer_Code;
	uint32_t Constructor_counter;

	FSDATA_LIST DeleteEntityList;
	FSDATA_LIST DeleteLayerList;
	FSDATA_LIST DeleteServicesList;

	STRINGS_LIST ClassesOff;
	LAYER_SERVICE CommonLayers;

	TIMER Timer;
	SYSTEM_MESSAGE MessageStack[SYSTEM_MESSAGE_STACK_SIZE];
	uint32_t SystemMessagesNum;

	//INPUT * Input;

	COMPILER Compiler;
	//PROGRAM Program;

	void ProcessControls();


	float fTimeScale;
	long nSplitScreenshotGrid;

	void DumpEntitiesInfo();
	void DeleteEntities();
	void EraseEntities();
	void ClearEvents();
	void * MakeClass(char * class_name);
	void AppState(bool state);
	uint32_t MakeHashValue(const char * string);
	VMA * FindVMA(char * class_name);
	VMA * FindVMA(long hash);
	void FreeServices();
//------------------------------------------------------------------------------------------------
// API functions : (virtual API)

	// common programm control
	
	// shutdown core, delete all objects and close programm
	void Exit();
	// restart core
	void Reset();
	// return application handle
	HWND GetAppHWND();
	HINSTANCE GetAppInstance();
	// add path where core will search for modules; default: \MODULES
	bool AddModulesPath(char * _path);
	// return pointer to user data
	void * GetUserData(long * data_size);
	// copy into system user data
	void * SetUserData(void * ud_PTR,long data_size);
	// set time scale; affect on std entity functions DeltaTime parameter
	void  SetTimeScale(float _scale);
	// get curretn value of time scale; default 1.0f
	float GetTimeScale();
	// write message to system log file
	void _cdecl Trace(const char * Format,...);
	// OR operation with core exceptions mask, returned current mask state
	uint32_t SetExceptions(uint32_t _flags);
	// AND operation with core exceptions mask, returned current mask state
	uint32_t ClrExceptions(uint32_t _flags);
	// switch on/off engine gdi display 



	// work with objects classes
	
	// converting class name to static code (constant until next restart)
	uint32_t Class_Name2Code(char * class_name);	 
	// find first entity with pointed class
	bool FindClass(ENTITY_ID * id_PTR, char * class_name, uint32_t class_code);
	// continue searching process, started by FindClass(...) function
	bool FindClassNext(ENTITY_ID * id_PTR);


	// service managment

	// return service object pointer; 
	void * CreateService(char * service_name);
	// free service (unload module)
	void FreeService(char * service_name);
	

	// entity managment
	
	// compare two entity ids, return true if ids is identical
	bool CompareID(ENTITY_ID * ida_PTR,ENTITY_ID * idb_PTR);
	// return true if entity with that id exist
	bool ValidateEntity(ENTITY_ID * id_PTR);
	// create entity with class type "class_name"; if id_PTR no null - fill this structure with entity id
	bool CreateEntity(ENTITY_ID * id_PTR, char * class_name);
	bool CreateEntity(ENTITY_ID * id_PTR, char * class_name, ATTRIBUTES * ap);
	// delete entity; this function can be called even if programm control still in this object
	bool DeleteEntity(ENTITY_ID entity_id);
	// return entity object pointer, if this entity exist
	ENTITY * GetEntityPointer(ENTITY_ID * id_PTR);
	// find first entity id, depending on layer configuration
	bool GetEntity(ENTITY_ID * id_PTR);
	// continue enumerating entities; process started by GetEntity(...)
	bool GetEntityNext(ENTITY_ID * id_PTR);
	// if layer_name isnt null, functions GetEntity and GetEntityNext work with entity in pointed layer, otherwise - with all entities
	bool SetEntityScanLayer(char * layer_name);

	ATTRIBUTES * Entity_GetAttributeClass(ENTITY_ID * id_PTR, char * name);
	char *	Entity_GetAttribute(ENTITY_ID * id_PTR, char * name);
	uint32_t	Entity_GetAttributeAsDword(ENTITY_ID * id_PTR, char * name, uint32_t def = 0);
	FLOAT	Entity_GetAttributeAsFloat(ENTITY_ID * id_PTR, char * name, FLOAT def = 0);
	BOOL	Entity_SetAttribute(ENTITY_ID * id_PTR, char * name, char * attribute);
	BOOL	Entity_SetAttributeUseDword(ENTITY_ID * id_PTR, char * name, uint32_t val);
	BOOL	Entity_SetAttributeUseFloat(ENTITY_ID * id_PTR, char * name, FLOAT val);
	void	Entity_SetAttributePointer(ENTITY_ID * id_PTR, ATTRIBUTES * pA);
	uint32_t	Entity_AttributeChanged(ENTITY_ID * id_PTR, ATTRIBUTES *);
	ATTRIBUTES * Entity_GetAttributePointer(ENTITY_ID * id_PTR);
	
	// messeges system

	// send message to an object
	uint32_t _cdecl Send_Message(ENTITY_ID Destination,char * Format,...);
	
	// layer managment 
	
	// return true if this layer exist
	bool VerifyLayer(char * layer_name);
	// create layer with name pointed by layer_name; layer may be ordered
	bool LayerCreate(char * layer_name, bool ordered, bool fail_if_exist);
	// delete layer (no objects will be deleted)
	void LayerSTORM_DELETE(char * layer_name);
	// set flags to layer
	void LayerSetFlags(char * layer_name, uint32_t flags);
	// clear flags for layer
	void LayerClrFlags(char * layer_name, uint32_t flags);
	// get current flags configuration
	uint32_t LayerGetFlags(char * layer_name);
	// insert object into layer list
	bool LayerAdd(const char * layer_name, ENTITY_ID eid, uint32_t priority);
	// remove object from layer list
	void LayerDel(const char * layer_name, ENTITY_ID eid);
	// delete layer content, delete all objects referenced in this layer; layer doesn't deleted
	bool LayerDeleteContent(char * layer_name);
	// set layer sleeping time, layer will skip execution till this time
	void LayerSetSleep(char * layer_name,uint32_t sleep_time_ms);
	// on/off execute
	void LayerSetExecute(char * layer_name, bool on);
	// on/off realize
	void LayerSetRealize(char * layer_name, bool on);
	// get id walker object
	VIDWALKER * LayerGetWalker(char * layer_name);

	
	// save core state
	bool SaveState(char * file_name);
	// force core to load state file at the start of next game loop, return false if no state file
	bool InitiateStateLoading(char * file_name);

	// return current fps
	uint32_t EngineFps();
	// set timer
	uint32_t SetTimer(uint32_t elapse,ENTITY_ID id);
	// set fixed delta time mode, (-1) - off
	void SetDeltaTime(long delta_time);
	// on/off system messages
	void SystemMessages(ENTITY_ID eid, bool on);
	//
	uint32_t GetDeltaTime();
	uint32_t GetRDeltaTime();
	//
	float GetKeyState(uint32_t key_code, uint32_t * value);
	//
	VDATA * _cdecl Event(char * Event_name, char * Format,...);
	uint32_t _cdecl PostEvent(char * Event_name, uint32_t post_time, char * Format,...);
	//
	void Execute(char * name);

	void * GetSaveData(char * file_name, long & data_size);
	
	bool SetSaveData(char * file_name, void * data_ptr, long data_size);

	uint32_t SetScriptFunction(IFUNCINFO * pFuncInfo);

	void DeleteScriptFunction(uint32_t nFuncHandle);

	char * EngineIniFileName();

	uint32_t AttributeName2Code(const char * pAttributeName);

	void * GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex);

	void SetNetActive(bool bActive);

	bool IsNetActive() const;

	bool __declspec(dllexport) __cdecl LoCheck();
};

#endif