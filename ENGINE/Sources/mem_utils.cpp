#include "mem_utils.h"
#include "system_log.h"
#include "../../Common_h/vapi.h"
#include "../../Common_h/defines.h"

extern VAPI * api;

MEM_USAGE_INFO::MEM_USAGE_INFO()
{
	nTotalAllocated = 0;
	nCurrentAllocated = 0;
	nMaxSimAllocated = 0;
	nTotalBlocks = 0;
	nCurrentBlocks = 0;
	nMaxSimBlocks = 0;

	nTestBlocks = 0;

	PZERO(&nBlockTableSBS,sizeof(nBlockTableSBS));
	PZERO(&nBlockTableMBS,sizeof(nBlockTableMBS));

	pMemBL = (MEM_USAGE_INFO_BLOCK *)malloc(sizeof(MEM_USAGE_INFO_BLOCK));
	nMemBLNum = 1;
	pMemBL[0].nLine = 0;
	const auto len = sizeof "unknown file" + 1;
	pMemBL[0].pFileName = (char *)malloc(len);
	strcpy_s(pMemBL[0].pFileName, len, "unknown file");
	pMemBL[0].nTotalAllocated = 0;
	pMemBL[0].nTotalBlocks = 0;
	pMemBL[0].nCurrentAllocated = 0;
	pMemBL[0].nCurrentBlocks = 0;
	pMemBL[0].nMaxAllocated = 0;
	pMemBL[0].nMaxBlocks = 0;

	nTimePeriod = 1000;
	nTimeCounter = 0;
}

MEM_USAGE_INFO::~MEM_USAGE_INFO()
{
	uint32_t n;
	if(pMemBL)
	{
		for(n=0;n<nMemBLNum;n++)
		{
			free(pMemBL[n].pFileName);
		}
		free(pMemBL);
	}
}


void MEM_USAGE_INFO::Register(char * pFileName, uint32_t nLine, uint32_t nMemSize)
{
	uint32_t n;

	if(pFileName == nullptr)
	{
		n = 0;
		pMemBL[n].nTotalBlocks++;
		pMemBL[n].nTotalAllocated += nMemSize;

		pMemBL[n].nCurrentAllocated += nMemSize;
		pMemBL[n].nCurrentBlocks++;
		if(pMemBL[n].nMaxAllocated < pMemBL[n].nCurrentAllocated) pMemBL[n].nMaxAllocated = pMemBL[n].nCurrentAllocated;
		if(pMemBL[n].nMaxBlocks < pMemBL[n].nCurrentBlocks) pMemBL[n].nMaxBlocks = pMemBL[n].nCurrentBlocks;

		return;
	}

	for(n=0;n<nMemBLNum;n++)
	{
		if(pMemBL[n].nLine != nLine) continue;
		if(strcmp(pMemBL[n].pFileName,pFileName)!=0) continue;
		pMemBL[n].nTotalBlocks++;
		pMemBL[n].nTotalAllocated += nMemSize;
		pMemBL[n].nCurrentAllocated += nMemSize;
		pMemBL[n].nCurrentBlocks++;
		if(pMemBL[n].nMaxAllocated < pMemBL[n].nCurrentAllocated) pMemBL[n].nMaxAllocated = pMemBL[n].nCurrentAllocated;
		if(pMemBL[n].nMaxBlocks < pMemBL[n].nCurrentBlocks) pMemBL[n].nMaxBlocks = pMemBL[n].nCurrentBlocks;

		return;
	}
	n = nMemBLNum;
	nMemBLNum++;
	pMemBL = (MEM_USAGE_INFO_BLOCK *)realloc(pMemBL,nMemBLNum*sizeof(MEM_USAGE_INFO_BLOCK));
	pMemBL[n].nLine = nLine;
	const auto len = strlen(pFileName) + 1;
	pMemBL[n].pFileName = (char *)malloc(len);
	strcpy_s(pMemBL[n].pFileName, len, pFileName);
	pMemBL[n].nTotalBlocks = 1;
	pMemBL[n].nTotalAllocated = nMemSize;
	pMemBL[n].nCurrentAllocated = nMemSize;
	pMemBL[n].nCurrentBlocks = 1;
	pMemBL[n].nMaxAllocated  = nMemSize;
	pMemBL[n].nMaxBlocks = 1;

}

