#ifndef _SCRSHOTER_H_
#define _SCRSHOTER_H_

#include "../../Common_h/dx9render.h"

class SCRSHOTER : public Entity
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
