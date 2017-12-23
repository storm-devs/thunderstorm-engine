#include "TEXT\DIALOGS\Tavern\Marigo_Tavern.h"
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
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "SeekChumakeiro_ToAaronHouse": //Голландская линейка, квест №1. поиски Чумакейро.
                    link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[10],
                    DLG_TEXT_TV[11], DLG_TEXT_TV[12], DLG_TEXT_TV[13], npchar, Dialog.CurrentNode);
                    link.l1.go = DialogGoNodeRepeat("Step_H1_1", "", "", "", npchar, Dialog.CurrentNode);
                break;

            }
            // <== Проверяем поле состояния квестов.
 		break;
        //============ Голландская линейка, квест №1. поиски Чумакейро.
 		case "Step_H1_1":
    		dialog.text = DLG_TEXT_TV[14];
    		link.l1 = DLG_TEXT_TV[15];
    		link.l1.go = "Step_H1_2";
 		break;
 		case "Step_H1_2":
    		dialog.text = DLG_TEXT_TV[16] + npchar.name + DLG_TEXT_TV[17];
    		link.l1 = DLG_TEXT_TV[18];
    		link.l1.go = "Step_H1_3";
 		break;
 		case "Step_H1_3":
    		dialog.text = DLG_TEXT_TV[19];
    		link.l1 = DLG_TEXT_TV[20];
    		link.l1.go = "Step_H1_4";
 		break;
 		case "Step_H1_4":
    		dialog.text = DLG_TEXT_TV[21];
    		link.l1 = DLG_TEXT_TV[22];
    		link.l1.go = "Step_H1_5";
 		break;
 		case "Step_H1_5":
    		dialog.text = DLG_TEXT_TV[23];
    		link.l1 = DLG_TEXT_TV[24];
    		link.l1.go = "exit";
 		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

