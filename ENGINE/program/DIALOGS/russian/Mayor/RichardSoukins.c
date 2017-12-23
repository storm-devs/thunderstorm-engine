#include "TEXT\DIALOGS\Mayor\RichardSoukins.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = DLG_TEXT_MR[0];
			link.l1 = DLG_TEXT_MR[1];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = DLG_TEXT_MR[2];
				link.l1.go = "PL_Q7_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = DLG_TEXT_MR[3];
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = DLG_TEXT_MR[4];
			link.l1 = DLG_TEXT_MR[5];
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = DLG_TEXT_MR[6];
			link.l1 = DLG_TEXT_MR[7];
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		case "PL_Q7_5":
			dialog.text = DLG_TEXT_MR[8];
			link.l1 = DLG_TEXT_MR[9];
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		//пиратка, квест №8
		case "PL_Q8_deck":
			dialog.text = DLG_TEXT_MR[10];
			link.l1 = DLG_TEXT_MR[11];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = DLG_TEXT_MR[12];
			link.l1 = DLG_TEXT_MR[13];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8_deck_2":
			dialog.text = DLG_TEXT_MR[14];
			link.l1 = DLG_TEXT_MR[15];
			link.l1.go = "PL_Q8_deck_3";
		break;
		case "PL_Q8_deck_3":
			dialog.text = DLG_TEXT_MR[16];
			link.l1 = DLG_TEXT_MR[17];
			link.l1.go = "PL_Q8_deck_4";
		break;
		case "PL_Q8_deck_4":
			dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		case "PL_Q8_deck_5":
			dialog.text = DLG_TEXT_MR[20];
			link.l1 = DLG_TEXT_MR[21];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		//в бухте Дарьенский залив
		case "Shore48":
			dialog.text = DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Shore48_1";
		break;
		case "Shore48_1":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], false); 
			chrDisableReloadToLocation = false; 
			LAi_SetWarriorTypeNoGroup(npchar);
			NextDiag.TempNode = "Shore48_over";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Shore48_over":
			dialog.text = DLG_TEXT_MR[24];
			link.l1 = DLG_TEXT_MR[25];
			link.l1.go = "exit";
		break;
		//после штурма у стен Панамы
		case "PQ8_exitTown":
			dialog.text = DLG_TEXT_MR[26];
			link.l1 = DLG_TEXT_MR[27];
			link.l1.go = "PQ8_exitTown_1";
		break;
		case "PQ8_exitTown_1":
			dialog.text = DLG_TEXT_MR[28];
			link.l1 = DLG_TEXT_MR[29];
			link.l1.go = "PQ8_exitTown_2";
		break;
		case "PQ8_exitTown_2":
			dialog.text = DLG_TEXT_MR[30];
			link.l1 = DLG_TEXT_MR[31];
			link.l1.go = "PQ8_exitTown_3";
		break;
		case "PQ8_exitTown_3":
			dialog.text = DLG_TEXT_MR[32];
			link.l1 = DLG_TEXT_MR[33];
			link.l1.go = "exit";
			LAi_warrior_DialogEnable(npchar, false);
		break;
	}
}
