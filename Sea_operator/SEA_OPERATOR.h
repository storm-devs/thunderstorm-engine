#ifndef _SEA_OPERATOR_H_
#define _SEA_OPERATOR_H_

#include "../Common_h/dx9render.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/ship_base.h"
#include "TFIFOBuffer.h"

#define ACTION_TIME			 1000
#define TIME_BETWEEN_ACTIONS 1000
#define IDLE_ACTION_SEED	 500

class SEA_OPERATOR;
//--------------------------------------------------------------------
struct tAction
{
	long timePassed;
	float timeK;
	long actionTime;
	CVECTOR destination, direction;
	SHIP_BASE *attackerShip;
	int hitIntoShip;
	void (SEA_OPERATOR::* actionMethod)(tAction *_action);
};

typedef TFIFOBuffer<tAction> TActionBuffer;

enum BORT_TYPE
{
	BORT_FRONT,
	BORT_LEFT,
	BORT_RIGHT,
	BORT_REAR
};

//--------------------------------------------------------------------
class SEA_OPERATOR: public ENTITY
{
public:
	SEA_OPERATOR();
	virtual ~SEA_OPERATOR();

	virtual bool Init();
	virtual uint32_t _cdecl ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);
	virtual uint32_t AttributeChanged(ATTRIBUTES *_newAttr);

protected:
	void ShowAttackerBort(tAction *_action);
	void ShowFromBall(tAction *_action);
	void ShowAroundPoint(tAction *_action);
	void ShowBallAtMyShip(tAction *_action);
	void ShowMyShipFromPoint(tAction *_action);
private:
	void FirstInit();
	bool IsTimeToActivate(bool _testControls = true);
	void SetIfMyShip (ENTITY_ID &_shipID);
	void HandleShipFire (ENTITY_ID &_shipID, char *_bortName, const CVECTOR &_destination, const CVECTOR &_direction);
	void HandleShipHit();
	void HandleShipIdle();
	void StartNewAction();
	void ProcessActions(uint32_t _dTime);

	bool enabled, active;
	SEA_BASE *sea;
	VDX9RENDER *renderer;
	SHIP_BASE *myShip, *enemyShip;
	long actionTime;
	bool ballTracked;
	CVECTOR ballPosition, lastBallPosition, finalBallPosition;

	uint32_t idleTime, sinceLastActionTime;
	TActionBuffer actionBuffer;
	CVECTOR cameraPos, cameraTargetPos;
};

//--------------------------------------------------------------------
#endif