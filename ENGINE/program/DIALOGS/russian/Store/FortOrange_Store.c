#include "TEXT\DIALOGS\Store\FortOrange_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[0], DLG_TEXT_STR[1]), DLG_TEXT_STR[2], DLG_TEXT_STR[3],
                          DLG_TEXT_STR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_STR[5], DLG_TEXT_STR[6]), DLG_TEXT_STR[7],
                      DLG_TEXT_STR[8], DLG_TEXT_STR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeStore": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
                    link.l2 = DLG_TEXT_STR[10];
                    link.l2.go = "Step_H2_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[11],
                         DLG_TEXT_STR[12],
                         DLG_TEXT_STR[13],
                         DLG_TEXT_STR[14], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[15], DLG_TEXT_STR[16],
                      DLG_TEXT_STR[17], DLG_TEXT_STR[18] , npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
         case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = DLG_TEXT_STR[19];
            link.l2 = DLG_TEXT_STR[20];
            link.l2.go = "Step_H4_1";
        break;

        case "Step_H4_1":
			dialog.text = DLG_TEXT_STR[21];
			link.l1 = DLG_TEXT_STR[22];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);
}

