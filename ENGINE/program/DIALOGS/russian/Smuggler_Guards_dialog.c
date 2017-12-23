#include "TEXT\DIALOGS\Smuggler_Guards_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
    int iTemp, i; // нужно для вычислений любых целых (нации)
	string attrName; // любые строки для вычислений
	ref sld;

    switch(Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":			
			chrDisableReloadToLocation = false;
   			LAi_LockFightMode(pchar, false);
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0],
                                     DLG_TEXT_BASE[1]+NationKingsName(npchar)+ DLG_TEXT_BASE[2]);
			Link.l1 = DLG_TEXT_BASE[3];
			if (makeint(Pchar.reputation) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				Link.l1.go = "IDontBelieveYou";
			}
			Link.l2 = DLG_TEXT_BASE[4];
			if(makeint(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 5)
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}
			Link.l3 = DLG_TEXT_BASE[5];
			if(makeint(Pchar.reputation) <= 25 && GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) >= 8)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}

		break;

		case "ThisTimeFree":
			dialog.snd = "Voice\COGU\COGU002";		
			dialog.text = DLG_TEXT_BASE[6] + Pchar.name + DLG_TEXT_BASE[7];
			Link.l1 = DLG_TEXT_BASE[8];
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = DLG_TEXT_BASE[9];
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			ChangeCharacterReputation(pchar, -40);
			dialog.text = DLG_TEXT_BASE[10];
			Link.l1 = DLG_TEXT_BASE[11];
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);

			//LAi_SetPlayerType(Pchar);
            LAi_SetFightMode(Pchar, true);
			//trace("And we fight those soldiers!!" + Pchar.quest.contraband.CurrentPlace);
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			
            DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);			
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
		break;

		case "IDontBelieveYou":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = DLG_TEXT_BASE[12];
			Link.l1 = DLG_TEXT_BASE[13];
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":	
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = DLG_TEXT_BASE[14];
			Link.l1 = DLG_TEXT_BASE[15] + makeint(sti(Pchar.money)/10) + DLG_TEXT_BASE[16];
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = DLG_TEXT_BASE[17] + makeint(sti(Pchar.money)/5) + DLG_TEXT_BASE[18];
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = DLG_TEXT_BASE[19] + makeint(sti(Pchar.money)/2) + DLG_TEXT_BASE[20];
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/2))
			{
				Link.l3.go = "MoneyAccepted2";
			}
			else
			{
				Link.l3.go = "TryingToGiveBribe";
			}
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = DLG_TEXT_BASE[21];
			Link.l1 = DLG_TEXT_BASE[22];
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = DLG_TEXT_BASE[23];
			Link.l1 = DLG_TEXT_BASE[24];
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = DLG_TEXT_BASE[25];
			Link.l1 = DLG_TEXT_BASE[26];
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = DLG_TEXT_BASE[27];
			Link.l1 = DLG_TEXT_BASE[28];
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = DLG_TEXT_BASE[29];
			Link.l1 = DLG_TEXT_BASE[30];
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = DLG_TEXT_BASE[31];
			Link.l1 = DLG_TEXT_BASE[32];
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();
            
			StopCoastalGuardPursuit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[sti(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[sti(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = DLG_TEXT_BASE[33];
			Link.l1 = DLG_TEXT_BASE[34];
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
