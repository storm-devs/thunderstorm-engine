#include "TEXT\DIALOGS\Store\Villemstad_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco")// квест №2 голл. линейки.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Store"))
                {
                    dialog.text = DLG_TEXT_STR[9];
        			link.l1 = DLG_TEXT_STR[10] + GetFullName(pchar) + DLG_TEXT_STR[11];
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JacowDeFonseka"))
                    {
                        dialog.text = DLG_TEXT_STR[12];
            			link.l1 = DLG_TEXT_STR[13];
            			link.l1.go = "Step_S2_7";
                        AddMoneyToCharacter(pchar, 100000);
                        pchar.questTemp.State.Store = "Ok";
                        AddQuestRecord("Spa_Line_2_Inquisition", "14");
                        RemovePassenger(pchar, characterFromId("JacowDeFonseka"));
                    }
                    else
                    {
                        if (pchar.questTemp.State.Store != "Ok")
                        {
                            dialog.text = DLG_TEXT_STR[14];
                			link.l1 = DLG_TEXT_STR[15];
                			link.l1.go = "exit";
                		}
                		else
                		{
                            dialog.text = DLG_TEXT_STR[16];
                			link.l1 = DLG_TEXT_STR[17];
                			link.l1.go = "exit";
                		}
                    }
                }
            }
            // <== Проверяем поле состояния квестов.
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text = DLG_TEXT_STR[18];
    		link.l1 = DLG_TEXT_STR[19];
    		link.l1.go = "Step_S2_2";
 		break;
 		case "Step_S2_2":
    		dialog.text = DLG_TEXT_STR[20];
    		link.l1 = DLG_TEXT_STR[21];
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = DLG_TEXT_STR[22];
    		link.l1 = DLG_TEXT_STR[23];
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = DLG_TEXT_STR[24];
    		link.l1 = DLG_TEXT_STR[25];
    		link.l1.go = "Step_S2_5";
 		break;
 		case "Step_S2_5":
    		dialog.text = DLG_TEXT_STR[26]+
                          DLG_TEXT_STR[27];
    		link.l1 = DLG_TEXT_STR[28];
    		link.l1.go = "Step_S2_6";
 		break;
 		case "Step_S2_6":
    		dialog.text = DLG_TEXT_STR[29]+
                          DLG_TEXT_STR[30];
    		link.l1 = DLG_TEXT_STR[31];
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "3");
            pchar.questTemp.State.Store = 1;
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightForJacow.win_condition.l1.location = "Panama_houseSp1";
            Pchar.quest.Inquisition_fightForJacow.win_condition = "Inquisition_fightForJacow";
 		break;
 		case "Step_S2_7":
    		dialog.text = DLG_TEXT_STR[32];
    		link.l1 = DLG_TEXT_STR[33];
    		link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
        		link.l2 = DLG_TEXT_STR[34];
        		link.l2.go = "Step_S2_8";
            }
 		break;
 		case "Step_S2_8":
    		dialog.text = DLG_TEXT_STR[35];
    		link.l1 = DLG_TEXT_STR[36];
    		link.l1.go = "Step_S2_9";
    		link.l2 = DLG_TEXT_STR[37];
    		link.l2.go = "exit";
 		break;
 		case "Step_S2_9":
    		dialog.text = DLG_TEXT_STR[38];
    		link.l1 = DLG_TEXT_STR[39];
    		link.l1.go = "Step_S2_10";
 		break;
 		case "Step_S2_10":
    		dialog.text = DLG_TEXT_STR[40]+
                          DLG_TEXT_STR[41];
    		link.l1 = DLG_TEXT_STR[42];
    		link.l1.go = "Step_S2_11";
    		TakeItemFromCharacter(pchar, "Bible");
 		break;
 		case "Step_S2_11":
    		dialog.text = DLG_TEXT_STR[43];
    		link.l1 = DLG_TEXT_STR[44];
    		link.l1.go = "Step_S2_12";
    		AddMoneyToCharacter(pchar, 1000000);
 		break;
 		case "Step_S2_12":
    		dialog.text = DLG_TEXT_STR[45];
    		link.l1 = DLG_TEXT_STR[46];
    		link.l1.go = "exit";
 		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}

