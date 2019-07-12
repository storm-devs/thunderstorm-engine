#ifndef InterfaceManager_h
#define InterfaceManager_h

#include "BaseManager.h"
#include "../../Common_h/defines.h"
#include <vector>

class BI_BaseGroup;

class BI_InterfaceManager : public BI_ManagerBase
{
public:
	BI_InterfaceManager();
	~BI_InterfaceManager();

	bool Init();
	void Execute(uint32_t delta_time);
	void Realize(uint32_t delta_time);
    uint32_t ProcessMessage(MESSAGE & message);
	void ProcessStage(Stage stage, uint32_t delta) override
	{
		switch (stage)
		{
		case Stage::execute:
			Execute(delta); break;
		case Stage::realize:
			Realize(delta); break;
			/*case Stage::lost_render:
				LostRender(delta); break;
			case Stage::restore_render:
				RestoreRender(delta); break;*/
		}
	}

	virtual BI_ManagerNodeBase* CreateImageNode(const char* texture, const FRECT& uv, const RECT& pos, uint32_t color, long nPrioritet);
	virtual BI_ManagerNodeBase* CreateStringNode(const char* text, const char* font, uint32_t color, float scale, const RECT& pos, long nHAlign, long nVAlign, long prioritet);
	virtual void DeleteNode(BI_ManagerNodeBase* pNod);

protected:
	long MsgLoadSheet(MESSAGE & message);
	long MsgCreateImage(MESSAGE & message);
	long MsgCreateString(MESSAGE & message);
	long MsgDeleteNode(MESSAGE & message);
	long MsgEvent(MESSAGE & message);

	std::vector<BI_ManagerNodeBase*> m_aNodes;

	BI_BaseGroup* m_pInterfaceSheet;
};

#endif
