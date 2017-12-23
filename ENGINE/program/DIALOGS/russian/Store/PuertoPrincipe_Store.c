#include "TEXT\DIALOGS\Store\PuertoPrincipe_Store.h"
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
			if (pchar.questTemp.BlueBird == "toPuertoPrincipe")
			{
				link.l1 = DLG_TEXT_STR[9];
				link.l1.go = "BlueBird_1";
			}
		break;
		case "BlueBird_1":
			if (isBadReputation(pchar, 5)) 
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[10], 
					DLG_TEXT_STR[11], 
					DLG_TEXT_STR[12],
					DLG_TEXT_STR[13], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[14], 
					DLG_TEXT_STR[15],
					DLG_TEXT_STR[16], 
					DLG_TEXT_STR[17], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("BlueBird_close", "", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = DLG_TEXT_STR[18];
				link.l1 = DLG_TEXT_STR[19];
				link.l1.go = "BlueBird_2";
			}
		break;

		case "BlueBird_close":
			dialog.text = DLG_TEXT_STR[20];
			link.l1 = DLG_TEXT_STR[21];
			link.l1.go = "exit";
		break;

		case "BlueBird_2":
			dialog.text = DLG_TEXT_STR[22];
			link.l1 = DLG_TEXT_STR[23];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_STR[24];
			link.l1 = DLG_TEXT_STR[25];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_STR[26];
			link.l1 = DLG_TEXT_STR[27];
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = DLG_TEXT_STR[28];
			link.l1 = DLG_TEXT_STR[29];
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = DLG_TEXT_STR[30];
			link.l1 = DLG_TEXT_STR[31];
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = DLG_TEXT_STR[32];
			link.l1 = DLG_TEXT_STR[33];
			link.l1.go = "BlueBird_8";
		break;
		case "BlueBird_8":
			dialog.text = DLG_TEXT_STR[34];
			link.l1 = DLG_TEXT_STR[35];
			link.l1.go = "BlueBird_9";
		break;
		case "BlueBird_9":
			dialog.text = DLG_TEXT_STR[36];
			link.l1 = DLG_TEXT_STR[37];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toSeekBermudes";
			AddQuestRecord("Xebeca_BlueBird", "4");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

