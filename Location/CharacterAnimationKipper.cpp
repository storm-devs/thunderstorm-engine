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
#include "../Common_h/dx9render.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

CharacterAnimationKipper::CharacterAnimationKipper()
{
	asr = nullptr;
	aniMan = nullptr;
	aniWoman = nullptr;
	for(long i = 0; i < sizeof(lockTextures)/sizeof(long); i++) lockTextures[i] = -1;
	numLTextures = 0;
	rs = nullptr;
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
	;
	const auto walker = api->GetEntityIdWalker("CharacterAnimationKipper");
	if(entid_t eid = walker(); eid)
	{
		if(EntityManager::GetEntityPointer(eid) != this || walker())
		{
			api->Trace("CharacterAnimationKipper::Init() -> CharacterAnimationKipper already created");
			return false;
		}
	}
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if(!rs) throw std::exception("No service: dx9render");
	AnimationService * asr = (AnimationService *)api->CreateService("AnimationServiceImp");
	if(!asr) throw std::exception("Anumation service not created!");
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

