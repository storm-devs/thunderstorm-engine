#ifndef _IBOARDINGSTATUS_H_
#define _IBOARDINGSTATUS_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../defines.h"

class IBoardingStatus : public Entity
{
	VDX9RENDER *rs;
public:
	IBoardingStatus();
	~IBoardingStatus();
	bool Init();
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::EXECUTE:
		//	Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}


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
