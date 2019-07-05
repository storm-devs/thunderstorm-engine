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


	entid_t mdl;
	CVECTOR cnt;
	float kTime, time;
	float y, dltY;
	float kRad, dltRad;
	float ay;
	float kAy, timeAy;
};

#endif
