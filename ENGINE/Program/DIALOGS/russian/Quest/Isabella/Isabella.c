#include "TEXT\DIALOGS\Quest\Isabella\Isabella.h"
void ProcessDialogEvent()
{
	ref NPChar, d, sld, rColony;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i, iMoney, iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
					//когда достал обещаниями денег дать
                    if (npchar.angry.name == "NewLife_Budget_Add") Dialog.CurrentNode = "AngryRepeat_Budget_Add";
					//когда подарками достал, а сам не давал
					if (npchar.angry.name == "NewLife_Present") Dialog.CurrentNode = "AngryRepeat_Present";
                break;
				case "quest":
					//когда долги достали Изабеллу
					if (npchar.angry.name == "NewLife_Budget_Pay") Dialog.CurrentNode = "AngryRepeat_Budget_Pay";
					//когда достало Изабеллу пиратсво ГГ
					if (npchar.angry.name == "NewLife_KnowPirates") Dialog.CurrentNode = "AngryRepeat_KnowPirates";
				break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			//был в спальне
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			// прерывание на выход, а то ход истории в руках геймера
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
            dialog.text = DLG_TEXT_QB[0];
			link.l1 = DLG_TEXT_QB[1] + GetFullName(pchar) + DLG_TEXT_QB[2];
			link.l1.go = "Next_1";
			link.l2 = DLG_TEXT_QB[3];
			link.l2.go = "exit";
		break;
		
		case "Next_1":
			NextDiag.TempNode = "Next_2";
			
            dialog.text = DLG_TEXT_QB[4]+ NPChar.Name + " " + NPChar.LastName +
                          DLG_TEXT_QB[5];
            link.l1 = DLG_TEXT_QB[6];
			link.l1.go = "Next_4";
			link.l2 = DLG_TEXT_QB[7];
			link.l2.go = "exit";
		break;
		
		case "Next_2":
			NextDiag.TempNode = "Next_2";			
            dialog.text = DLG_TEXT_QB[8];
            link.l1 = DLG_TEXT_QB[9];
			link.l1.go = "Next_3";
            link.l2 = DLG_TEXT_QB[10];
			link.l2.go = "exit";
		break;
		
		case "Next_3":
			NextDiag.TempNode = "Next_2";			
            dialog.text = DLG_TEXT_QB[11];
            link.l1 = DLG_TEXT_QB[12];
			link.l1.go = "exit";
		break;
		
		case "Next_4":
            dialog.text = DLG_TEXT_QB[13];
            link.l1 = DLG_TEXT_QB[14];
			link.l1.go = "Next_5";
            link.l2 = DLG_TEXT_QB[15];
			link.l2.go = "Next_6";
			link.l3 = DLG_TEXT_QB[16];
			link.l3.go = "Next_7";
		break;
		
		case "Next_5":
            dialog.text = DLG_TEXT_QB[17];
            link.l1 = DLG_TEXT_QB[18];
			link.l1.go = "Next_8";
            link.l2 = DLG_TEXT_QB[19];
			link.l2.go = "Next_9";
			Pchar.RomanticQuest.TalkInShop = true;
		break;
		
		case "Next_6":
            dialog.text = DLG_TEXT_QB[20]+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = DLG_TEXT_QB[21];
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;
		
		case "Next_7":
			dialog.text = DLG_TEXT_QB[22]+ Characters[GetCharacterIndex("Husband")].Name + "!!!";
            link.l1 = DLG_TEXT_QB[23];
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;
		
		case "Next_8":
		    NextDiag.TempNode = "Good_1";
            dialog.text = DLG_TEXT_QB[24];
            link.l1 = DLG_TEXT_QB[25];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
		break;
		
		case "Next_9":
		    NextDiag.TempNode = "Next_2";
            dialog.text = DLG_TEXT_QB[26];
            link.l1 = DLG_TEXT_QB[27];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -4);
		break;
		
		case "Good_1":
		    NextDiag.TempNode = "Good_1";
            dialog.text = DLG_TEXT_QB[28];
            link.l1 = DLG_TEXT_QB[29]+Npchar.Name+".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		
		case "Romantic_Battle_in_Bedroom":
		    NextDiag.CurrentNode = "Next_2";
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_1");
		break;
		
		case "Murder":
		    NextDiag.TempNode = "Murder";
            dialog.text = DLG_TEXT_QB[30];
            link.l1 = "...";
			link.l1.go = "exit";
			PChar.quest.Romantic_TalkInShop.over = "yes";
		break;
		
		case "TalkInShop":
		    NextDiag.TempNode = "TalkInShop_2";
            dialog.text = DLG_TEXT_QB[31]+GetFullName(PChar)+"!";
            link.l1 = DLG_TEXT_QB[32];
			link.l1.go = "exit";
		break;
		
		case "TalkInShop_2":
            dialog.text = DLG_TEXT_QB[33];
            link.l1 = DLG_TEXT_QB[34];
			link.l1.go = "TalkInShop_3";
		break;
		
		case "TalkInShop_3":
            dialog.text = DLG_TEXT_QB[35];
            link.l1 = DLG_TEXT_QB[36];
			link.l1.go = "TalkInShop_4";
		break;
		
		case "TalkInShop_4":
            dialog.text = DLG_TEXT_QB[37]+
                          GetCharacterFullName("SanJuan_trader")+DLG_TEXT_QB[38] +
                          GetCharacterFullName("SanJuan_trader")+DLG_TEXT_QB[39];
            link.l1 = DLG_TEXT_QB[40];
			link.l1.go = "TalkInShop_5";
			link.l2 = DLG_TEXT_QB[41];
			link.l2.go = "TalkInShop_6";
		break;
		
		case "TalkInShop_5":
            AddMoneyToCharacter(pchar, -1200);
		    NextDiag.TempNode = "Good_1";
            dialog.text = DLG_TEXT_QB[42];
            link.l1 = DLG_TEXT_QB[43];
			link.l1.go = "TalkInShop_Go";
		break;
		
		case "TalkInShop_6":
            NextDiag.CurrentNode = "TalkInShop_7";
			DialogExit();
			characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_2";
			AddDialogExitQuest("Romantic_TalkInShop_3");
		break;
		
		case "TalkInShop_7":
		    NextDiag.TempNode = "Good_1";
            dialog.text = DLG_TEXT_QB[44];
            link.l1 = DLG_TEXT_QB[45];
			link.l1.go = "TalkInShop_Go";
		break;
		
		case "TalkInShop_Go":
            NextDiag.CurrentNode = "Good_1";
			DialogExit();
            LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "SanJuan_church", "goto", "goto1", "Romantic_TalkInShop_end", 4.0);
			chrDisableReloadToLocation = true;
		break;
		
		case "TalkInChurch":
            dialog.text = DLG_TEXT_QB[46];
            link.l1 = DLG_TEXT_QB[47];
			link.l1.go = "TalkInChurch_1";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
		break;
		
		case "TalkInChurch_1":
            dialog.text = DLG_TEXT_QB[48];
            link.l1 = DLG_TEXT_QB[49];
			link.l1.go = "TalkInChurch_2";
		break;
		
		case "TalkInChurch_2":
            dialog.text = DLG_TEXT_QB[50];
            link.l1 = DLG_TEXT_QB[51];
			link.l1.go = "TalkInChurch_3";
		break;
		
		case "TalkInChurch_3":
            dialog.text = DLG_TEXT_QB[52];
            link.l1 = DLG_TEXT_QB[53];
			link.l1.go = "TalkInChurch_4";
		break;
		
		case "TalkInChurch_4":
            dialog.text = DLG_TEXT_QB[54];
            link.l1 = DLG_TEXT_QB[55];
			link.l1.go = "TalkInChurch_Go";
		break;
		
		case "TalkInChurch_Go":
			chrDisableReloadToLocation = true;
            NextDiag.CurrentNode = "WaitShip";
            Pchar.RomanticQuest.ShipToCumana = true;
			DialogExit();
			AddQuestRecord("Romantic_Line", "5");
			LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 20.0);
            // немного веселой жизни
            TraderHunterOnMap();
		break;
		
		case "WaitShip":
		    NextDiag.TempNode = "WaitShip";
            dialog.text = DLG_TEXT_QB[56];
            link.l1 = DLG_TEXT_QB[57]+Npchar.Name+ ".";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// разговор с братом
		case "Brother_1":
            dialog.text = DLG_TEXT_QB[58];
            link.l1 = DLG_TEXT_QB[59];
			link.l1.go = "Brother_2";
		break;		
		case "Brother_2":
            dialog.text = DLG_TEXT_QB[60];
            link.l1 = DLG_TEXT_QB[61];
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_Brother_House_3");
			NextDiag.TempNode = "Brother_3";
		break;		
		case "Brother_3":
            dialog.text = DLG_TEXT_QB[62]+GetFullName(pchar)+DLG_TEXT_QB[63];
            link.l1 = DLG_TEXT_QB[64];
			link.l1.go = "Brother_4";
		break;
		case "Brother_4":
			AddQuestRecord("Romantic_Line", "8");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 5.0);
			NextDiag.CurrentNode = "Temp_Thanks";
			DialogExit();
		break;		
		case "Temp_Thanks":
            NextDiag.TempNode = "Temp_Thanks";
            dialog.text = DLG_TEXT_QB[65];
            link.l1 = DLG_TEXT_QB[66];
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep)+1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";			
		break;
		// разговор с ГГ на взятом бриге
		case "BrigAbordage":
            dialog.text = DLG_TEXT_QB[67];
            link.l1 = DLG_TEXT_QB[68];
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
            dialog.text = DLG_TEXT_QB[69];
            link.l1 = DLG_TEXT_QB[70];
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
            dialog.text = DLG_TEXT_QB[71];
			if (CheckCharacterItem(pchar, "Order"))
			{			
				link.l1 = DLG_TEXT_QB[72];
				link.l1.go = "BrigAbordage_8";
			}
			else
			{
				link.l1 = DLG_TEXT_QB[73];
				link.l1.go = "BrigAbordage_3";
			}
		break;
		// --> нету поддельных векселей в наличие
		case "BrigAbordage_3":
            dialog.text = DLG_TEXT_QB[74];
            link.l1 = DLG_TEXT_QB[75];
			link.l1.go = "BrigAbordage_4";
		break;
		case "BrigAbordage_4":
            dialog.text = DLG_TEXT_QB[76];
            link.l1 = DLG_TEXT_QB[77];
			link.l1.go = "BrigAbordage_5";
		break;	
		case "BrigAbordage_5":
            dialog.text = DLG_TEXT_QB[78];
            link.l1 = DLG_TEXT_QB[79];
			link.l1.go = "BrigAbordage_6";
		break;	
		case "BrigAbordage_6":
            dialog.text = DLG_TEXT_QB[80];
            link.l1 = DLG_TEXT_QB[81];
			link.l1.go = "BrigAbordage_7";
		break;	
		case "BrigAbordage_7":
            dialog.text = DLG_TEXT_QB[82];
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.location = "none";
			npchar.location.group = "";
			npchar.location.locator = "";
			AddQuestRecord("Romantic_Line", "17");
			QuestSetCurrentNode("Atilla", "Isabella_Sink");
		break;	
		// --> поддельные векселя - у ГГ.
		case "BrigAbordage_8":
            dialog.text = DLG_TEXT_QB[83] + GetFullName(pchar) + ".";
            link.l1 = DLG_TEXT_QB[84];
			link.l1.go = "BrigAbordage_9";
			TakeItemFromCharacter(pchar, "Order");
		break;	
		case "BrigAbordage_9":
            dialog.text = DLG_TEXT_QB[85];
            link.l1 = DLG_TEXT_QB[86];
			link.l1.go = "BrigAbordage_10";
		break;	
		case "BrigAbordage_10":
            dialog.text = DLG_TEXT_QB[87]+
				          DLG_TEXT_QB[88];
            link.l1 = DLG_TEXT_QB[89];
			link.l1.go = "BrigAbordage_11";
		break;	
		case "BrigAbordage_11":
            dialog.text = DLG_TEXT_QB[90];
            link.l1 = DLG_TEXT_QB[91];
			link.l1.go = "BrigAbordage_12";
		break;	
		case "BrigAbordage_12":
            dialog.text = DLG_TEXT_QB[92];
            link.l1 = DLG_TEXT_QB[93];
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			pchar.RomanticQuest = "SeekInPortoBello";
			AddQuestRecord("Romantic_Line", "18");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);			
			//засада, оставленная Сальватором в Порто Белло
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1.location = "PortoBello_houseF2";
            Pchar.quest.Romantic_AmbushInPortoBello.win_condition = "Romantic_AmbushInPortoBello";
			//кузину Роситу в дом Белиза
			sld = GetCharacter(NPC_GenerateCharacter("Rosita", "girl_11", "woman", "towngirl", 5, SPAIN, -1, false));
            sld.name 	= DLG_TEXT_QB[94];
	        sld.lastname = DLG_TEXT_QB[95];
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
	        sld.dialog.currentnode = "Rosita";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_houseS4", "goto", "goto2");
		break;	
		//Изабелла в доме с засадой в Порто Белло
		case "AmbushPortoBello":
            dialog.text = DLG_TEXT_QB[96] + pchar.name + DLG_TEXT_QB[97];
            link.l1 = DLG_TEXT_QB[98];
			link.l1.go = "AmbushPortoBello_1";
		break;	
		case "AmbushPortoBello_1":
            dialog.text = DLG_TEXT_QB[99];
            link.l1 = DLG_TEXT_QB[100];
			link.l1.go = "AmbushPortoBello_2";
		break;	
		case "AmbushPortoBello_2":
            dialog.text = DLG_TEXT_QB[101];
			link.l1 = DLG_TEXT_QB[102];
			link.l1.go = "AmbushPortoBello_3";
		break;	
		case "AmbushPortoBello_3":
            dialog.text = DLG_TEXT_QB[103];
            link.l1 = DLG_TEXT_QB[104];
			link.l1.go = "AmbushPortoBello_4";
		break;	
		case "AmbushPortoBello_4":
            dialog.text = DLG_TEXT_QB[105] + pchar.name + DLG_TEXT_QB[106]+
				          DLG_TEXT_QB[107];
            link.l1 = DLG_TEXT_QB[108];
			link.l1.go = "AmbushPortoBello_5";
		break;	
		case "AmbushPortoBello_5":
			AddQuestRecord("Romantic_Line", "24");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			DialogExit();
		break;
		//Изабелла на выходе из дома Роситы в Белизе
		case "BelizTalk":
            dialog.text = DLG_TEXT_QB[109] + pchar.name + "?";
            link.l1 = DLG_TEXT_QB[110];
			link.l1.go = "BelizTalk_1";
		break;
		case "BelizTalk_1":
            dialog.text = DLG_TEXT_QB[111];
            link.l1 = DLG_TEXT_QB[112];
			link.l1.go = "BelizTalk_2";
		break;
		case "BelizTalk_2":
            dialog.text = DLG_TEXT_QB[113];
            link.l1 = DLG_TEXT_QB[114];
			link.l1.go = "BelizTalk_3";
		break;
		case "BelizTalk_3":
            dialog.text = DLG_TEXT_QB[115] + pchar.name + DLG_TEXT_QB[116];
            link.l1 = DLG_TEXT_QB[117];
			link.l1.go = "BelizTalk_4";
		break;
		case "BelizTalk_4":
            dialog.text = DLG_TEXT_QB[118];
            link.l1 = DLG_TEXT_QB[119];
			link.l1.go = "BelizTalk_5";
		break;
		case "BelizTalk_5":
            dialog.text = DLG_TEXT_QB[120];
            link.l1 = DLG_TEXT_QB[121];
			link.l1.go = "BelizTalk_6";
		break;
		case "BelizTalk_6":
            dialog.text = DLG_TEXT_QB[122];
            link.l1 = DLG_TEXT_QB[123];
			link.l1.go = "BelizTalk_7";
		break;
		case "BelizTalk_7":
            dialog.text = DLG_TEXT_QB[124];
            link.l1 = DLG_TEXT_QB[125];
			link.l1.go = "BelizTalk_8";
		break;
		case "BelizTalk_8":
			QuestSetCurrentNode("Atilla", "SalvatorNews");
			NextDiag.CurrentNode = "BelizTalk_after";
			AddQuestRecord("Romantic_Line", "19");
			chrDisableReloadToLocation = false;
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseS4", "Beliz_houseS4", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			DialogExit();
		break;
		case "BelizTalk_after":
            dialog.text = DLG_TEXT_QB[126];
            link.l1 = DLG_TEXT_QB[127];
			link.l1.go = "exit";
			NextDiag.TempNode = "BelizTalk_after";
		break;
		//Изабелла в пещере
		case "IsabellaInCave":
            dialog.text = DLG_TEXT_QB[128] + pchar.name + DLG_TEXT_QB[129];
            link.l1 = DLG_TEXT_QB[130];
			link.l1.go = "IsabellaInCave_1";
		break;
		case "IsabellaInCave_1":
            dialog.text = DLG_TEXT_QB[131];
            link.l1 = DLG_TEXT_QB[132];
			link.l1.go = "IsabellaInCave_2";
		break;
		case "IsabellaInCave_2":
            dialog.text = pchar.name + DLG_TEXT_QB[133];
            link.l1 = DLG_TEXT_QB[134];
			link.l1.go = "IsabellaInCave_3";
		break;
		case "IsabellaInCave_3":
            dialog.text = DLG_TEXT_QB[135];
            link.l1 = DLG_TEXT_QB[136];
			link.l1.go = "IsabellaInCave_4";
		break;
		case "IsabellaInCave_4":
            dialog.text = DLG_TEXT_QB[137];
            link.l1 = DLG_TEXT_QB[138];
			link.l1.go = "IsabellaInCave_5";
		break;
		case "IsabellaInCave_5":
            dialog.text = DLG_TEXT_QB[139] + pchar.name + DLG_TEXT_QB[140];
            link.l1 = DLG_TEXT_QB[141];
			link.l1.go = "IsabellaInCave_6";
		break;
		case "IsabellaInCave_6":
            dialog.text = DLG_TEXT_QB[142];
            link.l1 = DLG_TEXT_QB[143];
			link.l1.go = "IsabellaInCave_7";
		break;
		case "IsabellaInCave_7":
            dialog.text = DLG_TEXT_QB[144];
            link.l1 = DLG_TEXT_QB[145];
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			pchar.RomanticQuest = "FoundIsabella";
			AddDialogExitQuest("Romantic_SalvatorInCave");
		break;
		//после схватки с Сальватором в пещере
		case "SalvatorIsDead":
            dialog.text = DLG_TEXT_QB[146];
            link.l1 = DLG_TEXT_QB[147];
			link.l1.go = "SalvatorIsDead_1";
		break;
		case "SalvatorIsDead_1":
            dialog.text = DLG_TEXT_QB[148] + pchar.name + DLG_TEXT_QB[149];
            link.l1 = DLG_TEXT_QB[150];
			link.l1.go = "SalvatorIsDead_2";
		break;
		case "SalvatorIsDead_2":
            dialog.text = pchar.name + DLG_TEXT_QB[151];
            link.l1 = DLG_TEXT_QB[152];
			link.l1.go = "SalvatorIsDead_3";
		break;
		case "SalvatorIsDead_3":
            dialog.text = DLG_TEXT_QB[153]+
				          DLG_TEXT_QB[154];
            link.l1 = DLG_TEXT_QB[155];
			link.l1.go = "SalvatorIsDead_4";
		break;
		case "SalvatorIsDead_4":
            dialog.text = DLG_TEXT_QB[156];
            link.l1 = DLG_TEXT_QB[157];
			link.l1.go = "SalvatorIsDead_5";
		break;
		case "SalvatorIsDead_5":
            dialog.text = DLG_TEXT_QB[158];
            link.l1 = DLG_TEXT_QB[159];
			link.l1.go = "SalvatorIsDead_6";
		break;
		case "SalvatorIsDead_6":
            dialog.text = DLG_TEXT_QB[160] + pchar.name + DLG_TEXT_QB[161];
            link.l1 = DLG_TEXT_QB[162];
			link.l1.go = "SalvatorIsDead_7";
		break;
		case "SalvatorIsDead_7":
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1 = "location";
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1.location = "Beliz_houseS4";
			Pchar.quest.Romantic_DelivToRosita.win_condition = "Romantic_DelivToRosita";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//после спасения в доме у Роситы
		case "RositaHouse":
            dialog.text = DLG_TEXT_QB[163] + GetFullName(pchar) + DLG_TEXT_QB[164];
            link.l1 = DLG_TEXT_QB[165];
			link.l1.go = "RositaHouse_1";
			AddQuestRecord("Romantic_Line", "22");
		break;
		case "RositaHouse_1":
            dialog.text = DLG_TEXT_QB[166];
            link.l1 = DLG_TEXT_QB[167];
			link.l1.go = "exit";
			NextDiag.TempNode = "RositaHouse_1";
		break;
		//Изабелла вновь в Сан-Хуане
		case "InSanJuanAgain":
            dialog.text = DLG_TEXT_QB[168] + pchar.name + DLG_TEXT_QB[169];
            link.l1 = DLG_TEXT_QB[170];
			link.l1.go = "InSanJuanAgain_1";
		break;
		case "InSanJuanAgain_1":
            dialog.text = DLG_TEXT_QB[171];
            link.l1 = DLG_TEXT_QB[172];
			link.l1.go = "InSanJuanAgain_2";
		break;
		case "InSanJuanAgain_2":
            dialog.text = DLG_TEXT_QB[173];
            link.l1 = DLG_TEXT_QB[174];
			link.l1.go = "InSanJuanAgain_3";
		break;
		case "InSanJuanAgain_3":
            dialog.text = DLG_TEXT_QB[175] + pchar.name + DLG_TEXT_QB[176];
            link.l1 = DLG_TEXT_QB[177];
			link.l1.go = "InSanJuanAgain_4";
		break;
		case "InSanJuanAgain_4":
            dialog.text = DLG_TEXT_QB[178];
            link.l1 = DLG_TEXT_QB[179];
			link.l1.go = "exit";
			NextDiag.TempNode = "InSanJuanAgain_after";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем двери дома.
			pchar.RomanticQuest = "WaitBeginWidding";
			AddQuestRecord("Romantic_Line", "23");
		break;
		case "InSanJuanAgain_after":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[180], DLG_TEXT_QB[181], DLG_TEXT_QB[182],
                          DLG_TEXT_QB[183], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[184], DLG_TEXT_QB[185],
                      DLG_TEXT_QB[186], DLG_TEXT_QB[187], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "InSanJuanAgain_out", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "InSanJuanAgain_after";
		break;
		case "InSanJuanAgain_out":
			AddDialogExitQuest("Romantic_OutFromHouse");
			DialogExit();
		break;

		case "Cancel_Widding":
            dialog.text = DLG_TEXT_QB[188];
            link.l1 = DLG_TEXT_QB[189];
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем дом
			CloseQuestHeader("Romantic_Line");
		break;
		case "Cancel_Widding_1":
            dialog.text = DLG_TEXT_QB[190];
            link.l1 = DLG_TEXT_QB[191];
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
		break;
		//свадьба
		case "TalkWidding":
            dialog.text = DLG_TEXT_QB[192] + pchar.name + ".";
            link.l1 = DLG_TEXT_QB[193];
			link.l1.go = "TalkWidding_1";
		break;
		case "TalkWidding_1":
            dialog.text = DLG_TEXT_QB[194] + pchar.name + DLG_TEXT_QB[195];
            link.l1 = DLG_TEXT_QB[196];
			link.l1.go = "TalkWidding_2";
		break;
		case "TalkWidding_2":
            dialog.text = DLG_TEXT_QB[197];
            link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "barmen", "stay");
			AddDialogExitQuest("Romantic_Padre");
		break;
		//драка в церкви
		case "AmbushInChurch":
            dialog.text = DLG_TEXT_QB[198] + pchar.name + DLG_TEXT_QB[199];
            link.l1 = DLG_TEXT_QB[200];
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_2");
		break;
		case "IsabellaIsMyWife":
			dialog.text = DLG_TEXT_QB[201];
			link.l1 = DLG_TEXT_QB[202];
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = DLG_TEXT_QB[203];
			link.l1 = DLG_TEXT_QB[204];
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = DLG_TEXT_QB[205] + pchar.name + DLG_TEXT_QB[206];
			link.l1 = DLG_TEXT_QB[207];
			link.l1.go = "IsabellaIsMyWife_3";
		break;
		case "IsabellaIsMyWife_3":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = DLG_TEXT_QB[208];
			if (sti(rColony.HeroOwn))
			{	
				link.l1 = DLG_TEXT_QB[209];	
				LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			}
			else
			{
				link.l1 = DLG_TEXT_QB[210];				
				pchar.RomanticQuest.MayorOk = 1; //флаг на базар с мэром Сан-Хуана
			}
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 15.0);
			NextDiag.TempNode = "NewLife_firstTime";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый диалог после свадьбы
		case "NewLife_firstTime":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = DLG_TEXT_QB[211];
			if (sti(rColony.HeroOwn))
			{
				dialog.text = DLG_TEXT_QB[212];
				link.l1 = DLG_TEXT_QB[213];
			}
			else
			{
				dialog.text = DLG_TEXT_QB[214];
				link.l1 = DLG_TEXT_QB[215];
			}
			link.l1.go = "NewLife_firstTime_1";
		break;
		case "NewLife_firstTime_1":
			dialog.text = DLG_TEXT_QB[216];
			link.l1 = DLG_TEXT_QB[217];
			link.l1.go = "NewLife_firstTime_2";
		break;
		case "NewLife_firstTime_2":
			dialog.text = DLG_TEXT_QB[218];
			link.l1 = DLG_TEXT_QB[219];
			link.l1.go = "NewLife_firstTime_3";
		break;
		case "NewLife_firstTime_3":
			dialog.text = DLG_TEXT_QB[220];
			link.l1 = DLG_TEXT_QB[221];
			link.l1.go = "NewLife_firstTime_4";
		break;
		case "NewLife_firstTime_4":
			dialog.text = DLG_TEXT_QB[222]+
				          DLG_TEXT_QB[223];
			link.l1 = DLG_TEXT_QB[224];
			link.l1.go = "NewLife_firstTime_5";
		break;
		case "NewLife_firstTime_5":
			dialog.text = DLG_TEXT_QB[225] + FindRussianMoneyString(MOD_SKILL_ENEMY_RATE*10000) + ".";
			link.l1 = DLG_TEXT_QB[226];
			link.l1.go = "NewLife_firstTime_6";
		break;
		case "NewLife_firstTime_6":
			dialog.text = DLG_TEXT_QB[227];
			link.l1 = DLG_TEXT_QB[228];
			link.l1.go = "exit";
			NextDiag.TempNode = "NewLife";
			AddDialogExitQuest("Romantic_afterFirstTime");
		break;
