#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include "../../../Common_h/vmodule_api.h"
#include "../../../Common_h/particles/iparticlesystem.h"
#include "../../ICommon/Types.h"
#include "../../Manager/particlemanager.h"
#include "../DataSource/DataSource.h"


class IEmitter;

class ParticleSystem : public IParticleSystem
{
	struct EmitterDesc
	{
		EmitterType Type;
		IEmitter* pEmitter;
	};

	std::vector<EmitterDesc> Emitters;

	//Автоудаляемая система или обычная
	bool AutoDeleted;  
	
	// Не рождать новые партиклы !!!
	bool EmissionPause;		

	bool DeleteIfNeed ();

	std::string SystemName;


	

protected:

	virtual ~ParticleSystem();


	IEmitter* CreatePointEmitter (DataSource::EmitterDesc* pEmitter);

	void DeleteAllEmitters ();

	ParticleManager* pMaster;

	Matrix matWorld;

public:

//Создание/удаление 
	ParticleSystem(ParticleManager* serv);
	virtual bool Release ();

//Отработать всем партиклам
  virtual uint32_t Execute (float DeltaTime);


//Перезапустить партикловую систему  
  virtual void Restart (uint32_t RandomSeed);
  
//Запаузить испускание партиклов  
  virtual void PauseEmission (bool bPause);

	virtual void Stop ();
//Узнать на паузе эмиссия или нет  
  virtual bool IsEmissionPaused ();


//Установить автоудаляемая система или обычная...  
  virtual void AutoDelete (bool Enabled);
//Узнаять автоудаляемая система или нет  
	virtual bool IsAutoDeleted ();
//Установить матрицу трансформации для системы 
	virtual void SetTransform (const Matrix& transform);
	virtual void GetTransform (Matrix& _matWorld);


	void CreateFromDataSource (DataSource* pDataSource);


	ParticleManager* GetMaster ();

	IEmitter* FindEmitter (const char* name);
	IEmitter* FindEmitterByData (FieldList* Data);
	

	void Teleport (const Matrix &transform);

	bool IsAlive ();

	const char* GetName ();
	void SetName (const char* Name);


public:
	uint32_t GetEmittersCount ();
	IEmitter* GetEmitterByIndex (uint32_t Index);
	EmitterType GetEmitterTypeByIndex  (uint32_t Index);

	void Editor_UpdateCachedData ();



};

#endif