#include "TEXT\DIALOGS\error_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			
			dialog.text = DLG_TEXT_BASE[0];
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = DLG_TEXT_BASE[1] + CharacterRef.Dialog.Filename + DLG_TEXT_BASE[2];
			}
			link.l1 = "ok";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
