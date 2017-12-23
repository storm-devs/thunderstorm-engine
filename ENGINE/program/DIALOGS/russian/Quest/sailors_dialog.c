#include "TEXT\DIALOGS\Quest\sailors_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			Link.l1 = DLG_TEXT_Q[1];
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = DLG_TEXT_Q[2];
			Link.l1 = DLG_TEXT_Q[3];
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple(DLG_TEXT_Q[4],
	                                           DLG_TEXT_Q[5]);
				Link.l1 = DLG_TEXT_Q[6];
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple(DLG_TEXT_Q[7], DLG_TEXT_Q[8]);
			Link.l1 = DLG_TEXT_Q[9];
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple(DLG_TEXT_Q[10],
                                           DLG_TEXT_Q[11]);
			Link.l1 = DLG_TEXT_Q[12];
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple(DLG_TEXT_Q[13],
                                           DLG_TEXT_Q[14]);
			Link.l1 = DLG_TEXT_Q[15];
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
