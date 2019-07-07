#ifndef AI_SEA_GOODS_HPP
#define AI_SEA_GOODS_HPP

#include "AIHelper.h"
#include "../Common_h/geometry.h"
#include "../Common_h/sea_base.h"
#include "../Common_h/ship_base.h"
#include "../Common_h/dtimer.h"

class AISeaGoods : public Entity
{
private:
	struct item_t
	{
		char		sGoodName[48];
		long		iCharIndex, iQuantity;
		float		fTime;
		CVECTOR		vPos, vNormal;
	};

	struct goods_t
	{
		std::string			sModel;
		std::vector<item_t>	aItems;
		GEOS			* pGeo;

		goods_t() {};
	};

	std::vector<goods_t*>		aGoods;
	std::vector<SHIP_BASE*>	aShips;
	
	VGEOMETRY		* pGeoService;
	SEA_BASE		* pSea;
	item_t			TmpItem;
	std::string			sModelPath, sTmpModel;
	DTimer			dtCheckShips;
	bool			bDeleteGoodAnyway;
	float			fDistanceMultiply;	

public:
	AISeaGoods();
	~AISeaGoods();

	bool	Init();
	void	SetDevice();

	void	Realize(uint32_t Delta_Time);
	void	Execute(uint32_t Delta_Time);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}
	uint32_t	AttributeChanged(ATTRIBUTES * pAttributeChanged);
};

#endif