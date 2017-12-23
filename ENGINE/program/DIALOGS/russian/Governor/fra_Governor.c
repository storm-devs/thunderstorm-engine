#include "TEXT\DIALOGS\Governor\fra_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_GUB[0], DLG_TEXT_GUB[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_GUB[2], DLG_TEXT_GUB[3]);
		    link.l1.go = "exit";

            //******************** голландская линейка ***************************
        	switch (pchar.questTemp.State)   // что делаем в данный момент
            {
				case "DelivLettTortuga_toDOjeron": // Квест №7 голл. линейки. Письмо от Стэвезанта
					link.l1 = DLG_TEXT_GUB[4];
					link.l1.go = "Step_H7_1";
				break;
				case "DelivLettTortuga_WaitTwoHours":
					if (GetQuestPastTimeParam("questTemp") > 1)
					{
						link.l1 = DLG_TEXT_GUB[5];
						link.l1.go = "Step_H7_3";
					}
					else
					{
						dialog.text = DLG_TEXT_GUB[6];
						link.l1 = DLG_TEXT_GUB[7];
						link.l1.go = "exit";
					}
				break;
				case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. после грабежа.
					link.l1 = DLG_TEXT_GUB[8];
					link.l1.go = "Step_H7_5";
				break;
			}
		break;
		//******************** французская линейка ***************************
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
                                dialog.text = DLG_TEXT_GUB[22];
								link.l1 = DLG_TEXT_GUB[23];
                                link.l1.go = "Step_4_1";
                            break;
                            case "5":
                                dialog.text = DLG_TEXT_GUB[24];
								link.l1 = DLG_TEXT_GUB[25];
                                link.l1.go = "exit";
								LAi_group_Delete("PeaceGroup");
    							pchar.questTemp.State = "Fr5AnnaHant_toAnna";
								AddQuestRecord("Fra_Line_5_KillAnnaHanters", "1");
								sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
								sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
								sld.name = DLG_TEXT_GUB[26];
								sld.lastname = DLG_TEXT_GUB[27];
								LAi_SetStayType(sld);
								LAi_group_MoveCharacter(sld, "PeaceGroup");
								ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "goto","goto2");
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
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = DLG_TEXT_GUB[34];
								link.l1 = DLG_TEXT_GUB[35];
                                link.l1.go = "Step_9_1";
                            break;
                            case "10":
                                dialog.text = DLG_TEXT_GUB[36];
								link.l1 = DLG_TEXT_GUB[37];
                                link.l1.go = "Step_10_1";
                            break;
                            case "11":
                                dialog.text = DLG_TEXT_GUB[38];
								link.l1 = DLG_TEXT_GUB[39];
                                link.l1.go = "Step_11_1";
                            break;
                            case "12":
                                dialog.text = DLG_TEXT_GUB[40];
								link.l1 = DLG_TEXT_GUB[41];
                                link.l1.go = "Step_12_1";
                            break;
						}
					}
				break;
                case "":           // Квест №1, Охрана пирата Леграна.
                    dialog.text = DLG_TEXT_GUB[42];
                    link.l1 = DLG_TEXT_GUB[43];
                    link.l1.go = "Step_1_1";
                break;
                case "Fr1Legran_backGovernor":
                    dialog.text = DLG_TEXT_GUB[44];
                    link.l1 = DLG_TEXT_GUB[45];
                    link.l1.go = "Step_1_2";
                break;
                case "Fr1Legran_LegranKilled":
                    dialog.text = DLG_TEXT_GUB[46];
                    link.l1 = DLG_TEXT_GUB[47];
                    link.l1.go = "Step_1_3";
                break;
                case "Fr1Legran_LegranIsDead":
                    dialog.text = DLG_TEXT_GUB[48];
                    link.l1 = DLG_TEXT_GUB[49];
                    link.l1.go = "Step_1_5";
                break;
                case "Fr2Letter_SeekProblems":
                    dialog.text = DLG_TEXT_GUB[50];
                    link.l1 = DLG_TEXT_GUB[51];
                    link.l1.go = "Step_2_3";
                break;
                case "Fr2Letter_NiceResult":
                    dialog.text = DLG_TEXT_GUB[52];
                    link.l1 = DLG_TEXT_GUB[53];
                    link.l1.go = "Step_2_6";
                break;
                case "Fr3TakeAnna_BadResult":
                    dialog.text = DLG_TEXT_GUB[54];
                    link.l1 = DLG_TEXT_GUB[55];
                    link.l1.go = "Step_3_5";
                break;
                case "Fr3TakeAnna_NiceResult":
                    dialog.text = DLG_TEXT_GUB[56];
                    link.l1 = DLG_TEXT_GUB[57];
                    link.l1.go = "Step_3_7";
                break;
                case "Fr4SoleiRoyal_DieHard":
                    dialog.text = DLG_TEXT_GUB[58];
                    link.l1 = DLG_TEXT_GUB[59];
                    link.l1.go = "Step_4_7";
                break;
                case "Fr4SoleiRoyal_SoleiRoyalSunk":
                    dialog.text = DLG_TEXT_GUB[60];
                    link.l1 = DLG_TEXT_GUB[61];
                    link.l1.go = "Step_4_9";
                break;
                case "Fr4SoleiRoyal_backTortuga":
                    dialog.text = DLG_TEXT_GUB[62];
                    link.l1 = DLG_TEXT_GUB[63];
                    link.l1.go = "Step_4_11";
                break;
                case "Fr5AnnaHant_GoodWork":
                    dialog.text = DLG_TEXT_GUB[64];
                    link.l1 = DLG_TEXT_GUB[65];
                    link.l1.go = "exit";
					DeleteAttribute(&locations[FindLocation("Mayak10")], "DisableEncounters"); //откроем энканутеры
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "6";
					pchar.questTemp.Waiting_time = "7";
					CloseQuestHeader("Fra_Line_5_KillAnnaHanters");
					AddMoneyToCharacter(pchar, 5000);
                break;
                case "Fr6Olone_OloneIsDead":
                    dialog.text = DLG_TEXT_GUB[66];
                    link.l1 = DLG_TEXT_GUB[67];
                    link.l1.go = "Step_6_3";
                break;
                case "Fr6Olone_OloneIsLive":
                    dialog.text = DLG_TEXT_GUB[68];
                    link.l1 = DLG_TEXT_GUB[69];
                    link.l1.go = "Step_6_7";
                break;
                case "Fr6Olone_TakeMoney":
                    dialog.text = DLG_TEXT_GUB[70];
                    link.l1 = DLG_TEXT_GUB[71];
                    link.l1.go = "Step_6_9";
                break;
                case "Fr7RockBras_toSeekPlace":
                    dialog.text = DLG_TEXT_GUB[72];
                    link.l1 = DLG_TEXT_GUB[73];
                    link.l1.go = "exit";
					link.l2 = DLG_TEXT_GUB[74];
                    link.l2.go = "Step_7_6";
                break;
                case "Fr7RockBras_RockIsDead":
                    dialog.text = DLG_TEXT_GUB[75];
                    link.l1 = DLG_TEXT_GUB[76];
                    link.l1.go = "Step_7_7";
                break;
                case "Fr7RockBras_RockIsSaved":
                    dialog.text = DLG_TEXT_GUB[77];
                    link.l1 = DLG_TEXT_GUB[78];
                    link.l1.go = "Step_7_8";
                break;
                case "Fr7RockBras_RockIsAgony":
                    dialog.text = DLG_TEXT_GUB[79];
                    link.l1 = DLG_TEXT_GUB[80];
                    link.l1.go = "Step_7_7";
                break;
                case "Fr8ThreeCorsairs_backGovernor":
                    dialog.text = DLG_TEXT_GUB[81] + GetFullName(pchar) + DLG_TEXT_GUB[82];
                    link.l1 = DLG_TEXT_GUB[83];
                    link.l1.go = "Step_8_2";
                break;
                case "Fr9GuardPP_GoodWork":
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						dialog.text = DLG_TEXT_GUB[84];
						link.l1 = DLG_TEXT_GUB[85];
						link.l1.go = "Step_9_4";
					}
					else
					{
						dialog.text = DLG_TEXT_GUB[86];
						link.l1 = DLG_TEXT_GUB[87];
						link.l1.go = "Step_9_2";					
					}
                break;
                case "Fr9GuardPP_SoleiRoyalSunk":
                    dialog.text = DLG_TEXT_GUB[88];
                    link.l1 = DLG_TEXT_GUB[89];
                    link.l1.go = "Step_9_4";
                break;
                case "Fr9GuardPP_DieHard":
                    dialog.text = DLG_TEXT_GUB[90];
                    link.l1 = DLG_TEXT_GUB[91];
                    link.l1.go = "Step_9_6";
                break;
                case "Fr9GuardPP_Late":
                    dialog.text = DLG_TEXT_GUB[92];
                    link.l1 = DLG_TEXT_GUB[93];
                    link.l1.go = "Step_9_7";
                break;
                case "Fr10OccupySD_toWeWon":
					dialog.text = DLG_TEXT_GUB[94];
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = DLG_TEXT_GUB[95];
						link.l1.go = "Step_10_4";
					}
					else
					{
						link.l1 = DLG_TEXT_GUB[96];
						link.l1.go = "Step_10_6";
					}
                break;
                case "Fr11OccupySC_toWeWon":
					dialog.text = DLG_TEXT_GUB[97];
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = DLG_TEXT_GUB[98];
						link.l1.go = "Step_11_3";
					}
					else
					{
						link.l1 = DLG_TEXT_GUB[99];
						link.l1.go = "Step_11_5";
					}
                break;
                case "QuestLineBreake":
                    dialog.text = DLG_TEXT_GUB[100];
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;	
                case "EndOfQuestLine":
                    dialog.text = DLG_TEXT_GUB[101];
                    link.l1 = DLG_TEXT_GUB[102];
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
			}
		break;
        //********************** Квест №7 голландки, Доставка письма д'Ожерону от Стэвезанта ************************
        case "Step_H7_1":
            dialog.text = DLG_TEXT_GUB[103];
            link.l1 = DLG_TEXT_GUB[104];
            link.l1.go = "Step_H7_2";
            TakeItemFromCharacter(pchar, "letter_2");
            BackItemDescribe("letter_2");
        break;
        case "Step_H7_2":
            dialog.text = DLG_TEXT_GUB[105];
            link.l1 = DLG_TEXT_GUB[106];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "2");
            pchar.questTemp.State = "DelivLettTortuga_WaitTwoHours";
            SaveCurrentQuestDateParam("questTemp");
        break;
        case "Step_H7_3":
            dialog.text = DLG_TEXT_GUB[107];
            link.l1 = DLG_TEXT_GUB[108];
            link.l1.go = "Step_H7_4";
        break;
        case "Step_H7_4":
            dialog.text = DLG_TEXT_GUB[109];
            link.l1 = DLG_TEXT_GUB[110];
            link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "3");
            pchar.questTemp.State = "DelivLettTortuga_SnapMeeting";
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_HolLineQ7");
            GiveItem2Character(pchar,"letter_1");
            LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload1_back", true);
            LocatorReloadEnterDisable("Tortuga_town", "reload2_back", true);
            LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1.location = "Tortuga_town";
            Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition = "DelivLettTortuga_SnapMeeting";
        break;
        case "Step_H7_5":
            dialog.text = DLG_TEXT_GUB[111];
            link.l1 = DLG_TEXT_GUB[112];
            link.l1.go = "Step_H7_6";
        break;
        case "Step_H7_6":
            dialog.text = DLG_TEXT_GUB[113];
            link.l1 = DLG_TEXT_GUB[114];
            link.l1.go = "exit";
            pchar.questTemp.State = "DelivLettTortuga_toPortMan";
        break;
        //********************** Квест №1 французской линейки, охрана Леграна ************************
        case "Step_1_1":
            dialog.text = DLG_TEXT_GUB[115]+
				          DLG_TEXT_GUB[116];
            link.l1 = DLG_TEXT_GUB[117];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		// остальные линейки в сад -->
    		pchar.questTemp.NationQuest = FRANCE;
    		// остальные линейки в сад <--
    		pchar.questTemp.State = "Fr1Legran_toTavern";
            AddQuestRecord("Fra_Line_1_LegranDis", "1");
            sld = GetCharacter(NPC_GenerateCharacter("Legran", "officer_9", "man", "man", 40, FRANCE, -1, false));
			FantomMakeCoolFighter(sld, 40, 90, 40, "blade28", "pistol4", 120);
			sld.name = DLG_TEXT_GUB[118];
			sld.lastname = DLG_TEXT_GUB[119];
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.money = 1000000;
			sld.items.jewelry5 = 30;
			sld.items.indian6 = 1;
			sld.items.jewelry14 = 12;
			sld.items.indian2 = 1;
			sld.items.indian8 = 1;
			sld.items.indian7 = 1;
			sld.items.indian12 = 1;
			sld.items.jewelry2 = 20;
			sld.greeting = "Gr_MiddPirate";
			GiveItem2Character(sld, "cirass4");
			FreeSitLocator("Tortuga_tavern", "sit3");
            LAi_SetSitType(sld);
            ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
        break;		
		case "Step_1_2":
            dialog.text = DLG_TEXT_GUB[120];
            link.l1 = DLG_TEXT_GUB[121];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			AddCharacterExpToSkill(pchar, "Commerce", 90);
			AddCharacterExpToSkill(pchar, "Fencing", 80);
			AddCharacterExpToSkill(pchar, "Fortune",70);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        case "Step_1_3":
            dialog.text = DLG_TEXT_GUB[122];
            link.l1 = DLG_TEXT_GUB[123];
            link.l1.go = "Step_1_4";
        break;
        case "Step_1_4":
            dialog.text = DLG_TEXT_GUB[124]+
				          DLG_TEXT_GUB[125];
            link.l1 = DLG_TEXT_GUB[126];
            link.l1.go = "exit";
            pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_1_LegranDis");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -3);
			bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			//слухи			
			AddSimpleRumour(DLG_TEXT_GUB[127] + GetMainCharacterNameGen() + DLG_TEXT_GUB[128], FRANCE, 5, 1);
        break;
        case "Step_1_5":
            dialog.text = DLG_TEXT_GUB[129];
            link.l1 = DLG_TEXT_GUB[130];
            link.l1.go = "Step_1_6";
        break;
		case "Step_1_6":
            dialog.text = DLG_TEXT_GUB[131] + pchar.lastname + DLG_TEXT_GUB[132];
            link.l1 = DLG_TEXT_GUB[133];
            link.l1.go = "Step_1_7";
        break;
        case "Step_1_7":
            dialog.text = DLG_TEXT_GUB[134];
            link.l1 = DLG_TEXT_GUB[135];
            link.l1.go = "Step_1_8";
        break;
        case "Step_1_8":
            dialog.text = DLG_TEXT_GUB[136];
            link.l1 = DLG_TEXT_GUB[137];
            link.l1.go = "Step_1_9";
        break;
        case "Step_1_9":
            dialog.text = DLG_TEXT_GUB[138]; 
			link.l1 = DLG_TEXT_GUB[139];
			link.l1.go = "Step_1_10";
        break;
        case "Step_1_10":
            dialog.text = DLG_TEXT_GUB[140];
			if (sti(pchar.money) >= 1200000)
			{
				link.l1 = DLG_TEXT_GUB[141];
				link.l1.go = "Step_1_11";
				AddMoneyToCharacter(pchar, -1200000);
				NextDiag.TempNode = "First time";
			}
			else
			{
				link.l1 = DLG_TEXT_GUB[142];
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_1_10";
			}
        break;

		case "Step_1_11":
            dialog.text = DLG_TEXT_GUB[143]; 
			link.l1 = DLG_TEXT_GUB[144];
			link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "2";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[145] + GetFullName(pchar) + DLG_TEXT_GUB[146], FRANCE, 5, 1);
        break;
        //********************** Квест №2 доставка письма на Кюрасао ************************
        case "Step_2_1":
            dialog.text = DLG_TEXT_GUB[147];
			link.l1 = DLG_TEXT_GUB[148];
            link.l1.go = "Step_2_2";
        break;
        case "Step_2_2":
            dialog.text = DLG_TEXT_GUB[149];
            link.l1 = DLG_TEXT_GUB[150];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
    		pchar.questTemp.State = "Fr2Letter_toCuracao";
            AddQuestRecord("Fra_Line_2_DelivLetter", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ1");
            GiveItem2Character(pchar,"letter_1");
        break;	
        case "Step_2_3":
            dialog.text = DLG_TEXT_GUB[151];
			link.l1 = DLG_TEXT_GUB[152];
            link.l1.go = "Step_2_4";
        break;
        case "Step_2_4":
            dialog.text = DLG_TEXT_GUB[153];
			link.l1 = DLG_TEXT_GUB[154];
            link.l1.go = "Step_2_5";
        break;
        case "Step_2_5":
            dialog.text = DLG_TEXT_GUB[155];
			link.l1 = DLG_TEXT_GUB[156];
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Accuracy", 200);
			ChangeCharacterReputation(pchar, -1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[157] + GetFullName(pchar) + DLG_TEXT_GUB[158], FRANCE, 5, 1);
        break;
        case "Step_2_6":
            dialog.text = DLG_TEXT_GUB[159];
			link.l1 = DLG_TEXT_GUB[160];
            link.l1.go = "Step_2_7";
        break;
        case "Step_2_7":
            dialog.text = DLG_TEXT_GUB[161];
			link.l1 = DLG_TEXT_GUB[162];
            link.l1.go = "Step_2_8";
        break;
        case "Step_2_8":
            dialog.text = DLG_TEXT_GUB[163]+
				          DLG_TEXT_GUB[164]+
						  DLG_TEXT_GUB[165];
			link.l1 = DLG_TEXT_GUB[166];
            link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[167] + GetFullName(pchar) + DLG_TEXT_GUB[168], FRANCE, 5, 1);
		break;
        //********************** Квест №3 похищение донны Анны ************************
        case "Step_3_1":
            dialog.text = DLG_TEXT_GUB[169];
			link.l1 = DLG_TEXT_GUB[170];
            link.l1.go = "Step_3_2";
        break;
        case "Step_3_2":
            dialog.text = DLG_TEXT_GUB[171];
			link.l1 = DLG_TEXT_GUB[172];
            link.l1.go = "Step_3_3";
        break;
        case "Step_3_3":
            dialog.text = DLG_TEXT_GUB[173];
			link.l1 = DLG_TEXT_GUB[174];
            link.l1.go = "Step_3_4";
        break;
        case "Step_3_4":
            dialog.text = DLG_TEXT_GUB[175]+
						  DLG_TEXT_GUB[176]+
				          DLG_TEXT_GUB[177];
			link.l1 = DLG_TEXT_GUB[178];
            link.l1.go = "exit";
            GiveNationLicence(SPAIN, 60);
			GiveItem2Character(pchar,"DOjeronRing");
    		pchar.questTemp.State = "Fr3TakeAnna_toHavana";
            AddQuestRecord("Fra_Line_3_TakeAnna", "1");
			LocatorReloadEnterDisable("Havana_town", "houseS1", true);
        break;
        case "Step_3_5":
            dialog.text = DLG_TEXT_GUB[179];
			link.l1 = DLG_TEXT_GUB[180];
            link.l1.go = "Step_3_6";
        break;
        case "Step_3_6":
            dialog.text = DLG_TEXT_GUB[181]+
				          DLG_TEXT_GUB[182];
			link.l1 = DLG_TEXT_GUB[183];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[184] + GetFullName(pchar) + DLG_TEXT_GUB[185], FRANCE, 5, 1);
		break;
        case "Step_3_7":
			dialog.text = DLG_TEXT_GUB[186]+
				          DLG_TEXT_GUB[187];
			link.l1 = DLG_TEXT_GUB[188];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "4";
            pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
            TakeItemFromCharacter(pchar, "letter_open");
            BackItemDescribe("letter_open");
			TakeNationLicence(SPAIN);
			AddMoneyToCharacter(pchar, 25000);
            sld = characterFromId("AnnaDeLeiva");
            RemovePassenger(pchar, sld);
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // уберем нпс
			pchar.questTemp.AnnaIsLife = true; //но оставим флаг на пятый квест
			//==> вешаем прерывание на узнавание в таверне.
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1 = "location";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1.location = "Havana_tavern";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition = "Fr3_AfterAnna_IKnowYou";			
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[189] + GetFullName(pchar) + DLG_TEXT_GUB[190], FRANCE, 5, 1);
		break;

        //********************** Квест №4  Солей Руаяль ************************		
		case "Step_4_1":
            dialog.text = DLG_TEXT_GUB[191];
			link.l1 = DLG_TEXT_GUB[192];
            link.l1.go = "Step_4_2";
        break;
		case "Step_4_2":
            dialog.text = DLG_TEXT_GUB[193];
			link.l1 = DLG_TEXT_GUB[194];
            link.l1.go = "Step_4_3";
        break;
		case "Step_4_3":
            dialog.text = DLG_TEXT_GUB[195]+
				          DLG_TEXT_GUB[196];
			link.l1 = DLG_TEXT_GUB[197];
            link.l1.go = "Step_4_4";
        break;
		case "Step_4_4":
            dialog.text = DLG_TEXT_GUB[198];
			link.l1 = DLG_TEXT_GUB[199];
            link.l1.go = "Step_4_5";
        break;
		case "Step_4_5":
            dialog.text = DLG_TEXT_GUB[200] + GetFullName(characterFromId("BasTer_Mayor")) + ".";
			link.l1 = DLG_TEXT_GUB[201];
            link.l1.go = "Step_4_6";
        break;
		case "Step_4_6":
            dialog.text = DLG_TEXT_GUB[202];
			link.l1 = DLG_TEXT_GUB[203];
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr4SoleiRoyal_toPortMan";
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "1");
        break;
		case "Step_4_7":
            dialog.text = DLG_TEXT_GUB[204];
			link.l1 = DLG_TEXT_GUB[205];
            link.l1.go = "Step_4_8";
        break;
		case "Step_4_8":
            dialog.text = DLG_TEXT_GUB[206];
			link.l1 = DLG_TEXT_GUB[207];
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[208], FRANCE, 5, 1);
        break;
		case "Step_4_9":
            dialog.text = DLG_TEXT_GUB[209];
			link.l1 = DLG_TEXT_GUB[210];
            link.l1.go = "Step_4_10";
        break;
		case "Step_4_10":
            dialog.text = DLG_TEXT_GUB[211]+
				          DLG_TEXT_GUB[212];
			link.l1 = DLG_TEXT_GUB[213];
            link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[214], FRANCE, 5, 1);
        break;
		case "Step_4_11":
            dialog.text = DLG_TEXT_GUB[215];
			link.l1 = DLG_TEXT_GUB[216];
            link.l1.go = "Step_4_12";
        break;
		case "Step_4_12":
            dialog.text = DLG_TEXT_GUB[217];
			link.l1 = DLG_TEXT_GUB[218];
            link.l1.go = "Step_4_check";
			AddMoneyToCharacter(pchar, 28000);  
            pchar.questTemp.Waiting_time = "8";
        break;
		case "Step_4_check":
			if (CheckAttribute(pchar, "questTemp.AnnaIsLife"))
			{
				pchar.questTemp.CurQuestNumber = "5";
				DeleteAttribute(pchar, "questTemp.AnnaIsLife");
			}
			else pchar.questTemp.CurQuestNumber = "6";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[219], FRANCE, 5, 1);
			DialogExit();
        break;
        //********************** Квест №6. Доставка письма Олоне ************************	
		case "Step_6_1":
            dialog.text = DLG_TEXT_GUB[220];
			link.l1 = DLG_TEXT_GUB[221];
            link.l1.go = "Step_6_2";
        break;
		case "Step_6_2":
            dialog.text = DLG_TEXT_GUB[222];
			link.l1 = DLG_TEXT_GUB[223];
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
    		pchar.questTemp.State = "Fr5Olone_toGuadeloupe";
            AddQuestRecord("Fra_Line_6_Olone", "1");
            ChangeItemDescribe("letter_1", "itmdescr_letter_1_FraLineQ6");
            GiveItem2Character(pchar,"letter_1");
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1.location = "Guadeloupe";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition = "Fr6Olone_GuadeloupeBattle";
			//==> Олоне
            sld = GetCharacter(NPC_GenerateCharacter("Olone", "BigPirate", "man", "man", 45, FRANCE, -1, false));
            FantomMakeCoolSailor(sld, SHIP_FRIGATE, DLG_TEXT_GUB[224], CANNON_TYPE_CULVERINE_LBS32, 90, 80, 80);
			FantomMakeCoolFighter(sld, 45, 100, 90, "blade28", "pistol5", 200);
			sld.name = DLG_TEXT_GUB[225];
			sld.lastname = DLG_TEXT_GUB[226];
            sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.CompanionEnemyEnable = false; 
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			sld.RebirthPhantom = true;
			sld.greeting = "Gr_EvilPirate";
			ChangeCharacterReputation(sld, -100);
            LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
            ChangeCharacterAddressGroup(sld, "BasTer_houseF1", "goto", "goto5");
        break;
		case "Step_6_3":
            dialog.text = DLG_TEXT_GUB[227];
			link.l1 = DLG_TEXT_GUB[228];
            link.l1.go = "Step_6_4";
        break;
		case "Step_6_4":
            dialog.text = DLG_TEXT_GUB[229];
			link.l1 = DLG_TEXT_GUB[230];
            link.l1.go = "Step_6_5";
        break;
		case "Step_6_5":
            dialog.text = DLG_TEXT_GUB[231]+
				          DLG_TEXT_GUB[232];
			link.l1 = DLG_TEXT_GUB[233];
            link.l1.go = "Step_6_6";
        break;
		case "Step_6_6":
            dialog.text = DLG_TEXT_GUB[234];
			link.l1 = DLG_TEXT_GUB[235];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", 170);
			AddCharacterExpToSkill(pchar, "Sneak", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[236], FRANCE, 5, 1);
        break;
		case "Step_6_7":
            dialog.text = DLG_TEXT_GUB[237];
			link.l1 = DLG_TEXT_GUB[238];
            link.l1.go = "Step_6_8";
        break;
		case "Step_6_8":
            dialog.text = DLG_TEXT_GUB[239];
			link.l1 = DLG_TEXT_GUB[240];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 6);
			AddCharacterExpToSkill(pchar, "Grappling", 220);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Defence", 280);
			AddCharacterExpToSkill(pchar, "Accuracy", 190);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[241], FRANCE, 5, 1);
        break;
		case "Step_6_9":
            dialog.text = DLG_TEXT_GUB[242];
			link.l1 = DLG_TEXT_GUB[243];
            link.l1.go = "Step_6_10";
        break;
		case "Step_6_10":
            dialog.text = DLG_TEXT_GUB[244];
			link.l1 = DLG_TEXT_GUB[245];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 2);	
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Sneak", 190);
			AddCharacterExpToSkill(pchar, "Defence", 150);
			AddCharacterExpToSkill(pchar, "Accuracy", 220);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
        break;
        //********************** Квест №7. Вызволение из тюрьмы Рока Бральзильца ************************	
		case "Step_7_1":
            dialog.text = DLG_TEXT_GUB[246];
			link.l1 = DLG_TEXT_GUB[247];
            link.l1.go = "Step_7_2";
        break;
		case "Step_7_2":
            dialog.text = DLG_TEXT_GUB[248];
			link.l1 = DLG_TEXT_GUB[249];
            link.l1.go = "Step_7_3";
        break;
		case "Step_7_3":
            dialog.text = DLG_TEXT_GUB[250];
			link.l1 = DLG_TEXT_GUB[251];
            link.l1.go = "Step_7_4";
        break;
		case "Step_7_4":
            dialog.text = DLG_TEXT_GUB[252];
			link.l1 = DLG_TEXT_GUB[253];
            link.l1.go = "Step_7_5";
        break;
		case "Step_7_5":
            dialog.text = DLG_TEXT_GUB[254];
			link.l1 = DLG_TEXT_GUB[255];
            link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
			GiveNationLicence(SPAIN, 20);
			SetNationRelation2MainCharacter(SPAIN, RELATION_NEUTRAL);
    		pchar.questTemp.State = "Fr7RockBras_toSeekPlace";
            AddQuestRecord("Fra_Line_7_RockBras", "1");
			SaveCurrentQuestDateParam("questTemp");
			//==> Бразильца - в инквизицию. 
            sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "bocman", "man", "man", 30, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 90, 90, "", "", 80);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
			sld.RebirthPhantom = true;
        	sld.name 	= DLG_TEXT_GUB[256];
        	sld.lastname 	= DLG_TEXT_GUB[257];
			LAi_LoginInCaptureTown(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetGroundSitType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison9");
        break;
		case "Step_7_6":
            dialog.text = DLG_TEXT_GUB[258]+
				          DLG_TEXT_GUB[259];
			link.l1 = DLG_TEXT_GUB[260];
            link.l1.go = "Step_7_exit";	
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[261] + GetFullName(pchar) + DLG_TEXT_GUB[262], FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "35";
        break;
		case "Step_7_7":
            dialog.text = DLG_TEXT_GUB[263]+
				          DLG_TEXT_GUB[264];
			link.l1 = DLG_TEXT_GUB[265];
            link.l1.go = "Step_7_exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 100);
			AddCharacterExpToSkill(pchar, "Defence", 100);
			AddCharacterExpToSkill(pchar, "Cannons", 100);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[266] + GetFullName(pchar) + DLG_TEXT_GUB[267], FRANCE, 5, 1);
            pchar.questTemp.Waiting_time = "15";
        break;
		case "Step_7_exit":
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
			TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
            sld = characterFromId("RockBrasilian");
			DeleteAttribute(sld, "RebirthPhantom");
         	sld.LifeDay = 0; // уберем нпс
			DialogExit();
        break;
		case "Step_7_8":
            dialog.text = DLG_TEXT_GUB[268];
			link.l1 = DLG_TEXT_GUB[269];
            link.l1.go = "Step_7_9";
        break;
		case "Step_7_9":
            dialog.text = DLG_TEXT_GUB[270];
			link.l1 = DLG_TEXT_GUB[271];
            link.l1.go = "Step_7_Rock";
			AddMoneyToCharacter(pchar, 30000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
            TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);	
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[272] + GetFullName(pchar) + DLG_TEXT_GUB[273], FRANCE, 5, 1);
        break;
		case "Step_7_Rock":
			sld = characterFromId("RockBrasilian");
			RemovePassenger(PChar, sld);
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			DialogExit();
        break;
        //********************** Квест №8. Встреча с тремя корсарами ************************	
		case "Step_8_1":
            dialog.text = DLG_TEXT_GUB[274];
			link.l1 = DLG_TEXT_GUB[275];
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr8ThreeCorsairs_toBonrepo";
            AddQuestRecord("Fra_Line_8_ThreeCorsairs", "1");
			//==> маркиз Бонрепо.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= DLG_TEXT_GUB[276];
        	sld.lastname 	= DLG_TEXT_GUB[277];
			sld.greeting = "Gr_QuestMan";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
		case "Step_8_2":
            dialog.text = DLG_TEXT_GUB[278];
			link.l1 = DLG_TEXT_GUB[279];
            link.l1.go = "Step_8_3";
        break;
		case "Step_8_3":
            dialog.text = DLG_TEXT_GUB[280];
			link.l1 = DLG_TEXT_GUB[281];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "12";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", -100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[282] + GetMainCharacterNameDat() + DLG_TEXT_GUB[283], FRANCE, 5, 1);
        break;
        //********************** Квест №9. Отбить нападение на Порт-о-Принс ************************	
		case "Step_9_1":
            dialog.text = DLG_TEXT_GUB[284];
			link.l1 = DLG_TEXT_GUB[285];
            link.l1.go = "Step_9_11";
        break;
		case "Step_9_11":
            dialog.text = DLG_TEXT_GUB[286]+
				          DLG_TEXT_GUB[287];
			link.l1 = DLG_TEXT_GUB[288];
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr9GuardPP_toPortPax";
            AddQuestRecord("Fra_Line_9_GuardPortPax", "1");
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			sld.Ship.Name = DLG_TEXT_GUB[289];
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");	
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);	
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			SetTimerCondition("Fr9GuardPP_Late", 0, 0, 5, false);
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr9GuardPP_Fight.win_condition.l1.location = "Hispaniola2";
            Pchar.quest.Fr9GuardPP_Fight.win_condition = "Fr9GuardPP_Fight";
        break;
		case "Step_9_2":
            dialog.text = DLG_TEXT_GUB[290];
			link.l1 = DLG_TEXT_GUB[291];
            link.l1.go = "Step_9_3";
        break;
		case "Step_9_3":
            dialog.text = DLG_TEXT_GUB[292]+
				          DLG_TEXT_GUB[293];
			link.l1 = DLG_TEXT_GUB[294];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "18";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
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
			AddSimpleRumour(DLG_TEXT_GUB[295] + GetFullName(pchar) + DLG_TEXT_GUB[296], FRANCE, 5, 1);
        break;
		case "Step_9_4":
            dialog.text = DLG_TEXT_GUB[297];
			link.l1 = DLG_TEXT_GUB[298];
            link.l1.go = "Step_9_5";
        break;
		case "Step_9_5":
            dialog.text = DLG_TEXT_GUB[299];
			link.l1 = DLG_TEXT_GUB[300];
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[301], FRANCE, 5, 1);
        break;
		case "Step_9_6":
            dialog.text = DLG_TEXT_GUB[302];
			link.l1 = DLG_TEXT_GUB[303];
            link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[304], FRANCE, 5, 1);
        break;
		case "Step_9_7":
            dialog.text = DLG_TEXT_GUB[305];
			link.l1 = DLG_TEXT_GUB[306];
            link.l1.go = "exit";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[307], FRANCE, 5, 1);
        break;
        //********************** Квест №10. Захват Санто-Доминго ************************	
		case "Step_10_1":
            dialog.text = DLG_TEXT_GUB[308];
			link.l1 = DLG_TEXT_GUB[309];
            link.l1.go = "Step_10_2";
        break;
		case "Step_10_2":
            dialog.text = DLG_TEXT_GUB[310];
			link.l1 = DLG_TEXT_GUB[311];
            link.l1.go = "Step_10_3";
        break;
		case "Step_10_3":
            dialog.text = DLG_TEXT_GUB[312];
			link.l1 = DLG_TEXT_GUB[313];
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr10OccupySD_toSantoDomingo";
            AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "1");
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			characters[GetCharacterIndex("SantoDomingo_Mayor")].dialog.captureNode = "FraLine10Quest_OccupySD"; //капитулянтская нода мэра
        break;
		case "Step_10_4":
            dialog.text = DLG_TEXT_GUB[314];
			link.l1 = DLG_TEXT_GUB[315];
            link.l1.go = "Step_10_5";
        break;
		case "Step_10_5":
            dialog.text = DLG_TEXT_GUB[316];
			link.l1 = DLG_TEXT_GUB[317];
            link.l1.go = "exit";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_12_EndOfWar");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause   = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "FencingLight", -130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -130);
			AddCharacterExpToSkill(pchar, "Fencing", -130);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[318], FRANCE, 5, 1);
        break;
		case "Step_10_6":
            dialog.text = DLG_TEXT_GUB[319]+
				          DLG_TEXT_GUB[320];
			link.l1 = DLG_TEXT_GUB[321];
            link.l1.go = "Step_10_7";
        break;
		case "Step_10_7":
            dialog.text = DLG_TEXT_GUB[322];
			link.l1 = DLG_TEXT_GUB[323];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 40000);
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 330);
			AddCharacterExpToSkill(pchar, "Fortune", 360);
			AddCharacterExpToSkill(pchar, "Accuracy", 320);
			AddCharacterExpToSkill(pchar, "Grappling", 350);
			AddCharacterExpToSkill(pchar, "Defence", 350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[324], FRANCE, 5, 1);
        break;
        //********************** Квест №11. Захват Санта-Каталины ************************
		case "Step_11_1":
            dialog.text = DLG_TEXT_GUB[325];
			link.l1 = DLG_TEXT_GUB[326];
            link.l1.go = "Step_11_2";
        break;
		case "Step_11_2":
            dialog.text = DLG_TEXT_GUB[327];
			link.l1 = DLG_TEXT_GUB[328];
            link.l1.go = "exit";
    		pchar.questTemp.State = "Fr11OccupySC_toSantaCatalina";
            AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "1");
			characters[GetCharacterIndex("SantaCatalina_Mayor")].dialog.captureNode = "FraLine11Quest_OccupySC"; //капитулянтская нода мэра
        break;
		case "Step_11_3":
            dialog.text = DLG_TEXT_GUB[329];
			link.l1 = DLG_TEXT_GUB[330];
            link.l1.go = "Step_11_4";
        break;
		case "Step_11_4":
            dialog.text = DLG_TEXT_GUB[331];
			link.l1 = DLG_TEXT_GUB[332];
            link.l1.go = "Step_11_2";
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
            DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause   = false; // Конец линейки
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			AddCharacterExpToSkill(pchar, "Repair", -550);
			AddCharacterExpToSkill(pchar, "Pistol", -530);
			AddCharacterExpToSkill(pchar, "Fortune", -560);
			AddCharacterExpToSkill(pchar, "Accuracy", -520);
			AddCharacterExpToSkill(pchar, "Grappling", -550);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[333], FRANCE, 5, 1);
        break;
		case "Step_11_5":
            dialog.text = DLG_TEXT_GUB[334];
			link.l1 = DLG_TEXT_GUB[335];
            link.l1.go = "Step_11_6";
        break;
		case "Step_11_6":
            dialog.text = DLG_TEXT_GUB[336];
			link.l1 = DLG_TEXT_GUB[337];
            link.l1.go = "Step_11_7";
        break;
		case "Step_11_7":
            dialog.text = DLG_TEXT_GUB[338];
			link.l1 = DLG_TEXT_GUB[339];
            link.l1.go = "Step_11_8";
        break;
		case "Step_11_8":
            dialog.text = DLG_TEXT_GUB[340];
			link.l1 = DLG_TEXT_GUB[341];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "10";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[342], FRANCE, 5, 1);
        break;
        //********************** Квест №12. Завершение линейки ************************
		case "Step_12_1":
            dialog.text = DLG_TEXT_GUB[343]+
				          DLG_TEXT_GUB[344];
			link.l1 = DLG_TEXT_GUB[345];
            link.l1.go = "Step_12_2";
        break;
		case "Step_12_2":
            dialog.text = DLG_TEXT_GUB[346];
			link.l1 = DLG_TEXT_GUB[347];
            link.l1.go = "Step_12_3";
        break;
		case "Step_12_3":
            dialog.text = DLG_TEXT_GUB[348];
			link.l1 = DLG_TEXT_GUB[349];
            link.l1.go = "exit";
			pchar.questTemp.State = "Fr12EndWar_toBorepo";
			AddQuestRecord("Fra_Line_12_EndOfWar", "1");
			//==> маркиз Бонрепо.
            sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
            sld.Dialog.Filename    = "Quest\FraLineNpc_1.c";
        	sld.name 	= DLG_TEXT_GUB[350];
        	sld.lastname 	= DLG_TEXT_GUB[351];
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
