#ifndef _SAIL_H_
#define _SAIL_H_

#include "SAILONE.h"
#include "../common_h/vmodule_api.h"
#include "../common_h/dx9render.h"
#include "../common_h/sail_base.h"
#include "../common_h/geos.h"
#include "../common_h/model.h"

struct SAILGROUP {
    uint32_t nVert,nIndx;
    long vertBuf,indxBuf;
};

class SAIL : public SAIL_BASE
{
    // ��������� ����������� �� INI-����� //
    //--------------------------------------
//float sailDownStep;
float SsailWindDepend;
float TsailWindDepend;
float FLEXSPEED;
float MAXSUMWIND;
float WINDANGL_DISCRETE;
float MAXTURNANGL;
float TURNSTEPANGL;
float ROLLINGSPEED;
int WINDVECTOR_TINCR;
int WINDVECTOR_TADD;
int WINDVECTOR_SINCR;
int WINDVECTOR_SADD;
int WINDVECTOR_QUANTITY;
float ts_min;
float ts_xdep;
float ts_zdep;
float fs_min;
float fs_xdep;
float fs_zdep;
float ss_min;
float ss_xdep;
float ss_zdep;
int texQuantity;
float texNumCommon;
float texNumEnglish;
float texNumTreangle;
float ROLL_Z_VAL;
float ROLL_Z_DELTA;
float ROLL_Y_VAL;
float ROLL_Y_DELTA;
float SSailRollForm[SAIL_COL_MAX];
float TSailRollForm[5];
float TR_FORM_MUL;
float fWindAdding;
float fTHoleFlexDepend;
float fSHoleFlexDepend;
float FALL_SSAIL_ADD_MIN;
float FALL_SSAIL_ADD_RAND;
float FALL_TSAIL_ADD_MIN;
float FALL_TSAIL_ADD_RAND;

long GROUP_UPDATE_TIME;

uint16_t SailQuantity;
uint16_t SailCurNum;

float m_fMinSpeedVal; // ����������� �������� �������� ��������

// �������� �����
WIND globalWind;
float *WindVect;
    //------------------------------------------

    friend SAILONE;
    bool bUse;
	VDX9RENDER * RenderService;
    D3DMATERIAL9 mat;
    FILETIME ft_old;
    long texl;
	long m_nEmptyGerbTex;

public:
	 SAIL();
	~SAIL();
    // Entity func
	bool Init();
	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);
	bool CreateState(ENTITY_STATE_GEN * state_gen);
	bool LoadState(ENTITY_STATE * state);
	uint32_t _cdecl ProcessMessage(MESSAGE & message);
	void SetDevice();
    // Collision func
    int LastTraceGroup;
    float Trace(const CVECTOR &src,const CVECTOR &dst);
	const char *GetCollideMaterialName();
	bool GetCollideTriangle(TRIANGLE &triangle);
	bool Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly);
    float Cannon_Trace(long iBallOwner, const CVECTOR &src,const CVECTOR &dst);
    ENTITY_ID GetShipID() {return gdata[LastTraceGroup].shipEI;}
	SAILONE_BASE * FindSailForCharacter(int chrIdx,char* nodeName,int grNum);
	uint32_t AttributeChanged(ATTRIBUTES * pAttr);

	void LostRender();
	void RestoreRender();

	int GetSailStateForCharacter(int chrIdx);

    SAILGROUP sg;

private:
    SAILTIME tm;
    // ������ ���� �������
    int sailQuantity;
    SAILONE* *slist;
    // ������ ���� ����� �������
    int groupQuantity;
    struct GROUPDATA
    {
        bool bDeleted;
		bool bYesShip;
        ENTITY_ID shipEI;
        ENTITY_ID modelEI;
        int   sailQuantity;
        int*  sailIdx;
        // ��������������� ������
        CVECTOR boxCenter,boxSize;
        float boxRadius;
        // ������� �� �������� �������
        float shipSpeed;
        float maxSpeed;
        float speed_c,speed_m; // �������� � ������������ �������� �������� ��������
		int   maxHole,curHole;
		int maxSP;
        // �����\������ �������
        int   curSailSet;
        bool  bFinalSailUp;
        bool  bFinalSailDo;
		bool  bFinalSailDoOld;
        float fSpeedMul;
		float fRollingSpeed;
		// ���� �������
		uint32_t dwSailsColor;
    };
    GROUPDATA* gdata;
    void FirstRun();

	bool	GetSailGrid();
    void	AddSailLabel(GEOS::LABEL& lbl, NODE* nod, bool bSailUp);
    void	SetAllSails(int groupNum);
    void	SetAllSails();
    void	SetAddSails(int firstSail);
    void	LoadSailIni();
    void	DoSailToNewHost(ENTITY_ID newMdlEI, ENTITY_ID hewHostEI, int grNum, NODE *nod, ENTITY_ID oldmodelEI);
    void	DoNoRopeSailToNewHost(ENTITY_ID newModel, ENTITY_ID newHost, ENTITY_ID oldHost);
    void	DeleteSailGroup();
	int		FindGroupForCharacter(int chrIdx);
	int		GetCharacterForGroup(int grNum);
	SAILONE * FindSailFromData(int gn,char* nodeName,char* grName);
	void	SetSailTextures(long grNum, VDATA* pvd);
	void	DoRandomsSailsDmg(int chrIdx, int gn, float fDmg);

	// ��������� ���������� ��������
	uint32_t _cdecl ScriptProcessing(char * name, MESSAGE & message);

    bool bFirstRun;
    int  wFirstIndx;
    bool bDeleteState;
    bool bCannonTrace;

	long m_nMastCreatedCharacter;
	char* m_sMastName;

	long m_nLastUpdate;
};

#endif