#ifndef _SEAFOAM_H_
#define _SEAFOAM_H_

#include "..\common_h\geos.h"
#include "..\common_h\dx9render.h"
#include "..\common_h\ship_base.h"
#include "..\common_h\model.h"
#include "..\common_h\sea_base.h"
#include "..\SoundService\VSoundService.h"
#include "SeafoamDefines.h"
#include "seafoam_ps.h"
#include "TCarcass.h"

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
struct tFoamEmitter
{
	CVECTOR center[TRACE_STEPS_Y];
	CVECTOR meanPoint;
	float k;
	CVECTOR finalPos;
};

struct tShipFoamInfo
{
	tFoamEmitter hull[2][TRACE_STEPS_Z];
	CVECTOR levelStarts[2][TRACE_STEPS_Z];
	GEOS::INFO hullInfo;
	SHIP_BASE *ship;
	TCarcass *carcass[2];
	SEAFOAM_PS *frontEmitter[3];
	MODEL *shipModel;
	TSD_ID sound;
	bool doSplash;
	bool firstSoundPlay;
	bool enabled;
};
 
class SEAFOAM: public ENTITY
{
public:
	SEAFOAM();
	virtual ~SEAFOAM();

	virtual bool Init();
	uint32_t AttributeChanged(ATTRIBUTES * pA);
	virtual uint32_t _cdecl ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);

private:
	void InitializeShipFoam();
	void ReleaseShipFoam();
	void RealizeShipFoam_Particles(tShipFoamInfo &_shipFoamInfo, uint32_t _dTime);
	void RealizeShipFoam_Mesh(tShipFoamInfo &_shipFoamInfo, uint32_t _dTime);
	void CreateTracePoints(tShipFoamInfo *_shipFoamInfo);
	void InterpolateLeftParticle(tShipFoamInfo &_shipFoamInfo, int z, uint32_t _dTime);
	void InterpolateRightParticle(tShipFoamInfo &_shipFoamInfo, int z, uint32_t _dTime);
	void AddShip(ENTITY_ID * pShipEID);

	VDX9RENDER *renderer;
	ENTITY_ID seaID;
	SEA_BASE *sea;
	tShipFoamInfo shipFoamInfo[MAX_SHIPS]{};
	int shipsCount;
	INIFILE *psIni;
	long carcassTexture;
	bool isStorm;
	VSoundService *soundService;
};

#endif