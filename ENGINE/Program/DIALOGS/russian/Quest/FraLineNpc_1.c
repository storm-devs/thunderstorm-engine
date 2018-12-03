#include "TEXT\DIALOGS\Quest\FraLineNpc_1.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
    float locx, locy, locz;
	string sTemp, attrName;

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
            if (pchar.questTemp.State == "Fr1Legran_toTavern")// квест №1, Легран в таверне
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3];
    			link.l1.go = "Step_F1_1";
            }
            if (pchar.questTemp.State == "Fr1Legran_afterFightBand")// квест №1, Легаран после боя.
            {
    			dialog.text = DLG_TEXT_Q[4];
    			link.l1 = DLG_TEXT_Q[5];
    			link.l1.go = "Step_F1_3";
    			link.l2 = DLG_TEXT_Q[6];
    			link.l2.go = "Step_F1_5";
            } 
            //Квест №2, доставка письма на Тортугу
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, странные типы в таверне
            {
    			dialog.text = DLG_TEXT_Q[7];
				link.l1 = DLG_TEXT_Q[8];
    			link.l1.go = "Step_F2_1";
            }
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems" && pchar.location == "Shore22")// квест №2, странные типы в бухте
            {
    			dialog.text = DLG_TEXT_Q[9];
				link.l1 = DLG_TEXT_Q[10];
    			link.l1.go = "Step_F2_5";
            }
			if (npchar.id == "DeLeiva")// квест №3, база с мужем донны Анны
            {
    			dialog.text = DLG_TEXT_Q[11];
				link.l1 = DLG_TEXT_Q[12];
    			link.l1.go = "Step_F3_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toAnna")// квест №5, донна Анна в резиденции Тортуги
            {
    			dialog.text = DLG_TEXT_Q[13];
    			link.l1 = DLG_TEXT_Q[14];
    			link.l1.go = "Step_F5_1";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")
            {
    			dialog.text = DLG_TEXT_Q[15];
    			link.l1 = DLG_TEXT_Q[16];
    			link.l1.go = "exit";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
            {
    			dialog.text = DLG_TEXT_Q[17];
    			link.l1 = DLG_TEXT_Q[18];
    			link.l1.go = "exit";
            }
			if (npchar.id == "DeLeivaBrother_1" || npchar.id == "DeLeivaBrother_2")// квест №5, братья де Лейва
            {
    			dialog.text = DLG_TEXT_Q[19];
    			link.l1 = DLG_TEXT_Q[20];
    			link.l1.go = "Step_F5_2";
            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")// квест №5, донна Анна после выполнения задачи
            {
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[21],
					         DLG_TEXT_Q[22], DLG_TEXT_Q[23], DLG_TEXT_Q[24], "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[25], 
					      DLG_TEXT_Q[26], DLG_TEXT_Q[27], DLG_TEXT_Q[28], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);

            }
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "empty")// квест №5, донна Анна после выполнения задачи
            {
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[29],
					         DLG_TEXT_Q[30], DLG_TEXT_Q[31], DLG_TEXT_Q[32], "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[33], 
					      DLG_TEXT_Q[34], DLG_TEXT_Q[35], DLG_TEXT_Q[36], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_toGuadeloupe")// квест №6, базар в доме Олоне
            {
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[37],
					         DLG_TEXT_Q[38], DLG_TEXT_Q[39], DLG_TEXT_Q[40], "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[41], 
					      DLG_TEXT_Q[42], DLG_TEXT_Q[43], DLG_TEXT_Q[44], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F6_1", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_FoundMoney") //успели к деньгам
            {
    			dialog.text = DLG_TEXT_Q[45];
    			link.l1 = DLG_TEXT_Q[46];
    			link.l1.go = "Step_F6_14";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
            }
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_WeLate") //деньги ушли
            {
    			dialog.text = DLG_TEXT_Q[47];
    			link.l1 = DLG_TEXT_Q[48];
    			link.l1.go = "Step_F6_10";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toBonrepo") //Квест №8. Маркиз Бонрепо в Бас-Тере
            {
    			dialog.text = DLG_TEXT_Q[49];
    			link.l1 = DLG_TEXT_Q[50] + GetFullName(pchar) + DLG_TEXT_Q[51];
    			link.l1.go = "Step_F8_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek") 
            {
    			dialog.text = DLG_TEXT_Q[52];
    			if (sti(pchar.questTemp.Count) == 3)
				{
					link.l1 = DLG_TEXT_Q[53];
    				link.l1.go = "Step_F8_9";
				}
				else
				{
					link.l1 = DLG_TEXT_Q[54];
    				link.l1.go = "exit";
				}
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr12EndWar_toBorepo")
            {
    			dialog.text = DLG_TEXT_Q[55];
    			link.l1 = DLG_TEXT_Q[56];
    			link.l1.go = "Step_F12_1";
            }
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "EndOfQuestLine")
            {
    			dialog.text = DLG_TEXT_Q[57];
    			link.l1 = DLG_TEXT_Q[58];
    			link.l1.go = "exit";
            }
		break;
//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Доставка Леграна до Мартиники. Квест №1 **********************************
 		case "Step_F1_1":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60]+ GetFullName(pchar) +DLG_TEXT_Q[61];
			link.l1.go = "Step_F1_2";
		break;
 		case "Step_F1_2":
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "Step_F1_exit";
		break;
 		case "Step_F1_exit":
			locations[FindLocation("Shore39")].DisableEncounters = true; //энкаунтеры закроем
    		pchar.questTemp.State = "Fr1Legran_toLeMaren";
            AddQuestRecord("Fra_Line_1_LegranDis", "2");
			LAi_SetStayType(npchar);
            GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1 = "location";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1.location = "Shore39";
            Pchar.quest.Fr1Legran_intoLeMaren.win_condition = "Fr1Legran_intoLeMaren";
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            DialogExit();
		break;
 		case "Step_F1_3":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "Step_F1_4";
		break;
 		case "Step_F1_4":
			dialog.text = DLG_TEXT_Q[66]+
				          DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Step_F1_4_exit";
		break;
		case "Step_F1_4_exit":
			pchar.questTemp.State = "Fr1Legran_backGovernor";
			AddQuestRecord("Fra_Line_1_LegranDis", "3");
			AddMoneyToCharacter(pchar, 20000);
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
			NPChar.LifeDay = 0;
			RemovePassenger(pchar, npchar);
            DialogExit();
		break;
 		case "Step_F1_5":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Step_F1_6";
		break;
 		case "Step_F1_6":
			LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
			AddQuestRecord("Fra_Line_1_LegranDis", "4");
			pchar.questTemp.State = "Fr1Legran_LegranKilled";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
 		case "Step_F2_1":
			dialog.text = DLG_TEXT_Q[71];
			link.l1 = DLG_TEXT_Q[72] + GetFullName(pchar) + DLG_TEXT_Q[73];
    		link.l1.go = "Step_F2_2";
		break;
 		case "Step_F2_2":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "Step_F2_3";
		break;
 		case "Step_F2_3":
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "Step_F2_4";
		break;
 		case "Step_F2_4":
			chrDisableReloadToLocation = true; 
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetStayType(sld);
				if (i==2) ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "tables", "stay2");
				else ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "goto", "goto3");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", 10);
			}
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1 = "location";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1.location = "Villemstad_town";
            Pchar.quest.Fr2Letter_OutTavern_2.win_condition = "Fr2Letter_OutTavern_2";
			locations[FindLocation("Shore22")].DisableEncounters = true; //энкаутеры уберем временно
			LAi_SetPlayerType(pchar);
            DialogExit();
		break;

 		case "Step_F2_5":
			dialog.text = DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
    		link.l1.go = "Step_F2_6";
		break;
 		case "Step_F2_6":
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
    		link.l1.go = "Step_F2_7";
		break;
 		case "Step_F2_7":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
    		link.l1.go = "Step_F2_8";
		break;
 		case "Step_F2_8":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
    		link.l1.go = "Step_F2_9";
		break;
 		case "Step_F2_9":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
    		link.l1.go = "Step_F2_10";
		break;
 		case "Step_F2_10":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
    		link.l1.go = "Step_F2_11";
		break;
 		case "Step_F2_11":
			DeleteAttribute(&locations[FindLocation("Shore22")], "DisableEncounters"); //энкаутеры вернем
			chrDisableReloadToLocation = true;
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1 = "location";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1.location = "Curacao";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition = "Fr2Letter_FightWithGaleon";
			AddQuestRecord("Fra_Line_2_DelivLetter", "4");
            for (i=1; i<=2; i++)
            {
				sld = characterFromId("Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Драка с мужем де Лейва. Квест №3 **********************************
 		case "Step_F3_1":
			dialog.text = DLG_TEXT_Q[90]+
				          DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
    		link.l1.go = "Step_F3_2";
		break;
 		case "Step_F3_2":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
    		link.l1.go = "Step_F3_3";
		break;
 		case "Step_F3_3":
			LAi_LocationFightDisable(loadedLocation, false); 
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Месть Анне де Лейва. Квест №5 **********************************
 		case "Step_F5_1":
			dialog.text = DLG_TEXT_Q[95]+
				          DLG_TEXT_Q[96];
			link.l1 = DLG_TEXT_Q[97];
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Fr5AnnaHant_toHavana";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "2");			
			sld = GetCharacter(NPC_GenerateCharacter("InesDeLasCierras", "girl_8", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = DLG_TEXT_Q[98];
			sld.lastname = DLG_TEXT_Q[99];
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_houseSp2", "goto","goto2");
		break;
 		case "Step_F5_2":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
    		link.l1.go = "Step_F5_3";
		break;
 		case "Step_F5_3":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
    		link.l1.go = "Step_F5_4";
		break;
 		case "Step_F5_4":
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
    		link.l1.go = "Step_F5_5";
		break;
 		case "Step_F5_5":
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
    		link.l1.go = "Step_F5_6";
		break;
 		case "Step_F5_6":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
    		link.l1.go = "Step_F5_7";
		break;
 		case "Step_F5_7":
			LAi_LocationDisableOfficersGen("Mayak10", false); //офицеров пускать
			pchar.questTemp.State = "Fr5AnnaHant_GoodWork";
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], false); 			
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=2; i++)
            {				
				LAi_group_MoveCharacter(characterFromId("DeLeivaBrother_"+i), "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
		break;
 		case "Step_F5_8":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = DLG_TEXT_Q[111];
    		link.l1.go = "Step_F5_9";
		break;
 		case "Step_F5_9":
			dialog.text = DLG_TEXT_Q[112] + pchar.name + DLG_TEXT_Q[113];
			link.l1 = DLG_TEXT_Q[114];
    		link.l1.go = "Step_F5_10";
		break;
 		case "Step_F5_10":
			dialog.text = DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
		break;
//********************************* Франсуа Олоне. Квест №6 **********************************
 		case "Step_F6_1":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
    		link.l1.go = "Step_F6_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
		break;
 		case "Step_F6_2":
			dialog.text = DLG_TEXT_Q[119];
			link.l1 = DLG_TEXT_Q[120];
    		link.l1.go = "Step_F6_3";
		break;
 		case "Step_F6_3":
			dialog.text = DLG_TEXT_Q[121];
			link.l1 = DLG_TEXT_Q[122];
    		link.l1.go = "Step_F6_WantMoney";
			link.l2 = DLG_TEXT_Q[123];
    		link.l2.go = "Step_F6_4";
			SaveCurrentQuestDateParam("questTemp");
		break;
 		case "Step_F6_WantMoney":
			dialog.text = DLG_TEXT_Q[124];
			link.l1 = DLG_TEXT_Q[125];
    		link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddMoneyToCharacter(pchar, 10000);
			pchar.questTemp.State = "Fr6Olone_TakeMoney";
			AddQuestRecord("Fra_Line_6_Olone", "2");
		break;
 		case "Step_F6_4":
            if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
            {
				if (GetQuestPastDayParam("questTemp") < 6)
				{
					dialog.text = DLG_TEXT_Q[126];
					link.l1 = DLG_TEXT_Q[127];
    				link.l1.go = "Step_F6_5";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[128];
					link.l1 = DLG_TEXT_Q[129];
    				link.l1.go = "Step_F6_7";
				}
            }
            else
            {
				dialog.text = DLG_TEXT_Q[130];
				link.l1 = DLG_TEXT_Q[131];
    			link.l1.go = "exit";
				link.l2 = DLG_TEXT_Q[132];
    			link.l2.go = "Step_F6_WantMoney";
				NextDiag.TempNode = "Step_F6_4";
             }
		break;
 		case "Step_F6_5":
			dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
    		link.l1.go = "Step_F6_6";
		break;
 		case "Step_F6_6":
			dialog.text = DLG_TEXT_Q[135];
			link.l1 = DLG_TEXT_Q[136];
    		link.l1.go = "Step_F6_GoOn";
		break;
		case "Step_F6_GoOn": 
			//==> формируем эскадру
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 5, false);
			for (i=1; i<=2; i++)
			{
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "officer_"+(rand(9)+1), "man", "man", 20, FRANCE, -1, true));
                FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS24, 70, 80, 40);
                FantomMakeCoolFighter(sld, 20, 90, 70, BLADE_LONG, "pistol4", 120);
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				sld.CompanionEnemyEnable = false; 
				sld.Abordage.Enable = false; // НЕЛЬЗЯ!
				sld.RebirthPhantom = true; 
                SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.DeckDialogNode = "HaveHotBussines";
				SetCharacterRemovable(sld, false);
				LAi_LoginInCaptureTown(sld, true);
			}
            // ==> текущая дата, у генерал-губернатора Куманы потом сверим
            SaveCurrentQuestDateParam("questTemp");            
            pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
            // ==> капитулянтская нода губернатору Куманы
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "FraLine6Quest_Attack"; 
			npchar.DeckDialogNode = "HaveHotBussines";
			AddQuestRecord("Fra_Line_6_Olone", "3");
			DialogExit();
		break;
		case "Step_F6_7":
			dialog.text = DLG_TEXT_Q[137];
			link.l1 = DLG_TEXT_Q[138];
    		link.l1.go = "Step_F6_8";
		break;
 		case "Step_F6_8":
			dialog.text = DLG_TEXT_Q[139];
			link.l1 = DLG_TEXT_Q[140];
    		link.l1.go = "Step_F6_9";
		break;
 		case "Step_F6_9":
			dialog.text = DLG_TEXT_Q[141];
			link.l1 = DLG_TEXT_Q[142];
    		link.l1.go = "Step_F6_WantMoney";
		break;
 		case "HaveHotBussines":
			dialog.text = DLG_TEXT_Q[143];
			link.l1 = DLG_TEXT_Q[144];
    		link.l1.go = "exit";
		break;
 		case "Step_F6_10":
			dialog.text = DLG_TEXT_Q[145] + pchar.name + ".";
			link.l1 = DLG_TEXT_Q[146];
    		link.l1.go = "Step_F6_11";
		break;
 		case "Step_F6_11":
			dialog.text = DLG_TEXT_Q[147];
			link.l1 = DLG_TEXT_Q[148];
    		link.l1.go = "Step_F6_12";
		break;
 		case "Step_F6_12":
			dialog.text = DLG_TEXT_Q[149];
			link.l1 = DLG_TEXT_Q[150];
    		link.l1.go = "Step_F6_13";
		break;
 		case "Step_F6_13":
			dialog.text = DLG_TEXT_Q[151];
			link.l1 = DLG_TEXT_Q[152];
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "4");
		break;
 		case "Step_F6_fight":			
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Captain_"+i);
				sld.LifeDay = 0;
				DeleteAttribute(sld, "RebirthPhantom");
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F6_14":
			if (sti(pchar.money) >= 200000)
			{
				dialog.text = DLG_TEXT_Q[153];
				link.l1 = DLG_TEXT_Q[154];
    			link.l1.go = "Step_F6_15";
				link.l2 = DLG_TEXT_Q[155];
    			link.l2.go = "Step_F6_20";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[156];
				link.l1 = DLG_TEXT_Q[157];
    			link.l1.go = "Step_F6_17";			
			}
		break;
 		case "Step_F6_15":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159];
    		link.l1.go = "Step_F6_16";
			AddMoneyToCharacter(pchar, -150000);
		break;
 		case "Step_F6_16":
			chrDisableReloadToLocation = true;
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
				}
			}
			AddQuestRecord("Fra_Line_6_Olone", "5");
			pchar.questTemp.State = "Fr6Olone_OloneIsLive";
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], true);
            DialogExit();
		break;
 		case "Step_F6_17":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
    		link.l1.go = "Step_F6_18";
		break;
 		case "Step_F6_18":			
			dialog.text = DLG_TEXT_Q[162];
			link.l1 = DLG_TEXT_Q[163];
    		link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "6");
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));	
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
		break;
 		case "Step_F6_20":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
    		link.l1.go = "Step_F6_21";
		break;
 		case "Step_F6_21":
			NPChar.LifeDay = 0;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "8");
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("Captain_"+i)
				if (iTemp > 0)
				{				
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));	
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
//********************************* Маркиз Бонрепо. Квест №8 **********************************
 		case "Step_F8_1":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
    		link.l1.go = "Step_F8_2";
		break;
 		case "Step_F8_2":
			dialog.text = DLG_TEXT_Q[168]+
				          DLG_TEXT_Q[169];
			link.l1 = DLG_TEXT_Q[170];
    		link.l1.go = "Step_F8_3";
		break;
 		case "Step_F8_3":
			dialog.text = DLG_TEXT_Q[171]+
				          DLG_TEXT_Q[172]+
						  DLG_TEXT_Q[173];
			link.l1 = DLG_TEXT_Q[174];
    		link.l1.go = "Step_F8_4";
		break;
 		case "Step_F8_4":
			dialog.text = DLG_TEXT_Q[175]+
				          DLG_TEXT_Q[176];
			link.l1 = DLG_TEXT_Q[177];
    		link.l1.go = "Step_F8_5";
		break;
 		case "Step_F8_5":
			dialog.text = DLG_TEXT_Q[178];
			link.l1 = DLG_TEXT_Q[179];
    		link.l1.go = "Step_F8_6";
		break;
 		case "Step_F8_6":
			dialog.text = DLG_TEXT_Q[180];
			link.l1 = DLG_TEXT_Q[181];
    		link.l1.go = "Step_F8_Fight";
			link.l2 = DLG_TEXT_Q[182];
    		link.l2.go = "Step_F8_7";
		break;
 		case "Step_F8_Fight":
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            for (i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, "Sold_fra_"+(rand(7)+1), "man", "man", 30, FRANCE, 0, true));
				FantomMakeCoolFighter(sld, 30, 65, 50, BLADE_LONG, "pistol3", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
            }
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			NPChar.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "2");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
 		case "Step_F8_7":
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
    		link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "3");
			pchar.questTemp.State = "Fr8ThreeCorsairs_toSeek";
			SaveCurrentQuestDateParam("questTemp");
            // ==>  Помещаем Моргана на Антигуа и даем ноду доступа к квестам
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "FraLine8_talk");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  Генерим и помещаем Джона Морриса в Бриджтаун и даем ноду доступа к квестам
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name 	= DLG_TEXT_Q[185];
        	sld.lastname = DLG_TEXT_Q[186];
            sld.Dialog.Filename = "Quest\JohnMorris.c"; 
			sld.greeting = "Gr_HeadPirates";
           	LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
        	LAi_SetLoginTime(sld, 0.0, 24.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  Даем ноду доступа к квестам Джону Моррису
            QuestSetCurrentNode("John Morris", "FraLine8_talk");
            // ==>  Даем ноду доступа к квестам Джекмену
            QuestSetCurrentNode("Jackman", "FraLine8_talk");
            // ==>  Оформляем счетчик посещения корсаров, в итоге должен == 3
            pchar.questTemp.Count = "0";
		break;
 		case "Step_F8_9":
			dialog.text = DLG_TEXT_Q[187];
			link.l1 = DLG_TEXT_Q[188];
    		link.l1.go = "Step_F8_10";
		break;
 		case "Step_F8_10":
			dialog.text = DLG_TEXT_Q[189]+
				          DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
    		link.l1.go = "Step_F8_11";
		break;
 		case "Step_F8_11":
			pchar.questTemp.State = "Fr8ThreeCorsairs_backGovernor";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "8");
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 6.0);
			pchar.name = DLG_TEXT_Q[192] + pchar.name;
            DialogExit();
		break;
