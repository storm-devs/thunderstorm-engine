#include "TEXT\DIALOGS\Smuggler Agent_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;

			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = DLG_TEXT_BASE[0];
				Link.l1 = DLG_TEXT_BASE[1] + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				Dialog.Text = DLG_TEXT_BASE[2];
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4]);
				}
				if(FindFirstContrabandGoods(PChar) != -1)
				{
					Link.l1 = DLG_TEXT_BASE[5];
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = DLG_TEXT_BASE[6];
				else
					Link.l2 = DLG_TEXT_BASE[7];
				Link.l2.go = "Travel";
				
				Link.l3 = DLG_TEXT_BASE[8];
				Link.l3.go = "Exit";				
			}
		break;

		case "Meeting":
			Dialog.Text = DLG_TEXT_BASE[9];
			if(FindFirstContrabandGoods(PChar) != -1)
			{
				Link.l1 = DLG_TEXT_BASE[10];
				Link.l1.go = "Meeting_1";
			}
			Link.l2 = DLG_TEXT_BASE[11];
			Link.l2.go = "Travel";				
			Link.l3 = DLG_TEXT_BASE[12];
			Link.l3.go = "Exit";				
		break;

		case "Meeting_1":
			Dialog.Text = DLG_TEXT_BASE[13];
			Link.l1 = DLG_TEXT_BASE[14];
			Link.l1.go = "Meeting_2";				
			Link.l2 = DLG_TEXT_BASE[15];
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = DLG_TEXT_BASE[16];
			Link.l1 = DLG_TEXT_BASE[17];
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = DLG_TEXT_BASE[18];
				Link.l1 = DLG_TEXT_BASE[19];
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2)
			{
				Dialog.Text = DLG_TEXT_BASE[20];
				Link.l1 = DLG_TEXT_BASE[21];
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = DLG_TEXT_BASE[22] + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = DLG_TEXT_BASE[23] + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = DLG_TEXT_BASE[24];
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = DLG_TEXT_BASE[25];
            				Link.l1 = DLG_TEXT_BASE[26];
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = DLG_TEXT_BASE[27];
        				Link.l1 = DLG_TEXT_BASE[28];
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = DLG_TEXT_BASE[29];
    				Link.l1 = DLG_TEXT_BASE[30];
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = DLG_TEXT_BASE[31];
				Link.l1 = DLG_TEXT_BASE[32];
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = DLG_TEXT_BASE[33];
						Link.l2 = DLG_TEXT_BASE[34];
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = DLG_TEXT_BASE[35];
							Link.l1 = DLG_TEXT_BASE[36];
							Link.l1.go = "Travel_pay";
							Link.l3 = DLG_TEXT_BASE[37];
							Link.l3.go = "Travel_abort";
							Link.l2 = DLG_TEXT_BASE[38];
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = DLG_TEXT_BASE[39];
								Link.l2 = DLG_TEXT_BASE[40];
								Link.l1 = DLG_TEXT_BASE[41];
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = DLG_TEXT_BASE[42];
								Link.l2 = DLG_TEXT_BASE[43];
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и еще сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = DLG_TEXT_BASE[44] + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + DLG_TEXT_BASE[45] +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + DLG_TEXT_BASE[46] + pchar.GenQuest.contraTravel.price + DLG_TEXT_BASE[47] +
								FindRussianDaysString(nDay) + DLG_TEXT_BASE[48] +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + DLG_TEXT_BASE[49];

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = DLG_TEXT_BASE[50];
							Link.l1.go = "Travel_agree";
							Link.l2 = DLG_TEXT_BASE[51];
						}
						else
						{
							Dialog.Text = DLG_TEXT_BASE[52];
							Link.l2 = DLG_TEXT_BASE[53];
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = DLG_TEXT_BASE[54];
        				Link.l2 = DLG_TEXT_BASE[55];
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = DLG_TEXT_BASE[56];
					Link.l2 = RandSwear() + DLG_TEXT_BASE[57];
				}
				else
				{
					Dialog.Text = DLG_TEXT_BASE[58];
					Link.l2 = DLG_TEXT_BASE[59];
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = DLG_TEXT_BASE[60];
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = DLG_TEXT_BASE[61];
				Link.l1 = DLG_TEXT_BASE[62];
				AddQuestRecord("Gen_ContrabandTravel", "2");
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "pirate_6", "man", "man", 5, PIRATE, Sum + 2, true));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_SILVER));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = DLG_TEXT_BASE[63]
				Link.l1 = DLG_TEXT_BASE[64];
			}
			Link.l1.go = "Exit";
			break;  
			
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
	}
}
