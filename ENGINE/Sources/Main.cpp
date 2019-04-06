#include <Windows.h>
#include "system_log.h"
#include "gdi_display.h"
#include "Core.h"
#include "s_debug.h"
#include "../../Common_h/Exs.h"
#include "memory_service.h"
#include "file_service.h"
#include "control_stack.h"
#include "system_api.h"


const int SPLASH_WIDTH = 600;
const int SPLASH_HEIGHT = 400;
const char SPLASH_CLASS[] = "Storm Engine";

char ENGINE_INI_FILE_NAME[256] = "engine.ini";

MEMORY_SERVICE Memory_Service;
FILE_SERVICE File_Service;
GDI_DISPLAY gdi_display;

CORE Core;
VAPI * _CORE_API; // ~!~ TODO: remove
VAPI * api = nullptr;

//VMA * _pModuleClassRoot = nullptr;
//extern std::vector<VMA*> _pModuleClassRoot { };

VFILE_SERVICE * fio = nullptr;

bool bBackspaceExit = false;
bool bDebugWindow = false, bAcceleration = false;
bool bActive = true;
bool bNetActive = false;
bool System_Hold = false;
bool Error_Flag = false;
char Last_Error[512];

CONTROL_STACK Control_Stack;
CONTROL_BLOCK Control_Block;
SYSTEM_API System_Api;
VSYSTEM_API * _VSYSTEM_API;
S_DEBUG CDebug;
CODESOURCE CodeSource;

uint32_t Exceptions_Mask;
extern bool bTraceFilesOff;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessKeys(HWND hwnd, int code, int Press);
void EmergencyExit();


