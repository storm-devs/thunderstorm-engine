// boal 25/04/04 общий диалог мэры
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_Mayor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool   bOk;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
	// подставляем квестовую ноду при захвате города, если она есть
	/*if (LAi_IsCapturedLocation && CheckAttribute(NextDiag, "captureNode"))
	{
		Dialog.CurrentNode = NextDiag.captureNode;
		DeleteAttribute(NextDiag, "captureNode");
	}*/
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
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
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]));
				link.l1.go = "fight";
				break;
			} 
			//провека защиты -->
			/*if (GetEngineVersion() != iScriptVersion)
			{
       			dialog.text = DLG_TEXT_BASE[11];
				link.l1 = "...";
				link.l1.go = "exit";
				break;
			}*/ 
			//<-- провека защиты
			if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = DLG_TEXT_BASE[12];
				link.l1 = DLG_TEXT_BASE[13];
				link.l1.go = "Exit";
				break;
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 15)
            {
                dialog.text = DLG_TEXT_BASE[14] + GetFullName(pchar) + DLG_TEXT_BASE[15];
                if (sti(pchar.Money) >= ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000)
                {
                    link.l1 = DLG_TEXT_BASE[16];
				    link.l1.go = "arestFree_1";
                }
				link.l2 = DLG_TEXT_BASE[17];
				link.l2.go = "arest_1";
                /*if (CheckAttribute(NPChar, "NotHaveFort") && GetCharacterShipClass(PChar) <= 3) // to_do
                {
                    link.l3 = DLG_TEXT_BASE[18];
				    link.l3.go = "Town_Capture_1";
                } */
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = DLG_TEXT_BASE[19];
				link.l1 = DLG_TEXT_BASE[20];
				link.l1.go = "fight"; 
				break;
			}			

            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[21] + GetFullName(npchar) +
                              DLG_TEXT_BASE[22]+ GetCityName(NPChar.city) + DLG_TEXT_BASE[23] + NationKingsName(npchar)+
                              DLG_TEXT_BASE[24] + GetAddress_Form(NPChar) + ".";
				link.l1 = DLG_TEXT_BASE[25] + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
               	//ОСАДЫ homo
            if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = DLG_TEXT_BASE[26];
                        link.l1 = DLG_TEXT_BASE[27];
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = DLG_TEXT_BASE[28]+NationNamePeople(sti(aData.nation))+DLG_TEXT_BASE[29];
                        link.l1 = DLG_TEXT_BASE[30];
                        link.l1.go = "siege_task";
                        link.l2 = DLG_TEXT_BASE[31];
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                     makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterReputation(PChar, 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                        //--> слухи
                        SiegeRumour(DLG_TEXT_BASE[32]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[33]+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = DLG_TEXT_BASE[34]+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[35]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[36]+(sti(aData.iSquadronPower)*1000)+DLG_TEXT_BASE[37];
                        link.l1 = DLG_TEXT_BASE[38] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[39];
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 100 && sti(pchar.questTemp.HorseQty) > 5)
						{
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = DLG_TEXT_BASE[40];
								link.l1 = DLG_TEXT_BASE[41];
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[42],
                                      DLG_TEXT_BASE[43] +GetAddress_Form(NPChar)+"?");
        				link.l1 = DLG_TEXT_BASE[44] + NationNameGenitive(sti(NPChar.nation));
        				link.l1.go = "work";
        				link.l2 = DLG_TEXT_BASE[45];
        				link.l2.go = "quests";   //(перессылка в файл города)
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = DLG_TEXT_BASE[46];
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = DLG_TEXT_BASE[47];
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = DLG_TEXT_BASE[48];
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = DLG_TEXT_BASE[49];
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
        				link.l6 = DLG_TEXT_BASE[50] + NationNameGenitive(sti(NPChar.nation)) + ".";
        				link.l6.go = "Where_guber";
        				link.l7 = DLG_TEXT_BASE[51];
        			    link.l7.go = "Play_Game";
        				link.l10 = DLG_TEXT_BASE[52];
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;

		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = DLG_TEXT_BASE[53]+
				DLG_TEXT_BASE[54];
			link.l1 = DLG_TEXT_BASE[55];
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = DLG_TEXT_BASE[56];
			link.l1 = DLG_TEXT_BASE[57];
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = DLG_TEXT_BASE[58];
			link.l1 = DLG_TEXT_BASE[59];
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "TakeRing_5";
			link.l2 = DLG_TEXT_BASE[62] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[63];
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = (rand(2)+1)*500;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo(DLG_TEXT_BASE[66] + sld.startLocation + DLG_TEXT_BASE[67] + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = DLG_TEXT_BASE[68];
			link.l1 = DLG_TEXT_BASE[69];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;

		case "TakeRing_S1":
			dialog.text = DLG_TEXT_BASE[70];
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = DLG_TEXT_BASE[72];
			link.l1 = DLG_TEXT_BASE[73];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = DLG_TEXT_BASE[74];
			link.l1 = DLG_TEXT_BASE[75];
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = DLG_TEXT_BASE[76];
			link.l1 = DLG_TEXT_BASE[77] + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = DLG_TEXT_BASE[78];
                    link.l1 = DLG_TEXT_BASE[79];
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = DLG_TEXT_BASE[80]+NationNamePeople(sti(aData.nation))+DLG_TEXT_BASE[81];
                    link.l1 = DLG_TEXT_BASE[82];
                    link.l1.go = "siege_task";
                    link.l2 = DLG_TEXT_BASE[83];
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterReputation(PChar, 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
                    //--> слухи
                    SiegeRumour(DLG_TEXT_BASE[84]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[85]+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = DLG_TEXT_BASE[86]+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+DLG_TEXT_BASE[87]+NationNameSK(sti(aData.nation))+DLG_TEXT_BASE[88]+(sti(aData.iSquadronPower)*1000)+DLG_TEXT_BASE[89];
                    link.l1 = DLG_TEXT_BASE[90] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[91];
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = DLG_TEXT_BASE[92];
        			link.l1 = DLG_TEXT_BASE[93] + NationNameGenitive(sti(NPChar.nation));
        			link.l1.go = "work";
        			link.l2 = DLG_TEXT_BASE[94];
        			link.l2.go = "quests";
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = DLG_TEXT_BASE[95];
        			    link.l3.go = "sell_prisoner";
        			}
        			link.l4 = DLG_TEXT_BASE[96] + NationNameGenitive(sti(NPChar.nation)) + ".";
        			link.l4.go = "Where_guber";
        			link.l5 = DLG_TEXT_BASE[97];
        			link.l5.go = "Play_Game";
        			link.l10 = DLG_TEXT_BASE[98] + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "Card_Game";
   			link.l2 = DLG_TEXT_BASE[101];
			link.l2.go = "Dice_Game";
			link.l10 = DLG_TEXT_BASE[102];
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = DLG_TEXT_BASE[103];
    			link.l1 = DLG_TEXT_BASE[104];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[105];
	    			link.l1 = DLG_TEXT_BASE[106];
	    			link.l1.go = "Cards_begin";
	    			link.l2 = DLG_TEXT_BASE[107];
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[108];
	    			link.l1 = DLG_TEXT_BASE[109];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = GetConvertStr("CARDS_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[110];
			link.l1.go = "Cards_begin";
			link.l3 = DLG_TEXT_BASE[111];
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "Cards_Node_100";
			link.l2 = DLG_TEXT_BASE[114];
			link.l2.go = "Cards_Node_500";
			link.l3 = DLG_TEXT_BASE[115];
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[116];
                link.l1 = DLG_TEXT_BASE[117];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[118] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[119];
                link.l1 = DLG_TEXT_BASE[120];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[121];
                link.l1 = DLG_TEXT_BASE[122];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[123];
			link.l1 = DLG_TEXT_BASE[124];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[125];
                link.l1 = DLG_TEXT_BASE[126];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[127];
                link.l1 = DLG_TEXT_BASE[128];
			    link.l1.go = "Cards_Node_100";
				link.l2 = DLG_TEXT_BASE[129];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[130] + GetAddress_Form(npchar) + DLG_TEXT_BASE[131];
                link.l1 = DLG_TEXT_BASE[132];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[133];
                link.l1 = DLG_TEXT_BASE[134];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[135];
			link.l1 = DLG_TEXT_BASE[136];
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = DLG_TEXT_BASE[137];
    			link.l1 = DLG_TEXT_BASE[138];
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = DLG_TEXT_BASE[139];
	    			link.l1 = DLG_TEXT_BASE[140];
	    			link.l1.go = "Dice_begin";
	    			link.l2 = DLG_TEXT_BASE[141];
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = DLG_TEXT_BASE[142];
	    			link.l1 = DLG_TEXT_BASE[143];
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = GetConvertStr("DICE_RULE", "MiniGames.txt");
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "Dice_begin";
			link.l3 = DLG_TEXT_BASE[145];
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = DLG_TEXT_BASE[146];
			link.l1 = DLG_TEXT_BASE[147];
			link.l1.go = "Dice_Node_100";
			link.l2 = DLG_TEXT_BASE[148];
			link.l2.go = "Dice_Node_500";
			link.l3 = DLG_TEXT_BASE[149];
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[150];
                link.l1 = DLG_TEXT_BASE[151];
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[152] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[153];
                link.l1 = DLG_TEXT_BASE[154];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = DLG_TEXT_BASE[155];
                link.l1 = DLG_TEXT_BASE[156];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[157];
			link.l1 = DLG_TEXT_BASE[158];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = DLG_TEXT_BASE[159];
                link.l1 = DLG_TEXT_BASE[160];
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = DLG_TEXT_BASE[161];
                link.l1 = DLG_TEXT_BASE[162];
			    link.l1.go = "Dice_Node_100";
				link.l2 = DLG_TEXT_BASE[163];
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[164] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[165];
                link.l1 = DLG_TEXT_BASE[166];
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = DLG_TEXT_BASE[167];
                link.l1 = DLG_TEXT_BASE[168];
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = DLG_TEXT_BASE[169];
			link.l1 = DLG_TEXT_BASE[170];
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.snd = "Voice\CHMA\CHMA004";
			dialog.text = DLG_TEXT_BASE[171];
			link.l1 = DLG_TEXT_BASE[172];
			link.l1.go = "exit";
		break;

		case "Where_guber":
            offref = characterFromID(NationShortName(sti(NPChar.nation))+"_guber");

            if (NPChar.location == offref.location)
            {
                dialog.text = DLG_TEXT_BASE[173] + RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]) + DLG_TEXT_BASE[176]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                              DLG_TEXT_BASE[177];
    			link.l1 = DLG_TEXT_BASE[178];
    			link.l1.go = "exit";
            }
            else
            {
                if (bBettaTestMode || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) > rand(5) || CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))))// когда патен всегда
                {
                    cn = FindLocation(offref.location);
                	if(cn < 0)
                    {
                        attrLoc = "error";
                        dialog.text = DLG_TEXT_BASE[179] + RandPhraseSimple(DLG_TEXT_BASE[180], DLG_TEXT_BASE[181]) + DLG_TEXT_BASE[182]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                      DLG_TEXT_BASE[183];
                    }
                	else
                	{
                	    attrLoc = locations[cn].islandId;
                	    if (attrLoc == "Mein")
                	    {
        			    	dialog.text = DLG_TEXT_BASE[184] + RandPhraseSimple(DLG_TEXT_BASE[185], DLG_TEXT_BASE[186]) + DLG_TEXT_BASE[187]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(DLG_TEXT_BASE[188],
                                            DLG_TEXT_BASE[189],
                                            DLG_TEXT_BASE[190]) + DLG_TEXT_BASE[191] + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
						else
						{
						    dialog.text = DLG_TEXT_BASE[192] + RandPhraseSimple(DLG_TEXT_BASE[193], DLG_TEXT_BASE[194]) + DLG_TEXT_BASE[195]+NationNameGenitive(sti(NPChar.nation))+ " " + GetFullName(offref)+
                                  LinkRandPhrase(DLG_TEXT_BASE[196],
                                            DLG_TEXT_BASE[197],
                                            DLG_TEXT_BASE[198]) + GetConvertStr(attrLoc, "LocLables.txt") + DLG_TEXT_BASE[199] + GetConvertStr(locations[cn].fastreload + " Town", "LocLables.txt") + ".";
						}
                    }
        			link.l1 = DLG_TEXT_BASE[200];
        			link.l1.go = "exit";
    			}
    			else
    			{
                    dialog.text = DLG_TEXT_BASE[201];
        			link.l1 = DLG_TEXT_BASE[202];
        			link.l1.go = "exit";
    			}
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = DLG_TEXT_BASE[203];
        	link.l1 = DLG_TEXT_BASE[204];
        	link.l1.go = "exit";
        	// boal квесты от ВМЛ -->
            if (CheckAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id))
			{
				dialog.text = DLG_TEXT_BASE[205];
				link.l1 = DLG_TEXT_BASE[206];
				link.l1.go = "GhostShipDone";
				break;
			}
			if (CheckAttribute(NPChar, "from_sea") && Pchar.location.from_sea == NPChar.from_sea)
            {
    			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
                     CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins")  &&
                    GetNpcQuestPastDayWOInit(npchar, "GhostShipHelp") > 30  &&
                    !CheckAttribute(pchar, "GenQuest.GhostShipWorkId")      &&
                    cRand(2) == 1)
                {
                    dialog.text = DLG_TEXT_BASE[207] + GetAddress_Form(NPChar) + RandPhraseSimple(DLG_TEXT_BASE[208],
                                                       DLG_TEXT_BASE[209]);
    				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[210],
                                               DLG_TEXT_BASE[211]);
    				link.l1.go = "GhostShipHelp_1";
    				break;
                }
            }
            // boal квесты от ВМЛ <--
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[212] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen") + DLG_TEXT_BASE[213], 
						DLG_TEXT_BASE[214] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Dat") + DLG_TEXT_BASE[215]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[216], DLG_TEXT_BASE[217]+ GetAddress_Form(NPChar) + ".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[218] + GetFullName(arName) + DLG_TEXT_BASE[219], 
								DLG_TEXT_BASE[220] + GetFullName(arName) + DLG_TEXT_BASE[221], 
								DLG_TEXT_BASE[222] + GetFullName(arName) + DLG_TEXT_BASE[223]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[224] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[225]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[226] + GetFullName(arName) + DLG_TEXT_BASE[227] + GetAddress_Form(NPChar) + ".",
								DLG_TEXT_BASE[228] + GetFullName(arName) + DLG_TEXT_BASE[229]);
							link.l1 = DLG_TEXT_BASE[230] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[231] + GetFullName(arName) + DLG_TEXT_BASE[232], DLG_TEXT_BASE[233] + GetFullName(arName) + DLG_TEXT_BASE[234]);
							link.l1 = DLG_TEXT_BASE[235] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[236];
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[237] + GetFullName(arName) + DLG_TEXT_BASE[238], DLG_TEXT_BASE[239] + GetFullName(arName) + DLG_TEXT_BASE[240]);
							link.l1 = DLG_TEXT_BASE[241] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Execute";		
						break;
					}
				}
				//------ поиска шпиона ------------>>
				if (QuestName == "SeekSpy")
				{
					switch (pchar.GenQuest.SeekSpy)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[242], 
								DLG_TEXT_BASE[243], 
								DLG_TEXT_BASE[244]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[245] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[246]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[247],
								DLG_TEXT_BASE[248]);
							link.l1 = DLG_TEXT_BASE[249] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[250], DLG_TEXT_BASE[251]);
							link.l1 = DLG_TEXT_BASE[252];
							link.l1.go = "All_Execute";		
						break;
						case "FoundSpy":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[253], DLG_TEXT_BASE[254]);
							link.l1 = DLG_TEXT_BASE[255];
							link.l1.go = "All_Execute";	
							sld = characterFromId("MayorQuestSpy");
							sld.lifeDay = 0;
							ChangeCharacterAddress(sld, "none", "");
							LAi_SetStayType(sld);
							sTemp = npchar.city + "_town";
							LocatorReloadEnterDisable(sTemp, "gate_back", false);
							LocatorReloadEnterDisable(sTemp, "reload1_back", false);
							LocatorReloadEnterDisable(sTemp, "reload2_back", false);
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple(DLG_TEXT_BASE[256],
									DLG_TEXT_BASE[257]);
								link.l1 = DLG_TEXT_BASE[258] + GetAddress_Form(NPChar) + ".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase(DLG_TEXT_BASE[259], 
									DLG_TEXT_BASE[260], 
									DLG_TEXT_BASE[261]);
								link.l1 = RandPhraseSimple(DLG_TEXT_BASE[262] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[263]+ GetAddress_Form(NPChar) + ".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[264], DLG_TEXT_BASE[265]);
							link.l1 = DLG_TEXT_BASE[266];
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
							}
							else
							{
								link.l1.go = "All_Execute";		
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				//------ уничтожение контры ------------>>
				if (QuestName == "KillSmugglers")
				{
					switch (pchar.GenQuest.KillSmugglers)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[267], 
								DLG_TEXT_BASE[268], 
								DLG_TEXT_BASE[269]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[270] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[271]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[272],
								DLG_TEXT_BASE[273]);
							link.l1 = DLG_TEXT_BASE[274] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							int lngFileID = LanguageOpenFile("LocLables.txt");
							sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.KillSmugglers.shoreId);
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[275], DLG_TEXT_BASE[276]);
							link.l1 = DLG_TEXT_BASE[277] + sTemp + DLG_TEXT_BASE[278];
							link.l1.go = "All_Execute";		
						break;
					}
				}
				//------ найти пирата в море ------------>>
				if (QuestName == "DestroyPirate")
				{
					switch (pchar.GenQuest.DestroyPirate)
					{
						case "":
							dialog.text = LinkRandPhrase(DLG_TEXT_BASE[279], 
								DLG_TEXT_BASE[280], 
								DLG_TEXT_BASE[281]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[282] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[283]+ GetAddress_Form(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[284],
								DLG_TEXT_BASE[285]);
							link.l1 = DLG_TEXT_BASE[286] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[287], DLG_TEXT_BASE[288]);
							link.l1 = DLG_TEXT_BASE[289] + GetAddress_Form(NPChar) + ".";
							link.l1.go = "All_Execute";	
							//здесь снимаем торговцев
							for (i=0; i<5; i++)
							{
								Group_DeleteGroup("MQGroupAll_" + i);
							}
						break;
						case "Found":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[290], DLG_TEXT_BASE[291]);
							link.l1 = DLG_TEXT_BASE[292] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[293];
							link.l1.go = "All_Found";		
						break;
						case "PirateIsOut":
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[294], DLG_TEXT_BASE[295]);
							link.l1 = DLG_TEXT_BASE[296] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[297];
							link.l1.go = "All_Found";		
						break;
					}
				}
				//<<------ взятые квесты ------------
				break;
			}
			//==> раздача патентов
			sTemp = npchar.city;
			if (CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp) && sti(pchar.GenQuest.MayorQuestsList.(sTemp)) > (5 + rand(5)) && !CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) )
            {
                dialog.text = DLG_TEXT_BASE[298] + GetAddress_Form(NPChar) +
                              DLG_TEXT_BASE[299] + NationNameGenitive(sti(NPChar.nation))+".";

    		    link.l1 = DLG_TEXT_BASE[300]+ NationNameGenitive(sti(NPChar.nation))+".";
    			link.l1.go = "Patent_Give";
    			if(isMainCharacterPatented())
				{
				    link.l2 = DLG_TEXT_BASE[301];
				}
				else
				{
    			    link.l2 = DLG_TEXT_BASE[302];
    			}
    			link.l2.go = "exit";    			
    			pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
				break;
			}			
