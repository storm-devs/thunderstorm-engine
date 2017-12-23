#include "TEXT\DIALOGS\Tavern\Maracaibo_Tavern.h"
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
			if (pchar.questTemp.MC == "toMaracaibo")
			{
				link.l1 = DLG_TEXT_TV[10];
				link.l1.go = "MCTavernMar";
			}
		break;
		//зачарованный город
		case "MCTavernMar":
			dialog.text = DLG_TEXT_TV[11];
			link.l1 = DLG_TEXT_TV[12];
			link.l1.go = "MCTavernMar_1";
		break;
		case "MCTavernMar_1":
			dialog.text = DLG_TEXT_TV[13];
			link.l1 = DLG_TEXT_TV[14];
			link.l1.go = "MCTavernMar_2";
		break;
		case "MCTavernMar_2":
			dialog.text = DLG_TEXT_TV[15];
			link.l1 = DLG_TEXT_TV[16];
			link.l1.go = "exit";
			pchar.questTemp.MC = "toDesMoines";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

