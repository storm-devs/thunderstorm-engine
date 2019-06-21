/******************************************************************************
File:  blade.h

Author:   Nick Chirkov

Comments:
model binded to an animated locator
******************************************************************************/
#pragma once

#include "../Common_h/EntityManager.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/collide.h"
#include "../Common_h/model.h"

#define BLADE_INFO_QUANTITY	2
#define ITEMS_INFO_QUANTITY 10

class BLADE : public Entity
{
	#define FVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)
	struct VERTEX
	{
		CVECTOR pos;
		unsigned long diffuse;
	};
	#define WAY_LENGTH 64

	struct BLADE_INFO
	{
		ENTITY_ID eid;
		long color[2];//	color of the blade
		float defLifeTime, lifeTime;	//
		float time;	//current time

		VERTEX vrt[WAY_LENGTH*2];	//16 stripped quads
		float vrtTime[WAY_LENGTH];
		const char *locatorName;

		BLADE_INFO();
		~BLADE_INFO();
		void DrawBlade(VDX9RENDER * rs,unsigned int blendValue,MODEL *mdl,NODE *manNode);
		bool LoadBladeModel(MESSAGE &message);
	};

	struct TIEITEM_INFO
	{
		long nItemIndex;
		ENTITY_ID eid;
		char * locatorName;

		TIEITEM_INFO() {nItemIndex=-1; locatorName=nullptr;}
		~TIEITEM_INFO() {Release();}
		void Release();
		void DrawItem(VDX9RENDER * rs,unsigned int blendValue,MODEL *mdl,NODE *manNode);
		bool LoadItemModel(const char* mdlName,const char* locName);
	};

	VDX9RENDER * rs;
	COLLIDE *col;
	ENTITY_ID man;
	unsigned int blendValue;

	BLADE_INFO blade[BLADE_INFO_QUANTITY];

	ENTITY_ID gun;
	const char *gunLocName;

	TIEITEM_INFO items[ITEMS_INFO_QUANTITY];

	bool LoadBladeModel(MESSAGE &message);
	bool LoadGunModel(MESSAGE &message);
	void GunFire();

	void AddTieItem(MESSAGE &message);
	void DelTieItem(MESSAGE &message);
	void DelAllTieItem();
	long FindTieItemByIndex(long n);

public:
	BLADE();
	~BLADE();
	bool Init() override;
	void ProcessStage(Stage stage, uint32_t delta) override	{
		switch(stage)
		{
		//case Stage::EXECUTE:
		//	Execute(delta);
		//	break;
		case Stage::REALIZE:
			Realize(delta);
			break;
		//case Stage::LOST_RENDER:
		//	LostRender();
		//	break;
		//case Stage::RESTORE_RENDER:
		//	RestoreRender();
		//	break;
		}
	}
	void Realize(uint32_t Delta_Time);
	uint32_t ProcessMessage(MESSAGE &message) override;
};
