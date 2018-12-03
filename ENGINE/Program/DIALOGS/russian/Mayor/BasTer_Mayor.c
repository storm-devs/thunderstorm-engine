#include "TEXT\DIALOGS\Mayor\BasTer_Mayor.h"
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
			if (pchar.questTemp.State == "Fr4SoleiRoyal_GoodWork")
			{
				dialog.text = DLG_TEXT_MR[10];
				link.l1 = DLG_TEXT_MR[11];
				link.l1.go = "Step_F4_1";		
			}
		break;
		//************************** Фр.линкейка, квест №4. Солей Руаяль ************************
		case "Step_F4_1":
            dialog.text = DLG_TEXT_MR[12];
			link.l1 = DLG_TEXT_MR[13];
            link.l1.go = "Step_F4_2";
        break;
		case "Step_F4_2":
            dialog.text = DLG_TEXT_MR[14];
			link.l1 = DLG_TEXT_MR[15];
            link.l1.go = "Step_F4_3";
        break;
		case "Step_F4_3":
			if (CheckCompanionInCharacter(pchar, "SoleiRoyalCaptain"))
			{
				dialog.text = DLG_TEXT_MR[16];
				link.l1 = DLG_TEXT_MR[17];
				link.l1.go = "exit";
				RemoveCharacterCompanion(pchar, characterFromId("SoleiRoyalCaptain"));
				pchar.questTemp.State = "Fr4SoleiRoyal_backTortuga";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "6");
			}
			else
			{
				dialog.text = DLG_TEXT_MR[18];
				link.l1 = DLG_TEXT_MR[19];
				link.l1.go = "exit";
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "7");
			}
        break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[20], DLG_TEXT_MR[21]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[22], DLG_TEXT_MR[23]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//Квест Аскольда, штурм в обличие мумии
        case "Ascold_MummyAttack":         
			dialog.text = DLG_TEXT_MR[24];
			Link.l1 = DLG_TEXT_MR[25];
			Link.l1.go = "Step_Asc1";
			AfterTownBattle();
        break;
        case "Step_Asc1":
            dialog.text = DLG_TEXT_MR[26];
			Link.l1 = DLG_TEXT_MR[27];
			Link.l1.go = "Step_Asc2";
        break;
        case "Step_Asc2":
            dialog.text = DLG_TEXT_MR[28];
			Link.l1 = DLG_TEXT_MR[29];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
			Locations[FindLocation(pchar.location)].box1.items.sculMa1 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa2 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa3 = 1;
            Locations[FindLocation(pchar.location)].box1.items.indian22 = 1;
            pchar.questTemp.Ascold = "Ascold_MummyFoundItems"; 
			chrDisableReloadToLocation = false;
			SetReturn_Gover_Dialog_Exit(NPChar);
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

