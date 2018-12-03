#ifndef _ENTITY_ID_H_
#define _ENTITY_ID_H_

#include <cstdint>

#ifndef _XBOX
#include <windows.h>
#else
#include <xtl.h>
#endif

#define CRTM_DWORDS			2

typedef struct { uint32_t time[CRTM_DWORDS];} ENTITY_CREATION_TIME;

//typedef struct { void * pointer; uint32_t  class_code; } ID_BASE;

struct ENTITY_ID
{
	ENTITY_ID() 
	{
		memset(&creation_time,0,sizeof(creation_time));
		atom_position = 0;
		class_code = 0;
		pointer = nullptr;
		pName = nullptr;
	};
	ENTITY_CREATION_TIME creation_time;
	uint32_t  atom_position;
	uint32_t  class_code;
	void * pointer; 
	inline bool operator == (const ENTITY_ID & eID) 
	{
		return (memcmp(this,&eID,sizeof(ENTITY_ID)) == 0);
	};
	char * pName;

};

#endif