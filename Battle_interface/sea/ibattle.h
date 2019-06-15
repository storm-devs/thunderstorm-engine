#ifndef __BATTLE_INTERFACE_H_
#define __BATTLE_INTERFACE_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "battle_navigator.h"
#include "../Utils.h"

class BIShipIcon;
class ShipInfoImages;

class BATTLE_INTERFACE : public ENTITY
{
	VDX9RENDER *rs;

public:
	BATTLE_INTERFACE();
	~BATTLE_INTERFACE();
	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	uint32_t AttributeChanged(ATTRIBUTES * pAttr);

	void LostRender() override { BattleNavigator.LostRender(); };
	void RestoreRender() override { BattleNavigator.RestoreRender(); };

protected:
	BATTLE_NAVIGATOR	BattleNavigator; // навигационные иконки
	//MESSAGE_ICONS *		m_pMessageIcons;
	BIShipIcon*			m_pShipIcon; // иконки команд и целеуказаний в боевом меню
	bool	m_bShowCommandMenu;
	bool	m_bShowBattleNavigator;
	bool	m_bYesShowAll;
	bool	m_bVisible;

	float	m_fBlinkSpeed;
	float	m_fCurBlinkTime;

	bool	m_bNeedIslandSet;

	bool	m_bMyShipView;

	std::vector<BITextInfo> m_TextArray;
	BILinesInfo m_LinesInfo;
	bool m_bShowBattleBorder;
	BIBorderInfo m_BattleBorder;
	BIImagesInfo m_ImagesInfo;

	ShipInfoImages* m_pShipInfoImages;

protected:
	void LoadIniFile();
	void CheckSeaState();
	void EnableMessageIcons(VDATA * pvdat);
};

#endif