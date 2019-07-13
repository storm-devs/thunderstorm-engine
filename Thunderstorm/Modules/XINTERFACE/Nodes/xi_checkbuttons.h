#ifndef __XI_CHECKBUTTONS_H__
#define __XI_CHECKBUTTONS_H__

#include "../inode.h"
#include "xi_image.h"
#include "../xdefines.h"

struct ButtonDescribe
{
	ButtonDescribe() { pImg= nullptr; bSetPos=false; }
	~ButtonDescribe() { STORM_DELETE( pImg ); }

	struct StrDescribe
	{
		std::string str;
		float fX;
	};
	std::vector<StrDescribe> aStr;
	bool bChoose;
	bool bDisable;

	bool bSetPos;
	FXYPOINT pos;

	CXI_IMAGE* pImg;
};

// picture
class CXI_CHECKBUTTONS : public CINODE
{
public:
	CXI_CHECKBUTTONS();
	~CXI_CHECKBUTTONS();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	uint32_t MessageProc(long msgcode, MESSAGE & message);

	virtual bool GetInternalNameList( std::vector<std::string>& aStr );
	virtual void SetInternalName(std::string& sName );

protected:
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);
	void	AddButton( const char* pcText, bool bDisable, bool bSelect );
	void	ChangeText( long nButtonNum, const char* pcText );

	void	CheckMouseClick( const FXYPOINT & pntMouse );
	void	SetButtonOn( long nButtonNum );
	void	SetButtonOff( long nButtonNum );
	void	SetAllButtonsToOff();
	void	SetCheckToButton( long nButtonNum, bool bCheck );

	void	UpdateAllTextInfo();
	void	UpdateTextInfo( long nButtonNum );
	void	WriteToAttributeButtonState( long nButtonIndex );

	bool m_bExclusiveChoose;

	long m_nFontNum;
	float m_fFontScale;
	uint32_t m_dwNormalFontColor;
	uint32_t m_dwSelectFontColor;
	uint32_t m_dwDisableFontColor;
	FXYRECT m_frTextOffset;
	float m_fTextLineHeight;
	float m_fTextSectionInterval;
	long m_nFontAlignment;

	bool m_bClickIntoTextActive;
	bool m_bIndividualPos;
	std::vector<ButtonDescribe*> m_aButton;
	long m_nEditableSectionIndex;

	FXYPOINT m_fpIconSize;
	FXYPOINT m_fpIconOffset;
	std::string m_sIconGroupName;
	//
	std::string m_sNormalPicture;
	uint32_t m_dwNormalPicColor;
	//
	std::string m_sSelectPicture;
	uint32_t m_dwSelectPicColor;
	//
	std::string m_sDisablePicture;
	uint32_t m_dwDisablePicColor;
};

#endif