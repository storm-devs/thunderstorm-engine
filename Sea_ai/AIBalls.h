#ifndef SEA_BALLS_AI_HPP
#define SEA_BALLS_AI_HPP

#include "../Common_h/vmodule_api.h"
#include "../Common_h/Character.h"
#include "../Common_h/Sd2_h/CannonTrace.h"
#include "../Common_h/vparticle_system.h"
#include "AIHelper.h"

struct BALL_PARAMS
{
	CVECTOR				vFirstPos, vPos;	// first and current ball position
	VPARTICLE_SYSTEM	* pParticle;
	std::string				sBallEvent;
	long				iBallOwner;			// ball owner(character index)
	float				fTime;				// ball time: in seconds
	float				fSpeedV0;			// initial speed: in m/s
	float				fDirX, fDirZ;		// X/Z identity moving(cos(dir),sin(dir))

	float				fSinAngle;			// initial angle: sin(a)
	float				fCosAngle;			// initial angle: cos(a)

	float				fHeightMultiply;	// Height position multiply
	float				fSizeMultiply;		// Size of ball multiply
	float				fTimeSpeedMultiply;	// Time speed multiply
	float				fMaxFireDistance;
	uint32_t				dwCannonType;		// Additional parameter
};

// ============================================================================
// One ball type, contain common parameters
// ============================================================================
struct BALL_TYPE
{
	std::string				sName;				// ball name
	std::string				sParticleName;		// particle name
	uint32_t				dwSubTexIndex;		// 
	uint32_t				dwGoodIndex;		//
	float				fSize;				// ball size(sprite size in meters)
	float				fWeight;			// ball weight
	std::vector<BALL_PARAMS>	Balls;				// container with current balls 

	// constructor for initialization
	//BALL_TYPE() : Balls(_FL_, 64) {};
};

// ============================================================================
// Master class AIBalls
// Contains functions of balls : drawing, physics and collision
// ============================================================================
class AIBalls : public ENTITY
{
private:
	CANNON_TRACE_BASE	* pSail, * pSea, * pFort, * pIsland;

	float				fDeltaTimeMultiplyer;
	float				fBallFlySoundDistance;
	float				fBallFlySoundStereoMultiplyer;

	std::string				sTextureName;				// texture name
	uint32_t				dwTextureIndex;				// texture index
	uint32_t				dwSubTexX, dwSubTexY;		// all balls must be in one texture
	VIDWALKER			* pVWForts, * pVWShips;		// 
	uint32_t				dwFireBallFromCameraTime;

	std::vector<BALL_TYPE>	aBallTypes;					// Balls types container
	std::vector<RS_RECT>		aBallRects;					// Balls container for render

	VDX9RENDER* rs;

	void	AddBall(ATTRIBUTES * pABall);

	// inherited functions from ENTITY
	bool	Init();
	void	SetDevice();

	void	Realize(uint32_t Delta_Time);
	void	Execute(uint32_t Delta_Time);
	
	void	FireBallFromCamera();

	uint32_t	AttributeChanged(ATTRIBUTES * pAttributeChanged);

	uint32_t _cdecl	ProcessMessage(MESSAGE & message);

public:
	static AIBalls * pAIBalls;

	AIBalls();
	~AIBalls();

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);
};

#endif