//============================================================================================
//	Spirenkov Maxim, 2003
//--------------------------------------------------------------------------------------------
//	
//--------------------------------------------------------------------------------------------
//	Lizards
//--------------------------------------------------------------------------------------------
//	
//============================================================================================

#include "Lizards.h"
#include "Location.h"


Lizards::Lizards()
{
	num = sizeof(lizard)/sizeof(Lizard);
}

Lizards::~Lizards()
{

}

//Инициализация
bool Lizards::Init()
{
	//Указатель на локацию
	ENTITY_ID loc;
	_CORE_API->FindClass(&loc, "location", 0);
	Location * location = (Location *)_CORE_API->GetEntityPointer(&loc);
	if(!location) return false;
	//Заводим ящерец
	for(size_t i = 0; i < num; i++) lizard[i].Init(location);
	//Исполнение
	_CORE_API->LayerCreate("realize", true, false);
	_CORE_API->LayerSetFlags("realize", LRFLAG_REALIZE);
	_CORE_API->LayerAdd("realize", GetID(), 100000);
	return true;
}

//Исполнение
void Lizards::Execute(uint32_t delta_time)
{
}

//Рисование
void Lizards::Realize(uint32_t delta_time)
{
	float dltTime = delta_time*0.001f;
	for(size_t i = 0; i < num; i++) lizard[i].Update(dltTime);

}



