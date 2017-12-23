#include "TEXT\DIALOGS\Quest\Ascold.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = DLG_TEXT_Q[0];
        		link.l1 = DLG_TEXT_Q[1] + GetFullName(pchar) + ".";
        		link.l1.go = "Step_1";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = DLG_TEXT_Q[2];
        		link.l1 = DLG_TEXT_Q[3];
        		link.l1.go = "exit";
        		link.l2 = DLG_TEXT_Q[4];
        		link.l2.go = "Step_3";
                NextDiag.TempNode = "First time";
            }
		break;

 		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "Step_1":
        	dialog.text = DLG_TEXT_Q[5];
    		link.l1 = DLG_TEXT_Q[6];
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = DLG_TEXT_Q[7];
    		link.l1 = DLG_TEXT_Q[8];
    		link.l1.go = "First time";
		break;

 		case "Step_3":
            if (npchar.quest.meeting == "1")
            {
            	dialog.text = DLG_TEXT_Q[9];
        		link.l1 = "...";
        		npchar.quest.meeting = "2";
            }
            else
            {
            	dialog.text = RandPhraseSimple(DLG_TEXT_Q[10], DLG_TEXT_Q[11]);
        		link.l1 = RandPhraseSimple(DLG_TEXT_Q[12], DLG_TEXT_Q[13]);
            }
            link.l1.go = "Step_4";
		break;

 		case "Step_4":
            DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "HaveRecomendation":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = DLG_TEXT_Q[14];
				link.l1 = DLG_TEXT_Q[15] + GetFullName(pchar) + DLG_TEXT_Q[16] + GetFullName(sld) + DLG_TEXT_Q[17] + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = DLG_TEXT_Q[18];
        		link.l1 = DLG_TEXT_Q[19] + GetFullName(sld) + DLG_TEXT_Q[20] + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
            }
            link.l1.go = "Step_5";
		break;
		
 		case "Step_5":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
        	dialog.text = DLG_TEXT_Q[21]+
                          DLG_TEXT_Q[22]+
                          DLG_TEXT_Q[23];
    		link.l1 = sld.lastname + DLG_TEXT_Q[24];
    		link.l1.go = "Step_6";
		break;

 		case "Step_6":
        	dialog.text = DLG_TEXT_Q[25];
    		link.l1 = DLG_TEXT_Q[26];
            if (CheckCharacterItem(pchar, "Powder_mummie"))
            {
        		link.l1.go = "Step_7";
        		TakeItemFromCharacter(pchar, "Powder_mummie");
        		AddMoneyToCharacter(pchar, 30000);
            }
            else
            {
        		link.l1.go = "No_Powder";
            }
		break;

 		case "No_Powder":
        	dialog.text = DLG_TEXT_Q[27]+
                          DLG_TEXT_Q[28];
    		link.l1 = DLG_TEXT_Q[29];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_7":
        	dialog.text = DLG_TEXT_Q[30];
    		link.l1 = DLG_TEXT_Q[31];
    		link.l1.go = "Step_8";
		break;

 		case "Step_8":
        	dialog.text = DLG_TEXT_Q[32]+
                          DLG_TEXT_Q[33]+
                          DLG_TEXT_Q[34];
    		link.l1 = DLG_TEXT_Q[35];
    		link.l1.go = "Step_9";
		break;

 		case "Step_9":
        	dialog.text = DLG_TEXT_Q[36]+
                          DLG_TEXT_Q[37];
    		link.l1 = DLG_TEXT_Q[38];
    		link.l1.go = "Step_10";
    		link.l2 = DLG_TEXT_Q[39];
    		link.l2.go = "No_Work";
		break;

 		case "No_Work":
        	dialog.text = DLG_TEXT_Q[40];
    		link.l1 = DLG_TEXT_Q[41];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		group_DeleteGroup("Ascold_Spa_Attack");
    		DeleteAttribute(PChar, "questTemp.Ascold.Ship");
		break;

 		case "Step_10":
        	dialog.text = DLG_TEXT_Q[42]+
                          DLG_TEXT_Q[43];
    		link.l1 = DLG_TEXT_Q[44];
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "SeekThreeObject";
    	    NextDiag.TempNode = "ResultOfSeek";
            AddQuestRecord("Ascold", "3");
		break;

 		case "ResultOfSeek":
        	dialog.text = DLG_TEXT_Q[45];
    		link.l1 = DLG_TEXT_Q[46];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "ResultOfSeek";
            if (CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21"))
            {
                link.l2 = DLG_TEXT_Q[47];
                link.l2.go = "Step_11";
            }
		break;

 		case "Step_11":
        	dialog.text = DLG_TEXT_Q[48];
            link.l1 = DLG_TEXT_Q[49];
            if (pchar.questTemp.Ascold == "SoughtThreeObject")
            {
               link.l1 = DLG_TEXT_Q[50];
            }
    		link.l1.go = "Step_12";
            link.l2 = DLG_TEXT_Q[51];
    		link.l2.go = "WantMoreMoney";
		break;

 		case "WantMoreMoney":
        	dialog.text = DLG_TEXT_Q[52]+
                          DLG_TEXT_Q[53];
        	link.l1 = DLG_TEXT_Q[54];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_12":
        	dialog.text = DLG_TEXT_Q[55];
        	link.l1 = DLG_TEXT_Q[56];
    		link.l1.go = "Step_13";
		break;

 		case "Step_13":
        	dialog.text = DLG_TEXT_Q[57];
    		link.l1 = DLG_TEXT_Q[58];
    		link.l1.go = "exit";
    		TakeItemFromCharacter(pchar, "indian19");
    		TakeItemFromCharacter(pchar, "indian20");
    		TakeItemFromCharacter(pchar, "indian21");
    		AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "WalkTwoMounth";
    		AddQuestRecord("Ascold", "4");
		break;

		case "WalkTwoMounth":
		    if (GetQuestPastDayParam("questTemp.Ascold") > 62)
		    {
            	dialog.text = DLG_TEXT_Q[59] + GetFullName(pchar) + ".";
            	link.l1 = DLG_TEXT_Q[60];
        		link.l1.go = "Step_14";
		    }
            else
            {
            	dialog.text = DLG_TEXT_Q[61] + GetFullName(pchar) + DLG_TEXT_Q[62];
            	link.l1 = DLG_TEXT_Q[63];
        		link.l1.go = "exit";
        		NextDiag.TempNode = "WalkTwoMounth";
            }
		break;
		
 		case "Step_14":
        	dialog.text = DLG_TEXT_Q[64];
        	link.l1 = DLG_TEXT_Q[65];
    		link.l1.go = "Step_15";
		break;

 		case "Step_15":
        	dialog.text = DLG_TEXT_Q[66]+
                          DLG_TEXT_Q[67]+
                          DLG_TEXT_Q[68]+
                          DLG_TEXT_Q[69];
        	link.l1 = DLG_TEXT_Q[70];
    		link.l1.go = "Step_16";
        	link.l2 = DLG_TEXT_Q[71];
    		link.l2.go = "No_Work";
		break;

 		case "Step_16":
        	dialog.text = DLG_TEXT_Q[72];
        	link.l1 = DLG_TEXT_Q[73];
    		link.l1.go = "exit";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "AfterManowarsBattle";
    		pchar.questTemp.Ascold = "ToHavanna";
    		AddQuestRecord("Ascold", "5");
		break;
		
 		case "AfterManowarsBattle":
        	dialog.text = DLG_TEXT_Q[74];
        	link.l1 = DLG_TEXT_Q[75];
    		link.l1.go = "exit";
        	link.l2 = DLG_TEXT_Q[76];
    		link.l2.go = "No_Work";
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
            {
             	link.l1 = DLG_TEXT_Q[77];
        		link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
             	link.l1 = DLG_TEXT_Q[78];
        		link.l1.go = "Step_20";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[79];
        		link.l1.go = "Step_24";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[80];
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[81];
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[82];
        		link.l1.go = "NoFoundList";
            }
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "ILookedThisAss")
    		{
            	link.l1 = DLG_TEXT_Q[83];
        		link.l1.go = "Step_26";
    		}
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "2ILookedThisAss")
    		{
            	link.l1 = DLG_TEXT_Q[84];
        		link.l1.go = "Step_26";
    		}
            if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
            {
             	link.l1 = DLG_TEXT_Q[85];
        		link.l1.go = "ManowarGoodWork";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = DLG_TEXT_Q[86];
        		link.l1.go = "ManowarGoodWork";
            }
		break;

 		case "Step_17":
        	dialog.text = DLG_TEXT_Q[87];
        	link.l1 = DLG_TEXT_Q[88];
    		link.l1.go = "Step_18";
		break;

 		case "Step_18":
        	dialog.text = DLG_TEXT_Q[89];
        	link.l1 = DLG_TEXT_Q[90];
    		link.l1.go = "Step_19";
		break;

 		case "Step_19":
        	dialog.text = DLG_TEXT_Q[91];
        	link.l1 = DLG_TEXT_Q[92];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2SeekInformatorHavanna";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_20":
        	dialog.text = DLG_TEXT_Q[93];
        	link.l1 = DLG_TEXT_Q[94];
    		link.l1.go = "Step_21";
		break;

 		case "Step_21":
        	dialog.text = DLG_TEXT_Q[95];
        	link.l1 = DLG_TEXT_Q[96];
    		link.l1.go = "Step_22";
		break;

 		case "Step_22":
        	dialog.text = DLG_TEXT_Q[97]+
                          DLG_TEXT_Q[98];
        	link.l1 = DLG_TEXT_Q[99];
    		link.l1.go = "Step_23";
        	link.l2 = DLG_TEXT_Q[100];
    		link.l2.go = "No_Work";
		break;

 		case "Step_23":
        	dialog.text = DLG_TEXT_Q[101];
        	link.l1 = DLG_TEXT_Q[102];
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "8");
    		pchar.questTemp.Ascold = "IMustKillAll";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_24":
        	dialog.text = DLG_TEXT_Q[103];
        	link.l1 = DLG_TEXT_Q[104];
    		link.l1.go = "Step_25";
            link.l2 = DLG_TEXT_Q[105];
    		link.l2.go = "No_Work";
		break;

 		case "Step_25":
        	dialog.text = DLG_TEXT_Q[106];
        	link.l1 = DLG_TEXT_Q[107];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2ILookedThisAss";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "NoFoundList":
        	dialog.text = DLG_TEXT_Q[108]+
                      DLG_TEXT_Q[109];
    		link.l1 = DLG_TEXT_Q[110];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_26":
        	dialog.text = DLG_TEXT_Q[111];
        	link.l1 = DLG_TEXT_Q[112];
    		link.l1.go = "Step_27";
            link.l2 = DLG_TEXT_Q[113];
    		link.l2.go = "No_Work";
            link.l3 = DLG_TEXT_Q[114];
    		link.l3.go = "WantMoreMoney";
            BackItemDescribe("ShipsJournal");
            TakeItemFromCharacter(pchar, "ShipsJournal");
            pchar.questTemp.Ascold.list = 1;
		break;

 		case "Step_27":
        	dialog.text = DLG_TEXT_Q[115];
        	link.l1 = DLG_TEXT_Q[116];
    		link.l1.go = "exit";
            AddQuestRecord("Ascold", "10");
		break;

 		case "ManowarGoodWork":
        	dialog.text = DLG_TEXT_Q[117];
        	link.l1 = DLG_TEXT_Q[118];
    		link.l1.go = "exit";
            link.l2 = DLG_TEXT_Q[119];
    		link.l2.go = "Step_28";
    		NextDiag.TempNode = "ManowarGoodWork";
		break;

 		case "Step_28":
        	dialog.text = DLG_TEXT_Q[120];
        	link.l1 = DLG_TEXT_Q[121];
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		pchar.quest.Ascold_FightNearTemple.over = "yes";
		break;

 		case "Ascold_KilledTemple":
        	dialog.text = DLG_TEXT_Q[122];
        	link.l1 = DLG_TEXT_Q[123];
    		link.l1.go = "NoFoundList";
            if (CheckCharacterItem(pchar, "ShipsJournal") || CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
            	link.l1 = DLG_TEXT_Q[124];
        		link.l1.go = "Step_29";
                BackItemDescribe("ShipsJournal");
                TakeItemFromCharacter(pchar, "ShipsJournal");
                DeleteAttribute(PChar, "questTemp.Ascold.List");
            }
		break;
		
 		case "Step_29":
        	dialog.text = DLG_TEXT_Q[125];
        	link.l1 = DLG_TEXT_Q[126];
    		link.l1.go = "Step_30";
		break;

 		case "Step_30":
        	dialog.text = DLG_TEXT_Q[127];
        	link.l1 = DLG_TEXT_Q[128];
    		link.l1.go = "Step_31";
		break;

 		case "Step_31":
        	dialog.text = DLG_TEXT_Q[129];
        	link.l1 = DLG_TEXT_Q[130];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		AddQuestRecord("Ascold", "12");
		break;

 		case "Mummie_begin":
        	dialog.text = DLG_TEXT_Q[131]+ GetFullName(pchar) + DLG_TEXT_Q[132];
        	link.l1 = DLG_TEXT_Q[133];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
		    if (GetQuestPastDayParam("questTemp.Ascold") > 40)
            {
            	dialog.text = DLG_TEXT_Q[134]+ GetFullName(pchar) + "...";
            	link.l1 = DLG_TEXT_Q[135];
        		link.l1.go = "Step_31A";
            }
		break;

 		case "Step_31A":
        	dialog.text = DLG_TEXT_Q[136];
        	link.l1 = DLG_TEXT_Q[137];
    		link.l1.go = "Step_32";
		break;

 		case "Step_32":
        	dialog.text = DLG_TEXT_Q[138];
        	link.l1 = DLG_TEXT_Q[139];
    		link.l1.go = "Step_33";
        break;

        case "Step_33":
        	dialog.text = DLG_TEXT_Q[140];
        	link.l1 = DLG_TEXT_Q[141];
    		link.l1.go = "Step_34";
            link.l2 = DLG_TEXT_Q[142];
    		link.l2.go = "No_Work";
		break;

 		case "Step_34":
        	dialog.text = DLG_TEXT_Q[143]+
                          DLG_TEXT_Q[144];
        	link.l1 = DLG_TEXT_Q[145];
    		link.l1.go = "Step_35";
        	link.l2 = DLG_TEXT_Q[146];
    		link.l2.go = "No_Work";
		break;
		
 		case "Step_35":
        	dialog.text = DLG_TEXT_Q[147];
        	link.l1 = DLG_TEXT_Q[148];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
    		AddQuestRecord("Ascold", "13");
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "Ascold_SeekGrave";
		break;

 		case "Seek_Grave":
        	dialog.text = DLG_TEXT_Q[149];
        	link.l1 = DLG_TEXT_Q[150];
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
            if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
            {
            	dialog.text = DLG_TEXT_Q[151];
            	link.l1 = DLG_TEXT_Q[152];
        		link.l1.go = "Step_36";
            }
            if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
            {
            	dialog.text = DLG_TEXT_Q[153];
            	link.l1 = DLG_TEXT_Q[154];
        		link.l1.go = "Step_37";
            }
            if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
            {
            	dialog.text = DLG_TEXT_Q[155];
            	link.l1 = DLG_TEXT_Q[156];
        		link.l1.go = "Step_38";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && !CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = DLG_TEXT_Q[157];
            	link.l1 = DLG_TEXT_Q[158];
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = DLG_TEXT_Q[159];
            	link.l1 = DLG_TEXT_Q[160];
        		link.l1.go = "Step_45";
            }
            if (pchar.questTemp.Ascold == "Ascold_EnterGrave")
            {
            	dialog.text = DLG_TEXT_Q[161];
            	link.l1 = DLG_TEXT_Q[162];
        		link.l1.go = "exit";
            }
		break;
		
 		case "Step_36":
        	dialog.text = DLG_TEXT_Q[163]+
                          DLG_TEXT_Q[164];
        	link.l1 = DLG_TEXT_Q[165];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;
		
 		case "Step_37":
        	dialog.text = DLG_TEXT_Q[166];
        	link.l1 = DLG_TEXT_Q[167];
    		link.l1.go = "exit";
		break;

 		case "Step_38":
        	dialog.text = DLG_TEXT_Q[168]+
                          DLG_TEXT_Q[169];
        	link.l1 = DLG_TEXT_Q[170];
    		link.l1.go = "Step_40";
		break;
		
 		case "Step_40":
        	dialog.text = DLG_TEXT_Q[171]+
                          DLG_TEXT_Q[172]+
                          DLG_TEXT_Q[173];
        	link.l1 = DLG_TEXT_Q[174];
    		link.l1.go = "Step_41";
		break;

 		case "Step_41":
        	dialog.text = DLG_TEXT_Q[175]+
                          DLG_TEXT_Q[176]+
                          DLG_TEXT_Q[177];
        	link.l1 = DLG_TEXT_Q[178];
    		link.l1.go = "Step_42";
		break;

 		case "Step_42":
        	dialog.text = DLG_TEXT_Q[179];
        	link.l1 = DLG_TEXT_Q[180];
    		link.l1.go = "Step_43";
		break;
		
 		case "Step_43":
        	dialog.text = DLG_TEXT_Q[181]+
                          DLG_TEXT_Q[182];
        	link.l1 = DLG_TEXT_Q[183];
    		link.l1.go = "Step_44";
        	link.l2 = DLG_TEXT_Q[184];
    		link.l2.go = "No_Work";
		break;

 		case "Step_44":
        	dialog.text = DLG_TEXT_Q[185];
        	link.l1 = DLG_TEXT_Q[186];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
            // ==> Делаем скрижали видимыми, теперь их можно найти.
            sld = ItemsFromID("Rock_letter");
            sld.shown = 1;
		break;

 		case "Step_45":
        	dialog.text = DLG_TEXT_Q[187];
        	link.l1 = DLG_TEXT_Q[188];
    		link.l1.go = "exit";
			bDisableLandEncounters = true; //закроем энкаунтеров, лучше раньше, чем баги.
    		pchar.questTemp.Ascold = "Ascold_EnterGrave";
		break;
		
 		case "Found_Grave":
            if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
            {
            	dialog.text = DLG_TEXT_Q[189] + GetFullName(pchar) + DLG_TEXT_Q[190];
            	link.l1 = DLG_TEXT_Q[191];
        		link.l1.go = "Step_46";
            }
		break;
		
 		case "Step_46":
        	dialog.text = DLG_TEXT_Q[192];
        	link.l1 = DLG_TEXT_Q[193];
    		link.l1.go = "Step_47";
		break;
		
 		case "Step_47":
        	dialog.text = DLG_TEXT_Q[194];
        	link.l1 = DLG_TEXT_Q[195];
    		link.l1.go = "Step_48";
		break;
		
 		case "Step_48":
        	dialog.text = DLG_TEXT_Q[196]+
                          DLG_TEXT_Q[197];
        	link.l1 = DLG_TEXT_Q[198];
    		link.l1.go = "Step_49";
		break;
		
 		case "Step_49":
        	dialog.text = DLG_TEXT_Q[199];
        	link.l1 = DLG_TEXT_Q[200];
    		link.l1.go = "Step_50";
		break;

 		case "Step_50":
        	dialog.text = DLG_TEXT_Q[201];
        	link.l1 = DLG_TEXT_Q[202];
    		link.l1.go = "Step_51";
		break;

 		case "Step_51":
        	dialog.text = DLG_TEXT_Q[203];
           	link.l1 = DLG_TEXT_Q[204];
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_WateringMummy";
    		GiveItem2Character(Pchar,"Ascold_rabble");
		break;

 		case "AfterAttackMummy":
        	dialog.text = DLG_TEXT_Q[205];
        	link.l1 = DLG_TEXT_Q[206];
    		link.l1.go = "Step_52";
            if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
            {
            	dialog.text = DLG_TEXT_Q[207];
            	link.l1 = DLG_TEXT_Q[208];
        		link.l1.go = "exit";
                NextDiag.TempNode = "AfterAttackMummy";
            }
            if (GetCharacterIndex("LeifEricson") == -1)
            {
            	dialog.text = DLG_TEXT_Q[209];
            	link.l1 = DLG_TEXT_Q[210];
        		link.l1.go = "Step_60";
            }
		break;

 		case "Step_52":
        	dialog.text = DLG_TEXT_Q[211]+
                          DLG_TEXT_Q[212];
        	link.l1 = DLG_TEXT_Q[213];
    		link.l1.go = "Step_53";
		break;

 		case "Step_53":
        	dialog.text = DLG_TEXT_Q[214];
        	link.l1 = DLG_TEXT_Q[215];
    		link.l1.go = "Step_54";
		break;

 		case "Step_54":
        	dialog.text = DLG_TEXT_Q[216]+
                          DLG_TEXT_Q[217];
        	link.l1 = DLG_TEXT_Q[218];
    		link.l1.go = "Step_55";
		break;

 		case "Step_55":
        	dialog.text = DLG_TEXT_Q[219];
        	link.l1 = DLG_TEXT_Q[220];
    		link.l1.go = "Step_56";
		break;

 		case "Step_56":
        	dialog.text = DLG_TEXT_Q[221]+
                          DLG_TEXT_Q[222];
        	link.l1 = DLG_TEXT_Q[223];
    		link.l1.go = "Step_57";
		break;

 		case "Step_57":
        	dialog.text = DLG_TEXT_Q[224];
        	link.l1 = DLG_TEXT_Q[225];
    		link.l1.go = "Step_58";
		break;

 		case "Step_58":
        	dialog.text = DLG_TEXT_Q[226]+
                          DLG_TEXT_Q[227];
        	link.l1 = DLG_TEXT_Q[228];
    		link.l1.go = "Step_59";
		break;

 		case "Step_59":
        	dialog.text = DLG_TEXT_Q[229];
        	link.l1 = DLG_TEXT_Q[230];
    		link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
    		pchar.questTemp.Ascold = "Ascold_SaveWorld";
			sld = characterFromId("LeifEricson");
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		break;

 		case "Step_60":
        	dialog.text = DLG_TEXT_Q[231]+
                          DLG_TEXT_Q[232];
        	link.l1 = DLG_TEXT_Q[233];
    		link.l1.go = "Step_61";
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
            	link.l2 = DLG_TEXT_Q[234];
        		link.l2.go = "Step_63";				
            }
		break;

 		case "Step_61":
        	dialog.text = DLG_TEXT_Q[235]+
                          DLG_TEXT_Q[236];
        	link.l1 = DLG_TEXT_Q[237];
    		link.l1.go = "Step_62";
		break;

 		case "Step_62":
        	dialog.text = DLG_TEXT_Q[238];
        	link.l1 = DLG_TEXT_Q[239];
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            pchar.questTemp.Ascold = "Ascold_OverBusiness";
		break;

 		case "GoodFriends":
        	dialog.text = DLG_TEXT_Q[240] + GetFullName(pchar) + DLG_TEXT_Q[241];
        	link.l1 = DLG_TEXT_Q[242];
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
            	link.l1 = DLG_TEXT_Q[243];
        		link.l1.go = "Step_64";
            }
		break;

 		case "Step_63":
        	dialog.text = DLG_TEXT_Q[244];
        	link.l1 = DLG_TEXT_Q[245];
    		link.l1.go = "BuyAzzy";
        	link.l2 = DLG_TEXT_Q[246];
    		link.l2.go = "Step_62";
		break;

 		case "BuyAzzy":
        	dialog.text = DLG_TEXT_Q[247];
        	link.l1 = DLG_TEXT_Q[248];
    		link.l1.go = "Step_62";
            TakeItemFromCharacter(pchar, "Azzy_bottle");
            AddMoneyToCharacter(pchar, 50000);
		break;
		
 		case "Step_64":
        	dialog.text = DLG_TEXT_Q[249];
        	link.l1 = DLG_TEXT_Q[250];
    		link.l1.go = "Step_65";
		break;
		
 		case "Step_65":
        	dialog.text = DLG_TEXT_Q[251];
        	link.l1 = DLG_TEXT_Q[252];
    		link.l1.go = "Step_66";
		break;

 		case "Step_66":
        	dialog.text = DLG_TEXT_Q[253];
        	link.l1 = DLG_TEXT_Q[254];
    		link.l1.go = "Step_67";
		break;

 		case "Step_67":
        	dialog.text = DLG_TEXT_Q[255];
        	link.l1 = DLG_TEXT_Q[256];
    		link.l1.go = "Step_68";
		break;

 		case "Step_68":
        	dialog.text = DLG_TEXT_Q[257];
        	link.l1 = DLG_TEXT_Q[258];
    		link.l1.go = "Step_69";
		break;

 		case "Step_69":
        	dialog.text = DLG_TEXT_Q[259];
        	link.l1 = DLG_TEXT_Q[260];
    		link.l1.go = "Step_70";
		break;

 		case "Step_70":
           	dialog.text = DLG_TEXT_Q[261];
        	link.l1 = DLG_TEXT_Q[262];
    		link.l1.go = "exit";
            pchar.questTemp.Azzy = "DestrContract";
        	if (sti(pchar.questTemp.Azzy.Immortal.Penalty) >= 15 && GetQuestPastDayParam("questTemp.Azzy") > 90)
        	{
                dialog.text = DLG_TEXT_Q[263];
                link.l1 = DLG_TEXT_Q[264];
                link.l1.go = "Step_71";
            }
		break;
		
 		case "Step_71":
        	dialog.text = DLG_TEXT_Q[265];
        	link.l1 = DLG_TEXT_Q[266];
    		link.l1.go = "Step_72";
            GiveItem2Character(pchar, "sculMa1");
            GiveItem2Character(pchar, "sculMa2");
            GiveItem2Character(pchar, "sculMa3");
            GiveItem2Character(pchar, "indian22");
		break;

 		case "Step_72":
        	dialog.text = DLG_TEXT_Q[267];
        	link.l1 = DLG_TEXT_Q[268];
    		link.l1.go = "exit";
		break;
	}
}


