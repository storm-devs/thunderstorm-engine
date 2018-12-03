#include "TEXT\DIALOGS\Governor\eng_Governor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
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
                                dialog.text = DLG_TEXT_GUB[13];
                                link.l1 = DLG_TEXT_GUB[14];
                                link.l1.go = "Step_2_1";
                            break;
                            case "3":   // раньше тройки не было, теперь нужно для того, чтобы ГГ мог взять квест №4 без квеста №3.
                                dialog.text = DLG_TEXT_GUB[15];
                                link.l1 = DLG_TEXT_GUB[16];
                                link.l1.go = "exit";
                                pchar.questTemp.Waiting_time = "2";
                                SaveCurrentQuestDateParam("questTemp");
                                pchar.questTemp.CurQuestNumber = "4";
                            break;
                            case "4":
                                dialog.text = DLG_TEXT_GUB[17];
                                link.l1 = DLG_TEXT_GUB[18];
                                link.l1.go = "Step_4_0";
                            break;
                            case "5":
                                dialog.text = DLG_TEXT_GUB[19];
                                link.l1 = DLG_TEXT_GUB[20];
                                link.l1.go = "Step_5_1";
                            break;
                            case "6":
                                dialog.text = DLG_TEXT_GUB[21];
                                link.l1 = DLG_TEXT_GUB[22];
                                link.l1.go = "Step_6_1";
                            break;
                            case "7":
                                dialog.text = DLG_TEXT_GUB[23];
                                link.l1 = DLG_TEXT_GUB[24];
                                link.l1.go = "Step_7_1";
                                // ==> Убираем Морриса Уильямса
                                sld = characterFromID("Morris_Willams");
                        	    sld.LifeDay = 1; // уберем нпс на след.день.
                        	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
                            break;
                            case "8":
                                dialog.text = DLG_TEXT_GUB[25];
                                link.l1 = DLG_TEXT_GUB[26];
                                link.l1.go = "Step_8_1";
                            break;
                            case "9":
                                dialog.text = DLG_TEXT_GUB[27];
                                link.l1 = DLG_TEXT_GUB[28];
                                link.l1.go = "Step_9_1";
                                link.l2 = DLG_TEXT_GUB[29];
                                link.l2.go = "exit";
                            break;
                            case "10":
                                dialog.text = DLG_TEXT_GUB[30];
                                link.l1 = DLG_TEXT_GUB[31];
                                link.l1.go = "exit";
                                pchar.questTemp.State = "SpanishAttack_ShipsInShore";
                                SetQuestHeader("Eng_Line_10_SpanishAttack");
                                AddQuestRecord("Eng_Line_10_SpanishAttack", "1");
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1 = "location";
                                Pchar.quest.SpanishAttack_Battle.win_condition.l1.location = "Jamaica";
                                Pchar.quest.SpanishAttack_Battle.win_condition = "SpanishAttack_Battle";
                                ChangeCharacterAddress(characterFromID("Henry Morgan"), "None", "");
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
                            case "13":
                                dialog.text = DLG_TEXT_GUB[36];
                                link.l1 = DLG_TEXT_GUB[37];
                                link.l1.go = "Step_12_5";
                            break;
                        }
                    }
                break;

                case "":           // Квест №1 - сопровождение Альбермаля
                    dialog.text = DLG_TEXT_GUB[38];
                    link.l1 = DLG_TEXT_GUB[39];
                    link.l1.go = "Step_1_1";
                    link.l2 = DLG_TEXT_GUB[40];
                    link.l2.go = "exit";
                break;
                case "Albermal_good_time":                  // Геймер успел доставить Альбермаля за неделю.
                    dialog.text = DLG_TEXT_GUB[41]+
                                  DLG_TEXT_GUB[42]+
                                  DLG_TEXT_GUB[43];
                    link.l1 = DLG_TEXT_GUB[44];
                    link.l1.go = "exit";
    				AddMoneyToCharacter(pchar, 50000);
    				ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
    				AddCharacterExpToSkill(pchar, "Defence", 100);
    				AddTitleNextRate(sti(NPChar.nation), 1);
                    CloseQuestHeader("Eng_Line_1_Albermal");
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    TakeItemFromCharacter(pchar, "letter_Albermal");
					//слухи
					AddSimpleRumour(DLG_TEXT_GUB[45] + GetMainCharacterNameGen() + DLG_TEXT_GUB[46], ENGLAND, 5, 1);
                break;
                case "Albermal_late":  // Геймер не успел за неделю доставить Альбермаля.
                    dialog.text = DLG_TEXT_GUB[47];
                    link.l1 = DLG_TEXT_GUB[48];
                    link.l1.go = "Step_1_4";
                break;
                case "after_talks_with_pirates":  // После опроса пиратов
                    dialog.text = DLG_TEXT_GUB[49];
                    link.l1 = DLG_TEXT_GUB[50];
                    link.l1.go = "Step_2_3";
                break;
                case "Intelligence_Curacao_Sink":  // Голландский флейт с инфой на борту был потоплен, провал миссии
                    dialog.text = DLG_TEXT_GUB[51];
                    link.l1 = DLG_TEXT_GUB[52];
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_Boarding":  // Миссия выполнена, голландский флейт взят на абордаж
                    dialog.text = DLG_TEXT_GUB[53];
                    link.l1 = DLG_TEXT_GUB[54];
                    link.l1.go = "Step_4_2";
                break;
                case "Intelligence_Curacao_BoardingNotFoundLetter":  // Миссия провалена, голландский флейт взят на абордаж, но письмо не найдено
                    dialog.text = DLG_TEXT_GUB[55];
                    link.l1 = DLG_TEXT_GUB[56];
                    link.l1.go = "Step_4_1";
                break;
                case "Intelligence_Curacao_OutPrison":  // Миссия провалена, ГГ побывал в тюрьме
                    dialog.text = DLG_TEXT_GUB[57];
                    link.l1 = DLG_TEXT_GUB[58];
                    link.l1.go = "Step_4_4";
                break;
                case "Intelligence_Curacao_FightGard": // Миссия провалена, ГГ дрался и ушел из города ни с чем
                    dialog.text = DLG_TEXT_GUB[59];
                    link.l1 = DLG_TEXT_GUB[60];
                    link.l1.go = "Step_4_5";
                break;
                case "AttackFortOrange_WeWin":   // Форт Оранж взят.
                    dialog.text = DLG_TEXT_GUB[61];
                    link.l1 = DLG_TEXT_GUB[62];
                    link.l1.go = "Step_5_2";
                break;
                case "MorrisWillams_AfterFirstTalkingWithMorris": // Получено согласие Морриса Уильямса зайти в Порт Рояль.
                    dialog.text = DLG_TEXT_GUB[63] + GetFullName(pchar) + "?";
                    link.l1 = DLG_TEXT_GUB[64];
                    link.l1.go = "Step_6_2";
                break;
                case "MorrisWillams_ToModifordForCoolTalking": // На разборки после разговора с Уильямсом в таверне
                    dialog.text = DLG_TEXT_GUB[65] + GetFullName(pchar) + DLG_TEXT_GUB[66];
                    link.l1 = DLG_TEXT_GUB[67];
                    link.l1.go = "Step_6_3";
                break;
                case "MorrisWillams_ArrestedToModiford": // На разборки после разговора с начальником тюрьмы
                    dialog.text = DLG_TEXT_GUB[68] + GetFullName(pchar) + DLG_TEXT_GUB[69];
                    link.l1 = DLG_TEXT_GUB[70];
                    link.l1.go = "Step_6_6";
                break;
                case "MorrisWillams_ModifordGood5000":
                    dialog.text = DLG_TEXT_GUB[71];
                    link.l1 = DLG_TEXT_GUB[72];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_ModifordPolitic":
                    dialog.text = DLG_TEXT_GUB[73];
                    link.l1 = DLG_TEXT_GUB[74];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_SeekSpanishGoods":
                    dialog.text = DLG_TEXT_GUB[75];
                    link.l1 = DLG_TEXT_GUB[76];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoard":
                    dialog.text = DLG_TEXT_GUB[77];
                    link.l1 = DLG_TEXT_GUB[78];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceBoardNotFoundMoney":
                    dialog.text = DLG_TEXT_GUB[79];
                    link.l1 = DLG_TEXT_GUB[80];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_PinnaceSink":
                    dialog.text = DLG_TEXT_GUB[81];
                    link.l1 = DLG_TEXT_GUB[82];
                    link.l1.go = "exit";
                break;
                case "MorrisWillams_DieHard":
                    dialog.text = DLG_TEXT_GUB[83];
                    link.l1 = DLG_TEXT_GUB[84];
                    link.l1.go = "exit";
                break;
                case "SevenTreasures_GoOn":
                    dialog.text = DLG_TEXT_GUB[85];
                    link.l1 = DLG_TEXT_GUB[86];
                    link.l1.go = "exit";
                    if (CheckCharacterItem(pchar, "jewelry5"))
                    {
                        link.l1 = DLG_TEXT_GUB[87];
                        link.l1.go = "Step_7_4";
                    }
                    link.l2 = DLG_TEXT_GUB[88];
                    link.l2.go = "Step_7_10";
                break;
                case "ToMansfield_CatchToPardal":
                    dialog.text = DLG_TEXT_GUB[89];
                    link.l1 = DLG_TEXT_GUB[90];
                    link.l1.go = "Step_8_3";
                break;
                case "ToMansfield_NotFoundGaleon":
                    dialog.text = DLG_TEXT_GUB[91];
                    link.l1 = DLG_TEXT_GUB[92];
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = DLG_TEXT_GUB[93];
                        link.l1 = DLG_TEXT_GUB[94];
                    }
                    link.l1.go = "Step_8_5";
                break;
                case "ToMansfield_Boarding":
                    dialog.text = DLG_TEXT_GUB[95];
                    link.l1 = DLG_TEXT_GUB[96];
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = DLG_TEXT_GUB[97];
                        link.l1 = DLG_TEXT_GUB[98];
                    }
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 1; // признак результата завершения квеста, 1 == было захвачено письмо
        			AddCharacterExpToSkill(pchar, "Cannons", 600);
        			AddCharacterExpToSkill(pchar, "Sailing", 750);
        			AddCharacterExpToSkill(pchar, "Defence", 550);
        			AddCharacterExpToSkill(pchar, "Accuracy", 700);
        			AddTitleNextRate(sti(NPChar.nation), 1);
                break;
                case "ToMansfield_BoardingNotFoundLetter":
                    dialog.text = DLG_TEXT_GUB[99];
                    link.l1 = DLG_TEXT_GUB[100];
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = DLG_TEXT_GUB[101];
                        link.l1 = DLG_TEXT_GUB[102];
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 40);
        			AddCharacterExpToSkill(pchar, "Commerce", 50);
        			AddCharacterExpToSkill(pchar, "Defence", 20);
        			AddCharacterExpToSkill(pchar, "Leadership", 10);
        			AddTitleNextRate(sti(NPChar.nation), 0.5);
                break;
                case "ToMansfield_GaleonSink":
                    dialog.text = DLG_TEXT_GUB[103];
                    link.l1 = DLG_TEXT_GUB[104];
                    if (CheckAttribute(npchar , "TempQuest.KnowAboutModiford"))
                    {
                        dialog.text = DLG_TEXT_GUB[105];
                        link.l1 = DLG_TEXT_GUB[106];
                    }
                    link.l1.go = "Step_8_5";
        			AddCharacterExpToSkill(pchar, "Repair", 5);
        			AddCharacterExpToSkill(pchar, "Commerce", 10);
        			AddCharacterExpToSkill(pchar, "Cannons", -50);
        			AddCharacterExpToSkill(pchar, "Accuracy", -70);
        			AddCharacterExpToSkill(pchar, "Fencing", -100);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "ToMansfield_DidNotFindBecaners":
                    dialog.text = DLG_TEXT_GUB[107];
                    link.l1 = DLG_TEXT_GUB[108];
                    link.l1.go = "Step_8_5";
                    npchar.TempQuest.KindResult = 2; // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
        			AddCharacterExpToSkill(pchar, "Cannons", 10);
        			AddCharacterExpToSkill(pchar, "Pistol", -200);
        			AddCharacterExpToSkill(pchar, "Defence", -100);
        			AddCharacterExpToSkill(pchar, "Accuracy", -210);
        			AddCharacterExpToSkill(pchar, "Fencing", -400);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
                break;
                case "AttackSantiago_GoodWork":
                    dialog.text = DLG_TEXT_GUB[109];
                    link.l1 = DLG_TEXT_GUB[110];
                    link.l1.go = "Step_9_4";
                break;
                case "SpanishAttack_GoodWork":
                    dialog.text = DLG_TEXT_GUB[111];
                    link.l1 = DLG_TEXT_GUB[112];
                    link.l1.go = "Step_10_1";
                break;
                case "OccupyMein_GoOn":
                    dialog.text = DLG_TEXT_GUB[113];
                    link.l1 = DLG_TEXT_GUB[114];
                    link.l1.go = "exit";
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas"))
                    {
                        dialog.text = DLG_TEXT_GUB[115];
                        link.l1 = DLG_TEXT_GUB[116];
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = DLG_TEXT_GUB[117];
                        link.l1 = DLG_TEXT_GUB[118];
                        link.l1.go = "exit";
                    }
                    if (CheckAttribute(pchar, "questTemp.Q11_Caracas") && CheckAttribute(pchar, "questTemp.Q11_Cumana"))
                    {
                        dialog.text = DLG_TEXT_GUB[119];
                        link.l1 = DLG_TEXT_GUB[120];
                        link.l1.go = "Step_11_2";
                    }
                break;
                case "ColonelLinch_ArrestModiford":
                    dialog.text = DLG_TEXT_GUB[121];
                    link.l1 = DLG_TEXT_GUB[122];
                    link.l1.go = "Step_12_2";
                break;
                case "ColonelLinch_ModifordArrested":
                    dialog.text = DLG_TEXT_GUB[123];
                    link.l1 = DLG_TEXT_GUB[124];
                    link.l1.go = "exit";
                    pchar.questTemp.State = "empty";
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.CurQuestNumber = "13";
                    pchar.questTemp.Waiting_time = "30";
                    CloseQuestHeader("Eng_Line_12_ColonelLinch");
                break;
                case "QuestLineBreake":
                    dialog.text = DLG_TEXT_GUB[125];
                    link.l1 = "...";
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
                case "EndOfQuestLine":
                    dialog.text = DLG_TEXT_GUB[126];
                    link.l1 = DLG_TEXT_GUB[127];
                    link.l1.go = "exit";
                    bWorldAlivePause   = false; // Конец линейки
                break;
             }
		break;

		case "Step_1_1":
            dialog.text = DLG_TEXT_GUB[128]+
                          DLG_TEXT_GUB[129];
            link.l1 = DLG_TEXT_GUB[130];
            link.l1.go = "Step_1_2";
        break;

        case "Step_1_2":
            dialog.text = DLG_TEXT_GUB[131];
            link.l1 = DLG_TEXT_GUB[132];
            link.l1.go = "Step_1_3";
        break;

        case "Step_1_3":
            dialog.text = DLG_TEXT_GUB[133];
            link.l1 = DLG_TEXT_GUB[134];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = ENGLAND;
			// остальные линейки в сад <--
            pchar.questTemp.State = "to_Albermal";               // переменная состояния квеста для линеек
            sld = GetCharacter(NPC_GenerateCharacter("Albermal", "Albermal", "man", "man", 10, ENGLAND, -1, false));
        	sld.name 	= DLG_TEXT_GUB[135];
        	sld.lastname = DLG_TEXT_GUB[136];
            sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_QuestMan";
        	LAi_SetHuberStayType(sld);
        	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Albermal")], "PortRoyal_RoomTownhall", "goto", "goto3");
            AddQuestRecord("Eng_Line_1_Albermal", "1");
        break;
            
        case "Step_1_4":
            dialog.text = DLG_TEXT_GUB[137];
            link.l1 = DLG_TEXT_GUB[138];
            link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			pchar.questTemp.Waiting_time = 10;
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            CloseQuestHeader("Eng_Line_1_Albermal");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            TakeItemFromCharacter(pchar, "letter_Albermal");
			AddCharacterExpToSkill(pchar, "Leadership", -70);
			//слухи			
			AddSimpleRumour(DLG_TEXT_GUB[139] + GetFullName(pchar) + DLG_TEXT_GUB[140], ENGLAND, 5, 1);
        break;

        case "Step_2_1":
            dialog.text = DLG_TEXT_GUB[141]+
                          DLG_TEXT_GUB[142];
            link.l1 = DLG_TEXT_GUB[143];
            link.l1.go = "Step_2_2";
        break;

        case "Step_2_2":
            dialog.text = DLG_TEXT_GUB[144];
            link.l1 = DLG_TEXT_GUB[145];
            link.l1.go = "Step_2_21";
        break;
        
        case "Step_2_21":
            dialog.text = DLG_TEXT_GUB[146];
            link.l1 = DLG_TEXT_GUB[147];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "go_talks_with_pirates";          // переменная состояния квеста для линеек
            AddQuestRecord("Eng_Line_2_Talking", "1");
            // ==>  Помещаем Моргана на Антигуа и даем ноду доступа к квестам
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            QuestSetCurrentNode("Henry Morgan", "EngLine_quests");
            sld = characterFromID("Henry Morgan");
            LAi_SetHuberStayType(sld);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            // ==>  Генерим и помещаем Джона Морриса в Бриджтаун и даем ноду доступа к квестам
            sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        	sld.name = DLG_TEXT_GUB[148];
        	sld.lastname = DLG_TEXT_GUB[149];
            sld.Dialog.Filename = "Quest\JohnMorris.c";
            FantomMakeCoolSailor(sld, SHIP_GALEON_H, DLG_TEXT_GUB[150], CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol3", 150);
			sld.greeting = "Gr_HeadPirates";
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.  
           	LAi_SetHuberType(sld);
        	LAi_SetLoginTime(sld, 0.0, 24.0);
        	LAi_SetHP(sld, 180.0, 180.0);
            ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
            LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
            // ==>  Даем ноду доступа к квестам Джону Моррису
            QuestSetCurrentNode("John Morris", "EngLine_quests");
            // ==>  Даем ноду доступа к квестам Джекмену
            QuestSetCurrentNode("Jackman", "EngLine_quests");
            // ==>  Даем ноду доступа к квестам Манфсфилду
            QuestSetCurrentNode("Edward Mansfield", "EngLine_quests");
            // ==>  Оформляем счетчик посещения корсаров, в итоге должен == 4
            pchar.questTemp.Count = "0";
        break;

        case "Step_2_3":
            dialog.text = DLG_TEXT_GUB[151];
            link.l1 = DLG_TEXT_GUB[152];
            link.l1.go = "Step_2_4";
        break;

        case "Step_2_4":
            if (GetQuestPastDayParam("questTemp") < 35)
            {
                dialog.text = DLG_TEXT_GUB[153];
                link.l1 = DLG_TEXT_GUB[154];
                AddMoneyToCharacter(pchar, 15000);
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Repair", 150);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddTitleNextRate(sti(NPChar.nation), 2);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            }
            else
            {
                dialog.text = DLG_TEXT_GUB[155] +
                                GetQuestPastDayParam("questTemp") + DLG_TEXT_GUB[156];
                link.l1 = DLG_TEXT_GUB[157];;
                AddMoneyToCharacter(pchar, 800);
				ChangeCharacterReputation(pchar, 1);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
            }
            link.l1.go = "exit";
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[158] + GetFullName(pchar) + DLG_TEXT_GUB[159], ENGLAND, 5, 1);
            DeleteAttribute(pchar, "questTemp.Count");
            pchar.questTemp.State = "empty";
            AddQuestRecord("Eng_Line_2_Talking", "6");
            CloseQuestHeader("Eng_Line_2_Talking");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "3";
            pchar.questTemp.Waiting_time = "70";    // Чтобы Мэдифорд дал квест №4 через 70 дней, даже если ГГ не зашел к Моргану
            // ==> Моргана - в резиденцию на Ямайке
            LAi_SetHuberType(characterFromID("Henry Morgan"));
            QuestSetCurrentNode("Henry Morgan", "hot_business");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
        break;

        case "Step_4_0":
            dialog.text = DLG_TEXT_GUB[160];
            link.l1 = DLG_TEXT_GUB[161];
            link.l1.go = "exit";
			GiveNationLicence(HOLLAND, 20);
			pchar.questTemp.State = "Intelligence_Curacao_tavern";
			SetQuestHeader("Eng_Line_4_Intelligence_Curacao");
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "1");
			SaveCurrentQuestDateParam("questTemp");
		break; 

        case "Step_4_1":
            dialog.text = DLG_TEXT_GUB[162];
            link.l1 = DLG_TEXT_GUB[163];
            link.l1.go = "exit";
			TakeNationLicence(HOLLAND);
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    //только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -140);
			AddCharacterExpToSkill(pchar, "Sneak", -180);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[164], ENGLAND, 5, 1);
        break;

        case "Step_4_2":
            dialog.text = DLG_TEXT_GUB[165]+
                          DLG_TEXT_GUB[166];
            link.l1 = DLG_TEXT_GUB[167];
            link.l1.go = "Step_4_3";
        break;

        case "Step_4_3":
            dialog.text = DLG_TEXT_GUB[168];
            link.l1 = DLG_TEXT_GUB[169];
            link.l1.go = "exit";
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "10");
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "2";
            AddMoneyToCharacter(pchar, 110000);
			AddCharacterExpToSkill(pchar, "Sailing", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 170);
			AddCharacterExpToSkill(pchar, "Grappling", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
			TakeNationLicence(HOLLAND);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[170],ENGLAND, 5, 1);
        break;

        case "Step_4_4":
            dialog.text = DLG_TEXT_GUB[171];
            link.l1 = DLG_TEXT_GUB[172];
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Leadership", -150);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[173], ENGLAND, 5, 1);
        break;

        case "Step_4_5":
            dialog.text = DLG_TEXT_GUB[174]+
                          DLG_TEXT_GUB[175];
            link.l1 = DLG_TEXT_GUB[176];
            link.l1.go = "exit";
            CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "5";
            SaveCurrentQuestDateParam("questTemp");
			TakeNationLicence(HOLLAND);
            pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Fencing", -300);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[177], ENGLAND, 5, 1);
        break;
        
        case "Step_5_1":
            dialog.text = DLG_TEXT_GUB[178]+
                          DLG_TEXT_GUB[179]+
                          DLG_TEXT_GUB[180];
            link.l1 = DLG_TEXT_GUB[181];
            link.l1.go = "exit";
         	pchar.GenQuestBox.Trinidad_Cave = true;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry3 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry4 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry5 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry7 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry8 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry10 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry14 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry17 = Rand(5)+1;
            pchar.GenQuestBox.FortOrange_townhall.box1.items.cirass4 = 1;
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			pchar.questTemp.State = "AttackFortOrange_GoToFort";
            SetQuestHeader("Eng_Line_5_AttackFortOrange");
            AddQuestRecord("Eng_Line_5_AttackFortOrange", "1");
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], false);
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1 = "location";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1.location = "FortOrange_ExitTown";
            Pchar.quest.AttackFortOrange_GoToFort.win_condition = "AttackFortOrange_GoToFort";
        break;

        case "Step_5_2":
            dialog.text = DLG_TEXT_GUB[182]+
                          DLG_TEXT_GUB[183]+
                          DLG_TEXT_GUB[184];
            link.l1 = DLG_TEXT_GUB[185];
            link.l1.go = "Step_5_3";
        break;

        case "Step_5_3":
            dialog.text = DLG_TEXT_GUB[186]+
                          DLG_TEXT_GUB[187]+
                          DLG_TEXT_GUB[188];
            link.l1 = DLG_TEXT_GUB[189];
            link.l1.go = "exit";
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            CloseQuestHeader("Eng_Line_5_AttackFortOrange");
            pchar.questTemp.CurQuestNumber = "6";
            pchar.questTemp.Waiting_time = "30"; // По идее геймер должен испытывать угрызения совести после этого задания. Пусть поболтается просто так с месяц.
            // ==> вертаем разграбленному форту Оранж нормальную жизнь.
            SetLocationCapturedState("FortOrange_town", false);
            LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], true);
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");	
			//<-- огонь и пламень
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_patch";
			AddCharacterExpToSkill(pchar, "Pistol", 250);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Repair", 350);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[190], ENGLAND, 5, 1);
        break;
        
        case "Step_6_1":
            dialog.text = DLG_TEXT_GUB[191]+
                          DLG_TEXT_GUB[192]+
                          DLG_TEXT_GUB[193];
            link.l1 = DLG_TEXT_GUB[194];
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_GoToMorrisBegin";
            SetQuestHeader("Eng_Line_6_MorrisWillams");
            AddQuestRecord("Eng_Line_6_MorrisWillams", "1");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = "Jamaica";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_ShipToPort";
        break;

        case "Step_6_2":
            dialog.text = DLG_TEXT_GUB[195];
            link.l1 = DLG_TEXT_GUB[196];
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordGood5000";
            AddMoneyToCharacter(pchar, 5000);
            AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "3");
            group_DeleteGroup("Willams_Group");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = Pchar.location.from_sea;
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_MeetWithManFromWillams";
        break;

        case "Step_6_3":
            dialog.text = DLG_TEXT_GUB[197];
            link.l1 = DLG_TEXT_GUB[198];
            link.l1.go = "Step_6_4";
        break;

        case "Step_6_4":
            dialog.text = DLG_TEXT_GUB[199];
            link.l1 = DLG_TEXT_GUB[200];
            link.l1.go = "Step_6_5";
        break;

        case "Step_6_5":
            dialog.text = DLG_TEXT_GUB[201]+
                          DLG_TEXT_GUB[202];
            link.l1 = DLG_TEXT_GUB[203];
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ModifordPolitic";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "5");
            QuestSetCurrentNode("Morris_Willams", "First time");
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[204], ENGLAND, 5, 1);
        break;

        case "Step_6_6":
            dialog.text = DLG_TEXT_GUB[205];
            link.l1 = DLG_TEXT_GUB[206];
            link.l1.go = "Step_6_7";
        break;

        case "Step_6_7":
            dialog.text = DLG_TEXT_GUB[207]+
                          DLG_TEXT_GUB[208];
            link.l1 = DLG_TEXT_GUB[209];
            link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedToUsurer";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "17");
        break;
        
        case "Step_7_1":
            dialog.text = DLG_TEXT_GUB[210]+
                          DLG_TEXT_GUB[211]+
                          DLG_TEXT_GUB[212]+
                          DLG_TEXT_GUB[213]+
                          DLG_TEXT_GUB[214]+
                          DLG_TEXT_GUB[215]+
                          DLG_TEXT_GUB[216]+
                          DLG_TEXT_GUB[217]+
                          DLG_TEXT_GUB[218]+
                          DLG_TEXT_GUB[219]+
                          DLG_TEXT_GUB[220]+
                          DLG_TEXT_GUB[221]+
                          DLG_TEXT_GUB[222]+
                          DLG_TEXT_GUB[223];
            link.l1 = DLG_TEXT_GUB[224];
            link.l1.go = "Step_7_3";
            link.l2 = DLG_TEXT_GUB[225];
            link.l2.go = "Step_7_2";
        break;

        case "Step_7_2":
            dialog.text = DLG_TEXT_GUB[226];
            link.l1 = DLG_TEXT_GUB[227];
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 3);
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "8";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.Waiting_time = "35";
            AddCharacterExpToSkill(pchar, "Leadership", -500);
            AddCharacterExpToSkill(pchar, "Cannons", -300);
            AddCharacterExpToSkill(pchar, "Sneak", -350);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[228] + GetFullName(pchar) + DLG_TEXT_GUB[229], ENGLAND, 5, 1);
        break;

        case "Step_7_3":
            dialog.text = DLG_TEXT_GUB[230];
            link.l1 = DLG_TEXT_GUB[231];
            link.l1.go = "exit";
            ChangeCharacterReputation(pchar, -4);
            pchar.questTemp.State = "SevenTreasures_GoOn";
            pchar.questTemp.GoldQtyGaveModiford = "0"; // кол-во сданное Мэдифорду
            pchar.questTemp.GoldQtyForSeek = "2100"; // кол-во, которое еще нужно разыскать
            SaveCurrentQuestDateParam("questTemp");
            SetQuestHeader("Eng_Line_7_SevenTresures");
            AddQuestRecord("Eng_Line_7_SevenTresures", "1");
            // ==> клад Томаса Уитсона в пещере близ Картахены.
         	pchar.GenQuestBox.Cartahena_Cave = true;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry5 = 300;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.statue1 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.indian17 = 1;
            pchar.GenQuestBox.Cartahena_Cave.box1.items.pistol2 = 1;
            // ==> клад Адриана Сварта на Тринидаде.
         	pchar.GenQuestBox.Trinidad_Grot = true;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry5 = 450;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.blade5 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potion2 = 10;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.potionwine = 3;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry2 = 20;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian6 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian11 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian15 = 1;
            pchar.GenQuestBox.Trinidad_Grot.box1.items.indian12 = 1;
            // ==> клад Капитана Гея в гроте на Терксе.
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 250;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade10 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
            // ==> клад Капитана Купера на Домнинике.
         	pchar.GenQuestBox.Dominica_Grot = true;
            pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 150;
            pchar.GenQuestBox.Dominica_Grot.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potion1 = 5;
            pchar.GenQuestBox.Dominica_Grot.box1.items.potionrum = 2;
            // ==> клад Джоржа Бренинхема на Каймане.
         	pchar.GenQuestBox.Caiman_Grot = true;
            pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry5 = 350;
            pchar.GenQuestBox.Caiman_Grot.box1.items.blade2 = 1;
            pchar.GenQuestBox.Caiman_Grot.box1.items.potion5 = 10;
            pchar.GenQuestBox.Caiman_Grot.box1.items.indian18 = 1;
            // ==> клад капитана Гудли на Кубе.
         	pchar.GenQuestBox.Cuba_Grot = true;
            pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry5 = 350;
            pchar.GenQuestBox.Cuba_Grot.box1.items.topor2 = 1;
            pchar.GenQuestBox.Cuba_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
            // ==> клад Абрахама Блаувельта в катакомбах Гаити рядом с городом.
         	pchar.GenQuestBox.Guadeloupe_Cave = true;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry5 = 250;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box1.items.mineral8 = 1;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry5 = 250;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry14= 10;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.potion3 = 5;
            pchar.GenQuestBox.Guadeloupe_Cave.box4.items.mineral8 = 1;
        break;

        case "Step_7_4":
            dialog.text = DLG_TEXT_GUB[232];
            link.l1 = DLG_TEXT_GUB[233] + pchar.items.jewelry5 + DLG_TEXT_GUB[234];
            link.l1.go = "Step_7_5";
            link.l2 = DLG_TEXT_GUB[235] + pchar.items.jewelry5 + DLG_TEXT_GUB[236];
            link.l2.go = "Step_7_7";
        break;

        case "Step_7_5":
            if ((sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5)) <= 2100)
            {
                pchar.questTemp.GoldQtyGaveModiford = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5);
                pchar.questTemp.GoldQtyForSeek = 2100 - sti(pchar.questTemp.GoldQtyGaveModiford);
                if (pchar.questTemp.GoldQtyForSeek != "0")
                {
                    dialog.text = DLG_TEXT_GUB[237] + pchar.items.jewelry5 + DLG_TEXT_GUB[238] + pchar.questTemp.GoldQtyGaveModiford + DLG_TEXT_GUB[239] + pchar.questTemp.GoldQtyForSeek + DLG_TEXT_GUB[240];
                    link.l1 = DLG_TEXT_GUB[241];
                    link.l1.go = "exit";
                    AddQuestRecord("Eng_Line_7_SevenTresures", "3");
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyGaveModiford", pchar.questTemp.GoldQtyGaveModiford);
                    AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyForSeek", pchar.questTemp.GoldQtyForSeek);
                }
                else
                {
                    dialog.text = DLG_TEXT_GUB[242];
                    link.l1 = DLG_TEXT_GUB[243];
                    link.l1.go = "Step_7_6";
                }
                DeleteAttribute(pchar, "items.jewelry5");
            }
            else
            {
                pchar.questTemp.GoldQtyForSeek = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5) - 2100);
                dialog.text = DLG_TEXT_GUB[244] + pchar.items.jewelry5 + DLG_TEXT_GUB[245] + pchar.questTemp.GoldQtyGaveModiford + DLG_TEXT_GUB[246] + pchar.questTemp.GoldQtyForSeek + DLG_TEXT_GUB[247];
                link.l1 = DLG_TEXT_GUB[248];
                link.l1.go = "Step_7_6";
                pchar.items.jewelry5 = pchar.questTemp.GoldQtyForSeek;
            }
        break;

        case "Step_7_6":
            dialog.text = DLG_TEXT_GUB[249];
            link.l1 = DLG_TEXT_GUB[250];
            link.l1.go = "exit";
            AddMoneyToCharacter(pchar, 70000);
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "2";
            AddQuestRecord("Eng_Line_7_SevenTresures", "2");
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
            DeleteAttribute(pchar, "questTemp.GoldQtyGaveModiford");
            DeleteAttribute(pchar, "questTemp.GoldQtyForSeek");
			AddCharacterExpToSkill(pchar, "Repair", 500);
			AddCharacterExpToSkill(pchar, "Commerce", 550);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[251], ENGLAND, 5, 1);
        break;

        case "Step_7_7":
            dialog.text = RandPhraseSimple(DLG_TEXT_GUB[252], DLG_TEXT_GUB[253]);
            link.l1 = DLG_TEXT_GUB[254];
            link.l1.go = "exit";
        break;
 
        case "Step_7_10":
			dialog.text = DLG_TEXT_GUB[255];
            link.l1 = DLG_TEXT_GUB[256];
            link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuestBox.Cartahena_Cave");
			DeleteAttribute(pchar, "GenQuestBox.Trinidad_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Terks_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Dominica_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Caiman_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Cuba_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Guadeloupe_Cave");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "8";
            pchar.questTemp.Waiting_time = "20";
            AddQuestRecord("Eng_Line_7_SevenTresures", "4");
            CloseQuestHeader("Eng_Line_7_SevenTresures");
            DeleteQuestHeader("Eng_Line_7_Second");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			ChangeCharacterReputation(pchar, -5);
			AddMoneyToCharacter(pchar, -150000);
        break;

        case "Step_8_1":
            dialog.text = DLG_TEXT_GUB[257]+
                          DLG_TEXT_GUB[258];
            link.l1 = DLG_TEXT_GUB[259];
            link.l1.go = "Step_8_2";
        break;

        case "Step_8_2":
            dialog.text = DLG_TEXT_GUB[260];
            link.l1 = DLG_TEXT_GUB[261];
            link.l1.go = "exit";
            pchar.questTemp.State = "ToMansfield_GoOn";
            SetQuestHeader("Eng_Line_8_ToMansfield");
            AddQuestRecord("Eng_Line_8_ToMansfield", "1");
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1 = "location";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1.location = "LaVega_town";
            Pchar.quest.ToMansfield_IntoTheTown.win_condition = "ToMansfield_IntoTheTown";
            SetLocationCapturedState("LaVega_town", true);
			//--> огонь и пламень
			locations[FindLocation("LaVega_town")].hidden_effects = true;
			locations[FindLocation("LaVega_ExitTown")].hidden_effects = true;	
			//<-- огонь и пламень
            Log_QuestInfo(DLG_TEXT_GUB[262]);
        break;

        case "Step_8_3":
            dialog.text = DLG_TEXT_GUB[263];
            link.l1 = DLG_TEXT_GUB[264];
            link.l1.go = "Step_8_4";
        break;

        case "Step_8_4":
            dialog.text = DLG_TEXT_GUB[265];
            link.l1 = DLG_TEXT_GUB[266];
            link.l1.go = "exit";
            npchar.TempQuest.KnowAboutModiford = 1;
        break;

        case "Step_8_5":
            dialog.text = DLG_TEXT_GUB[267];
            link.l1 = DLG_TEXT_GUB[268];
            link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "letter_open");
			BackItemDescribe("letter_open");
            DeleteAttribute(npchar, "TempQuest.KnowAboutModiford");
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "9";
            pchar.questTemp.Waiting_time = "10";
            CloseQuestHeader("Eng_Line_8_ToMansfield");
            SetLocationCapturedState("LaVega_town", false);
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("LaVega_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "hidden_effects");	
			//<-- огонь и пламень
            // ==> Мэнсфилд убит, теперь он будет Алистером Гудом.
            sld = characterFromID("Edward Mansfield");
            LAi_SetStayTypeNoGroup(sld);
            sld.model = "bocman";
        	sld.name 	= DLG_TEXT_GUB[269];
        	sld.lastname = DLG_TEXT_GUB[270];
            SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
            FaceMaker(sld);
            QuestSetCurrentNode("Edward Mansfield", "No_Mansfield_first_time");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Edward Mansfield")], "LaVega_townhall", "sit", "sit1");
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			AddCharacterExpToSkill(pchar, "Sailing", 550);
			AddCharacterExpToSkill(pchar, "FencingLight", 450);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[271], ENGLAND, 5, 1);
		break;
        
        case "Step_9_1":
            pchar.questTemp.State = "AttackSantiago_GoOn";
            if (!CheckAttribute(npchar, "TempQuest.KindResult")) // письмо не получено, но в курсе нападения испанцев
            {
                dialog.text = DLG_TEXT_GUB[272];
                link.l1 = DLG_TEXT_GUB[273];
                link.l1.go = "Step_9_2";
            }
            else if (npchar.TempQuest.KindResult == 2) // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
            {
                dialog.text = DLG_TEXT_GUB[274];
                link.l1 = DLG_TEXT_GUB[275];
                link.l1.go = "Step_9_2";
            }
            else // признак результата завершения квеста, 1 == было захвачено письмо
            {
                dialog.text = DLG_TEXT_GUB[276];
                link.l1 = DLG_TEXT_GUB[277];
                link.l1.go = "Step_9_2";
            }
            Log_QuestInfo(DLG_TEXT_GUB[278]);
            DeleteAttribute(npchar, "TempQuest.KindResult");
			characters[GetCharacterIndex("Santiago_Mayor")].dialog.captureNode = "EL9_SantiagoAttack"; //капитулянтская нода мэра
        break;

        case "Step_9_2":
            dialog.text = DLG_TEXT_GUB[279];
            link.l1 = DLG_TEXT_GUB[280];
            link.l1.go = "Step_9_3";
        break;

        case "Step_9_3":
            dialog.text = DLG_TEXT_GUB[281];
            link.l1 = DLG_TEXT_GUB[282];
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_9_AttackSantiago");
            AddQuestRecord("Eng_Line_9_AttackSantiago", "1");
        break;

        case "Step_9_4":
            dialog.text = DLG_TEXT_GUB[283] + pchar.name + DLG_TEXT_GUB[284];
            link.l1 = DLG_TEXT_GUB[285];
            link.l1.go = "Step_9_5";
            QuestSetCurrentNode("Santiago_Mayor", "First time");
        break;

        case "Step_9_5":
            dialog.text = DLG_TEXT_GUB[286]+
                          DLG_TEXT_GUB[287]+
                          DLG_TEXT_GUB[288];
            link.l1 = DLG_TEXT_GUB[289];
            link.l1.go = "exit";
            QuestSetCurrentNode("Henry Morgan", "Give_blade");
            sld = characterFromID("Himenes");
            RemovePassenger(pchar, sld);
    	    sld.LifeDay = 1; // уберем нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "10";
            pchar.questTemp.Waiting_time = "20";
            CloseQuestHeader("Eng_Line_9_AttackSantiago");
			AddCharacterExpToSkill(pchar, "Repair", 550);
			AddCharacterExpToSkill(pchar, "Cannons", 760);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Pistol", 300);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[290], ENGLAND, 5, 1);
        break;
        
        case "Step_10_1":
            dialog.text = DLG_TEXT_GUB[291];
            link.l1 = DLG_TEXT_GUB[292];
            link.l1.go = "Step_10_2";
        break;

        case "Step_10_2":
            dialog.text = DLG_TEXT_GUB[293]+
                          DLG_TEXT_GUB[294];
            link.l1 = DLG_TEXT_GUB[295];
            link.l1.go = "exit";
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "11";
            pchar.questTemp.Waiting_time = "7";
            CloseQuestHeader("Eng_Line_10_SpanishAttack");
			AddCharacterExpToSkill(pchar, "Repair", 600);
			AddCharacterExpToSkill(pchar, "Leadership", 550);
			AddCharacterExpToSkill(pchar, "Commerce", 600);
			AddCharacterExpToSkill(pchar, "Accuracy", 400);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 80000);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[296], ENGLAND, 10, 6);
        break;
        
        case "Step_11_1":
            dialog.text = DLG_TEXT_GUB[297]+
                          DLG_TEXT_GUB[298]+
                          DLG_TEXT_GUB[299];
            link.l1 = DLG_TEXT_GUB[300];
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_11_OccupyMein");
            AddQuestRecord("Eng_Line_11_OccupyMein", "1");
            pchar.questTemp.State = "OccupyMein_GoOn";
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Caracas_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
        break;

        case "Step_11_2":
            dialog.text = DLG_TEXT_GUB[301]+
                          DLG_TEXT_GUB[302];
            link.l1 = DLG_TEXT_GUB[303];
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Q11_Cumana");
            DeleteAttribute(pchar, "questTemp.Q11_Caracas");
            pchar.questTemp.State = "empty";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.CurQuestNumber = "12";
            pchar.questTemp.Waiting_time = "30";
            CloseQuestHeader("Eng_Line_11_OccupyMein");
			AddCharacterExpToSkill(pchar, "Repair", 1000);
			AddCharacterExpToSkill(pchar, "Commerce", 1600);
			AddCharacterExpToSkill(pchar, "Accuracy", 1000);
			AddCharacterExpToSkill(pchar, "Defence", 1100);
			AddCharacterExpToSkill(pchar, "Cannons", 1300);
			AddCharacterExpToSkill(pchar, "Sailing", 1200);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[304] + pchar.name + DLG_TEXT_GUB[305], ENGLAND, 5, 1);
        break;
        
        case "Step_12_1":
            dialog.text = DLG_TEXT_GUB[306]+
                          DLG_TEXT_GUB[307];
            link.l1 = DLG_TEXT_GUB[308];
            link.l1.go = "exit";
            SetQuestHeader("Eng_Line_12_ColonelLinch");
            AddQuestRecord("Eng_Line_12_ColonelLinch", "1");
            pchar.questTemp.State = "ColonelLinch_GoToKingstown";

            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1 = "location";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1.location = "SentJons_townhall";
            Pchar.quest.ColonelLinch_IntoTheResidence.win_condition = "ColonelLinch_IntoTheResidence";
        break;

        case "Step_12_2":
            dialog.text = DLG_TEXT_GUB[309];
            link.l1 = DLG_TEXT_GUB[310];
            link.l1.go = "Step_12_3";
        break;

        case "Step_12_3":
            dialog.text = DLG_TEXT_GUB[311];
            link.l1 = DLG_TEXT_GUB[312];
            link.l1.go = "Step_12_4";
        break;

        case "Step_12_4":
            pchar.nation = PIRATE;
            LAi_SetImmortal(npchar, true);
            LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), true);
            bDisableFastReload = true; // закрыть переходы.
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
            LAi_NoRebirthEnable(npchar);
            //LAi_SetActorType(npchar);
            //LAi_ActorAfraid(npchar, pchar, false);

            LAi_group_Register("EnemyFight");
           	float locx, locy, locz;
            GetCharacterPos(pchar, &locx, &locy, &locz);
			//поставим стражников во враждебную группу
			int num = FindNearCharacters(pchar, 20.0, -1.0, -1.0, 0.01, true, true);
			if(num > 0)
			{
				for(int i = 0; i < num; i++)
				{
					int idx = sti(chrFindNearCharacters[i].index);
					sld = &Characters[idx];
					if (sld.chr_ai.type == "guardian")
					{
						LAi_NoRebirthEnable(sld);
						LAi_CharacterReincarnation(sld, false, false);
						LAi_group_MoveCharacter(sld, "EnemyFight");						
					}
				}
			}
			//добавим солдат для хардокора
            string SModel;
            for (i=1; i<=3; i++)
            {
                SModel = "off_eng_"+i;
                if (i == 3) SModel = "sold_eng_3";
                sld = GetCharacter(NPC_GenerateCharacter("EngSolder"+i, SModel, "man", "man", 30, ENGLAND, 0, true));
                FantomMakeCoolFighter(sld, 30, 100, 100, "topor1", "pistol3", 250);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ColonelLinch_AfterFight");
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
			//слухи
			AddSimpleRumour(DLG_TEXT_GUB[313], ENGLAND, 5, 1);
        break;

        case "Step_12_5":
            dialog.text = DLG_TEXT_GUB[314]+
                          DLG_TEXT_GUB[315]+
                          DLG_TEXT_GUB[316]+
                          DLG_TEXT_GUB[317];
            link.l1 = DLG_TEXT_GUB[318];
            link.l1.go = "Step_12_6";
        break;

        case "Step_12_6":
            dialog.text = DLG_TEXT_GUB[319]+
                          DLG_TEXT_GUB[320];
            link.l1 = DLG_TEXT_GUB[321];
            link.l1.go = "exit";
			pchar.name = DLG_TEXT_GUB[322] + pchar.name;
            AddMoneyToCharacter(pchar, 300000);
            AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            SetNationRelationBoth(SPAIN, ENGLAND, RELATION_NEUTRAL);
            DeleteAttribute(pchar, "questTemp.Waiting_time");
            pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause   = false; // Конец линейки
        break;
        
        
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
