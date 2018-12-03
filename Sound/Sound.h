#ifndef _SOUND_H_
#define _SOUND_H_

#include "../common_h/entity.h"
#include "../common_h/dx9render.h"

///////////////////////////////////////////////////////////////////
// DEFINES & TYPES
///////////////////////////////////////////////////////////////////
// SoundPlay (..., type, ...)
#define SOUND_WAV_3D     1
#define SOUND_MP3_STEREO 2
#define SOUND_MP3_3D     3
#define SOUND_WAV_STEREO 4
//SoundSet3DParam(..., type, ...)
#define SOUND_PARAM_MAX_DISTANCE    1
#define SOUND_PARAM_MIN_DISTANCE    2
#define SOUND_PARAM_POSITION        3
#define SOUND_STRING_SIZE         512

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class SOUND: public ENTITY
{
public:
	SOUND();
	virtual ~SOUND();

	virtual bool Init();
	virtual uint32_t _cdecl ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);

private:
	VSoundService *soundService;
	VDX9RENDER	  *renderer;
};

//API_MODULE_START("Sound")
//	CREATE_CLASS(0, SOUND)
//API_MODULE_END

#endif
