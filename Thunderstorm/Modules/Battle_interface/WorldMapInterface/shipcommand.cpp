#include "shipcommand.h"
#include "../../../Shared/battle_interface/msg_control.h"
#include "../vmodule_api.h"

WMShipCommandList::WMShipCommandList( entid_t eid, ATTRIBUTES* pA, VDX9RENDER* rs ) :
	BICommandList(eid,pA,rs)
{
	Init();
}

WMShipCommandList::~WMShipCommandList()
{
	Release();
}

void WMShipCommandList::FillIcons()
{
	long nIconsQuantity = 0;

	if( m_nCurrentCommandMode & BI_COMMODE_COMMAND_SELECT )
		nIconsQuantity += CommandAdding();
}

void WMShipCommandList::Init()
{
	BICommandList::Init();
}

void WMShipCommandList::Release()
{
}

long WMShipCommandList::CommandAdding()
{
	api->Event("WM_SetPossibleCommands","l",m_nCurrentCommandCharacterIndex);
	long retVal = 0;
	ATTRIBUTES * pAttr = m_pARoot->GetAttributeClass( "Commands" );
	if( !pAttr ) return 0;
	long attrQuant = pAttr->GetAttributesNum();

	for(long i=0; i<attrQuant; i++)
	{
		ATTRIBUTES * pA = pAttr->GetAttributeClass(i);
		if(pA== nullptr) continue; // ��� ������ ��������
		if(pA->GetAttributeAsDword("enable",0)==0) continue; // ������� ����������
		long pictureNum = pA->GetAttributeAsDword("picNum",0);
		long selPictureNum = pA->GetAttributeAsDword("selPicNum",0);
		long texNum = pA->GetAttributeAsDword("texNum",-1);
		char * eventName = pA->GetAttribute("event");
		retVal += AddToIconList( texNum, pictureNum, selPictureNum, -1,
			-1, eventName, -1, nullptr, pA->GetAttribute("note") );
	}

	return retVal;
}