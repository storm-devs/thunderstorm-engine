#ifndef _ENTITY_STATE_R_H_
#define _ENTITY_STATE_R_H_

#include <Windows.h>
#include "../../Common_h/entity_state.h"
#include "../../Common_h/vfile_service.h"
#include <vector>

#define INITIAL_BUFFER_SIZE		1024

class ENTITY_STATE_GEN_R : public ENTITY_STATE_GEN
{
	HANDLE file_handle;
	VFILE_SERVICE * fio;
	std::vector<char> Buffer;
	uint32_t  Buffer_size;
	uint32_t  Data_size;
	char * Format_string;
	va_list args;

	void CopyData(uint32_t add_data_size);
	void VerifyFreeSpace(uint32_t add_data_size);

public:
	ENTITY_STATE_GEN_R();
	virtual ~ENTITY_STATE_GEN_R();
	void Init(VFILE_SERVICE * _fio,HANDLE _file_handle);
	void CloseState();
	void _cdecl SetState(char * Format,...);
};

class ENTITY_STATE_R : public ENTITY_STATE
{
	HANDLE file_handle;
	VFILE_SERVICE * fio;

	char * Format_string;
	char * Buffer;
	uint32_t  Buffer_size;
	uint32_t  Data_size;
	uint32_t  Format_index;
	uint32_t  Data_index;
	char * Data_PTR;
	void LoadStateBlock();
	void ValidateFormat(char c);

public:
	ENTITY_STATE_R();
	virtual ~ENTITY_STATE_R();
	void Init(VFILE_SERVICE * _fio,HANDLE _file_handle);

	uint8_t	Byte();
	uint16_t	Word();
	long	Long();
	uint32_t	Dword();
	float	Float();
	double	Double();
	char *	Pointer(); 
	void	String(uint32_t dest_buffer_size,char * buffer);
	void	MemoryBlock(uint32_t memsize, char * buffer);
	void	Struct(uint32_t sizeofstruct, char * s); 
};

#endif