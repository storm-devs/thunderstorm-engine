#include "Core.h"
#include "externs.h"
#include <cinttypes>
#include "../../Common_h/dx9render.h"

CREATE_SERVICE(CONTROLS)

uint32_t dwNumberScriptCommandsExecuted = 0;
auto constexpr CORE_DEFAULT_ATOMS_SPACE = 128;

typedef struct
{
	uint32_t  code;
	void * pointer;
} CODE_AND_POINTER;

CORE::CORE()
{
	Initialized = false;
	bEngineIniProcessed = false;
	App_Hwnd = nullptr;
	State_file_name = nullptr;
	PZERO(&CoreState,sizeof(CoreState));
	CoreState.engine_version = 00000000;
	SystemMessagesNum = 0;
	Exit_flag = false;
	State_loading = false;
	Memory_Leak_flag = false;
	Controls = nullptr;
	fTimeScale = 1.0f;
	//bNetActive = false;
	nSplitScreenshotGrid = 4;
}

void CORE::ResetCore()
{
	Initialized = false;
	bEngineIniProcessed = false;

	ReleaseServices();

	Services_List.Release();

	SystemMessagesNum = 0;

	STORM_DELETE(State_file_name); 
}

void CORE::CleanUp()
{
	Initialized = false;
	bEngineIniProcessed = false;
	ReleaseServices();
	Compiler.Release();
	Services_List.Release();
	Services_List.Release();
	delete State_file_name;
}

void CORE::InitBase()
{
	LoadClassesTable();
}

void CORE::ReleaseBase()
{
	Compiler.Token.Release();
}

bool CORE::LoCheck()
{
	// ~!~
	entid_t test_eid = CreateEntity("LocationP");
	if (!EntityFound(test_eid))
		return false;
	auto* pE = entityManager.GetEntity(test_eid);
	pE->ProcessStage(Entity::Stage::EXECUTE, ENGINE_SCRIPT_VERSION);
	DeleteEntity(test_eid);
	return true;
}

