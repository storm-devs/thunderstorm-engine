#ifndef _FILE_SERVICE_H_
#define _FILE_SERVICE_H_

#include "..\..\common_h\vfile_service.h"
#include "ifs.h"


#define _MAX_OPEN_INI_FILES		1024

class INIFILE_T : public INIFILE
{
public:
	 INIFILE_T(IFS * iR)
	 {
		ifs_PTR = iR;
		Search.Section = nullptr;
		Search.Key = nullptr;
	 };
	~INIFILE_T();
	
	SEARCH_DATA Search;

	IFS * ifs_PTR;

	// add string to file
	void	AddString(char * section_name, char * key_name, char * string);
	// write string to file, overwrite data if exist, throw EXS exception object if failed
	void	WriteString(char * section_name, char * key_name, char * string);
	// write long value of key in pointed section if section and key exist, throw EXS object otherwise
	void	WriteLong(char * section_name, char * key_name, long value);
	// write double value of key in pointed section if section and key exist, throw EXS object otherwise
	void	WriteDouble(char * section_name, char * key_name,double value);
	
	// fill buffer with key value, throw EXS exception object if failed or if section or key doesnt exist
	void	ReadString(char * section_name, char * key_name, char * buffer, uint32_t buffer_size);
	// fill buffer with key value if section and key exist, otherwise fill with def_string and return false
	bool	ReadString(char * section_name, char * key_name, char * buffer, uint32_t buffer_size, char * def_string);
	// continue search from key founded in previous call this function or to function ReadString
	// fill buffer with key value if section and key exist, otherwise return false
	bool	ReadStringNext(char * section_name, char * key_name, char * buffer, uint32_t buffer_size);

	// return long value of key in pointed section if section and key exist, throw EXS object otherwise
	long	GetLong(char * section_name, char * key_name);
	// return long value of key in pointed section if section and key exist, if not - return def_value
	long	GetLong(char * section_name, char * key_name, long def_val);

	// return double value of key in pointed section if section and key exist, throw EXS object otherwise
	double	GetDouble(char * section_name, char * key_name);
	// return double value of key in pointed section if section and key exist, if not - return def_value
	double	GetDouble(char * section_name, char * key_name, double def_val);

	bool GetLongNext(char * section_name, char * key_name, long * val);
	bool GetDoubleNext(char * section_name, char * key_name, double * val);


	float	GetFloat(char * section_name, char * key_name);
	float	GetFloat(char * section_name, char * key_name, float def_val);
	bool	GetFloatNext(char * section_name, char * key_name, float * val);


	void DeleteKey(char * section_name, char * key_name);

	void DeleteKey(char * section_name, char * key_name, char * key_value);

	void DeleteSection(char * section_name);

	bool TestKey(char * section_name, char * key_name, char * key_value);

	bool GetSectionName(char * section_name_buffer, long buffer_size);

	bool GetSectionNameNext(char * section_name_buffer, long buffer_size);

	void Flush();

	bool Reload();

	bool CaseSensitive(bool v);

	bool TestSection(char * section_name);

};

#define CACHEDIRSTABLESIZE	1024
struct HASHLINEDESC
{
	HASHLINEDESC(){dwElementsNum = 0; pDirName = nullptr;};
	uint32_t dwElementsNum;
	char ** pDirName;
};

class FILE_SERVICE : public VFILE_SERVICE
{
protected:
	//INIFILE_R * OpenFiles[_MAX_OPEN_INI_FILES];
	IFS * OpenFiles[_MAX_OPEN_INI_FILES];
	uint32_t Files_Num;
	uint32_t Max_File_Index;

	HASHLINEDESC CacheDirs[CACHEDIRSTABLESIZE];

public:

	
	FILE_SERVICE();
	~FILE_SERVICE();
	HANDLE _CreateFile(const char * lpFileName,uint32_t dwDesiriedAccess = GENERIC_READ,uint32_t dwShareMode = FILE_SHARE_READ,uint32_t dwCreationDisposition = OPEN_EXISTING);
	void   _CloseHandle(HANDLE hFile);
	uint32_t  _SetFilePointer(HANDLE hFile,long DistanceToMove,long * lpDistanceToMoveHigh,uint32_t dwMoveMethod);
	BOOL   _DeleteFile(const char * lpFileName);
	BOOL   _WriteFile(HANDLE hFile,const void * lpBuffer,uint32_t nNumberOfBytesToWrite,uint32_t * lpNumberOfBytesWritten);
	BOOL   _ReadFile(HANDLE hFile,void * lpBuffer,uint32_t nNumberOfBytesToRead,uint32_t * lpNumberOfBytesRead);
	HANDLE _FindFirstFile(const char * lpFileName,LPWIN32_FIND_DATA lpFindFileData);
	BOOL   _FindNextFile(HANDLE hFindFile,LPWIN32_FIND_DATA lpFindFileData);
	BOOL   _FindClose(HANDLE hFindFile);
	BOOL   _FlushFileBuffers(HANDLE hFile);
	uint32_t  _GetCurrentDirectory(uint32_t nBufferLength,char * lpBuffer);
	BOOL   _GetDiskFreeSpaceEx(const char * lpDirectoryName,PULARGE_INTEGER lpFreeBytesAvailableToCaller,
		     PULARGE_INTEGER lpTotalNumberOfBytes,PULARGE_INTEGER lpTotalNumberOfFreeBytes);
	UINT   _GetDriveType(const char * lpRootPathName);
	uint32_t  _GetFileSize(HANDLE hFile,uint32_t * lpFileSizeHigh);
	uint32_t  _GetLogicalDrives(VOID);
	uint32_t  _GetLogicalDriveStrings(uint32_t nBufferLength,char * lpBuffer);
	BOOL   _SetCurrentDirectory(const char * lpPathName);
	BOOL   _CreateDirectory(const char * lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
	BOOL   _RemoveDirectory(const char * lpPathName);
 	BOOL   _CopyFile(const char * lpExistingFileName,const char * lpNewFileName,bool bFailIfExists);
	BOOL   _SetFileAttributes(const char * lpFileName,uint32_t dwFileAttributes);
	BOOL FileExist(const char * file_name);
	BOOL LoadFile(const char * file_name, char * * ppBuffer, uint32_t * dwSize);
	// ini files section
	void  Close();
	INIFILE * CreateIniFile(const char * file_name, bool fail_if_exist);
	INIFILE * OpenIniFile(const char * file_name);
	void	  RefDec(INIFILE * ini_obj);
	void FlushIniFiles();
	BOOL SetDrive(const char * pDriveName);

	BOOL CacheDirectory(const char * pDirName);
	BOOL UnCacheDirectory(const char * pDirName);
	uint32_t MakeHashValue(const char * string);
	BOOL IsCached(const char * pFileName);
	void MarkDirectoryCached(const char * pFileName);

};

#endif