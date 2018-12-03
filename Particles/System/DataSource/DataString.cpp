#include "DataString.h"
#include "../../ICommon/MemFile.h"
#include "../../../Common_h/vmodule_api.h"


//конструктор/деструктор
DataString::DataString ()
{
}

DataString::~DataString ()
{
}

//Получить значение
const char* DataString::GetValue ()
{
	return Value.c_str();
}

//Установить значение
void DataString::SetValue (const char* val)
{
	Value = val;
}

void DataString::Load (MemFile* File)
{
	static char TempString[128];
	File->Read(TempString, 128);
	SetValue(TempString);

	static char AttribueName[128];
	uint32_t NameLength = 0;
	File->ReadType(NameLength);
	Assert (NameLength < 128);
	File->Read(AttribueName, NameLength);

	SetName (AttribueName);
}

void DataString::SetName (const char* szName)
{
	//api->Trace("DataString::SetName - '%s'", szName);
	Name = szName;
}

const char* DataString::GetName ()
{
	return Name.c_str();
}

void DataString::Write (MemFile* File)
{
	static char WriteTempString[128];
	memset (WriteTempString, 0, 128);
	strncpy (WriteTempString, GetValue (), 128);
	File->Write(WriteTempString, 128);

	//save name
	uint32_t NameLength = Name.size();
	uint32_t NameLengthPlusZero = NameLength+1;
	File->WriteType(NameLengthPlusZero);
	Assert (NameLength < 128);
	File->Write(Name.c_str(), NameLength);
	File->WriteZeroByte();
}
