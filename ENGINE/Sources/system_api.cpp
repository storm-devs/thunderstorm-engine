#include "system_api.h"
#include "externs.h"
#include "Core.h"
#include "system_log.h"

extern CORE Core;

void SYSTEM_API::Push(void * pointer, uint32_t class_code)
{
	//if(entityID_PTR) Control_Stack.Push(idbase.pointer,idbase.class_code,CTP_CONSTRUCTOR);
	if(entityID_PTR) PUSH_CONTROL(pointer,class_code,CTP_CONSTRUCTOR);
}

void SYSTEM_API::Pop(void * pointer)
{
	return;
/*	if(Control_Stack.ScanClassCTPInv(idbase.class_code,CTP_DESTRUCTOR)) STORM_THROW('delete this' not allowed);
	POP_CONTROL(0);
	Memory_Service.Lock(idbase.pointer);	// protect memory from being freed by FreeMem func
	Core.MarkEntityAsDeleted(idbase.pointer);		// assign entity for deleting*/
}

void SYSTEM_API::SetEntityPointer(void * ep)
{
	if(entityID_PTR) entityID_PTR->pointer = ep;
}

ENTITY_ID SYSTEM_API::GetEntityID()
{
	ENTITY_ID id;
	PZERO(&id,sizeof(id));
	if(entityID_PTR == nullptr) return id;
	return *entityID_PTR;
}

char buffer[4096];
void _cdecl SYSTEM_API::Trace(char * data_PTR,...)
{
	va_list args;
	va_start(args,data_PTR);
	_vsnprintf_s(buffer,sizeof(buffer) - 4,data_PTR,args);
	va_end(args);
	trace(buffer);
	strcat_s(buffer,"\x0d\x0a");
	OutputDebugString(buffer);
}

void SYSTEM_API::SetX()
{
	Exceptions = true;
}

void SYSTEM_API::SetXNF()
{
	ExceptionsNF = true;
}

void * SYSTEM_API::GetCoreApi()
{
	return api;
}

void * SYSTEM_API::CreateService(const char * pServiceName)
{
	return api->CreateService((char*)pServiceName);
}
