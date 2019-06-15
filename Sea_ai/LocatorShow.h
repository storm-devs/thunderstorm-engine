#ifndef SEA_LOCATOR_SHOW_HPP
#define SEA_LOCATOR_SHOW_HPP

#include "AIHelper.h"

class SeaLocatorShow : public ENTITY
{
	ATTRIBUTES	* pALocators;
	bool		bShow;
	float		fScale;

	float		fWidth, fHeight;
	CMatrix		view,mtx;

	struct SphVertex
	{
		CVECTOR v;
		uint32_t	c;
	};

	uint32_t		sphereNumTrgs;
	SphVertex * sphereVertex;

	void		CreateSphere();

	bool		isLocator(ATTRIBUTES * pA);
	CVECTOR		GetLocatorPos(ATTRIBUTES * pA);
	float		GetLocatorAng(ATTRIBUTES * pA);
	float		GetLocatorRadius(ATTRIBUTES * pA);
	char		* GetRealLocatorName(ATTRIBUTES * pA);
	char		* GetLocatorName(ATTRIBUTES * pA);
	char		* GetLocatorGroupName(ATTRIBUTES * pA);

	void		PrintLocator(ATTRIBUTES * pA);
	void		ProcessLocators(ATTRIBUTES * pA);

public:
	SeaLocatorShow();
	~SeaLocatorShow();

	bool Init();
	void SetDevice();

	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);
	
	bool CreateState(ENTITY_STATE_GEN * state_gen);
	bool LoadState(ENTITY_STATE * state);
	
	void ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam);
	uint32_t ProcessMessage(MESSAGE & message);

	uint32_t AttributeChanged(ATTRIBUTES *pAttribute);
};

#endif
