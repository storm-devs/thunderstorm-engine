#include "externs.h"

char ENGINE_INI_FILE_NAME[256] = "engine.ini";

FILE_SERVICE File_Service;

CORE Core;
VAPI* api = nullptr;

VFILE_SERVICE* fio = nullptr;

bool bDebugWindow = false, bAcceleration = false;
bool bActive = true;

bool Error_Flag = false;
bool bNetActive;
char Last_Error[512];

//CONTROL_STACK Control_Stack;
//SYSTEM_API System_Api;
//VSYSTEM_API* _VSYSTEM_API;

uint32_t Exceptions_Mask;