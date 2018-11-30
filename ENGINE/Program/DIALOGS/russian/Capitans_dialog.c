// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Capitans_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = DLG_TEXT_BASE[0]; break;
            case 1:  fort = DLG_TEXT_BASE[1]; break;
            case 2:  fort = DLG_TEXT_BASE[2]; break;
            case 3:  fort = DLG_TEXT_BASE[3]; break;
            case 4:  fort = DLG_TEXT_BASE[4]; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+DLG_TEXT_BASE[5]+ GetFullName(NPChar) +DLG_TEXT_BASE[6]+NationKingsName(NPChar)+DLG_TEXT_BASE[7];
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+DLG_TEXT_BASE[8]+ GetFullName(NPChar) +DLG_TEXT_BASE[9];
    			}
    			link.l1 = DLG_TEXT_BASE[10] + GetFullName(Pchar) + DLG_TEXT_BASE[11];
    			link.l1.go = "quests";
                link.l2 = DLG_TEXT_BASE[12];
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[13] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[14];
    			link.l1 = DLG_TEXT_BASE[15];
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = DLG_TEXT_BASE[16] + GetAddress_Form(NPChar)+".";
                link.l1 = DLG_TEXT_BASE[17];
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //
                if (CheckAttribute(NPChar, "EncGroupName")) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple(DLG_TEXT_BASE[18],
                                               DLG_TEXT_BASE[19]);
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = DLG_TEXT_BASE[20];
	    			link.l3.go = "price_1";
	    			link.l4 = DLG_TEXT_BASE[21];
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = DLG_TEXT_BASE[22];
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = DLG_TEXT_BASE[23];
			    link.l5.go = "Play_Game";
                link.l9 = DLG_TEXT_BASE[24];
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = DLG_TEXT_BASE[25] + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              DLG_TEXT_BASE[26] + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
                link.l1 = DLG_TEXT_BASE[27];
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = DLG_TEXT_BASE[28];
			link.l1 = DLG_TEXT_BASE[29];
			link.l1.go = "Trade_2";
			link.l2 = DLG_TEXT_BASE[30];
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "Card_Game";
   			link.l2 = DLG_TEXT_BASE[33];
			link.l2.go = "Dice_Game";
			link.l10 = DLG_TEXT_BASE[34];
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = DLG_TEXT_BASE[35];
    			link.l1 = DLG_TEXT_BASE[36];
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[37];
    			link.l1 = DLG_TEXT_BASE[38];
    			link.l1.go = "Cards_begin";
    			link.l2 = DLG_TEXT_BASE[39];
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[40];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[41];
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "Cards_Node_100";
			link.l2 = DLG_TEXT_BASE[44];
			link.l2.go = "Cards_Node_500";
			link.l3 = DLG_TEXT_BASE[45];
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[46];
                link.l1 = DLG_TEXT_BASE[47];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[48];
                link.l1 = DLG_TEXT_BASE[49];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[52];
                link.l1 = DLG_TEXT_BASE[53];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[54];
                link.l1 = DLG_TEXT_BASE[55];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[56];
			link.l1 = DLG_TEXT_BASE[57];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = DLG_TEXT_BASE[58];
    			link.l1 = DLG_TEXT_BASE[59];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[60];
	    			link.l1 = DLG_TEXT_BASE[61];
	    			link.l1.go = "Dice_begin";
	    			link.l2 = DLG_TEXT_BASE[62];
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[63];
	    			link.l1 = DLG_TEXT_BASE[64];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[66];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "Dice_Node_100";
			link.l2 = DLG_TEXT_BASE[69];
			link.l2.go = "Dice_Node_500";
			link.l3 = DLG_TEXT_BASE[70];
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[71];
                link.l1 = DLG_TEXT_BASE[72];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[73];
                link.l1 = DLG_TEXT_BASE[74];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[75];
                link.l1 = DLG_TEXT_BASE[76];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[77];
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[79];
                link.l1 = DLG_TEXT_BASE[80];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[81];
                link.l1 = DLG_TEXT_BASE[82];
			    link.l1.go = "Dice_Node_100";
				link.l2 = DLG_TEXT_BASE[83];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[84];
                link.l1 = DLG_TEXT_BASE[85];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[86];
                link.l1 = DLG_TEXT_BASE[87];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = DLG_TEXT_BASE[90];
					Link.l1 = DLG_TEXT_BASE[91];
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = DLG_TEXT_BASE[92] + GetCityName(sld.City) + ".";
					Link.l1 = DLG_TEXT_BASE[93];
					Link.l1.go = "price_2";
					Link.l9 = DLG_TEXT_BASE[94];
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = DLG_TEXT_BASE[95];
				Link.l1 = DLG_TEXT_BASE[96];
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = DLG_TEXT_BASE[97];
			Link.l1 = DLG_TEXT_BASE[98];
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = DLG_TEXT_BASE[99];
                link.l1 = DLG_TEXT_BASE[100];
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = DLG_TEXT_BASE[101];
                    link.l1 = DLG_TEXT_BASE[102];
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
                    Dialog.text = RandSwear() + DLG_TEXT_BASE[103] +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + DLG_TEXT_BASE[104];
                    link.l1 = DLG_TEXT_BASE[105]+Pchar.GenQuest.MoneyForCaptureShip+DLG_TEXT_BASE[106]+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = DLG_TEXT_BASE[107];
                    link.l2.go = "exit";
                }
            }
            // тут нужен учет запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;

        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_BASE[108],
                                     DLG_TEXT_BASE[109]);
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple(DLG_TEXT_BASE[110],
                                     DLG_TEXT_BASE[111]);
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = DLG_TEXT_BASE[112];
			Link.l1 = DLG_TEXT_BASE[113];
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = DLG_TEXT_BASE[114]+GetAddress_Form(NPChar)+".";
			Link.l1 = DLG_TEXT_BASE[115];
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = DLG_TEXT_BASE[116];
			Link.l1 = DLG_TEXT_BASE[117];
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterReputation(pchar, -5);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = DLG_TEXT_BASE[118];
			Link.l1 = DLG_TEXT_BASE[119];
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = DLG_TEXT_BASE[120];
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = DLG_TEXT_BASE[121];  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = DLG_TEXT_BASE[122];
			Link.l1 = DLG_TEXT_BASE[123];
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = DLG_TEXT_BASE[124];
			Link.l1 = DLG_TEXT_BASE[125];
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = DLG_TEXT_BASE[126];
			Link.l1 = DLG_TEXT_BASE[127];
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = DLG_TEXT_BASE[128];
			Link.l1 = DLG_TEXT_BASE[129];
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = DLG_TEXT_BASE[130];
			Link.l1 = DLG_TEXT_BASE[131];
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = DLG_TEXT_BASE[132]+NationKingsName(NPChar)+DLG_TEXT_BASE[133]+NationNameSK(sti(NPChar.nation))+DLG_TEXT_BASE[134];
			Link.l1 = DLG_TEXT_BASE[135];
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":
		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			
    			dialog.text = DLG_TEXT_BASE[136] + fort +
                          DLG_TEXT_BASE[137];
                link.l1 = DLG_TEXT_BASE[138] + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = DLG_TEXT_BASE[139]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[140] + GetFullName(rchar)+
                              DLG_TEXT_BASE[141] + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.";
                link.l1 = DLG_TEXT_BASE[142];
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = DLG_TEXT_BASE[143];
                link.l1 = DLG_TEXT_BASE[144] +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ DLG_TEXT_BASE[145];
                link.l1.go = "Siegehelp_1";
                link.l2 = DLG_TEXT_BASE[146]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = DLG_TEXT_BASE[147];
            link.l1 = DLG_TEXT_BASE[148];
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
            if (sti(aData.win)==0)
            {
                dialog.text = DLG_TEXT_BASE[149];
                link.l1 = DLG_TEXT_BASE[150];
                link.l1.go = "Big_part";
                link.l2 = DLG_TEXT_BASE[151];
                link.l2.go = "Middle_part";
                link.l3 = DLG_TEXT_BASE[152];
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[153];
                link.l1 = DLG_TEXT_BASE[154] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[155];
                link.l1.go = "attack_fort_03";
                link.l2 = DLG_TEXT_BASE[156] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[157];
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":


            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = DLG_TEXT_BASE[158] + GetPart(4) + DLG_TEXT_BASE[159];
                link.l1 = DLG_TEXT_BASE[160] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[161];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = DLG_TEXT_BASE[162] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[163];
                link.l2.go = "exit";
            }else{
                dialog.text = DLG_TEXT_BASE[164];
                link.l1 = DLG_TEXT_BASE[165] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[166];
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = DLG_TEXT_BASE[167];
                link.l1 = DLG_TEXT_BASE[168] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[169];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[170] + GetNumShips(GetCompanionQuantity(PChar)) +
                              DLG_TEXT_BASE[171] + GetNumShips(Group_GetCharactersNum(sGroup)) + DLG_TEXT_BASE[172] + GetPart(4) +
                              DLG_TEXT_BASE[173];
                aData.PartAttaksFort = 4;
                link.l1 = DLG_TEXT_BASE[174] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[175];
                link.l1.go = "attack_fort_04";
                link.l2 = DLG_TEXT_BASE[176] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[177];
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = DLG_TEXT_BASE[178];
            link.l1 = DLG_TEXT_BASE[179] + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = DLG_TEXT_BASE[180];
                link.l1 = DLG_TEXT_BASE[181] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[182];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
                dialog.text = DLG_TEXT_BASE[183] + GetNumShips(GetCompanionQuantity(PChar)) + DLG_TEXT_BASE[184] + GetNumShips(Group_GetCharactersNum(sGroup)) + DLG_TEXT_BASE[185] + GetPart(4) + DLG_TEXT_BASE[186];
                link.l1 = DLG_TEXT_BASE[187] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[188];
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = DLG_TEXT_BASE[189] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[190];
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = DLG_TEXT_BASE[191];
            link.l1 = DLG_TEXT_BASE[192] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[193];
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = DLG_TEXT_BASE[194] + sti(aData.loot)+
                          DLG_TEXT_BASE[195]+ilt+
                          DLG_TEXT_BASE[196];
            link.l1 = DLG_TEXT_BASE[197] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[198];
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterReputation(PChar, 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour(DLG_TEXT_BASE[199]+NationNameSK(sti(aData.conation))+DLG_TEXT_BASE[200]+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+DLG_TEXT_BASE[201]+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = DLG_TEXT_BASE[202];
            link.l1 = DLG_TEXT_BASE[203] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[204];
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = DLG_TEXT_BASE[205];
                          
                link.l1 = DLG_TEXT_BASE[206]+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = DLG_TEXT_BASE[207] + GetFullName(rch)+
                              DLG_TEXT_BASE[208] + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.";
                link.l1 = DLG_TEXT_BASE[209];
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = DLG_TEXT_BASE[210]; break;
       case 1: numships = DLG_TEXT_BASE[211];      break;
       case 2: numships = DLG_TEXT_BASE[212];       break;
       case 3: numships = DLG_TEXT_BASE[213];       break;
       case 4: numships = DLG_TEXT_BASE[214];    break;
       case 5: numships = DLG_TEXT_BASE[215];     break;
       case 6: numships = DLG_TEXT_BASE[216];    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = DLG_TEXT_BASE[217]; break;
       case 2: numpart = DLG_TEXT_BASE[218]; break;
       case 3: numpart = DLG_TEXT_BASE[219]; break;
       case 4: numpart = DLG_TEXT_BASE[220];      break;

    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
