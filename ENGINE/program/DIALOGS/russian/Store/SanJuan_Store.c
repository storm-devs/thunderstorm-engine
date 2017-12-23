#include "TEXT\DIALOGS\Store\SanJuan_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Romantic_1":
            dialog.Text = DLG_TEXT_STR[9];
			Link.l1 = DLG_TEXT_STR[10];
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;
		
		case "Romantic_2":
            dialog.Text = DLG_TEXT_STR[11];
			Link.l1 = DLG_TEXT_STR[12];
		    Link.l1.go = "exit";
		    NextDiag.TempNode = "Second time";
		    AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}

