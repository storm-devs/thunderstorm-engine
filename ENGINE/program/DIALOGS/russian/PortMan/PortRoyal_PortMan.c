#include "TEXT\DIALOGS\PortMan\PortRoyal_PortMan.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №6 англ.линейки, базар о пинасе
            if (pchar.questTemp.State == "MorrisWillams_SeekSpanishGoods")
            {
    			link.l1 = DLG_TEXT_PRT[10];
    			link.l1.go = "Step_E6_1";
            }
		break;
//************************************* Диалоги по англ.линейке *******************************
		case "Step_E6_1":
            dialog.text = DLG_TEXT_PRT[11];
			link.l1 = DLG_TEXT_PRT[12];
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
            dialog.text = DLG_TEXT_PRT[13];
			link.l1 = DLG_TEXT_PRT[14];
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
            dialog.text = DLG_TEXT_PRT[15];
			link.l1 = DLG_TEXT_PRT[16];
			link.l1.go = "Step_E6_4";
		break;

		case "Step_E6_4":
            dialog.text = DLG_TEXT_PRT[17];
			link.l1 = DLG_TEXT_PRT[18];
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "9");
			pchar.questTemp.State = "MorrisWillams_CatchUpPinnace";
            SaveCurrentQuestDateParam("questTemp");
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1 = "location";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1.location = "Jamaica";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition = "MorrisWillams_CheckTimeForForward";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

