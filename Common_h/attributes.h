#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_

#include <cstdint>
#include <cstdio>
#include "memop.h"
#include "vstring_codec.h"

#define INVALID_ATTRIBUTE_HANDLE	0xffffffff
//--------------------------------------------------------------------------------------------------------------
// Each attribute is a class with Name and Attribute string values. Class can contain list of ... later
//
// GetAttributeClass(attribute_name) - return class ATTRIBUTES pointer for specified attribute
// GetAttribute(attribute_name) - return string value of specified attribute
// SetAttribute(attribute_name,attribute) - create or modify attribute in attributes set
// GetAttributeAsDword(attribute_name, DWORD def = 0) - return attribute value, converted from string to uint32_t
// GetAttributeAsFloat(attribute_name, DWORD def = 0) - return attribute value, converted from string to float
// SetAttributeUseDword(attribute_name, DWORD val) - create or modify attribute, converted from uint32_t to string
// SetAttributeUseFloat(attribute_name, FLOAT val) - create or modify attribute, converted from float to string

#define RDTSC_B(x)	{ x = __rdtsc(); }
#define RDTSC_E(x)	{ x = __rdtsc() - x; }

class ATTRIBUTES
{
	void  xtrace(const char * data_PTR,...)
	{
		char xBuffer_4k[4096];
		if(data_PTR == nullptr) return;

		HANDLE file_h = CreateFile("attributes.log",GENERIC_WRITE,FILE_SHARE_READ,nullptr,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
		SetFilePointer(file_h,0,nullptr,FILE_END);
		va_list args;

		va_start(args,data_PTR);
		_vsnprintf_s(xBuffer_4k,sizeof(xBuffer_4k) - 4,data_PTR,args);
		strcat_s(xBuffer_4k,"\x0d\x0a");
		uint32_t bytes;
		WriteFile(file_h,xBuffer_4k,strlen(xBuffer_4k),(LPDWORD)&bytes,nullptr);
		va_end(args);
		CloseHandle(file_h);
		_flushall();

	}

#ifdef _XBOX
	static VSTRING_CODEC * pVStringCodec;
#else
	VSTRING_CODEC * pVStringCodec;
#endif
	uint32_t Attributes_num;
	uint32_t nNameCode;
	char * Attribute;
	ATTRIBUTES * * pAttributes;
	ATTRIBUTES * pParent;
	bool bBreak;

	inline void SetParent(ATTRIBUTES * pP) {pParent = pP;};

	ATTRIBUTES * CreateNewAttribute(uint32_t name_code)
	{
		pAttributes = (ATTRIBUTES **)RESIZE(pAttributes,GetALen(Attributes_num + 1) * sizeof(ATTRIBUTES *));

		pAttributes[Attributes_num] = NEW ATTRIBUTES(pVStringCodec);
		pAttributes[Attributes_num]->SetParent(this);
		pAttributes[Attributes_num]->nNameCode = name_code;
		pAttributes[Attributes_num]->Attribute = nullptr;
		Attributes_num++;

		return pAttributes[Attributes_num - 1];
	}

public:
	ATTRIBUTES(VSTRING_CODEC * p)
	{
		pVStringCodec = p;
		pAttributes = nullptr;
		Attributes_num = 0;
		Attribute = nullptr;
		pParent = nullptr;
		bBreak = false;
		nNameCode = pVStringCodec->Convert("root");
	};

	~ATTRIBUTES()
	{
		Release();
	};

	__forceinline void SetBreak(bool bBreak)
	{
		this->bBreak = bBreak;
	}

	__forceinline ATTRIBUTES * GetParent()
	{
		return pParent;
	};

	inline bool operator == (const char * str)
	{
		if (!str || !str[0]) return false;
		return _stricmp(pVStringCodec->Convert(nNameCode), str) == 0;
	};

	__forceinline char * GetThisName()
	{
		return pVStringCodec->Convert(nNameCode);
	}

	__forceinline char * GetThisAttr() { return Attribute; };

	__forceinline void SetName(const char * _name)
	{
		if (_name) nNameCode = pVStringCodec->Convert(_name);
	};

	void SetValue(const char * _val)
	{
		if(_val == nullptr)
		{
			if(Attribute) delete Attribute;
			Attribute = nullptr;
			return;
		}

		size_t alignedLen = GetLen(strlen(_val) + 1);
		Attribute = (char *)RESIZE(Attribute,alignedLen);
		strcpy_s(Attribute,alignedLen,_val);

		if (bBreak) pVStringCodec->VariableChanged();
	};

	void Release()
	{
		/*DWORD n;
		if(Attribute) delete Attribute;
		Attribute = 0;
		if(pAttributes)
		{
			for(n=0;n<Attributes_num;n++) delete pAttributes[n];
			delete pAttributes;
		}
		pAttributes = 0;
		Attributes_num = 0;*/
		if (bBreak) pVStringCodec->VariableChanged();
		ReleaseLeafs();
		if(Attribute) delete Attribute;
		Attribute = nullptr;
	};

	void ReleaseLeafs()
	{
		uint32_t n;
		if(pAttributes)
		{
			for (n=0; n<Attributes_num; n++) delete pAttributes[n];
			delete pAttributes;
		}
		pAttributes = nullptr;
		Attributes_num = 0;
	};

	__forceinline uint32_t GetAttributesNum() {return Attributes_num;}

	ATTRIBUTES * GetAttributeClass(const char * name)
	{
		for (uint32_t n=0; n<Attributes_num; n++)
			if (_stricmp(name, pAttributes[n]->GetThisName()) == 0) return pAttributes[n];
		return nullptr;
	};

	__forceinline ATTRIBUTES * GetAttributeClass(uint32_t n)
	{
		return (n >= Attributes_num) ? nullptr : pAttributes[n];
	};

	ATTRIBUTES * VerifyAttributeClass(const char * name)
	{
		ATTRIBUTES * pTemp = GetAttributeClass(name);
		return (pTemp) ? pTemp : CreateAttribute(name, "");
	};

	__forceinline char * GetAttribute(uint32_t n)
	{
		return (n >= Attributes_num) ? nullptr : pAttributes[n]->Attribute;
	};

	__forceinline char * GetAttributeName(uint32_t n)
	{
		return (n >= Attributes_num) ? nullptr : pAttributes[n]->GetThisName();
	};

	char * GetAttribute(const char * name)
	{
		if (name == nullptr) return nullptr;
		for(uint32_t n=0; n<Attributes_num; n++)
			if (_stricmp(name,pAttributes[n]->GetThisName())== 0) return pAttributes[n]->Attribute;
		return nullptr;
	};

	uint32_t GetAttributeAsDword(const char * name = nullptr, uint32_t def = 0)
	{
		uint32_t vDword;
		char * pAttribute;
		vDword = def;
		if (name)
		{
			pAttribute = GetAttribute(name);
			if (pAttribute) vDword = atol(pAttribute);
		}
		else
		{
			vDword = atol(Attribute);
		}
		return vDword;
	};

	FLOAT GetAttributeAsFloat(const char * name = nullptr, FLOAT def = 0)
	{
		FLOAT vFloat;
		char * pAttribute;
		vFloat = def;
		if(name)
		{
			pAttribute = GetAttribute(name);
			if(pAttribute) vFloat = (FLOAT)atof(pAttribute);
		}
		else
		{
			vFloat = (FLOAT)atof(Attribute);
		}
		return vFloat;
	};

	BOOL SetAttributeUseDword(const char * name, uint32_t val)
	{
		char buffer[128];
		_ultoa_s(val,buffer,10);
		if (name)
			return SetAttribute(name,buffer);
		else
			SetValue(buffer);
		return true;
	};

	BOOL SetAttributeUseFloat(const char * name, FLOAT val)
	{
		char buffer[128];
		sprintf_s(buffer, "%g", val);
		if (name)
			return SetAttribute(name,buffer);
		else
			SetValue(buffer);

		return true;
	};

	ATTRIBUTES * CreateAttribute(const char * name, const char * attribute)
	{
		uint32_t len;
		if(name == nullptr) return nullptr;
		pAttributes = (ATTRIBUTES **)RESIZE(pAttributes,GetALen(Attributes_num + 1) * sizeof(ATTRIBUTES *));

		pAttributes[Attributes_num] = NEW ATTRIBUTES(pVStringCodec);
		pAttributes[Attributes_num]->SetParent(this);
		pAttributes[Attributes_num]->SetName(name);

		if(attribute)
		{
			len = strlen(attribute);
			size_t alignedLen = GetLen(len + 1);
			pAttributes[Attributes_num]->Attribute = NEW char[alignedLen];
			strcpy_s(pAttributes[Attributes_num]->Attribute,alignedLen,attribute);
		}
		else pAttributes[Attributes_num]->Attribute = nullptr;
		Attributes_num++;
		return pAttributes[Attributes_num-1];
	};

	inline uint32_t SetAttribute(const char * name, const char * attribute)
	{
		return SetAttribute(pVStringCodec->Convert(name),attribute);
	};

	void Copy(ATTRIBUTES * pASource)
	{
		uint32_t n,ah;
		if(pASource == nullptr) return;
		ReleaseLeafs();
		for(n=0;n<pASource->Attributes_num;n++)
		{
			ah = SetAttribute(pASource->pAttributes[n]->GetThisName(),pASource->pAttributes[n]->Attribute);
			pAttributes[ah]->Copy(pASource->pAttributes[n]);
		}
	};

	BOOL DeleteAttributeClassX(ATTRIBUTES * pA)
	{
		uint32_t n,i;
		if(pA == nullptr) return false;
		if(pA == this)
		{
			if(pAttributes)
			{
				for(n=0;n<Attributes_num;n++) delete pAttributes[n];
				delete pAttributes;
				pAttributes = nullptr;
				Attributes_num = 0;
			}
		}
		else
		{
			for(n=0;n<Attributes_num;n++)
			{
				if(pAttributes[n] == pA)
				{
					delete pA;
					for(i=n;i<(Attributes_num - 1);i++)
					{
						pAttributes[i] = pAttributes[i+1];
					}

					Attributes_num--;
					pAttributes = (ATTRIBUTES **)RESIZE(pAttributes,GetALen(Attributes_num) * sizeof(ATTRIBUTES *));
					return true;
				}
				if(pAttributes[n]->DeleteAttributeClassX(pA)) return true;
			}
		}
		return false;
	};

	ATTRIBUTES * CreateSubAClass(ATTRIBUTES * pRoot, const char * access_string)
	{
		uint32_t dwNameCode;
		uint32_t n = 0;
		ATTRIBUTES * pResult = nullptr;
		ATTRIBUTES * pTemp;
		if(pRoot == nullptr) return nullptr;
		if(access_string == nullptr) return nullptr;

		while(true)
		{
			switch(access_string[n])
			{
				case '.':
					dwNameCode = pVStringCodec->Convert(access_string, n);
					pTemp = pRoot->GetAttributeClassByCode(dwNameCode);
					if (!pTemp)
						pTemp = pRoot->CreateNewAttribute(dwNameCode);
					pResult = CreateSubAClass(pTemp, &access_string[n + 1]);
					return pResult;

				case 0:
					dwNameCode = pVStringCodec->Convert(access_string);
					pResult = pRoot->GetAttributeClassByCode(dwNameCode);
					return (pResult) ? pResult : pRoot->CreateNewAttribute(dwNameCode);
			}
			n++;
		}
		return nullptr;
	};

	ATTRIBUTES * FindAClass(ATTRIBUTES * pRoot, const char * access_string)
	{
		uint32_t n = 0;
		ATTRIBUTES * pResult = nullptr;
		ATTRIBUTES * pTemp = nullptr;

		if (!pRoot || !access_string) return nullptr;
		if (!access_string[0]) return pRoot;

		while(true)
		{
			switch(access_string[n])
			{
				case '.':
					pTemp = pRoot->GetAttributeClassByCode(pVStringCodec->Convert(access_string, n));
					if (!pTemp) return nullptr;
					pResult = FindAClass(pTemp, &access_string[n+1]);
					return pResult;
				case 0:
					pResult = pRoot->GetAttributeClassByCode(pVStringCodec->Convert(access_string));
					return pResult;
			}
			n++;
		}
		return nullptr;
	};

	__forceinline ATTRIBUTES * GetAttributeClassByCode(uint32_t name_code)
	{
		for (uint32_t n=0; n<Attributes_num; n++)
			if(name_code == pAttributes[n]->nNameCode) return pAttributes[n];
		return nullptr;
	};

	ATTRIBUTES * VerifyAttributeClassByCode(uint32_t name_code)
	{
		ATTRIBUTES * pTemp;
		pTemp = GetAttributeClassByCode(name_code);
		if(pTemp) return pTemp;
		return CreateAttribute(name_code,"");
	};

	ATTRIBUTES * CreateAttribute(uint32_t name_code, const char * attribute)
	{
		uint32_t len;
		pAttributes = (ATTRIBUTES **)RESIZE(pAttributes,GetALen(Attributes_num + 1) * sizeof(ATTRIBUTES *));

		pAttributes[Attributes_num] = NEW ATTRIBUTES(pVStringCodec);
		pAttributes[Attributes_num]->SetParent(this);
		pAttributes[Attributes_num]->nNameCode = name_code;
		if(attribute)
		{
			len = strlen(attribute);
			size_t alignedLen = GetLen(len + 1);
			pAttributes[Attributes_num]->Attribute = NEW char[alignedLen];
			strcpy_s(pAttributes[Attributes_num]->Attribute,alignedLen,attribute);
		} else pAttributes[Attributes_num]->Attribute = nullptr;
		Attributes_num++;
		return pAttributes[Attributes_num-1];
	};

	__forceinline uint32_t GetALen(uint32_t dwLen)
	{
		return (pParent) ? (1 + dwLen / 2) * 2 : (1 + dwLen / 8) * 8;
	}

	__forceinline uint32_t GetLen(uint32_t dwLen, uint32_t dwAlign = 8)
	{
		return (1 + dwLen / dwAlign) * dwAlign;
	}

	uint32_t SetAttribute(uint32_t name_code, const char * attribute)
	{
		uint32_t n;
		uint32_t len;
		if(attribute)
			len = strlen(attribute);

		//xtrace("1");

//		uint32_t dw1;
//		RDTSC_B(dw1);

		for(n=0;n<Attributes_num;n++)
		{
			if(pAttributes[n]->nNameCode == name_code)
			{
				if(attribute)
				{
					size_t alignedLen = GetLen(len + 1);
					pAttributes[n]->Attribute = (char *)RESIZE(pAttributes[n]->Attribute,alignedLen);
					strcpy_s(pAttributes[n]->Attribute,alignedLen,attribute);
				}
				else
				{
					if(pAttributes[n]->Attribute)
					{
						delete pAttributes[n]->Attribute;
					}
					pAttributes[n]->Attribute = nullptr;
				}
				return n;
			}
		}

		pAttributes = (ATTRIBUTES **)RESIZE(pAttributes,GetALen(Attributes_num + 1) * sizeof(ATTRIBUTES *));

		pAttributes[Attributes_num] = NEW ATTRIBUTES(pVStringCodec);
		pAttributes[Attributes_num]->SetParent(this);
		pAttributes[Attributes_num]->nNameCode = name_code;
		if(attribute)
		{
			size_t alignedLen = GetLen(len + 1);
			pAttributes[n]->Attribute = NEW char[alignedLen];
			strcpy_s(pAttributes[n]->Attribute, alignedLen, attribute);
		}
		else pAttributes[Attributes_num]->Attribute = nullptr;
		Attributes_num++;

//		RDTSC_E(dw1);
//		xtrace("SA = %d", dw1);

		return (Attributes_num - 1);
	};

	__forceinline uint32_t GetThisNameCode()
	{
		return nNameCode;
	}
	__forceinline void SetNameCode(uint32_t n)
	{
		nNameCode = n;
	}

	void Dump(ATTRIBUTES * pA, long level)
	{
		char buffer[128];
		if (pA == nullptr) return;

		if (level >= 128) level = 127;
		if (level != 0) 
			memset(buffer,' ',level); 
		buffer[level] = 0;

		for(uint32_t n = 0;n<pA->GetAttributesNum();n++)
		{
			xtrace("%s%s = %s", buffer, pA->GetAttributeName(n), pA->GetAttribute(n));
			Dump(pA->GetAttributeClass(pA->GetAttributeName(n)), level + 2);
		}
	}
};

#endif