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
	entid_t loc = api->GetEntityIdWalker("location")();
	Location * location = (Location *)EntityManager::GetEntityPointer(loc);
	if(!location) return false;
	//Заводим ящерец
	for(long i = 0; i < num; i++) lizard[i].Init(location);
	//Исполнение
	//api->LayerCreate("realize", true, false);
	api->LayerSetRealize("realize", true);
	EntityManager::AddToLayer(REALIZE, GetId(), 100000);
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
	for(long i = 0; i < num; i++) lizard[i].Update(dltTime);

}



