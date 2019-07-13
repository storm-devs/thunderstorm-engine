#pragma once

#include <windows.h>

#include "../EntityManager.h"
#include "../vapi.h"

#include "timer.h"
#include "services_list.h"
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
	//ENTITY_CREATION_TIME Creation_Time;

} CORE_STATE;

class CORE : public VAPI
{
public:
	CORE();
	~CORE() = default;
	

	void InitBase();
	void ReleaseBase();

	void CleanUp();
	void Set_Hwnd(HWND _hwnd) {App_Hwnd = _hwnd;};
	bool Initialize();
	bool LoadCoreState(CORE_STATE cs);
	void ResetCore();
	bool Run();
	bool LoadClassesTable();

	void ProcessExecute();
	void ProcessRealize();
	void ProcessStateLoading();
	void ProcessRunStart(uint32_t section_code);
	void ProcessRunEnd(uint32_t section_code);

	void CheckAutoExceptions(uint32_t xflag) const;
	void ReleaseServices();
	void ProcessEngineIniFile();

	bool bAppActive{};
	bool Memory_Leak_flag;			// true if core detected memory leak
	bool Root_flag;
	bool Exit_flag;					// true if the program closing 
	bool Initialized;				// initialized flag (false at startup or after Reset())
	bool bEngineIniProcessed;
	HWND App_Hwnd;					// application handle
	char gstring[_MAX_PATH]{};		// general purpose string 
	bool State_loading;
	bool bEnableTimeScale{};
	
	SERVICES_LIST Services_List;	// list for subsequent calls RunStart/RunEnd service functions
	
	HINSTANCE hInstance{};

	CORE_STATE CoreState{};
	char * State_file_name;

	TIMER Timer;
	SYSTEM_MESSAGE MessageStack[SYSTEM_MESSAGE_STACK_SIZE]{};
	uint32_t SystemMessagesNum;

	//INPUT * Input;

	COMPILER Compiler;
	//PROGRAM Program;

	void ProcessControls();


	float fTimeScale;
	long nSplitScreenshotGrid;

	void DumpEntitiesInfo();
	void EraseEntities();
	void ClearEvents();
	void * MakeClass(char * class_name);
	void AppState(bool state);
	uint32_t MakeHashValue(const char * string);
	VMA * FindVMA(char * class_name);
	VMA * FindVMA(long hash);
//------------------------------------------------------------------------------------------------
// API functions : (virtual API)

	// common programm control

	// shutdown core, delete all objects and close programm
	void Exit() override;
	// return application handle
	HWND GetAppHWND() override;
	HINSTANCE GetAppInstance() override;
	// set time scale; affect on std entity functions DeltaTime parameter
	void  SetTimeScale(float _scale) override;
	// write message to system log file
	void Trace(const char * Format,...) override;

	// return service object pointer; 
	void * CreateService(char * service_name) override;

	ATTRIBUTES * Entity_GetAttributeClass(entid_t id_PTR, char * name) override;
	char *	Entity_GetAttribute(entid_t id_PTR, char * name) override;
	uint32_t	Entity_GetAttributeAsDword(entid_t id_PTR, char * name, uint32_t def = 0) override;
	FLOAT	Entity_GetAttributeAsFloat(entid_t id_PTR, char * name, FLOAT def = 0) override;
	BOOL	Entity_SetAttribute(entid_t id_PTR, char * name, char * attribute) override;
	BOOL	Entity_SetAttributeUseDword(entid_t id_PTR, char * name, uint32_t val) override;
	BOOL	Entity_SetAttributeUseFloat(entid_t id_PTR, char * name, FLOAT val) override;
	void	Entity_SetAttributePointer(entid_t id_PTR, ATTRIBUTES * pA) override;
	uint32_t	Entity_AttributeChanged(entid_t id_PTR, ATTRIBUTES *);
	ATTRIBUTES * Entity_GetAttributePointer(entid_t id_PTR) override;
	
	// messeges system

	// send message to an object
	uint64_t Send_Message(entid_t Destination,char * Format,...) override;
	
	// save core state
	bool SaveState(char * file_name) override;
	// force core to load state file at the start of next game loop, return false if no state file
	bool InitiateStateLoading(char * file_name) override;

	// return current fps
	uint32_t EngineFps() override;
	// set fixed delta time mode, (-1) - off
	void SetDeltaTime(long delta_time) override;
	uint32_t GetDeltaTime() override;
	uint32_t GetRDeltaTime() override;
	//
	VDATA * Event(char * Event_name, char * Format,...) override;
	uint32_t PostEvent(char * Event_name, uint32_t post_time, char * Format,...) override;

	void * GetSaveData(char * file_name, long & data_size) override;
	
	bool SetSaveData(char * file_name, void * data_ptr, long data_size) override;

	uint32_t SetScriptFunction(IFUNCINFO * pFuncInfo) override;

	char * EngineIniFileName() override;

	void * GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex) override;

	bool LoCheck();
};