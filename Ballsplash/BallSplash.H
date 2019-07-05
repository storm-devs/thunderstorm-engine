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

class BALLSPLASH: public Entity
{
public:
	BALLSPLASH();
	virtual ~BALLSPLASH();

	virtual bool Init();
	virtual uint32_t ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);
	void BALLSPLASH::ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}


private:
	void InitializeSplashes();
	TSplash *TryToAddSplash(const CVECTOR &_pos, const CVECTOR &_dir);

	TSplash    splashes[MAX_SPLASHES];
	VDX9RENDER *renderer;
	SEA_BASE   *sea;
};

#endif