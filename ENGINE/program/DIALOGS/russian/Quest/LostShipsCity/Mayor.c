#include "TEXT\DIALOGS\Quest\LostShipsCity\Mayor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	string NodeName = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.location == "SanAugustineResidence")
			{
				dialog.text = DLG_TEXT_LSC[0];
				link.l1 = DLG_TEXT_LSC[1];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[2];
				link.l1 = DLG_TEXT_LSC[3];
				link.l1.go = "NRes_1";
			}
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				pchar.questTemp.LSC = "AdmiralFoundHero";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = DLG_TEXT_LSC[4];
					link.l1 = DLG_TEXT_LSC[5] + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
					PChar.quest.LSC_admiralOwnFind.over = "yes";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[6];
					link.l1 = DLG_TEXT_LSC[7] + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				break;
			}
			//квестовые ноды по главной линейке
			if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
			{
				link.l4 = DLG_TEXT_LSC[8];
				link.l4.go = "NarvalRing_1";
			}
			if (pchar.questTemp.LSC == "NarvalDestroyed")
			{
				link.l4 = DLG_TEXT_LSC[9];
				link.l4.go = "DestrNarval_1";
			}
			if (pchar.questTemp.LSC == "toAdmiralBarmenDead")
			{
				link.l4 = DLG_TEXT_LSC[10];
				link.l4.go = "BarmenDead_1";
			}
			if (pchar.questTemp.LSC == "fromMechanicToAdmiral")
			{
				link.l4 = DLG_TEXT_LSC[11];
				link.l4.go = "CasperDead_1";
			}
			//дополнительные квестовые ноды
			//муж Элис Тейлор
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.ElisHusband == "toElis")
			{
				link.l5 = DLG_TEXT_LSC[12];
				link.l5.go = "ELTHusb_begin";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
			{
				link.l5 = DLG_TEXT_LSC[13];
				link.l5.go = "ELTHusb_SF";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiralGood")
			{
				link.l5 = DLG_TEXT_LSC[14];
				link.l5.go = "ELTHusb_good";
			}
			//квест со скелетом Декстера
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.lostDecster == "toAdmiral")
			{
				link.l6 = DLG_TEXT_LSC[15];
				link.l6.go = "LostDecster";
			}	
			//поиск товаров на корвет
			if (pchar.questTemp.LSC == "toSeekGoods")
			{
				link.l8 = DLG_TEXT_LSC[16];
				link.l8.go = "SeekGoods";
			}
			//найм команды
			if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
			{
				link.l8 = DLG_TEXT_LSC[17];
				link.l8.go = "SeekCrew";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NRes_1":
			dialog.text = DLG_TEXT_LSC[18];
			link.l1 = DLG_TEXT_LSC[19];
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = DLG_TEXT_LSC[20] + GetFullName(npchar) + DLG_TEXT_LSC[21]; 
			link.l1 = DLG_TEXT_LSC[22];
			link.l1.go = "FT_1_1";
		break;
		case "FT_1_1":
			dialog.text = DLG_TEXT_LSC[23];
			link.l1 = DLG_TEXT_LSC[24];
			link.l1.go = "FT_1_2";
		break;
		case "FT_1_2":
			dialog.text = DLG_TEXT_LSC[25];
			link.l1 = DLG_TEXT_LSC[26] + npchar.name + ".";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[27];
			link.l1 = DLG_TEXT_LSC[28];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[29]+
				DLG_TEXT_LSC[30];
			link.l1 = DLG_TEXT_LSC[31];
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = DLG_TEXT_LSC[32];
			link.l1 = DLG_TEXT_LSC[33];
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = DLG_TEXT_LSC[34];
			link.l1 = DLG_TEXT_LSC[35];
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = DLG_TEXT_LSC[36];
			link.l1 = DLG_TEXT_LSC[37];
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = DLG_TEXT_LSC[38]+
				DLG_TEXT_LSC[39];
			link.l1 = DLG_TEXT_LSC[40];
			link.l1.go = "FT_7_1";
		break;
		case "FT_7_1":
			dialog.text = DLG_TEXT_LSC[41];
			link.l1 = DLG_TEXT_LSC[42];
			link.l1.go = "FT_7_2";
		break;
		case "FT_7_2":
			dialog.text = DLG_TEXT_LSC[43];
			link.l1 = DLG_TEXT_LSC[44];
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = DLG_TEXT_LSC[45];
			link.l1 = DLG_TEXT_LSC[46];
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = DLG_TEXT_LSC[47];
			link.l1 = DLG_TEXT_LSC[48];
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			if (pchar.questTemp.LSC == "AdmiralFoundHero")
			{
				dialog.text = DLG_TEXT_LSC[49];
				link.l1 = DLG_TEXT_LSC[50];
				link.l1.go = "FT_11";
				pchar.money = makeint(sti(pchar.money) / 50);
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[51];
				link.l1 = DLG_TEXT_LSC[52];
				link.l1.go = "FT_12";
				pchar.money = 0;
			}
		break;
		case "FT_11":
			dialog.text = DLG_TEXT_LSC[53];
			link.l1 = DLG_TEXT_LSC[54];
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = DLG_TEXT_LSC[55];
			link.l1 = DLG_TEXT_LSC[56];
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = DLG_TEXT_LSC[57];
			link.l1 = DLG_TEXT_LSC[58];
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = DLG_TEXT_LSC[59];
			link.l1 = DLG_TEXT_LSC[60];
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = DLG_TEXT_LSC[61];
			link.l1 = DLG_TEXT_LSC[62];
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			if (npchar.chr_ai.type == LAI_TYPE_ACTOR) LAi_SetLSCoutTypeNoGroup(npchar);
			AddDialogExitQuestFunction("LSC_admiralTakeAll");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//базар с ГГ, если сам не пришел к адмиралу
		case "FoundHero":
			npchar.quest.meeting = "1";
			NextDiag.TempNode = "First time";
			pchar.questTemp.LSC = "AdmiralNotFoundHero";
			dialog.text = DLG_TEXT_LSC[63];
			link.l1 = DLG_TEXT_LSC[64];
			link.l1.go = "FoundHero_1";
		break;
		case "FoundHero_1":
			dialog.text = DLG_TEXT_LSC[65];
			link.l1 = DLG_TEXT_LSC[66];
			link.l1.go = "FoundHero_2";
		break;
		case "FoundHero_2":
			dialog.text = DLG_TEXT_LSC[67];
			link.l1 = DLG_TEXT_LSC[68] + GetFullName(pchar) + ".";
			link.l1.go = "FT_1";
		break;

		//ГГ принес амулет нарвалов
		case "NarvalRing_1":
			dialog.text = DLG_TEXT_LSC[69];
			link.l1 = DLG_TEXT_LSC[70];
			link.l1.go = "NarvalRing_2";
		break;
		case "NarvalRing_2":
			dialog.text = DLG_TEXT_LSC[71];
			link.l1 = DLG_TEXT_LSC[72];
			link.l1.go = "NarvalRing_3";
		break;
		case "NarvalRing_3":
			dialog.text = DLG_TEXT_LSC[73];
			link.l1 = DLG_TEXT_LSC[74];
			link.l1.go = "NarvalRing_4";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			BackItemName("DOjeronRing");
			BackItemDescribe("DOjeronRing");
			ref itm;
			itm = ItemsFromID("DOjeronRing");
			itm.picIndex = 2;
			itm.picTexture = "ITEMS_9";
		break;
		case "NarvalRing_3":
			dialog.text = DLG_TEXT_LSC[75];
			link.l1 = DLG_TEXT_LSC[76];
			link.l1.go = "NarvalRing_4";
		break;
		case "NarvalRing_4":
			dialog.text = DLG_TEXT_LSC[77];
			link.l1 = DLG_TEXT_LSC[78];
			link.l1.go = "NarvalRing_5";
		break;
		case "NarvalRing_5":
			dialog.text = DLG_TEXT_LSC[79];
			link.l1 = DLG_TEXT_LSC[80];
			link.l1.go = "NarvalRing_6";
		break;
		case "NarvalRing_6":
			dialog.text = DLG_TEXT_LSC[81];
			link.l1 = DLG_TEXT_LSC[82];
			link.l1.go = "NarvalRing_7";
		break;
		case "NarvalRing_7":
			dialog.text = DLG_TEXT_LSC[83];
			link.l1 = DLG_TEXT_LSC[84];
			link.l1.go = "NarvalRing_8";
		break;
		case "NarvalRing_8":
			dialog.text = DLG_TEXT_LSC[85];
			link.l1 = DLG_TEXT_LSC[86];
			link.l1.go = "NarvalRing_9";
		break;
		case "NarvalRing_9":
			dialog.text = DLG_TEXT_LSC[87];
			link.l1 = DLG_TEXT_LSC[88];
			link.l1.go = "NarvalRing_10";
		break;
		case "NarvalRing_10":
			dialog.text = DLG_TEXT_LSC[89];
			link.l1 = DLG_TEXT_LSC[90];
			link.l1.go = "NarvalRing_11";
		break;
		case "NarvalRing_11":
			dialog.text = DLG_TEXT_LSC[91];
			link.l1 = DLG_TEXT_LSC[92];
			link.l1.go = "NarvalRing_12";
		break;
		case "NarvalRing_12":
			dialog.text = DLG_TEXT_LSC[93];
			link.l1 = DLG_TEXT_LSC[94];
			link.l1.go = "NarvalRing_13";
		break;
		case "NarvalRing_13":
			AddQuestRecord("ISS_MainLine", "12");
			pchar.questTemp.LSC = "toDestoyAllNarval";
			int idxMent;
			pchar.questTemp.LSC.qtyOfficers = 0;
			string sOffName;
			for (i=1 ; i<=3; i++)
			{
				idxMent = GetCharacterIndex("Ment_" + i);
				if (idxMent != -1)
				{
					ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "officers", "officer_"+i);
					characters[idxMent].Dialog.CurrentNode = "OffNarval";
					characters[idxMent].cityTape = "quest"; //тип нпс
					LAi_SetStayTypeNoGroup(&characters[idxMent]);
					pchar.questTemp.LSC.qtyOfficers = sti(pchar.questTemp.LSC.qtyOfficers) + 1;
				}
			}
			pchar.quest.NavalEnterOfficers.win_condition.l1 = "location";
			pchar.quest.NavalEnterOfficers.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.NavalEnterOfficers.function = "NavalEnterOfficers";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//клан Нарвал уничтожен
		case "DestrNarval_1":
			dialog.text = DLG_TEXT_LSC[95];
			iTemp = 0;
			for (i=1 ; i<=3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					iTemp++;
				}
			}
			if (iTemp == 0)
			{
				link.l1 = DLG_TEXT_LSC[96];
				link.l1.go = "DestrNarval_Bad";
			}
			else
			{
				if (iTemp == sti(pchar.questTemp.LSC.qtyOfficers))
				{
					link.l1 = DLG_TEXT_LSC[97];
					link.l1.go = "DestrNarval_Ok";
				}
				else
				{
					link.l1 = DLG_TEXT_LSC[98];
					link.l1.go = "DestrNarval_BadOk";
				}
				DeleteAttribute(pchar, "questTemp.LSC.qtyOfficers");
			}
		break;
		case "DestrNarval_Bad":
			dialog.text = DLG_TEXT_LSC[99];
			link.l1 = DLG_TEXT_LSC[100];
			link.l1.go = "DestrNarval_Bad1";
		break;
		case "DestrNarval_Bad1":
			dialog.text = DLG_TEXT_LSC[101];
			link.l1 = DLG_TEXT_LSC[102];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "16");
		break;
		case "DestrNarval_Ok":
			dialog.text = DLG_TEXT_LSC[103];
			link.l1 = DLG_TEXT_LSC[104];
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "14");
			AddMoneyToCharacter(pchar, 100000);
		break;
		case "DestrNarval_Ok1":
			dialog.text = DLG_TEXT_LSC[105];
			link.l1 = DLG_TEXT_LSC[106];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
		break;
		case "DestrNarval_BadOk":
			dialog.text = DLG_TEXT_LSC[107];
			link.l1 = DLG_TEXT_LSC[108];
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "15");
			AddMoneyToCharacter(pchar, 10000);
		break;
		//подслушивание в погребке
		case "Interception":
			sld = characterFromId("Blaze");
			bool bOk = false;
			float fAng;
			GetCharacterAy(sld, &fAng);
			if (fAng > -1.35 && fAng < -0.28) bOk = true;
			if (fAng > 1.8 && fAng < 2.9) bOk = true;
			if (sti(sld.questTemp.LSC.itemState) && bOk)
			{
				dialog.text = DLG_TEXT_LSC[109];
				link.l1 = DLG_TEXT_LSC[110];
				link.l1.go = "Interception_1";				
				sld.questTemp.LSC = "InterceptionOk";
				sld.questTemp.LSC.knowMechanic = true; //флаг ГГ знает о Механике
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[111];
				link.l1 = DLG_TEXT_LSC[112];
				link.l1.go = "exit";				
				sld.questTemp.LSC = "InterceptionYouSeen";
				AddDialogExitQuestFunction("LCS_EndScriptInterception");
			}
		break;
		case "Interception_1":
			dialog.text = DLG_TEXT_LSC[113];
			link.l1 = DLG_TEXT_LSC[114];
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			sld = characterFromId("Blaze");
			dialog.text = DLG_TEXT_LSC[115];
			link.l1 = DLG_TEXT_LSC[116] + GetFullName(sld) + DLG_TEXT_LSC[117];
			link.l1.go = "Interception_4";
		break;
		case "Interception_4":
			dialog.text = DLG_TEXT_LSC[118];
			link.l1 = DLG_TEXT_LSC[119];
			link.l1.go = "Interception_5";
		break;
		case "Interception_5":
			dialog.text = DLG_TEXT_LSC[120];
			link.l1 = DLG_TEXT_LSC[121];
			link.l1.go = "Interception_6";
		break;
		case "Interception_6":
			dialog.text = DLG_TEXT_LSC[122];
			link.l1 = DLG_TEXT_LSC[123];
			link.l1.go = "Interception_7";
		break;
		case "Interception_7":
			dialog.text = DLG_TEXT_LSC[124];
			link.l1 = DLG_TEXT_LSC[125];
			link.l1.go = "Interception_8";
		break;
		case "Interception_8":
			dialog.text = DLG_TEXT_LSC[126];
			link.l1 = DLG_TEXT_LSC[127];
			link.l1.go = "Interception_9";
		break;
		case "Interception_9":
			dialog.text = DLG_TEXT_LSC[128];
			link.l1 = DLG_TEXT_LSC[129];
			link.l1.go = "Interception_10";
		break;
		case "Interception_10":
			dialog.text = DLG_TEXT_LSC[130];
			link.l1 = DLG_TEXT_LSC[131];
			link.l1.go = "Interception_11";
		break;
		case "Interception_11":
			dialog.text = DLG_TEXT_LSC[132];
			link.l1 = DLG_TEXT_LSC[133];
			link.l1.go = "Interception_12";
		break;
		case "Interception_12":
			dialog.text = DLG_TEXT_LSC[134];
			link.l1 = DLG_TEXT_LSC[135];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LCS_EndScriptInterception");
		break;

		case "BarmenDead_1":
			dialog.text = DLG_TEXT_LSC[136];
			link.l1 = DLG_TEXT_LSC[137];
			link.l1.go = "BarmenDead_2";
		break;
		case "BarmenDead_2":
			dialog.text = DLG_TEXT_LSC[138];
			link.l1 = DLG_TEXT_LSC[139];
			link.l1.go = "BarmenDead_3";
		break;
		case "BarmenDead_3":
			dialog.text = DLG_TEXT_LSC[140];
			link.l1 = DLG_TEXT_LSC[141];
			link.l1.go = "BarmenDead_4";
		break;
		case "BarmenDead_4":
			dialog.text = DLG_TEXT_LSC[142];
			link.l1 = DLG_TEXT_LSC[143];
			link.l1.go = "BarmenDead_5";
		break;
		case "BarmenDead_5":
			dialog.text = DLG_TEXT_LSC[144];
			link.l1 = DLG_TEXT_LSC[145];
			link.l1.go = "BarmenDead_6";
		break;
		case "BarmenDead_6":
			dialog.text = DLG_TEXT_LSC[146];
			link.l1 = DLG_TEXT_LSC[147];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekOldCitizen";
			AddQuestRecord("ISS_MainLine", "27");
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1          = "location";
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_SaveSesilGalard.function                  = "LSC_SaveSesilGalard";
		break;
		//замочили касперов
		case "CasperDead_1":
			dialog.text = DLG_TEXT_LSC[148];
			link.l1 = DLG_TEXT_LSC[149];
			link.l1.go = "CasperDead_2";
		break;
		case "CasperDead_2":
			dialog.text = DLG_TEXT_LSC[150];
			link.l1 = DLG_TEXT_LSC[151];
			link.l1.go = "CasperDead_3";
		break;
		case "CasperDead_3":
			dialog.text = DLG_TEXT_LSC[152];
			link.l1 = DLG_TEXT_LSC[153];
			link.l1.go = "CasperDead_4";
		break;
		case "CasperDead_4":
			dialog.text = DLG_TEXT_LSC[154];
			link.l1 = DLG_TEXT_LSC[155];
			link.l1.go = "CasperDead_5";
		break;
		case "CasperDead_5":
			dialog.text = DLG_TEXT_LSC[156];
			link.l1 = DLG_TEXT_LSC[157];
			link.l1.go = "CasperDead_6";
		break;
		case "CasperDead_6":
			dialog.text = DLG_TEXT_LSC[158];
			link.l1 = DLG_TEXT_LSC[159];
			link.l1.go = "CasperDead_7";
		break;
		case "CasperDead_7":
			dialog.text = DLG_TEXT_LSC[160];
			link.l1 = DLG_TEXT_LSC[161];
			link.l1.go = "CasperDead_8";
		break;
		case "CasperDead_8":
			dialog.text = DLG_TEXT_LSC[162];
			link.l1 = DLG_TEXT_LSC[163];
			link.l1.go = "CasperDead_9";
		break;
		case "CasperDead_9":
			dialog.text = DLG_TEXT_LSC[164];
			link.l1 = DLG_TEXT_LSC[165];
			link.l1.go = "CasperDead_10";
		break;
		case "CasperDead_10":
			dialog.text = DLG_TEXT_LSC[166];
			link.l1 = DLG_TEXT_LSC[167];
			link.l1.go = "CasperDead_11";
		break;
		case "CasperDead_11":
			dialog.text = DLG_TEXT_LSC[168];
			link.l1 = DLG_TEXT_LSC[169];
			link.l1.go = "CasperDead_12";
		break;
		case "CasperDead_12":
			dialog.text = DLG_TEXT_LSC[170];
			link.l1 = DLG_TEXT_LSC[171];
			link.l1.go = "CasperDead_13";
		break;
		case "CasperDead_13":
			dialog.text = DLG_TEXT_LSC[172];
			link.l1 = DLG_TEXT_LSC[173];
			link.l1.go = "CasperDead_14";
		break;
		case "CasperDead_14":
			dialog.text = DLG_TEXT_LSC[174];
			link.l1 = DLG_TEXT_LSC[175];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "seekMillionAndHalf";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[176], 
				DLG_TEXT_LSC[177], 
				DLG_TEXT_LSC[178],
                DLG_TEXT_LSC[179], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[180], 
				DLG_TEXT_LSC[181],
                DLG_TEXT_LSC[182], 
				DLG_TEXT_LSC[183], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[184];
			link.l1 = DLG_TEXT_LSC[185];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[186];
			link.l1 = DLG_TEXT_LSC[187];
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = DLG_TEXT_LSC[188];
			link.l1 = DLG_TEXT_LSC[189];
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = DLG_TEXT_LSC[190];
			link.l1 = DLG_TEXT_LSC[191];
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = DLG_TEXT_LSC[192];
			link.l1 = DLG_TEXT_LSC[193];
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = DLG_TEXT_LSC[194];
			link.l1 = DLG_TEXT_LSC[195];
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = DLG_TEXT_LSC[196];
			link.l1 = DLG_TEXT_LSC[197];
			link.l1.go = "SeekGoods_8";
		break;
		case "SeekGoods_8":
			dialog.text = DLG_TEXT_LSC[198];
			link.l1 = DLG_TEXT_LSC[199];
			link.l1.go = "SeekGoods_9";
		break;
		case "SeekGoods_9":
			dialog.text = DLG_TEXT_LSC[200];
			link.l1 = DLG_TEXT_LSC[201];
			link.l1.go = "SeekGoods_10";
		break;
		case "SeekGoods_10":
			dialog.text = DLG_TEXT_LSC[202];
			link.l1 = DLG_TEXT_LSC[203];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "57")
			pchar.questTemp.LSC.additional.powder = true; //флаг на дачу квеста ментом
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[204], 
				DLG_TEXT_LSC[205], 
				DLG_TEXT_LSC[206],
                DLG_TEXT_LSC[207], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[208], 
				DLG_TEXT_LSC[209],
                DLG_TEXT_LSC[210], 
				DLG_TEXT_LSC[211], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[212];
			link.l1 = DLG_TEXT_LSC[213];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[214];
			link.l1 = DLG_TEXT_LSC[215];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[216];
			link.l1 = DLG_TEXT_LSC[217];
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = DLG_TEXT_LSC[218];
			link.l1 = DLG_TEXT_LSC[219];
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = DLG_TEXT_LSC[220];
			link.l1 = DLG_TEXT_LSC[221];
			link.l1.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = DLG_TEXT_LSC[222];
			link.l1 = DLG_TEXT_LSC[223];
			link.l1.go = "SeekCrew_7";
		break;
		case "SeekCrew_7":
			dialog.text = DLG_TEXT_LSC[224];
			link.l1 = DLG_TEXT_LSC[225];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "60");
		break;
		//финальный диалог
		case "fightTalking":
			dialog.text = DLG_TEXT_LSC[226];
			link.l1 = DLG_TEXT_LSC[227];
			link.l1.go = "fightTalking_1";
		break;
		case "fightTalking_1":
			dialog.text = DLG_TEXT_LSC[228];
			link.l1 = DLG_TEXT_LSC[229];
			link.l1.go = "fightTalking_2";
		break;
		case "fightTalking_2":
			dialog.text = DLG_TEXT_LSC[230];
			link.l1 = DLG_TEXT_LSC[231];
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_3":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorTypeNoGroup(NPChar);
			//LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuestFunction("LSC_figtInResidence");
            DialogExit();
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[232], 
				DLG_TEXT_LSC[233], 
				DLG_TEXT_LSC[234],
                DLG_TEXT_LSC[235], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[236], 
				DLG_TEXT_LSC[237],
                DLG_TEXT_LSC[238], 
				DLG_TEXT_LSC[239], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = DLG_TEXT_LSC[240];
			link.l1 = DLG_TEXT_LSC[241];
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = DLG_TEXT_LSC[242];
			link.l1 = DLG_TEXT_LSC[243];
			link.l1.go = "exit";
		break;

		case "ELTHusb_SF":
			dialog.text = DLG_TEXT_LSC[244];
			link.l1 = DLG_TEXT_LSC[245];
			link.l1.go = "ELTHusb_SF_1";
		break;		
		case "ELTHusb_SF_1":
			dialog.text = DLG_TEXT_LSC[246];
			link.l1 = DLG_TEXT_LSC[247];
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = DLG_TEXT_LSC[248];
			link.l1 = DLG_TEXT_LSC[249];
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = DLG_TEXT_LSC[250];
			link.l1 = DLG_TEXT_LSC[251];
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = DLG_TEXT_LSC[252];
			link.l1 = DLG_TEXT_LSC[253];
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = DLG_TEXT_LSC[254];
			link.l1 = DLG_TEXT_LSC[255];
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toWaitress";
			AddQuestRecord("ISS_ElisHusband", "7");
		break;

		case "ELTHusb_good":
			dialog.text = DLG_TEXT_LSC[256];
			link.l1 = DLG_TEXT_LSC[257];
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = DLG_TEXT_LSC[258];
			link.l1 = DLG_TEXT_LSC[259];
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = DLG_TEXT_LSC[260];
			link.l1 = DLG_TEXT_LSC[261];
			link.l1.go = "ELTHusb_good_3";
		break;
		case "ELTHusb_good_3":
			dialog.text = DLG_TEXT_LSC[262];
			link.l1 = DLG_TEXT_LSC[263];
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toElisGood";
			AddQuestRecord("ISS_ElisHusband", "10");
			sld = characterFromId("MaximTailor");
			ChangeCharacterAddress(sld, "none", "");
		break;
		//квест со скелетом Декстера
		case "LostDecster":
			dialog.text = DLG_TEXT_LSC[264];
			link.l1 = DLG_TEXT_LSC[265];
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = DLG_TEXT_LSC[266];
			link.l1 = DLG_TEXT_LSC[267];
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = DLG_TEXT_LSC[268];
			link.l1 = DLG_TEXT_LSC[269];
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = DLG_TEXT_LSC[270];
			link.l1 = DLG_TEXT_LSC[271];
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = DLG_TEXT_LSC[272];
			link.l1 = DLG_TEXT_LSC[273];
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = DLG_TEXT_LSC[274];
			link.l1 = DLG_TEXT_LSC[275];
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = DLG_TEXT_LSC[276];
			link.l1 = DLG_TEXT_LSC[277];
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "seekBox";
			AddQuestRecord("LSC_findDekster", "5");	
		break;

	}
}
