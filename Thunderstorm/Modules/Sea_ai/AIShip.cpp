#include "AIShip.h"
#include "AIFort.h"
#include "ship_base.h"
#include "inlines.h"

std::vector<AIShip*> AIShip::AIShips;
std::vector<AIShip::can_fire_t>	AIShip::aShipFire;

AIShip::AIShip(AI_OBJTYPE shiptype)
{
	pAShipBase = nullptr;
	
	pMoveController = nullptr;
	pTaskController = nullptr;
	pCannonController = nullptr;
	pCameraController = nullptr;
	pTouchController = nullptr;
	pRotateController = nullptr;
	pSpeedController = nullptr;

	dtFireTime.Setup(FRAND(3.0f), 1.0f, 3.0f);
	dtCheckSituation.Setup(FRAND(2.0f), 1.0f, 2.0f);
	dtUpdateSeaAIAttributes.Setup(0.6f, 0.4f, 0.5f);

	SetObjType(shiptype);
}

AIShip::~AIShip()
{
	DELETE_Entity(eidShip);
	
	STORM_DELETE(pMoveController);
	STORM_DELETE(pTaskController);
	STORM_DELETE(pCannonController);
	STORM_DELETE(pCameraController);
	STORM_DELETE(pTouchController);
	STORM_DELETE(pRotateController);
	STORM_DELETE(pSpeedController);

	aShipFire.clear();
}

void AIShip::Unload()
{
	GetCannonController()->Unload();
}

void AIShip::SetSeaAIAttributes(ATTRIBUTES * pAAttr, VAI_INNEROBJ * pObj)
{
	char str[256];
	uint32_t dwIdx = pAAttr->GetAttributesNum();
	sprintf_s(str,"l%d",dwIdx);
	pAAttr = pAAttr->CreateAttribute(str,"");

	// set common attributes
		pAAttr->SetAttributeUseDword("relation", Helper.GetRelation(GetACharacter(), pObj->GetACharacter()));
		pAAttr->SetAttributeUseDword("idx", GetIndex(pObj->GetACharacter()));
		//pAAttr->SetAttributeUseFloat("x", pObj->GetPos().x);
		//pAAttr->SetAttributeUseFloat("y", pObj->GetPos().y);
		//pAAttr->SetAttributeUseFloat("z", pObj->GetPos().z);
		//pAAttr->SetAttributeUseFloat("ay", pObj->GetAng().y);
		pAAttr->SetAttributeUseFloat("distance", GetDistance(*pObj));

	// calc angle between our ship and other object
		CVECTOR v1 = CVECTOR(sinf(GetAng().y), 0.0f, cosf(GetAng().y));
		CVECTOR v2 = CVECTOR(sinf(pObj->GetAng().y), 0.0f, cosf(pObj->GetAng().y));
		float fDot = v1 | v2; 
		pAAttr->SetAttributeUseFloat("d_ay", fDot);

	// calc relative speed
	if (pObj->GetObjType() != AIOBJ_FORT)
	{
		AIShip * pEnemyShip = ((AIShip*)pObj);

		float fOurCurSpeedZ = GetShipBasePointer()->GetCurrentSpeed();
		float fEnemyCurSpeedZ = pEnemyShip->GetShipBasePointer()->GetCurrentSpeed();

		float fRelativeSpeed = fOurCurSpeedZ - fDot * fEnemyCurSpeedZ;
		pAAttr->SetAttributeUseFloat("RelativeSpeed", fRelativeSpeed);
	}

}

