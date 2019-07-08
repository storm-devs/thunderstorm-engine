//============================================================================================
//	Spirenkov Maxim, 2001
//--------------------------------------------------------------------------------------------
//	Sea dogs II
//--------------------------------------------------------------------------------------------
//	ModelArray
//--------------------------------------------------------------------------------------------
//	Хранение информации о моделях
//============================================================================================

#include "../Common_h/geometry.h"

#include "ModelArray.h"
#include "../Shared/messages.h"
#include "../Common_h/model.h"

//============================================================================================
//Конструирование, деструктурирование
//============================================================================================

ModelArray::ModelArray()
{
	numModels = 0;
	maxModels = 0;
	modelspath[0] = 0;
	texturespath[0] = 0;
	lightpath[0] = 0;
	isHavecTrg = false;
}

ModelArray::~ModelArray()
{
	while(numModels) 
		DeleteModel(numModels - 1);
}

//Создать модель
long ModelArray::CreateModel(const char * modelName, const char * technique, long level, bool isVisible, void* pLights)
{
	if(!modelName || !modelName[0]) return -1;
	//Путь для модельки
	strcpy_s(resPath, modelspath);
	strcat_s(resPath, modelName);
	//Путь для текстур
	VGEOMETRY * gs = (VGEOMETRY *)api->CreateService("geometry");
	if(!gs)
	{
		api->Trace("Can't create geometry service!");
		return -1;
	}
	gs->SetTexturePath(texturespath);
	//Расширяем массивчик
	if(numModels == maxModels)
	{
		maxModels += 4;
		model.resize(maxModels);
	}
	//Создаём модельку
	entid_t id,idModelRealizer;
	if(!(id = api->CreateEntity("modelr"))) return -1;
	if(!(idModelRealizer = api->CreateEntity("LocModelRealizer"))) {api->EraseEntity(id); return -1;}
	api->Send_Message(idModelRealizer,"lil",1,id,(long)pLights);
	//if(isVisible) api->LayerAdd("realize", idModelRealizer, level);
	api->LayerAdd("realize", idModelRealizer, level);
	api->Send_Message(idModelRealizer,"ll",2,isVisible);
	MODEL * m = (MODEL *)api->GetEntityPointer(id);
	if(!m)
	{
		gs->SetTexturePath("");
		api->EraseEntity(id);
		api->EraseEntity(idModelRealizer);
		return -1;
	}
	//Загружаем
	api->Send_Message(id,
							"ls",
							MSG_MODEL_SET_LIGHT_PATH,
							lightpath);
	api->Send_Message(id,
							"ls",
							MSG_MODEL_SET_LIGHT_LMPATH,
							shadowpath);
	if(!api->Send_Message(id,
							"ls",
							MSG_MODEL_LOAD_GEO,
							resPath))
	{
		gs->SetTexturePath("");
		api->EraseEntity(id);
		api->EraseEntity(idModelRealizer);
		return -1;
	}
	gs->SetTexturePath("");

	//Запоминаем
	model[numModels].id = id;
	model[numModels].modelrealizer = idModelRealizer;
	//Сохраняем имя модельки
	if(strlen(modelName) < MA_MAX_NAME_LENGTH)
	{
		strcpy_s(model[numModels].name, modelName);
	}else{
		api->Trace("Model name %s is very long", maxModels);
		memcpy(model[numModels].name, modelName, MA_MAX_NAME_LENGTH);
		model[numModels].name[MA_MAX_NAME_LENGTH - 1] = 0;
	}
	model[numModels].hash = CalcHashString(model[numModels].name);
	model[numModels].slider = nullptr;
	model[numModels].rotator = nullptr;
	model[numModels].reflection = nullptr;
	model[numModels].flags = 0;
	model[numModels].isVisible = isVisible;
	//Устанавливаем технику модельки
	/*if(!technique || !technique[0])
	{
		technique = "DLightModel";
	}*/
	if(technique && technique[0])
	{
		for(long i = 0; i < 1024; i++)
		{
			NODE * nd = m->GetNode(i);
			if(!nd) break;
			nd->SetTechnique(technique);
		}
	}
	//Возвращаем индекс
	return numModels++;
}

//Удалить модель
void ModelArray::DeleteModel(long modelIndex)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	//Удаляем эфекты
	if(model[modelIndex].slider) delete model[modelIndex].slider;
	model[modelIndex].slider = nullptr;
	if(model[modelIndex].rotator) delete model[modelIndex].rotator;
	model[modelIndex].rotator = nullptr;
	if(model[modelIndex].reflection) delete model[modelIndex].reflection;
	model[modelIndex].reflection = nullptr;
	//Удаляем модельку
	api->EraseEntity(model[modelIndex].modelrealizer);
	api->EraseEntity(model[modelIndex].id);
	numModels--;
	if(modelIndex != numModels) model[modelIndex] = model[numModels];
}

