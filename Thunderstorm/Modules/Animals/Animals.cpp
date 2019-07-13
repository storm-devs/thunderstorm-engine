#include "../../Shared/messages.h"
//#include defines.h"
#include "Cvector.h"
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
	seagulls = new TSeagulls();
	//sharks = new TSharks();
	//fishSchools = new TFishSchools();
	butterflies = new TButterflies();
}

//--------------------------------------------------------------------
ANIMALS::~ANIMALS()
{
	if (seagulls)
		delete seagulls;
	//if (sharks)
	//	delete sharks;
	//if (fishSchools)
	//	delete fishSchools;
	if (butterflies)
		delete butterflies;
}

//--------------------------------------------------------------------
bool ANIMALS::Init()
{
	EntityManager::AddToLayer(REALIZE,GetId(),77);
	EntityManager::AddToLayer(EXECUTE, GetId(),77);

	seagulls->Init();
	//sharks->Init();
	//fishSchools->Init();
	butterflies->Init();

	return true;
}

//--------------------------------------------------------------------
uint64_t ANIMALS::ProcessMessage(MESSAGE & message)
{
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
}

//--------------------------------------------------------------------
void ANIMALS::Realize(uint32_t _dTime)
{
	seagulls->Realize(_dTime);
	//sharks->Realize(_dTime);
	//fishSchools->Realize(_dTime);
	butterflies->Realize(_dTime);
}

//--------------------------------------------------------------------
void ANIMALS::Execute(uint32_t _dTime)
{
	seagulls->Execute(_dTime);
	//sharks->Execute(_dTime);
	//fishSchools->Execute(_dTime);
	butterflies->Execute(_dTime);
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
