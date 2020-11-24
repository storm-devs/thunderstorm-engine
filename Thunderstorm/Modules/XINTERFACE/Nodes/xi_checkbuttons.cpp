#include <stdio.h>
#include "xi_checkbuttons.h"
#include "xi_util.h"

#define PicName(bDisable,bSelect) ( (bDisable && !m_sDisablePicture.empty()) ? m_sDisablePicture : ((bSelect) ? m_sSelectPicture : m_sNormalPicture) )
#define PicColor(bDisable,bSelect) ( (bDisable) ? m_dwDisablePicColor : ((bSelect) ? m_dwSelectPicColor : m_dwNormalPicColor) )

CXI_CHECKBUTTONS::CXI_CHECKBUTTONS()
{
	m_bClickable = true;
	m_nNodeType = NODETYPE_CHECKBUTTONS;
	m_nFontAlignment = PR_ALIGN_LEFT;
	m_nFontNum = -1;
	m_bClickIntoTextActive = false;
	m_bIndividualPos = false;
	m_nEditableSectionIndex = -1;
}

CXI_CHECKBUTTONS::~CXI_CHECKBUTTONS()
{
	ReleaseAll();
}

void CXI_CHECKBUTTONS::Draw(bool bSelected, uint32_t Delta_Time)
{
	float fX, fY;

	// ���������� ������
	fX = (float)m_rect.left;
	fY = (float)m_rect.top;
	for (long n = 0; n < m_aButton.size(); n++)
	{
		// ���������� ���� ������
    auto dwColor = m_dwNormalFontColor;
		if (m_aButton[n]->bChoose) dwColor = m_dwSelectFontColor;
		if (m_aButton[n]->bDisable) dwColor = m_dwDisableFontColor;

		if (m_bIndividualPos && m_aButton[n]->bSetPos)
		{
			fX = m_aButton[n]->pos.x;
			fY = m_aButton[n]->pos.y;
		}

		if (m_aButton[n]->pImg)
		{
			m_aButton[n]->pImg->SetDifferentPosition((long)(fX + m_fpIconOffset.x), (long)(fY + m_fpIconOffset.y),
			                                         (long)m_fpIconSize.x, (long)m_fpIconSize.y);
			m_aButton[n]->pImg->Draw();
		}

		// ������� ��� ������
		for (long i = 0; i < m_aButton[n]->aStr.size(); i++)
		{
			m_rs->ExtPrint(m_nFontNum, dwColor, 0,PR_ALIGN_LEFT, true, m_fFontScale, m_screenSize.x, m_screenSize.y,
			               (long)(fX + m_frTextOffset.left + m_aButton[n]->aStr[i].fX), (long)(fY + m_frTextOffset.top),
			               "%s", m_aButton[n]->aStr[i].str.c_str());
			fY += m_fTextLineHeight;
		}

		// ������ ����� �������� (����� ������ �� ������)
		fY += m_fTextSectionInterval;
	}
}

bool CXI_CHECKBUTTONS::Init(INIFILE* ini1, const char * name1, INIFILE* ini2, const char * name2, VDX9RENDER* rs, XYRECT& hostRect,
                            XYPOINT& ScreenSize)
{
	if (!CINODE::Init(ini1, name1, ini2, name2, rs, hostRect, ScreenSize)) return false;
	return true;
}

