#ifndef __XI_BUTTON_H__
#define __XI_BUTTON_H__

#include "../inode.h"

// picture
class CXI_BUTTON : public CINODE
{
public:
	CXI_BUTTON();
	~CXI_BUTTON();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	void	NotUsingTime(uint32_t Delta_Time) {nPressedDelay=0;}
	void	SetUsing(bool bUsing);
	uint32_t MessageProc(long msgcode, MESSAGE & message);

protected:
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);

protected:
	char    *m_sGroupName;
	long	m_idTex; // texture identity
	CVideoTexture *m_pTex;

	FXYRECT m_tRect;

	uint32_t	m_argbDisableColor;
	uint32_t   m_dwShadowColor;
	uint32_t   m_dwFaceColor;
	uint32_t	m_dwFontColor;
	uint32_t   m_dwLightColor;
	uint32_t   m_dwDarkColor;
	float	m_fBlindSpeed;
	float	m_fCurBlind;
	bool	m_bUpBlind;

	float   fXShadow;
	float   fYShadow;
	float   fXShadowPress;
	float   fYShadowPress;

	float   fXDeltaPress;
	float   fYDeltaPress;

	int		nPressedDelay;
	int     nMaxDelay;

	int		m_nFontNum;
	long	m_idString;
	int		m_dwStrOffset;
};

#endif