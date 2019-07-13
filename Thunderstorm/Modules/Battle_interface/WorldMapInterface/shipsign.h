#ifndef _WM_SHIPSIGN_H
#define _WM_SHIPSIGN_H

#include "../bi_defines.h"
#include "../battle_sign.h"

#define MAX_SHIP_QUANTITY	8

class WMShipIcon : public BISignIcon
{
public:
	WMShipIcon( entid_t BIEntityID, VDX9RENDER* pRS );
	~WMShipIcon();

	virtual void ExecuteCommand( CommandType command );

protected:
	virtual long CalculateSignQuantity();
	virtual void UpdateChildrens();
};

#endif