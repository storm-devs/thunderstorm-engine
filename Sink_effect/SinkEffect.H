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

class SINKEFFECT: public ENTITY
{
public:
	SINKEFFECT();
	virtual ~SINKEFFECT();

	virtual bool Init();
	virtual uint32_t ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);

private:
	void InitializeSinks();
	TSink *TryToAddSink(const CVECTOR &_pos, float _r);

	TSink    sinks[MAX_SINKS];
	VDX9RENDER *renderer;
	SEA_BASE *sea;
};

#endif