#include "ModelRealizer.h"
#include "CVector4.h"
#include "Lights.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

extern float fCausticScale, fCausticDelta, fFogDensity, fCausticDistance;
extern CVECTOR4 v4CausticColor;
extern bool bCausticEnable;
extern float fCausticFrame;
extern long iCausticTex[32];

LocModelRealizer::LocModelRealizer()
{
	lights = nullptr;
	bShow = true;
}

LocModelRealizer::~LocModelRealizer()
{
}

//Инициализация
bool LocModelRealizer::Init()
{
	rs = (VDX9RENDER*)api->CreateService("dx9render");
	gs = (VGEOMETRY *)api->CreateService("geometry");
	return true;
}

//Исполнение
void LocModelRealizer::Execute(uint32_t delta_time)
{
}

void LocModelRealizer::Realize(uint32_t delta_time)
{
	if (!bShow) return;
	Entity* pE = EntityManager::GetEntityPointer(eid_model);
	if (pE)
	{
		BOOL bLight0Enable;
		uint32_t dwLighting;
		if (lights)
		{
			rs->GetRenderState(D3DRS_LIGHTING, &dwLighting);
			rs->GetLightEnable(0, &bLight0Enable);
			lights->SetCharacterLights();
			rs->SetRenderState(D3DRS_LIGHTING, TRUE);
			rs->LightEnable(0, TRUE);
		}

		pE->ProcessStage(Stage::realize, delta_time);
		if (lights)
		{
			lights->DelCharacterLights();
			rs->SetRenderState(D3DRS_LIGHTING, dwLighting);
			rs->LightEnable(0, bLight0Enable);
		}

		if (bCausticEnable)
		{
			// константы
			// 10 - (caustic scale, caustic frame, 0, 0)
			// 11 - diffuse
			// 12 - (fog density, fog_start, 0, 0)
			// 13 - (0, 0, 0, 0)

			fCausticDelta = fCausticFrame - long(fCausticFrame);
			rs->SetVertexShaderConstantF(10, (const float*)&CVECTOR4(fCausticScale, fCausticDelta, 0.0f, 0.0f), 1);
			rs->SetVertexShaderConstantF(11, (const float*)&v4CausticColor, 1);
			rs->SetVertexShaderConstantF(12, (const float*)&CVECTOR4(fFogDensity, 0.0f, 0.0f, 0.0f), 1);
			rs->SetVertexShaderConstantF(13, (const float*)&CVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 1);
			rs->SetVertexShaderConstantF(14, (const float*)&CVECTOR4(0.0f, 1.0f, 0.0f, 0.0f), 1);
			rs->SetVertexShaderConstantF(15, (const float*)&CVECTOR4(1.0f / fCausticDistance, 1.0f, 0.0f, 0.0f), 1);

			rs->TextureSet(1, iCausticTex[long(fCausticFrame) % 32]);
			rs->TextureSet(2, iCausticTex[(long(fCausticFrame) + 1) % 32]);

			// рисуем каустики
			gs->SetCausticMode(true);
			pE->ProcessStage(Stage::realize, 0);
			gs->SetCausticMode(false);
		}
	}
}

//Сообщения
uint64_t LocModelRealizer::ProcessMessage(MESSAGE& message)
{
	switch (message.Long())
	{
	case 1:
		eid_model = message.EntityID();
		lights = (Lights*)message.Pointer();
		break;
	case 2:
		bShow = message.Long() != 0;
		break;
	}
	return 0;
}
