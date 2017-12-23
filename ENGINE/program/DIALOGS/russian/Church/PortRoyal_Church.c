#include "TEXT\DIALOGS\Church\PortRoyal_Church.h"
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
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo" || pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoFather")
            {
                link.l1 = DLG_TEXT_CHR[10];
                link.l1.go = "Step_E6_1";
            }
		break;

        case "Step_E6_1":
			dialog.text = DLG_TEXT_CHR[11];
			link.l1 = DLG_TEXT_CHR[12];
			link.l1.go = "Step_E6_2";
		break;

        case "Step_E6_2":
			dialog.text = DLG_TEXT_CHR[13]+
                          DLG_TEXT_CHR[14]+
                          DLG_TEXT_CHR[15]+
                          DLG_TEXT_CHR[16];
			link.l1 = DLG_TEXT_CHR[17];
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoWomen";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "19");
            ref sld = GetCharacter(NPC_GenerateCharacter("Gillian Atterbury", "girl_8", "woman", "towngirl", 5, ENGLAND, 100, false));
        	sld.name 	= DLG_TEXT_CHR[18];
        	sld.lastname = DLG_TEXT_CHR[19];
        	LAi_SetCitizenType(sld);
            sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
            LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
           	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
			LAi_SetFanatic(sld, "PortRoyal_church", "sit", "sit1", 11.0, 14.0);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

