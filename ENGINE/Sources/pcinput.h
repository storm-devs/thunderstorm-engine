#ifndef _PCINPUT_H_
#define _PCINPUT_H_

#include <Windows.h>
#include "..\..\common_h\input.h"
#include "..\..\common_h\key_codes.h"

struct KEY_STATE
{
	uint32_t state;
	uint32_t value;
};

class PCINPUT : public IINPUT
{
	KEY_STATE KeyState[KEY_CODES_NUM];
	POINT Mouse_Pos;
	POINT Mouse_Delta;
public:
	 PCINPUT(){};
	~PCINPUT(){};
	float GetKeyState(uint32_t key_code, uint32_t * value);
	void ProcessKeyState();
	void SetKeyState(uint32_t key_code, uint32_t * value);
};

#endif
