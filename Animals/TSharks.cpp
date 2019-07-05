#include "TSharks.h"
#include "../Common_h/ship_base.h"
#include "../Common_h/rands.h"
#include "../Shared/messages.h"
#include "../Common_h/defines.h"

#pragma warning (disable : 4244)

//--------------------------------------------------------------------
TSharks::TSharks()
	:enabled(false)
	,shipsCount(0)
{
	PZERO(sharks, SHARK_COUNT << 2);
	PZERO(ships,  SHARK_MAX_SHIPS  << 2);
}

//--------------------------------------------------------------------
TSharks::~TSharks()
{
	for (int i=0; i<sharksCount; i++)
	{
		if (sharks[i])
			delete sharks[i];
	}

	for (int i=0; i<shipsCount; i++)
	{
		if (ships[i])
			delete ships[i];
	}

	api->DeleteEntity(sharkModel);
}

//--------------------------------------------------------------------
void TSharks::LoadSettings()
{
	INIFILE * ini = fio->OpenIniFile(ANIMALS_INI_FILENAME);
	if (!ini)
		return;

	sharksCount = ini->GetLong(ANIMALS_SHARKS_SECTION, "count", SHARK_COUNT);
	maxDistance = ini->GetFloat(ANIMALS_SHARKS_SECTION, "distance", SHARK_DISTANCE);

	delete ini;
}

//--------------------------------------------------------------------
void TSharks::Init()
{
	LoadSettings();

	renderService = (VDX9RENDER *)api->CreateService("dx9render");
	if(!renderService)
		throw std::exception("!Sharks: No service 'dx9render'");

	api->FindClass(&seaID, "sea", 0);
	sea = (SEA_BASE*) api->GetEntityPointer(&seaID);
	if (!sea)
	{
		enabled = false;
		return;
	}

	int i;
	for (i=0; i<sharksCount; i++)
	{
		sharks[i] = new TShark();
		sharks[i]->TDynamicObject::Initialize(CVECTOR(0.0f, 0.0f, 0.0f), maxDistance);
		sharks[i]->depth = 0;
		sharks[i]->time = 0;
		TDynamicSystem::AddDeflector(sharks[i]);
	}

	entid_t shipID;
	shipsCount = 0;
	if (api->FindClass(&shipID, "ship", 0))
	{
		ships[shipsCount] = new TShip();
		ships[shipsCount]->ship = (SHIP_BASE*) api->GetEntityPointer(&shipID);
		TDynamicSystem::AddDeflector(ships[i]);
		++shipsCount;
		while (api->FindClassNext(&shipID))
		{
			ships[shipsCount] = new TShip();
			ships[shipsCount]->ship = (SHIP_BASE*) api->GetEntityPointer(&shipID);
			//TDynamicSystem::AddDeflector(ships[i]);
			++shipsCount;
			if (++shipsCount == SHARK_MAX_SHIPS)
				break;
		}
	}

	TDynamicSystem::AddAttractor(&cameraObject);

	api->CreateEntity(&sharkModel,"MODELR");
	api->Send_Message(sharkModel,"ls",MSG_MODEL_LOAD_GEO, ANIMALS_SHARK_FILENAME);
}

//--------------------------------------------------------------------
uint32_t TSharks::ProcessMessage(long _code, MESSAGE & message)
{
	uint32_t outValue = 0;

	switch (_code)
	{
	case MSG_ANIMALS_SHARKS_SHOW:
		enabled = true;
		break;

	case MSG_ANIMALS_SHARKS_HIDE:
		enabled = false;
		break;

	}

	return outValue;
}

//--------------------------------------------------------------------
void TSharks::Execute(uint32_t _dTime)
{
	if (!enabled)
		return;

	CVECTOR pos, ang;
	float   persp;
	renderService->GetCamera(pos, ang, persp);

	cameraObject.SetXYZ(pos);
	for (int i=0; i<shipsCount; i++)
		ships[i]->SetXYZ(ships[i]->ship->GetPos());

	float speedK = ((float) _dTime) / 200.0f;
	for (int i=0; i<sharksCount; i++)
	{
		sharks[i]->Calculate(attractors, MAX_DYNAMIC_OBJECTS,deflectors, MAX_DYNAMIC_OBJECTS, speedK);
		sharks[i]->time += _dTime;
	}
}

//--------------------------------------------------------------------
void TSharks::Realize(uint32_t _dTime)
{
	if (!enabled)
		return;
/*
	CVECTOR cameraPos, cameraAng;
	float   cameraPersp;
	renderService->GetCamera(cameraPos, cameraAng, cameraPersp);
*/
	MODEL *shark = (MODEL*) api->GetEntityPointer(&sharkModel);
	if (!shark)
		return;

	for (int i = 0; i<sharksCount; i++)
	{
		static const float TIME_DIVIDER = 100.0f;
		static const float OSC_AMPLITUDE = 0.2f;
		float sharkAngle = sharks[i]->GetAngle();
		CVECTOR sharkPos = sharks[i]->GetXYZ();
		float sharkTime = sharks[i]->time / TIME_DIVIDER;
		CVECTOR ang(0.0f, PId2-sharkAngle - (PId2 / 15.0f)*cosf(sharkTime), 0.0f);
		CVECTOR pos;
		pos.x = sharkPos.x + OSC_AMPLITUDE*cosf(sharkAngle + PId2)*sinf(sharkTime);
		pos.z = sharkPos.z + OSC_AMPLITUDE*sinf(sharkAngle + PId2)*sinf(sharkTime);
		pos.y = sea->WaveXZ(pos.x, pos.z) - sharks[i]->depth;
		shark->mtx.BuildMatrix(ang,pos);
		shark->Realize(_dTime);
	}
}

//--------------------------------------------------------------------
