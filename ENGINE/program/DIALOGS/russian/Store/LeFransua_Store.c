#include "TEXT\DIALOGS\Store\LeFransua_Store.h"
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
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = DLG_TEXT_STR[10];
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[11], 
				DLG_TEXT_STR[12], 
				DLG_TEXT_STR[13],
                DLG_TEXT_STR[14], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[15], 
				DLG_TEXT_STR[16],
                DLG_TEXT_STR[17], 
				DLG_TEXT_STR[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_STR[19];
			link.l1 = DLG_TEXT_STR[20];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "3");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