bool CORE::Run()
{
	bool bDebugWindow = true;
	if (bDebugWindow && api->Controls && api->Controls->GetDebugAsyncKeyState(VK_F7)<0) 
		DumpEntitiesInfo();
	dwNumberScriptCommandsExecuted = 0;

	if (Exit_flag) return false;				// exit

	Timer.Run(); // calc delta time

	auto pVCTime = static_cast<VDATA *>(api->GetScriptVariable("iRealDeltaTime"));
	if (pVCTime) 
		pVCTime->Set(static_cast<long>(GetRDeltaTime()));

	SYSTEMTIME st;
	GetLocalTime(&st);

	auto pVYear = static_cast<VDATA *>(api->GetScriptVariable("iRealYear"));
	auto* pVMonth = static_cast<VDATA *>(api->GetScriptVariable("iRealMonth"));
	auto* pVDay = static_cast<VDATA *>(api->GetScriptVariable("iRealDay"));

	if (pVYear) pVYear->Set(long(st.wYear));
	if (pVMonth) pVMonth->Set(long(st.wMonth));
	if (pVDay) pVDay->Set(long(st.wDay));

	//if (!bNetActive)
	{
		if(Controls && Controls->GetDebugAsyncKeyState('R')<0) Timer.Delta_Time *= 10;
		if(Controls && Controls->GetDebugAsyncKeyState('Y')<0) Timer.Delta_Time = static_cast<uint32_t>(Timer.Delta_Time * 0.2f);

		Timer.Delta_Time = static_cast<uint32_t>(Timer.Delta_Time * fTimeScale);
		Timer.fDeltaTime *= fTimeScale;
	}

	auto* pVData = static_cast<VDATA *>(GetScriptVariable("fHighPrecisionDeltaTime", nullptr));
	if (pVData) pVData->Set(Timer.fDeltaTime * 0.001f);

	if(!Initialized)
	{
		Initialize();	// initialization at start or after reset
		if (!LoCheck())
			throw;
	}
	if(!bEngineIniProcessed) ProcessEngineIniFile();

	Compiler.ProcessFrame(Timer.GetDeltaTime());
	Compiler.ProcessEvent("frame");

	ProcessStateLoading();

	ProcessRunStart(SECTION_ALL);
	ProcessExecute();						// transfer control to objects via Execute() function
	ProcessRealize();						// transfer control to objects via Realize() function

	if (Controls && bActive)
		Controls->Update(Timer.rDelta_Time);

	if (Controls && bActive) ProcessControls();

	ProcessRunEnd(SECTION_ALL);

	// ~!~
	if( Controls && Controls->GetDebugAsyncKeyState(VK_F8)<0 &&
		Controls->GetDebugAsyncKeyState(VK_SHIFT)<0 &&
		Controls->GetDebugAsyncKeyState(VK_CONTROL)<0 )
	{
		Timer.Delta_Time = 0;
		Timer.fDeltaTime = 0.f;

		auto* pRender = (VDX9RENDER*)CreateService("DX9RENDER");
		CVECTOR pos,ang{};
		float fPersp;
		pRender->GetCamera(pos,ang,fPersp);

		for( long y=0; y<nSplitScreenshotGrid; y++ )
			for( long x=0; x<nSplitScreenshotGrid; x++ )
			{
				CVECTOR tmpang = ang;
				tmpang.y += ((float)x - (nSplitScreenshotGrid-1)*0.5f) * (fPersp/nSplitScreenshotGrid);
				tmpang.x += ((float)y - (nSplitScreenshotGrid-1)*0.5f) * (fPersp/nSplitScreenshotGrid);
				pRender->SetCamera(&pos,&tmpang,fPersp/nSplitScreenshotGrid);
				pRender->SaveShoot();
				ProcessRealize();
			}

		pRender->SetCamera(&pos,&ang,fPersp);
	}

	return true;
}

void CORE::ProcessControls()
{
	CONTROL_STATE cs;
	USER_CONTROL  uc;

	if(!Controls) 
		return;

	for(long n = 0;n<Controls->GetControlsNum();n++)
	{
		Controls->GetControlState(n,cs);
		if(cs.state == CST_ACTIVATED)
		{
			Controls->GetControlDesc(n,uc);
			Event("Control Activation","s",uc.name);
		}
		else
		if(cs.state == CST_INACTIVATED)
		{
			Controls->GetControlDesc(n,uc);
			Event("Control Deactivation","s",uc.name);
		}

	}
}

//-------------------------------------------------------------------------------------------------
// internal functions
//-------------------------------------------------------------------------------------------------
bool CORE::Initialize()
{
	ResetCore();

	Initialized = true;

	return true;
}

bool CORE::LoadCoreState(CORE_STATE cs)
{
	ResetCore();

	CoreState = cs;

	Initialized = true;
	bEngineIniProcessed = true;

	return true;
}

void CORE::ProcessEngineIniFile()
{
	char String[_MAX_PATH];

	bEngineIniProcessed = true;

	INIFILE* engine_ini = File_Service.OpenIniFile(ENGINE_INI_FILE_NAME);
	if(engine_ini == nullptr) throw std::exception("no 'engine.ini' file");

	bool res = engine_ini->ReadString(nullptr, "program_directory", String, sizeof(String), "");
	if(res)
	{
		Compiler.SetProgramDirectory(String);
	}

	res = engine_ini->ReadString(nullptr,"controls",String,sizeof(String),"");
	if(res)
	{
		api->Controls = (CONTROLS *)MakeClass(String);
		if(api->Controls == nullptr) api->Controls = (CONTROLS *)MakeClass("controls");

	}
	else
	{
		if(Controls) delete Controls; Controls = nullptr;

		api->Controls = new CONTROLS;
	}

	res = engine_ini->ReadString(nullptr,"run",String,sizeof(String),"");
	if(res)
	{
		if(!Compiler.CreateProgram(String)) throw std::exception("fail to create program");
		if(!Compiler.Run()) throw std::exception("fail to run program");
		// Тест версии скрипта
		long iScriptVersion = 0xFFFFFFFF;
		VDATA * pVScriptVersion = (VDATA *)api->GetScriptVariable("iScriptVersion");
		if (pVScriptVersion) pVScriptVersion->Get(iScriptVersion);

		if (iScriptVersion != ENGINE_SCRIPT_VERSION)
		{
			ShowCursor(true);
			MessageBoxA(nullptr, "Wrong script version", "Error", MB_OK);
			Compiler.ExitProgram();
		}
	}

	delete engine_ini;
}

