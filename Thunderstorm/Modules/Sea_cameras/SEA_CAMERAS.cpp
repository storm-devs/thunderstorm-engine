#include "SEA_CAMERAS.h"
#include "Sd2_h/VAI_ObjBase.h"
#include "../../Shared/sea_ai/Script_defines.h"
#include "FreeCamera.h"
#include "DeckCamera.h"

INTERFACE_FUNCTION
CREATE_CLASS(SEA_CAMERAS)
CREATE_CLASS(FREE_CAMERA)
CREATE_CLASS(SHIP_CAMERA)
CREATE_CLASS(DECK_CAMERA)

SEA_CAMERAS::SEA_CAMERAS()
{
	bActive = true;
//	ShowCursor(false);
}

SEA_CAMERAS::~SEA_CAMERAS()
{
//	ShowCursor(true);
}

void SEA_CAMERAS::ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam)
{
/*	//GUARD(SEA_CAMERAS::ProcessMessage(uint32_t,uint32_t,uint32_t))
	switch(iMsg)
	{
		case WM_ACTIVATE: 
		{
			WORD wActive = LOWORD(wParam);           
			bActive = (wActive == WA_CLICKACTIVE || wActive == WA_ACTIVE);
			for (uint32_t i=0;i<CamerasArray.size();i++) CamerasArray[i]->SetActive(bActive);
		}
		break;
	}
	//UNGUARD*/
}

uint64_t SEA_CAMERAS::ProcessMessage(MESSAGE & message)
{
	uint32_t i;
	switch (message.Long())
	{
		case AI_CAMERAS_ADD_CAMERA:
		{
			entid_t eidCamera = message.EntityID();
			COMMON_CAMERA * pCamera = (COMMON_CAMERA*)EntityManager::GetEntityPointer(eidCamera);
			//if (CamerasArray.Find(pCamera) == INVALID_ARRAY_INDEX) CamerasArray.Add(pCamera);
			const auto it = std::find(CamerasArray.begin(), CamerasArray.end(), pCamera);
			if (it == CamerasArray.end())
				CamerasArray.push_back(pCamera);
			pCamera->SetOn(false);
			pCamera->SetActive(bActive);
		}
		break;
		case AI_CAMERAS_SET_CAMERA:
		{
			entid_t eidCamera = message.EntityID();
			ATTRIBUTES * pACharacter = message.AttributePointer();
			COMMON_CAMERA * pCamera = (COMMON_CAMERA*)EntityManager::GetEntityPointer(eidCamera);
			//if (CamerasArray.Find(pCamera) == INVALID_ARRAY_INDEX) CamerasArray.Add(pCamera);
			const auto it = std::find(CamerasArray.begin(), CamerasArray.end(), pCamera);
			if (it == CamerasArray.end())
				CamerasArray.push_back(pCamera);
			for (i=0;i<CamerasArray.size();i++) CamerasArray[i]->SetOn(false);
			pCamera->SetOn(true);
			pCamera->SetActive(bActive);
			pCamera->SetCharacter(pACharacter);
		}
		break;
		case AI_MESSAGE_SEASAVE:
		{
			CSaveLoad * pSL = (CSaveLoad*)message.Pointer();
			for (i=0; i<CamerasArray.size();i++) CamerasArray[i]->Save(pSL);
		}
		break;
		case AI_MESSAGE_SEALOAD:
		{
			CSaveLoad * pSL = (CSaveLoad*)message.Pointer();
			for (i=0; i<CamerasArray.size();i++) CamerasArray[i]->Load(pSL);
		}
		break;
	}
	return 0;
}