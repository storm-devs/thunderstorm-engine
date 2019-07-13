#ifndef EMITTER_INTERFACE
#define EMITTER_INTERFACE


#include "../math3d/Matrix.h"
#include "../system/DataSource/FieldList.h"



class IParticleSystem;

class IEmitter
{

public:
 
	// ����������� / ����������
  IEmitter() {};
  virtual ~IEmitter() {};
  
  
	//������ ��������, ������������� ��� �������� ������������ ��������
	virtual void BornParticles (float DeltaTime) = 0;

	//���������
	virtual void Execute (float DeltaTime) = 0;

	virtual void Restart () = 0;

	virtual uint32_t GetParticleCount () = 0;

	virtual bool IsStoped () = 0;

	virtual void SetTransform (const Matrix &matWorld) = 0;
	virtual void Teleport (const Matrix &matWorld) = 0;


	virtual const char* GetName () = 0;

	//���� ���� � true ������� �� ����� �������������� ��������� ��������
	//���, ��� �� ��������
	virtual void SetAttachedFlag (bool Flag) = 0;
	virtual bool IsAttached () = 0;

	//���������/������������ ���.����� ��������
	virtual float GetTime () = 0;
	virtual void SetTime (float Time) = 0;



	virtual uint32_t GetParticleTypesCount () = 0;
	virtual FieldList* GetParticleTypeDataByIndex (uint32_t Index) = 0;
	virtual ParticleType GetParticleTypeByIndex  (uint32_t Index) = 0;

	virtual FieldList* GetData () = 0;


	virtual bool SetEnable (bool bVisible) = 0;
	virtual bool GetEnable () = 0;

	//-1 ���� �� �����, ����� ������
	virtual int GetParticleTypeIndex (FieldList* pFields) = 0;
	virtual bool SetParticleTypeEnable (bool bVisible, uint32_t Index) = 0;
	virtual bool GetParticleTypeEnable (uint32_t Index) = 0;


	virtual void Editor_UpdateCachedData () = 0;


	virtual void SetName (const char* Name) = 0;


	virtual void Stop () = 0;





};

#endif