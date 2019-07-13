#ifndef BASE_EMITTER
#define BASE_EMITTER

#include "math3D.h"
#include "../../ICommon/IEmitter.h"
#include "../../ICommon/Types.h"
#include "../DataSource/DataSource.h"
#include "../ParticleSystem/particlesystem.h"

class DataGraph;

class BaseEmitter : public IEmitter
{
	struct structParticleType
	{
		bool Visible;										//Видим или нет
		ParticleType Type;							// Тип партикла
		float Remain;										// Сколько осталось незапущенных с прошлого кадра
		uint32_t ActiveCount;							// Количество активных партиклов данного типа
		uint32_t MaxParticlesCount;				// Максимальное кол-во партиклов этого типа
		DataGraph* EmissionRate;				// График задающий скорость испускания партиклов

		FieldList* pFields;


		structParticleType ()
		{
			ActiveCount = 0;
			Remain = 0.0f;
			EmissionRate = nullptr;
			pFields = nullptr;
			Type = UNKNOWN_PARTICLE;
		}

		
	};

	std::vector<structParticleType> ParticleTypes;


	DataSource::EmitterDesc* pEmitter;
	FieldList* pFields;
	bool IsAttachedFlag;


	Vector Position;
	EmitterType Type;
	float LifeTime;
	float ElapsedTime;
	DataGraph* EmissionDirX;
	DataGraph* EmissionDirY;
	DataGraph* EmissionDirZ;

	bool Looped;
	bool Stoped;
	bool Visible;

	uint32_t Unique_GUID;

	Matrix matWorldTransform;
	bool OldMatrixNotInitialized;
	Matrix matWorldTransformOld;
	Matrix matWorldTransformNew;

	void BlendMatrix (Matrix& result, const Matrix& mat1, const Matrix& mat2, float BlendK);


	void IncreaseTime (float DeltaTime);

protected:

	std::string Name;
	ParticleSystem* pMaster;

  

public:
 
	// Конструктор / деструктор
  BaseEmitter(ParticleSystem* pSystem);
  virtual ~BaseEmitter();
  
	//Получить позицию для рождения новых партиклов  
	virtual Vector GetNewParticlePosition (float DeltaTime) = 0;
  

	//Родить новые партиклы 
	void BornParticles (float DeltaTime);
 	//Исполнить
  virtual void Execute (float DeltaTime);

	//Присоединиться к источнику данных
	virtual void AttachToDataSource (DataSource::EmitterDesc* pEmitter);



	virtual void CreateBillBoardParticle (FieldList &Fields);
	virtual void CreateModelParticle (FieldList &Fields);


	ParticleSystem* GetMaster ();
	ParticleManager* GetManager ();
	void GetEmissionDirection (Matrix &matWorld);


	virtual void SetGUID (uint32_t GUID)
	{
		Unique_GUID = GUID;
	}

	virtual uint32_t GetGUID ()
	{
		return Unique_GUID;
	}

	virtual void Restart ();


	virtual uint32_t GetParticleCount ();
	virtual bool IsStoped ();

	virtual void SetTransform (const Matrix& matWorld);
	virtual void Teleport (const Matrix &matWorld);

	virtual const char* GetName ();

	//Если флаг в true емиттер не будет самостоятельно испускать партиклы
	//так, как он привязан
	virtual void SetAttachedFlag (bool Flag);
	virtual bool IsAttached ();

	virtual float GetTime ();
	virtual void SetTime (float Time);


	virtual uint32_t GetParticleTypesCount ();
	virtual FieldList* GetParticleTypeDataByIndex (uint32_t Index);
	virtual ParticleType GetParticleTypeByIndex  (uint32_t Index);


	virtual FieldList* GetData ();


	virtual bool SetEnable (bool bVisible);
	virtual bool GetEnable ();

	//-1 если не нашли, иначе индекс
	virtual int GetParticleTypeIndex (FieldList* pFields);
	virtual bool SetParticleTypeEnable (bool bVisible, uint32_t Index);
	virtual bool GetParticleTypeEnable (uint32_t Index);


	virtual void Editor_UpdateCachedData ();

	virtual void SetName (const char* Name);

	virtual void Stop ();

};

#endif