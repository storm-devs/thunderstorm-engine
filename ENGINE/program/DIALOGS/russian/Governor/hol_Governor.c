#include "TEXT\DIALOGS\Governor\hol_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_GUB[0], DLG_TEXT_GUB[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_GUB[2], DLG_TEXT_GUB[3]);
		    link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr2Letter_toCuracao")
			{
                dialog.text = DLG_TEXT_GUB[4];
                link.l1 = DLG_TEXT_GUB[5];
                link.l1.go = "Step_F2_1";			
			}
			if (pchar.questTemp.State == "Fr2Letter_NiceResult")
			{
                dialog.text = DLG_TEXT_GUB[6];
                link.l1 = DLG_TEXT_GUB[7];
                link.l1.go = "Step_F2_4";			
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				link.l1 = DLG_TEXT_GUB[8];
				link.l1.go = "TizerFind";
			}
		break;

		case "work_1":  // работа на благо короны - линейка нации
            // сюда вход только с патентом, проверка выше
            dialog.text = LinkRandPhrase(DLG_TEXT_GUB[9],
                                         DLG_TEXT_GUB[10],
                                         DLG_TEXT_GUB[11]);
            link.l1 = RandPhraseSimple(DLG_TEXT_GUB[12], DLG_TEXT_GUB[13]);
            link.l1.go = "exit";
            
        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase(DLG_TEXT_GUB[14],
                                                     DLG_TEXT_GUB[15],
                                                     DLG_TEXT_GUB[16]);
                        link.l1 = DLG_TEXT_GUB[17];
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = DLG_TEXT_GUB[18];
                                link.l1 = DLG_TEXT_GUB[19];
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = DLG_TEXT_GUB[20];
                                link.l1 = DLG_TEXT_GUB[21];
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
                                {
                                    dialog.text = DLG_TEXT_GUB[22];
                                    link.l1 = DLG_TEXT_GUB[23];
                                    link.l1.go = "Step_4_1";
                                }
                                else
                                {
                                    dialog.text = DLG_TEXT_GUB[24];
                                    link.l1 = DLG_TEXT_GUB[25];
                                    link.l1.go = "Step_4_1";
                                }
                            break;
                            case "5":
                                dialog.text = DLG_TEXT_GUB[26];
                                link.l1 = DLG_TEXT_GUB[27];
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = DLG_TEXT_GUB[28];
                                link.l1 = DLG_TEXT_GUB[29];
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = DLG_TEXT_GUB[30];
                                link.l1 = DLG_TEXT_GUB[31];
                                link.l1.go = "Step_7_1";
                            break;
                            case "8":
                                dialog.text = DLG_TEXT_GUB[32];
                                link.l1 = DLG_TEXT_GUB[33];
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SeekBible_toAaron";
                                AddQuestRecord("Hol_Line_8_SeekBible", "1");
                                SaveCurrentQuestDateParam("questTemp");
								sld = characterFromId("Chumakeiro");
								LAi_SetStayTypeNoGroup(sld);
                                ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "goto", "goto1");
                            break;
                            case "9":
                                dialog.text = DLG_TEXT_GUB[34];
                                link.l1 = DLG_TEXT_GUB[35];
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = DLG_TEXT_GUB[36] + pchar.name + DLG_TEXT_GUB[37];
                                link.l1 = DLG_TEXT_GUB[38];
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = DLG_TEXT_GUB[39];
                                link.l1 = DLG_TEXT_GUB[40];
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = DLG_TEXT_GUB[41];
                                link.l1 = DLG_TEXT_GUB[42];
                                link.l1.go = "Step_12_1";
                            break;
                        }
                    }
                break;

                case "":           // Квест №1, доставка главы янсенистов мистера Аарона.
                    dialog.text = DLG_TEXT_GUB[43]+
                                  DLG_TEXT_GUB[44]+
                                  DLG_TEXT_GUB[45];
                    link.l1 = DLG_TEXT_GUB[46];
                    link.l1.go = "Step_1_1";
                break;
                case "SeekChumakeiro_GoToVillemstad":
                    dialog.text = DLG_TEXT_GUB[47];
                    link.l1 = DLG_TEXT_GUB[48];
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "2";
                    pchar.questTemp.Waiting_time = "7";
                    CloseQuestHeader("Hol_Line_1_Chumakeiro");
					AddTitleNextRate(sti(NPChar.nation), 1);
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(pchar, "Pistol", 150);
					AddCharacterExpToSkill(pchar, "Grappling", 120);
					ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
					//слухи
					AddSimpleRumour(DLG_TEXT_GUB[49] + GetMainCharacterNameGen() + DLG_TEXT_GUB[50], HOLLAND, 5, 1);
                break;
                case "TakeFoodCuracao_toOrangeStore":
                    dialog.text = DLG_TEXT_GUB[51];
                    link.l1 = DLG_TEXT_GUB[52];
                    if (GetQuestPastDayParam("questTemp") > 60)
                    {
                        dialog.text = DLG_TEXT_GUB[53];
                        link.l1 = DLG_TEXT_GUB[54];
                    }
                    link.l1.go = "Step_2_5";
                break;
                case "WormEnglPlans_SurrenderWorkMorgan":
                    dialog.text = DLG_TEXT_GUB[55];
                    link.l1 = DLG_TEXT_GUB[56];
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_SaveOfficer":
                    dialog.text = DLG_TEXT_GUB[57];
                    link.l1 = DLG_TEXT_GUB[58];
                    link.l1.go = "Step_3_3";
                break;
                case "WormEnglPlans_GoodRusultWorm":
                    dialog.text = DLG_TEXT_GUB[59];
                    link.l1 = DLG_TEXT_GUB[60];
                    link.l1.go = "Step_3_7";
                break;
                case "DefenceOrange_LateRiseOrange":
                    dialog.text = DLG_TEXT_GUB[61];
                    link.l1 = DLG_TEXT_GUB[62];
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_DieHard":
                    dialog.text = DLG_TEXT_GUB[63];
                    link.l1 = DLG_TEXT_GUB[64];
                    link.l1.go = "Step_4_2";
                break;
                case "DefenceOrange_LandingDestroyed":
                    dialog.text = DLG_TEXT_GUB[65];
                    link.l1 = DLG_TEXT_GUB[66];
                    link.l1.go = "Step_4_4";
                break;
                case "DefenceOrange_SquadronDestroyed":
                    dialog.text = DLG_TEXT_GUB[67];
                    link.l1 = DLG_TEXT_GUB[68];
                    link.l1.go = "Step_4_5";
                break;
                case "ThreeFleutes_DieHard":
                    dialog.text = DLG_TEXT_GUB[69];
                    link.l1 = DLG_TEXT_GUB[70];
                    link.l1.go = "Step_5_3";
                break;
                case "ThreeFleutes_AllFleuts":
                    dialog.text = DLG_TEXT_GUB[71];
                    link.l1 = DLG_TEXT_GUB[72];
                    link.l1.go = "Step_5_4";
                break;
                case "ThreeFleutes_LostFleuts":
                    dialog.text = DLG_TEXT_GUB[73];
                    link.l1 = DLG_TEXT_GUB[74];
                    link.l1.go = "Step_5_9";
                break;
                case "RevengeMansfield_FromMorganWithResult":
                    dialog.text = DLG_TEXT_GUB[75];
                    link.l1 = DLG_TEXT_GUB[76];
                    link.l1.go = "Step_6_2";
                break;
                case "DelivLettTortuga_NotFoundLetter":
                    dialog.text = DLG_TEXT_GUB[77];
                    link.l1 = DLG_TEXT_GUB[78];
                    link.l1.go = "Step_7_2";
                break;
                case "DelivLettTortuga_LetterFound":
                    dialog.text = DLG_TEXT_GUB[79];
                    link.l1 = DLG_TEXT_GUB[80];
                    link.l1.go = "Step_7_8";
                break;
                case "DelivLettTortuga_WaitingNews":
                    if (GetQuestPastDayParam("questTemp") > 30)
                    {
                        dialog.text = DLG_TEXT_GUB[81];
                        link.l1 = DLG_TEXT_GUB[82];
                        link.l1.go = "Step_7_20";
                    }
                    else
                    {
                        dialog.text = DLG_TEXT_GUB[83];
                        link.l1 = DLG_TEXT_GUB[84];
                        link.l1.go = "exit";
                    }
                break;
                case "SeekBible_BadResult":
                    dialog.text = DLG_TEXT_GUB[85];
                    link.l1 = DLG_TEXT_GUB[86];
                    link.l1.go = "Step_8_1";
                break;
                case "SeekBible_GoodResult":
                    dialog.text = DLG_TEXT_GUB[87];
                    link.l1 = DLG_TEXT_GUB[88];
                    link.l1.go = "Step_8_2";
                break;
                case "TakeThreeShips_toAbordage":
                    dialog.text = DLG_TEXT_GUB[89];
                    tempQty = 0;
                    for (i=1; i<=COMPANION_MAX; i++)
                	{
                        chComp = GetCompanionIndex(pchar,i);
                        if(chComp != -1)
                		{
                			sld = GetCharacter(chComp);
                    		iShip = sti(sld.ship.type);
                    		iBaseType = sti(RealShips[iShip].basetype);
                            if (iBaseType == SHIP_MANOWAR)
                            {
                                tempQty++;
                                RemoveCharacterCompanion(pchar, sld);
                                AddPassenger(pchar, sld, false);
                                AddMoneyToCharacter(pchar, 50000);
                            }
                        }
                    }
                    if (tempQty == 0)
                    {
                        link.l1 = DLG_TEXT_GUB[90];
                        link.l1.go = "exit";
                    }
                    else
                    {
                        if (sti(pchar.questTemp.QtyShips) > tempQty)
                        {
                            if (tempQty > 1)
                            {
                                link.l1 = DLG_TEXT_GUB[91] + tempQty +  DLG_TEXT_GUB[92];
                            }
                            else
                            {
                                link.l1 = DLG_TEXT_GUB[93];
                            }
                            link.l1.go = "Step_9_5";
                            pchar.questTemp.QtyShips = sti(pchar.questTemp.QtyShips) - tempQty;
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "2");
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyTook", tempQty);
                            AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyElse", pchar.questTemp.QtyShips);
                        }
                        else
                        {
                            AddQuestRecord("Hol_Line_9_TakeThreeShips", "3");
                            link.l1 = DLG_TEXT_GUB[94];
                            link.l1.go = "Step_9_6";
                            DeleteAttribute(pchar, "questTemp.QtyShips");
                        }
                     }
                break;
                case "SpaAttackCuracao_GoodWork":
                    dialog.text = DLG_TEXT_GUB[95];
                    link.l1 = DLG_TEXT_GUB[96];
                    link.l1.go = "Step_10_3";
                break;
                case "SpaAttackSentMartin_Late":
                    dialog.text = DLG_TEXT_GUB[97];
                    link.l1 = DLG_TEXT_GUB[98];
                    link.l1.go = "Step_11_5";
                break;
                case "SpaAttackSentMartin_GoodWork":
                    dialog.text = DLG_TEXT_GUB[99];
                    link.l1 = DLG_TEXT_GUB[100];
                    link.l1.go = "Step_11_8";
                break;
                case "OccupyMaracaibo_toWeWon":
                    dialog.text = DLG_TEXT_GUB[101];
                    link.l1 = DLG_TEXT_GUB[102];
                    link.l1.go = "Step_12_3";
                break;
                case "QuestLineBreake":
                    dialog.text = DLG_TEXT_GUB[103];
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = DLG_TEXT_GUB[104];
                    link.l1 = DLG_TEXT_GUB[105];
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
            }
        break;
        //********************** Квест №1, доставка главы янсенистов мистера Аарона. ************************
        case "Step_1_1":
            dialog.text = DLG_TEXT_GUB[106]+
                          DLG_TEXT_GUB[107]+
                          DLG_TEXT_GUB[108]+
                          DLG_TEXT_GUB[109];
            link.l1 = DLG_TEXT_GUB[110];
            link.l1.go = "Step_1_2";
            link.l2 = DLG_TEXT_GUB[111];
            link.l2.go = "exit";
        break;
        case "Step_1_2":
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = HOLLAND;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "SeekChumakeiro_ToAaronHouse";
            sld = GetCharacter(NPC_GenerateCharacter("Chumakeiro", "usurer_4", "man", "man", 10, HOLLAND, -1, false));
        	sld.name 	= DLG_TEXT_GUB[112];
        	sld.lastname = DLG_TEXT_GUB[113];
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.greeting = "Gr_padre";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "goto", "goto1");
            AddQuestRecord("Hol_Line_1_Chumakeiro", "1");
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1 = "location";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1.location = "Marigo_houseF1";
            Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition = "SeekChumakeiro_intoMarigoHouse";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        //********************** Квест №2, закупка и доставка товара из форта Оранж. ************************
        case "Step_2_1":
            dialog.text = DLG_TEXT_GUB[114]+
                          DLG_TEXT_GUB[115]+
                          DLG_TEXT_GUB[116];
            link.l1 = DLG_TEXT_GUB[117];
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = DLG_TEXT_GUB[118];
            link.l1 = DLG_TEXT_GUB[119];
            link.l1.go = "Step_2_3";
        break;
        case "Step_2_3":
            dialog.text = DLG_TEXT_GUB[120]+
                          DLG_TEXT_GUB[121]+
                          DLG_TEXT_GUB[122];
            link.l1 = DLG_TEXT_GUB[123];
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = DLG_TEXT_GUB[124];
            link.l1 = DLG_TEXT_GUB[125];
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeFoodCuracao_toOrangeMayor";
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "1");
            ChangeItemDescribe("Trust", "itmdescr_Trust_HolLineQ2");
            GiveItem2Character(pchar,"Trust");
            AddMoneyToCharacter(pchar, 17700);
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.EbonyQtyElseNeed = 400;
            pchar.questTemp.CoffeeQtyElseNeed = 400;
            pchar.questTemp.MahoganyQtyElseNeed = 400;
            pchar.questTemp.SandalQtyElseNeed = 400;
        break;
        case "Step_2_5":
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = pchar.Ship.Cargo.Goods.Ebony;
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = pchar.Ship.Cargo.Goods.Coffee;
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = pchar.Ship.Cargo.Goods.Mahogany;
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = pchar.Ship.Cargo.Goods.Sandal;
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
                    if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = sti(pchar.questTemp.EbonyQty) + sti(sld.Ship.Cargo.Goods.Ebony);
                    if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = sti(pchar.questTemp.CoffeeQty) + sti(sld.Ship.Cargo.Goods.Coffee);
                    if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = sti(pchar.questTemp.MahoganyQty) + sti(sld.Ship.Cargo.Goods.Mahogany);
                    if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = sti(pchar.questTemp.SandalQty) + sti(sld.Ship.Cargo.Goods.Sandal);
                }
            }
            tempStr = DLG_TEXT_GUB[126];
            if (CheckAttribute(pchar, "questTemp.EbonyQty"))
            {
                if (sti(pchar.questTemp.EbonyQty > 0)) tempStr = tempStr + DLG_TEXT_GUB[127] + pchar.questTemp.EbonyQty + DLG_TEXT_GUB[128];
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQty"))
            {
                if (sti(pchar.questTemp.CoffeeQty > 0)) tempStr = tempStr + DLG_TEXT_GUB[129] + pchar.questTemp.CoffeeQty + DLG_TEXT_GUB[130];
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty > 0)) tempStr = tempStr + DLG_TEXT_GUB[131] + pchar.questTemp.MahoganyQty + DLG_TEXT_GUB[132];
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty > 0)) tempStr = tempStr + DLG_TEXT_GUB[133] + pchar.questTemp.SandalQty + DLG_TEXT_GUB[134];
            }
            dialog.text = DLG_TEXT_GUB[135];
            link.l1 = tempStr;
            link.l1.go = "Step_2_6";
            if (tempStr == DLG_TEXT_GUB[136])
            {
                link.l1 = DLG_TEXT_GUB[137];
                link.l1.go = "exit";
                DeleteAttribute(pchar, "questTemp.EbonyQty");
                DeleteAttribute(pchar, "questTemp.CoffeeQty");
                DeleteAttribute(pchar, "questTemp.MahoganyQty");
                DeleteAttribute(pchar, "questTemp.SandalQty");
            }
        break;
        case "Step_2_6":
            tempStr = DLG_TEXT_GUB[138];
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed"))
            {
                HolLine2_NullGoods();
                if (sti(pchar.questTemp.EbonyQty) >= sti(pchar.questTemp.EbonyQtyElseNeed))
                {
                    tempStr = tempStr + DLG_TEXT_GUB[139];
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_EBONY, sti(pchar.questTemp.EbonyQty)-sti(pchar.questTemp.EbonyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.EbonyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.EbonyQty > 0))
                    {
                        tempStr = tempStr + DLG_TEXT_GUB[140] + pchar.questTemp.EbonyQty + DLG_TEXT_GUB[141];
                        pchar.questTemp.EbonyQtyElseNeed = sti(pchar.questTemp.EbonyQtyElseNeed) - sti(pchar.questTemp.EbonyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed"))
            {
                if (sti(pchar.questTemp.CoffeeQty) >= sti(pchar.questTemp.CoffeeQtyElseNeed))
                {
                    tempStr = tempStr + DLG_TEXT_GUB[142];
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_COFFEE, sti(pchar.questTemp.CoffeeQty)-sti(pchar.questTemp.CoffeeQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.CoffeeQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.CoffeeQty > 0))
                    {
                        tempStr = tempStr + DLG_TEXT_GUB[143] + pchar.questTemp.CoffeeQty + DLG_TEXT_GUB[144];
                        pchar.questTemp.CoffeeQtyElseNeed = sti(pchar.questTemp.CoffeeQtyElseNeed) - sti(pchar.questTemp.CoffeeQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
            {
                if (sti(pchar.questTemp.MahoganyQty) >= sti(pchar.questTemp.MahoganyQtyElseNeed))
                {
                    tempStr = tempStr + DLG_TEXT_GUB[145];
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_MAHOGANY, sti(pchar.questTemp.MahoganyQty)-sti(pchar.questTemp.MahoganyQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.MahoganyQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.MahoganyQty > 0))
                    {
                        tempStr = tempStr + DLG_TEXT_GUB[146] + pchar.questTemp.MahoganyQty + DLG_TEXT_GUB[147];
                        pchar.questTemp.MahoganyQtyElseNeed = sti(pchar.questTemp.MahoganyQtyElseNeed) - sti(pchar.questTemp.MahoganyQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (sti(pchar.questTemp.SandalQty) >= sti(pchar.questTemp.SandalQtyElseNeed))
                {
                    tempStr = tempStr + DLG_TEXT_GUB[148];
                    HolLine2_NullGoods();
                    AddCharacterGoods(pchar, GOOD_SANDAL, sti(pchar.questTemp.SandalQty)-sti(pchar.questTemp.SandalQtyElseNeed));
                    DeleteAttribute(pchar, "questTemp.SandalQtyElseNeed");
                }
                else
                {
                    if (sti(pchar.questTemp.SandalQty > 0))
                    {
                        tempStr = tempStr + DLG_TEXT_GUB[149] + pchar.questTemp.SandalQty + DLG_TEXT_GUB[150];
                        pchar.questTemp.SandalQtyElseNeed = sti(pchar.questTemp.SandalQtyElseNeed) - sti(pchar.questTemp.SandalQty);
                        HolLine2_NullGoods();
                    }
                }
            }
            DeleteAttribute(pchar, "questTemp.EbonyQty");
            DeleteAttribute(pchar, "questTemp.CoffeeQty");
            DeleteAttribute(pchar, "questTemp.MahoganyQty");
            DeleteAttribute(pchar, "questTemp.SandalQty");
            dialog.text = tempStr;
            link.l1 = DLG_TEXT_GUB[151];
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            tempStr = "";
            if (!CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed") && !CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
            {
                if (GetQuestPastDayParam("questTemp") > 60)
                {
                    dialog.text = DLG_TEXT_GUB[152];
                    link.l1 = DLG_TEXT_GUB[153];
                    link.l1.go = "Step_2_8";
                }
                else
                {
                    dialog.text = DLG_TEXT_GUB[154];
                    link.l1 = DLG_TEXT_GUB[155];
                    link.l1.go = "Step_2_11";
                }
            }
            else
            {
                dialog.text = DLG_TEXT_GUB[156];
                link.l1 = DLG_TEXT_GUB[157];
                link.l1.go = "exit";
                AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "3");
                if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", pchar.questTemp.EbonyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", DLG_TEXT_GUB[158]);
                if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", pchar.questTemp.CoffeeQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", DLG_TEXT_GUB[159]);
                if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", pchar.questTemp.MahoganyQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", DLG_TEXT_GUB[160]);
                if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", pchar.questTemp.SandalQtyElseNeed);
                else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", DLG_TEXT_GUB[161]);
            }
        break;
        case "Step_2_8":
            dialog.text = DLG_TEXT_GUB[162]+
                          DLG_TEXT_GUB[163]+
                          DLG_TEXT_GUB[164];
            link.l1 = DLG_TEXT_GUB[165];
            link.l1.go = "Step_2_9";
        break;
        case "Step_2_9":
            dialog.text = DLG_TEXT_GUB[166];
            link.l1 = DLG_TEXT_GUB[167];
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 15000);
            pchar.questTemp.Waiting_time = "30";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[168] + GetFullName(pchar) + DLG_TEXT_GUB[169], HOLLAND, 5, 1);
        break;
        case "Step_2_10":
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "4");
            CloseQuestHeader("Hol_Line_2_TakeFoodCuracao");
			DeleteAttribute(pchar, "GenQuest.HL2_AgainDiscount");  //сносим дисконтные цены
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //восстанавливаем старые цены и кол-во
        	pchar.GenQuest.StoreGoods.HL2_QtyPriceIsBack = true;
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_2_11":
            dialog.text = DLG_TEXT_GUB[170];
            link.l1 = DLG_TEXT_GUB[171];
            link.l1.go = "Step_2_12";
        break;
        case "Step_2_12":
            dialog.text = DLG_TEXT_GUB[172];
            link.l1 = DLG_TEXT_GUB[173];
            link.l1.go = "Step_2_10";
            AddMoneyToCharacter(pchar, 75000);
            pchar.questTemp.Waiting_time = "2";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[174] + GetFullName(pchar) + DLG_TEXT_GUB[175], HOLLAND, 5, 1);
        break;
        //********************** Квест №3, Узнать о планах англичан в связи с торговой войной ************************
        case "Step_3_1":
            dialog.text = DLG_TEXT_GUB[176]+
                          DLG_TEXT_GUB[177]+
                          DLG_TEXT_GUB[178];
            link.l1 = DLG_TEXT_GUB[179];
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = DLG_TEXT_GUB[180];
            link.l1 = DLG_TEXT_GUB[181];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "WormEnglPlans_toMansfield";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ3");
            GiveItem2Character(pchar,"letter_1");
            QuestSetCurrentNode("Edward Mansfield", "HolLine3_WormEngPlans");
        break;
        case "Step_3_3":
            dialog.text = DLG_TEXT_GUB[182];
            link.l1 = DLG_TEXT_GUB[183];
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = DLG_TEXT_GUB[184];
            link.l1 = DLG_TEXT_GUB[185];
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = DLG_TEXT_GUB[186];
            link.l1 = DLG_TEXT_GUB[187];
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = DLG_TEXT_GUB[188];
            link.l1 = DLG_TEXT_GUB[189];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "5");
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[190] + GetFullName(pchar) + DLG_TEXT_GUB[191], HOLLAND, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = DLG_TEXT_GUB[192];
            link.l1 = DLG_TEXT_GUB[193];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "3";
            pchar.questTemp.GoodWormRusult = true;
            AddMoneyToCharacter(pchar, 50000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[194] + GetFullName(pchar) + DLG_TEXT_GUB[195], HOLLAND, 5, 1);
        break;
        //********************** Квест №4, Защитить форт Оранж ************************
        case "Step_4_1":
            dialog.text = DLG_TEXT_GUB[196];
            if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
            {
                link.l1 = DLG_TEXT_GUB[197];
            }
            else
            {
                link.l1 = DLG_TEXT_GUB[198];
            }
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.GoodWormRusult");
            AddQuestRecord("Hol_Line_4_DefenceOrange", "1");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DefenceOrange_toFortOrange";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1 = "location";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1.location = "Jamaica";
            Pchar.quest.DefenceOrange_FightNearJamaica.win_condition = "DefenceOrange_FightNearJamaica";
			locations[FindLocation("Shore35")].DisableEncounters = true;
        break;
        case "Step_4_2":
            dialog.text = DLG_TEXT_GUB[199];
            link.l1 = DLG_TEXT_GUB[200];
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = DLG_TEXT_GUB[201];
            link.l1 = DLG_TEXT_GUB[202];
            link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернем
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[203], HOLLAND, 5, 1);
        break;
        case "Step_4_4":
            dialog.text = DLG_TEXT_GUB[204];
            link.l1 = DLG_TEXT_GUB[205];
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 100000);
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "5";
            //==> на всякий случай дублируем снятие восторгов.
            QuestSetCurrentNode("FortOrange_Mayor", "First time");
            QuestSetCurrentNode("FortOrange_waitress", "First time");
            QuestSetCurrentNode("FortOrange_tavernkeeper", "First time");
            QuestSetCurrentNode("FortOrange_trader", "First time");
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернем
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[206], HOLLAND, 5, 1);
        break;
        case "Step_4_5":
            dialog.text = DLG_TEXT_GUB[207];
            link.l1 = DLG_TEXT_GUB[208];
            link.l1.go = "Step_4_6";
        break;
        case "Step_4_6":
            dialog.text = DLG_TEXT_GUB[209];
            link.l1 = DLG_TEXT_GUB[210];
            link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернем
            CloseQuestHeader("Hol_Line_4_DefenceOrange");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "15";
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			Pchar.quest.DefenceOrange_FightInShore.over = "yes";
			Pchar.quest.DefenceOrange_FightInExitTown.over = "yes";
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[211], HOLLAND, 5, 1);
        break;		
		
		//********************** Квест №5, Сопроводить три флейта к Мэнсфилду ************************
        case "Step_5_1":
            dialog.text = DLG_TEXT_GUB[212];
            link.l1 = DLG_TEXT_GUB[213];
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = DLG_TEXT_GUB[214];
            link.l1 = DLG_TEXT_GUB[215];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_5_ThreeFleutes", "1");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "ThreeFleutes_toPortMan";
        break;
        case "Step_5_3":
            dialog.text = DLG_TEXT_GUB[216];
            link.l1 = DLG_TEXT_GUB[217];
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "100";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[218], HOLLAND, 5, 1);
        break;

        case "Step_5_4":
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);     
			for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
					sld = GetCharacter(chComp);
					iShip = sti(sld.ship.type);
                    iBaseType = sti(RealShips[iShip].basetype); 
                    if (iBaseType == SHIP_FLEUT) tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food); //считаем только у флейтов
                }
            }
            tempQty = tempQty / 10; //вес от кол-ва
            dialog.text = DLG_TEXT_GUB[219];
            if (tempQty >= 7000)
            {
                link.l1 = DLG_TEXT_GUB[220];
                link.l1.go = "Step_5_5";
            }
            else
            {
                link.l1 = DLG_TEXT_GUB[221] + tempQty + DLG_TEXT_GUB[222];
                link.l1.go = "Step_5_8";
            }
        break;
        case "Step_5_5":
            dialog.text = DLG_TEXT_GUB[223];
            link.l1 = DLG_TEXT_GUB[224];
            link.l1.go = "Step_5_6";
            tempQty = sti(pchar.Ship.Cargo.Goods.Food);
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
        			tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food);
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = tempQty - 70000; //в пачке - 10 шт.
            AddMoneyToCharacter(pchar, 60000);
            pchar.questTemp.Waiting_time = "2";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
        break;
        case "Step_5_6":
            dialog.text = DLG_TEXT_GUB[225];
            link.l1 = DLG_TEXT_GUB[226];
            link.l1.go = "Step_5_7";
        break;
        case "Step_5_7":
            dialog.text = DLG_TEXT_GUB[227];
            link.l1 = DLG_TEXT_GUB[228];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
        break;
        case "Step_5_8":
            if (tempQty > 4000)
            {
                dialog.text = DLG_TEXT_GUB[229];
                link.l1 = DLG_TEXT_GUB[230];
                AddMoneyToCharacter(pchar, 20000);
				AddTitleNextRate(sti(NPChar.nation), 3);
            }
            else
            {
                dialog.text = DLG_TEXT_GUB[231];
                link.l1 = DLG_TEXT_GUB[232];
            }
            link.l1.go = "Step_5_6";
            for (i=1; i<=3; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            pchar.Ship.Cargo.Goods.Food = 0;
            pchar.questTemp.Waiting_time = "7";
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
        break;
        case "Step_5_9":
            dialog.text = DLG_TEXT_GUB[233];
            link.l1 = DLG_TEXT_GUB[234];
            link.l1.go = "Step_5_10";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
            for (i=1; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar,i);
                if(chComp != -1)
        		{
        			sld = GetCharacter(chComp);
        			tempStr = sld.id;
                    if (findsubstr(tempStr, "Captain_", 0) != -1)
                    {
                        RemoveCharacterCompanion(pchar, sld);
                        sld.LifeDay = 0;
                    }
                }
            }
        break;
        case "Step_5_10":
            dialog.text = DLG_TEXT_GUB[235];
            link.l1 = DLG_TEXT_GUB[236];
            link.l1.go = "Step_5_11";
        break;
        case "Step_5_11":
            dialog.text = DLG_TEXT_GUB[237];
            link.l1 = DLG_TEXT_GUB[238];
            link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_5_ThreeFleutes");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[239], HOLLAND, 5, 1);
		break;
        //********************** Квест №6, узнать о планах мщения за Мэнсфилда ************************
        case "Step_6_1":
            dialog.text = DLG_TEXT_GUB[240]+
                          DLG_TEXT_GUB[241]+
                          DLG_TEXT_GUB[242];
            link.l1 = DLG_TEXT_GUB[243];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "1");
            pchar.questTemp.State = "RevengeMansfield_toMorgan";
            QuestSetCurrentNode("Henry Morgan", "HolLine6_fromStuvesant");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_6_2":
            dialog.text = DLG_TEXT_GUB[244];
            link.l1 = DLG_TEXT_GUB[245];
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = DLG_TEXT_GUB[246];
            link.l1 = DLG_TEXT_GUB[247];
            link.l1.go = "Step_6_4";
        break;
        case "Step_6_4":
            dialog.text = DLG_TEXT_GUB[248];
            link.l1 = DLG_TEXT_GUB[249];
            link.l1.go = "Step_6_5";
        break;
        case "Step_6_5":
            dialog.text = DLG_TEXT_GUB[250];
            link.l1 = DLG_TEXT_GUB[251];
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 20000);
            CloseQuestHeader("Hol_Line_6_RevengeMansfield");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "4";
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[252], HOLLAND, 5, 1);
        break;
        //********************** Квест №7, Доставка письма д'Ожерону ************************
        case "Step_7_1":
            dialog.text = DLG_TEXT_GUB[253];
            link.l1 = DLG_TEXT_GUB[254];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "1");
            pchar.questTemp.State = "DelivLettTortuga_toDOjeron";
            SaveCurrentQuestDateParam("questTemp");
            ChangeItemDescribe("letter_2", "itmdescr_letter_2_HolLineQ7");
            GiveItem2Character(pchar,"letter_2");
        break;
        case "Step_7_2":
            dialog.text = DLG_TEXT_GUB[255];
            link.l1 = DLG_TEXT_GUB[256];
            link.l1.go = "Step_7_3";
        break;
        case "Step_7_3":
            dialog.text = DLG_TEXT_GUB[257];
            tempStr = DLG_TEXT_GUB[258];
            switch (pchar.questTemp.State.KingResult)
            {
                case "BrigNotFound":
                    tempStr = tempStr + DLG_TEXT_GUB[259];
                break;
                case "BrigSunk":
                    tempStr = tempStr + DLG_TEXT_GUB[260];
                break;
                case "BrigAborded":
                    tempStr = tempStr + DLG_TEXT_GUB[261];
                break;
                case "WarshipSunk":
                    tempStr = tempStr + DLG_TEXT_GUB[262];
                break;
            }
            link.l1 = tempStr;
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = DLG_TEXT_GUB[263];
            link.l1 = DLG_TEXT_GUB[264];
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = DLG_TEXT_GUB[265];
            link.l1 = DLG_TEXT_GUB[266];
            link.l1.go = "Step_7_6";
        break;
        case "Step_7_6":
            dialog.text = DLG_TEXT_GUB[267];
            link.l1 = DLG_TEXT_GUB[268];
            link.l1.go = "Step_7_7";
        break;
        case "Step_7_7":
            dialog.text = DLG_TEXT_GUB[269];
            link.l1 = DLG_TEXT_GUB[270];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "DelivLettTortuga_WaitingNews";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            BackItemDescribe("letter_1");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[271] + GetFullName(pchar) + DLG_TEXT_GUB[272], HOLLAND, 5, 1);
        break;
        
        case "Step_7_20":
            dialog.text = DLG_TEXT_GUB[273];
            link.l1 = DLG_TEXT_GUB[274];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
        break;

        case "Step_7_8":
            dialog.text = DLG_TEXT_GUB[275];
            link.l1 = DLG_TEXT_GUB[276];
            link.l1.go = "Step_7_9";
        break;
        case "Step_7_9":
            dialog.text = DLG_TEXT_GUB[277];
            link.l1 = DLG_TEXT_GUB[278];
            link.l1.go = "Step_7_10";
        break;
        case "Step_7_10":
            dialog.text = DLG_TEXT_GUB[279];
            link.l1 = DLG_TEXT_GUB[280];
            link.l1.go = "Step_7_11";
        break;
        case "Step_7_11":
            dialog.text = DLG_TEXT_GUB[281];
            link.l1 = DLG_TEXT_GUB[282];
            link.l1.go = "Step_7_12";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_7_12":
            dialog.text = DLG_TEXT_GUB[283];
            link.l1 = DLG_TEXT_GUB[284];
            link.l1.go = "Step_7_13";
        break;
        case "Step_7_13":
            dialog.text = DLG_TEXT_GUB[285];
            link.l1 = DLG_TEXT_GUB[286];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "10";
            DeleteAttribute(pchar, "questTemp.State.KingResult");
            AddMoneyToCharacter(pchar, 150000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[287] + GetFullName(pchar) + DLG_TEXT_GUB[288], HOLLAND, 5, 1);
        break;
        //********************** Квест №8, Поиски Евангелие для Аарона ************************
        case "Step_8_1":
            dialog.text = DLG_TEXT_GUB[289];
            link.l1 = DLG_TEXT_GUB[290];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[291] + GetFullName(pchar) + DLG_TEXT_GUB[292], HOLLAND, 5, 1);
		break;
        case "Step_8_2":
            dialog.text = DLG_TEXT_GUB[293];
            link.l1 = DLG_TEXT_GUB[294];
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = DLG_TEXT_GUB[295];
            link.l1 = DLG_TEXT_GUB[296];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_8_SeekBible");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "2";
			TakeItemFromCharacter(pchar, "LegransMap");
			ChangeCharacterReputation(pchar, 2);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[297] + GetFullName(pchar) + DLG_TEXT_GUB[298], HOLLAND, 5, 1);
        break;
        //********************** Квест №9, Захват линейных кораблей. ************************
        case "Step_9_1":
            dialog.text = DLG_TEXT_GUB[299];
            link.l1 = DLG_TEXT_GUB[300];
            link.l1.go = "Step_9_2";
        break;
        case "Step_9_2":
            dialog.text = DLG_TEXT_GUB[301];
            link.l1 = DLG_TEXT_GUB[302];
            link.l1.go = "Step_9_3";
        break;
        case "Step_9_3":
            dialog.text = DLG_TEXT_GUB[303];
            link.l1 = DLG_TEXT_GUB[304];
            link.l1.go = "Step_9_4";
        break;
        case "Step_9_4":
            dialog.text = DLG_TEXT_GUB[305];
            link.l1 = DLG_TEXT_GUB[306];
            link.l1.go = "exit";
            pchar.questTemp.QtyShips = 4;
            pchar.questTemp.State = "TakeThreeShips_toAbordage";
            AddQuestRecord("Hol_Line_9_TakeThreeShips", "1");
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_9_5":
            if (sti(pchar.questTemp.QtyShips)>1)
            {
                dialog.text = DLG_TEXT_GUB[307] + pchar.questTemp.QtyShips + DLG_TEXT_GUB[308];
            }
            else
            {
                dialog.text = DLG_TEXT_GUB[309];
            }
            link.l1 = DLG_TEXT_GUB[310];
            link.l1.go = "exit";
        break;
        case "Step_9_6":
            dialog.text = DLG_TEXT_GUB[311];
            link.l1 = DLG_TEXT_GUB[312];
            link.l1.go = "Step_9_7";
        break;
        case "Step_9_7":
            dialog.text = DLG_TEXT_GUB[313];
            link.l1 = DLG_TEXT_GUB[314];
            link.l1.go = "Step_9_8";
        break;
        case "Step_9_8":
            dialog.text = DLG_TEXT_GUB[315];
            link.l1 = DLG_TEXT_GUB[316];
            link.l1.go = "Step_9_9";
        break;
        case "Step_9_9":
            dialog.text = DLG_TEXT_GUB[317];
            link.l1 = DLG_TEXT_GUB[318];
            link.l1.go = "Step_9_10";
        break;
        case "Step_9_10":
            dialog.text = DLG_TEXT_GUB[319];
            link.l1 = DLG_TEXT_GUB[320];
            link.l1.go = "Step_9_11";
        break;
        case "Step_9_11":
            dialog.text = DLG_TEXT_GUB[321];
            link.l1 = DLG_TEXT_GUB[322];
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            CloseQuestHeader("Hol_Line_9_TakeThreeShips");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[323], HOLLAND, 5, 1);
        break;
        //********************** Квест №10, Оборона Кюрасао. ************************
        case "Step_10_1":
            dialog.text = DLG_TEXT_GUB[324]+
                          DLG_TEXT_GUB[325];
            link.l1 = DLG_TEXT_GUB[326];
            link.l1.go = "Step_10_2";
        break;
        case "Step_10_2":
            dialog.text = DLG_TEXT_GUB[327];
            link.l1 = DLG_TEXT_GUB[328];
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackCuracao_toBattle";
            AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "1");
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1.location = "Curacao";
            Pchar.quest.SpaAttackCuracao_Battle.win_condition = "SpaAttackCuracao_Battle";
        break;
        case "Step_10_3":
            dialog.text = DLG_TEXT_GUB[329];
            link.l1 = DLG_TEXT_GUB[330];
            link.l1.go = "Step_10_4";
        break;
        case "Step_10_4":
            dialog.text = DLG_TEXT_GUB[331];
            link.l1 = DLG_TEXT_GUB[332];
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
            AddMoneyToCharacter(pchar, 200000);
            CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "3";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[333], HOLLAND, 5, 5);
        break;
        //********************** Квест №11, Спасение Мариго от испанцев. ************************
        case "Step_11_1":
            dialog.text = DLG_TEXT_GUB[334];
            link.l1 = DLG_TEXT_GUB[335];
            link.l1.go = "Step_11_2";
        break;
        case "Step_11_2":
            dialog.text = DLG_TEXT_GUB[336]+
                          DLG_TEXT_GUB[337]+
                          DLG_TEXT_GUB[338];
            link.l1 = DLG_TEXT_GUB[339];
            link.l1.go = "Step_11_3";
        break;
        case "Step_11_3":
            dialog.text = DLG_TEXT_GUB[340];
            link.l1 = DLG_TEXT_GUB[341];
            link.l1.go = "Step_11_4";
        break;
        case "Step_11_4":
            dialog.text = DLG_TEXT_GUB[342];
            link.l1 = DLG_TEXT_GUB[343];
            link.l1.go = "exit";
            pchar.questTemp.State = "SpaAttackSentMartin_toBattle";
            AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "1");
            SaveCurrentQuestDateParam("questTemp");
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1 = "location";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1.location = "SentMartin";
            Pchar.quest.SpaAttackSentMartin_Battle.win_condition = "SpaAttackSentMartin_Battle";
            SetTimerCondition("SpaAttackSentMartin_YouLate", 0, 0, 10, false);
        break;
        case "Step_11_5":
            dialog.text = DLG_TEXT_GUB[344];
            link.l1 = DLG_TEXT_GUB[345];
            link.l1.go = "Step_11_6";
        break;
        case "Step_11_6":
            dialog.text = DLG_TEXT_GUB[346];
            link.l1 = DLG_TEXT_GUB[347];
            link.l1.go = "Step_11_7";
        break;
        case "Step_11_7":
            dialog.text = DLG_TEXT_GUB[348];
            link.l1 = DLG_TEXT_GUB[349];
            link.l1.go = "exit";
            CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
        break;
        case "Step_11_8":
            dialog.text = DLG_TEXT_GUB[350];
            link.l1 = DLG_TEXT_GUB[351];
            link.l1.go = "Step_11_9";
        break;
        case "Step_11_9":
            dialog.text = DLG_TEXT_GUB[352];
            link.l1 = DLG_TEXT_GUB[353];
            link.l1.go = "Step_11_10";
            AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[354], HOLLAND, 5, 1);
        break;
        case "Step_11_10":
            dialog.text = DLG_TEXT_GUB[355];
            link.l1 = DLG_TEXT_GUB[356];
            link.l1.go = "Step_11_7";
        break;
        //********************** Квест №12, Захват Венесуэллы. ************************
        case "Step_12_1":
            dialog.text = DLG_TEXT_GUB[357];
            link.l1 = DLG_TEXT_GUB[358];
            link.l1.go = "Step_12_2";
        break;
        case "Step_12_2":
            dialog.text = DLG_TEXT_GUB[359];
            link.l1 = DLG_TEXT_GUB[360];
            link.l1.go = "exit";
            pchar.questTemp.State = "OccupyMaracaibo_toFight";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "1");
            SaveCurrentQuestDateParam("questTemp");
			characters[GetCharacterIndex("Maracaibo_Mayor")].dialog.captureNode = "HolLine12Quest_Occupy"; //капитулянтская нода мэра
        break;
        case "Step_12_3":
            dialog.text = DLG_TEXT_GUB[361]+
                          DLG_TEXT_GUB[362];
            link.l1 = DLG_TEXT_GUB[363];
            link.l1.go = "Step_12_4";
        break;
        case "Step_12_4":
            dialog.text = DLG_TEXT_GUB[364];
            link.l1 = DLG_TEXT_GUB[365];
            link.l1.go = "Step_12_5";
            AddMoneyToCharacter(pchar, 300000);
        break;
        case "Step_12_5":
            dialog.text = DLG_TEXT_GUB[366];
            link.l1 = DLG_TEXT_GUB[367];
            link.l1.go = "Step_12_6";
        break;
        case "Step_12_6":
            dialog.text = DLG_TEXT_GUB[368];
            link.l1 = DLG_TEXT_GUB[369];
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			CloseQuestHeader("Hol_Line_12_OccupyMaracaibo");
			bWorldAlivePause   = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[370], HOLLAND, 5, 1);
        break;

        //********************** Французская линейка. Квест №2, доставка письма д'Ожерона. ************************
        case "Step_F2_1":
            dialog.text = DLG_TEXT_GUB[371];
            link.l1 = DLG_TEXT_GUB[372];
            link.l1.go = "Step_F2_2";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_F2_2":
            dialog.text = DLG_TEXT_GUB[373];
            link.l1 = DLG_TEXT_GUB[374];
            link.l1.go = "Step_F2_3";
        break;
        case "Step_F2_3":
			pchar.questTemp.State = "Fr2Letter_Arrest";
			for (i=1; i<=3; i++)
			{
				tempStr = "sold_hol_"+i;
				if (i==3) tempStr = "off_hol_1";
				sld = GetCharacter(NPC_GenerateCharacter("Guard_"+i, tempStr, "man", "man", 30, HOLLAND, 0, true));
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 30, 70, 60, "blade34", "pistol2", 70);
         		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorType(sld);
			}
			LAi_SetActorType(pchar);
            LAi_SetActorType(sld);
            SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		    LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
			DialogExit();
        break;
 		case "Step_F2_4":
    		dialog.text =  NPCStringReactionRepeat(DLG_TEXT_GUB[375],
            DLG_TEXT_GUB[376], DLG_TEXT_GUB[377], DLG_TEXT_GUB[378], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_GUB[379], DLG_TEXT_GUB[380], DLG_TEXT_GUB[381], DLG_TEXT_GUB[382], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_F2_5", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
        case "Step_F2_5":
            dialog.text = DLG_TEXT_GUB[383];
            link.l1 = DLG_TEXT_GUB[384];
            link.l1.go = "Step_F2_6";
        break;
        case "Step_F2_6":
            dialog.text = DLG_TEXT_GUB[385];
            link.l1 = DLG_TEXT_GUB[386];
            link.l1.go = "Step_F2_7";
        break;
        case "Step_F2_7":
            dialog.text = DLG_TEXT_GUB[387];
            link.l1 = DLG_TEXT_GUB[388];
            link.l1.go = "Step_F2_8";
        break;
        case "Step_F2_8":
            dialog.text = DLG_TEXT_GUB[389];
            link.l1 = DLG_TEXT_GUB[390];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("Fra_Line_2_DelivLetter", "6");
        break;
		// --------------------- линейка ГПК, вопрос о Тизере ---------------------
		case "TizerFind":
			dialog.text = DLG_TEXT_GUB[391];
			link.l1 = DLG_TEXT_GUB[392];
			link.l1.go = "TizerFind_1";
		break;
		case "TizerFind_1":
			dialog.text = DLG_TEXT_GUB[393];
			link.l1 = DLG_TEXT_GUB[394];
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = DLG_TEXT_GUB[395];
			link.l1 = DLG_TEXT_GUB[396];
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = DLG_TEXT_GUB[397];
			link.l1 = DLG_TEXT_GUB[398];
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = DLG_TEXT_GUB[399];
			link.l1 = DLG_TEXT_GUB[400];
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = DLG_TEXT_GUB[401];
			link.l1 = DLG_TEXT_GUB[402];
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = DLG_TEXT_GUB[403];
			link.l1 = DLG_TEXT_GUB[404];
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = DLG_TEXT_GUB[405];
			link.l1 = DLG_TEXT_GUB[406];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toLicencer";
			AddQuestRecord("ISS_PoorsMurder", "9");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
