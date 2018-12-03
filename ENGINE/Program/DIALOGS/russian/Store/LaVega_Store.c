#include "TEXT\DIALOGS\Store\LaVega_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[0], DLG_TEXT_STR[1]), DLG_TEXT_STR[2], DLG_TEXT_STR[3],
                          DLG_TEXT_STR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[5], DLG_TEXT_STR[6]), DLG_TEXT_STR[7],
                      DLG_TEXT_STR[8], DLG_TEXT_STR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

