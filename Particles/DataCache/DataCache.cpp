#include "datacache.h"
#include "..\..\common_h\particles.h"
#include "..\..\common_h\filesystem.h"
#include "..\icommon\memfile.h"

bool ReadingAlreadyComplete;

//Конструктор/деструктор
DataCache::DataCache (IParticleManager* pManager)
{
	Master = pManager;
}

DataCache::~DataCache ()
{
	ResetCache ();
}

//Положить в кэш данные для системы
void DataCache::CacheSystem (const char* FileName)
{
	//NameWithExt.AddExtention(".xps");
	//NameWithExt.Lower();

	//std::string LongFileName = "resource\\particles\\";
	//LongFileName+=FileName;
	//LongFileName.AddExtention(".xps");
	fs::path path = fs::path() / "resource" / "particles" / FileName;
	if (_stricmp(path.extension().string().c_str(), ".xps") != 0)
		path += ".xps";
	//MessageBoxA(NULL, (LPCSTR)path.c_str(), "", MB_OK); //~!~

	HANDLE pSysFile = api->fio->_CreateFile(path.string().c_str());

	if (pSysFile == INVALID_HANDLE_VALUE)
	{
		api->Trace("Particles: '%s' File not found !!!", path.string().c_str());
		return;
	}

	DWORD FileSize = api->fio->_GetFileSize(pSysFile, 0);

	BYTE* pMemBuffer = NEW BYTE[FileSize];
	api->fio->_ReadFile(pSysFile, pMemBuffer, FileSize, 0);

	//Создаем данные из файла...
	CreateDataSource (pMemBuffer, FileSize, path.string().c_str());


	delete pMemBuffer;

	api->fio->_CloseHandle(pSysFile);
}

//Сбросить кэш
void DataCache::ResetCache ()
{
	for (int n = 0; n < Cache.size(); n++)
	{
		if (Cache[n].pData) Cache[n].pData->Release();
	}

	Cache.clear();
}

//Получить указатель на данные для системы партиклов
DataSource* DataCache::GetParticleSystemDataSource (const char* FileName)
{
	//std::string NameWithExt = FileName;
	//NameWithExt.AddExtention(".xps");
	//NameWithExt.Lower();
	fs::path path = FileName;
	if (_stricmp(path.extension().string().c_str(), ".xps") != 0)
		path += ".xps";

	for (int n = 0; n < Cache.size(); n++)
	{
		if (Cache[n].FileName == path.string()) return Cache[n].pData;
	}

	return NULL;
}

//Проверить указатель на валидность
bool DataCache::ValidatePointer (DataSource* pData)
{
	for (int n = 0; n < Cache.size(); n++)
		if (Cache[n].pData == pData) //fix
			return true;

	return false;
}



void DataCache::CreateDataSource (void* pBuffer, DWORD BufferSize, const char* SourceFileName)
{
	LoadedDataSource NewDataSource;
	NewDataSource.FileName = SourceFileName;
	NewDataSource.pData = NEW DataSource(Master);
	Cache.push_back(NewDataSource);

  //api->Trace("\nCreate data source for file %s", SourceFileName);

	MemFile* ReadFile = NEW MemFile;
	ReadFile->OpenRead(pBuffer, BufferSize);
	NewDataSource.pData->Load(ReadFile);
	ReadFile->Close();
	delete ReadFile;
}

DWORD DataCache::GetCachedCount ()
{
	return Cache.size();
}

const char* DataCache::GetCachedNameByIndex (DWORD Index)
{
	return Cache[Index].FileName.c_str();
}
