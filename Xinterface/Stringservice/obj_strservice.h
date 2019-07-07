#ifndef _OBJ_STRSERVICE_H_
#define _OBJ_STRSERVICE_H_

#include "../../Common_h/stringService.h"

class OBJ_STRSERVICE : public Entity
{
	VSTRSERVICE * m_pStrService;
public:
	OBJ_STRSERVICE();
	~OBJ_STRSERVICE();
	bool	Init();
    uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage, uint32_t) override
	{
	}
};

#endif
