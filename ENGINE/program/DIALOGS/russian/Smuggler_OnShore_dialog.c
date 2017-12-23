#include "TEXT\DIALOGS\Smuggler_OnShore_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[0],
                                          RandSwear() + DLG_TEXT_BASE[1]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]);
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = DLG_TEXT_BASE[4] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + DLG_TEXT_BASE[5];
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = DLG_TEXT_BASE[8] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + DLG_TEXT_BASE[9];
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = DLG_TEXT_BASE[10];
						Link.l1 = DLG_TEXT_BASE[11];
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[12], DLG_TEXT_BASE[13]);
						Link.l1 = DLG_TEXT_BASE[14];
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбитьс€, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // еще бой идет
						{
						    dialog.Text = DLG_TEXT_BASE[15];
							Link.l1 = DLG_TEXT_BASE[16];
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[17], DLG_TEXT_BASE[18]);
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 10 + 4 * makeint(sti(PChar.rank)/2));
					}
					//тут все ок, отправл€емс€.
					Link.l2 = DLG_TEXT_BASE[19];
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим √ре€ в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(DLG_TEXT_BASE[20] + sti(Pchar.GenQuest.contraTravel.destination.days) + DLG_TEXT_BASE[21] + NewStr() + DLG_TEXT_BASE[22],
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 10 + 4 * makeint(sti(PChar.rank)/2));
					}
