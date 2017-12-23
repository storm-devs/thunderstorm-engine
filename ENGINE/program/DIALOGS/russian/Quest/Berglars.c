#include "TEXT\DIALOGS\Quest\Berglars.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp, sStr, sPlace;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (Dialog.CurrentNode == "First time")
	{
		switch (pchar.questTemp.tugs.berglarState)
		{
			case "2": Dialog.CurrentNode = "Second time";	break;
			case "3": Dialog.CurrentNode = "Third time";	break;
			case "4": Dialog.CurrentNode = "Fourth time";	break;
			case "5": Dialog.CurrentNode = "Fifth time";	break;
			case "6": Dialog.CurrentNode = "Sixth time";	break;
		}
	}
    
	switch (Dialog.CurrentNode)
    {
        //------------- первая боевка --------------
		case "First time":
            dialog.text = DLG_TEXT_Q[0];
            link.l1 = GetFullName(pchar) + DLG_TEXT_Q[1];
            link.l1.go = "Step1_1";
        break;
 		case "Step1_1":
        	dialog.text = DLG_TEXT_Q[2];
    		link.l1 = DLG_TEXT_Q[3];
    		link.l1.go = "Step1_2";
		break;
 		case "Step1_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = DLG_TEXT_Q[4];
			else sStr = DLG_TEXT_Q[5];
        	dialog.text = DLG_TEXT_Q[6] + sStr + DLG_TEXT_Q[7];
    		link.l1 = DLG_TEXT_Q[8];
    		link.l1.go = "Step1_3";
		break;
 		case "Step1_3":
        	dialog.text = DLG_TEXT_Q[9];
    		link.l1 = DLG_TEXT_Q[10];
    		link.l1.go = "Step1_4";
		break;
 		case "Step1_4":
        	dialog.text = DLG_TEXT_Q[11];
    		link.l1 = DLG_TEXT_Q[12];
    		link.l1.go = "Step_overAll";
		break;
		//--------------
        case "Fight_1":
            dialog.text = DLG_TEXT_Q[13];
            link.l1 = DLG_TEXT_Q[14];
            link.l1.go = "FirstFight_1";
        break;        
		case "FirstFight_1":
            dialog.text = DLG_TEXT_Q[15];
            link.l1 = DLG_TEXT_Q[16];
            link.l1.go = "FirstFight_2";
        break;        
		case "FirstFight_2":
            dialog.text = DLG_TEXT_Q[17];
            link.l1 = DLG_TEXT_Q[18];
            link.l1.go = "FirstFight_3";
        break;        
		case "FirstFight_3":
            dialog.text = DLG_TEXT_Q[19];
            link.l1 = DLG_TEXT_Q[20];
            link.l1.go = "FirstFight_4";        
		break; 
		case "FirstFight_4":
            dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
            link.l1.go = "FirstFight_overAll";
        break; 
        //------------ вторая боевка ----------------
        case "Second time":
            dialog.text = DLG_TEXT_Q[23];
            link.l1 = DLG_TEXT_Q[24];
            link.l1.go = "Step2_1";
        break;
        case "Step2_1":
            dialog.text = DLG_TEXT_Q[25];
            link.l1 = GetFullName(pchar) + DLG_TEXT_Q[26];
            link.l1.go = "Step2_2";
        break;
        case "Step2_2":
            dialog.text = DLG_TEXT_Q[27];
            link.l1 = DLG_TEXT_Q[28];
            link.l1.go = "Step2_3";
        break;
        case "Step2_3":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = DLG_TEXT_Q[29];
			else sStr = DLG_TEXT_Q[30];
            dialog.text = DLG_TEXT_Q[31] + sStr + DLG_TEXT_Q[32];
            link.l1 = DLG_TEXT_Q[33];
            link.l1.go = "Step_overAll";
        break;
		//----------
        case "Fight_2":
            dialog.text = DLG_TEXT_Q[34];
            link.l1 = DLG_TEXT_Q[35];
            link.l1.go = "SecondFight_1";
        break;
        case "SecondFight_1":
            dialog.text = DLG_TEXT_Q[36];
            link.l1 = DLG_TEXT_Q[37];
            link.l1.go = "SecondFight_2";
        break;
        case "SecondFight_2":
            dialog.text = DLG_TEXT_Q[38];
            link.l1 = DLG_TEXT_Q[39];
            link.l1.go = "SecondFight_3";
        break;
        case "SecondFight_3":
            dialog.text = DLG_TEXT_Q[40];
            link.l1 = DLG_TEXT_Q[41];
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ третья встреча, сумасшедший ----------------
        case "Third time":
            dialog.text = DLG_TEXT_Q[42];
            link.l1 = DLG_TEXT_Q[43];
            link.l1.go = "Step3_1";
        break;
        case "Step3_1":
            dialog.text = DLG_TEXT_Q[44];
            link.l1 = DLG_TEXT_Q[45];
            link.l1.go = "Step3_2";
        break;
        case "Step3_2":
            dialog.text = DLG_TEXT_Q[46];
            link.l1 = DLG_TEXT_Q[47];
            link.l1.go = "Step3_3";
        break;
        case "Step3_3":
            dialog.text = DLG_TEXT_Q[48];
            link.l1 = DLG_TEXT_Q[49];
            link.l1.go = "Step3_4";
        break;
        case "Step3_4":
            dialog.text = DLG_TEXT_Q[50];
            link.l1 = DLG_TEXT_Q[51];
            link.l1.go = "Step3_5";
        break;
        case "Step3_5":
            dialog.text = DLG_TEXT_Q[52];
            link.l1 = DLG_TEXT_Q[53];
            link.l1.go = "Step3_6";
        break;
        case "Step3_6":
            dialog.text = DLG_TEXT_Q[54];
            link.l1 = DLG_TEXT_Q[55];
            link.l1.go = "Step3_7";
        break;
        case "Step3_7":
            dialog.text = DLG_TEXT_Q[56];
            link.l1 = DLG_TEXT_Q[57];
            link.l1.go = "Step3_8";
        break;
        case "Step3_8":
            dialog.text = DLG_TEXT_Q[58];
            link.l1 = DLG_TEXT_Q[59];
            link.l1.go = "Step3_9";
        break;
        case "Step3_9":
			sTemp = "berglar" + npchar.city;
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        //------------ четвертая встреча ----------------
        case "Fourth time":
            dialog.text = DLG_TEXT_Q[60] + GetAddress_Form(NPChar) + ".";
            link.l1 = DLG_TEXT_Q[61];
            link.l1.go = "Step4_1";
        break;
        case "Step4_1":
            dialog.text = DLG_TEXT_Q[62];
            link.l1 = DLG_TEXT_Q[63];
            link.l1.go = "Step4_2";
        break;
        case "Step4_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = DLG_TEXT_Q[64];
			else sStr = DLG_TEXT_Q[65];
            dialog.text = DLG_TEXT_Q[66] + GetAddress_Form(NPChar) + DLG_TEXT_Q[67] + sStr + DLG_TEXT_Q[68];
            link.l1 = DLG_TEXT_Q[69];
            link.l1.go = "Step4_3";
            link.l2 = DLG_TEXT_Q[70];
            link.l2.go = "Step4_5";
        break;
        case "Step4_3":
            dialog.text = DLG_TEXT_Q[71];
            link.l1 = DLG_TEXT_Q[72];
            link.l1.go = "Step4_4";
        break;
        case "Step4_4":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step4_5":
            dialog.text = DLG_TEXT_Q[73];
            link.l1 = DLG_TEXT_Q[74];
            link.l1.go = "Step4_6";
        break;
        case "Step4_6":
            dialog.text = DLG_TEXT_Q[75] + GetAddress_Form(NPChar) + ".";
            link.l1 = DLG_TEXT_Q[76];
            link.l1.go = "Step_overAll";
        break;
        case "Fight_4":
            dialog.text = DLG_TEXT_Q[77];
            link.l1 = DLG_TEXT_Q[78];
            link.l1.go = "Fight4_1";
        break;
        case "Fight4_1":
            dialog.text = DLG_TEXT_Q[79];
            link.l1 = DLG_TEXT_Q[80];
            link.l1.go = "Fight4_2";
        break;
        case "Fight4_2":
			dialog.text = DLG_TEXT_Q[81];
            link.l1 = DLG_TEXT_Q[82];
            link.l1.go = "Fight4_3";
        break;
        case "Fight4_3":
            dialog.text = DLG_TEXT_Q[83];
            link.l1 = DLG_TEXT_Q[84];
            link.l1.go = "Fight4_4";
        break;
        case "Fight4_4":
            dialog.text = DLG_TEXT_Q[85];
            link.l1 = DLG_TEXT_Q[86];
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ пятая встреча ----------------
        case "Fifth time":
            dialog.text = DLG_TEXT_Q[87] + GetAddress_Form(NPChar) + DLG_TEXT_Q[88];
            link.l1 = DLG_TEXT_Q[89];
            link.l1.go = "Step5_1";
        break;
        case "Step5_1":
            dialog.text = DLG_TEXT_Q[90];
            link.l1 = DLG_TEXT_Q[91];
            link.l1.go = "Step5_2";
        break;
        case "Step5_2":
            dialog.text = DLG_TEXT_Q[92];
            link.l1 = DLG_TEXT_Q[93];
            link.l1.go = "Step5_3";
        break;
        case "Step5_3":
            dialog.text = DLG_TEXT_Q[94];
            link.l1 = DLG_TEXT_Q[95];
            link.l1.go = "Step5_4";
        break;
        case "Step5_4":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = DLG_TEXT_Q[96];
			else sStr = DLG_TEXT_Q[97];
            dialog.text = DLG_TEXT_Q[98] + sStr + DLG_TEXT_Q[99];
            link.l1 = DLG_TEXT_Q[100];
            link.l1.go = "Step5_5";
            link.l2 = DLG_TEXT_Q[101];
            link.l2.go = "Step5_7";
        break;
        case "Step5_5":
            dialog.text = DLG_TEXT_Q[102];
            link.l1 = "...";
            link.l1.go = "Step5_6";
        break;
        case "Step5_6":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step5_7":
            dialog.text = DLG_TEXT_Q[103];
            link.l1 = DLG_TEXT_Q[104];
            link.l1.go = "Step_overAll";
        break;
        case "Fight_5":
            dialog.text = DLG_TEXT_Q[105];
            link.l1 = DLG_TEXT_Q[106];
            link.l1.go = "Fight5_1";
        break;
        case "Fight5_1":
            dialog.text = DLG_TEXT_Q[107];
            link.l1 = DLG_TEXT_Q[108];
            link.l1.go = "Fight5_2";
        break;
        case "Fight5_2":
            dialog.text = DLG_TEXT_Q[109];
            link.l1 = DLG_TEXT_Q[110];
            link.l1.go = "Fight5_3";
        break;
        case "Fight5_3":
            dialog.text = DLG_TEXT_Q[111];
            link.l1 = DLG_TEXT_Q[112];
            link.l1.go = "Fight5_4";
        break;
        case "Fight5_4":
            dialog.text = DLG_TEXT_Q[113];
            link.l1 = DLG_TEXT_Q[114];
            link.l1.go = "Fight5_5";
        break;
        case "Fight5_5":
            dialog.text = DLG_TEXT_Q[115];
            link.l1 = DLG_TEXT_Q[116];
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ шестая встреча ----------------
        case "Sixth time":
            dialog.text = DLG_TEXT_Q[117] + GetAddress_Form(NPChar) + DLG_TEXT_Q[118] + GetFullName(pchar) + "?";
            link.l1 = DLG_TEXT_Q[119];
            link.l1.go = "Step6_1";
        break;
        case "Step6_1":
			dialog.text = DLG_TEXT_Q[120];
            link.l1 = DLG_TEXT_Q[121];
            link.l1.go = "Step6_2";
        break;
        case "Step6_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = DLG_TEXT_Q[122];
			else sStr = DLG_TEXT_Q[123];
            dialog.text = DLG_TEXT_Q[124] + sStr + DLG_TEXT_Q[125];
            link.l1 = DLG_TEXT_Q[126];
            link.l1.go = "Step_overAll";
        break;
        case "Fight_6":
            dialog.text = DLG_TEXT_Q[127];
            link.l1 = DLG_TEXT_Q[128];
            link.l1.go = "Fight6_1";
        break;
        case "Fight6_1":
            dialog.text = DLG_TEXT_Q[129];
            link.l1 = DLG_TEXT_Q[130];
            link.l1.go = "Fight6_2";
        break;
        case "Fight6_2":
            dialog.text = DLG_TEXT_Q[131];
            link.l1 = DLG_TEXT_Q[132];
            link.l1.go = "Fight6_3";
        break;
        case "Fight6_3":
            dialog.text = DLG_TEXT_Q[133];
            link.l1 = DLG_TEXT_Q[134];
            link.l1.go = "Fight6_4";
        break;
        case "Fight6_4":
            dialog.text = DLG_TEXT_Q[135];
            link.l1 = DLG_TEXT_Q[136];
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "1");
        break;
		//------------ общие ноды ----------------
 		case "Step_overAll":
			sTemp = "berglar" + npchar.city;
			sStr = "Birglars_fight_" + npchar.index;
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = pchar.questTemp.tugs.(sTemp);
			pchar.quest.(sStr).win_condition.l1.locator_group = "item";
			pchar.quest.(sStr).win_condition.l1.locator = "berglar1";
			pchar.quest.(sStr).function = "Birglars_fight";
			pchar.quest.(sStr).city = npchar.city; //запомним город грабителя
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "Fight_" + pchar.questTemp.tugs.berglarState;
			npchar.equip.blade = FindCharacterItemByGroup(npchar, BLADE_ITEM_TYPE);  
			npchar.equip.gun = FindCharacterItemByGroup(npchar, GUN_ITEM_TYPE); 			
			LAi_LocationDisableMonGenTimer(pchar.questTemp.tugs.(sTemp), 1); //монстров не генерить 1 день
			LAi_LocationDisableOffGenTimer(pchar.questTemp.tugs.(sTemp), 1); //офицеров не пускать 1 день
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, pchar.questTemp.tugs.(sTemp), "item", "berglar1", "OpenTheDoors", -1.0);
			chrDisableReloadToLocation = true;
			//pchar.questTemp.tugs.(sTemp) = "fight";
			DialogExit();
		break;
		case "FirstFight_overAll":
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //счетчик
			npchar.SaveItemsForDead  = true; 
			npchar.DontClearDead = true; 
			SetCharacterPerk(npchar, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			sTemp = "berglar" + npchar.city;
			LAi_SetHP(npchar, stf(pchar.questTemp.tugs.(sTemp).hp), stf(pchar.questTemp.tugs.(sTemp).hp));
			LAi_SetCurHPMax(npchar);
			chrDisableReloadToLocation = true;
			DeleteAttribute(npchar, "city"); //чтобы не ругались с нацией
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (npchar.id == "BerglarFortFrance")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 18, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 18, 60, 50, BLADE_LONG, "pistol3", 10);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarPanama")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 21, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 21, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarSantaCatalina")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 20, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        //------------ финальная боевка с Остином ----------------
        case "Final_fight":
            dialog.text = DLG_TEXT_Q[137];
            link.l1 = DLG_TEXT_Q[138];
            link.l1.go = "StepF1_1";
        break;
        case "StepF1_1":
            dialog.text = DLG_TEXT_Q[139] + GetFullName(pchar) + DLG_TEXT_Q[140];
            link.l1 = DLG_TEXT_Q[141];
            link.l1.go = "StepF1_2";
        break;
        case "StepF1_2":
            dialog.text = DLG_TEXT_Q[142];
            link.l1 = DLG_TEXT_Q[143];
            link.l1.go = "StepF1_3";
        break;
        case "StepF1_3":
            dialog.text = DLG_TEXT_Q[144];
            link.l1 = DLG_TEXT_Q[145];
            link.l1.go = "StepF1_4";
        break;
        case "StepF1_4":
            dialog.text = DLG_TEXT_Q[146];
            link.l1 = DLG_TEXT_Q[147];
            link.l1.go = "StepF1_5";
        break;
        case "StepF1_5":
            dialog.text = DLG_TEXT_Q[148];
            link.l1 = DLG_TEXT_Q[149];
            link.l1.go = "StepF1_6";
        break;
        case "StepF1_6":
            dialog.text = DLG_TEXT_Q[150];
            link.l1 = DLG_TEXT_Q[151];
            link.l1.go = "StepF1_7";
        break;
        case "StepF1_7":
            dialog.text = DLG_TEXT_Q[152];
            link.l1 = DLG_TEXT_Q[153];
            link.l1.go = "StepF1_8";
        break;
        case "StepF1_8":
            dialog.text = DLG_TEXT_Q[154];
            link.l1 = DLG_TEXT_Q[155];
            link.l1.go = "StepF1_9";
        break;
        case "StepF1_9":
			LAi_LocationFightDisable(loadedLocation, false);
			CloseQuestHeader("BerglarsGang");
			LAi_group_Delete("EnemyFight");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
