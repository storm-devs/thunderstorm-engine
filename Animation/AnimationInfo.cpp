//============================================================================================
//	Spirenkov Maxim aka Sp-Max Shaman, 2001
//--------------------------------------------------------------------------------------------
//	Storm engine v2.00
//--------------------------------------------------------------------------------------------
//	AnimationInfo
//--------------------------------------------------------------------------------------------
//	Здесь хранится информация об анимации, загружаемая 1 раз
//============================================================================================

#include "AnimationInfo.h"
#include "../Common_h/memop.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

AnimationInfo::AnimationInfo(const char * animationName)
{
	Assert(strlen(animationName) < 64);
	strcpy_s(name, animationName);
	bone = nullptr;
	numBones = 0;
	action = nullptr;
	numActions = 0;
	refCounter = 0;
	downtime = 0;
	fps = 15.0f;
}

AnimationInfo::~AnimationInfo()
{
	if(bone) delete [] bone;
	if(action)
	{
		for(size_t i = 0; i < numActions; i++)
				if(action[i]) delete action[i];
		delete action;
	}
}

//Создать кости
void AnimationInfo::CreateBones(long numbones)
{
	Assert(bone == nullptr || numBones == 0);
	Assert(numbones > 0 && numbones <= 256);
	numBones = numbones;
	bone = new Bone[numBones];
}

//Создать действие
ActionInfo * AnimationInfo::AddAction(const char * anctionName, long startframe, long endframe)
{
	Assert(anctionName);
	//Ищем повторение
	for(size_t i = 0; i < numActions; i++)
		if(action[i][0] == anctionName) return nullptr;
	//Всё нормально - новое действие
	numActions++;
	action = (ActionInfo **)RESIZE(action, numActions*4);	
	action[numActions - 1] = NEW ActionInfo(anctionName, startframe, endframe);
	return action[numActions - 1];
}

//--------------------------------------------------------------------------------------------
//Работа с анимацией
//--------------------------------------------------------------------------------------------

//Сравнить с текущим именем
bool AnimationInfo::operator == (const char * animationName)
{
	return _stricmp(animationName, name) == 0;
}

//Найти действие по имени
ActionInfo * AnimationInfo::FindAction(const char * actionName)
{
	for(size_t i = 0; i < numActions; i++)
		if(action[i][0] == actionName) return action[i];
	return nullptr;
}

