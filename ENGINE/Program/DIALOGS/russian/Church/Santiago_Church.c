#include "TEXT\DIALOGS\Church\Santiago_Church.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[0], DLG_TEXT_CHR[1]), DLG_TEXT_CHR[2], DLG_TEXT_CHR[3],
                          DLG_TEXT_CHR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_CHR[5], DLG_TEXT_CHR[6]), DLG_TEXT_CHR[7],
                      DLG_TEXT_CHR[8], DLG_TEXT_CHR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Inquisition_toDeSouza")
            {
                link.l1 = DLG_TEXT_CHR[10];
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
            {
                link.l1 = DLG_TEXT_CHR[11];
                link.l1.go = "Step_F7_1";
            }
		break;
        case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_CHR[12], DLG_TEXT_CHR[13], DLG_TEXT_CHR[14], DLG_TEXT_CHR[15],  "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_CHR[16], DLG_TEXT_CHR[17], DLG_TEXT_CHR[18], DLG_TEXT_CHR[19], npchar, Dialog.CurrentNode);
			link.l1.go = "Step_S2_2";
		break;
        case "Step_S2_2":
			dialog.text = DLG_TEXT_CHR[20];
			link.l1 = DLG_TEXT_CHR[21];
			link.l1.go = "Step_S2_3";
		break;
        case "Step_S2_3":
			dialog.text = DLG_TEXT_CHR[22];
			link.l1 = DLG_TEXT_CHR[23];
			link.l1.go = "Step_S2_4";
		break;
        case "Step_S2_4":
			dialog.text = DLG_TEXT_CHR[24];
			link.l1 = DLG_TEXT_CHR[25];
			link.l1.go = "exit";
		break;

        case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_CHR[26], DLG_TEXT_CHR[27], DLG_TEXT_CHR[28],
                          DLG_TEXT_CHR[29], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_CHR[30], DLG_TEXT_CHR[31],
                      DLG_TEXT_CHR[32], DLG_TEXT_CHR[33], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

