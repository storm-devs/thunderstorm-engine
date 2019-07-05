
#include "../Common_h/dx9render.h"
#include "../Common_h/model.h"
#include "../Common_h/ship_base.h"

#include "SailorsMenu.h"



class SailorsEditor : public ENTITY
{
	public:

	SailorsEditor();
	virtual ~SailorsEditor();

	virtual bool Init();
	virtual void Execute(uint32_t dltTime);
	virtual void Realize(uint32_t dltTime);


	VDX9RENDER * rs;
	entid_t sailors;
	entid_t shipID;
	entid_t pointID;


	MODEL * model;
	
	CVECTOR cameraPos;
	CVECTOR cameraTo;
	CVECTOR cameraAng;

	Menu menu;
	//SailorsPoints sailorsPoints;

	std::string _shipName;

	void SetCamera(uint32_t &dltTime);
	void LoadFromIni(std::string fileName);
};
