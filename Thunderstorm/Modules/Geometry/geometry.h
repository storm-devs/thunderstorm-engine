#ifndef __GEOMETRY2_H__
#define __GEOMETRY2_H__

#include "vmodule_api.h"
#include "geom.h"

class VGEOMETRY  : public SERVICE
{
public:
	virtual ~VGEOMETRY(){};
	virtual GEOS * CreateGeometry(const char * file_name,const char * light_file_name, const char *anim, long flags)= 0;
	virtual float SetTime(float time)=0;
	virtual void DeleteGeometry(GEOS *)= 0;
};

#endif