#ifndef _MAST_H_
#define _MAST_H_

#include "../common_h/dx9render.h"
#include "../common_h/model.h"
#include "../common_h/collide.h"

#define SR_MOVE         1
#define SR_STOPROTATE   2
#define SR_YROTATE      4

class MAST : public Entity
{
	struct MountData {
		NODE * pNode;
		entid_t shipEI;
		entid_t modelEI;
	} m_mount_param;
    bool            bUse;
    bool            bFallUnderWater;
    int             wMoveCounter;
	VDX9RENDER		*RenderService;
	COLLIDE			*pCollide;
    bool            bModel;
    entid_t       model_id,oldmodel_id;
    entid_t       ship_id;
    FILETIME        ft_old;
	NODE*			m_pMastNode;
public:
	 MAST();
	~MAST();
	void            SetDevice();
	bool            Init();
	void            Move();
    void            Execute(uint32_t Delta_Time);
	void            Realize(uint32_t Delta_Time);
	bool            CreateState(ENTITY_STATE_GEN * state_gen);
	bool            LoadState(ENTITY_STATE * state);
	uint32_t _cdecl    ProcessMessage(MESSAGE & message);
protected:
    void            AllRelease();
    void _cdecl     Mount( entid_t modelEI, entid_t shipEI, NODE* mastNodePointer );
    void            LoadIni();
    void            doMove(uint32_t DeltaTime);
    int             GetSlide(entid_t mod, CVECTOR &pbeg, CVECTOR &pend, CVECTOR &dp, CVECTOR &lrey, CVECTOR &rrey, float &angl);
    struct MASTMOVE
    {
        CVECTOR bp,ep; // координаты мачты
        CVECTOR brey,erey; // координаты реи

        CVECTOR ang,dang,sdang;
        CVECTOR mov,dmov,sdmov;
    };
    MASTMOVE mm;
};

#endif