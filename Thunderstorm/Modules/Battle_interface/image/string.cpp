#include "string.h"
#include "imgrender.h"
#include "../bi_defines.h"

BIString::BIString(BIImageRender* pImgRender, VDX9RENDER* rs) {
  m_pImgRender = pImgRender;
  Assert(m_pImgRender);
  m_pRS = rs;
  Assert(m_pRS);
  m_nPrioritet = ImagePrioritet_DefaultValue;
  m_bUpdateString = false;

  m_nFontID = -1;
  m_dwColor = 0xFFFFFFFF;
  m_fScale = 1.f;
  ZERO(m_pntOutPos);
}

BIString::~BIString() {
  Release();
}

void BIString::Render() {
  if (m_bUpdateString) {
    UpdateString();
  }
  m_pRS->ExtPrint(m_nFontID, m_dwColor, 0, PR_ALIGN_LEFT, true, m_fScale, 0, 0,
                  m_pntOutPos.x, m_pntOutPos.y, "%s", m_sText.c_str());
}

void BIString::SetFont(const char* pcFontName) {
  FONT_RELEASE(m_pRS, m_nFontID);
  m_nFontID = m_pRS->LoadFont((char*)pcFontName);
  m_bUpdateString = true;
}

void BIString::SetAlign(long nHorzAlign, long nVertAlign) {
  m_bUpdateString = true;
}

void BIString::SetPosition(long nLeft, long nTop, long nRight, long nBottom) {
  m_pImgRender->TranslateBasePosToRealPos(static_cast<float>(nLeft), static_cast<float>(nTop), m_BasePos.left,
                                          m_BasePos.top);
  m_pImgRender->TranslateBasePosToRealPos(static_cast<float>(nRight), static_cast<float>(nBottom), m_BasePos.right,
                                          m_BasePos.bottom);
  m_bUpdateString = true;
}

void BIString::SetString(const char* pcStr) {
  m_sText = pcStr;
  m_bUpdateString = true;
}

void BIString::Release() {
}

void BIString::UpdateString() {
  m_bUpdateString = false;
}