//************************************ новая жизнь бывшего корсара ********************************
		case "NewLife_hello":
			iDay = GetQuestPastDayParam("RomanticQuest");
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[229], DLG_TEXT_QB[230], DLG_TEXT_QB[231]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[232], DLG_TEXT_QB[233]);
			link.l1.go = "NewLife";
			if (iDay > 40)
			{				
				dialog.text = RandPhraseSimple(DLG_TEXT_QB[234] + FindRussianDaysString(iDay) + "?", DLG_TEXT_QB[235] + FindRussianDaysString(iDay) + DLG_TEXT_QB[236]);
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[237], DLG_TEXT_QB[238]);
				link.l1.go = "NewLife_hello_1";
			}
			if (GetQuestPastDayParam("RomanticQuest") > 3 && pchar.RomanticQuest == "OpenTheDoosOfHouse")
			{
				dialog.text = DLG_TEXT_QB[239];
				link.l1 = DLG_TEXT_QB[240];
				link.l1.go = "NewLife_hello_2";					
			}
		break;	
		case "NewLife_hello_1":
			dialog.text = DLG_TEXT_QB[241];
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[242], DLG_TEXT_QB[243]);
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		case "NewLife_hello_2":
			dialog.text = DLG_TEXT_QB[244];
			link.l1 = DLG_TEXT_QB[245];
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		//======================== типовое меню ==========================
		case "NewLife":
			//проверяем, как там с финансами у нас
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > 0)
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[246] + FindRussianMoneyString(iMoney) + DLG_TEXT_QB[247], 
					DLG_TEXT_QB[248] + FindRussianMoneyString(iMoney) + ".", 
					DLG_TEXT_QB[249] + FindRussianMoneyString(iMoney) + ".", 
					DLG_TEXT_QB[250] + FindRussianMoneyString(iMoney) + ".", "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_QB[251], DLG_TEXT_QB[252]), 
					DLG_TEXT_QB[253], 
					DLG_TEXT_QB[254], 
					DLG_TEXT_QB[255], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay";
				break;
			}
			//--> проверяем статистику на пиратство
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.GrabbingTown)*150) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[256], DLG_TEXT_QB[257]);
					link.l1 = LinkRandPhrase(DLG_TEXT_QB[258], DLG_TEXT_QB[259], DLG_TEXT_QB[260]);
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("GrabbingTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.TakeTown") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.TakeTown)*140) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[261], DLG_TEXT_QB[262]);
					link.l1 = LinkRandPhrase(DLG_TEXT_QB[263], DLG_TEXT_QB[264], DLG_TEXT_QB[265]);
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("TakeTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillFort") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillFort)*130) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[266], DLG_TEXT_QB[267]);
					link.l1 = LinkRandPhrase(DLG_TEXT_QB[268], DLG_TEXT_QB[269], DLG_TEXT_QB[270]);
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillFort");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.AbordShip") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.AbordShip)*70) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[271], DLG_TEXT_QB[272]);
					link.l1 = LinkRandPhrase(DLG_TEXT_QB[273], DLG_TEXT_QB[274], DLG_TEXT_QB[275]);
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("AbordShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillShip") && pchar.RomanticQuest.Cheking != "Ok") 
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillShip)*50) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[276], DLG_TEXT_QB[277]);
					link.l1 = LinkRandPhrase(DLG_TEXT_QB[278], DLG_TEXT_QB[279], DLG_TEXT_QB[280]);
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			//<-- проверяем статистику на пиратство
			//        -------  ОСНОВНОЕ МЕНЮ  ----------
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[281], DLG_TEXT_QB[282], DLG_TEXT_QB[283] + pchar.lastname + DLG_TEXT_QB[284]);
			link.l1 = DLG_TEXT_QB[285];
			link.l1.go = "NewLife_JustTalk";
			link.l2 = DLG_TEXT_QB[286];
			link.l2.go = "NewLife_Budget";
			link.l3 = DLG_TEXT_QB[287];
			link.l3.go = "NewLife_Present";
			link.l4 = DLG_TEXT_QB[288];
			link.l4.go = "NewLife_Sex";
			link.l5 = DLG_TEXT_QB[289];
			link.l5.go = "NewLife_Sleep";
		break;
		//=========================== Бюджет =================================
		case "NewLife_Budget":	
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > -(MOD_SKILL_ENEMY_RATE*10000)) //деньги на исходе
			{
				if (iMoney == 0)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_QB[290], DLG_TEXT_QB[291]);
				}
				else
				{
					dialog.text = DLG_TEXT_QB[292] + FindRussianMoneyString(-iMoney) + ".";
					link.l1 = RandPhraseSimple(DLG_TEXT_QB[293], DLG_TEXT_QB[294]);
					link.l1.go = "NewLife";
				}
				link.l2 = RandPhraseSimple(DLG_TEXT_QB[295], DLG_TEXT_QB[296]);
				link.l2.go = "NewLife_Budget_Add";
				LAi_CharacterPlaySound(npchar, "Gr_Isabella_4");
			}
			else //профицит
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_QB[297] + FindRussianMoneyString(-iMoney) + DLG_TEXT_QB[298], DLG_TEXT_QB[299] + FindRussianMoneyString(-iMoney) + ".");
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[300], DLG_TEXT_QB[301]);
				link.l1.go = "NewLife";			
				link.l2 = DLG_TEXT_QB[302];
				link.l2.go = "NewLife_Budget_Add";
			}
		break;
		case "NewLife_Budget_Add":			
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[303], DLG_TEXT_QB[304], DLG_TEXT_QB[305], DLG_TEXT_QB[306], "repeat", 10, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= 50000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[307], DLG_TEXT_QB[308], DLG_TEXT_QB[309], "...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_50";
			}
			if (sti(pchar.money) >= 100000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l2 = HeroStringReactionRepeat(DLG_TEXT_QB[310], DLG_TEXT_QB[311], DLG_TEXT_QB[311], "...", npchar, Dialog.CurrentNode);
				link.l2.go = "NewLife_Budget_100";
			}
			if (sti(pchar.money) >= 200000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l3 = HeroStringReactionRepeat(DLG_TEXT_QB[312], DLG_TEXT_QB[313], DLG_TEXT_QB[313], "...", npchar, Dialog.CurrentNode);
				link.l3.go = "NewLife_Budget_200";
			}
			if (sti(pchar.money) >= 500000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l4 = HeroStringReactionRepeat(DLG_TEXT_QB[314], DLG_TEXT_QB[315], DLG_TEXT_QB[315], "...", npchar, Dialog.CurrentNode);
				link.l4.go = "NewLife_Budget_500";
			}
			link.l5 = HeroStringReactionRepeat(DLG_TEXT_QB[316], DLG_TEXT_QB[317], DLG_TEXT_QB[318], DLG_TEXT_QB[319], npchar, Dialog.CurrentNode);
			link.l5.go = "NewLife_Budget_No";
		break;
		case "NewLife_Budget_50":
			dialog.text = DLG_TEXT_QB[320] + pchar.name + DLG_TEXT_QB[321];
			link.l1 = DLG_TEXT_QB[322];
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(50000);
		break;
		case "NewLife_Budget_100":
			dialog.text = DLG_TEXT_QB[323];
			link.l1 = DLG_TEXT_QB[324];
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(100000);
		break;
		case "NewLife_Budget_200":
			dialog.text = DLG_TEXT_QB[325];
			link.l1 = DLG_TEXT_QB[326];
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(200000);
		break;
		case "NewLife_Budget_500":
			dialog.text = DLG_TEXT_QB[327];
			link.l1 = DLG_TEXT_QB[328];
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(500000);
		break;
		case "NewLife_Budget_No":
            dialog.text = LinkRandPhrase(DLG_TEXT_QB[329], DLG_TEXT_QB[330] , DLG_TEXT_QB[331]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[332], DLG_TEXT_QB[333], DLG_TEXT_QB[334]);
			link.l1.go = "NewLife";
		break;
		//заплатить долги и понулить счетчик бюджета
		case "NewLife_Budget_Pay":
			iMoney = IsabellaCheckBudgetMoney();
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[335] + pchar.lastname + DLG_TEXT_QB[336], 
				DLG_TEXT_QB[337], 
				DLG_TEXT_QB[338], 
				DLG_TEXT_QB[339], "quest", 30, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= iMoney)
			{
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[340], DLG_TEXT_QB[341], DLG_TEXT_QB[342], DLG_TEXT_QB[343], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_2";
				link.l2 = DLG_TEXT_QB[344];
				link.l2.go = "NewLife_Budget_Pay_1";	
			}
			else
			{
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[345] + FindRussianMoneyString(iMoney) + "...", DLG_TEXT_QB[346], DLG_TEXT_QB[347], DLG_TEXT_QB[348], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_1";
			}
		break;
		case "NewLife_Budget_Pay_1":
			dialog.text = RandPhraseSimple(DLG_TEXT_QB[349], DLG_TEXT_QB[350]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[351], DLG_TEXT_QB[352]);
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_Budget_Pay_2":
            dialog.text = RandPhraseSimple(DLG_TEXT_QB[353], DLG_TEXT_QB[354]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[355], DLG_TEXT_QB[356]);
			link.l1.go = "NewLife";
			iMoney = IsabellaCheckBudgetMoney();
			AddMoneyToCharacter(pchar, -iMoney);
			IsabellaNullBudget();
		break;
		//=========================== Изабелла узнала, что ГГ опять пиратствует =================================
		case "NewLife_KnowPirates":
			pchar.RomanticQuest.Cheking = "Ok"; //флаг 'не проверять больше на пиратство' в этот раз
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma")) //поверила, дура :)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[357] + pchar.name + "...", DLG_TEXT_QB[358], DLG_TEXT_QB[359] + pchar.name + DLG_TEXT_QB[360]);
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[361], DLG_TEXT_QB[362]);
				link.l1.go = "NewLife";
			}
			else //не поверила, и правильно сделала
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[363], 
					DLG_TEXT_QB[364], 
					DLG_TEXT_QB[365] + pchar.name + ".", 
					DLG_TEXT_QB[366] + pchar.lastname + DLG_TEXT_QB[367], "quest", 80, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[368], 
					DLG_TEXT_QB[369], 
					DLG_TEXT_QB[370], 
					DLG_TEXT_QB[371], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife";	
			}
		break;
		//=========================== Секс =================================
		case "NewLife_Sex":			
			if (GetQuestPastMonthParam("RomanticQuest") > 2 && GetNpcQuestPastDayParam(npchar, "sex") != 0)
			{
				dialog.text = DLG_TEXT_QB[372];
				link.l1 = DLG_TEXT_QB[373];
				link.l1.go = "NewLife_Sex_1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[374], 
					DLG_TEXT_QB[375], 
					DLG_TEXT_QB[376], 
					DLG_TEXT_QB[377], "cycle", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[378], 
					DLG_TEXT_QB[379], 
					DLG_TEXT_QB[380], 
					DLG_TEXT_QB[381], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Sex_5";
			}			
		break;
		case "NewLife_Sex_1":
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
			dialog.text = DLG_TEXT_QB[382];
			link.l1 = DLG_TEXT_QB[383];
			link.l1.go = "NewLife_Sex_2";
		break;
		case "NewLife_Sex_2":
			dialog.text = DLG_TEXT_QB[384];
			link.l1 = DLG_TEXT_QB[385];
			link.l1.go = "NewLife_Sex_3";
		break;
		case "NewLife_Sex_3":
			dialog.text = DLG_TEXT_QB[386];
			link.l1 = DLG_TEXT_QB[387];
			link.l1.go = "NewLife_Sex_4";
		break;
		case "NewLife_Sex_4":
			if (rand(6) < 5)
			{
				dialog.text = DLG_TEXT_QB[388];
				link.l1 = DLG_TEXT_QB[389];
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = DLG_TEXT_QB[390];
				link.l1 = DLG_TEXT_QB[391];
				link.l1.go = "NewLife_exit";
			}
		break;

		case "NewLife_Sex_Late":
			dialog.text = DLG_TEXT_QB[392];
			link.l1 = DLG_TEXT_QB[393];
			link.l1.go = "NewLife_Sex_Late_1";			
		break;
		case "NewLife_Sex_Late_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NewLife_Sex_5":
			if (GetNpcQuestPastDayParam(npchar, "sex") > 3)
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[394], 
					DLG_TEXT_QB[395], 
					DLG_TEXT_QB[396], 
					DLG_TEXT_QB[397], "block", 60, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[398], 
					DLG_TEXT_QB[399], 
					DLG_TEXT_QB[400], 
					DLG_TEXT_QB[401], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("NewLife_Sex_10", "NewLife_Sex_11", "NewLife_Sex_12", "NewLife_Sex_13", npchar, Dialog.CurrentNode);
			}
			else //слишком часто, не прокатит
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[402], DLG_TEXT_QB[403], DLG_TEXT_QB[404]);
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[405], DLG_TEXT_QB[406]);
				link.l1.go = "NewLife_exit";
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
		break;
		case "NewLife_Sex_10":
			dialog.text = DLG_TEXT_QB[407];
			link.l1 = DLG_TEXT_QB[408];
			link.l1.go = "NewLife_GoSex";
		break;
		case "NewLife_Sex_11":
			if (rand(10) < 8)
			{
				dialog.text = DLG_TEXT_QB[409];
				link.l1 = DLG_TEXT_QB[410];
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[411], DLG_TEXT_QB[412], DLG_TEXT_QB[413]);
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[414], DLG_TEXT_QB[415]);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_12":
			if (rand(10) < 5)
			{
				dialog.text = DLG_TEXT_QB[416];
				link.l1 = DLG_TEXT_QB[417];
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[418], DLG_TEXT_QB[419], DLG_TEXT_QB[420]);
				link.l1 = RandPhraseSimple(DLG_TEXT_QB[421], DLG_TEXT_QB[422]);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_13":
			if (rand(10) < 2)
			{
				dialog.text = DLG_TEXT_QB[423];
				link.l1 = DLG_TEXT_QB[424];
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = DLG_TEXT_QB[425];
				link.l1 = DLG_TEXT_QB[426];
				link.l1.go = "NewLife_exit";
			}
		break;
		//идем в спальню
		case "NewLife_GoSex":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запомнить секс
			Pchar.quest.Romantic_Sex.win_condition.l1 = "location";
			Pchar.quest.Romantic_Sex.win_condition.l1.location = "SanJuan_houseS1Bedroom";
			Pchar.quest.Romantic_Sex.win_condition = "Romantic_Sex";
			SetTimerCondition("Romantic_IsabellaBackToHall", 0, 0, 1, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto6", "Romantic_TalkInChurch_end", 20.0);
			DialogExit();
		break;
		//после секса
		case "NewLife_afterSex":			
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[427], 
				DLG_TEXT_QB[428], 
				DLG_TEXT_QB[429], 
				DLG_TEXT_QB[430], "block", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[431], 
				DLG_TEXT_QB[432], 
				DLG_TEXT_QB[433], 
				DLG_TEXT_QB[434], npchar, Dialog.CurrentNode);
			link.l1.go = "NewLife_afterSex_1";
		break;
		case "NewLife_afterSex_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true; 
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto2", "Romantic_TalkInChurch_end", 20.0);
			Pchar.quest.Romantic_IsabellaBackToHall.over = "yes";
			DialogExit();
		break;
		//=========================== Сон =================================
		case "NewLife_Sleep":
			dialog.text = DLG_TEXT_QB[435];
			if(!isDay())
			{
				link.l1 = DLG_TEXT_QB[436];
				link.l1.go = "NewLife_Sleep_day";
			}
			else
			{
				link.l1 = DLG_TEXT_QB[437];
				link.l1.go = "NewLife_Sleep_night";
				link.l2 = DLG_TEXT_QB[438];
				link.l2.go = "NewLife_Sleep_day";
			}
		break;
		case "NewLife_Sleep_day":
			dialog.text = DLG_TEXT_QB[439];
			link.l1 = DLG_TEXT_QB[440];
			link.l1.go = "room_day_wait";
			link.l2 = DLG_TEXT_QB[441];
			link.l2.go = "NewLife_exit";
		break;
		case "NewLife_Sleep_night":
			dialog.text = DLG_TEXT_QB[442];
			link.l1 = DLG_TEXT_QB[443];
			link.l1.go = "room_night_wait";
			link.l2 = DLG_TEXT_QB[444];
			link.l2.go = "NewLife_exit";
		break;
		case "room_day_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_day");
			AddDialogExitQuest("sleep_in_home");
		break;
		case "room_night_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			TavernWaitDate("wait_night");
			AddDialogExitQuest("sleep_in_home");
		break;
		//=========================== Просто разговор =================================
		case "NewLife_JustTalk":
			if (CheckAttribute(pchar, "RomanticQuest.Atilla"))
			{
				switch (pchar.RomanticQuest.Atilla)
				{
					case "YouAreBaster": 
						dialog.text = DLG_TEXT_QB[445];
						link.l1 = DLG_TEXT_QB[446];
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreNormal": 
						dialog.text = DLG_TEXT_QB[447];
						link.l1 = DLG_TEXT_QB[448];
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreGood": 
						dialog.text = DLG_TEXT_QB[449];
						link.l1 = DLG_TEXT_QB[450];
						link.l1.go = "NewLife_exit";
					break;
				}
				DeleteAttribute(pchar, "RomanticQuest.Atilla");
				break;
			}
			switch (rand(1))
			{
				case 0: 
					dialog.text = LinkRandPhrase(DLG_TEXT_QB[451], pchar.name + DLG_TEXT_QB[452], DLG_TEXT_QB[453] + GetMainCharacterNameGen() + "...");
					link.l1 = RandPhraseSimple(DLG_TEXT_QB[454], DLG_TEXT_QB[455]);
					link.l1.go = "NewLife_exit";
				break;
				case 1: 
					dialog.text = LinkRandPhrase(DLG_TEXT_QB[456], DLG_TEXT_QB[457], DLG_TEXT_QB[458]);
					link.l1 = RandPhraseSimple(DLG_TEXT_QB[459], DLG_TEXT_QB[460]);
					link.l1.go = "NewLife_exit";
				break;
			}
		break;
		//=========================== Подарки =================================
		case "NewLife_Present":
			dialog.text = RandPhraseSimple(DLG_TEXT_QB[461], DLG_TEXT_QB[462]);
			iTemp = 1;
			for (i=18; i>=1; i--)
			{
				if (i==8 || i==9) continue;
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = XI_ConvertString("jewelry"+i+"Gen") + ".";
					link.(sTemp).go = "NewLife_jewelry_"+i;
					iTemp++;				
				}
			}
			if (iTemp == 1)
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_QB[463], 
					DLG_TEXT_QB[464], 
					pchar.name + DLG_TEXT_QB[465], 
					DLG_TEXT_QB[466], "repeat", 20, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_QB[467], 
					DLG_TEXT_QB[468], 
					DLG_TEXT_QB[469], 
					DLG_TEXT_QB[470], npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_jewelry_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[471], DLG_TEXT_QB[472] , DLG_TEXT_QB[473]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[474], DLG_TEXT_QB[475], DLG_TEXT_QB[476]);
			link.l1.go = "NewLife_exit";			
			TakeItemFromCharacter(pchar, "jewelry1");
		break;
		case "NewLife_jewelry_2":
			if (rand(4)==1)
			{
				dialog.text = DLG_TEXT_QB[477];
				link.l1 = DLG_TEXT_QB[478];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[479], DLG_TEXT_QB[480] , DLG_TEXT_QB[481]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[482], DLG_TEXT_QB[483], DLG_TEXT_QB[484]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry2");
		break;
		case "NewLife_jewelry_3":
			if (rand(10)==1)
			{
				dialog.text = DLG_TEXT_QB[485];
				link.l1 = DLG_TEXT_QB[486];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[487], DLG_TEXT_QB[488] , DLG_TEXT_QB[489]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[490], DLG_TEXT_QB[491], DLG_TEXT_QB[492]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry3");
		break;
		case "NewLife_jewelry_4":
			if (rand(3)==1)
			{
				dialog.text = DLG_TEXT_QB[493];
				link.l1 = DLG_TEXT_QB[494];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[495], DLG_TEXT_QB[496] , DLG_TEXT_QB[497]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[498], DLG_TEXT_QB[499], DLG_TEXT_QB[500]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry4");
		break;
		case "NewLife_jewelry_5":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[501], DLG_TEXT_QB[502] , DLG_TEXT_QB[503]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[504], DLG_TEXT_QB[505], DLG_TEXT_QB[506]);
			link.l1.go = "NewLife_exit";	
			TakeItemFromCharacter(pchar, "jewelry5");
		break;
		case "NewLife_jewelry_6":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[507], DLG_TEXT_QB[508] , DLG_TEXT_QB[509]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[510], DLG_TEXT_QB[511], DLG_TEXT_QB[512]);
			link.l1.go = "NewLife_exit";			
			TakeItemFromCharacter(pchar, "jewelry6");
		break;
		case "NewLife_jewelry_7":
			if (rand(2)==1)
			{
				dialog.text = DLG_TEXT_QB[513];
				link.l1 = DLG_TEXT_QB[514];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[515], DLG_TEXT_QB[516] , DLG_TEXT_QB[517]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[518], DLG_TEXT_QB[519], DLG_TEXT_QB[520]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry7");
		break;
		case "NewLife_jewelry_10":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[521], DLG_TEXT_QB[522] , DLG_TEXT_QB[523]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[524], DLG_TEXT_QB[525], DLG_TEXT_QB[526]);
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry10");
		break;
		case "NewLife_jewelry_11":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[527], DLG_TEXT_QB[528] , DLG_TEXT_QB[529]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[530], DLG_TEXT_QB[531], DLG_TEXT_QB[532]);
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry11");
		break;
		case "NewLife_jewelry_12":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[533], DLG_TEXT_QB[534] , DLG_TEXT_QB[535]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[536], DLG_TEXT_QB[537]);
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry12");
		break;
		case "NewLife_jewelry_13":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[538], DLG_TEXT_QB[539] , DLG_TEXT_QB[540]);
			link.l1 = LinkRandPhrase(DLG_TEXT_QB[541], DLG_TEXT_QB[542], DLG_TEXT_QB[543]);
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry13");
		break;
		case "NewLife_jewelry_14":
			if (rand(1)==1)
			{
				dialog.text = DLG_TEXT_QB[544];
				link.l1 = DLG_TEXT_QB[545];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[546], DLG_TEXT_QB[547] , DLG_TEXT_QB[548]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[549], DLG_TEXT_QB[550], DLG_TEXT_QB[551]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry14");
		break;
		case "NewLife_jewelry_15":
			if (rand(1)==1)
			{
				dialog.text = DLG_TEXT_QB[552];
				link.l1 = DLG_TEXT_QB[553];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[554], DLG_TEXT_QB[555] , DLG_TEXT_QB[556]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[557], DLG_TEXT_QB[558], DLG_TEXT_QB[559]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry15");
		break;
		case "NewLife_jewelry_16":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[560], DLG_TEXT_QB[561] , DLG_TEXT_QB[562]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[563], DLG_TEXT_QB[564]);
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_jewelry_17":
			dialog.text = LinkRandPhrase(DLG_TEXT_QB[565], DLG_TEXT_QB[566] , DLG_TEXT_QB[567]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[568], DLG_TEXT_QB[569]);
			link.l1.go = "NewLife_exit";	
			TakeItemFromCharacter(pchar, "jewelry17");
		break;
		case "NewLife_jewelry_18":
			if (rand(8)==1)
			{
				dialog.text = DLG_TEXT_QB[570];
				link.l1 = DLG_TEXT_QB[571];
				link.l1.go = "NewLife_GoSex";				
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_QB[572], DLG_TEXT_QB[573] , DLG_TEXT_QB[574]);
				link.l1 = LinkRandPhrase(DLG_TEXT_QB[575], DLG_TEXT_QB[576], DLG_TEXT_QB[577]);
				link.l1.go = "NewLife_exit";			
			}
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		//выход
		case "NewLife_exit":
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto"+(rand(3)+1), "Romantic_TalkInChurch_end", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryRepeat_Budget_Add":
            dialog.text = RandPhraseSimple(DLG_TEXT_QB[578], DLG_TEXT_QB[579]);
			link.l1 = DLG_TEXT_QB[580];
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_QB[581];
        			link.l1 = DLG_TEXT_QB[582];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через кольцо с сапфиром
				{
					if (CheckCharacterItem(pchar, "jewelry6") && CheckCharacterItem(pchar, "jewelry10"))
					{
         				dialog.text = DLG_TEXT_QB[583];
        				link.l1 = DLG_TEXT_QB[584];
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry6");
						TakeItemFromCharacter(pchar, "jewelry10");
					}
				}
            }	
    	break;
		//==> вовремя не рассчитался с долгами
		case "AngryRepeat_Budget_Pay":
            dialog.text = RandPhraseSimple(DLG_TEXT_QB[585], DLG_TEXT_QB[586]);
			link.l1 = DLG_TEXT_QB[587];
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_QB[588];
        			link.l1 = DLG_TEXT_QB[589];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через изумруды
				{
					if (CheckCharacterItem(pchar, "jewelry4") && CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "jewelry15"))
					{
         				dialog.text = DLG_TEXT_QB[590];
        				link.l1 = DLG_TEXT_QB[591];
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry4");
						TakeItemFromCharacter(pchar, "jewelry7");
						TakeItemFromCharacter(pchar, "jewelry15");
					}
				}
            }
    	break;
		//==> если попался на пиратстве
		case "AngryRepeat_KnowPirates":
            dialog.text = RandPhraseSimple(DLG_TEXT_QB[592], DLG_TEXT_QB[593]);
			link.l1 = DLG_TEXT_QB[594];
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 80 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_QB[595];
        			link.l1 = DLG_TEXT_QB[596];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar); 
					IsabellaSetCurrentState("All");
                }
				else //примирение через алмаз, рубины и большую жемчужину
				{
					if (CheckCharacterItem(pchar, "jewelry1") && CheckCharacterItem(pchar, "jewelry2") && CheckCharacterItem(pchar, "jewelry3") && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry11"))
					{
         				dialog.text = DLG_TEXT_QB[597] + pchar.name + DLG_TEXT_QB[598];
        				link.l1 = DLG_TEXT_QB[599];
        				link.l1.go = NextDiag.TempNode;
        				CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry1");
						TakeItemFromCharacter(pchar, "jewelry2");
						TakeItemFromCharacter(pchar, "jewelry3");
						TakeItemFromCharacter(pchar, "jewelry18");
						TakeItemFromCharacter(pchar, "jewelry11");
						IsabellaSetCurrentState("All");
					}
				}
			}
    	break;
		//==> если достал подарками
		case "AngryRepeat_Present":
            dialog.text = RandPhraseSimple(DLG_TEXT_QB[600], DLG_TEXT_QB[601]);
			link.l1 = RandPhraseSimple(DLG_TEXT_QB[602], DLG_TEXT_QB[603]);
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся 20 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_QB[604];
        			link.l1 = DLG_TEXT_QB[605];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
				else //примирение через злато-серебро
				{
					if (CheckCharacterItem(pchar, "jewelry5") && CheckCharacterItem(pchar, "jewelry17"))
					{
						if (sti(pchar.items.jewelry5) >= 3 && sti(pchar.items.jewelry17) >=5)
						{
         					dialog.text = DLG_TEXT_QB[606];
        					link.l1 = DLG_TEXT_QB[607];
        					link.l1.go = NextDiag.TempNode;
        					CharacterDelAngry(npchar);
							TakeNItems(pchar, "jewelry5", -3);
							TakeNItems(pchar, "jewelry17", -5);
						}
					}
				}
			}
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

