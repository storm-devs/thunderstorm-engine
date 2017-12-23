#include "TEXT\DIALOGS\Shipyard\Tortuga_Shipyard.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[0], DLG_TEXT_SHY[1]), DLG_TEXT_SHY[2], DLG_TEXT_SHY[3],
                          DLG_TEXT_SHY[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_SHY[5], DLG_TEXT_SHY[6]), DLG_TEXT_SHY[7],
                      DLG_TEXT_SHY[8], DLG_TEXT_SHY[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l2 = DLG_TEXT_SHY[10];
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== Проверяем поле состояния квестов.
		break;
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_SHY[11], DLG_TEXT_SHY[12], DLG_TEXT_SHY[13], DLG_TEXT_SHY[14], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_SHY[15], DLG_TEXT_SHY[16], DLG_TEXT_SHY[17], DLG_TEXT_SHY[18], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = DLG_TEXT_SHY[19];
			link.l1 = DLG_TEXT_SHY[20];
			link.l1.go = "exit";
            pchar.questTemp.Talks.Shipyard = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "9");
        break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

