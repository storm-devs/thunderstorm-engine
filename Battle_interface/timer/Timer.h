#ifndef _BI_TIMER_H_
#define _BI_TIMER_H_

#include "..\..\common_h\dx9render.h"
#include "..\..\common_h\defines.h"
#include <string>

class BIImageRender;
class IBIImage;

class BITimer : public ENTITY
{
public:
	BITimer();
	~BITimer();

	bool Init();
	void Realize(dword delta_time);
	dword _cdecl ProcessMessage(MESSAGE & message);

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
