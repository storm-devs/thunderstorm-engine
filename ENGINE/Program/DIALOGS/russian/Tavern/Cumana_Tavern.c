#include "TEXT\DIALOGS\Tavern\Cumana_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[0]+ GetCityName(npchar.city) +DLG_TEXT_TV[1],
                          DLG_TEXT_TV[2], DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[5] + NPChar.name + DLG_TEXT_TV[6], DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
    			link.l1 = DLG_TEXT_TV[10];
    			Link.l1.go = "RomanticQuest_1";
			}
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn"))
			{
    			link.l1 = DLG_TEXT_TV[11];
    			Link.l1.go = "RomanticQuest_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				link.l1 = DLG_TEXT_TV[12];
				link.l1.go = "PL_Q3_1";
			}
		break;

		case "RomanticQuest_1":
			dialog.text = DLG_TEXT_TV[13];
			link.l1 = DLG_TEXT_TV[14];
			link.l1.go = "exit";
		break;		
		case "RomanticQuest_2":
			dialog.text = DLG_TEXT_TV[15];
			link.l1 = DLG_TEXT_TV[16];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn");
		break;

		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[17], 
				DLG_TEXT_TV[18], 
				DLG_TEXT_TV[19],
                DLG_TEXT_TV[20], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[21], 
				DLG_TEXT_TV[22],
                DLG_TEXT_TV[23], 
				DLG_TEXT_TV[24], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

