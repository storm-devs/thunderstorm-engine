#include "TEXT\DIALOGS\Quest\Tenochtitlan\AztecCitizens.h"
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//------------------------ Мешитли ------------------------
		case "AztecFT":
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1] + GetFullName(pchar) + DLG_TEXT[2];
			link.l1.go = "AztecFT_1";
		break;
		case "AztecFT_1":
			dialog.text = DLG_TEXT[3];
			link.l1 = DLG_TEXT[4];
			link.l1.go = "AztecFT_2";
		break;
		case "AztecFT_2":
			dialog.text = DLG_TEXT[5];
			link.l1 = DLG_TEXT[6];
			link.l1.go = "AztecFT_3";
		break;
		case "AztecFT_3":
			dialog.text = DLG_TEXT[7];
			link.l1 = DLG_TEXT[8];
			link.l1.go = "AztecFT_4";
		break;
		case "AztecFT_4":
			dialog.text = DLG_TEXT[9];
			link.l1 = DLG_TEXT[10];
			link.l1.go = "AztecFT_5";
		break;
		case "AztecFT_5":
			dialog.text = DLG_TEXT[11];
			link.l1 = DLG_TEXT[12];
			link.l1.go = "AztecFT_6";
		break;
		case "AztecFT_6":
			dialog.text = DLG_TEXT[13];
			link.l1 = DLG_TEXT[14];
			link.l1.go = "AztecFT_7";
		break;
		case "AztecFT_7":
			dialog.text = DLG_TEXT[15];
			link.l1 = DLG_TEXT[16];
			link.l1.go = "AztecFT_8";
		break;
		case "AztecFT_8":
			dialog.text = DLG_TEXT[17];
			link.l1 = DLG_TEXT[18];
			link.l1.go = "AztecFT_9";
		break;
		case "AztecFT_9":
			dialog.text = DLG_TEXT[19];
			link.l1 = DLG_TEXT[20];
			link.l1.go = "AztecFT_10";
		break;
		case "AztecFT_10":
			dialog.text = DLG_TEXT[21];
			link.l1 = DLG_TEXT[22];
			link.l1.go = "AztecFT_11";
		break;
		case "AztecFT_11":
			LAi_SetImmortal(sld, false);
			LAi_SetCitizenType(npchar);
			NextDiag.TempNode = "Aztec1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Aztec1":
			dialog.text = DLG_TEXT[23] + GetFullName(pchar) + ".";
			link.l1 = DLG_TEXT[24];
			link.l1.go = "exit";
		break;

		case "Aztec1AF":
			dialog.text = DLG_TEXT[25];
			link.l1 = DLG_TEXT[26];
			link.l1.go = "Aztec1AF_1";
		break;
		case "Aztec1AF_1":
			dialog.text = DLG_TEXT[27];
			link.l1 = DLG_TEXT[28];
			link.l1.go = "Aztec1AF_2";
		break;
		case "Aztec1AF_2":
			dialog.text = DLG_TEXT[29];
			link.l1 = DLG_TEXT[30];
			link.l1.go = "Aztec1AF_3";
		break;
		case "Aztec1AF_3":
			dialog.text = DLG_TEXT[31];
			link.l1 = DLG_TEXT[32];
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec1";
		break;


		//------------------------ Ауисотль ------------------------
		case "AztecFT2":
			dialog.text = DLG_TEXT[33];
			link.l1 = DLG_TEXT[34];
			link.l1.go = "AztecFT2_1";
		break;
		
		case "AztecFT2_1":
			dialog.text = DLG_TEXT[35];
			link.l1 = DLG_TEXT[36] + GetFullName(pchar) + DLG_TEXT[37];
			link.l1.go = "AztecFT2_2";
		break;
		case "AztecFT2_2":
			dialog.text = DLG_TEXT[38];
			link.l1 = DLG_TEXT[39];
			link.l1.go = "AztecFT2_3";
		break;
		case "AztecFT2_3":
			dialog.text = DLG_TEXT[40];
			link.l1 = DLG_TEXT[41];
			link.l1.go = "AztecFT2_4";
		break;
		case "AztecFT2_4":
			dialog.text = DLG_TEXT[42];
			link.l1 = DLG_TEXT[43];
			link.l1.go = "AztecFT2_5";
		break;
		case "AztecFT2_5":
			dialog.text = DLG_TEXT[44];
			link.l1 = DLG_TEXT[45];
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2";
		break;

		case "Aztec2":
			dialog.text = DLG_TEXT[46];
			link.l1 = DLG_TEXT[47];
			link.l1.go = "exit";
		break;

		case "Aztec2AF":
			dialog.text = DLG_TEXT[48];
			link.l1 = DLG_TEXT[49];
			link.l1.go = "Aztec2AF_1";
		break;
		case "Aztec2AF_1":
			dialog.text = DLG_TEXT[50];
			link.l1 = DLG_TEXT[51];
			link.l1.go = "Aztec2AF_2";
		break;
		case "Aztec2AF_2":
			dialog.text = DLG_TEXT[52];
			link.l1 = DLG_TEXT[53];
			link.l1.go = "Aztec2AF_3";
		break;
		case "Aztec2AF_3":
			dialog.text = DLG_TEXT[54];
			link.l1 = DLG_TEXT[55];
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2AF_4";
		break;

		case "Aztec2AF_4":
			dialog.text = DLG_TEXT[56];
			link.l1 = DLG_TEXT[57];
			link.l1.go = "exit";
		break;
	}
}
