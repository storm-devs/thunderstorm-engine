#ifndef _TFISHSCHOOLS_H_
#define _TFISHSCHOOLS_H_

#include "..\common_h\matrix.h"
#include "..\common_h\geometry.h"
#include "..\common_h\dx9render.h"
#include "..\common_h\sea_base.h"
#include "..\common_h\ship_base.h"
#include "AnimalsDefines.h"
#include "TDynamicObject.h"
#include "TDynamicSystem.h"

///////////////////////////////////////////////////////////////////
// DEFINES & TYPES
///////////////////////////////////////////////////////////////////
class TFishSchool: public TDynamicObject
{
public:
	float depth;
	uint32_t time;
	float timeDivider;
	float amplitude;
};

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class TFishSchools : public TDynamicSystem
{
	friend class TFishSchool;
public:
	TFishSchools();
	virtual ~TFishSchools();

	uint32_t ProcessMessage(long _code, MESSAGE & message);
	void Init();
	void Realize(uint32_t _dTime);
	void Execute(uint32_t _dTime);

private:
	void LoadSettings();

	VDX9RENDER *renderService;
	ENTITY_ID  fishSchoolModel;
	TFishSchool *fishSchools[FISHSCHOOL_COUNT];
	long shipsCount;
	long fishSchoolsCount;
	TDynamicObject cameraObject;

	float maxDistance;
	
	bool enabled;
	ENTITY_ID seaID;
	SEA_BASE *sea;
};

#endif // !defined
