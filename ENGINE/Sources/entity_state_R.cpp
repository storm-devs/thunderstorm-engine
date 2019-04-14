#include "entity_state_R.h"

const char Signature[] = "ES";
char Signature_Buff[] = "ES";


ENTITY_STATE_GEN_R::ENTITY_STATE_GEN_R()
{
	Buffer_size = 0;
	Data_size = 0;
	Format_string = nullptr;
}

ENTITY_STATE_GEN_R::~ENTITY_STATE_GEN_R()
{
	free(Format_string);
}

void ENTITY_STATE_GEN_R::Init(VFILE_SERVICE * _fio,HANDLE _file_handle)
{
	//GUARD(ENTITY_STATE_GEN_R::Init)
	fio = _fio;
	if(fio == nullptr) throw std::exception();
	file_handle = _file_handle;
	if(file_handle == INVALID_HANDLE_VALUE) throw std::exception();
	//UNGUARD
}

void ENTITY_STATE_GEN_R::CloseState()
{
	//GUARD(ENTITY_STATE_GEN_R::CloseState)
	uint32_t sizeofstruct;
	uint32_t dwR;

	// if no state data - return
	if(Format_string == nullptr) return;

	// write signature
	sizeofstruct = strlen(Signature);
	fio->_WriteFile(file_handle,Signature,sizeofstruct,&dwR);
	if(dwR != sizeofstruct) throw std::exception();

	// write size of format string
	if(Format_string == nullptr) sizeofstruct = 0;
	else sizeofstruct = strlen(Format_string) + 1;
	fio->_WriteFile(file_handle,&sizeofstruct,sizeof(sizeofstruct),&dwR);
	if(dwR != sizeof(sizeofstruct)) throw std::exception();
	
	// write format string
	fio->_WriteFile(file_handle,Format_string,sizeofstruct,&dwR);
	if(dwR != sizeofstruct) throw std::exception();

	// write data size
	fio->_WriteFile(file_handle,&Data_size,sizeof(Data_size),&dwR);
	if(dwR != sizeof(Data_size)) throw std::exception();

	// write data
	fio->_WriteFile(file_handle,Buffer.data(),Data_size,&dwR);
	if(dwR != Data_size) throw std::exception();

	// reset buffer pointer and format string
	Data_size = 0;
	free(Format_string);
	Format_string = nullptr;

	//UNGUARD
}

#define _COPY_DATA(t) {CopyData(sizeof(t));}

void ENTITY_STATE_GEN_R::VerifyFreeSpace(uint32_t add_data_size)
{
	//GUARD(ENTITY_STATE_GEN_R::VerifyFreeSpace)
	if((Data_size + add_data_size) >= Buffer_size) 
	{
		Buffer_size <<= 1;
		Buffer.resize(Buffer_size);
	}
	//UNGUARD
}


void ENTITY_STATE_GEN_R::CopyData(uint32_t add_data_size)
{
	//GUARD(ENTITY_STATE_GEN_R::CopyData)
	VerifyFreeSpace(add_data_size);
	memcpy(Buffer.data() + Data_size,(char *)args,add_data_size);
	args += add_data_size;
	Data_size += add_data_size;
	//UNGUARD
}

