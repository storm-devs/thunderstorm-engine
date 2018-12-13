#include "TIVBufferManager.h"

//--------------------------------------------------------------------
TIVBufferManager::TIVBufferManager(VDX9RENDER *_renderer, long _vType, long _vSize, long _iCount, long _vCount, long _count)
	:renderer(_renderer)
	,vBuffer(0)
	,iBuffer(0)
	,vType(_vType)
	,vSize(_vSize)
	,iCount(_iCount)
	,vCount(_vCount)
	,elementsCount(_count)
	,used(nullptr)
	,locked(false)
	,indexes(nullptr)
	,vertices(nullptr)
	,count(0)
{
	iBuffer = renderer->CreateIndexBuffer(elementsCount * iCount * sizeof(uint16_t));
	vBuffer = renderer->CreateVertexBuffer(vType, elementsCount * vCount * vSize, D3DUSAGE_WRITEONLY);
	used = new bool[elementsCount];
	for (int i=0; i < elementsCount; ++i)
		used[i] = false;
}

//--------------------------------------------------------------------
TIVBufferManager::~TIVBufferManager()
{
	if (used)
		delete[] used;
	if (vBuffer)
		renderer->ReleaseVertexBuffer(vBuffer);
	if (iBuffer)
		renderer->ReleaseIndexBuffer(iBuffer);
}

//--------------------------------------------------------------------
long TIVBufferManager::ReserveElement()
{
	for (int i=0; i < elementsCount; i++)
	{
		if (!used[i])
		{
			used[i] = true;
			if (i == count)
				++count;
			return i;
		}
	}

	return -1;
}

//--------------------------------------------------------------------
void TIVBufferManager::FreeElement(long _i)
{
	if (_i < 0)
		return;

	used[_i] = false;
}

//--------------------------------------------------------------------
void TIVBufferManager::FreeAll()
{
	for (int i=0; i < elementsCount; ++i)
		used[i] = false;
}

//--------------------------------------------------------------------
void TIVBufferManager::LockBuffers()
{
	indexes = (uint16_t *) renderer->LockIndexBuffer(iBuffer);
	vertices = renderer->LockVertexBuffer(vBuffer);
	locked = true;
}

//--------------------------------------------------------------------
void TIVBufferManager::UnlockBuffers()
{
	renderer->UnLockIndexBuffer(iBuffer);
	renderer->UnLockVertexBuffer(vBuffer);
	locked = false;
}

//--------------------------------------------------------------------
void TIVBufferManager::GetPointers(long _i, uint16_t **iPointer, void **vPointer, long *vOffset/* = 0*/)
{
	if ((_i < 0) || !locked)
	{
		*iPointer = nullptr;
		*vPointer = nullptr;
		return;
	}

	*iPointer = indexes + _i*iCount;
	*vPointer = ((uint8_t *) vertices) + _i*vSize*vCount;
	if (vOffset)
		*vOffset = _i*vCount;
}

//--------------------------------------------------------------------
void TIVBufferManager::DrawBuffers(char *_technique)
{
	if (locked || !count)
		return;

		renderer->DrawBuffer(vBuffer, 
							 vSize, 
							 iBuffer, 
							 0, 
							 count * vCount, 
							 0, 
							 count * iCount / 3, 
							 _technique);
}

//--------------------------------------------------------------------