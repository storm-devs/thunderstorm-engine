#include "TEXT\DIALOGS\Tavern\Havana_Waitress.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
    float locx, locy, locz, fTemp;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0] + GetAddress_Form(NPChar) + "?", DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + DLG_TEXT_TV[3], DLG_TEXT_TV[4],
                          DLG_TEXT_TV[5] + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[6], DLG_TEXT_TV[7]), DLG_TEXT_TV[8],
                      DLG_TEXT_TV[9], DLG_TEXT_TV[10], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "Sp4Detection_FoundLetter")
            {
    		    dialog.text = DLG_TEXT_TV[11];
    			link.l1 = DLG_TEXT_TV[12];
    			link.l1.go = "Step_S4_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_toHavana")
            {
    		    dialog.text = DLG_TEXT_TV[13];
    			link.l1 = DLG_TEXT_TV[14];
    			link.l1.go = "Step_F3_1";
			}
            if (pchar.questTemp.State == "Fr3TakeAnna_WaitOneDay")
            {
				if (GetQuestPastDayParam("questTemp") > 0)
				{
    				dialog.text = DLG_TEXT_TV[15];
    				link.l1 = DLG_TEXT_TV[16];
    				link.l1.go = "Step_F3_4";
				}
				else
				{
    				dialog.text = DLG_TEXT_TV[17];
    				link.l1 = DLG_TEXT_TV[18];
    				link.l1.go = "exit";
				}
			}
            // <== Проверяем поле состояния квестов.
		break;
//========================== Исп. линейка, квест №4. Расследование убийства ==================================
 	 	case "Step_S4_1":
			dialog.text = DLG_TEXT_TV[19];
			link.l1 = DLG_TEXT_TV[20];
			link.l1.go = "Step_S4_2";
        break;
 	 	case "Step_S4_2":
			dialog.text = DLG_TEXT_TV[21];
			link.l1 = DLG_TEXT_TV[22];
			link.l1.go = "Step_S4_3";
        break;
 	 	case "Step_S4_3":
			dialog.text = DLG_TEXT_TV[23];
			link.l1 = DLG_TEXT_TV[24];
			link.l1.go = "Step_S4_4";
        break;
 	 	case "Step_S4_4":
			dialog.text = DLG_TEXT_TV[25];
			link.l1 = DLG_TEXT_TV[26];
			link.l1.go = "Step_S4_5";
        break;
 	 	case "Step_S4_5":
			dialog.text = DLG_TEXT_TV[27];
			link.l1 = DLG_TEXT_TV[28];
			link.l1.go = "Step_S4_6";
        break;
 	 	case "Step_S4_6":
			dialog.text = DLG_TEXT_TV[29];
			link.l1 = DLG_TEXT_TV[30];
			link.l1.go = "Step_S4_7";
        break;
 	 	case "Step_S4_7":
			dialog.text = DLG_TEXT_TV[31];
			link.l1 = DLG_TEXT_TV[32];
			link.l1.go = "Step_S4_8";
        break;
 	 	case "Step_S4_8":
			dialog.text = DLG_TEXT_TV[33]+
                          DLG_TEXT_TV[34];
			link.l1 = DLG_TEXT_TV[35];
			link.l1.go = "Step_S4_9";
        break;
 	 	case "Step_S4_9":
			dialog.text = DLG_TEXT_TV[36];
			link.l1 = DLG_TEXT_TV[37];
			link.l1.go = "Step_S4_10";
        break;
 	 	case "Step_S4_10":
			dialog.text = DLG_TEXT_TV[38];
			link.l1 = DLG_TEXT_TV[39];
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toGovernor";
            AddQuestRecord("Spa_Line_4_MirderDetection", "3");
        break;
//========================== Фр. линейка, квест №3. Увезти донну Анну ==================================
 	 	case "Step_F3_1":
			dialog.text = DLG_TEXT_TV[40];
			link.l1 = DLG_TEXT_TV[41];
			link.l1.go = "Step_F3_2";
        break;
 	 	case "Step_F3_2":
			dialog.text = DLG_TEXT_TV[42];
			link.l1 = DLG_TEXT_TV[43];
			link.l1.go = "Step_F3_3";
			AddMoneyToCharacter(pchar, -500);
        break;
 	 	case "Step_F3_3":
			dialog.text = DLG_TEXT_TV[44];
			link.l1 = DLG_TEXT_TV[45];
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			pchar.questTemp.State = "Fr3TakeAnna_WaitOneDay";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_3_TakeAnna", "2");
        break;
 	 	case "Step_F3_4":
			dialog.text = DLG_TEXT_TV[46];
			link.l1 = DLG_TEXT_TV[47];
			link.l1.go = "Step_F3_5";
        break;
 	 	case "Step_F3_5":
			dialog.text = DLG_TEXT_TV[48]+
				          DLG_TEXT_TV[49];
			link.l1 = DLG_TEXT_TV[50];
			link.l1.go = "Step_F3_6";
        break;
 	 	case "Step_F3_6":
			dialog.text = DLG_TEXT_TV[51];
			link.l1 = DLG_TEXT_TV[52];
			link.l1.go = "Step_F3_7";
        break;
 	 	case "Step_F3_7":
			dialog.text = DLG_TEXT_TV[53];
			link.l1 = DLG_TEXT_TV[54];
			link.l1.go = "Step_F3_8";
        break;
 	 	case "Step_F3_8":
			dialog.text = DLG_TEXT_TV[55];
			link.l1 = DLG_TEXT_TV[56];
			link.l1.go = "Step_F3_9";
        break;
 	 	case "Step_F3_9":
			dialog.text = DLG_TEXT_TV[57];
			link.l1 = DLG_TEXT_TV[58];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -500);
			AddQuestRecord("Fra_Line_3_TakeAnna", "3");
            ChangeItemDescribe("letter_open", "itmdescr_letter_open_FraLineQ3");
            GiveItem2Character(pchar,"letter_open");
			pchar.questTemp.State = "Fr3TakeAnna_WaitMidnight";
        break;
//========================== Тревога в таверне Гаваны ==================================
		case "Allarm": 
    		dialog.text = DLG_TEXT_TV[59];
    		link.l1 = DLG_TEXT_TV[60];
    		link.l1.go = "Step_F_Allarm";
			NextDiag.TempNode = "First time";
        break;
		case "Step_F_Allarm":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaGuard"+i, "sold_spa_"+(rand(7)+1), "man", "man", 20, SPAIN, 0, true));
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 30);
				LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
                ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto",   LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //на всякий случай	
			LAi_SetWaitressType(npchar);
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

