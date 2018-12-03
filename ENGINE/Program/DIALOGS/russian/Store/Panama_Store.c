#include "TEXT\DIALOGS\Store\Panama_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = DLG_TEXT_STR[9];
                link.l1.go = "Step_S2_1";
            }
            // <== проверка на квесты

		break;
//***************************  вест є2 испанки, задание »нквизиции ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[10],
                                                  DLG_TEXT_STR[11], DLG_TEXT_STR[12], DLG_TEXT_STR[13], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[14], DLG_TEXT_STR[15], DLG_TEXT_STR[16], DLG_TEXT_STR[17] + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = DLG_TEXT_STR[18];
			link.l1 = DLG_TEXT_STR[19];
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "11");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

