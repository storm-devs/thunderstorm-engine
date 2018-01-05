#ifndef _D_TYPES_H_
#define _D_TYPES_H_

typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

#define null 0

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

struct CODESOURCE
{
	CODESOURCE(){pFileName = 0; line = 0xffffffff;};
	char * pFileName;
	dword  line;
};

struct MSTATE
{
	unsigned long nBlocksNum;
	unsigned long nMemorySize;
};

#endif