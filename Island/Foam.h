#ifndef _COAST_FOAM_HPP_
#define _COAST_FOAM_HPP_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/collide.h"
#include "../Common_h/Island_Base.h"
#include "../Common_h/model.h"
#include "../Common_h/sea_base.h"
#include "../Sea_ai/AIFlowGraph.h"

enum FOAMTYPE
{
	FOAM_TYPE_1 = 1,
	FOAM_TYPE_2 = 2,

	FOAM_MODE_FORCEDWORD = 0x7FFFFFFF
};

class CoastFoam : public Entity 
{
public:
	CoastFoam();
	~CoastFoam();

	bool Init();
	void Realize(uint32_t Delta_Time);
	void Execute(uint32_t Delta_Time);
	uint32_t AttributeChanged(ATTRIBUTES * pA);

private:
	struct FoamVertex
	{
		CVECTOR vPos;
		uint32_t	dwColor;
		float	tu, tv;
	};

	struct FoamPart { CVECTOR v[2]; };

	struct SubPart
	{
		//float tv;
		float fPos;
		float fSpeed;
		//float fA;
	};

	struct WorkPart
	{
		SubPart		p[8];
		CVECTOR		v[2];
		float		tu;
		//FOAMMODE	Mode;
	};

	struct Foam 
	{
		Foam() { iTexture = -1; }

		std::vector<FoamPart>	aFoamParts;
		std::vector<WorkPart>	aWorkParts;
		float			fMove[2];
		float			fSX[2];
		float			fSpeed[2], fBraking[2];
		long			iMode[2];
		long			iTexture;
		std::string			sTexture;
		long			iNumFoams;

		FOAMTYPE		Type;

		float			fAlphaColor[2], fAlpha[2], fAlphaMin, fAlphaMax;
		float			fSpeedMin, fSpeedMax;
		float			fBrakingMin, fBrakingMax;
		float			fAppearMin, fAppearMax;
		float			fTexScaleX;
	};

	long			iEditFoam, iEditFoamPart, iEditFoamVertex;
	bool			bEditMode, bMoved, bCanEdit;
	float			fCursorPosX, fCursorPosY;
	long			iFoamTexture, iCursorTex;
	SEA_BASE		* pSea;
	std::vector<Foam*>	aFoams;
	long			iVBuffer, iIBuffer;
	PLANE			* pFrustumPlanes;

	float			fMaxFoamDistance, fFoamDeltaY;
	long			iFoamDivides;

	uint32_t			dwNumPenasExecuted;

	VDX9RENDER* rs;

	void ExtractRay (const D3DVIEWPORT9 & viewport, float fCursorX, float fCursorY, CVECTOR & raystart, CVECTOR & rayend);

	bool IsClipped(Foam * pF);

	void Save();
	void Load();
	void clear();

	void InitNewFoam(Foam * pF);
	void RecalculateFoam(long iFoam);
	void ExecuteFoamType2(Foam * pF, float fDeltaTime);
	void ExecuteFoamType1(Foam * pF, float fDeltaTime);
};

#endif