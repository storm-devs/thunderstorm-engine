//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	WdmWindRose
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _WdmWindRose_H_
#define _WdmWindRose_H_

#include "WdmRenderModel.h"

class WdmWindRose : public WdmRenderModel  
{
	struct Vertex
	{
		float x, y, z;
		uint32_t c;
		float tu, tv;
	};
//--------------------------------------------------------------------------------------------
//���������������, ������������������
//--------------------------------------------------------------------------------------------
public:
	WdmWindRose();
	virtual ~WdmWindRose();

	//�������
	void Update(float dltTime);

	void PRender(VDX9RENDER * rs){};
	void MRender(VDX9RENDER * rs){};
	void LRender(VDX9RENDER * rs);

//--------------------------------------------------------------------------------------------
//������������
//--------------------------------------------------------------------------------------------
private:
	long shadowTexture;
};

#endif