//Установить модели анимацию
bool ModelArray::SetAnimation(long modelIndex, const char * modelAni)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	return api->Send_Message(model[modelIndex].id,
									"ls",
									MSG_MODEL_LOAD_ANI,
									modelAni) != 0;
}

//Найти индекс модели по имени
long ModelArray::FindModel(const char * modelName)
{
	if(!modelName) return -1;
	//Конвертим во внутренние имя
	char buf[MA_MAX_NAME_LENGTH];
	if(strlen(modelName) < MA_MAX_NAME_LENGTH)
	{
		strcpy_s(buf, modelName);
	}else{
		memcpy(buf, modelName, MA_MAX_NAME_LENGTH);
		buf[MA_MAX_NAME_LENGTH - 1] = 0;
	}
	//Ищем хэшь значение
	uint32_t hash = CalcHashString(buf);
	//Ищем модельку
	for(long i = 0; i < numModels; i++)
	{
		if(model[i].hash == hash)
		{
			if(_stricmp(model[i].name, buf) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}

//Количество моделий
long ModelArray::Models()
{
	return numModels;
}

//Получение ID модели по индексу
entid_t  ModelArray::ID(long modelIndex)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	return model[modelIndex].id;
}

entid_t  ModelArray::RealizerID(long modelIndex)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	return model[modelIndex].modelrealizer;
}

//Получение модели по индексу
MODEL * ModelArray::operator [](long modelIndex)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	return (MODEL *)api->GetEntityPointer(model[modelIndex].id);
}

//Получение анимации по индексу
Animation * ModelArray::GetAnimation(long modelIndex)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	MODEL * m = (MODEL *)api->GetEntityPointer(model[modelIndex].id);
	if(!m) return nullptr;
	return m->GetAnimation();
}

//Установить модельке анимацию скольжения uv
void ModelArray::SetUVSlide(long modelIndex, float u0, float v0, float u1, float v1)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	if(!model[modelIndex].slider) model[modelIndex].slider = new UVSlider;
	UVSlider * sl = model[modelIndex].slider;
	sl->u0 = sl->v0 = 0.0f;
	sl->u1 = sl->v1 = 0.0f;
	sl->us0 = u0; sl->vs0 = v0;
	sl->us1 = u1; sl->vs1 = v1;
	MODEL * mdl = (*this)[modelIndex];
	if(mdl) mdl->SetRenderTuner(sl); else api->Trace("Location: Can't get model pointer for set RenderTuner");
}

//Установить модельке анимацию вращения
void ModelArray::SetRotation(long modelIndex, float rx, float ry, float rz)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	if(!model[modelIndex].rotator) model[modelIndex].rotator = new Rotator;
	model[modelIndex].rotator->rx = rx;
	model[modelIndex].rotator->ry = ry;
	model[modelIndex].rotator->rz = rz;
}

//Установить модельке режим генерации матрицы для отражения
void ModelArray::SetReflection(long modelIndex, float scale)
{
	Assert(modelIndex >= 0 && modelIndex < numModels);
	if(!model[modelIndex].reflection) model[modelIndex].reflection = new Relection();
	if(scale < 0.0f) scale = 0.0f;
	if(scale > 1.0f) scale = 1.0f;
	uint32_t alpha = uint32_t(scale*255.0f);
	model[modelIndex].reflection->tfactor = (alpha << 24) | 0x00ffffff;
	MODEL * mdl = (*this)[modelIndex];
	if(mdl) mdl->SetRenderTuner(model[modelIndex].reflection); else api->Trace("Location: Can't get model pointer for set RenderTuner");
}

//Анимировать текстурные координаты
void ModelArray::Update(float dltTime)
{
	for(long i = 0; i < numModels; i++)
	{
		if(model[i].slider)
		{
			UVSlider * sl = model[i].slider;
			sl->u0 += dltTime*sl->us0;
			sl->v0 += dltTime*sl->vs0;
			sl->u1 += dltTime*sl->us1;
			sl->v1 += dltTime*sl->vs1;
			if(sl->u0 > 1.0f) sl->u0 -= 1.0f;
			if(sl->v0 > 1.0f) sl->v0 -= 1.0f;
			if(sl->u1 > 1.0f) sl->u1 -= 1.0f;
			if(sl->v1 > 1.0f) sl->v1 -= 1.0f;
			if(sl->u0 < -1.0f) sl->u0 += 1.0f;
			if(sl->v0 < -1.0f) sl->v0 += 1.0f;
			if(sl->u1 < -1.0f) sl->u1 += 1.0f;
			if(sl->v1 < -1.0f) sl->v1 += 1.0f;
		}
		if(model[i].rotator)
		{
			CMatrix mtr(model[i].rotator->rx*dltTime, model[i].rotator->ry*dltTime, model[i].rotator->rz*dltTime);
			MODEL * mdl = (MODEL *)api->GetEntityPointer(model[i].id);
			if(mdl) mdl->mtx = CMatrix(mtr, mdl->mtx);
		}
	}
}

