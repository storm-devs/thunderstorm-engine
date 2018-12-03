#include "TEXT\DIALOGS\Quest\FraLineNpc_2.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	float locx, locy, locz;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            //Квест №1, сопровождение Леграна.
            if (pchar.questTemp.State == "Fr1Legran_toLeMaren")// квест №1, базар с бандиами 
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3];
    			link.l1.go = "Step_F1_1";
            }
            //Квест №2, доставка письма в Кюрасао.
            if (pchar.questTemp.State == "Fr2Letter_Arrest")// квест №2, базар с охраной при аресте
            {
    			dialog.text = DLG_TEXT_Q[4];
    			link.l1 = DLG_TEXT_Q[5];
    			link.l1.go = "Step_F2_1";
            }
            if (pchar.questTemp.State == "Fr2Letter_PrisonTalk")// квест №2, базар с тюремщиком
            {
    			dialog.text = DLG_TEXT_Q[6];
    			link.l1 = DLG_TEXT_Q[7];
    			link.l1.go = "Step_F2_2";
            }
            if (pchar.questTemp.State == "Fr2Letter_VisitGovernor")// квест №2, базар с фантомом губера в тюрьме
            {
    			dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "Step_F2_8";
            }
            if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, базар с кэпом галеона, абордаж
            {
    			dialog.text = DLG_TEXT_Q[10];
    			link.l1 = DLG_TEXT_Q[11];
    			link.l1.go = "Step_F2_12";
            }
			if (npchar.id == "AnnaDeLeiva")// квест №3, донна Анна в спальне
            {
    			dialog.text = DLG_TEXT_Q[12];
    			link.l1 = DLG_TEXT_Q[13];
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")// квест №5, Инесс
            {
    			dialog.text = DLG_TEXT_Q[14];
    			link.l1 = DLG_TEXT_Q[15];
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = DLG_TEXT_Q[16];
    			link.l1 = DLG_TEXT_Q[17];
    			link.l1.go = "exit";
            }
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")
            {
    			dialog.text = DLG_TEXT_Q[18];
    			link.l1 = DLG_TEXT_Q[19];
    			link.l1.go = "Step_F5_4";
            }
			if (npchar.id == "Captain_1" || npchar.id == "Captain_2")//квест №6, базар с кэпами
            {
    			dialog.text = DLG_TEXT_Q[20];
    			link.l1 = DLG_TEXT_Q[21];
    			link.l1.go = "exit";
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "Fr7RockBras_toSeekPlace")//квест №7, базар с Бразильцем. 
            {
    			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[22], DLG_TEXT_Q[23], DLG_TEXT_Q[24], DLG_TEXT_Q[25], "block", 0, npchar, Dialog.CurrentNode);
    			if (LAi_group_GetTarget(pchar) <= 0)
				{
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[26]+GetFullName(pchar)+DLG_TEXT_Q[27], DLG_TEXT_Q[28]+GetFullName(pchar)+DLG_TEXT_Q[29], DLG_TEXT_Q[30]+GetFullName(pchar)+DLG_TEXT_Q[29], DLG_TEXT_Q[31]+GetFullName(pchar)+DLG_TEXT_Q[29], npchar, Dialog.CurrentNode);
    				link.l1.go = "Step_F7_1";
				}
				else
				{
					link.l1 = DLG_TEXT_Q[32];
    				link.l1.go = "Step_F7_Late";
				}
				// --> типа опоздал...
				if (GetQuestPastDayParam("questTemp") > 8)
				{
    				dialog.text = DLG_TEXT_Q[33];
    				link.l1 = DLG_TEXT_Q[34];
    				link.l1.go = "Step_F7_8";
				}
				else SaveCurrentQuestDateParam("questTemp"); //чтобы не глюкнуло во время боя
				// <-- типа опоздал...
            }
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "empty")//квест №7, базар с Бразильцем в резиденции дОжерона. 
            {
    			dialog.text = DLG_TEXT_Q[35];
    			link.l1 = DLG_TEXT_Q[36];
    			link.l1.go = "Step_F7_5";
            }
			if (npchar.id == "CaptainGay")//квест №8, базар с кэпом Геем. 
            {
    			dialog.text = DLG_TEXT_Q[37];
    			link.l1 = DLG_TEXT_Q[38];
    			link.l1.go = "Step_F8_1";
            }			
		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Спасение трех горожан. Квест №1 **********************************
 		case "Step_F1_1":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Legran");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Fr1Legran_afterFightBandits");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
 		case "Step_F2_1":
			LAi_SetPlayerType(pchar);
            DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto9");
			SetTempRemoveParam(pchar, "items");
			pchar.questTemp.money = sti(pchar.money)/2;
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
			pchar.money = 0;
			DeleteAttribute(pchar, "items");
			DoQuestCheckDelay("Fr2Letter_intoPrison_1", 20);
			AddQuestRecord("Fra_Line_2_DelivLetter", "2");
            DialogExit();
		break;
 		case "Step_F2_2":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "Step_F2_5";
		break;
 		case "Step_F2_5":
			dialog.text = DLG_TEXT_Q[47];
			link.l1 = DLG_TEXT_Q[48];
			link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = DLG_TEXT_Q[49]+
				          DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "Step_F2_7";
		break;	
 		case "Step_F2_7":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
            DialogExit();
			DoQuestCheckDelay("Fr2Letter_intoPrison_3", 10);
		break;	
 		case "Step_F2_8":
			dialog.text = DLG_TEXT_Q[52]+
				          DLG_TEXT_Q[53]+
						  DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "Step_F2_9";
		break;		
 		case "Step_F2_9":
			dialog.text = DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FrLine_HoverGoOnPrison");
		break;

 		case "Step_F2_12":
			dialog.text = DLG_TEXT_Q[60] + GetFullName(npchar) + DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "Step_F2_13";
		break;
 		case "Step_F2_13":
			AddQuestRecord("Fra_Line_2_DelivLetter", "5");
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.questTemp.State = "Fr2Letter_NiceResult";
			DialogExit();
		break;
