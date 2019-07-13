#include "defines.h"
#include "FieldList.h"
#include "DataBool.h"
#include "DataColor.h"
#include "DataFloat.h"
#include "DataGraph.h"
#include "DataPosition.h"
#include "DataUV.h"
#include "DataString.h"


FieldList::FieldList ()
{
}

FieldList::~FieldList ()
{
	//DelAll ();
}

void FieldList::Load (MemFile* File)
{
	uint32_t DataFieldsCount = 0;
	File->ReadType(DataFieldsCount);

	for (uint32_t n = 0; n < DataFieldsCount; n++)
	{
		FieldType fldType = FIELD_UNKNOWN;
		File->ReadType(fldType);

		switch (fldType)
		{
			case FIELD_BOOL:
			{
				//api->Trace ("Particles info: BOOL field");
				CreateBoolField (File);
				break;
			}
			case FIELD_FLOAT:
			{
				//api->Trace ("Particles info: FLOAT field");
				CreateFloatField (File);
				break;
			}
			case FIELD_GRAPH:
			{
				//api->Trace ("Particles info: GRAPH field");
				CreateGraphField (File);
				break;
			}
			case FIELD_POSITION:
			{
				//api->Trace ("Particles info: POSITION field");
				CreatePositionField (File);
				break;
			}
			case FIELD_STRING:
			{
				//api->Trace ("Particles info: STRING field");
				CreateStringField (File);
				break;
			}
			case FIELD_UV:
			{
				//api->Trace ("Particles info: UV field");
				CreateUVField (File);
				break;
			}
			case FIELD_COLOR:
			{
				//api->Trace ("Particles info: COLOR field");
				CreateColorField (File);
				break;
			}
			default:
			{
				throw std::exception("Particles: Unknown field type !!!!");
			}
		}	//switch
	} // for all fileds
}



void FieldList::CreateEmptyBoolField (const char* Name, bool def_value)
{
	DataBool* Field = new DataBool;
	Field->SetName(Name);
	Field->SetValue(def_value);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_BOOL;
	Fields.push_back(pDesc);
}

void FieldList::CreateEmptyFloatField (const char* Name, float def_value)
{
	DataFloat* Field = new DataFloat;
	Field->SetName(Name);
	Field->SetValue(def_value);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_FLOAT;
	Fields.push_back(pDesc);
}

void FieldList::CreateEmptyGraphField (const char* Name, float def_value_min, float def_value_max)
{
	DataGraph* Field = new DataGraph;
	Field->SetName(Name);
	Field->SetDefaultValue(def_value_max, def_value_min);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_GRAPH;
	Fields.push_back(pDesc);
}

void FieldList::CreateEmptyPositionField (const char* Name, const Vector& def_value)
{
	DataPosition* Field = new DataPosition;
	Field->SetName(Name);
	Field->SetValue(def_value);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_POSITION;
	Fields.push_back(pDesc);
}

void FieldList::CreateEmptyStringField (const char* Name, const char* def_value)
{
	DataString* Field = new DataString;
	Field->SetName(Name);
	Field->SetValue(def_value);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_STRING;
	Fields.push_back(pDesc);

}

void FieldList::CreateEmptyUVField (const char* Name)
{
	DataUV* Field = new DataUV;
	Field->SetName(Name);
	Field->SetValues(&Vector4(0.0f, 0.0f, 1.0f, 1.0f), 1);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_UV;
	Fields.push_back(pDesc);
}

void FieldList::CreateEmptyColorField (const char* Name, uint32_t def_value)
{
	DataColor* Field = new DataColor;
	Field->SetName(Name);
	ColorVertex defVal[2];
	defVal[0].MinValue = def_value;
	defVal[0].MaxValue = def_value;
	defVal[1].MinValue = def_value;
	defVal[1].MaxValue = def_value;
	Field->SetValues(defVal, 2);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_COLOR;
	Fields.push_back(pDesc);
}


void FieldList::CreateBoolField (MemFile* pMemFile)
{
	DataBool* Field = new DataBool;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_BOOL;
	Fields.push_back(pDesc);
}

void FieldList::CreateFloatField (MemFile* pMemFile)
{
	DataFloat* Field = new DataFloat;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_FLOAT;
	Fields.push_back(pDesc);
}

void FieldList::CreateGraphField (MemFile* pMemFile)
{
	DataGraph* Field = new DataGraph;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_GRAPH;
	Fields.push_back(pDesc);
}

