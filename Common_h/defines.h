#ifndef DEFINES_HPP
#define DEFINES_HPP

namespace TOREMOVE
{
	inline unsigned long HashNoCase(const char * str)
	{
		unsigned long hval = 0;
		while(*str != '\0')
		{
			char c = *str++;
			if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
			hval = (hval<<4) + (unsigned long)c;
			unsigned long g = hval & ((unsigned long) 0xf << (32 - 4));
			if(g != 0)
			{
				hval ^= g >> (32 - 8);
				hval ^= g;
			}
		}
		return hval;
	}
}

// includes
#include <cstdint>
#include <cstring>
#include "math3D.h"

#define _FILE_				__FILE__
#define _L				__LINE__
#define _FL_			__FILE__, __LINE__
#define _FL				__FILE__, __LINE__
#define _FILELINE_		_FL_

struct FPOINT
{
	float	x,y;
};

struct FRECT
{
	union
	{
		struct { float	x1,y1,x2,y2; };
		struct { float	xs,ys,xe,ye; };
		struct { float	x_start,y_start,x_end,y_end; };
		struct { float	left,top,right,bottom; };
	};
};

// Constants

#define PI		3.14159265358979323846f
#define PIm2	(PI * 2.0f)
#define PId2	(PI / 2.0f)
#define PId4	(PI / 4.0f)

#define RDTSC_B(x)	{ x = __rdtsc(); }
#define RDTSC_E(x)	{ x = __rdtsc() - x; }

// Defines
#ifdef RGB
	#undef RGB
#endif

#ifdef DELETE
	#undef DELETE
#endif

#ifdef SQR
	#undef SQR
#endif

inline uint32_t F2DW( float f ) { return *reinterpret_cast<uint32_t*>(&f); }

inline int ftoi(float f)
{
	return _mm_cvt_ss2si(_mm_load_ss(&f));
}
#define STORM_DELETE(x)			{ delete x; x=0; }
#define DELETE_ENTITY(x)	{ if (_CORE_API->ValidateEntity(&x)) _CORE_API->DeleteEntity(x); }
#define RELEASE(x)			{ if (x) x->Release(); x = 0; }
#define SQR(a)				( (a)*(a) )
#define FRAND(x)			( (x) * (float)rand()/(float)RAND_MAX  )
#define SIGN(x)				( (x)<0 ? -1.0f : 1.0f )
#define SIGNZ(x)			( (x)==0.0f ? 0.0f : ((x)<0.0f ? -1.0f : 1.0f) )
#define MAX(x,y)			( ((x) > (y)) ? (x) : (y) )
#define MIN(x,y)			( ((x) < (y)) ? (x) : (y) )
#define MAX3(x,y,z)			( ((x) > (y)) ? ((x) > (z) ? (x) : (z)) : ((y) > (z) ? (y) : (z)) )
#define MIN3(x,y,z)			( ((x) < (y)) ? ((x) < (z) ? (x) : (z)) : ((y) < (z) ? (y) : (z)) )
#define CLAMP(x)			( ((x) > 1.0f) ? 1.0f : (((x) < 0.0f) ? 0.0f : (x)) )
#define RGB(r,g,b)			( uint32_t(b)|(uint32_t(g)<<8L)|(uint32_t(r)<<16L) )
#define ARGB(a,r,g,b)		( uint32_t(b)|(uint32_t(g)<<8L)|(uint32_t(r)<<16L)|(uint32_t(a)<<24L) )
#define STORM_ZERO(x,y)		{ memset(x, 0, y); }
#define ZERO(x)				{ STORM_ZERO(&x,sizeof(x)); }
#define ZERO2(x,y)			{ ZERO(x) ZERO(y) }
#define ZERO3(x,y,z)		{ ZERO2(x,y) ZERO(z) }
#define ZERO4(x,y,z,a)		{ ZERO2(x,y) ZERO2(z,a) }
#define PZERO(x,size)		{ STORM_ZERO(x,size); }
#define COPY_STRING(a,b)	{ a = NEW char[strlen(b)+1]; if (a) strcpy_s(a,b); }
#define COLOR2VECTOR(a)		CVECTOR(float((a&0xFF0000)>>0x10),float((a&0xFF00)>>0x8),float(a&0xFF));
#define COLOR2VECTOR4(a)	CVECTOR4(float((a&0xFF0000)>>0x10) / 255.0f, float((a&0xFF00)>>0x8) / 255.0f, float(a&0xFF) / 255.0f, float((a&0xFF000000)>>0x18) / 255.0f);

// game defines
#define METERS2KNOTS(x)		((x) * 3600.0f / 1853.0f)
#define KNOTS2METERS(x)		((x) * 1853.0f / 3600.0f)

template<class T> void Swap(T & t1, T & t2) { T tmp; tmp = t1; t1 = t2; t2 = tmp; };
template<class T> T Clamp(T t) { if (t < (T)0) return (T)0; if (t > (T)1) return (T)1; return t; };
template<class T> T Clamp(T t, T Min, T Max) { if (t < Min) return Min; if (t > Max) return Max; return t; };
template<class T> T Bring2Range(T Min1, T Max1, T Min2, T Max2, T Value) { if (Value < Min2) Value = Min2; if (Value > Max2) Value = Max2; float Delta = float(Value - Min2) / float(Max2 - Min2); return Min1 + Delta * (Max1 - Min1); };
template<class T> T Bring2RangeNoCheck(T Min1, T Max1, T Min2, T Max2, T Value) { float Delta = float(Value - Min2) / float(Max2 - Min2); return Min1 + Delta * (Max1 - Min1); };
template<class T> T Min(T t1, T t2) { return ((t1 < t2) ? t1 : t2); };
template<class T> T Max(T t1, T t2) { return ((t1 > t2) ? t1 : t2); };
template<class T> T Sqr(T t1) { return (t1 * t1); };

#include "inlines.h"

#endif