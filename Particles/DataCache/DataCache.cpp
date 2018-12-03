#include "DataCache.h"
#include "../../Common_h/particles.h"
#include "../../Common_h/filesystem.h"
#include "../ICommon/MemFile.h"

bool ReadingAlreadyComplete;

//�����������/����������
DataCache::DataCache (IParticleManager* pManager)
{
	Master = pManager;
}

DataCache::~DataCache ()
{
	ResetCache ();
}

//�������� � ��� ������ ��� �������
void DataCache::CacheSystem (const char* FileName)
{
	//NameWithExt.AddExtention(".xps");
	//NameWithExt.Lower();

	//std::string LongFileName = "resource\\particles\\";
	//LongFileName+=FileName;
	//LongFileName.AddExtention(".xps");
	fs::path path = fs::path() / "resource" / "particles" / FileName;
	std::string pathStr = path.extension().string();
	if (_stricmp(pathStr.c_str(), ".xps") != 0)
		path += ".xps";
	pathStr = path.string();
	//MessageBoxA(NULL, (LPCSTR)path.c_str(), "", MB_OK); //~!~

	HANDLE pSysFile = api->fio->_CreateFile(pathStr.c_str());

	if (pSysFile == INVALID_HANDLE_VALUE)
	{
		api->Trace("Particles: '%s' File not found !!!", pathStr.c_str());
		return;
	}

	uint32_t FileSize = api->fio->_GetFileSize(pSysFile, nullptr);

	uint8_t* pMemBuffer = NEW uint8_t[FileSize];
	api->fio->_ReadFile(pSysFile, pMemBuffer, FileSize, nullptr);

	//������� ������ �� �����...
	CreateDataSource (pMemBuffer, FileSize, pathStr.c_str());


	delete pMemBuffer;

	api->fio->_CloseHandle(pSysFile);
}

//�������� ���
void DataCache::ResetCache ()
{
	for (int n = 0; n < Cache.size(); n++)
	{
		if (Cache[n].pData) Cache[n].pData->Release();
	}

	Cache.clear();
}

//�������� ��������� �� ������ ��� ������� ���������
DataSource* DataCache::GetParticleSystemDataSource (const char* FileName)
{
	//std::string NameWithExt = FileName;
	//NameWithExt.AddExtention(".xps");
	//NameWithExt.Lower();
	fs::path path = FileName;
	std::string pathStr = path.extension().string();
	if (_stricmp(pathStr.c_str(), ".xps") != 0)
		path += ".xps";
	pathStr = path.string();

	for (int n = 0; n < Cache.size(); n++)
	{
		if (Cache[n].FileName == pathStr) return Cache[n].pData;
	}

	return nullptr;
}

//��������� ��������� �� ����������
bool DataCache::ValidatePointer (DataSource* pData)
{
	for (int n = 0; n < Cache.size(); n++)
		if (Cache[n].pData == pData) //fix
			return true;

	return false;
}



void DataCache::CreateDataSource (void* pBuffer, uint32_t BufferSize, const char* SourceFileName)
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

uint32_t DataCache::GetCachedCount ()
{
	return Cache.size();
}

const char* DataCache::GetCachedNameByIndex (uint32_t Index)
{
	return Cache[Index].FileName.c_str();
}