bool CORE::LoadClassesTable()
{
	for(auto c : _pModuleClassRoot)
	{
		const auto hash = MakeHashValue(c->GetName());
		c->SetHash(hash);
	}

	return true;
}

void CORE::CheckAutoExceptions(uint32_t = 0) const
{
	spdlog::warn("exception thrown");
}

entid_t CORE::CreateEntity(char * name)
{
	return entityManager.CreateEntity(name);
}

uint32_t CORE::Class_Name2Code(char * class_name)
{
	return MakeHashValue(class_name);
}

walker_t CORE::GetEntityIdWalker(const char * class_name, uint32_t class_code)
{
	const auto hash = class_name ? MakeHashValue(class_name) : class_code;
	return entityManager.GetEntityIdWalker(hash);
}

walker_t CORE::GetEntityIdWalker(const char* class_name, const char * layer, uint32_t class_code)
{
	const auto hash = class_name ? MakeHashValue(class_name) : class_code;
	return entityManager.GetEntityIdWalker(hash, layer);
}


Entity * CORE::GetEntityPointer(entid_t id_PTR)
{
	return entityManager.GetEntity(id_PTR);
}

uint32_t CORE::GetEntityClassCode(entid_t entity){
	return entityManager.GetClassCode(entity);
}

void CORE::EraseEntity(entid_t id)
{
	entityManager.EraseEntity(id);
}

void CORE::LayerSetExecute(char* layer_name, bool on)
{
	if(on)
		entityManager.setLayerFlag(layer_name, LayerFlags::EXECUTE);
	else
		entityManager.clearLayerFlag(layer_name, LayerFlags::EXECUTE);
}

void CORE::LayerSetRealize(char* layer_name, bool on)
{
	if (on)
		entityManager.setLayerFlag(layer_name, LayerFlags::REALIZE);
	else
		entityManager.clearLayerFlag(layer_name, LayerFlags::REALIZE);
}

void CORE::LayerSetFreeze(char* layer_name, bool on)
{
	if (on)
		entityManager.setLayerFlag(layer_name, LayerFlags::FROZEN);
	else
		entityManager.clearLayerFlag(layer_name, LayerFlags::FROZEN);
}


walker_t CORE::LayerGetWalker(char * layer_name)
{
	if(layer_name != nullptr)
		return entityManager.GetEntityIdWalker(layer_name);
	return entityManager.GetEntityIdWalker();
}

void CORE::Exit() { Exit_flag = true; }

//------------------------------------------------------------------------------------------------
// return application window handle
//
HWND CORE::GetAppHWND() { return App_Hwnd; }
HINSTANCE CORE::GetAppInstance() { return hInstance; }

void CORE::SetTimeScale(float _scale)
{
	fTimeScale = _scale;
}
float CORE::GetTimeScale()
{
	return fTimeScale;
}

//------------------------------------------------------------------------------------------------
// transfer message arguments and program control to entity, specified by Destination id
//
uint32_t CORE::Send_Message(entid_t Destination,char * Format,...)
{
	MESSAGE message;
	entptr_t ptr = entityManager.GetEntity(Destination); // check for valid destination
	message.Reset(Format);									// reset message class
	PZERO(&message.Sender_ID,sizeof(entid_t));
	va_start(message.args,Format);
	uint32_t rc = ((Entity *)ptr)->ProcessMessage(message);	// transfer control
	va_end(message.args);
	return rc;
}

