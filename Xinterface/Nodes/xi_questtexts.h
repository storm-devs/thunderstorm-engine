#ifndef _XI_QUESTTEXTS_H_
#define _XI_QUESTTEXTS_H_

#include "..//inode.h"

class CXI_QUESTTEXTS : public CINODE
{
public:
	CXI_QUESTTEXTS();
	~CXI_QUESTTEXTS();

	void	Draw(bool bSelected,uint32_t Delta_Time);
	bool	Init(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2, VDX9RENDER *rs, XYRECT &hostRect, XYPOINT &ScreenSize);
	void	ReleaseAll();
	int		CommandExecute(int wActCode);
	bool	IsClick(int buttonID,long xPos,long yPos);
	void	MouseThis(float fX, float fY) {}
	void	ChangePosition( XYRECT &rNewPos );
	void	SaveParametersToIni();
	uint32_t _cdecl MessageProc(long msgcode, MESSAGE & message);

	void	StartQuestShow(ATTRIBUTES * pA,int qn);

	float	GetLineStep();
	void	ScrollerChanged(float fPos);

protected:
	bool	GetLineNext(int fontNum,char* &pInStr,char* buf,int bufSize);
	void	LoadIni(INIFILE *ini1,char *name1, INIFILE *ini2,char *name2);
	void	ReleaseStringes();
	void	GetStringListForQuestRecord( std::vector<std::string> & asStringList, const char* pcRecText, const char* pcUserData );

	long	m_idFont;
	uint32_t	m_dwNonCompleteColor;
	uint32_t	m_dwCompleteColor;

	int		m_allStrings;
	int		m_vertOffset;

	struct STRING_DESCRIBER
	{
		int		strNum;
		char*	lineStr;
		bool	complete;
		STRING_DESCRIBER* next;
		STRING_DESCRIBER* prev;
		STRING_DESCRIBER* Add(char* ls,bool complete);
		STRING_DESCRIBER(char* ls);
	};
	STRING_DESCRIBER* m_listRoot;
	STRING_DESCRIBER* m_listCur;
	int		m_nAllTextStrings;
};

#endif
