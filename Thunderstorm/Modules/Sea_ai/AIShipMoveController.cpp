#include "AIShip.h"

AIShipMoveController::AIShipMoveController(AIShip* pShip)
{
	//EntityManager::CreateEntity(&eidSphere,"modelr");
	//api->Send_Message(eidSphere,"ls",MSG_MODEL_LOAD_GEO,"mirror");
	//EntityManager::AddToLayer("sea_realize",eidSphere,10000);
	fMoveTime = FRAND(2.0f);
	dwCurPnt = 0;
	vDeflectForce = 0.0f;
	vRetardForce = 0.0f;
	SetAIShip(pShip);
	Stop(true);
}

AIShipMoveController::~AIShipMoveController()
{
}

bool AIShipMoveController::Init()
{
	return true;
}

void AIShipMoveController::Execute(float fDeltaTime)
{
	//return;
	//entid_t	eid;
	//api->FindClass(&eid,"sea",0);
	//SEA_BASE * pSea = (SEA_BASE*)EntityManager::GetEntityPointer(eid);
	//MODEL* pModel = (MODEL*)EntityManager::GetEntityPointer(eidSphere);
	//pModel->mtx.BuildPosition(100.0f,pSea->WaveXZ(100.0f,200.0f),200.0f);
	//pModel->mtx.m[3][3] = 1.0f / 0.1f;

	fMoveTime -= fDeltaTime;

	if (isStopped() || GetAIShip()->isMainCharacter()) return;
	auto* pShip = (SHIP_BASE*)GetAIShip()->GetShipPointer();
	Assert(pShip);

  auto vCurPos = GetAIShip()->GetPos();
  auto vCurAng = GetAIShip()->GetAng();

  auto vMovePoint = vDestPoint;

	vDeflectForce.z = 1.0f; //FRAND(2.0f) - 1.0f;
	//vDeflectForce.z = FRAND(2.0f) - 1.0f;

  auto vCurDir = CVECTOR(sinf(vCurAng.y), 0.0f, cosf(vCurAng.y));
  auto vDestDir = !(vMovePoint - vCurPos);

  auto fTime = 0.0f;
  auto fDist = sqrtf(~(vCurPos - vMovePoint));
  auto fBrakingDistance = pShip->GetBrakingDistance(&fTime);

  auto fSpeed = 1.0f;
	if (fBrakingDistance > fDist + 20.0f)
	{
		fSpeed = 1.0f - (fBrakingDistance - (fDist + 20.0f)) / 20.0f;
		if (fSpeed < 0.0f) fSpeed = 0.0f;
	}
	if (fabsf(fBrakingDistance - fDist) < 10.0f) fSpeed = 0.0f;
	GetAIShip()->GetSpeedController()->AddSpeed(fSpeed);
	//pShip->SetSpeed(fSpeed);

  auto fRotationAngle = pShip->GetRotationAngle(&fTime);

  auto fTemp = ~vDeflectForce;
	if (~vDeflectForce > 0.00001f)
	{
    auto vRotDir = !vDeflectForce;

    auto fDot = vCurDir | vDestDir;
    auto fRotAng = fabsf(acosf(Clamp(fDot)));

    auto vProd = vCurDir ^ vDestDir;
    auto fSignRot = ((vProd.y > 0.0f) ? 1.0f : -1.0f);
		// check fSignRot with can Rotate in these direction
		//float fBestRotate = GetAIShip()->GetTouchController()->GetBestRotateDirection();
		//if (fBestRotate != 0.0f) fSignRot = fBestRotate;
    auto fMul = (fDot > 0.0f) ? Bring2Range(1.0f, 0.1f, 0.0f, 1.0f, fDot) : 1.0f;
    auto fAngRot = fSignRot;
		if (fRotationAngle >= fRotAng) fAngRot = 0.0f;
		GetAIShip()->GetRotateController()->AddRotate(fMul * fAngRot);
		if (fMul > 0.3f) GetAIShip()->GetSpeedController()->MulSpeed(0.5f);
		//pShip->SetRotate(fAngRot);
	}

	//vDeflectForce = 0.0f;
	vRetardForce = 0.0f;
}

void AIShipMoveController::Realize(float fDeltaTime)
{
	/* espkk. code was unreachable (return)
	RS_LINE line[2];	
	line[0].dwColor = 0xFFFFFF;
	line[0].vPos = GetAIShip()->GetPos() + 50.0f * (!vDeflectForce);
	line[1].dwColor = 0xFFFFFF;
	line[1].vPos = GetAIShip()->GetPos();
	AIHelper::pRS->DrawLines(&line[0],1,"Line");
	vDeflectForce = 0.0f;

	if (!GetAIShip()->isMainCharacter())
	{
		std::vector<RS_LINE>	aLines(_FL_);
		{
			RS_LINE * pRL = &aLines[aLines.Add()];
			pRL->dwColor = 0xFFFFFF;
			pRL->vPos = GetAIShip()->GetPos();
			pRL = &aLines[aLines.Add()];
			pRL->dwColor = 0xFFFFFF;
			pRL->vPos = vDestPoint;
		}
		CMatrix m;
		AIHelper::pRS->SetTransform(D3DTS_WORLD, m);
		if (aLines.size() >= 2) AIHelper::pRS->DrawLines(&aLines[0], aLines.size()/2, "Line");
	}
	*/
}

void AIShipMoveController::Move(CVECTOR vMovePoint)
{
  auto fDist = sqrtf(~(vMovePoint - vDestPoint));
	if (fMoveTime > 0.0f) return;
	fMoveTime = 2.0f;
	//if (fDist < 100.0f) return;

	if (AIHelper::pIsland)
	{
		CVECTOR vRealMovePoint;
    auto vOurPos = GetAIShip()->GetPos();
		vOurPos.y = vMovePoint.y = 0.0f;
    auto b = AIHelper::pIsland->GetMovePoint(vOurPos, vMovePoint, vRealMovePoint);
		if (b)
		{
			vMovePoint = vRealMovePoint;
		}
	}
	Stop(false);
	vDestPoint = vMovePoint;
}

void AIShipMoveController::AddRetardForce(CVECTOR _vRetardForce) { vRetardForce += _vRetardForce; }
void AIShipMoveController::AddDeflectForce(CVECTOR _vDeflectForce) { vDeflectForce += _vDeflectForce; }

void AIShipMoveController::Save(CSaveLoad* pSL)
{
	pSL->SaveDword(bStopped);
	pSL->SaveVector(vDestPoint);
	pSL->SaveVector(vRetardForce);
	pSL->SaveVector(vDeflectForce);
	pSL->SaveFloat(fMoveTime);
	pSL->SaveDword(dwCurPnt);
}

void AIShipMoveController::Load(CSaveLoad* pSL)
{
	bStopped = pSL->LoadDword() != 0;
	vDestPoint = pSL->LoadVector();
	vRetardForce = pSL->LoadVector();
	vDeflectForce = pSL->LoadVector();
	fMoveTime = pSL->LoadFloat();
	dwCurPnt = pSL->LoadDword();
}
