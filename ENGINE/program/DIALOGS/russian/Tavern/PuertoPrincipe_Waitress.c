#include "TEXT\DIALOGS\Tavern\PuertoPrincipe_Waitress.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[0] + GetAddress_Form(NPChar) + "?", DLG_TEXT_TV[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_TV[2] + GetAddress_Form(NPChar) + DLG_TEXT_TV[3], DLG_TEXT_TV[4],
                          DLG_TEXT_TV[5] + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_TV[6], DLG_TEXT_TV[7]), DLG_TEXT_TV[8],
                      DLG_TEXT_TV[9], DLG_TEXT_TV[10], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = DLG_TEXT_TV[11];
				link.l1.go = "PL_Q7_1";
			}
			if (pchar.questTemp.piratesLine == "Soukins_seekRings" && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
			{
				link.l1 = DLG_TEXT_TV[12];
				link.l1.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_1":
			dialog.text = DLG_TEXT_TV[13];
			link.l1 = DLG_TEXT_TV[14];
			link.l1.go = "PL_Q7_2";
			pchar.questTemp.piratesLine = "Soukins_seekRings";
			if (CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
            {
				link.l2 = DLG_TEXT_TV[15];
				link.l2.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_2":
			dialog.text = DLG_TEXT_TV[16];
			link.l1 = DLG_TEXT_TV[17];
			link.l1.go = "exit";
		break;
		case "PL_Q7_3":
			dialog.text = DLG_TEXT_TV[18];
			link.l1 = DLG_TEXT_TV[19];
			link.l1.go = "PL_Q7_4";
			TakeItemFromCharacter(pchar, "jewelry7");
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		case "PL_Q7_4":
			dialog.text = DLG_TEXT_TV[20];
			link.l1 = DLG_TEXT_TV[21];
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = DLG_TEXT_TV[22];
			link.l1 = DLG_TEXT_TV[23];
			link.l1.go = "PL_Q7_6";
		break;
		case "PL_Q7_6":
			dialog.text = DLG_TEXT_TV[24];
			link.l1 = DLG_TEXT_TV[25];
			link.l1.go = "PL_Q7_7";
		break;
		case "PL_Q7_7":
			dialog.text = DLG_TEXT_TV[26];
			link.l1 = DLG_TEXT_TV[27];
			link.l1.go = "PL_Q7_8";
		break;
		case "PL_Q7_8":
			dialog.text = DLG_TEXT_TV[28];
			link.l1 = DLG_TEXT_TV[29];
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toWindow";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