void CXI_CHECKBUTTONS::LoadIni(INIFILE* ini1, const char * name1, INIFILE* ini2, const char * name2)
{
	char param[2048];
	XYPOINT tmpLPnt;

	// ����� ������ ������ �������� ��� ���
	m_bExclusiveChoose = GetIniBool(ini1, name1, ini2, name2, "exclusiveChoose", true);

	// ����� ���������� ������ �� ���� ����
	m_bClickIntoTextActive = GetIniBool(ini1, name1, ini2, name2, "textClickable", false);

	// get font number
	if (ReadIniString(ini1, name1, ini2, name2, "font", param, sizeof(param), ""))
	{
		if ((m_nFontNum = m_rs->LoadFont(param)) == -1)
			api->Trace("can not load font:'%s'", param);
	}
	m_fFontScale = GetIniFloat(ini1, name1, ini2, name2, "fontScale", 1.f);

	// get normal font color
	m_dwNormalFontColor = GetIniARGB(ini1, name1, ini2, name2, "normalFontColor", 0xFFFFFFFF);
	// selected font color
	m_dwSelectFontColor = GetIniARGB(ini1, name1, ini2, name2, "selectFontColor", m_dwNormalFontColor);
	// disable font color
	m_dwDisableFontColor = GetIniARGB(ini1, name1, ini2, name2, "disableFontColor", m_dwNormalFontColor);

	//
	m_frTextOffset.left = m_frTextOffset.top = m_frTextOffset.right = m_frTextOffset.bottom = 0.f;
	m_frTextOffset = GetIniFloatRect(ini1, name1, ini2, name2, "rect_textoffset", m_frTextOffset);

	m_fTextLineHeight = GetIniFloat(ini1, name1, ini2, name2, "lineheight", (float)m_rs->CharHeight(m_nFontNum));
	m_fTextSectionInterval = GetIniFloat(ini1, name1, ini2, name2, "sectioninterval",
	                                     (float)m_rs->CharHeight(m_nFontNum));

	m_fpIconSize = GetIniFloatPoint(ini1, name1, ini2, name2, "iconsize", m_fpIconSize);
	if (ReadIniString(ini1, name1, ini2, name2, "icongroup", param, sizeof(param), "")) m_sIconGroupName = param;
	//
	if (ReadIniString(ini1, name1, ini2, name2, "normalpicture", param, sizeof(param), "")) m_sNormalPicture = param;
	m_dwNormalPicColor = GetIniARGB(ini1, name1, ini2, name2, "normalpiccolor", 0xFFFFFFFF);
	//
	if (ReadIniString(ini1, name1, ini2, name2, "selectpicture", param, sizeof(param), "")) m_sSelectPicture = param;
	else m_sSelectPicture = m_sNormalPicture;
	m_dwSelectPicColor = GetIniARGB(ini1, name1, ini2, name2, "selectpiccolor", m_dwNormalPicColor);
	//
	if (ReadIniString(ini1, name1, ini2, name2, "disablepicture", param, sizeof(param), "")) m_sDisablePicture = param;
	else m_sDisablePicture = m_sNormalPicture;
	m_dwDisablePicColor = GetIniARGB(ini1, name1, ini2, name2, "disablepiccolor", m_dwNormalPicColor);

	m_fpIconOffset = GetIniFloatPoint(ini1, name1, ini2, name2, "iconoffset", m_fpIconOffset);

	m_bIndividualPos = GetIniBool(ini1, name1, ini2, name2, "individualpos", false);

	// �������� �� ������� ��� ������
	char pcKeyName[128];
	for (long n = 0; n < 100; n++)
	{
		sprintf_s(pcKeyName, "section%d", n + 1);
		if (!ReadIniString(ini1, name1, ini2, name2, pcKeyName, param, sizeof(param), "")) break;
		const char* pTmpChar = param;
    const auto bSelect = CXI_UTILS::StringGetLong(pTmpChar) != 0;
    const auto bDisable = CXI_UTILS::StringGetLong(pTmpChar) != 0;
		AddButton(pTmpChar, bDisable, bSelect);
	}

	// special positions for sections
	if (m_bIndividualPos)
	{
		for (long n = 0; n < m_aButton.size(); n++)
		{
			sprintf_s(pcKeyName, "pos%d", n + 1);
			if (ReadIniString(ini1, name1, ini2, name2, pcKeyName, param, sizeof(param), ""))
			{
				const char* pTmpChar = param;
				m_aButton[n]->bSetPos = true;
				m_aButton[n]->pos.x = (float)CXI_UTILS::StringGetLong(pTmpChar);
				m_aButton[n]->pos.y = (float)CXI_UTILS::StringGetLong(pTmpChar);
			}
		}
	}

	m_nFontAlignment = PR_ALIGN_LEFT;
	if (ReadIniString(ini1, name1, ini2, name2, "alignment", param, sizeof(param), ""))
	{
		if (_stricmp(param, "center") == 0) m_nFontAlignment = PR_ALIGN_CENTER;
		if (_stricmp(param, "right") == 0) m_nFontAlignment = PR_ALIGN_RIGHT;
	}

	if (m_bExclusiveChoose)
	{
		long n;
		for (n = 0; n < m_aButton.size(); n++)
			if (m_aButton[n]->bChoose) break;
		if (n == m_aButton.size()) // �� ������� �� �����������
			SetButtonOn(0); // �� ��������� ������ �������
	}
	for (long n = 0; n < m_aButton.size(); n++)
		WriteToAttributeButtonState(n);

	UpdateAllTextInfo();
}

