#ifndef _S_IMPORT_FUNC_H_
#define _S_IMPORT_FUNC_H_

#include "v_s_stack.h"

#define IFUNCRESULT_OK		0
#define IFUNCRESULT_FAILED	0xffffffff

#define INVALID_FUNCHANDLE	0xffffffff

typedef uint32_t (__cdecl * SIMPORTFUNC)(VS_STACK *);

struct IFUNCINFO
{
	IFUNCINFO(): nArguments(0)
	{
		pFuncName = nullptr;
		pReturnValueName = nullptr;
		pFuncAddress = nullptr;
		pDeclFileName = nullptr;
		nDeclLine = 0;
	}
	;
	char * pFuncName;
	char * pReturnValueName;
	uint32_t  nArguments;
	SIMPORTFUNC pFuncAddress;
	char * pDeclFileName;
	uint32_t  nDeclLine;
};

#endif