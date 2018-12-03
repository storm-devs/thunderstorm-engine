#ifndef _BASE_VIDEO_H_
#define _BASE_VIDEO_H_

#include "..\..\common_h\vmodule_api.h"
#include "..\..\common_h\dx9render.h"

class xiBaseVideo : public ENTITY
{
public:
	virtual void SetShowVideo(bool bShowVideo) {}
	virtual IDirect3DTexture9 * GetCurrentVideoTexture() {return nullptr;}
};

#endif
