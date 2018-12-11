#include "s_stack.h"
#include "../../Common_h/Exs.h"
#include "../../Common_h/memop.h"
#include "../../Common_h/vapi.h"

extern void trace(char * p,...);
extern VAPI * api;

S_STACK::S_STACK()
{
	Buffer_size = 0;
	Data_num = 0;
	pVCompiler = nullptr;
}

S_STACK::~S_STACK()
{
	Release();
}

void S_STACK::Release()
{
	uint32_t n;
	for(n=0;n<Buffer_size;n++)
	{
		delete pStackData[n];
		//pStackData[n].~DATA();
	}
	pStackData.clear();
	Buffer_size = 0;
	Data_num = 0;
}

DATA * S_STACK::Push(DATA * pdataclass)
{
	uint32_t offset,n;

	if(Data_num > 1000)
	{
		Data_num = Data_num;
	}
	if(Data_num > STACK_BUFFER_LIMIT) STORM_THROW(stack overflaw);
	if(Data_num >= Buffer_size)
	{
		offset = Buffer_size;
		Buffer_size += STACK_BUFFER_BLOCK_SIZE;
		pStackData.resize(Buffer_size);
		//trace("stack: %d",Buffer_size);
		for(n=offset;n<Buffer_size;n++)
		{
			//new(&pStackData[n]) DATA;
			pStackData[n] = NEW DATA;
			//pStackData[n].SetVCompiler(pVCompiler);
			pStackData[n]->SetVCompiler(pVCompiler);
		}
	}
	pStackData[Data_num]->ClearType();
	pStackData[Data_num]->SetType(UNKNOWN);
	if(pdataclass) 
	{
		pStackData[Data_num]->Copy(pdataclass);
	}
	Data_num++;
	//return &pStackData[Data_num - 1];
	return pStackData[Data_num - 1];
}

DATA * S_STACK::Pop()
{
	Assert(Data_num);
	if(Data_num == 0) STORM_THROW(stack 'pop' error);
	Data_num--;
	//return &pStackData[Data_num];

	/*if(pStackData[Data_num]->GetType() == VAR_OBJECT)
	{
		ENTITY_ID id;
		pStackData[Data_num]->Get(id);
		api->Entity_SetAttributePointer(&id,0);
	}//*/
	return pStackData[Data_num];
}

DATA * S_STACK::Read(uint32_t offset,uint32_t index)
{
	if(offset + index >= Data_num) 
	{
		STORM_THROW(stack 'read' error);
	}
	//return &pStackData[offset + index];
	return pStackData[offset + index];
}

DATA * S_STACK::Read()
{
	if(Data_num <= 0) STORM_THROW(stack 'read' error);
	//return &pStackData[Data_num - 1];
	return pStackData[Data_num - 1];
}

void S_STACK::InvalidateFrom(uint32_t index)
{
	while(Data_num > index)
	{
		Pop();
	}
}