#ifndef WEATHER_RAIN_HPP
#define WEATHER_RAIN_HPP

#include "typedef.h"
#include "../Common_h/Weather_Base.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/ship_base.h"
#include <vector>

#define NUM_SEA_DROPS				500
#define D3DRAINVERTEX_FORMAT		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define D3DSEADROPVERTEX_FORMAT		(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef struct
{
	CVECTOR		vPos;
	uint32_t		dwColor;
} RAINVERTEX;

struct SEADROPVERTEX
{
	CVECTOR		vPos;
	uint32_t		dwColor;
	float		tu, tv;
};

typedef struct
{
	float		fWindFlaw,fWindSpeedJitter;
	uint32_t		dwTime;
	CVECTOR		vPos;
	CVECTOR		vAng;
} rainblock_t;

class RAIN : public ENTITY
{
struct ship_t
{
	ENTITY_ID	eid;
	SHIP_BASE	* pShip;
};

struct seadrop_t
{
	CVECTOR vPos;
	float	fTime;
	float	fLifeTime;
};

struct drop_t
{
	CVECTOR vPos;
	float	fLifeTime;
	long	iShip;
	//SHIP_BASE * pShip;
};

private:
	long				iRainDropsTexture;
	float				fDropsDeltaTime;
	std::vector<RS_RECT>		aRects;
	std::vector<drop_t>		aDrops;
	std::vector<seadrop_t>	aSeaDrops;
	std::vector<ship_t>		aShips;

	bool				bShow;

	WEATHER_BASE	* pWeather;

	uint32_t		dwRainMaxBlend, dwRainColor, dwRainR, dwRainG, dwRainB;
	float		fDropLength, fRainWindSpeed, fRainSpeed, fWindPower, fWindAngle,
				fRainJitter, fRainWindSpeedJitter;
	
	bool		bRainbowEnable;
	long		iRainbowTex;
	std::string		sRainbowTexture;

	uint32_t		dwRainTimeBlend;
	uint32_t		dwNumRainBlocks;
	rainblock_t	*pRainBlocks;

	CVECTOR		vCamPos,vCamAng;

	float		fRainHeight,fRainRadius;
	uint32_t		dwNumDrops;

	long		iVertexBuffer;

	uint32_t		dwDropsColor;
	uint32_t		dwDropsNearNum, dwDropsFarNum;
	float		fDropsNearRadius, fDropsFarRadius;
	float		fDropsLifeTime;
	float		fDropsSize;
	std::string		sDropsTexture, sSeaDropsTexture;

	long		iSeaDropTex;
	long		iIBSeaDrops;
	long		iVBSeaDrops;

	void	GenerateRandomDrop(CVECTOR *vPos);
	void	GenerateRain();
	void	InitialSomeBlockParameters(long iIdx);
	void	Release();
	void	RealizeDrops(uint32_t Delta_Time);

public:
	RAIN();
	~RAIN();

	void	SetDevice();
	bool	Init();
	void	Realize(uint32_t Delta_Time);
	void	Execute(uint32_t Delta_Time);
	bool	CreateState(ENTITY_STATE_GEN * state_gen);
	bool	LoadState(ENTITY_STATE * state);
	uint32_t _cdecl ProcessMessage(MESSAGE & message);
	uint32_t	AttributeChanged(ATTRIBUTES * pAttribute);
};

#endif