#include "TEXT\DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

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
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = DLG_TEXT_BASE[7];
			link.l1 = DLG_TEXT_BASE[8];
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			GenerateConvoyQuest(npchar);
			dialog.text = DLG_TEXT_BASE[9] + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + DLG_TEXT_BASE[10] + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") +
				DLG_TEXT_BASE[11] + FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)) +DLG_TEXT_BASE[12] + FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)) + DLG_TEXT_BASE[13];
			link.l1 = DLG_TEXT_BASE[14];
			link.l1.go = "convoy_agreeded";
			link.l2 = DLG_TEXT_BASE[15];
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = DLG_TEXT_BASE[16];
			Link.l1 = DLG_TEXT_BASE[17];
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[18] + GetFullName(npchar) + DLG_TEXT_BASE[19] + GetMainCharacterNameDat() + DLG_TEXT_BASE[20], 
				DLG_TEXT_BASE[21] + GetFullName(npchar) + DLG_TEXT_BASE[22] + GetMainCharacterNameDat() + DLG_TEXT_BASE[23] + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".", 
				DLG_TEXT_BASE[24] + GetFullName(npchar) + DLG_TEXT_BASE[25]), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney;

	DeleteAttribute(NPChar, "Ship");
    SetShipToFantom(NPChar, "trade", true);

	iTradeMoney = sti(PChar.rank)*100 + sti(NPChar.rank)*170 + cRand(30)*20;

	pchar.ConvoyQuest.convoymoney = iTradeMoney;
	pchar.ConvoyQuest.iDay  = 20 + cRand(10);

	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}
