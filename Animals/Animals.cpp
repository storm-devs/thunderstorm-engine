#include <stdio.h>
#include "../../Shared/messages.h"
//#include "..\common_h\defines.h"
#include "../Common_h/Exs.h"
#include "../Common_h/Cvector.h"
#include "../SoundService/VSoundService.h"

#include "Animals.H"

INTERFACE_FUNCTION
CREATE_CLASS(ANIMALS)
//--------------------------------------------------------------------
ANIMALS::ANIMALS()
	:seagulls(nullptr)
	//,sharks(0)
	,fishSchools(nullptr)
	,butterflies(nullptr)
{	
	seagulls = NEW TSeagulls();
	//sharks = NEW TSharks();
	fishSchools = NEW TFishSchools();
	butterflies = NEW TButterflies();
}

//--------------------------------------------------------------------
ANIMALS::~ANIMALS()
{
	GUARD(ANIMALS::~ANIMALS)

	if (seagulls)
		delete seagulls;
	//if (sharks)
	//	delete sharks;
	if (fishSchools)
		delete fishSchools;
	if (butterflies)
		delete butterflies;

	UNGUARD
}

//--------------------------------------------------------------------
bool ANIMALS::Init()
{
	GUARD(ANIMALS::Init)

	_CORE_API->LayerAdd("realize",GetID(),77);
	_CORE_API->LayerAdd("execute",GetID(),77);

	seagulls->Init();
	//sharks->Init();
	fishSchools->Init();
	butterflies->Init();

	return true;
	UNGUARD
}

//--------------------------------------------------------------------
uint32_t _cdecl ANIMALS::ProcessMessage(MESSAGE & message)
{
	GUARD(ANIMALS::ProcessMessage)

	long code = message.Long();
	uint32_t outValue = 0;

	switch (code)
	{
	case MSG_SOUND_SET_MASTER_VOLUME:
		break;
	default:
		outValue = seagulls->ProcessMessage(code, message);
		if (outValue)
			return outValue;
		outValue = fishSchools->ProcessMessage(code, message);
		if (outValue)
			return outValue;
		//outValue = sharks->ProcessMessage(code, message);
		//if (outValue)
		//	return outValue;
		outValue = butterflies->ProcessMessage(code, message);
		if (outValue)
			return outValue;

		break;
	}

	return outValue;
	UNGUARD
}

//--------------------------------------------------------------------
void ANIMALS::Realize(uint32_t _dTime)
{
	GUARD(ANIMALS::Realize)

	seagulls->Realize(_dTime);
	//sharks->Realize(_dTime);
	fishSchools->Realize(_dTime);
	butterflies->Realize(_dTime);

	UNGUARD
}

//--------------------------------------------------------------------
void ANIMALS::Execute(uint32_t _dTime)
{
	GUARD(ANIMALS::Execute)

	seagulls->Execute(_dTime);
	//sharks->Execute(_dTime);
	fishSchools->Execute(_dTime);
	butterflies->Execute(_dTime);
	
	UNGUARD
}

//--------------------------------------------------------------------
uint32_t ANIMALS::AttributeChanged(ATTRIBUTES * _pA)
{
	if (*_pA == "midY")
	{
		seagulls->SetStartY(this->AttributesPointer->GetAttributeAsFloat("midY"));
	}

	return 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
