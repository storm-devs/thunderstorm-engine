#ifndef _INPUT_H_
#define _INPUT_H_

class IINPUT
{
public:
	IINPUT(){};
	virtual ~IINPUT(){};
	virtual float GetKeyState(uint32_t key_code, uint32_t * value = nullptr)= 0;
	virtual void ProcessKeyState(){};
	virtual void SetKeyState(uint32_t key_code, uint32_t * value){};
};

#endif