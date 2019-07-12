#include <assert.h>
#include "ships_list.h"
#include "../../Common_h/Net.h"
#include "../../Shared/battle_interface/msg_control.h"
//#include "battle_command.h"

#define LOADING_MODE_MY_SHIP		0
#define LOADING_MODE_ENEMY_SHIP		1

class TMP_LONG_STACK
{
	long sizeIncr;
	long *ldat;
	long datsize;
	long curidx;
	long defReturn;
public:
	TMP_LONG_STACK() {sizeIncr=100;ldat= nullptr;datsize=0;curidx=0;defReturn=-1;}
	~TMP_LONG_STACK() {if(ldat!= nullptr) delete ldat; ldat= nullptr;}
	void Push(long data);
	long Pop();
	long GetFore();
	void SetSizeIncrement(long sizeinc) {sizeIncr=sizeinc;}
	void SetDefReturn(long defRet) {defReturn=defRet;}
};
void TMP_LONG_STACK::Push(long data)
{
	if(curidx>=datsize)
	{
		if(sizeIncr<=0)
		{
			api->Trace("WARNING! push for TMP_LONG_STACK impossible - array grid <= 0");
			return;
		}
		long *pold = ldat;
		ldat = new long[datsize+sizeIncr];
		if(ldat== nullptr)	{throw std::exception("allocate memory error");}
		if(pold!= nullptr)
		{
			memcpy(ldat,pold,sizeof(long)*datsize);
			delete pold;
		}
		datsize += sizeIncr;
	}
	ldat[curidx++] = data;
}
long TMP_LONG_STACK::GetFore()
{
	if(ldat== nullptr || curidx<=0)
	{
		api->Trace("WARNING! GetFore from TMP_LONG_STACK is empty");
		return defReturn;
	}
	long retVal = ldat[0];
	curidx--;
	if(curidx==0)
	{
		delete ldat;
		ldat = nullptr;
		datsize = 0;
	}
	else	for(int i=0; i<curidx; i++)	ldat[i] = ldat[i+1];
	return retVal;
}
long TMP_LONG_STACK::Pop()
{
	if(ldat== nullptr || curidx<=0)
	{
		api->Trace("WARNING! pop from TMP_LONG_STACK is empty");
		return defReturn;
	}
	long retVal = ldat[--curidx];
	if(curidx==0)
	{
		delete ldat;
		ldat = nullptr;
		datsize = 0;
	}
	return retVal;
}

void SetNLongData(VDATA * pvd, int n, ...)
{
	va_list args;
	va_start(args,n);

	for(int i=0; i<n; i++)
	{
		long * pIVal = va_arg(args,long*);
		if(!pIVal) break;
		long nDefVal = va_arg(args,long);
		if(pvd) pvd->Get(*pIVal,i);
		else *pIVal = nDefVal;
	}

	va_end(args);
}

SHIP_DESCRIBE_LIST::SHIP_DESCRIBE_LIST()
{
	root = nullptr;
	mainCharacter = nullptr;
	pMainShipAttr = nullptr;
}

SHIP_DESCRIBE_LIST::~SHIP_DESCRIBE_LIST()
{
	ReleaseAll();
}

void SHIP_DESCRIBE_LIST::ShipSink(long charIdx)
{
	SHIP_DESCR * sd = FindShip(charIdx);
	if(sd== nullptr) return;
	sd->isDead = true;
}

void SHIP_DESCRIBE_LIST::Release(long charIdx)
{
	if(charIdx == -1L) return;
	if(root== nullptr) return;

	SHIP_DESCR * sd = root;
	if(root->characterIndex == charIdx)
	{
		root = root->next;
		delete sd;
		return;
	}

	SHIP_DESCR * pr = root->next;
	while(pr!= nullptr)
	{
		if(pr->characterIndex == charIdx)
		{
			sd->next = pr->next;
			delete pr;
			return;
		}
		sd=pr; pr=pr->next;
	}

	mainCharacter = nullptr;
	pMainShipAttr = nullptr;
}

