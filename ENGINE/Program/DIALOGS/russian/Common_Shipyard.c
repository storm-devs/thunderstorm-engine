// boal 08/04/06 общий диалог верфи
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_Shipyard.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
			DialogExit();
			NextDiag.CurrentNode = "Master_Ship";  // выход дл€ тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
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
			NextDiag.TempNode = "First time";
			
			//homo Ћинейка Ѕлада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[12] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[13],
                                    DLG_TEXT_BASE[14] + GetFullName(pchar) + DLG_TEXT_BASE[15]);
                Link.l1 = DLG_TEXT_BASE[16] + NPChar.name + DLG_TEXT_BASE[17];
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = DLG_TEXT_BASE[18];
    				Link.l2.go = "Blood_Shipyard1";
                }
				break;
            }
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = TimeGreeting() + DLG_TEXT_BASE[19]+ GetFullName(NPChar) + DLG_TEXT_BASE[20];
				Link.l1 = DLG_TEXT_BASE[21] + GetFullName(Pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				//--->> квест украсть чертеж на верфи
				//дача квеста
				if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 7 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap"))
				{
					dialog.text = DLG_TEXT_BASE[22];					
					link.l1 = DLG_TEXT_BASE[23];
					link.l1.go = "ShipyardsMap_1";
					SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
					break;
				}
				//<<--- квест украсть чертеж на верфи			
				
				dialog.Text = pcharrepphrase(DLG_TEXT_BASE[24],
                                        TimeGreeting() + DLG_TEXT_BASE[25] + GetAddress_Form(NPChar) + "?");
				Link.l1 = pcharrepphrase(DLG_TEXT_BASE[26],
                                        DLG_TEXT_BASE[27]);
				Link.l1.go = "Shipyard";
				link.l11 = DLG_TEXT_BASE[28];
			    link.l11.go = "Cannons";
				Link.l2 = DLG_TEXT_BASE[29];
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = DLG_TEXT_BASE[30];
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на св€зь с нашим шпионом
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[31] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[32]);
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест јззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = DLG_TEXT_BASE[33];
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест јззи.
				//проверка выполнени€ квеста украсть чертеж на верфи
				if (CheckCharacterItem(pchar, "ShipyardsMap") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.Id") && pchar.questTemp.different.ShipyardsMap.Id == npchar.id)
				{				
					link.l6 = DLG_TEXT_BASE[34] + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + DLG_TEXT_BASE[35];
					link.l6.go = "ShipyardsMapOk_1";
				}
				Link.l9 = DLG_TEXT_BASE[36];
				Link.l9.go = "exit";
			}
		break;
		
		case "Meeting":
				dialog.Text = DLG_TEXT_BASE[37];
				Link.l1 = DLG_TEXT_BASE[38] + GetFullName(NPChar) + DLG_TEXT_BASE[39];
				Link.l1.go = "Shipyard";
				link.l11 = DLG_TEXT_BASE[40];
				link.l11.go = "Cannons";
				Link.l2 = DLG_TEXT_BASE[41];
				Link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = DLG_TEXT_BASE[42];
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на св€зь с нашим шпионом
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[43] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[44]);
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест јззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = DLG_TEXT_BASE[45];
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест јззи.
				Link.l9 = DLG_TEXT_BASE[46];
				Link.l9.go = "exit";
		break;
		
		case "shipyard":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[47],
				                                                     DLG_TEXT_BASE[48]),
													  pcharrepphrase(DLG_TEXT_BASE[49] +GetFullName(pchar)+ DLG_TEXT_BASE[50],
													                 DLG_TEXT_BASE[51]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[52],
				                                                 DLG_TEXT_BASE[53] +GetFullName(npchar)+ DLG_TEXT_BASE[54]),
												  pcharrepphrase(DLG_TEXT_BASE[55],
												                 DLG_TEXT_BASE[56]));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[57],
				                                                     DLG_TEXT_BASE[58]),
													  pcharrepphrase(DLG_TEXT_BASE[59] +GetFullName(pchar)+ DLG_TEXT_BASE[60],
													                 DLG_TEXT_BASE[61]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[62],
				                                                 DLG_TEXT_BASE[63] +GetFullName(npchar)+ DLG_TEXT_BASE[64]),
												  pcharrepphrase(DLG_TEXT_BASE[65],
												                 DLG_TEXT_BASE[66]));
			    link.l1.go = "exit";
			}
		break;
		// квест украсть чертеж на верфи
		case "ShipyardsMap_1":
			dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			pchar.questTemp.different = "ShipyardsMap";
			pchar.questTemp.different.ShipyardsMap = "toTarget";
			pchar.questTemp.different.ShipyardsMap.Id = npchar.id; //квестодатель
			pchar.questTemp.different.ShipyardsMap.city = findShipyardCity(npchar);
			pchar.questTemp.different.ShipyardsMap.what = LinkRandPhrase(DLG_TEXT_BASE[69], DLG_TEXT_BASE[70], DLG_TEXT_BASE[71]);
			pchar.questTemp.different.ShipyardsMap.chance = rand(5); //ценность чертежа
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = false; //не будет драки на складе
			}
			else
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = true; //будет драка на складе
			}
			pchar.questTemp.different.ShipyardsMap.sklad = rand(3)+1; //сколько денег попрос€т на складе за открытие двери
			pchar.questTemp.different.ShipyardsMap.fightQty = 2 + rand(3); //количество бойцов на верфи
			dialog.text = DLG_TEXT_BASE[72] + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + DLG_TEXT_BASE[73] + pchar.questTemp.different.ShipyardsMap.what + DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "ShipyardsMap_3";
		break;
		case "ShipyardsMap_3":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77];
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "ShipyardsMap_5";
		break;
		case "ShipyardsMap_5":
			dialog.text = DLG_TEXT_BASE[80];
			link.l1 = DLG_TEXT_BASE[81];
			link.l1.go = "ShipyardsMap_disagree";
			link.l2 = DLG_TEXT_BASE[82];
			link.l2.go = "ShipyardsMap_agree";
		break;

		case "ShipyardsMap_disagree":
			dialog.text = DLG_TEXT_BASE[83];
			link.l1 = DLG_TEXT_BASE[84];
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		case "ShipyardsMap_agree":
			dialog.text = DLG_TEXT_BASE[85];
			link.l1 = DLG_TEXT_BASE[86];
			link.l1.go = "exit";
			sld = ItemsFromID("ShipyardsMap");
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.ShipyardsMap.city + "_Shipyard";
			sld.startLocator = "item1";
			sld.ShipName = pchar.questTemp.different.ShipyardsMap.what;
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "1");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Dat"));
			AddQuestUserData("ShipyardsMap", "sShip", pchar.questTemp.different.ShipyardsMap.what);
		break;

		case "Allarm":
			dialog.text = DLG_TEXT_BASE[87];
			link.l1 = DLG_TEXT_BASE[88];
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			AddCharacterExpToSkill(pchar, "FencingLight", 10);
			AddCharacterExpToSkill(pchar, "Fencing", 10);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 10);
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=sti(pchar.questTemp.different.ShipyardsMap.fightQty); i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "Allarm_1":
			dialog.text = DLG_TEXT_BASE[89];
			link.l1 = DLG_TEXT_BASE[90];
			link.l1.go = "fight";
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "ShipyardsMapOk_1":
			sTemp = pchar.questTemp.different.ShipyardsMap.what;
			dialog.text = DLG_TEXT_BASE[91] + strcut(sTemp, 0, strlen(sTemp)-2) + "...";
			link.l1 = DLG_TEXT_BASE[92];
			link.l1.go = "ShipyardsMapOk_2";
		break;
		case "ShipyardsMapOk_2":
			TakeItemFromCharacter(pchar, "ShipyardsMap");
			if (sti(pchar.questTemp.different.ShipyardsMap.chance) > 0)
			{
				dialog.text = DLG_TEXT_BASE[93] + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.chance)*1000) + ".";
				link.l1 = DLG_TEXT_BASE[94];
				link.l1.go = "ShipyardsMapOk_5";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[95];
				link.l1 = DLG_TEXT_BASE[96];
				link.l1.go = "ShipyardsMapOk_3";
			}
		break;

		case "ShipyardsMapOk_3":
			dialog.text = DLG_TEXT_BASE[97];
			link.l1 = DLG_TEXT_BASE[98];
			link.l1.go = "ShipyardsMapOk_4";
			link.l2 = DLG_TEXT_BASE[99];
			link.l2.go = "Allarm_1";
		break;
		case "ShipyardsMapOk_4":
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "3");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = DLG_TEXT_BASE[102];
			link.l1 = DLG_TEXT_BASE[103];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			AddQuestRecord("ShipyardsMap", "4");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "iMoney", sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			CloseQuestHeader("ShipyardsMap");
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		
        ////////////////////////////////////////////////homo линейка Ѕлада/////////////////////////////////////////
        case "Blood_Shipyard1":
			dialog.text = DLG_TEXT_BASE[104];
			link.l1 = DLG_TEXT_BASE[105];
			link.l1.go = "Blood_Shipyard2";
			link.l2 = DLG_TEXT_BASE[106];
			link.l2.go = "Blood_Shipyard3";
			link.l3 = DLG_TEXT_BASE[107];
			link.l3.go = "Blood_Shipyard4";
		break;
		
		case "Blood_Shipyard2":
			dialog.text = DLG_TEXT_BASE[108];
			link.l1 = DLG_TEXT_BASE[109];
			link.l1.go = "Blood_Shipyard5";

		break;
		case "Blood_Shipyard3":
			dialog.text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111];
			link.l1.go = "exit";
			CloseQuestHeader("PirateQuest");
			Pchar.questTemp.CapBloodLine.ShipForJack = false;

		break;
        case "Blood_Shipyard4":
			dialog.text = DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "Blood_Shipyard6";
		break;
		
        case "Blood_Shipyard5":
			dialog.text = DLG_TEXT_BASE[114];
			link.l1 = DLG_TEXT_BASE[115];
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard6":
			dialog.text = DLG_TEXT_BASE[116];
			link.l1 = DLG_TEXT_BASE[117];
			link.l1.go = "Blood_Shipyard7";
		break;
		
        case "Blood_Shipyard7":
			dialog.text = DLG_TEXT_BASE[118];
			link.l1 = DLG_TEXT_BASE[119];
			link.l1.go = "Blood_Shipyard8";
		break;
		
        case "Blood_Shipyard8":
			dialog.text = DLG_TEXT_BASE[120];
			link.l1 = DLG_TEXT_BASE[121];
			link.l1.go = "Blood_Shipyard9";
			link.l2 = DLG_TEXT_BASE[122];
			link.l2.go = "Blood_Shipyard10";
		break;
		
        case "Blood_Shipyard9":
			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;
		
        case "Blood_Shipyard10":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "Blood_Shipyard11";
		break;
		
        case "Blood_Shipyard11":
			dialog.text = DLG_TEXT_BASE[127];
			link.l1 = DLG_TEXT_BASE[128];
			link.l1.go = "Blood_Shipyard12";
		break;
		
        case "Blood_Shipyard12":
			dialog.text = DLG_TEXT_BASE[129];
			link.l1 = DLG_TEXT_BASE[130];
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "3");
		break;

	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}
