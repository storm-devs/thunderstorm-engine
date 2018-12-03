#ifndef _S_WATCHERLIST_H_
#define _S_WATCHERLIST_H_

#ifndef _XBOX

#include "tm_list.h"
#include "Core.h"


class WATCHER_LIST : public TM_LIST
{
	uint32_t ShowMask;
	HMENU hMenu;
	INIFILE * ini;
public:
	WATCHER_LIST(HWND hwnd, HINSTANCE hinst);
	~WATCHER_LIST();
	void ProcessMessage(uint32_t,uint32_t,uint32_t);
	void SetShowMask(uint32_t mask) {ShowMask = mask;};
	void ItemChanged(long Item_index, long Subitem_index);
	void Refresh();
};

#endif

#endif