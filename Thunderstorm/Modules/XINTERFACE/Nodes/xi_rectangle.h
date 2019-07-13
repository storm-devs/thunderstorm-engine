#ifndef _XI_RECTANGLE_H_
#define _XI_RECTANGLE_H_

#include "../inode.h"

class CXI_RECTANGLE : public CINODE
{
public:
	 CXI_RECTANGLE();
	~CXI_RECTANGLE();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	uint32_t MessageProc(long msgcode, MESSAGE & message);
	bool	IsGlowChanged() {return true;}

protected:
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);
	void	UpdateColors();

	uint32_t m_dwTopColor;
	uint32_t m_dwBottomColor;
	uint32_t m_dwLeftColor;
	uint32_t m_dwRightColor;
    bool  m_bBorder;
    uint32_t m_dwBorderColor;

	XI_NOTEX_VERTEX m_pVert[4];
};

#endif
