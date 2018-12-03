#include "TEXT\DIALOGS\Usurer\Charles_Usurer.h"
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
            // ==> Квест Аззи
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveMoney"))
            {
                link.l5 = DLG_TEXT_USR[10];
                link.l5.go = "Step_Az_1";
            }
			if (!CheckAttribute(pchar, "questTemp.Azzy.GiveMoney") && pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
                link.l5 = DLG_TEXT_USR[11];
                link.l5.go = "Step_Az_4";
            }
		break;
        // ==> Квест Аззи. Дача трех лимонов ГГ по поручению Аззи.
		case "Step_Az_1":
			dialog.text = DLG_TEXT_USR[12] + GetAddress_Form(NPChar) + DLG_TEXT_USR[13];
			Link.l1 = DLG_TEXT_USR[14];
			Link.l1.go = "Step_Az_2";
		break;
		case "Step_Az_2":
			dialog.text = DLG_TEXT_USR[15] + GetAddress_Form(NPChar) + DLG_TEXT_USR[16];
			Link.l1 = DLG_TEXT_USR[17];
			Link.l1.go = "Step_Az_3";
            DeleteAttribute(pchar, "questTemp.Azzy.GiveMoney");
            AddMoneyToCharacter(pchar, 3000000);
		break;
		case "Step_Az_3":
			dialog.text = DLG_TEXT_USR[18];
			Link.l1 = DLG_TEXT_USR[19];
			Link.l1.go = "exit";
		break;
		case "Step_Az_4":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_USR[20], DLG_TEXT_USR[21], DLG_TEXT_USR[22], DLG_TEXT_USR[23], "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_USR[24], DLG_TEXT_USR[25], DLG_TEXT_USR[26], DLG_TEXT_USR[27], npchar, Dialog.CurrentNode);
			Link.l1.go = DialogGoNodeRepeat("Step_Az_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_Az_5":
			dialog.text = DLG_TEXT_USR[28]+
                     DLG_TEXT_USR[29]+
                     DLG_TEXT_USR[30]+
                     DLG_TEXT_USR[31];
			Link.l1 = DLG_TEXT_USR[32];
			Link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

