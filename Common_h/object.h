#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../Common_h/triangle.h"
#include "../Common_h/Matrix.h"
#include "dx9render.h"

typedef bool (*ADD_POLYGON_FUNC)(const CVECTOR *v, long nv);

class COLLISION_OBJECT : public Entity
{
public:
	void ProcessStage(Stage, uint32_t) override
	{
	}
	virtual ~COLLISION_OBJECT(){};
	CMatrix mtx;

	virtual float Trace(const CVECTOR &src, const CVECTOR &dst) = 0;
	virtual bool Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly) = 0;

	virtual const char *GetCollideMaterialName() = 0;
	virtual bool GetCollideTriangle(TRIANGLE &triangle) = 0;
};
#endif