void CXI_CHECKBUTTONS::ReleaseAll()
{
	FONT_RELEASE(m_rs, m_nFontNum);

	for (const auto& button : m_aButton)
		delete button;
	m_aButton.clear();
	//m_aButton.DelAllWithPointers();
}

int CXI_CHECKBUTTONS::CommandExecute(int wActCode)
{
	if (m_bUse)
	{
		switch (wActCode)
		{
		case ACTION_ACTIVATE:
			break;
			//case ACTION_MOUSEDBLCLICK:
		case ACTION_MOUSECLICK:
			CheckMouseClick(ptrOwner->GetMousePoint());
			break;
		}
	}
	return -1;
}

bool CXI_CHECKBUTTONS::IsClick(int buttonID, long xPos, long yPos)
{
	for (long n = 0; n < m_aButton.size(); n++)
		if (m_aButton[n]->pImg && m_aButton[n]->pImg->IsPointInside(xPos, yPos))
			return true;
	if (!m_bUse || !m_bClickable ||
		xPos < m_rect.left || xPos > m_rect.right ||
		yPos < m_rect.top || yPos > m_rect.bottom)
		return false;
	return m_bClickIntoTextActive;
}

void CXI_CHECKBUTTONS::ChangePosition(XYRECT& rNewPos)
{
	m_rect = rNewPos;
	UpdateAllTextInfo();
}

