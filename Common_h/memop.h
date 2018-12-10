#pragma once
#include <cstddef>

// not overriding align_val_t versions cause system runtime crash (C++17)

extern void * operator new(std::size_t count);
extern void * operator new(std::size_t count, std::align_val_t al);

extern void operator delete(void* ptr) noexcept;
extern void operator delete(void* ptr, std::align_val_t al) noexcept;
extern void operator delete(void* ptr, std::size_t sz, std::align_val_t al) noexcept;

#define NEW new
#define RESIZE(x,y) realloc(x,y)