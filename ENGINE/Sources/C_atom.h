#ifndef _C_ATOM_H_
#define _C_ATOM_H_

#include <cstdint>
#include "../../Common_h/entid_t.h"

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
	uint32_t Layers_mask[_LAYERS_BITMASK_DWORDS];

	uint64_t Realize_ticks_av;
	uint64_t Realize_ticks_max;
	uint64_t Execute_ticks_av;
	uint64_t Execute_ticks_max;
	uint64_t Message_ticks_av;
	uint64_t Message_ticks_max;

};

class C_ATOM 
{
public:
	C_ATOM();
	void SetLayerAttribute(uint32_t index);
	void ClrLayerAttribute(uint32_t index);
	bool TstLayerAttribute(uint32_t index);

	entid_t atom_id;
	ATOM_STATE as;
};

#endif