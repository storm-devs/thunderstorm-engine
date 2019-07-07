//============================================================================================
//	Spirenkov Maxim, 2003
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	LocEagle
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _LocEagle_H_
#define _LocEagle_H_

#include "../Common_h/model.h"

class LocEagle : public Entity  
{
public:
	LocEagle();
	virtual ~LocEagle();

	//Инициализация
	bool Init();
	//Исполнение
	void Execute(uint32_t delta_time);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		//case Stage::REALIZE:
		//	Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}


	entid_t mdl;
	CVECTOR cnt;
	float kTime, time;
	float y, dltY;
	float kRad, dltRad;
	float ay;
	float kAy, timeAy;
};

#endif
