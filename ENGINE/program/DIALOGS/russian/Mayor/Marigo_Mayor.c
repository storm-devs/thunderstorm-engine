#include "TEXT\DIALOGS\Mayor\Marigo_Mayor.h"
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

        //==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
        case "SpaLine11Quest_DestrHol":
			dialog.text = DLG_TEXT_MR[14];
			link.l1 = DLG_TEXT_MR[15];
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
        break;
        case "Step_S11_1":
			dialog.text = DLG_TEXT_MR[16];
			link.l1 = DLG_TEXT_MR[17];
			link.l1.go = "Step_S11_2";
        break;
        case "Step_S11_2":
			dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_11_DestrHolland", "3");
            pchar.questTemp.Q11_Marigo = 1;
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

