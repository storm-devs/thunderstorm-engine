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


class LocRats : public ENTITY  
{
public:
	LocRats();
	virtual ~LocRats();

//--------------------------------------------------------------------------------------------
public:
	//�������������
	bool Init();
	//����������
	void Execute(uint32_t delta_time);
	//���������
	void Realize(uint32_t delta_time);

	//���������
	uint32_t ProcessMessage(MESSAGE & message);

//--------------------------------------------------------------------------------------------
private:
	LocRat rat[32];
	long num;
};

#endif

