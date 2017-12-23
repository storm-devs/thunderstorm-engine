#include "TEXT\DIALOGS\Governor\spa_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_GUB[0], DLG_TEXT_GUB[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_GUB[2], DLG_TEXT_GUB[3]);
		    link.l1.go = "exit";
		break;

		case "work_1":  // работа на благо короны - линейка нации
            // сюда вход только с патентом, проверка выше
            dialog.text = LinkRandPhrase(DLG_TEXT_GUB[4],
                                         DLG_TEXT_GUB[5],
                                         DLG_TEXT_GUB[6]);
            link.l1 = RandPhraseSimple(DLG_TEXT_GUB[7], DLG_TEXT_GUB[8]);
            link.l1.go = "exit";

        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
                case "empty":   // Нет взятых квестов
                    if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
                    {
                        dialog.text = LinkRandPhrase(DLG_TEXT_GUB[9],
                                                     DLG_TEXT_GUB[10],
                                                     DLG_TEXT_GUB[11]);
                        link.l1 = DLG_TEXT_GUB[12];
                        link.l1.go = "exit";
                    }
                    else
                    {
						switch(pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
                        {
                            case "2":
                                dialog.text = DLG_TEXT_GUB[13] + pchar.name + DLG_TEXT_GUB[14];
                                link.l1 = DLG_TEXT_GUB[15];
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":
                                dialog.text = DLG_TEXT_GUB[16];
                                link.l1 = DLG_TEXT_GUB[17];
                                link.l1.go = "Step_3_1";
                            break;
                            case "4":
                                dialog.text = DLG_TEXT_GUB[18];
                                link.l1 = DLG_TEXT_GUB[19];
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = DLG_TEXT_GUB[20];
                                link.l1 = DLG_TEXT_GUB[21];
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = DLG_TEXT_GUB[22];
                                link.l1 = DLG_TEXT_GUB[23];
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = DLG_TEXT_GUB[24];
                                link.l1 = DLG_TEXT_GUB[25];
                                link.l1.go = "exit";
								pchar.questTemp.State = "Sp7SavePardal_toAntigua";
								AddQuestRecord("Spa_Line_7_SavePardal", "1");
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1 = "location";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1.location = "Antigua";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition = "Sp7SavePardal_FightNearAntigua";
							break;
                            case "8":
                                dialog.text = DLG_TEXT_GUB[26];
                                link.l1 = DLG_TEXT_GUB[27];
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = DLG_TEXT_GUB[28];
                                link.l1 = DLG_TEXT_GUB[29];
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = DLG_TEXT_GUB[30];
                                link.l1 = DLG_TEXT_GUB[31];
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = DLG_TEXT_GUB[32];
                                link.l1 = DLG_TEXT_GUB[33];
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = DLG_TEXT_GUB[34];
                                link.l1 = DLG_TEXT_GUB[35];
                                link.l1.go = "Step_12_1";
                            break;
						}
                    }
                break;
                
                case "":           // Квест №1, Спасти горожан от Моргана.
                    dialog.text = DLG_TEXT_GUB[36];
                    link.l1 = DLG_TEXT_GUB[37];
                    link.l1.go = "Step_1_1";
                break;
                case "SaveFromMorgan_OutOfPrison":
                    dialog.text = DLG_TEXT_GUB[38];
                    link.l1 = DLG_TEXT_GUB[39];
                    link.l1.go = "Step_1_7";
                break;
                case "Inquisition_backBad":
                    dialog.text = DLG_TEXT_GUB[40];
                    link.l1 = DLG_TEXT_GUB[41];
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backPartGood":
                    dialog.text = DLG_TEXT_GUB[42];
                    link.l1 = DLG_TEXT_GUB[43];
                    link.l1.go = "Step_2_3";
                break;
                case "Inquisition_backAllGood":
                    dialog.text = DLG_TEXT_GUB[44];
                    link.l1 = DLG_TEXT_GUB[45];
                    link.l1.go = "Step_2_3";
                break;
                case "TakeRockBras_RockSink":
                    dialog.text = DLG_TEXT_GUB[46];
                    link.l1 = DLG_TEXT_GUB[47];
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_DieHardRock":
                    dialog.text = DLG_TEXT_GUB[48];
                    link.l1 = DLG_TEXT_GUB[49];
                    link.l1.go = "Step_3_6";
                break;
                case "TakeRockBras_RockTaken":
                    dialog.text = DLG_TEXT_GUB[50];
                    link.l1 = DLG_TEXT_GUB[51];
                    link.l1.go = "Step_3_7";
                break;
                case "TakeRockBras_RockGiven":
                    dialog.text = DLG_TEXT_GUB[52];
                    link.l1 = DLG_TEXT_GUB[53];
                    link.l1.go = "Step_3_8";
                break;
                case "TakeRockBras_WaitTwoDays":
                if (GetQuestPastDayParam("questTemp") > 2)
                    {
                        dialog.text = DLG_TEXT_GUB[54];
                        link.l1 = DLG_TEXT_GUB[55];
                        link.l1.go = "Step_3_9";
                    }
                    else
                    {
                        dialog.text = DLG_TEXT_GUB[56];
                        link.l1 = DLG_TEXT_GUB[57];
                        link.l1.go = "exit";
                    }
                break;
                case "TakeRockBras_SeekRocksMoney":
                    dialog.text = DLG_TEXT_GUB[58];
                    link.l1 = DLG_TEXT_GUB[59];
                    link.l1.go = "exit";
                    if (sti(pchar.money) > 500000)
                    {
                        link.l2 = DLG_TEXT_GUB[60];
                        link.l2.go = "Step_3_10";
                    }
                break;
                case "Sp4Detection_toMirderPlace":
                    dialog.text = DLG_TEXT_GUB[61];
                    link.l1 = DLG_TEXT_GUB[62];
                    link.l1.go = "exit";
                break;
                case "Sp4Detection_toGovernor":
                    dialog.text = DLG_TEXT_GUB[63];
                    link.l1 = DLG_TEXT_GUB[64];
                    link.l1.go = "Step_4_6";
                break;
                case "Sp4Detection_toDEstre":
                    dialog.text = DLG_TEXT_GUB[65];
                    link.l1 = DLG_TEXT_GUB[66];
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_1":
                    dialog.text = DLG_TEXT_GUB[67];
                    link.l1 = DLG_TEXT_GUB[68];
                    link.l1.go = "Step_4_9";
                break;
                case "Sp4Detection_toDEstre_2":
                    dialog.text = DLG_TEXT_GUB[69];
                    link.l1 = DLG_TEXT_GUB[70];
                    link.l1.go = "Step_4_10";
                break;
                case "Sp4Detection_DEstreIsDead":
                    dialog.text = DLG_TEXT_GUB[71];
                    link.l1 = DLG_TEXT_GUB[72];
                    link.l1.go = "Step_4_14";
                break;
                case "Sp5LaVegaAttack_BackToHavana":
                    dialog.text = DLG_TEXT_GUB[73];
                    link.l1 = DLG_TEXT_GUB[74];
                    link.l1.go = "Step_5_3";
                break;
                case "Sp6TakeMess_waitMessanger":
                    dialog.text = DLG_TEXT_GUB[75];
                    link.l1 = DLG_TEXT_GUB[76];
                    link.l1.go = "Step_6_4";
                break;
                case "Sp6TakeMess_Action":
                    dialog.text = DLG_TEXT_GUB[77];
                    link.l1 = DLG_TEXT_GUB[78];
                    link.l1.go = "Step_6_4";
                break;
                case "Sp7SavePardal_PardalIsSink":
                    dialog.text = DLG_TEXT_GUB[79];
                    link.l1 = DLG_TEXT_GUB[80];
                    link.l1.go = "Step_7_1";
                break;
                case "Sp7SavePardal_GoodWork":
                    dialog.text = DLG_TEXT_GUB[81];
                    link.l1 = DLG_TEXT_GUB[82];
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_2GoodWork":
                    dialog.text = DLG_TEXT_GUB[83];
                    link.l1 = DLG_TEXT_GUB[84];
                    link.l1.go = "Step_7_3";
                break;
                case "Sp7SavePardal_DieHard":
                    dialog.text = DLG_TEXT_GUB[85];
                    link.l1 = DLG_TEXT_GUB[86];
                    link.l1.go = "Step_7_6";
                break;
                case "Sp8SaveCumana_YouLate":
                    dialog.text = DLG_TEXT_GUB[87];
                    link.l1 = DLG_TEXT_GUB[88];
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "20";
                break;
                case "Sp8SaveCumana_DieHard":
                    dialog.text = DLG_TEXT_GUB[89];
                    link.l1 = DLG_TEXT_GUB[90];
                    link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "40";
                break;
                case "Sp8SaveCumana_GoodWork":
                    dialog.text = DLG_TEXT_GUB[91];
                    link.l1 = DLG_TEXT_GUB[92];
                    link.l1.go = "Step_8_6";
                break;
                case "Sp9SaveCumana_BackHavana":
                    dialog.text = DLG_TEXT_GUB[93];
                    link.l1 = DLG_TEXT_GUB[94];
                    link.l1.go = "Step_9_2";
                break;
                case "Sp10Maracaibo_DieHard":
                    dialog.text = DLG_TEXT_GUB[95];
                    link.l1 = DLG_TEXT_GUB[96];
                    link.l1.go = "Step_10_6";
                break;
                case "Sp10Maracaibo_GoodWork":
                    dialog.text = DLG_TEXT_GUB[97];
                    link.l1 = DLG_TEXT_GUB[98];
                    link.l1.go = "Step_10_11";
                break;
                case "Sp10Maracaibo_2GoodWork":
                    dialog.text = DLG_TEXT_GUB[99];
                    link.l1 = DLG_TEXT_GUB[100];
                    link.l1.go = "Step_10_9";
                break;
                case "DestrHolland_GoOn":
                    dialog.text = DLG_TEXT_GUB[101];
                    link.l1 = DLG_TEXT_GUB[102];
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad"))
                    {
                        dialog.text = DLG_TEXT_GUB[103];
                        link.l1 = DLG_TEXT_GUB[104];
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = DLG_TEXT_GUB[105];
                        link.l1 = DLG_TEXT_GUB[106];
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Villemstad") && CheckAttribute(pchar, "questTemp.Q11_Marigo"))
                    {
                        dialog.text = DLG_TEXT_GUB[107];
                        link.l1 = DLG_TEXT_GUB[108];
                        link.l1.go = "Step_11_3";
                    }
                break;
                case "OccupyPortPax_WeWin":
                    dialog.text = DLG_TEXT_GUB[109];
                    link.l1 = DLG_TEXT_GUB[110];
                    link.l1.go = "Step_12_4";
                break;
                case "QuestLineBreake":
                    dialog.text = DLG_TEXT_GUB[111];
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = DLG_TEXT_GUB[112] + pchar.name + DLG_TEXT_GUB[113];
                    link.l1 = DLG_TEXT_GUB[114];
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
			}
        break;
        //********************** Квест №1, Спасти горожан от Моргана. ************************
        case "Step_1_1":
            dialog.text = DLG_TEXT_GUB[115]+
                          DLG_TEXT_GUB[116];
            link.l1 = DLG_TEXT_GUB[117];
            link.l1.go = "Step_1_2";
        break;
        case "Step_1_2":
            dialog.text = DLG_TEXT_GUB[118]+
                          DLG_TEXT_GUB[119]+
                          DLG_TEXT_GUB[120];
            link.l1 = DLG_TEXT_GUB[121];
            link.l1.go = "Step_1_3";
        break;
        case "Step_1_3":
            dialog.text = DLG_TEXT_GUB[122];
            link.l1 = DLG_TEXT_GUB[123];
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = DLG_TEXT_GUB[124]+
                          DLG_TEXT_GUB[125]+
                          DLG_TEXT_GUB[126]+
                          DLG_TEXT_GUB[127];
            link.l1 = DLG_TEXT_GUB[128];
            link.l1.go = "Step_1_5";
        break;
        case "Step_1_5":
            dialog.text = DLG_TEXT_GUB[129];
            link.l1 = DLG_TEXT_GUB[130];
            link.l1.go = "Step_1_6";
        break;
        case "Step_1_6":
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = SPAIN;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "SaveFromMorgan_toPrison";
            AddQuestRecord("Spa_Line_1_SaveCitizens", "1");
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("SpaPrisoner"+i, "usurer_"+i, "man", "man", 10, SPAIN, -1, false));
                sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
                LAi_SetCitizenType(sld);
            	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
                ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto9");
            }
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        case "Step_1_7":
            dialog.text = DLG_TEXT_GUB[131];
            link.l1 = DLG_TEXT_GUB[132];
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = DLG_TEXT_GUB[133];
            link.l1 = DLG_TEXT_GUB[134];
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = DLG_TEXT_GUB[135];
            link.l1 = DLG_TEXT_GUB[136];
            link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = DLG_TEXT_GUB[137];
            link.l1 = DLG_TEXT_GUB[138];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_1_SaveCitizens");
            AddMoneyToCharacter(pchar, 50000);
            for (i=1; i<=3; i++)
            {
                sld = characterFromId("SpaPrisoner"+i);
                RemovePassenger(pchar, sld);
         	    sld.LifeDay = 0; // уберем нпс
            }
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[139] + GetMainCharacterNameGen() + DLG_TEXT_GUB[140], SPAIN, 5, 1);
		break;
        //********************** Квест №2, задания Инквизиции. ************************
        case "Step_2_1":
            dialog.text = DLG_TEXT_GUB[141]+
                          DLG_TEXT_GUB[142];
            link.l1 = DLG_TEXT_GUB[143];
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = DLG_TEXT_GUB[144];
            link.l1 = "...";
            link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toDeSouza";
            AddQuestRecord("Spa_Line_2_Inquisition", "1");
            SaveCurrentQuestDateParam("questTemp");
            sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "priest", "man", "man", 10, SPAIN, -1, false));
        	sld.name 	= DLG_TEXT_GUB[145];
        	sld.lastname = DLG_TEXT_GUB[146];
			sld.model.animation = "man2";
            sld.Dialog.Filename = "Quest\AntonioDeSouza.c";
			sld.greeting = "Gr_padre";
            LAi_SetHuberType(sld);
        	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
        break;
        case "Step_2_3":
            dialog.text = DLG_TEXT_GUB[147];
            link.l1 = DLG_TEXT_GUB[148];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "15";
            CloseQuestHeader("Spa_Line_2_Inquisition");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[149] + GetFullName(pchar) + DLG_TEXT_GUB[150], SPAIN, 5, 1);
        break;
        //********************** Квест №3, захватить Рока Бразица. ************************
        case "Step_3_1":
            dialog.text = DLG_TEXT_GUB[151];
            link.l1 = DLG_TEXT_GUB[152];
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = DLG_TEXT_GUB[153]+
                          DLG_TEXT_GUB[154];
            link.l1 = DLG_TEXT_GUB[155];
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = DLG_TEXT_GUB[156] + pchar.name + DLG_TEXT_GUB[157];
            link.l1 = DLG_TEXT_GUB[158];
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = DLG_TEXT_GUB[159];
            link.l1 = DLG_TEXT_GUB[160];
            link.l1.go = "Step_3_5";
        break;
        case "Step_3_5":
            dialog.text = DLG_TEXT_GUB[161];
            link.l1 = DLG_TEXT_GUB[162];
            link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toTortuga";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "1");
        break;
        case "Step_3_6":
            dialog.text = DLG_TEXT_GUB[163]+
                          DLG_TEXT_GUB[164];
            link.l1 = DLG_TEXT_GUB[165];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[166] + GetFullName(pchar) + DLG_TEXT_GUB[167], SPAIN, 5, 1);
        break;
        case "Step_3_7":
            dialog.text = DLG_TEXT_GUB[168];
            link.l1 = DLG_TEXT_GUB[169];
            link.l1.go = "exit";
        break;
        case "Step_3_8":
            dialog.text = DLG_TEXT_GUB[170];
            link.l1 = DLG_TEXT_GUB[171];
            link.l1.go = "exit";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "9");
            pchar.questTemp.State = "TakeRockBras_WaitTwoDays";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_3_9":
            dialog.text = DLG_TEXT_GUB[172]+
                          DLG_TEXT_GUB[173]+
                          DLG_TEXT_GUB[174];
            link.l1 = DLG_TEXT_GUB[175];
            link.l1.go = "Step_3_13";
        break;
        case "Step_3_13":
            dialog.text = DLG_TEXT_GUB[176];
            link.l1 = DLG_TEXT_GUB[177];
            link.l1.go = "Step_3_14";
        break;
        case "Step_3_14":
            dialog.text = DLG_TEXT_GUB[178];
            link.l1 = DLG_TEXT_GUB[179];
            link.l1.go = "Step_3_15";
        break;
        case "Step_3_15":
            dialog.text = DLG_TEXT_GUB[180];
            link.l1 = DLG_TEXT_GUB[181];
            link.l1.go = "exit";
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.gold = 150000;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian18 = 1;
         	pchar.GenQuestBox.Hispaniola_Cave = true;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry5 = 250;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry14= 10;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.potion3 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.mineral8 = 1;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry7 = 5;
            pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry2 = 20;
         	pchar.GenQuestBox.Beliz_Cave = true;
            pchar.GenQuestBox.Beliz_Cave.box1.items.gold = 50000;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian6 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian11 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian15 = 1;
            pchar.GenQuestBox.Beliz_Cave.box1.items.indian12 = 1;
            pchar.GenQuestBox.Beliz_Cave.box2.items.gold = 150000;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion5 = 10;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potionrum = 2;
            pchar.GenQuestBox.Beliz_Cave.box2.items.potion4 = 10;
            pchar.questTemp.State = "TakeRockBras_SeekRocksMoney";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "8");
        break;
        case "Step_3_10":
            dialog.text = DLG_TEXT_GUB[182];
            link.l1 = DLG_TEXT_GUB[183];
            link.l1.go = "Step_3_11";
        break;
        case "Step_3_11":
            dialog.text = DLG_TEXT_GUB[184];
            link.l1 = DLG_TEXT_GUB[185];
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, -400000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_3_RockBrasilian");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[186] + GetFullName(pchar) + DLG_TEXT_GUB[187], SPAIN, 5, 1);
        break;
        //********************** Квест №4, расследование убийства. ************************
        case "Step_4_1":
            dialog.text = DLG_TEXT_GUB[188]+
                          DLG_TEXT_GUB[189];
            link.l1 = DLG_TEXT_GUB[190];
            link.l1.go = "Step_4_2";
        break;
        case "Step_4_2":
            dialog.text = DLG_TEXT_GUB[191];
            link.l1 = DLG_TEXT_GUB[192];
            link.l1.go = "Step_4_3";
        break;
        case "Step_4_3":
            dialog.text = DLG_TEXT_GUB[193];
            link.l1 = DLG_TEXT_GUB[194];
            link.l1.go = "Step_4_4";
        break;
        case "Step_4_4":
            dialog.text = DLG_TEXT_GUB[195];
            link.l1 = DLG_TEXT_GUB[196];
            link.l1.go = "Step_4_5";
        break;
        case "Step_4_5":
            dialog.text = DLG_TEXT_GUB[197]+
                          DLG_TEXT_GUB[198];
            link.l1 = DLG_TEXT_GUB[199];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toMirderPlace";
            AddQuestRecord("Spa_Line_4_MirderDetection", "1");
         	pchar.GenQuestBox.Havana_houseS1Bedroom = true;
            pchar.GenQuestBox.Havana_houseS1Bedroom.box2.items.letter_notes = 1;
        break;
        case "Step_4_6":
            dialog.text = DLG_TEXT_GUB[200];
            link.l1 = DLG_TEXT_GUB[201];
            link.l1.go = "Step_4_7";
        break;
        case "Step_4_7":
            dialog.text = DLG_TEXT_GUB[202];
            link.l1 = DLG_TEXT_GUB[203];
            link.l1.go = "Step_4_8";
            TakeItemFromCharacter(pchar, "letter_notes");
        break;
        case "Step_4_8":
            dialog.text = DLG_TEXT_GUB[204];
            link.l1 = DLG_TEXT_GUB[205];
            link.l1.go = "exit";
            GiveNationLicence(FRANCE, 50);
            pchar.questTemp.State = "Sp4Detection_toTortuga";
            AddQuestRecord("Spa_Line_4_MirderDetection", "4");
            sld = GetCharacter(NPC_GenerateCharacter("ServantDEstre", "Barmen_13", "man", "man", 10, FRANCE, -1, false));
        	sld.name 	= DLG_TEXT_GUB[206];
        	sld.lastname = "";
            sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
            LAi_SetStayType(sld);
        	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "goto", "goto2");
        break;
        case "Step_4_9":
            dialog.text = DLG_TEXT_GUB[207]+
                          DLG_TEXT_GUB[208]+
                          DLG_TEXT_GUB[209];
            link.l1 = DLG_TEXT_GUB[210];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            TakeNationLicence(FRANCE);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[211] + GetMainCharacterNameDat() + DLG_TEXT_GUB[212], SPAIN, 5, 1);
        break;
        case "Step_4_10":
            dialog.text = DLG_TEXT_GUB[213];
            link.l1 = DLG_TEXT_GUB[214];
            link.l1.go = "Step_4_11";
        break;
        case "Step_4_11":
            dialog.text = DLG_TEXT_GUB[215];
            link.l1 = DLG_TEXT_GUB[216];
            link.l1.go = "Step_4_12";
        break;
        case "Step_4_12":
            dialog.text = DLG_TEXT_GUB[217];
            link.l1 = DLG_TEXT_GUB[218];
            link.l1.go = "Step_4_13";
        break;
        case "Step_4_13":
            dialog.text = DLG_TEXT_GUB[219]+
                          DLG_TEXT_GUB[220];
            link.l1 = DLG_TEXT_GUB[221];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 3000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Grappling", 100);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 120);
			ChangeCharacterReputation(pchar, 2);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[222] + GetMainCharacterNameDat() + DLG_TEXT_GUB[223], SPAIN, 5, 1);
        break;
        case "Step_4_14":
            dialog.text = DLG_TEXT_GUB[224];
            link.l1 = DLG_TEXT_GUB[225];
            link.l1.go = "Step_4_15";
        break;
        case "Step_4_15":
            dialog.text = DLG_TEXT_GUB[226];
            link.l1 = DLG_TEXT_GUB[227];
            link.l1.go = "Step_4_16";
        break;
        case "Step_4_16":
            dialog.text = DLG_TEXT_GUB[228];
            link.l1 = DLG_TEXT_GUB[229];
            link.l1.go = "Step_4_17";
        break;
        case "Step_4_17":
            dialog.text = DLG_TEXT_GUB[230];
            link.l1 = DLG_TEXT_GUB[231];
            link.l1.go = "Step_4_18";
        break;
        case "Step_4_18":
            dialog.text = DLG_TEXT_GUB[232];
            link.l1 = DLG_TEXT_GUB[233];
            link.l1.go = "Step_4_19";
        break;
        case "Step_4_19":
            dialog.text = DLG_TEXT_GUB[234];
            link.l1 = DLG_TEXT_GUB[235];
            link.l1.go = "Step_4_20";
        break;
        case "Step_4_20":
            dialog.text = DLG_TEXT_GUB[236]+
                          DLG_TEXT_GUB[237];
            link.l1 = DLG_TEXT_GUB[238];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "5";
            pchar.questTemp.Waiting_time = "4";
            CloseQuestHeader("Spa_Line_4_MirderDetection");
            AddMoneyToCharacter(pchar, 120000);
            TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[239] + GetMainCharacterNameDat() + DLG_TEXT_GUB[240], SPAIN, 5, 1);
        break;
        //********************** Квест №5, Нападение на Ла Вегу. ************************
        case "Step_5_1":
            dialog.text = DLG_TEXT_GUB[241];
            link.l1 = DLG_TEXT_GUB[242];
            link.l1.go = "Step_5_2";
        break;
        case "Step_5_2":
            dialog.text = DLG_TEXT_GUB[243];
            link.l1 = DLG_TEXT_GUB[244];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_toSantiago";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "1");
        break;
        case "Step_5_3":
            dialog.text = DLG_TEXT_GUB[245]+
                          DLG_TEXT_GUB[246];
            link.l1 = DLG_TEXT_GUB[247];
            link.l1.go = "Step_5_4";
        break;
        case "Step_5_4":
            dialog.text = DLG_TEXT_GUB[248];
            link.l1 = DLG_TEXT_GUB[249];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Spa_Line_5_LaVegaAttack");
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "hidden_effects");	
			//<-- огонь и пламень
            //===> Эдвард убит :( теперь Ла Вегой рулит капитан Купер.
            sld = characterFromID("Edward Mansfield");
            sld.name 	= DLG_TEXT_GUB[250];
        	sld.lastname = DLG_TEXT_GUB[251];
        	sld.model.animation = "man"
            sld.model = "officer_8";
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[252], SPAIN, 5, 1);
        break;
        //********************** Квест №6, Разведка на Тортуге. ************************
        case "Step_6_1":
            dialog.text = DLG_TEXT_GUB[253]+
                          DLG_TEXT_GUB[254]+
                          DLG_TEXT_GUB[255];
            link.l1 = DLG_TEXT_GUB[256];
            link.l1.go = "Step_6_2";
        break;
        case "Step_6_2":
            dialog.text = DLG_TEXT_GUB[257];
            link.l1 = DLG_TEXT_GUB[258];
            link.l1.go = "Step_6_3";
        break;
        case "Step_6_3":
            dialog.text = DLG_TEXT_GUB[259]+
                          DLG_TEXT_GUB[260];
            link.l1 = DLG_TEXT_GUB[261];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp6TakeMess_toTotuga";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "1");
			GiveNationLicence(FRANCE, 60);
        break;
        case "Step_6_4":
            dialog.text = DLG_TEXT_GUB[262];
			if (CheckCharacterItem(pchar, "letter_1"))
			{
				link.l1 = DLG_TEXT_GUB[263];
				link.l1.go = "Step_6_6";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[264];
				link.l1.go = "Step_6_5";			
			}
        break;
        case "Step_6_5":
            dialog.text = DLG_TEXT_GUB[265];
            link.l1 = DLG_TEXT_GUB[266];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
            BackItemDescribe("letter_1");
  			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[267] + GetMainCharacterNameGen() + DLG_TEXT_GUB[268], SPAIN, 5, 1);
         break;
        case "Step_6_6":
            dialog.text = DLG_TEXT_GUB[269] + pchar.name + DLG_TEXT_GUB[270];
            link.l1 = DLG_TEXT_GUB[271];
            link.l1.go = "Step_6_7";
        break;
        case "Step_6_7":
            dialog.text = DLG_TEXT_GUB[272];
            link.l1 = DLG_TEXT_GUB[273];
            link.l1.go = "Step_6_8";
        break;
        case "Step_6_8":
            dialog.text = DLG_TEXT_GUB[274];
            link.l1 = DLG_TEXT_GUB[275];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "9";
            CloseQuestHeader("Spa_Line_6_TakeMessangeer");
			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[276] + GetFullName(pchar) + DLG_TEXT_GUB[277], SPAIN, 5, 1);
		break; 
        //********************** Квест №7, Спасти Пардаля. ************************
        case "Step_7_1":
            dialog.text = DLG_TEXT_GUB[278];
            link.l1 = DLG_TEXT_GUB[279];
            link.l1.go = "Step_7_2";
        break;
        case "Step_7_2":
            dialog.text = DLG_TEXT_GUB[280];
            link.l1 = DLG_TEXT_GUB[281];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Spa_Line_7_SavePardal"); 
		break;
        case "Step_7_3":
            dialog.text = DLG_TEXT_GUB[282];
            link.l1 = DLG_TEXT_GUB[283];
            link.l1.go = "Step_7_4";
        break;
        case "Step_7_4":
            dialog.text = DLG_TEXT_GUB[284];
            link.l1 = DLG_TEXT_GUB[285];
            link.l1.go = "Step_7_5";
        break;
        case "Step_7_5":
            dialog.text = DLG_TEXT_GUB[286]+ 
				          DLG_TEXT_GUB[287];
            link.l1 = DLG_TEXT_GUB[288];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 25000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "5";
            CloseQuestHeader("Spa_Line_7_SavePardal");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sneak", 250);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[289], SPAIN, 5, 1);
        break;
        case "Step_7_6":
            dialog.text = DLG_TEXT_GUB[290];
            link.l1 = DLG_TEXT_GUB[291];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "40";
            CloseQuestHeader("Spa_Line_7_SavePardal"); 
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[292], SPAIN, 5, 1);
        break;
