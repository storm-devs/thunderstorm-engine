#include "TEXT\DIALOGS\Tavern\Villemstad_Waitress.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0] + GetAddress_Form(NPChar) + "?", DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + DLG_TEXT_TV[3], DLG_TEXT_TV[4],
                          DLG_TEXT_TV[5] + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[6], DLG_TEXT_TV[7]), DLG_TEXT_TV[8],
                      DLG_TEXT_TV[9], DLG_TEXT_TV[10], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> проверяем поле состояния квестов
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))
            {
                dialog.text = DLG_TEXT_TV[11];
    			link.l1 = DLG_TEXT_TV[12];
    			link.l1.go = "Step_S2_1";
            }
            //<== проверяем поле состояния квестов
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[13], DLG_TEXT_TV[14], DLG_TEXT_TV[15], DLG_TEXT_TV[16], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[17], DLG_TEXT_TV[18], DLG_TEXT_TV[19], DLG_TEXT_TV[20], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_S2_2":
    		dialog.text = DLG_TEXT_TV[21];
    		link.l1 = DLG_TEXT_TV[22];
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = DLG_TEXT_TV[23];
    		link.l1 = DLG_TEXT_TV[24];
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = DLG_TEXT_TV[25];
    		link.l1 = DLG_TEXT_TV[26];
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "6");
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1 = "location";
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1.location = "Jamaica";
            Pchar.quest.Inquisition_AttackLugger.win_condition = "Inquisition_AttackLugger";
            SetTimerCondition("Inquisition_LuggerTimeOver", 0, 0, 20, false);
 		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

