#ifndef __BATTLE_NAVIGATOR_H_
#define __BATTLE_NAVIGATOR_H_

#include "../bi_defines.h"
#include "Weather_Base.h"

#define RADIAL_QUANTITY					36
#define BI_DEFAULT_COLOR				0xFF0010C0
#define BI_ONESIDE_SIZE					6
#define BI_SIDE_QUANTITY				4
#define FIRERANGE_QUANTITY				(BI_ONESIDE_SIZE+1)*BI_SIDE_QUANTITY
#define MAX_ENEMY_SHIP_QUANTITY			20

class BATTLE_NAVIGATOR {
  VDX9RENDER* rs;
  Entity* m_pOwnerEI;

public:
  BATTLE_NAVIGATOR(BATTLE_NAVIGATOR&&) = delete;
  BATTLE_NAVIGATOR(const BATTLE_NAVIGATOR&) = delete;
  BATTLE_NAVIGATOR();
  ~BATTLE_NAVIGATOR();

  void Draw() const;
  void Update();
  void Init(VDX9RENDER* RenderService, Entity* pOwnerEI);
  void SetIsland();

  void DecrementScale() {
    m_fCurScale -= m_fScaleStep;
    if (m_fCurScale < m_fMinScale) m_fCurScale = m_fMinScale;
  }

  void IncrementScale() {
    m_fCurScale += m_fScaleStep;
    if (m_fCurScale > m_fMaxScale) m_fCurScale = m_fMaxScale;
  }

  void SetEnoughBalls(bool notEnoughBallFlag) { m_bNotEnoughBallFlag = notEnoughBallFlag; }
  void LostRender();
  void RestoreRender();

protected:
  void CalculateTextureRect(FRECT& texRect, long num, long hq, long vq);
  long SetCircleVertexPos(BI_ONETEXTURE_VERTEX* v, float x, float y, float rad, float angle = 0) const;
  long SetCircleVertexTex(BI_ONETEXTURE_VERTEX* v, float x = .5f, float y = .5f, float rad = .5f, float angle = 0);
  long SetRectangleVertexPos(BI_ONETEXTURE_VERTEX* v, float x, float y, float width, float height,
                             float angle = 0) const;
  long SetRectangleVertexTex(BI_ONETEXTURE_VERTEX* v, float x = .5f, float y = .5f, float width = 1.f,
                             float height = 1.f, float angle = 0);
  long SetRectangleSegVertexPos(BI_ONETEXTURE_VERTEX* v, float x, float y, float width, float height, float begAngle,
                                float endAngle);
  long SetRectangleSegVertexTex(BI_ONETEXTURE_VERTEX* v, float x, float y, float width, float height, float begAngle,
                                float endAngle);
  float CalculateCrossX(int side, float w, float h, float angl);
  float CalculateCrossY(int side, float w, float h, float angl);

  void SetMainCharacterData();
  void SetAnotherShip();
  void ReleaseAll();
  void UpdateMiniMap();
  void UpdateFireRangeBuffer() const;
  void FillOneSideFireRange(BI_NOTEXTURE_VERTEX* pv, ATTRIBUTES* pShip, ATTRIBUTES* pChar, const char* pstr) const;
  void UpdateCurrentCharge();

  void UpdateWindParam();

protected:
  uint32_t m_dwBackGradColor1;
  uint32_t m_dwBackGradColor2;
  // ��������� �������� ���������
  float m_fMapRadius; // ������ ��������� �� ������
  float m_fTextureRad; // ������ ��������� � ��������
  float m_fWorldRad; // ������ ��������� � ������� �����������
  float m_fCurScale; // ������� ���������
  float m_fDefaultScale; // ������� ����� �� ���������
  float m_fMinScale; // ����������� ������� �����
  float m_fMaxScale; // ������������ ������� �����
  float m_fScaleStep; // ��� ��������� ��������
  float m_fShipShowRad; // ������ ������������� �������

  // ��������� �������������� ����
  long m_NavigationWidth;
  long m_NavigationHeight;
  long m_XNavigator;
  long m_YNavigator;

  // ���������� ������ �������
  float m_fXPos;
  float m_fYPos;
  float m_fAngle;
  float m_fShipSpeed;
  float m_fMaxShipSpeed;
  float m_fShipSpeedScale;