void AIShip::Execute(float fDeltaTime)
{
	uint32_t i;

	ATTRIBUTES * pAAIInit = GetACharacter()->FindAClass(GetACharacter(), "Ship.SeaAI.Init");

	fAbordageDistance = (pAAIInit) ? pAAIInit->GetAttributeAsFloat("AbordageDistance", 30.0f) : 30.0f;
	fFollowDistance = (pAAIInit) ? pAAIInit->GetAttributeAsFloat("FollowDistance", 200.0f) : 200.0f;
	fAttackDistance = (pAAIInit) ? pAAIInit->GetAttributeAsFloat("AttackDistance", 150.0f) : 150.0f;

	if (isMainCharacter())
	{
		if (!pCameraController) 
		{
			pCameraController = new AIShipCameraController(this); Assert(pCameraController);
			pCameraController->Init();
		}
	} else 
	{ 
		if (GetCameraController()) 
			STORM_DELETE(pCameraController); 
	}

	if (GetCameraController()) GetCameraController()->Execute(fDeltaTime);

	if (!isDead())
	{
		GetCannonController()->Execute(fDeltaTime); 
		GetTaskController()->Execute(fDeltaTime); 
		GetMoveController()->Execute(fDeltaTime); 
		if (!isMainCharacter()) GetTouchController()->Execute(fDeltaTime); 
		GetRotateController()->Execute(fDeltaTime);
		GetSpeedController()->Execute(fDeltaTime); 

		if (!isMainCharacter())
		{
			if (dtFireTime.Update(fDeltaTime)) Fire(true);
		}
	}
	SHIP_BASE * pShip = (SHIP_BASE*)GetShipPointer(); Assert(pShip);

	ATTRIBUTES * pASeaAIU = GetACharacter()->FindAClass(GetACharacter(),"SeaAI.Update");
	if (pASeaAIU) GetACharacter()->DeleteAttributeClassX(pASeaAIU);

	if (dtUpdateSeaAIAttributes.Update(fDeltaTime) && !isMainCharacter())
	{
		ATTRIBUTES * pASeaAIU = GetACharacter()->CreateSubAClass(GetACharacter(), "SeaAI.Update");
		ATTRIBUTES * pAShips = pASeaAIU->CreateAttribute("Ships", "");
		for (i=0; i<AIShips.size(); i++) if (this != AIShips[i] && !AIShips[i]->isDead()) 
		{
			SetSeaAIAttributes(pAShips, AIShips[i]);
		}
	}

	if (isMainCharacter())
	{
		uint64_t dw7;
		// delete old state
			
		// create new state
			pASeaAIU = GetACharacter()->CreateSubAClass(GetACharacter(), "SeaAI.Update");

		RDTSC_B(dw7); 
		// fill state for ships
			ATTRIBUTES * pAShips = pASeaAIU->CreateAttribute("Ships", "");

			for (i=0; i<AIShips.size(); i++) if (this != AIShips[i] && !AIShips[i]->isDead()) 
			{
				SetSeaAIAttributes(pAShips, AIShips[i]);
			}

		// fill state for forts
			ATTRIBUTES * pAForts = pASeaAIU->CreateAttribute("Forts", "");

			if (AIFort::pAIFort)
				for (i=0; i<AIFort::pAIFort->GetNumForts(); i++)
				{
					AIFort::AI_FORT * pFort = AIFort::pAIFort->GetFort(i);

					SetSeaAIAttributes(pAForts, pFort);
				}
		// 
			CheckSituation();
			RDTSC_E(dw7); 
			//api->Trace("dw7 = %d", dw7);
	}
	else 
	{
		if (dtCheckSituation.Update(fDeltaTime)) CheckSituation();
	}
}

void AIShip::CheckSituation()
{
	if (isDead()) return;
	//if (isMainCharacter()) return;

	float fMinEnemyDist = 1e9f;
	for (uint32_t i=0; i<AIShips.size(); i++) if (AIShips[i] != this)
	{
		float fDist = GetDistance(*AIShips[i]);
		if (Helper.isEnemy(GetACharacter(), AIShips[i]->GetACharacter()))
		{
			if (fDist < fMinEnemyDist) { fMinEnemyDist = fDist; }
		}
	}

	ATTRIBUTES * pACSituation = GetACharacter()->FindAClass(GetACharacter(), "SeaAI.Update.Situation");
	if (!pACSituation)
	{
		pACSituation = GetACharacter()->CreateSubAClass(GetACharacter(), "SeaAI.Update.Situation");
	}
	Assert(pACSituation);

	pACSituation->SetAttributeUseFloat("MinEnemyDistance", fMinEnemyDist);
	float fPower = GetPower();

	api->Event(SHIP_CHECK_SITUATION, "ai", GetACharacter(), GetShipEID());
}

