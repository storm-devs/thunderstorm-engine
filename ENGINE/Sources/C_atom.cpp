#include "c_atom.h"
#include "../../common_h/defines.h"

C_ATOM::C_ATOM()
{
	PZERO(&as,sizeof(as));
	//as.Service = false;
	as.Deleted = false;
	as.Connected = false;
	PZERO(&as.Layers_mask,sizeof(as.Layers_mask));
}

void C_ATOM::SetLayerAttribute(uint32_t index,bool system)
{
	uint32_t layer_flag;
	uint32_t uint32_t_number;
	uint32_t_number = index/32;
	layer_flag = (1<<(index - uint32_t_number*32));
	if(system) as.SysLayers_mask[uint32_t_number] |= layer_flag;
	else as.Layers_mask[uint32_t_number] |= layer_flag;
}

void C_ATOM::ClrLayerAttribute(uint32_t index,bool system)
{
	uint32_t layer_flag;
	uint32_t uint32_t_number;
	uint32_t_number = index/32;
	layer_flag = (1<<(index - uint32_t_number*32));
	if(system) as.SysLayers_mask[uint32_t_number] &= (~layer_flag);
	else as.Layers_mask[uint32_t_number] &= (~layer_flag);
}

bool C_ATOM::TstLayerAttribute(uint32_t index,bool system)
{
	uint32_t layer_flag;
	uint32_t uint32_t_number;
	uint32_t_number = index/32;
	layer_flag = (1<<(index - uint32_t_number*32));
	if(system) layer_flag = layer_flag & as.SysLayers_mask[uint32_t_number];
	else layer_flag = layer_flag & as.Layers_mask[uint32_t_number];
	if(layer_flag != 0) return true;
	return false;
}
