#include "TEXT\DIALOGS\HouseEnc_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = DLG_TEXT_BASE[10];
					link.l1 = DLG_TEXT_BASE[11];
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[12];
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14], DLG_TEXT_BASE[15]);
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[16], 
						DLG_TEXT_BASE[17], 
						DLG_TEXT_BASE[18],
						DLG_TEXT_BASE[19], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[20], 
						DLG_TEXT_BASE[21],
						DLG_TEXT_BASE[22], 
						DLG_TEXT_BASE[23], npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[24], 
						DLG_TEXT_BASE[25], 
						DLG_TEXT_BASE[26],
						DLG_TEXT_BASE[27], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[28], 
						DLG_TEXT_BASE[29],
						DLG_TEXT_BASE[30], 
						DLG_TEXT_BASE[31], npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = DLG_TEXT_BASE[32] + GetFullName(npchar) + DLG_TEXT_BASE[33];
			link.l1 = GetFullName(pchar) + DLG_TEXT_BASE[34];
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[35], DLG_TEXT_BASE[36], DLG_TEXT_BASE[37]);
			link.l1 = DLG_TEXT_BASE[38];
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[39], DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]), 
					LinkRandPhrase(DLG_TEXT_BASE[42], DLG_TEXT_BASE[43], DLG_TEXT_BASE[44]));
				link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[45], DLG_TEXT_BASE[46]), 
					RandPhraseSimple(DLG_TEXT_BASE[47], DLG_TEXT_BASE[48]));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = DLG_TEXT_BASE[49];
					link.l1 = DLG_TEXT_BASE[50];
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = DLG_TEXT_BASE[51];
					link.l1 = DLG_TEXT_BASE[52];
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[53] + GetFullName(npchar) + DLG_TEXT_BASE[54], 
						DLG_TEXT_BASE[55], 
						DLG_TEXT_BASE[56],
						DLG_TEXT_BASE[57], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + DLG_TEXT_BASE[58], 
						DLG_TEXT_BASE[59],
						DLG_TEXT_BASE[60], 
						DLG_TEXT_BASE[61], npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[62], 
						DLG_TEXT_BASE[63], 
						DLG_TEXT_BASE[64],
						DLG_TEXT_BASE[65], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[66], 
						DLG_TEXT_BASE[67],
						DLG_TEXT_BASE[68], 
						DLG_TEXT_BASE[69], npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[76], DLG_TEXT_BASE[77], DLG_TEXT_BASE[78]), 
					LinkRandPhrase(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80], DLG_TEXT_BASE[81]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[82], DLG_TEXT_BASE[83] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85]));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = DLG_TEXT_BASE[86];
				link.l1 = DLG_TEXT_BASE[87];
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[88] + GetFullName(npchar) + DLG_TEXT_BASE[89], 
					DLG_TEXT_BASE[90], 
					DLG_TEXT_BASE[91],
					RandPhraseSimple(DLG_TEXT_BASE[92], DLG_TEXT_BASE[93]), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[94], 
					DLG_TEXT_BASE[95],
					DLG_TEXT_BASE[96], 
					DLG_TEXT_BASE[97], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
				//открывание двери верфи по квесту промышленного шпионажа
				if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
				{
					link.l2 = DLG_TEXT_BASE[98];
					link.l2.go = "ShipyardsMap_1";
					pchar.questTemp.different.ShipyardsMap = "toResult";
				}
			}
		break;
		case "ShipyardsMap_1":
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = DLG_TEXT_BASE[101];
				link.l1 = DLG_TEXT_BASE[102];
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingLight", 5);
				AddCharacterExpToSkill(pchar, "Fencing", 5);
				AddCharacterExpToSkill(pchar, "FencingHeavy", 5);
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[103];
				link.l1 = DLG_TEXT_BASE[104];
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = DLG_TEXT_BASE[106];
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = DLG_TEXT_BASE[107] + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + DLG_TEXT_BASE[108];
			link.l1 = DLG_TEXT_BASE[109];
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = DLG_TEXT_BASE[110];
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = DLG_TEXT_BASE[111];
			link.l1 = DLG_TEXT_BASE[112];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
