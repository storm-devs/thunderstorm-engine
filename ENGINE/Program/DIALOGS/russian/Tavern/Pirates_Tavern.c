#include "TEXT\DIALOGS\Tavern\Pirates_Tavern.h"
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
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "SeekBible_toBermudes") 
			{				
                link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[10],
                DLG_TEXT_TV[11], DLG_TEXT_TV[12], DLG_TEXT_TV[13], npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_H8_1", "", "", "", npchar, Dialog.CurrentNode);
            }
            if (pchar.RomanticQuest == "BrotherIsDead") 
			{				
                link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[14],
                DLG_TEXT_TV[15], DLG_TEXT_TV[16], DLG_TEXT_TV[17], npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_Romantic_1", "", "", "", npchar, Dialog.CurrentNode);
            }
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_TV[18];
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toBermudes")
			{
				link.l1 = DLG_TEXT_TV[19];
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain" || pchar.questTemp.piratesLine == "KillLoy_2toTavernAgain")
			{
				link.l1 = DLG_TEXT_TV[20];
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toBermudes")
			{
				link.l1 = DLG_TEXT_TV[21];
				link.l1.go = "StepPL5Berm_1";
			}
            // <== Проверяем поле состояния квестов.
		break;
		//шебека Синяя Птица
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[22], 
				DLG_TEXT_TV[23], 
				DLG_TEXT_TV[24],
                DLG_TEXT_TV[25], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[26], 
				DLG_TEXT_TV[27],
                DLG_TEXT_TV[28], 
				DLG_TEXT_TV[29], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "BlueBird_2":
			dialog.text = DLG_TEXT_TV[30];
			link.l1 = DLG_TEXT_TV[31];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_TV[32];
			link.l1 = DLG_TEXT_TV[33];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_TV[34];
			link.l1 = DLG_TEXT_TV[35];
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = DLG_TEXT_TV[36];
			link.l1 = DLG_TEXT_TV[37];
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = DLG_TEXT_TV[38];
			link.l1 = DLG_TEXT_TV[39];
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = DLG_TEXT_TV[40] + GetAddress_Form(NPChar) + DLG_TEXT_TV[41];
			link.l1 = DLG_TEXT_TV[42];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "3");
			pchar.questTemp.BlueBird = "toPuertoPrincipe";
		break;

		//голл. линейка, квест №8
 		case "Step_H8_1":
    		dialog.text = DLG_TEXT_TV[43];
    		link.l1 = DLG_TEXT_TV[44];
    		link.l1.go = "Step_H8_2";
 		break;
 		case "Step_H8_2":
    		dialog.text = DLG_TEXT_TV[45];
    		link.l1 = DLG_TEXT_TV[46];
    		link.l1.go = "exit";
 		break;
		//Изабелла, ищем Атиллу
 		case "Step_Romantic_1":
    		dialog.text = DLG_TEXT_TV[47];
    		link.l1 = DLG_TEXT_TV[48];
    		link.l1.go = "exit";
 		break;
		//Пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = DLG_TEXT_TV[49];
			link.l1 = DLG_TEXT_TV[50];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "9");
			pchar.questTemp.piratesLine = "KillLoy_toAlexus";			
		break;

		case "PL_Q3_2":
			dialog.text = DLG_TEXT_TV[51];
			link.l1 = DLG_TEXT_TV[52];
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = DLG_TEXT_TV[53];
			link.l1 = DLG_TEXT_TV[54];
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "KillLoy_toGoogly";
		break;
		//Пиратка, квест №5, ОЗГ
		case "StepPL5Berm_1":
			dialog.text = DLG_TEXT_TV[55];
			link.l1 = DLG_TEXT_TV[56];
			link.l1.go = "StepPL5Berm_2";
		break;
		case "StepPL5Berm_2":
			dialog.text = DLG_TEXT_TV[57];
			link.l1 = DLG_TEXT_TV[58];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "10");
			pchar.questTemp.piratesLine = "PL5Hunter_toOrryHouse";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

