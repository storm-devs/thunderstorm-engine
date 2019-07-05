#ifndef _SHIPPOINTER_H_
#define _SHIPPOINTER_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../../Common_h/Sd2_h/VAI_ObjBase.h"

class SHIPPOINTER : public Entity
{
	VDX9RENDER *rs;

public:
	SHIPPOINTER();
	~SHIPPOINTER();
	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);

protected:
	void UpdateShipPointer();
	VAI_OBJBASE * FindShipByChrIndex(long chrIdx);

	bool	m_bVisible;
	bool	m_bFriend;

	long	m_idFriendTex;
	long	m_idEnemyTex;

	long	m_idVBuf;

	float	m_fShiftVal;
	float	m_fShiftSpeed;
	float	m_fShiftAmp;
	float	m_fShiftWSize;
	float	m_fShiftHSize;
	float	m_fShiftTop;

	VAI_OBJBASE * m_pShip;
};

#endif
