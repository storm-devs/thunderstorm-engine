#ifndef _DATA_CACHE_
#define _DATA_CACHE_

#include "..\system\datasource\datasource.h"
//#include "..\..\common_h\file.h"
#include <vector>

class IParticleManager;

class DataCache
{
	IParticleManager* Master;

	struct LoadedDataSource
	{
		std::string FileName;
		DataSource* pData;

		LoadedDataSource ()
		{
			pData = NULL;
		}
	};
	
	std::vector<LoadedDataSource> Cache;
	
	void CreateDataSource (void* pBuffer, DWORD BufferSize, const char* SourceFileName);


public:

//Конструктор/деструктор
	DataCache (IParticleManager* pManager);
	~DataCache ();

//Положить в кэш данные для системы
	void CacheSystem (const char* FileName);

//Сбросить кэш
	void ResetCache ();

//Получить указатель на данные для системы партиклов
	DataSource* GetParticleSystemDataSource (const char* FileName);

//Проверить указатель на валидность
	bool ValidatePointer (DataSource* pData);

	DWORD GetCachedCount ();
	const char* GetCachedNameByIndex (DWORD Index);


};


#endif