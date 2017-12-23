#include "TEXT\DIALOGS\Tavern\Santiago_Tavern.h"
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
			switch(pchar.questTemp.State)
            {
                case "RevengeMansfield_toTavern": //Голландская линейка, квест №6. Узнать инфу о губере.
                    link.l2 = DLG_TEXT_TV[10];
                    link.l2.go = "Step_H6_1";
                break;
                case "Fr7RockBras_toSeekPlace": //Фр. линейка, квест №7. Узнать инфу о Роке Бразильце.
					link.l1 = DLG_TEXT_TV[11];
					link.l1.go = "Step_F7_1";
                break;
            }
            // <== Проверяем поле состояния квестов.
		break;
//**************************** Голл. линейка, квест №6. Узнать для Моргана инфу о губере Сантьяго ************************
 	 	case "Step_H6_1":
			dialog.text = DLG_TEXT_TV[12];
			link.l1 = DLG_TEXT_TV[13];
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = DLG_TEXT_TV[14];
			link.l1 = DLG_TEXT_TV[15];
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = DLG_TEXT_TV[16];
			link.l1 = DLG_TEXT_TV[17];
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = DLG_TEXT_TV[18];
			link.l1 = DLG_TEXT_TV[19];
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = DLG_TEXT_TV[20];
			link.l1 = DLG_TEXT_TV[21];
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = DLG_TEXT_TV[22];
			link.l1 = DLG_TEXT_TV[23];
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = DLG_TEXT_TV[24];
			link.l1 = DLG_TEXT_TV[25];
			link.l1.go = "Step_H6_8";
        break;
 	 	case "Step_H6_8":
			dialog.text = DLG_TEXT_TV[26]+
                          DLG_TEXT_TV[27];
			link.l1 = DLG_TEXT_TV[28];
			link.l1.go = "Step_H6_9";
        break;
 	 	case "Step_H6_9":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "3");
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromSantiago");
            //==> потом вернуть
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            //<== потом вернуть
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "SPAIN_CITIZENS");
            LAi_group_Delete("QuestGroup");
            SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //если флаг сменен.
            ref sld;
            for (int i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Solder"+i, "off_spa_"+i, "man", "man", 30, SPAIN, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 80, "blade33", "pistol3", 120);

            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
            LAi_group_SetLookRadius("EnemyFight", 100);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
        break;
//**************************** Фр. линейка, квест №7. Узнать инфу о Роке Бразильце ************************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[29], DLG_TEXT_TV[30], 
				          DLG_TEXT_TV[31], DLG_TEXT_TV[32], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[33], DLG_TEXT_TV[34], DLG_TEXT_TV[35], DLG_TEXT_TV[36], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = DLG_TEXT_TV[37];
			link.l1 = DLG_TEXT_TV[38];
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = DLG_TEXT_TV[39]+
				          DLG_TEXT_TV[40];
			link.l1 = DLG_TEXT_TV[41];
			link.l1.go = "exit";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