/*
#include "C:\Users\espkk\source\repos\breakpad\src\exception_handler.h"

#pragma comment(lib, "common.lib")
#pragma comment(lib, "exception_handler.lib")
#pragma comment(lib, "crash_generation_client.lib")
	
bool CBK(const wchar_t* dump_path,
const wchar_t* minidump_id,
void* context,
EXCEPTION_POINTERS* exinfo,
MDRawAssertionInfo* assertion,
bool succeeded)
{
//MessageBoxA(NULL, "TEST", "TEST", MB_OK);
__debugbreak();
bool bOk = google_breakpad::ExceptionHandler::WriteMinidump(dump_path, nullptr, nullptr);
return bOk;
};*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	//~!~ TODO: replace with mutex
	if (FindWindow(SPLASH_CLASS, SPLASH_CLASS) != nullptr)
		return 0;

	//auto handler = new google_breakpad::ExceptionHandler(L".", nullptr, nullptr, nullptr, google_breakpad::ExceptionHandler::HANDLER_ALL);

	Core.hInstance = hInstance;
	_CORE_API = &Core;
	api = &Core;
	fio = &File_Service;
	_CORE_API->fio = &File_Service;
	_VSYSTEM_API = &System_Api;

	bool bMemoryStats = false;
	char sMemProfileFileName[MAX_PATH] = "";
	
	bool bFirstLaunch = true;
	uint32_t dwMaxFPS = 0;
	INIFILE *ini = File_Service.OpenIniFile(ENGINE_INI_FILE_NAME);
	if (ini)
	{
		bMemoryStats = ini->GetLong("stats", "memory_stats", 0) == 1;
		ini->ReadString(nullptr, "mem_profile", sMemProfileFileName, sizeof(sMemProfileFileName), "");

		dwMaxFPS = (uint32_t)ini->GetLong(nullptr, "max_fps", 0);
		bDebugWindow = ini->GetLong(nullptr, "DebugWindow", 0) == 1;
		bAcceleration = ini->GetLong(nullptr, "Acceleration", 0) == 1;
		bBackspaceExit = ini->GetLong(nullptr, "BackSpaceExit", 0) == 1;
		bTraceFilesOff = ini->GetLong(nullptr, "tracefilesoff", 0) == 1;
		bFirstLaunch = ini->GetLong(nullptr, "firstlaunch", 1) != 0;
		if (bFirstLaunch)
			ini->WriteLong(nullptr, "firstlaunch", 0);

		delete ini;
	}

	Memory_Service.CollectInfo(bMemoryStats);
	Memory_Service.ProcessMemProfile(sMemProfileFileName);

	if (bFirstLaunch)
	{
		PROCESS_INFORMATION pi;
		STARTUPINFO si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);

		BOOL bProcess = CreateProcessA("config.exe", nullptr, nullptr, nullptr, FALSE, NULL, nullptr, nullptr, &si, &pi);
		if (bProcess == TRUE)
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			return 0;
		}
	}

	//_CORE_API->SetExceptions(_X_NO_MEM|_X_NO_FILE|_X_NO_FILE_READ);
	_CORE_API->SetExceptions(_X_NO_MEM | _X_NO_FILE_READ);

	Control_Stack.Init();

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = sizeof(uint16_t);
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, "IDI_ICON1");
	wndclass.hCursor = LoadCursor(hInstance, "NULL_CURSOR");//LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = nullptr;
	wndclass.lpszClassName = SPLASH_CLASS;
	wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(SPLASH_CLASS, SPLASH_CLASS,
		WS_POPUP,
		//WS_POPUP|WS_CAPTION|WS_BORDER,
		0, 0, SPLASH_WIDTH, SPLASH_HEIGHT, NULL, NULL, hInstance, NULL);

	gdi_display.Init(hInstance, hwnd, SPLASH_WIDTH, SPLASH_HEIGHT);

	Core.InitBase();

	//SetProcessAffinityMask(GetCurrentProcess(), 0x3);

	bool Run_result;

	uint32_t dwOldTime = GetTickCount();
#ifndef EX_OFF
	try {
#endif

		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				if (WM_QUIT == msg.message) { break; }
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
#ifndef EX_OFF
				try {
#endif

					if (bActive || bNetActive)
					{
						if (dwMaxFPS)
						{
							uint32_t dwMS = 1000 / dwMaxFPS;
							uint32_t dwNewTime = GetTickCount();
							if (dwNewTime - dwOldTime < dwMS) continue;
							dwOldTime = dwNewTime;
						}
						if (!System_Hold) Run_result = Core.Run();
						if (!Run_result)
						{
							Core.CleanUp();
							gdi_display.Print("Unloading");
							gdi_display.Switch(true);
							if (System_Api.Exceptions || System_Api.ExceptionsNF)
							{
								gdi_display.Print("One or more exception(s) occuried on Run");
								gdi_display.Print("See log file for details");
								Sleep(ERROR_MESSAGE_DELAY);
							}
							if (Core.Memory_Leak_flag)
							{
								gdi_display.Print("Memory leak detected");
								gdi_display.Print("See log file for details");
								Sleep(ERROR_MESSAGE_DELAY);
							}

							System_Hold = true;
							SendMessage(hwnd, WM_CLOSE, 0, 0L);
						}
					}
					else
						Sleep(50);
#ifndef EX_OFF
				}
				catch (_EXS xobj)
				{
					trace("");
					switch (xobj.xtype)
					{
					case FATAL:	EmergencyExit(); break;
					case NON_FATAL:
						Core.TraceCurrent();
						System_Api.SetXNF();
						gdi_display.Print("EXCEPTION( non fatal ) : %s", xobj.string);
						break;
					}
					trace("");
				}
				catch (...)
				{
					EmergencyExit();
				}
#endif
			}
		}
#ifndef EX_OFF
	}
	catch (...)
	{
		trace("FATAL ERROR: %d", 0);
		ExitProcess(0xFFBADBAD);
	}
#endif

	if (Memory_Service.bCollectInfo)
	{
		Memory_Service.MemStat.Report();
		ini = File_Service.OpenIniFile(ENGINE_INI_FILE_NAME);
		if (ini)
		{
			if (ini->GetLong("stats", "update_mem_profile", 0) == 1)
			{
				Memory_Service.MemStat.UpdateMemoryProfile("memory.mp");
			}
			delete ini;
		}
	}
	Core.ReleaseBase();
	ClipCursor(nullptr);
	trace("System exit and cleanup:");
	trace("Mem state: User memory: %d  MSSystem: %d  Blocks: %d", Memory_Service.Allocated_memory_user, Memory_Service.Allocated_memory_system, Memory_Service.Blocks);


	Memory_Service.GlobalFree();


	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	ENTITY_ID eidNET;
	uint16_t wActive;
#ifndef EX_OFF
	try {
#endif

		switch (iMsg)
		{
		case WM_CREATE:
			Core.Set_Hwnd(hwnd);
			return 0;
		case WM_PAINT:
			gdi_display.On_Paint(hwnd);
			break;

		case WM_SYSKEYUP:
		case WM_SYSKEYDOWN:
			if (wParam == VK_F6) { return 0; }

			break;
		case WM_ACTIVATE:
			wActive = LOWORD(wParam);
			bActive = (wActive == WA_CLICKACTIVE || wActive == WA_ACTIVE);
			Core.AppState(bActive);
			break;

		case WM_KEYDOWN:
			if (bDebugWindow) ProcessKeys(hwnd, (int)wParam, 0);
			//case WM_ACTIVATE:
		case WM_KEYUP:
		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case MM_MCINOTIFY:
		case WM_LBUTTONDBLCLK:
		case WM_CHAR:
		case WM_MOUSEMOVE:
			//case 0x20A:
			//if(bActive)	Core.ProcessSystemMessage(iMsg,wParam,lParam);
			if (Core.Controls) Core.Controls->EngineMessage(iMsg, wParam, lParam);
			break;
		case 0x20A:
			Core.Event("evMouseWeel", "l", (short)HIWORD(wParam));
			if (Core.Controls) Core.Controls->EngineMessage(iMsg, wParam, lParam);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			Core.Event("DestroyWindow", nullptr);
			Core.Event("ExitApplication", nullptr);
			CDebug.Release();
			/*try { */Core.CleanUp();/* } catch(...) { gdi_display.Print("Cleanup exs");};*/
			gdi_display.Release();
			Control_Stack.Release();
			File_Service.Close();
			CDebug.CloseDebugWindow();

			//trace("System exit and cleanup:");
			//trace("Mem state: User memory: %d  MSSystem: %d  Blocks: %d",Memory_Service.Allocated_memory_user,Memory_Service.Allocated_memory_system,Memory_Service.Blocks);
			InvalidateRect(nullptr, nullptr, 0);
			PostQuitMessage(0);
			break;
		case SD_SERVERMESSAGE:
		case SD_CLIENTMESSAGE:
			if (Core.FindClass(&eidNET, "Net", 0))
			{
				Core.Send_Message(eidNET, "luu", iMsg, wParam, lParam);
			}
			break;
			//return 0;
		}

#ifndef EX_OFF
	}
	catch (...)
	{
		gdi_display.Print("ERROR in WndProc: System halted");
		System_Hold = true;

	}//*/
#endif

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ProcessKeys(HWND hwnd, int code, int Press)
{
	switch (code)
	{
		//case VK_ESCAPE:
	case VK_BACK:
		if (bBackspaceExit)
		{
			Core.Exit(); System_Hold = false;
		}
		break;
	case VK_F5:
		if (!CDebug.IsDebug()) CDebug.OpenDebugWindow(Core.hInstance);
		else
		{
			ShowWindow(CDebug.GetWindowHandle(), SW_NORMAL);
			SetFocus(CDebug.SourceView->hOwn);
		}
		break;
	default:break;
	}
}

void EmergencyExit()
{
	System_Api.SetX();
	gdi_display.Switch(true);
	Core.TraceCurrent();
	gdi_display.Print("FATAL EXCEPTION : System halted");
	System_Hold = true;
	Sleep(ERROR_MESSAGE_DELAY);
	ExitProcess(0xFFBADBAD);
}