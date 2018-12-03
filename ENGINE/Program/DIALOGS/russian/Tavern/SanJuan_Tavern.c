#include "TEXT\DIALOGS\Tavern\SanJuan_Tavern.h"
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
            // ==> Проверяем поле состояния квестов. Эдди.
			switch(pchar.questTemp.State)
            {
                case "MorrisWillams_PinnaceNotFound":
                    link.l2 = DLG_TEXT_TV[10];
                    link.l2.go = "Step_E6_1";
                break;
            }
		break;
        //---------------- квесты --------------------
        case "Step_E6_1":
			dialog.text = DLG_TEXT_TV[11];
			link.l1 = DLG_TEXT_TV[12];
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = DLG_TEXT_TV[13];
			link.l1 = DLG_TEXT_TV[14];
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = DLG_TEXT_TV[15];
			link.l1 = DLG_TEXT_TV[16];
			link.l1.go = "Step_E6_4";
		break;
        case "Step_E6_4":
			dialog.text = DLG_TEXT_TV[17];
			link.l1 = DLG_TEXT_TV[18];
			link.l1.go = "Step_E6_5";
		break;
        case "Step_E6_5":
			dialog.text = DLG_TEXT_TV[19];
			link.l1 = DLG_TEXT_TV[20];
			link.l1.go = "Step_E6_6";
		break;
        case "Step_E6_6":
			dialog.text = DLG_TEXT_TV[21];
			link.l1 = DLG_TEXT_TV[22];
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_2PinnaceNotFound";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

