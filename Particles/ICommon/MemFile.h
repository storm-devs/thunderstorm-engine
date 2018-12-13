//Класс для работы с памятью как с файлом...

#ifndef _MEMORY_FILE_
#define _MEMORY_FILE_

#include <cstdint>
#include <cstring>

#define VFSEEK_SET          (0x00000000)
#define VFSEEK_CURRENT      (0x00000001)
#define VFSEEK_END          (0x00000002)


class MemFile
{
	bool DataIsMy;

	uint8_t* Data;
	uint32_t MaxLen;
	uint32_t CurPos;
	uint32_t BiggestWritePos;

public:

	MemFile::MemFile ()
	{
		DataIsMy = false;
		Data = nullptr;
		MaxLen = 0;
		CurPos = 0;
		BiggestWritePos = 0;
	}

	MemFile::~MemFile ()
	{
		Close ();
	}

	inline bool Compare (MemFile* pMemfile)
	{
		if (GetLength () != pMemfile->GetLength()) return false;

		for (uint32_t i = 0; i < GetLength(); i++)
		{
			uint8_t* Buffer1 = (uint8_t*)GetBuffer();
			uint8_t* Buffer2 = (uint8_t*)pMemfile->GetBuffer();

			if (Buffer1[i] != Buffer2[i]) return false;
		}

		return true;
	}

	inline void OpenRead (void* Data, uint32_t DataSize)
	{
		DataIsMy = false;
		this->Data = (uint8_t*)Data;
		MaxLen = DataSize;
		CurPos = 0;
	}

	inline void OpenWrite (uint32_t MaxSize)
	{
		DataIsMy = true;
		Data = new uint8_t[MaxSize];
		memset (Data, 0, MaxSize);
		MaxLen = MaxSize;
		CurPos = 0;
	}


	inline uint32_t MemFile::Tell ()
	{
		return CurPos;
	}

	inline uint32_t MemFile::GetLength ()
	{
		if (DataIsMy) return BiggestWritePos;
		return MaxLen;
	}

	inline void MemFile::Seek (int NewPos, uint32_t flags)
	{
		switch (flags)
		{
		case VFSEEK_SET:
			CurPos = NewPos;
			break;
		case VFSEEK_CURRENT:
			CurPos +=	NewPos;
			break;
		case VFSEEK_END:
			CurPos = GetLength() + NewPos;
			break;
		}
	}

	inline void MemFile::Close ()
	{
		if (DataIsMy)
		{
			delete Data;
			Data = nullptr;
		}
	}


	inline uint32_t MemFile::Read (void* Buffer, uint32_t size)
	{
		if (!Data) return 0;
		uint32_t real_size = CurPos+size;
		if (real_size > MaxLen)	size = size - (real_size - MaxLen);
		if (size <= 0) return 0;
		memcpy (Buffer, (Data + CurPos), size);
		CurPos+=size;
		return size;
	}

	inline uint32_t MemFile::WriteZeroByte ()
	{
		uint8_t Zero = 0;
		return Write (&Zero, 1);
	}


	inline uint32_t MemFile::Write (const void* Buffer, uint32_t size)
	{
		if (!DataIsMy) return 0;
		if (!Data) return 0;

		uint32_t real_size = CurPos+size;
		if (real_size > MaxLen)	size = size - (real_size - MaxLen);
		if (size <= 0) return 0;

		memcpy ((Data + CurPos), Buffer, size);
		CurPos+=size;
		if (CurPos > BiggestWritePos) BiggestWritePos = CurPos;
		return size;
	}


	template <class TYPE>
	inline uint32_t WriteType(TYPE &Val)
	{
		return Write(&Val, sizeof(TYPE));
	}

	template <class TYPE>
	inline uint32_t ReadType(TYPE &Val)
	{
		return Read(&Val, sizeof(TYPE));
	}

	inline void* GetBuffer ()
	{
		return Data;
	}
 
};







#endif