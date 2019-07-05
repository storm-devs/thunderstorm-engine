#ifndef _BASE_VIDEO_H_
#define _BASE_VIDEO_H_

#include "../../Common_h/vmodule_api.h"
#include "../../Common_h/dx9render.h"

class xiBaseVideo : public Entity
{
public:
	virtual void SetShowVideo(bool bShowVideo) {}
	virtual IDirect3DTexture9 * GetCurrentVideoTexture() {return nullptr;}
};

#endif
