#ifndef _PARTICLE_DATA_BOOLEAN_H_
#define _PARTICLE_DATA_BOOLEAN_H_

#include "../../ICommon/MemFile.h"
#include <string>


class DataBool
{
	std::string Name;
  

	bool Value;

public:

//�����������/����������
	DataBool ();
	virtual ~DataBool ();

//�������� ��������
	bool GetValue ();

//���������� ��������
	void SetValue (bool val);


//���������/���������...
	void Load (MemFile* File);
	void Write (MemFile* File);


	void SetName (const char* szName);
	const char* GetName ();


};


#endif