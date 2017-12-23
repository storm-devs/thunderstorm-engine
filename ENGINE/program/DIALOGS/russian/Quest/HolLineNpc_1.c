#include "TEXT\DIALOGS\Quest\HolLineNpc_1.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
            if (npchar.id == "Bandit2" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")// перехват на бандитов, грябящих Аарона
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3]+ GetFullName(pchar) +DLG_TEXT_Q[4];
    			link.l1.go = "Step_H1_1";
            }// Аарон собственной персоной, после драки с грабителями
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")
            {
    			dialog.text = DLG_TEXT_Q[5];
    			link.l1 = DLG_TEXT_Q[6]+ GetFullName(pchar) +DLG_TEXT_Q[7];
    			link.l1.go = "Step_H1_3";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_GoToVillemstad")
            {
    			dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "Step_H1_6";
            }// Квест №3, лейтенант в тюрьме.
            if (npchar.id == "Alan_MacLine" && pchar.questTemp.State == "WormEnglPlans_SaveOfficer")
            {
    			dialog.text = DLG_TEXT_Q[10];
    			link.l1 = DLG_TEXT_Q[11];
    			link.l1.go = "Step_H3_1";
            } // Квест №5, базар в Ла Веге о гибели Мэнсфилда
            if (npchar.id == "Talker" && pchar.questTemp.State == "ThreeFleutes_toLaVega")
            {
    			dialog.text = DLG_TEXT_Q[12];
    			link.l1 = DLG_TEXT_Q[13];
    			link.l1.go = "Step_H5_1";
            } // Квест №7, незнакомец на Тортуге
            if (npchar.id == "Stranger_HL7" && pchar.questTemp.State == "DelivLettTortuga_SnapMeeting")
            {
    			dialog.text = DLG_TEXT_Q[14];
    			link.l1 = DLG_TEXT_Q[15];
    			link.l1.go = "Step_H7_1";
            } // Квест №7, Антонио в комнате таверны
            if (npchar.id == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_toStranger")
            {
    			dialog.text = DLG_TEXT_Q[16];
    			link.l1 = DLG_TEXT_Q[17];
    			link.l1.go = "Step_H7_4";
            }
            if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
            {
    			dialog.text = DLG_TEXT_Q[18];
    			link.l1 = DLG_TEXT_Q[19];
    			link.l1.go = "Step_H7_6";
            } // Квест №8, Аарон дает задание
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toAaron")
            {
    			dialog.text = DLG_TEXT_Q[20];
    			link.l1 = DLG_TEXT_Q[21];
    			link.l1.go = "Step_H8_1";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toBermudes")
            {
    			dialog.text = DLG_TEXT_Q[22];
    			link.l1 = DLG_TEXT_Q[23];
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafIsDead")
            {
    			dialog.text = DLG_TEXT_Q[24];
    			link.l1 = DLG_TEXT_Q[25];
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafDieHard")
            {
    			dialog.text = DLG_TEXT_Q[26];
    			link.l1 = DLG_TEXT_Q[27];
    			link.l1.go = "Step_H8_12";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_BadResult")
            {
    			dialog.text = DLG_TEXT_Q[28];
    			link.l1 = DLG_TEXT_Q[29];
    			link.l1.go = "exit";
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_WeWon")
            {
    			dialog.text = DLG_TEXT_Q[30];
    			link.l1 = DLG_TEXT_Q[31];
    			link.l1.go = "Step_H8_12";
    			link.l2 = DLG_TEXT_Q[32];
    			link.l2.go = "exit";
			}			
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_IHaveMap")
            {
                dialog.text = DLG_TEXT_Q[33];
    			link.l1 = DLG_TEXT_Q[34];
    			link.l1.go = "Step_H8_12";
				if (CheckCharacterItem(pchar, "Bible"))
				{
           			link.l2 = DLG_TEXT_Q[35];
        			link.l2.go = "Step_H8_13";
                }
                else
                {
        			link.l2 = DLG_TEXT_Q[36];
        			link.l2.go = "exit";
                }
            }
            if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_GoodResult")
            {
    			dialog.text = DLG_TEXT_Q[37];
    			link.l1 = DLG_TEXT_Q[38];
    			link.l1.go = "exit";
            }

        break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Дилоги бандитов, грабящих Аарона. Квест №1 **********************************
 		case "Step_H1_1":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "Step_H1_2";
		break;
 		case "Step_H1_2":
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_H1_3":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Step_H1_4";
		break;
 		case "Step_H1_4":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Step_H1_5";
		break;
 		case "Step_H1_5":
            AddQuestRecord("Hol_Line_1_Chumakeiro", "2");
		    pchar.questTemp.State = "SeekChumakeiro_GoToVillemstad";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1.location = "Villemstad_townhall";
            Pchar.quest.SeekChumakeiro_intoResidence.win_condition = "SeekChumakeiro_intoResidence";
			DialogExit();
		break;
 		case "Step_H1_6":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "Step_H1_7";
		break;
 		case "Step_H1_7":
            LAi_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 30000);
			RemovePassenger(pchar, npchar);
			AddQuestRecord("Hol_Line_1_Chumakeiro", "3");
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DialogExit();
		break;

//********************************* Дилоги лейтенанта в тюрьме. Квест №3 **********************************
 		case "Step_H3_1":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Step_H3_2";
		break;
 		case "Step_H3_2":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "Step_H3_3";
		break;
 		case "Step_H3_3":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "Step_H3_4";
		break;
 		case "Step_H3_4":
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(characterFromId("Henry Morgan"));
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "14");
 		    pchar.questTemp.State = "WormEnglPlans_GoodRusultWorm";
            ChangeCharacterAddressGroup(npchar, "SentJons_prison", "goto", "goto23");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
            DialogExit();
		break;

//********************************* Базар в Ла Веге о гибели Мэнсфилда. Квест №5 **********************************
  		case "Step_H5_1":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Step_H5_2";
		break;
 		case "Step_H5_2":
			chrDisableReloadToLocation = false;
 		    AddQuestRecord("Hol_Line_5_ThreeFleutes", "2");
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1 = "location";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1.location = "Hispaniola1";
            Pchar.quest.ThreeFleutes_BackToCuracao.win_condition = "ThreeFleutes_BackToCuracao";
            DialogExit();
		break;

//********************************* Базар с незнакомцем на Тортуге. Квест №7 **********************************
  		case "Step_H7_1":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "Step_H7_2";
		break;
  		case "Step_H7_2":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "Step_H7_3";
		break;
  		case "Step_H7_3":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "DelivLettTortuga_toStranger";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = GetCharacter(NPC_GenerateCharacter("AntonioDeBarras", "officer_9", "man", "man", 40, SPAIN, -1, true));
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	sld.name 	= DLG_TEXT_Q[59];
        	sld.lastname = DLG_TEXT_Q[60];
        	LAi_SetStayTypeNoGroup(sld);
            FantomMakeCoolSailor(sld, SHIP_WARSHIP, DLG_TEXT_Q[61], CANNON_TYPE_CULVERINE_LBS32, 100, 100, 100);
            FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol5", 150);
          	ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
            DialogExit();
		break;

        case "Step_H7_4":
			dialog.text = DLG_TEXT_Q[62]+
                          DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Step_H7_5";
		break;
  		case "Step_H7_5":
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", false);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", false);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
            LAi_SetActorType(npchar);
            LAi_SetActorType(pchar);
            LAi_ActorTurnToLocator(pchar, "reload", "reload1_back");
            DoQuestFunctionDelay("DelivLettTortuga_Digress", 1.0);
            DialogExit();
		break;

        case "Step_H7_6":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "Step_H7_7";
		break;
        case "Step_H7_7":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Step_H7_8";
		break;
        case "Step_H7_8":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Step_H7_9";
		break;
        case "Step_H7_9":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72];
			link.l1.go = "Step_H7_10";
            GiveItem2Character(pchar,"letter_1");
		break;
        case "Step_H7_10":
			dialog.text = DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "Step_H7_11";
		break;
        case "Step_H7_11":
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "11");
            pchar.questTemp.State = "DelivLettTortuga_LetterFound";
            pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
            pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
            Island_SetReloadEnableGlobal("SantaCatalina", true);
            QuestAboardCabinDialogSurrender();
            DialogExit();
		break;
		
//********************************* Поиски Библии. Квест №8 **********************************
        case "Step_H8_1":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "Step_H8_2";
		break;
        case "Step_H8_2":
			dialog.text = DLG_TEXT_Q[77]+
                          DLG_TEXT_Q[78]+
                          DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "Step_H8_3";
		break;
        case "Step_H8_3":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "Step_H8_4";
		break;
        case "Step_H8_4":
			dialog.text = DLG_TEXT_Q[83]+
                          DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "Step_H8_5";
		break;
        case "Step_H8_5":
			dialog.text = DLG_TEXT_Q[86]+
                          DLG_TEXT_Q[87]+
                          DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "Step_H8_6";
		break;
        case "Step_H8_6":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "Step_H8_7";
		break;
        case "Step_H8_7":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "Step_H8_8";
		break;
        case "Step_H8_8":
			dialog.text = DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Step_H8_9";
		break;
        case "Step_H8_9":
			dialog.text = DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
			link.l1.go = "Step_H8_10";
		break;
        case "Step_H8_10":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "Step_H8_11";
		break;
        case "Step_H8_11":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toBermudes";
            AddQuestRecord("Hol_Line_8_SeekBible", "2");
            QuestSetCurrentNode("Jackman", "HolLine8_quest");
		break;
        case "Step_H8_12":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_BadResult";
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
        case "Step_H8_13":
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "Step_H8_14";
			TakeItemFromCharacter(pchar, "Bible");
		break;
        case "Step_H8_14":
			dialog.text = GetFullName(pchar) + DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "Step_H8_15";
		break;
        case "Step_H8_15":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "Step_H8_16";
		break;
        case "Step_H8_16":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
			link.l1.go = "Step_H8_17";
		break;
        case "Step_H8_17":
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1235000);
            pchar.questTemp.State = "SeekBible_GoodResult";
            AddQuestRecord("Hol_Line_8_SeekBible", "10");
            NPChar.LifeDay = 0;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		break;
    }
}
