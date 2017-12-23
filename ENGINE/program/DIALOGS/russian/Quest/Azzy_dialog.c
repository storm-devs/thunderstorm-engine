#include "TEXT\DIALOGS\Quest\Azzy_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			Dialog.CurrentNode = "AngryQuest";
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	
    
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
        	dialog.text = DLG_TEXT_Q[0] + GetFullName(pchar) + DLG_TEXT_Q[1];
    		link.l1 = DLG_TEXT_Q[2] + XI_ConvertString("Colony"+pchar.questTemp.Ascold.ShipyarderColony+"Gen") + DLG_TEXT_Q[3];
    		link.l1.go = "Step_1";
		break;

		case "Step_1":
        	dialog.text = DLG_TEXT_Q[4]+
                          DLG_TEXT_Q[5]+
                          DLG_TEXT_Q[6];
    		link.l1 = DLG_TEXT_Q[7];
    		link.l1.go = "Step_2";
		break;

		case "Step_2":
        	dialog.text = DLG_TEXT_Q[8]+
                          DLG_TEXT_Q[9];
       		link.l1 = DLG_TEXT_Q[10];
    		link.l1.go = "Step_3";
		break;

		case "Step_3":
        	dialog.text = DLG_TEXT_Q[11];
    		link.l1 = DLG_TEXT_Q[12];
    		link.l1.go = "Step_4";
		break;

		case "Step_4":
        	dialog.text = DLG_TEXT_Q[13]+
                          DLG_TEXT_Q[14]+
                          DLG_TEXT_Q[15];
    		link.l1 = DLG_TEXT_Q[16];
    		link.l1.go = "Step_5";
		break;

		case "Step_5":
        	dialog.text = DLG_TEXT_Q[17]+
                          DLG_TEXT_Q[18]+
                          DLG_TEXT_Q[19]+
                          DLG_TEXT_Q[20]+
                          DLG_TEXT_Q[21];
    		link.l1 = DLG_TEXT_Q[22];
    		link.l1.go = "Step_6";
		break;

		case "Step_6":
        	dialog.text = DLG_TEXT_Q[23]+
                          DLG_TEXT_Q[24]+
                          DLG_TEXT_Q[25];
    		link.l1 = DLG_TEXT_Q[26];
    		link.l1.go = "Step_7";
		break;

		case "Step_7":
        	dialog.text = DLG_TEXT_Q[27]+
                          DLG_TEXT_Q[28]+
                          DLG_TEXT_Q[29]+
                          DLG_TEXT_Q[30];
    		link.l1 = DLG_TEXT_Q[31];
    		link.l1.go = "Step_8";
		break;

		case "Step_8":
        	dialog.text = DLG_TEXT_Q[32];
    		link.l1 = DLG_TEXT_Q[33];
    		link.l1.go = "Step_9";
		break;

		case "Step_9":
        	dialog.text = DLG_TEXT_Q[34];
    		link.l1 = DLG_TEXT_Q[35];
    		link.l1.go = "Step_10";
		break;
		
		case "Step_10":
        	dialog.text = DLG_TEXT_Q[36]+
                          DLG_TEXT_Q[37]+
                          DLG_TEXT_Q[38];
    		link.l1 = DLG_TEXT_Q[39];
    		link.l1.go = "Step_11";
		break;

		case "Step_11":
        	dialog.text = DLG_TEXT_Q[40];
    		link.l1 = DLG_TEXT_Q[41];
    		link.l1.go = "Step_12";
		break;

		case "Step_12":
        	dialog.text = DLG_TEXT_Q[42]+
                          DLG_TEXT_Q[43]+
                          DLG_TEXT_Q[44];
    		link.l1 = DLG_TEXT_Q[45];
    		link.l1.go = "Step_13";
		break;

		case "Step_13":
        	dialog.text = DLG_TEXT_Q[46]+
                          DLG_TEXT_Q[47]+
                          DLG_TEXT_Q[48];
    		link.l1 = DLG_TEXT_Q[49];
    		link.l1.go = "Step_14";
		break;
		
		case "Step_14":
        	dialog.text = DLG_TEXT_Q[50]+
                          DLG_TEXT_Q[51];
    		link.l1 = DLG_TEXT_Q[52];
    		link.l1.go = "Step_15";
		break;
		
		case "Step_15":
        	dialog.text = DLG_TEXT_Q[53]+
                          DLG_TEXT_Q[54]+
                          DLG_TEXT_Q[55];
        	link.l1 = DLG_TEXT_Q[56];
    		link.l1.go = "Wishes";
		break;

		case "Wishes":
            dialog.text = LinkRandPhrase(DLG_TEXT_Q[57], DLG_TEXT_Q[58] , DLG_TEXT_Q[59]);
    		link.l1 = DLG_TEXT_Q[60];
    		link.l1.go = "ToKillEnemy";
    		link.l2 = DLG_TEXT_Q[61];
    		link.l2.go = "ToGiveMoney";
    		link.l4 = DLG_TEXT_Q[62];
    		link.l4.go = "ToGiveRum";
    		link.l5 = DLG_TEXT_Q[63];
    		link.l5.go = "ToShip";
    		link.l6 = DLG_TEXT_Q[64];
    		link.l6.go = "ToImmortal";
    		link.l7 = DLG_TEXT_Q[65];
    		link.l7.go = "ToGovernor";
    		link.l8 = DLG_TEXT_Q[66];
    		link.l8.go = "ToAddSpecial";
    		link.l9 = DLG_TEXT_Q[67];
    		link.l9.go = "ToEnd";
		break;

		case "ToKillEnemy":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[68],
                                           DLG_TEXT_Q[69],
                                           DLG_TEXT_Q[70],
                                           DLG_TEXT_Q[71], "quest", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[72], DLG_TEXT_Q[73], DLG_TEXT_Q[74], DLG_TEXT_Q[75], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_16", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_16":
        	dialog.text = DLG_TEXT_Q[76] + GetFullName(pchar) + DLG_TEXT_Q[77];
    		link.l1 = DLG_TEXT_Q[78];
    		link.l1.go = "Step_17";
		break;

    	case "Step_17":
        	dialog.text = DLG_TEXT_Q[79]+
                          DLG_TEXT_Q[80]+
                          DLG_TEXT_Q[81];
    		link.l1 = DLG_TEXT_Q[82];
    		link.l1.go = "Step_18";
		break;

		case "Step_18":
        	dialog.text = DLG_TEXT_Q[83]+
                          DLG_TEXT_Q[84]+
                          DLG_TEXT_Q[85]+
						  DLG_TEXT_Q[86]+
                          DLG_TEXT_Q[87];
    		link.l1 = DLG_TEXT_Q[88];
    		link.l1.go = "Step_19";
		break;

		case "Step_19":
        	dialog.text = DLG_TEXT_Q[89]+
                          DLG_TEXT_Q[90]+
                          DLG_TEXT_Q[91];
    		link.l1 = DLG_TEXT_Q[92];
    		link.l1.go = "Wishes";
		break;

		case "ToGiveMoney":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[93], DLG_TEXT_Q[94], DLG_TEXT_Q[95], DLG_TEXT_Q[96], "quest", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[97], DLG_TEXT_Q[98], DLG_TEXT_Q[99], DLG_TEXT_Q[100], npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("Step_20", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_20":
        	dialog.text = DLG_TEXT_Q[101]+
                          DLG_TEXT_Q[102];
    		link.l1 = DLG_TEXT_Q[103];
    		link.l1.go = "Step_21";
		break;

		case "Step_21":
        	dialog.text = DLG_TEXT_Q[104]+
                          DLG_TEXT_Q[105] + GetFullName(characterFromId("Charles_usurer")) + DLG_TEXT_Q[106];
    		link.l1 = DLG_TEXT_Q[107];
    		link.l1.go = "Step_22";
    		pchar.questTemp.Azzy.GiveMoney = 1;
		break;

		case "Step_22":
        	dialog.text = DLG_TEXT_Q[108]+
                          DLG_TEXT_Q[109]+
                          DLG_TEXT_Q[110];
    		link.l1 = DLG_TEXT_Q[111];
    		link.l1.go = "Wishes";
		break;

		case "ToGovernor":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[112],
                                                  DLG_TEXT_Q[113],
                                                  DLG_TEXT_Q[114],
                                                  DLG_TEXT_Q[115], "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[116], DLG_TEXT_Q[117], DLG_TEXT_Q[118], DLG_TEXT_Q[119], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_25", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;
		
		case "Step_25":
        	dialog.text = DLG_TEXT_Q[120];
    		link.l1 = DLG_TEXT_Q[121];
    		link.l1.go = "Step_26";
		break;

		case "Step_26":
        	dialog.text = DLG_TEXT_Q[122];
    		link.l1 = DLG_TEXT_Q[123];
    		link.l1.go = "Step_27";
		break;

		case "Step_27":
        	dialog.text = DLG_TEXT_Q[124]+
                          DLG_TEXT_Q[125]+
                          DLG_TEXT_Q[126]+
                          DLG_TEXT_Q[127]+
                          DLG_TEXT_Q[128];
    		link.l1 = DLG_TEXT_Q[129];
    		link.l1.go = "Step_28";
		break;

		case "Step_28":
        	dialog.text = DLG_TEXT_Q[130];
    		link.l1 = DLG_TEXT_Q[131];
    		link.l1.go = "Wishes";
		break;
		
		case "ToImmortal":
        	dialog.text = dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[132],
                                    DLG_TEXT_Q[133],
                                    DLG_TEXT_Q[134],
                                    DLG_TEXT_Q[135], "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[136], DLG_TEXT_Q[137], DLG_TEXT_Q[138], DLG_TEXT_Q[139], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_29", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_29":
        	dialog.text = DLG_TEXT_Q[140]+
                          DLG_TEXT_Q[141];
    		link.l1 = DLG_TEXT_Q[142];
    		link.l1.go = "Step_30";
		break;

		case "Step_30":
        	dialog.text = DLG_TEXT_Q[143]+
                          DLG_TEXT_Q[144];
    		link.l1 = DLG_TEXT_Q[145];
    		link.l1.go = "Step_31";
		break;

		case "Step_31":
        	dialog.text = DLG_TEXT_Q[146]+
                          DLG_TEXT_Q[147];
    		link.l1 = DLG_TEXT_Q[148];
    		link.l1.go = "Step_32";
		break;
		
		case "Step_32":
        	dialog.text = DLG_TEXT_Q[149]+
                          DLG_TEXT_Q[150];
    		link.l1 = DLG_TEXT_Q[151];
    		link.l1.go = "Step_33";
		break;

		case "Step_33":
        	dialog.text = DLG_TEXT_Q[152]+
                          DLG_TEXT_Q[153];
    		link.l1 = DLG_TEXT_Q[154];
    		link.l1.go = "Step_34";
		break;

		case "Step_34":
        	dialog.text = DLG_TEXT_Q[155]+
                          DLG_TEXT_Q[156];
    		link.l1 = DLG_TEXT_Q[157];
    		link.l1.go = "Step_35";
		break;

		case "Step_35":
        	dialog.text = DLG_TEXT_Q[158]+
                          DLG_TEXT_Q[159]+
                          DLG_TEXT_Q[160];
    		link.l1 = DLG_TEXT_Q[161];
    		link.l1.go = "Step_36";
    		link.l2 = DLG_TEXT_Q[162];
    		link.l2.go = "Wishes";
		break;

		case "Step_36":
        	dialog.text = DLG_TEXT_Q[163]+
                          DLG_TEXT_Q[164] + GetFullName(pchar) + DLG_TEXT_Q[165];
    		link.l1 = DLG_TEXT_Q[166] + GetFullName(pchar) + DLG_TEXT_Q[167];
    		link.l1.go = "Step_37";
		break;

		case "Step_37":
        	dialog.text = DLG_TEXT_Q[168]+
                          DLG_TEXT_Q[169];
    		link.l1 = DLG_TEXT_Q[170];
    		link.l1.go = "Wishes";
    		LAi_SetImmortal(pchar, true);
            SetQuestHeader("ContractWithHell");
            AddQuestRecord("ContractWithHell", "1");
			AddQuestUserData("ContractWithHell", "Conrtragent", GetFullName(pchar));
            pchar.questTemp.Azzy.Immortal = 1;
            SaveCurrentQuestDateParam("questTemp.Azzy");
            SaveCurrentQuestDateParam("questTemp.Azzy.Immortal");
            pchar.questTemp.Azzy.Immortal.AllQuota = 0;
            pchar.questTemp.Azzy.Immortal.DayQuota = 3; //ежедневный норматив
            pchar.questTemp.Azzy.Immortal.CurBalance = 0;
            pchar.questTemp.Azzy.Immortal.CurKilled = 0;
            pchar.questTemp.Azzy.Immortal.Penalty = 0;
            pchar.questTemp.Azzy.Immortal.EarlyKilled = Statistic_AddValue(PChar, "Solder_s", 0) +
                                                 Statistic_AddValue(PChar, "Solder_g", 0) +
                                                 Statistic_AddValue(PChar, "Warrior_s", 0) +
                                    	         Statistic_AddValue(PChar, "Warrior_g", 0) +
                                    	         Statistic_AddValue(PChar, "Citizen_s", 0) +
                                    	         Statistic_AddValue(PChar, "Citizen_g", 0) +
                                    	         Statistic_AddValue(PChar, "Monster_s", 0) +
                                    	         Statistic_AddValue(PChar, "Monster_g", 0);
            AddQuestRecord("Azzy_HellSign", "1");
			AddQuestUserData("Azzy_HellSign", "sName", GetMainCharacterNameGen());
			AddQuestUserData("Azzy_HellSign", "DayQuota", pchar.questTemp.Azzy.Immortal.DayQuota);
			AddQuestUserData("Azzy_HellSign", "AllQuota", pchar.questTemp.Azzy.Immortal.AllQuota);
			AddQuestUserData("Azzy_HellSign", "CurKilled", pchar.questTemp.Azzy.Immortal.CurKilled);
			AddQuestUserData("Azzy_HellSign", "CurBalance", pchar.questTemp.Azzy.Immortal.CurBalance);
		break;

		case "ToGiveRum":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[171],
                                    DLG_TEXT_Q[172],
                                    DLG_TEXT_Q[173],
                                    DLG_TEXT_Q[174], "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[175], DLG_TEXT_Q[176], DLG_TEXT_Q[177], DLG_TEXT_Q[178], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_38", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_38":
        	dialog.text = DLG_TEXT_Q[179] + GetFullName(characterFromId("PortPax_trader")) + ".";
    		link.l1 = DLG_TEXT_Q[180];
    		link.l1.go = "Step_39";
    		pchar.questTemp.Azzy.GiveRum = 1;
		break;

		case "Step_39":
        	dialog.text = DLG_TEXT_Q[181];
    		link.l1 = DLG_TEXT_Q[182];
    		link.l1.go = "Wishes";
		break;

		case "ToAddSpecial":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[183],
                                    DLG_TEXT_Q[184],
                                    DLG_TEXT_Q[185],
                                    DLG_TEXT_Q[186], "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[187], DLG_TEXT_Q[188], DLG_TEXT_Q[189], DLG_TEXT_Q[190], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_40", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_40":
        	dialog.text = DLG_TEXT_Q[191];
    		link.l1 = DLG_TEXT_Q[192];
    		link.l1.go = "Wishes";
    		pchar.questTemp.Azzy.AddSpecial = 1;
		break;

		case "ToShip":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[193],
                                    DLG_TEXT_Q[194],
                                    DLG_TEXT_Q[195],
                                    DLG_TEXT_Q[196], "quest", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[197], DLG_TEXT_Q[198], DLG_TEXT_Q[199], DLG_TEXT_Q[200], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_41", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_41":
        	dialog.text = DLG_TEXT_Q[201];
    		link.l1 = DLG_TEXT_Q[202];
    		link.l1.go = "Step_42";
		break;

		case "Step_42":
        	dialog.text = DLG_TEXT_Q[203]+
                          DLG_TEXT_Q[204];
    		link.l1 = DLG_TEXT_Q[205];
    		link.l1.go = "Step_43";
		break;

		case "Step_43":
        	dialog.text = DLG_TEXT_Q[206]+
                          DLG_TEXT_Q[207]+
                          DLG_TEXT_Q[208];
    		link.l1 = DLG_TEXT_Q[209];
    		link.l1.go = "Wishes";
            if (CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
		    {
            	dialog.text = DLG_TEXT_Q[210];
        		link.l1 = DLG_TEXT_Q[211];
		    }
		break;

		case "ToEnd":
        	dialog.text = DLG_TEXT_Q[212]+
                          DLG_TEXT_Q[213]+
                          DLG_TEXT_Q[214];
    		link.l1 = DLG_TEXT_Q[215];
    		link.l1.go = "Back_Exit";
		break;

 		case "Back_Exit":
            LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    DoReloadCharacterToLocation(pchar.questTemp.Ascold.ShipyarderColony + "_Shipyard", "reload", "reload2");
 		    LAi_SetPlayerType(PChar);
 		    NextDiag.TempNode = "Second time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "Azzy_Exit":
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    LAi_SetPlayerType(PChar);
 		    NextDiag.TempNode = "Death";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Second time":
        	dialog.text = DLG_TEXT_Q[216] + GetFullName(pchar) + DLG_TEXT_Q[217];
    		link.l1 = DLG_TEXT_Q[218];
    		link.l1.go = "Step_44";
		break;

		case "Step_44":
        	dialog.text = DLG_TEXT_Q[219];
    		link.l1 = DLG_TEXT_Q[220];
    		link.l1.go = "Step_45";
		break;

		case "Step_45":
        	dialog.text = DLG_TEXT_Q[221];
    		link.l1 = DLG_TEXT_Q[222];
    		link.l1.go = "Step_46";
		break;

		case "Step_46":
        	dialog.text = DLG_TEXT_Q[223];
    		link.l1 = DLG_TEXT_Q[224];
    		link.l1.go = "Step_47";
		break;

		case "Step_47":
        	dialog.text = DLG_TEXT_Q[225];
    		link.l1 = DLG_TEXT_Q[226];
    		link.l1.go = "Step_48";
			pchar.questTemp.Azzy = "over";
    		LAi_SetImmortal(pchar, false);
    		DeleteAttribute(pchar, "questTemp.Azzy.Immortal");
    		DeleteQuestHeader("ContractWithHell");
    		DeleteQuestHeader("Azzy_HellSign");
		break;

		case "Step_48":
        	dialog.text = DLG_TEXT_Q[227]+
                          DLG_TEXT_Q[228];
    		link.l1 = DLG_TEXT_Q[229];
    		link.l1.go = "Azzy_Exit";
			npchar.lifeDay = 0;
		break;
		//помощь ГГ, если вляпался с долгом у ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = DLG_TEXT_Q[230];
			link.l1 = DLG_TEXT_Q[231];
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = DLG_TEXT_Q[232];
			link.l1 = DLG_TEXT_Q[233];
			link.l1.go = "ClimeUsurer_2";
		break;
		case "ClimeUsurer_2":
			dialog.text = DLG_TEXT_Q[234];
			link.l1 = DLG_TEXT_Q[235];
			link.l1.go = "ClimeUsurer_3";
		break;
		case "ClimeUsurer_3":
			dialog.text = DLG_TEXT_Q[236];
			link.l1 = DLG_TEXT_Q[237];
			link.l1.go = "ClimeUsurer_4";
		break;
		case "ClimeUsurer_4":
			dialog.text = DLG_TEXT_Q[238];
			link.l1 = DLG_TEXT_Q[239];
			link.l1.go = "ClimeUsurer_5";
		break;
		case "ClimeUsurer_5":
			dialog.text = DLG_TEXT_Q[240];
			link.l1 = DLG_TEXT_Q[241];
			link.l1.go = "ClimeUsurer_6";
		break;
		case "ClimeUsurer_6":
			dialog.text = DLG_TEXT_Q[242];
			link.l1 = DLG_TEXT_Q[243];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryQuest":
            Dialog.text = GetFullName(pchar)+ DLG_TEXT_Q[244];
			Link.l1 = DLG_TEXT_Q[245];
		    Link.l1.go = "AngStep_1";
    	break;

		case "AngStep_1":
            Dialog.text = DLG_TEXT_Q[246];
			Link.l1 = "...";
		    Link.l1.go = "Back_Exit";
            DeleteAttribute(npchar, "angry.ok");
            Dialog.CurrentNode = "Back_Exit";
    	break;

		case "AngryExitAgain":
 		    ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
 		    LAi_SetPlayerType(PChar);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}


