#include "TEXT\DIALOGS\Quest\T102_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
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
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "Term_1";
			TakeNItems(Pchar, "term_arm", -1);
		break;
		
		case "Term_1":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "Term_2";
		break;
		
		case "Term_2":
			dialog.text = DLG_TEXT_Q[4] +GetFullName(pchar) +
			              DLG_TEXT_Q[5];
			link.l1 = DLG_TEXT_Q[6];
			link.l1.go = "Term_3";
		break;
		
		case "Term_3":
			dialog.text = "Error. Main power too low. Critical error - restarting....";
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "Term_4";
		break;
		
		case "Term_4":
			dialog.text = "Loading from backup store....";
			link.l1 = DLG_TEXT_Q[8];
			link.l1.go = "Term_5";
		break;
		
		case "Term_5":
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "Term_6";
		break;
		
		case "Term_6":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12] + GetDataYear() + DLG_TEXT_Q[13];
			link.l1.go = "Term_7";
		break;
		
		case "Term_7":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "Term_8";
		break;
		
		case "Term_8":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "Term_9";
		break;
		
		case "Term_9":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "Term_9_1";
		break;
		
		case "Term_9_1":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "Term_9_2";
		break;
		
		case "Term_9_2":
			dialog.text = DLG_TEXT_Q[22] +GetFullName(pchar) +DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "Term_10";
		break;
		
		case "Term_10":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "Term_10_exit";
			//PChar.GenQuest.GhostShip.TakeShotgun = true;
		break;
		
		case "Term_10_exit":
            LAi_SetPlayerType(PChar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			//ChangeCharacterAddressGroup(NPChar, "none", "", "");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
	}
} 
