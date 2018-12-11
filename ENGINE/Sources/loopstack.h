#ifndef _LOOPSTACK_H_
#define _LOOPSTACK_H_

//#include <windows.h>
#include "token.h"
#include <vector>

struct LOOPBLOCK
{
	uint32_t start;
	uint32_t stop;
	S_TOKEN_TYPE type;
};

class LOOPSTACK
{
	std::vector<LOOPBLOCK> pBlock;
	long Block_Num;
	long Block_Size;
public:
	 LOOPSTACK();
	void Push(LOOPBLOCK block);
	bool Pop(LOOPBLOCK * pblock);
	bool Read(LOOPBLOCK * pblock);


};
#endif