//********************** Квест №8, Отбить нападение на Куману. ************************
        case "Step_8_1":
            dialog.text = DLG_TEXT_GUB[293];
            link.l1 = DLG_TEXT_GUB[294];
            link.l1.go = "Step_8_2";
        break;
        case "Step_8_2":
            dialog.text = DLG_TEXT_GUB[295]+
				          DLG_TEXT_GUB[296];
            link.l1 = DLG_TEXT_GUB[297];
            link.l1.go = "Step_8_3";
        break;
        case "Step_8_3":
            dialog.text = DLG_TEXT_GUB[298]+
				          DLG_TEXT_GUB[299]+
						  DLG_TEXT_GUB[300];
            link.l1 = DLG_TEXT_GUB[301];
            link.l1.go = "Step_8_4";
        break;
		case "Step_8_4":
            dialog.text = DLG_TEXT_GUB[302];
            link.l1 = DLG_TEXT_GUB[303];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp8SaveCumana_toCumana";
            AddQuestRecord("Spa_Line_8_SaveCumana", "1");
			SetTimerCondition("Sp8SaveCumana_RescueTimeOver", 0, 0, 20, false);
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1.location = "Cumana";
            Pchar.quest.Sp8SaveCumana_Battle.win_condition = "Sp8SaveCumana_Battle";
        break;
		case "Step_8_5":
            dialog.text = DLG_TEXT_GUB[304];
            link.l1 = DLG_TEXT_GUB[305];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			SetLocationCapturedState("Cumana_town", false);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
 			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[306] + GetFullName(pchar) + DLG_TEXT_GUB[307], SPAIN, 5, 1);
        break;
		case "Step_8_6":
            dialog.text = DLG_TEXT_GUB[308];
            link.l1 = DLG_TEXT_GUB[309];
            link.l1.go = "Step_8_7";
        break;
		case "Step_8_7":
            dialog.text = DLG_TEXT_GUB[310];
            link.l1 = DLG_TEXT_GUB[311];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "7";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
            CloseQuestHeader("Spa_Line_8_SaveCumana");
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
 			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[312], SPAIN, 5, 1);
        break;
