#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#include <cstdint>

#ifndef _XBOX
	#include <windows.h>
#else
	#include <xtl.h>
#endif

#define POOLHEADERSIZE	0//1

class BITLEVEL
{
	uint32_t * pBits;
	uint32_t nManagedBits;
	uint32_t nDwordsNum;
	uint32_t nTestCounter;
public:
	~BITLEVEL();
	 BITLEVEL(uint32_t nManagedBits);
	 bool SetBit(uint32_t nIndex, bool & bDwordFull);
	 void ClearBit(uint32_t nIndex);
	 bool FindFree(uint32_t & nIndex);
};
class MEMORY_SERVICE;

class MEMPOOL 
{
	friend MEMORY_SERVICE;
	uint32_t nBlockSize; 
	uint32_t nBlocksNum;
	uint32_t nSTLevelsNum;
	uint32_t nUsedBlocks;
	uint32_t nMissed;
	BITLEVEL * * pSTLevel;
	char * pPoolData;
public:
	~MEMPOOL();
	 MEMPOOL(uint32_t nBlockSize, uint32_t nBlocksNum);
	void * GetMemory();
	bool FreeMemory(void * pMem);
	bool IsInPool(void * pMem);
	uint32_t GetBlocksize(){return nBlockSize;};
};

#endif
