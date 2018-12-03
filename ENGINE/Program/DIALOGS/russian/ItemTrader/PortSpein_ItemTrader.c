#include "TEXT\DIALOGS\ItemTrader\PortSpein_ItemTrader.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_ITR[0], DLG_TEXT_ITR[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_ITR[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_ITR[3] + GetAddress_Form(NPChar) + "?",
                          DLG_TEXT_ITR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_ITR[5], DLG_TEXT_ITR[6]), DLG_TEXT_ITR[7],
                      DLG_TEXT_ITR[8], DLG_TEXT_ITR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

