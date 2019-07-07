//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	CharacterAnimationKipper
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#ifndef _CharacterAnimationKipper_H_
#define _CharacterAnimationKipper_H_


#include "../Common_h/vmodule_api.h"
#include "../Common_h/Animation.h"

class VDX9RENDER;

class CharacterAnimationKipper : public Entity
{
//--------------------------------------------------------------------------------------------
//Конструирование, деструктурирование
//--------------------------------------------------------------------------------------------
public:
	CharacterAnimationKipper();
	virtual ~CharacterAnimationKipper();

	//Инициализация
	bool Init();
	void LockTexture(const char * texture);
	void ProcessStage(Stage, uint32_t) override
	{
	}

//--------------------------------------------------------------------------------------------
//Инкапсуляция
//--------------------------------------------------------------------------------------------
private:
	VDX9RENDER * rs;

	AnimationService * asr;
	Animation * aniMan;
	Animation * aniWoman;

	long lockTextures[16];
	long numLTextures;
};

#endif

