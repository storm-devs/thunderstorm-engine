#include "TEXT\DIALOGS\Quest\SpaLineNpc_1.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            //Квест №1, спасение трех горожан.
            if (npchar.id == "SpaPrisoner1" || npchar.id == "SpaPrisoner2" || npchar.id == "SpaPrisoner3")
            {
    			if (pchar.questTemp.State == "SaveFromMorgan_toPrison")
    			{
                    dialog.text = DLG_TEXT_Q[2];
        			link.l1 = DLG_TEXT_Q[3];
        			link.l1.go = "Step_S1_1";
                }
                else
                {
                    dialog.text = LinkRandPhrase(DLG_TEXT_Q[4], DLG_TEXT_Q[5], DLG_TEXT_Q[6]);
        			link.l1 = DLG_TEXT_Q[7];
        			link.l1.go = "exit";
                }
            }
            if (pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")// квест №3, Рок Бриазилец в каюте на абордаже
            {
    			dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "Step_S3_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toTortuga")// квест №4, базар со слугой д'Эстре предварительный.
            {
    			dialog.text = DLG_TEXT_Q[10];
    			link.l1 = DLG_TEXT_Q[11];
    			link.l1.go = "exit";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre")// квест №4, базар со слугой д'Эстре
            {
    			dialog.text = DLG_TEXT_Q[12];
    			link.l1 = DLG_TEXT_Q[13];
    			link.l1.go = "Step_S4_1";
            }
            if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre_1")// квест №4, базар со слугой д'Эстре
            {
    			dialog.text = DLG_TEXT_Q[14];
    			link.l1 = DLG_TEXT_Q[15];
    			link.l1.go = "exit";
            }
            if (npchar.id == "AnryDEstre")// квест №4, базар с самим д'Эстре
            {
    			dialog.text = DLG_TEXT_Q[16];
    			link.l1 = DLG_TEXT_Q[17];
    			link.l1.go = "Step_S4_2";
            }
            if (npchar.id == "LaVega_Comendant") // ==>  квест №5, фантом Мэнсфилада при штурме Ла Веги
            {
    			dialog.text = DLG_TEXT_Q[18];
    			link.l1 = DLG_TEXT_Q[19];
    			link.l1.go = "Step_S5_1";
            }
            if (npchar.id == "Boozer") // ==>  квест №6, базар с алкашом в таверне
            {
    			dialog.text = DLG_TEXT_Q[20];
    			link.l1 = DLG_TEXT_Q[21];
    			link.l1.go = "Step_S6_1";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_waitMessanger") //квест №6, базар с голландским вестовым
            {
    			dialog.text = DLG_TEXT_Q[22];
    			link.l1 = DLG_TEXT_Q[23];
    			link.l1.go = "Step_S6_8";
    			link.l2 = DLG_TEXT_Q[24];
    			link.l2.go = "Step_S6_11";
            }
            if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_Action") //квест №6, базар с голландским вестовым
            {
    			dialog.text = DLG_TEXT_Q[25];
    			link.l1 = DLG_TEXT_Q[26];
    			link.l1.go = "Step_S6_13";
			}
            if (npchar.id == "OurCaptain_1") //квест №7, базар с Пардалем его на корабле до битвы
            {
    			dialog.text = DLG_TEXT_Q[27];
    			link.l1 = DLG_TEXT_Q[28];
    			link.l1.go = "Exit";
			}
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_GoodWork") //квест №7, базар с Пардалем его на корабле
            {
    			dialog.text = DLG_TEXT_Q[29];
    			link.l1 = DLG_TEXT_Q[30] + GetFullName(pchar) +DLG_TEXT_Q[31];
    			link.l1.go = "Step_S7_1";
			}		
            if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_2GoodWork") //квест №7, базар с Пардалем его на корабле
            {
    			dialog.text = DLG_TEXT_Q[32];
    			link.l1 = DLG_TEXT_Q[33];
    			link.l1.go = "exit";
			}				
            if (npchar.id == "SpaTalkOfficer" && pchar.questTemp.State == "Sp10Maracaibo_TalkWithOfficer") //квест №10, базар c оффом на выходе
            {
    			dialog.text = DLG_TEXT_Q[34];
    			link.l1 = DLG_TEXT_Q[35];
    			link.l1.go = "Step_S10_1";
			}

		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Спасение трех горожан. Квест №1 **********************************
 		case "Step_S1_1":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "Step_S1_2";
		break;
 		case "Step_S1_2":
            AddQuestRecord("Spa_Line_1_SaveCitizens", "2");
			pchar.questTemp.State = "SaveFromMorgan_OutOfPrison";
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto12");
                LAi_SetActorType(sld);
                LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
                AddPassenger(pchar, sld, false);
                SetCharacterRemovable(sld, false);
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
//********************************* Работа на инквизицию. Квест №3 **********************************
 		case "Step_S3_1":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "Step_S3_2";
		break;
 		case "Step_S3_2":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "Step_S3_3";
		break;
 		case "Step_S3_3":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "Step_S3_4";
		break;
 		case "Step_S3_4":
 		    pchar.questTemp.State = "TakeRockBras_RockTaken";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "5");
            pchar.quest.TakeRockBras_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Maracaibo", true);
		    QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
//********************************* Расследование убийства. Квест №4 **********************************
 		case "Step_S4_1":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toDEstre_1";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1.location = "Tortuga_town";
			pchar.quest.Sp4Detection_Race_1.win_condition = "Sp4Detection_Race_1";
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
 		case "Step_S4_2":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47] + GetFullName(pchar) + DLG_TEXT_Q[48];
			link.l1.go = "Step_S4_3";
		break;
 		case "Step_S4_3":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "Step_S4_4";
		break;
 		case "Step_S4_4":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "Step_S4_5";
		break;
 		case "Step_S4_5":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Step_S4_6";
		break;
 		case "Step_S4_6":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "Step_S4_7";
		break;
 		case "Step_S4_7":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "Step_S4_8";
		break;
 		case "Step_S4_8":
            LAi_SetPlayerType(pchar);
			pchar.questTemp.State = "Sp4Detection_toDEstre_2";
            LAi_SetHP(npchar, 300, 300);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Sp4Detection_YouWin");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Уничтожение Ла Веги. Квест №5 **********************************
 		case "Step_S5_1":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "Step_S5_2";
			AfterTownBattle();
		break;
 		case "Step_S5_2":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, LAI_GROUP_TmpEnemy);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Sp5LaVegaAttack_AfterFight");
    	    NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Перехват посыльного Сювесанта. Квест №6 **********************************
 		case "Step_S6_1": //алкаш
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Step_S6_6";
            AddMoneyToCharacter(pchar, -100);
		break;
 		case "Step_S6_6":
			pchar.questTemp.State = "Sp6TakeMess_Action";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "4");
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1.location = "Tortuga_tavern_upstairs";
            Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition = "Sp6TakeMess_WaitMessanger";
			pchar.quest.Sp6TakeMess_Interception.over = "yes";
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", true);
            DialogExit();
		break;
		//=====>>> вестовой при попытке взять его в городе.
		case "Step_S6_11": 
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "Step_S6_7";
		break;
 		case "Step_S6_7":
			LAi_RemoveCheckMinHP(sld);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
		break;
 		case "Step_S6_8":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[73],
                          DLG_TEXT_Q[74], DLG_TEXT_Q[75], "none", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[76], DLG_TEXT_Q[77], DLG_TEXT_Q[78], "none", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_9", "Step_S6_12", "Step_S6_7", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_9":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "Step_S6_10";
		break;
 		case "Step_S6_10":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "Step_S6_12";
		break;
 		case "Step_S6_12":
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
            LAi_Actor2WaitDialog(npchar, pchar);
            DialogExit();
		break;
		//=====>>> вестовой захвате в комнате таверны.
 		case "Step_S6_13":
			dialog.text = DLG_TEXT_Q[83];
			link.l1 = DLG_TEXT_Q[84];
			link.l1.go = "Step_S6_14";
		break;
 		case "Step_S6_14":
			dialog.text = DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "Step_S6_15";
		break;
		case "Step_S6_15":
			bDisableFastReload = false; // открыть переходы.
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", false);
			LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Спасение Пардаля. Квест №7 **********************************
 		case "Step_S7_1": 
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "Step_S7_2";
		break;
 		case "Step_S7_2":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp7SavePardal_2GoodWork";
		break;
//********************************* Спасение Пардаля. Квест №7 **********************************
 		case "Step_S10_1": 
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "Step_S10_2";
		break;
 		case "Step_S10_2": 
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "Step_S10_3";
		break;
 		case "Step_S10_3": 
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "Step_S10_4";
		break;
 		case "Step_S10_4": 
			pchar.questTemp.State = "Sp10Maracaibo_toGovernor";
			AddQuestRecord("Spa_Line_10_Maracaibo", "2");
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", true);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", true);
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
            DialogExit();
		break;




    }
}
