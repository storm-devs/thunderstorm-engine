#include <Windows.h>
#include "Core.h"
#include "s_debug.h"
#include "../../Common_h/Exs.h"
#include "file_service.h"
#include "control_stack.h"
#include "system_api.h"

char ENGINE_INI_FILE_NAME[256] = "engine.ini";

FILE_SERVICE File_Service;

CORE Core;
VAPI * _CORE_API; // ~!~ TODO: remove
VAPI * api = nullptr;

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

uint32_t Exceptions_Mask;
extern bool bTraceFilesOff;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessKeys(HWND hwnd, int code, int Press);
void EmergencyExit();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	if (!CreateEventA(nullptr, false, false, "Global\\FBBD2286-A9F1-4303-B60C-743C3D7AA7BE")
		|| GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBoxA(0, "Another instance is already running!", "Error", MB_ICONERROR);
		return 0;
	}

	_CORE_API = &Core;
	api = &Core;
	fio = &File_Service;
	_CORE_API->fio = &File_Service;
	_VSYSTEM_API = &System_Api;

	uint32_t dwMaxFPS = 0;
	INIFILE *ini = File_Service.OpenIniFile(ENGINE_INI_FILE_NAME);
	if (ini)
	{
		dwMaxFPS = (uint32_t)ini->GetLong(nullptr, "max_fps", 0);
		bDebugWindow = ini->GetLong(nullptr, "DebugWindow", 0) == 1;
		bAcceleration = ini->GetLong(nullptr, "Acceleration", 0) == 1;
		bBackspaceExit = ini->GetLong(nullptr, "BackSpaceExit", 0) == 1;
		bTraceFilesOff = ini->GetLong(nullptr, "tracefilesoff", 0) == 1;

		delete ini;
	}

	_CORE_API->SetExceptions(_X_NO_MEM | _X_NO_FILE_READ);

	Control_Stack.Init();

	MSG msg;
	
	const auto windowName = "Thunderstorm";

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
	wndclass.lpszClassName = windowName;
	wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	const auto hwnd = CreateWindowA(windowName, windowName,
		WS_POPUP,
		0, 0, 0, 0, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	Core.InitBase();


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
						if (!System_Hold && !Core.Run())
						{
							Core.CleanUp();
							System_Hold = true;
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

	Core.ReleaseBase();
	ClipCursor(nullptr);

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	ENTITY_ID eidNET;
	uint16_t wActive;

		switch (iMsg)
		{
		case WM_CREATE:
			Core.Set_Hwnd(hwnd);
			return 0;

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
			if (bDebugWindow) 
				ProcessKeys(hwnd, (int)wParam, 0);
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
			if (Core.Controls) 
				Core.Controls->EngineMessage(iMsg, wParam, lParam);
			break;
		case WM_MOUSEWHEEL:
			Core.Event("evMouseWeel", "l", (short)HIWORD(wParam));
			if (Core.Controls) 
				Core.Controls->EngineMessage(iMsg, wParam, lParam);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			Core.Event("DestroyWindow", nullptr);
			Core.Event("ExitApplication", nullptr);
			CDebug.Release();
			Core.CleanUp();
			Control_Stack.Release();
			File_Service.Close();
			CDebug.CloseDebugWindow();

			InvalidateRect(nullptr, nullptr, 0);
			PostQuitMessage(0);
			break;
		case SD_SERVERMESSAGE:
		case SD_CLIENTMESSAGE:
			if (Core.FindClass(&eidNET, "Net", 0))
				Core.Send_Message(eidNET, "luu", iMsg, wParam, lParam);
		default: ;
		}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ProcessKeys(HWND hwnd, int code, int Press)
{
	switch (code)
	{
	case VK_F5:
		if (!CDebug.IsDebug()) 
			CDebug.OpenDebugWindow(Core.hInstance);
		else
		{
			ShowWindow(CDebug.GetWindowHandle(), SW_NORMAL);
			SetFocus(CDebug.SourceView->hOwn);
		}
		break;
	default:;
	}
}

void EmergencyExit()
{
	System_Api.SetX();
	Core.TraceCurrent();
	System_Hold = true;
	Sleep(ERROR_MESSAGE_DELAY);
	ExitProcess(0xFFBADBAD);
}