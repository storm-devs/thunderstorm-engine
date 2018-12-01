#include "AISeaGoods.h"

AISeaGoods::AISeaGoods()
{
	pSea = null;
	pGeoService = null;

	bDeleteGoodAnyway = false;

	dtCheckShips.Setup(FRAND(1.0f), 1.0f);
}

AISeaGoods::~AISeaGoods()
{
	for (dword i=0; i<aGoods.size(); i++)
	{
		if (aGoods[i]->pGeo) pGeoService->DeleteGeometry(aGoods[i]->pGeo);
		aGoods[i]->sModel.clear();
		aGoods[i]->aItems.clear();
		STORM_DELETE(aGoods[i]);
	}
	aGoods.clear();
}

bool AISeaGoods::Init()
{
	SetDevice();
	return true;
}

void AISeaGoods::SetDevice()
{
	pGeoService = (VGEOMETRY*)api->CreateService("geometry"); Assert(pGeoService);
}

void AISeaGoods::Execute(dword dwDeltaTime)
{
	ENTITY_ID	EID;

	float fDeltaTime = float(dwDeltaTime) * 0.001f;

	if (!pSea && api->FindClass(&EID, "sea", 0))
		pSea = (SEA_BASE*)api->GetEntityPointer(&EID);
	
	if (!pSea) return;

	for (dword i=0; i<aGoods.size(); i++)
		for (dword j=0; j<aGoods[i]->aItems.size(); j++)
		{
			item_t * pI = &aGoods[i]->aItems[j];
			pI->fTime -= fDeltaTime;
			
			pI->vPos.y = pSea->WaveXZ(pI->vPos.x, pI->vPos.z, &pI->vNormal);

			if (pI->fTime <= 0.0f)
			{
				pI->vPos.y -= fabsf(pI->fTime) * 0.05f;
				if (pI->fTime < -20.0f)
				{
					//aGoods[i]->aItems.ExtractNoShift(j);
					aGoods[i]->aItems[i] = aGoods[i]->aItems.back();
					aGoods[i]->aItems.pop_back();
					j--;
					continue;
				}
			}

		if (dtCheckShips.Update(dwDeltaTime))
		{
			aShips.clear();

			// enumerate ships
			if (api->FindClass(&EID, "ship", 0)) do
			{
				aShips.push_back((SHIP_BASE*)api->GetEntityPointer(&EID));
			} while (api->FindClassNext(&EID));

			// check ships
			for (dword k=0; k<aShips.size(); k++)
			{
				SHIP_BASE * pS = aShips[k];
				ATTRIBUTES * pACharacter = pS->GetACharacter();
				int iCharacterIndex = GetIndex(pS->GetACharacter());
				float fDistance = sqrtf(~(pS->State.vPos - pI->vPos));
				if (fDistance <= pS->State.vBoxSize.z * fDistanceMultiply)
				{
					VDATA * pVData = api->Event(SHIP_EAT_SWIM_GOOD, "llsl", iCharacterIndex, pI->iCharIndex, pI->sGoodName, pI->iQuantity);
					if (pVData->GetLong() || bDeleteGoodAnyway)
					{
						//aGoods[i]->aItems.ExtractNoShift(j); 
						aGoods[i]->aItems[i] = aGoods[i]->aItems.back();
						aGoods[i]->aItems.pop_back();
						j--; 
						break;
					}
				}
			}
		}
	}
}

void AISeaGoods::Realize(dword dwDeltaTime)
{
	if (!pSea) return;

	AIHelper::pRS->SetRenderState(D3DRS_LIGHTING, true);

	for (dword i=0; i<aGoods.size(); i++) if (aGoods[i]->pGeo)
		for (dword j=0; j<aGoods[i]->aItems.size(); j++)
		{
			item_t * pI = &aGoods[i]->aItems[j];
	
			// set world matrix for item
			CMatrix m; m.BuildPosition(pI->vPos.x, pI->vPos.y, pI->vPos.z);
			
			AIHelper::pRS->SetTransform(D3DTS_WORLD, m);
			aGoods[i]->pGeo->Draw((GEOS::PLANE*)AIHelper::pRS->GetPlanes(), 0, null);
		}

	AIHelper::pRS->SetRenderState(D3DRS_LIGHTING, false);
}

dword AISeaGoods::AttributeChanged(ATTRIBUTES * pAttribute)
{
	ATTRIBUTES * pParent = pAttribute->GetParent();

	if (*pAttribute == "Add")
	{
		for (dword i=0; i<aGoods.size(); i++) if (aGoods[i]->sModel == sTmpModel)
		{
			aGoods[i]->aItems.push_back(TmpItem);
			return 0;
		}
		goods_t * pG = NEW goods_t;
		aGoods.push_back(pG);
		pG->sModel = sTmpModel;
		pG->aItems.push_back(TmpItem);
		pG->pGeo = pGeoService->CreateGeometry((sModelPath + "\\" + sTmpModel).c_str(), 0, 0);
		return 0;
	}

	if (*pAttribute == "CharIndex") { TmpItem.iCharIndex = pAttribute->GetAttributeAsDword(); return 0; }
	if (*pAttribute == "Time")		{ TmpItem.fTime = pAttribute->GetAttributeAsFloat(); return 0; }
	if (*pAttribute == "Quantity")	{ TmpItem.iQuantity = pAttribute->GetAttributeAsDword(); return 0; }
	if (*pAttribute == "Model")		{ sTmpModel = pAttribute->GetThisAttr(); return 0; }
	if (*pAttribute == "Good")		{ strcpy(TmpItem.sGoodName, pAttribute->GetThisAttr()); return 0; }
	
	if (*pParent == "Pos")
	{
		if (*pAttribute == "x")		{ TmpItem.vPos.x = pAttribute->GetAttributeAsFloat(); return 0; }
		if (*pAttribute == "z")		{ TmpItem.vPos.z = pAttribute->GetAttributeAsFloat(); return 0; }
	}

	if (*pAttribute == "ModelsPath")		{ sModelPath = pAttribute->GetThisAttr(); return 0; }
	if (*pAttribute == "DeleteGoodAnyway")	{ bDeleteGoodAnyway = pAttribute->GetAttributeAsDword() == 1; return 0; }
	if (*pAttribute == "DistanceMultiply")	{ fDistanceMultiply = pAttribute->GetAttributeAsFloat(); return 0; }

	return 0;
}
