#ifndef _K2_PSYSTEM_H
#define _K2_PSYSTEM_H

#include "../vmodule_api.h"
#include "../Cvector.h"
#include "../Matrix.h"
#include "../vparticle_system.h"


class IParticleSystem;
class PARTICLES;

class PARTICLE_SYSTEM : public VPARTICLE_SYSTEM
{
	IParticleSystem* pSystem;
	PARTICLES* pManager;



public:
	
	PARTICLE_SYSTEM(IParticleSystem* _pSystem);
	virtual ~PARTICLE_SYSTEM();
	virtual void	Stop();
	virtual void	SetEmitter(CVECTOR p, CVECTOR a);
	virtual void	LinkToObject(entid_t id, CVECTOR _LinkPos);
	virtual void	SetDelay(long _delay);
	virtual void	SetLifeTime(uint32_t time);
	virtual void	StopEmitter();
	virtual	void	Pause(bool _bPause);

public:
	void SetManager (PARTICLES* _pManager);
	IParticleSystem* GetSystem ();


};



#endif