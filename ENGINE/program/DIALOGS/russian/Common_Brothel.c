#include "TEXT\DIALOGS\Common_Brothel.h"
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp, str, str1;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = "exit";
				break;
			}
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[10] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[11],
                                    DLG_TEXT_BASE[12] + GetFullName(pchar) + DLG_TEXT_BASE[13]);
                Link.l1 = DLG_TEXT_BASE[14] + NPChar.name + DLG_TEXT_BASE[15];
				Link.l1.go = "exit";
				break;
            }
			//-->> квест пожертвования в церковь
			//результаты
			if (npchar.questChurch == "baster")
			{
				dialog.text = DLG_TEXT_BASE[16];
				link.l1 = DLG_TEXT_BASE[17];
				link.l1.go = "exit";
				link.l2 = DLG_TEXT_BASE[18];
				link.l2.go = "quests";//(перессылка в файл города)
				break;
			}
			if (npchar.questChurch == "taken")
			{
				dialog.text = DLG_TEXT_BASE[19];
				link.l1 = DLG_TEXT_BASE[20];
				link.l1.go = "exit";
				break;
			}
			if (npchar.questChurch == "yes")
			{
				dialog.text = DLG_TEXT_BASE[21];
				link.l1 = DLG_TEXT_BASE[22];
				link.l1.go = "ResultChurch_1";
				break;
			}
			if (npchar.questChurch == "no")
			{
				dialog.text = DLG_TEXT_BASE[23];
				link.l1 = DLG_TEXT_BASE[24] + npchar.name + DLG_TEXT_BASE[25];
				link.l1.go = "ResultChurch_2";
				break;
			}
			//-->> дача квеста пожертвования в церковь
			if (rand(2) == 1 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questChurch") > 45 && GetHour() < 20)
			{
				dialog.text = DLG_TEXT_BASE[26];
				link.l5 = DLG_TEXT_BASE[27];
				link.l5.go = "toChurch";
				//личные флаги хозяйки на взятие квеста
				npchar.questChurch = "taken";
				SaveCurrentNpcQuestDateParam(npchar, "questChurch");
				break;
			}
			//<<-- квест пожертвования в церковь

			//-->> дача развода на секс
			if (rand(3) == 1 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questSex") > 180 && !CheckAttribute(npchar, "quest.selected") && !CheckAttribute(npchar, "quest.NotGoneToSex.over"))
			{
				if (!CheckAttribute(npchar, "quest.NotGoneToSex"))
				{
					dialog.text = DLG_TEXT_BASE[28];
					link.l5 = DLG_TEXT_BASE[29];
					link.l5.go = "toHostessSex";
					link.l8 = DLG_TEXT_BASE[30] + npchar.name + DLG_TEXT_BASE[31];
					link.l8.go = "exit";
					pchar.questTemp.different = "HostessSex";
					SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questSex");
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[32];
					link.l1 = DLG_TEXT_BASE[33];
					link.l1.go = "exit";
					npchar.quest.NotGoneToSex.over = true; //больше вообще не говоить
				}
				break;
			}
			//<<-- развод на секс

			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + DLG_TEXT_BASE[34] + npchar.name + DLG_TEXT_BASE[35] + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + DLG_TEXT_BASE[36]+ NPChar.Name + DLG_TEXT_BASE[37]);
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + DLG_TEXT_BASE[38] + GetAddress_Form(NPChar) + "?",
				                               TimeGreeting() + DLG_TEXT_BASE[39] + GetAddress_Form(NPChar) + "?");
			}
			link.l2 = npchar.name + DLG_TEXT_BASE[40];
			link.l2.go = "Hostess_1";
			link.l3 = DLG_TEXT_BASE[41];
			link.l3.go = "ForCrew";
			link.l4 = DLG_TEXT_BASE[42];
			link.l4.go = "quests";//(перессылка в файл города)
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = DLG_TEXT_BASE[43] + npchar.name + DLG_TEXT_BASE[44];
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			link.l9 = DLG_TEXT_BASE[45];
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = DLG_TEXT_BASE[46];
					Link.l1 = DLG_TEXT_BASE[47];
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = DLG_TEXT_BASE[48];
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[49];
					Link.l1 = DLG_TEXT_BASE[50];
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[51];
				Link.l1 = DLG_TEXT_BASE[52];
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = DLG_TEXT_BASE[53];
				Link.l1 = DLG_TEXT_BASE[54];
				Link.l1.go = "exit";	
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[55] + GetFullName(sld) + DLG_TEXT_BASE[56] + FindRussianMoneyString(sti(sld.quest.price)) + DLG_TEXT_BASE[57];
				Link.l1 = DLG_TEXT_BASE[58];
				Link.l1.go = "exit";
				if (sti(pchar.money) >= sti(sld.quest.price))
				{
					Link.l2 = DLG_TEXT_BASE[59];
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = DLG_TEXT_BASE[60];
					Link.l1.go = "exit";
				}
			}
		break;
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= sti(sld.quest.price))
			{
				dialog.text = DLG_TEXT_BASE[61] + sld.name + DLG_TEXT_BASE[62];
				Link.l1 = DLG_TEXT_BASE[63];
				Link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -sti(sld.quest.price));
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[64] + sld.name + DLG_TEXT_BASE[65] + FindRussianMoneyString(sti(sld.quest.price)) + DLG_TEXT_BASE[66];
				Link.l1 = DLG_TEXT_BASE[67];
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = DLG_TEXT_BASE[68];
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_BASE[69];
				Link.l1 = DLG_TEXT_BASE[70];
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = DLG_TEXT_BASE[71];
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + DLG_TEXT_BASE[72];
				Link.l1 = DLG_TEXT_BASE[73];
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = DLG_TEXT_BASE[74];
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
        case "Hostess_Choice_2":
			dialog.text = DLG_TEXT_BASE[75];
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = DLG_TEXT_BASE[76];
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = DLG_TEXT_BASE[77] + FindRussianMoneyString(GetCrewQuantity(pchar)*30) + ".";
			link.l1 = DLG_TEXT_BASE[78];
			link.l1.go = "ForCrew_1";
			link.l2 = DLG_TEXT_BASE[79];
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*30 && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*30));

	            AddCrewMorale(Pchar, 10);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = DLG_TEXT_BASE[80];
			    link.l1 = DLG_TEXT_BASE[81];
			    link.l1.go = "exit";
		    }
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//просьба о пожертвовании в церкви
		case "toChurch":
			dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "toChurch_1";
		break;
		case "toChurch_1":
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "toChurch_2";
		break;
		case "toChurch_2":
			pchar.questTemp.different.HostessChurch.money = (rand(4)+1) * 300;
			dialog.text = DLG_TEXT_BASE[88] + FindRussianMoneyString(sti(pchar.questTemp.different.HostessChurch.money)) +  DLG_TEXT_BASE[89];
			link.l1 = DLG_TEXT_BASE[90];
			link.l1.go = "toChurch_3";
			link.l2 = DLG_TEXT_BASE[91];
			link.l2.go = "toChurch_4";
		break;
		case "toChurch_3":
			dialog.text = DLG_TEXT_BASE[92];
			link.l1 = DLG_TEXT_BASE[93];
			link.l1.go = "exit";
			pchar.questTemp.different.HostessChurch.city = npchar.city; //город
			pchar.questTemp.different = "HostessChurch_toChurch";
			SetTimerFunction("HostessChurch_null", 0, 0, 1); //освобождаем разрешалку на миниквесты и чистим структуру
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.HostessChurch.money));
			ChangeCharacterReputation(pchar, 0.30);
		break;
		case "toChurch_4":
			dialog.text = DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.HostessChurch");
			npchar.questChurch = ""; //нулим личный флаг квеста
			ChangeCharacterReputation(pchar, -1);
		break;

		case "ResultChurch_1":
			dialog.text = DLG_TEXT_BASE[96];
			link.l1 = DLG_TEXT_BASE[97] + npchar.name + DLG_TEXT_BASE[98];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			npchar.questChurch = ""; //нулим личный флаг квеста
		break;
		case "ResultChurch_2":
			dialog.text = DLG_TEXT_BASE[99];
			link.l1 = DLG_TEXT_BASE[100];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			npchar.questChurch = ""; //нулим личный флаг квеста
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		break;
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = DLG_TEXT_BASE[101];
			link.l1 = DLG_TEXT_BASE[102];
			link.l1.go = "TakeMayorsRing_H2";
		break;
		case "TakeMayorsRing_H2":
			dialog.text = DLG_TEXT_BASE[103];
			link.l1 = DLG_TEXT_BASE[104];
			link.l1.go = "TakeMayorsRing_H3";
		break;
		case "TakeMayorsRing_H3":
			dialog.text = DLG_TEXT_BASE[105];
			link.l1 = DLG_TEXT_BASE[106] + npchar.name + ".";
			link.l1.go = "exit";
		break;
		//------- развод на секс ------------
		case "toHostessSex":
			dialog.text = DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "toHostessSex_1";
			link.l2 = DLG_TEXT_BASE[109];
			link.l2.go = "toHostessSex_2";
			link.l3 = DLG_TEXT_BASE[110];
			link.l3.go = "toHostessSex_3";
		break;
		case "toHostessSex_1":
			dialog.text = DLG_TEXT_BASE[111];
			link.l1 = DLG_TEXT_BASE[112];
			link.l1.go = "exit";
		break;
		case "toHostessSex_2":
			if (rand(1))
			{
				dialog.text = DLG_TEXT_BASE[113];
				link.l1 = DLG_TEXT_BASE[114];
				link.l1.go = "SpeakHistory";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[115];
				link.l1 = DLG_TEXT_BASE[116];
				link.l1.go = "SpeakHistoryTwo";
			}
		break;
		case "toHostessSex_3":
			dialog.text = DLG_TEXT_BASE[117];
			link.l1 = DLG_TEXT_BASE[118];
			link.l1.go = "exit";
		break;
		//истории
		case "SpeakHistory":
			dialog.text = DLG_TEXT_BASE[119];
			if (rand(1))
			{
				link.l1 = DLG_TEXT_BASE[120];
				link.l1.go = "SpeakHistory_1";
			}
			else
			{
				link.l1 = DLG_TEXT_BASE[121];
				link.l1.go = "SpeakHistory_2";
			}
		break;
		case "SpeakHistory_1":
			dialog.text = DLG_TEXT_BASE[122];
			link.l1 = DLG_TEXT_BASE[123] + GetAddress_Form(PChar) + DLG_TEXT_BASE[124];
			link.l1.go = "SpeakHistory_3";
		break;
		case "SpeakHistory_2":
			dialog.text = DLG_TEXT_BASE[125];
			link.l1 = DLG_TEXT_BASE[126];
			link.l1.go = "exit";
		break;
		case "SpeakHistory_3":
			dialog.text = DLG_TEXT_BASE[127];
			link.l1 = DLG_TEXT_BASE[128];
			link.l1.go = "SpeakHistory_4";
		break;
		case "SpeakHistory_4":
			dialog.text = DLG_TEXT_BASE[129];
			link.l1 = DLG_TEXT_BASE[130];
			link.l1.go = "SpeakHistory_5";
		break;
		case "SpeakHistory_5":
			dialog.text = DLG_TEXT_BASE[131];
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "SpeakHistory_6";
			link.l2 = DLG_TEXT_BASE[133];
			link.l2.go = "SpeakHistory_7";
		break;
		case "SpeakHistory_6":
			dialog.text = DLG_TEXT_BASE[134];
			link.l1 = DLG_TEXT_BASE[135];
			link.l1.go = "exit";
		break;
		case "SpeakHistory_7":
			dialog.text = DLG_TEXT_BASE[136];
			link.l1 = DLG_TEXT_BASE[137];
			link.l1.go = "SpeakHistory_8";
		break;
		case "SpeakHistory_8":
			dialog.text = DLG_TEXT_BASE[138];
			link.l1 = DLG_TEXT_BASE[139];
			link.l1.go = "SpeakHistory_9";
			link.l2 = DLG_TEXT_BASE[140];
			link.l2.go = "SpeakHistory_10";
		break;
		case "SpeakHistory_9":
			dialog.text = DLG_TEXT_BASE[141];
			link.l1 = DLG_TEXT_BASE[142];
			link.l1.go = "exit";
		break;
		case "SpeakHistory_10":
			dialog.text = DLG_TEXT_BASE[143];
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes"; 
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "Hostess_inSexRoom":
			dialog.text = DLG_TEXT_BASE[145];
			link.l1 = DLG_TEXT_BASE[146];
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришел
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");
		break;

		case "SpeakHistoryTwo":
			dialog.text = DLG_TEXT_BASE[147];
			link.l1 = DLG_TEXT_BASE[148];
			link.l1.go = "SpeakHistoryTwo_1";
		break;
		case "SpeakHistoryTwo_1":
			dialog.text = DLG_TEXT_BASE[149];
			link.l1 = DLG_TEXT_BASE[150];
			link.l1.go = "SpeakHistoryTwo_2";
			link.l2 = DLG_TEXT_BASE[151];
			link.l2.go = "SpeakHistoryTwo_3";
		break;
		case "SpeakHistoryTwo_2":
			dialog.text = DLG_TEXT_BASE[152];
			link.l1 = DLG_TEXT_BASE[153];
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_3":
			dialog.text = DLG_TEXT_BASE[154];
			link.l1 = DLG_TEXT_BASE[155];
			link.l1.go = "SpeakHistoryTwo_4";
		break;
		case "SpeakHistoryTwo_4":
			dialog.text = DLG_TEXT_BASE[156];
			link.l1 = DLG_TEXT_BASE[157];
			link.l1.go = "SpeakHistoryTwo_5";
		break;
		case "SpeakHistoryTwo_5":
			dialog.text = DLG_TEXT_BASE[158];
			link.l1 = DLG_TEXT_BASE[159];
			link.l1.go = "SpeakHistoryTwo_6";
			link.l2 = DLG_TEXT_BASE[160];
			link.l2.go = "SpeakHistoryTwo_7";
		break;
		case "SpeakHistoryTwo_6":
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "exit";
		break;
		case "SpeakHistoryTwo_7":
			dialog.text = DLG_TEXT_BASE[163];
			link.l1 = DLG_TEXT_BASE[164];
			link.l1.go = "SpeakHistoryTwo_8";
		break;
		case "SpeakHistoryTwo_8":
			dialog.text = DLG_TEXT_BASE[165];
			link.l1 = DLG_TEXT_BASE[166];
			link.l1.go = "SpeakHistoryTwo_9";
		break;
		case "SpeakHistoryTwo_9":
			dialog.text = DLG_TEXT_BASE[167];
			link.l1 = DLG_TEXT_BASE[168];
			link.l1.go = "SpeakHistoryTwo_10";
			link.l2 = DLG_TEXT_BASE[169];
			link.l2.go = "SpeakHistoryTwo_15";
		break;
		case "SpeakHistoryTwo_10":
			dialog.text = DLG_TEXT_BASE[170];
			link.l1 = DLG_TEXT_BASE[171];
			link.l1.go = "SpeakHistoryTwo_11";
		break;
		case "SpeakHistoryTwo_11":
			dialog.text = DLG_TEXT_BASE[172];
			link.l1 = DLG_TEXT_BASE[173];
			link.l1.go = "SpeakHistoryTwo_12";
		break;
		case "SpeakHistoryTwo_12":
			dialog.text = DLG_TEXT_BASE[174];
			link.l1 = DLG_TEXT_BASE[175];
			link.l1.go = "SpeakHistoryTwo_13";
		break;
		case "SpeakHistoryTwo_13":
			dialog.text = DLG_TEXT_BASE[176];
			link.l1 = DLG_TEXT_BASE[177];
			link.l1.go = "SpeakHistoryTwo_14";
		break;
		case "SpeakHistoryTwo_14":
			dialog.text = DLG_TEXT_BASE[178];
			link.l1 = DLG_TEXT_BASE[179];
			link.l1.go = "exit";
			pchar.questTemp.different.HostessSex = "toRoom";
			pchar.questTemp.different.HostessSex.city = npchar.city;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			pchar.quest.SmallQuests_free.over = "yes"; 
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); //возврат хозяйки на место, если ГГ не прийдет в комнату
		break;

		case "SpeakHistoryTwo_15":
			dialog.text = DLG_TEXT_BASE[180];
			link.l1 = DLG_TEXT_BASE[181];
			link.l1.go = "SpeakHistoryTwo_16";
		break;
		case "SpeakHistoryTwo_16":
			dialog.text = DLG_TEXT_BASE[182];
			link.l1 = DLG_TEXT_BASE[183] + npchar.name + DLG_TEXT_BASE[184];
			link.l1.go = "exit";
		break;
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[185], DLG_TEXT_BASE[186], DLG_TEXT_BASE[187]), 
					LinkRandPhrase(DLG_TEXT_BASE[188], DLG_TEXT_BASE[189], DLG_TEXT_BASE[190]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[191], DLG_TEXT_BASE[192]), 
					RandPhraseSimple(DLG_TEXT_BASE[193], DLG_TEXT_BASE[194]));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[195] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[196], 
				DLG_TEXT_BASE[197], 
				DLG_TEXT_BASE[198] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[199], 
				DLG_TEXT_BASE[200] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[201], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[202], DLG_TEXT_BASE[203],
                      DLG_TEXT_BASE[204], DLG_TEXT_BASE[205], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = DLG_TEXT_BASE[206];
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(DLG_TEXT_BASE[207], DLG_TEXT_BASE[208], DLG_TEXT_BASE[209]);
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase(DLG_TEXT_BASE[210], 
					DLG_TEXT_BASE[211], 
					DLG_TEXT_BASE[212]);
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
            //--> Голл. линейка, квест №8. базар с девокой о Библиии.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" || pchar.questTemp.State == "SeekBible_toGirl")
            {
    			if (npchar.id == "HorseGen_"+FindLocation("FortFrance_Brothel")+"_1")
				{
					if (!CheckAttribute(npchar, "quest.HolLineTalk"))
					{
						dialog.text = DLG_TEXT_BASE[213];
    					link.l4 = DLG_TEXT_BASE[214];
    					link.l4.go = "Step_Hol8_1";
					}
					else
					{
						dialog.text = DLG_TEXT_BASE[215];
						link.l4 = DLG_TEXT_BASE[216];
    					link.l4.go = "Step_Hol8_5";
						AddMoneyToCharacter(pchar, -1000);
					}
				}
            }
			//<-- Голл. линейка, квест №8. базар с девокой о Библиии.
			NextDiag.TempNode = "Horse_talk";
		break;
        case "Horse_1":
			dialog.text = DLG_TEXT_BASE[217] + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = DLG_TEXT_BASE[218];
			Link.l1.go = "exit";			
		break;
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[219], DLG_TEXT_BASE[220], DLG_TEXT_BASE[221]);
				link.l1 = DLG_TEXT_BASE[222];
				Link.l1.go = "Horse_3";		
				Link.l2 = DLG_TEXT_BASE[223];
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[224], DLG_TEXT_BASE[225], DLG_TEXT_BASE[226]);
				link.l1 = DLG_TEXT_BASE[227];
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + DLG_TEXT_BASE[228] + npchar.name + DLG_TEXT_BASE[229];
			Link.l1 = DLG_TEXT_BASE[230];
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[231], 
				DLG_TEXT_BASE[232], 
				DLG_TEXT_BASE[233], 
				DLG_TEXT_BASE[234], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[235], DLG_TEXT_BASE[236],
                      DLG_TEXT_BASE[237], DLG_TEXT_BASE[238], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[239], 
					DLG_TEXT_BASE[240], 
					DLG_TEXT_BASE[241], 
					DLG_TEXT_BASE[242], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[243], DLG_TEXT_BASE[244],
						DLG_TEXT_BASE[245], DLG_TEXT_BASE[246], npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[247];
				Link.l1 = DLG_TEXT_BASE[248];
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[249], 
						DLG_TEXT_BASE[250], 
						DLG_TEXT_BASE[251], 
						DLG_TEXT_BASE[252], "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[253], DLG_TEXT_BASE[254],
							DLG_TEXT_BASE[255], DLG_TEXT_BASE[256], npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[257];
					Link.l1 = DLG_TEXT_BASE[258];
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[259];
				Link.l1 = DLG_TEXT_BASE[260];
				Link.l1.go = "exit";
				Link.l2 = DLG_TEXT_BASE[261];
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[262], 
					DLG_TEXT_BASE[263], 
					DLG_TEXT_BASE[264], 
					DLG_TEXT_BASE[265], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[266], DLG_TEXT_BASE[267],
						DLG_TEXT_BASE[268], DLG_TEXT_BASE[269], npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[270];
				Link.l1 = DLG_TEXT_BASE[271];
				Link.l1.go = "exit";
			}
		break;
        case "HorseChoice_1_Add":
			dialog.text = DLG_TEXT_BASE[272];
			Link.l1 = DLG_TEXT_BASE[273];
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		//===>> секс
        case "Horse_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[274], DLG_TEXT_BASE[275]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[276], DLG_TEXT_BASE[277]);
				break;
				case "1":
					dialog.text = DLG_TEXT_BASE[278];
					Link.l1 = DLG_TEXT_BASE[279];	
				break;
				case "2":
					dialog.text = DLG_TEXT_BASE[280];
					Link.l1 = DLG_TEXT_BASE[281];
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			
			/// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[282], DLG_TEXT_BASE[283], DLG_TEXT_BASE[284]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[285], DLG_TEXT_BASE[286]);
					Link.l1.go = "exit";
				break;
				case "1":
					if (sti(npchar.quest.sexHappend) > (rand(4)+5) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
					{
						dialog.text = DLG_TEXT_BASE[287];
						Link.l1 = DLG_TEXT_BASE[288];	
						Link.l1.go = "HorseQuest";
					}
					else
					{
						dialog.text = LinkRandPhrase(DLG_TEXT_BASE[289], DLG_TEXT_BASE[290], DLG_TEXT_BASE[291]);
						Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[292], DLG_TEXT_BASE[293]);	
						Link.l1.go = "exit";
					}
				break;
				case "2":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[294], DLG_TEXT_BASE[295]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[296], DLG_TEXT_BASE[297]);
					Link.l1.go = "exit";
				break;
			}
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
        case "Horse_AfterSex_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[298], DLG_TEXT_BASE[299], DLG_TEXT_BASE[300]);
			Link.l1 = DLG_TEXT_BASE[301];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		//==> квест на лут
        case "HorseQuest":
			pchar.questTemp.HorseLoot = sti(pchar.questTemp.HorseLoot) + 1;
			npchar.questTemp.HorseLoot = true; //уже давала
			dialog.text = DLG_TEXT_BASE[302];
			Link.l1 = DLG_TEXT_BASE[303];
			Link.l1.go = "HorseQuest_1";
		break;
        case "HorseQuest_1":
			dialog.text = DLG_TEXT_BASE[304];
			Link.l1 = DLG_TEXT_BASE[305];
			Link.l1.go = "HorseQuest_2";
		break;
        case "HorseQuest_2":
			dialog.text = DLG_TEXT_BASE[306];
			Link.l1 = DLG_TEXT_BASE[307];
			Link.l1.go = "HorseQuest_3";
		break;
        case "HorseQuest_3":
			sTemp = LinkRandPhrase("Shore55", "Shore9", "Shore_ship2");							
			if (sTemp == "Shore55") 
			{
				str = DLG_TEXT_BASE[308];
				str1 = "box" + (rand(1)+1);
			}
			if (sTemp == "Shore9") 
			{
				str = DLG_TEXT_BASE[309];
				str1 = "box1";
			}
			if (sTemp == "Shore_ship2") 
			{
				str = DLG_TEXT_BASE[310];
				str1 = "box2";
			}
         	pchar.GenQuestBox.(sTemp) = true;
			switch (pchar.questTemp.HorseLoot)
			{
				case "1": 
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass2 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry1 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry5 = 6;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry10 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.indian11 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 15000;
				break;
				case "2": 
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass3 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry14 = 3;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry16 = 2;
					pchar.GenQuestBox.(sTemp).(str1).items.jewelry18 = 4;
					pchar.GenQuestBox.(sTemp).(str1).items.indian17 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 19000;
				break;
				case "3": 
					pchar.GenQuestBox.(sTemp).(str1).items.indian20 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian5 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian10 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.spyglass4 = 1;
					pchar.GenQuestBox.(sTemp).(str1).items.indian19 = 1;
					pchar.GenQuestBox.(sTemp).(str1).money = 24000;
				break;
			}
			dialog.text = DLG_TEXT_BASE[311] + str + ".";
			Link.l1 = DLG_TEXT_BASE[312];
			Link.l1.go = "exit";
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[313], 
					DLG_TEXT_BASE[314], 
					DLG_TEXT_BASE[315]);
				link.l1 = DLG_TEXT_BASE[316];
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = DLG_TEXT_BASE[317];
					link.l1 = DLG_TEXT_BASE[318];
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[319], 
						DLG_TEXT_BASE[320], 
						DLG_TEXT_BASE[321]);
					link.l1 = DLG_TEXT_BASE[322];
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = DLG_TEXT_BASE[323];
			link.l1 = DLG_TEXT_BASE[324];
			link.l1.go = "TakeMayorsRing_S3";
		break;
		case "TakeMayorsRing_S3":
			dialog.text = DLG_TEXT_BASE[325];
			link.l1 = DLG_TEXT_BASE[326];
			link.l1.go = "TakeMayorsRing_S4";
		break;
		case "TakeMayorsRing_S4":
			dialog.text = DLG_TEXT_BASE[327];
			link.l1 = DLG_TEXT_BASE[328];
			link.l1.go = "TakeMayorsRing_S5";
		break;
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = DLG_TEXT_BASE[329];
				link.l1 = DLG_TEXT_BASE[330];
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[331];
				link.l1 = DLG_TEXT_BASE[332];
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		case "TakeMayorsRing_S6":
			dialog.text = DLG_TEXT_BASE[333];
			link.l1 = DLG_TEXT_BASE[334];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