void _cdecl ENTITY_STATE_GEN_R::SetState(char * Format,...)
{
	//GUARD(ENTITY_STATE_GEN_R::SetState)
	uint32_t n;
	char * tcharPTR;
	uint32_t sizeofstruct;

	// upload or append format string
	if(!Format) throw std::exception("empty format string");
	if(Format_string == nullptr)
	{
		const auto len = strlen(Format) + 1;
		Format_string = (char *)malloc(len);
		if(Format_string == nullptr) throw std::exception();
		memcpy(Format_string,Format,len);
	} else
	{
		const auto len = strlen(Format_string) + strlen(Format) + 1;
		Format_string = (char *)realloc(Format_string,len);
		if(Format_string == nullptr) throw std::exception();
		strcat_s(Format_string,len,Format);
	}

	// allocate memory for buffer, if mem still not allocated
	if(Buffer.empty())
	{
		Buffer_size = INITIAL_BUFFER_SIZE;
		Buffer.resize(Buffer_size);
	}

	// read data to buffer
	//va_list args;
	va_start(args,Format);
	for(n=0;Format[n];n++)
	{
		switch(Format[n])
		{
			case 'b': _COPY_DATA(uint8_t); break;
			case 'w': _COPY_DATA(uint16_t); break;
			case 'l': _COPY_DATA(long); break;
			case 'u': _COPY_DATA(uint32_t); break;
			case 'f': _COPY_DATA(float); break;
			case 'd': _COPY_DATA(double); break;
			case 'p': _COPY_DATA(char *); break;
			case 's':
				VerifyFreeSpace(sizeof(uint32_t));
				tcharPTR = va_arg(args,char*);
				sizeofstruct = strlen(tcharPTR) + 1;
				memcpy(Buffer.data() + Data_size,(char *)&sizeofstruct,sizeof(uint32_t));
				Data_size += sizeof(uint32_t);
				VerifyFreeSpace(sizeofstruct);
				memcpy(Buffer.data() + Data_size,tcharPTR,sizeofstruct);
				Data_size += sizeofstruct;
			break;
			case 'm':
				VerifyFreeSpace(sizeof(uint32_t));
				sizeofstruct = va_arg(args,uint32_t);
				memcpy(Buffer.data() + Data_size,(char *)&sizeofstruct,sizeof(uint32_t));
				Data_size += sizeof(uint32_t);
				VerifyFreeSpace(sizeofstruct);
				tcharPTR = va_arg(args,char*);
				memcpy(Buffer.data() + Data_size,tcharPTR,sizeofstruct);
				Data_size += sizeofstruct;
			break;
			case 'v':
				VerifyFreeSpace(sizeof(uint32_t));
				sizeofstruct = va_arg(args,uint32_t);
				memcpy(Buffer.data() + Data_size,(char *)&sizeofstruct,sizeof(uint32_t));
				Data_size += sizeof(uint32_t);
				VerifyFreeSpace(sizeofstruct);
				memcpy(Buffer.data() + Data_size,(char *)args,sizeofstruct);
				Data_size += sizeofstruct;
				args += ((sizeofstruct + sizeof(int) - 1) & ~(sizeof(int) - 1));
			break;
			default: throw std::exception("invalid format string specificator");
			break;

		}

	}

	va_end(args);
	//UNGUARD
}
ENTITY_STATE_R::ENTITY_STATE_R()
{
	Format_string = nullptr;
	Buffer = nullptr;
	Buffer_size = 0;
	Format_index = 0;
}

ENTITY_STATE_R::~ENTITY_STATE_R()
{
	free(Format_string);
	free(Buffer);
}

void ENTITY_STATE_R::Init(VFILE_SERVICE * _fio,HANDLE _file_handle)
{
	//uint32_t sizeofstruct;
	//uint32_t dwR;
	//GUARD(ENTITY_STATE_R::Init)
	fio = _fio;
	if(fio == nullptr) throw std::exception();
	file_handle = _file_handle;
	if(file_handle == INVALID_HANDLE_VALUE) throw std::exception();

	//UNGUARD
}

void ENTITY_STATE_R::LoadStateBlock()
{
	//GUARD(ENTITY_STATE_R::LoadStateBlock)
	uint32_t format_size;
	uint32_t sizeofstruct;
	uint32_t dwR;

	free(Format_string); Format_string = nullptr;
	Format_index = 0;
	Data_index = 0;
	Data_PTR = nullptr;
	// read block signature
	sizeofstruct = strlen(Signature);
	fio->_ReadFile(file_handle,Signature_Buff,sizeofstruct,&dwR);
	if(dwR != sizeofstruct) throw std::exception();
	if(memcmp(Signature,Signature_Buff,strlen(Signature)) != 0) throw std::exception("invalid signature");

	// read size of format string
	fio->_ReadFile(file_handle,&format_size,sizeof(format_size),&dwR);
	if(dwR != sizeof(format_size)) throw std::exception();
	if(format_size == 0) throw std::exception("empty block");

	// allocate mem for format string

	Format_string = (char *)new char[format_size];
	if(!Format_string) throw std::exception();

	// read format string
	fio->_ReadFile(file_handle,Format_string,format_size,&dwR);
	if(dwR != format_size) throw std::exception();

	// read data size
	fio->_ReadFile(file_handle,&Data_size,sizeof(Data_size),&dwR);
	if(dwR != sizeof(Buffer_size)) throw std::exception();

	// allocate or resize mem for data
	if(Buffer == nullptr)
	{
		Buffer_size = Data_size;

		Buffer = (char *)malloc(Buffer_size);
		if(!Buffer) throw std::exception();
	}
	else
	{
		if(Buffer_size < Data_size)
		{
			Buffer = (char *)realloc(Buffer,Data_size);
			if(!Buffer) throw std::exception();
			Buffer_size = Data_size;
		}
	}
	Data_PTR = Buffer;

	// read data
	fio->_ReadFile(file_handle,Buffer,Data_size,&dwR);
	if(dwR != Data_size) throw std::exception();

	//UNGUARD
}