void MEM_USAGE_INFO::Unregister(char * pFileName, uint32_t nLine, uint32_t nMemSize)
{
	uint32_t n;

	if(pFileName == nullptr)
	{
		n = 0;
		pMemBL[n].nCurrentAllocated -= nMemSize;
		pMemBL[n].nCurrentBlocks--;
		return;
	}

	for(n=0;n<nMemBLNum;n++)
	{
		if(pMemBL[n].nLine != nLine) continue;
		if(strcmp(pMemBL[n].pFileName,pFileName)!=0) continue;
		if(pMemBL[n].nTotalBlocks == 0)
		{
			pMemBL[n].nTotalBlocks = 0;
		}
		pMemBL[n].nCurrentAllocated -= nMemSize;
		pMemBL[n].nCurrentBlocks--;

		return;
	}
}


void MEM_USAGE_INFO::Allocate(char * pFileName, uint32_t nLine, uint32_t nMemSize)
{
	//nTestBlocks++;
	Register(pFileName,nLine,nMemSize);

	nTotalBlocks++;
	nTotalAllocated += nMemSize;

	
	nCurrentBlocks++;
	if(nCurrentBlocks > nMaxSimBlocks) nMaxSimBlocks = nCurrentBlocks;

	nCurrentAllocated += nMemSize;
	if(nCurrentAllocated > nMaxSimAllocated) nMaxSimAllocated = nCurrentAllocated;

	if(nMemSize < SMALL_BLOCKS_LIMIT) 
	{
		nBlockTableSBS[nMemSize].nCurrent++;
		if(nBlockTableSBS[nMemSize].nCurrent > nBlockTableSBS[nMemSize].nMax)
			nBlockTableSBS[nMemSize].nMax = nBlockTableSBS[nMemSize].nCurrent;
	}

	if(nMemSize < MEDIUM_BLOCK_MSIZE && nMemSize >= SMALL_BLOCKS_LIMIT) 
	{
		uint32_t nIndex;
		nIndex = nMemSize>>8;
		nBlockTableMBS[nIndex].nCurrent++;
		if(nBlockTableMBS[nIndex].nCurrent > nBlockTableMBS[nIndex].nMax)
			nBlockTableMBS[nIndex].nMax = nBlockTableMBS[nIndex].nCurrent;
	}

	


}

void MEM_USAGE_INFO::Resize(char * pFileName, uint32_t nLine, uint32_t nMemSize, 
		char * pOldFileName, uint32_t nOldLine, uint32_t nOldMemSize)
{
	if(nMemSize < SMALL_BLOCKS_LIMIT) 
	{
		nBlockTableSBS[nMemSize].nCurrent++;
		if(nBlockTableSBS[nMemSize].nCurrent > nBlockTableSBS[nMemSize].nMax)
			nBlockTableSBS[nMemSize].nMax = nBlockTableSBS[nMemSize].nCurrent;
	}
	
	if(nOldMemSize < SMALL_BLOCKS_LIMIT) nBlockTableSBS[nOldMemSize].nCurrent--;

	if(nMemSize < MEDIUM_BLOCK_MSIZE && nMemSize >= SMALL_BLOCKS_LIMIT) 
	{
		uint32_t nIndex;
		nIndex = nMemSize>>8;
		nBlockTableMBS[nIndex].nCurrent++;
		if(nBlockTableMBS[nIndex].nCurrent > nBlockTableMBS[nIndex].nMax)
			nBlockTableMBS[nIndex].nMax = nBlockTableMBS[nIndex].nCurrent;
	}

	if(nOldMemSize < MEDIUM_BLOCK_MSIZE && nOldMemSize >= SMALL_BLOCKS_LIMIT) 
	{
		uint32_t nIndex;
		nIndex = nOldMemSize>>8;
		nBlockTableMBS[nIndex].nCurrent--;
	}
	 

	Unregister(pOldFileName,nOldLine,nOldMemSize);
	Register(pFileName,nLine,nMemSize);
	

	if(nMemSize > nOldMemSize)
	{
		nTotalAllocated += (nMemSize - nOldMemSize);
		nCurrentAllocated += (nMemSize - nOldMemSize);
		if(nCurrentAllocated > nMaxSimAllocated) nMaxSimAllocated = nCurrentAllocated;
	}
	else
	{
		nTotalAllocated -= (nOldMemSize - nMemSize);
		nCurrentAllocated -= (nOldMemSize - nMemSize);
	}
}

void MEM_USAGE_INFO::Free(char * pFileName, uint32_t nLine, uint32_t nMemSize)
{
	//nTestBlocks--;
	if(nCurrentBlocks == 0)
	{
		bool a;
		a = true;
	}//*/
	nCurrentBlocks--;
	
	nCurrentAllocated -= nMemSize;

	if(nMemSize < SMALL_BLOCKS_LIMIT) nBlockTableSBS[nMemSize].nCurrent--;

	if(nMemSize < MEDIUM_BLOCK_MSIZE  && nMemSize >= SMALL_BLOCKS_LIMIT) 
	{
		uint32_t nIndex;
		nIndex = nMemSize>>8;
		nBlockTableMBS[nIndex].nCurrent--;
	}

	Unregister(pFileName,nLine,nMemSize);
}