bool CORE::LayerCreate(char* layer_name, bool ordered, bool fail_if_exist)
{
	return true;
}

bool CORE::LayerCheck(char* layer_name, LayerFlags flag)
{
	return entityManager.checkLayerFlag(layer_name, flag);
}

void CORE::LayerAdd(const char* layer_name, entid_t eid, uint32_t priority)
{
	entityManager.AddToLayer(eid, layer_name, priority);
}

void CORE::LayerDel(const char* layer_name, entid_t eid)
{
	entityManager.RemoveFromLayer(eid, layer_name);
}

uint32_t CORE::PostEvent(char * Event_name, uint32_t post_time, char * Format,...)
{
	MESSAGE_SCRIPT * pMS;
	MESSAGE message;

	entid_t id;

	if(Format != nullptr)
	{
		pMS = new MESSAGE_SCRIPT;
		va_start(message.args,Format);
		message.Reset(Format);
		pMS->Reset(Format);

		bool bAction = true;
		while(bAction)
		{
			switch(message.GetCurrentFormatType())
			{

				//-------------------------------------
				case 'l':
					long v;
					v = message.Long();
					pMS->Set((char *)&v);
				break;
				case 'f':
					float f;
					f = message.Float();
					pMS->Set((char *)&f);
				break;
				case 'i':
					id = message.EntityID();
					pMS->Set((char *)&id);
				break;
				case 'e':
					VDATA * e;
					e = message.ScriptVariablePointer();
					pMS->Set((char *)&e);
				break;
				case 's':
					char * s;
					s = message.StringPointer();
					pMS->Set((char *)s);
				break;
				case 'a':
					ATTRIBUTES * a;
					a = message.AttributePointer();
					pMS->Set((char *)&a);
				break;

				//-------------------------------------
				default: bAction = false; break;
			}
		}
		va_end(message.args);
	} else pMS = nullptr;

	S_EVENTMSG* pEM = new S_EVENTMSG(Event_name, pMS, post_time);
	pEM->bProcess = true;
	Compiler.AddPostEvent(pEM);
	return 0;
}

VDATA * CORE::Event(char * Event_name, char * Format,...)
{
	VDATA* pVD = nullptr;
	if(Format == nullptr)
	{
		pVD = Compiler.ProcessEvent(Event_name);
		return pVD;
	}
	MESSAGE message;
	va_start(message.args,Format);					// 1
	message.Reset(Format);	// reset message class	// 2
	// ....
	pVD = Compiler.ProcessEvent(Event_name,message);

	va_end(message.args);
	return pVD;
}

void * CORE::MakeClass(char * class_name)
{
	long hash = MakeHashValue(class_name);
	for (const auto c : _pModuleClassRoot)
		if (c->GetHash() == hash && _stricmp(class_name, c->GetName()) == 0)
			return c->CreateClass();

	return nullptr;
}


void CORE::ReleaseServices()
{
	for(const auto c : _pModuleClassRoot)
		if (c->Service())
			c->Clear();

	Controls = nullptr;
}

VMA * CORE::FindVMA(char * class_name)
{
	long hash = MakeHashValue(class_name);
	for (const auto c : _pModuleClassRoot)
		if (c->GetHash() == hash && _stricmp(class_name, c->GetName()) == 0)
			return c;

	return nullptr;
}

VMA * CORE::FindVMA(long hash)
{
	for (const auto c : _pModuleClassRoot)
		if (c->GetHash() == hash)
			return c;

	return nullptr;
}

