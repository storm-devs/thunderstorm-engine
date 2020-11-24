#ifndef _WM_SHIPSIGN_H
#define _WM_SHIPSIGN_H

#include "../bi_defines.h"
#include "../battle_sign.h"

#define MAX_SHIP_QUANTITY	8

class WMShipIcon : public BISignIcon {
public:
  WMShipIcon(entid_t BIEntityID, VDX9RENDER* pRS);
  ~WMShipIcon();

  void ExecuteCommand(CommandType command) override;

protected:
  long CalculateSignQuantity() override;
  void UpdateChildrens() override;
};

#endif
