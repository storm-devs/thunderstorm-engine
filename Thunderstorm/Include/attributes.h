#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_

#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <vector>
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
	uint32_t nNameCode;
	char * Attribute;
	std::vector<ATTRIBUTES *> pAttributes;
	ATTRIBUTES * pParent;
	bool bBreak;

	inline void SetParent(ATTRIBUTES * pP) {pParent = pP;};

	ATTRIBUTES * CreateNewAttribute(uint32_t name_code)
	{
		auto attr = pAttributes.emplace_back(new ATTRIBUTES(pVStringCodec));

		attr->SetParent(this);
		attr->nNameCode = name_code;

		return attr;
	}

public:
	ATTRIBUTES(VSTRING_CODEC * p)
	{
		pVStringCodec = p;
		Attribute = nullptr;
		pParent = nullptr;
		bBreak = false;
		nNameCode = pVStringCodec->Convert("root");
	}

	ATTRIBUTES(const ATTRIBUTES&) = delete;
	ATTRIBUTES(ATTRIBUTES&&) = delete;
	ATTRIBUTES & operator=(const ATTRIBUTES&) = delete;

	~ATTRIBUTES()
	{
		Release();
	};

	void SetBreak(bool bBreak)
	{
		this->bBreak = bBreak;
	}

	ATTRIBUTES * GetParent()
	{
		return pParent;
	};

	inline bool operator == (const char * str)
	{
		if (!str || !str[0]) return false;
		return _stricmp(pVStringCodec->Convert(nNameCode), str) == 0;
	};

	char * GetThisName()
	{
		return pVStringCodec->Convert(nNameCode);
	}

	char * GetThisAttr() { return Attribute; };

	void SetName(const char * _name)
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

		const auto len = GetLen(strlen(_val) + 1);
		const auto oldPtr = Attribute;
		Attribute =  new char[len];
		strcpy_s(Attribute, len, _val);
		delete[] oldPtr;

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
		if (bBreak) 
			pVStringCodec->VariableChanged();
		ReleaseLeafs();
		delete Attribute;
		Attribute = nullptr;
	};

	void ReleaseLeafs()
	{
		for (const auto & attribute : pAttributes)
			delete attribute;
		pAttributes.clear();
	};

	uint32_t GetAttributesNum() {return pAttributes.size();}

	ATTRIBUTES * GetAttributeClass(const char * name)
	{
		for (const auto & attribute : pAttributes)
			if (_stricmp(name, attribute->GetThisName()) == 0) 
				return attribute;
		return nullptr;
	};

	ATTRIBUTES * GetAttributeClass(uint32_t n)
	{
		return n >= pAttributes.size() ? nullptr : pAttributes[n];
	};

	ATTRIBUTES * VerifyAttributeClass(const char * name)
	{
		ATTRIBUTES * pTemp = GetAttributeClass(name);
		return (pTemp) ? pTemp : CreateAttribute(name, "");
	};

	char * GetAttribute(uint32_t n)
	{
		return n >= pAttributes.size() ? nullptr : pAttributes[n]->Attribute;
	};

	char * GetAttributeName(uint32_t n)
	{
		return n >= pAttributes.size() ? nullptr : pAttributes[n]->GetThisName();
	};

	char * GetAttribute(const char * name)
	{
		if (name == nullptr) return nullptr;
		for (const auto & attribute : pAttributes)
			if (_stricmp(name,attribute->GetThisName())== 0) 
				return attribute->Attribute;
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

	uint32_t GetAttributeAsQword(const char* name = nullptr, uint64_t def = 0)
	{
		uint32_t qDword;
		char* pAttribute;
		qDword = def;
		if (name)
		{
			pAttribute = GetAttribute(name);
			if (pAttribute) qDword = atoll(pAttribute);
		}
		else
		{
			qDword = atoll(Attribute);
		}
		return qDword;
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
		if(name == nullptr) return nullptr;
		auto attr = pAttributes.emplace_back(new ATTRIBUTES(pVStringCodec));

		attr->SetParent(this);
		attr->SetName(name);

		if(attribute)
		{
			const auto len = GetLen(strlen(attribute) + 1);
			attr->Attribute = new char[len];
			strcpy_s(attr->Attribute, len, attribute);
		}

		return attr;
	};

	inline uint32_t SetAttribute(const char * name, const char * attribute)
	{
		return SetAttribute(pVStringCodec->Convert(name),attribute);
	};

	void Copy(ATTRIBUTES * pASource)
	{
		if(pASource == nullptr) return;
		ReleaseLeafs();
		for (const auto & attribute : pASource->pAttributes)
		{
			uint32_t i = SetAttribute(attribute->GetThisName(), attribute->Attribute);
			pAttributes[i]->Copy(attribute);
		}
	};

	BOOL DeleteAttributeClassX(ATTRIBUTES * pA)
	{
		if(pA == nullptr) return false;
		if(pA == this)
		{
			for (const auto & attribute : pAttributes)
				delete attribute;
			pAttributes.clear();
		}
		else
		{
			for(uint32_t n = 0;n<pAttributes.size();n++)
			{
				if(pAttributes[n] == pA)
				{
					delete pA;
					for(uint32_t i = n;i<pAttributes.size() - 1;i++)
						pAttributes[i] = pAttributes[i+1];

					pAttributes.pop_back();
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

	ATTRIBUTES * GetAttributeClassByCode(uint32_t name_code)
	{
		for (const auto & attribute : pAttributes)
			if(name_code == attribute->nNameCode) 
				return attribute;
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
		auto attr = pAttributes.emplace_back(new ATTRIBUTES(pVStringCodec));

		attr->SetParent(this);
		attr->nNameCode = name_code;
		if(attribute)
		{
			const auto len = GetLen(strlen(attribute) + 1);
			attr->Attribute = new char[len];
			strcpy_s(attr->Attribute, len, attribute);
		}

		return attr;
	};

	uint32_t GetALen(uint32_t dwLen)
	{
		return (pParent) ? (1 + dwLen / 2) * 2 : (1 + dwLen / 8) * 8;
	}

	uint32_t GetLen(uint32_t dwLen, uint32_t dwAlign = 8)
	{
		return (1 + dwLen / dwAlign) * dwAlign;
	}

	uint32_t SetAttribute(uint32_t name_code, const char * attribute)
	{
		uint32_t len = 0;
		if(attribute)
			len = GetLen(strlen(attribute) + 1);

		size_t n;
		for(n=0;n<pAttributes.size();n++)
		{
			if(pAttributes[n]->nNameCode == name_code)
			{
				if(attribute)
				{
					const auto oldPtr = pAttributes[n]->Attribute;
					pAttributes[n]->Attribute = new char[len];
					strcpy_s(pAttributes[n]->Attribute, len, attribute);
					delete[] oldPtr;
				}
				else
				{
					if(pAttributes[n]->Attribute)
					{
						delete[] pAttributes[n]->Attribute;
					}
					pAttributes[n]->Attribute = nullptr;
				}
				return n;
			}
		}

		auto attr = pAttributes.emplace_back(new ATTRIBUTES(pVStringCodec));

		attr->SetParent(this);
		attr->nNameCode = name_code;
		if(attribute)
		{
			pAttributes[n]->Attribute = new char[len];
			strcpy_s(pAttributes[n]->Attribute, len, attribute);
		}

		return pAttributes.size() - 1;
	};

	uint32_t GetThisNameCode()
	{
		return nNameCode;
	}
	void SetNameCode(uint32_t n)
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