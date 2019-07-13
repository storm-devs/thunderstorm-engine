#include "BaseGroup.h"
#include "../../../Common_h/assert.h"

BI_BaseGroup::BI_BaseGroup( BI_ManagerBase* pManager )
{
	Assert(pManager);
	m_pManager = pManager;
	Init();
}

BI_BaseGroup::~BI_BaseGroup()
{
	for (auto& node : m_aNodes)
	{
		m_pManager->DeleteNode(node);
		delete node;
	}
}
