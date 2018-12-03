#ifndef _K2_PARTICLES_H_
#define _K2_PARTICLES_H_

#include "..\..\common_h\vmodule_api.h"
#include "..\..\common_h\entity.h"
#include <string>
#include <vector>

class IParticleService;
class IParticleManager;
class IParticleSystem;
class PARTICLE_SYSTEM;


class PARTICLES : public ENTITY
{
	bool CreationCapture;
	bool bSystemDelete;

	struct SystemInfo 
	{
		std::string FileName;
		PARTICLE_SYSTEM* pSystem;
		uint32_t LifeTime;
		uint32_t PassedTime;

		SystemInfo ()
		{
			PassedTime = 0;
			pSystem = nullptr;
			LifeTime = 0xFFFFFF00;
		}
	};
	std::vector<SystemInfo> CreatedSystems;

	IParticleService* pService;
	IParticleManager* pManager;


	PARTICLE_SYSTEM* CreateSystem (const char* pFileName, uint32_t LifeTime);
	void DeleteSystem (long SystemID);
	void DeleteAll ();

	void PauseAllActive (bool bPaused);


	std::vector<long> CaptureBuffer;

	void DeleteCaptured ();

public:
	void DeleteResource (PARTICLE_SYSTEM* pResource);


public:
 
  PARTICLES();
  ~PARTICLES();
  
  bool Init ();


	uint32_t _cdecl ProcessMessage(MESSAGE & message);

	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);


 
};


#endif