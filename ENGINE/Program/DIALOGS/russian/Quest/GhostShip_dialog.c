#include "TEXT\DIALOGS\Quest\GhostShip_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "Meeting_1";
			NextDiag.TempNode = "First time";
		break;

        case "Meeting_1":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "Meeting_2";
		break;
		
		case "Meeting_2":
			dialog.text = DLG_TEXT_Q[4];
			link.l1 = DLG_TEXT_Q[5];
			link.l1.go = "Meeting_3";
		break;
		
		case "Meeting_3":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "Meeting_4";
		break;
		
		case "Meeting_4":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			ReOpenQuestHeader("GhostShipQuest");
        	AddQuestRecord("GhostShipQuest", "4");
		break;
		
		case "AfterMeet":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			bOk = (sti(PChar.GenQuest.GhostShip.KillMe) > 0) || (sti(PChar.GenQuest.GhostShip.DeadByMe) > 0);
			if (bOk && !CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
            {
    			Link.l3 = DLG_TEXT_Q[12];
    			Link.l3.go = "GhostCapt";
			}
			if (GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
			{
                Link.l4 = DLG_TEXT_Q[13];
    			Link.l4.go = "quest_coin_2";
			}
		break;
		
		// корабль
		case "GhostCapt":
			NextDiag.TempNode = "AfterMeet";
			dialog.Text = DLG_TEXT_Q[14];
			Link.l1 = DLG_TEXT_Q[15];
			Link.l1.go = "GhostCapt_1";
		break;
		
		case "GhostCapt_1":
			dialog.Text = DLG_TEXT_Q[16];
			Link.l1 = DLG_TEXT_Q[17];
			Link.l1.go = "GhostCapt_2";
		break;
		
		case "GhostCapt_2":
			dialog.Text = DLG_TEXT_Q[18];
			Link.l1 = DLG_TEXT_Q[19];
			Link.l1.go = "GhostCapt_3";
		break;
		
		case "GhostCapt_3":
			dialog.Text = DLG_TEXT_Q[20];
			Link.l1 = DLG_TEXT_Q[21];
			Link.l1.go = "GhostCapt_4";
		break;
		
		case "GhostCapt_4":
			dialog.Text = DLG_TEXT_Q[22];
			Link.l1 = DLG_TEXT_Q[23];
			Link.l1.go = "Exit";
			AddQuestRecord("GhostShipQuest", "5");
			PChar.GenQuest.GhostShip.NeedCoins = true;
		break;
		
		case "quest_coin_2":
            dialog.Text = DLG_TEXT_Q[24];
			Link.l1 = DLG_TEXT_Q[25];
			Link.l1.go = "Exit";
			TakeNItems(pchar, "Coins", -666);
			AddQuestRecord("GhostShipQuest", "6");
			PChar.GenQuest.GhostShip.LastBattle = true;
			NPChar.location = "none";
			NPChar.LifeDay = 0;
            NextDiag.TempNode = "temp_coins";
		break;
		
		case "temp_coins":
            dialog.Text = DLG_TEXT_Q[26];
			Link.l1 = DLG_TEXT_Q[27];
			Link.l1.go = "Exit";
			NextDiag.TempNode = "temp_coins";
		break;
	}
}