//navy -->
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = DLG_TEXT_BASE[303] + GetFullName(&Characters[i])
					+ DLG_TEXT_BASE[304];
				link.l1 = DLG_TEXT_BASE[305];
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if (rand(5) > 4 && !bBettaTestMode)
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[306], 
						DLG_TEXT_BASE[307], 
						DLG_TEXT_BASE[308]);
					link.l1 = DLG_TEXT_BASE[309] + GetAddress_Form(NPChar) + ".";
					link.l1.go = "exit";
				}
				else 
				{
					// boal 02.09.06 -->
					if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
                    {   // если ПГГ контрит в этом городе, то мэр дает задание на контру по факту - приятное с полезным, жаловаться не нужно, если задания другие были, то в сад, этот код не сработает
                        i = 3;
                    }
                    else
                    {
                        //отсекаем возможность дать квест пирата в Панаме
						if (npchar.city == "Panama") i = rand(2);							
						else i = cRand(4);
                    }
                    // boal <--
					switch (i)
					{					
						//========== квест уничтожения банды ============
						case 0:
							pchar.GenQuest.DestroyGang.Terms = cRand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((cRand(8) + 2) * 170) + (sti(pchar.rank) * 200); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = DLG_TEXT_BASE[310] + XI_ConvertString("Colony"+npchar.city+"Gen") + DLG_TEXT_BASE[311] + GetFullName(arName) + DLG_TEXT_BASE[312];
							link.l1 = DLG_TEXT_BASE[313];
							link.l1.go = "DestroyGang";
						break;
						//========== розыска лазутчика ============
						case 1:
							pchar.GenQuest.SeekSpy.Terms = cRand(2) + 3; //сроки выполнения задания
							pchar.GenQuest.SeekSpy.Money = ((cRand(8) + 2) * 150) + (sti(pchar.rank) * 200); //вознаграждение
							dialog.text = DLG_TEXT_BASE[314] + XI_ConvertString("Colony"+npchar.city+"Dat") + DLG_TEXT_BASE[315];
							link.l1 = DLG_TEXT_BASE[316] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[317];
							link.l1.go = "SeekSpy";
						break;
						//========== пробраться во вражеский город ============
						case 2:
							pchar.GenQuest.Intelligence.Terms = cRand(10) + (30 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((cRand(4) + 6) * 500) + (sti(pchar.rank) * 200); //вознаграждение
							pchar.GenQuest.Intelligence.City = GetSpyColony(npchar); //враждебная колония
                            sTemp = DLG_TEXT_BASE[318] + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = DLG_TEXT_BASE[319] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc") + sTemp + DLG_TEXT_BASE[320];
							link.l1 = DLG_TEXT_BASE[321] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + DLG_TEXT_BASE[322];
							link.l1.go = "Intelligence";
						break;
						//========== уничтожение контрабандистов ============
						case 3:
							dialog.text = DLG_TEXT_BASE[323];
							link.l1 = DLG_TEXT_BASE[324];
							link.l1.go = "KillSmugglers";
						break;
						//========== замочить пирата, что грабит суда ============
						case 4:
							//--> генерим ранг 
							if (sti(pchar.rank) > 6) 
							{
								if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE);
								else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE/2);
							}
							else
							{	//казуалам зеленый свет на начало игры
								if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
								else iRank = 1;
							}	
							//<-- генерим ранг 
							LAi_group_Delete("MayorPirateGroup");
							sld = GetCharacter(NPC_GenerateCharacter("MQPirate", "", "man", "man", iRank, sti(npchar.nation), -1, true));							
							SetCaptanModelByEncType(sld, "pirate");
							DeleteAttribute(sld, "Ship");
							SetShipToFantom(sld, "pirate", false);
							sld.Ship.Mode = "Pirate";
							//sld.ShipTaskLock = true; //лочим таск
							sld.dialog.filename = "MayorQuests_dialog.c";
							sld.dialog.currentnode = "DestroyPirate_Abordage";
							sld.DeckDialogNode = "DestroyPirate_Deck"; 
							sld.DontRansackCaptain = true;
							sld.DontCheckFlag = true;  // не проверять флаг ГГ
							sld.SaveItemsForDead = true; // сохранять на трупе вещи
							sld.DontClearDead = true; // не убирать труп через 200с
							sld.AlwaysSandbankManeuver = true;
							sld.WatchFort = true; //видеть форты
							sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
							sld.greeting = "pirat_common";
							LAi_group_MoveCharacter(sld, "MayorPirateGroup");
							dialog.text = DLG_TEXT_BASE[325] + XI_ConvertString("Colony"+npchar.city+"Gen") + DLG_TEXT_BASE[326];  
							link.l1 = DLG_TEXT_BASE[327] + GetAddress_Form(NPChar) + "?";
							link.l1.go = "DestroyPirate";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[328], DLG_TEXT_BASE[329], DLG_TEXT_BASE[330]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[331], DLG_TEXT_BASE[332]+ GetAddress_Form(NPChar) + ". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "Patent_Give":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
            pchar.PatentPrice = 0;
			dialog.text = DLG_TEXT_BASE[333];
			link.l1 = DLG_TEXT_BASE[334]+GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
		break;

		case "sell_prisoner":
            dialog.text = DLG_TEXT_BASE[335];

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = DLG_TEXT_BASE[336];
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  DLG_TEXT_BASE[337] + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + DLG_TEXT_BASE[338] + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + DLG_TEXT_BASE[339] + FindRussianMoneyString(qty) + DLG_TEXT_BASE[340];
                    /*if (CheckAttribute(NPChar, "from_sea"))
                    {
                        link.l2 = DLG_TEXT_BASE[341];
			            link.l2.go = "sell_prisoner_DeathExec";
			        } */
                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + DLG_TEXT_BASE[342] + FindRussianMoneyString(qty) + ".";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = DLG_TEXT_BASE[343] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = DLG_TEXT_BASE[344];
			link.l3.go = "exit";
		break;

        /*case "sell_prisoner_DeathExec":
			dialog.text = DLG_TEXT_BASE[345];
			link.l1 = DLG_TEXT_BASE[346];
			link.l1.go = "sell_prisoner_DeathExec_1";
			link.l2 = DLG_TEXT_BASE[347];
			link.l2.go = "sell_prisoner_3";
		break;

		case "sell_prisoner_DeathExec_1":
			dialog.text = DLG_TEXT_BASE[348];
            if (sti(pchar.Money) >= 3000)
            {
			    link.l1 = DLG_TEXT_BASE[349];
			    link.l1.go = "sell_prisoner_DeathExec_2";
			}
			link.l2 = DLG_TEXT_BASE[350];
			link.l2.go = "exit";
		break;

		case "sell_prisoner_DeathExec_2":
            AddMoneyToCharacter(pchar, -3000);
            offref = characterFromID(pchar.prisonerToSellId);
            DeleteAttribute(offref,"prisoned"); // освободили пленника
			RemovePassenger(pchar, offref);
        	offref.location = "";
        	OfficersReaction("bad");
        	ChangeCharacterReputation(pchar, -5);

        	AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
        	AddCharacterSkill(pchar, SKILL_SNEAK, 0);

            Pchar.GenQuest.Death_Execution_location = NPChar.from_sea;
            DialogExit();
			NextDiag.CurrentNode = "First time";

			DeathExecutionStart(offref, sti(NPChar.nation));
		break;   */

		case "sell_prisoner_3":
			dialog.text = DLG_TEXT_BASE[351];
			link.l1 = DLG_TEXT_BASE[352];
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterReputation(pchar, -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // все, все свободны

            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = DLG_TEXT_BASE[353];
                Link.l1 = DLG_TEXT_BASE[354];
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернем диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = DLG_TEXT_BASE[355];
                Link.l2 = DLG_TEXT_BASE[356];
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = DLG_TEXT_BASE[357];
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = DLG_TEXT_BASE[358];
	    				}
	    				else
	    				{
	    					Link.l1 = DLG_TEXT_BASE[359];
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = DLG_TEXT_BASE[360];
				}
				else
				{
	            	Link.l2 = DLG_TEXT_BASE[361];
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = DLG_TEXT_BASE[362] + NationNameGenitive(sti(NPChar.nation)) + DLG_TEXT_BASE[363];
	                Link.l1 = DLG_TEXT_BASE[364];
	                Link.l1.go = "City_patent";
	                Link.l2 = DLG_TEXT_BASE[365] + NationNameGenitive(sti(PChar.nation)) + DLG_TEXT_BASE[366] + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = DLG_TEXT_BASE[367];
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 300);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info(DLG_TEXT_BASE[368]);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterReputation(GetMainCharacter(), -20); // пираты мы, но у нас патент
            dialog.Text = DLG_TEXT_BASE[369];
			Link.l1 = DLG_TEXT_BASE[370];
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = DLG_TEXT_BASE[371];
            Link.l1 = DLG_TEXT_BASE[372];
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернем диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = DLG_TEXT_BASE[373];
            Link.l1 = DLG_TEXT_BASE[374];
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 200);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 200);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = DLG_TEXT_BASE[375];
            Link.l1 = DLG_TEXT_BASE[376];
            Link.l1.go = "Summ";
            ChangeCharacterReputation(GetMainCharacter(), -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = DLG_TEXT_BASE[377];
			Link.l1 = DLG_TEXT_BASE[378];
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterReputation(GetMainCharacter(), 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 500);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 300);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecord("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не дает, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернем диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

			/*   to_do
            ref rFortCh = FindSiegeFortCommander();
            if (rFortCh.id == FortChref.id)//это и есть форт обложенный эскадрой
            {
                if (sti(Characters[GetCharacterIndex("NatCapitan_1")].nation) == sti(rFortCh.nation)) //они этой же нации
                {
                    AddDialogExitQuest("CheckFortsEndSiege_02");
                }
            }
			  */
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = DLG_TEXT_BASE[379];
			/*Link.l1 = DLG_TEXT_BASE[380];
			Link.l1.go = "Strike";
			if (!CheckAttribute(NPChar, "NotHaveFort"))
			{
			    Link.l2 = DLG_TEXT_BASE[381];
			    Link.l2.go = "Death_Execution_1";
            }       */
            Link.l3 = DLG_TEXT_BASE[382];
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = DLG_TEXT_BASE[383];
            link.l1 = DLG_TEXT_BASE[384] + ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000 + DLG_TEXT_BASE[385];
			link.l1.go = "arestFree_2";
			link.l2 = DLG_TEXT_BASE[386];
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(7))
            {
    			dialog.text = DLG_TEXT_BASE[387];
    		    link.l1 = DLG_TEXT_BASE[388];
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) * 6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
    		    AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
            }
            else
            {
    			dialog.text = DLG_TEXT_BASE[389];
    		    link.l1 = DLG_TEXT_BASE[390];
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 10);
            }
		break;

		case "arest_1":
			dialog.text = DLG_TEXT_BASE[391];
		    //link.l1 = DLG_TEXT_BASE[392];
		    //link.l1.go = "arest_2";
		    link.l1 = DLG_TEXT_BASE[393];
		    link.l1.go = "fight";
		break;

		/*case "arest_2":
            Pchar.GenQuest.Death_Execution_location = NPChar.from_sea;
            DialogExit();
			NextDiag.CurrentNode = "First time";

			DeathExecutionStart(Pchar, sti(NPChar.nation));
		break;    */
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = DLG_TEXT_BASE[394] + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + DLG_TEXT_BASE[395] + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
			link.l1 = DLG_TEXT_BASE[396];
		    link.l1.go = "DestroyGang_agree";
			link.l2 = DLG_TEXT_BASE[397];
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = DLG_TEXT_BASE[398];
				link.l1 = DLG_TEXT_BASE[399];
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[400];
				link.l1 = DLG_TEXT_BASE[401] + GetAddress_Form(NPChar) + ".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Поиски лазутчика
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "SeekSpy":
			dialog.text = DLG_TEXT_BASE[402] + FindRussianDaysString(sti(pchar.GenQuest.SeekSpy.Terms)) + DLG_TEXT_BASE[403] + FindRussianMoneyString(sti(pchar.GenQuest.SeekSpy.Money)) + ".";
			link.l1 = DLG_TEXT_BASE[404];
		    link.l1.go = "SeekSpy_agree";
			link.l2 = DLG_TEXT_BASE[405];
		    link.l2.go = "All_disagree";
		break;
		case "SeekSpy_agree":
			if (rand(1))
			{   //шпион в одной из общих локаций common
				pchar.GenQuest.SeekSpy.Location = GetSpyLocation(npchar); //определяем локацию
				Log_QuestInfo(pchar.GenQuest.SeekSpy.Location); //чит
				if (pchar.GenQuest.SeekSpy.Location == "none") //на всякий случай
				{
					dialog.text = DLG_TEXT_BASE[406];
					link.l1 = DLG_TEXT_BASE[407];
					link.l1.go = "exit";
					DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
					break;
				}
				else
				{
					pchar.quest.SeekSpy_login.again = true; //на всякий случай
				}
			}
			else
			{	//шпион гуляет по городу
				pchar.GenQuest.SeekSpy.Location = npchar.city + "_town"; //определяем локацию
				pchar.GenQuest.SeekSpy.City = rand(1); //флаг шпион в городе, ренд - кто будет подсказывать в таверне
			}
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "SeekSpy"; //тип квеста
			dialog.text = DLG_TEXT_BASE[408];
			link.l1 = DLG_TEXT_BASE[409] + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
			pchar.GenQuest.SeekSpy.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.quest.SeekSpy.win_condition.l1 = "location";
			pchar.quest.SeekSpy.win_condition.l1.location = pchar.GenQuest.SeekSpy.Location;
			pchar.quest.SeekSpy.win_condition = "SeekSpy_login";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.SeekSpy.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.SeekSpy.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.SeekSpy.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = DLG_TEXT_BASE[410] + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + DLG_TEXT_BASE[411];
			link.l1 = DLG_TEXT_BASE[412];
		    link.l1.go = "Intelligence_agree";
			link.l2 = DLG_TEXT_BASE[413];
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = DLG_TEXT_BASE[414];
				link.l1 = DLG_TEXT_BASE[415];
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = DLG_TEXT_BASE[416] + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + DLG_TEXT_BASE[417] + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					DLG_TEXT_BASE[418] + GetFullName(&characters[GetCharacterIndex(sTemp)]) + DLG_TEXT_BASE[419] + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + DLG_TEXT_BASE[420];
				link.l1 = DLG_TEXT_BASE[421] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[422];
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / (rand(2)+2);
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[423] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + DLG_TEXT_BASE[424], 
				DLG_TEXT_BASE[425] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + DLG_TEXT_BASE[426]);
			link.l1 = DLG_TEXT_BASE[427] + GetAddress_Form(NPChar) + ".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple(DLG_TEXT_BASE[428] + GetFullName(npchar) + DLG_TEXT_BASE[429] + GetMainCharacterNameGen() + ".", 
				DLG_TEXT_BASE[430] + GetFullName(npchar) + DLG_TEXT_BASE[431] + GetMainCharacterNameDat() + DLG_TEXT_BASE[432]), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение контры
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "KillSmugglers":
			pchar.GenQuest.questName = "KillSmugglers"; //тип квеста
			pchar.GenQuest.KillSmugglers.Terms = rand(2) + 1; //сроки выполнения задания
			pchar.GenQuest.KillSmugglers.Money = ((rand(8) + 2) * 200) + (sti(pchar.rank) * 200); //вознаграждение
			dialog.text = DLG_TEXT_BASE[433] + FindRussianDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)) + DLG_TEXT_BASE[434] + FindRussianMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)) + DLG_TEXT_BASE[435];
			link.l1 = DLG_TEXT_BASE[436] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[437];
		    link.l1.go = "KillSmugglers_agree";
			link.l2 = DLG_TEXT_BASE[438];
		    link.l2.go = "All_disagree";
		break;
		case "KillSmugglers_agree":
			dialog.text = DLG_TEXT_BASE[439];
			link.l1 = DLG_TEXT_BASE[440] + GetAddress_Form(NPChar) + ".";
		    link.l1.go = "exit";
			pchar.GenQuest.KillSmugglers.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.GenQuest.KillSmugglers.Areal = GetArealByCityName(npchar.city); //ареал, где нужно поработать
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (sld.id == "Rand_Smug01" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(sld.location)]))
				{
					pchar.quest.KillSmugglers.win_condition.l1 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l1.character = "Rand_Smug01";
					pchar.quest.KillSmugglers.win_condition.l2 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l2.character = "Rand_Smug02";
					pchar.quest.KillSmugglers.win_condition.l3 = "NPC_Death";
					pchar.quest.KillSmugglers.win_condition.l3.character = "Rand_Smug03";
					pchar.quest.KillSmugglers.win_condition = "KillSmugglers_after";
					break;
				}
			}
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.KillSmugglers.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.KillSmugglers.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.KillSmugglers.Money)));
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Поиск и уничтожение пирата
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyPirate":
			pchar.GenQuest.questName = "DestroyPirate"; //тип квеста
			pchar.GenQuest.DestroyPirate.Terms = cRand(3) + (15 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
			pchar.GenQuest.DestroyPirate.Money = ((cRand(5) + 5) * 500) + (sti(pchar.rank) * 200); //вознаграждение
			sld = characterFromId("MQPirate");
			dialog.text = DLG_TEXT_BASE[441] + XI_ConvertString("Colony"+npchar.city+"Gen") +
				DLG_TEXT_BASE[442] + FindRussianDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)) + DLG_TEXT_BASE[443] + FindRussianMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)) + DLG_TEXT_BASE[444];
			link.l1 = DLG_TEXT_BASE[445] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[446];
		    link.l1.go = "DestroyPirate_agree";
			link.l2 = DLG_TEXT_BASE[447];
		    link.l2.go = "All_disagree";
		break;
		case "DestroyPirate_agree":
			dialog.text = DLG_TEXT_BASE[448];
			link.l1 = DLG_TEXT_BASE[449] + GetAddress_Form(NPChar) + ".";
		    link.l1.go = "exit";
			pchar.GenQuest.DestroyPirate.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			pchar.GenQuest.DestroyPirate.Areal = GetArealByCityName(npchar.city); //ареал, куда будем ставить пирата
			AddDialogExitQuest("DestroyPirate_Begin");
		break;
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = DLG_TEXT_BASE[450];
			link.l1 = DLG_TEXT_BASE[451] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[452];
		    link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[453], 
				DLG_TEXT_BASE[454]);
			link.l1 = DLG_TEXT_BASE[455] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[456];
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[457] + GetFullName(npchar) + DLG_TEXT_BASE[458] + GetMainCharacterNameDat() + DLG_TEXT_BASE[459], 
				DLG_TEXT_BASE[460] + GetFullName(npchar) + DLG_TEXT_BASE[461] + GetFullName(pchar) + DLG_TEXT_BASE[462], 
				DLG_TEXT_BASE[463] + GetFullName(npchar) + DLG_TEXT_BASE[464] + GetFullName(pchar) + DLG_TEXT_BASE[465]), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[466], 
				DLG_TEXT_BASE[467]);
			link.l1 = DLG_TEXT_BASE[468] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[469];
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[470] + GetFullName(npchar) + DLG_TEXT_BASE[471] + GetMainCharacterNameDat() + DLG_TEXT_BASE[472], 
				DLG_TEXT_BASE[473] + GetFullName(npchar) + DLG_TEXT_BASE[474] + GetFullName(pchar) + DLG_TEXT_BASE[475], 
				DLG_TEXT_BASE[476] + GetFullName(npchar) + DLG_TEXT_BASE[477] + GetFullName(pchar) + DLG_TEXT_BASE[478]), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterReputation(pchar, -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[479] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + DLG_TEXT_BASE[480], 
				DLG_TEXT_BASE[481] + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + DLG_TEXT_BASE[482]);
			link.l1 = DLG_TEXT_BASE[483] + GetAddress_Form(NPChar) + ", " + RandPhraseSimple(DLG_TEXT_BASE[484], DLG_TEXT_BASE[485]);
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[486] + GetFullName(npchar) + DLG_TEXT_BASE[487] + GetMainCharacterNameGen() + ".", 
				DLG_TEXT_BASE[488] + GetFullName(npchar) + DLG_TEXT_BASE[489] + GetMainCharacterNameGen() + DLG_TEXT_BASE[490], 
				DLG_TEXT_BASE[491] + GetFullName(npchar) + DLG_TEXT_BASE[492] + GetFullName(pchar) + DLG_TEXT_BASE[493]), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[494], DLG_TEXT_BASE[495]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[496], DLG_TEXT_BASE[497]);
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterReputation(pchar, 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = DLG_TEXT_BASE[498];
			link.l1 = DLG_TEXT_BASE[499];
		    link.l1.go = "exit";
		break;
		//  boal из ВМЛ -->
		case "GhostShipDone":
            SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");
            
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddMoneyToCharacter(pchar, 5000 + rand(10) * 1000);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -20);
			sTemp = npchar.City;
   			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;

            OfficersReaction("good");
			DeleteAttribute(pchar, "GenQuest.GhostShipWorkId");
			DeleteAttribute(pchar, "GenQuest.GhostShipDone_" + NPChar.id);
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

		case "GhostShipHelp_1":
            SaveCurrentNpcQuestDateParam(npchar, "GhostShipHelp");
			pchar.GenQuest.GhostShipWorkId = NPChar.id;

			bDisableFastReload              = true;

			SetLocationCapturedState(NPChar.Default, true);

			Pchar.quest.GhostShipHelp.win_condition.l1          = "location";
    	    Pchar.quest.GhostShipHelp.win_condition.l1.location = NPChar.from_sea;
    	    Pchar.quest.GhostShipHelp.win_condition             = "GhostShipHelp";

			Pchar.GenQuest.Hunter2Pause            = true;

			ReOpenQuestHeader("GhostShipQuest");
			AddQuestRecord("GhostShipQuest", "help_t1");
			AddQuestUserData("GhostShipQuest", "sCity", GetCityName(npchar.City));
			
   			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[cRand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[cRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != npchar.City)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[cRand(howStore-1)]].id;
}
