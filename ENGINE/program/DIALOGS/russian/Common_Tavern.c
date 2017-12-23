#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_Tavern.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]),
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]),
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "exit";
				break;
			}
			
            // homo линейка капитана Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[12] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[13],
                                    DLG_TEXT_BASE[14] + GetFullName(pchar) + DLG_TEXT_BASE[15]);
                Link.l1 = DLG_TEXT_BASE[16] + NPChar.name + DLG_TEXT_BASE[17];
				Link.l1.go = "exit";

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
            		link.l2 = DLG_TEXT_BASE[18] + NPChar.name + DLG_TEXT_BASE[19];
            		link.l2.go = "TStep_0";
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {
            		link.l2 = DLG_TEXT_BASE[20];
            		link.l2.go = "TStep_1";
                }
                
                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && pchar.questTemp.CapBloodLine.QuestRaff == true)
                {
            		link.l2 = DLG_TEXT_BASE[21];
            		link.l2.go = "TStep_5";
                }
                break;
    		}

			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = DLG_TEXT_BASE[22];
				link.l1 = DLG_TEXT_BASE[23];
				link.l1.go = "MCTavern";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasWervolf" && npchar.city == "Caracas")
			{
				dialog.text = DLG_TEXT_BASE[24];
				link.l1 = DLG_TEXT_BASE[25];
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				dialog.text = DLG_TEXT_BASE[26];
				link.l1 = DLG_TEXT_BASE[27];
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = DLG_TEXT_BASE[28];
				link.l1 = DLG_TEXT_BASE[29];
				link.l1.go = "MCCaracasAfter";
				break;
			}
			//<-- зачарованный город 

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = DLG_TEXT_BASE[30] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[31];
				Link.l1 = DLG_TEXT_BASE[32] + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[33] + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[34] + GetAddress_Form(NPChar) + " " + PChar.name + ".",
                                    DLG_TEXT_BASE[35] + GetFullName(pchar) + DLG_TEXT_BASE[36]);
				Link.l1 = DLG_TEXT_BASE[37];
				Link.l1.go = "crew hire";
				Link.l2 = DLG_TEXT_BASE[38];
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = DLG_TEXT_BASE[39];
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				link.l3 = pcharrepphrase(DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
				link.l3.go = "room";
				Link.l4 = DLG_TEXT_BASE[42] + NPChar.name + DLG_TEXT_BASE[43];
				Link.l4.go = "exit";
			}

		break;
		
		case "Meeting":
			dialog.Text = DLG_TEXT_BASE[44] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[45] + GetFullName(npchar) + DLG_TEXT_BASE[46];
			Link.l1 = DLG_TEXT_BASE[47] + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + DLG_TEXT_BASE[48];
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = DLG_TEXT_BASE[49];
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			link.l3 = pcharrepphrase(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
			link.l3.go = "room";
			Link.l4 = DLG_TEXT_BASE[52];
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = DLG_TEXT_BASE[53];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[54], DLG_TEXT_BASE[55]);
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = DLG_TEXT_BASE[56];
				link.l1 = DLG_TEXT_BASE[57];
				link.l1.go = "room";
				link.l2 = DLG_TEXT_BASE[58];
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = DLG_TEXT_BASE[59];
					link.l1 = DLG_TEXT_BASE[60];
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = DLG_TEXT_BASE[61] + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = DLG_TEXT_BASE[62];
						link.l1.go = "exit";
					}
					else
					{
						DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
						NextDiag.CurrentNode =  NextDiag.TempNode;
						DialogExit();
						LaunchHireCrew();
					}
				}
			}
		break;
		
        case "int_quests":
			dialog.text = DLG_TEXT_BASE[63];
			link.l1 = DLG_TEXT_BASE[64];
			link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[65],DLG_TEXT_BASE[66],
                                    DLG_TEXT_BASE[67]);
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = DLG_TEXT_BASE[68];
			link.l3.go = "quests";//(перессылка в файл города)
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра поп поиску шпиона
			{
				link.l4 = DLG_TEXT_BASE[69];
				if (pchar.GenQuest.SeekSpy.City == "0")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			link.l9 = DLG_TEXT_BASE[70];
			link.l9.go = "exit";
		break;
		
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[71] + NationNameGenitive(sti(pchar.nation)) + "!", DLG_TEXT_BASE[72] + NationNameAblative(sti(pchar.nation)) + DLG_TEXT_BASE[73]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[74], DLG_TEXT_BASE[75]);
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[76];
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
            {
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
    			{					
					SaveCurrentNpcQuestDateParam(npchar, "work_date");
					if (isBadReputation(pchar, 40))
					{
						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[77], DLG_TEXT_BASE[78]);
						link.l1 = RandPhraseSimple(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80]);
						link.l1.go = "exit";
						break;
					}
					switch (rand(1))
        			{
                        case 0: //конвой
                            if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
                			{
								if (GetCompanionQuantity(PChar) == COMPANION_MAX)
								{
									dialog.text = DLG_TEXT_BASE[81];
									link.l1 = DLG_TEXT_BASE[82];
									link.l1.go = "exit";
								}
								else
								{
									if (rand(5) > 1)
									{
										dialog.text = DLG_TEXT_BASE[83];
										link.l1 = RandPhraseSimple(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85]);
										link.l1.go = "ConvoyAreYouSure";
									}
									else
									{
										dialog.text = DLG_TEXT_BASE[86];
										link.l1 = RandPhraseSimple(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]);
										link.l1.go = "exit";
									}
								}
                			}							
            			break;

            			case 1: // пассажир
							if (rand(6) > 1)
							{
								dialog.Text = DLG_TEXT_BASE[89];
								link.l1 = RandPhraseSimple(DLG_TEXT_BASE[90], DLG_TEXT_BASE[91]);
								Link.l1.go = "PassangerAreYouSure";
							}
							else
							{
								dialog.text = DLG_TEXT_BASE[92];
								link.l1 = RandPhraseSimple(DLG_TEXT_BASE[93], DLG_TEXT_BASE[94]);
								link.l1.go = "exit";
							}
            			break;
        			}
    			}
    			else
    			{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[95], DLG_TEXT_BASE[96]);
					link.l1 = DLG_TEXT_BASE[97];
                    link.l1.go = "SayAgain";
    			}
			}
			link.l2 = DLG_TEXT_BASE[98];
			link.l2.go = "First time";
		break;

        case "SayAgain":
		    dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "exit";
        break;

        case "ConvoyAreYouSure":
		    dialog.text = RandPhraseSimple(DLG_TEXT_BASE[101], DLG_TEXT_BASE[102]);
			Link.l1 = DLG_TEXT_BASE[103];
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			AddDialogExitQuest("prepare_for_convoy_quest");
        break;

        case "PassangerAreYouSure":
		    dialog.text = RandPhraseSimple(DLG_TEXT_BASE[104], DLG_TEXT_BASE[105]);
			Link.l1 = DLG_TEXT_BASE[106];
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			AddDialogExitQuest("prepare_for_passenger_quest");
        break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = DLG_TEXT_BASE[107] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[108];
				link.l1 = DLG_TEXT_BASE[109];
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.State.Open") && npchar.id == "Tortuga_tavernkeeper")//исп.линейка, квест №6, блокировка спать в комнате
			{
				dialog.text = DLG_TEXT_BASE[110];
				link.l1 = DLG_TEXT_BASE[111];
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = DLG_TEXT_BASE[112];
				if (sti(pchar.money) >= 100)
				{
					link.l1 = DLG_TEXT_BASE[113];
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = DLG_TEXT_BASE[114];
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = DLG_TEXT_BASE[115];
				link.l1 = DLG_TEXT_BASE[116];
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			dialog.text = DLG_TEXT_BASE[117];
			if(!isDay())
			{
				link.l1 = DLG_TEXT_BASE[118];
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[119];
				link.l1.go = "room_night";
				link.l2 = DLG_TEXT_BASE[120];
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = DLG_TEXT_BASE[121];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT_BASE[122];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[123],
            DLG_TEXT_BASE[124]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT_BASE[125];
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = DLG_TEXT_BASE[126];
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = DLG_TEXT_BASE[127];
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[128],
            DLG_TEXT_BASE[129]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT_BASE[130];
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = DLG_TEXT_BASE[131];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT_BASE[132];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT_BASE[133],
            DLG_TEXT_BASE[134]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT_BASE[135];
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (rand(2) == 1)
            {
                Dialog.text = DLG_TEXT_BASE[136];
				link.l1 = DLG_TEXT_BASE[137];
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (rand(1) == 1)
            {
                Dialog.text = DLG_TEXT_BASE[138];
				link.l1 = DLG_TEXT_BASE[139];
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = DLG_TEXT_BASE[140];
			link.l1 = DLG_TEXT_BASE[141];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		//==> eddy. квест мэра, вопросы не замечал ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[142], 
				DLG_TEXT_BASE[143], DLG_TEXT_BASE[144], DLG_TEXT_BASE[145], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[146], DLG_TEXT_BASE[147],
                      DLG_TEXT_BASE[148], DLG_TEXT_BASE[149], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[150], 
				DLG_TEXT_BASE[151], DLG_TEXT_BASE[152], DLG_TEXT_BASE[153], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[154], DLG_TEXT_BASE[155],
                      DLG_TEXT_BASE[156], DLG_TEXT_BASE[157], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		//==> homo линейка Блада
		case "TStep_0":
			dialog.text = DLG_TEXT_BASE[158];
			link.l1 = DLG_TEXT_BASE[159];
			link.l1.go = "Exit";
			int n= FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = false;
		break;
		
		case "TStep_1":
			dialog.text = DLG_TEXT_BASE[160];
			link.l1 = DLG_TEXT_BASE[161];
			link.l1.go = "TStep_2";
		break;
		
		case "TStep_2":
			dialog.text = DLG_TEXT_BASE[162];
			link.l1 = DLG_TEXT_BASE[163];
			link.l1.go = "TStep_3";
            if (makeint(pchar.money) >= 2500)
            {
    			link.l1 = DLG_TEXT_BASE[164];
    			link.l1.go = "TStep_4";
            }
		break;
		
		case "TStep_3":
			dialog.text = DLG_TEXT_BASE[165];
			link.l1 = DLG_TEXT_BASE[166];
			link.l1.go = "exit";
		break;
		
		case "TStep_4":
			dialog.text = DLG_TEXT_BASE[167];
			link.l1 = DLG_TEXT_BASE[168];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1";
			AddQuestRecord("WeaponsForEscape", "2");

		break;
		
		case "TStep_5":
            pchar.questTemp.CapBloodLine.QuestRaff = false;
			dialog.text = DLG_TEXT_BASE[169];
            if (makeint(pchar.money) >= 500)
            {
    			link.l1 = DLG_TEXT_BASE[170];
    			link.l1.go = "TStep_6";
            }
			link.l2 = DLG_TEXT_BASE[171];
			link.l2.go = "TStep_7";
		break;
		
		case "TStep_6":
            AddMoneyToCharacter(pchar, -500);
			dialog.text = DLG_TEXT_BASE[172];
			link.l1 = DLG_TEXT_BASE[173];
			link.l1.go = "TStep_8";
		break;
		
		case "TStep_7":
			dialog.text = DLG_TEXT_BASE[174];
			link.l1 = DLG_TEXT_BASE[175];
			link.l1.go = "TStep_10";
		break;
		
		case "TStep_8":
			dialog.text = DLG_TEXT_BASE[176];
			link.l1 = DLG_TEXT_BASE[177];
			link.l1.go = "TStep_9";
		break;
		
		case "TStep_9":
            AddQuestRecord("UsurerQuest", "2");
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
			sld.name = xiDStr("Alex");       //fix имени
			sld.lastname = xiDStr("Winner");
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_Shipyard", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "TStep_10":

            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
			sld.name = xiDStr("Alex");       //fix имени
			sld.lastname = xiDStr("Winner");
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH7", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		//зачарованный город
		case "MCTavern":
			dialog.text = DLG_TEXT_BASE[178];
			link.l1 = DLG_TEXT_BASE[179];
			link.l1.go = "exit";
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.MC = "toCaracasWervolf";
			DeleteAttribute(&locations[reload_location_index], "reload.l2.disable");
			sld = GetCharacter(NPC_GenerateCharacter("CaracasWervolf", "trader_14", "man", "man", 10, PIRATE, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasWervolf";  
			sld.location	= "Caracas_tavern_upstairs";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.BreakTmplAndFight = true;
			sld.reactionOnFightModeOn = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "EnemyFight");	
		break;

		case "MCCaracasAfter":
			dialog.text = DLG_TEXT_BASE[180];
			link.l1 = DLG_TEXT_BASE[181];
			link.l1.go = "MCCaracasAfter_1";
		break;
		case "MCCaracasAfter_1":
			dialog.text = DLG_TEXT_BASE[182];
			link.l1 = DLG_TEXT_BASE[183];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MC_endCaracas");
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}
