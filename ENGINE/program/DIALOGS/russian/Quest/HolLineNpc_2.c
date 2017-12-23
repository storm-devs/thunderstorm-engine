#include "TEXT\DIALOGS\Quest\HolLineNpc_2.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
            link.l1.go = "exit";

//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")// кэп пиратов, вывезший де Барраса из Тортуги
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3];
    			link.l1.go = "Step_H7_1";
            }
            if (npchar.id == "LoranDeGraf")// Лоран де Граф, квест №8
            {
    			dialog.text = DLG_TEXT_Q[4];
    			link.l1 = DLG_TEXT_Q[5];
    			link.l1.go = "exit";
            }
			if (pchar.questTemp.State == "SeekBible_WeWon" && npchar.id == "LoranDeGraf")// Лоран де Граф, квест №8
            {
    			dialog.text = DLG_TEXT_Q[6];
    			link.l1 = DLG_TEXT_Q[7];
    			link.l1.go = "Step_H8_10";
            }
            if (pchar.questTemp.State == "SeekBible_IHaveMap")
            {
    			dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "exit";
            }
            if (pchar.questTemp.State == "SeekBible_SeekMoney")
            {
    			dialog.text = DLG_TEXT_Q[10];
                if (sti(pchar.money) >= 235000)
                {
                    link.l1 = DLG_TEXT_Q[11];
        			link.l1.go = "Step_H8_13";
                }
                else
                {
                    link.l1 = DLG_TEXT_Q[12];
        			link.l1.go = "exit";
                }
            }
        break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Диалоги кэпа, который увез де Барраса из Тортуги **********************************
 		case "Step_H7_1":
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "Step_H7_2";
		break;
  		case "Step_H7_2":
			dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "Step_H7_3";
		break;
  		case "Step_H7_3":
			dialog.text = DLG_TEXT_Q[17]+
                          DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "Step_H7_4";
		break;
  		case "Step_H7_4":
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=2; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Pirate"+i, "officer_"+i, "man", "man", 25, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 25, 100, 100, BLADE_LONG, "pistol3", 50);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
               	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
            }
            LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            QuestAboardCabinDialogExitWithBattle("");
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "8");
            pchar.questTemp.State.KingResult = "BrigAborded"; //флаг бриг взят на абордаж
            pchar.quest.DelivLettTortuga_BrigDieHard.over = "yes";
            pchar.quest.DelivLettTortuga_AfterBrigSunk.over = "yes";
            Island_SetReloadEnableGlobal("PuertoRico", true);
            Pchar.quest.DelivLettTortuga_AttackWarship.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_AttackWarship.win_condition.l1.location = "SantaCatalina";
            Pchar.quest.DelivLettTortuga_AttackWarship.win_condition = "DelivLettTortuga_AttackWarship";
            SetTimerCondition("DelivLettTortuga_WarshipTimeOver", 0, 0, 12, false);
            DialogExit();
		break;

		case "Step_H8_10":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21] + GetFullName(pchar) + DLG_TEXT_Q[22];
			link.l1.go = "Step_H8_11";
    	break;
		case "Step_H8_11":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "Step_H8_12";
    	break;
		case "Step_H8_12":
			dialog.text = DLG_TEXT_Q[25];
            if (sti(pchar.money) >= 235000)
            {
                link.l1 = DLG_TEXT_Q[26];
    			link.l1.go = "Step_H8_13";
    			AddMoneyToCharacter(pchar, -235000);
            }
            else
            {
                link.l1 = DLG_TEXT_Q[27];
    			link.l1.go = "Step_H8_15";
            }
    	break;
		case "Step_H8_13":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = DLG_TEXT_Q[29];
			link.l1.go = "Step_H8_14";
            GiveItem2Character(pchar, "LegransMap");
    	break;
		case "Step_H8_14":
			dialog.text = DLG_TEXT_Q[30];
			link.l1 = DLG_TEXT_Q[31];
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_8_SeekBible", "9");
            NPChar.LifeDay = 2;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
    	    pchar.questTemp.State = "SeekBible_IHaveMap";
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 200;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade33 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade28 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade34 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade32 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade23 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.pistol5 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.pistol6 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
            pchar.GenQuestBox.Terks_Grot.box1.items.blade5 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 10;
            pchar.GenQuestBox.Terks_Grot.box1.items.potionwine = 3;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry2 = 20;
            pchar.GenQuestBox.Terks_Grot.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian6 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian11 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian15 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian12 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.cirass5 = 1;
            pchar.GenQuestBox.Terks_Grot.box1.items.Bible = 1;
        break;
		case "Step_H8_15":
			dialog.text = DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_SeekMoney";
			pchar.quest.SeekBible_DeGrafToTavern.win_condition.l1 = "MapEnter";
            pchar.quest.SeekBible_DeGrafToTavern.win_condition = "SeekBible_DeGrafToTavern";
    	break;
    	
    	
    }
}
