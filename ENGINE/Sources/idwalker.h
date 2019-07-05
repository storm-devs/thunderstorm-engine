#ifndef _IDWALKER_H_
#define _IDWALKER_H_

#include "../../Common_h/vidwalker.h"


class IDWALKER : VIDWALKER
{
	void * pLayer;
public:
	 IDWALKER(){pInterface = nullptr; pLayer = nullptr;Search_Link = nullptr;};
	~IDWALKER(){if(pInterface) pInterface->Invalidate();};
	entid_t * GetID();
	entid_t * GetIDNext();
	void Invalidate();
	void SetLayer(void * pl){pLayer = pl;};
	void SetInterface(void * pi){pInterface = (walker_t)pi;};
	walker_t pInterface;
	LPBYTE Search_Link;
	bool Validate() { return true; };
};

class TIDWALKER : public VIDWALKER
{
	IDWALKER * pReal;
	bool Invalide;
public:
	TIDWALKER(void * preal)
	{
		pReal = (IDWALKER*)preal; 
		Invalide = false;
	};
	~TIDWALKER()
	{
		pReal->Invalidate();
	};
	entid_t * GetID()
	{ 
		if(Invalide) return nullptr;
		return pReal->GetID();
	};
	entid_t * GetIDNext()
	{
		if(Invalide) return nullptr;
		return pReal->GetIDNext();
	};
	void Invalidate()
	{
		Invalide = true;
	}
	bool Validate() { return !Invalide; };
};



#endif