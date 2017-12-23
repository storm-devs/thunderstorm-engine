#include "TEXT\DIALOGS\Fort\Cartahena_Fort.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_FT[0], DLG_TEXT_FT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_FT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_FT[3],
                          DLG_TEXT_FT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_FT[5], DLG_TEXT_FT[6]), DLG_TEXT_FT[7],
                      DLG_TEXT_FT[8], DLG_TEXT_FT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

