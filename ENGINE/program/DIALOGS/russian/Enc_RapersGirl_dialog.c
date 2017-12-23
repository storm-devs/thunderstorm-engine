#include "TEXT\DIALOGS\Enc_RapersGirl_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(npchar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]);
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[6],
				DLG_TEXT_BASE[7],
				DLG_TEXT_BASE[8]);
			Link.l1 = DLG_TEXT_BASE[9];
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10],
				DLG_TEXT_BASE[11],
				DLG_TEXT_BASE[12]);
			Link.l1 = DLG_TEXT_BASE[13];
			Link.l1.go = "ThanksForHelp_1";			
		break;
		
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation) >= 80)
			{
				dialog.text = DLG_TEXT_BASE[14];
				Link.l1 = DLG_TEXT_BASE[15];
				Link.l1.go = "exit";
			}
			else 
			{
				if(Rand(1) == 0)
				{
					dialog.text = DLG_TEXT_BASE[16];
					Link.l1 = DLG_TEXT_BASE[17];
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = DLG_TEXT_BASE[18];
					Link.l1 = DLG_TEXT_BASE[19];
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = DLG_TEXT_BASE[20];
			Link.l1 = DLG_TEXT_BASE[21];
			Link.l1.go = "exit";
		break;
	}
}
