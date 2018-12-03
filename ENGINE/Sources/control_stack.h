#ifndef _CONTROL_STACK_H_
#define _CONTROL_STACK_H_

#include "..\..\common_h\entity_id.h"

typedef struct 
{
	void *	pointer;
	uint32_t	class_code;
	uint32_t	ctp;
} CONTROL_BLOCK;

#define DEFAULT_CONTROL_STACK_SIZE	8
#define CONTROL_BLOCK_SIZE			sizeof(CONTROL_BLOCK)

class CONTROL_STACK
{
	void * Data_PTR;
	uint32_t initiate_blocks;
	uint32_t used_blocks;

public:

	CONTROL_STACK();
	~CONTROL_STACK();
	bool Init();
	void Release();
	void Clear();
	uint32_t DataNum();
	bool Push(void * pointer, uint32_t class_code, uint32_t ctp);
	bool Pop(CONTROL_BLOCK * cb_PTR);
	bool ScanPointer(void * pointer);
	bool ScanClass(uint32_t class_code);
	bool ScanClassCTP(uint32_t class_code,uint32_t ctp_code);
	bool ScanClassCTPInv(uint32_t class_code,uint32_t ctp_code);
	bool ScanCTP(uint32_t ctp_code);
	bool Read(CONTROL_BLOCK * cb_PTR);
};


#endif