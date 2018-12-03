#include "TEXT\DIALOGS\Quest\ForAll_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//--------------------------- линейка ГПК --------------------------------
		//заказчик устранения всех нищих
		case "Begin_PoorKill":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "Begin_PoorKill_1";
		break;

		case "Begin_PoorKill_close":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterReputation(pchar, 10);
			pchar.questTemp.LSC = "PoorIsGood";
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "12");
		break;

		case "Begin_PoorKill_1":
			dialog.text = DLG_TEXT_Q[5];
			link.l1 = DLG_TEXT_Q[6];
			link.l1.go = "Begin_PoorKill_2";
		break;
		case "Begin_PoorKill_2":
			dialog.text = DLG_TEXT_Q[7] + GetFullName(npchar) + DLG_TEXT_Q[8] + GetFullName(pchar) + DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "Begin_PoorKill_3";
		break;
		case "Begin_PoorKill_3":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "Begin_PoorKill_4";
		break;
		case "Begin_PoorKill_4":
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "Begin_PoorKill_5";
		break;
		case "Begin_PoorKill_5":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "Begin_PoorKill_6";
		break;
		case "Begin_PoorKill_6":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "Begin_PoorKill_7";
			link.l2 = DLG_TEXT_Q[19];
			link.l2.go = "Begin_PoorKill_close";
		break;
		case "Begin_PoorKill_7":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "Begin_PoorKill_8";
		break;
		case "Begin_PoorKill_8":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "Begin_PoorKill_9";
		break;
		case "Begin_PoorKill_9":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "Begin_PoorKill_10";
		break;
		case "Begin_PoorKill_10":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "Begin_PoorKill_11";
		break;
		case "Begin_PoorKill_11":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = DLG_TEXT_Q[29];
			link.l1.go = "Begin_PoorKill_12";
		break;
		case "Begin_PoorKill_12":
			dialog.text = DLG_TEXT_Q[30];
			link.l1 = DLG_TEXT_Q[31];
			link.l1.go = "Begin_PoorKill_13";
		break;
		case "Begin_PoorKill_13":
			dialog.text = DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "Begin_PoorKill_14";
		break;
		case "Begin_PoorKill_14":
			SetQuestHeader("ISS_PoorsMurder");
			AddQuestRecord("ISS_PoorsMurder", "1");
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			pchar.quest.ISS_Murder1.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder1.win_condition.l1.character = "SentJons_Poorman";
			pchar.quest.ISS_Murder1.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder2.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder2.win_condition.l1.character = "Bridgetown_Poorman";
			pchar.quest.ISS_Murder2.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder3.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder3.win_condition.l1.character = "Beliz_Poorman";
			pchar.quest.ISS_Murder3.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder4.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder4.win_condition.l1.character = "Caracas_Poorman";
			pchar.quest.ISS_Murder4.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder5.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder5.win_condition.l1.character = "Cartahena_Poorman";
			pchar.quest.ISS_Murder5.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder6.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder6.win_condition.l1.character = "Cumana_Poorman";
			pchar.quest.ISS_Murder6.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder7.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder7.win_condition.l1.character = "BasTer_Poorman";
			pchar.quest.ISS_Murder7.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder8.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder8.win_condition.l1.character = "Havana_Poorman";
			pchar.quest.ISS_Murder8.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder9.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder9.win_condition.l1.character = "PortRoyal_Poorman";
			pchar.quest.ISS_Murder9.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder10.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder10.win_condition.l1.character = "FortFrance_Poorman";
			pchar.quest.ISS_Murder10.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder11.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder11.win_condition.l1.character = "Charles_Poorman";
			pchar.quest.ISS_Murder11.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder12.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder12.win_condition.l1.character = "PortoBello_Poorman";
			pchar.quest.ISS_Murder12.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder13.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder13.win_condition.l1.character = "PortPax_Poorman";
			pchar.quest.ISS_Murder13.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder14.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder14.win_condition.l1.character = "Santiago_Poorman";
			pchar.quest.ISS_Murder14.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder15.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder15.win_condition.l1.character = "Marigo_Poorman";
			pchar.quest.ISS_Murder15.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder16.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder16.win_condition.l1.character = "Tortuga_Poorman";
			pchar.quest.ISS_Murder16.function = "ISS_MurderSignExecute";
			pchar.quest.ISS_Murder17.win_condition.l1 = "NPC_Death";
			pchar.quest.ISS_Murder17.win_condition.l1.character = "PortSpein_Poorman";
			pchar.quest.ISS_Murder17.function = "ISS_MurderSignExecute";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "SignOnPoorMurder";
			pchar.questTemp.LSC.killCost = 17; //счетчик убитых нищих на декремент
			pchar.questTemp.LSC.usurerId = npchar.city + "_usurer"; //флаг на депозит у ростовщика
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "gate_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//воришка ключа 
		case "GiveKeyMan":
			dialog.text = DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "GiveKeyMan_1";
		break;
		case "GiveKeyMan_1":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37] + GetFullName(pchar) + ".";
			link.l1.go = "GiveKeyMan_2";
		break;
		case "GiveKeyMan_2":
			dialog.text = DLG_TEXT_Q[38] + GetFullName(pchar) + "?";
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "GiveKeyMan_3";
		break;
		case "GiveKeyMan_3":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "GiveKeyMan_4";
		break;
		case "GiveKeyMan_4":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "GiveKeyMan_5";
		break;
		case "GiveKeyMan_5":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "GiveKeyMan_6";
		break;
		case "GiveKeyMan_6":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "GiveKeyMan_7";
		break;
		case "GiveKeyMan_7":
			npchar.quest.price = makeint((sti(pchar.money)/4*3)/1000)*1000;
			if (sti(npchar.quest.price) > 10000)
			{
				dialog.text = DLG_TEXT_Q[48] + FindRussianMoneyString(sti(npchar.quest.price)) + ".";
				link.l1 = DLG_TEXT_Q[49];
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[50];
				link.l1 = DLG_TEXT_Q[51];
				link.l1.go = "GiveKeyMan_8";
			}
		break;
		case "GiveKeyMan_8":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeysNoMoney";
			NextDiag.TempNode = "GiveKeyMan_NoMoney";
		break;
		case "GiveKeyMan_NoMoney":
			if (sti(pchar.money) >= 20000)
			{
				npchar.quest.price = makeint((sti(pchar.money)/5*4)/1000)*1000;
				dialog.text = DLG_TEXT_Q[54] + FindRussianMoneyString(sti(npchar.quest.price)) + ".";
				link.l1 = DLG_TEXT_Q[55];
				link.l1.go = "GiveKeyMan_10";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[56];
				link.l1 = DLG_TEXT_Q[57];
				link.l1.go = "exit";
			}
		break;
		case "GiveKeyMan_10":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "GiveKeyMan_11";
		break;
		case "GiveKeyMan_11":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "GiveKeyMan_12";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
		break;
		case "GiveKeyMan_12":
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "exit";
			SetTimerFunction("LSC_openMasterHouse", 0, 0, 2);
			LocatorReloadEnterDisable("Villemstad_town", "houseSp5", true);
			npchar.location = "none";
			AddQuestRecord("ISS_PoorsMurder", "6");
		break;

		case "GiveKeyManInside":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "GiveKeyManInside_1";
		break;
		case "GiveKeyManInside_1":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "GiveKeyManInside_2";
		break;
		case "GiveKeyManInside_2":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "GiveKeyManInside_3";
		break;
		case "GiveKeyManInside_3":
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("LSC_enterSoldiers");			
		break;
		//арестовывающий офицер
		case "MK_HollOfficer":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "MK_HollOfficer_1";
		break;
		case "MK_HollOfficer_1":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "MK_HollOfficer_2";
		break;
		case "MK_HollOfficer_2":
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//заказчик нищих в Мариго
		case "PKInMarigo":
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "PKInMarigo_1";
		break;
		case "PKInMarigo_1":
			dialog.text = DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
			link.l1.go = "PKInMarigo_2";
		break;
		case "PKInMarigo_2":
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "PKInMarigo_3";
		break;
		case "PKInMarigo_3":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "PKInMarigo_4";
		break;
		case "PKInMarigo_4":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "PKInMarigo_5";
		break;
		case "PKInMarigo_5":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "PKInMarigo_6";
		break;
		case "PKInMarigo_6":
			dialog.text = DLG_TEXT_Q[88]+
				DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "PKInMarigo_7";
		break;
		case "PKInMarigo_7":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "PKInMarigo_8";
		break;
		case "PKInMarigo_8":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "PKInMarigo_9";
		break;
		case "PKInMarigo_9":
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_Attack(npchar, pchar);
			pchar.quest.PQ8_afterFight.win_condition.l1 = "NPC_Death";
			pchar.quest.PQ8_afterFight.win_condition.l1.character = "PoorKillSponsor";
			pchar.quest.PQ8_afterFight.win_condition = "OpenTheDoors";
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//мент в Протекторе
		case "LSCQuestMent":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "LSCQuestMent_1";
		break;
		case "LSCQuestMent_1":
			dialog.text = DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "LSCQuestMent_2";
		break;
		case "LSCQuestMent_2":
			dialog.text = DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "LSCQuestMent_3";
		break;
		case "LSCQuestMent_3":
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "LSCQuestMent_4";
		break;
		case "LSCQuestMent_4":
			AddQuestRecord("ISS_MainLine", "9");
			pchar.questTemp.LSC = "afterFightInProtector";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = characterFromId("AndreLabor");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//одиночный нарвал, которого надо замочить
		case "LSCQuestNarval":
			dialog.text = DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "LSCQuestNarval_1";
		break;
		case "LSCQuestNarval_1":
			dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "LSCQuestNarval_2";
		break;
		case "LSCQuestNarval_2":
			dialog.text = DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108];
			link.l1.go = "LSCQuestNarval_3";
		break;
		case "LSCQuestNarval_3":
			AddQuestRecord("ISS_MainLine", "11");
			pchar.questTemp.LSC = "toAdmNarvalRing";
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_1";
		break;
		case "_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_2";
		break;
		case "_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_3";
		break;
		case "_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_5";
		break;

		//--------------------------- дача шебеки Синяя Птица --------------------------------
		//капитан шебеки Синяя Птица
		case "BlueBirdCapitain":
			dialog.text = DLG_TEXT_Q[109];
			link.l1 = DLG_TEXT_Q[110] + GetFullName(pchar) + DLG_TEXT_Q[111];
			link.l1.go = "BlueBirdCapitain_1";
		break;
		case "BlueBirdCapitain_1":
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "BlueBirdCapitain_2";
		break;
		case "BlueBirdCapitain_2":
			dialog.text = DLG_TEXT_Q[114];
			link.l1 = DLG_TEXT_Q[115];
			link.l1.go = "BlueBirdCapitain_3";
		break;
		case "BlueBirdCapitain_3":
			dialog.text = DLG_TEXT_Q[116];
			link.l1 = DLG_TEXT_Q[117];
			link.l1.go = "BlueBirdCapitain_4";
		break;		
		case "BlueBirdCapitain_4":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		//капитаны флейтов торговцев
		case "BlueBirdTrader":
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "BlueBirdTrader_1";
		break;
		case "BlueBirdTrader_1":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121] + GetFullName(pchar) + DLG_TEXT_Q[122];
			link.l1.go = "BlueBirdTrader_2";
		break;
		case "BlueBirdTrader_2":
			dialog.text = DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "BlueBirdTrader_3";
		break;
		case "BlueBirdTrader_3":
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
		//--------------------------- жемчужный промысел, Шарп --------------------------------
		//капитан Шарп, первый базар на палубе
		case "DeckSharp":	//на палубе
			dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "DeckSharp_1";
			npchar.quest.meeting = true;
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = DLG_TEXT_Q[127];
				link.l1 = DLG_TEXT_Q[128];
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "DeckSharp_1":
			dialog.text = DLG_TEXT_Q[129];
			link.l1 = DLG_TEXT_Q[130];
			link.l1.go = "DeckSharp_2";
		break;
		case "DeckSharp_2":
			dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "DeckSharp_3";
		break;
		case "DeckSharp_3":
			dialog.text = DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "DeckSharp_4";
		break;
		case "DeckSharp_4":
			dialog.text = DLG_TEXT_Q[135];
			link.l1 = DLG_TEXT_Q[136];
			link.l1.go = "DeckSharp_5";
		break;		
		case "DeckSharp_5":
			dialog.text = DLG_TEXT_Q[137];
			link.l1 = DLG_TEXT_Q[138];
			link.l1.go = "DeckSharp_6";
		break;
		case "DeckSharp_6":
			GetPerlShore(); //где промысел ведется
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add; 
			dialog.text = DLG_TEXT_Q[139] + XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Dat") + DLG_TEXT_Q[140] + GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") +
				sTemp + DLG_TEXT_Q[141] + FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)) + DLG_TEXT_Q[142];
			link.l1 = DLG_TEXT_Q[143];
			link.l1.go = "DeckSharp_7";
		break;
		case "DeckSharp_7":
			dialog.text = RandPhraseSimple(DLG_TEXT_Q[144], DLG_TEXT_Q[145]);
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "DeckSharp_8";
		break;
		case "DeckSharp_8":
			dialog.text = RandPhraseSimple(DLG_TEXT_Q[147], DLG_TEXT_Q[148]);
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "DeckSharp_8exit";
		break;	
		case "DeckSharp_8exit":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.add")) sTemp = pchar.questTemp.Sharp.PearlAreal.add; 
			NextDiag.TempNode = "DeckSharp_over";
			npchar.DeckDialogNode = "NewDeckSharp"; //новая нода на палубу
			pchar.questTemp.Sharp = "toPearl"; //флаг квеста - на промысел!!!
			AddQuestRecord("SharpPearl", "5");
			AddQuestUserData("SharpPearl", "iDay", FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
			AddQuestUserData("SharpPearl", "sAreal", XI_ConvertString(pchar.questTemp.Sharp.PearlAreal + "Dat"));
			AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt") + sTemp);
			pchar.quest.SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.SeaPearl_login.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
			pchar.quest.SeaPearl_login.function = "SeaPearl_login";
			SetTimerFunction("SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//капитан Шарп, последующие разговоры на палубе
		case "NewDeckSharp":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "NewDeckSharp_1";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = DLG_TEXT_Q[152];
				link.l1 = DLG_TEXT_Q[153];
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "NewDeckSharp_1":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "NewDeckSharp_2";
		break;
		case "NewDeckSharp_2":
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow" || pchar.questTemp.Sharp.SeekSpy == "over")
			{
				dialog.text = DLG_TEXT_Q[156];
				link.l1 = DLG_TEXT_Q[157];
				link.l1.go = "exit";
				CloseQuestHeader("SharpPearl");
				NextDiag.TempNode = "DeckSharp_noWork";
				pchar.questTemp.Sharp = "over";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[158];
				link.l1 = DLG_TEXT_Q[159];
				link.l1.go = "NewDeckSharp_3";
			}
		break;
		case "NewDeckSharp_3":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
			link.l1.go = "NewDeckSharp_4";
		break;
		case "NewDeckSharp_4":
			dialog.text = DLG_TEXT_Q[162] + FindRussianMoneyString(sti(pchar.questTemp.Sharp.price)) + DLG_TEXT_Q[163];
			link.l1 = DLG_TEXT_Q[164];
			link.l1.go = "NewDeckSharp_noMoney";
			if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
			{
				link.l2 = DLG_TEXT_Q[165];
				link.l2.go = "NewDeckSharp_GiveMoney";
			}
		break;

		case "NewDeckSharp_GiveMoney":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_noMoney":
			if ((sti(pchar.questTemp.Sharp.price)*10) < sti(pchar.money))
			{
				if (pchar.location == "Deck_Near_Ship")
				{			
					dialog.text = DLG_TEXT_Q[168] + pchar.name + DLG_TEXT_Q[169];
					link.l1 = DLG_TEXT_Q[170];
				}
				else
				{
					dialog.text = DLG_TEXT_Q[171];
					link.l1 = DLG_TEXT_Q[172];
				}
				link.l1.go = "NewDeckSharp_5";
			}
			else
			{
				if (sti(pchar.questTemp.Sharp.price.evil))
				{	//Шарп не в настроении
					dialog.text = DLG_TEXT_Q[173];
					link.l1 = DLG_TEXT_Q[174];
					link.l1.go = "NewDeckSharp_7";
					if (sti(pchar.money) >= sti(pchar.questTemp.Sharp.price))
					{
						link.l2 = DLG_TEXT_Q[175];
						link.l2.go = "NewDeckSharp_GiveMoney";
					}
				}
				else
				{
					dialog.text = DLG_TEXT_Q[176];
					link.l1 = DLG_TEXT_Q[177];
					link.l1.go = "DeckSharp_6";
				}
			}
		break;
		case "NewDeckSharp_5":
			dialog.text = DLG_TEXT_Q[178] + pchar.name + DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "NewDeckSharp_6";
			link.l2 = DLG_TEXT_Q[181];
			link.l2.go = "NewDeckSharp_7";
		break;
		case "NewDeckSharp_6":
			dialog.text = DLG_TEXT_Q[182];
			link.l1 = DLG_TEXT_Q[183];
			link.l1.go = "DeckSharp_6";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharp.price));
		break;
		case "NewDeckSharp_7":
			dialog.text = DLG_TEXT_Q[184];
			link.l1 = DLG_TEXT_Q[185];
			link.l1.go = "NewDeckSharp_7exit";
		break;
		case "NewDeckSharp_7exit":
			AddQuestRecord("SharpPearl", "10");
			CloseQuestHeader("SharpPearl");
			pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
			pchar.questTemp.Sharp.brothelChance = rand(10);
			NextDiag.TempNode = "DeckSharp_overBad";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (pchar.location != "Deck_Near_Ship")
			{
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 15.0);
			}
		break;

		case "DeckSharp_over":
			dialog.text = DLG_TEXT_Q[186];
			link.l1 = DLG_TEXT_Q[187];
			link.l1.go = "exit";
		break;
		case "DeckSharp_overBad":
			dialog.text = DLG_TEXT_Q[188];
			link.l1 = DLG_TEXT_Q[189];
			link.l1.go = "exit";
		break;
		case "DeckSharp_noWork":
			dialog.text = DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
			link.l1.go = "exit";
			CloseQuestHeader("SharpPearl");
		break;
		//капитан Шарп, первый разговор в городе на улице
		case "CitySharp":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_Q[192] + pchar.lastname + DLG_TEXT_Q[193];
				link.l1 = DLG_TEXT_Q[194];
				link.l1.go = "CitySharp_1";
				npchar.quest.meeting = true;
			}
			else
			{
				dialog.text = DLG_TEXT_Q[195] + pchar.lastname + DLG_TEXT_Q[196];
				link.l1 = DLG_TEXT_Q[197];
				link.l1.go = "CitySharp_2";
			}
		break;

		case "CitySharp_1":
			dialog.text = DLG_TEXT_Q[198];
			link.l1 = DLG_TEXT_Q[199];
			link.l1.go = "DeckSharp_2";
		break;
		case "CitySharp_2":
			dialog.text = DLG_TEXT_Q[200];
			link.l1 = DLG_TEXT_Q[201];
			link.l1.go = "CitySharp_3";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = DLG_TEXT_Q[202];
				link.l1 = DLG_TEXT_Q[203];
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "CitySharp_3":
			dialog.text = DLG_TEXT_Q[204];
			link.l1 = DLG_TEXT_Q[205];
			link.l1.go = "NewDeckSharp_2";
		break;
		//капитан Шарп в борделе
		case "BrothelSharp":
			dialog.text = DLG_TEXT_Q[206] + pchar.lastname + DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "BrothelSharp_1";
			//блокировка генератора, если взят грабеж от Моргана
			if (pchar.questTemp.piratesLine == "PearlQ4_toTerks")
			{
				dialog.text = DLG_TEXT_Q[209];
				link.l1 = DLG_TEXT_Q[210];
				link.l1.go = "exit";
				NextDiag.TempNode = "DeckSharp_overBad";
				pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
				pchar.questTemp.Sharp.brothelChance = rand(10);
				DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
				AddQuestRecord("SharpPearl", "13");
				CloseQuestHeader("SharpPearl");
			}
		break;
		case "BrothelSharp_1":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "NewDeckSharp_2";
		break;
		//Эмилио Гарсиа. в бухте Сан-Хуна дель Норте
		case "SharpSeekSpy_Emi":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog");
		break;
		case "SharpSeekSpy_fri":
			dialog.text = DLG_TEXT_Q[214] + pchar.lastname + DLG_TEXT_Q[215];
			link.l1 = DLG_TEXT_Q[216];
			link.l1.go = "SharpSeekSpy_fri_1";
		break;
		case "SharpSeekSpy_fri_1":
			dialog.text = DLG_TEXT_Q[217];
			link.l1 = DLG_TEXT_Q[218];
			link.l1.go = "SharpSeekSpy_fri_2";
		break;
		case "SharpSeekSpy_fri_2":
			dialog.text = DLG_TEXT_Q[219];
			link.l1 = DLG_TEXT_Q[220];
			link.l1.go = "SharpSeekSpy_fri_3";
		break;
		case "SharpSeekSpy_fri_3":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "SharpSeekSpy_fri_4";
		break;
		case "SharpSeekSpy_fri_4":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_2");
		break;
		case "SharpSeekSpy_Emi_1":
			dialog.text = DLG_TEXT_Q[225];
			link.l1 = DLG_TEXT_Q[226];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharpSeekSpy_caveDialog_3");
		break;
		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = DLG_TEXT_Q[227];
			link.l1 = DLG_TEXT_Q[228];
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = DLG_TEXT_Q[229];
			link.l1 = DLG_TEXT_Q[230] + pchar.questTemp.different.FackWaitress.Name + DLG_TEXT_Q[231];
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = DLG_TEXT_Q[234];
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = DLG_TEXT_Q[235];
			link.l1 = DLG_TEXT_Q[236];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = DLG_TEXT_Q[237];
			link.l1 = DLG_TEXT_Q[238];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = DLG_TEXT_Q[239];
			link.l1 = DLG_TEXT_Q[240];
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = DLG_TEXT_Q[241];
			link.l1 = DLG_TEXT_Q[242];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = DLG_TEXT_Q[243] + GetFullName(npchar) + DLG_TEXT_Q[244] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'."; 
			link.l1 = DLG_TEXT_Q[245];
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = DLG_TEXT_Q[246];
			link.l1 = DLG_TEXT_Q[247] + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + ".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = DLG_TEXT_Q[248];
			link.l1 = DLG_TEXT_Q[249];
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = DLG_TEXT_Q[250] + FindRussianMoneyString(sti(npchar.quest.money)) + ".";
				link.l1 = DLG_TEXT_Q[251];
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = DLG_TEXT_Q[252] + FindRussianMoneyString(sti(npchar.quest.money)) + ".";
					link.l1 = DLG_TEXT_Q[253];
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[254];
					link.l1 = DLG_TEXT_Q[255];
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(600/sti(npchar.quest.stepsQty)));
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = DLG_TEXT_Q[258];
			link.l1 = DLG_TEXT_Q[259];
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Dat"));
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = DLG_TEXT_Q[260];
				link.l1 = DLG_TEXT_Q[261];
			}
			else
			{
				dialog.text = DLG_TEXT_Q[262];
				link.l1 = DLG_TEXT_Q[263];
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[264];
			link.l1 = DLG_TEXT_Q[265] + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + DLG_TEXT_Q[266];
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = DLG_TEXT_Q[267];
				link.l1 = DLG_TEXT_Q[268];
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = DLG_TEXT_Q[269];
					link.l1 = DLG_TEXT_Q[270];
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[271];
					link.l1 = DLG_TEXT_Q[272];
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = DLG_TEXT_Q[273] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[274];
			link.l1 = DLG_TEXT_Q[275];
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = DLG_TEXT_Q[276];
			link.l1 = DLG_TEXT_Q[277];
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(800/sti(npchar.quest.stepsQty)));
        	AddCharacterExpToSkill(pchar, "Repair", makeint(600/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterReputation(pchar, 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = DLG_TEXT_Q[278];
			link.l1 = DLG_TEXT_Q[279];
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = DLG_TEXT_Q[280];
			link.l1 = DLG_TEXT_Q[281];
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = DLG_TEXT_Q[282];
			link.l1 = DLG_TEXT_Q[283];
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[284];
			link.l1 = DLG_TEXT_Q[285];
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = DLG_TEXT_Q[286];
			link.l1 = DLG_TEXT_Q[287];
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = DLG_TEXT_Q[288];
			link.l1 = DLG_TEXT_Q[289];
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = DLG_TEXT_Q[290];
			link.l1 = DLG_TEXT_Q[291];
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = DLG_TEXT_Q[292];
			link.l1 = DLG_TEXT_Q[293];
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;	
		//--------------------------- ночное бдение в церкви --------------------------------
		case "ChurchBerglar":
			dialog.text = DLG_TEXT_Q[294];
			link.l1 = DLG_TEXT_Q[295];
			link.l1.go = "ChurchBerglar_1";
		break;
		case "ChurchBerglar_1":
			dialog.text = DLG_TEXT_Q[296];
			link.l1 = DLG_TEXT_Q[297];
			link.l1.go = "ChurchBerglar_2";
		break;
		case "ChurchBerglar_2":
			dialog.text = DLG_TEXT_Q[298];
			link.l1 = DLG_TEXT_Q[299];
			link.l1.go = "ChurchBerglar_fight";
		break;
		case "ChurchBerglar_fight":
			LAi_LocationFightDisable(&locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------- поиск кэпов, дача квеста горожанином --------------------------------
		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[300], 
				DLG_TEXT_Q[301], 
				DLG_TEXT_Q[302]);
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[303], DLG_TEXT_Q[304]);
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple(DLG_TEXT_Q[305], DLG_TEXT_Q[306]);
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = DLG_TEXT_Q[307] + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + DLG_TEXT_Q[308];
					link.l1 = DLG_TEXT_Q[309];
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = DLG_TEXT_Q[310];
					link.l1 = DLG_TEXT_Q[311];
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = DLG_TEXT_Q[312];
					link.l1 = DLG_TEXT_Q[313];
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = DLG_TEXT_Q[314];
			link.l1 = DLG_TEXT_Q[315];
			link.l1.go = "SCQ_Slave_1";
			link.l2 = DLG_TEXT_Q[316];
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = DLG_TEXT_Q[317] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[318] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + DLG_TEXT_Q[319] + npchar.quest.SeekCap.shipName + DLG_TEXT_Q[320] + FindRussianMoneyString(sti(npchar.quest.money)) + ".";
			link.l1 = DLG_TEXT_Q[321];
			link.l1.go = "SCQ_Slave_2";
			link.l2 = DLG_TEXT_Q[322];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = DLG_TEXT_Q[329] + FindRussianMoneyString(sti(npchar.quest.money)) + ".";
			link.l1 = DLG_TEXT_Q[330];
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = DLG_TEXT_Q[331];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = DLG_TEXT_Q[332] + npchar.quest.SeekCap.name + DLG_TEXT_Q[333] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[334] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + DLG_TEXT_Q[335] + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = DLG_TEXT_Q[336];
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = DLG_TEXT_Q[337];
			link.l1 = DLG_TEXT_Q[338];
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = DLG_TEXT_Q[339];
			link.l1 = DLG_TEXT_Q[340];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = DLG_TEXT_Q[341];
			link.l1 = DLG_TEXT_Q[342];
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = DLG_TEXT_Q[343] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[344];
			link.l1 = DLG_TEXT_Q[345];
			link.l1.go = "SCQ_Friend_2";
			link.l2 = DLG_TEXT_Q[346];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = DLG_TEXT_Q[347];
			link.l1 = DLG_TEXT_Q[348];
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = DLG_TEXT_Q[349] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[350] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + DLG_TEXT_Q[351] + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = DLG_TEXT_Q[352];
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = DLG_TEXT_Q[353];
			link.l1 = DLG_TEXT_Q[354];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = DLG_TEXT_Q[355];
			link.l1 = DLG_TEXT_Q[356];
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = DLG_TEXT_Q[357];
					link.l1 = DLG_TEXT_Q[358] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[359] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + DLG_TEXT_Q[360];
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = DLG_TEXT_Q[361];
					link.l1 = DLG_TEXT_Q[362] + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + DLG_TEXT_Q[363];
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = DLG_TEXT_Q[364];
					link.l1 = DLG_TEXT_Q[365];
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = DLG_TEXT_Q[366] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[367];
					link.l1 = DLG_TEXT_Q[368];
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = DLG_TEXT_Q[369] + npchar.quest.SeekCap.capName + "!";
					link.l1 = DLG_TEXT_Q[370];
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = DLG_TEXT_Q[371] + npchar.quest.SeekCap.capName + "?";
					link.l1 = DLG_TEXT_Q[372];
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = DLG_TEXT_Q[373] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = DLG_TEXT_Q[376] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[377];
			link.l1 = DLG_TEXT_Q[378];
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = DLG_TEXT_Q[379] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[380];
			link.l1 = DLG_TEXT_Q[381];
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[382], 
				DLG_TEXT_Q[383], 
				DLG_TEXT_Q[384]);
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[385], DLG_TEXT_Q[386] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[387]);
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple(DLG_TEXT_Q[388] + GetAddress_FormToNPC(NPChar) + "?", DLG_TEXT_Q[389] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[390]);
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = DLG_TEXT_Q[391];
					link.l1 = DLG_TEXT_Q[392];
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = DLG_TEXT_Q[393];
					link.l1 = DLG_TEXT_Q[394] + GetAddress_FormToNPC(NPChar) + "?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = DLG_TEXT_Q[395];
					link.l1 = DLG_TEXT_Q[396];
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = DLG_TEXT_Q[397];
			link.l1 = DLG_TEXT_Q[398];
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = DLG_TEXT_Q[399] + FindRussianMoneyString(sti(npchar.quest.money)) + ".";
			link.l1 = DLG_TEXT_Q[400];
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = DLG_TEXT_Q[401];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = DLG_TEXT_Q[402] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[403] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + DLG_TEXT_Q[404] + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = DLG_TEXT_Q[405];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = DLG_TEXT_Q[406];
			link.l1 = DLG_TEXT_Q[407];
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = DLG_TEXT_Q[408];
			link.l1 = DLG_TEXT_Q[409];
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = DLG_TEXT_Q[410];
			link.l1 = DLG_TEXT_Q[411];
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = DLG_TEXT_Q[412];
			link.l1 = DLG_TEXT_Q[413];
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = DLG_TEXT_Q[414];
			link.l1 = DLG_TEXT_Q[415];
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = DLG_TEXT_Q[416];
			link.l1 = DLG_TEXT_Q[417];
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = DLG_TEXT_Q[418];
			link.l1 = DLG_TEXT_Q[419];
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = DLG_TEXT_Q[420] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[421];
			link.l1 = DLG_TEXT_Q[422];
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = DLG_TEXT_Q[423];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = DLG_TEXT_Q[424] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[425] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + DLG_TEXT_Q[426] + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = DLG_TEXT_Q[427] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[428];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = DLG_TEXT_Q[429];
			link.l1 = DLG_TEXT_Q[430];
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = DLG_TEXT_Q[431];
			link.l1 = DLG_TEXT_Q[432];
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = DLG_TEXT_Q[433];
			link.l1 = DLG_TEXT_Q[434];
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = DLG_TEXT_Q[435];
			link.l1 = DLG_TEXT_Q[436];
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = DLG_TEXT_Q[437];
			link.l1 = DLG_TEXT_Q[438];
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = DLG_TEXT_Q[439] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[440];
			link.l1 = DLG_TEXT_Q[441];
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = DLG_TEXT_Q[442];
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = DLG_TEXT_Q[443];
			link.l1 = DLG_TEXT_Q[444];
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = DLG_TEXT_Q[445] + GetFullName(forName) + DLG_TEXT_Q[446] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[447] + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")) + DLG_TEXT_Q[448] + npchar.quest.SeekCap.shipName + "'.";
			link.l1 = DLG_TEXT_Q[449];
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = DLG_TEXT_Q[450];
			link.l1 = DLG_TEXT_Q[451] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[452];
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = DLG_TEXT_Q[453];
					link.l1 = DLG_TEXT_Q[454] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[455] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[456];
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = DLG_TEXT_Q[457] + npchar.quest.SeekCap.capName + DLG_TEXT_Q[458];
					link.l1 = DLG_TEXT_Q[459] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[460];
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = DLG_TEXT_Q[461];
					link.l1 = DLG_TEXT_Q[462] + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + DLG_TEXT_Q[463];
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = DLG_TEXT_Q[464] + npchar.quest.SeekCap.capName + "!";
					link.l1 = DLG_TEXT_Q[465];
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = DLG_TEXT_Q[466] + npchar.quest.SeekCap.capName + "?!";
					link.l1 = DLG_TEXT_Q[467] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[468];
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = DLG_TEXT_Q[469];
					link.l1 = DLG_TEXT_Q[470] + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = DLG_TEXT_Q[471] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[472];
			link.l1 = DLG_TEXT_Q[473];
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = DLG_TEXT_Q[474] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[475];
			link.l1 = DLG_TEXT_Q[476];
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, "jewelry14", rand(3));
			TakeNItems(pchar, "jewelry13", rand(3));
			TakeNItems(pchar, "jewelry10", rand(3));
			TakeNItems(pchar, "jewelry15", rand(3));
			TakeNItems(pchar, "jewelry16", rand(3));
			TakeNItems(pchar, "jewelry18", rand(3));
			TakeNItems(pchar, "jewelry6", rand(3));
			TakeNItems(pchar, "jewelry7", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = DLG_TEXT_Q[477] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_Q[478];
			link.l1 = DLG_TEXT_Q[479];
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = DLG_TEXT_Q[480];
					link.l1 = DLG_TEXT_Q[481] + GetFullName(npchar) + DLG_TEXT_Q[482];
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = DLG_TEXT_Q[483];
			link.l1 = DLG_TEXT_Q[484] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + DLG_TEXT_Q[485];
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = DLG_TEXT_Q[486];
			link.l1 = DLG_TEXT_Q[487];
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = DLG_TEXT_Q[488];
			link.l1 = DLG_TEXT_Q[489];
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = DLG_TEXT_Q[490];
			link.l1 = DLG_TEXT_Q[491];
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = DLG_TEXT_Q[492];
			link.l1 = DLG_TEXT_Q[493];
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = DLG_TEXT_Q[494];
			link.l1 = DLG_TEXT_Q[495];
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[496];
			link.l1 = DLG_TEXT_Q[497];
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[498];
			link.l1 = DLG_TEXT_Q[499];
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = DLG_TEXT_Q[500];
			link.l1 = DLG_TEXT_Q[501];
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[502];
			link.l1 = DLG_TEXT_Q[503] + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + DLG_TEXT_Q[504] + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = DLG_TEXT_Q[505];
			link.l1 = DLG_TEXT_Q[506];
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = DLG_TEXT_Q[507];
			link.l1 = DLG_TEXT_Q[508];
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = DLG_TEXT_Q[509];
			link.l1 = DLG_TEXT_Q[510];
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = DLG_TEXT_Q[511];
			link.l1 = DLG_TEXT_Q[512];
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[513];
			link.l1 = DLG_TEXT_Q[514] + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + DLG_TEXT_Q[515] + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[516];
			link.l1 = DLG_TEXT_Q[517];
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[518];
			link.l1 = DLG_TEXT_Q[519];
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = DLG_TEXT_Q[520];
			link.l1 = DLG_TEXT_Q[521];
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[522];
			link.l1 = DLG_TEXT_Q[523] + XI_ConvertString("Colony"+npchar.quest.cribCity) + DLG_TEXT_Q[524] + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = DLG_TEXT_Q[525];
			link.l1 = DLG_TEXT_Q[526];
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "girl_"+(rand(7)+1); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = DLG_TEXT_Q[527];
			link.l1 = DLG_TEXT_Q[528];
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = DLG_TEXT_Q[529];
			link.l1 = DLG_TEXT_Q[530] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = DLG_TEXT_Q[531];
			link.l1 = DLG_TEXT_Q[532] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[533];
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = DLG_TEXT_Q[534];
			link.l1 = TimeGreeting() + DLG_TEXT_Q[535];
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = DLG_TEXT_Q[536];
			link.l1 = DLG_TEXT_Q[537] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + DLG_TEXT_Q[538];
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = DLG_TEXT_Q[539];
			link.l1 = DLG_TEXT_Q[540] + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + DLG_TEXT_Q[541];
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = DLG_TEXT_Q[542];
			link.l1 = DLG_TEXT_Q[543];
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		break;
		case "FriendCap_exit":
			dialog.text = DLG_TEXT_Q[544];
			link.l1 = DLG_TEXT_Q[545];
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting() + DLG_TEXT_Q[546];
			link.l1 = DLG_TEXT_Q[547];
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[548];
			link.l1 = DLG_TEXT_Q[549] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + DLG_TEXT_Q[550];
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[551];
			link.l1 = DLG_TEXT_Q[552] + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat") + ".";
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = DLG_TEXT_Q[553] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[554];
			link.l1 = DLG_TEXT_Q[555];
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			DeleteAttribute(NullCharacter, "capitainBase." + npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = DLG_TEXT_Q[556];
			link.l1 = DLG_TEXT_Q[557] + GetFullName(npchar) + DLG_TEXT_Q[558];
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = DLG_TEXT_Q[559];
			link.l1 = DLG_TEXT_Q[560];
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = DLG_TEXT_Q[561];
			link.l1 = DLG_TEXT_Q[562];
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = DLG_TEXT_Q[563];
			link.l1 = DLG_TEXT_Q[564];
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = DLG_TEXT_Q[565];
			link.l1 = DLG_TEXT_Q[566] + GetFullName(npchar) + DLG_TEXT_Q[567];
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[568];
			link.l1 = DLG_TEXT_Q[569];
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[570];
			link.l1 = DLG_TEXT_Q[571];
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = DLG_TEXT_Q[572];
			link.l1 = DLG_TEXT_Q[573];
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			DeleteAttribute(NullCharacter, "capitainBase." + npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = DLG_TEXT_Q[574];
			link.l1 = DLG_TEXT_Q[575];
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = DLG_TEXT_Q[576];
			link.l1 = DLG_TEXT_Q[577];
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = DLG_TEXT_Q[578];
			link.l1 = DLG_TEXT_Q[579] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = DLG_TEXT_Q[580];
			link.l1 = DLG_TEXT_Q[581];
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = DLG_TEXT_Q[582];
			link.l1 = DLG_TEXT_Q[583];
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = DLG_TEXT_Q[584];
			link.l1 = DLG_TEXT_Q[585];
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = DLG_TEXT_Q[586];
			link.l1 = DLG_TEXT_Q[587];
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = DLG_TEXT_Q[588];
			link.l1 = DLG_TEXT_Q[589];
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = DLG_TEXT_Q[590];
			link.l1 = DLG_TEXT_Q[591];
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = DLG_TEXT_Q[592];
			link.l1 = DLG_TEXT_Q[593] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[594];
			link.l1 = DLG_TEXT_Q[595];
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[596];
			link.l1 = DLG_TEXT_Q[597];
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = DLG_TEXT_Q[598];
			link.l1 = DLG_TEXT_Q[599];
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = DLG_TEXT_Q[600];
			link.l1 = DLG_TEXT_Q[601];
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = DLG_TEXT_Q[602];
			link.l1 = DLG_TEXT_Q[603] + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + DLG_TEXT_Q[604];
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = DLG_TEXT_Q[605];
			link.l1 = DLG_TEXT_Q[606];
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = DLG_TEXT_Q[607];
			link.l1 = DLG_TEXT_Q[608];
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[609];
			link.l1 = DLG_TEXT_Q[610] + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = DLG_TEXT_Q[611];
			link.l1 = DLG_TEXT_Q[612];
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = DLG_TEXT_Q[613];
			link.l1 = DLG_TEXT_Q[614];
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCapCap_exit":
			dialog.text = DLG_TEXT_Q[615];
			link.l1 = DLG_TEXT_Q[616];
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[617];
			link.l1 = DLG_TEXT_Q[618] + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = DLG_TEXT_Q[619];
			link.l1 = DLG_TEXT_Q[620];
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = DLG_TEXT_Q[621];
			link.l1 = DLG_TEXT_Q[622];
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = DLG_TEXT_Q[623];
			link.l1 = DLG_TEXT_Q[624] + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = DLG_TEXT_Q[625];
			link.l1 = DLG_TEXT_Q[626];
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+1); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = DLG_TEXT_Q[627];
			link.l1 = DLG_TEXT_Q[628] + GetFullName(pchar) + DLG_TEXT_Q[629];
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = DLG_TEXT_Q[630];
			link.l1 = DLG_TEXT_Q[631];
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//несчастный мушкетер
		case "OffMushketer":
			dialog.text = DLG_TEXT_Q[632];
			link.l1 = DLG_TEXT_Q[633] + GetFullName(pchar) + ".";
			link.l1.go = "OffM_1";
		break;
		case "OffM_1":
			dialog.text = DLG_TEXT_Q[634];
			link.l1 = DLG_TEXT_Q[635];
			link.l1.go = "OffM_2";
		break;
		case "OffM_2":
			dialog.text = DLG_TEXT_Q[636];
			link.l1 = DLG_TEXT_Q[637];
			link.l1.go = "OffM_4";
		break;
		case "OffM_4":
			dialog.text = DLG_TEXT_Q[638];
			link.l1 = DLG_TEXT_Q[639];
			link.l1.go = "OffM_5";
		break;
		case "OffM_5":
			dialog.text = DLG_TEXT_Q[640];
			link.l1 = DLG_TEXT_Q[641];
			link.l1.go = "OffM_6";
		break;
		case "OffM_6":
			dialog.text = DLG_TEXT_Q[642];
			link.l1 = DLG_TEXT_Q[643];
			link.l1.go = "OffM_7";
		break;
		case "OffM_7":
			dialog.text = DLG_TEXT_Q[644]+
				DLG_TEXT_Q[645];
			link.l1 = DLG_TEXT_Q[646];
			link.l1.go = "OffM_8";
		break;
		case "OffM_8":
			dialog.text = DLG_TEXT_Q[647];
			link.l1 = DLG_TEXT_Q[648];
			link.l1.go = "OffM_9";
		break;
		case "OffM_9":
			dialog.text = DLG_TEXT_Q[649];
			link.l1 = DLG_TEXT_Q[650];
			link.l1.go = "OffM_10";
		break;
		case "OffM_10":
			dialog.text = DLG_TEXT_Q[651];
			link.l1 = DLG_TEXT_Q[652];
			link.l1.go = "OffM_11";
		break;
		case "OffM_11":
			dialog.text = DLG_TEXT_Q[653];
			link.l1 = DLG_TEXT_Q[654];
			link.l1.go = "OffM_12";
		break;
		case "OffM_12":
			dialog.text = DLG_TEXT_Q[655];
			link.l1 = DLG_TEXT_Q[656];
			link.l1.go = "exit";
			SetMushketCapitainInWorld();
			pchar.questTemp.mushket2x2 = true;
			AddQuestRecord("SeekDoubleMushket", "1");
			NextDiag.TempNode = "OffM_result";	
		break;

		case "OffM_result":
			dialog.text = DLG_TEXT_Q[657];
			if (CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = DLG_TEXT_Q[658];
				link.l1.go = "OffM_result_1";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[659];
				link.l1.go = "exit";
			}
		break;
		case "OffM_result_1":
			dialog.text = DLG_TEXT_Q[660];
			link.l1 = DLG_TEXT_Q[661];
			link.l1.go = "OffM_result_2";
			TakeItemFromCharacter(pchar, "mushket2x2");
			Npchar.quest.OfficerPrice = sti(pchar.rank)*300;
		break;
		case "OffM_result_2":
			dialog.text = DLG_TEXT_Q[662] + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + DLG_TEXT_Q[663];
			link.l1 = DLG_TEXT_Q[664];
			link.l1.go = "OffM_trade";
			link.l1 = DLG_TEXT_Q[665];
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_trade":
			dialog.text = DLG_TEXT_Q[666];
			link.l1 = DLG_TEXT_Q[667];
			link.l1.go = "OffM_Ok";
		break;
		case "OffM_Ok":
			Npchar.quest.OfficerPrice.add = sti(pchar.rank)*1000;
			dialog.text = DLG_TEXT_Q[668] + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + DLG_TEXT_Q[669];
			link.l1 = DLG_TEXT_Q[670];
			link.l1.go = "OffM_Ok_1";
		break;
		case "OffM_Ok_1":
			dialog.text = DLG_TEXT_Q[671];
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = DLG_TEXT_Q[672];
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[673];
				link.l1.go = "OffM_noMoney";
				link.l2 = DLG_TEXT_Q[674];
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
		case "OffM_noMoney":
			dialog.text = DLG_TEXT_Q[675];
			link.l1 = DLG_TEXT_Q[676];
			link.l1.go = "exit";
		break;
		case "OffM_Ok_3":
			dialog.text = DLG_TEXT_Q[677];
			link.l1 = DLG_TEXT_Q[678];
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			AddQuestRecord("SeekDoubleMushket", "3");
			CloseQuestHeader("SeekDoubleMushket");
			AddMoneyToCharacter(pchar, -sti(Npchar.quest.OfficerPrice.add));
			npchar.model = "MusketeerEnglish_2";
			npchar.model.animation = "mushketer";
			npchar.MusketerDistance = 5;
			npchar.greeting = "Gr_questOfficer";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		case "OffM_TWO":
			dialog.text = DLG_TEXT_Q[679] + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice.add)) + DLG_TEXT_Q[680] + FindRussianMoneyString(sti(Npchar.quest.OfficerPrice)) + DLG_TEXT_Q[681];
			if (sti(pchar.money) < sti(Npchar.quest.OfficerPrice.add))
			{
				link.l1 = DLG_TEXT_Q[682];
				link.l1.go = "OffM_noMoney";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[683];
				link.l1.go = "OffM_noMoney";
				link.l2 = DLG_TEXT_Q[684];
				link.l2.go = "OffM_Ok_3";
			}
			NextDiag.TempNode = "OffM_TWO";
		break;
	}
}


