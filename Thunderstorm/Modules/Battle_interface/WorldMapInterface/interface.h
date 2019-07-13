#ifndef _WM_INTERFACE_H_
#define _WM_INTERFACE_H_

#include "../bi_defines.h"
#include "Entity.h"

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
    uint64_t ProcessMessage(MESSAGE & message);
	uint32_t AttributeChanged(ATTRIBUTES * pAttr);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::execute:
		//	Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}

protected:
	WMShipIcon* m_pShipIcon; // ������ ������ � ������������ � ������ ����
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