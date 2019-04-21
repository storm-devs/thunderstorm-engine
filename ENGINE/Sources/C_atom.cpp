#include "C_atom.h"
#include "../../Common_h/defines.h"

C_ATOM::C_ATOM()
{
	PZERO(&as,sizeof(as));
	as.Deleted = false;
	as.Connected = false;
	PZERO(&as.Layers_mask,sizeof(as.Layers_mask));
}

void C_ATOM::SetLayerAttribute(const uint32_t index)
{
	const auto number = index / 32;
	const uint32_t layer_flag = (1 << (index - number * 32));
	as.Layers_mask[number] |= layer_flag;
}

void C_ATOM::ClrLayerAttribute(const uint32_t index)
{
	const auto number = index / 32;
	const uint32_t layer_flag = (1 << (index - number * 32));
	as.Layers_mask[number] &= (~layer_flag);
}

auto C_ATOM::TstLayerAttribute(const uint32_t index) -> bool
{
	const auto number = index / 32;
	uint32_t layer_flag = (1 << (index - number * 32));
	layer_flag = layer_flag & as.Layers_mask[number];
	return layer_flag != 0;
}
