#ifndef _ANIMALS_H_
#define _ANIMALS_H_

#include "../common_h/geometry.h"
#include "TSeagulls.h"
//#include "TSharks.h"
#include "TFishSchools.h"
#include "TButterflies.h"

///////////////////////////////////////////////////////////////////
// DEFINES & TYPES
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class ANIMALS: public Entity
{
public:
	ANIMALS();
	virtual ~ANIMALS();

	virtual bool Init();
	virtual uint32_t ProcessMessage(MESSAGE & message);
	virtual void Realize(uint32_t _dTime);
	virtual void Execute(uint32_t _dTime);
	uint32_t AttributeChanged(ATTRIBUTES * pA);
	//virtual bool CreateState(ENTITY_STATE_GEN * state_gen);
	//virtual bool LoadState(ENTITY_STATE * state);

private:
	TSeagulls    *seagulls;
	//TSharks      *sharks;
	TFishSchools *fishSchools;
	TButterflies *butterflies;
};

//API_MODULE_START("Animals")
//	CREATE_CLASS(ANIMALS)
//API_MODULE_END

#endif