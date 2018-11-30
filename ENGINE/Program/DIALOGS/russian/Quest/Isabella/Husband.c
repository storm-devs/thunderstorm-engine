#include "TEXT\DIALOGS\Quest\Isabella\Husband.h"
void ProcessDialogEvent()
{
	ref NPChar, d, sld;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Good_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "RP_talkWithHusbandIsOver", 0);
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			if (CheckAttribute(pchar, "quest.wasInBeedroom"))
			{
	            if (CheckAttribute(NPChar, "quest.NiceMeet"))
				{
					dialog.text = DLG_TEXT_QB[0];
					link.l1 = DLG_TEXT_QB[1];
					link.l1.go = "Good_exit";
				}
				else
				{
					dialog.text = DLG_TEXT_QB[2];
					link.l1 = DLG_TEXT_QB[3];
					link.l1.go = "Romantic_Battle_in_Bedroom_2";
				}
				DeleteAttribute(pchar, "quest.wasInBeedroom");
			}
			else
			{				
				dialog.text = DLG_TEXT_QB[4];
				link.l1 = DLG_TEXT_QB[5] + PChar.Name + " " + PChar.LastName +
						DLG_TEXT_QB[6];
				link.l1.go = "Next_1";
				link.l2 = DLG_TEXT_QB[7];
				link.l2.go = "Good_exit";
			}
		break;
		
        case "Next_1":
            NextDiag.TempNode = "Usual_1";
			dialog.text = DLG_TEXT_QB[8];
			link.l1 = DLG_TEXT_QB[9];
			link.l1.go = "Next_2";
			link.l2 = DLG_TEXT_QB[10];
			link.l2.go = "Good_exit";
		break;
		
		case "Next_2":
		    NextDiag.TempNode = "Usual_1";
			dialog.text = DLG_TEXT_QB[11];
			link.l1 = DLG_TEXT_QB[12];
			link.l1.go = "Good_exit";
			NPChar.quest.NiceMeet = true;
		break;
		
		case "Usual_1":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		    NextDiag.TempNode = "Usual_1";
			dialog.text = DLG_TEXT_QB[13];
			link.l1 = DLG_TEXT_QB[14];
			link.l1.go = "Good_exit";
			if (CheckAttribute(pchar, "quest.VisitStep"))
			{
				if (sti(pchar.quest.VisitStep)>2 && !CheckAttribute(pchar, "quest.wasInBeedroom"))
				{
					dialog.text = DLG_TEXT_QB[15]+ GetFullName(pchar)+DLG_TEXT_QB[16];
					link.l1 = DLG_TEXT_QB[17];
					link.l1.go = "Step_2";
				}				
				if (sti(pchar.quest.VisitStep)>2 && CheckAttribute(pchar, "quest.wasInBeedroom"))
				{					
					if (!CheckAttribute(pchar, "quest.already"))
					{
						dialog.text = DLG_TEXT_QB[18];
						link.l1 = DLG_TEXT_QB[19];
						link.l1.go = "Step_1";
					}
					else
					{
						dialog.text = DLG_TEXT_QB[20];
						link.l1 = DLG_TEXT_QB[21];
						link.l1.go = "Good_exit";
						LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
					}
					DeleteAttribute(pchar, "quest.wasInBeedroom");
				}		
			}
		break;
		case "Step_1":
			dialog.text = DLG_TEXT_QB[22];
			link.l1 = DLG_TEXT_QB[23];
			link.l1.go = "Good_exit";
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true);
			pchar.quest.already = true;
		break;
		case "Step_2":
			dialog.text = DLG_TEXT_QB[24];
			link.l1 = DLG_TEXT_QB[25];
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = DLG_TEXT_QB[26];
			link.l1 = DLG_TEXT_QB[27];
			link.l1.go = "Good_exit";
			if (pchar.RomanticQuest == "DelivMigel")
			{
				dialog.text = DLG_TEXT_QB[28];
				link.l1 = DLG_TEXT_QB[29];			
			}
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
		break;

		case "Romantic_Battle_in_Bedroom":
		    if (CheckAttribute(NPChar, "quest.NiceMeet"))
		    {
			    dialog.text = PChar.Name + " " + PChar.LastName +DLG_TEXT_QB[30] + Characters[GetCharacterIndex("Isabella")].Name + DLG_TEXT_QB[31];
			    link.l1 = DLG_TEXT_QB[32];
			    link.l1.go = "Romantic_Battle_in_Bedroom_3";
			}
			else
			{
			    dialog.text = DLG_TEXT_QB[33];
			    link.l1 = DLG_TEXT_QB[34];
			    link.l1.go = "Romantic_Battle_in_Bedroom_1";
			}
		break;
		
		case "Romantic_Battle_in_Bedroom_1":
			dialog.text = DLG_TEXT_QB[35];
			link.l1 = DLG_TEXT_QB[36];
			link.l1.go = "Romantic_Battle_in_Bedroom_2";
		break;
		
		case "Romantic_Battle_in_Bedroom_2":
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_3");
		break;
		
		case "Romantic_Battle_in_Bedroom_3":
		    NextDiag.CurrentNode = "Usual_1";
            Pchar.RomanticQuest.TalkInShop = true;// обошлось все мирно - до встречи в магазине
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_4");
		break;

		case "WeWaitYouTonight":
			NextDiag.CurrentNode = "WeWaitYouTonight";
			dialog.text = DLG_TEXT_QB[37];
			link.l1 = DLG_TEXT_QB[38];
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;

		case "SeenMainHero":
			dialog.text = DLG_TEXT_QB[39] + GetFullName(pchar) + DLG_TEXT_QB[40];
			link.l1 = "...";
			link.l1.go = "SeenMainHero_1";
		break;
		case "SeenMainHero_1":
			AddQuestRecord("Romantic_Line", "9");
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "houseSp6", "SanJuan_houseSp6", "goto", "goto1", "Romantic_DeadBrother_3", 2.0);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			NextDiag.CurrentNode = "ArrestInHome_1";
			DialogExit();
		break;

		case "ArrestInHome_1":
			dialog.text = DLG_TEXT_QB[41]+
				          DLG_TEXT_QB[42];
			link.l1 = DLG_TEXT_QB[43];
			link.l1.go = "ArrestInHome_2";
		break;
		case "ArrestInHome_2":
			AddDialogExitQuest("Romantic_ArrestInHouse");
			NextDiag.CurrentNode = "Romantic_Battle_in_Bedroom_1";
			DialogExit();
		break;
		//базар в пещере
		case "TalkInCave":
			dialog.text = DLG_TEXT_QB[44];
			link.l1 = DLG_TEXT_QB[45];
			link.l1.go = "TalkInCave_1";
		break;
		case "TalkInCave_1":
			dialog.text = DLG_TEXT_QB[46];
			link.l1 = DLG_TEXT_QB[47];
			link.l1.go = "TalkInCave_2";
		break;
		case "TalkInCave_2":
			dialog.text = DLG_TEXT_QB[48];
			link.l1 = DLG_TEXT_QB[49];
			link.l1.go = "TalkInCave_3";
		break;
		case "TalkInCave_3":
			dialog.text = DLG_TEXT_QB[50];
			link.l1 = DLG_TEXT_QB[51];
			link.l1.go = "TalkInCave_4";
		break;
		case "TalkInCave_4":
			dialog.text = DLG_TEXT_QB[52] + GetFullName(pchar) + "!";
			link.l1 = DLG_TEXT_QB[53];
			link.l1.go = "TalkInCave_5";
		break;
		case "TalkInCave_5":
			dialog.text = DLG_TEXT_QB[54];
			link.l1 = DLG_TEXT_QB[55];
			link.l1.go = "TalkInCave_6";
		break;
		case "TalkInCave_6":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto5", "", -1);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Romantic_SalvatorIsDead");
			DialogExit();
		break;
	}
}