void * CORE::CreateService(char * service_name)
{
	VMA* pClass = FindVMA(service_name);
	if(pClass == nullptr)
	{
		CheckAutoExceptions(0);
		return nullptr;
	}

	if(pClass->GetHash() == 0)
	{
		CheckAutoExceptions(0);
		return nullptr;
	}

	if(pClass->GetReference() > 0) return pClass->CreateClass();

	SERVICE* service_PTR = (SERVICE *)pClass->CreateClass();

	uint32_t class_code = MakeHashValue(service_name);
	pClass->SetHash(class_code);

	if(!service_PTR->Init())
		CheckAutoExceptions(0);

	Services_List.Add(class_code,class_code,service_PTR);

	return service_PTR;

}

void CORE::Trace(const char * format, ...)
{
	static	char buffer_4k[4096];

	va_list args;
	va_start(args,format);
	_vsnprintf_s(buffer_4k,sizeof(buffer_4k) - 4,format,args);
	va_end(args);
	spdlog::trace(buffer_4k);
}

//------------------------------------------------------------------------------------------------
// Transfer programm control to objects via Execute() functions
//
void CORE::ProcessExecute()
{
	uint64_t ticks;

	ProcessRunStart(SECTION_EXECUTE);

	uint32_t deltatime = Timer.GetDeltaTime();
	auto layerWalker = entityManager.GetLayerWalker(LayerFlags::EXECUTE);
	for(auto walker = layerWalker(); walker != nullptr; walker = layerWalker())
	{
		for (auto id = walker(); id; id = walker()) {
			if (EntityFound(id)) {
				((Entity*)entityManager.GetEntity(id))->ProcessStage(Entity::Stage::EXECUTE, deltatime);
			}
		}
	}

	ProcessRunEnd(SECTION_EXECUTE);
}

void CORE::ProcessRealize()
{
	uint64_t ticks;
	ProcessRunStart(SECTION_REALIZE);

	uint32_t deltatime = Timer.GetDeltaTime();
	auto layerWalker = entityManager.GetLayerWalker(LayerFlags::REALIZE);
	for (auto walker = layerWalker(); walker != nullptr; walker = layerWalker())
	{
		for (auto id = walker(); id; id = walker()) {
			if (EntityFound(id)) {
				((Entity*)entityManager.GetEntity(id))->ProcessStage(Entity::Stage::REALIZE, deltatime);
			}
		}
	}

	ProcessRunEnd(SECTION_REALIZE);
}

// save core state
bool CORE::SaveState(char * file_name)
{
	if(!file_name)
		return false;

	fio->SetDrive(XBOXDRIVE_NONE);
	HANDLE fh = fio->_CreateFile(file_name,GENERIC_WRITE | GENERIC_READ, 0,CREATE_ALWAYS);
	fio->SetDrive();

	if(fh == INVALID_HANDLE_VALUE) 
		return false;

	Compiler.SaveState(fh);
	fio->_CloseHandle(fh);

	return true;
}

