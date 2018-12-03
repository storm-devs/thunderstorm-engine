#ifndef _INTERFACE_EDITOR_H_
#define _INTERFACE_EDITOR_H_

#include "../Common_h/dx9render.h"
#include "../Common_h/vmodule_api.h"
#include "../XINTERFACE/xinterface.h"

class EditorManager;

class InterfaceEditor : public ENTITY
{
public:
	InterfaceEditor();
	~InterfaceEditor();

	virtual bool Init();
	virtual uint32_t _cdecl ProcessMessage( MESSAGE& message );
	virtual void Realize( uint32_t dwDeltaTime );

protected:
	VDX9RENDER* m_pRender;
	XINTERFACE* m_pInterface;

	EditorManager* m_pManager;
};

#endif