//********************** Квест №9, Четыре золотых галеона. ************************
		case "Step_9_1":
            dialog.text = DLG_TEXT_GUB[313];
            link.l1 = DLG_TEXT_GUB[314];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp9SaveCumana_toPortoBello";
            AddQuestRecord("Spa_Line_9_FourGolgGaleons", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_SpaLineQ10");
            GiveItem2Character(pchar,"letter_1");
        break;
		case "Step_9_2":
            dialog.text = DLG_TEXT_GUB[315];
            link.l1 = DLG_TEXT_GUB[316];
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = DLG_TEXT_GUB[317];
            link.l1 = DLG_TEXT_GUB[318];
            link.l1.go = "Step_9_4";
        break;
		case "Step_9_4":
            dialog.text = DLG_TEXT_GUB[319];
            link.l1 = DLG_TEXT_GUB[320];
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = DLG_TEXT_GUB[321];
			iTemp = 0;
			iMoney = 0;
            for (i=1; i<=COMPANION_MAX; i++)
            {
                ShipType = GetCompanionIndex(pchar,i);
                if(ShipType != -1)
                {
                	sld = GetCharacter(ShipType);
                    ShipType = sti(sld.ship.type);
                    Rank = sti(RealShips[ShipType].basetype);
                    if (Rank == SHIP_GALEON_L) 
					{
						iTemp++;
						iMoney = iMoney + sti(sld.Ship.Cargo.Goods.Gold);
					}
                }
            } 
			npchar.quest.money = iMoney;
			if (iTemp < 4 && iTemp > 0)
            {
                if (iTemp == 1)
                {
					link.l1 = DLG_TEXT_GUB[322];
					link.l1.go = "Step_9_6";
                }
                else
                {
					link.l1 = DLG_TEXT_GUB[323] + iTemp + DLG_TEXT_GUB[324];
					link.l1.go = "Step_9_6";
                }
            }
            else
            {
				if (iTemp == 0)
				{
					link.l1 = DLG_TEXT_GUB[325];
					link.l1.go = "Step_9_8";				
				}
				else
				{
					link.l1 = DLG_TEXT_GUB[326];
					link.l1.go = "Step_9_11";
				}
            }
        break;
		case "Step_9_6":
            dialog.text = DLG_TEXT_GUB[327]+
				          DLG_TEXT_GUB[328];
            link.l1 = DLG_TEXT_GUB[329];
            link.l1.go = "Step_9_7";
        break;
		case "Step_9_7":
            dialog.text = DLG_TEXT_GUB[330];
            link.l1 = DLG_TEXT_GUB[331];
            link.l1.go = "Step_9_71";
		break;
		case "Step_9_71":
			if (sti(npchar.quest.money) < (iTemp*1200))
			{
				dialog.text = DLG_TEXT_GUB[332];
				link.l1 = DLG_TEXT_GUB[333];
				link.l1.go = "Step_9_exit";
				pchar.questTemp.Waiting_time = "20";
				pchar.questTemp.State = "empty";
				SaveCurrentQuestDateParam("questTemp");
				pchar.questTemp.CurQuestNumber = "10";
			}
			else
			{
				dialog.text = DLG_TEXT_GUB[334];
				link.l1 = DLG_TEXT_GUB[335];
				link.l1.go = "Step_9_exit";
				pchar.questTemp.State = "QuestLineBreake";	
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				AddCharacterExpToSkill(pchar, "Sailing", -300);
				AddCharacterExpToSkill(pchar, "Leadership", -300);
				AddCharacterExpToSkill(pchar, "Commerce", -300);
				AddCharacterExpToSkill(pchar, "Pistol", -300);
				//слухи
				AddSimpleRumour(DLG_TEXT_GUB[336], SPAIN, 5, 1);
			}
        break;
		case "Step_9_8":
            dialog.text = DLG_TEXT_GUB[337];
            link.l1 = DLG_TEXT_GUB[338];
            link.l1.go = "Step_9_10";
        break;
		case "Step_9_10":
            dialog.text = DLG_TEXT_GUB[339]+
				          DLG_TEXT_GUB[340];
            link.l1 = DLG_TEXT_GUB[341];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "60";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons"); 
        break;
		case "Step_9_11":
            dialog.text = DLG_TEXT_GUB[342];
			if (sti(npchar.quest.money) >= 5000)
			{
				link.l1 = DLG_TEXT_GUB[343];
				link.l1.go = "Step_9_12";			
			}
			else
			{
				if(sti(npchar.quest.money) > 4800)
				{
					link.l1 = DLG_TEXT_GUB[344] + FindRussianQtyString(sti(npchar.quest.money)) + DLG_TEXT_GUB[345];
					link.l1.go = "Step_9_14";	
				}
				else
				{
					link.l1 = DLG_TEXT_GUB[346] + FindRussianQtyString(sti(npchar.quest.money)) + DLG_TEXT_GUB[347];
					link.l1.go = "Step_9_16";				
				}
			}
        break;
		case "Step_9_12":
            dialog.text = DLG_TEXT_GUB[348];
            link.l1 = DLG_TEXT_GUB[349];
            link.l1.go = "Step_9_13";
        break;
		case "Step_9_13":
            dialog.text = DLG_TEXT_GUB[350];
            link.l1 = DLG_TEXT_GUB[351];
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "7";
			pchar.questTemp.State = "empty";
			AddMoneyToCharacter(pchar, 220000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[352], SPAIN, 5, 1);
        break;
		case "Step_9_14":
            dialog.text = DLG_TEXT_GUB[353]+
				          DLG_TEXT_GUB[354];
            link.l1 = DLG_TEXT_GUB[355];
            link.l1.go = "Step_9_15";
        break;
		case "Step_9_15":
            dialog.text = DLG_TEXT_GUB[356];
            link.l1 = DLG_TEXT_GUB[357];
            link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "12";
			pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");            
			AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 190);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[358], SPAIN, 5, 1);
		break;
		case "Step_9_16":
			dialog.text = DLG_TEXT_GUB[359] + FindRussianQtyString(5000-sti(npchar.quest.money)) + DLG_TEXT_GUB[360];
            link.l1 = DLG_TEXT_GUB[361];
            link.l1.go = "Step_9_17";
        break;
		case "Step_9_17":
            dialog.text = DLG_TEXT_GUB[362];
            link.l1 = DLG_TEXT_GUB[363];
            link.l1.go = "Step_9_exit";
			pchar.questTemp.State = "QuestLineBreake";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			AddCharacterExpToSkill(pchar, "Pistol", -300);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[364], SPAIN, 5, 1);
		break;
		case "Step_9_exit":
			pchar.questTemp.CurQuestNumber = "10";
            CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
            for (i=1; i<=4; i++)
            {
                sld = characterFromID("Captain_"+i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
            }
            DialogExit();
        break;
//********************** Квест №10, Защита Маракайбо ************************
		case "Step_10_1":
            dialog.text = DLG_TEXT_GUB[365];
            link.l1 = DLG_TEXT_GUB[366];
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = DLG_TEXT_GUB[367];
            link.l1 = DLG_TEXT_GUB[368];
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = DLG_TEXT_GUB[369];
            link.l1 = DLG_TEXT_GUB[370];
            link.l1.go = "Step_10_4";
        break;
		case "Step_10_4":
            dialog.text = DLG_TEXT_GUB[371];
            link.l1 = DLG_TEXT_GUB[372];
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = DLG_TEXT_GUB[373];
            link.l1 = DLG_TEXT_GUB[374];
            link.l1.go = "exit";
            pchar.questTemp.State = "Sp10Maracaibo_toMaracaibo";
            AddQuestRecord("Spa_Line_10_Maracaibo", "1");
        break;
		case "Step_10_6":
            dialog.text = DLG_TEXT_GUB[375];
            link.l1 = DLG_TEXT_GUB[376];
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = DLG_TEXT_GUB[377];
            link.l1 = DLG_TEXT_GUB[378];
            link.l1.go = "Step_10_8";
        break;
		case "Step_10_8":
            dialog.text = DLG_TEXT_GUB[379];
            link.l1 = "...";
            link.l1.go = "exit";
			CloseQuestHeader("Spa_Line_10_Maracaibo"); 
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
            bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Pistol", -430);
			AddCharacterExpToSkill(pchar, "Fortune", -460);
			AddCharacterExpToSkill(pchar, "Accuracy", -420);
			AddCharacterExpToSkill(pchar, "Grappling", -450);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[380], SPAIN, 5, 1);
        break;
		case "Step_10_9":
            dialog.text = DLG_TEXT_GUB[381];
            link.l1 = DLG_TEXT_GUB[382] + Characters[GetCharacterIndex("Maracaibo_Mayor")].name + DLG_TEXT_GUB[383];
            link.l1.go = "Step_10_10";
        break;
		case "Step_10_10":
            dialog.text = DLG_TEXT_GUB[384];
            link.l1 = DLG_TEXT_GUB[385];
            link.l1.go = "Step_10_11";
        break;
		case "Step_10_11":
            dialog.text = DLG_TEXT_GUB[386];
            link.l1 = DLG_TEXT_GUB[387];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "15";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            CloseQuestHeader("Spa_Line_10_Maracaibo"); 
			ChangeCharacterReputation(pchar, 5);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[388], SPAIN, 5, 1);
        break;
