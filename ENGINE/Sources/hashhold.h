#ifndef _HASHHOLD_H_
#define _HASHHOLD_H_

#include "../../Common_h/vmodule_api.h"
#include <vector>

class HASHHOLD
{
	std::vector<std::vector<uint32_t>> pHashTable;
	uint32_t * pLineSize;
	uint32_t dwHashTableSize;
public:
	 HASHHOLD();
	~HASHHOLD();

	void  Release();
	bool  Init(uint32_t dwHashTableSize);
	bool  Add(uint32_t dwHashValue, uint32_t dwHoldValue);
	uint32_t GetCodesNum(uint32_t dwHashValue,uint32_t * & pHashLine);
	uint32_t MakeHash(const char * string, bool bCaseIndependent = false);
	
};

#endif