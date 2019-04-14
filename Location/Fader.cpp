//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
//	Fader
//--------------------------------------------------------------------------------------------
//
//============================================================================================

#include "Fader.h"
#include "../Shared/messages.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

long Fader::numberOfTips = 0;
long Fader::currentTips = -1;

Fader::Fader()
{
	rs = nullptr;
	isWork = false;
	haveFrame = false;
	endFade = false;
	alpha = 0.0f;
	surface = nullptr;
	renderTarget = nullptr;
	textureID = -1;
	tipsID = -1;
	eventStart = false;
	eventEnd = false;
	deleteMe = 0;
}

Fader::~Fader()
{
	if(surface) rs->Release(surface);
	if(renderTarget) renderTarget->Release();
	surface = nullptr;
	renderTarget = nullptr;
	if(rs)
	{
		if(textureID >= 0) rs->TextureRelease(textureID);
		if(tipsID >= 0) rs->TextureRelease(tipsID);
	}
}

//Инициализация
bool Fader::Init()
{
	GUARD(Fader::Init())
	//Проверим что единственные
	ENTITY_ID eid;
	if(api->FindClass(&eid, "Fader", 0))
	{
		if(api->GetEntityPointer(&eid) != this || api->FindClassNext(&eid))
		{
			if(fadeIn == ((Fader *)api->GetEntityPointer(&eid))->fadeIn)
			{
				api->Trace("Fader::Init() -> Fader already created, %s", fadeIn ? "fade in phase" : "fade out phase");
			}
			//!!!
			//return false;
		}
	}
	//Layers
	api->LayerCreate("fader_realize", true, false);
	api->LayerSetRealize("fader_realize", true);
	api->LayerAdd("fader_realize", GetID(), -256);
	api->LayerCreate("fader_execute", true, false);
	api->LayerSetExecute("fader_execute", true);
	api->LayerAdd("fader_execute", GetID(), -256);
	//DX9 render
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if(!rs) STORM_THROW("No service: dx9render");
	D3DVIEWPORT9 vp;
	rs->GetViewport(&vp);
	w = float(vp.Width);
	h = float(vp.Height);
	if(w <= 0 || h <= 0) return false;
	if(rs->GetRenderTarget(&renderTarget) != D3D_OK) return false;
	//Зачитаем количество типсов, если надо
	if(!numberOfTips)
	{
		INIFILE * ini = fio->OpenIniFile(api->EngineIniFileName());
		if(ini)
		{
			numberOfTips = ini->GetLong(nullptr, "numoftips", -1);
			delete ini;
		}else numberOfTips = -1;
		if(numberOfTips > 9999) numberOfTips = 9999;
	}
	return true;
	UNGUARD
}

//Сообщения
uint32_t _cdecl Fader::ProcessMessage(MESSAGE & message)
{
	char _name[MAX_PATH];
	switch(message.Long())
	{
	case FADER_OUT:	//Запустить затемнение экрана
		alpha = 0.0f;
		fadeSpeed = message.Float();
		if(fadeSpeed > 0.0f) fadeSpeed = 1.0f/fadeSpeed; else fadeSpeed = 0.0f;
		isWork = true;
		haveFrame = false;
		fadeIn = false;
		isStart = true;
		endFade = false;
		isAutodelete = message.Long() != 0;
		eventStart = false;
		eventEnd = false;
		break;
	case FADER_IN:	//Запустить проявление экрана
		alpha = 0.0f;
		fadeSpeed = message.Float();
		if(fadeSpeed < 0.00001f) fadeSpeed = 0.00001f;
		fadeSpeed = 1.0f/fadeSpeed;
		haveFrame = false;
		isWork = true;
		fadeIn = true;
		isStart = true;
		endFade = false;
		isAutodelete = message.Long() != 0;
		haveFrame = false;
		if(surface) surface->Release();
		surface = nullptr;
		eventStart = false;
		eventEnd = false;
		break;
	case FADER_STARTFRAME:
		haveFrame = true;
		break;
	case FADER_PICTURE:
		if(textureID >= 0 && rs) rs->TextureRelease(textureID);
		message.String(sizeof(_name),_name);
		textureID = rs->TextureCreate(_name);
		if(rs)
		{
			rs->SetProgressImage(_name);
			//Текстура подсказки
			if(numberOfTips > 0)
			{
				sprintf_s(_name, "tips\\tips_%.4u.tga", rand() % numberOfTips);
				tipsID = rs->TextureCreate(_name);
				rs->SetTipsImage(_name);
			}
		}
		break;
	case FADER_PICTURE0:
		if(textureID >= 0 && rs) rs->TextureRelease(textureID);
		message.String(sizeof(_name),_name);
		textureID = rs->TextureCreate(_name);
		if(rs)
		{
			rs->SetProgressImage(_name);
			//Текстура подсказки
			if(numberOfTips > 0)
			{
				//sprintf_s(_name, "tips\\tips_%.4u.tga", rand() % numberOfTips);
				char * pTipsName = rs->GetTipsImage();
				if(pTipsName)
				{
					tipsID = rs->TextureCreate(pTipsName);
					//rs->SetTipsImage(_name);
				}
			}
		}
		break;
	}
	return 0;
}