//********************** Квест №11, Нападение на Кюрасао и Сан Мартин ************************
		case "Step_11_1":
            dialog.text = DLG_TEXT_GUB[389]+
				          DLG_TEXT_GUB[390]+
						  DLG_TEXT_GUB[391]+
						  DLG_TEXT_GUB[392]+
						  DLG_TEXT_GUB[393];
            link.l1 = DLG_TEXT_GUB[394];
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = DLG_TEXT_GUB[395];
            link.l1 = DLG_TEXT_GUB[396];
            link.l1.go = "exit";
            SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY); //ссорим ГГ и голландцев. 
            SetNationRelationBoth(HOLLAND, SPAIN, RELATION_ENEMY);
            SetQuestHeader("Spa_Line_11_DestrHolland");
            AddQuestRecord("Spa_Line_11_DestrHolland", "1");
            pchar.questTemp.State = "DestrHolland_GoOn";
			characters[GetCharacterIndex("Villemstad_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Marigo_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра       
		break;
		case "Step_11_3":
            dialog.text = DLG_TEXT_GUB[397]+
				          DLG_TEXT_GUB[398];
            link.l1 = DLG_TEXT_GUB[399];
            link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 2);
            DeleteAttribute(pchar, "questTemp.Q11_Villemstad");
            DeleteAttribute(pchar, "questTemp.Q11_Marigo");
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            CloseQuestHeader("Spa_Line_11_DestrHolland"); 
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[400], SPAIN, 5, 5);
        break;
