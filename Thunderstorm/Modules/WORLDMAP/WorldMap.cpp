//============================================================================================
//	Spirenkov Maxim, 2001
//--------------------------------------------------------------------------------------------
//	Sea Dogs II
//--------------------------------------------------------------------------------------------
//	WorldMap
//--------------------------------------------------------------------------------------------
//
//============================================================================================

#include "../../Shared/messages.h"
#include "WorldMap.h"
#include "WdmCameraStdCtrl.h"
#include "WdmSea.h"
#include "WdmIslands.h"
#include "WdmClouds.h"
#include "WdmStorm.h"
#include "WdmPlayerShip.h"
#include "WdmFollowShip.h"
#include "WdmMerchantShip.h"
#include "WdmWarringShip.h"
#include "WdmWindUI.h"
#include "WdmIcon.h"
#include "defines.h"
#include "EntityManager.h"

//============================================================================================

//#define EVENTS_OFF
//#define ENCS_OFF

#define WDM_MAX_STORMS		4

long WorldMap::month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//============================================================================================
//���������������, ������������������
//============================================================================================

WorldMap::WorldMap()
{
	Assert(!wdmObjects);
	new WdmObjects();
	firstFreeObject = 0;
	firstObject = -1;
	firstPrObject = -1;
	firstMrObject = -1;
	firstLrObject = -1;
	for (long i = 0; i < WDMAP_MAXOBJECTS; i++) object[i].next = i + 1;
	object[WDMAP_MAXOBJECTS - 1].next = -1;
	wdmObjects->wm = this;
	camera = nullptr;
	srand(GetTickCount());
	encTime = 0.0f;
	aStorm = nullptr;
	aEncounter = nullptr;
	aInfo = nullptr;
	saveData = nullptr;
	timeScale = 1.0f;
	hour = 11.0f;
	day = 14;
	mon = 6;
	year = 1655;
	encCounter = 0;
}

WorldMap::~WorldMap()
{
	if (AttributesPointer)
	{
		AttributesPointer->SetAttribute("WindData", wdmObjects->GetWindSaveString(bufForSave));
	}
	//������� ��������� ����������� �����������
	for (long i = 0; i < wdmObjects->ships.size(); i++)
	{
		if (wdmObjects->ships[i] == wdmObjects->playerShip) continue;
		((WdmEnemyShip *)wdmObjects->ships[i])->SetSaveAttribute(nullptr);
	}
	for (long i = 0; i < wdmObjects->storms.size(); i++)
	{
		wdmObjects->storms[i]->SetSaveAttribute(nullptr);
	}
	//������� ������
	if (wdmObjects->playerShip)
	{
		float x, z, ay;
		wdmObjects->playerShip->GetPosition(x, z, ay);
		AttributesPointer->CreateSubAClass(AttributesPointer, "playerShipX");
		AttributesPointer->CreateSubAClass(AttributesPointer, "playerShipZ");
		AttributesPointer->CreateSubAClass(AttributesPointer, "playerShipAY");
		AttributesPointer->SetAttributeUseFloat("playerShipX", x);
		AttributesPointer->SetAttributeUseFloat("playerShipZ", z);
		AttributesPointer->SetAttributeUseFloat("playerShipAY", ay);
	}
	//������
	if (wdmObjects->camera)
	{
		AttributesPointer->CreateSubAClass(AttributesPointer, "wdmCameraY");
		AttributesPointer->CreateSubAClass(AttributesPointer, "wdmCameraAY");
		AttributesPointer->SetAttributeUseFloat("wdmCameraY", wdmObjects->camera->pos.y);
		AttributesPointer->SetAttributeUseFloat("wdmCameraAY", wdmObjects->camera->ang.y);
	}
	ResetScriptInterfaces();
	/*for(; firstObject >= 0; firstObject = object[firstObject].next)
	{
		delete object[firstObject].ro;
	}*/
	delete camera;
	WdmRenderObject::DeleteAllObjects();
	wdmObjects->Clear();

	delete wdmObjects;
}

//============================================================================================
//Entity
//============================================================================================