void SHIP_DESCRIBE_LIST::Add(long mainChrIndex, long chIdx, ATTRIBUTES * pChAttr, ATTRIBUTES * pShipAttr, bool bMyShip,long relation,uint32_t dwShipColor)
{
	assert(pChAttr!=NULL);
	assert(pShipAttr!=NULL);
	SHIP_DESCR * pr = new SHIP_DESCR;
	if(pr== nullptr)
	{
		throw std::exception("Can`t allocate memory");
	}
	pr->characterIndex = chIdx;
	pr->maxCrew = pShipAttr->GetAttributeAsDword("MaxCrew");
	pr->maxHP = pShipAttr->GetAttributeAsDword("HP");
	pr->maxSP = pShipAttr->GetAttributeAsDword("SP");
	pr->isMyShip = bMyShip;
	pr->relation = relation;
	pr->isDead = false;
	pr->pShip = nullptr;
	pr->dwShipColor = dwShipColor;

	ATTRIBUTES * pAttr = pChAttr->GetAttributeClass("Ship");
	assert(pAttr!=NULL);
	pr->pAttr = pAttr;
	long lTmp;
	SetNLongData( api->Event(BI_EVENT_GET_DATA,"ll",BIDT_SHIPPICTURE,chIdx), 4, &pr->pictureNum,0, &pr->selectPictureNum,0, &pr->textureNum,-1, &lTmp,0 );//&pr->isDead,false );
	pr->isDead = lTmp!=0;

	pr->next = nullptr;

	// find this ship
	const auto walker = api->GetEntityIdWalker("ship");
	entid_t ei;
	while(ei = walker())
	{
		VAI_OBJBASE* vob = (VAI_OBJBASE*)EntityManager::GetEntityPointer(ei);
		if (vob == nullptr) continue;
		ATTRIBUTES* pA = vob->GetACharacter();
		if ((long)pA->GetAttributeAsDword("index") == chIdx)
		{
			pr->pShip = vob;
			break;
		}
	}
	/*if( NetFindClass(false,&ei,"netship") ) do
	{
		VAI_OBJBASE * vob = (VAI_OBJBASE*)EntityManager::GetEntityPointer(ei);
		if(vob== nullptr) continue;
		ATTRIBUTES *pA = vob->GetACharacter();
		if((long)pA->GetAttributeAsDword("id")==chIdx)
		{
			pr->pShip = vob;
			break;
		}
	} while( NetFindClassNext(false,&ei) );*/

	SHIP_DESCR * ptmp = root;
	if(ptmp== nullptr)	root = pr;
	else
	{
		while(ptmp->next!= nullptr) ptmp = ptmp->next;
		ptmp->next = pr;
	}

	//if(pChAttr->GetAttributeAsDword("MainCharacter",0)!=0)
	if( mainChrIndex == chIdx )
	{
		mainCharacter = pr;
		pMainShipAttr = pShipAttr;
	}
}

void SHIP_DESCRIBE_LIST::ReleaseAll()
{
	while(root!= nullptr)
	{
		SHIP_DESCR * ptmp = root;
		root = root->next;
		delete ptmp;
	}
	root = nullptr;
	mainCharacter = nullptr;
	pMainShipAttr = nullptr;
}

SHIP_DESCRIBE_LIST::SHIP_DESCR * SHIP_DESCRIBE_LIST::FindShip(long idxCharacter)
{
	for(SHIP_DESCR *ptmp=root; ptmp!= nullptr; ptmp=ptmp->next)
		if(ptmp->characterIndex==idxCharacter)
			return ptmp;
	return nullptr;
}

void SHIP_DESCRIBE_LIST::Refresh()
{
	ReleaseAll();

	TMP_LONG_STACK tls;

	const auto walker = api->GetEntityIdWalker("ship");
	entid_t ei;
//	tls.Push(-1);

	while(ei = walker())
	{
		VAI_OBJBASE* vob = (VAI_OBJBASE*)EntityManager::GetEntityPointer(ei);
		if (vob == nullptr) continue;
		ATTRIBUTES* pA = vob->GetACharacter();
		if (pA == nullptr) continue;
		tls.Push((long)pA->GetAttributeAsDword("index"));
	}

	/*if( NetFindClass(false,&ei,"NetShip") ) do
	{
		VAI_OBJBASE * vob = (VAI_OBJBASE*)EntityManager::GetEntityPointer(ei);
		if(vob== nullptr) continue;
		ATTRIBUTES * pA= vob->GetACharacter();
		if(pA== nullptr) continue;
		tls.Push((long)pA->GetAttributeAsDword("id"));
	} while( NetFindClassNext(false,&ei) );*/
	tls.Push(-1);

	for(long chrIdx = tls.GetFore(); chrIdx>=0; chrIdx = tls.GetFore())
	{
		api->Event("BI_CallUpdateShip","l",chrIdx);
	}

	//BATTLE_COMMAND::m_bMakeModeUpdate = true;
}
