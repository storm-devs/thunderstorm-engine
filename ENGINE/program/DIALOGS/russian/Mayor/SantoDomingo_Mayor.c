#include "TEXT\DIALOGS\Mayor\SantoDomingo_Mayor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[10], DLG_TEXT_MR[11]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[12], DLG_TEXT_MR[13]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //********************** Фр.линейка. Квест №10. Захват Санто-Доминго ************************
		case "FraLine10Quest_OccupySD":
            dialog.text = DLG_TEXT_MR[14];
			link.l1 = DLG_TEXT_MR[15] + GetFullName(pchar) + DLG_TEXT_MR[16];
            link.l1.go = "Step_F10_1";
			AfterTownBattle();
        break;

		case "Step_F10_1":
            dialog.text = DLG_TEXT_MR[17];
			link.l1 = DLG_TEXT_MR[18];
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr10OccupySD_toWeWon";
            AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "2");
            NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            UpdateRelations();
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка 
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

