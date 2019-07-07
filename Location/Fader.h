//============================================================================================
//	Spirenkov Maxim, 2003
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	Fader
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _Fader_H_
#define _Fader_H_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"

class Fader : public Entity  
{
//--------------------------------------------------------------------------------------------
//Конструирование, деструктурирование
//--------------------------------------------------------------------------------------------
public:
	Fader();
	virtual ~Fader();

	//Инициализация
	bool Init();
	//Сообщения
	uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}

	//Работа
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);


//--------------------------------------------------------------------------------------------
//Инкапсуляция
//--------------------------------------------------------------------------------------------
private:
	VDX9RENDER * rs;
	IDirect3DSurface9 * renderTarget;
	IDirect3DSurface9 * surface;

	bool isWork;
	bool haveFrame;
	bool fadeIn;
	bool isStart;
	bool isAutodelete;
	bool endFade;
	float fadeSpeed;
	float alpha;
	float w, h;

	bool eventStart;
	bool eventEnd;
	long deleteMe;

	long textureID;
	long tipsID;

public:
	static long numberOfTips;
	static long currentTips;
};

#endif

