#include "TEXT\DIALOGS\Quest\Isabella\BrigCaptain.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
			dialog.text = DLG_TEXT_QB[0];
			link.l1 = DLG_TEXT_QB[1];
			link.l1.go = "ShipToDomingoTavenr_2";
			link.l2 = DLG_TEXT_QB[2];
			link.l2.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipToDomingoTavenr_2":
			dialog.text = DLG_TEXT_QB[3]+
				          DLG_TEXT_QB[4];
			link.l1 = DLG_TEXT_QB[5];
			link.l1.go = "ShipToDomingoTavenr_3";
		break;
		
		case "ShipToDomingoTavenr_3":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
			dialog.text = DLG_TEXT_QB[6];
			link.l1 = DLG_TEXT_QB[7];
			link.l1.go = "exit";
			Pchar.quest.Romantic_Brother.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother.win_condition.l1.location  = "Cumana_town";
        	Pchar.quest.Romantic_Brother.win_condition              = "Romantic_Brother";
        	Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
        	AddQuestRecord("Romantic_Line", "6");
			npchar.LifeDay = 2;
            SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ShipToDomingoTavenr_Temp":
            NextDiag.TempNode = "ShipToDomingoTavenr_Temp";
            dialog.text = DLG_TEXT_QB[8];
			link.l1 = DLG_TEXT_QB[9];
			link.l1.go = "exit";
		break;
		// братан Изабеллы
		case "Romantic_Brother_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = DLG_TEXT_QB[10]+GetFullName(Pchar)+DLG_TEXT_QB[11];
			link.l1 = DLG_TEXT_QB[12]+GetFullName(Pchar)+DLG_TEXT_QB[13];
			link.l1.go = "Step_1";
		break;
		case "Step_1":
			AddQuestRecord("Romantic_Line", "7");
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 40);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddPassenger(pchar, NPChar, false);
			SetCharacterRemovable(NPChar, false);
            Pchar.quest.Romantic_Brother_port.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_port.win_condition.l1.location  = "SanJuan_town";
        	Pchar.quest.Romantic_Brother_port.win_condition              = "Romantic_Brother_port";
            // немного веселой жизни
            TraderHunterOnMap();
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false; 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_2":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = DLG_TEXT_QB[14];
			link.l1 = DLG_TEXT_QB[15];
			link.l1.go = "exit";
		break;
		
		case "Romantic_Brother_port_1":
            NextDiag.TempNode = "Romantic_Brother_2";
            dialog.text = DLG_TEXT_QB[16];
			link.l1 = DLG_TEXT_QB[17];
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			RemovePassenger(pchar, NPChar);
            Pchar.quest.Romantic_Brother_House.win_condition.l1           = "location";
        	Pchar.quest.Romantic_Brother_House.win_condition.l1.location  = "SanJuan_houseSp6";
        	Pchar.quest.Romantic_Brother_House.win_condition              = "Romantic_Brother_House";
            chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "", "goto", "goto4", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Romantic_Brother_Thanks":
            NextDiag.TempNode = "Romantic_Brother_Thanks";
            dialog.text = DLG_TEXT_QB[18];
			link.l1 = DLG_TEXT_QB[19];
			link.l1.go = "Step_3";
		break;
		case "Step_3":
            dialog.text = DLG_TEXT_QB[20];
			link.l1 = DLG_TEXT_QB[21];
			link.l1.go = "exit";
		break;
		//разборки Сальватора с братом
		case "TalkNearHouse_1":
            dialog.text = DLG_TEXT_QB[22];
			link.l1 = DLG_TEXT_QB[23];
			link.l1.go = "TalkNearHouse_2";
		break;
		case "TalkNearHouse_2":
            dialog.text = DLG_TEXT_QB[24];
			link.l1 = DLG_TEXT_QB[25];
			link.l1.go = "TalkNearHouse_3";
		break;
		case "TalkNearHouse_3":		
			DialogExit();
			AddDialogExitQuest("Romantic_DeadBrother_1");
		break;
		//офицер в доме Сальватора при аресте
		case "ArrestInHome_2":
			ref rColony = GetColonyByIndex(FindColony("SanJuan"));
			if (sti(rColony.HeroOwn))
			{
				dialog.text = DLG_TEXT_QB[26];
				link.l1 = DLG_TEXT_QB[27];
				link.l1.go = "ArrestInHome_5";
			}
			else
			{
				dialog.text = DLG_TEXT_QB[28] + GetFullName(pchar) + DLG_TEXT_QB[29];
				link.l1 = DLG_TEXT_QB[30];
				link.l1.go = "ArrestInHome_3";
			}
		break;
		case "ArrestInHome_3":
			dialog.text = DLG_TEXT_QB[31];
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = DLG_TEXT_QB[32];
				link.l1.go = "ArrestInHome_Have";				
			}
			else
			{
				link.l1 = DLG_TEXT_QB[33];
				link.l1.go = "ArrestInHome_NotHave";
			}
		break;
		case "ArrestInHome_Have":
			dialog.text = DLG_TEXT_QB[34];
			link.l1 = DLG_TEXT_QB[35];
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = DLG_TEXT_QB[36];
			link.l1 = DLG_TEXT_QB[37];
			link.l1.go = "FightInHouse";
		break;

		case "ArrestInHome_NotHave":
			dialog.text = DLG_TEXT_QB[38];
			link.l1 = DLG_TEXT_QB[39];
			link.l1.go = "ArrestInHome_4";
		break;
		case "ArrestInHome_4":
			dialog.text = DLG_TEXT_QB[40];
			link.l1 = DLG_TEXT_QB[41];
			link.l1.go = "FightInHouse";
		break;

		case "FightInHouse":
			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], false);
			AddQuestRecord("Romantic_Line", "10");
		break;

		case "ArrestInHome_5":
			dialog.text = DLG_TEXT_QB[42];
			link.l1 = DLG_TEXT_QB[43];
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "31");
		break;
		//засада в доме Сальватора, диалог с наемным убийцей
		case "AmbushBandit":
			dialog.text = DLG_TEXT_QB[44];
			link.l1 = DLG_TEXT_QB[45];
			link.l1.go = "AmbushBandit_1";
		break;
		case "AmbushBandit_1":
			dialog.text = DLG_TEXT_QB[46];
			link.l1 = DLG_TEXT_QB[47];
			link.l1.go = "AmbushBandit_fight";
		break;
		case "AmbushBandit_fight":
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Romantic_Line", "12");
		break;
		//абордаж брига, где Изабеллу типа держат
		case "BrigAbordage":
			dialog.text = DLG_TEXT_QB[48];
			link.l1 = DLG_TEXT_QB[49];
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
			dialog.text = DLG_TEXT_QB[50];
			link.l1 = DLG_TEXT_QB[51];
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
			dialog.text = DLG_TEXT_QB[52];
			link.l1 = DLG_TEXT_QB[53];
			link.l1.go = "BrigAbordage_3";
		break;
		case "BrigAbordage_3":
			dialog.text = DLG_TEXT_QB[54];
			link.l1 = DLG_TEXT_QB[55];
			link.l1.go = "BrigAbordage_4";
		break;
  		case "BrigAbordage_4":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("Romantic_TaklInCabinBrig");            
            pchar.quest.Romantic_BrigDieHard.over = "yes";
			pchar.quest.Romantic_AfterBrigSunk.over = "yes";
            Island_SetReloadEnableGlobal("PortoBello", true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//засада в Порто Белло
		case "AmbushPotroBello":
			dialog.text = DLG_TEXT_QB[56];
			link.l1 = DLG_TEXT_QB[57];
			link.l1.go = "AmbushPotroBello_1";
		break;
		case "AmbushPotroBello_1":
			dialog.text = DLG_TEXT_QB[58];
			link.l1 = DLG_TEXT_QB[59];
			link.l1.go = "AmbushPotroBello_2";
		break;
		case "AmbushPotroBello_2":
			dialog.text = DLG_TEXT_QB[60];
			link.l1 = DLG_TEXT_QB[61];
			link.l1.go = "AmbushPotroBello_3";
		break;
		case "AmbushPotroBello_3":
			dialog.text = DLG_TEXT_QB[62];
			link.l1 = DLG_TEXT_QB[63];
			link.l1.go = "AmbushPotroBello_4";
		break;
		case "AmbushPotroBello_4":
			dialog.text = DLG_TEXT_QB[64];
			link.l1 = DLG_TEXT_QB[65];
			link.l1.go = "AmbushPotroBello_5";
		break;
		case "AmbushPotroBello_5":
			dialog.text = DLG_TEXT_QB[66];
			link.l1 = DLG_TEXT_QB[67];
			link.l1.go = "AmbushPotroBello_6";
		break;
		case "AmbushPotroBello_6":
			dialog.text = DLG_TEXT_QB[68];
			link.l1 = DLG_TEXT_QB[69];
			link.l1.go = "AmbushPotroBello_7";
		break;
		case "AmbushPotroBello_7":
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], false);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Romantic_TalkPortoBello");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//доставка Изабеллы Росите в Белиз
		case "Rosita":
			dialog.text = DLG_TEXT_QB[70];
			link.l1 = DLG_TEXT_QB[71] + GetFullName(pchar) + DLG_TEXT_QB[72];
			link.l1.go = "Rosita_1";
		break;
		case "Rosita_1":
			dialog.text = DLG_TEXT_QB[73];
			link.l1 = DLG_TEXT_QB[74];
			link.l1.go = "Rosita_2";
		break;
		case "Rosita_2":
			dialog.text = DLG_TEXT_QB[75];
			link.l1 = DLG_TEXT_QB[76];
			link.l1.go = "Rosita_3";
		break;
		case "Rosita_3":
			dialog.text = DLG_TEXT_QB[77];
			link.l1 = DLG_TEXT_QB[78];
			link.l1.go = "Rosita_4";
		break;
		case "Rosita_4":
			dialog.text = DLG_TEXT_QB[79];
			link.l1 = DLG_TEXT_QB[80];
			link.l1.go = "Rosita_5";
		break;
		case "Rosita_5":
			dialog.text = DLG_TEXT_QB[81];
			link.l1 = DLG_TEXT_QB[82];
			link.l1.go = "Rosita_6";
		break;
		case "Rosita_6":
			dialog.text = DLG_TEXT_QB[83] + pchar.name + DLG_TEXT_QB[84];
			link.l1 = DLG_TEXT_QB[85];
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1 = "location";
            Pchar.quest.Romantic_BelizCityTalk.win_condition.l1.location = "Beliz_town";
            Pchar.quest.Romantic_BelizCityTalk.win_condition = "Romantic_BelizCityTalk";
			//снимем прерывания на засады на всякий случай
			pchar.quest.Romantic_AmbushInHouse.over = "yes";
			pchar.quest.Romantic_AmbushInPortoBello.over = "yes";
		break;
		case "Rosita_after":
			dialog.text = DLG_TEXT_QB[86] + GetFullName(pchar) + DLG_TEXT_QB[87];
			link.l1 = DLG_TEXT_QB[88];
			link.l1.go = "exit";
			NextDiag.TempNode = "Rosita_after";
		break;
		//Росита переживает, что Изабелла пропала
		case "BackRosita":
			dialog.text = DLG_TEXT_QB[89] + pchar.name + DLG_TEXT_QB[90];
			link.l1 = DLG_TEXT_QB[91];
			link.l1.go = "BackRosita_1";
		break;
		case "BackRosita_1":
			dialog.text = DLG_TEXT_QB[92];
			link.l1 = DLG_TEXT_QB[93];
			link.l1.go = "BackRosita_2";
		break;
		case "BackRosita_2":
			dialog.text = DLG_TEXT_QB[94];
			link.l1 = DLG_TEXT_QB[95];
			link.l1.go = "BackRosita_3";
		break;
		case "BackRosita_3":
			dialog.text = DLG_TEXT_QB[96];
			link.l1 = DLG_TEXT_QB[97];
			link.l1.go = "exit";
			NextDiag.TempNode = "BackRosita_after";
			pchar.RomanticQuest = "SeekIsabella";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1 = "locator";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator_group = "quest";
			pchar.quest.SeekIsabella_exitTown.win_condition.l1.locator = "detector1";
			pchar.quest.SeekIsabella_exitTown.function = "SeekIsabella_exitTown";		
			AddQuestRecord("Romantic_Line", "21");
			//миортвая служанка
			sld = GetCharacter(NPC_GenerateCharacter("ServantGirl", "girl_6", "woman", "towngirl", 5, SPAIN, 30, false));
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_ExitTown", "goto", "goto17");
			locations[FindLocation("Beliz_ExitTown")].DisableEncounters = true; //энкаутеры запретим
			//охранник Изабеллы в шахте
            sld = GetCharacter(NPC_GenerateCharacter("Bandit", "officer_6", "man", "man", 35, PIRATE, -1, true));
            FantomMakeCoolFighter(sld, 35, 85, 75, "topor2", "pistol3", 60);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto4");
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", true); //офицеров не пускать
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", true); //монстров не генерить
			pchar.quest.Romantic_BanditIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Romantic_BanditIsDead.win_condition.l1.character = "Bandit";
			pchar.quest.Romantic_BanditIsDead.win_condition = "Romantic_BanditIsDead";
		break;
		case "BackRosita_after":
			dialog.text = DLG_TEXT_QB[98];
			link.l1 = DLG_TEXT_QB[99];
			link.l1.go = "exit";
		break;
		//если Изабелла погибла где-нить при похищении
		case "IsabellaIsDead_Beliz":
			dialog.text = DLG_TEXT_QB[100];
			link.l1 = DLG_TEXT_QB[101];
			link.l1.go = "IsabellaIsDead_Beliz_1";
			NextDiag.TempNode = "IsabellaIsDead_Beliz_after";
		break;
		case "IsabellaIsDead_Beliz_1":
			dialog.text = DLG_TEXT_QB[102];
			link.l1 = DLG_TEXT_QB[103];
			link.l1.go = "exit";
		break;
		case "IsabellaIsDead_Beliz_after":
			dialog.text = DLG_TEXT_QB[104];
			link.l1 = DLG_TEXT_QB[105];
			link.l1.go = "exit";
		break;
		//после спасения Изабеллы в пещере
		case "SavedIsabella":
			dialog.text = DLG_TEXT_QB[106];
			link.l1 = DLG_TEXT_QB[107];
			link.l1.go = "SavedIsabella_1";
		break;
		case "SavedIsabella_1":
			dialog.text = DLG_TEXT_QB[108];
			link.l1 = DLG_TEXT_QB[109];
			link.l1.go = "SavedIsabella_2";
		break;
		case "SavedIsabella_2":
			dialog.text = DLG_TEXT_QB[110];
			link.l1 = DLG_TEXT_QB[111];
			link.l1.go = "SavedIsabella_3";
		break;
		case "SavedIsabella_3":
			dialog.text = DLG_TEXT_QB[112];
			link.l1 = DLG_TEXT_QB[113];
			link.l1.go = "SavedIsabella_4";
		break;
		case "SavedIsabella_4":
			dialog.text = DLG_TEXT_QB[114];
			link.l1 = DLG_TEXT_QB[115];
			link.l1.go = "SavedIsabella_5";
		break;
		case "SavedIsabella_5":
			dialog.text = DLG_TEXT_QB[116];
			link.l1 = DLG_TEXT_QB[117];
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";			
			AddDialogExitQuest("Romantic_DelivToRosita_2");
		break;
		case "SavedIsabella_after":
			dialog.text = DLG_TEXT_QB[118];
			link.l1 = DLG_TEXT_QB[119];
			link.l1.go = "exit";
			NextDiag.TempNode = "SavedIsabella_after";
		break;
		//Нападения на ГГ и Изабеллу в церкви
		case "AmbushInChurch":
			dialog.text = DLG_TEXT_QB[120];
			link.l1 = DLG_TEXT_QB[121];
			link.l1.go = "AmbushInChurch_1";
		break;
		case "AmbushInChurch_1":
			dialog.text = DLG_TEXT_QB[122];
			link.l1 = DLG_TEXT_QB[123];
			link.l1.go = "AmbushInChurch_2";
		break;
		case "AmbushInChurch_2":
			dialog.text = DLG_TEXT_QB[124];
			link.l1 = DLG_TEXT_QB[125];
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_1");
		break;
		//базар с Роситой после убийства Изабеллы
		case "IsabellaIsDead":
			dialog.text = DLG_TEXT_QB[126] + GetFullName(pchar) + DLG_TEXT_QB[127];
			link.l1 = DLG_TEXT_QB[128];
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = DLG_TEXT_QB[129]+
				          DLG_TEXT_QB[130];
			link.l1 = DLG_TEXT_QB[131];
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = DLG_TEXT_QB[132];
			link.l1 = DLG_TEXT_QB[133];
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		case "IsabellaIsDead_after":
			dialog.text = DLG_TEXT_QB[134];
			link.l1 = DLG_TEXT_QB[135];
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
		break;
		//базар с Роситой, если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = DLG_TEXT_QB[136] + pchar.name + DLG_TEXT_QB[137];
			link.l1 = DLG_TEXT_QB[138];
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = DLG_TEXT_QB[139];
			link.l1 = DLG_TEXT_QB[140];
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = DLG_TEXT_QB[141] + pchar.name + DLG_TEXT_QB[142];
			link.l1 = DLG_TEXT_QB[143];
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = DLG_TEXT_QB[144] + pchar.name + "!";
			link.l1 = DLG_TEXT_QB[145];
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		//семейная жизнь ГГ
		case "IsabellaIsWife":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[146], 
				DLG_TEXT_QB[147], 
				DLG_TEXT_QB[148], 
				DLG_TEXT_QB[149], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[150], 
				DLG_TEXT_QB[151], 
				DLG_TEXT_QB[152], 
				DLG_TEXT_QB[153], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("IsabellaIsWife_1", "none", "none", "none", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "IsabellaIsWife";
		break;
		case "IsabellaIsWife_1":
			dialog.text = DLG_TEXT_QB[154];
			link.l1 = DLG_TEXT_QB[155];
			link.l1.go = "exit";				
			if (pchar.RomanticQuest == "over")
			{
				link.l2 = DLG_TEXT_QB[156];
				link.l2.go = "HorseCheck";	
				break;
			}			
			if (pchar.RomanticQuest == "TheDoosIsClosed")
			{
				link.l2 = DLG_TEXT_QB[157];
				link.l2.go = "TheDoosIsClosed";			
			}
			sld = characterFromID("Isabella");
			if (CheckAttribute(sld, "angry")) //если Изабелла сидит на ангри
			{
				if (sld.angry.name == "NewLife_Budget_Pay")
				{
					link.l3 = DLG_TEXT_QB[158];
					link.l3.go = "Budget";			
				}
				if (sld.angry.name == "NewLife_KnowPirates")
				{
					link.l4 = DLG_TEXT_QB[159];
					link.l4.go = "KnowPirates";			
				}
				if (sld.angry.name == "NewLife_Present")
				{
					link.l5 = DLG_TEXT_QB[160];
					link.l5.go = "Present";			
				}
			}
		break;
		case "TheDoosIsClosed":
			dialog.text = DLG_TEXT_QB[161];
			link.l1 = DLG_TEXT_QB[162];
			link.l1.go = "TheDoosIsClosed_1";	
		break;
		case "TheDoosIsClosed_1":
			dialog.text = DLG_TEXT_QB[163];
			link.l1 = DLG_TEXT_QB[164];
			link.l1.go = "TheDoosIsClosed_2";	
		break;
		case "TheDoosIsClosed_2":
			dialog.text = DLG_TEXT_QB[165] + pchar.name + DLG_TEXT_QB[166];
			link.l1 = DLG_TEXT_QB[167];
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "30");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			pchar.RomanticQuest = "OpenTheDoosOfHouse";
		break;

		case "Budget":
			dialog.text = DLG_TEXT_QB[168];
			link.l1 = DLG_TEXT_QB[169];
			link.l1.go = "Budget_1";	
		break;
		case "Budget_1":
			dialog.text = DLG_TEXT_QB[170];
			link.l1 = DLG_TEXT_QB[171];
			link.l1.go = "exit";	
		break;

		case "KnowPirates":
			dialog.text = DLG_TEXT_QB[172];
			link.l1 = DLG_TEXT_QB[173];
			link.l1.go = "KnowPirates_1";	
		break;
		case "KnowPirates_1":
			dialog.text = DLG_TEXT_QB[174];
			link.l1 = DLG_TEXT_QB[175];
			link.l1.go = "KnowPirates_2";	
		break;
		case "KnowPirates_2":
			dialog.text = DLG_TEXT_QB[176];
			link.l1 = DLG_TEXT_QB[177];
			link.l1.go = "KnowPirates_3";	
		break;
		case "KnowPirates_3":
			dialog.text = DLG_TEXT_QB[178];
			link.l1 = DLG_TEXT_QB[179];
			link.l1.go = "exit";	
		break;

		case "Present":
			dialog.text = DLG_TEXT_QB[180];
			link.l1 = DLG_TEXT_QB[181];
			link.l1.go = "Present_1";	
		break;
		case "Present_1":
			dialog.text = DLG_TEXT_QB[182];
			link.l1 = DLG_TEXT_QB[183];
			link.l1.go = "Present_2";	
		break;
		case "Present_2":
			dialog.text = DLG_TEXT_QB[184];
			link.l1 = DLG_TEXT_QB[185];
			link.l1.go = "Present_3";	
		break;
		case "Present_3":
			dialog.text = DLG_TEXT_QB[186];
			link.l1 = DLG_TEXT_QB[187];
			link.l1.go = "exit";	
		break;

		case "HorseCheck":
			dialog.text = DLG_TEXT_QB[188];
			link.l1 = DLG_TEXT_QB[189];
			link.l1.go = "HorseCheck_1";	
		break;
		case "HorseCheck_1":
			dialog.text = DLG_TEXT_QB[190];
			link.l1 = DLG_TEXT_QB[191];
			link.l1.go = "HorseCheck_2";	
		break;
		case "HorseCheck_2":
			dialog.text = DLG_TEXT_QB[192];
			link.l1 = DLG_TEXT_QB[193];
			link.l1.go = "HorseCheck_3";	
		break;
		case "HorseCheck_3":
			dialog.text = DLG_TEXT_QB[194];
			link.l1 = DLG_TEXT_QB[195];
			link.l1.go = "HorseCheck_4";	
		break;
		case "HorseCheck_4":
			dialog.text = DLG_TEXT_QB[196];
			link.l1 = DLG_TEXT_QB[197];
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "HorseCheck_Bue";
			CloseQuestHeader("Romantic_Line");
		break;
		case "HorseCheck_Bue":
			dialog.text = DLG_TEXT_QB[198];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "HorseCheck_Bue";
		break;
	}
}
