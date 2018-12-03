#include "TEXT\DIALOGS\Smuggler_Ship_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

    string ret;
    
	switch(Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "start":
			dialog.text = DLG_TEXT_BASE[0] + Pchar.name + DLG_TEXT_BASE[1]+ Pchar.HeroParam.Land +DLG_TEXT_BASE[2]+
                          DLG_TEXT_BASE[3];
			link.l1 = DLG_TEXT_BASE[4];
			link.l1.go = "start1";
			link.l2 = DLG_TEXT_BASE[5];
			link.l2.go = "start2";
		break;

		case "start1":
			dialog.text = DLG_TEXT_BASE[6];
			link.l1 = DLG_TEXT_BASE[7];
			link.l1.go = "game_begin";
		break;
		
		case "start2":
            ret = Pchar.name + DLG_TEXT_BASE[8];
            if (sti(Pchar.nation) == PIRATE)
            {
                dialog.text = ret + DLG_TEXT_BASE[9]+
                              DLG_TEXT_BASE[10];
            }
            else
            {
                dialog.text = ret + DLG_TEXT_BASE[11];
            }
            link.l1 = DLG_TEXT_BASE[12];
			link.l1.go = "game_begin";
			link.l2 = DLG_TEXT_BASE[13];
			link.l2.go = "start3";
		break;
		
		case "game_begin":
			DialogExit();
            addDialogExitQuest("Tut_SkipTutorialOnShip");
		break;
		
		case "start3":
			dialog.text = DLG_TEXT_BASE[14];
			link.l1 = DLG_TEXT_BASE[15];
			link.l1.go = "game_begin";
			link.l2 = DLG_TEXT_BASE[16];
			link.l2.go = "start4";
		break;
		
		case "start4":
			dialog.text = DLG_TEXT_BASE[17];
			link.l1 = DLG_TEXT_BASE[18];
			link.l1.go = "exit";
			addDialogExitQuest("Tut_KillOnShip");
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = DLG_TEXT_BASE[19];
			Link.l1.go = "exit";
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
            NPChar.location = "none"; // чтоб на палубе не болтался
			//Шанс на то что продадут на рудники.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = DLG_TEXT_BASE[20];
				link.l1 = DLG_TEXT_BASE[21];
				//заглушка, пока нет рудников.
				link.l1.go = "Travel_fight";
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[22];
				link.l1 = DLG_TEXT_BASE[23];
				link.l1.go = "Travel_end";
				link.l2 = DLG_TEXT_BASE[24];
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//Квест бук
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt")));


			LAi_SetPlayerType(PChar);
			//грузим ГГ куда нужно.... 
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
									pchar.GenQuest.contraTravel.destination.group,
									pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
