#ifndef _BI_TIMER_H_
#define _BI_TIMER_H_

#include <string>
#include "Entity.h"
#include "../bi_defines.h"

class BIImageRender;
class IBIImage;

class BITimer : public Entity
{
public:
	BITimer();
	~BITimer();

	bool Init();
	void Realize(uint32_t delta_time);
	uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::execute:
		//	Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}

protected:
	bool ReadAndCreate();
	void SetBeginData();
	void Release();

	void OpenTimer( float fTime, const char* pcEventName );
	void CloseTimer( bool bTimeOut );

protected: // data
	float m_fCurTimerCounter;
	float m_fMaxTimerCounter;
	std::string m_sEventName;

	VDX9RENDER* m_pRender;
	BIImageRender* m_pImgRndr;
	IBIImage* m_pBackImage;
	IBIImage* m_pForeImage;
};

#endif
