#ifndef SEA_COMMON_CAMERA_HPP
#define SEA_COMMON_CAMERA_HPP

#include "vmodule_api.h"
#include "Sd2_h/VAI_ObjBase.h"
#include "EntityManager.h"

class COMMON_CAMERA : public Entity
{
private:
	bool			bActive;
	bool			bOn;

	float			fPerspective;

	entid_t		eidObject;
	VAI_OBJBASE		* pAIObj;

protected:
	ATTRIBUTES		* pACharacter;

public:
	bool FindShip()
	{
		Assert(pACharacter);
		// get entity id from loaded ships
		auto& entities = EntityManager::GetEntityIdVector("ship");
		for (auto ship : entities) {
			VAI_OBJBASE * pObj = (VAI_OBJBASE*)EntityManager::GetEntityPointer(ship);
			if (pObj->GetACharacter() == pACharacter)
			{
				SetEID(pObj->GetModelEID());
				SetAIObj(pObj);
				return true;
			}
		}
		return false;
	}

	MODEL *GetModelPointer()
	{
		return (MODEL*)EntityManager::GetEntityPointer(eidObject);
	}
	void		SetAIObj(VAI_OBJBASE * _pAIObj) { pAIObj = _pAIObj; }
	VAI_OBJBASE * GetAIObj() { return pAIObj; }
	void		SetEID(entid_t pEID) { eidObject = pEID; };
	entid_t	GetEID() { return eidObject; };
	
	virtual void SetCharacter(ATTRIBUTES *_pACharacter) { pACharacter = _pACharacter; };

	void	SetPerspective(float _fPerspective) { fPerspective = _fPerspective; };
	float	GetPerspective() { return fPerspective; };

	void SetOn(bool bOnOff) { bOn = bOnOff; };
	void SetActive(bool bNewActive) { bActive = bNewActive; };

	bool isOn() { return bOn; };
	bool isActive() { return bActive; };

	virtual void Save(CSaveLoad * pSL) = 0;
	virtual void Load(CSaveLoad * pSL) = 0;

	COMMON_CAMERA() { bOn = false; bActive = false; fPerspective = 1.285f; };
	virtual ~COMMON_CAMERA() {};
};

#endif