void FieldList::CreatePositionField (MemFile* pMemFile)
{
	DataPosition* Field = new DataPosition;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_POSITION;
	Fields.push_back(pDesc);
}

void FieldList::CreateStringField (MemFile* pMemFile)
{
	DataString* Field = new DataString;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_STRING;
	Fields.push_back(pDesc);
}

void FieldList::CreateUVField (MemFile* pMemFile)
{
	DataUV* Field = new DataUV;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_UV;
	Fields.push_back(pDesc);
}

void FieldList::CreateColorField (MemFile* pMemFile)
{
	DataColor* Field = new DataColor;
	Field->Load(pMemFile);

	FieldDesc pDesc;
	pDesc.MarkForDelete = false;
	pDesc.Name = Field->GetName();
	pDesc.HashValue = TOREMOVE::HashNoCase(pDesc.Name.c_str());
	pDesc.pPointer = Field;
	pDesc.Type = FIELD_COLOR;
	Fields.push_back(pDesc);
}

void FieldList::DelAll ()
{
	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		DeleteFieldData (Fields[n]);
	} // loop

	Fields.clear();
}


DataColor* FieldList::FindColor (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);
	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_COLOR)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataColor*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataBool* FieldList::FindBool (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);
	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_BOOL)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataBool*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataFloat* FieldList::FindFloat (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);
	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_FLOAT)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataFloat*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataGraph* FieldList::FindGraph (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);

	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_GRAPH)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataGraph*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataString* FieldList::FindString (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);

	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_STRING)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataString*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataPosition* FieldList::FindPosition (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);

	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_POSITION)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataPosition*)Fields[n].pPointer);
				}
			}
		}
	}

	return nullptr;
}

DataUV* FieldList::FindUV (const char* AttrName)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(AttrName);

	for (uint32_t n = 0; n < Fields.size(); n++)
	{
		if (Fields[n].Type == FIELD_UV)
		{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), AttrName) == 0)
				{
					return ((DataUV*)Fields[n].pPointer);
				}
			}
		}
	}
	return nullptr;
}

FieldList::FieldDesc* FieldList::FindField (const char* Name)
{
	uint32_t SearchHash = TOREMOVE::HashNoCase(Name);

	for (uint32_t n = 0; n < Fields.size(); n++)
	{
			if (SearchHash == Fields[n].HashValue)
			{
				if (_stricmp (Fields[n].Name.c_str(), Name) == 0)
				{
					return &Fields[n];
				}
			}
	}
	return nullptr;
}

float FieldList::GetFloat (const char* AttrName, float def_value)
{
	DataFloat* pFind = FindFloat(AttrName);
	if (!pFind) return def_value;
	return pFind->GetValue();
}

int FieldList::GetFloatAsInt (const char* AttrName, int def_value)
{
	float val = GetFloat(AttrName, (float)def_value);
	return (int)val;
}


bool FieldList::GetBool (const char* AttrName, bool def_value)
{
	DataBool* pFind = FindBool(AttrName);
	if (!pFind) return def_value;
	return pFind->GetValue();
}

const char* FieldList::GetString (const char* AttrName, const char* def_value)
{
	DataString* pFind = FindString(AttrName);
	if (!pFind) return def_value;
	return pFind->GetValue();
}

const Vector& FieldList::GetPosition (const char* AttrName, const Vector& def_value)
{
	DataPosition* pFind = FindPosition(AttrName);
	if (!pFind) return def_value;
	return pFind->GetValue();
}

float FieldList::GetGraphVal (const char* AttrName, float Time, float LifeTime, float K_Rand, float def_value)
{
	DataGraph* pFind = FindGraph(AttrName);
	if (!pFind) return def_value;
	return pFind->GetValue(Time, LifeTime, K_Rand);
}

float FieldList::GetRandomGraphVal (const char* AttrName, float Time, float LifeTime, float def_value)
{
	DataGraph* pFind = FindGraph(AttrName);
	if (!pFind) return def_value;
	return pFind->GetRandomValue(Time, LifeTime);
}

uint32_t FieldList::GetFieldCount ()
{
	return Fields.size();
}

const FieldList::FieldDesc& FieldList::GetFieldByIndex (uint32_t Index)
{
	return Fields[Index];
}


