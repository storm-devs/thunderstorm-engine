#ifndef _LAYER_H_
#define _LAYER_H_

#include "../../Common_h/entity_id.h"
#include "common_h.h"
#include "idwalker.h"

#define _MAX_LAYER_NAME		290

typedef struct
{
	bool  System;
	bool  Ordered;
	bool  Deleted;
	uint32_t Flags;
	uint32_t System_flags;
} LAYER_STATE;

class LAYER_NODE
{
public:
	 LAYER_NODE(){};
	~LAYER_NODE(){};

	ENTITY_ID	id;
	LAYER_NODE * link_L;
	LAYER_NODE * link_R;
	uint32_t		priority;
};

class LAYER
{
public:
	 LAYER(char * name, bool ordered,bool system,uint32_t system_flags);
	~LAYER();
	bool Add(ENTITY_ID eid, uint32_t priority);
	bool Add(ENTITY_ID eid);
	bool Del(ENTITY_ID eid);
	ENTITY_ID * GetID();
	ENTITY_ID * GetNextID();
	ENTITY_ID * GetID(uint32_t * priority_PTR);
	ENTITY_ID * GetNextID(uint32_t * priority_PTR);
	void SetFlag(uint32_t flag);
	void ClrFlag(uint32_t flag);
	uint32_t GetPriority(ENTITY_ID eid);

	uint32_t Count;
	LAYER_STATE ls;
	char  Name[_MAX_LAYER_NAME];
	LAYER_NODE * Base_Link;
	LAYER_NODE * Search_Link;

	VIDWALKER * GetWalker();
	void DelWalker(void *);
	IDWALKER * * walkers;
	uint32_t walkers_num;

	ENTITY_ID * WalkerGetID(LPBYTE& sl);
	ENTITY_ID * WalkerGetNextID(LPBYTE& sl);

	
};

#endif