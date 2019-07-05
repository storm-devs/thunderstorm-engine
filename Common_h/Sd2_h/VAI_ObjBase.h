#ifndef VAI_BASE_HPP
#define VAI_BASE_HPP

#include "../vmodule_api.h"
#include "../Matrix.h"
#include "../model.h"
#include "../Cvector.h"
#include "CannonTrace.h"

class CSaveLoad;

class VAI_OBJBASE : public CANNON_TRACE_BASE
{
private:
	ATTRIBUTES	* pACharacter;

public:
	virtual ~VAI_OBJBASE(){};

	virtual void		SetACharacter(ATTRIBUTES * pAP) { pACharacter = pAP; };
	virtual ATTRIBUTES*	GetACharacter() { return pACharacter; };

	virtual bool		Mount(ATTRIBUTES * ) { return false; };

	virtual void		SetPos(CVECTOR & vNewPos){};

	virtual CVECTOR		GetPos() { return 0.0f; };
	virtual CVECTOR		GetAng() { return 0.0f; };
	virtual CMatrix *	GetMatrix() = 0;
	virtual CVECTOR		GetBoxsize() { return 0.0f; };

	virtual MODEL *		GetModel() = 0;
	virtual entid_t	GetModelEID() = 0;

	virtual void Save(CSaveLoad * pSL) = 0;
	virtual void Load(CSaveLoad * pSL) = 0;	

	virtual void Fire(const CVECTOR & vPos) = 0;
};

#endif