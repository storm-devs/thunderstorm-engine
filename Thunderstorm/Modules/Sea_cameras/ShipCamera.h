#ifndef SEA_SHIP_CAMERA_HPP
#define SEA_SHIP_CAMERA_HPP

#include "dx9render.h"
#include "sea_base.h"
#include "model.h"
#include "Island_Base.h"
#include "Common_Camera.h"

#define MIN_DIST	70.f
#define MAX_DIST	120.f
#define MIN_XANG	PI / 6
#define MAX_XANG	(PI / 2 + PI / 12)
#define CAMERA_HEIGHT	1.0f
#define CAMERA_ANGLE	PI / 18

class SHIP_CAMERA : public COMMON_CAMERA
{
private:
	long		iLockX, iLockY;

	float		fMinHeightOnSea, fMaxHeightOnShip;
	float		fDistance, fMaxDistance, fMinDistance;
	float		fDistanceDlt, fDistanceInertia;
	float		fMinAngleX, fMaxAngleX;
	float		fAngleXDlt, fAngleXInertia;
	float		fAngleYDlt, fAngleYInertia;
	float		fSensivityDistance, fSensivityAzimuthAngle, fSensivityHeightAngle;
	float		fSensivityHeightAngleOnShip;
	float		fInvertMouseX, fInvertMouseY;
	CVECTOR		vCenter, vAng;
	float		fModelAy;

	//long minHeightOnSea,maxHeightOnSea;



private:
	SEA_BASE	*	pSea;
	ISLAND_BASE *	pIsland;
	long			lIlsInitCnt;
	VDX9RENDER	*	pRS;

	void Move(float fDeltaTime);

	bool Init();
	void SetDevices();
	void Execute(uint32_t dwDeltaTime);
	void Realize(uint32_t dwDeltaTime);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}
	void SetCharacter(ATTRIBUTES *_pACharacter);

	uint32_t AttributeChanged(ATTRIBUTES *);
	void ShipsCollision(CVECTOR & pos);
	bool IslandCollision(CVECTOR & pos);

public:
	SHIP_CAMERA();
	virtual ~SHIP_CAMERA();

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);
};

#endif