#include "TEXT\DIALOGS\Quest\AntonioDeSouza.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[0],
                         DLG_TEXT_Q[1], DLG_TEXT_Q[2],
                         DLG_TEXT_Q[3] + GetFullName(pchar) + DLG_TEXT_Q[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[5],
                                               DLG_TEXT_Q[6],
                                               DLG_TEXT_Q[7],
                                               DLG_TEXT_Q[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
//>>>>>>>>>>>>========= Разброс диалогов =====================
			if (pchar.questTemp.State == "Inquisition_toDeSouza")//Квест №2, базар с гл.Инквизитором
			{
                dialog.text = DLG_TEXT_Q[9];
    			link.l1 = DLG_TEXT_Q[10];
    			link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Inquisition_toCuracao")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = DLG_TEXT_Q[11] + GetFullName(pchar) + DLG_TEXT_Q[12];
        			link.l1 = DLG_TEXT_Q[13];
        			link.l1.go = "Step_S2_12";
        			link.l2 = DLG_TEXT_Q[14];
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = DLG_TEXT_Q[15];
        			link.l1 = DLG_TEXT_Q[16];
        			link.l1.go = "exit";
                }
            }
			if (pchar.questTemp.State == "Inquisition_afterFrancisco")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = DLG_TEXT_Q[17] + GetFullName(pchar) + DLG_TEXT_Q[18];
        			link.l1 = DLG_TEXT_Q[19];
        			link.l1.go = "Step_S2_12";
        			link.l2 = DLG_TEXT_Q[20];
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = DLG_TEXT_Q[21];
        			link.l1 = DLG_TEXT_Q[22];
        			link.l1.go = "Step_S2_11";
                }
            }
			if (pchar.questTemp.State == "Inquisition_backAllGood" || pchar.questTemp.State == "Inquisition_backPartGood" || pchar.questTemp.State == "Inquisition_backBad")
			{
                dialog.text = DLG_TEXT_Q[23];
    			link.l1 = DLG_TEXT_Q[24];
    			link.l1.go = "exit";
            }
			if (pchar.questTemp.State == "TakeRockBras_RockTaken")
			{
                dialog.text = DLG_TEXT_Q[25];
    			link.l1 = DLG_TEXT_Q[26];
    			link.l1.go = "Step_S3_1";
            }

        break;

//<<<<<<<<<<<<===== Разброс диалогов  =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Задания Инквизиции. Квест №2 **********************************
 		case "Step_S2_1":
			dialog.text = DLG_TEXT_Q[27]+
                          DLG_TEXT_Q[28]+
                          DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = DLG_TEXT_Q[35]+
                          DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = DLG_TEXT_Q[44]+
                          DLG_TEXT_Q[45]+
                          DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toCuracao";
            AddQuestRecord("Spa_Line_2_Inquisition", "2");
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1 = "location";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1.location = "Santiago_town";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition = "Inquisition_MeetFrancisco";
		break;
 		case "Step_S2_11":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
            GiveItem2Character(pchar,"DeSouzaCross");
		break;
 		case "Step_S2_12":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "Step_S2_NotMoney";
            if (pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = DLG_TEXT_Q[56];
    			link.l1.go = "Step_S2_OnlyUsurer";
            }
            if (pchar.questTemp.State.Store == "Ok")
            {
    			link.l1 = DLG_TEXT_Q[57];
    			link.l1.go = "Step_S2_OnlyStore";
            }
            if (pchar.questTemp.State.Store == "Ok" && pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = DLG_TEXT_Q[58];
    			link.l1.go = "Step_S2_All";
            }
		break;
 		case "Step_S2_NotMoney":
			dialog.text = DLG_TEXT_Q[59];
			link.l1 = DLG_TEXT_Q[60];
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
			dialog.text = DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "exit";
            pchar.questTemp.State = "Inquisition_backBad";
            AddQuestRecord("Spa_Line_2_Inquisition", "15");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
		break;
 		case "Step_S2_OnlyUsurer":
            if (sti(pchar.money) >= 50000)
            {
                dialog.text = DLG_TEXT_Q[63];
    			link.l1 = DLG_TEXT_Q[64];
    			link.l1.go = "Step_S2_14";
            }
            else
            {
                dialog.text = DLG_TEXT_Q[65];
    			link.l1 = DLG_TEXT_Q[66];
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyUsurer";
            }
		break;
 		case "Step_S2_14":
			dialog.text = DLG_TEXT_Q[67]+
                          DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = DLG_TEXT_Q[70];
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -41000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_OnlyStore":
            if (sti(pchar.money) >= 100000)
            {
                dialog.text = DLG_TEXT_Q[71];
    			link.l1 = DLG_TEXT_Q[72];
    			link.l1.go = "Step_S2_15";
            }
            else
            {
                dialog.text = DLG_TEXT_Q[73];
    			link.l1 = DLG_TEXT_Q[74];
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyStore";
            }
		break;
 		case "Step_S2_15":
			dialog.text = DLG_TEXT_Q[75]+
                          DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = DLG_TEXT_Q[78];
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -82000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_All":
            if (sti(pchar.money) >= 150000)
            {
                dialog.text = DLG_TEXT_Q[79];
    			link.l1 = DLG_TEXT_Q[80];
    			link.l1.go = "Step_S2_16";
            }
            else
            {
                dialog.text = DLG_TEXT_Q[81];
    			link.l1 = DLG_TEXT_Q[82];
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_All";
            }
		break;
 		case "Step_S2_16":
			dialog.text = DLG_TEXT_Q[83]+
                          DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = DLG_TEXT_Q[86];
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backAllGood";
			AddMoneyToCharacter(pchar, -123000);
			AddQuestRecord("Spa_Line_2_Inquisition", "17");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_17":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = DLG_TEXT_Q[93]+
                          DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Step_S2_21";
			TakeItemFromCharacter(pchar, "Bible");
		break;
 		case "Step_S2_21":
			dialog.text = DLG_TEXT_Q[96]+
                          DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "Step_S2_22";
		break;
 		case "Step_S2_22":
			dialog.text = DLG_TEXT_Q[99];
			link.l1 = DLG_TEXT_Q[100];
			link.l1.go = "exit";
            GiveItem2Character(pchar, "cirass5");
		break;
//********************************* Захват Рока Бразильца. Квест №3 **********************************
 		case "Step_S3_1":
            if (CheckPassengerInCharacter(pchar, "RockBrasilian"))
            {
    			dialog.text = DLG_TEXT_Q[101];
    			link.l1 = DLG_TEXT_Q[102];
    			link.l1.go = "Step_S3_2";
            }
            else
            {
    			dialog.text = DLG_TEXT_Q[103];
    			link.l1 = DLG_TEXT_Q[104];
    			link.l1.go = "exit";
            }
		break;
 		case "Step_S3_2":
			dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "exit";
			NPChar.LifeDay = 10;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddQuestRecord("Spa_Line_3_RockBrasilian", "6");
			pchar.questTemp.State = "TakeRockBras_RockGiven";
			sld = characterFromId("RockBrasilian");
			ReleasePrisoner(sld);
     	    sld.LifeDay = 0; // уберем нпс
		break;

    }
}
