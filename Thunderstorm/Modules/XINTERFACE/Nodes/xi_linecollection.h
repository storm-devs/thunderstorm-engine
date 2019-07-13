#ifndef _XI_LINECOLLECTION_H
#define _XI_LINECOLLECTION_H

#include "../inode.h"

// text collection
class CXI_LINECOLLECTION : public CINODE
{
public:
	 CXI_LINECOLLECTION();
	~CXI_LINECOLLECTION();

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

protected:
    std::vector<RS_LINE> m_aLines;
};

#endif