//********************** Квест №12, Захват Порт-о-Принса ************************
		case "Step_12_1":
            dialog.text = DLG_TEXT_GUB[401];
            link.l1 = DLG_TEXT_GUB[402];
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = DLG_TEXT_GUB[403];
            link.l1 = DLG_TEXT_GUB[404];
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = DLG_TEXT_GUB[405];
            link.l1 = DLG_TEXT_GUB[406];
            link.l1.go = "exit";
            SetQuestHeader("Spa_Line_12_OccupyPortPax");
            AddQuestRecord("Spa_Line_12_OccupyPortPax", "1");
            pchar.questTemp.State = "OccupyPortPax_GoOn";
			characters[GetCharacterIndex("PortPax_Mayor")].dialog.captureNode = "SpaLine12Quest_PortPax"; //капитулянтская нода мэра 
        break;
		case "Step_12_4":
            dialog.text = DLG_TEXT_GUB[407];
            link.l1 = DLG_TEXT_GUB[408];
            link.l1.go = "Step_12_5";
        break;
		case "Step_12_5":
            dialog.text = DLG_TEXT_GUB[409];
            link.l1 = DLG_TEXT_GUB[410];
            link.l1.go = "Step_12_6";
        break;
		case "Step_12_6":
            dialog.text = DLG_TEXT_GUB[411];
            link.l1 = DLG_TEXT_GUB[412];
            link.l1.go = "exit";
            AddTitleNextRate(sti(NPChar.nation), 4);
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine"; 
			bWorldAlivePause   = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			CloseQuestHeader("Spa_Line_12_OccupyPortPax"); 
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
			AddSimpleRumour(DLG_TEXT_GUB[413], SPAIN, 5, 1);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
