
#include "../Common_h/dx9render.h"
#include "../Common_h/model.h"
#include "../Common_h/ship_base.h"

#include "SailorsMenu.h"



class SailorsEditor : public Entity
{
	public:

	SailorsEditor();
	virtual ~SailorsEditor();

	virtual bool Init();
	virtual void Execute(uint32_t dltTime);
	virtual void Realize(uint32_t dltTime);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}

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
