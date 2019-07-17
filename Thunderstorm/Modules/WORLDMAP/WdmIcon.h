//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	WdmIcon
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _WdmIcon_H_
#define _WdmIcon_H_

#include "WdmInterfaceObject.h"

class WdmEnemyShip;

class WdmIcon : public WdmInterfaceObject
{
	struct Icon
	{
		float u;
		float alpha;
	};

	//--------------------------------------------------------------------------------------------
	//���������������, ������������������
	//--------------------------------------------------------------------------------------------
public:
	WdmIcon();
	virtual ~WdmIcon();

	//�������
	void Update(float dltTime) override;
	//���������
	void LRender(VDX9RENDER* rs) override;

	//--------------------------------------------------------------------------------------------
	//������������
	//--------------------------------------------------------------------------------------------
private:
	WdmEnemyShip* lastShip;
	long texture;
	Icon icon[2];
	float islandAlpha;
	float skipAlpha;
	float stormAlpha;
};

#endif
