//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	Sharks
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _Sharks_H_
#define _Sharks_H_

#include "../Common_h/dx9render.h"
#include "../Common_h/Matrix.h"
#include "../Common_h/ship_base.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/Island_Base.h"
#include "../Common_h/Animation.h"

class Sharks : public ENTITY  
{
	struct Vertex
	{
		CVECTOR pos;
		uint32_t color;
		float u, v;
	};

	class Shark : public AnimationEventListener
	{
		static uint16_t indeces[];
	public:
		Shark();
		~Shark();

		bool Init(float vp_x, float vp_z, bool isLoadModel = true);

		void Reset(float cam_x, float cam_z);
		void Repulsion(Shark & shr);
		void ShipApply(float x, float z, float r2);
		void Coordination(float cam_x, float cam_z, float dltTime, SEA_BASE * sb, ISLAND_BASE * ib);
		void IslandCollision(ISLAND_BASE * ib, long numPnt, float rad, float frc);
		virtual void Event(Animation * animation, long index, long eventID, AnimationEvent event);
		long GenerateTrack(uint16_t * inds, Vertex * vrt, uint16_t base, SEA_BASE * sb);

		//����� ����������
		CVECTOR pos;		//������� ����� ����������
		CVECTOR vel;		//����������� �����������
		CVECTOR force;		//���� ����������� ��������
		float yDir;			//��������� � �������� ��� ����������
		float dirTime;		//����� �� ��������� �����
		float accs;			//��������� �����
		CVECTOR rForce;		//��������� ��������� ����
		float rTime;
		//�����
		CVECTOR fforce;		//���� ����������� ��������
		CVECTOR spos;		//������� ��������
		CVECTOR angs;		//���� ��������
		float turn;			//�������� ��������� ����
		float imspd;		//�������� ����������
		float speed;		//�������� �����������
		float shipY;		//����������� �������
		float vBase;		//�������� ����� �����
		ENTITY_ID model;	//�������� �����		
		//��������
		float aniTime;		//����� ������������ ������� ��������
		float jumpTime;		//����� �� ���������� ������������
		bool speedUp;
	};

	friend Shark;

	struct Periscope
	{
		CVECTOR pos;
		float ay;
		float time;
		ENTITY_ID model;
	};

//--------------------------------------------------------------------------------------------
//���������������, ������������������
//--------------------------------------------------------------------------------------------
public:
	Sharks();
	virtual ~Sharks();

	//�������������
	bool Init();
	//����������
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);


//--------------------------------------------------------------------------------------------
//������������
//--------------------------------------------------------------------------------------------
private:
	bool LoadPeriscopeModel();

private:
	VDX9RENDER * rs;
	Shark shark[6];
	long numShakes;
	Periscope periscope;
	float waitPTime;
	CVECTOR camPos;
	long shipcode;
	ENTITY_ID sea;
	ENTITY_ID island;
	long trackTx;
	uint16_t indeces[7*10*3];
	Vertex vrt[7*10];
};

#endif

