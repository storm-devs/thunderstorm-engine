#ifndef _MEMOP_H_
#define _MEMOP_H_
#include <cstddef>

// not overriding align_val_t versions cause system runtime crash (C++17)

extern void * __cdecl operator new(size_t count);
extern void * __cdecl operator new (size_t count, std::align_val_t al);

extern void __cdecl operator delete(void* ptr) noexcept;
extern void __cdecl operator delete(void* ptr, std::align_val_t al) noexcept;
extern void __cdecl operator delete(void* ptr, size_t sz, std::align_val_t al) noexcept;

extern void * __cdecl operator new(size_t count, char * file, size_t line);
extern void __cdecl operator delete(void * ptr, char * file, size_t line) noexcept;

extern void * __cdecl resize(void *, size_t size);
extern void * __cdecl resize(void *, size_t size, char *file, size_t line);

#define NEW new(__FILE__,__LINE__)
#define RESIZE(p,n) resize(p,n,__FILE__,__LINE__)

#endif