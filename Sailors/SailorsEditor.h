
#include "..\common_h\dx9render.h"
#include "..\common_h\model.h"
#include "..\common_h\messages.h"
#include "..\common_h\rands.h"
#include "..\common_h\ship_base.h"

#include "SailorsMenu.h"



class SailorsEditor : public ENTITY
{
	public:

	SailorsEditor();
	virtual ~SailorsEditor();

	virtual bool Init();
	virtual void Execute(dword dltTime);
	virtual void Realize(dword dltTime);


	VDX9RENDER * rs;
	ENTITY_ID sailors;
	ENTITY_ID shipID;
	ENTITY_ID pointID;


	MODEL * model;
	
	CVECTOR cameraPos;
	CVECTOR cameraTo;
	CVECTOR cameraAng;

	Menu menu;
	//SailorsPoints sailorsPoints;

	std::string _shipName;

	void SetCamera(dword &dltTime);
	void LoadFromIni(std::string fileName);
};
