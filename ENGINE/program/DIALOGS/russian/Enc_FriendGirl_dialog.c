#include "TEXT\DIALOGS\Enc_FriendGirl_dialog.h"
void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0],
				DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4],
				DLG_TEXT_BASE[5]);
			Link.l1.go = "Step_1";			
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[6],
				DLG_TEXT_BASE[7],
				DLG_TEXT_BASE[8]);
			Link.l1 = DLG_TEXT_BASE[9];
			Link.l1.go = "Step_2";			
		break;
		case "Step_2":
			dialog.text = DLG_TEXT_BASE[10];
			Link.l1 = DLG_TEXT_BASE[11];
			Link.l1.go = "Step_3";			
		break;		
		case "Step_3":
			dialog.text = DLG_TEXT_BASE[12];
			Link.l1 = DLG_TEXT_BASE[13];
			Link.l1.go = "Step_agree";
			Link.l2 = DLG_TEXT_BASE[14];
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirl.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "pirate_1";
				model[1] = "pirate_2";
				model[2] = "pirate_3";
				model[3] = "pirate_4";
				model[4] = "pirate_5";
				model[5] = "pirate_6";
				model[6] = "pirate_7";
				model[7] = "pirate_8";
				model[8] = "pirate_9";
				model[9] = "pirate_10";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = rand(5) * 1000;
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, PIRATE, 1, false));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "monsters", "monster"+(rand(9)+1));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterReputation(pchar, -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = DLG_TEXT_BASE[15];
			Link.l1 = DLG_TEXT_BASE[16];
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = DLG_TEXT_BASE[17];
			Link.l1 = DLG_TEXT_BASE[18];
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = DLG_TEXT_BASE[19];
			Link.l1 = DLG_TEXT_BASE[20];
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = DLG_TEXT_BASE[21] + GetAddress_Form(NPChar) + ".";
			Link.l1 = DLG_TEXT_BASE[22];
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterReputation(pchar, 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = DLG_TEXT_BASE[23];
			Link.l1 = DLG_TEXT_BASE[24];
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = DLG_TEXT_BASE[25];
			Link.l1 = DLG_TEXT_BASE[26];
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = DLG_TEXT_BASE[27];
			Link.l1 = DLG_TEXT_BASE[28];
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = DLG_TEXT_BASE[29];
			Link.l1 = DLG_TEXT_BASE[30];
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = DLG_TEXT_BASE[31];
			Link.l1 = DLG_TEXT_BASE[32];
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = DLG_TEXT_BASE[33];
			Link.l1 = DLG_TEXT_BASE[34];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = DLG_TEXT_BASE[35];
			Link.l1 = DLG_TEXT_BASE[36];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
