#ifndef _BI_ITEM_ENTITY_H_
#define _BI_ITEM_ENTITY_H_

#include "../../Common_h/dx9render.h"
#include "../../Common_h/defines.h"
#include "../../Common_h/Animation.h"
#include "../../Common_h/vparticle_system.h"
#include <string>

class MODEL;
class NODE;

class ItemEntity : public ENTITY
{
public:
	ItemEntity();
	~ItemEntity();

	bool Init();
	void Realize(uint32_t delta_time);
	uint32_t ProcessMessage(MESSAGE & message);

protected:
	bool ReadAndCreate();
	void SetBeginData();
	void Release();

	void SetModelToPosition(const CMatrix& mtx);
	void SetTechnique( const char* pcTechnique );
	bool TieToLocator(ENTITY_ID& mdlEID, const char* pcLocName);
	void UnTieFromLocator();
	void EndEventProcess();

	void DrawIntoLocator();

	void SetEventListener(ENTITY_ID& mdlEID, ENTITY_ID& mdlToTieEID,const char* pcLocName, const char* pcStartEvent,const char* pcEndEvent);
	ENTITY_ID GetModelEIDFromCharacterEID(ENTITY_ID& chrEID);

protected: // data
	bool m_bVisible;
	ENTITY_ID m_eidModel;
	MODEL* m_pModel;
	CMatrix m_mtxpos;

	bool m_bTieToLocator;
	ENTITY_ID m_eidTieModel;
	NODE* m_pMdlNode;
	std::string m_sTieLocName;

	class EventListener : public AnimationEventListener
	{
	public:
		//Принять событие
		virtual void Event(Animation * animation, long playerIndex, const char * eventName);

		ItemEntity* item;
		std::string m_sStartEvent;
		std::string m_sEndEvent;
		bool m_bStartWaiting;
		ENTITY_ID m_eidListenedModel;
		ENTITY_ID m_eidToTieModel;
		std::string m_sToTieLocator;
	};
	friend EventListener;
	EventListener m_eventListener;

	VPARTICLE_SYSTEM* m_pParticle;
	bool CreateParticle();
	void DeleteParticle();
};

#endif
