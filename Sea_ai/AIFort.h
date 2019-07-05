#ifndef SEA_FORT_AI_HPP
#define SEA_FORT_AI_HPP

#include "AICannon.h"
#include "AIShip.h"

#include "../Common_h/ShipLights.h"

// ============================================================================
// Master class AIFort
// Contain AI part for fort, fort cannons, collision part and other
// ============================================================================
class AIShip;
class AIGroup;

class AIFort : public VAI_OBJBASE
{
public:
	class AI_FORT : public VAI_INNEROBJ
	{
	private:
		class TmpVAI_OBJBASE : public VAI_OBJBASE
		{
		public:
			TmpVAI_OBJBASE()
			{
				mTmp.SetIdentity();
			}

			CMatrix mTmp;
			AI_FORT * pFort;

			virtual CMatrix * GetMatrix() { return &GetModel()->mtx; };

			virtual MODEL *		GetModel() { return pFort->GetModel(); };
			virtual entid_t	GetModelEID() { return pFort->GetModelEID(); };

			virtual void Save(CSaveLoad * pSL) {};
			virtual void Load(CSaveLoad * pSL) {};	
			virtual void Fire(const CVECTOR & vPos)	{};

			virtual float Cannon_Trace(long iBallOwner, const CVECTOR &src, const CVECTOR &dst) { return 2.0f; };
			virtual float Trace(const CVECTOR & vSrc, const CVECTOR & vDst) { return 2.0f; };
			virtual bool Clip(const PLANE * planes, long nplanes, const CVECTOR & vCenter, float radius, ADD_POLYGON_FUNC addpoly) { return false; };
			virtual const char * GetCollideMaterialName() { return nullptr; };
			virtual bool GetCollideTriangle(TRIANGLE & triangle) { return false; };
		};

		entid_t			eidModel;
		entid_t			eidBlot;
					

	public:
		CMatrix				mOldMatrix;
		CVECTOR				vPos;
		ATTRIBUTES			* pFortLabelAP;
		TmpVAI_OBJBASE		tmpObject;

		std::vector<AICannon>		aCannons;			// fort cannons container
		std::vector<AICannon>		aCulverins;			// fort culverins container
		std::vector<AICannon>		aMortars;			// fort mortars container

		uint32_t				dwCannonType, dwCulverinType, dwMortarType;

		MODEL *		GetModel() { Assert(api->ValidateEntity(&GetModelEID())); return (MODEL*)api->GetEntityPointer(GetModelEID()); }
		void		SetModelEID(entid_t _eidModel) { eidModel = _eidModel; } 
		entid_t	GetModelEID() { return eidModel; } 
		void		SetBlotEID(entid_t _eidBlot) { eidBlot = _eidBlot; } 
		entid_t	GetBlotEID() { return eidBlot; } 
		uint32_t		GetAllCannonsNum() const { return aCannons.size() + aCulverins.size() + aMortars.size(); }
		uint32_t		GetCannonType(uint32_t dwCannonIndex) 
		{ 
			if (dwCannonIndex < aCannons.size()) return dwCannonType;
			if (dwCannonIndex < aCannons.size() + aCulverins.size()) return dwCulverinType;
			return dwMortarType;
		} 
		uint32_t		GetDamagedCannonsNum() 
		{
			uint32_t i, dwDamagedNum = 0;

			for (i=0; i<aCannons.size(); i++) if (aCannons[i].isDamaged()) dwDamagedNum++;
			for (i=0; i<aCulverins.size(); i++) if (aCulverins[i].isDamaged()) dwDamagedNum++;
			for (i=0; i<aMortars.size(); i++) if (aMortars[i].isDamaged()) dwDamagedNum++;
			
			return dwDamagedNum;
		}

		bool		isNormalMode()
		{
			ATTRIBUTES * pAFM = GetACharacter()->FindAClass(GetACharacter(),"Fort.Mode");
			if (pAFM) return (pAFM->GetAttributeAsDword() == FORT_NORMAL);
			return false;
		}

		AICannon	* GetCannon(uint32_t dwCannonIndex)
		{
			if (dwCannonIndex < aCannons.size()) return &aCannons[dwCannonIndex];
			if (dwCannonIndex < aCannons.size() + aCulverins.size()) return &aCulverins[dwCannonIndex - aCannons.size()];
			return &aMortars[dwCannonIndex - (aCannons.size() + aCulverins.size())];
		}

