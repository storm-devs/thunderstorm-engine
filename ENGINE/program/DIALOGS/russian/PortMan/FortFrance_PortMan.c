#include "TEXT\DIALOGS\PortMan\FortFrance_PortMan.h"
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
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = DLG_TEXT_PRT[10];
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_noMoney")
			{
				link.l1 = DLG_TEXT_PRT[11];
				link.l1.go = "PL_Q3_7";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_PRT[12], 
				DLG_TEXT_PRT[13], 
				DLG_TEXT_PRT[14],
                DLG_TEXT_PRT[15], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_PRT[16], 
				DLG_TEXT_PRT[17],
                DLG_TEXT_PRT[18], 
				DLG_TEXT_PRT[19], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = DLG_TEXT_PRT[20];
			link.l1 = DLG_TEXT_PRT[21];
			link.l1.go = "PL_Q3_out";
			link.l2 = DLG_TEXT_PRT[22];
			link.l2.go = "PL_Q3_3";
		break;

		case "PL_Q3_out":
			dialog.text = DLG_TEXT_PRT[23];
			link.l1 = DLG_TEXT_PRT[24];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "6");
			pchar.questTemp.piratesLine = "KillLoy_notFound";
			QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
		break;
		case "PL_Q3_3":
			if (GetCharacterSkill(pchar, "Sneak") >= 60 || GetCharacterSPECIAL(pchar, "Charisma") > 6)
			{
				dialog.text = DLG_TEXT_PRT[25];
				link.l1 = DLG_TEXT_PRT[26];
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "7");
				pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			}
			else
			{
				dialog.text = DLG_TEXT_PRT[27];
				link.l1 = DLG_TEXT_PRT[28];
				link.l1.go = "PL_Q3_4";
			}
		break;
		case "PL_Q3_4":
			dialog.text = DLG_TEXT_PRT[29];
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = DLG_TEXT_PRT[30];
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				link.l1 = DLG_TEXT_PRT[31];
				link.l1.go = "PL_Q3_6";
			}
		break;
		case "PL_Q3_5":
			dialog.text = DLG_TEXT_PRT[32];
			link.l1 = DLG_TEXT_PRT[33];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "7");
			pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			AddMoneyToCharacter(pchar, -15000);
		break;
		case "PL_Q3_6":
			dialog.text = DLG_TEXT_PRT[34];
			link.l1 = DLG_TEXT_PRT[35];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "8");
			pchar.questTemp.piratesLine = "KillLoy_noMoney";
		break;
		case "PL_Q3_7":
			if (sti(pchar.money) >= 15000)
			{
				dialog.text = DLG_TEXT_PRT[36];
				link.l1 = DLG_TEXT_PRT[37];
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				dialog.text = DLG_TEXT_PRT[38];
				link.l1 = DLG_TEXT_PRT[39];
				link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

