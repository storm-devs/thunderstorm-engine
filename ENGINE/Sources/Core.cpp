#include "Core.h"
#include "externs.h"
#include <cinttypes>

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
	CoreState.engine_version = ENGINE_VERSION;
	SystemMessagesNum = 0;
	Exit_flag = false;
	State_loading = false;
	Constructor_counter = 0;
	Memory_Leak_flag = false;
	Controls = nullptr;
	fTimeScale = 1.0f;
	bNetActive = false;
	nSplitScreenshotGrid = 4;
}

void CORE::ResetCore()
{
	Initialized = false;
	bEngineIniProcessed = false;

	ReleaseAtoms();
	ReleaseServices();
	ReleaseLayers();

	Services_List.Release();

	DeleteEntityList.Release();
	DeleteServicesList.Release();
	Services_List.Release();
	DeleteLayerList.Release();

	SystemMessagesNum = 0;
	Scan_Layer_Code = INVALID_LAYER_CODE;

	STORM_DELETE(State_file_name); 

	Constructor_counter = 0;
}

void CORE::CleanUp()
{
	Initialized = false;
	bEngineIniProcessed = false;

	if(!Atoms_PTR.empty())
	{
		for(uint32_t n = 0;n<=CoreState.Atoms_max_orbit;n++)
		{
			if(Atoms_PTR[n] == nullptr) continue;
			EraseEntity(Atoms_PTR[n]->atom_id);
		}
	}

	ProcessDeleteList();
	ReleaseServices();
	ReleaseLayers();
	Compiler.Release();
	Atoms_PTR.clear();
	Services_List.Release();
	DeleteEntityList.Release();
	DeleteServicesList.Release();
	Services_List.Release();
	DeleteLayerList.Release();
	delete State_file_name;
}

void CORE::InitBase()
{
	char String[_MAX_PATH];

	INIFILE* engine_ini = File_Service.OpenIniFile(ENGINE_INI_FILE_NAME);
 	if(engine_ini != nullptr)
	{

		if(engine_ini->ReadString(nullptr,"offclass",String,sizeof(String),""))
		{
			ClassesOff.AddString(String);
			while(engine_ini->ReadStringNext(nullptr,"offclass",String,sizeof(String)))
			{
				ClassesOff.AddString(String);
			}
		}

		nSplitScreenshotGrid = engine_ini->GetLong( nullptr, "SplitScreenShotGrid", 4 );

		delete engine_ini;
	}
	LoadClassesTable();					// creating classes table

}

void CORE::ReleaseBase()
{
	Compiler.Token.Release();
	ClassesOff.Release();
}

bool CORE::LoCheck()
{
	// ~!~
	ENTITY_ID test_eid;
	if (!CreateEntity(&test_eid, "LocationP"))
		return false;
	auto* pE = static_cast<ENTITY *>(test_eid.pointer);
	pE->Execute(ENGINE_SCRIPT_VERSION);
	DeleteEntity(test_eid);
	return true;
}

