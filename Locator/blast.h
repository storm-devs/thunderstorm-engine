#ifndef _BLAST_H_
#define _BLAST_H_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/geometry.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/Matrix.h"
#include "blast.h"
#include "../Common_h/Sd2_h/CannonTrace.h"

typedef struct
{
	CVECTOR pos;
	CVECTOR ang;
	CVECTOR ang_speed;
	CVECTOR dir;
	GEOS *  geo;
	float speed;
	bool bDouble;
	bool bEffect;
} GEOPARTICLE;

class BLAST : public Entity 
{
	VDX9RENDER * rs;
	VGEOMETRY * gs;
	std::vector<GEOPARTICLE> Item;
	CANNON_TRACE_BASE * pSea;
	entid_t sea_eid;
	float AngleDeviation;
	uint32_t ItemsNum;
	CMatrix Center;
	entid_t Splash;
public:
	~BLAST();
	 BLAST();
	bool Init();
	uint32_t ProcessMessage(MESSAGE & message);
	uint32_t AttributeChanged(ATTRIBUTES *);
	void Realize(uint32_t Delta_Time);
	void ProcessTime(uint32_t Delta_Time);
	void SetBlastCenter(CVECTOR pos, CVECTOR ang);
	void AddGeometry(char * name, long num);
};
#endif