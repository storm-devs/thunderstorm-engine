#ifndef _IEDITOR_UTILS_H_
#define _IEDITOR_UTILS_H_

#include "defines.h"
#include "..\..\common_h\dx9render.h"

class EdUtils
{
public:
	static bool CheckPointInsideRect( const EdPoint& epnt, const EdRect& erect );
	static void DrawColorRect( const EdRect& erPlace, dword dwColor );
	static void DrawColorSprite( const EdRect& erPlace, dword dwColor, long nTexture, const EdRect& erUV );

public:
	static VDX9RENDER* m_pRender;
};

#endif
