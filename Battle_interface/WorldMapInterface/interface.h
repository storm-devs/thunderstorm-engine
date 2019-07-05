#ifndef _WM_INTERFACE_H_
#define _WM_INTERFACE_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../../Common_h/Entity.h"

class WMShipIcon;
class WMShipCommandList;

class WM_INTERFACE : public Entity
{
	VDX9RENDER *rs;

public:
	WM_INTERFACE();
	~WM_INTERFACE();
	bool Init();
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	uint32_t AttributeChanged(ATTRIBUTES * pAttr);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::EXECUTE:
		//	Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}

protected:
	WMShipIcon* m_pShipIcon; // иконки команд и целеуказаний в боевом меню
	WMShipCommandList* m_pCommandList;
	bool m_bVisible;
	long m_nCommandListVerticalOffset;
	long m_nMainCharIndex;
	long m_nCommandMode;

protected:
	void LoadIniFile();

	void MakeControl();
	void ExecuteCommand( long command );
	void UpdateCommandList();
	long GetCurrentCommandTopLine();
	long GetCurrentCommandCharacterIndex();
	long GetCurrentCommandMode();

	bool IsCommandMenuActive();
};

#endif