//********************************* Конец войне. Квест №12 **********************************
 		case "Step_F12_1":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
    		link.l1.go = "Step_F12_2";
		break;
 		case "Step_F12_2":
			dialog.text = DLG_TEXT_Q[195];
			link.l1 = DLG_TEXT_Q[196];
    		link.l1.go = "Step_F12_3";
		break;
 		case "Step_F12_3":
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
    		link.l1.go = "Step_F12_4";
		break;
 		case "Step_F12_4":
			dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
    		link.l1.go = "Step_F12_5";
		break;
 		case "Step_F12_5":
			dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
    		link.l1.go = "Step_F12_6";
		break;
 		case "Step_F12_6":
			dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
    		link.l1.go = "Step_F12_7";
		break;
 		case "Step_F12_7":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
    		link.l1.go = "Step_F12_8";
		break;
 		case "Step_F12_8":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
    		link.l1.go = "exit";
			npchar.LifeDay = 0;
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // Конец линейки
			AddQuestRecord("Fra_Line_12_EndOfWar", "2");
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			//==> в течение месяца Солей Руаяль можно взять себе.			
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			Group_SetType("SoleiRoyal", "war");
			Group_AddCharacter("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetGroupCommander("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetAddress("SoleiRoyal", "Guadeloupe", "Quest_ships", "quest_ship_1");
			SetTimerCondition("Fr12EndOfWar_TakeOutShip", 0, 0, 30, false);
			AddTitleNextRate(sti(NPChar.nation), 5);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//слухи
			AddSimpleRumour(DLG_TEXT_Q[209], sti(npchar.nation), 5, 1);
		break;
    }
}
