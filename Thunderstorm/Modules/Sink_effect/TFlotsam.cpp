#include "TFlotsam.h"
#include "rands.h"
#include "../../Shared/messages.h"
#include "EntityManager.h"

int		  TFlotsam::modelsInitialized = 0;
MODEL *   TFlotsam::models[FLOTSAM_MODELS_COUNT];
char	  TFlotsam::modelNames[FLOTSAM_MODELS_COUNT][128];
entid_t TFlotsam::modelIDs[FLOTSAM_MODELS_COUNT];

//--------------------------------------------------------------------
TFlotsam::TFlotsam()
	:sea(nullptr)
	,enabled(false)
{

}

//--------------------------------------------------------------------
TFlotsam::~TFlotsam()
{
	--modelsInitialized;

	if (!modelsInitialized)
		for (int i=0; i<FLOTSAM_MODELS_COUNT; i++)
			EntityManager::EraseEntity(modelIDs[i]);
}

//--------------------------------------------------------------------
void TFlotsam::Start(float _x, float _z, float _radius)
{
	enabled = true;
	floatTime = 0;
	x = _x + randCentered(_radius);
	z = _z + randCentered(_radius);
	y = sea->WaveXZ(x, z)-FLOTSAM_START_DELTAY; 
	vX = randCentered(1.0f) * FLOTSAM_H_SPEED;
	vY = randUpper(1.0f) * FLOTSAM_V_SPEED;
	vZ = randCentered(1.0f) * FLOTSAM_H_SPEED;
	angY = rand(PIm2);
	turnY = randCentered(1.0f) * FLOTSAM_TURN_SPEED;
	maxFloatTime = (uint32_t) randUpper(FLOTSAM_FLOAT_TIME);
	state = FLOTSAM_RISE;
	//model = models[rand() % FLOTSAM_MODELS_COUNT];
	ModelID = modelIDs[rand() % FLOTSAM_MODELS_COUNT];
	
}

//--------------------------------------------------------------------
void TFlotsam::Initialize(SEA_BASE *_sea)
{
	if (!modelsInitialized)
	{
		//modelsInitialized = true;
		strcpy_s(modelNames[0], "particles\\palka01");
		strcpy_s(modelNames[1], "particles\\palka02");
		strcpy_s(modelNames[2], "particles\\palka03");
		strcpy_s(modelNames[3], "particles\\palka04");

		for (int i=0; i<FLOTSAM_MODELS_COUNT; i++)
		{
			modelIDs[i] = EntityManager::CreateEntity("MODELR");
			api->Send_Message(modelIDs[i],"ls",MSG_MODEL_LOAD_GEO, modelNames[i]);
			models[i] = (MODEL*)EntityManager::GetEntityPointer(modelIDs[i]);
		}
	}

	++modelsInitialized;
	sea = _sea;
}

//--------------------------------------------------------------------
void TFlotsam::Process(uint32_t _dTime)
{
	if (!enabled)
		return;

	float dTime = _dTime / 1000.0f; // msec -> sec

	switch (state)
	{
	case FLOTSAM_RISE:
		x += dTime * vX;
		z += dTime * vZ;
		y += dTime * vY;
		if (y > (sea->WaveXZ(x,z) + FLOTSAM_DY))
			state = FLOTSAM_FLOAT;
		break;
	case FLOTSAM_FLOAT:
		x += dTime * vX;
		z += dTime * vZ;
		floatTime += _dTime;
		angY = (float) fmod(angY + dTime * turnY, PIm2);
		if (floatTime > maxFloatTime)
			state = FLOTSAM_SINK;
		break;
	case FLOTSAM_SINK:
		x += dTime * vX;
		z += dTime * vZ;
		y -= dTime * vY;
		if (y <= sea->WaveXZ(x,z) - FLOTSAM_START_DELTAY)
			enabled = false;
		break;
	}

}

//--------------------------------------------------------------------
void TFlotsam::Realize(uint32_t _dTime)
{
	if (!enabled)
		return;

	CVECTOR pos(x, 0, z);
	if (state == FLOTSAM_FLOAT)
		pos.y = sea->WaveXZ(x,z) + FLOTSAM_DY;
	else
		pos.y = y;
	CVECTOR ang(0.0f, angY, 0.0f);
	MODEL * model;
	model = (MODEL *)EntityManager::GetEntityPointer(ModelID);
	if(model)
	{
		model->mtx.BuildMatrix(ang, pos);
		model->ProcessStage(Entity::Stage::realize, _dTime);
	}
}

//--------------------------------------------------------------------
bool TFlotsam::Enabled()
{
	return enabled;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------