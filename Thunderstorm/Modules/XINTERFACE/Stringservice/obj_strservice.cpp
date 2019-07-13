#include "obj_strservice.h"
#include "../../../Shared/interface/messages.h"

OBJ_STRSERVICE::OBJ_STRSERVICE()
{
	m_pStrService = nullptr;
}

OBJ_STRSERVICE::~OBJ_STRSERVICE()
{
	m_pStrService = nullptr;
}

bool OBJ_STRSERVICE::Init()
{
	m_pStrService = (VSTRSERVICE *)api->CreateService("STRSERVICE");
	if (!m_pStrService)	
		throw std::exception("No service: strservice");

	return true;
}

uint32_t OBJ_STRSERVICE::ProcessMessage(MESSAGE & message)
{
	switch(message.Long())
	{
	case MSG_STRSERVICE_OPEN_FILE:
		{
			char param[256];
			message.String(sizeof(param)-1,param);
			if(m_pStrService!= nullptr) return m_pStrService->OpenUsersStringFile(param);
			return -1;
		}
		break;
	case MSG_STRSERVICE_CLOSE_FILE:
		{
			long fileID = message.Long();
			m_pStrService->CloseUsersStringFile(fileID);
		}
		break;
	case MSG_STRSERVICE_TRANSLATE_STRING:
		{
			long nUsrID = message.Long();
			VDATA * pvdat = message.ScriptVariablePointer();
			char * inStr = pvdat== nullptr ? nullptr : pvdat->GetString();
			pvdat = message.ScriptVariablePointer();
			char * outStr = nullptr;
			if(m_pStrService!= nullptr) outStr = m_pStrService->TranslateFromUsers(nUsrID,inStr);
			if(outStr!= nullptr && pvdat!= nullptr)	pvdat->Set(outStr);
			else
				pvdat->Set("");
		}
		break;
	case MSG_STRSERVICE_GET_LANGUAGE:
		{
			VDATA * pvdat = message.ScriptVariablePointer();
			char * outStr = nullptr;
			if(m_pStrService!= nullptr) outStr = m_pStrService->GetLanguage();
			if(outStr!= nullptr && pvdat!= nullptr)	pvdat->Set(outStr);
			else	pvdat->Set("");
		}
		break;
	}

	return 0;
}
