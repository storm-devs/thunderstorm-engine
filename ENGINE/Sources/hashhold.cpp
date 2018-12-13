#include "hashhold.h"

HASHHOLD::HASHHOLD()
{
	pLineSize = nullptr;
	dwHashTableSize = 0;
}

HASHHOLD::~HASHHOLD()
{
	Release();
}

void HASHHOLD::Release()
{
	pHashTable.clear();

	delete pLineSize; 
	pLineSize = nullptr;
	dwHashTableSize = 0;
}

bool HASHHOLD::Init(uint32_t _dwHashTableSize)
{
	Release();
	dwHashTableSize = _dwHashTableSize;
	pHashTable.resize(dwHashTableSize);
	pLineSize = (uint32_t *)new char[dwHashTableSize * sizeof(uint32_t)];
	if(!pLineSize) THROW;
	memset(pLineSize,0,dwHashTableSize * sizeof(uint32_t));
	return true;
}

bool HASHHOLD::Add(uint32_t dwHashValue, uint32_t dwHoldValue)
{
	uint32_t n;
	if(dwHashValue >= dwHashTableSize)
	{
		api->Trace("ERROR: hash value out of range");
		return false;
	}
	n = pLineSize[dwHashValue];
	pLineSize[dwHashValue]++;
	pHashTable[dwHashValue].resize(pLineSize[dwHashValue]);
	pHashTable[dwHashValue][n] = dwHoldValue;
	return true;
}

uint32_t HASHHOLD::GetCodesNum(uint32_t dwHashValue,uint32_t * & pHashLine)
{
	pHashLine = nullptr;
	if(dwHashValue >= dwHashTableSize)
	{
		api->Trace("ERROR: request for hash value out of range");
		return 0;
	}
	pHashLine = pHashTable[dwHashValue].data();
	return pLineSize[dwHashValue];
}

uint32_t HASHHOLD::MakeHash(const char * string, bool bCaseIndependent)
{
	uint32_t hval = 0;
	uint32_t g;
	char v;
	while(*string != 0)
	{
		v = *string++;
		if(bCaseIndependent)
		{
			if ('A' <= v && v <= 'Z') v += 'a' - 'A';	// case independent
		}
		hval = (hval<<4) + (unsigned long int)v;
		g = hval & ((unsigned long int) 0xf << (32 - 4));
		if(g != 0)
		{
			hval ^= g >> (32 - 8);
			hval ^= g;
		}
	}
	return hval;
}
