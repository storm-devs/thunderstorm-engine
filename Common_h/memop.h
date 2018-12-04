#pragma once

extern void * _cdecl operator new(size_t size);
extern void _cdecl operator delete(void * block_ptr);
extern void * _cdecl resize(void *,size_t size);
extern void * _cdecl operator new(size_t size,char *,unsigned long);
extern void _cdecl operator delete(void * block_ptr,char *,unsigned long);
extern void * _cdecl resize(void *,size_t size,char *,unsigned long);

#define NEW new(__FILE__,__LINE__)
#define RESIZE(p,n) resize(p,n,__FILE__,__LINE__)