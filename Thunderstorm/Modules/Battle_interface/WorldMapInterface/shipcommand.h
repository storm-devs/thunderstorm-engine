#ifndef _WM_SHIPCOMMAND_H_
#define _WM_SHIPCOMMAND_H_

#include "../battle_command.h"

class WMShipCommandList : public BICommandList
{
public:
	WMShipCommandList( entid_t eid, ATTRIBUTES* pA, VDX9RENDER* rs );
	virtual ~WMShipCommandList();

	virtual void FillIcons();
	virtual void Init();

protected:
	void Release();

	long CommandAdding();
};

#endif