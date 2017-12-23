#include "TEXT\DIALOGS\Prison\SentJons_Prison.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = DLG_TEXT_PRS[0];
			link.l1 = DLG_TEXT_PRS[1];
			link.l1.go = "Exit";
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "WormEnglPlans_SaveOfficer")   // разговор по квест №3 голландской линейке.
            {
    			link.l2 = DLG_TEXT_PRS[2];
    			link.l2.go = "Step_H3_1";
            }
             // <== Проверяем поле состояния квестов.
		break;

        case "Step_H3_1":
            dialog.text = DLG_TEXT_PRS[3];
			link.l1 = DLG_TEXT_PRS[4];
			link.l1.go = "fight";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

