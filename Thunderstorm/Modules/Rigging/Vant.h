#ifndef _VANT_H_
#define _VANT_H_

#include "dx9render.h"
#include "geos.h"
#include "Matrix.h"
#include "vmodule_api.h"

class NODE;

#define VANT_EDGE 5 // ����� ������ � ������� �������

#define VANTVERTEX_FORMAT		(D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEXTUREFORMAT2)

struct VANTVERTEX {
  CVECTOR pos;
  float tu, tv;
};

class VANT : public Entity {
  // ��������� ���������� �� INI-����� //
  //-------------------------------------
  int ROPE_QUANT; // ���������� �������
  float ROPE_WIDTH; // ������� �������
  float upWidth; // ������ �������� ������������
  float upHeight; // ������ �������� ������������
  float treangXl; // ���������� �������� ������������
  float treangXr; //
  float treangYu; //
  float treangYd; //
  float balkYu; // ���������� �������� �����
  float balkYd; //
  float ropeXl; // ���������� �������� ������������ �������
  float ropeXr; //
  float vRopeXl; // ���������� �������� �������������� ������� xBeg
  float vRopeXr; //
  float vRopeHeight; // ������ ������������ �������
  float hRopeHeight; // ������ �������������� �������
  float fBalkHeight; // ������ ����� ������������ ������ ������������
  float fBalkWidth; //
  float fVantMaxDist; // ������� ���������� � �������� �� ����� �����
  float ZERO_CMP_VAL; // ��� ������������� �������� �����
  float MAXFALL_CMP_VAL; // ������������ ��������� ��������� ����� ��� ������� ���� ��������� ������������
  //-------------------------------------
  FILETIME ft_old;

  bool bUse;
  bool bRunFirstTime;
  bool bYesDeleted;
  int wVantLast;
  VDX9RENDER* RenderService;
  char* TextureName;
  long texl;

public:
  VANT();
  ~VANT();
  void SetDevice();
  bool Init() override;
  void Realize(uint32_t Delta_Time) const;
  void Execute(uint32_t Delta_Time);
  bool CreateState(ENTITY_STATE_GEN* state_gen);
  bool LoadState(ENTITY_STATE* state);
  uint64_t ProcessMessage(MESSAGE& message) override;

  void ProcessStage(Stage stage, uint32_t delta) override {
    switch (stage) {
    case Stage::execute:
      Execute(delta);
      break;
    case Stage::realize:
      Realize(delta);
      break;
      /*case Stage::lost_render:
        LostRender(delta); break;
      case Stage::restore_render:
        RestoreRender(delta); break;*/
    }
  }

private:
  struct VANTDATA {
    bool bDeleted;
    CVECTOR pUp, pLeft, pRight;
    CMatrix *pUpMatWorld, *pDownMatWorld;
    uint32_t sv, nv, st, nt;

    int vantNum;
    CVECTOR pos[VANT_EDGE];

    CVECTOR pUpOld, pLeftOld, pUpStart, pLeftStart;
    int HostGroup;
  };

  int vantQuantity;
  VANTDATA** vlist;

  struct GROUPDATA {
    bool bDeleted;
    int vantQuantity;
    int* vantIdx;
    long sVert, nVert;
    long sIndx, nIndx;

    CMatrix* pMatWorld;
    entid_t model_id;
    entid_t shipEI;
  };

  int groupQuantity;
  GROUPDATA* gdata;

  void SetVertexes() const;
  void SetIndex() const;
  void AddLabel(GEOS::LABEL& lbl, NODE* nod);
  void SetAll();
  void SetAdd(int firstNum);
  void LoadIni();
  void doMove();
  bool VectCmp(CVECTOR v1, CVECTOR v2, float minCmpVal);
  void FirstRun();
  void DoSTORM_DELETE();

  VANTVERTEX* vertBuf;

  long vBuf, iBuf;
  uint32_t nVert, nIndx;
};


#endif
