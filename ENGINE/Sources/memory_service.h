#ifndef _MEMORY_SERVICE_H_
#define _MEMORY_SERVICE_H_

/* --------------------------------------------------------------------------------------------
   Memory Tracer:
   -------------------------------------------------------------------------------------------- */

#include <cstdint>

#ifndef _XBOX
#include <windows.h>
#else
#include <xtl.h>
#endif

#include "..\..\common_h\vmemory_service.h"
#include "mem_utils.h"
#include "mem_pool.h"

struct CODESOURCE
{
	CODESOURCE(){pFileName = nullptr; line = 0xffffffff;};
	char * pFileName;
	uint32_t  line;
};

#define		M_LOCKED	1

//#pragma pack(push,1)

/*typedef struct 
{
	uint32_t  ctp;
	uint32_t  class_code;
} MEM_EXE_STATE;
*/
typedef struct 
{
//	uint32_t reference;
//	uint32_t check_sum;
//	MEM_EXE_STATE state;
	//DWORD a;
	//char b;
	uint32_t address;
	uint32_t data_size;
	char * link_L;
	char * link_R;
	//CODESOURCE cs;
	//word flags;	
	//word le;
	//byte sb1;
	//byte sb2;
} MEM_BLOCK;

#define SBCNUM	64

//#pragma pack(pop)


class MEMORY_SERVICE : public VMEMORY_SERVICE
{
protected:
//	MEM_EXE_STATE Exe_state;
	MEM_BLOCK * Mem_link;
	void * Search_Pointer;
	uint32_t Minimal_Pointer;
	uint32_t Maximal_Pointer;
	uint32_t dwTotalMemory;
	uint32_t dwTotalBlocks;
	
	MEMPOOL * * pMPool;
	uint32_t nMPoolClassesNum;

	bool bPoolOn;

public:

	uint32_t SBCounter[SBCNUM];

//#ifdef DEBUGCLASSES
	MEM_ALLOC_ADDRESS cMemAddress;
//#endif
	MEM_USAGE_INFO MemStat;
	bool bCollectInfo;

	MEMORY_SERVICE();
	~MEMORY_SERVICE();
	
	void * Allocate(long size);
	void * Reallocate(void * block_PTR,long size);
	void  Free(void * block_PTR);
	void * PoolAllocate(long size);
	bool PoolFree(void * block_PTR, uint32_t nBlockSize = 0xffffffff);
	uint32_t PoolFind(void * block_PTR);

	//void  IsolateMemBlock(MEM_BLOCK mem_block, MEM_BLOCK * mb_PTR);
	bool  ValidateBlock(void * block_PTR/*,MEM_EXE_STATE * lpBlockState*/);

	void  GlobalFree();
	void  SetState(uint16_t control_transfer_point, uint32_t module_class);
	//void  SetFlags(uint32_t _flags,void * block_PTR);
	//void  ClrFlags(uint32_t _flags,void * block_PTR);
	//uint32_t GetFlags(void * block_PTR);
	uint32_t GetBlockSize(void * block_PTR);

	//uint32_t RefInc(void * block_PTR);
	//uint32_t RefDec(void * block_PTR);
	//void  SetRef(void * block_PTR,uint32_t ref);
	//void Lock(void * block_PTR);
	//void Unlock(void * block_PTR);

	void * GetFirstPointer();
	void * GetNextPointer();
	bool GetPointerState(void * block_PTR/*,MEM_EXE_STATE * lpBlockState*/);
	
	uint32_t Allocated_memory_user;
	uint32_t Allocated_memory_system;
	uint32_t Blocks;

	void CollectInfo(bool bv){ bCollectInfo = bv;};

	void ProcessMemProfile(char * pFileName);

	char * GetFileName(void * pMemory);
	uint32_t GetFileLineCode(void * pMemory);

	void DumpMemoryState();
		
};

//#pragma pack(pop)

#endif