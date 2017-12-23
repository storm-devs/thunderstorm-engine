#include "TEXT\DIALOGS\Rumours\Common_rumours.h"
void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag)
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{
	case "rumours_citizen":	
		NextDiag.CurrentNode = "rumours";
		//------------- квестовые слухи горожан --------->>>>>>>>
		//жемчужный генератор Ўарпа
		if (pchar.questTemp.Sharp.City == npchar.city && sti(pchar.questTemp.Sharp.City.rumour))
		{
			pchar.questTemp.Sharp.City.rumour = false; //слух дан
			Dialog.Text = Sharp_choiceAction();
			link.l1 = DLG_TEXT_RUM[0];
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple(DLG_TEXT_RUM[1],
									DLG_TEXT_RUM[2]);
			link.l2.go = "exit";
			break;
		}
		//квест шебеки —ин€€ ѕтица
		if (pchar.questTemp.BlueBird.City == npchar.city && pchar.questTemp.BlueBird == "returnMoney")
		{
			Dialog.Text = BlueBurd_setTradeShip();
			link.l1 = DLG_TEXT_RUM[3];
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple(DLG_TEXT_RUM[4],
									DLG_TEXT_RUM[5]);
			link.l2.go = "exit";
			//новый слух в другом городе
			pchar.questTemp.BlueBird.City = GetSharpCity();
			break;
		}
		//<<<<<-------- квестовые слухи горожан -----------------
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 3 )
        srum = SelectRumourEx("citizen", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(4)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(DLG_TEXT_RUM[6], DLG_TEXT_RUM[7]);
            posrep2 = DLG_TEXT_RUM[8];
            answ1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[9]+GetFullName(NPChar)+".",
                                 DLG_TEXT_RUM[10]);
            answ2 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[11],
                                 DLG_TEXT_RUM[12]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[13],
                                 DLG_TEXT_RUM[14]);
            answ4 = "";
        
        }
        else
        {
            posrep1 = DLG_TEXT_RUM[15];
            posrep2 = DLG_TEXT_RUM[16] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[17];
            answ1 = RandPhraseSimple(DLG_TEXT_RUM[18],
                                 RandSwear() + DLG_TEXT_RUM[19]);
            answ2 = RandPhraseSimple(DLG_TEXT_RUM[20],
                                 DLG_TEXT_RUM[21]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_RUM[22])+DLG_TEXT_RUM[23]);
            answ3 = RandPhraseSimple(DLG_TEXT_RUM[24],
                                 DLG_TEXT_RUM[25]);
            answ4 = "";
        
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
                                                srum+posrep1,
                                                srum+posrep2,
                                                RandPhraseSimple(DLG_TEXT_RUM[26],
                                                                    DLG_TEXT_RUM[27]),
                                                "block", 1, npchar, Dialog.CurrentNode);
		
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[28],
                                 DLG_TEXT_RUM[29]);
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		Dialog.Text = LinkRandPhrase(DLG_TEXT_RUM[30],DLG_TEXT_RUM[31],DLG_TEXT_RUM[32])+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[33],
                                 DLG_TEXT_RUM[34]);
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple(DLG_TEXT_RUM[35],
                                 DLG_TEXT_RUM[36]);
		link.l2.go = "exit_sit";
		if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && npchar.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
		{
			dialog.text = DLG_TEXT_RUM[37];
			link.l1 = DLG_TEXT_RUM[38];
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "3");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirstUsurer";
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && npchar.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
		{
			dialog.text = DLG_TEXT_RUM[39];
			link.l1 = DLG_TEXT_RUM[40];
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "5");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecondUsurer";
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && npchar.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
		{
			dialog.text = DLG_TEXT_RUM[41];
			link.l1 = DLG_TEXT_RUM[42];
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "7");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			pchar.questTemp.piratesLine = "PPL5Hunter_toThirdUsurer";
		}
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(4)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+DLG_TEXT_RUM[43],
                                                   strum+DLG_TEXT_RUM[44],
                                                    RandPhraseSimple(DLG_TEXT_RUM[45],
                                                                        DLG_TEXT_RUM[46]),
                                                                         "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + DLG_TEXT_RUM[47],DLG_TEXT_RUM[48]),
                                                pcharrepphrase(DLG_TEXT_RUM[49],
                                                                DLG_TEXT_RUM[50]),
                                                pcharrepphrase(RandSwear() +DLG_TEXT_RUM[51],DLG_TEXT_RUM[52]),
                                                pcharrepphrase(DLG_TEXT_RUM[53],
                                                                DLG_TEXT_RUM[54]),
                                                npchar, Dialog.CurrentNode);

			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_RUM[55],
													               DLG_TEXT_RUM[56]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase(DLG_TEXT_RUM[57],
													               DLG_TEXT_RUM[58]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+DLG_TEXT_RUM[59])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_RUM[60],
													               DLG_TEXT_RUM[61]),
													pcharrepphrase(DLG_TEXT_RUM[62],
													               DLG_TEXT_RUM[63])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_RUM[64],
													               DLG_TEXT_RUM[65]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase(DLG_TEXT_RUM[66],
													               DLG_TEXT_RUM[67]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_RUM[68] +GetFullName(pchar)+ DLG_TEXT_RUM[69],
													               DLG_TEXT_RUM[70]),
													pcharrepphrase(DLG_TEXT_RUM[71],
													               DLG_TEXT_RUM[72] + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[73],
                                     DLG_TEXT_RUM[74]);
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[75],
                                     DLG_TEXT_RUM[76]);
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06

                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase(DLG_TEXT_RUM[77],
                DLG_TEXT_RUM[78],
                DLG_TEXT_RUM[79]),
                DLG_TEXT_RUM[80],
                "", "", "block", 1, npchar, Dialog.CurrentNode);
             
    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[81],
                                         DLG_TEXT_RUM[82]), DLG_TEXT_RUM[83], DLG_TEXT_RUM[83], DLG_TEXT_RUM[83], npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_RUM[84], DLG_TEXT_RUM[85]),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat(DLG_TEXT_RUM[86], "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;
		
		case "rumours_tavern_yes":

			//------------- квестовые слухи тавернщика --------->>>>>>>>
			//пиратка, квест є3
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				Dialog.Text =  DLG_TEXT_RUM[87];
				link.l1 = DLG_TEXT_RUM[88];
				link.l1.go = "rumours_tavern";
				AddQuestRecord("Pir_Line_3_KillLoy", "14");		
				pchar.questTemp.piratesLine = "KillLoy_toCumana_2";
				break;
			}
			//<<<<<-------- квестовые слухи тавернщика -----------------
		
            string RumText = SelectRumourEx("tavern", NPChar); //fix
		    if ( RumText == NO_RUMOUR_TEXT[0] || RumText == NO_RUMOUR_TEXT[1]
                || RumText == NO_RUMOUR_TEXT[2] || RumText == NO_RUMOUR_TEXT[3] || RumText == NO_RUMOUR_TEXT[4] )//fix
            {

                Dialog.Text = NO_RUMOUR_TEXT[rand(3)]; //fix
                link.l1 = RandPhraseSimple(DLG_TEXT_RUM[89], DLG_TEXT_RUM[90]);

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);

                Dialog.Text = RumText;

    			link.l1 = RandPhraseSimple(DLG_TEXT_RUM[91], DLG_TEXT_RUM[92]);
    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;
            }

		break;

		case "rumours_tavern_no":
			Dialog.Text = DLG_TEXT_RUM[93];
            link.l1 = DLG_TEXT_RUM[94];
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase(DLG_TEXT_RUM[95],
                                     DLG_TEXT_RUM[96],DLG_TEXT_RUM[97]);
			link.l2.go = "Exit";
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[98],
										DLG_TEXT_RUM[99]);
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[100],
										DLG_TEXT_RUM[101]);
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[102], 
					DLG_TEXT_RUM[103]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[104],
										DLG_TEXT_RUM[105]);
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + DLG_TEXT_RUM[106],
										DLG_TEXT_RUM[107]);
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple(DLG_TEXT_RUM[108],
										DLG_TEXT_RUM[109]);
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[110], 
					DLG_TEXT_RUM[111]);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[112],
										DLG_TEXT_RUM[113]);
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[114],
										DLG_TEXT_RUM[115]);
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple(DLG_TEXT_RUM[116], DLG_TEXT_RUM[117]), 
					RandPhraseSimple(DLG_TEXT_RUM[118], DLG_TEXT_RUM[119]));
				Link.l1 = RandPhraseSimple(DLG_TEXT_RUM[120], DLG_TEXT_RUM[121]);
				Link.l1.go = "exit";			
			}
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		 редитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanForAll": //пересылка в финансы дл€ всех
			dialog.text = LinkRandPhrase(DLG_TEXT_RUM[122], DLG_TEXT_RUM[123], DLG_TEXT_RUM[124]);
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
                    dialog.text = LinkRandPhrase(DLG_TEXT_RUM[125] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[126] + GetFullName(npchar) + DLG_TEXT_RUM[127],
                             DLG_TEXT_RUM[128] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[129] + GetFullName(npchar) + DLG_TEXT_RUM[130],
                             DLG_TEXT_RUM[131] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[132] + GetFullName(npchar) + ".");
                    link.l1 = NPCharRepPhrase(pchar, DLG_TEXT_RUM[133], DLG_TEXT_RUM[134] + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "LoanFindCitizen_1";
				    NPChar.quest.LoanFindCitizenType = rand(2); // три типа
                    break;
                }
            }
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l2 = DLG_TEXT_RUM[135];
                link.l2.go = "TakeChest_2";
            }
			link.l9 = RandPhraseSimple(DLG_TEXT_RUM[136], DLG_TEXT_RUM[137]);
			link.l9.go = "exit";
		break;
		// вернуть долг ростовщику
		case "LoanFindCitizen_1":
            switch (sti(NPChar.quest.LoanFindCitizenType))
            {
                case 0 :
                    dialog.text = DLG_TEXT_RUM[138];
        			Link.l1 = DLG_TEXT_RUM[139] + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = DLG_TEXT_RUM[140];
        			Link.l2.go = "exit";
                break;
                
                case 1 :
                    dialog.text = DLG_TEXT_RUM[141];
                    Link.l1 = DLG_TEXT_RUM[142] + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + DLG_TEXT_RUM[143];
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = DLG_TEXT_RUM[144];
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
                
                case 2 :
                    dialog.text = DLG_TEXT_RUM[145];
                    Link.l1 = DLG_TEXT_RUM[146] + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + DLG_TEXT_RUM[147];
        			Link.l1.go = "LoanFindCitizen_1";
        			Link.l2 = DLG_TEXT_RUM[148];
        			Link.l2.go = "LoanFindCitizenType_2";
        			NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
                break;
			}
		break;

		case "LoanFindCitizenType_0":
            dialog.text = DLG_TEXT_RUM[149];
			Link.l1 = DLG_TEXT_RUM[150];
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, (sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent)));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog(DLG_TEXT_RUM[151]);
        	AddCharacterExpToSkill(pchar, "COMMERCE", 20);        	
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		
		case "LoanFindCitizenType_1_1":
            dialog.text = DLG_TEXT_RUM[152];
			Link.l1 = DLG_TEXT_RUM[153];
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog(DLG_TEXT_RUM[154]);
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;
		
		case "LoanFindCitizenType_1":
            dialog.text = DLG_TEXT_RUM[155];
			Link.l1 = DLG_TEXT_RUM[156];
			Link.l1.go = "fight";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog(DLG_TEXT_RUM[157]);
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;
		
		case "LoanFindCitizenType_2":
            pchar.GenQuest.Loan.FindCitizenTempMoney = 10 + rand(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent) - 1000));
            dialog.text = DLG_TEXT_RUM[158] + pchar.GenQuest.Loan.FindCitizenTempMoney + DLG_TEXT_RUM[159];
			Link.l1 = DLG_TEXT_RUM[160];
			Link.l1.go = "LoanFindCitizen_1";
			Link.l2 = DLG_TEXT_RUM[161];
			Link.l2.go = "LoanFindCitizenType_2_1";
			NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
		break;
		
		case "LoanFindCitizenType_2_1":
            dialog.text = DLG_TEXT_RUM[162];
			Link.l1 = DLG_TEXT_RUM[163];
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, sti(pchar.GenQuest.Loan.FindCitizenTempMoney));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog(DLG_TEXT_RUM[164]);
        	OfficersReaction("good");
        	ChangeCharacterReputation(pchar, 3);
        	AddCharacterExpToSkill(pchar, "Leadership", 20);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		//доставка сундуков
        case "TakeChest_2":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                if (CheckAttribute(pchar, "GenQuest.LoanChest.Money.Discount"))
				{
					Dialog.Text = DLG_TEXT_RUM[165] + pchar.GenQuest.LoanChest.Money.Discount + DLG_TEXT_RUM[166];
					link.l1 = DLG_TEXT_RUM[167];
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money)/100*sti(pchar.GenQuest.LoanChest.Money.Discount));
				}
				else
				{
					Dialog.Text = DLG_TEXT_RUM[168];
					link.l1 = DLG_TEXT_RUM[169];
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money));
				}
				ChangeCharacterReputation(pchar, 1);
                AddCharacterExpToSkill(pchar, "Sailing", 50);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
                OfficersReaction("good");
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));    			
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
    			AddQuestRecord("Gen_LoanTakeChest", "3");
                CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
                Dialog.Text = DLG_TEXT_RUM[170];
                link.l1 = DLG_TEXT_RUM[171];
    			link.l1.go = "TakeChest_3";
                link.l2 = DLG_TEXT_RUM[172];
    			link.l2.go = "exit";
			}
		break;

		case "TakeChest_3":
            Dialog.Text = DLG_TEXT_RUM[173];
            link.l1 = DLG_TEXT_RUM[174];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_RUM[175] + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Chest)*30000) + DLG_TEXT_RUM[176];
			link.l2.go = "TakeChest_4";
		break;

		case "TakeChest_4":
            Dialog.Text = DLG_TEXT_RUM[177];
            if (sti(pchar.Money) >= (sti(pchar.GenQuest.LoanChest.Chest)*30000))
            {
                link.l1 = DLG_TEXT_RUM[178];
    			link.l1.go = "TakeChest_5";
			}
			link.l2 = DLG_TEXT_RUM[179];
			link.l2.go = "exit";
		break;

		case "TakeChest_5":
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Sailing", 30);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			AddCharacterExpToSkill(pchar, "COMMERCE", 5);
            OfficersReaction("good");
            Dialog.Text = DLG_TEXT_RUM[180];
            link.l1 = DLG_TEXT_RUM[181];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1*(sti(pchar.GenQuest.LoanChest.Chest)*30000));
			DeleteAttribute(pchar, "GenQuest.LoanChest");
			DeleteAttribute(Pchar, "quest.LoanChestTimer");
			AddQuestRecord("Gen_LoanTakeChest", "4");
            CloseQuestHeader("Gen_LoanTakeChest");
		break; 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		 весты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple(DLG_TEXT_RUM[182], 
				DLG_TEXT_RUM[183]);
            link.l1 = RandPhraseSimple(DLG_TEXT_RUM[184], DLG_TEXT_RUM[185]);
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		 вест јсокольда, рендомные базары
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "AscoldTrader": //рендомный хоз€ин магаза
            dialog.Text = DLG_TEXT_RUM[186];
            if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = DLG_TEXT_RUM[187];
            	Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = DLG_TEXT_RUM[188];
            	Link.l1.go = "quests";
			}
		break;
        case "AscoldTrader_WasSeek":
            dialog.Text = DLG_TEXT_RUM[189];
            Link.l2 = DLG_TEXT_RUM[190];
            Link.l2.go = "AscoldTrader_1";
        break;		
		case "AscoldTrader_1":
        	dialog.text = DLG_TEXT_RUM[191];
    		link.l1 = DLG_TEXT_RUM[192];
    		link.l1.go = "AscoldTrader_2";
		break;
 		case "AscoldTrader_2":
        	dialog.text = DLG_TEXT_RUM[193]+
                          DLG_TEXT_RUM[194];
            if (Characters[GetCharacterIndex("Ascold")].quest.meeting == "0")
            {
                link.l1 = DLG_TEXT_RUM[195];
                link.l1.go = "AscoldTrader_4";
            }
            else
            {
                link.l1 = DLG_TEXT_RUM[196];
                link.l1.go = "AscoldTrader_3";
            }
		break;
 		case "AscoldTrader_3":
        	dialog.text = DLG_TEXT_RUM[197];
    		link.l1 = DLG_TEXT_RUM[198];
    		link.l1.go = "AscoldTrader_4";
		break;
 		case "AscoldTrader_4":
        	dialog.text = DLG_TEXT_RUM[199]+
                          DLG_TEXT_RUM[200]+
                          DLG_TEXT_RUM[201]+
                          DLG_TEXT_RUM[202];
    		link.l1 = DLG_TEXT_RUM[203];
    		link.l1.go = "AscoldTrader_5";
		break;
 		case "AscoldTrader_5":
        	dialog.text = DLG_TEXT_RUM[204];
    		link.l1 = DLG_TEXT_RUM[205];
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "GoToAscold";
    	    QuestSetCurrentNode("Ascold", "HaveRecomendation");
            AddQuestRecord("Ascold", "2");
		break;
 		case "AscoldTrader_6":
        	dialog.text = DLG_TEXT_RUM[206];
    		link.l1 = DLG_TEXT_RUM[207];
    		link.l1.go = "AscoldTrader_7";
		break;
 		case "AscoldTrader_7":
        	dialog.text = DLG_TEXT_RUM[208];
    		link.l1 = DLG_TEXT_RUM[209];
    		link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
        //==> ќбщий диалог дл€ хоз€ев верфи, квест јззи.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat(DLG_TEXT_RUM[210], "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
  			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_RUM[211], "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat(DLG_TEXT_RUM[212], "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat(DLG_TEXT_RUM[213] + npchar.name + ".", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[GetItemIndex("Azzy_bottle")].shown = 0; //даем возможность вскрыть лампу
		break;
		//==> ќбщий диалог дл€ церкви, квест јззи.
        case "GiveLamp":
			dialog.text = DLG_TEXT_RUM[214]+
                          DLG_TEXT_RUM[215];
			link.l1 = DLG_TEXT_RUM[216];
			link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 100);
            TakeItemFromCharacter(pchar, "Azzy_bottle");
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		√рабеж среди бела дн€, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_RUM[217], DLG_TEXT_RUM[218], DLG_TEXT_RUM[219]);
			link.l1 = LinkRandPhrase(DLG_TEXT_RUM[220], DLG_TEXT_RUM[221], DLG_TEXT_RUM[222]);
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		 вест получени€ —иней птицы
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RBlueBird":
			dialog.text = DLG_TEXT_RUM[223];
			link.l1 = DLG_TEXT_RUM[224];
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = DLG_TEXT_RUM[225];
			link.l1 = DLG_TEXT_RUM[226];
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = DLG_TEXT_RUM[227];
			link.l1 = DLG_TEXT_RUM[228];
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = DLG_TEXT_RUM[229];
			link.l1 = DLG_TEXT_RUM[230];
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = DLG_TEXT_RUM[231];
			link.l1 = DLG_TEXT_RUM[232];
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = DLG_TEXT_RUM[233];
			link.l1 = DLG_TEXT_RUM[234];
			link.l1.go = "RBlueBird_close";
			link.l2 = DLG_TEXT_RUM[235];
			link.l2.go = "RBlueBird_6";
		break;
		case "RBlueBird_6":
			dialog.text = DLG_TEXT_RUM[236];
			link.l1 = DLG_TEXT_RUM[237];
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = DLG_TEXT_RUM[238];
			link.l1 = DLG_TEXT_RUM[239];
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = DLG_TEXT_RUM[240] + GetAddress_Form(NPChar) + "." ;
			link.l1 = DLG_TEXT_RUM[241];
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = DLG_TEXT_RUM[242];
			link.l1 = DLG_TEXT_RUM[243];
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = DLG_TEXT_RUM[244];
			link.l1 = DLG_TEXT_RUM[245];
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = DLG_TEXT_RUM[246];
			link.l1 = DLG_TEXT_RUM[247];
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = DLG_TEXT_RUM[248];
			link.l1 = DLG_TEXT_RUM[249];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //запомним Id торговца
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
		break;


		case "RBlueBird_close":
			dialog.text = DLG_TEXT_RUM[250];
			link.l1 = DLG_TEXT_RUM[251];
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "over";
		break;
		case "RBlueBirdWon":
			dialog.text = DLG_TEXT_RUM[252];
			link.l1 = DLG_TEXT_RUM[253];
			link.l1.go = "RBlueBirdWon_1";
			int chComp;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "XebekVML1")
        		{	
					dialog.text = DLG_TEXT_RUM[254];
					link.l1 = DLG_TEXT_RUM[255];
					link.l1.go = "RBlueBirdWon_10";
					break;
                }
            }
		break;

		case "RBlueBirdWon_1":
			dialog.text = DLG_TEXT_RUM[256];
			link.l1 = DLG_TEXT_RUM[257];
			link.l1.go = "RBlueBirdWon_2";
			AddMoneyToCharacter(pchar, 50000);
		break;
		case "RBlueBirdWon_2":
			dialog.text = DLG_TEXT_RUM[258];
			link.l1 = DLG_TEXT_RUM[259];
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = DLG_TEXT_RUM[260];
			link.l1 = DLG_TEXT_RUM[261];
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = DLG_TEXT_RUM[262];
			link.l1 = DLG_TEXT_RUM[263];
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBirdWon_10":
			dialog.text = DLG_TEXT_RUM[264];
			link.l1 = DLG_TEXT_RUM[265];
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = DLG_TEXT_RUM[266];
			link.l1 = DLG_TEXT_RUM[267];
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = DLG_TEXT_RUM[268];
			link.l1 = DLG_TEXT_RUM[269];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			pchar.questTemp.BlueBird = "returnMoney";
			pchar.questTemp.BlueBird.City = GetSharpCity();
		break;

		case "RBlueBirdDieHard":
			dialog.text = DLG_TEXT_RUM[270];
			link.l1 = DLG_TEXT_RUM[271];
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = DLG_TEXT_RUM[272];
			link.l1 = DLG_TEXT_RUM[273];
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = DLG_TEXT_RUM[274];
			link.l1 = DLG_TEXT_RUM[275];
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = DLG_TEXT_RUM[276];
			link.l1 = DLG_TEXT_RUM[277];
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = DLG_TEXT_RUM[278];
			link.l1 = DLG_TEXT_RUM[279];
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = DLG_TEXT_RUM[280];
			link.l1 = DLG_TEXT_RUM[281];
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = DLG_TEXT_RUM[282];
			link.l1 = DLG_TEXT_RUM[283];
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = DLG_TEXT_RUM[284];
			link.l1 = DLG_TEXT_RUM[285];
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = DLG_TEXT_RUM[286];
			link.l1 = DLG_TEXT_RUM[287];
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = DLG_TEXT_RUM[288];
			link.l1 = DLG_TEXT_RUM[289];
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = DLG_TEXT_RUM[290];
			link.l1 = DLG_TEXT_RUM[291];
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = DLG_TEXT_RUM[292];
			link.l1 = DLG_TEXT_RUM[293];
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = DLG_TEXT_RUM[294];
			link.l1 = DLG_TEXT_RUM[295];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //закрываем квест
			AddMoneyToCharacter(pchar, 200000);
			AddQuestRecord("Xebeca_BlueBird", "14");
			CloseQuestHeader("Xebeca_BlueBird");
		break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Ћинейка острова погибших кораблей ISS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ISS_deposit":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_RUM[296], 
				DLG_TEXT_RUM[297] + GetAddress_Form(NPChar) + DLG_TEXT_RUM[298], 
				DLG_TEXT_RUM[299],
				DLG_TEXT_RUM[300], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_RUM[301], 
				DLG_TEXT_RUM[302],
				DLG_TEXT_RUM[303], 
				DLG_TEXT_RUM[304] + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "ISS_takeDeposit":
			dialog.text = DLG_TEXT_RUM[305] + GetAddress_Form(NPChar) + ".";
			link.l1 = DLG_TEXT_RUM[306];
			link.l1.go = "ISS_takeDeposit_1";
			AddMoneyToCharacter(pchar, 1000000);
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		case "ISS_takeDeposit_1":
			dialog.text = DLG_TEXT_RUM[307];
			link.l1 = DLG_TEXT_RUM[308];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "over"; //конец линейки √ѕ 
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		//механика арестовали, диалоги мужика
		case "MechanicIsPrison_man":
			dialog.text = DLG_TEXT_RUM[309];
			link.l1 = DLG_TEXT_RUM[310];
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_man_1":
			dialog.text = DLG_TEXT_RUM[311];
			link.l1 = DLG_TEXT_RUM[312];
			link.l1.go = "MechanicIsPrison_man_2";
		break;
		case "MechanicIsPrison_man_2":
			dialog.text = DLG_TEXT_RUM[313];
			link.l1 = DLG_TEXT_RUM[314];
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MechanicIsPrison_man_3":
			dialog.text = DLG_TEXT_RUM[315];
			link.l1 = DLG_TEXT_RUM[316];
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_man_4":
			dialog.text = DLG_TEXT_RUM[317];
			link.l1 = DLG_TEXT_RUM[318];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true; 
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		//механика арестовали, диалоги бабы
		case "MechanicIsPrison_woman":
			dialog.text = DLG_TEXT_RUM[319];
			link.l1 = DLG_TEXT_RUM[320];
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_woman_1":
			dialog.text = DLG_TEXT_RUM[321];
			link.l1 = DLG_TEXT_RUM[322];
			link.l1.go = "MechanicIsPrison_woman_2";
		break;
		case "MechanicIsPrison_woman_2":
			dialog.text = DLG_TEXT_RUM[323];
			link.l1 = DLG_TEXT_RUM[324];
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MMechanicIsPrison_woman_3":
			dialog.text = DLG_TEXT_RUM[325];
			link.l1 = DLG_TEXT_RUM[326];
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_woman_4":
			dialog.text = DLG_TEXT_RUM[327];
			link.l1 = DLG_TEXT_RUM[328];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true; 
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		case "SeekCrew_all":
			pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
			chrDisableReloadToLocation = true;
			float   locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			if (sti(pchar.questTemp.LSC.crew) >= 15)
			{
				DeleteAttribute(pchar, "questTemp.LSC.crew");
				pchar.questTemp.LSC = "MechanicIsArrest";
				pchar.questTemp.LSC.lastManId = npchar.index; //сюда запишем индекс
				NextDiag.TempNode = "MechanicIsPrison_" + npchar.sex;
				AddQuestRecord("ISS_MainLine", "63");
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				npchar.cityTape = "quest";  //чтобы не передвигалс€
				DeleteAttribute(npchar, "location.going"); //сн€ть метку на перемещение
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
				pchar.quest.LSC_afterArestMachanic.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSC_afterArestMachanic.win_condition.l1.location = pchar.location;
				pchar.quest.LSC_afterArestMachanic.function = "LSC_afterArestMachanic";
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "62");
				AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
				AddQuestUserData("ISS_MainLine", "Sex", NPCharSexPhrase(npchar, DLG_TEXT_RUM[329], DLG_TEXT_RUM[330]));
				AddQuestUserData("ISS_MainLine", "iCrew", FindRussianPeoplesString(15-sti(pchar.questTemp.LSC.crew), "Acc"));
				npchar.lifeDay = 0;
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);			
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
	}
}

