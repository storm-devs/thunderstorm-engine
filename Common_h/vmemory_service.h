#ifndef _VMEMORY_SERVICE_H_
#define _VMEMORY_SERVICE_H_

class VMEMORY_SERVICE
{
public:
	VMEMORY_SERVICE(){};
	virtual ~VMEMORY_SERVICE(){};
	
	virtual void * Allocate(long size)=0;
	virtual void * Reallocate(void * block_PTR,long size)=0;
	virtual void  Free(void * block_PTR)=0;
	virtual void  GlobalFree()=0;
//	virtual void  SetState(word entry_point, uint32_t module_code)=0;
//	virtual void  SetFlags(uint32_t _flags,void * block_PTR)=0;
//	virtual uint32_t GetFlags(void * block_PTR)=0;
};

#endif