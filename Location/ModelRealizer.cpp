#include "ModelRealizer.h"
#include "..\common_h\messages.h"
#include "..\common_h\cvector4.h"
#include "lights.h"
#include "Character.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

extern float	fCausticScale, fCausticDelta, fFogDensity, fCausticDistance;
extern CVECTOR4	v4CausticColor;
extern bool		bCausticEnable;
extern float	fCausticFrame;
extern long		iCausticTex[32];

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
void LocModelRealizer::Execute(dword delta_time)
{
}

void LocModelRealizer::Realize(dword delta_time)
{
	if( !bShow ) return;
	ENTITY* pE = api->GetEntityPointer( &eid_model );
	if( pE ) {
		BOOL bLight0Enable;
		dword dwLighting;
		if (lights) {
			rs->GetRenderState(D3DRS_LIGHTING, &dwLighting);
			rs->GetLightEnable(0, &bLight0Enable);
			lights->SetCharacterLights();
			rs->SetRenderState(D3DRS_LIGHTING, TRUE);
			rs->LightEnable(0, TRUE);
		}

		pE->Realize(delta_time);

		if (lights) {
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
			Render().SetVertexShaderConstantF(10, (const float*)&CVECTOR4(fCausticScale, fCausticDelta, 0.0f, 0.0f), 1);
			Render().SetVertexShaderConstantF(11, (const float*)&v4CausticColor, 1);
			Render().SetVertexShaderConstantF(12, (const float*)&CVECTOR4(fFogDensity, 0.0f, 0.0f, 0.0f), 1);
			Render().SetVertexShaderConstantF(13, (const float*)&CVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 1);
			Render().SetVertexShaderConstantF(14, (const float*)&CVECTOR4(0.0f, 1.0f, 0.0f, 0.0f), 1);
			Render().SetVertexShaderConstantF(15, (const float*)&CVECTOR4(1.0f / fCausticDistance, 1.0f, 0.0f, 0.0f), 1);

			Render().TextureSet(1, iCausticTex[long(fCausticFrame) % 32]);
			Render().TextureSet(2, iCausticTex[(long(fCausticFrame) + 1) % 32]);

			// рисуем каустики
			Geometry().SetCausticMode(true);
			pE->Realize(0);
			Geometry().SetCausticMode(false);
		}
	}
}

//Сообщения
dword _cdecl LocModelRealizer::ProcessMessage(MESSAGE & message)
{
	switch(message.Long())
	{
	case 1:
		eid_model = message.EntityID();
		lights = (Lights*)message.Long();
	break;
	case 2:
		bShow = message.Long()!=0;
		break;
	}
	return 0;
}
