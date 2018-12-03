#include "DIALOGS\russian\Common_Duel.c" //navy
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Habitue_dialog.h"
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2;
	int DonationSize;
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	// boal 13.03.2004 -->
	int d1,d2,d3,d4;
	bool ok;
	// boal 13.03.2004 <--
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.last_theme = makeint(rand(1));
		npchar.quest.last_theme_game = makeint(rand(1));
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = DLG_TEXT_BASE[0];
			link.l1 = DLG_TEXT_BASE[1];
			link.l1.go = "Beta_test_alc";
            link.l2 = DLG_TEXT_BASE[2];
			link.l2.go = "Beta_test_card";
			link.l3 = DLG_TEXT_BASE[3];
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = DLG_TEXT_BASE[4];
			link.l1 = DLG_TEXT_BASE[5];
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = DLG_TEXT_BASE[6];
			link.l1 = DLG_TEXT_BASE[7];
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = DLG_TEXT_BASE[8];
			link.l1 = DLG_TEXT_BASE[9];
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11] , DLG_TEXT_BASE[12]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14]); 
				link.l1.go = "exit";
				break;
			}
            ok = CheckFreeSitFront(npchar); //checkAttribute(npchar, "Default.ToLocator"); // есть куда сесть
            
            dialog.text = DLG_TEXT_BASE[15];
            link.l1 = DLG_TEXT_BASE[16];
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = DLG_TEXT_BASE[17];
						link.l1 = DLG_TEXT_BASE[18];
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = DLG_TEXT_BASE[19];
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = DLG_TEXT_BASE[20];
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]);
										link.l1 = DLG_TEXT_BASE[23];
										link.l1.go = "Cards_begin";
										link.l2 = DLG_TEXT_BASE[24];
										link.l2.go = "Cards_Rule";
										link.l3 = DLG_TEXT_BASE[25];
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = DLG_TEXT_BASE[26];
						    			link.l1 = DLG_TEXT_BASE[27];
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29]);
										link.l1 = DLG_TEXT_BASE[30];
										link.l1.go = "Dice_begin";
										link.l2 = DLG_TEXT_BASE[31];
										link.l2.go = "Dice_Rule";
										link.l3 = DLG_TEXT_BASE[32];
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = DLG_TEXT_BASE[33];
					    				link.l1 = DLG_TEXT_BASE[34];
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) // && sti(NPChar.Quest.HeroLose))
									{
					    				link.l9 = RandSwear() + DLG_TEXT_BASE[35];
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} //switch
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple(DLG_TEXT_BASE[36], DLG_TEXT_BASE[37]);
	                        link.l1 = RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple(DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[42];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[43];
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "Cards_Node_100";
			link.l2 = DLG_TEXT_BASE[46];
			link.l2.go = "Cards_Node_500";
			link.l3 = DLG_TEXT_BASE[47];
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[48];
                link.l1 = DLG_TEXT_BASE[49];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[50];
                link.l1 = DLG_TEXT_BASE[51];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[52];
                link.l1 = DLG_TEXT_BASE[53];
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[54];
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[56];
                link.l1 = DLG_TEXT_BASE[57];
			    link.l1.go = "exit_sit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[58];
                link.l1 = DLG_TEXT_BASE[59];
			    link.l1.go = "Cards_Node_100";
				link.l2 = DLG_TEXT_BASE[60];
			    link.l2.go = "exit_sit";
			    break;
		    }
		    
			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[61];
                link.l1 = DLG_TEXT_BASE[62];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[63];
                link.l1 = DLG_TEXT_BASE[64];
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[65];
			link.l1 = DLG_TEXT_BASE[66];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = true;
		break;
		
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[67];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[68];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";
		    
			Dialog.text = DLG_TEXT_BASE[69];
			link.l1 = DLG_TEXT_BASE[70];
			link.l1.go = "Dice_Node_100";
			link.l2 = DLG_TEXT_BASE[71];
			link.l2.go = "Dice_Node_500";
			link.l3 = DLG_TEXT_BASE[72];
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[73];
                link.l1 = DLG_TEXT_BASE[74];
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[75];
                link.l1 = DLG_TEXT_BASE[76];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = DLG_TEXT_BASE[77];
                link.l1 = DLG_TEXT_BASE[78];
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[79];
			link.l1 = DLG_TEXT_BASE[80];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = true;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[81];
                link.l1 = DLG_TEXT_BASE[82];
			    link.l1.go = "exit_sit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[83];
                link.l1 = DLG_TEXT_BASE[84];
			    link.l1.go = "Dice_Node_100";
				link.l2 = DLG_TEXT_BASE[85];
			    link.l2.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[86];
                link.l1 = DLG_TEXT_BASE[87];
			    link.l1.go = "exit_sit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = DLG_TEXT_BASE[88];
                link.l1 = DLG_TEXT_BASE[89];
			    link.l1.go = "exit_sit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[91];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = true;
		break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--
	    // homo 01/08/06 to_del
        // наводка на товар - перенес в слухи
	    //case "Find_Merchant_1":
            //if (pchar.GenQuest.Find_Merchant.lastspeak_date == LastSpeakDate())
            //{
            //    dialog.text = DLG_TEXT_BASE[92];
    		//	link.l1 = DLG_TEXT_BASE[93];
    	//		link.l1.go = "exit_sit";
            /*}    // to_do
            else
            {
                pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
                MerchantOnMap();
                sld = characterFromID("Quest_Merchant");
       			dialog.text = DLG_TEXT_BASE[94] + RandPhraseSimple(DLG_TEXT_BASE[95], DLG_TEXT_BASE[96]) + DLG_TEXT_BASE[97] + sld.Ship.Name +
                              DLG_TEXT_BASE[98] + NationNameGenitive(sti(sld.nation)) + DLG_TEXT_BASE[99] + GetGoodsNameAlt(sti(sld.QuestGoodsIdx)) + ".";
    			link.l1 = DLG_TEXT_BASE[100];
    			link.l1.go = "exit_sit";
			} */
		//break;
		//////  1
	    case "GhostShip_Speak_1":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
   			dialog.text = DLG_TEXT_BASE[101];
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "GhostShip_Speak_1_2";
		break;
		
		case "GhostShip_Speak_1_2":
			dialog.text = DLG_TEXT_BASE[103];
			link.l1 = DLG_TEXT_BASE[104];
			link.l1.go = "GhostShip_Speak_1_3";
		break;
		
		case "GhostShip_Speak_1_3":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = DLG_TEXT_BASE[106];
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "1";
			AddQuestRecord("GhostShipQuest", pchar.GenQuest.GhostShip.AskAbout);
		break;
		//////  2
		case "GhostShip_Speak_2":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
            dialog.text = DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "GhostShip_Speak_2_2";
		break;

		case "GhostShip_Speak_2_2":
			dialog.text = DLG_TEXT_BASE[109];
			link.l1    = DLG_TEXT_BASE[110];
			link.l1.go = "GhostShip_Speak_2_3";
		break;

		case "GhostShip_Speak_2_3":
			dialog.text = DLG_TEXT_BASE[111];
			link.l1 = DLG_TEXT_BASE[112];
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";
			AddQuestRecord("GhostShipQuest", "2");
		break;
		//////  3
		case "GhostShip_Speak_3":
            npchar.GhostShip_Speak_Yet = true;
            pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
            
			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
                             CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins")  &&
                            !CheckAttribute(npchar, "quest.GhostShipHelp")          &&
                            !CheckAttribute(pchar, "GenQuest.GhostShipWorkId")      &&
                            rand(2) == 1)
            {
                dialog.text = DLG_TEXT_BASE[113];
                link.l1 = DLG_TEXT_BASE[114];
    			link.l1.go = "exit_sit";
                break;
            }

            dialog.text = DLG_TEXT_BASE[115];
            if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
            {
                link.l1 = DLG_TEXT_BASE[116];
            }
            else
            {
				link.l1 = DLG_TEXT_BASE[117];
			}
			link.l1.go = "GhostShip_Speak_3_2";
		break;

		case "GhostShip_Speak_3_2":
			dialog.text = DLG_TEXT_BASE[118];
			link.l1    = DLG_TEXT_BASE[119];
			link.l1.go = "GhostShip_Speak_3_3";
		break;

		case "GhostShip_Speak_3_3":
			dialog.text = DLG_TEXT_BASE[120];
    		if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
            {
                link.l1 = DLG_TEXT_BASE[121];
            }
            else
            {
				link.l1 = DLG_TEXT_BASE[122];
			}
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";// вечный генератор
			AddQuestRecord("GhostShipQuest", "3");
			GhostShipOnMap();
		break;
		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = DLG_TEXT_BASE[125];
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = DLG_TEXT_BASE[128];
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = DLG_TEXT_BASE[129];
			link.l1 = DLG_TEXT_BASE[130];
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = DLG_TEXT_BASE[131];
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "sit_2";
		break;

		case "sit_2":
			AddMoneyToCharacter(pchar, -2);
			WaitDate("",0,0,0, 0, 30);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[133],
			                             DLG_TEXT_BASE[134],
										 DLG_TEXT_BASE[135]);
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = DLG_TEXT_BASE[137];
				link.l2.go = "sit_3";
			}
			// homo 01/08/06 to_del
            // наводка на товар - перенес в слухи
			//if (sti(pchar.reputation) < 41)
            //{
            //    link.l3 = DLG_TEXT_BASE[138];
			//	link.l3.go = "Find_Merchant_1";
            //}
            //homo 15/06/06 слухи
            link.l4 = LinkRandPhrase(DLG_TEXT_BASE[139],
                                    DLG_TEXT_BASE[140],
                                    DLG_TEXT_BASE[141]);
		    link.l4.go = "rumours_habitue";
		    //homo
		break;

		case "sit_3":
			int iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[142];
					link.l1 = DLG_TEXT_BASE[143];
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[144];
					link.l1 = DLG_TEXT_BASE[145];
					link.l1.go = "sit_case_2_friend";
					link.l2 = DLG_TEXT_BASE[146];
					link.l2.go = "sit_case_2_enemy";
				break;

				case 2:
					dialog.text = DLG_TEXT_BASE[147];
					link.l1 = DLG_TEXT_BASE[148];
					link.l1.go = "exit_sit";
					link.l2 = DLG_TEXT_BASE[149];
					link.l2.go = "sit_case_3";
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[150];
					link.l1 = DLG_TEXT_BASE[151];
					link.l1.go = "sit_case_4_exit";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[152];
					link.l1 = DLG_TEXT_BASE[153];
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 5:
                    if (!CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd") && !checkAttribute(npchar, "GhostShip_Speak_Yet") && pchar.GenQuest.GhostShip.lastspeak_date != LastSpeakDate())
					{
                        dialog.text = DLG_TEXT_BASE[154];
                        link.l1 = DLG_TEXT_BASE[155];
						link.l1.go = "exit_sit";
						switch (sti(pchar.GenQuest.GhostShip.AskAbout))
						{
							case 0 :
								link.l2 = DLG_TEXT_BASE[156];
								link.l2.go = "GhostShip_Speak_1";
							break;

							case 1 :
								link.l2 = DLG_TEXT_BASE[157];
								link.l2.go = "GhostShip_Speak_2";
							break;

							case 2 :
								link.l2 = DLG_TEXT_BASE[158];
								link.l2.go = "GhostShip_Speak_3";
							break;
						}
					}
					else
					{
	         			dialog.text = DLG_TEXT_BASE[159];
						link.l1 = DLG_TEXT_BASE[160];
						link.l1.go = "sit_2";
					}
                break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT_BASE[163];
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = DLG_TEXT_BASE[164];
			link.l1 = DLG_TEXT_BASE[165];
			link.l1.go = "exit_sit";
			link.l2 = DLG_TEXT_BASE[166];
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = DLG_TEXT_BASE[167];
			link.l1 = DLG_TEXT_BASE[168];
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = DLG_TEXT_BASE[169];
			link.l1 = DLG_TEXT_BASE[170];
//			link.l1.go = "tavern_keeper";
			link.l1.go = "fight_right_now"; //navy -- битва в таверне без базаров! :)
		break;

		case "exit_sit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "tavern_keeper":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
