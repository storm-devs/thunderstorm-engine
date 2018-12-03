 #ifndef _TSPLASH_H_
#define _TSPLASH_H_

#include "..\common_h\dx9render.h"
#include "..\common_h\sea_base.h"
#include "..\common_h\defines.h"
#include "..\common_h\CVECTOR.h"
//#include "..\SoundService\VSoundService.h"

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
struct GRID_VERTEX
{
	CVECTOR pos;
	uint32_t color;
	float tu,tv;
};

struct GRID_VERTEX2
{
	CVECTOR pos;
	uint32_t color;
	float tu,tv;
	float tu2,tv2;
};

class TSplash  
{
public:
	TSplash();
	virtual ~TSplash();

	void Initialize(INIFILE * _ini, IDirect3DDevice9 *_device, SEA_BASE *sea, VDX9RENDER *_renderer);
	void Release();
	void Start(const CVECTOR &_pos, const CVECTOR &_dir);
	bool Process(uint32_t _dTime);
	bool Process2(uint32_t _dTime);
	void PostProcess();
	void PostProcess2();
	void Realize(uint32_t _dTime);
	void Realize2(uint32_t _dTime);
	bool Enabled();

	static bool startRender;
	static uint32_t lockTicks, fillTicks, unlockTicks, realizeTicks, processCount, topIndex, topIndex2;

private:
	float HeightF(uint32_t _time, float _r, float _k);

	bool enabled;

	static VDX9RENDER *renderer;
	SEA_BASE *sea;
	IDirect3DDevice9 *device;

	static long vBuffer, iBuffer, texture, texture2, vBuffer2, iBuffer2;
	static int buffersUsage;
	uint32_t time;

	float width2;
	float distortDivider;
	CVECTOR center,dir;
	float growK;
	float height, midY;
};

#endif 
