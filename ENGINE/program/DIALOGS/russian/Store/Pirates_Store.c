#include "TEXT\DIALOGS\Store\Pirates_Store.h"
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
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_STR[9];
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = DLG_TEXT_STR[10];
				link.l1.go = "BlueBird_3";
			}
		break;
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[11], 
				DLG_TEXT_STR[12], 
				DLG_TEXT_STR[13],
                DLG_TEXT_STR[14], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[15], 
				DLG_TEXT_STR[16],
                DLG_TEXT_STR[17], 
				DLG_TEXT_STR[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = DLG_TEXT_STR[19];
			link.l1 = DLG_TEXT_STR[20];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
		break;

		case "BlueBird_3":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[21], 
				DLG_TEXT_STR[22], 
				DLG_TEXT_STR[23],
                DLG_TEXT_STR[24], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[25], 
				DLG_TEXT_STR[26],
                DLG_TEXT_STR[27], 
				DLG_TEXT_STR[28], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