void AIShip::Realize(float fDeltaTime)
{
	GetCannonController()->Realize(fDeltaTime);
	if (GetCameraController()) GetCameraController()->Realize(fDeltaTime);
	GetMoveController()->Realize(fDeltaTime);
	GetTouchController()->Realize(fDeltaTime);
	GetRotateController()->Realize(fDeltaTime);
	GetSpeedController()->Realize(fDeltaTime);

	// print info about ship
/*   // boal del_cheat
#ifndef _XBOX
	if (api->Controls->GetDebugAsyncKeyState('O')<0)
	{
		
	}
#endif
*/
}

void AIShip::SetACharacter(ATTRIBUTES * pAP) 
{ 
	pACharacter = pAP; 
	GetAIObjShipPointer()->SetACharacter(GetACharacter());
}

void AIShip::CreateShip(entid_t _eidShip, ATTRIBUTES * _pACharacter, ATTRIBUTES * _pAShipBase, CVECTOR * vInitPos)
{
	Assert(_pACharacter && _pAShipBase);
	pAShipBase = _pAShipBase;

	eidShip = _eidShip; Assert(EntityManager::GetEntityPointer(eidShip));
	VAI_OBJBASE * pObj = GetAIObjShipPointer(); Assert(pObj);
	SetACharacter(_pACharacter);
	pObj->SetACharacter(GetACharacter());
	pObj->Mount(pAShipBase);
	SHIP_BASE * pShip = (SHIP_BASE *)pObj;
	if (vInitPos) 
	{
		pObj->SetPos(CVECTOR(vInitPos->x, 0.0f, vInitPos->z));
		//if (!isMainCharacter()) pObj->SetPos(pObj->GetPos() + CVECTOR(FRAND(100.0f), 0.0f, 40.0f + FRAND(100.0f)));
		pShip->State.vAng.y = vInitPos->y;
	}

	pCannonController = new AIShipCannonController(this); GetCannonController()->Init(pAShipBase);
	pTaskController = new AIShipTaskController(this); GetTaskController()->Init();
	pMoveController = new AIShipMoveController(this); GetMoveController()->Init();
	pTouchController = new AIShipTouchController(this); GetTouchController()->Init();
	pRotateController = new AIShipRotateController(this); GetRotateController()->Init();
	pSpeedController = new AIShipSpeedController(this); GetSpeedController()->Init();	
}

bool AIShip::isCanPlace(CVECTOR vNewPos) const
{
	CVECTOR vBoxSize = GetBoxsize();
	vBoxSize.x += 30.0f;
	vBoxSize.z += 30.0f;
	for (uint32_t i=0; i<AIShips.size(); i++) if (this != AIShips[i])
	{
		float fMinDist = (vBoxSize.z + AIShips[i]->GetBoxsize().z) / 2.0f;
		if (AIShips[i]->GetDistance(vNewPos) < fMinDist) return false;
	}
	if (AIHelper::pIsland && AIHelper::pIsland->Check2DBoxDepth(vNewPos, vBoxSize, 0.0f, -14.0f)) return false;
	return true;
}

void AIShip::CheckStartPosition()
{
	CVECTOR vOurPos = GetPos();
	CVECTOR vNewPos = vOurPos;
	CVECTOR vBoxSize = GetBoxsize();
	float fRadius = vBoxSize.z;
	float fAng = 0.0f;
	while (!isCanPlace(vNewPos))
	{
		vNewPos = vOurPos + fRadius * CVECTOR(sinf(fAng), 0.0f, cosf(fAng));
		fAng += PI / 8.0f;
		if (fAng >= PIm2)
		{
			fAng = 0.0f;
			fRadius += vBoxSize.z;
		}
	}
	GetShipBasePointer()->State.vPos = vNewPos;
}

