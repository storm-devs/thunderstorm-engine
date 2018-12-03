#include "TEXT\DIALOGS\Tavern\PortRoyal_Tavern.h"
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
            // ==> Шестой квест английки, Моррис Уильямс
            if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo")
			{
                link.l1 = DLG_TEXT_TV[10];
                link.l1.go = "Step_E6_1";
			}
            // ==> Восьмой квест фр.линейки, отговорить трех корсаров
            if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")
			{
                link.l1 = DLG_TEXT_TV[11];
                link.l1.go = "Step_F8_1";
			}
		break;
        //********************** Английская линейка **********************
        case "Step_E6_1":
			dialog.text = DLG_TEXT_TV[12];
			link.l1 = DLG_TEXT_TV[13];
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = DLG_TEXT_TV[14];
			link.l1 = DLG_TEXT_TV[15];
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = DLG_TEXT_TV[16];
			link.l1 = DLG_TEXT_TV[17];
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoFather";
		break;
		//********************** Французская линейка **********************
        case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[18], 
				          DLG_TEXT_TV[19], DLG_TEXT_TV[20], DLG_TEXT_TV[21], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[22], DLG_TEXT_TV[23], DLG_TEXT_TV[24], DLG_TEXT_TV[25], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

