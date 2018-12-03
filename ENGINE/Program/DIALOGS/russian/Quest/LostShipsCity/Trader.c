#include "TEXT\DIALOGS\Quest\LostShipsCity\Trader.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	//if (CheckAttribute(npchar, "quest.takeMap")) Log_SetStringToLog(DLG_TEXT_LSC[0] + npchar.quest.takeMap);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = DLG_TEXT_LSC[1];
					link.l1 = DLG_TEXT_LSC[2] + GetFullName(pchar) + DLG_TEXT_LSC[3];
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[4];
					link.l1 = DLG_TEXT_LSC[5] + GetFullName(pchar) + DLG_TEXT_LSC[6];
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[7];
				link.l1 = DLG_TEXT_LSC[8];
				link.l1.go = "Trade_exit";
				//квест получения карты -->
				if (!CheckAttribute(npchar, "quest.takeMap"))
				{
					link.l2 = DLG_TEXT_LSC[9];
					link.l2.go = "tekeMap_begin";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "mapIsToken" && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l2 = DLG_TEXT_LSC[10];
					link.l2.go = "tekeMap_off";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "discount")
				{
					link.l2 = DLG_TEXT_LSC[11] + npchar.quest.takeMap.name + DLG_TEXT_LSC[12];
					link.l2.go = "tekeMap_on";
				}
				//<-- квест получения карты
				link.l3 = DLG_TEXT_LSC[13];
				link.l3.go = "exit";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(pchar, "questTemp.LSC.goods.trader"))
				{
					link.l8 = DLG_TEXT_LSC[14];
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.goods.trader") && sti(pchar.questTemp.LSC.goods.trader))
				{
					link.l8 = DLG_TEXT_LSC[15];
					link.l8.go = "SeekGoodsOk";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[16];
					link.l8.go = "SeekCrew";
				}
				NextDiag.TempNode = "First time";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = DLG_TEXT_LSC[17] + GetFullName(npchar) + DLG_TEXT_LSC[18];
			link.l1 = DLG_TEXT_LSC[19];
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[20] + GetFullName(npchar) + DLG_TEXT_LSC[21];
			link.l1 = DLG_TEXT_LSC[22];
			link.l1.go = "exit";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date") || npchar.quest.takeMap == "changePrice")
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[23], DLG_TEXT_LSC[24], DLG_TEXT_LSC[25]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[26], DLG_TEXT_LSC[27], DLG_TEXT_LSC[28]);
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[29];
			link.l1 = DLG_TEXT_LSC[30];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[31], DLG_TEXT_LSC[32], DLG_TEXT_LSC[33]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[34], DLG_TEXT_LSC[35], DLG_TEXT_LSC[36]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[37], DLG_TEXT_LSC[38]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[39], DLG_TEXT_LSC[40], DLG_TEXT_LSC[41]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[42], DLG_TEXT_LSC[43]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[44], DLG_TEXT_LSC[45]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = DLG_TEXT_LSC[46];
			link.l1 = DLG_TEXT_LSC[47];
			link.l1.go = "SeekGoods_1";
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[48];
			link.l1 = DLG_TEXT_LSC[49];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[50];
			link.l1 = DLG_TEXT_LSC[51];
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = DLG_TEXT_LSC[52];
			link.l1 = DLG_TEXT_LSC[53];
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = DLG_TEXT_LSC[54];
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = DLG_TEXT_LSC[55];
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[56];
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		case "SeekGoods_notMoney":
			dialog.text = DLG_TEXT_LSC[57];
			link.l1 = DLG_TEXT_LSC[58];
			link.l1.go = "exit";
			pchar.questTemp.LSC.goods.trader = true;
		break;

		case "SeekGoods_5":
			dialog.text = DLG_TEXT_LSC[59];
			link.l1 = DLG_TEXT_LSC[60];
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = DLG_TEXT_LSC[61];
			link.l1 = DLG_TEXT_LSC[62];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "46");
			AddMoneyToCharacter(pchar, -40000);
			AddCharacterGoods(pchar, GOOD_FOOD, 200);
			AddCharacterGoods(pchar, GOOD_PLANKS, 50);
			AddCharacterGoods(pchar, GOOD_SAILCLOTH, 50);
			pchar.questTemp.LSC.goods.trader = false;
		break;

		case "SeekGoodsOk":
			dialog.text = DLG_TEXT_LSC[63];
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = DLG_TEXT_LSC[64];
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[65];
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[66], 
				DLG_TEXT_LSC[67], 
				DLG_TEXT_LSC[68],
                DLG_TEXT_LSC[69], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[70], 
				DLG_TEXT_LSC[71],
                DLG_TEXT_LSC[72], 
				DLG_TEXT_LSC[73], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[74];
			link.l1 = DLG_TEXT_LSC[75];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[76];
			link.l1 = DLG_TEXT_LSC[77];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[78];
			link.l1 = DLG_TEXT_LSC[79];
			link.l1.go = "exit";
		break;
		//квест получения карты Города
		case "tekeMap_begin":
			dialog.text = DLG_TEXT_LSC[80];
			link.l1 = DLG_TEXT_LSC[81];
			link.l1.go = "tekeMap_begin_1";
		break;
		case "tekeMap_begin_1":
			dialog.text = DLG_TEXT_LSC[82];
			link.l1 = DLG_TEXT_LSC[83];
			link.l1.go = "tekeMap_begin_2";
		break;
		case "tekeMap_begin_2":
			dialog.text = DLG_TEXT_LSC[84];
			link.l1 = DLG_TEXT_LSC[85];
			link.l1.go = "First time";
			npchar.quest.takeMap = "firstGiveMap";
		break;
		case "tekeMap_off":
			dialog.text = DLG_TEXT_LSC[86];
			link.l1 = DLG_TEXT_LSC[87];
			link.l1.go = "tekeMap_off_1";
		break;
		case "tekeMap_off_1":
			dialog.text = DLG_TEXT_LSC[88];
			link.l1 = DLG_TEXT_LSC[89];
			link.l1.go = "tekeMap_off_2";
		break;
		case "tekeMap_off_2":
			dialog.text = DLG_TEXT_LSC[90];
			link.l1 = DLG_TEXT_LSC[91];
			link.l1.go = "exit";
			npchar.quest.takeMap = "notTrade"; //поговорили о том, что не торгуется 
		break;
		case "tekeMap_on":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				dialog.text = DLG_TEXT_LSC[92];
				link.l1 = DLG_TEXT_LSC[93];
				link.l1.go = "tekeMap_on_1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[94] + npchar.quest.takeMap.name + DLG_TEXT_LSC[95];
				link.l1 = DLG_TEXT_LSC[96];
				link.l1.go = "exit";
			}
		break;
		case "tekeMap_on_1":
			dialog.text = DLG_TEXT_LSC[97];
			link.l1 = DLG_TEXT_LSC[98];
			link.l1.go = "exit"; 
			npchar.quest.takeMap = "changePrice"; //снизить цену
		break;

	}
}