bool AIShip::isCanFire(const CVECTOR & vFirePos) const
{
	CVECTOR v1, v2, vOurPos;
	float	fAng, fCos, fSin, fDist;
	
	vOurPos = GetPos();

	fAng = 8.0f * PI / 180.0f;
	fCos = cosf(fAng), fSin = sinf(fAng);
	fDist = sqrtf(~(vOurPos - vFirePos));

	v1 = v2 = fDist * !(vFirePos - vOurPos);
	RotateAroundY(v1.x, v1.z, fCos, fSin);
	RotateAroundY(v2.x, v2.z, -fCos, -fSin);

	for (uint32_t i=0;i<AIShips.size();i++) if (this != AIShips[i] && isFriend(*AIShips[i]))
	{
		if (AIShips[i]->isDead()) continue;
		if (AIShips[i]->GetTouchController()->isCollision2D(vOurPos, vFirePos)) return false;
		if (AIShips[i]->GetTouchController()->isCollision2D(vOurPos, v1)) return false;
		if (AIShips[i]->GetTouchController()->isCollision2D(vOurPos, v2)) return false;
	}

	return true;
}

bool AIShip::Fire(bool bCameraOutside)
{
	uint32_t i, k, iMax;

	if (isDead()) return false;
	if (isMainCharacter() && !bCameraOutside)
	{
		return GetCameraController()->Fire();
	}
	if (bCameraOutside)
	{
		aShipFire.clear();

		for (i=0; i<AIShips.size(); i++) if (isEnemy(*AIShips[i]))
		{
			bool bCanFire = GetCannonController()->isCanFire(AIShips[i]);
			if (!isCanFire(AIShips[i]->GetPos())) continue;
			if (bCanFire) 
			{
				// check for friendly fire
				//uint32_t dwIdx = aShipFire.Add();
				//aShipFire[dwIdx].pShip = AIShips[i];
				//aShipFire[dwIdx].pFortCannon = null;
				//aShipFire[dwIdx].fDistance = GetDistance(*AIShips[i]);
				aShipFire.push_back(can_fire_t{ AIShips[i], nullptr, GetDistance(*AIShips[i]) });
			}
		}

		// fort cannons check
		if (AIFort::pAIFort)
		{
			for (k=0; k<AIFort::pAIFort->GetNumForts(); k++)
			{
				AIFort::AI_FORT * pFort = AIFort::pAIFort->GetFort(k);
				if (!Helper.isEnemy(pFort->GetACharacter(), GetACharacter())) continue;
				if (!pFort->isNormalMode()) continue;
				iMax = pFort->GetAllCannonsNum(); // boal fix
				for (i=0;i<iMax;i++)
				{
					AICannon * pC = pFort->GetCannon(i);
					if (pC && !pC->isDamaged() && GetCannonController()->isCanFirePos(pC->GetPos()) && isCanFire(pC->GetPos()))
					{
						// check for friendly fire
						//uint32_t dwIdx = aShipFire.Add();
						//aShipFire[dwIdx].pShip = null;
						//aShipFire[dwIdx].pFortCannon = pC;
						//aShipFire[dwIdx].fDistance = GetDistance(pC->GetPos());
						aShipFire.push_back(can_fire_t{ nullptr, pC, GetDistance(pC->GetPos()) });
					}
				}
			}
		}
		if (aShipFire.size())
		{
			// sorting
			//aShipFire.Sort();
			std::sort(aShipFire.begin(), aShipFire.end());

			for (i=0; i<aShipFire.size(); i++) 
			{
				can_fire_t * pFire = &aShipFire[i];
				if (pFire->pShip)		GetCannonController()->Fire(pFire->pShip);
				if (pFire->pFortCannon) GetCannonController()->Fire(pFire->pFortCannon->GetPos());
			}
		}
	}
	return true;
}

