#include "TEXT\DIALOGS\Mayor\Maracaibo_Mayor.h"
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
			//==> Проверка на стейт квестов
			if (pchar.questTemp.State == "Sp10Maracaibo_toMaracaibo")
			{
				dialog.text = DLG_TEXT_MR[10];
				link.l1 = DLG_TEXT_MR[11];
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toGovernor")
			{
				dialog.text = DLG_TEXT_MR[12];
				link.l1 = DLG_TEXT_MR[13];
				link.l1.go = "Step_S10_4";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toBattle")
			{
				dialog.text = DLG_TEXT_MR[14];
				link.l1 = DLG_TEXT_MR[15];
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_GoodWork")
			{
				dialog.text = DLG_TEXT_MR[16];
				link.l1 = DLG_TEXT_MR[17];
				link.l1.go = "Step_S10_5";
			}
			//<== Проверка на стейт квестов
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[18], DLG_TEXT_MR[19]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[20], DLG_TEXT_MR[21]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //==> Двенадцатый квест голл. линейки. Захват Маракайбо.
        case "HolLine12Quest_Occupy":
			dialog.text = DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Step_H12_1";
			AfterTownBattle();
        break;
        case "Step_H12_1":
			dialog.text = DLG_TEXT_MR[24];
			link.l1 = DLG_TEXT_MR[25];
			link.l1.go = "Step_H12_2";
        break;
        case "Step_H12_2":
			dialog.text = DLG_TEXT_MR[26];
			link.l1 = DLG_TEXT_MR[27];
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "2");
            pchar.questTemp.State = "OccupyMaracaibo_toWeWon";
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
        //==> Десятый квест испанки. Защита Маракайбо.
        case "Step_S10_1":
			dialog.text = DLG_TEXT_MR[28];
			link.l1 = DLG_TEXT_MR[29];
			link.l1.go = "Step_S10_2";
        break;
        case "Step_S10_2":
			dialog.text = DLG_TEXT_MR[30];
			link.l1 = DLG_TEXT_MR[31];
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = DLG_TEXT_MR[32];
			link.l1 = DLG_TEXT_MR[33];
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_TalkWithOfficer";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1.location = "Maracaibo_town";
            Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition = "Sp10Maracaibo_TalkWithOfficer";
		break;
        case "Step_S10_4":
			dialog.text = DLG_TEXT_MR[34];
			link.l1 = DLG_TEXT_MR[35];
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			pchar.questTemp.State = "Sp10Maracaibo_toBattle";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1 = "location";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1.location = "Maracaibo";
            Pchar.quest.Sp10Maracaibo_Battle.win_condition = "Sp10Maracaibo_Battle";
        break;
        case "Step_S10_5":
			dialog.text = DLG_TEXT_MR[36];
			link.l1 = DLG_TEXT_MR[37];
			link.l1.go = "Step_S10_6";
        break;
        case "Step_S10_6":
			dialog.text = DLG_TEXT_MR[38];
			link.l1 = DLG_TEXT_MR[39];
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_2GoodWork";
			AddMoneyToCharacter(pchar, 70000);
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

