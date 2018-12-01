#ifndef _CONTROL_KEYBUFFER_H_
#define _CONTROL_KEYBUFFER_H_

#include "..\common_h\vmodule_api.h"
#include "..\common_h\controls.h"

struct ControlKeyBuffer
{
public:
	ControlKeyBuffer();
	~ControlKeyBuffer();

	void Reset();
	void AddKey( long nKeyCode, UINT uScanCode, bool bSystem );

	long GetBufferLength() {return m_nBufLen;}
	const KeyDescr* c_str() {return m_pcBuffer;}

	long m_nBufLen;
	KeyDescr m_pcBuffer[512];
};

#endif
