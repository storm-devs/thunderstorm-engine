#include "TEXT\DIALOGS\Enc_Raiders_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			ChangeCharacterReputation(pchar, -1);
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[0] + GetFullName(npchar) + DLG_TEXT_BASE[1] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[2], 
				DLG_TEXT_BASE[3] + GetFullName(pchar) + DLG_TEXT_BASE[4] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[5] + GetFullName(npchar) + DLG_TEXT_BASE[6], 
				DLG_TEXT_BASE[7] + GetMainCharacterNameGen() + DLG_TEXT_BASE[8] + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(DLG_TEXT_BASE[9] + GetFullName(npchar) + DLG_TEXT_BASE[10], 
				DLG_TEXT_BASE[11] + GetFullName(pchar) + DLG_TEXT_BASE[12] + GetFullName(npchar) + DLG_TEXT_BASE[13], 
				DLG_TEXT_BASE[14] + GetFullName(npchar) + DLG_TEXT_BASE[15] + GetMainCharacterNameGen() + DLG_TEXT_BASE[16]), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetCitizenTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetTheHellOut";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[17],
				DLG_TEXT_BASE[18],
				DLG_TEXT_BASE[19]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[20],DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]);
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[23],
				DLG_TEXT_BASE[24],
				DLG_TEXT_BASE[25]);
			Link.l2.go = "CheckSkills";	
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[26],
				DLG_TEXT_BASE[27],
				DLG_TEXT_BASE[28]);
			Link.l1 = DLG_TEXT_BASE[29] + makeint(makeint(Pchar.money)/20)*10 + DLG_TEXT_BASE[30];
			Link.l1.go = "CheckMoney";
			Link.l2 = DLG_TEXT_BASE[31];
			Link.l2.go = "CheckSkills";			
		break;

		case "CheckSkills":
			if (GetCharacterSkillToOld(Pchar, "Fencing") >= 7 && makeint(Pchar.Rank) >= 8 && Makeint(PChar.reputation) <= 30)
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[32],//15
					DLG_TEXT_BASE[33],
					DLG_TEXT_BASE[34]);
				Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[35],
					DLG_TEXT_BASE[36],
					DLG_TEXT_BASE[37]);
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase(DLG_TEXT_BASE[38],
					DLG_TEXT_BASE[39],
					DLG_TEXT_BASE[40]);
				Link.l99.go = "Exit_RunFight";
			}
			else 
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[41],
					DLG_TEXT_BASE[42],
					DLG_TEXT_BASE[43]);
				Link.l1 = DLG_TEXT_BASE[44];
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[45],
					DLG_TEXT_BASE[46],
					DLG_TEXT_BASE[47]);
				Link.l1 = DLG_TEXT_BASE[48];
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[49];
				Link.l1 = DLG_TEXT_BASE[50];
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[51],
				DLG_TEXT_BASE[52],
				DLG_TEXT_BASE[53]);
			Link.l1 = DLG_TEXT_BASE[54];
			Link.l1.go = "Exit";
			Link.l2 = DLG_TEXT_BASE[55];
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[56],
				DLG_TEXT_BASE[57],
				DLG_TEXT_BASE[58]);
			Link.l1 = DLG_TEXT_BASE[59];
			Link.l1.go = "Exit";
			Link.l2 = DLG_TEXT_BASE[60];
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[61],
				DLG_TEXT_BASE[62],
				DLG_TEXT_BASE[63]);
			Link.l1 = DLG_TEXT_BASE[64];
			Link.l1.go = "Exit";			
		break;
	}
}
