//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	Tornado
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _Tornado_H_
#define _Tornado_H_

#include "TornadoParticles.h"
#include "NoiseCloud.h"
#include "Debris.h"

class Tornado : public ENTITY  
{
//--------------------------------------------------------------------------------------------
//Конструирование, деструктурирование
//--------------------------------------------------------------------------------------------
public:
	Tornado();
	virtual ~Tornado();

	//Инициализация
	bool Init();
	//Исполнение
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
	uint32_t _cdecl ProcessMessage(MESSAGE & message);

	void SetAlpha(float a);

//--------------------------------------------------------------------------------------------
//Инкапсуляция
//--------------------------------------------------------------------------------------------
private:
	VDX9RENDER * rs;

	VSoundService * soundService;
	long sID;

	Pillar pillar;
	TornadoParticles particles;
	NoiseCloud noiseCloud;
	Debris debris;

	float eventCounter;

	float liveTime;
	float galhpa;

	long ib, vb;
};

#endif

