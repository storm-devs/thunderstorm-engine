#ifndef _BALLSPLASH_H_
#define _BALLSPLASH_H_

#include "../common_h/geometry.h"
#include "../common_h/dx9render.h"
#include "../common_h/sea_base.h"
#include "../common_h/CVECTOR.h"
#include "BallSplashDefines.h"
#include "TSplash.h"

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////

class BALLSPLASH: public ENTITY
{
public:
	BALLSPLASH();
	virtual ~BALLSPLASH();

	virtual bool Init();
	virtual uint32_t ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);

private:
	void InitializeSplashes();
	TSplash *TryToAddSplash(const CVECTOR &_pos, const CVECTOR &_dir);

	TSplash    splashes[MAX_SPLASHES];
	VDX9RENDER *renderer;
	SEA_BASE   *sea;
};

#endif