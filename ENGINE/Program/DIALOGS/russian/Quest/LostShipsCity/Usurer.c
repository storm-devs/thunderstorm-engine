#include "TEXT\DIALOGS\Quest\LostShipsCity\Usurer.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_LSC[0];
				link.l1 = DLG_TEXT_LSC[1] + GetFullName(pchar) + ".";
				link.l1.go = "FT_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[2];
				link.l1 = DLG_TEXT_LSC[3];
				link.l1.go = "GiveMoney";
				link.l10 = DLG_TEXT_LSC[4];
				link.l10.go = "Exit";
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[5];
					link.l8.go = "SeekCrew";
				}
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FT_1":
			dialog.text = DLG_TEXT_LSC[6];
			link.l1 = DLG_TEXT_LSC[7];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[8];
			link.l1 = DLG_TEXT_LSC[9];
			link.l1.go = "Exit";
		break;

		//обнаружение √√ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = DLG_TEXT_LSC[10];
			link.l1 = DLG_TEXT_LSC[11];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[12];
			link.l1 = DLG_TEXT_LSC[13];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = DLG_TEXT_LSC[14];
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[15], DLG_TEXT_LSC[16], DLG_TEXT_LSC[17]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[18], DLG_TEXT_LSC[19]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[20], DLG_TEXT_LSC[21], DLG_TEXT_LSC[22]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[23], DLG_TEXT_LSC[24]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[25], DLG_TEXT_LSC[26]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[27], 
				DLG_TEXT_LSC[28], 
				DLG_TEXT_LSC[29],
                DLG_TEXT_LSC[30], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[31], 
				DLG_TEXT_LSC[32],
                DLG_TEXT_LSC[33], 
				DLG_TEXT_LSC[34], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[35];
			link.l1 = DLG_TEXT_LSC[36];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[37];
			link.l1 = DLG_TEXT_LSC[38];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[39];
			link.l1 = DLG_TEXT_LSC[40];
			link.l1.go = "exit";
		break;

		//зан€ть бабла
		case "GiveMoney":
			if (CheckAttribute(npchar, "quest.loan"))
			{
				if (sti(npchar.quest.loan.qtyMoney) >= 1000000)
				{
					dialog.text = DLG_TEXT_LSC[41];
					link.l1 = DLG_TEXT_LSC[42];
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[43];
					link.l1 = DLG_TEXT_LSC[44];
					link.l1.go = "GiveMoney_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[45];
				link.l1 = DLG_TEXT_LSC[46];
				link.l1.go = "GiveMoneyKn_1";
				npchar.quest.loan = true;
				npchar.quest.loan.qtyMoney = 0; //кол-во вз€тых денег
			}
		break;

		case "GiveMoneyKn_1":
			dialog.text = DLG_TEXT_LSC[47];
			link.l1 = DLG_TEXT_LSC[48];
			link.l1.go = "GiveMoneyKn_2";
		break;
		case "GiveMoneyKn_2":
			dialog.text = DLG_TEXT_LSC[49];
			link.l1 = DLG_TEXT_LSC[50];
			link.l1.go = "GiveMoneyKn_3";
		break;
		case "GiveMoneyKn_3":
			dialog.text = DLG_TEXT_LSC[51];
			link.l1 = DLG_TEXT_LSC[52];
			link.l1.go = "GiveMoneyKn_4";
		break;
		case "GiveMoneyKn_4":
			dialog.text = DLG_TEXT_LSC[53];
			link.l1 = DLG_TEXT_LSC[54];
			link.l1.go = "GiveMoney_1";
		break;

		case "GiveMoney_1":
			dialog.text = DLG_TEXT_LSC[55];
			Link.l1.edit = 4;
			Link.l1 = "";
			link.l1.go = "GiveMoney_2";
			Link.l2 = DLG_TEXT_LSC[56];
			link.l2.go = "GiveMoney_disAgree";
		break;
		case "GiveMoney_2":
			iTemp = sti(dialogEditStrings[4]);
			if ((iTemp + sti(npchar.quest.loan.qtyMoney)) > 1000000)
			{
				dialog.text = DLG_TEXT_LSC[57] + FindRussianMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)) + DLG_TEXT_LSC[58];
				link.l1 = DLG_TEXT_LSC[59];
				link.l1.go = "exit";
			}
			else
			{
				if (iTemp <= 0)
				{
					dialog.text = DLG_TEXT_LSC[60];
					link.l1 = DLG_TEXT_LSC[61];
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[62];
					link.l1 = DLG_TEXT_LSC[63];
					link.l1.go = "GiveMoney_3";
					AddMoneyToCharacter(pchar, iTemp);
					npchar.quest.loan.qtyMoney = sti(npchar.quest.loan.qtyMoney) + iTemp;
				}
			}
		break;
		case "GiveMoney_3":
			dialog.text = DLG_TEXT_LSC[64] + FindRussianMoneyString(sti(npchar.quest.loan.qtyMoney) * 5) + ".";
			link.l1 = DLG_TEXT_LSC[65];
			link.l1.go = "GiveMoney_4";
		break;
		case "GiveMoney_4":
			dialog.text = DLG_TEXT_LSC[66];
			link.l1 = DLG_TEXT_LSC[67];
			link.l1.go = "exit";
		break;
		case "GiveMoney_disAgree":
			dialog.text = DLG_TEXT_LSC[68];
			link.l1 = DLG_TEXT_LSC[69];
			link.l1.go = "exit";
		break;
	}
}
