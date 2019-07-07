#ifndef __VCOLLIDE_H__
#define __VCOLLIDE_H__


#include "../Common_h/collide.h"

#pragma pack(push)
#pragma pack(1)


class LCOLL : public LOCAL_COLLIDE
{
	PLANE plane[6];
	walker_t walker;
	CVECTOR boxCenter;
	float boxRadius;
	COLLIDE *col;
	VAPI &api;

public:
	LCOLL(const char *layerName, VAPI &_api);
	virtual ~LCOLL();
	virtual long SetBox(const CVECTOR &boxSize, const CMatrix &transform, bool testOnly = false);
	virtual const CVECTOR *GetFace(long &numVertices);
	virtual float Trace(const CVECTOR &src, const CVECTOR &dst);

};

class COLL  : public COLLIDE
{
public:
	COLL();
	virtual LOCAL_COLLIDE *CreateLocalCollide(const char *layerName);
	virtual ~COLL();
	virtual float Trace(entid_t entity, const CVECTOR &src, const CVECTOR &dst);
	virtual float Trace(walker_t walker, const CVECTOR &src, const CVECTOR &dst, const entid_t exclude_list, long entities);
	virtual bool Clip(walker_t walker, const PLANE *planes, long nplanes, const CVECTOR &center,
		float radius, ADD_POLYGON_FUNC addpoly, const entid_t exclude_list, long entities);
	virtual entid_t GetObjectID();
};


#pragma pack(pop)

//API_SERVICE_START("collide service")
//	DECLARE_MAIN_SERVICE(COLL)
//API_SERVICE_END(COLL)


#endif