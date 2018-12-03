#ifndef AISHIPROTATECONTROLLER_HPP
#define AISHIPROTATECONTROLLER_HPP

#include "../Common_h/vmodule_api.h"
#include "../Common_h/Sd2_h/VAI_ObjBase.h"

// ============================================================================
// master class AIShipRotateController
// Contain base virtual functions 
// ============================================================================
class AIShip;
class AIShipRotateController
{
private:
	AIShip			*pOurAIShip;	// our AI ship pointer

	uint32_t			dwRotateNum;
	float			fRotateMode, fRotateTime, fRotateSmooth, fRotate;
	float			fGlobalMultiply;

public:

	void	AddRotate(float _fRotate);
	void	SetGlobalMultiply(float _fGlobalMul);

	// init/execute/realize section
	virtual	bool	Init();
	virtual void	Execute(float);
	virtual void	Realize(float);

	// set our ship pointer
	void	SetAIShip(AIShip *pShip) { pOurAIShip = pShip; }
	AIShip	*GetAIShip() { return pOurAIShip; }

	AIShipRotateController(AIShip *pShip);
	virtual ~AIShipRotateController();

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);
};

#endif