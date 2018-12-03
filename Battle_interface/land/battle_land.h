#ifndef _BATTLE_LAND_H_
#define _BATTLE_LAND_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../Utils.h"

class BIManSign;

class BATTLE_LAND_INTERFACE : public ENTITY
{
	// metods
public:
	BATTLE_LAND_INTERFACE();
	~BATTLE_LAND_INTERFACE();
	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t _cdecl ProcessMessage(MESSAGE & message);

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