void ModelArray::UpdateModelsPath()
{
	UpdatePath(modelspath);
	strcat_s(modelspath, "\\");
}

void ModelArray::UpdateTexturesPath()
{
	UpdatePath(texturespath);
	strcat_s(texturespath, "\\");
}

void ModelArray::UpdateLightPath()
{
	UpdatePath(lightpath);
}

void ModelArray::UpdateShadowPath()
{
	UpdatePath(shadowpath);
};

uint32_t ModelArray::CalcHashString(const char * str)
{
  unsigned long hval = 0;
  while(*str != '\0')
  {
	char c = *str++;
	if(c >= 'A' && c <= 'Z') c += 'a' - 'A';
    hval = (hval<<4) + (unsigned long int)c;
    unsigned long g = hval & ((unsigned long int) 0xf << (32 - 4));
    if(g != 0)
		{
			hval ^= g >> (32 - 8);
			hval ^= g;
		}
  }
  return hval;
}

void ModelArray::UVSlider::Set(MODEL * model, VDX9RENDER * rs)
{
	static CMatrix mtx;
	mtx.m[2][0] = u0;
	mtx.m[2][1] = v0;
	rs->SetTransform(D3DTS_TEXTURE0, mtx);
	mtx.m[2][0] = u1;
	mtx.m[2][1] = v1;
	rs->SetTransform(D3DTS_TEXTURE1, mtx);
	rs->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	rs->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
}

void ModelArray::UVSlider::Restore(MODEL * model, VDX9RENDER * rs)
{
	static CMatrix mtx;
	rs->SetTransform(D3DTS_TEXTURE0, mtx);
	rs->SetTransform(D3DTS_TEXTURE1, mtx);
  	rs->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	rs->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
}

void ModelArray::Relection::Set(MODEL * model, VDX9RENDER * rs)
{
	CMatrix mtx;
	rs->GetTransform(D3DTS_VIEW, mtx);
	mtx.Transposition();
	mtx.Pos() = 0.0f;
	rs->SetTransform(D3DTS_TEXTURE1, mtx);
	rs->SetRenderState(D3DRS_TEXTUREFACTOR, tfactor);
}

void ModelArray::Relection::Restore(MODEL * model, VDX9RENDER * rs)
{
	CMatrix mtx;
	rs->SetTransform(D3DTS_TEXTURE1, mtx);
}


void ModelArray::UpdatePath(char * path)
{
	long j = 0;
	for(long i = 0; path[i]; i++)
	{
		if(path[i] == '\\')
		{
			if(j > 0)
			{
				if(path[j - 1] != '\\')	path[i] = path[j++];
			}
		}else path[i] = path[j++];
	}
	if(--j >= 0 && path[j] == '\\') path[j] = 0;
}

//Проверить видимость 2-х точек
bool ModelArray::VisibleTest(const CVECTOR & p1, const CVECTOR & p2)
{
	for(long i = 0; i < numModels; i++)
	{
		if(model[i].isVisible)
		{
			MODEL * mdl = (MODEL *)api->GetEntityPointer(model[i].id);
			if(mdl->Trace(p1, p2) < 1.0f) return false;
		}
	}
	return true;
}

//Протрейсит луч через локацию
float ModelArray::Trace(const CVECTOR & src, const CVECTOR & dst)
{
	isHavecTrg = false;
	float k = 2.0f;
	for(long i = 0; i < numModels; i++)
	{
		if(model[i].isVisible)
		{
			MODEL * mdl = (MODEL *)api->GetEntityPointer(model[i].id);
			float km = mdl->Trace(src, dst);
			if(k > km)
			{
				k = km;
				isHavecTrg = mdl->GetCollideTriangle(ctrg);
			}
		}
	}
	return k;
}

bool ModelArray::GetCollideTriangle(TRIANGLE & trg)
{
	trg = ctrg;
	return isHavecTrg;
}

void ModelArray::Clip(PLANE * p, long numPlanes, CVECTOR & cnt, float rad, bool (* fnc)(const CVECTOR * vtx, long num))
{
	for(long i = 0; i < numModels; i++)
	{
		if(model[i].isVisible)
		{
			MODEL * mdl = (MODEL *)api->GetEntityPointer(model[i].id);
			mdl->Clip(p, numPlanes, cnt, rad, fnc);
		}
	}
}

