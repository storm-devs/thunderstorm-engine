#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include "Typedef.h"
#include "../common_h/Weather_base.h"
#include <vector>

#define MAX_LIGHTNING_TEXTURES		2

class LIGHTNING : public ENTITY
{
	struct flash_t
	{
		char	sTechnique[128];
		float	fSize;
		float	fTime;
	};
	
	struct lightning_t
	{
		// script parameters
		uint32_t		dwSubTexture;
		uint32_t		dwFlickerTime;
		float		fTime;
		float		fSize, fScaleX, fScaleY;
		CVECTOR		vPos;
		
		// inner parameters
		float		fAlpha;
		float		fPower;

		char		sTechnique[128];
		
		flash_t		Flash;
	};

	std::vector<lightning_t>	aLightnings;

	uint32_t			dwSubTexX, dwSubTexY;
	long			iLightningTexture, iFlashTexture;

	float			fKDist;
	long			iFlickerTime;

	WEATHER_BASE	* pWeather;
	VDX9RENDER		* pRS;
	COLLIDE			* pCollide;
	VIDWALKER		* pVWSunTrace;

	void			Release();
	void			CalcFlashPower(lightning_t * pL);

public:
	LIGHTNING();
	~LIGHTNING();

	void	SetDevice();
	bool	Init();
	void	Realize(uint32_t Delta_Time);
	void	Execute(uint32_t Delta_Time);
	bool	CreateState(ENTITY_STATE_GEN * state_gen);
	bool	LoadState(ENTITY_STATE * state);
	uint32_t	ProcessMessage(MESSAGE & message);
	uint32_t	AttributeChanged(ATTRIBUTES * pAttributeChanged);
};

#endif