void MEM_USAGE_INFO::Report()
{
	uint32_t n;
	trace("-------------------------------------------------------------------");
	trace("MEM INFO:");
	trace("");
	trace("Allocated:");
	trace("           Total  Mem : %d",nTotalAllocated);
	trace("           Blocks     : %d",nTotalBlocks);
	trace("");
	trace("           Simultaneously");
	trace("");
	trace("           Max Mem    : %d",nMaxSimAllocated);
	trace("           Max Blocks : %d",nMaxSimBlocks);
	trace("");
	trace("");
	trace("SBS Table (blocks):");
	uint32_t nSBTotal,nSBTotalNum;
	nSBTotal = 0;
	nSBTotalNum = 0;
	for(n=0;n<SMALL_BLOCKS_LIMIT;n++)
	{
		nSBTotal += nBlockTableSBS[n].nMax*n;
		nSBTotalNum += nBlockTableSBS[n].nMax;
		trace("    [%d] : %d  summ[ %d ]  b2tr : %d",n,nBlockTableSBS[n].nMax,nBlockTableSBS[n].nMax*n,nBlockTableSBS[n].nB2TRatio);
	}

	trace("");
	trace("SB Total : %d in %d blocks",nSBTotal,nSBTotalNum);


	trace("MBS Table (blocks):");
	nSBTotal = 0;
	nSBTotalNum = 0;
	for(n=0;n<MEDIUM_BLOCKS_LIMIT;n++)
	{
		nSBTotal += nBlockTableMBS[n].nMax*n*256;
		nSBTotalNum += nBlockTableMBS[n].nMax;
		trace("    [%d - %d] : %d  summ[ %d ] ",n*256,n*256+255,nBlockTableMBS[n].nMax,nBlockTableMBS[n].nMax*n*255);
	}

	trace("");
	trace("MB Total : %d in %d blocks",nSBTotal,nSBTotalNum);

	trace("");
	trace("Mem Usage By Location:");
	trace("");
	trace("Sorted By Size:");
	uint32_t msize;
	uint32_t mn,i;
	for(i=0;i<nMemBLNum;i++)
	{
		msize = 0;
		mn = 0;
		for(n=0;n<nMemBLNum;n++)
		{
			if(msize < pMemBL[n].nMaxAllocated)
			{
				mn = n;
				msize = pMemBL[n].nMaxAllocated;
			}
			
		}
		trace("%d in %d blocks  : %s  line %d",pMemBL[mn].nMaxAllocated,pMemBL[mn].nMaxBlocks,pMemBL[mn].pFileName,pMemBL[mn].nLine);
		pMemBL[mn].nMaxAllocated = 0;
	}

	trace("-------------------------------------------------------------------");

}

void MEM_USAGE_INFO::ProcessTime(uint32_t time)
{
	uint32_t n;
	nTimeCounter += time;
	if(nTimeCounter < nTimePeriod) return;
	nTimeCounter = 0;

	for(n=0;n<SMALL_BLOCKS_LIMIT;n++)
	{
		nBlockTableSBS[n].nB2TRatio = (nBlockTableSBS[n].nB2TRatio + nBlockTableSBS[n].nCurrent)/2;
	}
}

#define MEM_PROFILE_BLOCKS_NUM	64

