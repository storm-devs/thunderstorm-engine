#include "TEXT\DIALOGS\Prison\PortRoyal_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
            if (pchar.questTemp.State == "MorrisWillams_ArrestedToPrison")   // разговор по шестому квесту англ.линейки
            {
    			link.l2 = DLG_TEXT_PRS[2];
    			link.l2.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "SaveFromMorgan_toPrison")   // испанка, квест №1
            {
    			link.l2 = DLG_TEXT_PRS[3];
    			link.l2.go = "Step_S1_1";
            }
		break;

        case "Step_E6_1":
            dialog.text = DLG_TEXT_PRS[4]+
                          DLG_TEXT_PRS[5];
			link.l1 = DLG_TEXT_PRS[6];
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
            dialog.text = DLG_TEXT_PRS[7];
			link.l1 = DLG_TEXT_PRS[8];
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
            dialog.text = DLG_TEXT_PRS[9];
			link.l1 = DLG_TEXT_PRS[10];
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			pchar.questTemp.State = "MorrisWillams_ArrestedToModiford";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "16");
		break;

        case "Step_S1_1":
            dialog.text = DLG_TEXT_PRS[11];
			link.l1 = DLG_TEXT_PRS[12];
			link.l1.go = "Step_S1_2";
		break;
        case "Step_S1_2":
            dialog.text = DLG_TEXT_PRS[13];
			link.l1 = DLG_TEXT_PRS[14];
			link.l1.go = "Step_S1_3";
		break;
        case "Step_S1_3":
            dialog.text = DLG_TEXT_PRS[15];
			link.l1 = DLG_TEXT_PRS[16];
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

