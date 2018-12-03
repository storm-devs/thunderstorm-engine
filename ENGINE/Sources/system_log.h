#ifndef _SYSTEM_LOG_H_
#define _SYSTEM_LOG_H_

#ifndef _XBOX
#else
#include <xtl.h>
#endif

void  _cdecl trace(char * data_PTR,...);

#endif