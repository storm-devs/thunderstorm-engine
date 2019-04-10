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
//���������������, ������������������
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

//�������������
bool CharacterAnimationKipper::Init()
{
	//�������� ��� ������������
	ENTITY_ID eid;
	if(api->FindClass(&eid, "CharacterAnimationKipper", 0))
	{
		if(api->GetEntityPointer(&eid) != this || api->FindClassNext(&eid))
		{
			api->Trace("CharacterAnimationKipper::Init() -> CharacterAnimationKipper already created");
			return false;
		}
	}
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if(!rs) STORM_THROW("No service: dx9render");
	AnimationService * asr = (AnimationService *)api->CreateService("AnimationServiceImp");
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

