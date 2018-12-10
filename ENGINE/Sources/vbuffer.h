#ifndef _VBUFFER_H_
#define _VBUFFER_H_

#ifndef _XBOX
#else
#include <xtl.h>
#endif

#include "../../Common_h/Exs.h"

class VBUFFER
{
	uint32_t dwSize;
public:
	char * Ptr;
	 VBUFFER() {dwSize = 0; Ptr = nullptr;}
	~VBUFFER() { free(Ptr);}
	void Size(uint32_t _size)
	{
		Ptr = (char*)realloc(Ptr,_size);
		if(!Ptr) THROW; 
		dwSize = _size; };
};

#endif