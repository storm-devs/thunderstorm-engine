#ifndef _VEVENT_H_
#define _VEVENT_H_

#include "vmodule_api.h"

class VEVENT : public SERVICE
{
public:
	VEVENT()
	{
	};

	virtual ~VEVENT()
	{
	};

	virtual uint32_t _cdecl Event(char* name, char* format,...)
	{
	};
};

#endif
