#include "TEXT\DIALOGS\Tavern\Charles_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0], DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[5], DLG_TEXT_TV[6]), DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = DLG_TEXT_TV[10];
				link.l1.go = "MCLiz";
			}
		break;
		case "MCLiz":
			dialog.text = DLG_TEXT_TV[11];
			link.l1 = DLG_TEXT_TV[12];
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = DLG_TEXT_TV[13];
			link.l1 = DLG_TEXT_TV[14];
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = DLG_TEXT_TV[15];
			link.l1 = DLG_TEXT_TV[16];
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = DLG_TEXT_TV[17];
			link.l1 = DLG_TEXT_TV[18];
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = DLG_TEXT_TV[19]+
				DLG_TEXT_TV[20];
			link.l1 = DLG_TEXT_TV[21];
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = DLG_TEXT_TV[22];
			link.l1 = DLG_TEXT_TV[23];
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = DLG_TEXT_TV[24];
			link.l1 = DLG_TEXT_TV[25];
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = DLG_TEXT_TV[26];
			link.l1 = DLG_TEXT_TV[27];
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = DLG_TEXT_TV[28];
			link.l1 = DLG_TEXT_TV[29];
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