void AIShip::ReleasePoint(VAI_INNEROBJ * pOtherObj)
{
	Assert(pOtherObj);

	// delete object in all point array's
	auto it = std::find(aFollowPoints.begin(), aFollowPoints.end(), AI_POINT(pOtherObj));
	if (it != aFollowPoints.end())
		aFollowPoints.erase(it);
	it = std::find(aAttackPoints.begin(), aAttackPoints.end(), AI_POINT(pOtherObj));
	if (it != aAttackPoints.end())
		aAttackPoints.erase(it);

	//aFollowPoints.Del(AI_POINT(pOtherObj));
	//aAttackPoints.Del(AI_POINT(pOtherObj));
}

CVECTOR	AIShip::GetAbordagePoint(VAI_INNEROBJ * pOtherObj)  
{
	CVECTOR vDir = !(pOtherObj->GetPos() - GetPos());
	CVECTOR vAdd = fAbordageDistance * vDir;

	return vAdd;
}

CVECTOR	AIShip::GetFollowPoint(VAI_INNEROBJ * pOtherObj)  
{
	CVECTOR vDir = !(pOtherObj->GetPos() - GetPos());
	//float fAng = GetAng().y;
	CVECTOR vAdd = fFollowDistance * vDir;//CVECTOR(0.0f, 0.0f, 200.0f);
	//RotateAroundY(vAdd.x,vAdd.z,cosf(fAng),sinf(fAng));

	return vAdd;
	/*uint32_t dwIdx = aFollowPoints.Find(AI_POINT(pOtherObj));
	if (dwIdx == INVALID_ARRAY_INDEX)
	{
		dwIdx = aFollowPoints.Add(); Assert(dwIdx != INVALID_ARRAY_INDEX);
		aFollowPoints[dwIdx].pObj = pOtherObj;
	}
	float fAng = GetAng().y;
	CVECTOR vAdd = CVECTOR(0.0f, 0.0f, 100.0f);
	RotateAroundY(vAdd.x,vAdd.z,cosf(fAng),sinf(fAng));

	aFollowPoints[dwIdx].fAngle = 0.0f;

	return vAdd;*/
}

CVECTOR	AIShip::GetAttackPoint(VAI_INNEROBJ * pOtherObj) 
{
	CVECTOR vSrc = pOtherObj->GetPos();
	vSrc.y = 0.0f;

	CVECTOR	vBestPos = GetPos();
	float	fBestDist = 1e16f;
	for (uint32_t i=0; i<16; i++)
	{
		float fAngle = FRAND(0.1f) + PIm2 * float(i) / 15.0f;
		CVECTOR vRay = CVECTOR(0.0f , 0.0f, fAttackDistance);
		RotateAroundY(vRay.x, vRay.z, cosf(fAngle), sinf(fAngle));

		//float fAng = GetAng().y;
		//RotateAroundY(vDst.x, vDst.z, cosf(fAng), sinf(fAng));

		CVECTOR vDst = GetPos() + vRay; vDst.y = 0.0f;
		float fDist = ~(vSrc - vDst);

		float fDepth = -20.0f;
		if (AIHelper::pIsland) AIHelper::pIsland->GetDepth(vDst.x, vDst.z, &fDepth);

		if (fDist < fBestDist && fDepth < -4.0f)
		{
			vBestPos = vRay;
			fBestDist = fDist;
		}
	}

	/*float fTempAng = PId2 / 2.0f;
	if (aAttackPoints.size()) fTempAng = aAttackPoints[aAttackPoints.Last()].fAngle + PId2 / 2.0f;

	uint32_t dwIdx = aAttackPoints.Find(AI_POINT(pOtherObj));
	if (dwIdx == INVALID_ARRAY_INDEX)
	{
		dwIdx = aAttackPoints.Add(); Assert(dwIdx != INVALID_ARRAY_INDEX);
		aAttackPoints[dwIdx].pObj = pOtherObj;
		aAttackPoints[dwIdx].fAngle = fTempAng;
	}

	CVECTOR vAdd = CVECTOR(0.0f , 0.0f, 150.0f);	
	RotateAroundY(vAdd.x,vAdd.z,cosf(aAttackPoints[dwIdx].fAngle),sinf(aAttackPoints[dwIdx].fAngle));

	float fAng = GetAng().y;
	RotateAroundY(vAdd.x,vAdd.z,cosf(fAng),sinf(fAng));
	*/

	return vBestPos;
}

