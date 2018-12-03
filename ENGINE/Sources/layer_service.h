#ifndef _LAYER_SERVICE_H_
#define _LAYER_SERVICE_H_

#include "layer.h"
#include "C_atom.h"
#include "../../Common_h/Exs.h"

typedef struct
{
	uint32_t Layer_max_index;
	uint32_t Scan_layer_code;
	uint32_t Layers_number;
} LAYER_SERVICE_STATE;

#define INVALID_LAYER_CODE				0xffffffff

class LAYER_SERVICE
{
public:
	LAYER * Layer_Table[_MAX_LAYERS];
	bool	ToClean;
	LAYER_SERVICE_STATE lss;
	
	LAYER_SERVICE();
	bool Create(char * layer_name, bool ordered, bool fail_if_exist);
	bool Verify(char * layer_name);
	void Delete(char * layer_name);
	bool Add(char * layer_name, ENTITY_ID eid, uint32_t priority);
	void Del(char * layer_name, ENTITY_ID eid);
	bool Add(uint32_t index, ENTITY_ID eid, uint32_t priority);
	void Del(uint32_t index, ENTITY_ID eid);
	void Fit(uint32_t pos,char * layer_name,LAYER_STATE ls);
	void Erase(uint32_t dwcode);
	bool DeleteContent(char * layer_name);
	void SetSleep(char * layer_name,uint32_t sleep_time_ms);
	void SetFlags(char * layer_name, uint32_t flags);
	void ClrFlags(char * layer_name, uint32_t flags);
	uint32_t GetFlags(char * layer_name);
	uint32_t GetIndex(char * layer_name);
	LAYER * GetLayer(char * layer_name);
	LAYER * GetLayer(uint32_t index);
	void CheckAutoExceptions();
	void Clean();
	void Release();

};

#endif