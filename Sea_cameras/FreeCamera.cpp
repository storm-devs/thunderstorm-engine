#include "FreeCamera.h"
#include "../Common_h/collide.h"
#include "../Model/modelr.h"
#include "../Common_h/defines.h"
#include "../Common_h/Sd2_h/SaveLoad.h"

#define SENSITIVITY		0.0015f
#define FOV				1.285f

entid_t	sphere;
COLLIDE		*pCollide;

FREE_CAMERA::FREE_CAMERA()
{
	SetOn(false);
	SetActive(false);

	pIslandBase = nullptr;
	pRS = nullptr;
	ZERO2(vPos,vAng);
	vPos.z = 250.0f;
	vPos.y = 3.0f;
	fFov = FOV;

	iLockX = 0;
	iLockY = 0;

	fCameraOnEarthHeight = 3.0f;
	bCameraOnEarth = false;
}

FREE_CAMERA::~FREE_CAMERA()
{
}

bool FREE_CAMERA::Init()
{
	//GUARD(FREE_CAMERA::FREE_CAMERA())
	api->LayerCreate("realize",true,false);
	api->LayerAdd("system_messages",GetId(),1);
	SetDevice();
	//UNGUARD
	return true;
}

void FREE_CAMERA::SetDevice()
{
	pRS = (VDX9RENDER *)api->CreateService("dx9render");
	Assert(pRS);
	pCollide		= (COLLIDE*)api->CreateService("COLL");
	Assert(pCollide);

	/*api->CreateEntity(&sphere,"modelr");
	api->Send_Message(sphere,"ls",MSG_MODEL_LOAD_GEO,"mirror");
	api->LayerAdd("realize",sphere,10000);*/
}

bool FREE_CAMERA::CreateState(Entity_STATE_GEN * state_gen)
{
	state_gen->SetState("vv",sizeof(vPos),vPos,sizeof(vAng),vAng);
	return true;
}

bool FREE_CAMERA::LoadState(Entity_STATE * state)
{
	SetDevice();
	state->Struct(sizeof(vPos),(char *)&vPos);
	state->Struct(sizeof(vAng),(char *)&vAng);
	return true;
}

void FREE_CAMERA::Execute(uint32_t Delta_Time)
{
	if (!isOn()) return;

	SetPerspective(AttributesPointer->GetAttributeAsFloat("Perspective"));

	entid_t ent;
	if (!pIslandBase && api->FindClass(&ent,"island",0))
		pIslandBase = (ISLAND_BASE*)api->GetEntityPointer(ent);

	Move(api->GetDeltaTime());
}

void FREE_CAMERA::Move(uint32_t DeltaTime)
{
	if (!isActive()) return;
	if(LOWORD(GetKeyState(VK_NUMLOCK)) != 0) return;

	//POINT pnt;
	//GetCursorPos(&pnt);
	//if(pnt.x != iLockX || pnt.y != iLockY)
	CONTROL_STATE cs;

	{
		api->Controls->GetControlState("FreeCamera_Turn_H",cs);
		vAng.y += SENSITIVITY*(float)(cs.fValue);
		api->Controls->GetControlState("FreeCamera_Turn_V",cs);
		vAng.x += SENSITIVITY*(float)(cs.fValue);
		//SetCursorPos(iLockX,iLockY);
	}
	if (bCameraOnEarth && pIslandBase) 
	{
		pIslandBase->GetDepth(vPos.x,vPos.z,&vPos.y);
		vPos.y += fCameraOnEarthHeight;
	}
	float c0 = cosf(vAng.y);	float s0 = sinf(vAng.y);
	float c1 = cosf(vAng.x);	float s1 = sinf(vAng.x);
	float c2 = cosf(vAng.z);	float s2 = sinf(vAng.z);
	float speed = 5.0f * 0.001f * float(DeltaTime);
#ifndef _XBOX
	if (GetAsyncKeyState(VK_SHIFT))		speed *= 4.0f;
	if (GetAsyncKeyState(VK_CONTROL))	speed *= 8.0f;
#endif
	api->Controls->GetControlState("FreeCamera_Forward",cs);
	if(cs.state == CST_ACTIVE) vPos += speed*CVECTOR(s0*c1, -s1, c0*c1);
	api->Controls->GetControlState("FreeCamera_Backward",cs);
	if(cs.state == CST_ACTIVE) vPos -= speed*CVECTOR(s0*c1, -s1, c0*c1);

	/*if (GetAsyncKeyState(VK_LBUTTON))	vPos += speed*CVECTOR(s0*c1, -s1, c0*c1);
	if (GetAsyncKeyState(VK_RBUTTON))	vPos -= speed*CVECTOR(s0*c1, -s1, c0*c1);
	if(GetAsyncKeyState('I'))	vPos += speed*CVECTOR(0.0f, 0.1f , 0.0f);
	if(GetAsyncKeyState('K'))	vPos += speed*CVECTOR(0.0f, -0.1f, 0.0f);*/
	
	//vPos = CVECTOR(0.0f, 20.0f, 0.0f);

	pRS->SetCamera(&vPos,&vAng,GetPerspective());

	return; //~!~

	CVECTOR vRes;
	CVECTOR vDst = vPos + 2000.0f*CVECTOR(s0*c1, -s1, c0*c1);

	walker_tpVW = api->LayerGetWalker("sun_trace");
	float fRes = pCollide->Trace(*pVW,vPos,vDst,nullptr,0);
	if (fRes > 1.0f) vRes = vDst;
	else 
	{
		vRes = vPos + fRes * (vDst - vPos);
		entid_t ent = pCollide->GetObjectID();
		MODELR *pEntity = (MODELR*)api->GetEntityPointer(ent);
	}


	MODEL* pModel = (MODEL*)api->GetEntityPointer(sphere);
	pModel->mtx.BuildPosition(vRes.x,vRes.y,vRes.z);
	delete pVW;
}

void FREE_CAMERA::Save(CSaveLoad * pSL)
{
	pSL->SaveVector(vPos);
	pSL->SaveVector(vAng);
	pSL->SaveFloat(fFov);
	pSL->SaveLong(iLockX);
	pSL->SaveLong(iLockY);

	pSL->SaveDword(bCameraOnEarth);
	pSL->SaveFloat(fCameraOnEarthHeight);
}

void FREE_CAMERA::Load(CSaveLoad * pSL)
{
	vPos = pSL->LoadVector();
	vAng = pSL->LoadVector();
	fFov = pSL->LoadFloat();
	iLockX = pSL->LoadLong();
	iLockY = pSL->LoadLong();

	bCameraOnEarth = pSL->LoadDword() != 0;
	fCameraOnEarthHeight = pSL->LoadFloat();
}
