#include "TEXT\DIALOGS\Quest\OliverGreen.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    sld = characterFromID("Henry Morgan");
    
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sld.location == pchar.location && bWorldAlivePause)
            {
    			dialog.text = DLG_TEXT_Q[0];
    			link.l1 = DLG_TEXT_Q[1];
            }
            else
            {
    			if (pchar.questTemp.piratesLine == "Panama_inEngland" || pchar.questTemp.piratesLine == "Panama_backToShip")
				{
					dialog.text = DLG_TEXT_Q[2];
    				link.l1 = DLG_TEXT_Q[3];
				}
				else
				{
					dialog.text = DLG_TEXT_Q[4];
    				link.l1 = DLG_TEXT_Q[5];
				}
            }
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_Q[6] + GetFullName(npchar) + DLG_TEXT_Q[7];
				link.l1 = DLG_TEXT_Q[8] + GetFullName(pchar) + ".";
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
            //============>>>>>>>>> перехват квестовых диалогов
            if (pchar.questTemp.State == "WormEnglPlans_toMorgan")  // HolLine_3, переадресовка в Антигуа.
            {
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "Step_H3_1";
            }
            if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")  // FraLine_8, переадресовка в Антигуа.
            {
    			link.l1 = DLG_TEXT_Q[10];
    			link.l1.go = "Step_F8_1";
            }
            // квест Аскольда. Пасхалка на получение индейских предметов.
            if (pchar.questTemp.Ascold == "SeekThreeObject" && !CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = DLG_TEXT_Q[11];
    			link.l2.go = "Step_As_1";
            }
            if (pchar.questTemp.Ascold == "SeekThreeObject" && CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = DLG_TEXT_Q[12];
    			link.l2.go = "Step_As_7";
            }
            if (pchar.questTemp.Azzy == "DestrContract" || pchar.questTemp.Azzy == "2DestrContract")
            {
                if (!CheckAttribute(pchar, "questTemp.Azzy.Oliver"))
                {
        			link.l2 = DLG_TEXT_Q[13];
        			link.l2.go = "Step_As_9";
        		}
            }
            //============>>>>>>>>> перехват квестовых диалогов
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
		//********************* Голландская линейка *********************
        case "Step_H3_1":
            dialog.text = DLG_TEXT_Q[14];
            link.l1 = DLG_TEXT_Q[15] + GetFullName(pchar) + DLG_TEXT_Q[16];
            link.l1.go = "Step_H3_2";
        break;
        case "Step_H3_2":
            dialog.text = DLG_TEXT_Q[17];
            link.l1 = DLG_TEXT_Q[18];
            link.l1.go = "Step_H3_3";
        break;
        case "Step_H3_3":
            dialog.text = DLG_TEXT_Q[19]+
                          DLG_TEXT_Q[20]+
                          DLG_TEXT_Q[21];
            link.l1 = DLG_TEXT_Q[22];
            link.l1.go = "exit";
            pchar.questTemp.State = "WormEnglPlans_toMorganAntigua";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "3");
        break;
		//********************* Французская линейка *********************
 	 	case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[23], DLG_TEXT_Q[24], 
				          DLG_TEXT_Q[25], DLG_TEXT_Q[26], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[27] + GetFullName(pchar) + DLG_TEXT_Q[28], DLG_TEXT_Q[29], DLG_TEXT_Q[30], DLG_TEXT_Q[31], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F8_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;  
        case "Step_F8_2":
            dialog.text = DLG_TEXT_Q[32];
            link.l1 = DLG_TEXT_Q[33];
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = DLG_TEXT_Q[34];
            link.l1 = DLG_TEXT_Q[35];
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = DLG_TEXT_Q[36];
            link.l1 = DLG_TEXT_Q[37];
            link.l1.go = "exit";
        break;
		//********************* Квест Асокльда *********************
   		case "Step_As_1":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "Step_As_2";
		break;
   		case "Step_As_2":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "Step_As_3";
		break;
   		case "Step_As_3":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "Step_As_4";
		break;
   		case "Step_As_4":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "Step_As_5";
		break;
   		case "Step_As_5":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "Step_As_6";
		break;
   		case "Step_As_6":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "Step_As_7";
			pchar.questTemp.Ascold.Oliver = 1;
		break;
   		case "Step_As_7":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[51], DLG_TEXT_Q[52]);
			link.l1.go = "exit";
            if (sti(pchar.money) >= 1000000)
            {
    			link.l2 = DLG_TEXT_Q[53];
    			link.l2.go = "Step_As_8";
            }
            else
            {
    			link.l2 = DLG_TEXT_Q[54];
    			link.l2.go = "exit";
            }
		break;
   		case "Step_As_8":
			dialog.text = GetFullName(pchar) + DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			DeleteAttribute(pchar, "questTemp.Ascold.Oliver");
			pchar.questTemp.Ascold = "SoughtThreeObject";
    		GiveItem2Character(pchar, "indian19");
    		GiveItem2Character(pchar, "indian20");
    		GiveItem2Character(pchar, "indian21");
		break;
   		case "Step_As_9":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[58], DLG_TEXT_Q[59]);
			link.l1.go = "exit";
            if (sti(pchar.money) >= 5000000)
            {
    			link.l2 = DLG_TEXT_Q[60];
    			link.l2.go = "Step_As_10";
            }
            else
            {
    			link.l2 = DLG_TEXT_Q[61];
    			link.l2.go = "exit";
            }
		break;		
   		case "Step_As_10":
			dialog.text = GetFullName(pchar) + DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000000);
    		GiveItem2Character(pchar, "sculMa1");
    		GiveItem2Character(pchar, "sculMa2");
    		GiveItem2Character(pchar, "sculMa3");
    		GiveItem2Character(pchar, "indian22");
    		pchar.questTemp.Azzy.Oliver = 1;
		break;

		case "PL_Q8_over":
			dialog.text = DLG_TEXT_Q[64] + GetFullName(pchar) + ".";
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "PL_Q8_over_1";
		break;
		case "PL_Q8_over_1":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "PL_Q8_over_2";
		break;
		case "PL_Q8_over_2":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
	}
}


