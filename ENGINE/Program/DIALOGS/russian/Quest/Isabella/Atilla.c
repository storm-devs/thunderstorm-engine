#include "TEXT\DIALOGS\Quest\Isabella\Atilla.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "First time":
			dialog.text = DLG_TEXT_QB[0] + GetFullName(PChar) + "!";
			link.l1 = DLG_TEXT_QB[1];
			link.l1.go = "port_1";		
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
		break;

		case "port_1":
		    sld = characterFromID("Atilla");
			dialog.text = DLG_TEXT_QB[2];
			if (pchar.RomanticQuest == "")
			{
			    link.l1 = DLG_TEXT_QB[3];
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = DLG_TEXT_QB[4];
				link.l1.go = "port_1_1";
			}
		break;

		case "port_1_1":
			dialog.text = DLG_TEXT_QB[5];
			link.l1 = DLG_TEXT_QB[6];
			link.l1.go = "port_toTavern";
		break;

		case "port_toTavern":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1"; 
			chrDisableReloadToLocation = true; 
			bDisableFastReload = true; 
			FreeSitLocator("Pirates_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Pirates_tavern", "sit", "sit3", "Romantic_Pirat_toTavern", -1);
		break;

		case "Tavern_1":
			LAi_SetSitType(Pchar);
			dialog.text = DLG_TEXT_QB[7]+GetFullName(PChar)+DLG_TEXT_QB[8];
			link.l1 = DLG_TEXT_QB[9];
			link.l1.go = "Tavern_2";
		break;
		
		case "Tavern_2":
			dialog.text = DLG_TEXT_QB[10];
			link.l1 = DLG_TEXT_QB[11];
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			dialog.text = DLG_TEXT_QB[12];
			link.l1 = DLG_TEXT_QB[13];
			link.l1.go = "Tavern_4";
		break;
		
		case "Tavern_4":
			dialog.text = DLG_TEXT_QB[14];
			link.l1 = DLG_TEXT_QB[15];
			link.l1.go = "Tavern_5";
		break;
		
		case "Tavern_5":
			dialog.text = DLG_TEXT_QB[16];
			link.l1 = DLG_TEXT_QB[17];
			link.l1.go = "Tavern_6";
		break;
		
		case "Tavern_6":
			dialog.text = DLG_TEXT_QB[18];
			link.l1 = DLG_TEXT_QB[19];
			link.l1.go = "Tavern_Out";
		break;
		
		case "Tavern_Out":
			NextDiag.CurrentNode = "Tavern_Bye";
			DialogExit();
			AddDialogExitQuest("Romantic_Pirat_toTavern_end");			
		break;

		case "Tavern_Bye":
            NextDiag.TempNode = "Tavern_Bye";
			dialog.text = DLG_TEXT_QB[20];
			link.l1 = DLG_TEXT_QB[21];
			link.l1.go = "exit";
		break;
		//доводим новости до сведения Атиллы
		case "TalkingNews":
			dialog.text = DLG_TEXT_QB[22] + GetFullName(pchar) + DLG_TEXT_QB[23];
			link.l1 = DLG_TEXT_QB[24];
			link.l1.go = "TalkingNews_1";
		break;
		case "TalkingNews_1":
			dialog.text = DLG_TEXT_QB[25];
			link.l1 = DLG_TEXT_QB[26];
			link.l1.go = "TalkingNews_2";
		break;
		case "TalkingNews_2":
			dialog.text = DLG_TEXT_QB[27];
			link.l1 = DLG_TEXT_QB[28];
			link.l1.go = "TalkingNews_3";
		break;
		case "TalkingNews_3":
			dialog.text = DLG_TEXT_QB[29];
			link.l1 = DLG_TEXT_QB[30];
			link.l1.go = "TalkingNews_4";
		break;
		case "TalkingNews_4":
			dialog.text = DLG_TEXT_QB[31];
			link.l1 = DLG_TEXT_QB[32];
			link.l1.go = "TalkingNews_5";
		break;
		case "TalkingNews_5":
			dialog.text = DLG_TEXT_QB[33];
			link.l1 = DLG_TEXT_QB[34];
			link.l1.go = "TalkingNews_6";
		break;
		case "TalkingNews_6":
			dialog.text = DLG_TEXT_QB[35];
			link.l1 = DLG_TEXT_QB[36];
			link.l1.go = "TalkingNews_7";
		break;
		case "TalkingNews_7":
			dialog.text = DLG_TEXT_QB[37];
			link.l1 = DLG_TEXT_QB[38];
			link.l1.go = "TalkingNews_8";
		break;
		case "TalkingNews_8":
			dialog.text = DLG_TEXT_QB[39];
			link.l1 = DLG_TEXT_QB[40];
			link.l1.go = "TalkingNews_9";
		break;
		case "TalkingNews_9":
			dialog.text = "L'amour... Qu'ici faire?..";
			link.l1 = DLG_TEXT_QB[41];
			link.l1.go = "TalkingNews_10";
		break;
		case "TalkingNews_10":
			dialog.text = DLG_TEXT_QB[42]+
				          DLG_TEXT_QB[43];
			link.l1 = DLG_TEXT_QB[44];
			link.l1.go = "TalkingNews_11";
		break;
		case "TalkingNews_11":
			dialog.text = DLG_TEXT_QB[45];
			link.l1 = DLG_TEXT_QB[46];
			link.l1.go = "TalkingNews_12";
		break;
		case "TalkingNews_12":
			dialog.text = DLG_TEXT_QB[47];
			link.l1 = DLG_TEXT_QB[48];
			link.l1.go = "TalkingNews_13";
		break;
		case "TalkingNews_13":
			dialog.text = DLG_TEXT_QB[49];
			link.l1 = DLG_TEXT_QB[50];
			link.l1.go = "TalkingNews_14";
		break;
		case "TalkingNews_14":
			SetTimerCondition("Romantic_AtillaToHouse", 0, 2, 0, false);
			AddQuestRecord("Romantic_Line", "11");
            LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			//открываем дом Сальватора и убираем Изабеллу, ставим наемных убийц в дом.
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1.location = "SanJuan_houseSp6";
            Pchar.quest.Romantic_AmbushInHouse.win_condition = "Romantic_AmbushInHouse";
			DialogExit();
		break;
		//через два месяца по завершению поисков
		case "AtillaInHouse":
			dialog.text = DLG_TEXT_QB[51] + GetFullName(pchar) + DLG_TEXT_QB[52];
			link.l1 = DLG_TEXT_QB[53];
			link.l1.go = "AtillaInHouse_1";
		break;
		case "AtillaInHouse_1":
			dialog.text = DLG_TEXT_QB[54] + pchar.name + DLG_TEXT_QB[55];
			link.l1 = DLG_TEXT_QB[56];
			link.l1.go = "AtillaInHouse_2";
		break;
		case "AtillaInHouse_2":
			dialog.text = DLG_TEXT_QB[57];
			link.l1 = DLG_TEXT_QB[58];
			link.l1.go = "AtillaInHouse_3";
		break;
		case "AtillaInHouse_3":
			dialog.text = DLG_TEXT_QB[59];
			link.l1 = DLG_TEXT_QB[60];
			link.l1.go = "AtillaInHouse_4";
		break;
		case "AtillaInHouse_4":
			dialog.text = DLG_TEXT_QB[61];
			link.l1 = DLG_TEXT_QB[62];
			link.l1.go = "AtillaInHouse_5";
		break;
		case "AtillaInHouse_5":
			dialog.text = DLG_TEXT_QB[63];
			link.l1 = DLG_TEXT_QB[64];
			link.l1.go = "AtillaInHouse_6";
		break;
		case "AtillaInHouse_6":
			dialog.text = DLG_TEXT_QB[65];
			link.l1 = DLG_TEXT_QB[66];
			link.l1.go = "AtillaInHouse_7";
		break;
		case "AtillaInHouse_7":
			dialog.text = DLG_TEXT_QB[67] + pchar.name + DLG_TEXT_QB[68];
			link.l1 = DLG_TEXT_QB[69];
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "13");
			pchar.RomanticQuest = "AttackBrig"; //флаг для кэпа на абордаже брига
            Pchar.quest.Romantic_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.Romantic_AttackBrig.win_condition.l1.location = "PortoBello";
            Pchar.quest.Romantic_AttackBrig.win_condition = "Romantic_AttackBrig";
			SetTimerCondition("Romantic_BrigTimeOver", 0, 0, 16, false);
		break;
		case "AtillaInHouse_Again":
			dialog.text = DLG_TEXT_QB[70];
			link.l1 = DLG_TEXT_QB[71];
			link.l1.go = "exit";
		break;
		// после погони за бригом Восторженный, если не догнал его вообще
		case "Brig_Late":
			dialog.text = DLG_TEXT_QB[72];
			link.l1 = DLG_TEXT_QB[73];
			link.l1.go = "Brig_Late_1";
		break;
		case "Brig_Late_1":
			dialog.text = DLG_TEXT_QB[74];
			link.l1 = DLG_TEXT_QB[75];
			link.l1.go = "Brig_Late_2";
		break;
		case "Brig_Late_2":
			dialog.text = DLG_TEXT_QB[76];
			link.l1 = DLG_TEXT_QB[77];
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
			CloseQuestHeader("Romantic_Line");
			DeleteAttribute(pchar, "RomanticQuest");
		break;
		case "Last_Talk":
			dialog.text = DLG_TEXT_QB[78];
			link.l1 = DLG_TEXT_QB[79];
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
		break;
		// если догнал бриг свалил или ГГ ушел на карту
		case "Brig_DieHard":
			dialog.text = DLG_TEXT_QB[80];
			link.l1 = DLG_TEXT_QB[81];
			link.l1.go = "Brig_DieHard_1";
		break;
		case "Brig_DieHard_1":
			dialog.text = DLG_TEXT_QB[82];
			link.l1 = DLG_TEXT_QB[83];
			link.l1.go = "Brig_Late_2";
		break;
		// если догнал бриг, но утопил его
		case "Brig_Sunk":
			dialog.text = DLG_TEXT_QB[84];
			link.l1 = DLG_TEXT_QB[85];
			link.l1.go = "Brig_Sunk_1";
		break;
		case "Brig_Sunk_1":
			dialog.text = DLG_TEXT_QB[86];
			link.l1 = DLG_TEXT_QB[87];
			link.l1.go = "Brig_Late_2";
		break;
		// если Изабелла утонула с бригом, нет векселей
		case "Isabella_Sink":
			dialog.text = DLG_TEXT_QB[88];
			link.l1 = DLG_TEXT_QB[89];
			link.l1.go = "Isabella_Sink_1";
		break;
		case "Isabella_Sink_1":
			dialog.text = DLG_TEXT_QB[90];
			link.l1 = DLG_TEXT_QB[91];
			link.l1.go = "Brig_Late_2";
		break;
		// узнать что-нибудь новое о Сальватора
		case "SalvatorNews":
			dialog.text = DLG_TEXT_QB[92] + GetFullName(pchar) + DLG_TEXT_QB[93];
			link.l1 = DLG_TEXT_QB[94];
			link.l1.go = "SalvatorNews_1";
		break;
		case "SalvatorNews_1":
			dialog.text = DLG_TEXT_QB[95];
			link.l1 = DLG_TEXT_QB[96];
			link.l1.go = "SalvatorNews_2";
		break;
		case "SalvatorNews_2":
			dialog.text = DLG_TEXT_QB[97];
			link.l1 = DLG_TEXT_QB[98];
			link.l1.go = "SalvatorNews_3";
		break;
		case "SalvatorNews_3":
			dialog.text = DLG_TEXT_QB[99];
			link.l1 = DLG_TEXT_QB[100];
			link.l1.go = "SalvatorNews_4";
		break;
		case "SalvatorNews_4":
			dialog.text = DLG_TEXT_QB[101];
			link.l1 = DLG_TEXT_QB[102];
			link.l1.go = "SalvatorNews_5";
		break;
		case "SalvatorNews_5":
			dialog.text = DLG_TEXT_QB[103];
			link.l1 = DLG_TEXT_QB[104];
			link.l1.go = "SalvatorNews_6";
		break;
		case "SalvatorNews_6":
			dialog.text = DLG_TEXT_QB[105];
			link.l1 = DLG_TEXT_QB[106];
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "20");
			ChangeCharacterAddress(characterFromId("Isabella"), "nonr", "");
			QuestSetCurrentNode("Rosita", "BackRosita");
			//Изабеллу в шахту
			sld = characterFromId("Isabella");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto5");
			sld.dialog.currentnode = "IsabellaInCave";
		break;
		//Изабелла убита в церкви.
		case "IsabellaIsDead":
			dialog.text = DLG_TEXT_QB[107] + GetFullName(pchar) + DLG_TEXT_QB[108];
			link.l1 = DLG_TEXT_QB[109];
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = DLG_TEXT_QB[110];
			link.l1 = DLG_TEXT_QB[111];
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = DLG_TEXT_QB[112];
			link.l1 = DLG_TEXT_QB[113];
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
			CloseQuestHeader("Romantic_Line");
		break;
		case "IsabellaIsDead_after":
			dialog.text = DLG_TEXT_QB[114];
			link.l1 = DLG_TEXT_QB[115];
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
			npchar.lifeDay = 0;
		break;
		//если ГГ отбился в церкви
		case "IsabellaIsMyWife":
			dialog.text = DLG_TEXT_QB[116];
			link.l1 = DLG_TEXT_QB[117];
			link.l1.go = "IsabellaIsMyWife_1";
			npchar.lifeDay = 0;
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = DLG_TEXT_QB[118];
			link.l1 = DLG_TEXT_QB[119];
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = DLG_TEXT_QB[120];
			link.l1 = DLG_TEXT_QB[121];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_QB[122];
			link.l2.go = "IsabellaIsMyWife_3";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
			pchar.RomanticQuest.Atilla = "YouAreBaster";
			npchar.LifeDay = 0;
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = DLG_TEXT_QB[123] + pchar.name + DLG_TEXT_QB[124];
			link.l1 = DLG_TEXT_QB[125];
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_3":
			dialog.text = DLG_TEXT_QB[126];
			link.l1 = DLG_TEXT_QB[127];
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			dialog.text = DLG_TEXT_QB[128];
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = DLG_TEXT_QB[129];
				link.l1.go = "AddRepa_1";
			}
			if (sti(pchar.money) >= 70000)
			{
				link.l2 = DLG_TEXT_QB[130];
				link.l2.go = "AddRepa_2";
			}
			if (sti(pchar.money) >= 150000)
			{
				link.l3 = DLG_TEXT_QB[131];
				link.l3.go = "AddRepa_3";
			}
			if (sti(pchar.money) >= 300000)
			{
				link.l4 = DLG_TEXT_QB[132];
				link.l4.go = "AddRepa_4";
			}
		break;
		case "AddRepa_1":
			dialog.text = DLG_TEXT_QB[133] + pchar.name + DLG_TEXT_QB[134];
			link.l1 = DLG_TEXT_QB[135];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			ChangeCharacterReputation(pchar, -10);
		break;	
		case "AddRepa_2":
			dialog.text = DLG_TEXT_QB[136] + GetFullName(pchar) + ".";
			link.l1 = DLG_TEXT_QB[137];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -70000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 5);
		break;	
		case "AddRepa_3":
			dialog.text = DLG_TEXT_QB[138];
			link.l1 = DLG_TEXT_QB[139];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -150000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 15);
		break;
		case "AddRepa_4":
			dialog.text = DLG_TEXT_QB[140]+
				          DLG_TEXT_QB[141];
			link.l1 = DLG_TEXT_QB[142];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300000);
			pchar.RomanticQuest.Atilla = "YouAreGood";
			ChangeCharacterReputation(pchar, 30);
		break;	
	}
}