void GetPerlShore()
{	
	switch (rand(4))
	{
		case 0:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Beliz";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore_ship2";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = DLG_TEXT_Q[685];
			break;
		case 1:
			pchar.questTemp.Sharp.PearlAreal = "Mein";
			pchar.questTemp.Sharp.PearlAreal.Island = "Cumana";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore18";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_8";
			pchar.questTemp.Sharp.PearlAreal.add = DLG_TEXT_Q[686];
			break;
		case 2:
			pchar.questTemp.Sharp.PearlAreal = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Island = "Dominica";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore26";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_3";
			break;
		case 3:
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
		case 4:
			pchar.questTemp.Sharp.PearlAreal = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Island = "Caiman";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore17";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			break;
	}
	pchar.questTemp.Sharp.PearlAreal.terms = rand(5) + 5; //сроки
	pchar.questTemp.Sharp.PearlAreal.qtyShips = rand(6) + 6; //кол-во тартан ловцов
	pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчета
	pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_" + npchar.index, "", "man", "man", Rank, iNation, -1, true));
	switch (npchar.quest.SeekCap)
	{
		case "manSlave": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
		break;
		case "manRapeWife": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
		break;
		case "manFriend": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
		break;
		case "womanHasband": 
			SetCaptanModelByEncType(sld, "trade");
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
		break;
		case "womanRevenge": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
		break;
		case "womanPirates": 
			SetCaptanModelByEncType(sld, "pirate");
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo(DLG_TEXT_Q[687] + sld.id + DLG_TEXT_Q[688] + sld.city + DLG_TEXT_Q[689] + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

void SetMushketCapitainInWorld()
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "", "man", "man", Rank, PIRATE, -1, true));
	sld.name = DLG_TEXT_Q[690];
	sld.lastname = DLG_TEXT_Q[691];
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, DLG_TEXT_Q[692], CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
	sld.Ship.Mode = "pirate";	

	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "Bridgetown"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo(DLG_TEXT_Q[693] + sld.city + DLG_TEXT_Q[694] + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = DLG_TEXT_Q[695];
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
