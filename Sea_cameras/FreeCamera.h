#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "..\common_h\dx9render.h"
#include "..\common_h\Island_Base.h"
#include "Common_Camera.h"

class FREE_CAMERA : public COMMON_CAMERA
{
private:
	VDX9RENDER *	pRS;
	CVECTOR			vPos,vAng;
	float			fFov;
	long			iLockX,iLockY;

	ISLAND_BASE	*	pIslandBase;
	BOOL			bCameraOnEarth;
	float			fCameraOnEarthHeight;

public:
	 FREE_CAMERA();
	virtual ~FREE_CAMERA();

	void SetDevice();
	bool Init();
	void Move(uint32_t DeltaTime);
	void Execute(uint32_t Delta_Time);
	bool CreateState(ENTITY_STATE_GEN * state_gen);
	bool LoadState(ENTITY_STATE * state);

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);
};

#endif