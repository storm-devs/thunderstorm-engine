//============================================================================================
//	Spirenkov Maxim, 2003
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	LocRats
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _LocRats_h_
#define _LocRats_h_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"

#include "LocRat.h"


class LocRats : public Entity  
{
public:
	LocRats();
	virtual ~LocRats();

//--------------------------------------------------------------------------------------------
public:
	//Инициализация
	bool Init();
	//Исполнение
	void Execute(uint32_t delta_time);
	//Рисование
	void Realize(uint32_t delta_time);
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

	//Сообщения
	uint32_t ProcessMessage(MESSAGE & message);

//--------------------------------------------------------------------------------------------
private:
	LocRat rat[32];
	long num;
};

#endif

