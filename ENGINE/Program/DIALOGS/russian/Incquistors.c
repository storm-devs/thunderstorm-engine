#include "TEXT\DIALOGS\Incquistors.h"
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
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
					link.l1 = DLG_TEXT_BASE[2];
					link.l1.go = "fight";			
			}
			else
			{
				if (pchar.questTemp.MC == "toByeBye" && findsubstr(npchar.id, "Incquisitor_", 0) != -1)
				{
					dialog.text = DLG_TEXT_BASE[3];
					link.l1 = DLG_TEXT_BASE[4];
					link.l1.go = "MCIncq";
					pchar.questTemp.MC = "Incquisitio";
					break;
				}
				
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[5], DLG_TEXT_BASE[6]),
							DLG_TEXT_BASE[7], DLG_TEXT_BASE[8],
							RandPhraseSimple(DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]), 
							DLG_TEXT_BASE[13], DLG_TEXT_BASE[14], RandPhraseSimple(DLG_TEXT_BASE[15], DLG_TEXT_BASE[16]), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = DLG_TEXT_BASE[17];
					link.l1 = DLG_TEXT_BASE[18];
					link.l1.go = "fight";
					StartIncquisitioAttack();
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23]);	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[24], DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[27], DLG_TEXT_BASE[28]);
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце. 
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = DLG_TEXT_BASE[29];
						link.l1.go = "Step_F7_2";
					}
					//<== квест №7, базар о Роке Бразильце. 
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[33], DLG_TEXT_BASE[34]);
					link.l1.go = "exit";
					//==> квест №7, базар о Роке Бразильце. 
					if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
					{
						link.l1 = DLG_TEXT_BASE[35];
						link.l1.go = "Step_F7_1";
					}
					//<== квест №7, базар о Роке Бразильце. 
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

//**************************** Фр. линейка. Квест №7, спасение Рока Бразильца ********************************
 		case "Step_F7_1":
			dialog.text = DLG_TEXT_BASE[36];
			link.l1 = DLG_TEXT_BASE[37];
			link.l1.go = "exit";
		break;
 		case "Step_F7_2":
			dialog.text = DLG_TEXT_BASE[38];
			link.l1 = DLG_TEXT_BASE[39];
			link.l1.go = "exit";
		break;
		
//**************************** сдаем зачарованный Дес-Мойнес ********************************
		case "MCIncq":
			dialog.text = DLG_TEXT_BASE[40];
			link.l1 = DLG_TEXT_BASE[41];
			link.l1.go = "MCIncq_1";
		break;
		case "MCIncq_1":
			dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "MCIncq_2";
		break;
		case "MCIncq_2":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "MCIncq_3";
		break;
		case "MCIncq_3":
			dialog.text = DLG_TEXT_BASE[46];
			link.l1 = DLG_TEXT_BASE[47];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterReputation(pchar, -10);
		break;
	}
}
