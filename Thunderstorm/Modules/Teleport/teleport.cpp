#include "teleport.h"
#include "defines.h"
#include "../Pcs_controls/pcs_controls.h"

#define DELETE_PTR(x)	if(x) delete x; x=0;

INTERFACE_FUNCTION
CREATE_CLASS(TMPTELEPORT)
CREATE_CLASS(FINDFILESINTODIRECTORY)
CREATE_CLASS(FINDDIALOGNODES)

bool GetStringLine(char * &pStr, char * bufer, long bufSize)
{
	if(pStr== nullptr || bufer== nullptr || bufSize==0) return false;
	bufer[0] = 0;

	char * ps = pStr;
	while(*ps && (*ps==32 || *ps==9 || *ps==10 || *ps==13) ) ps++;
	char * pStart = ps;

	while(*ps && *ps!=10 && *ps!=13) ps++;
	char * pEnd = ps;
	pStr = pEnd;

	if(pEnd==pStart && *ps==0) return false;
	if( (long)(pEnd-pStart)>bufSize-1 ) pEnd = pStart+bufSize-1;
	else bufSize = pEnd-pStart;

	if(bufSize>0)
	{
		strcpy_s(bufer,bufSize,pStart);
		bufer[bufSize] = 0;
	}
	return true;
}

void GetQuotedString(char * inBuf, char * outBuf, long bufSize)
{
	if(outBuf== nullptr || bufSize<=0) return;
	*outBuf = 0;
	if(inBuf== nullptr) return;

	while(*inBuf && *inBuf!='\"') inBuf++;
	if(*inBuf) inBuf++;

	int bufIdx=0;
	while(*inBuf && *inBuf!='\"' && bufIdx<bufSize-1)
	{
		*outBuf = *inBuf;
		outBuf++; inBuf++;
		bufIdx++;
	}
	*outBuf = 0;
}

TMPTELEPORT::TMPTELEPORT()
{
	rs= nullptr;
	m_descrArray= nullptr;
	m_nStrQuantity = m_nCurStr = m_nCurShowPos = 0;
}

TMPTELEPORT::~TMPTELEPORT()
{
	ReleaseAll();
}

bool TMPTELEPORT::Init()
{
	rs = (VDX9RENDER *)api->CreateService("dx9render");
	if(!rs)	throw std::exception("No service: dx9render");

	m_leftPos = 20;
	m_topPos = 80;
	m_deltaPos = 30;
	m_showStrQuantity = 10;

	m_nShowType = 0;

	return true;
}

void TMPTELEPORT::Execute(uint32_t Delta_Time)
{
	CONTROL_STATE cs;
	if( ((PCS_CONTROLS*)api->Controls)->m_bIsOffDebugKeys ) return;
	api->Controls->GetControlState("TeleportActive",cs);
	if(cs.state == CST_ACTIVATED)
	{
		if(m_nShowType==0)
		{
			api->Event("TeleportStart","");
			m_nShowType=1;
		}
		else
		{
			ReleaseAll();
			m_nShowType=0;
		}
	}
	long csVal;
	if(api->Controls->GetDebugAsyncKeyState(VK_SHIFT)<0)
		csVal = CST_ACTIVE;
	else
		csVal = CST_ACTIVATED;
	api->Controls->GetControlState("TeleportUp",cs);
	if(cs.state == csVal)
	{
		if(m_nStrQuantity>0)
		{
			if(m_nCurShowPos>0)
				m_nCurShowPos--;
			else
				if(m_nCurStr>0)
					m_nCurStr--;
		}
	}
	api->Controls->GetControlState("TeleportDown",cs);
	if(cs.state == csVal)
	{
		if(m_nStrQuantity>0)
		{
			if( m_nCurStr+m_nCurShowPos < m_nStrQuantity-1 )
				if( m_nCurShowPos < m_showStrQuantity-1 )
					m_nCurShowPos++;
				else
					m_nCurStr++;
		}
	}
	api->Controls->GetControlState("TeleportSelect",cs);
	if(cs.state == CST_ACTIVATED)
	{
		if(m_nStrQuantity>0)
		{
			long n = m_descrArray[m_nCurStr+m_nCurShowPos].num;
			ReleaseAll();
			api->Event("TeleportChoose","l",n);
		}
	}
}

void TMPTELEPORT::Realize(uint32_t Delta_Time)
{
	if(m_nStrQuantity>0)
	{
		int j=0;
		long ftop = m_topPos;
		for(int i=m_nCurStr; i<m_nStrQuantity; i++)
		{
			if(j>=m_showStrQuantity) break;
			if(j==m_nCurShowPos)
				rs->Print(FONT_DEFAULT,ARGB(255,155,155,55),m_leftPos,ftop,"%s",m_descrArray[i].name);
			else
				rs->Print(FONT_DEFAULT,ARGB(255,255,255,255),m_leftPos,ftop,"%s",m_descrArray[i].name);
			ftop += m_deltaPos;
			j++;
		}
	}
}

void TMPTELEPORT::ReleaseAll()
{
	if(m_descrArray!= nullptr)
	{
		for(int i=0; i<m_nStrQuantity; i++)
		{
			DELETE_PTR(m_descrArray[i].name);
		}
	}
	DELETE_PTR(m_descrArray);
	m_nStrQuantity = 0;
	m_nCurStr = m_nCurShowPos = 0;
	m_nShowType = 0;
}

