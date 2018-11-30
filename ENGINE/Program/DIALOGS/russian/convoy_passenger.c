//пассажир на доставку
#include "TEXT\DIALOGS\convoy_passenger.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]);
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + DLG_TEXT_BASE[4]+ GetFullName(NPChar) + DLG_TEXT_BASE[5];
				link.l1 = DLG_TEXT_BASE[6];
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = DLG_TEXT_BASE[7] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + DLG_TEXT_BASE[8] + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") +
                          DLG_TEXT_BASE[9] + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + DLG_TEXT_BASE[10] + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + DLG_TEXT_BASE[11];
			link.l1 = DLG_TEXT_BASE[12];
			link.l1.go = "convoy_agreeded";
			link.l2 = DLG_TEXT_BASE[13];
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + DLG_TEXT_BASE[14] + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернем его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = DLG_TEXT_BASE[15];
			Link.l1 = DLG_TEXT_BASE[16];
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[17] + GetFullName(npchar) + DLG_TEXT_BASE[18] + GetMainCharacterNameDat() + DLG_TEXT_BASE[19] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				DLG_TEXT_BASE[20] + GetFullName(npchar) + DLG_TEXT_BASE[21] + GetMainCharacterNameDat() + DLG_TEXT_BASE[22] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + DLG_TEXT_BASE[23], 
				DLG_TEXT_BASE[24] + GetFullName(npchar) + DLG_TEXT_BASE[25]), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterReputation(pchar, 1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + DLG_TEXT_BASE[26] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", 
						  RandSwear() + DLG_TEXT_BASE[27] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?" , 
						  RandSwear() + DLG_TEXT_BASE[28] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + DLG_TEXT_BASE[29]), 
				RandPhraseSimple(DLG_TEXT_BASE[30] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", DLG_TEXT_BASE[31] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?"), 
				RandPhraseSimple(RandSwear() + DLG_TEXT_BASE[32] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", DLG_TEXT_BASE[33] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"), 
                DLG_TEXT_BASE[34], "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[35], DLG_TEXT_BASE[36] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[37]),
					RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]),
					RandPhraseSimple(DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]),
					DLG_TEXT_BASE[42] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[43], npchar, Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[44], DLG_TEXT_BASE[45]),
				DLG_TEXT_BASE[46],
				DLG_TEXT_BASE[47],
				DLG_TEXT_BASE[48] + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[49], DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[52], DLG_TEXT_BASE[53], DLG_TEXT_BASE[54]);
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
			Link.l1 = DLG_TEXT_BASE[57];
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear() + DLG_TEXT_BASE[58];
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = DLG_TEXT_BASE[59];
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = DLG_TEXT_BASE[60];
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear() + DLG_TEXT_BASE[61];
			Link.l1 = DLG_TEXT_BASE[62];
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[63] + GetFullName(pchar) + DLG_TEXT_BASE[64] + GetFullName(npchar) + DLG_TEXT_BASE[65], 
				DLG_TEXT_BASE[66] + GetFullName(pchar) + DLG_TEXT_BASE[67] + GetFullName(npchar) + DLG_TEXT_BASE[68], 
				DLG_TEXT_BASE[69] + GetFullName(npchar) + DLG_TEXT_BASE[70] + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + DLG_TEXT_BASE[71]), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterReputation(pchar, -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 10+rand(10));// награда            
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp;

	iTradeMoney = sti(PChar.rank)*100 + sti(NPChar.rank)*120 + cRand(30)*20;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * (Rand(2)/2.0 + 1.0)); //то размер награды увеличивается

	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;
    npchar.GenQuest.GetPassenger_Time  = 20 + cRand(10);

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}
