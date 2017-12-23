#include "TEXT\DIALOGS\Tavern\LeFransua_Tavern.h"
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
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = DLG_TEXT_TV[10];
				link.l1.go = "PL_Q2_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = DLG_TEXT_TV[11];
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №2, черная метка для Лоу
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[12], 
				DLG_TEXT_TV[13], 
				DLG_TEXT_TV[14],
                DLG_TEXT_TV[15], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[16], 
				DLG_TEXT_TV[17],
                DLG_TEXT_TV[18], 
				"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q2_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q2_2":
			dialog.text = DLG_TEXT_TV[19];
			link.l1 = DLG_TEXT_TV[20];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_2_BlackLabel", "2");
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[21], 
				DLG_TEXT_TV[22], 
				DLG_TEXT_TV[23],
                DLG_TEXT_TV[24], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[25], 
				DLG_TEXT_TV[26],
                DLG_TEXT_TV[27], 
				DLG_TEXT_TV[28], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_TV[29];
			link.l1 = DLG_TEXT_TV[30];
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = DLG_TEXT_TV[31];
			link.l1 = DLG_TEXT_TV[32];
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

