#ifndef _ModelWraper_H_
#define _ModelWraper_H_

#include "../Common_h/vmodule_api.h"
#include "../Common_h/geometry.h"
#include "../Common_h/dx9render.h"

class Lights;

class LocModelRealizer : public Entity
{
	entid_t eid_model;
	Lights* lights;
	VDX9RENDER* rs;
	VGEOMETRY* gs;
	bool bShow;

//--------------------------------------------------------------------------------------------
//Конструирование, деструктурирование
//--------------------------------------------------------------------------------------------
public:
	LocModelRealizer();
	~LocModelRealizer();

	//Инициализация
	bool Init();
	//Исполнение
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::EXECUTE:
			Execute(delta); break;
		case Stage::REALIZE:
			Realize(delta); break;
			/*case Stage::LOST_RENDER:
				LostRender(delta); break;
			case Stage::RESTORE_RENDER:
				RestoreRender(delta); break;*/
		}
	}

	//Сообщения
	uint32_t ProcessMessage(MESSAGE & message);
};

#endif
