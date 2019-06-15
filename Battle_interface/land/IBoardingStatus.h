#ifndef _IBOARDINGSTATUS_H_
#define _IBOARDINGSTATUS_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../defines.h"

class IBoardingStatus : public ENTITY
{
	VDX9RENDER *rs;
public:
	IBoardingStatus();
	~IBoardingStatus();
	bool Init();
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);

protected:
	void Create();
	void SetCharactersHP(float myHP,float enemyHP);

protected:
	// show parameters
	//-----------------------
	long	m_Width;
	long	m_Height;
	FPOINT	m_myPos;
	FPOINT	m_enemyPos;
	uint32_t	m_myColor;
	uint32_t	m_enemyColor;

	BI_COLORONLY_VERTEX	m_MyChar[4];
	BI_COLORONLY_VERTEX	m_EnemyChar[4];
};

#endif
