#include "control_stack.h"
#include "../../Common_h/Exs.h"
#include "externs.h"


CONTROL_STACK::CONTROL_STACK() {initiate_blocks = 0; Data_PTR = nullptr; used_blocks = 0;};
CONTROL_STACK::	~CONTROL_STACK()
{
	free(Data_PTR);
};
bool CONTROL_STACK::Init() 
{
	Release();
	initiate_blocks = DEFAULT_CONTROL_STACK_SIZE;

	Data_PTR = (void *) malloc(CONTROL_BLOCK_SIZE*initiate_blocks);
	return Data_PTR != nullptr;
};
void CONTROL_STACK::Release() 
{
	free(Data_PTR); 
	initiate_blocks = 0; 
	Data_PTR = nullptr; 
	used_blocks = 0;
};
void CONTROL_STACK::Clear() {used_blocks = 0;};
uint32_t CONTROL_STACK::DataNum() {return used_blocks;};
bool CONTROL_STACK::Push(void * pointer, uint32_t class_code, uint32_t ctp)
{
	//trace("PUSH: %d class: %d ctp: %d",pointer,class_code,ctp);
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	//if(pointer) Memory_Service.Lock(pointer);
	if(Data_PTR == nullptr) return false;
	if(used_blocks >= initiate_blocks)
	{
		initiate_blocks = initiate_blocks*2;
		Data_PTR = realloc(Data_PTR,CONTROL_BLOCK_SIZE*initiate_blocks);
		if(Data_PTR == nullptr) return false;
	}
	mem_PTR = (char*)Data_PTR + used_blocks*CONTROL_BLOCK_SIZE;
	cb_PTR = (CONTROL_BLOCK *)mem_PTR;
	cb_PTR->class_code = class_code;
	cb_PTR->pointer = pointer;
	cb_PTR->ctp = ctp;
	used_blocks++;
	return true;
};
bool CONTROL_STACK::Pop(CONTROL_BLOCK * cb_PTR)
{
	GUARD(CONTROL_STACK::Pop)
	char * mem_PTR;
	CONTROL_BLOCK * b_PTR;
	if(used_blocks == 0)
	{
		STORM_THROW(invalid pop);
	}
	if(Data_PTR == nullptr) return false;
	used_blocks--;
	b_PTR = (CONTROL_BLOCK *)((char *)Data_PTR + used_blocks*CONTROL_BLOCK_SIZE);
	//trace(" POP: %d class: %d ctp: %d",b_PTR->pointer,b_PTR->class_code,b_PTR->ctp);
	if(cb_PTR != nullptr)
	{
		mem_PTR = (char*)Data_PTR + used_blocks*CONTROL_BLOCK_SIZE;
		memcpy(cb_PTR,mem_PTR,CONTROL_BLOCK_SIZE);
		
	}	
//	if(b_PTR->pointer) Memory_Service.Unlock(b_PTR->pointer);
	UNGUARD
	return true;
};
bool CONTROL_STACK::ScanPointer(void * pointer)
{
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	uint32_t n;
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	for(n=0;n<used_blocks;n++)
	{
		mem_PTR = (char*)Data_PTR + n*CONTROL_BLOCK_SIZE;
		cb_PTR = (CONTROL_BLOCK *)mem_PTR;
		if(pointer == cb_PTR->pointer) 
			return true;
	}
	return false;
};
bool CONTROL_STACK::ScanClass(uint32_t class_code)
{
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	uint32_t n;
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	for(n=0;n<used_blocks;n++)
	{
		mem_PTR = (char*)Data_PTR + n*CONTROL_BLOCK_SIZE;
		cb_PTR = (CONTROL_BLOCK *)mem_PTR;
		if(class_code == cb_PTR->class_code) return true;
	}
	return false;
};
bool CONTROL_STACK::ScanClassCTP(uint32_t class_code,uint32_t ctp_code)
{
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	uint32_t n;
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	for(n=0;n<used_blocks;n++)
	{
		mem_PTR = (char*)Data_PTR + n*CONTROL_BLOCK_SIZE;
		cb_PTR = (CONTROL_BLOCK *)mem_PTR;
		if(class_code == cb_PTR->class_code) 
		{
			if(ctp_code == cb_PTR->ctp) return true;
		}
	}
	return false;
};
bool CONTROL_STACK::ScanClassCTPInv(uint32_t class_code,uint32_t ctp_code)
{
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	uint32_t n;
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	for(n=0;n<used_blocks;n++)
	{
		mem_PTR = (char*)Data_PTR + n*CONTROL_BLOCK_SIZE;
		cb_PTR = (CONTROL_BLOCK *)mem_PTR;
		if(class_code == cb_PTR->class_code) 
		{
			if(ctp_code != cb_PTR->ctp) return true;
		}
	}
	return false;
};

bool CONTROL_STACK::ScanCTP(uint32_t ctp_code)
{
	CONTROL_BLOCK * cb_PTR;
	char * mem_PTR;
	uint32_t n;
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	for(n=0;n<used_blocks;n++)
	{
		mem_PTR = (char*)Data_PTR + n*CONTROL_BLOCK_SIZE;
		cb_PTR = (CONTROL_BLOCK *)mem_PTR;
		if(ctp_code == cb_PTR->ctp) return true;
	}
	return false;
};
bool CONTROL_STACK::Read(CONTROL_BLOCK * cb_PTR)
{
	char * mem_PTR;
	if(cb_PTR) memset(cb_PTR,0,sizeof(CONTROL_BLOCK));
	if(used_blocks == 0) return false;
	if(Data_PTR == nullptr) return false;
	mem_PTR = (char*)Data_PTR + (used_blocks - 1)*CONTROL_BLOCK_SIZE;
	if(cb_PTR) memcpy(cb_PTR,mem_PTR,sizeof(CONTROL_BLOCK));
	return true;
};
