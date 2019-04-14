#pragma once
#include "vapi.h"
#include <vector>

#define INTERFACE_FUNCTION

class VMA;

//extern VMA* _pModuleClassRoot;
inline std::vector<VMA*> _pModuleClassRoot;
extern VAPI* api;
//extern VSYSTEM_API* _VSYSTEM_API;
extern VFILE_SERVICE* fio;

class VMA
{
protected:
	VMA * pNext;
	long  nHash;
	long  nReference;
public:
	VMA(): pNext(nullptr)
	{
		nReference = 0;
		nHash = 0;
		_pModuleClassRoot.push_back(this);
		//pNext = _pModuleClassRoot;
		//_pModuleClassRoot = this;
	}
	;
	VMA * Next(){return pNext;}
	virtual ~VMA(){};
	long Build_Version() {return ENGINE_VERSION;};
	void SetHash(long _hash) {nHash = _hash;}
	long GetHash() {return nHash;}
	void Set(VMA * _p){pNext = _p;};
	virtual bool Service() {return false;}
	virtual char * GetName() {return nullptr;}
	virtual void * CreateClass() {return nullptr;}
	virtual void RefDec(){nReference--;};
	virtual long GetReference(){return nReference;}
	virtual void Clear(){nReference = 0;};
	virtual bool ScriptLibriary() {return false;}
};


#define CREATE_CLASS(a)	class a##vmacd : public VMA { public: char * GetName() {return TEXT(#a);} void * CreateClass() {nReference++; return new a;}} a##vmaci;
#define CREATE_SERVICE(a)	class a##vmacd : public VMA { public: a * pService = 0; char * GetName() {return TEXT(#a);} void * CreateClass() {if(pService == 0) pService = new a; nReference++; return pService;} bool Service() {return true;} void Clear(){nReference = 0; if(pService) delete pService; pService = 0;};} a##vmaci;
#define CREATE_SCRIPTLIBRIARY(a)	class a##vmacd : public VMA { public: /*a * pLibraryInitClass;*/ char * GetName() {return TEXT(#a);} void * CreateClass() {/*if(pLibraryInitClass == 0) pLibraryInitClass = new a; nReference++; return pLibraryInitClass;*/ return new a;} bool ScriptLibriary() {return true;} /*void Clear(){nReference = 0; if(pLibraryInitClass) delete pLibraryInitClass; pLibraryInitClass = 0;}*/;} a##vmaci;