#pragma once

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/collide.h"

class CameraDialog : public Entity
{
	VDX9RENDER * rs;
	COLLIDE *col;
	CVECTOR pos, ang;
	float fov;
	entid_t person, personId;

	float time;
	struct ANIFRAME
	{
		CVECTOR pos, ang;
	};
	long frames;
	ANIFRAME* track;

public:
	CameraDialog();
	~CameraDialog();
	bool Init();
	void Execute(uint32_t Delta_Time);
	void Realize(uint32_t Delta_Time);
	uint32_t ProcessMessage(MESSAGE &msg);
};


//API_MODULE_START("CameraDialog")
//	CREATE_CLASS(0,CameraDialog)
//API_MODULE_END