bool CORE::Run()
{
	if (bDebugWindow && api->Controls && api->Controls->GetDebugAsyncKeyState(VK_F7)<0) 
		DumpEntitiesInfo();
	dwNumberScriptCommandsExecuted = 0;

	if (bDebugWindow)
	{
		for (uint32_t n = 0; n < CoreState.Atoms_max_orbit; n++)
		{
			if (Atoms_PTR[n] == nullptr) 
				continue;
			Atoms_PTR[n]->as.Execute_ticks_av = 0;
			Atoms_PTR[n]->as.Realize_ticks_av = 0;
		}
	}

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

	if (!bNetActive)
	{
		if(bAcceleration && Controls && Controls->GetDebugAsyncKeyState('R')<0) Timer.Delta_Time *= 10;
		if(bAcceleration && Controls && Controls->GetDebugAsyncKeyState('Y')<0) Timer.Delta_Time = static_cast<uint32_t>(Timer.Delta_Time * 0.2f);

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

	ProcessDeleteList();					// delete objects marked for deletion

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

	CommonLayers.Clean();

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

	// create atoms space
	if(!CreateAtomsTable(CORE_DEFAULT_ATOMS_SPACE)) return false;

	DeleteServicesList.Init(sizeof(CODE_AND_POINTER),8);
	DeleteEntityList.Init(sizeof(ENTITY_ID),2);
	DeleteLayerList.Init(sizeof(uint32_t),8);

	Initialized = true;

	return true;
}

bool CORE::LoadCoreState(CORE_STATE cs)
{
	ResetCore();

	// create atoms space
	if(!CreateAtomsTable(cs.Atoms_space)) throw std::exception();

	DeleteServicesList.Init(sizeof(CODE_AND_POINTER),8);
	DeleteEntityList.Init(sizeof(ENTITY_ID),2);
	DeleteLayerList.Init(sizeof(uint32_t),8);

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

	res = engine_ini->ReadString(nullptr,"load class",String,sizeof(String),"");
	while(res)
	{
		CreateEntity(nullptr,String);
		res = engine_ini->ReadStringNext(nullptr,"load class",String,sizeof(String));
	}

	delete engine_ini;
}

bool CORE::LoadClassesTable()
{
	for(auto c : _pModuleClassRoot)
	{
		auto hash = MakeHashValue(c->GetName());

		if (ClassesOff.GetStringCode(c->GetName()) != INVALID_ORDINAL_NUMBER)
			hash = 0;

		c->SetHash(hash);
	}

	return true;
}


bool CORE::CreateAtomsTable(uint32_t _space)
{
	// allocate space for atoms table
	CoreState.Atoms_space = _space;

	Atoms_PTR.resize(CoreState.Atoms_space);
	PZERO(&CoreState.Creation_Time,sizeof(CoreState.Creation_Time));

	return true;
}

void CORE::ReleaseLayers()
{
	CommonLayers.Release();
}

void CORE::ReleaseAtoms()
{
	// release atoms and entity objects
	if(!Atoms_PTR.empty())
	{
		for(uint32_t n = 0;n<=CoreState.Atoms_max_orbit;n++)
		{
			if(Atoms_PTR[n] == nullptr) continue;
			EraseEntity(Atoms_PTR[n]->atom_id);
		}
	}
	CoreState.Atoms_number = 0;
	CoreState.Atoms_max_orbit = 0;
	CoreState.Atoms_min_free_orbit = 0;
	Atoms_PTR.clear();
	PZERO(&CoreState.Creation_Time,sizeof(CoreState.Creation_Time));
}


void CORE::CheckAutoExceptions(uint32_t = 0) const
{
	spdlog::warn("exception thrown");
}

bool CORE::CreateEntity(ENTITY_ID * id_PTR, char * class_name)
{
	return CreateEntity(id_PTR,class_name,nullptr);
}

//bool CORE::CreateEntity(ENTITY_ID * id_PTR, char * class_name)
bool CORE::CreateEntity(ENTITY_ID * id_PTR, char * class_name, ATTRIBUTES * attributesPTR)
{
	if(id_PTR) 
		memset(id_PTR,0,sizeof(ENTITY_ID));

	VMA * pClass = nullptr;

	const long hash = MakeHashValue(class_name);
	if(hash == 0) return false;

	for (const auto c : _pModuleClassRoot)
	{
		if (c->GetHash() == hash && _stricmp(class_name, c->GetName()) == 0)
		{
			pClass = c;
			break;
		}
	}

	if(!pClass)
	{
		CheckAutoExceptions(0);
		return false;
	}

	C_ATOM* atom_PTR = CreateAtom(hash);

	if(atom_PTR == nullptr) throw std::exception("Cant create Atom");
	atom_PTR->atom_id.pName = pClass->GetName();
	auto* Entity_PTR = static_cast<ENTITY*>(pClass->CreateClass());
	
	if(Entity_PTR == nullptr)
	{
		Trace("empty class: %s",class_name);
		throw std::exception("invalid class");
	}
	Entity_PTR->SetEntityID(atom_PTR->atom_id);
	Entity_PTR->AttributesPointer = attributesPTR;

	atom_PTR->as.Connected = true;

	if(!Entity_PTR->Init())
	{
		MarkEntityAsDeleted(Entity_PTR->GetID());
		CheckAutoExceptions(0);
		return false;
	}

	if(id_PTR)
		memcpy(id_PTR,&atom_PTR->atom_id,sizeof(ENTITY_ID));

	return true;
}

// continuously increasing creation time structure making unical time stamp for entity
// exception generated at the end of period
void CORE::CreationTimeInc()
{
	uint32_t n = 0;
	bool transfer = false;
	do
	{
		if(CoreState.Creation_Time.time[n] == 0xffffffff) transfer = true; else transfer = false;
		CoreState.Creation_Time.time[n]++;
		n++;
	} while (transfer && n < CRTM_DWORDS);
	if(transfer && n >= CRTM_DWORDS) throw std::exception("Id time overflaw");
}

C_ATOM * CORE::CreateAtom(uint32_t class_code)
{
	if(CoreState.Atoms_number >= CoreState.Atoms_space)
	{
		uint32_t new_space = 2 * CoreState.Atoms_space;
		Atoms_PTR.resize(new_space);
		CoreState.Atoms_space = new_space;
	}

	for(uint32_t n = CoreState.Atoms_min_free_orbit;n<CoreState.Atoms_space;n++)
	{
		if(Atoms_PTR[n] != nullptr) continue;

		Atoms_PTR[n] = new C_ATOM;
		if(Atoms_PTR[n] == nullptr) throw std::exception();

		if(CoreState.Atoms_max_orbit < n) CoreState.Atoms_max_orbit = n;

		Atoms_PTR[n]->atom_id.atom_position = n;
		if(CoreState.Atoms_min_free_orbit == n)
		for(;CoreState.Atoms_min_free_orbit<CoreState.Atoms_space;CoreState.Atoms_min_free_orbit++)
		{
			if(Atoms_PTR[CoreState.Atoms_min_free_orbit] == nullptr) break;
		}

		Atoms_PTR[n]->atom_id.creation_time = CoreState.Creation_Time;
		CreationTimeInc();
		Atoms_PTR[n]->atom_id.class_code = class_code;
		Atoms_PTR[n]->as.Deleted = false;
		Atoms_PTR[n]->atom_id.pointer = nullptr;
		CoreState.Atoms_number++;
		return Atoms_PTR[n];
	}
	return nullptr;
}

C_ATOM * CORE::FitAtom(ENTITY_ID entity_id, ATOM_STATE atom_state)
{
	if(entity_id.atom_position > CoreState.Atoms_max_orbit) throw std::exception();
	if(Atoms_PTR[entity_id.atom_position] != nullptr) throw std::exception();

	Atoms_PTR[entity_id.atom_position] = new C_ATOM;
	if(Atoms_PTR[entity_id.atom_position] == nullptr) throw std::exception();
	Atoms_PTR[entity_id.atom_position]->as = atom_state;
	Atoms_PTR[entity_id.atom_position]->atom_id = entity_id;
	Atoms_PTR[entity_id.atom_position]->atom_id.pointer = nullptr;
	return Atoms_PTR[entity_id.atom_position];
}

bool CORE::DeleteAtom(C_ATOM * atom_PTR)
{
	if(atom_PTR == nullptr) return false;
	uint32_t ap = atom_PTR->atom_id.atom_position;
	if(ap >= CoreState.Atoms_space) throw std::exception();
	if(Atoms_PTR[ap] != atom_PTR) throw std::exception();
	delete Atoms_PTR[ap];
	Atoms_PTR[ap] = nullptr;
	CoreState.Atoms_number--;
	if(CoreState.Atoms_min_free_orbit > ap) CoreState.Atoms_min_free_orbit = ap;
	return true;
}

uint32_t CORE::Class_Name2Code(char * class_name)
{
	return MakeHashValue(class_name);
}

bool CORE::FindClass(ENTITY_ID * id_PTR,char * class_name,uint32_t class_code)
{
	uint32_t hash;

	if(class_name != nullptr) hash = MakeHashValue(class_name);
	else hash = class_code;

	for(uint32_t n = 0;n<=CoreState.Atoms_max_orbit;n++)
	{
		if(Atoms_PTR[n] == nullptr) continue;
		if(Atoms_PTR[n]->as.Deleted) continue;
		if(Atoms_PTR[n]->atom_id.class_code == hash)
		{
			// class found
			Atom_Search_Position = n;
			Atom_Search_Class_Code = hash;
			if(id_PTR) memcpy(id_PTR,&Atoms_PTR[n]->atom_id,sizeof(ENTITY_ID));
			return true;
		}
	}

	if(id_PTR) *id_PTR = ENTITY_ID();

	return false;
}

bool CORE::FindClassNext(ENTITY_ID * id_PTR)
{
	for(uint32_t n = (Atom_Search_Position + 1);n<=CoreState.Atoms_max_orbit;n++)
	{
		if(Atoms_PTR[n] == nullptr) continue;//break;
		if(Atoms_PTR[n]->as.Deleted) continue;
		if(Atoms_PTR[n]->atom_id.class_code == Atom_Search_Class_Code)
		{
			// class found
			Atom_Search_Position = n;
			if(id_PTR) memcpy(id_PTR,&Atoms_PTR[n]->atom_id,sizeof(ENTITY_ID));
			return true;
		}
	}
	if(id_PTR) *id_PTR = ENTITY_ID();
	return false;
}

bool CORE::CompareID(ENTITY_ID * ida_PTR,ENTITY_ID * idb_PTR)
{
	if(ida_PTR == nullptr || idb_PTR == nullptr) return false;
	if(memcmp(ida_PTR,idb_PTR,sizeof(ENTITY_ID)) == 0) return true;
	return false;
}

bool CORE::GetEntity(ENTITY_ID * id_PTR)
{
	if(id_PTR == nullptr) return false;

	// scan all entities
	if(Scan_Layer_Code == INVALID_LAYER_CODE)
	{
		Atom_Get_Position = 0;
		do
		{
			if(Atom_Get_Position > CoreState.Atoms_max_orbit) return false;
			if(Atoms_PTR[Atom_Get_Position])
			{
				if(!Atoms_PTR[Atom_Get_Position]->as.Deleted)
				{
					memcpy(id_PTR,&Atoms_PTR[Atom_Get_Position]->atom_id,sizeof(ENTITY_ID));
					return true;
				}
			}
			Atom_Get_Position++;
		} while(Atom_Get_Position <= CoreState.Atoms_max_orbit);
	}
	else
	{
		LAYER* lPTR = CommonLayers.GetLayer(Scan_Layer_Code);
		if(lPTR)
		{
			ENTITY_ID* eid_PTR = lPTR->GetID();
			if(eid_PTR)
			{
				memcpy(id_PTR,eid_PTR,sizeof(ENTITY_ID));
				return true;
			}
		}
		return false;
	}
	return false;
}

bool CORE::GetEntityNext(ENTITY_ID * id_PTR)
{
	if(id_PTR == nullptr) return false;

	if(Scan_Layer_Code == INVALID_LAYER_CODE)
	{
		do
		{
			Atom_Get_Position++;
			if(Atom_Get_Position > CoreState.Atoms_max_orbit) return false;
			if(Atoms_PTR[Atom_Get_Position])
			{
				if(!Atoms_PTR[Atom_Get_Position]->as.Deleted)
				{
					memcpy(id_PTR,&Atoms_PTR[Atom_Get_Position]->atom_id,sizeof(ENTITY_ID));
					return true;
				}
			}
		} while(Atom_Get_Position <= CoreState.Atoms_max_orbit);
	}
	else
	{
		LAYER* lPTR = CommonLayers.GetLayer(Scan_Layer_Code);
		if(lPTR)
		{
			ENTITY_ID* eid_PTR = lPTR->GetNextID();
			if(eid_PTR)
			{
				memcpy(id_PTR,eid_PTR,sizeof(ENTITY_ID));
				return true;
			}
		}
		return false;
	}

	return false;
}

bool CORE::SetEntityScanLayer(char * layer_name)
{
	Scan_Layer_Code = CommonLayers.GetIndex(layer_name);
	if(Scan_Layer_Code == INVALID_LAYER_CODE) return false;
	return true;
}

ENTITY * CORE::GetEntityPointer(ENTITY_ID * id_PTR)
{
	if(!ValidateEntity(id_PTR)) return nullptr;
	ENTITY* ep = (ENTITY *)Atoms_PTR[id_PTR->atom_position]->atom_id.pointer;
	if(Atoms_PTR[id_PTR->atom_position]->as.Deleted) return nullptr;
	return ep;
}

//-------------------------------------------------------------------------------------------------
// Return true, if entity with id pointed by id_PTR exist and false otherwise
//
bool CORE::ValidateEntity(ENTITY_ID * id_PTR)
{
	if(id_PTR) id_PTR->pointer = nullptr;
	if(id_PTR == nullptr) return false;
	// check fo valid object position and pointer
	uint32_t pos = id_PTR->atom_position; if(pos >= CoreState.Atoms_space) return false;
	if(Atoms_PTR[pos] == nullptr) return false;
	if(Atoms_PTR[pos]->atom_id.pointer == nullptr)
	{
		CheckAutoExceptions(0);
		return false;
	}

	// update pointer
	id_PTR->pointer = Atoms_PTR[pos]->atom_id.pointer;

	// compare id structure
	if(memcmp(&Atoms_PTR[pos]->atom_id,id_PTR,sizeof(ENTITY_ID)) != 0)
	{
		id_PTR->pointer = nullptr;
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
// Mark entity for further deleting using id
//
bool CORE::MarkEntityAsDeleted(ENTITY_ID entity_id)
{
	if(!ValidateEntity(&entity_id)) return false;
	Atoms_PTR[entity_id.atom_position]->as.Deleted = true;
	DeleteEntityList.AddData(&entity_id);
	return true;
}

//-------------------------------------------------------------------------------------------------
// Mark entity for further deleting using object pointer
//
bool CORE::MarkEntityAsDeleted(void * entity_PTR)
{
	const auto entity_id = static_cast<ENTITY*>(entity_PTR)->GetID();
	MarkEntityAsDeleted(entity_id);
	return true;
}

//-------------------------------------------------------------------------------------------------
// Delete objects (entities and layers) previously assigned for deleting
//
void CORE::ProcessDeleteList()
{
	uint32_t n,dwcode;
	ENTITY_ID entity_id;

	// delete entity, added to delete list -------------------------
	uint32_t deleted_num = DeleteEntityList.DataNum();
	if(deleted_num != 0)
	{
		for(n=0;n<deleted_num;n++)
		{
			if(!DeleteEntityList.GetData(n,&entity_id)) continue;
			EraseEntity(entity_id);
			deleted_num = DeleteEntityList.DataNum();
			//DeleteEntityList.ShiftLeft();
		}
		DeleteEntityList.Clear();
	}

	//--------------------------------------------------------------

	// delete common layers, added to delete list ------------------
	deleted_num = DeleteLayerList.DataNum();
	if(deleted_num != 0)
	{
		for(n=0;n<deleted_num;n++)
		{
			if(!DeleteLayerList.GetData(n,&dwcode)) continue;
			CommonLayers.Erase(dwcode);
			deleted_num = DeleteLayerList.DataNum();
			//EraseLayer(dwcode);
		}
		DeleteLayerList.Clear();
	}

	//-------------------------------------------------------------

	CODE_AND_POINTER data;
	deleted_num = DeleteServicesList.DataNum();
	if(deleted_num != 0)
	{
		for(n=0;n<deleted_num;n++)
		{
			if(!DeleteServicesList.GetData(n,&data)) continue;
			SERVICE* service_PTR = (SERVICE *)data.pointer;
			if(!service_PTR) 
				throw std::exception("invalid service");
			delete service_PTR;

		}
		DeleteServicesList.Clear();
	}
}
//-------------------------------------------------------------------------------------------------
// Delete entity
//
bool CORE::EraseEntity(ENTITY_ID entity_id)
{
	if(!ValidateEntity(&entity_id)) return false;

	delete (ENTITY *)Atoms_PTR[entity_id.atom_position]->atom_id.pointer;


	for(uint32_t n = 0;n<=CommonLayers.lss.Layer_max_index;n++)
	{
		if(CommonLayers.Layer_Table[n] == nullptr) continue;
		if(Atoms_PTR[entity_id.atom_position]->TstLayerAttribute(n,false))
			CommonLayers.Layer_Table[n]->Del(entity_id);
	}

	DeleteAtom(Atoms_PTR[entity_id.atom_position]);

	if(CoreState.Atoms_max_orbit == entity_id.atom_position)
	{
		for(CoreState.Atoms_max_orbit = entity_id.atom_position; CoreState.Atoms_max_orbit > 0;CoreState.Atoms_max_orbit--)
		{
			if(Atoms_PTR[CoreState.Atoms_max_orbit] == nullptr) continue;
			break;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
// function scan all entities untill entity with memory pointer equal to _entity_pointer
// if such entity found function return true
// if id_PTR not null, function fill pointed structure by entity_id
//
bool CORE::Convert_Pointer2ID(void * _entity_pointer,ENTITY_ID * id_PTR)
{
	auto* entity_PTR = static_cast<ENTITY *>(_entity_pointer);
	ENTITY_ID eid = entity_PTR->GetID();
	if(eid.atom_position > CoreState.Atoms_max_orbit) throw std::exception();
	if(Atoms_PTR[eid.atom_position] == nullptr) throw std::exception();
	if(Atoms_PTR[eid.atom_position]->atom_id.pointer != _entity_pointer) throw std::exception();
	if(id_PTR != nullptr) memcpy(id_PTR,&Atoms_PTR[eid.atom_position]->atom_id,sizeof(ENTITY_ID));
	return true;
}

uint32_t CORE::GetLayerIndex(char* layer_name)
{
	return CommonLayers.GetIndex(layer_name);
}


bool CORE::VerifyLayer(char * layer_name)
{
	return CommonLayers.Verify(layer_name);
}

bool CORE::LayerCreate(char * layer_name, bool ordered, bool fail_if_exist)
{
	return CommonLayers.Create(layer_name,ordered,fail_if_exist);
}

bool CORE::LayerCreate(char * layer_name, bool ordered, bool fail_if_exist, bool system, uint32_t system_flags)
{
	return CommonLayers.Create(layer_name,ordered,fail_if_exist);
}

C_ATOM * CORE::GetAtom(ENTITY_ID * id_PTR)
{
	if(!ValidateEntity(id_PTR)) return nullptr;
	return Atoms_PTR[id_PTR->atom_position];
}

//------------------------------------------------------------------------------------------------
// Mark layer for deletion before next game loop
//
void CORE::LayerDelete(char * layer_name)
{
	if(CommonLayers.Verify(layer_name))
	{
		LAYER* layer_PTR = CommonLayers.GetLayer(layer_name);
		if(layer_PTR)
		{
			ENTITY_ID* id_PTR = layer_PTR->GetID();
			while(id_PTR)
			{
				C_ATOM* atom_PTR = GetAtom(id_PTR);
				if(atom_PTR) atom_PTR->ClrLayerAttribute(CommonLayers.GetIndex(layer_name),false);
				id_PTR = layer_PTR->GetNextID();
			}
		}
	}

	CommonLayers.Delete(layer_name);
}

void CORE::LayerSetFlags(char * layer_name, uint32_t flags)
{
	CommonLayers.SetFlags(layer_name,flags);
}

void CORE::LayerClrFlags(char * layer_name, uint32_t flags)
{
	CommonLayers.ClrFlags(layer_name,flags);
}

uint32_t CORE::LayerGetFlags(char * layer_name)
{
	return CommonLayers.GetFlags(layer_name);
}


bool CORE::LayerAdd(const char * layer_name, ENTITY_ID eid, uint32_t priority)
{
	return LayerAdd((char *)layer_name,eid,priority,false);
}

bool CORE::LayerAdd(const char * pLayerName, ENTITY_ID eid, uint32_t priority, bool system)
{
	char * layer_name = (char*)pLayerName;

	LayerCreate(layer_name,true,false,false,0);
	uint32_t index = CommonLayers.GetIndex(layer_name);
	if(index == INVALID_LAYER_CODE) return false;
	if(!ValidateEntity(&eid)) return false;
	if(Atoms_PTR[eid.atom_position]->TstLayerAttribute(index,false)) return true;
	if(!CommonLayers.Add(index,eid,priority)) return false;
	Atoms_PTR[eid.atom_position]->SetLayerAttribute(index,false);

	return true;
}

void CORE::LayerDel(const char * layer_name, ENTITY_ID eid)
{
	LayerDel((char*)layer_name,eid,false);
}

void CORE::LayerDel(const char * pLayerName, ENTITY_ID eid,bool system)
{
	char * layer_name = (char*)pLayerName;
	uint32_t index = CommonLayers.GetIndex(layer_name);
	CommonLayers.Del(index,eid);
	if(!ValidateEntity(&eid)) return;
	Atoms_PTR[eid.atom_position]->ClrLayerAttribute(index,false);
}

bool CORE::LayerDeleteContent(char * layer_name)
{
	//GUARD(CORE::DeleteLayerContent)

	if(CommonLayers.Verify(layer_name))
	{
		LAYER* layer_PTR = CommonLayers.GetLayer(layer_name);
		if(layer_PTR)
		{
			ENTITY_ID* id_PTR = layer_PTR->GetID();
			while(id_PTR)
			{
				MarkEntityAsDeleted(*id_PTR);
				id_PTR = layer_PTR->GetNextID();
			}
		}
	}

	return true;
}

// on/off execute
void CORE::LayerSetExecute(char * layer_name, bool on)
{
	if(on) LayerSetFlags(layer_name,LRFLAG_EXECUTE);
	else LayerClrFlags(layer_name,LRFLAG_EXECUTE);
}

// on/off realize
void CORE::LayerSetRealize(char * layer_name, bool on)
{
	if(on) LayerSetFlags(layer_name,LRFLAG_REALIZE);
	else LayerClrFlags(layer_name,LRFLAG_REALIZE);
}

VIDWALKER * CORE::LayerGetWalker(char * layer_name)
{
	LAYER* pl = CommonLayers.GetLayer(layer_name);
	if(pl == nullptr)
	{
		CommonLayers.Create(layer_name,true,false);
		pl = CommonLayers.GetLayer(layer_name);
	}
	return pl->GetWalker();
}

void CORE::Exit() { Exit_flag = true; }

//------------------------------------------------------------------------------------------------
// return application window handle
//
HWND CORE::GetAppHWND() { return App_Hwnd; }
HINSTANCE CORE::GetAppInstance() { return hInstance; }

//------------------------------------------------------------------------------------------------
// Mark entity for following deletion
//
bool CORE::DeleteEntity(ENTITY_ID entity_id)
{
	if(!ValidateEntity(&entity_id)) return false;
	return MarkEntityAsDeleted(entity_id);
}

void * CORE::GetUserData(long * data_size)
{
	return nullptr;
}

void * CORE::SetUserData(void * ud_PTR,long data_size)
{
	return nullptr;
}
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
uint32_t _cdecl CORE::Send_Message(ENTITY_ID Destination,char * Format,...)
{
	MESSAGE message;
	if(!ValidateEntity(&Destination)) return 0;				// check for valid destination
	message.Reset(Format);									// reset message class
	PZERO(&message.Sender_ID,sizeof(ENTITY_ID));
	va_start(message.args,Format);
	uint32_t rc = ((ENTITY *)Destination.pointer)->ProcessMessage(message);	// transfer control
	va_end(message.args);
	return rc;
}

uint32_t _cdecl CORE::PostEvent(char * Event_name, uint32_t post_time, char * Format,...)
{
	MESSAGE_SCRIPT * pMS;
	MESSAGE message;

	ENTITY_ID id;

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

VDATA * _cdecl CORE::Event(char * Event_name, char * Format,...)
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

void _cdecl CORE::Trace(const char * format, ...)
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

	for(uint32_t n = 0;n<=CommonLayers.lss.Layer_max_index;n++)
	{
		LAYER* l_PTR = CommonLayers.Layer_Table[n];
		if(l_PTR == nullptr) continue;
		uint32_t flags = l_PTR->ls.Flags & LRFLAG_FROZEN; if(flags != 0) continue;	// skip frozen layers
		flags = l_PTR->ls.Flags & LRFLAG_EXECUTE; if(flags == 0) continue;	// skip non execute layers
		ENTITY_ID* eid_PTR = l_PTR->GetID();
		while(eid_PTR)
		{
			if(ValidateEntity(eid_PTR))
			{
				if(!Atoms_PTR[eid_PTR->atom_position]->as.Deleted)
				{
				RDTSC_B(ticks);
				((ENTITY *)eid_PTR->pointer)->Execute(deltatime);
				RDTSC_E(ticks);

				ATOM_STATE* pAs = &Atoms_PTR[eid_PTR->atom_position]->as;
				pAs->Execute_ticks_av = ticks;
				if(pAs->Execute_ticks_max < ticks) pAs->Execute_ticks_max = ticks;

				}
			}
			eid_PTR = l_PTR->GetNextID();
		}
	}
	ProcessRunEnd(SECTION_EXECUTE);
}

void CORE::ProcessRealize()
{
	uint64_t ticks;
	ProcessRunStart(SECTION_REALIZE);

	uint32_t deltatime = Timer.GetDeltaTime();

	for(uint32_t n = 0;n<=CommonLayers.lss.Layer_max_index;n++)
	{
		LAYER* l_PTR = CommonLayers.Layer_Table[n];
		if(l_PTR == nullptr) continue;
		uint32_t flags = l_PTR->ls.Flags & LRFLAG_FROZEN; if(flags != 0) continue;	// skip frozen layers
		flags = l_PTR->ls.Flags & LRFLAG_REALIZE; if(flags == 0) continue;	// skip non realize layers
		ENTITY_ID* eid_PTR = l_PTR->GetID();
		while(eid_PTR)
		{
			if(ValidateEntity(eid_PTR))
			{
				if(!Atoms_PTR[eid_PTR->atom_position]->as.Deleted)
				{
				RDTSC_B(ticks);
				((ENTITY *)eid_PTR->pointer)->Realize(deltatime);
				RDTSC_E(ticks);

				ATOM_STATE* pAs = &Atoms_PTR[eid_PTR->atom_position]->as;
				pAs->Realize_ticks_av = ticks;
				if(pAs->Realize_ticks_max < ticks) pAs->Realize_ticks_max = ticks;

				}
			}
			eid_PTR = l_PTR->GetNextID();
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

ATTRIBUTES * CORE::Entity_GetAttributeClass(ENTITY_ID * id_PTR, char * name)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	if(pE->AttributesPointer == nullptr) return nullptr;
	return pE->AttributesPointer->FindAClass(pE->AttributesPointer,name);
}

char *	CORE::Entity_GetAttribute(ENTITY_ID * id_PTR, char * name)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	if(pE->AttributesPointer == nullptr) return nullptr;
	return pE->AttributesPointer->GetAttribute(name);
}

uint32_t	CORE::Entity_GetAttributeAsDword(ENTITY_ID * id_PTR, char * name, uint32_t def)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return def;
	if(pE->AttributesPointer == nullptr) return def;
	return pE->AttributesPointer->GetAttributeAsDword(name,def);

}

FLOAT	CORE::Entity_GetAttributeAsFloat(ENTITY_ID * id_PTR, char * name, FLOAT def)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return def;
	if(pE->AttributesPointer == nullptr) return def;
	return pE->AttributesPointer->GetAttributeAsFloat(name,def);
}

BOOL	CORE::Entity_SetAttribute(ENTITY_ID * id_PTR, char * name, char * attribute)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttribute(name,attribute);
}

BOOL	CORE::Entity_SetAttributeUseDword(ENTITY_ID * id_PTR, char * name, uint32_t val)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttributeUseDword(name,val);
}

BOOL	CORE::Entity_SetAttributeUseFloat(ENTITY_ID * id_PTR, char * name, FLOAT val)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return false;
	if(pE->AttributesPointer == nullptr) return false;
	return pE->AttributesPointer->SetAttributeUseFloat(name,val);
}

void CORE::Entity_SetAttributePointer(ENTITY_ID * id_PTR, ATTRIBUTES * pA)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return;
	pE->AttributesPointer = pA;
}

uint32_t	CORE::Entity_AttributeChanged(ENTITY_ID * id_PTR, ATTRIBUTES * pA)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return 0;
	return pE->AttributeChanged(pA);
}

ATTRIBUTES * CORE::Entity_GetAttributePointer(ENTITY_ID * id_PTR)
{
	ENTITY* pE = GetEntityPointer(id_PTR);
	if(pE == nullptr) return nullptr;
	return pE->AttributesPointer;
}

void CORE::EraseEntities()
{
	for(uint32_t n = 0;n<=CoreState.Atoms_max_orbit;n++)
	{
		if(Atoms_PTR[n] == nullptr) continue;
		EraseEntity(Atoms_PTR[n]->atom_id);
	}
}

void CORE::DeleteEntities()
{
	for(uint32_t n = 0;n<=CoreState.Atoms_max_orbit;n++)
	{
		if(Atoms_PTR[n] == nullptr) continue;
		DeleteEntity(Atoms_PTR[n]->atom_id);
	}
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
	LARGE_INTEGER li;
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
		ENTITY_ID* eid_PTR = l_PTR->GetID();
		while(eid_PTR)
		{
			Trace("ENTITY:");
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

	Sleep(200);
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

void CORE::SetNetActive(bool bActive)
{
	bNetActive = bActive;
}

bool CORE::IsNetActive() const
{
	return bNetActive;
}
