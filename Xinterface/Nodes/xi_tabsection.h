#ifndef __XI_TABSECTION_H__
#define __XI_TABSECTION_H__

#include "../inode.h"

class CXI_TABSECTION : public CINODE
{
public:
	CXI_TABSECTION();
	~CXI_TABSECTION();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	uint32_t MessageProc(long msgcode, MESSAGE & message);

protected:
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);
	void	UpdateImage();

	std::string m_sIconGroupName;
	long m_idIconTexture;
	long m_idVBuf;
	long m_idIBuf;
	long m_nSubQ;

	long m_nIcon_TopBorder;
	long m_nIcon_BottomBorder;
	long m_nIcon_LeftArrow;
	long m_nIcon_RightArrow;
	long m_nIcon_LeftBookmarkPart;
	long m_nIcon_RightBookmarkPart;
	long m_nIcon_MiddleBookmarkPart;

	long m_nTopBorderHeight;
	long m_nBottomBorderHeight;
	long m_nTopBorderOffset;
	long m_nBottomBorderOffset;
	long m_nArrowOffset;
	long m_nBookmarkSpace;

	XYPOINT m_pntArrowSize;
	XYPOINT m_pntLeftBookmarkSize;
	XYPOINT m_pntRightBookmarkSize;
	XYPOINT m_pntMiddleBookmarkSize;

	uint32_t m_dwBorderColor;
	uint32_t m_dwArrowColor;
	uint32_t m_dwBookmarkColor;
};

#endif
