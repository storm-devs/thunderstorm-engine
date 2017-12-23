#include "TEXT\DIALOGS\Usurer_dialog.h"
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
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
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff"))
                {
                    dialog.text = DLG_TEXT_BASE[12];
                    Link.l1 = DLG_TEXT_BASE[13];
    				Link.l1.go = "CapBloodUsurer_5";
                    break;
                }
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[14] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[15],
                                    DLG_TEXT_BASE[16] + GetFullName(pchar) + DLG_TEXT_BASE[17]);
                Link.l1 = DLG_TEXT_BASE[18] + NPChar.name + DLG_TEXT_BASE[19];
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == false)//homo линейка Блада
                {
                    Link.l2 = DLG_TEXT_BASE[20];
    				Link.l2.go = "CapBloodUsurer_1";
                }
				break;
            }
			//пиратка, квест №5, заглушка на возврат бабла -->
			if (CheckAttribute(npchar, "PLQ5Money"))
			{
				dialog.text = DLG_TEXT_BASE[21];
				link.l1 = DLG_TEXT_BASE[22];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[23];
				link.l2.go = "StepPL5End_close";
				if (sti(pchar.money) >= 50000)
				{
					link.l3 = DLG_TEXT_BASE[24];
					link.l3.go = "StepPL5End_1";
				}
				break;
			}
			//<--пиратка, квест №5, заглушка на возврат бабла
			//-->> дача квеста найти потерянный драгоценный камень
			if (rand(1) && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel"))
			{
				dialog.text = DLG_TEXT_BASE[25];
				link.l1 = DLG_TEXT_BASE[26];
				link.l1.go = "usurersJewel_1";
				npchar.quest.usurersJewel = "inSeek"; //личный флаг ростовщика на взятый квест
				SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
				break;
			}
			//<<-- дача квеста найти потерянный драгоценный камень
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[27] + GetAddress_Form(npchar) + DLG_TEXT_BASE[28], 
				DLG_TEXT_BASE[29] + GetAddress_Form(npchar) + DLG_TEXT_BASE[30], 
				DLG_TEXT_BASE[31] + GetAddress_Form(npchar) + DLG_TEXT_BASE[32],
                DLG_TEXT_BASE[33] + GetAddress_Form(npchar) + DLG_TEXT_BASE[34] , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[35], 
				DLG_TEXT_BASE[36],
                DLG_TEXT_BASE[37], 
				DLG_TEXT_BASE[38], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[39];
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = DLG_TEXT_BASE[40];
			link.l3.go = "quests";//(перессылка в файл города)
			//линейка ГПК, закладка миллиона на депозит
			if (CheckAttribute(pchar, "questTemp.LSC.usurerId") && pchar.questTemp.LSC.usurerId == npchar.id)
			{
				if (pchar.questTemp.LSC == "SignOnPoorMurder")
				{
					link.l4 = DLG_TEXT_BASE[41];
					link.l4.go = "ISS_deposit";
				}
				if (pchar.questTemp.LSC == "PoorMurderExecute")
				{
					link.l4 = DLG_TEXT_BASE[42];
					link.l4.go = "ISS_takeDeposit";
					DeleteAttribute(pchar, "questTemp.LSC.usurerId");
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple(DLG_TEXT_BASE[43] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[44]);
				link.l7.go = "IntelligenceForAll";
			}
			//<<<<---------------- пиратка, квест №5. --------------------
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1") && npchar.city == pchar.questTemp.piratesLine.Q5.city_1)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirstUsurer")
				{
					link.l5 = DLG_TEXT_BASE[45];
					link.l5.go = "StepPL5First_1";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst")
				{
					link.l5 = DLG_TEXT_BASE[46];
					link.l5.go = "StepPL5First_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2") && npchar.city == pchar.questTemp.piratesLine.Q5.city_2)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecondUsurer")
				{
					link.l5 = DLG_TEXT_BASE[47];
					link.l5.go = "StepPL5Second_0";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond")
				{
					link.l5 = DLG_TEXT_BASE[48];
					link.l5.go = "StepPL5Second_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3") && npchar.city == pchar.questTemp.piratesLine.Q5.city_3)
			{
				if (pchar.questTemp.piratesLine == "PPL5Hunter_toThirdUsurer" || pchar.questTemp.piratesLine == "PPL5Hunter_toThird")
				{
					link.l5 = DLG_TEXT_BASE[49];
					link.l5.go = "StepPL5Third_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_4") && npchar.city == pchar.questTemp.piratesLine.Q5.city_4)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFourth")
				{
					link.l5 = DLG_TEXT_BASE[50];
					link.l5.go = "StepPL5Four_1";
				}
			}
			//-------------------- пиратка, квест №5. ---------------->>>>
			//-->> сдача квеста найти потерянный драгоценный камень
			if (CheckCharacterItem(pchar, "UsurersJew") && CheckAttribute(npchar, "quest.usurersJewel.type"))
			{
				link.l6 = DLG_TEXT_BASE[51] + npchar.quest.usurersJewel.type + DLG_TEXT_BASE[52];
				link.l6.go = "usurersJewel_R1";
			}
			//<<-- сдача квеста найти потерянный драгоценный камень
			NextDiag.TempNode = "First time";
		break;

		//<<<<---------------- пиратка, квест №5. --------------------
		case "StepPL5First_1":
			dialog.text = DLG_TEXT_BASE[53];
			link.l1 = DLG_TEXT_BASE[54];
			link.l1.go = "StepPL5First_2";
		break;
		case "StepPL5First_2":
			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "StepPL5First_3";
		break;
		case "StepPL5First_3":
			pchar.questTemp.piratesLine.Q5.city_2 = GetQuestNationsCity(SPAIN); 
			dialog.text = DLG_TEXT_BASE[57] + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Dat") + DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "4");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Acc"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_2) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecond";
		break;

		case "StepPL5Second_0":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "StepPL5Second_1";
		break;
		case "StepPL5Second_1":
			dialog.text = DLG_TEXT_BASE[62]+
				DLG_TEXT_BASE[63]+
				DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "StepPL5Second_2";
		break;
		case "StepPL5Second_2":
			pchar.questTemp.piratesLine.Q5.city_3 = GetQuestNationsCity(FRANCE);
			dialog.text = DLG_TEXT_BASE[66];
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "6");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_3) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toThird";
		break;

		case "StepPL5Third_1":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "StepPL5Third_2";
		break;
		case "StepPL5Third_2":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "StepPL5Third_3";
		break;
		case "StepPL5Third_3":
			pchar.questTemp.piratesLine.Q5.city_4 = GetQuestNationsCity(Holland);
			dialog.text = DLG_TEXT_BASE[72] + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4) + ".";
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "StepPL5Third_4";
		break;
		case "StepPL5Third_4":
			dialog.text = DLG_TEXT_BASE[74] + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Dat") + DLG_TEXT_BASE[75];
			link.l1 = DLG_TEXT_BASE[76];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "8");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_4) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFourth";
		break;

		case "StepPL5Four_1":
			dialog.text = DLG_TEXT_BASE[77];
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "StepPL5Four_2";
		break;
		case "StepPL5Four_2":
			dialog.text = DLG_TEXT_BASE[78];
			link.l1 = DLG_TEXT_BASE[79];
			link.l1.go = "StepPL5Four_3";
		break;
		case "StepPL5Four_3":
			dialog.text = DLG_TEXT_BASE[80];
			link.l1 = DLG_TEXT_BASE[81];
			link.l1.go = "StepPL5Four_4";
		break;
		case "StepPL5Four_4":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "StepPL5Four_5";
		break;
		case "StepPL5Four_5":
			dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "StepPL5Four_6";
		break;
		case "StepPL5Four_6":
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "StepPL5Four_7";
		break;
		case "StepPL5Four_7":
			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "9");
			pchar.questTemp.piratesLine = "PL5Hunter_toBermudes";
			npchar.PLQ5Money = true; //метка на ростовщика, которому должен бабла
			//здесь ставим прерывание на вход в дом Орри на Бермудах
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1 = "location";
            Pchar.quest.PQ5_inOrryHouse.win_condition.l1.location = "Pirates_houseS1";
            Pchar.quest.PQ5_inOrryHouse.function = "PQ5_inOrryHouse";
		break;

		case "StepPL5End_close":
			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[91];
			link.l1.go = "exit";
			DeleteAttribute(npchar, "PLQ5Money");
    		ChangeCharacterReputation(pchar, -50);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -20);
		break;

		case "StepPL5End_1":
			dialog.text = DLG_TEXT_BASE[92];
			link.l1 = DLG_TEXT_BASE[93];
			link.l1.go = "StepPL5End_2";
		break;
		case "StepPL5End_2":
			dialog.text = DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "StepPL5End_3";
		break;
		case "StepPL5End_3":
			dialog.text = DLG_TEXT_BASE[96];
			link.l1 = DLG_TEXT_BASE[97];
			link.l1.go = "StepPL5End_4";
			DeleteAttribute(npchar, "PLQ5Money");
			AddMoneyToCharacter(pchar, -45000);
    		ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
		break;
		case "StepPL5End_4":
			dialog.text = DLG_TEXT_BASE[98];
			link.l1 = DLG_TEXT_BASE[99];
			link.l1.go = "exit";
		break;
		//-------------------- пиратка, квест №5. ---------------->>>>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer": 
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "Loan_GiveWork";
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
            {
                link.l2 = DLG_TEXT_BASE[102];
                link.l2.go = "FindCitizen_1";
            }
			//доставить сундук
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
            {
                link.l3 = DLG_TEXT_BASE[103];
                link.l3.go = "TakeChest_1";
            }
            if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l4 = DLG_TEXT_BASE[104];
                link.l4.go = "TakeChest_2";
            }
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = DLG_TEXT_BASE[105]+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(DLG_TEXT_BASE[106], DLG_TEXT_BASE[107], DLG_TEXT_BASE[108]);
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase(DLG_TEXT_BASE[109], DLG_TEXT_BASE[110], DLG_TEXT_BASE[111]);
				Link.l6.go = "loan";	
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase(DLG_TEXT_BASE[112],DLG_TEXT_BASE[113], DLG_TEXT_BASE[114]);
					Link.l7.go = "deposit";				
				}
			}
			if(CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear),makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth),makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Deposits.(NPC_Area).Interest))*iPastMonths;
				Link.l8 = LinkRandPhrase(DLG_TEXT_BASE[115], DLG_TEXT_BASE[116], DLG_TEXT_BASE[117]);
				Link.l8.go = "Deposit_return";									
			}
			//выход
			if (sTemp == "credit")
			{
				link.l9 = LinkRandPhrase(DLG_TEXT_BASE[118], DLG_TEXT_BASE[119], DLG_TEXT_BASE[120]);
				link.l9.go = "Loan_Remind";
			}
			else
			{
				link.l9 = DLG_TEXT_BASE[121];
				link.l9.go = "exit";
			}
		break;
		//=============================  даем или не даем работу - сундуки и должники
		case "Loan_GiveWork": 
            // проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[122] + GetFullName(pchar)+ DLG_TEXT_BASE[123] +
                              RandPhraseSimple(DLG_TEXT_BASE[124],DLG_TEXT_BASE[125]) + DLG_TEXT_BASE[126];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[127], RandSwear() + DLG_TEXT_BASE[128]);
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
            dialog.text = DLG_TEXT_BASE[129];

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
                npchar.quest.trade_date = lastspeak_date;
                iNum = rand(1);
                if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
                {
                    iNum = 0; // всегда первый
                }
                switch (iNum)
                {
                    case 0 : // найти должника
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;
                        
                        if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
                        {
                            iNum = findCitizenMan(Npchar, true);
                            npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // знатичит на суше без корабля
                        }
                        else
                        {
                            iNum = findCitizenMan(Npchar, false);
                        }
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.Loan.FindCitizenMoney   = (1 + cRand(sti(PChar.rank)))*400 + cRand(10)*100;
                            pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3+rand(2)));
                            pchar.GenQuest.Loan.FindCitizenIdx  =  iNum;
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = DLG_TEXT_BASE[130] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = DLG_TEXT_BASE[131]+
                                     GetFullName(chr) + DLG_TEXT_BASE[132] + XI_ConvertString("Colony"+chr.city+"Dat") + sTemp + DLG_TEXT_BASE[133] + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)) +
                                     DLG_TEXT_BASE[134] + FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)) + ".";
                            link.l1 = DLG_TEXT_BASE[135];
                			link.l1.go = "LoanUsurer_GiveWork_1";
            			}
                    break;

                    case 1: // доставить сундуки
                        if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;
                        
                        iNum = findChestMan(Npchar);
                        if (iNum > 0)
                        {
                            chr = &Characters[iNum];
                            pchar.GenQuest.LoanChest.Chest      = 2 + rand(2);
                            pchar.GenQuest.LoanChest.Money      = (1 + cRand(sti(pchar.GenQuest.LoanChest.Chest)))*400 + cRand(10)*100;
                            pchar.GenQuest.LoanChest.TargetIdx  =  iNum;
                            pchar.GenQuest.LoanChest.Time       = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = DLG_TEXT_BASE[136] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
							}
                            dialog.text = DLG_TEXT_BASE[137] + pchar.GenQuest.LoanChest.Chest + 
									DLG_TEXT_BASE[138]+ XI_ConvertString("Colony"+chr.city+"Acc") + sTemp + DLG_TEXT_BASE[139] +
									GetFullName(chr) + DLG_TEXT_BASE[140] + GetWorkTypeOfMan(chr, "") +
									DLG_TEXT_BASE[141] + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)) + DLG_TEXT_BASE[142] + FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)) + ".";
                            link.l1 = DLG_TEXT_BASE[143];
                			link.l1.go = "LoanUsurer_ChestWork_1";
            			}
                     break;
    			}
    		}
            else
            {
                dialog.text = DLG_TEXT_BASE[144];
            }
            link.l9 = DLG_TEXT_BASE[145];
		    link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
            pchar.GenQuest.Loan.FindCitizen = true;
            pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
            dialog.text = DLG_TEXT_BASE[146];
			link.l9 = DLG_TEXT_BASE[147];
			link.l9.go = "exit";			
            chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];     
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = DLG_TEXT_BASE[148] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
            AddQuestRecord("Gen_LoanFindCitizen", "1");
            AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
            AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony"+chr.city+"Dat") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindRussianMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
            dialog.text = DLG_TEXT_BASE[149];
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
            {
                link.l1 = DLG_TEXT_BASE[150];
                link.l1.go = "finish_work";
                link.l2 = DLG_TEXT_BASE[151];
                if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
                {
                    link.l2.go = "finish_work_bad";
                }
                else
                {
                    link.l2.go = "finish_work_lie";
                }
            }

            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                link.l1 = DLG_TEXT_BASE[152];
                link.l1.go = "finish_work_bad";
            }
            link.l3 = DLG_TEXT_BASE[153];
            link.l3.go = "finish_work_cancel";
            link.l9 = DLG_TEXT_BASE[154];
			link.l9.go = "exit";
		break; 

		case "finish_work":
            if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
            {
                dialog.text = DLG_TEXT_BASE[155];
    			link.l9 = DLG_TEXT_BASE[156];
    			link.l9.go = "exit";
    			AddMoneyToCharacter(Pchar, -1*sti(pchar.GenQuest.Loan.FindCitizenMoney));
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
    			ChangeCharacterReputation(pchar, 1);
    			OfficersReaction("good");    			
    			AddQuestRecord("Gen_LoanFindCitizen", "4");
                CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
			    dialog.text = DLG_TEXT_BASE[157];
    			link.l9 = DLG_TEXT_BASE[158];
    			link.l9.go = "exit";
    		}
		break;
		
		case "finish_work_bad":
            dialog.text = DLG_TEXT_BASE[159];
			link.l9 = DLG_TEXT_BASE[160];
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
            CloseQuestHeader("Gen_LoanFindCitizen");
		break;
		
		case "finish_work_cancel":
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                dialog.text = DLG_TEXT_BASE[161];
                link.l1 = DLG_TEXT_BASE[162];
    			link.l1.go = "finish_work";
    			link.l2 = DLG_TEXT_BASE[163];
    			if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
                {
    			   link.l2.go = "finish_work_bad";
    			}
    			else
    			{
    			   link.l2.go = "finish_work_bad_2";
    			}
    			link.l9 = DLG_TEXT_BASE[164];
    			link.l9.go = "exit";
    			ChangeCharacterReputation(pchar, -1);
			}
            else
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = DLG_TEXT_BASE[165];
                link.l1 = DLG_TEXT_BASE[166];
    			link.l1.go = "exit";
    			DeleteAttribute(pchar, "GenQuest.Loan");
    			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
    			AddQuestRecord("Gen_LoanFindCitizen", "6");
                CloseQuestHeader("Gen_LoanFindCitizen");
            }
		break;
		
		case "finish_work_bad_2":
            dialog.text = DLG_TEXT_BASE[167];
            link.l1 = DLG_TEXT_BASE[168];
    		link.l1.go = "finish_work";
		break;
		
		case "finish_work_lie":
            dialog.text = DLG_TEXT_BASE[169];
            link.l1 = DLG_TEXT_BASE[170];
    		link.l1.go = "finish_work_cancel";
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1": 
            pchar.GenQuest.LoanChest.TakeChest = true;
            pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
            dialog.text = DLG_TEXT_BASE[171];
			link.l9 = DLG_TEXT_BASE[172];
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного веселой жизни
            TraderHunterOnMap();
            chr  = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = DLG_TEXT_BASE[173] + XI_ConvertString(GetIslandByCityName(chr.city)+"Dat");
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
            AddQuestRecord("Gen_LoanTakeChest", "1");
            AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony"+Npchar.city+"Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", pchar.GenQuest.LoanChest.Chest);
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony"+chr.city+"Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindRussianDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
            dialog.text = DLG_TEXT_BASE[174];
            link.l1 = DLG_TEXT_BASE[175];
            link.l1.go = "TakeChestFinish_work_cancel";
            link.l9 = DLG_TEXT_BASE[176];
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                ChangeCharacterReputation(pchar, -1);
                dialog.text = DLG_TEXT_BASE[177];
                link.l1 = DLG_TEXT_BASE[178];
    			link.l1.go = "exit";
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
                AddQuestRecord("Gen_LoanTakeChest", "5");
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[179];
                link.l1 = DLG_TEXT_BASE[180];
    			link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = DLG_TEXT_BASE[181];
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = DLG_TEXT_BASE[182];
	                Link.l1.go = "deposit";
				}
                Link.l2 = DLG_TEXT_BASE[183];
				link.l2.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[184] + GetFullName(pchar)+ DLG_TEXT_BASE[185] +
                              RandPhraseSimple(DLG_TEXT_BASE[186],DLG_TEXT_BASE[187]) + DLG_TEXT_BASE[188];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[189], RandSwear() + DLG_TEXT_BASE[190]);
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = DLG_TEXT_BASE[191];
			Link.l1 = DLG_TEXT_BASE[192];
			Link.l1.go = "Small";
			Link.l2 = DLG_TEXT_BASE[193];
			Link.l2.go = "Medium";
			Link.l3 = DLG_TEXT_BASE[194];
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = DLG_TEXT_BASE[195] + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = DLG_TEXT_BASE[196];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[197];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[198];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 11 - makeint(GetCharacterSkillToOld(Pchar, "commerce"));
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = DLG_TEXT_BASE[199] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + DLG_TEXT_BASE[200];
			Link.l1 = DLG_TEXT_BASE[201];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[202];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[203];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(GetCharacterSkillToOld(Pchar, "commerce"));
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = DLG_TEXT_BASE[204] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + DLG_TEXT_BASE[205];
			Link.l1 = DLG_TEXT_BASE[206];
			Link.l1.go = "Interest";
			Link.l2 = DLG_TEXT_BASE[207];
			Link.l2.go = "Loan";
			Link.l3 = DLG_TEXT_BASE[208];
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 26 - makeint(GetCharacterSkillToOld(Pchar, "commerce"));
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest + DLG_TEXT_BASE[209]; 
			Link.l1 = DLG_TEXT_BASE[210];
			Link.l1.go = "Period";
			Link.l3 = DLG_TEXT_BASE[211];
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  DLG_TEXT_BASE[212] + Pchar.name + DLG_TEXT_BASE[213] + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + DLG_TEXT_BASE[214]; 
			Link.l1 = DLG_TEXT_BASE[215];
			Link.l1.go = "LoanGranted";
			Link.l3 = DLG_TEXT_BASE[216];
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = DLG_TEXT_BASE[217];
			Link.l1 = DLG_TEXT_BASE[218];
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = DLG_TEXT_BASE[219];
			Link.l1 = DLG_TEXT_BASE[220];
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 5);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[221], DLG_TEXT_BASE[222],  DLG_TEXT_BASE[223] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[224]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[225], DLG_TEXT_BASE[226], DLG_TEXT_BASE[227]);
			Link.l1.go = "loan";
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[228],DLG_TEXT_BASE[229], DLG_TEXT_BASE[230]);
				Link.l2.go = "deposit";				
			}
			Link.l3 = DLG_TEXT_BASE[231] + NPchar.name + ".";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[232], DLG_TEXT_BASE[233], DLG_TEXT_BASE[234]);
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;

		case "result":
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = makeint(GetCharacterSkillToOld(Pchar, "commerce")/2.0 + 0.33) + 1;
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = DLG_TEXT_BASE[235];
				link.l1 = DLG_TEXT_BASE[236];
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = DLG_TEXT_BASE[237];
				link.l1 = DLG_TEXT_BASE[238];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[239] + Pchar.QuestTemp.Deposits.(NPC_Area).Interest + DLG_TEXT_BASE[240];
			Link.l1 = DLG_TEXT_BASE[241];
			Link.l1.go = "Deposit_placed";
			Link.l2 = DLG_TEXT_BASE[242];
			Link.l2.go = "Deposit";
			Link.l3 = DLG_TEXT_BASE[243];
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)+".Result"))
			{
			    Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = DLG_TEXT_BASE[244] +
				        FindRussianMoneyString(MakeMoneyShow(sti(Pchar.Quest.Deposits.(NPC_Area).Result), MONEY_SIGN,MONEY_DELIVER)) +
				        DLG_TEXT_BASE[245] +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = DLG_TEXT_BASE[246];
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[247];
				Link.l1 = DLG_TEXT_BASE[248];
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum      = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			DialogExit();
		break;

		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = DLG_TEXT_BASE[249] + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)) + DLG_TEXT_BASE[250];
			Link.l1 = DLG_TEXT_BASE[251];			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = DLG_TEXT_BASE[252];			
			Link.l2.go = "Exit";		
		break;

		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[253];			
			Link.l1 = DLG_TEXT_BASE[254];			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[255];
            		Link.l1 = DLG_TEXT_BASE[256];
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[257], DLG_TEXT_BASE[258], DLG_TEXT_BASE[259]);
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = DLG_TEXT_BASE[260];			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = DLG_TEXT_BASE[261];
			Link.l1 = DLG_TEXT_BASE[262] + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + DLG_TEXT_BASE[263];
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = DLG_TEXT_BASE[264] + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = DLG_TEXT_BASE[265];
			Link.l1 = DLG_TEXT_BASE[266];
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
		//поиски драгоценного камня за гордом
		case "usurersJewel_1":
			sld = ItemsFromID("UsurersJew");
			switch (rand(3))
			{
				case 0: 
					sld.JevelType = DLG_TEXT_BASE[267];  
					sld.model = "Diamond";
					sld.picIndex = 2;
				break;
				case 1: 
					sld.JevelType = DLG_TEXT_BASE[268];  
					sld.model = "Ruby";
					sld.picIndex = 3;
				break;
				case 2: 
					sld.JevelType = DLG_TEXT_BASE[269];  
					sld.model = "Emerald";
					sld.picIndex = 4;
				break;
				case 3: 
					sld.JevelType = DLG_TEXT_BASE[270];  
					sld.model = "Sapphire";
					sld.picIndex = 1;
				break;
			}			
			dialog.text = DLG_TEXT_BASE[271] + sld.JevelType + DLG_TEXT_BASE[272];
			link.l1 = DLG_TEXT_BASE[273] + sld.JevelType + DLG_TEXT_BASE[274];
			link.l1.go = "usurersJewel_2";
			npchar.quest.usurersJewel.type = sld.JevelType; //тип камня
			npchar.quest.usurersJewel.money = (cRand(6)+2) * 500; //вознаграждение
		break;
		case "usurersJewel_2":
			dialog.text = DLG_TEXT_BASE[275] + npchar.quest.usurersJewel.type + DLG_TEXT_BASE[276];
			link.l1 = DLG_TEXT_BASE[277];
			link.l1.go = "usurersJewel_3";
		break;
		case "usurersJewel_3":
			dialog.text = DLG_TEXT_BASE[278] + npchar.quest.usurersJewel.type + DLG_TEXT_BASE[279];
			link.l1 = DLG_TEXT_BASE[280];
			link.l1.go = "usurersJewel_4";
		break;
		case "usurersJewel_4":
			dialog.text = DLG_TEXT_BASE[281];
			link.l1 = DLG_TEXT_BASE[282];
			link.l1.go = "usurersJewel_out";
			link.l2 = DLG_TEXT_BASE[283];
			link.l2.go = "usurersJewel_5";
		break;

		case "usurersJewel_out":
			dialog.text = DLG_TEXT_BASE[284];
			link.l1 = DLG_TEXT_BASE[285];
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.usurersJewel");
			ChangeCharacterReputation(pchar, -1);
		break;
		case "usurersJewel_5":
			dialog.text = DLG_TEXT_BASE[286] + npchar.quest.usurersJewel.type + DLG_TEXT_BASE[287];
			link.l1 = DLG_TEXT_BASE[288];
			link.l1.go = "exit";
			pchar.questTemp.different = "SeekUsurersJewel";
			pchar.questTemp.different.SeekUsurersJewel = true;
			//ложим камень
			sld = ItemsFromID("UsurersJew");
			sld.shown = true;
			sld.startLocation = npchar.city + "_ExitTown";
			sld.startLocator = "item" + (rand(14)+1);
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			Log_QuestInfo(DLG_TEXT_BASE[289] + sld.startLocator);
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			sTitle = npchar.city + "UsurersJewel";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SeekUsurersJewel", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sJewType", npchar.quest.usurersJewel.type);
		break;

		case "usurersJewel_R1":
			dialog.text = DLG_TEXT_BASE[290] + npchar.quest.usurersJewel.type + DLG_TEXT_BASE[291];
			link.l1 = DLG_TEXT_BASE[292];
			link.l1.go = "usurersJewel_R2";
			TakeItemFromCharacter(pchar, "UsurersJew");
		break;
		case "usurersJewel_R2":
			dialog.text = DLG_TEXT_BASE[293];
			link.l1 = DLG_TEXT_BASE[294];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fortune", 25);
			AddMoneyToCharacter(pchar, sti(npchar.quest.usurersJewel.money));
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			sTitle = npchar.city + "UsurersJewel";
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.usurersJewel");
		break;

        //============== Линейка Блада =============== homo
    	
		case "CapBloodUsurer_1":
			dialog.text = DLG_TEXT_BASE[295];
			link.l1 = DLG_TEXT_BASE[296];
			link.l1.go = "CapBloodUsurer_2";
		break;
		
		case "CapBloodUsurer_2":
			dialog.text = DLG_TEXT_BASE[297];
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = DLG_TEXT_BASE[298];
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = DLG_TEXT_BASE[299];
    			link.l1.go = "CapBloodUsurer_4";
            }
		break;
		
		
		case "CapBloodUsurer_3":
            AddMoneyToCharacter(pchar, -5000);
            Pchar.questTemp.CapBloodLine.Ogl = true;
            AddQuestRecord("OglQuest", "2");
			dialog.text = DLG_TEXT_BASE[300];
			link.l1 = DLG_TEXT_BASE[301];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "CapBloodUsurer_4":
			dialog.text = DLG_TEXT_BASE[302];
			if (sti(pchar.money) >= 5000)
			{
    			link.l1 = DLG_TEXT_BASE[303];
    			link.l1.go = "CapBloodUsurer_3";
            }
            else
            {
    			link.l1 = DLG_TEXT_BASE[304];
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_4";
            }
		break;
		
		case "CapBloodUsurer_5":
			dialog.text = DLG_TEXT_BASE[305];
			link.l1 = DLG_TEXT_BASE[306];
			link.l1.go = "CapBloodUsurer_6";
		break;
		
		case "CapBloodUsurer_6":
			dialog.text = DLG_TEXT_BASE[307];
			link.l1 = DLG_TEXT_BASE[308];
			link.l1.go = "CapBloodUsurer_7";
			link.l2 = DLG_TEXT_BASE[309];
			link.l2.go = "Exit";
			NextDiag.TempNode = "First time";
			PChar.questTemp.CapBloodLine.QuestRaff = false;
		break;
		
		case "CapBloodUsurer_7":
		
            AddQuestRecord("UsurerQuest", "1");
            PChar.questTemp.CapBloodLine.QuestRaff = true;
            NextDiag.CurrentNode = "CapBloodUsurer_8";
			DialogExit();
		break;
		
		case "CapBloodUsurer_8":
			dialog.text = DLG_TEXT_BASE[310];
			if (sti(pchar.money) >= 27000)
			{
    			link.l1 = DLG_TEXT_BASE[311];
    			link.l1.go = "exit";
    			AddMoneyToCharacter(pchar, -27000);
                Pchar.quest.QUsurer.over = "yes";
                NextDiag.TempNode = "First time"; // fix многократной отдачи денег
		   		CloseQuestHeader("UsurerQuest");
            }
            else
            {
    			link.l1 = DLG_TEXT_BASE[312];
    			link.l1.go = "Exit";
    			NextDiag.TempNode = "CapBloodUsurer_8";
            }
		break;
	}
}

int findCitizenMan(ref NPChar, bool bCity)
{
    ref ch;
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(npchar.nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{		
		for(n=0; n<MAX_COLONIES; n++)
		{			
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));	
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1; 
		nation = storeArray[cRand(howStore-1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", "citiz_"+(rand(11)+1), "man", "man", 10, sti(colonies[nation].nation), -1, false));
		ch.dialog.filename = "Common_citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true; 
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[TOTAL_CHARACTERS];
    int howStore = 0;
	string sTemp, sCity;

	for(n=2; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
		// магазины
		if (sTemp == "trader")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
        // мэры
		if (sTemp == "Mayor")
		{
            if (NPChar.city == ch.city) continue;
            if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
            if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
            storeArray[howStore] = n;
            howStore++;
		}
        // верфисты
		if (sTemp == "shipyarder")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
	    // церковники
		if (sTemp == "Priest")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}		
		// ростовщики
		if (sTemp == "usurer")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
            if (NPChar.city == ch.city) continue;
            if (ch.location == "none") continue;
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[cRand(howStore-1)];
    }
}
