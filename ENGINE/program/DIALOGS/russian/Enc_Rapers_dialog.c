#include "TEXT\DIALOGS\Enc_Rapers_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();			
		break;

		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]);
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[6],
				DLG_TEXT_BASE[7],
				DLG_TEXT_BASE[8]);
			Link.l2.go = "Exit_NoFight";
		break;
		
		case "Node_2":
			dialog.text = DLG_TEXT_BASE[9];
			Link.l1 = DLG_TEXT_BASE[10];
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[11];
			Link.l1 = DLG_TEXT_BASE[12];
			Link.l1.go = "Exit_NoFight";
			Link.l2 = DLG_TEXT_BASE[13];
			Link.l2.go = "Node_2";
		break;
				
	}
}
