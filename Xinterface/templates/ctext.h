#ifndef _TEMPLATES_TEXT_LIST_
#define _TEMPLATES_TEXT_LIST_

class CText
{
	char * pString;

public:
	CText() {pString=nullptr;}
	CText(char * str, BOOL bNewCreate=true)
	{
		if(bNewCreate && str) {
			pString = new char[strlen(str)+1];
			if(pString) strcpy_s(pString,str);
		} else pString=str;
	}
	CText(char * str, size_t nSize)
	{
		if(str) {
			pString = new char[nSize+1];
			if(pString)
			{
				strncpy_s(pString,str,nSize);
				pString[nSize] = 0;
			}
		} else pString=nullptr;
	}
	CText(CText & text)
	{
		if(text.pString)
		{
			int n = strlen(text.pString);
			pString = new char[n+1];
			memcpy(pString,text.pString,n*sizeof(char));
			pString[n] = 0;
		} else pString=nullptr;
	}
	~CText() {if(pString) delete pString; pString=nullptr;}

	void Release() {if(pString) delete pString; pString=nullptr;}
	bool IsEmpty() {return !pString;}
	size_t size() {if(!pString) return 0; return strlen(pString);}

	operator char*() {return pString;}
	char * c_str() {return pString;}

	CText & operator =(char* pStr)
	{
		//if(!pStr || pString==pStr) return *this;
		if(pString==pStr) return *this;
		Release();
		if(!pStr) return *this;
		pString = new char[strlen(pStr)+1];
		if(pString) strcpy_s(pString,pStr);
		return *this;
	}
	CText & operator =(CText & text) {return *this=text.pString;}

	//----------------------------------------------------------
	// compare operation
	bool operator ==(char* pStr)
	{
		if(pStr && pString) return _stricmp(pStr,pString)==0;
		return pStr==pString;
	}
	bool operator ==(CText & text)	{return *this==text.pString;}

	//----------------------------------------------------------
	// increment operation
	CText & operator +=(char* pStr)
	{
		if(!pString) {pString = pStr; return *this;}
		if(!pStr) return *this;
		int n = strlen(pString);
		int m = strlen(pStr);
		char * newStr = new char[n+m+1];
		if(!newStr) return *this;
		strncpy_s(newStr,pString,n);
		strncpy_s(&newStr[n],pStr,m);
		newStr[n+m] = 0;
		delete pString;
		pString = newStr;
		return *this;
	}
	CText & operator +=(CText & text) {return *this+=text.pString;}

	CText operator +(char * pStr) {return CText(pString)+=pStr;}
	CText operator +(CText & text) {return CText(pString)+=text.pString;}
	friend CText operator +(char * pStrOne, CText & textTwo)
	{
		return CText(pStrOne)+=textTwo;
	}

	//----------------------------------------------------------
	// decrement operation
	CText & operator -=(char * pStr)
	{
		if(!pString || !pStr) return *this;
		int q1 = strlen(pString);
		int q2 = strlen(pStr);
		if(q1<q2) return *this;
		int q = q1-q2+1;
		for(int n=0; n<q; n++)
			if ( strnicmp(&pString[n],pStr,q2)==0 )
			{
				if(q1>q2)
				{
					char * pNew = new char[q1-q2+1];
					if(pNew)
					{
						if(n>0) memcpy(pNew,pString,n);
						if(n<q) memcpy(&pNew[n],&pString[n+q2],q-n); //~!~
					}
					delete pString;
					pString = pNew;
				} else {delete pString; pString=nullptr;}
				break;
			}
		return *this;
	}
	CText & operator -=(CText & text) {return *this-=text.pString;}

	CText operator -(char * pStr) {return CText(pString)-=pStr;}
	CText operator -(CText & text) {return CText(pString)-=text.pString;}
	friend CText operator -(char * pStrOne, CText & textTwo)
	{
		return CText(pStrOne)+=textTwo.pString;
	}

	//----------------------------------------------------------
	// array operation
	char operator [](int n) {return pString[n];}
};

#endif