//================ METRO ====================
				}
				else
				{
                    // если таможн€ уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+ DLG_TEXT_BASE[23];
						Link.l1 = DLG_TEXT_BASE[24];
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = DLG_TEXT_BASE[25];
						Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[26], DLG_TEXT_BASE[27]);
						Link.l1.go = "Exit_fight";
						Link.l2 = DLG_TEXT_BASE[28];
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = DLG_TEXT_BASE[29];
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31]);
			Link.l1.go = "No_ship_1";
			Link.l2 = DLG_TEXT_BASE[32];
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = DLG_TEXT_BASE[33];
			Link.l1 = DLG_TEXT_BASE[34];
			Link.l1.go = "Exit";
		break;
		
		case "Exit_fight":
            //DeleteAttribute(Pchar, "quest.Contraband");
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
			DeleteAttribute(Pchar, "quest.Contraband.price1");
			DeleteAttribute(Pchar, "quest.Contraband.price2");
			DeleteAttribute(Pchar, "quest.Contraband.price3");
			DeleteAttribute(Pchar, "quest.Contraband.price4");
			DeleteAttribute(Pchar, "quest.Contraband.price5");
			DeleteAttribute(Pchar, "quest.Contraband.price6");
			DeleteAttribute(Pchar, "quest.Contraband.price7");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX1");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX2");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX3");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX4");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX5");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX6");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX7");
			DeleteAttribute(Pchar, "quest.Contraband.sum");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsQty");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsID");


			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = DLG_TEXT_BASE[35];
    			Link.l1 = DLG_TEXT_BASE[36];
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = DLG_TEXT_BASE[37];
    			Link.l1 = DLG_TEXT_BASE[38];
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = DLG_TEXT_BASE[39];
					Link.l1 = DLG_TEXT_BASE[40];
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = DLG_TEXT_BASE[41];
					Link.l1 = DLG_TEXT_BASE[42];
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = DLG_TEXT_BASE[43];
				Link.l1 = DLG_TEXT_BASE[44];
				Link.l1.go = "Exit_cancel";			
			}	
		break;
		
        case "GenQuestKillContraband_1":
			//счетчик подстав по DLG_TEXT_BASE[45]...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = DLG_TEXT_BASE[46];
			Link.l1 = DLG_TEXT_BASE[47];
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exchange":
			// сама торговл€ -->
            if(FindFirstContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = DLG_TEXT_BASE[48];
				Link.l1 = DLG_TEXT_BASE[49];
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали еще
                {
                    if(rand(11) == 3)
                    {
        				dialog.Text = DLG_TEXT_BASE[50];
        				Link.l1 = DLG_TEXT_BASE[51];
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше Ќ≈«ј¬»—»ћџ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патрул€ на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
                dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[52],
                                          DLG_TEXT_BASE[53]);
                shit = FindFirstContrabandGoods(Pchar);
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX1 = shit;
    				Pchar.quest.Contraband.price1 = GetCurrentIslandGoodsPrice(shit);
    				Link.l1 = XI_ConvertString(Goods[shit].name);
				    Link.l1.go = "goodsIDX1";
    			}
    			shit = FindNextContrabandGoods(Pchar);
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX2 = shit;
    				Pchar.quest.Contraband.price2 = GetCurrentIslandGoodsPrice(shit);
    				Link.l2 = XI_ConvertString(Goods[shit].name);
				    Link.l2.go = "goodsIDX2";
    			}
    			shit = FindNextContrabandGoods(Pchar);
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX3 = shit;
    				Pchar.quest.Contraband.price3 = GetCurrentIslandGoodsPrice(shit);
    				Link.l3 = XI_ConvertString(Goods[shit].name);
				    Link.l3.go = "goodsIDX3";
    			}
    			shit = FindNextContrabandGoods(Pchar);
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX4 = shit;
    				Pchar.quest.Contraband.price4 = GetCurrentIslandGoodsPrice(shit);
    				Link.l4 = XI_ConvertString(Goods[shit].name);
				    Link.l4.go = "goodsIDX4";
    			}
    			shit = FindNextContrabandGoods(Pchar);
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX5 = shit;
    				Pchar.quest.Contraband.price5 = GetCurrentIslandGoodsPrice(shit);
    				Link.l5 = XI_ConvertString(Goods[shit].name);
				    Link.l5.go = "goodsIDX5";
    			}
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX6 = shit;
    				Pchar.quest.Contraband.price6 = GetCurrentIslandGoodsPrice(shit);
    				Link.l6 = XI_ConvertString(Goods[shit].name);
				    Link.l6.go = "goodsIDX6";
    			}
    			if(shit != -1)
    			{
    				Pchar.quest.Contraband.goodsIDX7 = shit;
    				Pchar.quest.Contraband.price7 = GetCurrentIslandGoodsPrice(shit);
    				Link.l7 = XI_ConvertString(Goods[shit].name);
				    Link.l7.go = "goodsIDX7";
    			}
    			if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = DLG_TEXT_BASE[54];
    				Link.l99.go = "Cancellation";
				}
				else
				{
        			Link.l99 = DLG_TEXT_BASE[55];
    				Link.l99.go = "Finish_exit";
				}
            }
		break;

        case "goodsIDX1":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX1;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price1);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[56] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[57]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[58];
			Link.l1 = DLG_TEXT_BASE[59];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[60];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX2":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX2;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price2);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[61] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[62]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[63];
			Link.l1 = DLG_TEXT_BASE[64];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[65];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX3":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX3;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price3);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[66] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[67]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[68];
			Link.l1 = DLG_TEXT_BASE[69];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[70];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX4":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX4;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price4);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[71] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[72]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[73];
			Link.l1 = DLG_TEXT_BASE[74];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[75];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX5":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX5;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price5);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[76] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[77]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[78];
			Link.l1 = DLG_TEXT_BASE[79];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[80];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX6":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX6;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price6);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[81] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[82]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[83];
			Link.l1 = DLG_TEXT_BASE[84];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[85];
			Link.l2.go = "Cancellation";
		break;
		
		case "goodsIDX7":
            Pchar.quest.Contraband.ChooseGoodsID    = Pchar.quest.Contraband.goodsIDX7;
            Pchar.quest.Contraband.ChooseGoodsPrice = sti(Pchar.quest.Contraband.price7);
            Pchar.quest.Contraband.ChooseGoodsUnit  = sti(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].Units);

			dialog.Text = XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[86] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[87]+ Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[88];
			Link.l1 = DLG_TEXT_BASE[89];
			Link.l1.go = "Make_trade_1";
			Link.l2 = DLG_TEXT_BASE[90];
			Link.l2.go = "Cancellation";
		break;
		
		case "Make_trade_1":
			dialog.Text = DLG_TEXT_BASE[91]+XI_ConvertString(Goods[sti(Pchar.quest.Contraband.ChooseGoodsID)].name) + DLG_TEXT_BASE[92]+
                     GetSquadronGoods(Pchar, sti(Pchar.quest.Contraband.ChooseGoodsID)) + DLG_TEXT_BASE[93] + Pchar.quest.Contraband.ChooseGoodsPrice +DLG_TEXT_BASE[94]+Pchar.quest.Contraband.ChooseGoodsUnit+DLG_TEXT_BASE[95];
			Link.l1 = DLG_TEXT_BASE[96];
			Link.l1.go = "Make_trade_Sell_All";
			Link.l2 = DLG_TEXT_BASE[97];
			Link.l2.go = "Make_trade_Sell_Half";
			Link.l3 = DLG_TEXT_BASE[98];
			Link.l3.go = "Make_trade_Sell_10th";
			Link.l9 = DLG_TEXT_BASE[99];
			Link.l9.go = "Cancellation";
		break;
		
		case "Make_trade_Sell_All":
            Pchar.quest.Contraband.ChooseGoodsQty =  GetSquadronGoods(Pchar, sti(Pchar.quest.Contraband.ChooseGoodsID));
            pchar.quest.contraband.sum = makeint(stf(Pchar.quest.Contraband.ChooseGoodsQty) * stf(Pchar.quest.Contraband.ChooseGoodsPrice) / stf(Pchar.quest.Contraband.ChooseGoodsUnit));
            
			dialog.Text = DLG_TEXT_BASE[100] + Pchar.quest.Contraband.ChooseGoodsQty + DLG_TEXT_BASE[101]+ pchar.quest.contraband.sum + DLG_TEXT_BASE[102];
			Link.l1 = DLG_TEXT_BASE[103];
			Link.l1.go = "Make_trade_End";
			Link.l9 = DLG_TEXT_BASE[104];
			Link.l9.go = "Cancellation";
		break;
		
		case "Make_trade_Sell_Half":
            Pchar.quest.Contraband.ChooseGoodsQty =  makeint(GetSquadronGoods(Pchar, sti(Pchar.quest.Contraband.ChooseGoodsID)) / 2);
            pchar.quest.contraband.sum = makeint(stf(Pchar.quest.Contraband.ChooseGoodsQty) * stf(Pchar.quest.Contraband.ChooseGoodsPrice) / stf(Pchar.quest.Contraband.ChooseGoodsUnit));

			dialog.Text = DLG_TEXT_BASE[105] + Pchar.quest.Contraband.ChooseGoodsQty + DLG_TEXT_BASE[106]+ pchar.quest.contraband.sum + DLG_TEXT_BASE[107];
			Link.l1 = DLG_TEXT_BASE[108];
			Link.l1.go = "Make_trade_End";
			Link.l9 = DLG_TEXT_BASE[109];
			Link.l9.go = "Cancellation";
		break;
		
		case "Make_trade_Sell_10th":
            Pchar.quest.Contraband.ChooseGoodsQty =  makeint(GetSquadronGoods(Pchar, sti(Pchar.quest.Contraband.ChooseGoodsID)) / 10);
            pchar.quest.contraband.sum = makeint(stf(Pchar.quest.Contraband.ChooseGoodsQty) * stf(Pchar.quest.Contraband.ChooseGoodsPrice) / stf(Pchar.quest.Contraband.ChooseGoodsUnit));

			dialog.Text = DLG_TEXT_BASE[110] + Pchar.quest.Contraband.ChooseGoodsQty + DLG_TEXT_BASE[111]+ pchar.quest.contraband.sum + DLG_TEXT_BASE[112];
			Link.l1 = DLG_TEXT_BASE[113];
			Link.l1.go = "Make_trade_End";
			Link.l9 = DLG_TEXT_BASE[114];
			Link.l9.go = "Cancellation";
		break;

		case "NoGoods":
			Dialog.snd = "voice\SMSH\SMSH015";
			ChangeContrabandRelation(pchar, -10);
			dialog.Text = DLG_TEXT_BASE[115];
			Link.l1 = DLG_TEXT_BASE[116];
			Link.l1.go = "Exit_Cancel";				
		break; 
			
		case "Make_trade_End":
            RemoveCharacterGoods(Pchar, makeint(Pchar.quest.contraband.ChooseGoodsID), makeint(Pchar.quest.contraband.ChooseGoodsQty));
            // засунуть товар в магазин, иначе не работает затаривание 031104 boal -->
            Shit = GetCharacterCurrentStore(Pchar);
            if (Shit >= 0)
            {
                refStore = &Stores[Shit];
                Shit     = sti(Pchar.quest.contraband.ChooseGoodsID);
                SetStoreGoods(refStore, Shit, GetStoreGoodsQuantity(refStore, Shit)+ sti(Pchar.quest.contraband.ChooseGoodsQty));
            }
            // засунуть товар в магазин, иначе не работает затаривание 031104 boal <--
            Pchar.quest.Contraband.Counter = 1; // поторговали!
            AddMoneyToCharacter(Pchar, makeint(Pchar.quest.Contraband.sum));
			dialog.Text = DLG_TEXT_BASE[117];
			Link.l1 = DLG_TEXT_BASE[118];
			Link.l1.go = "Exchange";
			Link.l2 = DLG_TEXT_BASE[119];
			Link.l2.go = "Finish_exit";
		break;
		
		case "Finish_exit":
            // таможн€ на суше
            if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 10 + 4 * makeint(sti(PChar.rank)/2));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterReputation(pchar, -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
			DeleteAttribute(Pchar, "quest.Contraband.price1");
			DeleteAttribute(Pchar, "quest.Contraband.price2");
			DeleteAttribute(Pchar, "quest.Contraband.price3");
			DeleteAttribute(Pchar, "quest.Contraband.price4");
			DeleteAttribute(Pchar, "quest.Contraband.price5");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX1");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX2");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX3");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX4");
			DeleteAttribute(Pchar, "quest.Contraband.goodsIDX5");
			DeleteAttribute(Pchar, "quest.Contraband.sum");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsQty");
			DeleteAttribute(Pchar, "quest.Contraband.ChooseGoodsID");

			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
		break;
	}
}
