
#ifndef _Sailors_h_
#define _Sailors_h_

#include "vmodule_api.h"
#include "dx9render.h"
#include "collide.h"
#include "model.h"
#include "ship_base.h"

#include "sea_base.h"


const float RUN_SPEED=  0.30f;
const float MOVE_SPEED= 0.15f;
const float CLIMB_SPEED= 0.065f;

const float JUMP_SPEED_X_MASTFALL= 3.0f;
const float JUMP_SPEED_Y_EXPLOSION= 30.0f;

#include "SailorsWayPoints.h"
#include "../../Shared/SEA_AI/seaPeople.h"

#define CREW2VISIBLE(n)			5.0f*logf(n) //???
#define SHIP_BLACK_PEARL		164


enum ManMode{MAN_JUMP, MAN_SWIM, MAN_OFF ,MAN_WALK, MAN_RUN, MAN_STAY, MAN_CANNONRELOAD, MAN_TURNLEFT, MAN_TURNRIGHT, MAN_CLIMB_UP,  MAN_CLIMB_DOWN};
enum ManMoveTo{ MOVE_TO_POINT, MOVE_TO_CANNON, MOVE_TO_TOP};



struct ShipState{

	uint32_t mode;
	bool dead;
	SEA_BASE * sea;

	ShipState(){
		mode= SHIP_SAIL;	
		dead= false;
	};
};


class ShipMan
{
public:
	entid_t modelID;
	MODEL * model;

	CVECTOR pos, ang; //������� ���������
	CVECTOR ptTo, angTo, dir; 

	CVECTOR spos; //����� ���� �����
//	float sang;   //����� ���� �����

	float dieTime;
	bool  inWater;
	float jumpSpeedX, jumpSpeedY;

	Path path; //������� ����

	ManMode mode, lastMode; //�����
	int newWayPoint,lastWayPoint,targetWayPoint,lastTargetPoint;

	ManMoveTo moveTo; //��� ������� �����

	float manSpeed;
	float rotSpeed;

	ShipMan();

	void SetPos(MODEL *ship, SHIP_BASE *ship_base, uint32_t &dltTime, ShipState &shipState);
	void FindNextPoint(SailorsPoints &sailorsPoints, ShipState &shipState);
	int  FindRandomPoint(SailorsPoints &sailorsPoints, ShipState &shipState);
	int  FindRandomPointWithoutType(SailorsPoints &sailorsPoints);
	void ApplyTargetPoint(CVECTOR pt, bool randomWalk);

	void UpdatePos(uint32_t &dltTime, SailorsPoints &sailorsPoints, ShipState &shipState);

	void SetAnimation(uint32_t dltTime, ShipState &shipState);


	bool MoveToPosition(uint32_t &dltTime, SailorsPoints &sailorsPoints, ShipState &shipState);
	bool RotateToAngle(uint32_t &dltTime, SailorsPoints &sailorsPoints);
	bool Stay(uint32_t &dltTime, SailorsPoints &sailorsPoints);
	bool Turn(uint32_t &dltTime, SailorsPoints &sailorsPoints);
	bool Swim(uint32_t &dltTime, SailorsPoints &sailorsPoints, ShipState &shipState);
	bool Jump(uint32_t &dltTime, SailorsPoints &sailorsPoints, ShipState &shipState);

	void NewAction(SailorsPoints &sailorsPoints, ShipState &shipState, uint32_t &dltTime);
	void Free();
	int  GetNearestEmptyCannon(SailorsPoints &sailorsPoints);
};

class ShipWalk
{
public:
	//ShipWalk() shipMan(_FL_) {}

	SHIP_BASE *ship;
	MODEL *shipModel;
	int crewCount; //���������� �������

	bool bHide;

	entid_t shipID;

	SailorsPoints sailorsPoints; //�����

	void ReloadCannons(int bort);
	ShipState shipState; //��������� �������

	std::vector<ShipMan> shipMan;
	void CreateNewMan(SailorsPoints &sailorsPoints);
	void DeleteMan(int Index);

	void Init(entid_t _shipID, int editorMode, char *shipType);
	void CheckPosition(uint32_t &dltTime);
	void SetMastBroken(int iMastIndex);
	void OnHullHit(CVECTOR &v);
	void Reset();

	void Free();
};


class Sailors : public Entity
{
public:

	VDX9RENDER *rs;

	std::vector<ShipWalk> shipWalk;
	bool editorMode;
	int shipsCount;
	bool disabled;

	Sailors();
	virtual ~Sailors();

	virtual bool Init();
	virtual void Realize(uint32_t dltTime);

	virtual uint64_t ProcessMessage(MESSAGE &message);
	virtual uint32_t AttributeChanged(ATTRIBUTES *_newAttr);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::execute:
		//	Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}
	int IsOnDeck;

	void DeleteShip(int i);
};

#endif