//Работа
void Fader::Execute(uint32_t delta_time)
{
	//api->Trace("fader frame");
	if(deleteMe)
	{
		deleteMe++;
		if(deleteMe >= 3) api->DeleteEntity(GetID());
	}
	if(eventStart)
	{
		eventStart = false;
		if(!fadeIn)
		{
			api->PostEvent("FaderEvent_StartFade", 0, "li", fadeIn, GetID());
			//api->Trace("FaderEvent_StartFade");
		}else{
			api->PostEvent("FaderEvent_StartFadeIn", 0, "li", fadeIn, GetID());
		//	api->Trace("FaderEvent_StartFadeIn");
		}
	}
	if(eventEnd)
	{
		eventEnd = false;
		deleteMe = isAutodelete;
		if(!fadeIn)
		{
			api->PostEvent("FaderEvent_EndFade", 0, "li", fadeIn, GetID());
			//api->Trace("FaderEvent_EndFade");
		}else{
			api->PostEvent("FaderEvent_EndFadeIn", 0, "li", fadeIn, GetID());
		//	api->Trace("FaderEvent_EndFadeIn");
		}
	}
}


void Fader::Realize(uint32_t delta_time)
{
	if(!isWork) return;
	if(isStart) eventStart = true;
	//Снятие и рисование стартового кадра
	if(!endFade)
	{
		if(haveFrame)
		{
			if(isStart)
			{
				//Надо снять шот
				bool isOk = false;
				D3DSURFACE_DESC desc;
				if(renderTarget->GetDesc(&desc) == D3D_OK)
				{
					if(rs->CreateOffscreenPlainSurface(desc.Width, desc.Height, desc.Format, &surface) == D3D_OK)
					{
						if(rs->GetRenderTargetData(renderTarget, surface) == D3D_OK)
						{
							isOk = true;
						}
					}
				}
				if(!isOk) api->Trace("Screen shot for fader not created!");
			}else{
				//Копируем шот
				if(rs->UpdateSurface(surface, nullptr, 0, renderTarget, nullptr) != D3D_OK)
				{
					api->Trace("Can't copy fader screen shot to render target!");
				}
			}
		}
	}
	//Рисование затеняющего прямоугольника
	static struct
	{
		float x, y, z, rhw;
		uint32_t color;
		float u, v;
	} drawbuf[6];
	if(alpha >= 1.0f)
	{
		alpha = 1.0f;
		if(!endFade)
		{
			endFade = true;
			eventEnd = true;
		}
	}
	uint32_t color = (uint32_t((fadeIn ? (1.0f - alpha) : alpha)*255.0f) << 24);
	if(textureID >= 0)  color |= 0x00ffffff;
	drawbuf[0].x = 0.0f; drawbuf[0].y = 0.0f; drawbuf[0].z = 0.5f; drawbuf[0].rhw = 1.0f; drawbuf[0].color = color; drawbuf[0].u = 0.0f; drawbuf[0].v = 0.0f;
	drawbuf[1].x = w;    drawbuf[1].y = 0.0f; drawbuf[1].z = 0.5f; drawbuf[1].rhw = 1.0f; drawbuf[1].color = color; drawbuf[1].u = 1.0f; drawbuf[1].v = 0.0f;
	drawbuf[2].x = 0.0f; drawbuf[2].y = h; drawbuf[2].z = 0.5f; drawbuf[2].rhw = 1.0f; drawbuf[2].color = color; drawbuf[2].u = 0.0f; drawbuf[2].v = 1.0f;
	drawbuf[3].x = 0.0f; drawbuf[3].y = h; drawbuf[3].z = 0.5f; drawbuf[3].rhw = 1.0f; drawbuf[3].color = color; drawbuf[3].u = 0.0f; drawbuf[3].v = 1.0f;
	drawbuf[4].x = w;    drawbuf[4].y = 0.0f; drawbuf[4].z = 0.5f; drawbuf[4].rhw = 1.0f; drawbuf[4].color = color; drawbuf[4].u = 1.0f; drawbuf[4].v = 0.0f;
	drawbuf[5].x = w;    drawbuf[5].y = h;    drawbuf[5].z = 0.5f; drawbuf[5].rhw = 1.0f; drawbuf[5].color = color; drawbuf[5].u = 1.0f; drawbuf[5].v = 1.0f;
	rs->TextureSet(0, textureID);
	if(tipsID >= 0)
	{
		rs->TextureSet(1, tipsID);
		rs->DrawPrimitiveUP(D3DPT_TRIANGLELIST, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXTUREFORMAT2, 2, drawbuf, sizeof(drawbuf[0]), "FaderWithTips");
	}else{
		rs->DrawPrimitiveUP(D3DPT_TRIANGLELIST, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXTUREFORMAT2, 2, drawbuf, sizeof(drawbuf[0]), "Fader");
	}
	//Увеличение alpha
	if(!endFade)
	{
		if(fadeSpeed > 0.0f) alpha += delta_time*0.001f*fadeSpeed; else alpha = 1.0f;
	}
	isStart = false;
}


