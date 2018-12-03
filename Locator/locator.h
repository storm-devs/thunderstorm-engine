#ifndef _LOCATOR_H_
#define _LOCATOR_H_


#include "..\common_h\vmodule_api.h"
#include "..\common_h\geometry.h"
#include "blast.h"

class LOCATOR : public ENTITY 
{
	enum
	{
		_X_ = 1,
		_Y_ = 2,
		_Z_ = 4,
		_AX_ = 8,
		_AY_ = 16,
		_AZ_ = 32,
		_XYZ_ = _X_|_Y_|_Z_
	};
	VGEOMETRY * gs;
	VDX9RENDER * rs;
	GEOS * geo;
	long groupID;
	long stringIndex;
	ENTITY_ID ParticlesID;

	void	LocateForI(VDATA * pData);
	void	LocateForI_L2(ATTRIBUTES * pA,GEOS * g, GEOS::LABEL & label);
	void	LocateForI_Locators(ATTRIBUTES * pA, GEOS * geo, long iGroupID, uint32_t dwFlags);

public:
	~LOCATOR();
	 LOCATOR();
	bool Init();
	uint32_t _cdecl ProcessMessage(MESSAGE & message);
	uint32_t AttributeChanged(ATTRIBUTES *);
	bool VerifyParticles();
};

//API_MODULE_START(0)
//	CREATE_CLASS(0,LOCATOR)
//	CREATE_CLASS(1,BLAST)
//API_MODULE_END

#endif