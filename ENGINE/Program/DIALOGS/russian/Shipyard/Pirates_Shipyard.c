#include "TEXT\DIALOGS\Shipyard\Pirates_Shipyard.h"
// It's tuning master
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    if ( sti(Pchar.Ship.Type) != SHIP_NOTUSED)
    {
	    int   cannonQ       = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity);
		int   cannonMax     = sti(RealShips[sti(Pchar.Ship.Type)].MaxCaliber);
		int   shipClass     = sti(RealShips[sti(Pchar.Ship.Type)].Class);
		//int   shipPrice     = sti(RealShips[sti(Pchar.Ship.Type)].Price);
		int   shipCapacity  = sti(RealShips[sti(Pchar.Ship.Type)].Capacity);
		float shipSpeedRate = stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);
		int   shipMaxCrew   = sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew);
		int   shipHP        = sti(RealShips[sti(Pchar.Ship.Type)].HP);
		float shipTurnRate  = stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);
		
	    int  cannonMatherial1 = makeint(cannonQ * (cannonMax/shipClass));
	    int	 cannonMatherial2 = makeint(cannonQ * (30/shipClass));
	    int  cannonWorkPrice  = makeint(30*(10-shipClass)/(0.5*shipClass) * cannonQ * cannonMax);
	    //int  cannonWorkPrice  = makeint(shipPrice * cannonQ * cannonMax / 2000);
	    
	    int  сapacityMatherial1 = makeint(shipCapacity /(shipClass*2));
	    int	 сapacityMatherial2 = makeint(cannonQ *10 /shipClass);
	    int  сapacityWorkPrice  = makeint(shipCapacity/5 * 200);
	    
	    int  SpeedRateMatherial1 = makeint(shipSpeedRate*18 / shipClass);
	    int	 SpeedRateMatherial2 = makeint(shipSpeedRate*24 / shipClass);
	    int  SpeedRateWorkPrice  = makeint(shipSpeedRate/5 * 10000*6/shipClass);
	    
	    int  MaxCrewMatherial1 = makeint(shipMaxCrew*10 / shipClass);
	    int	 MaxCrewMatherial2 = makeint(shipMaxCrew*12 / shipClass);
	    int  MaxCrewWorkPrice  = makeint(shipMaxCrew/5 * 500*6/shipClass);
	    
	    int  TurnRateMatherial1 = makeint(shipTurnRate*8 / shipClass);
	    int	 TurnRateMatherial2 = makeint(shipTurnRate*10 / shipClass);
	    int  TurnRateWorkPrice  = makeint(shipTurnRate/5 * 3350*6/shipClass);
	    
	    int  HPMatherial1 = makeint(shipHP / (5*shipClass));
	    int	 HPMatherial2 = makeint(shipHP / (7*shipClass));
	    int  HPWorkPrice  = makeint(shipHP/5 * 70*6/shipClass);
	
	}
	int amount;
	ref shTo;
    string sTemp;
    string s1;
    
	switch (Dialog.CurrentNode)
	{
		
		// -----------------------------------ƒиалог первый - перва€ встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = DLG_TEXT_SHY[0] + GetFullName(npchar) + DLG_TEXT_SHY[1];
				Link.l1 = pcharrepphrase(DLG_TEXT_SHY[2] + GetFullName(pchar) + DLG_TEXT_SHY[3],
	            DLG_TEXT_SHY[4] + GetFullName(pchar) + DLG_TEXT_SHY[5]);
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = DLG_TEXT_SHY[6];
				link.l1 = pcharrepphrase(DLG_TEXT_SHY[7],
	            DLG_TEXT_SHY[8]);
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase(DLG_TEXT_SHY[9],
	            DLG_TEXT_SHY[10]);
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
			dialog.text = DLG_TEXT_SHY[11];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[12],
            DLG_TEXT_SHY[13]);
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(DLG_TEXT_SHY[14],
            DLG_TEXT_SHY[15]);
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = DLG_TEXT_SHY[16];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[17],
            DLG_TEXT_SHY[18]);
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[20],
            DLG_TEXT_SHY[21]);
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(DLG_TEXT_SHY[22],
            DLG_TEXT_SHY[23]);
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = DLG_TEXT_SHY[24] + GetAddress_Form(NPChar) + "?";
			link.l1 = pcharrepphrase(DLG_TEXT_SHY[25],DLG_TEXT_SHY[26]);
			link.l1.go = "shipyard_dlg";
            Link.l2 = DLG_TEXT_SHY[27];
			Link.l2.go = "quests"; //(перессылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = DLG_TEXT_SHY[28];
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase(DLG_TEXT_SHY[29], DLG_TEXT_SHY[30]);
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":
			dialog.Text = DLG_TEXT_SHY[31];
			Link.l1 = DLG_TEXT_SHY[32];
			Link.l1.go = "ship_tunning_start";
			link.l2 = DLG_TEXT_SHY[33];
			link.l2.go = "shipyard";
			link.l3 = DLG_TEXT_SHY[34];
			link.l3.go = "Cannons";
			Link.l9 = DLG_TEXT_SHY[35];
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_again":
			dialog.Text = RandPhraseSimple(DLG_TEXT_SHY[36],
                                           RandPhraseSimple(DLG_TEXT_SHY[37],
                                           DLG_TEXT_SHY[38]));
			Link.l1 = DLG_TEXT_SHY[39];
			Link.l1.go = "ship_tunning_start";
			link.l2 = DLG_TEXT_SHY[40];
			link.l2.go = "shipyard";
			link.l3 = DLG_TEXT_SHY[41];
			link.l3.go = "Cannons";
            Link.l4 = DLG_TEXT_SHY[42];
			Link.l4.go = "quests"; //(перессылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = DLG_TEXT_SHY[43];
				link.l5.go = "LoanForAll";//(перессылка в файл города)
			}
			Link.l9 = DLG_TEXT_SHY[44];
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
        case "ship_tunning_not_now_2":
			dialog.Text = DLG_TEXT_SHY[45];
			Link.l1 = RandPhraseSimple(DLG_TEXT_SHY[46], DLG_TEXT_SHY[47]);
			Link.l1.go = "ship_tunning_not_now";
		break;
        		
        case "ship_tunning_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = DLG_TEXT_SHY[48];
			    Link.l1 = DLG_TEXT_SHY[49];
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
                    dialog.Text = DLG_TEXT_SHY[50];
			        Link.l1 = DLG_TEXT_SHY[51];
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if (shipClass == 7)
                    {
                        dialog.Text = DLG_TEXT_SHY[52];
    			        Link.l1 = DLG_TEXT_SHY[53];
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }

                    s1 = DLG_TEXT_SHY[54] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + DLG_TEXT_SHY[55];
    			    }
    			    s1 = s1 + DLG_TEXT_SHY[56];
                    dialog.Text = s1;
                    if (cannonMax < 32 && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
                    {
                        Link.l1 = DLG_TEXT_SHY[57];
    			        Link.l1.go = "ship_tunning_cannon";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
                    {
    			        Link.l2 = DLG_TEXT_SHY[58];
    			        Link.l2.go = "ship_tunning_Capacity";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
                    {
    			        Link.l3 = DLG_TEXT_SHY[59];
    			        Link.l3.go = "ship_tunning_SpeedRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
                    {
    			        Link.l4 = DLG_TEXT_SHY[60];
    			        Link.l4.go = "ship_tunning_TurnRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
                    {
    			        Link.l5 = DLG_TEXT_SHY[61];
    			        Link.l5.go = "ship_tunning_MaxCrew";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
                    {
    			        Link.l6 = DLG_TEXT_SHY[62];
    			        Link.l6.go = "ship_tunning_HP";
    			    }
    			    Link.l10 = DLG_TEXT_SHY[63];
    			    Link.l10.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_tunning_cannon":
			s1 = DLG_TEXT_SHY[64] + cannonQ + DLG_TEXT_SHY[65] + cannonMax + DLG_TEXT_SHY[66];
			
			s1 = s1 + DLG_TEXT_SHY[67]+ cannonMatherial1 + DLG_TEXT_SHY[68]+ cannonMatherial2+DLG_TEXT_SHY[69];
			s1 = s1 + DLG_TEXT_SHY[70] + cannonWorkPrice + DLG_TEXT_SHY[71];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[72];
			Link.l1.go = "ship_tunning_cannon_start";
			Link.l2 = DLG_TEXT_SHY[73];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_cannon_start":
		    amount = cannonWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
				NPChar.Tuning.Cannon = true;
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = cannonMatherial1; // черное дерево
			    NPChar.Tuning.Matherial2 = cannonMatherial2; // кожа
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    
				NextDiag.TempNode = "ship_tunning_cannon_again";
                dialog.text = DLG_TEXT_SHY[74];
			    link.l1 = DLG_TEXT_SHY[75];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_SHY[76] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[77]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[78]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[79] + NPChar.Tuning.Money + DLG_TEXT_SHY[80]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[81];
				link.l1 = DLG_TEXT_SHY[82];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_cannon_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_cannon_again";
			    dialog.Text = DLG_TEXT_SHY[83] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[84] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[85] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[86];
			    Link.l1 = DLG_TEXT_SHY[87];
			    Link.l1.go = "ship_tunning_cannon_again_2";
			    Link.l2 = DLG_TEXT_SHY[88];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[89];
			    Link.l1 = DLG_TEXT_SHY[90];
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_cannon_again_2":
		    amount = makeint(Pchar.money) - sti(NPChar.Tuning.Money);
		    if (amount < 0)
		    {
		       amount = amount + sti(NPChar.Tuning.Money);
		    }
		    else
		    {
		        amount = sti(NPChar.Tuning.Money);
		    }
		    AddMoneyToCharacter(Pchar, -amount);
		    NPChar.Tuning.Money = makeint(sti(NPChar.Tuning.Money) - amount);
		    
		    amount = GetSquadronGoods(Pchar, GOOD_EBONY) - sti(NPChar.Tuning.Matherial1);
		    if (amount < 0)
		    {
		       amount = amount + sti(NPChar.Tuning.Matherial1);
		    }
		    else
		    {
		        amount = sti(NPChar.Tuning.Matherial1);
		    }
		    RemoveCharacterGoods(Pchar, GOOD_EBONY, amount);
		    NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;
		    
		    amount = GetSquadronGoods(Pchar, GOOD_LEATHER) - sti(NPChar.Tuning.Matherial2);
		    if (amount < 0)
		    {
		       amount = amount + sti(NPChar.Tuning.Matherial2);
		    }
		    else
		    {
		        amount = sti(NPChar.Tuning.Matherial2);
		    }
		    RemoveCharacterGoods(Pchar, GOOD_LEATHER, amount);
		    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[91];
			    link.l1 = DLG_TEXT_SHY[92];
			    link.l1.go = "ship_tunning_cannon_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_cannon_again";
                dialog.Text = DLG_TEXT_SHY[93] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[94] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[95] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[96];
				link.l1 = DLG_TEXT_SHY[97];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_SHY[98] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[99]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[100]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[101]);
			}
		break;
		
		case "ship_tunning_cannon_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	    int iCaliber = sti(shTo.MaxCaliber);
        switch(iCaliber)
	    {
		case 12:
			iCaliber = 0;
		break;
		case 16:
			iCaliber = 1;
		break;
		case 24:
			iCaliber = 2;
		break;
		case 32:
			iCaliber = 3;
		break;
	    }
	    iCaliber = iCaliber + 1;
	    if (iCaliber > 3) iCaliber = 3;
	    switch(iCaliber)
	    {
		case 0:
			iCaliber = 12;
		break;
		case 1:
			iCaliber = 16;
		break;
		case 2:
			iCaliber = 24;
		break;
		case 3:
			iCaliber = 32;
		break;
	    }
	    shTo.MaxCaliber = iCaliber;
	    shTo.Tuning.Cannon = true;
	    // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[102];
			Link.l1 = DLG_TEXT_SHY[103];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// трюм ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			s1 = DLG_TEXT_SHY[104] + shipCapacity;
			
			s1 = s1 + DLG_TEXT_SHY[105]+ сapacityMatherial1 + DLG_TEXT_SHY[106]+ сapacityMatherial2+DLG_TEXT_SHY[107];
			s1 = s1 + DLG_TEXT_SHY[108] + сapacityWorkPrice + DLG_TEXT_SHY[109];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[110];
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = DLG_TEXT_SHY[111];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = сapacityWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = сapacityMatherial1; // красное дерево GOOD_MAHOGANY
			    NPChar.Tuning.Matherial2 = сapacityMatherial2; //  GOOD_OIL
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = DLG_TEXT_SHY[112];
			    link.l1 = DLG_TEXT_SHY[113];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_SHY[114] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[115]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[116]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[117] + NPChar.Tuning.Money + DLG_TEXT_SHY[118]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[119];
				link.l1 = DLG_TEXT_SHY[120];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
			    dialog.Text = DLG_TEXT_SHY[121] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[122] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[123] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[124];
			    Link.l1 = DLG_TEXT_SHY[125];
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = DLG_TEXT_SHY[126];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[127];
			    Link.l1 = DLG_TEXT_SHY[128];
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_MAHOGANY, GOOD_OIL);
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[129];
			    link.l1 = DLG_TEXT_SHY[130];
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.Text = DLG_TEXT_SHY[131] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[132] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[133] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[134];
				link.l1 = DLG_TEXT_SHY[135];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_SHY[136] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[137]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[138]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[139]);
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
	        shTo.Tuning.Capacity = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[140];
			Link.l1 = DLG_TEXT_SHY[141];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			s1 = DLG_TEXT_SHY[142] + shipSpeedRate;
			
			s1 = s1 + DLG_TEXT_SHY[143]+ SpeedRateMatherial1 + DLG_TEXT_SHY[144]+ SpeedRateMatherial2+DLG_TEXT_SHY[145];
			s1 = s1 + DLG_TEXT_SHY[146] + SpeedRateWorkPrice + DLG_TEXT_SHY[147];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[148];
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = DLG_TEXT_SHY[149];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_SpeedRate_start":
		    amount = SpeedRateWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = SpeedRateMatherial1; // GOOD_SAILCLOTH
			    NPChar.Tuning.Matherial2 = SpeedRateMatherial2; //  GOOD_SILK
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = DLG_TEXT_SHY[150];
			    link.l1 = DLG_TEXT_SHY[151];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", DLG_TEXT_SHY[152] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[153]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[154]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[155] + NPChar.Tuning.Money + DLG_TEXT_SHY[156]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[157];
				link.l1 = DLG_TEXT_SHY[158];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
			    dialog.Text = DLG_TEXT_SHY[159] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[160] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[161] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[162];
			    Link.l1 = DLG_TEXT_SHY[163];
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = DLG_TEXT_SHY[164];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[165];
			    Link.l1 = DLG_TEXT_SHY[166];
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SAILCLOTH, GOOD_SILK);
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[167];
			    link.l1 = DLG_TEXT_SHY[168];
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.Text = DLG_TEXT_SHY[169] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[170] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[171] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[172];
				link.l1 = DLG_TEXT_SHY[173];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[174] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[175]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[176]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[177]);
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
	        shTo.Tuning.SpeedRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[178];
			Link.l1 = DLG_TEXT_SHY[179];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			s1 = DLG_TEXT_SHY[180] + shipMaxCrew + DLG_TEXT_SHY[181];
			
			s1 = s1 + DLG_TEXT_SHY[182]+ MaxCrewMatherial1 + DLG_TEXT_SHY[183]+ MaxCrewMatherial2+DLG_TEXT_SHY[184];
			s1 = s1 + DLG_TEXT_SHY[185] + MaxCrewWorkPrice + DLG_TEXT_SHY[186];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[187];
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = DLG_TEXT_SHY[188];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_MaxCrew_start":
		    amount = MaxCrewWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = MaxCrewMatherial1; // GOOD_FRUITS
			    NPChar.Tuning.Matherial2 = MaxCrewMatherial2; //  GOOD_CLOTHES
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = DLG_TEXT_SHY[189];
			    link.l1 = DLG_TEXT_SHY[190];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[191] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[192]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[193]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[194] + NPChar.Tuning.Money + DLG_TEXT_SHY[195]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[196];
				link.l1 = DLG_TEXT_SHY[197];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
			    dialog.Text = DLG_TEXT_SHY[198] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[199] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[200] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[201];
			    Link.l1 = DLG_TEXT_SHY[202];
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = DLG_TEXT_SHY[203];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[204];
			    Link.l1 = DLG_TEXT_SHY[205];
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_FRUITS, GOOD_CLOTHES);
		    
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[206];
			    link.l1 = DLG_TEXT_SHY[207];
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.Text = DLG_TEXT_SHY[208] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[209] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[210] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[211];
				link.l1 = DLG_TEXT_SHY[212];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[213] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[214]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[215]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[216]);
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[217];
			Link.l1 = DLG_TEXT_SHY[218];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			s1 = DLG_TEXT_SHY[219] + shipTurnRate;
			
			s1 = s1 + DLG_TEXT_SHY[220]+ TurnRateMatherial1 + DLG_TEXT_SHY[221]+ TurnRateMatherial2+DLG_TEXT_SHY[222];
			s1 = s1 + DLG_TEXT_SHY[223] + TurnRateWorkPrice + DLG_TEXT_SHY[224];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[225];
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = DLG_TEXT_SHY[226];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_TurnRate_start":
		    amount = TurnRateWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = TurnRateMatherial1; // GOOD_PLANKS
			    NPChar.Tuning.Matherial2 = TurnRateMatherial2; //  GOOD_LINEN
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = DLG_TEXT_SHY[227];
			    link.l1 = DLG_TEXT_SHY[228];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[229] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[230]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[231]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[232] + NPChar.Tuning.Money + DLG_TEXT_SHY[233]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[234];
				link.l1 = DLG_TEXT_SHY[235];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
			    dialog.Text = DLG_TEXT_SHY[236] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[237] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[238] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[239];
			    Link.l1 = DLG_TEXT_SHY[240];
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = DLG_TEXT_SHY[241];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[242];
			    Link.l1 = DLG_TEXT_SHY[243];
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_PLANKS, GOOD_LINEN);
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[244];
			    link.l1 = DLG_TEXT_SHY[245];
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.Text = DLG_TEXT_SHY[246] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[247] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[248] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[249];
				link.l1 = DLG_TEXT_SHY[250];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[251] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[252]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[253]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[254]);
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
	        shTo.Tuning.TurnRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[255];
			Link.l1 = DLG_TEXT_SHY[256];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			s1 = DLG_TEXT_SHY[257] + shipHP;
			
			s1 = s1 + DLG_TEXT_SHY[258]+ HPMatherial1 + DLG_TEXT_SHY[259]+ HPMatherial2+DLG_TEXT_SHY[260];
			s1 = s1 + DLG_TEXT_SHY[261] + HPWorkPrice + DLG_TEXT_SHY[262];
            dialog.Text = s1;
			Link.l1 = DLG_TEXT_SHY[263];
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = DLG_TEXT_SHY[264];
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_tunning_HP_start":
		    amount = HPWorkPrice;
		    if(makeint(Pchar.money) >= makeint(amount / 2 +0.5))
			{
				AddMoneyToCharacter(Pchar, -makeint(amount / 2 +0.5));
			    NPChar.Tuning.Money  = makeint(amount - makeint(amount / 2 +0.5));
			    NPChar.Tuning.Matherial1 = HPMatherial1; // GOOD_EBONY
			    NPChar.Tuning.Matherial2 = HPMatherial2; //  GOOD_SANDAL
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = DLG_TEXT_SHY[265];
			    link.l1 = DLG_TEXT_SHY[266];
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[267] + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
                DLG_TEXT_SHY[268]+NPChar.Tuning.Matherial1+ DLG_TEXT_SHY[269]+ NPChar.Tuning.Matherial2+DLG_TEXT_SHY[270] + NPChar.Tuning.Money + DLG_TEXT_SHY[271]);
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = DLG_TEXT_SHY[272];
				link.l1 = DLG_TEXT_SHY[273];
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
			    dialog.Text = DLG_TEXT_SHY[274] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[275] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[276] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[277];
			    Link.l1 = DLG_TEXT_SHY[278];
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = DLG_TEXT_SHY[279];
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = DLG_TEXT_SHY[280];
			    Link.l1 = DLG_TEXT_SHY[281];
			    Link.l1.go = "Exit";
			    
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_EBONY, GOOD_SANDAL);
		
		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Money) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = DLG_TEXT_SHY[282];
			    link.l1 = DLG_TEXT_SHY[283];
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.Text = DLG_TEXT_SHY[284] + sti(NPChar.Tuning.Matherial1) + DLG_TEXT_SHY[285] + sti(NPChar.Tuning.Matherial2) + DLG_TEXT_SHY[286] + sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[287];
				link.l1 = DLG_TEXT_SHY[288];
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  DLG_TEXT_SHY[289] +  sti(NPChar.Tuning.Matherial1)+ DLG_TEXT_SHY[290]+ sti(NPChar.Tuning.Matherial2)+DLG_TEXT_SHY[291]+ sti(NPChar.Tuning.Money) + DLG_TEXT_SHY[292]);
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
	        shTo.Tuning.HP = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = DLG_TEXT_SHY[293];
			Link.l1 = DLG_TEXT_SHY[294];
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[295], DLG_TEXT_SHY[296]), DLG_TEXT_SHY[297], DLG_TEXT_SHY[298],
                          DLG_TEXT_SHY[299], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[300], DLG_TEXT_SHY[301]), DLG_TEXT_SHY[302],
                      DLG_TEXT_SHY[303], DLG_TEXT_SHY[304], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = DLG_TEXT_SHY[305];
				link.l2.go = "Step_Door_1";
			}
        // ==> ѕерехват на квесты
			if (pchar.questTemp.BlueBird == "toSeekBermudes") //шебека —ин€€ ѕтица
			{
				link.l1 = DLG_TEXT_SHY[306];
				link.l1.go = "BlueBird_1";
			}
            if (CheckAttribute(pchar, "questTemp.State.SeekBible"))// квест є2, поиск ≈вангелие
            {
                if (!CheckCharacterItem(pchar, "Bible"))
                {
                    dialog.text = DLG_TEXT_SHY[307];
        			link.l2 = DLG_TEXT_SHY[308];
        			link.l2.go = "Step_S2_1";
                }
                else
                {
                    dialog.text = DLG_TEXT_SHY[309];
        			link.l2 = DLG_TEXT_SHY[310];
        			link.l2.go = "exit";
                }
            }
			if (pchar.questTemp.piratesLine == "KillLoy_toAlexus")
			{
				link.l1 = DLG_TEXT_SHY[311];
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_GoodWork")
			{
				link.l1 = DLG_TEXT_SHY[312];
				link.l1.go = "PL_Q3_SW1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_LoyIsDied")
			{
				link.l1 = DLG_TEXT_SHY[313];
				link.l1.go = "PL_Q3_SW2";
			}
        // <== ѕерехват на квесты
		break;
//*************************** ѕиратка, квест є3, поиски Ћоу ***************************
		case "PL_Q3_1":
			dialog.text = DLG_TEXT_SHY[314];
			link.l1 = DLG_TEXT_SHY[315];
			link.l1.go = "PL_Q3_3";
			link.l2 = DLG_TEXT_SHY[316];
			link.l2.go = "PL_Q3_2";
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_SHY[317];
			link.l1 = DLG_TEXT_SHY[318];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "10");
			pchar.questTemp.piratesLine = "KillLoy_toJackman";
		break;
		case "PL_Q3_3":
			dialog.text = DLG_TEXT_SHY[319];
			link.l1 = DLG_TEXT_SHY[320];
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = DLG_TEXT_SHY[321];
			link.l1 = DLG_TEXT_SHY[322];
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = DLG_TEXT_SHY[323];
			link.l1 = DLG_TEXT_SHY[324];
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = DLG_TEXT_SHY[325];
			link.l1 = DLG_TEXT_SHY[326];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "11");
			pchar.questTemp.piratesLine = "KillLoy_toTavernAgain";
			//садим капитана √удли в таверну
			sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "officer_9", "man", "man", 20, PIRATE, -1, true));
			sld.name = DLG_TEXT_SHY[327];
			sld.lastname = DLG_TEXT_SHY[328];
			sld.rank = 20;
			sld.city = "Pirates";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "CapGoodly";
			sld.greeting = "Gr_EvilPirate";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
            FreeSitLocator("Pirates_tavern", "sit2");
         	ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit2");
		break;

		case "PL_Q3_SW1":
			dialog.text = DLG_TEXT_SHY[329];
			link.l1 = DLG_TEXT_SHY[330];
			link.l1.go = "exit";
		break;
		case "PL_Q3_SW2":
			dialog.text = DLG_TEXT_SHY[331];
			link.l1 = DLG_TEXT_SHY[332];
			link.l1.go = "PL_Q3_SW3";
		break;
		case "PL_Q3_SW3":
			dialog.text = DLG_TEXT_SHY[333];
			link.l1 = DLG_TEXT_SHY[334];
			link.l1.go = "exit";
		break;
