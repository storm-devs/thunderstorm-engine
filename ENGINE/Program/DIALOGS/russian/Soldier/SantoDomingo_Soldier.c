#include "TEXT\DIALOGS\Soldier\SantoDomingo_Soldier.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SLD[0], DLG_TEXT_SLD[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_SLD[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_SLD[3],
                          DLG_TEXT_SLD[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SLD[5], DLG_TEXT_SLD[6]), DLG_TEXT_SLD[7],
                      DLG_TEXT_SLD[8], DLG_TEXT_SLD[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

