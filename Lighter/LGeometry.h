//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	LGeometry
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _LGeometry_H_
#define _LGeometry_H_

#include "LTypes.h"
#include "../Common_h/model.h"

class LGeometry  
{
	struct Object
	{
		Object()
		{
			name = nullptr;
			nameReal = nullptr;
			m = nullptr;
			lBufSize = 0;
		};
		char * name;			//���� �� col �����
		char * nameReal;		//��� ��������
		MODEL * m;				//��������� �� ��������
		ENTITY_ID model;		//��������
		long lBufSize;			//������ ������ ������ ��� ���� ��������
	};

//--------------------------------------------------------------------------------------------
//���������������, ������������������
//--------------------------------------------------------------------------------------------
public:
	LGeometry();
	virtual ~LGeometry();

	//���������� ���� �� �������
	void SetModelsPath(const char * mPath);
	//���������� ���� ��� ������� ������
	void SetLightPath(const char * lPath);
	//�������� ������
	void AddObject(const char * name, ENTITY_ID & model);
	//���������� ������
	bool Process(VDX9RENDER * rs, long numLights);
	//���������� �������
	void DrawNormals(VDX9RENDER * rs);
	//�������� ����� � �������
	void UpdateColors(VDX9RENDER * rs);
	//����������� ��� ����� ��� ������
	float Trace(CVECTOR & src, CVECTOR & dst);
	//��������� ���������
	bool Save();


	Object * object;
	long numObjects;
	long maxObjects;

	Vertex * vrt;
	long numVrt;
	long maxVrt;

	Triangle * trg;
	long numTrg;
	long maxTrg;

	VertexBuffer * vbuffer;
	long numVBuffers;
	long maxVBuffers;

	Shadow * shadows;
	
	CVECTOR min, max;
	float radius;

	bool useColor;

	CVECTOR * drawbuf;

	char modelsPath[512];
	char lightPath[512];
};

#endif

