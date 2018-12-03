#include "InterfaceEditor.h"
#include "EditorManager.h"
#include "gui/utils.h"

INTERFACE_FUNCTION
CREATE_CLASS(InterfaceEditor)

InterfaceEditor::InterfaceEditor()
{
}

InterfaceEditor::~InterfaceEditor()
{
}

bool InterfaceEditor::Init()
{
	m_pRender = (VDX9RENDER*)api->CreateService( "DX9Render" );
	Assert( m_pRender );
	EdUtils::m_pRender = m_pRender;

	ENTITY_ID eid;
	if( !api->CreateEntity( &eid, "XINTERFACE" ) )
	{
		api->Trace( "Warning! Can`t create interface entity!" );
		return false;
	}
	m_pInterface = (XINTERFACE*)eid.pointer;

	m_pManager = NEW EditorManager;
	Assert( m_pManager );
	m_pManager->Init();

	return true;
}

uint32_t _cdecl InterfaceEditor::ProcessMessage( MESSAGE& message )
{
	return 0;
}

void InterfaceEditor::Realize( uint32_t dwDeltaTime )
{
	float fDeltaTime = dwDeltaTime * 0.001f;
	if( m_pManager ) m_pManager->Execute( fDeltaTime );
}
