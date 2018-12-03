#ifndef _TELEPORT_H_
#define _TELEPORT_H_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"

class TMPTELEPORT : public ENTITY
{
	VDX9RENDER * rs;

	struct TELEPORT_DESCR
	{
		int num;
		char* name;
	} *m_descrArray;

public:
	TMPTELEPORT();
	~TMPTELEPORT();
	bool Init();
	void Execute(uint32_t Delta_Time);
	void Realize(uint32_t Delta_Time);
	uint32_t _cdecl ProcessMessage(MESSAGE &message);

protected:
	void ReleaseAll();
	void SetShowData(ATTRIBUTES * pA);
	void SortShowData();
	void XChange(TELEPORT_DESCR & d1,TELEPORT_DESCR & d2);

protected:
	long m_leftPos;
	long m_topPos;
	long m_deltaPos;
	long m_showStrQuantity;

	long m_nStrQuantity;
	long m_nCurStr;
	long m_nCurShowPos;

	long m_nShowType;
};

class FINDFILESINTODIRECTORY : public ENTITY
{
public:
	FINDFILESINTODIRECTORY() {}
	~FINDFILESINTODIRECTORY() {}
	bool Init();
};

class FINDDIALOGNODES : public ENTITY
{
public:
	FINDDIALOGNODES() {}
	~FINDDIALOGNODES() {}
	bool Init();
};

#endif
