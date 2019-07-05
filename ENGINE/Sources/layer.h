#ifndef _LAYER_H_
#define _LAYER_H_

#include "../../Common_h/entid_t.h"
#include "idwalker.h"
#include <vector>

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

	entid_t	id;
	LAYER_NODE * link_L;
	LAYER_NODE * link_R;
	uint32_t		priority;
};

class LAYER
{
public:
	 LAYER(char * name, bool ordered,bool system,uint32_t system_flags);
	~LAYER();
	bool Add(entid_t eid, uint32_t priority);
	bool Add(entid_t eid);
	bool Del(entid_t eid);
	entid_t * GetId();
	entid_t * GetNextID();
	entid_t * GetID(uint32_t * priority_PTR);
	entid_t * GetNextID(uint32_t * priority_PTR);
	void SetFlag(uint32_t flag);
	void ClrFlag(uint32_t flag);
	uint32_t GetPriority(entid_t eid);

	uint32_t Count;
	LAYER_STATE ls;
	char  Name[_MAX_LAYER_NAME];
	LAYER_NODE * Base_Link;
	LAYER_NODE * Search_Link;

	walker_t GetWalker();
	void DelWalker(void *);
	std::vector<IDWALKER*> walkers;
	uint32_t walkers_num;

	entid_t * WalkerGetID(LPBYTE& sl);
	entid_t * WalkerGetNextID(LPBYTE& sl);

	
};

#endif