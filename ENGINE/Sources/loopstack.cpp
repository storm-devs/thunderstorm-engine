#include "loopstack.h"
#include "../../Common_h/defines.h"

LOOPSTACK::LOOPSTACK()
{
	Block_Num = 0;
	Block_Size = 0;
}

void LOOPSTACK::Push(LOOPBLOCK block)
{
	Block_Num++;
	if(Block_Num >= Block_Size)
	{
		pBlock.resize(Block_Num);
		Block_Size = Block_Num;
		pBlock[Block_Num - 1] = block;
	}
}

bool LOOPSTACK::Pop(LOOPBLOCK * _pblock)
{
	if(Block_Num == 0) return false;
	if(_pblock) memcpy(_pblock,&pBlock[Block_Num - 1],sizeof(LOOPBLOCK));
	Block_Num--;
	return true;
}

bool LOOPSTACK::Read(LOOPBLOCK * _pblock)
{
	if(Block_Num == 0) return false;
	if(_pblock) memcpy(_pblock,&pBlock[Block_Num - 1],sizeof(LOOPBLOCK));
	return true;
}