void FieldList::Convert (DataDescripion* pDataDescriptor)
{
	for (uint32_t i = 0; i < Fields.size(); i++)
	{
		Fields[i].MarkForDelete = true;
	}

	uint32_t NeedFieldsCount = pDataDescriptor->GetFieldCount();

	for (uint32_t n = 0; n < NeedFieldsCount; n++)
	{
		const char* NeedFieldName = pDataDescriptor->GetFieldName(n);
		FieldType NeedFieldType = pDataDescriptor->GetFieldType(n);
		FieldDesc* pDesc = FindField (NeedFieldName);
		bool FieldExist = false;
		if (pDesc)
		{
			if (pDesc->Type == NeedFieldType)
			{
				//���� ����� ���� � ��� ������� ����, ������� ������� �� ��������
				pDesc->MarkForDelete = false;
				FieldExist = true;
			}
		}

		//���� ���� �� ����������, ���� ��� �������...
		if (!FieldExist)
		{
			switch (NeedFieldType)
			{
			case FIELD_COLOR:
				CreateEmptyColorField(NeedFieldName, 0xFFFFA030);
				break;
			case FIELD_BOOL:
				CreateEmptyBoolField(NeedFieldName, false);
				break;
			case FIELD_FLOAT:
				CreateEmptyFloatField(NeedFieldName, 0.0f);
				break;
			case FIELD_GRAPH:
				CreateEmptyGraphField(NeedFieldName, 0.0f, 0.0f);
				break;
			case FIELD_POSITION:
				CreateEmptyPositionField(NeedFieldName, Vector(0.0f));
				break;
			case FIELD_UV:
				CreateEmptyUVField(NeedFieldName);
				break;
			case FIELD_STRING:
				CreateEmptyStringField(NeedFieldName, "###");
				break;
			default:
				throw std::exception("Unknown Field type !!!");
			}
		}
	}

	for (uint32_t i = 0; i < Fields.size(); i++)
	{
		if (Fields[i].MarkForDelete)
		{
			DeleteFieldData (Fields[i]);
			//Fields.ExtractNoShift(i);
			Fields[i] = Fields.back();
			Fields.pop_back();
			i--;
		}
	}

}

void FieldList::DeleteFieldData (const FieldList::FieldDesc& pData)
{
	FieldType fldType = pData.Type;

	switch (fldType)
	{
	case FIELD_BOOL:
		{
			delete ((DataBool*)pData.pPointer);
			break;
		}
	case FIELD_FLOAT:
		{
			delete ((DataFloat*)pData.pPointer);
			break;
		}
	case FIELD_GRAPH:
		{
			delete ((DataGraph*)pData.pPointer);
			break;
		}
	case FIELD_POSITION:
		{
			delete ((DataPosition*)pData.pPointer);
			break;
		}
	case FIELD_STRING:
		{
			delete ((DataString*)pData.pPointer);
			break;
		}
	case FIELD_UV:
		{
			delete ((DataUV*)pData.pPointer);
			break;
		}
	case FIELD_COLOR:
		{
			delete ((DataColor*)pData.pPointer);
			break;
		}
	default:
		{
			throw std::exception("Particles: Try delete unknown field type !!!!");
		}
	}	//switch
}


void FieldList::Write (MemFile* File)
{
	uint32_t DataFieldsCount = Fields.size();
	File->WriteType(DataFieldsCount);


	for (uint32_t n = 0; n < DataFieldsCount; n++)
	{
		File->WriteType(Fields[n].Type);

		switch (Fields[n].Type)
		{
			case FIELD_BOOL:
				{
					DataBool* pBoolField = (DataBool*)Fields[n].pPointer;
					pBoolField->Write (File);
					break;
				}
			case FIELD_FLOAT:
				{
					DataFloat* pFloatField = (DataFloat*)Fields[n].pPointer;
					pFloatField->Write (File);
					break;
				}
			case FIELD_GRAPH:
				{
					DataGraph* pGraphField = (DataGraph*)Fields[n].pPointer;
					pGraphField->Write (File);
					break;
				}
			case FIELD_POSITION:
				{
					DataPosition* pPositionField = (DataPosition*)Fields[n].pPointer;
					pPositionField->Write (File);
					break;
				}
			case FIELD_STRING:
				{
					DataString* pStringField = (DataString*)Fields[n].pPointer;
					pStringField->Write (File);
					break;
				}
			case FIELD_UV:
				{
					DataUV* pUVField = (DataUV*)Fields[n].pPointer;
					pUVField->Write (File);
					break;
				}
			case FIELD_COLOR:
				{
					DataColor* pColorField = (DataColor*)Fields[n].pPointer;
					pColorField->Write (File);
					break;
				}
			default:
				{
					throw std::exception("Particles: Unknown field type !!!!");
				}
		}	//switch
	} // loop

}
