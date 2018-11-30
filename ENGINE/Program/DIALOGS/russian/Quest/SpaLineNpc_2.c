#include "TEXT\DIALOGS\Quest\SpaLineNpc_2.h"
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
            if (npchar.id == "Francisco")// квест №2, базар с Франциско
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3];
    			link.l1.go = "Step_S2_1";
            }
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))// квест №2, малый де Фонкейсао
            {
    			dialog.text = DLG_TEXT_Q[4];
    			link.l1 = DLG_TEXT_Q[5];
    			link.l1.go = "Step_S2_6";
            }
            if (npchar.id == "Bandit" && CheckAttribute(pchar, "questTemp.State.Store"))// квест №2, бандит на 1-м этаже
            {
    			dialog.text = DLG_TEXT_Q[6];
    			link.l1 = DLG_TEXT_Q[7];
    			link.l1.go = "Step_S2_11";
            }
			if (npchar.id == "JacowDeFonseka" && CheckAttribute(pchar, "questTemp.State.Store"))
			{
                dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "Step_S2_14";
            }
			if (npchar.id == "PortMansBoy")  //квест №6, посыльный начальника порта.
			{
                dialog.text = DLG_TEXT_Q[10];
    			link.l1 = DLG_TEXT_Q[11];
    			link.l1.go = "Step_S6_1";
            }	//квест №7, Моисей Воклейн.
 			if (pchar.questTemp.State == "Sp7SavePardal_toAntigua" || pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")  
			{
                dialog.text = DLG_TEXT_Q[12];
    			link.l1 = DLG_TEXT_Q[13];
    			link.l1.go = "Step_S7_1";
            }  //квест №8, капитан Ансель.
 			if (pchar.questTemp.State == "Sp8SaveCumana_toCumana")  
			{
                dialog.text = DLG_TEXT_Q[14];
    			link.l1 = DLG_TEXT_Q[15];
    			link.l1.go = "exit";
				LAi_SetCurHPMax(npchar);
				QuestAboardCabinDialogExitWithBattle("");
            }
		break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//*************************** Квест №2, диалоги с Франциско на выходе из Инквизиии ***************************
 		case "Step_S2_1":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "Inquisition_afterFrancisco";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            DialogExit();
		break;
 		case "Step_S2_6":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = DLG_TEXT_Q[29];
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = DLG_TEXT_Q[30];
			link.l1 = DLG_TEXT_Q[31];
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
            AddQuestRecord("Spa_Line_2_Inquisition", "8");
            pchar.quest.Inquisition_DieHard.over = "yes";
            Island_SetReloadEnableGlobal("Jamaica", true);
            QuestAboardCabinDialogQuestSurrender();
            DialogExit();
		break;
 		case "Step_S2_11":
			dialog.text = DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "Step_S2_12";
		break;
 		case "Step_S2_12":
			dialog.text = DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_S2_14":
			dialog.text = DLG_TEXT_Q[36]+
                          DLG_TEXT_Q[37];
			link.l1 = DLG_TEXT_Q[38] + GetFullName(pchar) + DLG_TEXT_Q[39];
			link.l1.go = "Step_S2_15";
		break;
 		case "Step_S2_15":
			dialog.text = DLG_TEXT_Q[40]+
                          DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Step_S2_16";
		break;
 		case "Step_S2_16":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Step_S2_17";
		break;
 		case "Step_S2_17":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = DLG_TEXT_Q[49];
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = DLG_TEXT_Q[51];
			link.l1 = DLG_TEXT_Q[52];
			link.l1.go = "Step_S2_21";
		break;
 		case "Step_S2_21":
 		    LAi_SetPlayerType(pchar);
            AddQuestRecord("Spa_Line_2_Inquisition", "12");
            AddQuestRecord("Spa_Line_2_Inquisition", "13");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
            pchar.questTemp.State.SeekBible = 1; //флаг на поиск Евангелие
            LocatorReloadEnterDisable("Shore3", "reload2_back", true); //закрываем для особо хитрых
            DialogExit();
		break;
//*************************** Квест №6, базар с посыльным начальника порта ***************************
 		case "Step_S6_1":
			dialog.text = DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Step_S6_2";
		break;
 		case "Step_S6_2":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "3");
			bDisableFastReload = true; //закрываем фаст релоад
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.Sp6TakeMess_Interception.win_condition.l1 = "location";
            Pchar.quest.Sp6TakeMess_Interception.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.Sp6TakeMess_Interception.win_condition = "Sp6TakeMess_Interception";
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
            DialogExit();
		break;
//*************************** Квест №7, базар с Моисеем Воклейном при абордаже ***************************
 		case "Step_S7_1":
			dialog.text = DLG_TEXT_Q[57];
			link.l1 = DLG_TEXT_Q[58];
			link.l1.go = "exit";
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
		break;


    }
}