//�������������
bool WorldMap::Init()
{
	//GUARD(LocationCamera::Init())
	//Layers
	//api->LayerCreate("execute", true, false);
	EntityManager::SetLayerType(EXECUTE, EntityManager::Layer::Type::execute);
	//api->LayerCreate("realize", true, false);
	EntityManager::SetLayerType(REALIZE, EntityManager::Layer::Type::realize);
	EntityManager::AddToLayer(EXECUTE, GetId(), 10000);
	EntityManager::AddToLayer(REALIZE, GetId(), 10000);

	//DX9 render
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if (!rs) throw std::exception("No service: dx9render");
	rs->SetPerspective((1.57f + 1.0f) / 2);
	wdmObjects->rs = rs;
	//GS
	wdmObjects->gs = (VGEOMETRY *)api->CreateService("geometry");
	//������ ������� �����
	WdmRenderObject* ro;
	//������ �������
	ro = AddObject(new WdmIslands());
	AddObject(ro, -100000);
	AddLObject(ro, 500);
	//
	rs->ProgressView();
	//������ ����
	auto* sea = new WdmSea();
	AddObject(sea);
	AddPObject(sea, 10);
	AddLObject(sea, -1);
	//������ ������
	AddLObject(AddObject(new WdmClouds()), 10000);
	rs->ProgressView();
	//������ ������
	camera = new WdmCameraStdCtrl();
  auto camAy = 0.0f;
  auto camH = -1.0f;
  auto camLock = false;
	if (AttributesPointer)
	{
		camAy = AttributesPointer->GetAttributeAsFloat("wdmCameraAY", camAy);
		camH = AttributesPointer->GetAttributeAsFloat("wdmCameraY", camH);
		camLock = AttributesPointer->GetAttributeAsDword("wdmCameraRotLock", false) != 0;
		wdmObjects->SetWindSaveString(AttributesPointer->GetAttribute("WindData"));
		wdmObjects->shipSpeedOppositeWind = AttributesPointer->GetAttributeAsFloat(
			"shipSpeedOppositeWind", wdmObjects->shipSpeedOppositeWind);
		wdmObjects->shipSpeedOverWind = AttributesPointer->GetAttributeAsFloat(
			"shipSpeedOverWind", wdmObjects->shipSpeedOverWind);
	}
	else
	{
		wdmObjects->SetWindSaveString(nullptr);
	}
	camera->Init(camAy, camH);
	camera->lock = camLock;
	//������ ������� ������
	ro = CreateModel(new WdmPlayerShip(), "Ship");
	Assert(ro);
	AddLObject(ro, 100);
  auto psX = 50.0f;
  auto psZ = 0.0f;
  auto psAy = 0.0f;
  auto psRad = 16.0f;
	if (AttributesPointer)
	{
		psX = AttributesPointer->GetAttributeAsFloat("playerShipX", psX);
		psZ = AttributesPointer->GetAttributeAsFloat("playerShipZ", psZ);
		psAy = AttributesPointer->GetAttributeAsFloat("playerShipAY", psAy);
		psRad = AttributesPointer->GetAttributeAsFloat("playerShipActionRadius", psRad);
		wdmObjects->enemyshipViewDistMin = AttributesPointer->GetAttributeAsFloat(
			"enemyshipViewDistMin", wdmObjects->enemyshipViewDistMin);
		wdmObjects->enemyshipViewDistMax = AttributesPointer->GetAttributeAsFloat(
			"enemyshipViewDistMax", wdmObjects->enemyshipViewDistMax);
		wdmObjects->enemyshipDistKill = AttributesPointer->GetAttributeAsFloat(
			"enemyshipDistKill", wdmObjects->enemyshipDistKill);
		wdmObjects->enemyshipBrnDistMin = AttributesPointer->GetAttributeAsFloat(
			"enemyshipBrnDistMin", wdmObjects->enemyshipBrnDistMin);
		wdmObjects->enemyshipBrnDistMax = AttributesPointer->GetAttributeAsFloat(
			"enemyshipBrnDistMax", wdmObjects->enemyshipBrnDistMax);
		wdmObjects->stormViewDistMin = AttributesPointer->GetAttributeAsFloat(
			"stormViewDistMin", wdmObjects->stormViewDistMin);
		wdmObjects->stormViewDistMax = AttributesPointer->GetAttributeAsFloat(
			"stormViewDistMax", wdmObjects->stormViewDistMax);
		wdmObjects->stormDistKill = AttributesPointer->GetAttributeAsFloat("stormDistKill", wdmObjects->stormDistKill);
		wdmObjects->stormBrnDistMin = AttributesPointer->GetAttributeAsFloat(
			"stormBrnDistMin", wdmObjects->stormBrnDistMin);
		wdmObjects->stormBrnDistMax = AttributesPointer->GetAttributeAsFloat(
			"stormBrnDistMax", wdmObjects->stormBrnDistMax);
		wdmObjects->stormZone = AttributesPointer->GetAttributeAsFloat("stormZone", wdmObjects->stormZone);
    const auto s = AttributesPointer->GetAttribute("debug");
		wdmObjects->isDebug = s && (_stricmp(s, "true") == 0);
		saveData = AttributesPointer->CreateSubAClass(AttributesPointer, "encounters");
	}
	((WdmShip *)ro)->Teleport(psX, psZ, psAy);
	((WdmPlayerShip *)ro)->SetActionRadius(psRad);
	rs->ProgressView();
	//������ ��������� �������
	wdmObjects->islands->SetIslandsData(AttributesPointer, false);
	//�������� ���������� �� ��������
	if (AttributesPointer)
	{
		//Storms interface
		AttributesPointer->CreateSubAClass(AttributesPointer, "storm.num");
		AttributesPointer->CreateSubAClass(AttributesPointer, "storm.cur");
		AttributesPointer->CreateSubAClass(AttributesPointer, "storm.x");
		AttributesPointer->CreateSubAClass(AttributesPointer, "storm.z");
		AttributesPointer->CreateSubAClass(AttributesPointer, "storm.time");
		aStorm = AttributesPointer->FindAClass(AttributesPointer, "storm");
		//Ship encounters inderface
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.num");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.cur");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.x");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.z");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.ay");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.time");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.type");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.attack");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.nation");
		AttributesPointer->CreateSubAClass(AttributesPointer, "encounter.id");
		aEncounter = AttributesPointer->FindAClass(AttributesPointer, "encounter");
		//Info
		AttributesPointer->CreateSubAClass(AttributesPointer, "info.playerInStorm");
		AttributesPointer->CreateSubAClass(AttributesPointer, "info.updateinfo");
		aInfo = AttributesPointer->FindAClass(AttributesPointer, "info");
		//����
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.sec");
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.min");
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.hour");
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.day");
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.month");
		AttributesPointer->CreateSubAClass(AttributesPointer, "date.year");
		aDate = AttributesPointer->FindAClass(AttributesPointer, "date");
	}
	if (aDate)
	{
    const long sec = aDate->GetAttributeAsDword("sec", 1);
    const long min = aDate->GetAttributeAsDword("min", 1);
		hour = float(aDate->GetAttributeAsDword("hour", long(hour)));
		hour += (min + sec / 60.0f) / 60.0f;
		day = aDate->GetAttributeAsDword("day", day);
		mon = aDate->GetAttributeAsDword("month", mon);
		year = aDate->GetAttributeAsDword("year", year);
		timeScale = aDate->GetAttributeAsFloat("hourPerSec", timeScale);
	}
	ResetScriptInterfaces();
	rs->ProgressView();
	//������ �������� ����������

	//����
	auto* windUI = new WdmWindUI();
	windUI->SetAttributes(AttributesPointer);
	AddLObject(AddObject(windUI, 1001), 10100);

	//������
	//ro = CreateModel(new WdmWindRose(), "WindRose");
	//AddLObject(ro, 10099);
	//���������
	//WdmCounter * cnt = new WdmCounter();
	//if(!cnt->Init()) api->Trace("Counter not created");

	//AddLObject(cnt, 10099);
	//������
	AddLObject(AddObject(new WdmIcon(), 1000), 10099);

	//��������� ����������, ���� ������ ����
	if (saveData)
	{
    const auto num = saveData->GetAttributesNum();
		for (uint32_t i = 0; i < num; i++)
		{
      auto a = saveData->GetAttributeClass(i);
			if (!a) continue;
			const char* type = a->GetAttribute("type");
			const char* modelName = a->GetAttribute("modelName");
			if (!type || !type[0])
			{
				saveData->DeleteAttributeClassX(a);
				continue;
			}
			if (_stricmp(type, "Merchant") == 0 && modelName && modelName[0])
			{
				if (!CreateMerchantShip(modelName, nullptr, nullptr, 1.0f, -1.0f, a))
				{
					api->Trace("WoldMap: not loaded merchant encounter.");
				}
				continue;
			}
			if (_stricmp(type, "Follow") == 0 && modelName && modelName[0])
			{
				if (!CreateFollowShip(modelName, 1.0f, -1.0f, a))
				{
					api->Trace("WoldMap: not loaded follow encounter.");
				}
				continue;
			}
			if (_stricmp(type, "Warring") == 0 && modelName && modelName[0])
			{
        const auto attacked = a->GetAttribute("attacked");
				if (attacked)
				{
          auto a1 = saveData->FindAClass(saveData, attacked);
					if (a1)
					{
            const auto modelName1 = a1->GetAttribute("modelName");
						if (modelName1 && modelName1[0])
						{
							if (!CreateWarringShips(modelName, modelName1, -1.0f, a, a1))
							{
								api->Trace("WoldMap: not loaded warring encounter.");
							}
						}
						else
						{
							api->Trace("WoldMap: not loaded warring encounter.");
							saveData->DeleteAttributeClassX(a);
							saveData->DeleteAttributeClassX(a1);
						}
					}
				}
				continue;
			}
			if (_stricmp(type, "Attacked") == 0)
			{
				continue;
			}
			if (_stricmp(type, "Storm") == 0)
			{
        const auto isTornado = (a->GetAttributeAsDword("isTornado", 0) != 0);
				if (!CreateStorm(isTornado, -1.0f, a))
				{
					api->Trace("WoldMap: not loaded storm encounter.");
				}
				continue;
			}
			saveData->DeleteAttributeClassX(a);
		}
	}

	rs->ProgressView();


	//������������ ������� ������
  auto playerShip = (WdmPlayerShip *)wdmObjects->playerShip;
	playerShip->PushOutFromIsland();
  const auto atrData = AttributesPointer->FindAClass(AttributesPointer, "island");
	if (atrData)
	{
		float x, z, ay;
		playerShip->GetPosition(x, z, ay);
		if (!wdmObjects->islands->CheckIslandArea(atrData->GetThisAttr(), x, z))
		{
			wdmObjects->islands->GetNearPointToArea(atrData->GetThisAttr(), x, z);
			playerShip->Teleport(x, z, ay);
		}
	}
	return true;
	//UNGUARD
}

