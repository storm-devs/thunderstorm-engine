#include "TEXT\DIALOGS\Quest\Mictlantecuhtli.h"
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
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//должок ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = DLG_TEXT_Q[2];
			link.l1 = DLG_TEXT_Q[3];
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = DLG_TEXT_Q[4] + FindRussianMoneyString(sti(pchar.questTemp.LSC_climeUsurer.qtyMoney )) + DLG_TEXT_Q[5];
			if (sti(pchar.money) >= sti(pchar.questTemp.LSC_climeUsurer.qtyMoney))
			{
				link.l1 = DLG_TEXT_Q[6];
				link.l1.go = "ClimeUsurer_yes";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[7];
				link.l1.go = "ClimeUsurer_no";
			}
		break;
		case "ClimeUsurer_yes":
			dialog.text = DLG_TEXT_Q[8];
			link.l1 = DLG_TEXT_Q[9];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LSC_climeUsurer.qtyMoney));
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;
		case "ClimeUsurer_no":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_noMoney");
		break;

		//в большом храме разговор перед боевкой
		case "InGreateTemple":
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "InGreateTemple_1";
		break;
		case "InGreateTemple_1":
			dialog.text = DLG_TEXT_Q[14];
			link.l1 = DLG_TEXT_Q[15];
			link.l1.go = "InGreateTemple_2";
		break;
		case "InGreateTemple_2":
			dialog.text = DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "InGreateTemple_3";
		break;
		case "InGreateTemple_3":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_fightInTemple");
		break;

		//в большом храме разговор после боевки
		case "WinInTemple":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "WinInTemple_1";
		break;
		case "WinInTemple_1":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "WinInTemple_2";
		break;
		case "WinInTemple_2":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "WinInTemple_3";
		break;
		case "WinInTemple_3":
			dialog.text = DLG_TEXT_Q[26]+
				DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "WinInTemple_4";
		break;
		case "WinInTemple_4":
			dialog.text = DLG_TEXT_Q[29]+
				DLG_TEXT_Q[30]+
				DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "WinInTemple_5";
		break;
		case "WinInTemple_5":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "WinInTemple_6";
		break;
		case "WinInTemple_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			AddQuestRecord("Tenochtitlan", "4");
			DialogExit();
		break;
	}
}
