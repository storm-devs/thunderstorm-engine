#include "TEXT\DIALOGS\Shipyard\SantoDomingo_Shipyard.h"
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
			if (pchar.questTemp.piratesLine == "Soukins_toSantoDomingo")
			{
				link.l1 = DLG_TEXT_SHY[10];
				link.l1.go = "PL_Q7_1";
			}
		break;
		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = DLG_TEXT_SHY[11];
			link.l1 = DLG_TEXT_SHY[12];
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = DLG_TEXT_SHY[13];
			link.l1 = DLG_TEXT_SHY[14];
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = DLG_TEXT_SHY[15];
			link.l1 = DLG_TEXT_SHY[16];
			link.l1.go = "PL_Q7_4";
		break;
		case "PL_Q7_4":
			dialog.text = DLG_TEXT_SHY[17];
			link.l1 = DLG_TEXT_SHY[18];
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = DLG_TEXT_SHY[20];
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_seekLeon";
			AddQuestRecord("Pir_Line_7_Soukins", "6");
			AddDialogExitQuestFunction("PQ7_LoginLeon");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