void AIShip::GetPrediction(float fTime, CVECTOR * vPos, CVECTOR * vAng)
{
	if (vPos)
	{
		float fSpeed = GetShipBasePointer()->GetCurrentSpeed();
		CVECTOR vDir = CVECTOR(sinf(GetAng().y), 0.0f, cosf(GetAng().y));

		*vPos = GetPos() + fTime * fSpeed * vDir;
	}
}

float AIShip::GetShipHP()
{
	ATTRIBUTES * pAHP = GetACharacter()->FindAClass(GetACharacter(), "Ship.HP"); Assert(pAHP);
	return pAHP->GetAttributeAsFloat();
}

float AIShip::GetShipBaseHP()
{
	return GetAShip()->GetAttributeAsFloat("HP");
}

bool AIShip::isAttack(ATTRIBUTES * pAOtherCharacter)
{
	if (isDead()) return false;
	return GetTaskController()->isAttack(pAOtherCharacter);
}

float AIShip::GetDefendHP()
{
	return 0.0f;
}

float AIShip::GetAttackHP(float fAttackDistance)
{
	float fHP = 0.0f;
	for (uint32_t i=0; i<AIShips.size(); i++) if (AIShips[i] != this)
	{
		float fHP1 = 0.0f;
		if (fAttackDistance <= 0.0f && AIShips[i]->isAttack(GetACharacter())) fHP1 = AIShips[i]->GetShipHP();
		if (isEnemy(*AIShips[i]) && AIShips[i]->GetDistance(*AIShips[i]) <= fAttackDistance) fHP1 = AIShips[i]->GetShipHP();
		fHP += fHP1;
	}
	return fHP;
}

float AIShip::GetPower() 
{ 
	Assert(GetAShip());
	if (isDead()) return 0.0f;
	float fHP = GetAShip()->GetAttributeAsFloat("HP");
	uint32_t dwCannonsNum = GetCannonController()->GetCannonsNum();
	return fHP + dwCannonsNum * 100.0f; 
};

void AIShip::SwapShips(AIShip * pOtherShip)
{
	ATTRIBUTES * pAThisCharacter = GetACharacter();
	SetACharacter(pOtherShip->GetACharacter());
	pOtherShip->SetACharacter(pAThisCharacter);

	bool bThisDead = isDead();
	SetDead(pOtherShip->isDead());
	pOtherShip->SetDead(bThisDead);

	Swap(pMoveController, pOtherShip->pMoveController);
	Swap(pRotateController, pOtherShip->pRotateController);
	Swap(pSpeedController, pOtherShip->pSpeedController);
	Swap(pTaskController, pOtherShip->pTaskController);

	pCannonController->SetAIShip(this);
	if (pCameraController) pCameraController->SetAIShip(this);
	pMoveController->SetAIShip(this);
	pRotateController->SetAIShip(this);
	pSpeedController->SetAIShip(this);
	pTaskController->SetAIShip(this);
	pTouchController->SetAIShip(this);

	pOtherShip->pCannonController->SetAIShip(pOtherShip);
	if (pOtherShip->pCameraController) pOtherShip->pCameraController->SetAIShip(pOtherShip);
	pOtherShip->pMoveController->SetAIShip(pOtherShip);
	pOtherShip->pRotateController->SetAIShip(pOtherShip);
	pOtherShip->pSpeedController->SetAIShip(pOtherShip);
	pOtherShip->pTaskController->SetAIShip(pOtherShip);
	pOtherShip->pTouchController->SetAIShip(pOtherShip);

	//GetAIObjShipPointer()->SetACharacter(GetACharacter());
	//pOtherShip->GetAIObjShipPointer()->SetACharacter(pOtherShip->GetACharacter());
}

// static members
AIShip * AIShip::FindShip(ATTRIBUTES * pACharacter) 
{
	for (uint32_t i=0; i<AIShip::AIShips.size(); i++) if (*AIShip::AIShips[i] == pACharacter) return AIShip::AIShips[i];
	return nullptr;
}