// force core to load state file at the start of next game loop, return false if no state file
bool CORE::InitiateStateLoading(char * file_name)
{
	fio->SetDrive(XBOXDRIVE_NONE);
	HANDLE fh = fio->_CreateFile(file_name,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
	fio->SetDrive();
	if(fh == INVALID_HANDLE_VALUE) return false;
	fio->_CloseHandle(fh);
	delete State_file_name;

	const auto len = strlen(file_name) + 1;
	State_file_name = (char *)new char[len];
	if(State_file_name == nullptr) throw std::exception();
	strcpy_s(State_file_name, len, file_name);
	return true;
}


void CORE::ProcessStateLoading()
{
	if(!State_file_name) 
		return;

	State_loading = true;
	EraseEntities();

	fio->SetDrive(XBOXDRIVE_NONE);
	HANDLE fh = fio->_CreateFile(State_file_name,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
	fio->SetDrive();
	if(fh == INVALID_HANDLE_VALUE) return;
	Compiler.LoadState(fh);
	fio->_CloseHandle(fh);

	delete State_file_name; 
	State_file_name = nullptr;
	State_loading = false;
}

void CORE::ProcessRunStart(uint32_t section_code)
{
	uint32_t class_code;
	SERVICE* service_PTR = Services_List.GetService(class_code);
	while(service_PTR)
	{

		uint32_t section = service_PTR->RunSection();
		if(section == section_code)
		{
			service_PTR->RunStart();
		}
		service_PTR = Services_List.GetServiceNext(class_code);
	}
}

void CORE::ProcessRunEnd(uint32_t section_code)
{
	uint32_t class_code;
	SERVICE* service_PTR = Services_List.GetService(class_code);
	while(service_PTR)
	{
		uint32_t section = service_PTR->RunSection();
		if(section == section_code)
		{
			service_PTR->RunEnd();
		}
		service_PTR = Services_List.GetServiceNext(class_code);
	}
}

uint32_t CORE::EngineFps()
{
	return Timer.fps;
}

void CORE::SetDeltaTime(long delta_time)
{
	Timer.SetDelta(delta_time);
}

uint32_t CORE::GetDeltaTime()
{
	return Timer.GetDeltaTime();
}

uint32_t CORE::GetRDeltaTime()
{
	return Timer.rDelta_Time;
}

ATTRIBUTES * CORE::Entity_GetAttributeClass(entid_t  id_PTR, char * name)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	if(pE->AttributesPointer == nullptr) return nullptr;
	return pE->AttributesPointer->FindAClass(pE->AttributesPointer,name);
}

char *	CORE::Entity_GetAttribute(entid_t  id_PTR, char * name)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	if(pE->AttributesPointer == nullptr) return nullptr;
	return pE->AttributesPointer->GetAttribute(name);
}

uint32_t	CORE::Entity_GetAttributeAsDword(entid_t  id_PTR, char * name, uint32_t def)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return def;
	if(pE->AttributesPointer == nullptr) return def;
	return pE->AttributesPointer->GetAttributeAsDword(name,def);

}

FLOAT	CORE::Entity_GetAttributeAsFloat(entid_t  id_PTR, char * name, FLOAT def)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return def;
	if(pE->AttributesPointer == nullptr) return def;
	return pE->AttributesPointer->GetAttributeAsFloat(name,def);
}

BOOL	CORE::Entity_SetAttribute(entid_t  id_PTR, char * name, char * attribute)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttribute(name,attribute);
}

BOOL	CORE::Entity_SetAttributeUseDword(entid_t  id_PTR, char * name, uint32_t val)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttributeUseDword(name,val);
}

BOOL	CORE::Entity_SetAttributeUseFloat(entid_t  id_PTR, char * name, FLOAT val)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttributeUseFloat(name,val);
}

void CORE::Entity_SetAttributePointer(entid_t  id_PTR, ATTRIBUTES * pA)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return;
	pE->AttributesPointer = pA;
}

uint32_t	CORE::Entity_AttributeChanged(entid_t  id_PTR, ATTRIBUTES * pA)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return 0;
	return pE->AttributeChanged(pA);
}

ATTRIBUTES * CORE::Entity_GetAttributePointer(entid_t  id_PTR)
{
	Entity* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	return pE->AttributesPointer;
}

void CORE::EraseEntities()
{
	entityManager.EraseAll();
}


void CORE::ClearEvents()
{
	Compiler.ClearEvents();
}

void CORE::AppState(bool state)
{
	if(Controls) Controls->AppState(state);
}

uint32_t CORE::MakeHashValue(const char * string)
{
  uint32_t hval = 0;

  while(*string != 0)
  {
	char v = *string++;
	if ('A' <= v && v <= 'Z') v += 'a' - 'A';

    hval = (hval<<4) + (unsigned long int)v;
    uint32_t g = hval & ((unsigned long int)0xf << (32 - 4));
    if(g != 0)
		{
			hval ^= g >> (32 - 8);
			hval ^= g;
		}
  }
  return hval;
}

