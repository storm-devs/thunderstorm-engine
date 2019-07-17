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


#include "vmodule_api.h"
#include "dx9render.h"

#include "Lizard.h"


class Lizards : public Entity
{
public:
	Lizards();
	virtual ~Lizards();

	//Инициализация
	bool Init() override;
	//Исполнение
	void Execute(uint32_t delta_time);
	//Рисование
	void Realize(uint32_t delta_time);

	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta);
			break;
		case Stage::realize:
			Realize(delta);
			break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}


	Lizard lizard[8];
	long num;
};

#endif