//����������
void WorldMap::Execute(uint32_t delta_time)
{
}

void WorldMap::Realize(uint32_t delta_time)
{
	if (AttributesPointer && wdmObjects->playerShip)
	{
		CVECTOR wind(0.0f);
		float x, z, ay;
		wdmObjects->playerShip->GetPosition(x, z, ay);
    const auto force = wdmObjects->GetWind(x, z, wind);
		AttributesPointer->SetAttributeUseFloat("WindX", wind.x);
		AttributesPointer->SetAttributeUseFloat("WindZ", wind.z);
		AttributesPointer->SetAttributeUseFloat("WindF", force);
	}
	if (!wdmObjects->isPause)
	{
		CONTROL_STATE cs;
		api->Controls->GetControlState("WMapCancel", cs);
		if (cs.state == CST_ACTIVATED)
		{
			if (wdmObjects->playerShip)
			{
				if (!((WdmPlayerShip *)wdmObjects->playerShip)->ExitFromMap()) api->Event("ExitFromWorldMap");
			}
			else api->Event("ExitFromWorldMap");
		}
	}
	//---------------------------------------------------------
  const auto dltTime = 0.001f * delta_time;
	//��������� ����
	if (hour < 0.0f) hour = 0.0f;
	hour += dltTime * timeScale;
  auto days = long(hour / 24.0f);
	hour = (hour / 24.0f - days) * 24.0f;
  const auto dtHour = long(hour);
  const auto dtMin = long((hour - dtHour) * 60.0f);
  const auto dtSec = long(((hour - dtHour) * 60.0f - dtMin) * 60.0f);
	aDate->SetAttributeUseDword("sec", dtSec);
	aDate->SetAttributeUseDword("min", dtMin);
	aDate->SetAttributeUseDword("hour", dtHour);
	if (days)
	{
		for (; days > 0; days--)
		{
			day++;
			if (day > month[mon])
			{
				day -= month[mon++];
				if (mon > 12)
				{
					mon = 1;
					year++;
					aDate->SetAttributeUseDword("year", year);
				}
				aDate->SetAttributeUseDword("month", mon);
			}
			aDate->SetAttributeUseDword("day", day);

#ifndef EVENTS_OFF
			api->Event("WorldMap_UpdateDate", "f", hour);
			wdmObjects->isNextDayUpdate = true;
			api->Event("NextDay");
#endif
		}
	}
	else
	{
#ifndef EVENTS_OFF
		api->Event("WorldMap_UpdateDate", "f", hour);
#endif
	}
	//
  auto tmp = aDate->GetAttribute("sec");
	if (tmp) strcpy_s(wdmObjects->attrSec, tmp);
	tmp = aDate->GetAttribute("min");
	if (tmp) strcpy_s(wdmObjects->attrMin, tmp);
	tmp = aDate->GetAttribute("hour");
	if (tmp) strcpy_s(wdmObjects->attrHour, tmp);
	tmp = aDate->GetAttribute("day");
	if (tmp) strcpy_s(wdmObjects->attrDay, tmp);
	tmp = aDate->GetAttribute("month");
	if (tmp) strcpy_s(wdmObjects->attrMonth, tmp);
	tmp = aDate->GetAttribute("year");
	if (tmp) strcpy_s(wdmObjects->attrYear, tmp);
	//---------------------------------------------------------
	if (camera && !wdmObjects->isPause) camera->Move(dltTime, rs);
  auto isKill = false;
	//�������� ��� �������
	for (auto i = firstObject; i >= 0; i = object[i].next)
	{
		if (!object[i].ro->killMe) object[i].ro->Update(object[i].ro->isEnablePause && wdmObjects->isPause
			                                                ? 0.0f
			                                                : dltTime);
		isKill |= object[i].ro->killMe;
	}
	//������ ������� ���� ����
	if (isKill)
	{
		for (auto i = firstObject; i >= 0;)
			if (object[i].ro->killMe)
			{
				DeleteObject(object[i].ro);
				i = firstObject;
			}
			else i = object[i].next;
	}
	//������� ���������� �������
	if (aStorm) aStorm->SetAttributeUseDword("num", wdmObjects->storms.size());
	if (aEncounter) aEncounter->SetAttributeUseDword(
		"num", wdmObjects->ships.size() - (wdmObjects->playerShip != nullptr));
	//�������
	encTime += dltTime;
	if (encTime >= 1.0f && wdmObjects->playerShip && !wdmObjects->isPause)
	{
    auto psx = 0.0f, psz = 0.0f, psay = 0.0f;
		wdmObjects->playerShip->GetPosition(psx, psz, psay);
#ifndef ENCS_OFF
		api->Event("WorldMap_EncounterCreate", "ffff", encTime, psx, psz, psay);
#endif
		encTime = 0.0f;
	}
	rs->SetRenderState(D3DRS_FOGENABLE, FALSE);
	rs->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (auto i = firstPrObject; i >= 0; i = object[i].next)
	{
		if (!object[i].ro->killMe) object[i].ro->PRender(rs);
	}
	for (auto i = firstMrObject; i >= 0; i = object[i].next)
	{
		if (!object[i].ro->killMe) object[i].ro->MRender(rs);
	}
	for (auto i = firstLrObject; i >= 0; i = object[i].next)
	{
		if (!object[i].ro->killMe) object[i].ro->LRender(rs);
	}
	//������� �����
	wdmObjects->UpdateWind(dltTime);
	wdmObjects->isNextDayUpdate = false;
	//�������� ������� ���������� ����������
	if (AttributesPointer)
	{
		const char* upd = AttributesPointer->GetAttribute("addQuestEncounters");
		if (upd && upd[0] != 0)
		{
			api->Event("WorldMap_AddQuestEncounters", nullptr);
		}
	}
}

