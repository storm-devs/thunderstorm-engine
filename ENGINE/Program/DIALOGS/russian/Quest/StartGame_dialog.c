#include "TEXT\DIALOGS\Quest\StartGame_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Finish_2":
            DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_RemoveCheckMinHP(Pchar); // снимем проверки
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		
		case "ChangePIRATES":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Teach_battle_1":
		    LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			dialog.text = DLG_TEXT_Q[0];
			if (bBettaTestMode)
			{
				link.l0 = DLG_TEXT_Q[1];
				link.l0.go = "Finish_2";
			}
			link.l1 = DLG_TEXT_Q[2];
			link.l1.go = "Node_1";
		break;

        case "Node_1":
			dialog.text = DLG_TEXT_Q[3];
			link.l1     = DLG_TEXT_Q[4];
			link.l1.go  = "Node_2";
		break;
		
		case "Node_2":
			dialog.text = DLG_TEXT_Q[5]+ 
			XI_ConvertString("people"+GetNationNameByType(sti(pchar.HeroParam.EnemyNation)) + "Acc") + DLG_TEXT_Q[6];
			link.l1     = DLG_TEXT_Q[7];
			link.l1.go  = "Node_3";
		break;
		
		case "Node_3":
			dialog.text = DLG_TEXT_Q[8]+
			              XI_ConvertString("Colony" + pchar.HeroParam.FromCityId + "Gen") + DLG_TEXT_Q[9];
			link.l1     = DLG_TEXT_Q[10];
			link.l1.go  = "Node_4";
		break;
		
		case "Node_4":
			dialog.text = DLG_TEXT_Q[11];
			link.l1     = DLG_TEXT_Q[12];
			link.l1.go  = "ChangePIRATES";
			link.l2     = DLG_TEXT_Q[13];
			link.l2.go  = "Node_5";
		break;
		
		case "Node_5":
			dialog.text = DLG_TEXT_Q[14];
			link.l1     = DLG_TEXT_Q[15];
			link.l1.go  = "Teach_1";
			link.l2     = DLG_TEXT_Q[16];
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			dialog.text = DLG_TEXT_Q[17] + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + DLG_TEXT_Q[18];
			link.l1     = DLG_TEXT_Q[19];
			link.l1.go  = "Finish_2";
			link.l2     = DLG_TEXT_Q[20];
			link.l2.go  = "Advice_1";
		break;
		
		case "Advice_1":
			dialog.text = DLG_TEXT_Q[21];
			link.l1     = DLG_TEXT_Q[22];
			link.l1.go  = "Advice_2";
			link.l2     = DLG_TEXT_Q[23];
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = DLG_TEXT_Q[24];
			link.l1     = DLG_TEXT_Q[25];
			link.l1.go  = "Advice_3";
			link.l2     = DLG_TEXT_Q[26];
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = DLG_TEXT_Q[27];
			link.l1     = DLG_TEXT_Q[28];
			link.l1.go  = "Advice_4";
			link.l2     = DLG_TEXT_Q[29];
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = DLG_TEXT_Q[30];
			link.l1     = DLG_TEXT_Q[31];
			link.l1.go  = "Advice_5";
			link.l2     = DLG_TEXT_Q[32];
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = DLG_TEXT_Q[33];
			link.l1     = DLG_TEXT_Q[34];
			link.l1.go  = "Advice_6";
			link.l2     = DLG_TEXT_Q[35];
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = DLG_TEXT_Q[36];
			link.l1     = DLG_TEXT_Q[37];
			link.l1.go  = "Advice_7";
			link.l2     = DLG_TEXT_Q[38];
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = DLG_TEXT_Q[39];
			link.l1     = DLG_TEXT_Q[40];
			link.l1.go  = "Advice_8";
			link.l2     = DLG_TEXT_Q[41];
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = DLG_TEXT_Q[42];
			link.l1     = DLG_TEXT_Q[43];
			link.l1.go  = "Advice_9";
			link.l2     = DLG_TEXT_Q[44];
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = DLG_TEXT_Q[45];
			link.l1     = DLG_TEXT_Q[46];
			link.l1.go  = "Advice_10";
			link.l2     = DLG_TEXT_Q[47];
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = DLG_TEXT_Q[48];
			link.l1     = DLG_TEXT_Q[49];
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = DLG_TEXT_Q[50];
			link.l1     = DLG_TEXT_Q[51];
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = DLG_TEXT_Q[52];
			link.l1     = DLG_TEXT_Q[53];
			link.l1.go  = "Teach_3";
			link.l2     = DLG_TEXT_Q[54];
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = DLG_TEXT_Q[55]+
						  DLG_TEXT_Q[56];
			link.l1     = DLG_TEXT_Q[57];
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = DLG_TEXT_Q[58];
			link.l1     = DLG_TEXT_Q[59];
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = DLG_TEXT_Q[60];
			link.l1     = DLG_TEXT_Q[61];
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = DLG_TEXT_Q[62];
			link.l1     = DLG_TEXT_Q[63];
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = DLG_TEXT_Q[64];
			link.l1     = DLG_TEXT_Q[65];
			link.l1.go  = "Teach_battle_1";
			link.l2     = DLG_TEXT_Q[66];
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[67],
			                             DLG_TEXT_Q[68],
										 DLG_TEXT_Q[69]) +
										 DLG_TEXT_Q[70];
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = DLG_TEXT_Q[71];
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = DLG_TEXT_Q[72];
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = DLG_TEXT_Q[73] +
						  DLG_TEXT_Q[74];
			link.l1     = DLG_TEXT_Q[75];
			link.l1.go  = "Teach_battle_1";
			link.l2     = DLG_TEXT_Q[76];
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = DLG_TEXT_Q[77];
			link.l1     = DLG_TEXT_Q[78];
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = DLG_TEXT_Q[79];
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = DLG_TEXT_Q[80];
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = DLG_TEXT_Q[81];
			link.l2.go  = "Finish_1";
		break;
	}
}
