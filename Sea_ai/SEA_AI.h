#ifndef SEA_AI_HPP
#define SEA_AI_HPP

#include "AIHelper.h"
#include "AIFort.h"
#include "AIBalls.h"

class SEA_AI : public Entity
{
private:
	bool		bFirstInit;

	void	AddShip(entid_t _eidShip, ATTRIBUTES *pCharacter, ATTRIBUTES *pAShip);
	void	SetCompanionEnemy(ATTRIBUTES * pACharacter);

public:
	SEA_AI();
	~SEA_AI();

	bool Init();
	void SetDevice();
	void Save(const char * pName);
	void Load(const char * pName);

	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);
	
	bool CreateState(ENTITY_STATE_GEN * state_gen);
	bool LoadState(ENTITY_STATE * state);
	
	void ProcessMessage(uint32_t iMsg,uint32_t wParam,uint32_t lParam);
	uint32_t ProcessMessage(MESSAGE & message);

	uint32_t AttributeChanged(ATTRIBUTES *pAttribute);
};

#endif