//���������
uint64_t WorldMap::ProcessMessage(MESSAGE& message)
{
	char buf[256];
	char sName[256];
	char sName2[256];
	switch (message.Long())
	{
	case MSG_WORLDMAP_CREATESTORM:
		{
      const auto isTornado = message.Long() != 0;
			CreateStorm(isTornado);
		}
		break;
	case MSG_WORLDMAP_CREATEENC_MER:
		{
			message.String(sizeof(sName), sName);
			message.String(sizeof(buf), buf);
			message.String(sizeof(sName2), sName2);
      const auto kSpeed = message.Float();
      const auto timeOut = message.Float(); //boal
			return CreateMerchantShip(sName, buf, sName2, kSpeed, timeOut); //boal
		}
		break;
		// boal 04/01/06 -->
	case MSG_WORLDMAP_CREATEENC_MER_XZ:
		{
			message.String(sizeof(sName), sName);
      const auto fx1 = message.Float();
      const auto fz1 = message.Float();
      const auto fx2 = message.Float();
      const auto fz2 = message.Float();
      const auto kSpeed = message.Float();
      const auto timeOut = message.Float();
			return CreateMerchantShipXZ(sName, fx1, fz1, fx2, fz2, kSpeed, timeOut);
		}
		break;
		// boal <--
	case MSG_WORLDMAP_CREATEENC_FLW:
		{
			message.String(sizeof(sName), sName);
      const auto kSpeed = message.Float();
      const auto timeOut = message.Float();
			return CreateFollowShip(sName, kSpeed, timeOut);
		}
		break;
	case MSG_WORLDMAP_CREATEENC_WAR:
		{
			message.String(sizeof(sName), sName);
			message.String(sizeof(sName), sName2);
      const auto timeOut = message.Float();
			return CreateWarringShips(sName, sName2, timeOut);
		}
		break;
	case MSG_WORLDMAP_CREATEENC_RELEASE:
		ReleaseEncounters();
		break;
	case MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA:
		if (wdmObjects->playerShip)
		{
			if (!((WdmPlayerShip *)wdmObjects->playerShip)->ExitFromMap()) api->Event("ExitFromWorldMap");
		}
		else api->Event("ExitFromWorldMap");
		break;
	}
	return 0;
}

