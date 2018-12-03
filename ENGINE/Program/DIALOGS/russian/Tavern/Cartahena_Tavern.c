#include "TEXT\DIALOGS\Tavern\Cartahena_Tavern.h"
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
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

