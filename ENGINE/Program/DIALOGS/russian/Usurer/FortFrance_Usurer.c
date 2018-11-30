#include "TEXT\DIALOGS\Usurer\FortFrance_Usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = DLG_TEXT_USR[10];
				link.l1.go = "PL_Q3_1";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_USR[11], 
				DLG_TEXT_USR[12], 
				DLG_TEXT_USR[13],
                DLG_TEXT_USR[14], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_USR[15], 
				DLG_TEXT_USR[16],
                DLG_TEXT_USR[17], 
				DLG_TEXT_USR[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_USR[19];
			link.l1 = DLG_TEXT_USR[20];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "5");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

