#ifndef _SSTRING_H_
#define _SSTRING_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

class SSTRING
{
	char * pDataPointer;
	public:
	 SSTRING(){pDataPointer = nullptr;};
	 SSTRING(const char * p){if(!p) return; pDataPointer = NEW char[strlen(p) + 1]; strcpy(pDataPointer,p);};
	 SSTRING(const SSTRING& ss) : pDataPointer(nullptr)
	 {
		 pDataPointer = NEW char[strlen(ss.pDataPointer)+1];
		 strcpy(pDataPointer,ss.pDataPointer);
	 }
	~SSTRING()
	{
		if(pDataPointer) delete pDataPointer; pDataPointer = nullptr;
	};
	SSTRING& operator = (const SSTRING& ss) 
	{
		if(this == &ss) return *this;
		if(pDataPointer) delete pDataPointer;
		pDataPointer = NEW char[strlen(ss.pDataPointer)+1];
		strcpy(pDataPointer,ss.pDataPointer);
		return *this;
	}
	SSTRING& operator = (const char sym) 
	{
		if(pDataPointer) delete pDataPointer;
		pDataPointer = NEW char[2];
		pDataPointer[0] = sym;
		pDataPointer[1] = 0;
		return *this;
	}
	operator const char*(){ return pDataPointer; };
	bool operator ==(const char * p) 
	{
		if(pDataPointer == p) return true;
		if(pDataPointer == nullptr || p == nullptr) return false;
		if(strcmp(pDataPointer,p)==0) return true;
		return false;
	};
	bool operator !=(const char * p) 
	{
		if(pDataPointer == p) return false;
		if(pDataPointer == nullptr || p == nullptr) return true;
		if(strcmp(pDataPointer,p)==0) return false;
		return true;
	};
	void operator +=(const char * p)
	{
		char * pp;
		if(p == nullptr) return;
		if(pDataPointer == nullptr)
		{
			pDataPointer = NEW char[strlen(p) + 1]; strcpy(pDataPointer,p);
			return;
		}
		pp = NEW char[strlen(pDataPointer) + strlen(p) + 1];
		strcpy(pp,pDataPointer);
		strcat(pp,p);
		delete pDataPointer;
		pDataPointer = pp;
	};
	void operator +=(const char sym)
	{
		char * pp;
		DWORD nLen;
		if(pDataPointer == nullptr)
		{
			pDataPointer = NEW char[2]; 
			pDataPointer[0] = sym;
			pDataPointer[1] = sym;
			return;
		}
		nLen = strlen(pDataPointer);
		pp = NEW char[nLen + 2];
		strcpy(pp,pDataPointer);
		pp[nLen] = sym;
		pp[nLen + 1] = 0;
		delete pDataPointer;
		pDataPointer = pp;
	};
	SSTRING& format(const char * format_string,...)
	{
		char buffer[256];
		va_list args;
		va_start(args,format_string);
		_vsnprintf(buffer,sizeof(buffer),format_string,args);
		va_end(args);
		if(pDataPointer) delete pDataPointer;
		pDataPointer = NEW char[strlen(buffer)+1];
		strcpy(pDataPointer,buffer);
		return *this;
	}
};

#endif