void CXI_CHECKBUTTONS::SaveParametersToIni()
{
	char pcWriteKeyName[128];
	char pcWriteParam[2048];

  auto* pIni = fio->OpenIniFile((char*)ptrOwner->m_sDialogFileName.c_str());
	if (!pIni)
	{
		api->Trace("Warning! Can`t open ini file name %s", ptrOwner->m_sDialogFileName.c_str());
		return;
	}

	// save position
	sprintf_s(pcWriteParam, sizeof(pcWriteParam), "%d,%d,%d,%d", m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	pIni->WriteString(m_nodeName, "position", pcWriteParam);

	if (m_bIndividualPos)
	{
		for (long n = 0; n < m_aButton.size(); n++)
		{
			sprintf_s(pcWriteKeyName, "pos%d", n + 1);
			if (m_aButton[n]->bSetPos)
			{
				sprintf_s(pcWriteParam, sizeof(pcWriteParam), "%d,%d", (int)m_aButton[n]->pos.x,
				          (int)m_aButton[n]->pos.y);
				pIni->WriteString(m_nodeName, pcWriteKeyName, pcWriteParam);
			}
			else
			{
				pIni->DeleteKey(m_nodeName, pcWriteKeyName);
			}
		}
	}

	delete pIni;
}

uint32_t CXI_CHECKBUTTONS::MessageProc(long msgcode, MESSAGE& message)
{
	switch (msgcode)
	{
	case 0: // �������� ������
		{
			char param[1024];
			message.String(sizeof(param), param);
      const auto bSelect = (message.Long() != 0);
      const auto bDisable = (message.Long() != 0);
			AddButton(param, bDisable, bSelect);
			UpdateTextInfo(m_aButton.size() - 1);
		}
		break;

	case 1: // ���������� ����� ����� �� ������
		{
      const auto nButtonNum = message.Long() - 1;
			char param[1024];
			message.String(sizeof(param), param);
			ChangeText(nButtonNum, param);
			UpdateTextInfo(nButtonNum);
		}
		break;

	case 2: // ���������� ����� �� ������
		{
      const auto nButtonNum = message.Long() - 1;
      const bool bChoose = (message.Long() != 0);
			SetCheckToButton(nButtonNum, bChoose);
		}
		break;

	case 3: // �������� ���������� ������
		{
      const long nButtonNum = message.Long() - 1;
			if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return 0;
			return m_aButton[nButtonNum]->bChoose;
		}
		break;

	case 4: // �������� ��������� ������ (��� �� ������������� ������ ������ ����� ������ ���������)
		{
			for (long n = 0; n < m_aButton.size(); n++)
				if (m_aButton[n]->bChoose)
					return n;
		}
		break;

	case 5: // ���������/��������� ������
		{
      const long nButtonNum = message.Long() - 1;
      const bool bDisable = (message.Long() != 0);
			if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return 0;
			m_aButton[nButtonNum]->bDisable = bDisable;
			m_aButton[nButtonNum]->pImg->LoadFromBase(m_sIconGroupName.c_str(),
			                                          PicName(bDisable, m_aButton[nButtonNum]->bChoose).c_str(), false);
		}
		break;
	}

	return 0;
}

bool CXI_CHECKBUTTONS::GetInternalNameList(std::vector<std::string>& aStr)
{
	aStr.clear();
	if (m_bIndividualPos)
	{
		std::string sTmp = "all";
		aStr.push_back(sTmp);
		for (long n = 0; n < m_aButton.size(); n++)
			if (m_aButton[n]->bSetPos)
			{
				sTmp = "btn";
				sTmp += (n + 1);
				aStr.push_back(sTmp);
			}
		return true;
	}
	return false;
}

void CXI_CHECKBUTTONS::SetInternalName(std::string& sName)
{
	if (sName == "all")
	{
		m_nEditableSectionIndex = -1;
	}
	else
	{
		m_nEditableSectionIndex = -1;
		if (_strnicmp(sName.c_str(), "btn", 3) == 0)
		{
			m_nEditableSectionIndex = atoi(&sName.c_str()[3]) - 1;
		}
	}
}

void CXI_CHECKBUTTONS::AddButton(const char* pcText, bool bDisable, bool bSelect)
{
	ButtonDescribe* pBD = new ButtonDescribe;
	Assert(pBD);
	//pBD->aStr.Add();
	ButtonDescribe::StrDescribe strDescribe;
	if (pcText && pcText[0] == '#')
		strDescribe.str = &pcText[1];
	else
		strDescribe.str = pStringService->GetString(pStringService->GetStringNum(pcText));
	strDescribe.fX = 0;
	pBD->aStr.push_back(strDescribe);
	pBD->bDisable = bDisable;
	pBD->bChoose = bSelect;
	pBD->pImg = new CXI_IMAGE();
	Assert(pBD->pImg);
	pBD->pImg->LoadFromBase(m_sIconGroupName.c_str(), PicName(bDisable, bSelect).c_str());
	pBD->pImg->SetColor(PicColor(bDisable, bSelect));
	pBD->pImg->SetSize((long)m_fpIconSize.x, (long)m_fpIconSize.y);

	m_aButton.push_back(pBD);
}

void CXI_CHECKBUTTONS::ChangeText(long nButtonNum, const char* pcText)
{
	if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return;
	m_aButton[nButtonNum]->aStr.clear();
	m_aButton[nButtonNum]->aStr.push_back(ButtonDescribe::StrDescribe{pcText, 0.0f});
	//m_aButton[nButtonNum]->aStr[0].fX = 0.f;
	//m_aButton[nButtonNum]->aStr[0].str = pcText;
}

void CXI_CHECKBUTTONS::CheckMouseClick(const FXYPOINT& pntMouse)
{
	if (m_bClickIntoTextActive)
	{
		if (!m_bIndividualPos)
		{
			if (pntMouse.x < m_rect.left || pntMouse.x > m_rect.right) return;
			long nY = m_rect.top;
			long n;
			for (n = 0; n < m_aButton.size(); n++)
			{
        const long nHeight = (long)(m_aButton[n]->aStr.size() * m_fTextLineHeight);
				if (!m_aButton[n]->bDisable)
				{
					if (pntMouse.y >= nY && pntMouse.y <= nY + nHeight)
					{
						if (m_bExclusiveChoose)
						{
							if (!m_aButton[n]->bChoose)
								SetCheckToButton(n, true);
						}
						else
							SetCheckToButton(n, !m_aButton[n]->bChoose);
						break;
					}
				}
				nY += nHeight + (long)m_fTextSectionInterval;
			}
			if (n < m_aButton.size()) return;
		}
	}

	for (long n = 0; n < m_aButton.size(); n++)
	{
		if (m_aButton[n]->bDisable) continue;
		if (!m_aButton[n]->pImg) continue;
		if (m_aButton[n]->pImg->IsPointInside((long)pntMouse.x, (long)pntMouse.y))
		{
			if (m_bExclusiveChoose)
			{
				if (!m_aButton[n]->bChoose)
					SetCheckToButton(n, true);
			}
			else
			{
				SetCheckToButton(n, !m_aButton[n]->bChoose);
			}
			break;
		}
	}
}

void CXI_CHECKBUTTONS::SetButtonOn(long nButtonNum)
{
	if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return;
	if (m_aButton[nButtonNum]->bChoose) return;
	m_aButton[nButtonNum]->bChoose = true;
	m_aButton[nButtonNum]->pImg->LoadFromBase(m_sIconGroupName.c_str(), m_sSelectPicture.c_str(), false);
	WriteToAttributeButtonState(nButtonNum);
}

void CXI_CHECKBUTTONS::SetButtonOff(long nButtonNum)
{
	if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return;
	if (!m_aButton[nButtonNum]->bChoose) return;
	m_aButton[nButtonNum]->bChoose = false;
	m_aButton[nButtonNum]->pImg->LoadFromBase(m_sIconGroupName.c_str(), m_sNormalPicture.c_str(), false);
	WriteToAttributeButtonState(nButtonNum);
}

void CXI_CHECKBUTTONS::SetAllButtonsToOff()
{
	for (long n = 0; n < m_aButton.size(); n++)
		if (!m_aButton[n]->bDisable && m_aButton[n]->bChoose)
			SetButtonOff(n);
}

void CXI_CHECKBUTTONS::SetCheckToButton(long nButtonNum, bool bCheck)
{
	if (nButtonNum < 0 || nButtonNum >= m_aButton.size()) return; // ��� ����� ������
	if (m_aButton[nButtonNum]->bChoose == bCheck) return; // ��� ����������� ��� ���������

	if (m_bExclusiveChoose)
	{
		if (bCheck) SetAllButtonsToOff();
		else return; // �� ����� ����� ���� �� ���� ������
	}

	if (bCheck) SetButtonOn(nButtonNum);
	else SetButtonOff(nButtonNum);

	api->Event("CheckButtonChange", "sll", m_nodeName, nButtonNum + 1, (bCheck ? 1 : 0));
}

void CXI_CHECKBUTTONS::UpdateAllTextInfo()
{
	for (long n = 0; n < m_aButton.size(); n++)
		UpdateTextInfo(n);
}

void CXI_CHECKBUTTONS::UpdateTextInfo(long nButtonNum)
{
	// ������� ������ �����
	std::string sAllText;
	for (long n = 0; n < m_aButton[nButtonNum]->aStr.size(); n++)
		sAllText += m_aButton[nButtonNum]->aStr[n].str;

	long nWidth = (m_rect.right - m_rect.left) - (long)(m_frTextOffset.right + m_frTextOffset.left);
	if (nWidth < 10) nWidth = 10;
	std::vector<std::string> asOutStr;
	CXI_UTILS::SplitStringByWidth(sAllText.c_str(), m_nFontNum, m_fFontScale, nWidth, asOutStr);

	//m_aButton[nButtonNum]->aStr.clear();
	m_aButton[nButtonNum]->aStr.resize(asOutStr.size());
	for (long n = 0; n < asOutStr.size(); n++)
	{
		//m_aButton[nButtonNum]->aStr.Add();
		m_aButton[nButtonNum]->aStr[n].str = asOutStr[n];
    const long nOffset = m_rs->StringWidth((char*)asOutStr[n].c_str(), m_nFontNum, m_fFontScale, 0);
		switch (m_nFontAlignment)
		{
		case PR_ALIGN_LEFT: m_aButton[nButtonNum]->aStr[n].fX = 0.f;
			break;
		case PR_ALIGN_CENTER: m_aButton[nButtonNum]->aStr[n].fX = (float)((nWidth - nOffset) / 2);
			break;
		case PR_ALIGN_RIGHT: m_aButton[nButtonNum]->aStr[n].fX = (float)(nWidth - nOffset);
			break;
		}
	}
}

void CXI_CHECKBUTTONS::WriteToAttributeButtonState(long nButtonIndex)
{
	if (nButtonIndex < 0 || nButtonIndex >= m_aButton.size()) return;
	char atrName[128];
	sprintf_s(atrName, sizeof(atrName), "state%d", nButtonIndex + 1);
	ATTRIBUTES* pA = ptrOwner->AttributesPointer->GetAttributeClass(m_nodeName);
	if (!pA) pA = ptrOwner->AttributesPointer->CreateSubAClass(ptrOwner->AttributesPointer, m_nodeName);
	if (pA) pA->SetAttributeUseDword(atrName, m_aButton[nButtonIndex]->bChoose ? 1 : 0);
}
