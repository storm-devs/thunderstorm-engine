#include "TEXT\DIALOGS\Quest\Banders_dialog.h"
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
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1] + pchar.questTemp.jailCanMove.Deliver.name + DLG_TEXT_Q[2];
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		case "Step_1":
			dialog.text = DLG_TEXT_Q[3];
			link.l1 = DLG_TEXT_Q[4];
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		case "Step_2":
			if (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				dialog.text = DLG_TEXT_Q[5];
				link.l1 = DLG_TEXT_Q[6];
				link.l1.go = "Step_fight";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[7] + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.Deliver.price)) + ".";
				link.l1 = DLG_TEXT_Q[8];
				link.l1.go = "Step_good";
			}
		break;
		case "Step_fight":
			dialog.text = DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "quest_fight";
		break;

		case "Step_good":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "Step_good_exit";
		break;
        case "Step_good_exit":
			AddQuestRecord("GivePrisonFree", "11");
			AddQuestUserData("GivePrisonFree", "iMoney", FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.Deliver.price)));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.jailCanMove.Deliver.price));
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Man_FackYou":
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = LinkRandPhrase(DLG_TEXT_Q[14], DLG_TEXT_Q[15], DLG_TEXT_Q[16]);
			link.l1.go = "fight";
		break;

		case "Second time":
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
	}
}