void ENTITY_STATE_R::ValidateFormat(char c)
{
	//GUARD(ENTITY_STATE_R::ValidateFormat)
	if(Format_string)
	if(Format_index >= strlen(Format_string))
	{
		free(Format_string); Format_string = nullptr;
		Format_index = 0;
	}
	if(Format_string == nullptr) LoadStateBlock();
	if(Format_string == nullptr) throw std::exception("no state data");
	if(Format_string[Format_index] != c) throw std::exception("incorrect state data");
	Format_index++;
	//UNGUARD
}

//#define RETURN_DATA(t) {Data_index += sizeof(t);if(Data_index > Data_size) throw std::exception(no data);return (*(t *)(Buffer[Data_index - sizeof(t)]));}
#define RETURN_DATA(t) {Data_PTR += sizeof(t);if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data"); return (*(t *)(Data_PTR - sizeof(t)));}
//#define RETURN_DATA2(c,t) {ValidateFormat(#@c);Data_index += sizeof(t);if(Data_index > Data_size) throw std::exception(no data);return (*(t *)(Buffer[Data_index - sizeof(t)]));}
uint8_t ENTITY_STATE_R::Byte()
{
	ValidateFormat('b');
	RETURN_DATA(uint8_t);
	
	//RETURN_DATA2(b,byte);
	/*Data_index += sizeof(byte); 
	if(Data_index > Data_size) throw std::exception(no data);	
	return (*(byte *)(Buffer[Data_index - sizeof(byte)]));*/
}

uint16_t ENTITY_STATE_R::Word()
{
	ValidateFormat('w');
	RETURN_DATA(uint16_t);
}

long ENTITY_STATE_R::Long()
{
	ValidateFormat('l');
	RETURN_DATA(long);
}

uint32_t ENTITY_STATE_R::Dword()
{
	ValidateFormat('u');
	RETURN_DATA(uint32_t);
}

float	ENTITY_STATE_R::Float()
{
	ValidateFormat('f');
	RETURN_DATA(float);
}

double	ENTITY_STATE_R::Double()
{
	ValidateFormat('d');
	RETURN_DATA(double);
}

char *	ENTITY_STATE_R::Pointer()
{
	ValidateFormat('p');
	RETURN_DATA(char*);
}

void ENTITY_STATE_R::String(uint32_t dest_buffer_size, char * buffer)
{
	//GUARD(ENTITY_STATE_R::String)
	uint32_t size;
	if(buffer == nullptr) throw std::exception("invalid buffer");
	ValidateFormat('s');
	Data_PTR += sizeof(uint32_t); 
	if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data");
	size = (*(uint32_t *)(Data_PTR - sizeof(uint32_t)));
	Data_PTR += size; 
	if(size > dest_buffer_size) throw std::exception("insufficient string buffer");
	memcpy(buffer,(char *)(Data_PTR - size),size);
	//UNGUARD
}

void ENTITY_STATE_R::MemoryBlock(uint32_t memsize, char * buffer)
{
	//GUARD(ENTITY_STATE_R::MemoryBlock)
	uint32_t size;
	if(buffer == nullptr) throw std::exception("invalid buffer");
	ValidateFormat('m');
	Data_PTR += sizeof(uint32_t); 
	if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data");
	size = (*(uint32_t *)(Data_PTR - sizeof(uint32_t)));
	if(size != memsize) throw std::exception("invalid buffer size");
	Data_PTR += size; 
	if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data");
	memcpy(buffer,(char *)(Data_PTR - size),size);
	//UNGUARD
}

void ENTITY_STATE_R::Struct(uint32_t memsize, char * buffer)
{
	//GUARD(ENTITY_STATE_R::Struct)
	uint32_t size;
	if(buffer == nullptr) throw std::exception("invalid buffer");
	ValidateFormat('v');
	Data_PTR += sizeof(uint32_t); 
	if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data");
	size = (*(uint32_t *)(Data_PTR - sizeof(uint32_t)));
	if(size != memsize) throw std::exception("invalid structure size");
	Data_PTR += size; 
	if(Data_PTR > (Buffer + Data_size)) throw std::exception("no data");
	memcpy(buffer,(char *)(Data_PTR - size),size);
	//UNGUARD

}