//��������� ��������
uint32_t WorldMap::AttributeChanged(ATTRIBUTES* apnt)
{
	float x, z, ay;
	if (!apnt || !AttributesPointer) return 0;
	if (_stricmp(apnt->GetThisName(), "deleteUpdate") == 0)
	{
		for (long i = 0; i < wdmObjects->ships.size(); i++)
		{
			if (wdmObjects->ships[i] == wdmObjects->playerShip) continue;
			((WdmEnemyShip *)wdmObjects->ships[i])->DeleteUpdate();
		}
		for (long i = 0; i < wdmObjects->storms.size(); i++)
		{
			wdmObjects->storms[i]->DeleteUpdate();
		}
	}
	else if (_stricmp(apnt->GetThisName(), "playerShipUpdate") == 0)
	{
		if (wdmObjects->playerShip)
		{
			float x, z, ay;
			wdmObjects->playerShip->GetPosition(x, z, ay);
			AttributesPointer->SetAttributeUseFloat("playerShipX", x);
			AttributesPointer->SetAttributeUseFloat("playerShipZ", z);
			AttributesPointer->SetAttributeUseFloat("playerShipAY", ay);
		}
	}
	else if (_stricmp(apnt->GetThisName(), "cur") == 0)
	{
    auto pa = apnt->GetParent();
		if (pa == aStorm)
		{
      const auto cur = long(pa->GetAttributeAsDword("cur"));
			if (cur >= 0 && cur < wdmObjects->storms.size())
			{
				Assert(wdmObjects->storms[cur]);
				wdmObjects->storms[cur]->GetPosition(x, z);
				pa->SetAttributeUseFloat("x", x);
				pa->SetAttributeUseFloat("z", z);
				pa->SetAttributeUseFloat("time", wdmObjects->storms[cur]->GetLiveTime());
			}
			else
			{
				pa->SetAttributeUseDword("cur", -1);
			}
		}
		else if (pa == aEncounter)
		{
      const auto cur = long(pa->GetAttributeAsDword("cur"));
			//��������� ������ ����������
			long i = 0;
			for (long enc = 0; i < wdmObjects->ships.size(); i++)
			{
				if (wdmObjects->ships[i] == wdmObjects->playerShip) continue;
				if (enc == cur) break;
				enc++;
			}
			if (i < wdmObjects->ships.size())
			{
				Assert(wdmObjects->ships[i]);
				wdmObjects->ships[i]->GetPosition(x, z, ay);
				pa->SetAttributeUseFloat("x", x);
				pa->SetAttributeUseFloat("z", z);
				pa->SetAttributeUseFloat("ay", ay);
        const auto es = (WdmEnemyShip *)wdmObjects->ships[i];
				pa->SetAttributeUseFloat("time", es->GetLiveTime());
				char buf[32];
				sprintf_s(buf, "%i", es->type);
				pa->SetAttribute("type", buf);
				pa->SetAttributeUseDword("select", es->isSelect);
				pa->SetAttribute("id", (char *)((WdmEnemyShip *)wdmObjects->ships[i])->GetAttributeName());
				//���� ���� ���������, ��������� ��� ������
				if (es->attack)
				{
					Assert(es->attack != es);
					long i, j = 0;
					for (i = 0; i < wdmObjects->ships.size(); i++)
					{
						if (wdmObjects->ships[i] == wdmObjects->playerShip) continue;
						if (wdmObjects->ships[i] == es->attack) break;
						j++;
					}
					if (i >= wdmObjects->ships.size()) j = -1;
					pa->SetAttributeUseDword("attack", j);
				}
				else
				{
					pa->SetAttributeUseDword("attack", -1);
				}
			}
			else
			{
				pa->SetAttributeUseDword("cur", -1);
			}
		}
	}
	else if (_stricmp(apnt->GetThisName(), "updateinfo") == 0)
	{
    auto pa = apnt->GetParent();
		if (pa == aInfo)
		{
			pa->SetAttributeUseDword("playerInStorm", long(wdmObjects->playarInStorm));
		}
	}
	else
	{
		for (auto pa = apnt; pa; pa = pa->GetParent())
		{
			if (_stricmp(pa->GetThisName(), "labels") == 0)
			{
				wdmObjects->islands->SetIslandsData(AttributesPointer, true);
				return 0;
			}
		}
	}
	return 0;
}