uint64_t TMPTELEPORT::ProcessMessage(MESSAGE &message)
{
	switch(message.Long())
	{
	case 42222:
		{
			ATTRIBUTES * pA = message.AttributePointer();
			SetShowData(pA);
			if(m_nStrQuantity==0)
				m_nShowType=0;
			else
				m_nShowType=1;
		}
		break;
	}
	return 0;
}

void TMPTELEPORT::SetShowData(ATTRIBUTES * pA)
{
	ReleaseAll();
	m_nStrQuantity = 0;
	if(pA== nullptr) return;
	m_nStrQuantity = pA->GetAttributesNum();
	if(m_nStrQuantity==0) return;
	if((m_descrArray=new TELEPORT_DESCR[m_nStrQuantity])== nullptr)
	{
		throw std::exception("Allocate memory error");
	}

	for(int i=0;i<m_nStrQuantity;i++)
	{
		char * tmpStr = pA->GetAttribute(i);
		m_descrArray[i].name = nullptr;
		m_descrArray[i].num = i;
		if(tmpStr== nullptr) continue;
		const auto len = strlen(tmpStr) + 1;
		if( (m_descrArray[i].name=new char[len]) == nullptr )
		{
			throw std::exception("Allocate memory error");
		}
		memcpy(m_descrArray[i].name,tmpStr,len);
	}

	SortShowData();
}

void TMPTELEPORT::SortShowData()
{
	if(m_nStrQuantity==0) return;
	bool bContinueSort=true;
	do
	{
		bContinueSort = false;
		for(int i=1; i<m_nStrQuantity; i++)
		{
			if(m_descrArray[i-1].name== nullptr) continue;
			if(m_descrArray[i].name== nullptr)
			{
				XChange(m_descrArray[i-1],m_descrArray[i]);
				bContinueSort = true;
				continue;
			}
			if(strcmp(m_descrArray[i].name,m_descrArray[i-1].name)<0)
			{
				XChange(m_descrArray[i-1],m_descrArray[i]);
				bContinueSort = true;
			}
		}
	} while(bContinueSort);
}

void TMPTELEPORT::XChange(TELEPORT_DESCR & d1,TELEPORT_DESCR & d2)
{
	int n=d1.num;
	d1.num=d2.num;
	d2.num=n;

	char* nm=d1.name;
	d1.name=d2.name;
	d2.name=nm;
}

bool FINDFILESINTODIRECTORY::Init()
{
	if(AttributesPointer)
	{
		char * dirName = AttributesPointer->GetAttribute("dir");
		char * maskName = AttributesPointer->GetAttribute("mask");
		char fullName[512];
		fullName[0]=0;
		if(dirName) sprintf_s(fullName,"%s\\",dirName);
		if(maskName) strcat_s(fullName,maskName);
		else strcat_s(fullName,"*.*");
		WIN32_FIND_DATA finddat;
		HANDLE hdl = fio->_FindFirstFile( fullName, &finddat );
		ATTRIBUTES * pA = AttributesPointer->CreateSubAClass(AttributesPointer,"filelist");
		for(int file_idx=0; hdl!=INVALID_HANDLE_VALUE; file_idx++)
		{
			char sname[32];
			sprintf_s(sname,"id%d",file_idx);
			if(finddat.cFileName)
				pA->SetAttribute(sname,finddat.cFileName);
			if( !fio->_FindNextFile(hdl, &finddat) ) break;
		}
		if(hdl!=INVALID_HANDLE_VALUE) fio->_FindClose(hdl);
		return true;
	}
	api->Trace("Attributes Pointer into class FINDFILESINTODIRECTORY = NULL");
	return false;
}

bool FINDDIALOGNODES::Init()
{
	if(AttributesPointer)
	{
		char * fileName = AttributesPointer->GetAttribute("file");
		ATTRIBUTES * pA = AttributesPointer->CreateSubAClass(AttributesPointer,"nodelist");
		if(fileName && pA)
		{
			HANDLE hfile = fio->_CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
			if(hfile==INVALID_HANDLE_VALUE)
			{
				api->Trace("WARNING! Can`t dialog file %s",fileName);
				return false;
			}

			long filesize = fio->_GetFileSize(hfile,nullptr);
			if(filesize==0)
			{
				api->Trace("Empty dialog file %s",fileName);
				fio->_CloseHandle(hfile);
				return false;
			}

			char * fileBuf = new char[filesize+1];
			if(fileBuf== nullptr)
			{
				api->Trace("Can`t create buffer for read dialog file %s",fileName);
				fio->_CloseHandle(hfile);
				return false;
			}

			uint32_t readsize;
			if( fio->_ReadFile(hfile,fileBuf,filesize,&readsize) == FALSE ||
				readsize!=(uint32_t)filesize )
			{
				api->Trace("Can`t read dialog file: %s",fileName);
				fio->_CloseHandle(hfile);
				delete[] fileBuf;
				return false;
			}
			fio->_CloseHandle(hfile);
			fileBuf[filesize] = 0;

			// ������ ���� ����� - ������ ��� �������������
			char * pStr = fileBuf;
			char param[1024];

			int nodIdx = 0;
			while( GetStringLine(pStr, param, sizeof(param)-1) )
			{
				if( strlen(param)<5 || _strnicmp(param,"case",4) ) continue;
				char param2[512];
				GetQuotedString(param,param2,sizeof(param2)-1);
				if(strlen(param2)>0)
				{
					sprintf_s(param,"id%d",nodIdx);
					nodIdx++;
					pA->SetAttribute(param,param2);
				}
			}

			delete[] fileBuf;
			return true;
		}
	}
	api->Trace("Attributes Pointer into class FINDDIALOGNODES = NULL");
	return false;
}
