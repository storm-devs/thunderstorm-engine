#ifndef _SOUND_VISUALISATION_H_
#define _SOUND_VISUALISATION_H_


#include "../Common_h/dx9render.h"
#include "../Common_h/entity.h"

class SoundService;

class SoundVisualisationEntity : public Entity
{
	SoundService* pSound;

public:

  SoundVisualisationEntity();
  virtual ~SoundVisualisationEntity();

	virtual bool Init();
	virtual void Realize(uint32_t dTime);
  virtual void Execute(uint32_t dTime);


	void SetMasterSoundService (SoundService* pSoundService);
	void Wakeup();
  
};


#endif