#include "vano_files.h"
#include "s_import_func.h"
#include "defines.h"
#include "vdata.h"
#include "v_s_stack.h"
#include "vmodule_api.h"

uint32_t _RDTSC_B(VS_STACK * pS)
{
	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;
	uint64_t dwRDTSC;
	RDTSC_B(dwRDTSC);
	pVR->Set((long)dwRDTSC);
	return IFUNCRESULT_OK;
}

uint32_t _RDTSC_E(VS_STACK * pS)
{
	VDATA * pValue = (VDATA*)pS->Pop();
	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;
	uint64_t dwRDTSC =	(uint32_t)pValue->GetLong();
	RDTSC_E(dwRDTSC);
	pVR->Set((long)dwRDTSC);
	return IFUNCRESULT_OK;
}

uint32_t _Clampf(VS_STACK * pS)
{
	VDATA * pValue = (VDATA*)pS->Pop();
	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;
	pVR->Set(Clamp(pValue->GetFloat()));

	return IFUNCRESULT_OK;
}

uint32_t _Degree2Radian(VS_STACK * pS)
{
	VDATA * pValue = (VDATA*)pS->Pop();
	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;

	pVR->Set(PIm2 * pValue->GetFloat() / 360.0f);

	return IFUNCRESULT_OK;
}

uint32_t _Bring2Range(VS_STACK * pS)
{
	VDATA * pValue = (VDATA*)pS->Pop();
	VDATA * pMax2 = (VDATA*)pS->Pop();
	VDATA * pMin2 = (VDATA*)pS->Pop();
	VDATA * pMax1 = (VDATA*)pS->Pop();
	VDATA * pMin1 = (VDATA*)pS->Pop();

	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;
	pVR->Set(Bring2Range(pMin1->GetFloat(), pMax1->GetFloat(), pMin2->GetFloat(), pMax2->GetFloat(), pValue->GetFloat()));

	return IFUNCRESULT_OK;
}

uint32_t _Bring2RangeNoCheck(VS_STACK * pS)
{
	VDATA * pValue = (VDATA*)pS->Pop();
	VDATA * pMax2 = (VDATA*)pS->Pop();
	VDATA * pMin2 = (VDATA*)pS->Pop();
	VDATA * pMax1 = (VDATA*)pS->Pop();
	VDATA * pMin1 = (VDATA*)pS->Pop();

	VDATA * pVR = (VDATA*)pS->Push(); if (!pVR) return IFUNCRESULT_FAILED;
	pVR->Set(Bring2RangeNoCheck(pMin1->GetFloat(), pMax1->GetFloat(), pMin2->GetFloat(), pMax2->GetFloat(), pValue->GetFloat()));

	return IFUNCRESULT_OK;
}

void Vano_Init()
{
	IFUNCINFO sIFuncInfo;

	sIFuncInfo.nArguments = 5;
	sIFuncInfo.pFuncName = "Bring2Range";
	sIFuncInfo.pReturnValueName = "float";
	sIFuncInfo.pFuncAddress = _Bring2Range;
	api->SetScriptFunction(&sIFuncInfo);

	sIFuncInfo.nArguments = 5;
	sIFuncInfo.pFuncName = "Bring2RangeNoCheck";
	sIFuncInfo.pReturnValueName = "float";
	sIFuncInfo.pFuncAddress = _Bring2RangeNoCheck;
	api->SetScriptFunction(&sIFuncInfo);

	sIFuncInfo.nArguments = 1;
	sIFuncInfo.pFuncName = "Degree2Radian";
	sIFuncInfo.pReturnValueName = "float";
	sIFuncInfo.pFuncAddress = _Degree2Radian;
	api->SetScriptFunction(&sIFuncInfo);

	sIFuncInfo.nArguments = 1;
	sIFuncInfo.pFuncName = "Clampf";
	sIFuncInfo.pReturnValueName = "float";
	sIFuncInfo.pFuncAddress = _Clampf;
	api->SetScriptFunction(&sIFuncInfo);

	sIFuncInfo.nArguments = 0;
	sIFuncInfo.pFuncName = "rdtsc_b";
	sIFuncInfo.pReturnValueName = "int";
	sIFuncInfo.pFuncAddress = _RDTSC_B;
	api->SetScriptFunction(&sIFuncInfo);

	sIFuncInfo.nArguments = 1;
	sIFuncInfo.pFuncName = "rdtsc_e";
	sIFuncInfo.pReturnValueName = "int";
	sIFuncInfo.pFuncAddress = _RDTSC_E;
	api->SetScriptFunction(&sIFuncInfo);

}