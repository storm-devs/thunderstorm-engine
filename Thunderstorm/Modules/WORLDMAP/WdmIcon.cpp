//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	WdmIcon
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#include "WdmIcon.h"
#include "WdmObjects.h"
#include "WdmEnemyShip.h"

//============================================================================================
//���������������, ������������������
//============================================================================================

WdmIcon::WdmIcon()
{
	lastShip = nullptr;
	icon[0].u = -1.0f;
	icon[1].u = -1.0f;
	texture = wdmObjects->rs->TextureCreate("WorldMap\\Interfaces\\BigIcons.tga");
	islandAlpha = 0.0f;
	skipAlpha = 0.0f;
	stormAlpha = 0.0f;
}

WdmIcon::~WdmIcon()
{
	if(texture >= 0) wdmObjects->rs->TextureRelease(texture);
}

//�������
void WdmIcon::Update(float dltTime)
{
	if(lastShip != wdmObjects->enemyShip)
	{
		lastShip = wdmObjects->enemyShip;
		icon[1] = icon[0];
		if(lastShip != nullptr)
		{			
			icon[0].alpha = 0.0f;
			switch(lastShip->shipType)
			{
			case wdmest_unknow:
				icon[0].u = 0.0f;				
				break;
			case wdmest_merchant:
				icon[0].u = 1.0f/8.0f;
				break;
			case wdmest_warring:
				icon[0].u = 2.0f/8.0f;
				break;
			case wdmest_follow:
				icon[0].u = 3.0f/8.0f;
				break;
			}
		}else icon[0].u = -1.0f;
	}
	icon[0].alpha += 2.0f*dltTime;
	if(icon[0].alpha > 1.0f) icon[0].alpha = 1.0f;
	icon[1].alpha -= 1.5f*dltTime;
	if(icon[1].alpha < 0.0f)
	{
		icon[1].u = -1.0f;
		icon[1].alpha = 0.0f;
	}
	if(wdmObjects->curIsland)
	{
		islandAlpha += 2.0f*dltTime;
		if(islandAlpha > 1.0f) islandAlpha = 1.0f;
	}else{
		islandAlpha -= 2.0f*dltTime;
		if(islandAlpha < 0.0f) islandAlpha = 0.0f;
	}
	if(wdmObjects->enableSkipEnemy)
	{
		skipAlpha += 2.0f*dltTime;
		if(skipAlpha > 1.0f) skipAlpha = 1.0f;
	}else{
		skipAlpha -= 2.0f*dltTime;
		if(skipAlpha < 0.0f) skipAlpha = 0.0f;
	}
	//���������� ��������� � �����
	if(wdmObjects->playarInStorm)
	{
		stormAlpha += 2.0f*dltTime;
		if(stormAlpha > 1.0f) stormAlpha = 1.0f;
	}else{
		stormAlpha -= 2.0f*dltTime;
		if(stormAlpha < 0.0f) stormAlpha = 0.0f;
	}
}

//���������
void WdmIcon::LRender(VDX9RENDER * rs)
{
	return; //~!~
	Vertex vrt[6];
	rs->TextureSet(0, texture);
	float w, h;
	wdmObjects->GetVPSize(w, h);
	//������ � ������� ����
	float kDef = rs->GetHeightDeformator();
#ifndef _XBOX
	FillRectCoord(vrt, 8.0f, 8.0f, 64.0f, 64.0f*kDef);
#else
	FillRectCoord(vrt, 50.0f, 50.0f, 64.0f, 64.0f*kDef);
#endif
	FillRectUV1(vrt, 0.0f, 0.0f, 1.0f, 1.0f);
	long alpha;
	if(icon[1].u >= 0.0f)
	{
		alpha = long(255.0f*icon[1].alpha);
		FillRectUV(vrt, icon[1].u, 0.0f, 1.0f/8.0f, 1.0f);
		FillRectColor(vrt, (alpha << 24) | 0xffffff);
		DrawRects(vrt, 1, "WdmDrawIcon");
	}
	if(icon[0].u >= 0.0f)
	{
		alpha = long(255.0f*icon[0].alpha);
		FillRectUV(vrt, icon[0].u, 0.0f, 1.0f/8.0f, 1.0f);
		FillRectColor(vrt, (alpha << 24) | 0xffffff);
		DrawRects(vrt, 1, "WdmDrawIcon");
	}
	//������ � ������ ����
	if(islandAlpha > 0.0f)
	{
#ifndef _XBOX
		FillRectCoord(vrt, 8.0f + 8.0f, h - 64.0f*kDef - 8.0f, 64.0f, 64.0f*kDef);
#else
		FillRectCoord(vrt, 50.0f, h - 64.0f*kDef - 50.0f, 64.0f, 64.0f*kDef);
#endif

		FillRectUV(vrt, 0.0f, 0.0f, 1.0f/8.0f, 1.0f);
		FillRectUV1(vrt, 0.0f, 0.0f, 1.0f, 1.0f);
		FillRectColor(vrt, (long(islandAlpha*255.0f) << 24) | 0xffffff);
		DrawRects(vrt, 1, "WdmDrawIcon");
	}
	//������ �������� ����������
	if(skipAlpha > 0.0f)
	{
#ifndef _XBOX
		FillRectCoord(vrt, 8.0f + 64.0f + 8.0f, 8.0f, 64.0f, 64.0f*kDef);
#else
		FillRectCoord(vrt, 50.0f + 64.0f + 8.0f, 50.0f, 64.0f, 64.0f*kDef);
#endif
		FillRectUV(vrt, 4.0f/8.0f, 0.0f, 1.0f/8.0f, 1.0f);
		FillRectUV1(vrt, 0.0f, 0.0f, 1.0f, 1.0f);
		FillRectColor(vrt, (long(skipAlpha*255.0f) << 24) | 0xffffff);
		DrawRects(vrt, 1, "WdmDrawIcon");
	}
	//������ ������
	if(stormAlpha > 0.0f)
	{
		float move = 0.0f, m;
		if(icon[0].u >= 0.0f)
		{
			move = icon[0].alpha*5.0f;
			if(move > 1.0f) move = 1.0f;
		}
		if(icon[1].u >= 0.0f)
		{
			m = icon[1].alpha*5.0f;
			if(m > 1.0f) m = 1.0f;
			if(m > move) move = m;
		}		
		m = skipAlpha*5.0f;
		if(m > 1.0f) m = 1.0f;
		move += m;
		move *= 64.0f + 8.0f;

#ifndef _XBOX
		FillRectCoord(vrt, 8.0f + move, 8.0f, 64.0f, 64.0f*kDef);
#else
		FillRectCoord(vrt, 50.0f + move, 50.0f, 64.0f, 64.0f*kDef);
#endif
		FillRectUV(vrt, 5.0f/8.0f, 0.0f, 1.0f/8.0f, 1.0f);
		FillRectUV1(vrt, 0.0f, 0.0f, 1.0f, 1.0f);
		FillRectColor(vrt, (long(stormAlpha*255.0f) << 24) | 0xffffff);
		DrawRects(vrt, 1, "WdmDrawIcon");
	}
}
