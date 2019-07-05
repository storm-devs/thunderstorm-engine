#ifndef WATERFLARE_HPP
#define WATERFLARE_HPP

#include "Typedef.h"
#include "../common_h/Weather_base.h"

class WATERFLARE : public Entity
{
	RS_RECT			*pRSRect;
	float			*pfAlpha;
	long			iFlareTex,iFlaresNum;
	WEATHER_BASE	*pWeather;
	VDX9RENDER		*RS;


	void	GenerateFlares();

public:
	WATERFLARE();
	~WATERFLARE();

	void SetDevice();
	bool Init();
	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);
	bool CreateState(Entity_STATE_GEN * state_gen);
	bool LoadState(Entity_STATE * state);
	void ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam);
};

#endif