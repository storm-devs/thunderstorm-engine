#ifndef _BASE_VIDEO_H_
#define _BASE_VIDEO_H_

#include "../vmodule_api.h"
#include "../dx9render.h"

class xiBaseVideo : public Entity
{
public:
	virtual void SetShowVideo(bool bShowVideo) {}
	virtual IDirect3DTexture9 * GetCurrentVideoTexture() {return nullptr;}
};

#endif
