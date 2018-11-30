#include "TEXT\DIALOGS\Tavern\SantaCatalina_Waitress.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0] + GetAddress_Form(NPChar) + "?", DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + DLG_TEXT_TV[3], DLG_TEXT_TV[4],
                          DLG_TEXT_TV[5] + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[6], DLG_TEXT_TV[7]), DLG_TEXT_TV[8],
                      DLG_TEXT_TV[9], DLG_TEXT_TV[10], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

