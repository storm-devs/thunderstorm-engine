#ifndef _MODULES_TABLE_H_
#define _MODULES_TABLE_H_

#include "..\..\common_h\vmodule_api.h"

typedef struct 
{
	HINSTANCE hInst;
	DLLAPIFUNC api_func_PTR;
} MODULE_STATE;


class MODULES_TABLE
{
	uint32_t Paths_Count;
	char * * Paths_Table;
	char gstring[_MAX_PATH];
	uint32_t nModulesNum;
	MODULE_STATE * pTable;
public:

	~MODULES_TABLE();
	MODULES_TABLE();
	void Release();
	bool SetModulesPath(char * _name);		// clear all paths and add first path
	bool AddModulesPath(char * _name);		// add alternative search path
	bool LoadModule(char * name, long path_code, MODULE_STATE & ms);
	void __declspec(dllexport) __cdecl Load_ModulesTable();
	char * GetPath(uint32_t code);
	uint32_t GetModulesCount();
	VMA * GetClassesRoot(uint32_t _n);
};


/*

#include "strings_list.h"
#include "..\..\common_h\vmodule_api.h"

#define INVALID_MODULE_CODE	INVALID_ORDINAL_NUMBER

typedef struct 
{
	bool  service;
	uint32_t path_code;
	uint32_t reference;
	HINSTANCE hInst;
	DLLAPIFUNC api_func_PTR;
	VMODULE_API * mapi_PTR;
} MODULE_STATE;

class MODULES_TABLE
{
protected:

	STRINGS_LIST list;
public:

	MODULES_TABLE();
	~MODULES_TABLE();

	char * GetPath(uint32_t code);
	uint32_t  GetPathsCount();
	bool  ServiceFlag(uint32_t code);
	bool  AddModule(char * _char_PTR,uint32_t path_code);
	uint32_t GetModuleCode(char * _char_PTR);
	
	//VMODULE_API * GetModuleAPI(uint32_t code);
	void Release();
	uint32_t GetModulesCount();
	char * GetModuleName(uint32_t code);		// return module name with path	
	
	bool SetModulesPath(char * _name);		// clear all paths and add first path
	bool AddModulesPath(char * _name);		// add alternative search path
	
	uint32_t Paths_Count;
	char * * Paths_Table;
	char gstring[_MAX_PATH];				// general purpose string 

	//------------------------------------------------------------------------
	// pc/xbox modification
	bool LoadModule(char * name, long path_code, MODULE_STATE& ms);
	long Load_ModulesTable();
	
};

//*/
#endif