#ifndef _INFO_HANDLER_H_
#define _INFO_HANDLER_H_

#include "../Common_h/dx9render.h"
#include "../Common_h/Entity.h"

class InfoHandler : public Entity
{
	VDX9RENDER * m_rs;

public:
	InfoHandler();
	~InfoHandler();
	bool	Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}


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
