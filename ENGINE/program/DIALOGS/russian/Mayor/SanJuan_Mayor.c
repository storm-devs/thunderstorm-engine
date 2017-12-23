#include "TEXT\DIALOGS\Mayor\SanJuan_Mayor.h"
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
			if (CheckAttribute(pchar, "RomanticQuest.MayorOk"))
			{
				link.l1 = DLG_TEXT_MR[10] + GetFullName(pchar) + DLG_TEXT_MR[11];
				link.l1.go = "Romantic_1";
			}
		break;
		case "Romantic_1":
			dialog.text = DLG_TEXT_MR[12]+
				          DLG_TEXT_MR[13];
			link.l1 = DLG_TEXT_MR[14] + npchar.lastname + DLG_TEXT_MR[15];
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
			dialog.text = DLG_TEXT_MR[16];
			link.l1 = DLG_TEXT_MR[17];
			link.l1.go = "Romantic_3";
		break;
		case "Romantic_3":
			dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "Romantic_4";
		break;
		case "Romantic_4":
			dialog.text = DLG_TEXT_MR[20];
			link.l1 = DLG_TEXT_MR[21];
			link.l1.go = "Romantic_5";
		break;
		case "Romantic_5":
			dialog.text = DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Romantic_6";
		break;
		case "Romantic_6":
			dialog.text = DLG_TEXT_MR[24];
			link.l1 = DLG_TEXT_MR[25];
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "27");
			DeleteAttribute(pchar, "RomanticQuest.MayorOk");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //и только теперь открываем дверь в дом Изабеллы
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