//********************************* Диалоги девки из борделя ФФ **********************************
  		case "Step_Hol8_1":
			dialog.text = DLG_TEXT_BASE[335];
			link.l1 = DLG_TEXT_BASE[336];
			link.l1.go = "Step_Hol8_2";
		break;
  		case "Step_Hol8_2":
			dialog.text = DLG_TEXT_BASE[337];
			link.l1 = DLG_TEXT_BASE[338];
			link.l1.go = "Step_Hol8_3";
		break;
  		case "Step_Hol8_3":
			dialog.text = DLG_TEXT_BASE[339];
			link.l1 = DLG_TEXT_BASE[340];
			link.l1.go = "Step_Hol8_4";
		break;
  		case "Step_Hol8_4":
			dialog.text = DLG_TEXT_BASE[341];
            if (sti(pchar.money) >= 1000)
            {
    			link.l1 = DLG_TEXT_BASE[342];
    			link.l1.go = "Step_Hol8_5";
                AddMoneyToCharacter(pchar, -1000);
            }
            else
            {
    			link.l1 = DLG_TEXT_BASE[343];
    			link.l1.go = "exit";
				npchar.quest.HolLineTalk = true;
            }
			NextDiag.TempNode = "Horse_talk";
		break;
		case "Step_Hol8_5":
			dialog.text = DLG_TEXT_BASE[344];
			link.l1 = DLG_TEXT_BASE[345];
			link.l1.go = "Step_Hol8_6";
		break;
		case "Step_Hol8_6":
			dialog.text = DLG_TEXT_BASE[346];
			link.l1 = DLG_TEXT_BASE[347];
			link.l1.go = "Step_Hol8_7";
    	break;
		case "Step_Hol8_7":
			dialog.text = DLG_TEXT_BASE[348];
			link.l1 = DLG_TEXT_BASE[349];
			link.l1.go = "Step_Hol8_8";
    	break;
		case "Step_Hol8_8":
			dialog.text = DLG_TEXT_BASE[350];
			link.l1 = DLG_TEXT_BASE[351];
			link.l1.go = "Step_Hol8_9";
    	break;
		case "Step_Hol8_9":
			dialog.text = DLG_TEXT_BASE[352];
			link.l1 = DLG_TEXT_BASE[353];
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "4");
			pchar.questTemp.State = "SeekBible_toTavern";
			NextDiag.TempNode = "Horse_talk";
    	break;
	}
}


ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
