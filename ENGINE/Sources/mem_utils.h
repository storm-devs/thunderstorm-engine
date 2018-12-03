#ifndef _MEM_UTILS_H_
#define _MEM_UTILS_H_

#include <cstdint>

#define DEBUGCLASSES

#define SMALL_BLOCKS_LIMIT	256
#define MEDIUM_BLOCKS_LIMIT	256
#define MEDIUM_BLOCK_MSIZE  65536

struct MEM_USAGE_INFO_BLOCK
{
	char * pFileName;
	uint32_t  nLine;
	uint32_t  nCurrentAllocated;
	uint32_t  nCurrentBlocks;
	uint32_t  nMaxAllocated;
	uint32_t  nMaxBlocks;


	uint32_t  nTotalAllocated;
	uint32_t  nTotalBlocks;
};

struct SBSUNIT
{
	uint32_t nCurrent;
	uint32_t nMax;
	uint32_t nB2TRatio;
};

class MEM_USAGE_INFO
{
	MEM_USAGE_INFO_BLOCK * pMemBL;
	uint32_t nMemBLNum;
public:
	uint32_t nTotalAllocated;
	uint32_t nCurrentAllocated;
	uint32_t nMaxSimAllocated;
	uint32_t nTotalBlocks;
	uint32_t nCurrentBlocks;
	uint32_t nMaxSimBlocks;

	uint32_t nTestBlocks;

	SBSUNIT nBlockTableSBS[SMALL_BLOCKS_LIMIT];
	SBSUNIT nBlockTableMBS[MEDIUM_BLOCKS_LIMIT];

	uint32_t nTimePeriod;
	uint32_t nTimeCounter;

	 MEM_USAGE_INFO();
	~MEM_USAGE_INFO();
	void Allocate(char * pFileName, uint32_t nLine, uint32_t nMemSize);
	void Resize(char * pFileName, uint32_t nLine, uint32_t nMemSize, 
		char * pOldFileName, uint32_t nOldLine, uint32_t nOldMemSize);
	void Free(char * pFileName, uint32_t nLine, uint32_t nMemSize);
	void Report();
	void Register(char * pFileName, uint32_t nLine, uint32_t nMemSize);
	void Unregister(char * pFileName, uint32_t nLine, uint32_t nMemSize);

	void ProcessTime(uint32_t time);
	void UpdateMemoryProfile(char * pFileName);

};

class MEM_ALLOC_ADDRESS
{
public:
	struct SOURCE_DESC
	{
		SOURCE_DESC(){pFileName = nullptr; dwLine = 0;};
		char * pFileName;
		uint32_t dwLine;
	};
	SOURCE_DESC * pData;
	uint32_t dwRecordsNum;
	uint32_t dwBufferSize;

	MEM_ALLOC_ADDRESS();
	~MEM_ALLOC_ADDRESS();
	uint32_t  GetAddress(const char * pFileName, uint32_t dwLine);
	char * GetSource(uint32_t dwAddress, uint32_t * dwLine);
};

#endif