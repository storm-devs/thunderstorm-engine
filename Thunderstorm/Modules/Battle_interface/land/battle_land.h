#ifndef _BATTLE_LAND_H_
#define _BATTLE_LAND_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../Utils.h"

class BIManSign;

class BATTLE_LAND_INTERFACE : public Entity
{
	// metods
public:
	BATTLE_LAND_INTERFACE();
	~BATTLE_LAND_INTERFACE();
	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}

protected:
	void SetShowParameters();
	void SetParameters();
	void UpdateCommandos();
	void UpdateAlarm();
	void EndShow();
	void Release();
	void EnableMessageIcons(VDATA * pvdat);
	void DisableMessageIcons();
	void SetTextData();

	// data
protected:
	VDX9RENDER* m_pRS;
	bool m_bShowCommandos;

	BIManSign* m_pManSign;

	std::vector<BITextInfo> m_TextInfo;

	BIImagesInfo m_Images;
};

#endif
