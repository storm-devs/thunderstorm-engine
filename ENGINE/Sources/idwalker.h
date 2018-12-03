#ifndef _IDWALKER_H_
#define _IDWALKER_H_

#include "../../Common_h/vidwalker.h"


class IDWALKER : VIDWALKER
{
	void * pLayer;
public:
	 IDWALKER(){pInterface = nullptr; pLayer = nullptr;Search_Link = nullptr;};
	~IDWALKER(){if(pInterface) pInterface->Invalidate();};
	ENTITY_ID * GetID();
	ENTITY_ID * GetIDNext();
	void Invalidate();
	void SetLayer(void * pl){pLayer = pl;};
	void SetInterface(void * pi){pInterface = (VIDWALKER *)pi;};
	VIDWALKER * pInterface;
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
	ENTITY_ID * GetID()
	{ 
		if(Invalide) return nullptr;
		return pReal->GetID();
	};
	ENTITY_ID * GetIDNext()
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