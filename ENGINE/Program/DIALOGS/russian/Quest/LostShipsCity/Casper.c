#include "TEXT\DIALOGS\Quest\LostShipsCity\Casper.h"
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
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fightQuest":
			pchar.questTemp.LSC.Armo.checkCasper = npchar.index; //для обработки в АИ
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый каспер на разводе Армо
		case "Casper_1":
			dialog.text = DLG_TEXT_LSC[0];
			link.l1 = DLG_TEXT_LSC[1];
			link.l1.go = "Casper_1_1";
			NextDiag.TempNode = "Casper_12";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_1_1":
			dialog.text = DLG_TEXT_LSC[2];
			link.l1 = DLG_TEXT_LSC[3];
			link.l1.go = "Casper_1_2";
			link.l2 = DLG_TEXT_LSC[4];
			link.l2.go = "exit";
		break;
		case "Casper_1_2":
			dialog.text = DLG_TEXT_LSC[5];
			link.l1 = DLG_TEXT_LSC[6];
			link.l1.go = "fightQuest";
		break;

		case "Casper_12":
			dialog.text = DLG_TEXT_LSC[7];
			link.l1 = DLG_TEXT_LSC[8];
			link.l1.go = "Casper_12_1";
			link.l2 = DLG_TEXT_LSC[9];
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_13";
		break;
		case "Casper_12_1":
			dialog.text = DLG_TEXT_LSC[10];
			link.l1 = DLG_TEXT_LSC[11];
			link.l1.go = "fightQuest";
		break;

		case "Casper_13":
			dialog.text = DLG_TEXT_LSC[12];
			link.l1 = DLG_TEXT_LSC[13];
			link.l1.go = "fightQuest";
		break;
		//второй каспер на разводе Армо
		case "Casper_3":
			dialog.text = DLG_TEXT_LSC[14];
			link.l1 = DLG_TEXT_LSC[15];
			link.l1.go = "Casper_3_1";
			NextDiag.TempNode = "Casper_32";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_3_1":
			dialog.text = DLG_TEXT_LSC[16];
			link.l1 = DLG_TEXT_LSC[17];
			link.l1.go = "Casper_3_2";
			link.l2 = DLG_TEXT_LSC[18];
			link.l2.go = "exit";
		break;
		case "Casper_3_2":
			dialog.text = DLG_TEXT_LSC[19];
			link.l1 = DLG_TEXT_LSC[20];
			link.l1.go = "fightQuest";
		break;

		case "Casper_32":
			dialog.text = DLG_TEXT_LSC[21];
			link.l1 = DLG_TEXT_LSC[22];
			link.l1.go = "Casper_32_1";
			link.l2 = DLG_TEXT_LSC[23];
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_33";
		break;
		case "Casper_32_1":
			dialog.text = DLG_TEXT_LSC[24];
			link.l1 = DLG_TEXT_LSC[25];
			link.l1.go = "fightQuest";
		break;

		case "Casper_33":
			dialog.text = DLG_TEXT_LSC[26];
			link.l1 = DLG_TEXT_LSC[27];
			link.l1.go = "fightQuest";
		break;
		//третий каспер на разводе Армо
		case "Casper_5":
			dialog.text = DLG_TEXT_LSC[28];
			link.l1 = DLG_TEXT_LSC[29];
			link.l1.go = "Casper_5_1";
			NextDiag.TempNode = "Casper_52";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_5_1":
			dialog.text = DLG_TEXT_LSC[30];
			link.l1 = DLG_TEXT_LSC[31];
			link.l1.go = "Casper_5_2";
			link.l2 = DLG_TEXT_LSC[32];
			link.l2.go = "exit";
		break;
		case "Casper_5_2":
			dialog.text = DLG_TEXT_LSC[33];
			link.l1 = DLG_TEXT_LSC[34];
			link.l1.go = "fightQuest";
		break;

		case "Casper_52":
			dialog.text = DLG_TEXT_LSC[35];
			link.l1 = DLG_TEXT_LSC[36];
			link.l1.go = "Casper_52_1";
			link.l2 = DLG_TEXT_LSC[37];
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_53";
		break;
		case "Casper_52_1":
			dialog.text = DLG_TEXT_LSC[38];
			link.l1 = DLG_TEXT_LSC[39];
			link.l1.go = "fightQuest";
		break;

		case "Casper_53":
			dialog.text = DLG_TEXT_LSC[40];
			link.l1 = DLG_TEXT_LSC[41];
			link.l1.go = "fightQuest";
		break;
		//ГГ застукали за первым
		case "FackYou":
			dialog.text = DLG_TEXT_LSC[42];
			link.l1 = DLG_TEXT_LSC[43];
			link.l1.go = "FackYou_1";
		break;
		case "FackYou_1":
			dialog.text = DLG_TEXT_LSC[44];
			link.l1 = DLG_TEXT_LSC[45];
			link.l1.go = "FackYou_2";
		break;
		case "FackYou_2":
			dialog.text = DLG_TEXT_LSC[46];
			link.l1 = DLG_TEXT_LSC[47];
			link.l1.go = "FackYou_3";
		break;
		case "FackYou_3":
			dialog.text = DLG_TEXT_LSC[48];
			link.l1 = DLG_TEXT_LSC[49];
			link.l1.go = "FackYou_4";
		break;
		case "FackYou_4":
			dialog.text = DLG_TEXT_LSC[50];
			link.l1 = DLG_TEXT_LSC[51];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_3CarperAttackArmo");
		break;

	}
}
