#include "TEXT\DIALOGS\Church\LeFransua_Church.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple(DLG_TEXT_CHR[0], DLG_TEXT_CHR[1]);
			link.l1 = RandPhraseSimple(DLG_TEXT_CHR[2], DLG_TEXT_CHR[3]);
		    link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

