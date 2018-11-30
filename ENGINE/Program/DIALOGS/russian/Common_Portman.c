#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_Portman.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (5000 + rand(4)*1000);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn;
    ref chref;
    string attrL, sTitle, sCapitainId;
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}	
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
			//провека защиты -->
			/*if (GetEngineVersion() != iScriptVersion)
			{
       			dialog.text = DLG_TEXT_BASE[12];
				link.l1 = "...";
				link.l1.go = "exit";
				break;
			} */
			//<-- провека защиты
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[13] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[14],
                                    DLG_TEXT_BASE[15] + GetFullName(pchar) + DLG_TEXT_BASE[16]);
                Link.l1 = DLG_TEXT_BASE[17] + NPChar.name + DLG_TEXT_BASE[18];
				Link.l1.go = "exit";
				break;
            }
			//homo
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = DLG_TEXT_BASE[19] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[20]  + GetFullName(npchar)+ DLG_TEXT_BASE[21];
				Link.l1 = DLG_TEXT_BASE[22] + GetFullName(NPChar) + DLG_TEXT_BASE[23] + GetFullName(PChar) + DLG_TEXT_BASE[24] + PChar.ship.name + ".";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[25] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[26],
                                    DLG_TEXT_BASE[27] + GetFullName(Pchar) + DLG_TEXT_BASE[28],
                                    DLG_TEXT_BASE[29] + GetFullName(Pchar) + DLG_TEXT_BASE[30]);
				Link.l1 = DLG_TEXT_BASE[31] + GetFullName(NPChar) + DLG_TEXT_BASE[32];
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			dialog.text = DLG_TEXT_BASE[33] + GetFullName(PChar) + ".";
			Link.l2 = DLG_TEXT_BASE[34];
			Link.l2.go = "node_4";
			Link.l3 = DLG_TEXT_BASE[35];
			Link.l3.go = "ShipStock_1";
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = DLG_TEXT_BASE[36];
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = DLG_TEXT_BASE[37];
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple(DLG_TEXT_BASE[38] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[39]);
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = DLG_TEXT_BASE[40];
			link.l6.go = "CapitainList";
			link.l8 = DLG_TEXT_BASE[41];
			link.l8.go = "quests";
			Link.l9 = DLG_TEXT_BASE[42];
			Link.l9.go = "exit";
		break;

		case "node_4":
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = DLG_TEXT_BASE[43] + npchar.quest.PortmansJornal.capName + DLG_TEXT_BASE[44];
				link.l1 = DLG_TEXT_BASE[45];
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = DLG_TEXT_BASE[46] + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " " + npchar.quest.PortmansSeekShip.shipName + DLG_TEXT_BASE[47];
				link.l1 = DLG_TEXT_BASE[48];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[49];
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = DLG_TEXT_BASE[50] + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " " + npchar.quest.PortmansSeekShip.shipName + DLG_TEXT_BASE[51];
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = DLG_TEXT_BASE[52];
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[53];
					link.l1.go = "exit";
				}
				link.l2 = DLG_TEXT_BASE[54];
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 

			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[55], 
					DLG_TEXT_BASE[56], 
					DLG_TEXT_BASE[57]);
				link.l1 = DLG_TEXT_BASE[58] + GetAddress_Form(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}			
			//<-- дача миниквестов начальника порта.

			dialog.text = DLG_TEXT_BASE[59];
			Link.l1 = DLG_TEXT_BASE[60];
			Link.l1.go = "node_2";
			Link.l2 = DLG_TEXT_BASE[61];
			Link.l2.go = "exit";
		break;
		case "PortmanQuest_NF":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "node_2";
		break;

		//--> миниквесты портмана
		case "PortmanQuest":
			if (cRand(2) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = DLG_TEXT_BASE[64];
				link.l1 = DLG_TEXT_BASE[65];
				link.l1.go = "PortmanQuest_1";
				link.l2 = DLG_TEXT_BASE[66];
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = DLG_TEXT_BASE[67];
				link.l1 = DLG_TEXT_BASE[68];
				link.l1.go = "SeekShip_1";
				link.l2 = DLG_TEXT_BASE[69];
				link.l2.go = "node_2";
			}
		break;
		// -------------------------------- квест доставки судового журнала до рассеяного кэпа --------------------------
		case "PortmanQuest_1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
		break;
		case "PortmanQuest_2":
			dialog.text = DLG_TEXT_BASE[72] + npchar.quest.PortmansJornal.capName + DLG_TEXT_BASE[73] + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")) + DLG_TEXT_BASE[74] + npchar.quest.PortmansJornal.shipName + DLG_TEXT_BASE[75] + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[76];
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + DLG_TEXT_BASE[77];
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", DLG_TEXT_BASE[79] + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = DLG_TEXT_BASE[80];
			link.l1 = DLG_TEXT_BASE[81];
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + DLG_TEXT_BASE[82] + npchar.quest.PortmansSeekShip.shipName + DLG_TEXT_BASE[83] + FindRussianDaysString(rand(5)+10) + DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[91];
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterReputation(pchar, -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = DLG_TEXT_BASE[92];
				link.l1 = DLG_TEXT_BASE[93];
				npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[94];
				link.l1 = DLG_TEXT_BASE[95];
				ChangeCharacterReputation(pchar, 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = DLG_TEXT_BASE[96] + FindRussianMoneyString(sti(npchar.quest.money)) + DLG_TEXT_BASE[97];
			link.l1 = DLG_TEXT_BASE[98];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = DLG_TEXT_BASE[99];
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + DLG_TEXT_BASE[100] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " " + sld.Ship.name + ".";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[101];
				link.l1 = DLG_TEXT_BASE[102];
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[103], DLG_TEXT_BASE[104], DLG_TEXT_BASE[105]) +
				DLG_TEXT_BASE[106] + GetFullName(sld) + " " + arCapLocal.date + DLG_TEXT_BASE[107] + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "CapitainList";
			link.l2 = DLG_TEXT_BASE[109];
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", DLG_TEXT_BASE[110] + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[111], DLG_TEXT_BASE[112], DLG_TEXT_BASE[113]) +
				DLG_TEXT_BASE[114] + GetFullName(sld) + " " + arCapLocal.date + DLG_TEXT_BASE[115] + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[116];
			link.l1.go = "CapitainList";
			link.l2 = DLG_TEXT_BASE[117];
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", DLG_TEXT_BASE[118] + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[119], DLG_TEXT_BASE[120], DLG_TEXT_BASE[121]) +
				DLG_TEXT_BASE[122] + GetFullName(sld) + " " + arCapLocal.date + DLG_TEXT_BASE[123] + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "CapitainList";
			link.l2 = DLG_TEXT_BASE[125];
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", DLG_TEXT_BASE[126] + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[127], DLG_TEXT_BASE[128], DLG_TEXT_BASE[129]) +
				DLG_TEXT_BASE[130] + GetFullName(sld) + " " + arCapLocal.date + DLG_TEXT_BASE[131] + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "CapitainList";
			link.l2 = DLG_TEXT_BASE[133];
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", DLG_TEXT_BASE[134] + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[135], DLG_TEXT_BASE[136], DLG_TEXT_BASE[137]) +
				DLG_TEXT_BASE[138] + GetFullName(sld) + " " + arCapLocal.date + DLG_TEXT_BASE[139] + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = DLG_TEXT_BASE[140];
			link.l1.go = "CapitainList";
			link.l2 = DLG_TEXT_BASE[141];
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", DLG_TEXT_BASE[142] + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
            if (sti(NPChar.Portman) >= 3)
			{
                dialog.text = DLG_TEXT_BASE[143];
    			Link.l1 = DLG_TEXT_BASE[144];
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = DLG_TEXT_BASE[145];
	    			for(i=1; i<COMPANION_MAX; i++)
	                {
	        	        cn = GetCompanionIndex(PChar, i);
	        	        if( cn >0 )
	        	        {
	        		        chref = GetCharacter(cn);
	                        if (!GetRemovable(chref)) continue;
	
	        		        attrL = "l"+i;
	        		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " " + chref.Ship.Name;
	        		        Link.(attrL).go = "ShipStockMan_" + i;
	        		    }
	        	    }
	    			Link.l9 = DLG_TEXT_BASE[146];
	    			Link.l9.go = "exit";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[147];
	    			Link.l1 = DLG_TEXT_BASE[148];
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = DLG_TEXT_BASE[149];
			Link.l1 = DLG_TEXT_BASE[150];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_BASE[151];
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = DLG_TEXT_BASE[152];
			Link.l1 = DLG_TEXT_BASE[153];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_BASE[154];
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = DLG_TEXT_BASE[155];
			Link.l1 = DLG_TEXT_BASE[156];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_BASE[157];
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = DLG_TEXT_BASE[158];
			Link.l1 = DLG_TEXT_BASE[159];
			Link.l1.go = "ShipStock_2";
			Link.l2 = DLG_TEXT_BASE[160];
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            NPChar.MoneyForShip =  (8-sti(RealShips[sti(chref.Ship.Type)].Class)) * sti(NPChar.PortManPrice);
			dialog.text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " " + chref.Ship.Name + DLG_TEXT_BASE[161] + RealShips[sti(chref.Ship.Type)].Class +
                     DLG_TEXT_BASE[162] + NPChar.MoneyForShip;
			Link.l1 = DLG_TEXT_BASE[163];
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = DLG_TEXT_BASE[164];
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = DLG_TEXT_BASE[165];
			Link.l1 = DLG_TEXT_BASE[166];
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
            AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
            chref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";

            NPChar.Portman    = sti(NPChar.Portman) + 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = DLG_TEXT_BASE[167];
			Link.l1 = DLG_TEXT_BASE[168];
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = DLG_TEXT_BASE[169];
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
	            	{
	            		makeref(chref, Characters[i]);
	            		if (CheckAttribute(chref, "ShipInStockMan"))
	            		{
	                        if (chref.ShipInStockMan == NPChar.id)
	        		        {
	                            attrL = "l"+cn;
	            		        Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " " + chref.Ship.Name;
	            		        Link.(attrL).go = "ShipStockManBack_" + cn;
	            		        attrL = "ShipToStoreId" + cn;
	            		        NPChar.Temp.(attrL) = i;
	            		        cn++;
	        		        }
	            		}
	                }
	
	    			Link.l9 = DLG_TEXT_BASE[170];
	    			Link.l9.go = "exit";
				}
				else
				{
	                dialog.text = DLG_TEXT_BASE[171];
	    			Link.l1 = DLG_TEXT_BASE[172];
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[173];
    			Link.l1 = DLG_TEXT_BASE[174];
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack_1":
            NPChar.ShipToStoreIdx = sti(NPChar.Temp.ShipToStoreId1);
			dialog.text = DLG_TEXT_BASE[175];
			Link.l1 = DLG_TEXT_BASE[176];
			Link.l1.go = "ShipStockManBack";
			Link.l2 = DLG_TEXT_BASE[177];
			Link.l2.go = "exit";
		break;

		case "ShipStockManBack_2":
            NPChar.ShipToStoreIdx = sti(NPChar.Temp.ShipToStoreId2);
            dialog.text = DLG_TEXT_BASE[178];
			Link.l1 = DLG_TEXT_BASE[179];
			Link.l1.go = "ShipStockManBack";
			Link.l2 = DLG_TEXT_BASE[180];
			Link.l2.go = "exit";
		break;

		case "ShipStockManBack_3":
            NPChar.ShipToStoreIdx = sti(NPChar.Temp.ShipToStoreId3);
            dialog.text = DLG_TEXT_BASE[181];
			Link.l1 = DLG_TEXT_BASE[182];
			Link.l1.go = "ShipStockManBack";
			Link.l2 = DLG_TEXT_BASE[183];
			Link.l2.go = "exit";
		break;

		case "ShipStockManBack":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		break;
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true));
	SetCaptanModelByEncType(sld, "trade");
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo(DLG_TEXT_BASE[184] + sld.id + DLG_TEXT_BASE[185] + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " " + npchar.quest.PortmansJornal.shipName;
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true));
	SetCaptanModelByEncType(sld, "pirate");
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
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
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo(DLG_TEXT_BASE[186] + sld.id + DLG_TEXT_BASE[187] + sld.city + DLG_TEXT_BASE[188] + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " " + npchar.quest.PortmansSeekShip.shipName;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
