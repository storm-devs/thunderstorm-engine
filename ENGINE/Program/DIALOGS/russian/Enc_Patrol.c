#include "TEXT\DIALOGS\Enc_Patrol.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0] + XI_ConvertString("Colony" + npchar.city + "Dat") + DLG_TEXT_BASE[1], DLG_TEXT_BASE[2] + NationNamePeople(sti(pchar.nation))+ DLG_TEXT_BASE[3] + NationNameAblative(sti(npchar.nation)) + DLG_TEXT_BASE[4]);
				}
				else
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[5] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[6], DLG_TEXT_BASE[7] + NationNamePeople(sti(pchar.nation))+ DLG_TEXT_BASE[8] + XI_ConvertString("Colony" + npchar.city + "Dat") + DLG_TEXT_BASE[9]);
				}
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]);
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[12] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[13],
					DLG_TEXT_BASE[14] + XI_ConvertString("Colony" + npchar.city + "Gen") + DLG_TEXT_BASE[15],
					DLG_TEXT_BASE[16] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[17] + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[18],
				DLG_TEXT_BASE[19] + GetAddress_Form(NPChar) + "?",
				DLG_TEXT_BASE[20]);
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[21],
				DLG_TEXT_BASE[22] + GetAddress_Form(NPChar) + "?");
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[23], DLG_TEXT_BASE[24]);
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[25] + GetAddress_Form(NPChar) + ".",
				DLG_TEXT_BASE[26]);
			Link.l1 = DLG_TEXT_BASE[27];
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[28],
				DLG_TEXT_BASE[29],
				DLG_TEXT_BASE[30]);
			Link.l1 = DLG_TEXT_BASE[31];
			Link.l1.go = "Exit";			
		break;
	}
}
