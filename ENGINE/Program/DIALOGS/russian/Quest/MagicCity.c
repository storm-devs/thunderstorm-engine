#include "TEXT\DIALOGS\Quest\MagicCity.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	
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

		case "exit_orient":			
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
                LAi_ActorStay(sld);
			}
			LAi_ActorTurnByLocator(npchar, npchar.location.group, npchar.location.locator);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//замечение по обнаженному оружию
		case "CitizenNotBlade":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = LinkRandPhrase(DLG_TEXT_Q[3], DLG_TEXT_Q[4], DLG_TEXT_Q[5]);
			link.l1.go = "exit";
			NextDiag.TempNode = "DesMoinesCitizen";
		break;

		//бунтующие горожане в Каракасе
		case "CaracasMan":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "CaracasMan_1";
		break;
		case "CaracasMan_1":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "CaracasMan_2";
		break;
		case "CaracasMan_2":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "CaracasMan_3";
		break;
		case "CaracasMan_3":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "exit_orient";
			DeleteAttribute(&locations[reload_location_index], "reload.l41.disable");
		break;
		//оборотень в Каракасе
		case "CaracasWervolf":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15] + GetFullName(pchar) + DLG_TEXT_Q[16];
			link.l1.go = "CaracasWervolf_1";
		break;
		case "CaracasWervolf_1":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "CaracasWervolf_2";
		break;
		case "CaracasWervolf_2":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.MC = "toCaracasPadre";
			iTemp = FindLocation("Caracas_tavern");
			DeleteAttribute(&locations[iTemp], "reload.l1.disable");
			DeleteAttribute(&locations[iTemp], "reload.l4.disable");
			LocatorReloadEnterDisable("Caracas_town", "reload7_back", false);
			locations[iTemp].reload.l2.disable = true;
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.dialog.currentnode = "CaracasMan2";  
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorWaitDialog(sld, pchar);
			}
		break;
		//горожане Каракаса на выходе из таверны
		case "CaracasMan2":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "exit_orient";
		break;
		//охрана Дес-Мойнеса в бухте
		case "ShoreGuard":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "ShoreGuard_1";
		break;
		case "ShoreGuard_1":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "ShoreGuard_2";
		break;
		case "ShoreGuard_2":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "ShoreGuard_3";
		break;
		case "ShoreGuard_3":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("MagicCity", "3");
			DialogExit();
		break;
		//жители Дес-Мойнеса обычные
		case "DMCitiz":
			NextDiag.TempNode = "DMCitiz";
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[29], DLG_TEXT_Q[30], DLG_TEXT_Q[31]);
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "DesMoinesCitizen_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[33], DLG_TEXT_Q[34], DLG_TEXT_Q[35]);
				link.l1 = DLG_TEXT_Q[36];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[37], DLG_TEXT_Q[38], DLG_TEXT_Q[39]);
				link.l1 = DLG_TEXT_Q[40];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = DLG_TEXT_Q[41];
				link.l1 = DLG_TEXT_Q[42];
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesCitizen_1":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "DesMoinesCitizen_2";
		break;
		case "DesMoinesCitizen_2":
			dialog.text = DLG_TEXT_Q[45];
			link.l1 = DLG_TEXT_Q[46];
			link.l1.go = "exit";
		break;
		//жители Дес-Мойнеса скелеты
		case "DMSkel":
			NextDiag.TempNode = "DMSkel";
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[47], DLG_TEXT_Q[48], DLG_TEXT_Q[49]);
			link.l1 = DLG_TEXT_Q[50];
			link.l1.go = "DesMoinesSkel_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[51], DLG_TEXT_Q[52], DLG_TEXT_Q[53]);
				link.l1 = DLG_TEXT_Q[54];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister" || pchar.questTemp.MC == "toSeekSkull" || pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_Q[55], DLG_TEXT_Q[56], DLG_TEXT_Q[57]);
				link.l1 = DLG_TEXT_Q[58];
				link.l1.go = "exit";
			}
		break;
		case "DesMoinesSkel_1":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "exit";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", true);
		break;
		//глава городка обычный
		case "DMCitizHead":
			NextDiag.TempNode = "DMCitizHead";
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "DMCitizHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = DLG_TEXT_Q[63];
				link.l1 = DLG_TEXT_Q[64];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = DLG_TEXT_Q[65];
				link.l1 = DLG_TEXT_Q[66];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = DLG_TEXT_Q[67];
				link.l1 = DLG_TEXT_Q[68];
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = DLG_TEXT_Q[69];
				link.l1 = DLG_TEXT_Q[70];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = DLG_TEXT_Q[71];
				link.l1 = DLG_TEXT_Q[72];
				link.l1.go = "DMHeadOver";
			}
			if (CheckAttribute(pchar, "questTemp.MC.DesMoines"))
			{
				dialog.text = DLG_TEXT_Q[73];
				link.l1 = DLG_TEXT_Q[74];
				link.l1.go = "exit";
			}
		break;
		case "DMCitizHead_1":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "DMCitizHead_2";
		break;
		case "DMCitizHead_2":
			dialog.text = DLG_TEXT_Q[77];
			link.l1 = DLG_TEXT_Q[78];
			link.l1.go = "DMCitizHead_3";
		break;
		case "DMCitizHead_3":
			dialog.text = DLG_TEXT_Q[79];
			link.l1 = DLG_TEXT_Q[80];
			link.l1.go = "exit";
		break;

		case "FoundLiz":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[81], 
				DLG_TEXT_Q[82], 
				DLG_TEXT_Q[83],
                DLG_TEXT_Q[84], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[85], 
				DLG_TEXT_Q[86],
                DLG_TEXT_Q[87], 
				DLG_TEXT_Q[88], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FoundLiz_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FoundLiz_1":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "FoundLiz_2";
		break;
		case "FoundLiz_2":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "exit";
		break;

		case "DMHeadOver":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "DMHeadOver_1";
		break;
		case "DMHeadOver_1":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "DMHeadOver_2";
			link.l2 = DLG_TEXT_Q[97];
			link.l2.go = "DMHeadOver_3";
		break;
		case "DMHeadOver_2":
			dialog.text = DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 20);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;
		case "DMHeadOver_3":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("MagicCity", "9");
			CloseQuestHeader("MagicCity");
			pchar.questTemp.MC.DesMoines = true;
		break;

		//глава городка скелет
		case "DMSkelHead":
			NextDiag.TempNode = "DMSkelHead";
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "DMSkelHead_1";
			if (pchar.questTemp.MC == "toByeBye")
			{
				dialog.text = DLG_TEXT_Q[104];
				link.l1 = DLG_TEXT_Q[105];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSister")
			{
				dialog.text = DLG_TEXT_Q[106];
				link.l1 = DLG_TEXT_Q[107];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.MC == "toSeekSkull")
			{
				dialog.text = DLG_TEXT_Q[108];
				link.l1 = DLG_TEXT_Q[109];
				link.l1.go = "FoundLiz";
			}
			if (pchar.questTemp.MC == "toSeekQueen")
			{
				dialog.text = DLG_TEXT_Q[110];
				link.l1 = DLG_TEXT_Q[111];
				link.l1.go = "exit";
			}
		break;
		case "DMSkelHead_1":
			dialog.text = DLG_TEXT_Q[112];
			link.l1 = DLG_TEXT_Q[113];
			link.l1.go = "DMSkelHead_2";
		break;
		case "DMSkelHead_2":
			dialog.text = DLG_TEXT_Q[114]+
				DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "DMSkelHead_3";
		break;
		case "DMSkelHead_3":
			dialog.text = DLG_TEXT_Q[117];
			link.l1 = DLG_TEXT_Q[118];
			link.l1.go = "DMSkelHead_4";
		break;
		case "DMSkelHead_4":
			dialog.text = DLG_TEXT_Q[119];
			link.l1 = DLG_TEXT_Q[120];
			link.l1.go = "DMSkelHead_5";
		break;
		case "DMSkelHead_5":
			dialog.text = DLG_TEXT_Q[121];
			link.l1 = DLG_TEXT_Q[122];
			link.l1.go = "DMSkelHead_6";
		break;
		case "DMSkelHead_6":
			dialog.text = DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "DMSkelHead_7";
		break;
		case "DMSkelHead_7":
			dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "DMSkelHead_8";		
			link.l2 = DLG_TEXT_Q[127];
			link.l2.go = "DMSkelHead_bye";
			LocatorReloadEnterDisable("DesMoines_town", "reload1_back", false); //выпускаем из города
		break;

		case "DMSkelHead_bye":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -20);
			AddQuestRecord("MagicCity", "4");
			pchar.questTemp.MC = "toByeBye"; //флаг квеста	
		break;

		case "DMSkelHead_8":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "DMSkelHead_9";
		break;
		case "DMSkelHead_9":
			dialog.text = DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "DMSkelHead_10";
		break;
		case "DMSkelHead_10":
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "DMSkelHead_11";
		break;
		case "DMSkelHead_11":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "DMSkelHead_12";
		break;
		case "DMSkelHead_12":
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("MagicCity", "5");
			pchar.questTemp.MC = "toSeekSister"; //флаг квеста	
			LocatorReloadEnterDisable("Charles_town", "housePirate", false);
			//ставим Лиз Шеппард
			sld = GetCharacter(NPC_GenerateCharacter("LizSheppard", "BaynesDaughter", "woman", "towngirl", 10, ENGLAND, -1, false));
			sld.name = DLG_TEXT_Q[140];
			sld.lastname = DLG_TEXT_Q[141];		
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "LizBegin"; 
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Charles_PirateHouse", "goto", "goto1");
		break;
		//Элизабет Шеппард
		case "LizBegin":
			dialog.text = DLG_TEXT_Q[142];
			link.l1 = DLG_TEXT_Q[143] + GetFullName(pchar) + DLG_TEXT_Q[144];
			link.l1.go = "LizBegin_1";
		break;
		case "LizBegin_1":
			dialog.text = DLG_TEXT_Q[145];
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "LizBegin_2";
		break;
		case "LizBegin_2":
			dialog.text = DLG_TEXT_Q[147];
			link.l1 = DLG_TEXT_Q[148];
			link.l1.go = "LizBegin_3";
		break;
		case "LizBegin_3":
			dialog.text = DLG_TEXT_Q[149];
			link.l1 = DLG_TEXT_Q[150];
			link.l1.go = "LizBegin_4";
		break;
		case "LizBegin_4":
			dialog.text = DLG_TEXT_Q[151];
			link.l1 = DLG_TEXT_Q[152];
			link.l1.go = "LizBegin_5";
		break;
		case "LizBegin_5":
			dialog.text = DLG_TEXT_Q[153];
			link.l1 = DLG_TEXT_Q[154];
			link.l1.go = "LizBegin_6";
		break;
		case "LizBegin_6":
			dialog.text = DLG_TEXT_Q[155];
			link.l1 = DLG_TEXT_Q[156];
			link.l1.go = "LizBegin_7";
		break;
		case "LizBegin_7":
			dialog.text = DLG_TEXT_Q[157];
			link.l1 = DLG_TEXT_Q[158];
			link.l1.go = "LizBegin_8";
		break;
		case "LizBegin_8":
			dialog.text = DLG_TEXT_Q[159];
			link.l1 = DLG_TEXT_Q[160];
			link.l1.go = "LizBegin_9";
		break;
		case "LizBegin_9":
			dialog.text = DLG_TEXT_Q[161];
			link.l1 = DLG_TEXT_Q[162];
			link.l1.go = "LizBegin_10";
		break;
		case "LizBegin_10":
			dialog.text = DLG_TEXT_Q[163];
			link.l1 = DLG_TEXT_Q[164];
			link.l1.go = "LizBegin_11";
		break;
		case "LizBegin_11":
			dialog.text = DLG_TEXT_Q[165];
			link.l1 = DLG_TEXT_Q[166];
			link.l1.go = "LizBegin_12";
		break;
		case "LizBegin_12":
			dialog.text = DLG_TEXT_Q[167];
			link.l1 = DLG_TEXT_Q[168];
			link.l1.go = "LizBegin_13";
		break;
		case "LizBegin_13":
			dialog.text = DLG_TEXT_Q[169];
			link.l1 = DLG_TEXT_Q[170];
			link.l1.go = "LizBegin_14";
		break;
		case "LizBegin_14":
			dialog.text = DLG_TEXT_Q[171];
			link.l1 = DLG_TEXT_Q[172];
			link.l1.go = "LizBegin_15";
		break;
		case "LizBegin_15":
			dialog.text = DLG_TEXT_Q[173];
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = DLG_TEXT_Q[174];
				link.l1.go = "LizBegin_haveSkull";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[175];
				link.l1.go = "LizBegin_seekSkull";
			}
		break;
		
		case "LizBegin_SeekSkull":
			dialog.text = DLG_TEXT_Q[176];
			link.l1 = DLG_TEXT_Q[177];
			link.l1.go = "LizBegin_16";
			ChangeCharacterReputation(pchar, 3);
		break;
		case "LizBegin_16":
			dialog.text = DLG_TEXT_Q[178];
			link.l1 = DLG_TEXT_Q[179];
			link.l1.go = "exit";
			AddQuestRecord("MagicCity", "6");
			pchar.questTemp.MC = "toSeekSkull"; //флаг квеста	
			NextDiag.TempNode = "LizCheckSkull";
		break;

		case "LizBegin_haveSkull":
			dialog.text = DLG_TEXT_Q[180];
			link.l1 = DLG_TEXT_Q[181];
			link.l1.go = "LizCheckSkull_1";
		break;
		//проверка черепа
		case "LizCheckSkull":
			dialog.text = DLG_TEXT_Q[182];
			if (CheckCharacterItem(pchar, "SkullAztec"))
			{
				link.l1 = DLG_TEXT_Q[183];
				link.l1.go = "LizCheckSkull_Ok";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[184];
				link.l1.go = "exit";
			}
		break;
		case "LizCheckSkull_Ok":
			dialog.text = DLG_TEXT_Q[185];
			link.l1 = DLG_TEXT_Q[186];
			link.l1.go = "LizCheckSkull_1";
		break;
		case "LizCheckSkull_1":
			dialog.text = DLG_TEXT_Q[187];
			link.l1 = DLG_TEXT_Q[188];
			link.l1.go = "LizCheckSkull_2";
		break;
		case "LizCheckSkull_2":
			dialog.text = DLG_TEXT_Q[189];
			link.l1 = DLG_TEXT_Q[190];
			link.l1.go = "LizCheckSkull_3";
		break;
		case "LizCheckSkull_3":
			dialog.text = DLG_TEXT_Q[191];
			link.l1 = DLG_TEXT_Q[192];
			link.l1.go = "exit";
			SetDanielleInWorld();
			AddQuestRecord("MagicCity", "7");
			pchar.questTemp.MC = "toSeekQueen"; //флаг квеста	
			NextDiag.TempNode = "LizSeekQueen";
		break;
		case "LizSeekQueen":
			dialog.text = DLG_TEXT_Q[193];
			link.l1 = DLG_TEXT_Q[194];
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "over")
			{
				dialog.text = DLG_TEXT_Q[195];
				link.l1 = DLG_TEXT_Q[196];
				link.l1.go = "LizOver";
			}
		break;

		case "LizOver":
			dialog.text = DLG_TEXT_Q[197];
			link.l1 = DLG_TEXT_Q[198];
			link.l1.go = "LizOver_1";
		break;
		case "LizOver_1":
			dialog.text = DLG_TEXT_Q[199];
			link.l1 = DLG_TEXT_Q[200];
			link.l1.go = "LizOver_2";
		break;
		case "LizOver_2":
			dialog.text = DLG_TEXT_Q[201];
			link.l1 = DLG_TEXT_Q[202];
			link.l1.go = "exit";
			npchar.lifeDay = 30;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			NextDiag.TempNode = "LizOver_end";
		break;
		case "LizOver_end":
			dialog.text = DLG_TEXT_Q[203];
			link.l1 = DLG_TEXT_Q[204];
			link.l1.go = "exit";
		break;
		//Даниэль на абордаже
		case "DanAbordage":
			dialog.text = DLG_TEXT_Q[205];
			link.l1 = DLG_TEXT_Q[206];
			link.l1.go = "DanAbordage_1";
		break;
		case "DanAbordage_1":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "DanAbordage_2";
		break;
		case "DanAbordage_2":
			dialog.text = DLG_TEXT_Q[209];
			link.l1 = DLG_TEXT_Q[210];
			link.l1.go = "DanAbordage_3";
		break;
		case "DanAbordage_3":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "DanAbordage_4";
		break;
		case "DanAbordage_4":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214] + GetFullName(pchar) + DLG_TEXT_Q[215];
			link.l1.go = "DanAbordage_5";
		break;
		case "DanAbordage_5":
			dialog.text = DLG_TEXT_Q[216]+
				DLG_TEXT_Q[217]+
				DLG_TEXT_Q[218]+
				DLG_TEXT_Q[219];
			link.l1 = DLG_TEXT_Q[220];
			link.l1.go = "DanAbordage_6";
		break;
		case "DanAbordage_6":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "DanAbordage_7";
		break;
		case "DanAbordage_7":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "DanAbordage_8";
		break;
		case "DanAbordage_8":
			dialog.text = DLG_TEXT_Q[225];
			link.l1 = DLG_TEXT_Q[226];
			link.l1.go = "DanAbordage_10";
		break;
		case "DanAbordage_10":
			dialog.text = DLG_TEXT_Q[227];
			link.l1 = DLG_TEXT_Q[228];
			link.l1.go = "DanAbordage_11";
		break;
		case "DanAbordage_11":
			dialog.text = DLG_TEXT_Q[229];
			link.l1 = DLG_TEXT_Q[230];
			link.l1.go = "DanAbordage_12";
		break;
		case "DanAbordage_12":
			dialog.text = DLG_TEXT_Q[231];
			link.l1 = DLG_TEXT_Q[232];
			link.l1.go = "DanAbordage_13";
		break;
		case "DanAbordage_13":
			dialog.text = DLG_TEXT_Q[233];
			link.l1 = DLG_TEXT_Q[234];
			link.l1.go = "DanAbordage_14";
		break;
		case "DanAbordage_14":
			//чистим базу нпс-кэпов  -->
			DeleteAttribute(NullCharacter, "capitainBase.Danielle");
			//<-- чистим базу нпс-кэпов
			AddQuestRecord("MagicCity", "8");
			pchar.questTemp.MC = "over"; //флаг квеста
			sld = GetCharacter(NPC_GenerateCharacter("DanielleOff", "Danielle", "woman", "woman", 30, PIRATE, -1, true));
			sld.name = DLG_TEXT_Q[235];
			sld.lastname = DLG_TEXT_Q[236];
			sld.greeting = "Gr_Danielle";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			SetSelfSkill(sld, 90, 60, 1, 60, 90);
			SetShipSkill(sld, 100, 10, 90, 80, 90, 20, 70, 80, 70);
			SetSPECIAL(sld, 6, 9, 9, 10, 8, 8, 10);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "IronWill");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "FastReload");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "ShipSpeedUp");
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			QuestAboardCabinDialogNotBattle(); 
            DialogExit();
		break;	
	}
}

void SetDanielleInWorld()
{
	//создаем кэпов
	ref sld = GetCharacter(NPC_GenerateCharacter("Danielle", "Danielle", "woman", "woman", 30, PIRATE, -1, true));
	sld.name = DLG_TEXT_Q[237];
	sld.lastname = DLG_TEXT_Q[238];
	sld.dialog.filename   = "Quest\MagicCity.c";
	sld.dialog.currentnode   = "DanAbordage";
	sld.greeting = "";
	sld.GenQuest.CrewSkelMode = true; //команда - скелеты 
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, DLG_TEXT_Q[239], CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
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
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "SantaCatalina"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo(DLG_TEXT_Q[240] + sld.city + DLG_TEXT_Q[241] + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = DLG_TEXT_Q[242];
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "Danielle"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "MagicCity"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "MagicCity"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

