#include <stdio.h>
#include "WaterFlare.h"

#define WATERFLARE_DIR		"WEATHER\\SEA\\FLARE\\"

WATERFLARE::WATERFLARE()
{
	//GUARD(WATERFLARE::WATERFLARE())
	iFlareTex = -1;
	iFlaresNum = 0;
	RS = nullptr;
	pWeather = nullptr;
	pfAlpha = nullptr;
	pRSRect = nullptr;
	//UNGUARD
}

WATERFLARE::~WATERFLARE()
{
	//GUARD(WATERFLARE::~WATERFLARE())
	STORM_DELETE(pRSRect);
	STORM_DELETE(pfAlpha);
	//UNGUARD
}

bool WATERFLARE::Init()
{
	//GUARD(bool WATERFLARE::Init())

	api->LayerAdd("realize",GetId(),-1);
	api->LayerAdd("execute",GetId(),-1);
	
	SetDevice();

	//UNGUARD
	return true;
}

void WATERFLARE::SetDevice()
{
	//GUARD(void WATERFLARE::SetDevice())

	RS = (VDX9RENDER *)api->CreateService("dx9render");
	if (!RS) throw std::exception("No service: dx9render");

	entid_t	ent;
	if (!api->FindClass(&ent,"Weather",0)) throw std::exception("No found WEATHER entity!");
	pWeather = (WEATHER_BASE*)api->GetEntityPointer(&ent);

	//UNGUARD
}

bool WATERFLARE::CreateState(ENTITY_STATE_GEN * state_gen)
{
	//GUARD(bool WATERFLARE::CreateState(ENTITY_STATE_GEN * state_gen))
	//UNGUARD
	return true;
}

bool WATERFLARE::LoadState(ENTITY_STATE * state)
{
	//GUARD(bool WATERFLARE::LoadState(ENTITY_STATE * state))
	//UNGUARD
	return true;
}

void WATERFLARE::Execute(uint32_t Delta_Time)
{
	//GUARD(void WATERFLARE::Execute(uint32_t Delta_Time))

	/*if (pWeather->GetLong(whi_weather_update)) 
	{
		char str[256];
		// create texture
		sprintf_s(str,"%swaterflare.tga",WATERFLARE_DIR);
		if (iFlareTex>0) RS->TextureRelease(iFlareTex);
		iFlareTex = RS->TextureCreate(str);
		GenerateFlares();
	}*/

	//UNGUARD
}

void WATERFLARE::GenerateFlares()
{
	iFlaresNum = 1024 + (rand()%64);
	pRSRect = (RS_RECT*)new RS_RECT[iFlaresNum];
	pfAlpha = (float*)new float[iFlaresNum];
	for (long i=0;i<iFlaresNum;i++)
	{
		pfAlpha[i] = FRAND(-40.0f);
		pRSRect[i].vPos = CVECTOR(FRAND(1000.0f),0.0f,FRAND(1000.0f));
		pRSRect[i].fAngle = 0.0f;
		pRSRect[i].dwSubTexture = 0;
		pRSRect[i].fSize = 0.5f;
	}
}

void WATERFLARE::Realize(uint32_t Delta_Time)
{
	//GUARD(void WATERFLARE::Realize(uint32_t Delta_Time))

	for (long i=0;i<iFlaresNum;i++)
	{
		float fDeltaTime = float(Delta_Time) * 0.001f;
		pfAlpha[i] += fDeltaTime;
		if (pfAlpha[i]>2.0f)
		{
			pfAlpha[i] = 0.0f;
			pRSRect[i].vPos = CVECTOR(FRAND(200.0f),0.0f,FRAND(200.0f));
		}
		uint32_t dwAlpha = uint32_t(255.0f * ((pfAlpha[i]>1.0f) ? 2.0f - pfAlpha[i] : pfAlpha[i]));
		pRSRect[i].dwColor = RGB(dwAlpha,dwAlpha,dwAlpha);
	}

	RS->TextureSet(0,iFlareTex);
	RS->DrawRects(pRSRect,iFlaresNum,"waterflare");

	//UNGUARD
}

void WATERFLARE::ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam)
{
	//GUARD(void WATERFLARE::ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam))
	//UNGUARD
}
