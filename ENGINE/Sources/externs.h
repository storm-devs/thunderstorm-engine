#ifndef _EXTERNS_H_
#define _EXTERNS_H_

#include "Core.h"
#include "file_service.h"
#include "../../Common_h/vapi.h"

extern CORE Core;
extern VAPI* api;

extern uint32_t Exceptions_Mask;
extern FILE_SERVICE File_Service;
extern char Last_Error[512];
extern bool Error_Flag;
extern char * CTP_Name[];
//extern SYSTEM_API System_Api;
//extern VSYSTEM_API * _VSYSTEM_API;

extern char ENGINE_INI_FILE_NAME[256];
extern bool bDebugWindow, bAcceleration;
extern bool bNetActive;

extern bool bActive;
extern bool bTraceFilesOff;

#define SET_ERROR(x) {Error_Flag = true; if(x) strcpy_s(Last_Error,x); }
#define GET_ERROR Last_Error
#define CLR_ERROR {Error_Flag = false; Last_Error[0] = 0;}
#define TST_ERROR Error_Flag
//#define SET_CODE_STATE(a,b) {Code_State.ctp = (word)a; Code_State.class_code = b; Memory_Service.SetState((word)a,b,0); }
//#define CODE_CORE {Code_State.ctp = (word)CTP_CORE; Code_State.class_code = 0xffffffff; Memory_Service.SetState((word)CTP_CORE,0xffffffff,0);}
#define CTP_NAME(x) CTP_Name[x]

//#define PUSH_CONTROL(ptr,code,c) 
//#define POP_CONTROL(control_block_ptr) 


#endif