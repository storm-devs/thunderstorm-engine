#include "TEXT\DIALOGS\PortMan\Villemstad_PortMan.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №5 голл.линейки, забрать три флейта.
            if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
            {
    			link.l1 = DLG_TEXT_PRT[10];
    			link.l1.go = "Step_H5_1";
            }
		break;

//************************************* Диалоги по голл.линейке *******************************
		case "Step_H5_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = DLG_TEXT_PRT[11];
    			link.l1 = DLG_TEXT_PRT[12];
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
            }
            else
            {
                dialog.text = DLG_TEXT_PRT[13];
    			link.l1 = DLG_TEXT_PRT[14];
    			link.l1.go = "exit";
            }
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

