#ifndef AIHELPER_HPP
#define AIHELPER_HPP

#include "..\common_h\dx9render.h"
#include "..\common_h\island_base.h"
#include "..\common_h\collide.h"
#include "..\common_h\Character.h"
#include "..\common_h\SD2_H\SaveLoad.h"
#include <vector>

class AIAttributesHolder
{
protected:
	ATTRIBUTES		* pACharacter;
public:
	virtual void		SetACharacter(ATTRIBUTES * pAP) { pACharacter = pAP; };
	virtual ATTRIBUTES	* GetACharacter() const { return pACharacter; };
};

class VAI_INNEROBJ;
class AIHelper
{
public:
	AIHelper();
	~AIHelper();

	static	ATTRIBUTES		* pASeaCameras;
	static	ISLAND_BASE		* pIsland;
	static	VDX9RENDER		* pRS;
	static	COLLIDE			* pCollide;

	static	float			fGravity;

	bool	SetDevice();
	bool	Init();
	bool	Uninit();
	void	AddCharacter(ATTRIBUTES * pACharacter, ATTRIBUTES * pAMainCharacter);
	void	CalculateRelations();

	bool	isFriend(ATTRIBUTES * pA1, ATTRIBUTES * pA2) const;
	bool	isEnemy(ATTRIBUTES * pA1, ATTRIBUTES * pA2) const;
	bool	isNeutral(ATTRIBUTES * pA1, ATTRIBUTES * pA2) const;

	ATTRIBUTES * GetMainCharacter(ATTRIBUTES * pACharacter);

	static	VAI_INNEROBJ	* FindAIInnerObj(ATTRIBUTES * pACharacter);

	uint32_t	GetRelation(ATTRIBUTES * pA1, ATTRIBUTES * pA2) const;
	uint32_t	GetRelationSafe(ATTRIBUTES * pA1, ATTRIBUTES * pA2) const;

	static void	Print(float x, float y, float fScale, char * pFormat, ...);
	static void Print3D(CVECTOR vPos, float dy, float fScale, char * pFormat, ...);

	void Save(CSaveLoad * pSL);
	void Load(CSaveLoad * pSL);

private:
	uint32_t				* pRelations, dwRelationSize;
	std::vector<ATTRIBUTES*>	aCharacters, aMainCharacters;

	uint32_t * GetRelation(uint32_t x, uint32_t y) const;
	uint32_t FindIndex(ATTRIBUTES * pACharacter) const;
};

extern AIHelper	Helper;

#endif