//============================================================================================
//���������� ���������
//============================================================================================

//�������� ������
WdmRenderObject* WorldMap::AddObject(WdmRenderObject* obj, long level)
{
	if (!obj) return nullptr;
  const auto i = GetObject(firstObject, level);
	object[i].ro = obj;
	return obj;
}

//�������� ������ � ������ ��������� �� ���������
void WorldMap::AddPObject(WdmRenderObject* obj, long level)
{
	if (!obj) return;
  const auto i = GetObject(firstPrObject, level);
	object[i].ro = obj;
}

//�������� ������ � ������ ��������� ���������
void WorldMap::AddMObject(WdmRenderObject* obj, long level)
{
	if (!obj) return;
  const long i = GetObject(firstMrObject, level);
	object[i].ro = obj;
}

//�������� ������ � ������ ��������� ����� ���������
void WorldMap::AddLObject(WdmRenderObject* obj, long level)
{
	if (!obj) return;
  const long i = GetObject(firstLrObject, level);
	object[i].ro = obj;
}

//������� ������
void WorldMap::DeleteObject(WdmRenderObject* obj)
{
	if (!obj) return;
	//���������� �� ���� �������, ������ ������ �� �������
	for (long i = firstObject, j; i >= 0;)
	{
		j = i;
		i = object[i].next;
		if (object[j].ro == obj) FreeObject(firstObject, j);
	}
	for (long i = firstPrObject, j; i >= 0;)
	{
		j = i;
		i = object[i].next;
		if (object[j].ro == obj) FreeObject(firstPrObject, j);
	}

	for (long i = firstMrObject, j; i >= 0;)
	{
		j = i;
		i = object[i].next;
		if (object[j].ro == obj) FreeObject(firstMrObject, j);
	}
	for (long i = firstLrObject, j; i >= 0;)
	{
		j = i;
		i = object[i].next;
		if (object[j].ro == obj) FreeObject(firstLrObject, j);
	}
	delete obj;
}


//============================================================================================
//������������
//============================================================================================

//���������� ���������

//�������� ������ �� ������� � ������ � ����������� �������
long WorldMap::GetObject(long& first, long level)
{
	Assert(firstFreeObject >= 0);
  const long i = firstFreeObject;
	firstFreeObject = object[firstFreeObject].next;
	object[i].ro = nullptr;
	object[i].level = level;
	object[i].prev = -1;
	object[i].next = -1;
	if (first >= 0)
	{
		if (level >= object[first].level)
		{
			long j;
			for (j = first; object[j].next >= 0 && level >= object[object[j].next].level; j = object[j].next);
			object[i].prev = j;
			object[i].next = object[j].next;
			object[j].next = i;
			if (object[i].next >= 0) object[object[i].next].prev = i;
		}
		else
		{
			object[i].next = first;
			first = i;
		}
	}
	else first = i;
	return i;
}

//��������� ������ �� ������
void WorldMap::FreeObject(long& first, long i)
{
	Assert(i >= 0.0f && i < WDMAP_MAXOBJECTS);
	object[i].ro = nullptr;
	object[i].level = 0;
	if (object[i].next >= 0) object[object[i].next].prev = object[i].prev;
	if (object[i].prev >= 0) object[object[i].prev].next = object[i].next;
	else first = object[i].next;
	object[i].prev = -1;
	object[i].next = firstFreeObject;
	firstFreeObject = i;
}

//���������

//������������������� �������� � ������� � ������ ������ �������
WdmRenderObject* WorldMap::CreateModel(WdmRenderModel* rm, const char* modelName, bool pr, bool mr, bool lr,
                                       long objectLevel, long drawLevel)
{
	if (!modelName || !modelName[0])
	{
		delete rm; // boal fix ����� ������
		return nullptr;
	}
	if (!rm->Load(modelName))
	{
		delete rm;
		return nullptr;
	}
	AddObject(rm, objectLevel);
	if (pr) AddPObject(rm, drawLevel);
	if (mr) AddMObject(rm, drawLevel);
	if (lr) AddLObject(rm, drawLevel);
	return rm;
}

//������� �����, ���� ��� ��������, � ���������� ����� �����
bool WorldMap::CreateStorm(bool isTornado, float time, ATTRIBUTES* save)
{
	if (wdmObjects->storms.size() >= WDM_MAX_STORMS) return false;
	auto* s = new WdmStorm();
	AddLObject(s, 800);
	if (!AddObject(s)) return false;
	if (time > 0.0f)
	{
		if (time < 1.0f) time = 1.0f;
		s->SetLiveTime(time);
	}
	if (!save) save = GetEncSaveData("Storm", "EncounterID1");
	s->SetSaveAttribute(save);
	s->isTornado = isTornado;
	return true;
}

