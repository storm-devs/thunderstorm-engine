#ifndef _TBUTTERFLIES_H_
#define _TBUTTERFLIES_H_

#include "../Common_h/Matrix.h"
#include "../Common_h/Animation.h"
#include "../Common_h/geometry.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/collide.h"
#include "AnimalsDefines.h"
#include "TButterfly.h"
#include "../Common_h/TIVBufferManager.h"

#define Y_REDEFINE_TIME		250

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class TButterflies
{
public:
	TButterflies();
	virtual ~TButterflies();

	uint32_t ProcessMessage(long _code, MESSAGE & message);
	void Init();
	void Realize(uint32_t _dTime);
	void Execute(uint32_t _dTime);

private:
	void LoadSettings();

	VDX9RENDER *renderService;
	COLLIDE *collide;
	VIDWALKER *walker;
	TIVBufferManager *ivManager;
	ENTITY_ID  butterflyModel;
	TButterfly butterflies[BUTTERFLY_COUNT];
	long butterfliesCount;

	float maxDistance;
	
	bool enabled;
	long yDefineTime;
	long texture;
};

#endif // !defined
