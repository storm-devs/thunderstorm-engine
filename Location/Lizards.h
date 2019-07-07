//============================================================================================
//	Spirenkov Maxim
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	Lizards
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _Lizards_h_
#define _Lizards_h_


#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"

#include "Lizard.h"


class Lizards : public Entity
{
public:
	Lizards();
	virtual ~Lizards();

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


	Lizard lizard[8];
	long num;
};

#endif