void AIShip::ReloadCannons(ATTRIBUTES * pACharacter)
{
	FindShip(pACharacter)->GetCannonController()->Reload();
}

bool AIShip::ShipFire(ATTRIBUTES * pACharacter, bool bCameraOutside)
{
	return FindShip(pACharacter)->Fire(bCameraOutside);
}

void AIShip::ShipSetAttack(uint32_t dwPriority, ATTRIBUTES * pACharacter1, ATTRIBUTES * pACharacter2)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_ATTACK, pACharacter2);
}

void AIShip::ShipSetRunAway(uint32_t dwPriority, ATTRIBUTES * pACharacter1)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_RUNAWAY, nullptr);
}

void AIShip::ShipSetMove(uint32_t dwPriority, ATTRIBUTES * pACharacter1, ATTRIBUTES * pACharacter2)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_MOVE, pACharacter2);
}

void AIShip::ShipSetMove(uint32_t dwPriority, ATTRIBUTES * pACharacter1, CVECTOR & vPnt)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_MOVE, vPnt);
}

void AIShip::ShipSetDrift(uint32_t dwPriority, ATTRIBUTES * pACharacter1)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_DRIFT, nullptr);
}

void AIShip::ShipSetDefend(uint32_t dwPriority, ATTRIBUTES * pACharacter1, ATTRIBUTES * pACharacter2)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_DEFEND, pACharacter2);
}

void AIShip::ShipSetBrander(uint32_t dwPriority, ATTRIBUTES * pACharacter1, ATTRIBUTES * pACharacter2)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_BRANDER, pACharacter2);
}

void AIShip::ShipSetAbordage(uint32_t dwPriority, ATTRIBUTES * pACharacter1, ATTRIBUTES * pACharacter2)
{
	AIShip * pShip = FindShip(pACharacter1);
	if (pShip) pShip->GetTaskController()->SetNewTask(dwPriority, AITASK_ABORDAGE, pACharacter2);
}

void AIShip::Save(CSaveLoad * pSL)
{
	GetShipBasePointer()->Save(pSL);
	
	pSL->SaveAPointer("character", GetACharacter());
	pSL->SaveDword(ObjType);
	pSL->SaveDword(bDead);

	pCannonController->Save(pSL);
	pSL->SaveQword((uintptr_t)pCameraController);
	if (pCameraController) pCameraController->Save(pSL);
	pMoveController->Save(pSL);
	pRotateController->Save(pSL);
	pSpeedController->Save(pSL);
	pTaskController->Save(pSL);
	pTouchController->Save(pSL);
}

void AIShip::Load(CSaveLoad * pSL)
{
	// create ship
	eidShip = EntityManager::CreateEntity("Ship");
	GetShipBasePointer()->Load(pSL);
	
	SetACharacter(pSL->LoadAPointer("character"));
	ObjType = (AI_OBJTYPE)pSL->LoadDword();
	bDead = pSL->LoadDword() != 0;

	// set entid_t to character 
	VDATA * pVCharacter = (VDATA *)api->GetScriptVariable("Characters");
	pVCharacter->Set(eidShip, GetIndex(GetACharacter()));

	// create controllers
	pCannonController = new AIShipCannonController(this); 
	pTaskController = new AIShipTaskController(this); 
	pMoveController = new AIShipMoveController(this); 
	pTouchController = new AIShipTouchController(this); 
	pRotateController = new AIShipRotateController(this); 
	pSpeedController = new AIShipSpeedController(this); 

	api->Event(SHIP_CREATELOADSHIP, "l", GetIndex(GetACharacter()));

	// Load controllers
	pCannonController->Load(pSL);
	bool bCameraController = pSL->LoadQword() != 0;
	if (bCameraController) 
	{
		pCameraController = new AIShipCameraController(this); 
		pCameraController->Load(pSL);
	}
	pMoveController->Load(pSL);
	pRotateController->Load(pSL);
	pSpeedController->Load(pSL);
	pTaskController->Load(pSL);
	pTouchController->Load(pSL);
}