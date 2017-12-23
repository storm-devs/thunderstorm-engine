#include "TEXT\DIALOGS\Citizen\Cumana_Citizen.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CZ[0], DLG_TEXT_CZ[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CZ[2], DLG_TEXT_CZ[3]);
		    link.l1.go = "exit";
			// Квест Изабеллы, розыск кэпа брига DLG_TEXT_CZ[4]
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
                dialog.Text = DLG_TEXT_CZ[5];
    			link.l1 = DLG_TEXT_CZ[6];
    			Link.l1.go = "RomanticQuest_1";
			}			
		break;
		// ==> Квест Изабеллы, розыск кэпа брига DLG_TEXT_CZ[7]
		case "RomanticQuest_1":
			dialog.Text = DLG_TEXT_CZ[8];
			link.l1 = DLG_TEXT_CZ[9];
			Link.l1.go = "RomanticQuest_2";
		break;		
		case "RomanticQuest_2":
			dialog.Text = DLG_TEXT_CZ[10];
			link.l1 = DLG_TEXT_CZ[11];
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumana");
			Pchar.RomanticQuest.ShipToCumanaTavenrn = true;			
			ref rChar = GetCharacter(NPC_GenerateCharacter("BrigCaptain", "shipowner_13", "man", "man", 20, SPAIN, -1, false));
            rChar.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
            FreeSitLocator("Cumana_tavern", "sit3");  // очистим стул
			ChangeCharacterAddressGroup(rChar, "Cumana_tavern", "sit", "sit3");
            LAi_SetSitType(rChar);
		break;
		// <== Квест Изабеллы, розыск кэпа брига DLG_TEXT_CZ[12]
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = DLG_TEXT_CZ[13]+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = DLG_TEXT_CZ[14];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[15];
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = DLG_TEXT_CZ[16];

            link.l1 = DLG_TEXT_CZ[17];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_CZ[18];
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
