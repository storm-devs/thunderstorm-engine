#include "TEXT\DIALOGS\Church\SanJuan_Church.h"
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
			//============= Изабелла Росселини ================
            if (CheckAttribute(Pchar, "RomanticQuest.PriestAsk"))
			{
				link.l2 = DLG_TEXT_CHR[10];
				link.l2.go = "Romantic_1";
			}
		break;

        case "Romantic_1":
			dialog.text = DLG_TEXT_CHR[11];
			link.l1 = DLG_TEXT_CHR[12];
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "RomanticQuest.PriestAsk");
		break;

        case "Romantic_2":
			dialog.text = GetFullName(pchar) + DLG_TEXT_CHR[13];
			link.l1 = DLG_TEXT_CHR[14];
			link.l1.go = "Romantic_3";
		break;
        case "Romantic_3":	
			locCameraToPos(3.64, 3.25, -7.84, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = DLG_TEXT_CHR[15] + GetMainCharacterNameGen() + DLG_TEXT_CHR[16];
			link.l1 = DLG_TEXT_CHR[17];
			link.l1.go = "Romantic_4";
		break;
        case "Romantic_4":	
			locCameraToPos(-0.75, 3.85, -10.60, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = DLG_TEXT_CHR[18];
			link.l1 = "...";
			link.l1.go = "Romantic_5";
		break;
        case "Romantic_5":		
			dialog.text = DLG_TEXT_CHR[19];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("Romantic_Padre_3");			
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
