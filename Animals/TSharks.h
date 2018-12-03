#ifndef _TSHARKS_H_
#define _TSHARKS_H_

#include "../Common_h/Matrix.h"
#include "../Common_h/geometry.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/ship_base.h"
#include "AnimalsDefines.h"
#include "TDynamicObject.h"
#include "TDynamicSystem.h"

///////////////////////////////////////////////////////////////////
// DEFINES & TYPES
///////////////////////////////////////////////////////////////////
class TShark: public TDynamicObject
{
public:
	float depth;
	uint32_t time;
};

class TShip : public TDynamicObject
{
public:
	SHIP_BASE *ship;
};

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class TSharks : public TDynamicSystem
{
	friend class TShark;
	friend class TShip;
public:
	TSharks();
	virtual ~TSharks();

	uint32_t ProcessMessage(long _code, MESSAGE & message);
	void Init();
	void Realize(uint32_t _dTime);
	void Execute(uint32_t _dTime);

private:
	void LoadSettings();

	VDX9RENDER *renderService;
	ENTITY_ID  sharkModel;
	TShark *sharks[SHARK_COUNT];
	TShip  *ships[SHARK_MAX_SHIPS];
	long shipsCount;
	long sharksCount;
	TDynamicObject cameraObject;

	float maxDistance;
	
	bool enabled;
	ENTITY_ID seaID;
	SEA_BASE *sea;
};

#endif // !defined
