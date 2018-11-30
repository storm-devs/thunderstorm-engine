#include "TEXT\DIALOGS\Usurer\PortRoyal_Usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedToUsurer")
            {
                link.l1 = DLG_TEXT_USR[10];
                link.l1.go = "Step_E6_1";
            }
			if (pchar.questTemp.State == "MorrisWillams_AfterFightGoRedmond")
            {
                link.l1 = DLG_TEXT_USR[11];
                link.l1.go = "Step_E6_5";
            }
		break;

		case "Step_E6_1":
			dialog.text = DLG_TEXT_USR[12];
			link.l1 = DLG_TEXT_USR[13];
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = DLG_TEXT_USR[14];
			link.l1 = DLG_TEXT_USR[15];
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = DLG_TEXT_USR[16];
			link.l1 = DLG_TEXT_USR[17];
			link.l1.go = "Step_E6_4";
		break;
		case "Step_E6_4":
			dialog.text = DLG_TEXT_USR[18];
			link.l1 = DLG_TEXT_USR[19];
			link.l1.go = "exit";
            pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfo";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "18");
		break;
		case "Step_E6_5":
			dialog.text = DLG_TEXT_USR[20];
			link.l1 = DLG_TEXT_USR[21];
			link.l1.go = "Step_E6_6";
		break;
		case "Step_E6_6":
			dialog.text = DLG_TEXT_USR[22];
			link.l1 = DLG_TEXT_USR[23];
			link.l1.go = "Step_E6_7";
		break;
		case "Step_E6_7":
			dialog.text = DLG_TEXT_USR[24];
			link.l1 = DLG_TEXT_USR[25];
			link.l1.go = "Step_E6_8";
		break;
		case "Step_E6_8":
			dialog.text = DLG_TEXT_USR[26]+
                     DLG_TEXT_USR[27]+
                     DLG_TEXT_USR[28];
			link.l1 = DLG_TEXT_USR[29];
			link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
            pchar.questTemp.Waiting_time = "5";
            //ChangeCharacterReputation(pchar, -2); // за попытку шантажа TO_DO eddy
            AddCharacterExpToSkill(pchar, "Accuracy", 80);
            AddCharacterExpToSkill(pchar, "Commerce", 50);
            AddCharacterExpToSkill(pchar, "Sneak ", 70);
            AddCharacterExpToSkill(pchar, "Fencing  ", 100);
            AddCharacterExpToSkill(pchar, "Defence  ", 50);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "22");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Morris_Willams")], "PortRoyal_tavern", "sit", "sit1");
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "Willams_NiceTalking";
            LAi_SetSitTypeNoGroup(characterFromID("Morris_Willams"));
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

