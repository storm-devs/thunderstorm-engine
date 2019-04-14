#pragma once

#include <exception>

class VBUFFER
{
	uint32_t dwSize;
public:
	char * Ptr;
	 VBUFFER() {dwSize = 0; Ptr = nullptr;}
	~VBUFFER() { free(Ptr);}
	void Size(uint32_t _size)
	{
		Ptr = static_cast<char*>(realloc(Ptr, _size));
		if(!Ptr) throw std::exception(); 
		dwSize = _size; };
};