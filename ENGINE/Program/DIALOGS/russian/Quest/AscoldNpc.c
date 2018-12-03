#include "TEXT\DIALOGS\Quest\AscoldNpc.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
            link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna" || pchar.questTemp.Ascold == "2SeekInformatorHavanna")
            {
            	dialog.text = DLG_TEXT_Q[2];
        		link.l1 = DLG_TEXT_Q[3] + GetFullName(pchar) + DLG_TEXT_Q[4];
        		link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
            	dialog.text = DLG_TEXT_Q[5];
        		link.l1 = DLG_TEXT_Q[6];
        		link.l1.go = "exit";
            }
        break;
//<<<<<<<<<<<<======== Разброс диалогов по персонажам ======================
 		case "Step_1":
        	dialog.text = DLG_TEXT_Q[7];
    		link.l1 = DLG_TEXT_Q[8];
    		link.l1.go = "Step_2";
		break;
 		case "Step_2":
        	dialog.text = DLG_TEXT_Q[9];
    		link.l1 = DLG_TEXT_Q[10];
    		link.l1.go = "Step_3";
		break;
 		case "Step_3":
        	dialog.text = DLG_TEXT_Q[11]+
                          DLG_TEXT_Q[12];
    		link.l1 = DLG_TEXT_Q[13];
    		link.l1.go = "Step_4";
		break;
 		case "Step_4":
        	dialog.text = DLG_TEXT_Q[14]+
                          DLG_TEXT_Q[15];
    		link.l1 = DLG_TEXT_Q[16];
    		link.l1.go = "Step_5";
		break;
 		case "Step_5":
        	dialog.text = DLG_TEXT_Q[17];
    		link.l1 = DLG_TEXT_Q[18];
    		link.l1.go = "Step_6";
		break;
 		case "Step_6":
        	dialog.text = DLG_TEXT_Q[19]+
                          DLG_TEXT_Q[20];
    		link.l1 = DLG_TEXT_Q[21];
    		link.l1.go = "Step_7";
		break;
 		case "Step_7":
        	dialog.text = DLG_TEXT_Q[22];
    		link.l1 = DLG_TEXT_Q[23];
    		link.l1.go = "exit";
			npchar.LifeDay = 5;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            AddQuestRecord("Ascold", "7");
            pchar.questTemp.Ascold = "ReciveInformationManowar";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1 = "location";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1.location = "Beliz";
            Pchar.quest.Ascold_AttackTenManowars.win_condition = "Ascold_AttackTenManowars";
		break;



        case "Step_":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "Step_";
        break;
 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
