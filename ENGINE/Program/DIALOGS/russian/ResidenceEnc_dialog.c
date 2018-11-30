#include "TEXT\DIALOGS\ResidenceEnc_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- служанка в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[1], DLG_TEXT_BASE[2], DLG_TEXT_BASE[3] + XI_ConvertString("Colony" + npchar.city + "Gen") + "!");
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[6] + GetFullName(NPChar) + ".", DLG_TEXT_BASE[7] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[8] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[9]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]);
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_BASE[12];
			link.l1 = DLG_TEXT_BASE[13];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[14], DLG_TEXT_BASE[15], DLG_TEXT_BASE[16] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[17]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[18], DLG_TEXT_BASE[19]);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[20] + GetFullName(NPChar) + ".", DLG_TEXT_BASE[21] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[22] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[23]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[24], DLG_TEXT_BASE[25]);
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = DLG_TEXT_BASE[26];
			link.l1 = DLG_TEXT_BASE[27];
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 40))
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29], DLG_TEXT_BASE[30] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[31]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[32], DLG_TEXT_BASE[33]);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[34], DLG_TEXT_BASE[35] + GetAddress_Form(NPChar) + ".", DLG_TEXT_BASE[36]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38]);
				link.l1.go = "exit";
			}
		break;
	}
}
