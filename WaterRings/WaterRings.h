#pragma once

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/collide.h"
#include "../Common_h/model.h"
#include "../Common_h/sea_base.h"
//#include "..\geom_lib\geos.h"
#include "../Common_h/TIVBufferManager.h"

#define MAX_RINGS     25
#define FADE_IN_TIME  200
#define FADE_OUT_TIME 1200

#define GRID_STEPS_COUNT 3
#define TRIANGLES_COUNT  ((GRID_STEPS_COUNT - 1)*(GRID_STEPS_COUNT - 1)*2)
#define Y_DELTA          .01f

#define RING_FVF (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_TEXTUREFORMAT2)
struct RING_VERTEX
{
	CVECTOR pos;
	uint32_t color;
	float tu,tv;
};

enum tRingState {RING_WALK, RING_RUN, RING_SWIM};
struct tRing
{
	bool active;
	long activeTime;
	long ivIndex;
	float x,z;
	tRingState state;	
	bool firstUpdate;
	float cosA, sinA;
};

class WaterRings : public ENTITY
{
public:
	WaterRings();
	~WaterRings();
	bool Init();
	void Realize(uint32_t _dTime);
	uint32_t _cdecl ProcessMessage(MESSAGE &message);

private:
	void UpdateGrid(int _ringI, uint16_t *iPointer, RING_VERTEX *vPointer, long vOffset);

	VDX9RENDER       *renderService;
	SEA_BASE		 *sea;
	TIVBufferManager *ivManager;
	long             ringTexture;
	tRing			 rings[MAX_RINGS];
};
