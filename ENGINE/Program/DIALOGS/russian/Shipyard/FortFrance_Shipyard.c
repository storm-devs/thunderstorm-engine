#include "TEXT\DIALOGS\Shipyard\FortFrance_Shipyard.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[0], DLG_TEXT_SHY[1]), DLG_TEXT_SHY[2], DLG_TEXT_SHY[3],
                          DLG_TEXT_SHY[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[5], DLG_TEXT_SHY[6]), DLG_TEXT_SHY[7],
                      DLG_TEXT_SHY[8], DLG_TEXT_SHY[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = DLG_TEXT_SHY[10];
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_SHY[11], 
				DLG_TEXT_SHY[12], 
				DLG_TEXT_SHY[13],
                DLG_TEXT_SHY[14], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_SHY[15], 
				DLG_TEXT_SHY[16],
                DLG_TEXT_SHY[17], 
				DLG_TEXT_SHY[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = DLG_TEXT_SHY[20];
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = DLG_TEXT_SHY[21];
			link.l1 = DLG_TEXT_SHY[22];
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = DLG_TEXT_SHY[23];
			link.l1 = DLG_TEXT_SHY[24];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "4");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

