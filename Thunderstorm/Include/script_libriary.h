#ifndef _SCRIPT_LIBRIARY_H_
#define _SCRIPT_LIBRIARY_H_

#ifndef _XBOX
#else
#include <xtl.h>
#endif

class SCRIPT_LIBRIARY
{
public:
	SCRIPT_LIBRIARY()
	{
	};

	virtual ~SCRIPT_LIBRIARY()
	{
	};
	virtual bool Init() { return false; };
};

#endif