//*************************** шебека —ин€€ ѕтица ***************************
		case "BlueBird_1":
			dialog.text = DLG_TEXT_SHY[335];
			link.l1 = DLG_TEXT_SHY[336];
			link.l1.go = "BlueBird_2";
		break;
		case "BlueBird_2":
			dialog.text = DLG_TEXT_SHY[337];
			link.l1 = DLG_TEXT_SHY[338];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_SHY[339];
			link.l1 = DLG_TEXT_SHY[340];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_SHY[341];
			link.l1 = DLG_TEXT_SHY[342];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "5");
			pchar.questTemp.BlueBird = "toCavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1 = "locator";
			pchar.quest.BlueBird_inCavern.win_condition.l1.location = "Bermudes_Cavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator_group = "quest";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator = "BlueBird";
			pchar.quest.BlueBird_inCavern.function = "BlueBird_inCavern";
			LAi_LocationDisableMonstersGen("Bermudes_Cavern", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Bermudes_Cavern", true); //офицеров не пускать
		break;	
//*************************** ќткрывание двери ***************************
 		case "Step_Door_1":
			dialog.text = DLG_TEXT_SHY[343];
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = DLG_TEXT_SHY[344];
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = DLG_TEXT_SHY[345];
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = DLG_TEXT_SHY[346];
    		link.l2.go = "exit";
		break;
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = DLG_TEXT_SHY[347];
			link.l1 = DLG_TEXT_SHY[348] + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
 		case "Step_Door_3":
			dialog.text = DLG_TEXT_SHY[349];
			link.l1 = DLG_TEXT_SHY[350];
			link.l1.go = "exit";
		break;
//***************************  вест є2, диалоги с ‘ранциско на выходе из »нквизиии ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_SHY[351], DLG_TEXT_SHY[352], DLG_TEXT_SHY[353], DLG_TEXT_SHY[354], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_SHY[355], DLG_TEXT_SHY[356], DLG_TEXT_SHY[357], DLG_TEXT_SHY[358], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = DLG_TEXT_SHY[359];
			link.l1 = DLG_TEXT_SHY[360];
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = DLG_TEXT_SHY[361];
			link.l1 = DLG_TEXT_SHY[362];
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = DLG_TEXT_SHY[363];
			link.l1 = DLG_TEXT_SHY[364];
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = DLG_TEXT_SHY[365]+
                          DLG_TEXT_SHY[366];
			link.l1 = DLG_TEXT_SHY[367];
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = DLG_TEXT_SHY[368];
			link.l1 = DLG_TEXT_SHY[369];
			link.l1.go = "exit";
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            LocatorReloadEnterDisable("Shore3", "reload2_back", false);
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1.location = "Bermudes_Dungeon";
            Pchar.quest.Inquisition_fightInDangeon.win_condition = "Inquisition_fightInDangeon";
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry5 = 200;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade33 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade28 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade34 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade32 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade23 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry7 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potionwine = 3;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry2 = 20;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian11 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian15 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian12 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.Bible = 1;
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial(ref Pchar, ref NPChar, int good1, int good2)
{
    int amount;
    amount = makeint(Pchar.money) - sti(NPChar.Tuning.Money);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Money);
    }
    else
    {
        amount = sti(NPChar.Tuning.Money);
    }
    AddMoneyToCharacter(Pchar, -amount);
    NPChar.Tuning.Money = makeint(sti(NPChar.Tuning.Money) - amount);

    amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial1);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial1);
    }
    RemoveCharacterGoods(Pchar, good1, amount);
    NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

    amount = GetSquadronGoods(Pchar, good2) - sti(NPChar.Tuning.Matherial2);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial2);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial2);
    }
    RemoveCharacterGoods(Pchar, good2, amount);
    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;
}
