#ifndef _SCRSHOTER_H_
#define _SCRSHOTER_H_

#include "../../Common_h/dx9render.h"

class SCRSHOTER : public ENTITY
{
	VDX9RENDER  *rs;

	struct SAVETEXTURES
	{
		char * fileName;
		char * dataString;
		IDirect3DTexture9 * m_pTex;
		SAVETEXTURES * next;
	};

public:
	 SCRSHOTER();
	~SCRSHOTER();
	void SetDevice();
	bool Init();
    void Execute(uint32_t Delta_Time);
	void Realize(uint32_t Delta_Time);
    uint32_t _cdecl ProcessMessage(MESSAGE & message);

private:
	bool MakeScreenShot();
	IDirect3DTexture9 * FindSaveTexture(char * fileName);
	char * FindSaveData(char * fileName);
	IDirect3DTexture9 * AddSaveTexture(char * dirName, char * fileName);
	void DelSaveTexture(char * fileName);
	IDirect3DTexture9 * GetTexFromSave(char * fileName, char **pDatStr);

	IDirect3DTexture9 * m_pScrShotTex;
	SAVETEXTURES * m_list;
};

#endif