//������� �������� �����
bool WorldMap::CreateMerchantShip(const char* modelName, const char* locNameStart, const char* locNameEnd, float kSpeed,
                                  float time, ATTRIBUTES* save)
{
	if (kSpeed < 0.1f) kSpeed = 0.1f;
	WdmShip* ship = new WdmMerchantShip();
	if (ship->killMe)
	{
		delete ship;
		return false;
	}
	if (!CreateModel(ship, modelName)) return false;
	AddLObject(ship, 100);
	//���� ����� ���� �����
	if (!wdmObjects->islands)
	{
		api->Trace("World map: Islands not found");
	}
	CVECTOR gpos;
	if (!locNameEnd || !locNameEnd[0])
	{
		if (wdmObjects->islands)
		{
			if (!wdmObjects->islands->GetRandomMerchantPoint(gpos))
			{
				api->Trace("World map: Locators <Merchants:...> not found");
			}
		}
	}
	else
	{
		if (wdmObjects->islands)
		{
			if (!wdmObjects->islands->GetQuestLocator(locNameEnd, gpos))
			{
				api->Trace("World map: Quest locator <Quests:%s> for merchant not found", locNameEnd);
			}
		}
	}
	((WdmMerchantShip *)ship)->Goto(gpos.x, gpos.z, 2.0f);
	//���� ����, �������� ������� �������
	if (locNameStart && locNameStart[0])
	{
		if (wdmObjects->islands)
		{
			if (wdmObjects->islands->GetQuestLocator(locNameStart, gpos))
			{
				ship->Teleport(gpos.x, gpos.z, rand() * (PI * 2.0f / RAND_MAX));
			}
			else
			{
				api->Trace("World map: Quest locator <Quests:%s> for merchant not found", locNameStart); // boal fix
			}
		}
	}
	//��������
	ship->SetMaxSpeed(kSpeed);
	//����� �����
	if (time >= 0.0f)
	{
		if (time < 3.0f) time = 3.0f;
		((WdmEnemyShip *)ship)->SetLiveTime(time);
	}
	if (!save) save = GetEncSaveData("Merchant", "EncounterID1");
	if (save)
	{
		save->SetAttribute("modelName", (char *)modelName);
	}
	((WdmEnemyShip *)ship)->SetSaveAttribute(save);
	return true;
}

// boal ������� �������� ����� � �����������
bool WorldMap::CreateMerchantShipXZ(const char* modelName, float x1, float z1, float x2, float z2, float kSpeed,
                                    float time, ATTRIBUTES* save)
{
	if (kSpeed < 0.1f) kSpeed = 0.1f;
	WdmShip* ship = new WdmMerchantShip();
	if (ship->killMe)
	{
		delete ship;
		return false;
	}
	if (!CreateModel(ship, modelName)) return false;
	AddLObject(ship, 100);
	//���� ����� ���� �����
	if (!wdmObjects->islands)
	{
		api->Trace("World map: Islands not found");
	}

	((WdmMerchantShip *)ship)->Goto(x2, z2, 2.0f); // ����
	//���� ����, �������� ������� �������
	ship->Teleport(x1, z1, rand() * (PI * 2.0f / RAND_MAX)); // ������
	//��������
	ship->SetMaxSpeed(kSpeed);
	//����� �����
	if (time >= 0.0f)
	{
		if (time < 3.0f) time = 3.0f;
		((WdmEnemyShip *)ship)->SetLiveTime(time);
	}
	if (!save) save = GetEncSaveData("Merchant", "EncounterID1");
	if (save)
	{
		save->SetAttribute("modelName", (char *)modelName);
	}
	((WdmEnemyShip *)ship)->SetSaveAttribute(save);
	return true;
}

//������� �������� ������������ ���
bool WorldMap::CreateFollowShip(const char* modelName, float kSpeed, float time, ATTRIBUTES* save)
{
	if (kSpeed < 0.1f) kSpeed = 0.1f;
	WdmShip* ship = new WdmFollowShip();
	if (ship->killMe)
	{
		delete ship;
		return false;
	}
	if (!CreateModel(ship, modelName)) return false;
	AddLObject(ship, 100);
	//��������
	ship->SetMaxSpeed(kSpeed);
	//����� �����
	if (time >= 0.0f)
	{
		if (time < 1.0f) time = 1.0f;
		((WdmEnemyShip *)ship)->SetLiveTime(time);
	}
	VDATA* isSkipEnable = api->Event("WorldMap_IsSkipEnable");
	if (isSkipEnable)
	{
		long skipEnable = 0;
		if (isSkipEnable->Get(skipEnable))
		{
			((WdmEnemyShip *)ship)->canSkip = skipEnable != 0;
		}
	}
	if (!save) save = GetEncSaveData("Follow", "EncounterID1");
	if (save)
	{
		save->SetAttribute("modelName", (char *)modelName);
	}
	((WdmEnemyShip *)ship)->SetSaveAttribute(save);
	return true;
}