//********************************* Похищение донны Анны. Квест №3 **********************************
 		case "Step_F3_1":
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			pchar.questTemp.State = "Fr3TakeAnna_HavanaOut";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1.location = "Cuba2";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition = "Fr3TakeAnna_DelivShip";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
//********************************* Проблемы донны Анны. Квест №5 **********************************
 		case "Step_F5_1":
			dialog.text = DLG_TEXT_Q[65]+
				          DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
    		link.l1.go = "Step_F5_2";
		break;
 		case "Step_F5_2":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
    		link.l1.go = "exit";
			pchar.questTemp.State = "Fr5AnnaHant_SeekHoseBrothers";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "3");			
			npchar.LifeDay = 1; // уберем нпс
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			locations[FindLocation("Mayak10")].DisableEncounters = true; //энкаутеры закроем
			LAi_LocationDisableOfficersGen("Mayak10", true); //офицеров не пускать
			Pchar.quest.Fr5Anna_InShore.win_condition.l1 = "location";
			Pchar.quest.Fr5Anna_InShore.win_condition.l1.location = "Mayak10";
			Pchar.quest.Fr5Anna_InShore.win_condition = "Fr5Anna_InShore";
		break;
 		case "Step_F5_4":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
    		link.l1.go = "exit";
		break;
//********************************* Вызволение Рока Бразильца. Квест №7 **********************************
 		case "Step_F7_1":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = DLG_TEXT_Q[74];
				link.l1 =  DLG_TEXT_Q[75];
    			link.l1.go = "Step_F7_2";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[76];
				link.l1 = DLG_TEXT_Q[77];
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_2":
    		if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = DLG_TEXT_Q[78];
				link.l1 =  DLG_TEXT_Q[79];
    			link.l1.go = "Step_F7_3";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[80];
				link.l1 = DLG_TEXT_Q[81];
    			link.l1.go = "Step_F7_Late";
			}
		break;
 		case "Step_F7_3":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
    		link.l1.go = "Step_F7_4";
		break;
 		case "Step_F7_4":
			bDisableFastReload = false;
			AddQuestRecord("Fra_Line_7_RockBras", "2");
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1.location = "Cuba1";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition = "Fr7RockBras_DelivShip";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
 		case "Step_F7_5":
			dialog.text = DLG_TEXT_Q[84]+
				          DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
    		link.l1.go = "Step_F7_6";
		break;
		case "Step_F7_6":
            dialog.text = DLG_TEXT_Q[87]+
				          DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
            link.l1.go = "Step_F7_7";
        break;
		case "Step_F7_7":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "none", "", "", "", 6.0);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // уберем нпс
			pchar.GenQuestRandItem.FortFrance_Dungeon = true;
			pchar.GenQuestRandItem.FortFrance_Dungeon.randitem3 = "cirass5";
			DialogExit();
        break;
 		case "Step_F7_8":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
    		link.l1.go = "Step_F7_9";
		break;
 		case "Step_F7_9":
			bDisableFastReload = true;
			LAi_KillCharacter(npchar);
			DeleteAttribute(npchar, "RebirthPhantom");
         	npchar.LifeDay = 0; // уберем нпс
			pchar.questTemp.State = "Fr7RockBras_RockIsAgony";
			DialogExit();
		break;
 		case "Step_F7_Late":
			bDisableFastReload = true;
			LAi_ActorWaitDialog(npchar, pchar);
			DialogExit();
		break;
//********************************* Объехать трех корсаров. Квест №8 **********************************
        case "Step_F8_1":
            dialog.text = DLG_TEXT_Q[92];
            link.l1 = DLG_TEXT_Q[93];
            link.l1.go = "Step_F8_2";
        break;
 		case "Step_F8_2":
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", true);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CanFightCurLocation");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	}
}
