#ifndef _C_ATOM_H_
#define _C_ATOM_H_

#include <cstdint>
#include "../../Common_h/entity_id.h"

#define _LAYERS_BITMASK_DWORDS	4
#define _MAX_LAYERS				(_LAYERS_BITMASK_DWORDS*32)

struct ATOM_STATE
{
	ATOM_STATE(): Connected(false), Deleted(false)
	{
		Realize_ticks_av = 0;
		Realize_ticks_max = 0;
		Execute_ticks_av = 0;
		Execute_ticks_max = 0;
		Message_ticks_av = 0;
		Message_ticks_max = 0;
	}
	;
	bool Connected;
	bool Deleted;
	//bool Service;
	uint32_t Layers_mask[_LAYERS_BITMASK_DWORDS];
	uint32_t SysLayers_mask[_LAYERS_BITMASK_DWORDS];

	uint32_t Realize_ticks_av;
	uint32_t Realize_ticks_max;
	uint32_t Execute_ticks_av;
	uint32_t Execute_ticks_max;
	uint32_t Message_ticks_av;
	uint32_t Message_ticks_max;

};

class C_ATOM 
{
public:
	C_ATOM();
	~C_ATOM(){};
	void SetLayerAttribute(uint32_t index,bool system);
	void ClrLayerAttribute(uint32_t index,bool system);
	bool TstLayerAttribute(uint32_t index,bool system);

	ENTITY_ID atom_id;
	ATOM_STATE as;
};

#endif