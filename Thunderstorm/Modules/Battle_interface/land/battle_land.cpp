#include "battle_land.h"
#include "battle_mansign.h"
#include "../../Shared/battle_interface/msg_control.h"
#include <message.h>
#include <core.h>

BATTLE_LAND_INTERFACE::BATTLE_LAND_INTERFACE() : m_bShowCommandos(false) {
  m_pRS = nullptr;
  m_pManSign = nullptr;
}

BATTLE_LAND_INTERFACE::~BATTLE_LAND_INTERFACE() {
  Release();
}

bool BATTLE_LAND_INTERFACE::Init() {
  m_pRS = static_cast<VDX9RENDER*>(core.CreateService("dx9render"));
  if (!m_pRS) {
    throw std::exception("Can`t create render service");
  }

  SetShowParameters();
  return true;
}

void BATTLE_LAND_INTERFACE::Execute(uint32_t delta_time) const {
  CONTROL_STATE cs;

  if (m_bShowCommandos && m_pManSign) {
    if (!m_pManSign->IsActive()) {
      core.Controls->GetControlState(BI_COMMANDS_ACTIVATE_LAND, cs);
      if (cs.state == CST_ACTIVATED) {
        m_pManSign->SetActive(true);
      }
    }
    else {
      m_pManSign->MakeControl();
    }
  }
}

void BATTLE_LAND_INTERFACE::Realize(uint32_t delta_time) {
  if (m_bShowCommandos) {
    m_pRS->MakePostProcess();
    if (m_pManSign)
      m_pManSign->Draw();

    m_Images.Draw();
    BIUtils::PrintTextInfoArray(m_TextInfo);
  }
}

uint64_t BATTLE_LAND_INTERFACE::ProcessMessage(MESSAGE& message) {
  switch (message.Long()) {
  case MSG_BATTLE_LAND_START:
    if (m_pManSign) m_pManSign->SetUpdate();
    break;

  case MSG_BATTLE_LAND_END:
    EndShow();
    break;

  case BI_IN_SET_COMMAND_MODE:
    if (m_bShowCommandos && m_pManSign) {
      auto comMode = message.Long();
      auto startTextureNumber = message.Long();
      auto startPictureNumber = message.Long();
      auto characterNum = message.Long();
    }
    break;

  case MSG_BATTLE_LAND_SET_SHOW:
    m_bShowCommandos = (message.Long() != 0);
    break;

  case MSG_BATTLE_LAND_SET_MSGICONS:
    EnableMessageIcons(message.ScriptVariablePointer());
    break;

  case BI_MSG_ADD_NEWTEXTURE:
    {
      char param[256];
      message.String(sizeof(param) - 1, param);
      const int hQ = message.Long();
      const int vQ = message.Long();
      if (m_pManSign) return m_pManSign->AddTexture(param, hQ, vQ);
      return -1;
    }
    break;

  case MSG_BATTLE_LAND_MAKE_COMMAND:
    {
      char param[256];
      message.String(sizeof(param) - 1, param);
      if (_stricmp(param, "cancel") == 0) {
        if (m_pManSign) m_pManSign->ExecuteCommand(BI_MSG_COMMAND_DEACTIVATE);
      }
    }
    break;

  case BI_MSG_CARE_COMMANDLIST_UPDATE:
    m_pManSign->SetUpdate();
    break;
  }
  return 0;
}

void BATTLE_LAND_INTERFACE::SetParameters() {
  UpdateCommandos();
  UpdateAlarm();
}

void BATTLE_LAND_INTERFACE::Release() {
  m_pRS = nullptr;
  STORM_DELETE(m_pManSign);

  m_TextInfo.clear();
}

void BATTLE_LAND_INTERFACE::EndShow() {
}

void BATTLE_LAND_INTERFACE::SetShowParameters() {
  auto* const pA = AttributesPointer ? AttributesPointer->GetAttributeClass("Parameters") : nullptr;
  m_bShowCommandos = 0 != BIUtils::GetLongFromAttr(pA, "DoShowCommandos", true);

  m_pManSign = new BIManSign(GetId(), m_pRS);
  Assert(m_pManSign);
  m_pManSign->Init(AttributesPointer,
                   (AttributesPointer ? AttributesPointer->GetAttributeClass("ManSign") : nullptr));

  BIUtils::FillTextInfoArray(m_pRS, AttributesPointer ? AttributesPointer->GetAttributeClass("textinfo") : nullptr,
                             m_TextInfo);

  m_Images.Init(m_pRS, AttributesPointer ? AttributesPointer->GetAttributeClass("imageslist") : nullptr);
}

void BATTLE_LAND_INTERFACE::UpdateCommandos() const {
  auto* pA = AttributesPointer ? AttributesPointer->GetAttributeClass("data") : nullptr;
  if (pA) pA = pA->GetAttributeClass("icons");
  if (!pA) return;
}

void BATTLE_LAND_INTERFACE::UpdateAlarm() {
}

void BATTLE_LAND_INTERFACE::EnableMessageIcons(VDATA* pvdat) {
}

void BATTLE_LAND_INTERFACE::DisableMessageIcons() {
}

void BATTLE_LAND_INTERFACE::SetTextData() {
}
