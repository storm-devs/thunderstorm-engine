#ifndef _SAIL_H_
#define _SAIL_H_

#include "SAILONE.h"
#include "vmodule_api.h"
#include "dx9render.h"
#include "sail_base.h"
#include "geos.h"
#include "model.h"

struct SAILGROUP {
    uint32_t nVert,nIndx;
    long vertBuf,indxBuf;
};

class SAIL : public SAIL_BASE
{
    // параметры загружаемые из INI-файла //
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

float m_fMinSpeedVal; // минимальная скорость даваемая парусами

// описание ветра
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
	uint64_t ProcessMessage(MESSAGE & message);
	void SetDevice();
    // Collision func
    int LastTraceGroup;
    float Trace(const CVECTOR &src,const CVECTOR &dst);
	const char *GetCollideMaterialName();
	bool GetCollideTriangle(TRIANGLE &triangle);
	bool Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly);
    float Cannon_Trace(long iBallOwner, const CVECTOR &src,const CVECTOR &dst);
    entid_t GetShipID() {return gdata[LastTraceGroup].shipEI;}
	SAILONE_BASE * FindSailForCharacter(int chrIdx,char* nodeName,int grNum);
	uint32_t AttributeChanged(ATTRIBUTES * pAttr);

	void LostRender();
	void RestoreRender();

	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
		case Stage::lost_render:
			LostRender(); break;
		case Stage::restore_render:
			RestoreRender(); break;
		}
	}

	int GetSailStateForCharacter(int chrIdx);

    SAILGROUP sg;

private:
    SAILTIME tm;
    // список всех парусов
    int sailQuantity;
    SAILONE* *slist;
    // список всех групп парусов
    int groupQuantity;
    struct GROUPDATA
    {
        bool bDeleted;
		bool bYesShip;
        entid_t shipEI;
        entid_t modelEI;
        int   sailQuantity;
        int*  sailIdx;
        // ограничительный гробик
        CVECTOR boxCenter,boxSize;
        float boxRadius;
        // Влияние на скорость корабля
        float shipSpeed;
        float maxSpeed;
        float speed_c,speed_m; // реальная и максимальная скорость даваемая парусами
		int   maxHole,curHole;
		int maxSP;
        // спуск\подъем парусов
        int   curSailSet;
        bool  bFinalSailUp;
        bool  bFinalSailDo;
		bool  bFinalSailDoOld;
        float fSpeedMul;
		float fRollingSpeed;
		// цвет парусов
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
    void	DoSailToNewHost(entid_t newMdlEI, entid_t hewHostEI, int grNum, NODE *nod, entid_t oldmodelEI);
    void	DoNoRopeSailToNewHost(entid_t newModel, entid_t newHost, entid_t oldHost);
    void	DeleteSailGroup();
	int		FindGroupForCharacter(int chrIdx);
	int		GetCharacterForGroup(int grNum);
	SAILONE * FindSailFromData(int gn,char* nodeName,char* grName);
	void	SetSailTextures(long grNum, VDATA* pvd);
	void	DoRandomsSailsDmg(int chrIdx, int gn, float fDmg);

	// обработка скриптовых запросов
	uint32_t ScriptProcessing(char * name, MESSAGE & message);

    bool bFirstRun;
    int  wFirstIndx;
    bool bDeleteState;
    bool bCannonTrace;

	long m_nMastCreatedCharacter;
	char* m_sMastName;

	long m_nLastUpdate;
};

#endif