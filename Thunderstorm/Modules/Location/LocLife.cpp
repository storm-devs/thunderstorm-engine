//============================================================================================
//	Spirenkov Maxim, 2003
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	LocLife
//--------------------------------------------------------------------------------------------
//	
//============================================================================================
			


#include "geometry.h"
#include "LocLife.h"
#include "Location.h"
#include "Character.h"
#include "../../Shared/messages.h"
#include "EntityManager.h"

//============================================================================================

LocLife::LocLife()
{
	location = nullptr;
	node = -1;
	kSpeed = 1.0f;
	speed = 0.6f;
}

LocLife::~LocLife()
{
	EntityManager::EraseEntity(model);
}


//============================================================================================


bool LocLife::Init(Location * loc)
{
	Assert(loc);
	if(!(model = EntityManager::CreateEntity("modelr"))) return false;
	EntityManager::AddToLayer(REALIZE, model, 20);
	//���� ��� �������
	VGEOMETRY * gs = (VGEOMETRY *)api->CreateService("geometry");
	if(!gs)
	{
		api->Trace("Can't create geometry service!");
		return false;
	}
	gs->SetTexturePath("Animals\\");
	if(!api->Send_Message(model, "ls", MSG_MODEL_LOAD_GEO, GetModelName()))
	{
		gs->SetTexturePath("");
		return false;
	}
	gs->SetTexturePath("");
	//��������
	if(!api->Send_Message(model, "ls", MSG_MODEL_LOAD_ANI, GetAniName())) return false;
	//��������� ����� ���������
	location = loc;
	if(FindRandomPos(pos) < 0){ location = nullptr; return false; }
	FindPos();
	ay = rand()*(6.28f/RAND_MAX);
	//��������
	MODEL * m = (MODEL *)EntityManager::GetEntityPointer(model);
	if(!m){ location = nullptr; return false; }
	NODE * node = m->GetNode(0);
	if(node) node->SetTechnique("DLightModel");
	Animation * ani = m->GetAnimation();
	if(!ani){ location = nullptr; return false; }
	if(!PostInit(ani)){ location = nullptr; return false; }
	return true;
}

void LocLife::Update(float dltTime)
{
	if(!location) return;
	if(location->IsExDebugView())
	{
		location->DrawLine(pos, 0xff00ffff, pos + CVECTOR(0.0f, 1.0f, 0.0f), 0xff00ffff);
		location->DrawLine(pos, 0xff00ff00, pos + CVECTOR(sinf(ay), 0.0f, cosf(ay))*0.5f, 0xff00ff00);
	}
	//���������� � ������ � �������
	MODEL * m = (MODEL *)EntityManager::GetEntityPointer(model);
	if(!m) return;
	Animation * ani = m->GetAnimation();
	if(!ani) return;
	PtcData & ptc = location->GetPtcData();
	if(node < 0)
	{
		IdleProcess(ani, dltTime);
	}else{
		//������������
		long cnode = FindPos();
		if(cnode < 0)
		{
			StopMove();
			FindPos();
			return;
		}
		if(cnode == node)
		{
			StopMove();
			return;
		}
		//���� �����������
		CVECTOR dir = pos;
		if(!ptc.FindPathDir(cnode, pos, node, npos, cnode, dir))
		{
			StopMove();
			return;
		}
		if(location->IsExDebugView()) location->DrawLine(dir, 0xff00ff00, dir + CVECTOR(0.0f, 1.0f, 0.0f), 0xffff0000);
		dir -= pos;
		double dirl = ~dir;
		double vx = dir.x;
		double vz = dir.z;
		double l = vx*vx + vz*vz;
		if(l <= 0.0)
		{
			StopMove();
			return;
		}
		vz = acos(vz/sqrt(l));
		if(vx < 0) vz = -vz;
		ay = float(vz);
		//�������
		pos.x += sinf(ay)*dltTime*speed*kSpeed;
		pos.z += cosf(ay)*dltTime*speed*kSpeed;
		//������ ��������
		MoveProcess(ani, dltTime);
	}
}

long LocLife::FindPos()
{
	MODEL * m = (MODEL *)EntityManager::GetEntityPointer(model);
	if(!m) return -1;
	PtcData & ptc = location->GetPtcData();
	//�����������
	CVECTOR dir(sinf(ay), 0.0f, cosf(ay));
	//������
	float yf, yc, yb;
	long curnode = ptc.FindNode(pos, yc);
	if(curnode < 0)
	{
		FindRandomPos(pos);
		FindPos();
		ay = rand()*(6.28f/RAND_MAX);
		return ptc.FindNode(pos, yc);
	}
	CVECTOR p1 = pos + dir*0.1f;
	CVECTOR p2 = pos - dir*0.1f;
	if(ptc.FindNode(p1, yf) < 0) yf = yc;
	if(ptc.FindNode(p2, yb) < 0) yb = yc;
	pos.y = max(yf, max(yc, yb));
	yc = location->Trace(pos + CVECTOR(0.0f, 0.2f, 0.0f), pos - CVECTOR(0.0f, 0.2f, 0.0f));
	if(yc <= 1.0f) pos.y += 0.2f - 0.4f*yc;
	pos.y += 0.05f;
	p1.y = yf; p2.y = yb;
	CMatrix mtx;
	mtx.BuildViewMatrix(pos + (p2 - p1), pos, CVECTOR(0.0f, 1.0f, 0.0f));
	mtx.Transposition();
	m->mtx = mtx;
	return curnode;
}

void LocLife::StartMove()
{
	//������
	MODEL * m = (MODEL *)EntityManager::GetEntityPointer(model);
	if(!m) return;
	//��������� ������������ ��������
	Animation * ani = m->GetAnimation();
	if(!ani) return;
	node = FindRandomPos(npos);
	IsStartMove(ani);
}

void LocLife::StopMove()
{
	node = -1;
	MODEL * m = (MODEL *)EntityManager::GetEntityPointer(model);
	if(!m) return;
	//��������� ������������ ��������
	Animation * ani = m->GetAnimation();
	if(!ani) return;
	IsStopMove(ani);	
}

bool LocLife::IsNearPlayer(float radius)
{
	if(location->supervisor.player)
	{
		CVECTOR playerPos;
		location->supervisor.player->GetPosition(playerPos);
		playerPos -= pos; playerPos.y = 0.0f;
		if(~playerPos < radius*radius) return true;
	}
	return false;
}

long LocLife::FindRandomPos(CVECTOR & pos)
{
	PtcData & ptc = location->GetPtcData();
	if(!ptc.numTriangles) return -1;
	long i = rand() % ptc.numTriangles;
	long i1 = ptc.triangle[i].i[0];
	long i2 = ptc.triangle[i].i[1];
	long i3 = ptc.triangle[i].i[2];
	pos.x = ptc.vertex[i1].x;
	pos.x += ptc.vertex[i2].x;
	pos.x += ptc.vertex[i3].x;
	pos.y = ptc.vertex[i1].y;
	pos.y += ptc.vertex[i2].y;
	pos.y += ptc.vertex[i3].y;
	pos.z = ptc.vertex[i1].z;
	pos.z += ptc.vertex[i2].z;
	pos.z += ptc.vertex[i3].z;
	pos *= 1.0f/3.0f;
	return i;
}



