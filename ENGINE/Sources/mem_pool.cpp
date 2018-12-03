#include "mem_pool.h"

static const char ER_NOMEM[] = "No memory";

#define DWORDBITS		32
//#define POOLHEADERSIZE	0//1

BITLEVEL::~BITLEVEL()
{
	//if(pBits) delete pBits;
	if(pBits) free(pBits);
}

BITLEVEL::BITLEVEL(uint32_t _nManagedBits)
{
	nManagedBits = _nManagedBits;
	nDwordsNum = nManagedBits/DWORDBITS + 1;
	//pBits = (DWORD *) NEW DWORD[nDwordsNum];
	pBits = (uint32_t *) malloc(nDwordsNum * sizeof(uint32_t));
	memset(pBits,0,nDwordsNum*sizeof(uint32_t));
	nTestCounter = 0;
}

// return false if index beyond managed range
bool BITLEVEL::SetBit(uint32_t nIndex, bool & bDwordFull)
{
	uint32_t nOffset;
	uint32_t nDwordBitIndex;
	uint32_t nMask;
	
	if(nIndex >= nManagedBits) return false;


//	return true;

	nOffset = nIndex/DWORDBITS;
	nDwordBitIndex = nIndex - nOffset*DWORDBITS;
	nMask = 1;
	if(nDwordBitIndex) nMask = (nMask<<nDwordBitIndex);
	pBits[nOffset] = pBits[nOffset] | nMask;

	if(pBits[nOffset] == 0xffffffff) bDwordFull = true;
	else bDwordFull = false;

	return true;
}

void BITLEVEL::ClearBit(uint32_t nIndex)
{
	uint32_t nOffset;
	uint32_t nDwordBitIndex;
	uint32_t nMask;
	if(nIndex >= nManagedBits) return;

//	return;

	nOffset = nIndex/DWORDBITS;
	nDwordBitIndex = nIndex - nOffset*DWORDBITS;
	nMask = 1;
	if(nDwordBitIndex) nMask = (nMask<<nDwordBitIndex);

	
	pBits[nOffset] = pBits[nOffset] & (~nMask);
}
	
bool BITLEVEL::FindFree(uint32_t & nIndex)
{
	uint32_t n,i;
	uint32_t nMask;
	uint32_t nV;
	uint32_t nCounter;
	uint32_t nTest;

/*	if(nTestCounter < nManagedBits)
	{
		nIndex = nTestCounter;
		nTestCounter++;
		return true;
	} else return false;
//*/
	nCounter = 0;

	for(n=0;n<nDwordsNum;n++)
	{
		if(nCounter >= nManagedBits) return false;

		if(pBits[n] == 0xffffffff)
		{
			nCounter += DWORDBITS;
			continue;
		}
		nMask = 1;
		nV = pBits[n];
		for(i=0;i<DWORDBITS;i++)
		{
			if(nCounter >= nManagedBits) return false;
			nTest = nV & nMask;
			//if((nV & nMask) == 0)
			if(nTest == 0)
			{
				nIndex = n * DWORDBITS + i;
				if(nIndex >= nManagedBits) 
				{
					return false;
				}

				return true;
			}
			nMask = nMask<<1;
			nCounter++;
		}
		return false;
		
	}
	return false;
}


MEMPOOL::~MEMPOOL()
{
	uint32_t n;
	//if(pPoolData) delete pPoolData;
	if(pPoolData) free(pPoolData);

	if(pSTLevel)
	{
		for(n = 0; n < nSTLevelsNum;n++)
		{
			delete pSTLevel[n];
		}
		//delete pSTLevel;
		free(pSTLevel);
	}
}

MEMPOOL::MEMPOOL(uint32_t _nBlockSize, uint32_t _nBlocksNum)
{
	nBlockSize = _nBlockSize;
	nBlocksNum = _nBlocksNum;
	//pPoolData = (char *)NEW char[(nBlockSize + POOLHEADERSIZE)* nBlocksNum];
	pPoolData = (char *)malloc((nBlockSize + POOLHEADERSIZE)* nBlocksNum);
	if(pPoolData == nullptr) throw ER_NOMEM;

	nSTLevelsNum = 1;
	//pSTLevel = (BITLEVEL * *)NEW char[sizeof(BITLEVEL *) * nSTLevelsNum];
	pSTLevel = (BITLEVEL * *)malloc(sizeof(BITLEVEL *) * nSTLevelsNum);
	pSTLevel[0] = new BITLEVEL(nBlocksNum);
	nUsedBlocks = 0;
	nMissed = 0;

}

void * MEMPOOL::GetMemory()
{
	uint32_t nIndex;
	bool bDwordFull;
	if(!pSTLevel[0]->FindFree(nIndex)) 
	{
		if(nBlockSize == 10)
		{
			nBlockSize = 10;
		}//*/
		nMissed++;
		return nullptr;
	}
	pSTLevel[0]->SetBit(nIndex,bDwordFull);
	nUsedBlocks++;
	if(POOLHEADERSIZE != 0)
	*(pPoolData + nIndex * (nBlockSize + POOLHEADERSIZE)) = (uint8_t)nBlockSize;
	return pPoolData + nIndex * (nBlockSize + POOLHEADERSIZE) + POOLHEADERSIZE;
}

bool MEMPOOL::FreeMemory(void * pMem)
{
	uint32_t nIndex;
	if((uint32_t)pMem < (uint32_t)pPoolData) return false;
	nIndex = ((uint32_t)pMem - (uint32_t)pPoolData - POOLHEADERSIZE)/(nBlockSize + POOLHEADERSIZE);
	if(nIndex >= nBlocksNum) 
	{
		return false;
	}
	nUsedBlocks--;
	pSTLevel[0]->ClearBit(nIndex);
	return true;
}

bool MEMPOOL::IsInPool(void * pMem)
{
	if((uint32_t)pMem - POOLHEADERSIZE < (uint32_t)pPoolData) return false;
	if((uint32_t)pMem - POOLHEADERSIZE > (uint32_t)pPoolData + (nBlockSize + POOLHEADERSIZE)*(nBlocksNum - 1)) return false;
	return true;
}