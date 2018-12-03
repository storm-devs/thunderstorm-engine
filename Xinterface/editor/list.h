#ifndef _GI_EDITOR_LIST_H
#define _GI_EDITOR_LIST_H

#include "..\inode.h"
#include "defines.h"

class GIEditor;
class CXI_IMAGE;
class GIFont;

class GIEditorList : public GIEditorObject
{
public:
	GIEditorList(GIEditor* pEditor);
	~GIEditorList();

	void Release();
	void Create();

	void Render();

	void SetPosition( float fLeft, float fTop, float fRight, float fBottom );

	void AddString(std::string& sNewStr );
	void RemoveString(std::string& sStr );
	void RemoveString( long nIndex );
	void RemoveAllStrings();
	long FindString(std::string& sStr );
	long GetStringQuantity() {return m_aStrings.size();}
	std::string& GetString( long nIndex );
	long GetSelectIndex() {return m_nSelectIndex;}
	void SetSelectIndex( long nIndex );
	std::string& GetSelectString() {return GetString(m_nSelectIndex);}

	bool CheckMouseInside( float fX, float fY );
	void MakeMouseClick( float fX, float fY );
	void DoKeyChecking();

	void IncrementSelectedLine( bool bIncr );

protected:
	void UpdateSelectPosition();

	GIEditor* m_pEditor;

	CXI_IMAGE* m_pBackImage;
	CXI_IMAGE* m_pSelectImage;

	bool m_bShowSelect;
	FXYRECT m_frBackRect;
	FXYRECT m_frSelectRect;

	std::string m_sEmptyString;
	GIFont* m_pFont;

	FXYRECT m_frStrOffset;
	float m_fStrLineStep;
	std::vector<std::string> m_aStrings;
	long m_nSelectIndex;
	long m_nTopIndex;
	long m_nLineQuantity;

	float m_fUpPressTime;
	float m_fDownPressTime;
	float m_fKeyRepeatDelay;
	float m_fKeyRepeatInterval;

public:
	uint32_t m_dwStatus;
	GIEditorEventHandler* m_pChangeSelected;
};

#endif
