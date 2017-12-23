#include "TEXT\DIALOGS\Tavern\PuertoPrincipe_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0], DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[5], DLG_TEXT_TV[6]), DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = DLG_TEXT_TV[10];
				link.l1.go = "PL_Q7_1";
			}
		break;
		//пиратка, квест №7, попытка узнать о планах Соукинса
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[11], 
				DLG_TEXT_TV[12], 
				DLG_TEXT_TV[13],
                DLG_TEXT_TV[14], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[15], 
				DLG_TEXT_TV[16],
                DLG_TEXT_TV[17], 
				DLG_TEXT_TV[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = DLG_TEXT_TV[19];
			link.l1 = DLG_TEXT_TV[20];
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = DLG_TEXT_TV[21];
			link.l1 = DLG_TEXT_TV[22];
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

