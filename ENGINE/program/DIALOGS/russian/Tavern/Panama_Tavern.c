#include "TEXT\DIALOGS\Tavern\Panama_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[0]+ GetCityName(npchar.city) +DLG_TEXT_TV[1],
                          DLG_TEXT_TV[2], DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[5] + NPChar.name + DLG_TEXT_TV[6], DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = DLG_TEXT_TV[10];
                link.l1.go = "Step_S2_1";
            }
            // <== проверка на квесты
		break;
//***************************  вест є2 испанки, задание »нквизиции ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[11], DLG_TEXT_TV[12], DLG_TEXT_TV[13], DLG_TEXT_TV[14], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[15], DLG_TEXT_TV[16], DLG_TEXT_TV[17], DLG_TEXT_TV[18] + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

