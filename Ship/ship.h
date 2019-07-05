#ifndef _SHIP_H_
#define _SHIP_H_

#include "../Common_h/ship_base.h"
#include "../Common_h/collide.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/model.h"
#include "../Common_h/Island_Base.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/Character.h"
#include "../Common_h/geometry.h"

#include "FirePlace.h"
#include "../Common_h/ShipLights.h"

#include "../Common_h/Sd2_h/SaveLoad.h"
#include <vector>
#include "../Common_h/dtimer.h"
#include "../Common_h/ship_msg.h"

#define DELTA_TIME(x)			((x) * 0.001f)
#define DELTA_TIME_ROTATE(x)	((x) * 1.0f / 10.0f)

#define MAX_STRENGTH		16
#define STRENGTH_MAIN		0
#define RESERVED_STRENGTH	1

#define MAX_KEEL_POINTS		5

class SHIP : public SHIP_BASE {
protected:
// struct section
struct mast_t
{
	NODE		* pNode;			// node pointer in model
	CVECTOR		vSrc, vDst;			// src and dest vectors
	long		iMastNum;			// mast number
	bool		bBroken;			// if mast is broken then pNode = 0
	float		fDamage;
};

struct ship_point_t
{
	float	fSpeed;
	float	fGravity;			// acceleration
	float	fExpulsiveForce;
	bool	bUnderWater;

	float	fY;
	float	fA;
	float	fV;
	
};

// init parameters
	static std::string	sRealizeLayer, sExecuteLayer;
	char			cShipIniName[256];
	long			iShipPriorityExecute, iShipPriorityRealize;
	float			fGravity;

	float			fRockingY, fRockingAZ;

// entity_id section
	ENTITY_ID		model_id, sphere[36];
	ENTITY_ID		sail_id, rope_id, flag_id, cannon_id,
					vant_id, touch_id, sea_id, blots_id;

	static VDX9RENDER		* pRS;
	static SEA_BASE			* pSea;
	static ISLAND_BASE		* pIsland;
	static COLLIDE			* pCollide;
	static VGEOMETRY		* pGS;

	CMatrix				mRoot;
	CVECTOR				vSpeed, vSpeedsA;
	float				fMinusVolume;
	float				fXOffset, fZOffset;

	bool				bModelUpperShip;
	MODEL				* pModelUpperShip;
	float				fUpperShipAY, fUpperShipY;

// Ships lights 
	IShipLights			* pShipsLights;

// Fire places 
	std::vector<FirePlace>	aFirePlaces;

// Sound section

// temporary used
	bool			bMassaShow;
	long			uniIDX;
	bool			bUse;
	ship_point_t	ShipPoints[16][16];

// executed parameters
	CVECTOR			vSpeedAccel;
	ship_t			SP;
	CVECTOR			vPos, vAng;
	float			fSailState;
	float			fWaterLine;
	bool			bDead, bVisible;
	CVECTOR			vDeadDir, vCurDeadDir;
	CVECTOR			vKeelContour[MAX_KEEL_POINTS];
	long			iNumMasts;
	std::vector<mast_t>	pMasts;
	bool			bShip2Strand;
	bool			bMounted;
	bool			bKeelContour;
	CVECTOR			vOldAng, vOldPos;
	bool			bSetFixed;
	float			fFixedSpeed;

	// fast turn perk parameters
	bool			bPerkTurnActive;
	float			fInitialPerkAngle, fResultPerkAngle;

	STRENGTH		Strength[MAX_STRENGTH];

	DTimer			dtMastTrace, dtUpdateParameters;

// executed functions
	CVECTOR		ShipRocking(float fDeltaTime);
	BOOL		ApplyStrength(float dtime, BOOL bCollision);
	BOOL		CalculateNewSpeedVector(CVECTOR *Speed, CVECTOR *Rotate);
	void		CalculateImmersion();						//
	void		CheckShip2Strand(float fDeltaTime);							
	void		MastFall(mast_t * pM);

	CMatrix		UpdateModelMatrix();
	void		RecalculateWorldOffset();
	
// init section
	void		ScanShipForFirePlaces();
	void		LoadPositionFromAttributes();
	BOOL		LoadShipParameters();
	void		CalcRealBoxsize();

	void		SetDead();
	bool		isDead() { return bDead; };
	bool		isVisible() { return bVisible; };


public:

	virtual ~SHIP();
	SHIP();

	float		GetMaxSpeedZ();
	float		GetMaxSpeedY();
	long		AddStrength(STRENGTH *strength);
	bool		DelStrength(long iIdx);
	
	BOOL		BuildContour(CVECTOR *vContour,long &iNumVContour);
	bool		BuildMasts();

	BOOL		Move(uint32_t DeltaTime, BOOL bCollision);
	BOOL		TouchMove(uint32_t DeltaTime, TOUCH_PARAMS *pTPOld, TOUCH_PARAMS *pTPNew);

	void		LoadServices();

// inherit functions SHIP_BASE
	bool			bSetLightAndFog;
	uint32_t			dwSaveAmbient, dwSaveFogColor;
	D3DLIGHT9		saveLight;

	virtual void	SetLightAndFog(bool bSetLight);
	virtual void	RestoreLightAndFog();
	
	virtual void	SetSpeed(float fSpeed);
	virtual float	GetSpeed();

	virtual void	SetRotate(float fRotSpeed);
	virtual float	GetRotate();

	virtual float	GetBrakingDistance(float * pfTime = nullptr);
	virtual float	GetRotationAngle(float * pfTime = nullptr);

	virtual float 	GetCurrentSpeed();

	virtual void	SetLights();
	virtual void	UnSetLights();
	virtual void	Fire(const CVECTOR & vPos);

	virtual void	SetFixedSpeed(bool bSetFixed, float fFixedSpeed);

// inherit functions COLLISION_OBJECT
	virtual float Trace(const CVECTOR &src, const CVECTOR &dst);
	virtual bool Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly) { return false; };

	virtual const char *GetCollideMaterialName() { return nullptr; };
	virtual bool GetCollideTriangle(TRIANGLE &triangle) { return false; };

// inherit functions CANNON_TRACE_BASE
    float	Cannon_Trace(long iBallOwner, const CVECTOR &src, const CVECTOR &dst);

// inherit functions VAI_OBJBASE
	void		SetACharacter(ATTRIBUTES * pAP);

	CMatrix *	GetMatrix();
	void		SetMatrix(CMatrix & mtx);
	MODEL *		GetModel();
	ENTITY_ID	GetModelEID();
	CVECTOR		GetPos();
	CVECTOR		GetAng();
	CVECTOR		GetBoxsize();

	void		SetPos(CVECTOR & vNewPos);

	bool		Mount(ATTRIBUTES*);

// inherit functions ENTITY
	bool	Init();
	void	Realize(uint32_t Delta_Time);
	void	Execute(uint32_t Delta_Time);
	uint32_t ProcessMessage(MESSAGE & message);
	uint32_t	AttributeChanged(ATTRIBUTES * pAttribute);

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);	
};

#endif