  // ���������� �������
  bool m_bYesIsland;
  float m_fXIsland;
  float m_fYIsland;
  float m_fIslandWidth;
  float m_fIslandHeight;
  float m_fIslandRadius;

  // �����
  float m_fWindAngle;
  float m_fWindStrength;
  float m_fWindMaxStrength;
  long m_windWidth;
  long m_windHeight;

  // ��������� ������ �����
  uint32_t m_dwChargeCannon;
  uint32_t m_dwReadyCannon;
  uint32_t m_dwDamagedCannon;

  float m_fBegAnglLeftCharge;
  float m_fCurAnglLeftCharge;
  float m_fCurAnglLeftDamage;
  float m_fEndAnglLeftCharge;

  float m_fBegAnglRightCharge;
  float m_fCurAnglRightCharge;
  float m_fCurAnglRightDamage;
  float m_fEndAnglRightCharge;

  float m_fBegAnglForwardCharge;
  float m_fCurAnglForwardCharge;
  float m_fCurAnglForwardDamage;
  float m_fEndAnglForwardCharge;

  float m_fBegAnglBackCharge;
  float m_fCurAnglBackCharge;
  float m_fCurAnglBackDamage;
  float m_fEndAnglBackCharge;

  // ��������� �������� ������� � �����
  float m_fBegAnglShipSpeed;
  float m_fEndAnglShipSpeed;
  float m_fCurAnglShipSpeed;
  float m_fBegAnglWindSpeed;
  float m_fEndAnglWindSpeed;
  float m_fCurAnglWindSpeed;

  // ��������
  long m_idCompasTex; // ������
  long m_idSpeedTex; // �������� ������� � �����
  long m_idCannonTex; // ����� �����
  long m_idEmptyTex; // ������ ����� ��� �������� � ������
  long m_idIslandTexture; // ������
  long m_idWindTex; // �����
  long m_idChargeTexture; // ������� ��� ������ �����
  long m_idPowderTexture; // ������� �����
  long m_idWindTexture; // �������� �����
  long m_idSailTexture; // ��������� �������/�������� �������
  IDirect3DTexture9* m_pIslandTexture;

  uint32_t m_dwSeaColor; // ���� ���� �� ���������
  uint32_t m_dwFireZoneColor; // ���� ���� ���� �� ���������
  uint32_t m_dwEnemyShipColor; // ���� ��������� ��������
  uint32_t m_dwFrendShipColor; // ���� ����� ��������
  uint32_t m_dwNeutralShipColor; // ���� ����� ��������
  uint32_t m_dwDeadShipColor; // ���� �������� �������

  // ������
  long m_idEmptyVBuf;
  long m_idMapVBuf;
  //--------------------
  long m_idFireZoneVBuf; // ������� ����� ���� �����
  //--------------------
  long m_idCannonVBuf;
  long m_nvCannonCharge;
  long m_nvCannonReady;
  long m_nvCannonDamage;
  //--------------------
  long m_idSpeedVBuf;
  long m_nvSpeed;
  //--------------------
  long m_idShipsVBuf;
  long m_nvShips;
  //--------------------
  long m_idGradBackVBuf;
  //--------------------
  long m_idCurChargeVBuf;

  // ������ � �������
  long m_speedFont;
  long m_ySpeedShow;
  long m_xShipSpeed;
  long m_xWindSpeed;

  WEATHER_BASE* m_wb;
  ATTRIBUTES* m_pAWeather;

  // ������ �������� ���� ������ �����
  POINT m_ChargeGreed;
  POINT m_ChargePos;
  POINT m_ChargeSize;
  long m_curCharge;
  // ������ ������
  POINT m_PowderGreed;
  POINT m_PowderPos;
  POINT m_PowderSize;
  long m_curPowder;
  bool m_bPowderRunOut; // ��� �������
  // ������ �����
  long m_curWindPic;
  POINT m_WindGreed;
  POINT m_WindPos;
  POINT m_WindSize;
  // ������ ��������� �������
  long m_curSailState;
  POINT m_SailGreed;
  POINT m_SailPos;
  POINT m_SailSize;

  float m_fFontScale;

  bool m_bNotEnoughBallFlag;

  float m_fAspectRatio;
};

#endif
