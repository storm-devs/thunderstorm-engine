#ifndef _TIVBUFFERMANAGER_H_
#define _TIVBUFFERMANAGER_H_

#include "..\common_h\dx9render.h"

///////////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////////
class TIVBufferManager  
{
public:
	TIVBufferManager(VDX9RENDER *_renderer, long _vType, long _vSize, long _iCount, long _vCount, long _count);
	virtual ~TIVBufferManager();

	long ReserveElement();
	void FreeElement(long _i);
	void FreeAll();
	void LockBuffers();
	void UnlockBuffers();
	void GetPointers(long _i, uint16_t **iPointer, void **vPointer, long *vOffset = nullptr);
	void DrawBuffers(char *_technique);

private:
	VDX9RENDER *renderer;
	long vBuffer, iBuffer;
	long vType, vSize, iCount, vCount, elementsCount;
	bool *used;
	bool locked;
	uint16_t *indexes;
	void *vertices;
	long count;
};

#endif
