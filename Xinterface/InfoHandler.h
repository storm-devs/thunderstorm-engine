#ifndef _INFO_HANDLER_H_
#define _INFO_HANDLER_H_

#include "../Common_h/dx9render.h"

class InfoHandler : public ENTITY
{
	VDX9RENDER * m_rs;

public:
	InfoHandler();
	~InfoHandler();
	bool	Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t _cdecl ProcessMessage(MESSAGE & message);

protected:
	void	StringToBufer(char * outStr, int sizeBuf, char * inStr, int copySize);
	char *	GetCutString( char * pstr, int nOutWidth, float fScale );
	bool	DoPreOut();

	IDirect3DSurface9 * m_pSurface;
	IDirect3DSurface9 * m_pRenderTarget;

	/*long	m_idVBuf;

	int		m_dwOutputWidth;
	int		m_nOutCenterX, m_nOutCenterY;

	DWORD	m_dwBackFillColor;
	DWORD	m_dwFrontFillColor;

	long	m_idFont;

	struct	STRING_LIST
	{
		int x,y;
		char * strData;
		STRING_LIST	* next;
	} * m_strList;*/
};

#endif
