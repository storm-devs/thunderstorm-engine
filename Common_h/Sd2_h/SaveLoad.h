#ifndef SAVE_LOAD_HPP
#define SAVE_LOAD_HPP

#include <string>
#include "../../Common_h/memop.h"
#include "../../Common_h/defines.h"

class CSaveLoad
{
private:
	char	* pSaveBuffer;
	uint32_t	dwCurSize, dwMaxSize;
	bool	bSave, bLoad;

public:
	CSaveLoad() 
	{
		dwCurSize = 0;
		dwMaxSize = 0;
		bSave = bLoad = false;
		pSaveBuffer = nullptr;
	}

	~CSaveLoad() 
	{
		Close();
	}

	void Close()
	{
		if (bSave)
		{
			const auto size = dwCurSize * 2 + 8 + 1;
			auto pFFSave = new char[size];
			sprintf_s(pFFSave, size, "%.8x", dwCurSize);
			for (uint32_t i=0; i<dwCurSize; i++)
				sprintf_s(&pFFSave[8 + i * 2], 3, "%.2x", uint8_t(pSaveBuffer[i]));

			VDATA * pV = api->Event("SeaLoad_GetPointer", "sl", "seasave", -1);
			if (pV)
				pV->GetAClass()->SetAttribute("save", pFFSave);

			delete[] pFFSave;
		}
		free(pSaveBuffer);
	}

	void CreateWrite()
	{
		pSaveBuffer = nullptr;
		dwCurSize = 0;
		dwMaxSize = 0;
		bSave = true;
		bLoad = false;
	}

	void CreateLoad()
	{
		bSave = false;
		bLoad = true;
		dwCurSize = 0;

		VDATA * pV = api->Event("SeaLoad_GetPointer", "sl", "seasave", -1);
		char * pSave = pV->GetAClass()->GetAttribute("save");
		uint32_t dwSize;
		char str[256];
		strncpy_s(str, pSave, 8);
		str[8] = 0;
		sscanf(str, "%x", &dwSize);
		pSaveBuffer = (char*)malloc(dwSize);
		for (uint32_t i=0; i<dwSize; i++)
		{
			strncpy_s(str, &pSave[8 + i * 2], 2); str[2] = 0;
			uint32_t dwValue;
			sscanf(str, "%x", &dwValue);
			pSaveBuffer[i] = char(dwValue);
		}
	}

	void Write(const void * pBuffer, uint32_t dwSize)
	{
		if (dwMaxSize <= dwCurSize + dwSize)
		{
			dwMaxSize = 2048 * ((dwCurSize + dwSize + 2048) / 2048);
			pSaveBuffer = (char*)realloc(pSaveBuffer, dwMaxSize);
		}
		memcpy(&pSaveBuffer[dwCurSize], pBuffer, dwSize);
		dwCurSize += dwSize;
	}

	void Read(void * pBuffer, uint32_t dwSize)
	{
		memcpy(pBuffer, &pSaveBuffer[dwCurSize], dwSize);
		dwCurSize += dwSize;
	}

// =======================================================================================
// Save functions
// =======================================================================================

	void SaveDword(uint32_t dwValue)
	{
		Write(&dwValue, sizeof(dwValue));
	}

	void SaveFloat(float fValue)
	{
		Write(&fValue, sizeof(fValue));
	}

	void SaveLong(long iValue)
	{
		Write(&iValue, sizeof(iValue));
	}

	void SaveString(std::string & str)
	{
		if (str.size())
		{
			uint32_t dwLen = str.size() + 1;
			SaveDword(dwLen);
			Write(str.c_str(), dwLen);
		}
		else
		{
			uint32_t dwLen = 0;
			SaveDword(dwLen);
		}
	}

	void SaveVector(const CVECTOR & vVector)
	{
		Write((void*)&vVector, sizeof(vVector));
	}

	void SaveBuffer(const char * pBuffer, uint32_t dwSize)
	{
		SaveDword(dwSize);
		Write((void*)pBuffer, dwSize);
	}

	void SaveAPointer(const char * pStr, ATTRIBUTES * pAttribute)
	{
		long iIndex = -1;
		if (pAttribute)
		{
			iIndex = (long)pAttribute->GetAttributeAsDword("index", -1);
		}
		SaveLong(iIndex);
		SaveString(std::string(pStr));
	}

// =======================================================================================
// Load functions
// =======================================================================================

	uint32_t LoadDword()
	{
		uint32_t dwValue;
		Read(&dwValue, sizeof(dwValue));
		return dwValue;
	}

	float LoadFloat()
	{
		float fValue;
		Read(&fValue, sizeof(fValue));
		return fValue;
	}

	long LoadLong()
	{
		long iValue;
		Read(&iValue, sizeof(iValue));
		return iValue;
	}

	std::string LoadString()
	{
		std::string str;
		uint32_t dwLen;
		Read(&dwLen, sizeof(dwLen));
		if (dwLen == 0) return std::string();
		char * pBuffer = NEW char[dwLen];
		Read(pBuffer, dwLen);
		str = pBuffer;
		delete[] pBuffer;
		return str;
	}

	CVECTOR LoadVector()
	{
		CVECTOR v;
		Read(&v, sizeof(v));
		return v;
	}

	void LoadBuffer(char * * pBuffer)
	{
		uint32_t dwSize;
		Read(&dwSize, sizeof(dwSize));
		*pBuffer = NEW char[dwSize];
		Read(*pBuffer, dwSize);
	}

	void Load2Buffer(char * pBuffer)
	{
		uint32_t dwSize;
		Read(&dwSize, sizeof(dwSize));
		Read(pBuffer, dwSize);
	}

	ATTRIBUTES * LoadAPointer(const char * pStr)
	{
		long iIndex = LoadLong();
		std::string str = LoadString();
		if (str == "character" && iIndex < 0) return nullptr;
		VDATA * pV = api->Event("SeaLoad_GetPointer", "sl", pStr, iIndex);
		return (pV) ? pV->GetAClass() : nullptr;
	}
};

#endif