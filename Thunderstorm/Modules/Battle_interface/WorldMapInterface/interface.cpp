#include "interface.h"
#include "shipsign.h"
#include "shipcommand.h"
#include "../../Shared/battle_interface/msg_control.h"
#include "vmodule_api.h"

WM_INTERFACE::WM_INTERFACE(): rs(nullptr)
{
	m_pShipIcon = nullptr;
	m_pCommandList = nullptr;

	m_nCommandListVerticalOffset = 0;
	m_nMainCharIndex = -1;
	m_nCommandMode = 0;

	m_bVisible = true;
}

WM_INTERFACE::~WM_INTERFACE()
{
	STORM_DELETE(m_pShipIcon);
	STORM_DELETE(m_pCommandList);
}

bool WM_INTERFACE::Init()
{
	rs = (VDX9RENDER*)api->CreateService("DX9RENDER");
	Assert(rs);

	LoadIniFile();
	return true;
}

void WM_INTERFACE::Realize(uint32_t delta_time)
{
	if (m_bVisible)
	{
		rs->MakePostProcess();

		if (m_pShipIcon)
		{
			m_pShipIcon->Draw();
		}
		if (m_pCommandList)
		{
			if (!m_pCommandList->GetActive())
			{
				CONTROL_STATE cs;
				api->Controls->GetControlState(BI_COMMANDS_ACTIVATE_SEA, cs);
				if (cs.state == CST_ACTIVATED)
				{
					m_pCommandList->SetActive(true);
					m_nCommandMode = BI_COMMODE_COMMAND_SELECT;
					UpdateCommandList();
				}
			}
			else
			{
				MakeControl();
			}
			m_pCommandList->Draw();
		}
	}
}

uint64_t WM_INTERFACE::ProcessMessage(MESSAGE& message)
{
	switch (message.Long())
	{
	case MSG_BATTLE_LAND_MAKE_COMMAND:
		{
			char param[256];
			message.String(sizeof(param) - 1, param);
			if (_stricmp(param, "cancel") == 0)
			{
				ExecuteCommand(BI_MSG_COMMAND_DEACTIVATE);
			}
		}
		break;
	case BI_MSG_REFRESH:
		m_pShipIcon->SetUpdate();
		UpdateCommandList();
		break;
	}
	return 0;
}

uint32_t WM_INTERFACE::AttributeChanged(ATTRIBUTES* pAttr)
{
	return 0;
}

void WM_INTERFACE::LoadIniFile()
{
	m_pShipIcon = new WMShipIcon(GetId(), rs);
	Assert(m_pShipIcon);
  auto pA = AttributesPointer ? AttributesPointer->GetAttributeClass("wm_sign") : nullptr;
	m_pShipIcon->Init(AttributesPointer, pA);
	m_nCommandListVerticalOffset = pA ? pA->GetAttributeAsDword("commandlistverticaloffset") : -48;

	m_nMainCharIndex = AttributesPointer ? AttributesPointer->GetAttributeAsDword("maincharindex", -1) : -1;

	m_pCommandList = new WMShipCommandList(GetId(), AttributesPointer, rs);
	Assert(m_pCommandList);

	UpdateCommandList();
}

void WM_INTERFACE::MakeControl()
{
	CONTROL_STATE cs;

	api->Controls->GetControlState(BI_COMMANDS_CONFIRM, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_ACTIVATE);

	api->Controls->GetControlState(BI_COMMANDS_LEFTSTEP, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_LEFT);

	api->Controls->GetControlState(BI_COMMANDS_RIGHTSTEP, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_RIGHT);

	api->Controls->GetControlState(BI_COMMANDS_UPSTEP, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_UP);

	api->Controls->GetControlState(BI_COMMANDS_DOWNSTEP, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_DOWN);

	api->Controls->GetControlState(BI_COMMANDS_CANCEL, cs);
	if (cs.state == CST_ACTIVATED)
		ExecuteCommand(BI_MSG_COMMAND_DEACTIVATE);
}

void WM_INTERFACE::ExecuteCommand(long command)
{
	switch (command)
	{
	case BI_MSG_COMMAND_ACTIVATE:
		if (m_pCommandList)
		{
      const auto nTmp = m_pCommandList->ExecuteConfirm();
			if (nTmp != -1) m_nCommandMode = nTmp;
			if (m_nCommandMode == 0)
			{
				m_pCommandList->SetActive(false);
				m_nCommandMode = BI_COMMODE_COMMAND_SELECT;
			}
		}
		break;

	case BI_MSG_COMMAND_LEFT:
		if (m_pCommandList)
			m_pCommandList->ExecuteLeft();
		break;

	case BI_MSG_COMMAND_RIGHT:
		if (m_pCommandList)
			m_pCommandList->ExecuteRight();
		break;

	case BI_MSG_COMMAND_UP:
		break;

	case BI_MSG_COMMAND_DOWN:
		break;

	case BI_MSG_COMMAND_DEACTIVATE:
		if (m_pCommandList)
		{
			m_nCommandMode = m_pCommandList->ExecuteCancel();
			if (m_nCommandMode == 0)
			{
				m_pCommandList->SetActive(false);
				m_nCommandMode = BI_COMMODE_COMMAND_SELECT;
			}
			else UpdateCommandList();
		}
		break;

	default:
		api->Trace("Warning! Unknown executing command: %d", command);
	}
}

void WM_INTERFACE::UpdateCommandList() const {
	if (m_pCommandList)
		m_pCommandList->Update(GetCurrentCommandTopLine(), GetCurrentCommandCharacterIndex(), GetCurrentCommandMode());
}

long WM_INTERFACE::GetCurrentCommandTopLine() const {
	return m_pShipIcon->GetLineY(0) + m_nCommandListVerticalOffset;
}

long WM_INTERFACE::GetCurrentCommandCharacterIndex() const {
	return m_nMainCharIndex;
}

long WM_INTERFACE::GetCurrentCommandMode() const {
	return m_nCommandMode;
}

bool WM_INTERFACE::IsCommandMenuActive() const {
	if (!m_pCommandList) return false;
	return m_pCommandList->GetActive();
}