		AI_FORT(ATTRIBUTES * _pFortLabelAP)
		{
			SetObjType(AIOBJ_FORT);

			tmpObject.pFort = this;

			pFortLabelAP = _pFortLabelAP;

			vPos.x = pFortLabelAP->GetAttributeAsFloat("x");
			vPos.y = 0.0f;//pFortLabelAP->GetAttributeAsFloat("y");
			vPos.z = pFortLabelAP->GetAttributeAsFloat("z");
		}

		virtual CVECTOR		GetPos() const { return vPos; };
		virtual CVECTOR		GetAttackPoint(VAI_INNEROBJ *);
		virtual CVECTOR		GetFollowPoint(VAI_INNEROBJ *) { return 0.0f; };
		virtual CVECTOR		GetAbordagePoint(VAI_INNEROBJ *) { return 0.0f; };

		virtual float		GetMaxFireDistance() { return 0.0f; };
		virtual float		GetMinFireDistance() { return 0.0f; };

		void Save(CSaveLoad * pSL);
		void Load(CSaveLoad * pSL, entid_t eid);
	};

	uint32_t		GetNumForts() { return aForts.size(); }
	AI_FORT		* FindFort(ATTRIBUTES * pACharacter);
	AI_FORT		* GetFort(uint32_t k)
	{
		Assert(k < aForts.size());
		return aForts[k];
	}
private:
	CMatrix					mtxFort;

	DTimer					dtFiredTimer;
	AI_FORT					* pLastTraceFort;
	std::vector<AI_FORT*>			aForts;				// fort container

	float	fMinCannonDamageDistance;

	// Ships lights 
	IShipLights			* pShipsLights;

	void	AddFortHit(long iCharacterIndex, CVECTOR & vHitPos);
	float	GetSpeedV0(uint32_t dwFortIndex);
	bool	ScanFortForCannons(AI_FORT * pFort, char * pModelsDir, char * pLocatorsName);
	bool	AddFort(ATTRIBUTES * pIslandAP, ATTRIBUTES * pFortAP, ATTRIBUTES * pFortCharacter, entid_t eidModel, entid_t eidBlot);
	AI_FORT * FindFort(entid_t eidModel);

public:
	static AIFort			* pAIFort;

	AIFort();
	~AIFort();

	// AI section
		bool		isAttack(AIGroup * pGroup);
		bool		isDead();		// is group dead?
		float		GetPower();

	// inherit functions Entity
		bool Init();
		void SetDevice();

		void Realize(uint32_t Delta_Time);
		void Execute(uint32_t Delta_Time);
		
		bool CreateState(Entity_STATE_GEN * state_gen);
		bool LoadState(Entity_STATE * state);
		
		uint32_t ProcessMessage(MESSAGE & message);

		uint32_t AttributeChanged(ATTRIBUTES * pAttribute);

	// inherit functions COLLISION_OBJECT
		virtual float Trace(const CVECTOR & vSrc, const CVECTOR & vDst);
		virtual bool Clip(const PLANE * planes, long nplanes, const CVECTOR & vCenter, float radius, ADD_POLYGON_FUNC addpoly) { return false; };

		virtual const char * GetCollideMaterialName() { return nullptr; };
		virtual bool GetCollideTriangle(TRIANGLE & triangle) { return false; };

	// inherit functions CANNON_TRACE_BASE
		float		Cannon_Trace(long iBallOwner, const CVECTOR & vSrc, const CVECTOR & vDst);

	// inherit functions VAI_OBJBASE
		ATTRIBUTES	* GetACharacter();

		CMatrix		* GetMatrix() { return &mtxFort; };
		MODEL		* GetModel() { return nullptr; };
		entid_t	GetModelEID() { entid_t eid; return eid; };
		CVECTOR		GetPos() { return CVECTOR(0.0f,0.0f,0.0f); };
		CVECTOR		GetAng() { return CVECTOR(0.0f,0.0f,0.0f); };

		bool		Mount(ATTRIBUTES * pAttribute);

		void Save(CSaveLoad * pSL);
		void Load(CSaveLoad * pSL);

		void Fire(const CVECTOR & vPos);
};

#endif