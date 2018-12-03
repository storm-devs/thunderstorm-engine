#include "s_deftab.h"
#include <string.h>

#define DTMAKEHASHINDEX(x)	(x&0xff)

S_DEFTAB::S_DEFTAB()
{
	pTable = nullptr;
	Buffer_size = 0;
	Def_num = 0;
//	bKeepName = false;
	uint32_t n;
	for(n=0;n<DTHASHT_SIZE;n++)
	{
		HashLine[n].nNumElements = 0;
		HashLine[n].pElements = nullptr;
	}

}

S_DEFTAB::~S_DEFTAB()
{
	Release();
}

void  S_DEFTAB::Release()
{
	uint32_t n;
	if(pTable) 
	{
		for(n=0;n<Def_num;n++)	
		{ 
			if(pTable[n].name) delete pTable[n].name;	
			if(pTable[n].deftype == STRING) 
			{
				if(pTable[n].data4b != 0) delete ((char *)pTable[n].data4b);
			}
		}
		delete pTable; pTable = nullptr;
	}
	Buffer_size = 0;
	Def_num = 0;
	for(n=0;n<DTHASHT_SIZE;n++)
	{
		HashLine[n].nNumElements = 0;
		if(HashLine[n].pElements)  delete HashLine[n].pElements;
		HashLine[n].pElements = nullptr;
	}

}

bool S_DEFTAB::GetDef(DEFINFO& di,uint32_t def_code)
{
	if(def_code >= Def_num) return false;
	if(pTable[def_code].segment_id == INVALID_SEGMENT_ID) return false;
	di = pTable[def_code];
	return true;
}

bool S_DEFTAB::GetDefX(DEFINFO& di,uint32_t def_code)
{
	if(def_code >= Def_num) return false;
	di = pTable[def_code];
	return true;
}

uint32_t S_DEFTAB::AddDef(DEFINFO& di)
{
	uint32_t n;
	uint32_t hash;


	if(di.name == nullptr) return INVALID_DEF_CODE;
	hash = MakeHashValue(di.name);
	
	for(n=0;n<Def_num;n++)
	{
		if(pTable[n].hash == hash)
		if(_stricmp(pTable[n].name,di.name)==0)
		{
			// define with such name already registred,
			if(pTable[n].segment_id == INVALID_SEGMENT_ID)
			{
				// but not used
				pTable[n].data4b = di.data4b;
				pTable[n].deftype = di.deftype;
				pTable[n].segment_id = di.segment_id;
				UpdateHashTable(n,hash,true);
				
				return n;
			}
			else
			{
				// and already exist
				// this is 'define redefinition' error 
				return INVALID_DEF_CODE;
			}
		}
	}
	// function not found, add anew one
	// adjust buffer size
	if(Def_num >= Buffer_size)
	{
		Buffer_size += DEF_BUFFER_BLOCK_SIZE;
		pTable = (DEFINFO *)RESIZE(pTable,Buffer_size*sizeof(DEFINFO));
	}
	pTable[n].data4b = di.data4b;
	pTable[n].deftype = di.deftype;
	pTable[n].segment_id = di.segment_id;
	//pTable[Def_num] = di;
	pTable[Def_num].hash = hash;
	pTable[Def_num].name = nullptr;
	UpdateHashTable(Def_num,hash,true);
	if(true)//bKeepName)
	{
		if(di.name)
		{

			pTable[Def_num].name = NEW char[strlen(di.name) + 1];
			strcpy(pTable[Def_num].name,di.name);
		}
	}
	Def_num++;

	return (Def_num - 1);
}

uint32_t S_DEFTAB::MakeHashValue(const char * string)
{
	uint32_t hval = 0;
	uint32_t g;
	char v;
	while(*string != 0)
	{
		v = *string++;
		if ('A' <= v && v <= 'Z') v += 'a' - 'A';	// case independent
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

void S_DEFTAB::InvalidateBySegmentID(uint32_t segment_id)
{
	uint32_t n;
	for(n=0;n<Def_num;n++)
	{
		if(pTable[n].segment_id != segment_id) continue;
		UpdateHashTable(n,pTable[n].hash,false);
		pTable[n].segment_id = INVALID_SEGMENT_ID;
		if(pTable[n].deftype == STRING)
		{
			if(pTable[n].data4b)
			{
				delete ((char *)pTable[n].data4b);
			}
			pTable[n].data4b = 0;
		}
	}
}

uint32_t S_DEFTAB::FindDef(char * def_name)
{
	uint32_t n;
	uint32_t hash;
	if(def_name == nullptr) return INVALID_DEF_CODE;
	hash = MakeHashValue(def_name);
	
	uint32_t hash_index,ni;
	hash_index = DTMAKEHASHINDEX(hash);
	for(n=0;n<HashLine[hash_index].nNumElements;n++)
	{
		ni = HashLine[hash_index].pElements[n];
		if(pTable[ni].hash == hash) //return n;
		if(_stricmp(pTable[ni].name,def_name)==0) return ni;
	}
	return INVALID_DEF_CODE;

	/*
	for(n=0;n<Def_num;n++)
	{
		if(pTable[n].hash == hash) return n;
	}
	return INVALID_DEF_CODE;*/
}

void S_DEFTAB::UpdateHashTable(uint32_t code, uint32_t hash, bool in)
{
	uint32_t n;
	uint32_t hash_index;
	hash_index = DTMAKEHASHINDEX(hash);

	for(n=0;n<HashLine[hash_index].nNumElements;n++)
	{
		if(HashLine[hash_index].pElements[n] != code) continue;
		if(!in)
		{
			// take element out of list
			HashLine[hash_index].pElements[n] = HashLine[hash_index].pElements[HashLine[hash_index].nNumElements - 1];
			HashLine[hash_index].nNumElements--;
			HashLine[hash_index].pElements = (uint32_t *)RESIZE(HashLine[hash_index].pElements,HashLine[hash_index].nNumElements * sizeof(uint32_t));
			return;
		}
		else return;	// ok, already in list (? possible)
	}
	// not in list - add
	HashLine[hash_index].nNumElements++;
	HashLine[hash_index].pElements = (uint32_t *)RESIZE(HashLine[hash_index].pElements,HashLine[hash_index].nNumElements * sizeof(uint32_t));
	HashLine[hash_index].pElements[HashLine[hash_index].nNumElements - 1] = code;
}