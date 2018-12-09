#pragma once
#include <cstddef>

// not overriding align_val_t versions cause system runtime crash (C++17)

extern void * operator new(std::size_t count);
extern void * operator new(std::size_t count, std::align_val_t al);

extern void operator delete(void* ptr) noexcept;
extern void operator delete(void* ptr, std::align_val_t al) noexcept;
extern void operator delete(void* ptr, std::size_t sz, std::align_val_t al) noexcept;

extern void * operator new(std::size_t count, char * file, std::size_t line);
extern void * operator new(std::size_t count, std::align_val_t al, char * file, std::size_t line);
extern void operator delete(void * ptr, char * file, std::size_t line) noexcept;

extern void * resize(void *, std::size_t size);
extern void * resize(void *, std::size_t size, char *file, std::size_t line);

#define NEW new(__FILE__,__LINE__)
#define RESIZE(p,n) resize(p,n,__FILE__,__LINE__)