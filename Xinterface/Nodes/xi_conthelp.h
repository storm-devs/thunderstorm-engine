#ifndef _XI_CONTEXTHELP_H_
#define _XI_CONTEXTHELP_H_

#include "../inode.h"

struct HELPENTITY
{
    char * nodeName;
    CINODE * pNode;
    long idHelpString;
};

class CXI_CONTEXTHELP : public CINODE
{
public:
	 CXI_CONTEXTHELP();
	~CXI_CONTEXTHELP();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	uint32_t MessageProc(long msgcode, MESSAGE & message);
    void    ChangeNode(CINODE * pNode);
    void    SetTempHelp(const char * string);

    long    m_helpQuantity;
    HELPENTITY * m_pHelpList;

protected:
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);
    char *  GetCurrentHelpString(uint32_t deltaTime);

	uint32_t   m_dwColor;
    uint32_t   m_dwBorderColor;
    uint32_t   m_dwFontColor;

    bool    m_bBorder;
    long    m_offset;
    long    m_nHelpWidth;

    HELPENTITY * m_curHelp;
    long    m_defaultString;

    long    m_nMaxDelayCounter;
    long    m_nCurDelayCounter;
    long    m_idTempString;
    char*   m_sTempString;

    long    m_idFont;
	float	m_fCurScale;
	float	m_fMaxScale;

	XI_NOTEX_VERTEX m_pVert[4];
    RS_LINE m_pLines[8];
};

#endif
