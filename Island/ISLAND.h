#ifndef _ISLAND_H_
#define _ISLAND_H_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/dx9render.h"
#include "../Common_h/collide.h"
#include "../Common_h/Island_Base.h"
#include "../Common_h/model.h"
#include "../Common_h/geometry.h"
#include "../Sea_ai/AIFlowGraph.h"

class MapZipper
{
private: 
	uint32_t	dwSizeX;
	uint32_t	dwDX;
	uint32_t	dwBlockSize, dwBlockShift;
	uint32_t	dwShiftNumBlocksX;
	uint32_t	dwNumRealBlocks;

	uint16_t	* pWordTable;
	uint8_t	* pRealData;
public:
	MapZipper();
	~MapZipper(); 

	uint32_t	GetSizeX() { return dwSizeX; };

	void	UnInit();
	void	DoZip(uint8_t * pSrc, uint32_t dwSizeX);
	uint8_t	Get(uint32_t dwX, uint32_t dwY);

	bool	Save(std::string sFileName);
	bool	Load(std::string sFileName);

	bool	isLoaded() { return pRealData != nullptr; }
};

class ISLAND : public ISLAND_BASE
{
private:
	std::string				sIslandName;
	std::vector<entid_t>	aSpheres;
	std::vector<entid_t>	aForts;
	AIFlowGraph			AIPath;
	entid_t			AIFortEID;

	FRECT				rIsland;
	bool				bForeignModels;
	bool				bDrawReflections;
	float				fStepDX, fStepDZ, fStep1divDX, fStep1divDZ;
	float				fShadowMapSize, fShadowMapStep;
	CVECTOR				vBoxSize, vBoxCenter, vRealBoxSize;
	uint32_t				iDMapSize, iDMapSizeShift;
	entid_t			model_id, seabed_id;

	bool				bFirstRealize;

	char				cModelsDir[256], cModelsID[256], cFoamDir[256];
	
	float				fDepthHeight[256];

	MapZipper			mzShadow, mzDepth;

	uint8_t				* pDepthMap;
	uint8_t				* pShadowMap;

	VDX9RENDER			* pRS;
	VGEOMETRY			* pGS;
	COLLIDE				* pCollide;

	CMatrix				mIslandOld, mSeaBedOld;
	float				fImmersionDepth, fImmersionDistance;
	float				fCurrentImmersion;

	void	Blur8(uint8_t * * pBuffer, uint32_t dwSize);
	bool	SaveTga8(char * fname, uint8_t * pBuffer, uint32_t dwSizeX, uint32_t dwSizeY);

	// shadow map section
	bool	CreateShadowMap(char * pDir, char * pName);
	float	GetShadowTemp(long iX, long iZ);

	// depth map section
	bool	CreateHeightMap(char * pDir, char * pName);
	bool	ActivateCamomileTrace(CVECTOR & vSrc);
	inline float	GetDepthCheck(uint32_t iX, uint32_t iZ);
	inline float	GetDepthNoCheck(uint32_t iX, uint32_t iZ);

	bool	Mount(char *fname, char * fdir, entid_t * eID);
	void	Uninit();

	void	CalcBoxParameters(CVECTOR & vBoxCenter, CVECTOR & vBoxSize);

	void	CreateDirectories(char * pDir);

	void	SetName(char * pIslandName) { sIslandName = pIslandName; };
	char	* GetName() { return (char*)sIslandName.c_str(); };

	void	AddLocationModel(entid_t  eid, char * pIDStr, char * pStr);

	// debug
	void	DoZapSuperGenerator();
	void	DoZapSuperGeneratorInnerDecodeFiles(char * sub_dir, char * mask);
	bool	DoZapSuperGeneratorDecodeFile(char * sname);

public:
	 ISLAND();
	~ISLAND();
	bool			Init();
	void			Realize(uint32_t Delta_Time);
	uint32_t	ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		//case Stage::execute:
		//	Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}


	void			Move();
	void			SetDevice();

// inherit functions COLLISION_OBJECT
	float		Trace(const CVECTOR &src, const CVECTOR &dst);
	bool		Clip(const PLANE *planes, long nplanes, const CVECTOR &center, float radius, ADD_POLYGON_FUNC addpoly) { return false; };

	const char	*GetCollideMaterialName() { return nullptr; };
	bool		GetCollideTriangle(TRIANGLE &triangle) { return false; };

// inherit functions CANNON_TRACE_BASE
    float		Cannon_Trace(long iBallOwner, const CVECTOR &src, const CVECTOR &dst);

// inherit functions ISLAND_BASE
	bool		GetMovePoint(CVECTOR & vSrc, CVECTOR & vDst, CVECTOR & vRes);

	entid_t	GetModelEID() { return model_id; };
	entid_t	GetSeabedEID() { return seabed_id; };

	bool		Check2DBoxDepth(CVECTOR vPos, CVECTOR vSize, float fAngY, float fMinDepth);
	bool		GetDepth(float x, float z, float * fRes = nullptr);
	bool		GetDepthFast(float x, float z, float * fRes = nullptr);
	bool		GetDepth(FRECT * pRect, float * fMinH, float * fMaxH);

	bool		GetShadow(float x, float z, float * fRes = nullptr);

	float		GetCurrentImmersion() { return fCurrentImmersion; };
};

#endif