void MEM_USAGE_INFO::UpdateMemoryProfile(char * pFileName)
{
	HANDLE fh;
	uint32_t dwR;
	uint32_t n;
	uint32_t nProfileBlocks;
	fh = api->fio->_CreateFile(pFileName,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
	if(fh == INVALID_HANDLE_VALUE)
	{
		// create new profile information file
		fh = api->fio->_CreateFile(pFileName,GENERIC_WRITE,FILE_SHARE_READ,CREATE_ALWAYS);
		if(fh == INVALID_HANDLE_VALUE) return;
	
		nProfileBlocks = MEM_PROFILE_BLOCKS_NUM;
		
		api->fio->_WriteFile(fh,&nProfileBlocks,sizeof(nProfileBlocks),&dwR);

		for(n=0;n<MEM_PROFILE_BLOCKS_NUM;n++)
		{
			api->fio->_WriteFile(fh,&nBlockTableSBS[n].nMax,sizeof(nBlockTableSBS[n].nMax),&dwR);
		}
		api->fio->_CloseHandle(fh);
		
		return;
	}

	uint32_t * pTempProfileInfo;
	uint32_t nProfileValue;
	api->fio->_ReadFile(fh,&nProfileBlocks,sizeof(nProfileBlocks),&dwR);
	pTempProfileInfo = new uint32_t[nProfileBlocks];
	api->fio->_ReadFile(fh,pTempProfileInfo,nProfileBlocks*sizeof(uint32_t),&dwR);
	api->fio->_CloseHandle(fh);

	//fh = api->fio->_CreateFile(pFileName,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
	//if(fh == INVALID_HANDLE_VALUE) return;

	fh = api->fio->_CreateFile(pFileName,GENERIC_WRITE,FILE_SHARE_READ,CREATE_ALWAYS);
	if(fh == INVALID_HANDLE_VALUE) return;

	nProfileBlocks = MEM_PROFILE_BLOCKS_NUM;
	
	api->fio->_WriteFile(fh,&nProfileBlocks,sizeof(nProfileBlocks),&dwR);

	for(n=0;n<MEM_PROFILE_BLOCKS_NUM;n++)
	{
		if(n < nProfileBlocks) //~!~
		{
			if(nBlockTableSBS[n].nMax > pTempProfileInfo[n]) nProfileValue = nBlockTableSBS[n].nMax;
			else nProfileValue = pTempProfileInfo[n];
		} 
		else nProfileValue = nBlockTableSBS[n].nMax;
		api->fio->_WriteFile(fh,&nProfileValue,sizeof(nBlockTableSBS[n].nMax),&dwR);
	}
	api->fio->_CloseHandle(fh);
}

#ifdef DEBUGCLASSES

MEM_ALLOC_ADDRESS::MEM_ALLOC_ADDRESS()
{
	pData = nullptr; 
	dwRecordsNum = 0;
	dwBufferSize = 0;
/*	dwBufferSize = 128;
	pData = (SOURCE_DESC *)malloc(dwBufferSize * sizeof(SOURCE_DESC));
	if(!pData) throw "MEM_ALLOC_ADDRESS::MEM_ALLOC_ADDRESS()";
	memset(pData,0,dwBufferSize * sizeof(SOURCE_DESC));
*/
}

MEM_ALLOC_ADDRESS::~MEM_ALLOC_ADDRESS()
{
	uint32_t n;
	if(pData)
	{
		for(n=0;n<dwRecordsNum;n++)
		{
			if(pData[n].pFileName) free(pData[n].pFileName);
		}
		free(pData);
	}
	pData = nullptr; 
	dwRecordsNum = 0;
}

uint32_t  MEM_ALLOC_ADDRESS::GetAddress(const char * pFileName, uint32_t dwLine)
{
	//return 0xffffffff;
	uint32_t n;
	if(pFileName == nullptr) return 0xffffffff;
	for(n=0;n<dwRecordsNum;n++)
	{
		if(pData[n].dwLine != dwLine) continue;
		if(_stricmp(pData[n].pFileName,pFileName)!=0) continue;
		return n;
	}
	while((dwRecordsNum + 1) >= dwBufferSize)
	{
		uint32_t offset;
		if(dwBufferSize == 0)
		{
			dwBufferSize = 128;
			pData = (SOURCE_DESC *)malloc(dwBufferSize * sizeof(SOURCE_DESC));
			if(!pData) throw "MEM_ALLOC_ADDRESS::::GetAddress";
			//memset(pData,0,dwBufferSize * sizeof(SOURCE_DESC));
		}
		else
		{
			offset = dwBufferSize * sizeof(SOURCE_DESC);
			dwBufferSize = dwBufferSize * 2;
			pData = (SOURCE_DESC *)realloc(pData,dwBufferSize * sizeof(SOURCE_DESC));
			if(!pData) throw "MEM_ALLOC_ADDRESS::GetAddress";
			//memset(pData + offset,0,offset);
		}
	}
	pData[dwRecordsNum].dwLine = dwLine;
	const auto len = strlen(pFileName) + 1;
	pData[dwRecordsNum].pFileName = (char *)malloc(len);
	if(!pData[dwRecordsNum].pFileName) throw "MEM_ALLOC_ADDRESS::GetAddress";
	strcpy_s(pData[dwRecordsNum].pFileName, len, pFileName);
	dwRecordsNum++;
	return dwRecordsNum - 1;
}

char * MEM_ALLOC_ADDRESS::GetSource(uint32_t dwAddress, uint32_t * dwLine)
{
	if(dwAddress >= dwRecordsNum) 
	{
		if(dwLine) *dwLine = 0;
		return "Bad memory address";
	}
	if(dwLine) *dwLine = pData[dwAddress].dwLine;
	return pData[dwAddress].pFileName;
}	

#endif