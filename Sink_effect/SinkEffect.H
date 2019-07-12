#ifndef _SINKEFFECT_H_
#define _SINKEFFECT_H_

#include "../common_h/geometry.h"
#include "../common_h/dx9render.h"
#include "../common_h/sea_base.h"
#include "../common_h/CVECTOR.h"
#include "SinkSplashDefines.h"
#include "TSink.h"

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////

class SINKEFFECT: public Entity
{
public:
	SINKEFFECT();
	virtual ~SINKEFFECT();

	virtual bool Init();
	virtual uint32_t ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t dTime);
	virtual void Execute(uint32_t dTime);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}
private:
	void InitializeSinks();
	TSink *TryToAddSink(const CVECTOR &_pos, float _r);

	TSink    sinks[MAX_SINKS];
	VDX9RENDER *renderer;
	SEA_BASE *sea;
};

#endif