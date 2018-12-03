#ifndef AI_SEA_GOODS_HPP
#define AI_SEA_GOODS_HPP

#include "AIHelper.h"
#include "..\common_h\geometry.h"
#include "..\common_h\sea_base.h"
#include "..\common_h\ship_base.h"
#include "..\common_h\dtimer.h"

class AISeaGoods : public ENTITY
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

	uint32_t	AttributeChanged(ATTRIBUTES * pAttributeChanged);
};

#endif