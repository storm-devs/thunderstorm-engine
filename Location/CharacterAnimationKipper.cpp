//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	CharacterAnimationKipper
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#include "CharacterAnimationKipper.h"
#include "..\common_h\dx9render.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

CharacterAnimationKipper::CharacterAnimationKipper()
{
	asr = null;
	aniMan = null;
	aniWoman = null;
	for(long i = 0; i < sizeof(lockTextures)/sizeof(long); i++) lockTextures[i] = -1;
	numLTextures = 0;
	rs = null;
}

CharacterAnimationKipper::~CharacterAnimationKipper()
{
	if(aniMan) delete aniMan;
	if(aniWoman) delete aniWoman;
	if(rs)
	{
		for(long i = 0; i < sizeof(lockTextures)/sizeof(long); i++) 
			if(lockTextures[i] >= 0) rs->TextureRelease(lockTextures[i]);
	}
}

//Инициализация
bool CharacterAnimationKipper::Init()
{
	//Проверим что единственные
	ENTITY_ID eid;
	if(_CORE_API->FindClass(&eid, "CharacterAnimationKipper", 0))
	{
		if(_CORE_API->GetEntityPointer(&eid) != this || _CORE_API->FindClassNext(&eid))
		{
			_CORE_API->Trace("CharacterAnimationKipper::Init() -> CharacterAnimationKipper already created");
			return false;
		}
	}
	rs = (VDX9RENDER *)_CORE_API->CreateService("dx9render");
	if(!rs) STORM_THROW("No service: dx9render");
	AnimationService * asr = (AnimationService *)_CORE_API->CreateService("AnimationServiceImp");
	if(!asr) STORM_THROW("Anumation service not created!");
	aniMan = asr->CreateAnimation("man");
	aniWoman = asr->CreateAnimation("towngirl");
	//LockTexture("dialog\dialog.tga");
	return true;
}

void CharacterAnimationKipper::LockTexture(const char * texture)
{
	if(numLTextures >= sizeof(lockTextures)/sizeof(long)) return;
	lockTextures[numLTextures++] = rs->TextureCreate(texture);
}

