#include <stdio.h>

#ifndef _XBOX
	#include <Windows.h>
#else
	#include <xtl.h>
#endif

#include "../Shared/messages.h"
#include "../Common_h/defines.h"
#include "../Common_h/Cvector.h"
#include "../SoundService/VSoundService.h"

#include "SOUND.H"

#define MSG_SOUND_ALIAS_ADD					77017   //"s"		  alias_name

INTERFACE_FUNCTION
CREATE_CLASS(SOUND)
//--------------------------------------------------------------------
SOUND::SOUND()
	:soundService(nullptr)
{
}

//--------------------------------------------------------------------
SOUND::~SOUND()
{
}

//--------------------------------------------------------------------
bool SOUND::Init()
{
	//GUARD(SOUND::Init)

	soundService = (VSoundService *)api->CreateService("SoundService");
	if (!soundService)
		api->Trace("!SOUND: Can`t create sound service");

	renderer = (VDX9RENDER *) api->CreateService("dx9render");
	api->LayerAdd("realize",GetId(),-1);

	return true;
	//UNGUARD
}

//--------------------------------------------------------------------
uint32_t _cdecl SOUND::ProcessMessage(MESSAGE & message)
{
	////GUARD(SOUND::ProcessMessage)

	if (!soundService)
		return 0;

	long code = message.Long();
	CVECTOR vector, vector2;
	char tempString[SOUND_STRING_SIZE];
	long temp, temp2, temp3, temp4, vt;
	long id, tempLong;
	float minD, maxD;
	long loopPauseTime;
	float v1, v2, v3;
	float volume;
	VDATA *vd1, *vd2, *vd3;
	uint32_t outValue = 0;

	switch (code)
	{
	case MSG_SOUND_SET_MASTER_VOLUME:
		v1 = message.Float();
		v2 = message.Float();
		v3 = message.Float();
		soundService->SetMasterVolume(v1, v2, v3);
		break;
	case MSG_SOUND_GET_MASTER_VOLUME:
		soundService->GetMasterVolume(&v1, &v2, &v3);
		vd1 = message.ScriptVariablePointer();
		vd2 = message.ScriptVariablePointer();
		vd3 = message.ScriptVariablePointer();
		vd1->Set(v1);
		vd2->Set(v2);
		vd3->Set(v3);
		break;
	case MSG_SOUND_SET_CAMERA_POSITION:
		vector.x = message.Float();
		vector.y = message.Float();
		vector.z = message.Float();
		soundService->SetCameraPosition(vector);
		break;
	case MSG_SOUND_SET_CAMERA_ORIENTATION:
		vector.x = message.Float();
		vector.y = message.Float();
		vector.z = message.Float();
		vector2.x = message.Float();
		vector2.y = message.Float();
		vector2.z = message.Float();
		soundService->SetCameraOrientation(vector, vector2);
		break;
	case MSG_SOUND_PLAY:
		message.String(sizeof(tempString), tempString); //filename

		temp     = message.Long(); //type
		//defaults
		vt       = (int) VOLUME_FX; //volume type
		temp2    = 0;
		temp3    = 0;
		temp4    = 0;
		tempLong = 0;
		vector.x = 0;
		vector.y = 0;
		vector.z = 0;
		minD     = -1.0f;
		maxD     = -1.0f;
		loopPauseTime = 0;
		volume   = 1.f;
		//try to read as many parameters   as we can
		if (message.GetCurrentFormatType())	vt       = message.Long(); //volume_type
		if (message.GetCurrentFormatType())	temp2    = message.Long(); //simple_cache
		if (message.GetCurrentFormatType())	temp3    = message.Long(); //looped
		if (message.GetCurrentFormatType())	temp4    = message.Long(); //cached
		if (message.GetCurrentFormatType())	tempLong = message.Long(); //fade_in_time
		// boal fix 28.10.06
		if (temp == SOUND_MP3_STEREO)
		{
			if (temp3) // stereo OGG, looped
			{
				if (message.GetCurrentFormatType())	loopPauseTime = message.Long();
				if (message.GetCurrentFormatType())	volume		  = message.Float();
			}
		}
		else
		{
			if (message.GetCurrentFormatType())	vector.x = message.Float();
			if (message.GetCurrentFormatType())	vector.y = message.Float();
			if (message.GetCurrentFormatType())	vector.z = message.Float();
			if (message.GetCurrentFormatType())	minD	 = message.Float();
			if (message.GetCurrentFormatType())	maxD	 = message.Float();
		}

		outValue = (uint32_t) soundService->SoundPlay(tempString, (eSoundType) temp, (eVolumeType) vt, (temp2 != 0), (temp3 != 0), (temp4 != 0), tempLong, &vector, minD, maxD, loopPauseTime, volume);
		
		break;
	case MSG_SOUND_STOP:
		id = message.Long();
		tempLong = message.Long();
		soundService->SoundStop(id, tempLong);
		break;
	case MSG_SOUND_RELEASE:
		id = message.Long();
		soundService->SoundRelease(id);
		break;
	case MSG_SOUND_DUPLICATE:
		id = message.Long();
		outValue = (uint32_t) soundService->SoundDuplicate(id);
		break;
	case MSG_SOUND_SET_3D_PARAM:
		id = message.Long();
		tempLong = message.Long();
		switch (tempLong)
		{
		case SOUND_PARAM_MAX_DISTANCE:
			vector.x = message.Float();
			//memcpy(&(vector.x) ,message.Pointer(), sizeof(float));
			soundService->SoundSet3DParam(id, SM_MAX_DISTANCE, &(vector.x));
			break;
		case SOUND_PARAM_MIN_DISTANCE:
			vector.x = message.Float();
			//memcpy(&(vector.x) ,message.Pointer(), sizeof(float));
			soundService->SoundSet3DParam(id, SM_MIN_DISTANCE, &(vector.x));
			break;
		case SOUND_PARAM_POSITION:
			vector.x = message.Float();
			vector.y = message.Float();
			vector.z = message.Float();
			//memcpy(&(vector.x) ,message.Pointer(), sizeof(float));
			//memcpy(&(vector.y) ,message.Pointer()+sizeof(float), sizeof(float));
			//memcpy(&(vector.z) ,message.Pointer()+(sizeof(float) << 1), sizeof(float));
			soundService->SoundSet3DParam(id, SM_POSITION, &vector);
			break;
		}
		break;
	case MSG_SOUND_SET_VOLUME:
		id = message.Long();
		vector.x = message.Float();
		soundService->SoundSetVolume(id, vector.x);
		break;
	case MSG_SOUND_IS_PLAYING:
		id = message.Long();
		outValue = soundService->SoundIsPlaying(id);
		break;
	case MSG_SOUND_GET_POSITION:
		id = message.Long();
		outValue = (uint32_t) (soundService->SoundGetPosition(id) * 100.0f);
		break;
	case MSG_SOUND_RESTART:
		id = message.Long();
		soundService->SoundRestart(id);
		break;
	case MSG_SOUND_RESUME:
		id = message.Long();
		temp = message.Long();
		soundService->SoundResume(id, temp);
		break;
	case MSG_SOUND_SCHEME_RESET:
		soundService->ResetScheme();
		break;
	case MSG_SOUND_SCHEME_SET:
		message.String(sizeof(tempString), tempString); //scheme_name
		soundService->SetScheme(tempString);
		break;
	case MSG_SOUND_SCHEME_ADD:
		message.String(sizeof(tempString), tempString); //scheme_name
		soundService->AddScheme(tempString);
		break;

	case MSG_SOUND_SET_ENABLED:
		soundService->SetEnabled(message.Long() != 0);
		break;

	case MSG_SOUND_ALIAS_ADD:
		message.String(sizeof(tempString), tempString); //alias_name
		soundService->LoadAliasFile(tempString);
		break;
	}

	return outValue;
	////UNGUARD
}

//--------------------------------------------------------------------
void SOUND::Realize(uint32_t _dTime)
{
	if (!soundService)
		return;
/*
	bool drawInfo;
#ifndef _XBOX
	drawInfo = (GetKeyState(VK_SUBTRACT) & 0x8000) != 0;
#else
	drawInfo = true;
#endif
	if (drawInfo)
	{
		renderer->Print(0, 90, "cnt[%d,%d] buf[%d,%d] cach[%d,%d]"
					   ,soundService->soundStatistics.soundsCount
					   ,soundService->soundStatistics.maxSoundsCount
					   ,soundService->soundStatistics.bytesInBuffers / 1024
		 			   ,soundService->soundStatistics.maxBytesInBuffers / 1024
					   ,soundService->soundStatistics.bytesCached / 1024
					   ,soundService->soundStatistics.maxBytesCached / 1024
					   );
	}
*/
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------