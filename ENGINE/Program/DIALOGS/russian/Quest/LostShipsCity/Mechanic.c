#include "TEXT\DIALOGS\Quest\LostShipsCity\Mechanic.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	string sTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_LSC[0];
			link.l1 = DLG_TEXT_LSC[1];
			link.l1.go = "FT_1";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[2], DLG_TEXT_LSC[3], DLG_TEXT_LSC[4]);
			link.l1 = DLG_TEXT_LSC[5];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[6];
			link.l1 = DLG_TEXT_LSC[7];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[8], DLG_TEXT_LSC[9], DLG_TEXT_LSC[10]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[11], DLG_TEXT_LSC[12], DLG_TEXT_LSC[13]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[14], DLG_TEXT_LSC[15]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[16], DLG_TEXT_LSC[17], DLG_TEXT_LSC[18]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[19], DLG_TEXT_LSC[20]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[21], DLG_TEXT_LSC[22]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		case "FT_1":
			dialog.text = DLG_TEXT_LSC[23];
			link.l1 = DLG_TEXT_LSC[24] + GetFullName(pchar) + DLG_TEXT_LSC[25];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[26];
			link.l1 = DLG_TEXT_LSC[27];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[28];
			link.l1 = DLG_TEXT_LSC[29];
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = DLG_TEXT_LSC[30];
			link.l1 = DLG_TEXT_LSC[31];
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = DLG_TEXT_LSC[32];
			link.l1 = DLG_TEXT_LSC[33];
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = DLG_TEXT_LSC[34];
			link.l1 = DLG_TEXT_LSC[35];
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = DLG_TEXT_LSC[36];
			link.l1 = DLG_TEXT_LSC[37];
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = DLG_TEXT_LSC[38];
			link.l1 = DLG_TEXT_LSC[39];
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = DLG_TEXT_LSC[40];
			link.l1 = DLG_TEXT_LSC[41];
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = DLG_TEXT_LSC[42];
			link.l1 = DLG_TEXT_LSC[43];
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = DLG_TEXT_LSC[44];
			link.l1 = DLG_TEXT_LSC[45];
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = DLG_TEXT_LSC[46];
			link.l1 = DLG_TEXT_LSC[47];
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = DLG_TEXT_LSC[48];
			link.l1 = DLG_TEXT_LSC[49];
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = DLG_TEXT_LSC[50];
			link.l1 = DLG_TEXT_LSC[51];
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = DLG_TEXT_LSC[52];
			link.l1 = DLG_TEXT_LSC[53];
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = DLG_TEXT_LSC[54];
			link.l1 = DLG_TEXT_LSC[55];
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = DLG_TEXT_LSC[56];
			link.l1 = DLG_TEXT_LSC[57];
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = DLG_TEXT_LSC[58];
			link.l1 = DLG_TEXT_LSC[59];
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = DLG_TEXT_LSC[60];
			link.l1 = DLG_TEXT_LSC[61];
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = DLG_TEXT_LSC[62];
			link.l1 = DLG_TEXT_LSC[63];
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = DLG_TEXT_LSC[64];
			link.l1 = DLG_TEXT_LSC[65];
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = DLG_TEXT_LSC[66];
			link.l1 = DLG_TEXT_LSC[67];
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = DLG_TEXT_LSC[68];
			link.l1 = DLG_TEXT_LSC[69];
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = DLG_TEXT_LSC[70];
			link.l1 = DLG_TEXT_LSC[71];
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = DLG_TEXT_LSC[72];
			link.l1 = DLG_TEXT_LSC[73];
			link.l1.go = "FT_26";
		break;
		case "FT_26":
			dialog.text = DLG_TEXT_LSC[74];
			link.l1 = DLG_TEXT_LSC[75];
			link.l1.go = "FT_27";
		break;
		case "FT_27":
			dialog.text = DLG_TEXT_LSC[76];
			link.l1 = DLG_TEXT_LSC[77];
			link.l1.go = "FT_28";
		break;
		case "FT_28":
			dialog.text = DLG_TEXT_LSC[78];
			link.l1 = DLG_TEXT_LSC[79];
			link.l1.go = "FT_29";
		break;
		case "FT_29":
			dialog.text = DLG_TEXT_LSC[80];
			link.l1 = DLG_TEXT_LSC[81];
			link.l1.go = "FT_30";
		break;
		case "FT_30":
			dialog.text = DLG_TEXT_LSC[82];
			link.l1 = DLG_TEXT_LSC[83];
			link.l1.go = "FT_30_1";
		break;
		case "FT_30_1":
			dialog.text = DLG_TEXT_LSC[84];
			link.l1 = DLG_TEXT_LSC[85];
			link.l1.go = "FT_31";
		break;
		case "FT_31":
			dialog.text = DLG_TEXT_LSC[86];
			link.l1 = DLG_TEXT_LSC[87];
			link.l1.go = "FT_32";
		break;
		case "FT_32":
			dialog.text = DLG_TEXT_LSC[88];
			link.l1 = DLG_TEXT_LSC[89];
			link.l1.go = "FT_33";
		break;
		case "FT_33":
			dialog.text = DLG_TEXT_LSC[90];
			link.l1 = DLG_TEXT_LSC[91];
			link.l1.go = "FT_34";
		break;
		case "FT_34":
			dialog.text = DLG_TEXT_LSC[92];
			link.l1 = DLG_TEXT_LSC[93];
			link.l1.go = "FT_35";
		break;
		case "FT_35":
			dialog.text = DLG_TEXT_LSC[94];
			link.l1 = DLG_TEXT_LSC[95];
			link.l1.go = "exit";
			NextDiag.TempNode = "CheckMillion";
			pchar.questTemp.LSC = "fromMechanicToAdmiral";
			Npchar.quest.money = 0; //счетчик бабла, отданного Механику
			AddQuestRecord("ISS_MainLine", "40");
		break;

		//проверка миллиона
		case "CheckMillion":
			dialog.text = DLG_TEXT_LSC[96];
			if (sti(pchar.money) < 20000)
			{
				link.l1 = DLG_TEXT_LSC[97];
				link.l1.go = "CheckMillion_noMoney";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[98];
				link.l1.go = "OffM_GiveMoney";
			}
			NextDiag.TempNode = "CheckMillion";
		break;
		case "CheckMillion_noMoney":
			dialog.text = DLG_TEXT_LSC[99];
			link.l1 = DLG_TEXT_LSC[100];
			link.l1.go = "exit";
		break;
		case "OffM_GiveMoney":
			dialog.text = DLG_TEXT_LSC[101];
			link.l1 = "";
			Link.l1.edit = 6;
			link.l1.go = "OffM_GiveMoney_1";			
		break;
		case "OffM_GiveMoney_1":
			iTemp = sti(dialogEditStrings[6]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_LSC[102];
				link.l1 = DLG_TEXT_LSC[103];
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = DLG_TEXT_LSC[104];
				link.l1 = DLG_TEXT_LSC[105];
				link.l1.go = "exit";
				break;
			}
			Npchar.quest.money = sti(Npchar.quest.money) + iTemp;
			AddMoneyToCharacter(pchar, -iTemp);
			if (sti(Npchar.quest.money) < 1500000)
			{
				dialog.text = DLG_TEXT_LSC[106] + FindRussianMoneyString(iTemp) + DLG_TEXT_LSC[107] + FindRussianMoneyString(sti(Npchar.quest.money)) + DLG_TEXT_LSC[108] + FindRussianMoneyString(1500000 - sti(Npchar.quest.money)) + ".";
				link.l1 = DLG_TEXT_LSC[109];
				link.l1.go = "exit";
				AddQuestRecord("ISS_MainLine", "41");
				AddQuestUserData("ISS_MainLine", "iMoney1", sti(Npchar.quest.money));
				AddQuestUserData("ISS_MainLine", "iMoney2", 1500000 - sti(Npchar.quest.money));
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[110];
				link.l1 = DLG_TEXT_LSC[111];
				link.l1.go = "FreeCorvett";
			}
		break;
		//освобождние корвета
		case "FreeCorvett":
			dialog.text = DLG_TEXT_LSC[112];
			link.l1 = DLG_TEXT_LSC[113];
			link.l1.go = "FreeCorvett_1";
		break;
		case "FreeCorvett_1":
			dialog.text = DLG_TEXT_LSC[114];
			link.l1 = DLG_TEXT_LSC[115];
			link.l1.go = "FreeCorvett_2";
		break;
		case "FreeCorvett_2":
			dialog.text = DLG_TEXT_LSC[116];
			link.l1 = DLG_TEXT_LSC[117];
			link.l1.go = "FreeCorvett_3";
		break;
		case "FreeCorvett_3":
			dialog.text = DLG_TEXT_LSC[118];
			link.l1 = DLG_TEXT_LSC[119];
			link.l1.go = "FreeCorvett_4";
		break;
		case "FreeCorvett_4":
			dialog.text = DLG_TEXT_LSC[120];
			link.l1 = DLG_TEXT_LSC[121];
			link.l1.go = "FreeCorvett_5";
		break;
		case "FreeCorvett_5":
			dialog.text = DLG_TEXT_LSC[122];
			link.l1 = DLG_TEXT_LSC[123];
			link.l1.go = "FreeCorvett_6";
		break;
		case "FreeCorvett_6":
			dialog.text = DLG_TEXT_LSC[124];
			link.l1 = DLG_TEXT_LSC[125];
			link.l1.go = "FreeCorvett_7";
		break;
		case "FreeCorvett_7":
			dialog.text = DLG_TEXT_LSC[126];
			link.l1 = DLG_TEXT_LSC[127];
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor";
			pchar.questTemp.LSC = "toUnderwater";
			pchar.questTemp.LSC.immersions = 0; //количество совершенных погружений
			pchar.questTemp.LSC.immersions.model = pchar.model; //запомним модельку ГГ
			pchar.questTemp.LSC.immersions.pay = true; //оплачено
			pchar.questTemp.LSC.immersions.pinion = false; //флаг найденной шестеренки
			AddQuestRecord("ISS_MainLine", "42");
			pchar.Ship.Type = GenerateShip(SHIP_CORVETTE_QUEST, false);
			SetBaseShipData(pchar);
			pchar.Ship.name = DLG_TEXT_LSC[128];
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
			SetCharacterGoods(pchar, GOOD_BALLS, 0);
			SetCharacterGoods(pchar, GOOD_GRAPES, 0);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
			SetCharacterGoods(pchar, GOOD_BOMBS, 0);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 0);
			SetCharacterGoods(pchar, GOOD_PLANKS, 0);
			SetCharacterGoods(pchar, GOOD_POWDER, 0);
			SetCharacterGoods(pchar, GOOD_FOOD, 0);
			SetCharacterGoods(pchar, GOOD_WEAPON, 0);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 0);
			SetCrewQuantity(pchar, 0);
			AddSimpleRumourCityTip(DLG_TEXT_LSC[129], "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(DLG_TEXT_LSC[130], "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(DLG_TEXT_LSC[131], "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(DLG_TEXT_LSC[132], "LostShipsCity", 10, 1, "LSC", "");		
			// нулим предметы в каюте
			ref loc;
			int n;
			if (Pchar.SystemInfo.CabinType != "")
			{
				loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

				for (n = 1; n <= 4; n++)
				{
					sTemp = "box" + n;
					DeleteAttribute(loc, sTemp + ".items");
					loc.(sTemp).items = "";
					loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
					loc.(sTemp).money = 0;
				}
			}
			loc = &locations[FindLocation("My_Deck")];
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}	
		break;
		//
		case "takeArmor":
			dialog.text = DLG_TEXT_LSC[133];
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = DLG_TEXT_LSC[134];
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[135];
				link.l1.go = "DeepAgain";			
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = DLG_TEXT_LSC[136];
					link.l2.go = "FoundPinion";
				}
			}
		break;

		case "DeepAgain":
			dialog.text = DLG_TEXT_LSC[137];
			link.l1 = DLG_TEXT_LSC[138];
			link.l1.go = "DeepAgain_1";
		break;
		case "DeepAgain_1":
			dialog.text = DLG_TEXT_LSC[139];
			link.l1 = DLG_TEXT_LSC[140];
			link.l1.go = "DeepAgain_2";
		break;
		case "DeepAgain_2":
			dialog.text = DLG_TEXT_LSC[141];
			link.l1 = DLG_TEXT_LSC[142];
			link.l1.go = "DeepAgain_3";
		break;
		case "DeepAgain_3":
			dialog.text = DLG_TEXT_LSC[143];
			link.l1 = DLG_TEXT_LSC[144];
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "takeArmor2":
			dialog.text = DLG_TEXT_LSC[145];
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = DLG_TEXT_LSC[146];
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[147];
				link.l1.go = "DeepAgain2";			
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = DLG_TEXT_LSC[148];
					link.l2.go = "FoundPinion";
				}
			}
			if (sti(pchar.questTemp.LSC.immersions.pinion))
			{
				link.l3 = DLG_TEXT_LSC[149];
				link.l3.go = "endImmersion";
			}
		break;

		case "DeepAgain2":
			dialog.text = DLG_TEXT_LSC[150];
			if (sti(pchar.money) >= 30000)
			{
				link.l1 = DLG_TEXT_LSC[151];
				link.l1.go = "DeepAgain2_1";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[152];
				link.l1.go = "exit";
			}
		break;
		case "DeepAgain2_1":
			dialog.text = DLG_TEXT_LSC[153];
			link.l1 = DLG_TEXT_LSC[154];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -30000);
			SaveCurrentQuestDateParam("questTemp.LSC.immersions");
			NextDiag.TempNode = "readyArmor";
		break;
		case "readyArmor":
			if (GetQuestPastDayParam("questTemp.LSC.immersions") > 1)
			{
				dialog.text = DLG_TEXT_LSC[155];
				link.l1 = DLG_TEXT_LSC[156];
				link.l1.go = "exit";
				pchar.questTemp.LSC.immersions.pay = true; //оплачено
				NextDiag.TempNode = "takeArmor2";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[157];
				link.l1 = DLG_TEXT_LSC[158];
				link.l1.go = "exit";
			}
		break;

		case "FoundPinion":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "FoundPinion_1";
		break;
		case "FoundPinion_1":
			dialog.text = DLG_TEXT_LSC[161];
			link.l1 = DLG_TEXT_LSC[162];
			link.l1.go = "FoundPinion_deep";
			link.l2 = DLG_TEXT_LSC[163];
			link.l2.go = "endImmersion";
			TakeItemFromCharacter(pchar, "Pinion");
			pchar.questTemp.LSC.immersions.pinion = true; //нашел шестеренку
			AddQuestRecord("ISS_MainLine", "44");
		break;
		case "FoundPinion_deep":
			dialog.text = DLG_TEXT_LSC[164];
			link.l1 = DLG_TEXT_LSC[165];
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "endImmersion":
			dialog.text = DLG_TEXT_LSC[166];
			link.l1 = DLG_TEXT_LSC[167];
			link.l1.go = "endImmersion_1";
		break;
		case "endImmersion_1":
			dialog.text = DLG_TEXT_LSC[168];
			link.l1 = DLG_TEXT_LSC[169];
			link.l1.go = "endImmersion_2";
		break;
		case "endImmersion_2":
			dialog.text = DLG_TEXT_LSC[170];
			link.l1 = DLG_TEXT_LSC[171];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.immersions");
			AddQuestRecord("ISS_MainLine", "45");
			pchar.questTemp.LSC = "toSeekGoods";
			NextDiag.TempNode = "takeGoods";
		break;
		//комплектование корвета товарами
		case "takeGoods":
			NextDiag.TempNode = "takeGoods";
			dialog.text = DLG_TEXT_LSC[172];
			npchar.quest.LSC.Balls = false;
			npchar.quest.LSC.Grapes = false;
			npchar.quest.LSC.Knippels = false;
			npchar.quest.LSC.Bombs = false;
			npchar.quest.LSC.Sailcloth = false; //магазин
			npchar.quest.LSC.Planks = false; //магазин
			npchar.quest.LSC.Powder = false;
			npchar.quest.LSC.Food = false; //магазин
			npchar.quest.LSC.Weapon = false;
			npchar.quest.LSC.Medicament = false;
			iTemp = 0;
			npchar.quest.LSC.s0 = "";
			npchar.quest.LSC.s1 = "";
			if (GetCargoGoods(pchar , GOOD_BALLS) >= 100) 
			{
				npchar.quest.LSC.Balls = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Balls;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[173];
			if (GetCargoGoods(pchar , GOOD_GRAPES) >= 100) 
			{
				npchar.quest.LSC.Grapes = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Grapes;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[174];
			if (GetCargoGoods(pchar , GOOD_KNIPPELS) >= 100) 
			{
				npchar.quest.LSC.Knippels = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Knippels;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[175];
			if (GetCargoGoods(pchar , GOOD_BOMBS) >= 100) 
			{
				npchar.quest.LSC.Bombs = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Bombs;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[176];
			if (GetCargoGoods(pchar , GOOD_SAILCLOTH) >= 50) 
			{
				npchar.quest.LSC.Sailcloth = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Sailcloth;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[177];
			if (GetCargoGoods(pchar , GOOD_PLANKS) >= 50) 
			{
				npchar.quest.LSC.Planks = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Planks;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[178];
			if (GetCargoGoods(pchar , GOOD_POWDER) >= 200) 
			{
				npchar.quest.LSC.Powder = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Powder;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[179];
			if (GetCargoGoods(pchar , GOOD_FOOD) >= 200) 
			{
				npchar.quest.LSC.Food = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Food;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[180];
			if (GetCargoGoods(pchar , GOOD_WEAPON) >= 50) 
			{
				npchar.quest.LSC.Weapon = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Weapon;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[181];
			if (GetCargoGoods(pchar , GOOD_MEDICAMENT) >= 50) 
			{
				npchar.quest.LSC.Medicament = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Medicament;
			npchar.quest.LSC.(sTemp) = npchar.quest.LSC.(sTemp) + DLG_TEXT_LSC[182];
			if (iTemp < 10)
			{
				if (iTemp == 0)
				{
					link.l1 = DLG_TEXT_LSC[183];			
				}
				else
				{
					sTemp = npchar.quest.LSC.s0;
					npchar.quest.LSC.s0 = strcut(sTemp, 0, (strlen(sTemp)-2));
					sTemp = npchar.quest.LSC.s1;
					npchar.quest.LSC.s1 = strcut(sTemp, 0, (strlen(sTemp)-2));
					link.l1 = DLG_TEXT_LSC[184] + npchar.quest.LSC.s1 + DLG_TEXT_LSC[185] + npchar.quest.LSC.s0 + ".";
				}
				link.l1.go = "takeGoods_again";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[186];
				link.l1.go = "TakeCrew";
				DeleteAttribute(pchar, "questTemp.LSC.Balls");
				DeleteAttribute(pchar, "questTemp.LSC.Grapes");
				DeleteAttribute(pchar, "questTemp.LSC.Knippels");
				DeleteAttribute(pchar, "questTemp.LSC.Bombs");
				DeleteAttribute(pchar, "questTemp.LSC.Sailcloth");
				DeleteAttribute(pchar, "questTemp.LSC.Planks");
				DeleteAttribute(pchar, "questTemp.LSC.Powder");
				DeleteAttribute(pchar, "questTemp.LSC.Food");
				DeleteAttribute(pchar, "questTemp.LSC.Weapon");
				DeleteAttribute(pchar, "questTemp.LSC.Medicament");
				DeleteAttribute(pchar, "questTemp.LSC.additional");
			}
		break;
		case "takeGoods_again":
			dialog.text = DLG_TEXT_LSC[187];
			link.l1 = DLG_TEXT_LSC[188];
			link.l1.go = "exit";
		break;
		//Набор команды
		case "TakeCrew":
			dialog.text = DLG_TEXT_LSC[189];
			link.l1 = DLG_TEXT_LSC[190];
			link.l1.go = "TakeCrew_1";
		break;
		case "TakeCrew_1":
			dialog.text = DLG_TEXT_LSC[191];
			link.l1 = DLG_TEXT_LSC[192];
			link.l1.go = "TakeCrew_2";
		break;
		case "TakeCrew_2":
			dialog.text = DLG_TEXT_LSC[193];
			link.l1 = DLG_TEXT_LSC[194];
			link.l1.go = "TakeCrew_3";
		break;
		case "TakeCrew_3":
			dialog.text = DLG_TEXT_LSC[195];
			link.l1 = DLG_TEXT_LSC[196];
			link.l1.go = "TakeCrew_4";
		break;
		case "TakeCrew_4":
			dialog.text = DLG_TEXT_LSC[197];
			link.l1 = DLG_TEXT_LSC[198];
			link.l1.go = "TakeCrew_5";
		break;
		case "TakeCrew_5":
			dialog.text = DLG_TEXT_LSC[199];
			link.l1 = DLG_TEXT_LSC[200];
			link.l1.go = "exit";
			NextDiag.TempNode = "TakeCrewNew";
			AddQuestRecord("ISS_MainLine", "59");
			pchar.questTemp.LSC = "toSeekPeopleInCrew";
			pchar.questTemp.LSC.crew = 0; //количество уговоренных людей.
			AddDialogExitQuestFunction("LSC_SmallStormIsBegin");
		break;
		//прием народа в команду
		case "TakeCrewNew":
			if (sti(pchar.questTemp.LSC.crew) > 0)
			{
				dialog.text = DLG_TEXT_LSC[201] + FindRussianPeoplesString(sti(pchar.questTemp.LSC.crew), "Acc") + DLG_TEXT_LSC[202];
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[203];
			}
			link.l1 = DLG_TEXT_LSC[204];
			link.l1.go = "exit";
		break;
		//разговор в тюрьме
		case "inPrison":
			dialog.text = DLG_TEXT_LSC[205];
			link.l1 = DLG_TEXT_LSC[206];
			link.l1.go = "inPrison_1";
		break;
		case "inPrison_1":
			dialog.text = DLG_TEXT_LSC[207];
			link.l1 = DLG_TEXT_LSC[208];
			link.l1.go = "inPrison_2";
		break;
		case "inPrison_2":
			dialog.text = DLG_TEXT_LSC[209];
			link.l1 = DLG_TEXT_LSC[210];
			link.l1.go = "inPrison_3";
		break;
		case "inPrison_3":
			dialog.text = DLG_TEXT_LSC[211];
			link.l1 = DLG_TEXT_LSC[212];
			link.l1.go = "inPrison_4";
		break;
		case "inPrison_4":
			dialog.text = DLG_TEXT_LSC[213];
			link.l1 = DLG_TEXT_LSC[214];
			link.l1.go = "inPrison_5";
		break;
		case "inPrison_5":
			dialog.text = DLG_TEXT_LSC[215];
			link.l1 = DLG_TEXT_LSC[216];
			link.l1.go = "inPrison_6";
		break;
		case "inPrison_6":
			dialog.text = DLG_TEXT_LSC[217];
			link.l1 = DLG_TEXT_LSC[218];
			link.l1.go = "inPrison_7";
		break;
		case "inPrison_7":
			dialog.text = DLG_TEXT_LSC[219];
			link.l1 = DLG_TEXT_LSC[220];
			link.l1.go = "inPrison_8";
		break;
		case "inPrison_8":
			dialog.text = DLG_TEXT_LSC[221];
			link.l1 = DLG_TEXT_LSC[222];
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("ISS_MainLine", "67");
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
		break;
	}
}
