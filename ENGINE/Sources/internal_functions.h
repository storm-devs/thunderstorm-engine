#ifndef _INTERNAL_FUNCTIONS_H_
#define _INTERNAL_FUNCTIONS_H_


#include "token.h"
#include "data.h"
#include "stack.h"

class INTERNAL_FUNCTIONS
{
	VSTACK * pStack;
	TOKEN *  pToken;
public:
	 INTERNAL_FUNCTIONS();
	~INTERNAL_FUNCTIONS();

	void SetStackAndToken(VSTACK * pStack, TOKEN *  pToken);
	DATA * CallIntFunction(char * func_name);
	DATA * CallIntFunction(uint32_t func_code);
	uint32_t  GetIntFunctionCode(char * func_name);
};

#endif