bool WorldMap::CreateWarringShips(const char* modelName1, const char* modelName2, float time, ATTRIBUTES* save1,
                                  ATTRIBUTES* save2)
{
	static const float pi = 3.14159265359f;
	//������ ���������
	auto* ship1 = new WdmWarringShip();
	if (ship1->killMe)
	{
		delete ship1;
		return false;
	}
	if (!CreateModel(ship1, modelName1)) return false;
	auto* ship2 = new WdmWarringShip();
	if (ship2->killMe)
	{
		delete ship2;
		return false;
	}
	if (!CreateModel(ship2, modelName2)) return false;
  const float moveRadius = (ship1->modelRadius + ship2->modelRadius) * (0.4f + (rand() & 3) * (0.1f / 3.0f));
  const float fullRadius = 0.6f * (moveRadius + 2.0f * max(ship1->modelRadius, ship2->modelRadius));
	//����� �������
	float x, z;
	if (!WdmEnemyShip::GeneratePosition(fullRadius, 1.5f, x, z)) return false;
	//����� ����
  const float angl = rand() * 2.0f * pi / (RAND_MAX + 1);
	//�������� ������������ ������
  const float dx = moveRadius * cosf(angl);
  const float dz = -moveRadius * sinf(angl);
	AddLObject(ship1, 100);
	ship1->Teleport(x + dx, z + dz, angl + pi * (rand() & 1));
	AddLObject(ship2, 100);
	ship2->Teleport(x - dx, z - dz, angl + pi * (rand() & 1));
	ship2->SetLiveTime(ship1->GetLiveTime());
	//������������� ��������������
	ship1->attack = ship2;
	ship2->attack = ship1;
	//����� �����
	if (time >= 0.0f)
	{
		if (time < 1.0f) time = 1.0f;
		ship1->SetLiveTime(time);
		ship2->SetLiveTime(time);
	}
	if (!save2) save2 = GetEncSaveData("Attacked", "EncounterID1");
	if (!save1) save1 = GetEncSaveData("Warring", "EncounterID2");
	if (save1 && save2)
	{
		save1->SetAttribute("attacked", save2->GetThisName());
	}
	if (save1)
	{
		save1->SetAttribute("modelName", (char *)modelName1);
	}
	if (save2)
	{
		save2->SetAttribute("modelName", (char *)modelName2);
	}
	ship1->SetSaveAttribute(save1);
	ship2->SetSaveAttribute(save2);
	return true;
}

//����� ���������� � ������ �� ����� ����������
bool WorldMap::FindIslandPosition(const char* name, float& x, float& z, float& r)
{
	return false;
}

void WorldMap::ResetScriptInterfaces() const {
	if (aStorm)
	{
		aStorm->SetAttributeUseDword("num", 0);
		aStorm->SetAttributeUseDword("cur", 0);
		aStorm->SetAttributeUseDword("x", 0);
		aStorm->SetAttributeUseDword("z", 0);
		aStorm->SetAttributeUseDword("time", 0);
	}
	if (aEncounter)
	{
		aEncounter->SetAttributeUseDword("num", 0);
		aEncounter->SetAttributeUseDword("cur", 0);
		aEncounter->SetAttributeUseDword("x", 0);
		aEncounter->SetAttributeUseDword("z", 0);
		aEncounter->SetAttributeUseDword("ay", 0);
		aEncounter->SetAttributeUseDword("time", 0);
		aEncounter->SetAttribute("type", "-1");
		aEncounter->SetAttributeUseDword("attack", -1);
		aEncounter->SetAttributeUseDword("nation", -1);
		aEncounter->SetAttribute("id", "");
	}
	if (aInfo)
	{
		aInfo->SetAttributeUseDword("playerInStorm", 0);
	}
}

//������� ��� ����������
void WorldMap::ReleaseEncounters()
{
	//������� ��������� ����������� �����������
	for (long i = 0; i < wdmObjects->ships.size(); i++)
	{
		if (wdmObjects->ships[i] == wdmObjects->playerShip) continue;
		((WdmEnemyShip *)wdmObjects->ships[i])->SetSaveAttribute(nullptr);
		wdmObjects->ships[i]->killMe = true;
	}
	for (long i = 0; i < wdmObjects->storms.size(); i++)
	{
		wdmObjects->storms[i]->SetSaveAttribute(nullptr);
		wdmObjects->storms[i]->killMe = true;
	}
}

//������� ������� ��� ���������� ���������� ����������
ATTRIBUTES* WorldMap::GetEncSaveData(const char* type, const char* retName)
{
	if (!saveData) return nullptr;
	//������� ��� ��������
	encCounter++;
	char atrName[64];
	long i;
	for (i = 0; i < 1000000; i++, encCounter++)
	{
		sprintf_s(atrName, "enc_%u", encCounter);
		ATTRIBUTES* a = saveData->FindAClass(saveData, atrName);
		if (!a) break;
		if (a->FindAClass(a, "needDelete"))
		{
			saveData->DeleteAttributeClassX(a);
			break;
		}
	}
	if (i == 1000000) return nullptr;
	//������ �����
	ATTRIBUTES* a = saveData->CreateSubAClass(saveData, atrName);
	if (!a) return nullptr;
	//������������� ���
	a->SetAttribute("type", (char *)type);
	//��������� ���
	if (AttributesPointer)
	{
		AttributesPointer->SetAttribute((char *)retName, atrName);
	}
	return a;
}