//==========================================================================================================================
// end
//==========================================================================================================================

void CORE::DumpEntitiesInfo()
{
	/*LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		throw std::exception();

	const auto freq = double(li.QuadPart)/1000.0;

	uint32_t n;
	char * ptr;
	VMA * pClass;

	Trace("Script commands executed: %" PRIu32, dwNumberScriptCommandsExecuted);
	Trace("Entity Dump -----------------------------------");

	for(n=0;n<=CoreState.Atoms_max_orbit;n++)
	{
		if(Atoms_PTR[n] == nullptr) continue;

		pClass = FindVMA(Atoms_PTR[n]->atom_id.class_code);
		if(pClass)
		{
			ptr = pClass->GetName();
			if(ptr)
			{
				Trace("Class: %s", ptr);
				Trace("     : Realize:  Cur( %fms ) Max( %fms )", Atoms_PTR[n]->as.Realize_ticks_av/freq, Atoms_PTR[n]->as.Realize_ticks_max/freq);
				Trace("     : Execute:  Cur( %fms ) Max( %fms )", Atoms_PTR[n]->as.Execute_ticks_av/freq, Atoms_PTR[n]->as.Execute_ticks_max/freq);
			}
		}
	}

	Trace(" ------- Running objects ------- ");
	for(n=0;n<=CommonLayers.lss.Layer_max_index;n++)
	{
		LAYER* l_PTR = CommonLayers.Layer_Table[n];
		if(l_PTR == nullptr) continue;

		uint32_t flags = l_PTR->ls.Flags & LRFLAG_FROZEN;
		if(flags != 0)
		{
			Trace("LAYER: %s frozen -------------------------------------",l_PTR->Name);
			continue;
		}
		Trace("LAYER: %s --------------------------------------",l_PTR->Name);
		entid_t  eid_PTR = l_PTR->GetId();
		while(eid_PTR)
		{
			Trace("Entity:");
			if(ValidateEntity(eid_PTR))
			{
				pClass = FindVMA(Atoms_PTR[eid_PTR->atom_position]->atom_id.class_code);
				if(pClass) ptr = pClass->GetName();
				Trace("        %s",ptr);
				if(Atoms_PTR[eid_PTR->atom_position]->as.Deleted) Trace("        deleted");

			}
			eid_PTR = l_PTR->GetNextID();
		}
	}

	Sleep(200);*/
}

void * CORE::GetSaveData(char * file_name, long & data_size)
{
	return Compiler.GetSaveData(file_name,data_size);

}

bool CORE::SetSaveData(char * file_name, void * data_ptr, long data_size)
{
	return Compiler.SetSaveData(file_name,data_ptr,data_size);
}


uint32_t CORE::SetScriptFunction(IFUNCINFO * pFuncInfo)
{
	return Compiler.SetScriptFunction(pFuncInfo);
}

void CORE::DeleteScriptFunction(uint32_t nFuncHandle)
{
	Compiler.DeleteScriptFunction(nFuncHandle);
}

char * CORE::EngineIniFileName()
{
	return ENGINE_INI_FILE_NAME;
}

uint32_t CORE::AttributeName2Code(const char * pAttributeName)
{
	return Compiler.SCodec.Convert(pAttributeName);
}

void * CORE::GetScriptVariable(const char * pVariableName, uint32_t * pdwVarIndex)
{
	VARINFO vi;

	const auto dwVarIndex = Compiler.VarTab.FindVar(pVariableName);
	if(dwVarIndex == INVALID_VAR_CODE || !Compiler.VarTab.GetVar(vi, dwVarIndex))
		return nullptr;

	if(pdwVarIndex) 
		*pdwVarIndex = dwVarIndex;

	return vi.pDClass;
}
/*
void CORE::SetNetActive(bool bActive)
{
	//bNetActive = bActive;
}

bool CORE::IsNetActive() const
{
	return false;
	//return bNetActive;
}
*/