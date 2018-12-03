#include "TEXT\DIALOGS\Quest\EngLineNpc_2.h"
void ProcessDialogEvent()
{
	ref NPChar;
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
            // ==> Боцман Морриса Уильямса
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса
            {
    			dialog.text = DLG_TEXT_Q[2];
    			link.l1 = DLG_TEXT_Q[3];
    			link.l1.go = "Step_E6_1";
            }
            if (pchar.questTemp.State == "MorrisWillams_GoToHimselfBussines" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса второй раз
            {
    			dialog.text = DLG_TEXT_Q[4];
    			link.l1 = DLG_TEXT_Q[5];
    			link.l1.go = "Step_E6_4";
            }
			// ==> Джилиан Эттербери.
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoWomen" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери
            {
    			dialog.text = DLG_TEXT_Q[6];
                link.l2 = DLG_TEXT_Q[7];
                link.l2.go = "Step_E6_25";
            }
			if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери после дачи задания
            {
    			dialog.text = DLG_TEXT_Q[8];
    			link.l1 = DLG_TEXT_Q[9];
    			link.l1.go = "exit";
            }
			if (npchar.id == "Gillian Atterbury" && CheckAttribute(npchar, "TempQuest.SavedHusband")) // разговор с Джиллиан Эттербери, если мы спасли ее мужа
            {
                dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[10],
                         DLG_TEXT_Q[11], DLG_TEXT_Q[12],
                         DLG_TEXT_Q[13], "block", 1, npchar, Dialog.CurrentNode);
    			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[14],
                                               DLG_TEXT_Q[15],
                                               DLG_TEXT_Q[16],
                                               DLG_TEXT_Q[17], npchar, Dialog.CurrentNode);
    			link.l1.go = "exit";
    			//ChangeCharacterReputation(pchar, 1); // чит, но вряд ли кто-то найдет TO_DO eddy
            }
            // ==> Один из бандитов в пещере, удерживающий мужа Джилиан
            if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Bandit3")   // базар в пещере перед боевкой
            {
    			dialog.text = DLG_TEXT_Q[18];
    			link.l1 = DLG_TEXT_Q[19];
    			link.l1.go = "Step_E6_30";
            }
            // ==> Муж Джилиан
            if (pchar.questTemp.State == "MorrisWillams_AfterFight" && npchar.id == "Jillians_Husband")   // базар в пещере с мужем, англ.линейка, квест №6
            {
    			dialog.text = DLG_TEXT_Q[20];
    			link.l1 = DLG_TEXT_Q[21];
    			link.l1.go = "Step_E6_32";
            }
            // ==> Спасишийся перец в поселении буканьеров
            if (pchar.questTemp.State == "ToMansfield_GoOn")   // разговор со спасшимся перцем, анл.линейка, квест №8
            {
    			dialog.text = DLG_TEXT_Q[22];
    			link.l1 = DLG_TEXT_Q[23];
    			link.l1.go = "Step_E8_1";
            }
            if (pchar.questTemp.State == "ToMansfield_CatchToPardal")   // остаточный разговор со спасшимся перцем
            {
    			dialog.text = DLG_TEXT_Q[24];
    			link.l1 = DLG_TEXT_Q[25];
    			link.l1.go = "exit";
            }


        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
        
//*************************************** Диалог боцмана Морриса Уильямса *********************************
 		case "Step_E6_1":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "Step_E6_2";
		break;

 		case "Step_E6_2":
			dialog.text = DLG_TEXT_Q[28];
			link.l1 = DLG_TEXT_Q[29];
			link.l1.go = "Step_E6_3";
		break;

 		case "Step_E6_3":
			chrDisableReloadToLocation = false;
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            LAi_SetPlayerType(pchar);
            sld = characterFromID("Morris_Willams");
            LAi_SetHuberTypeNoGroup(sld);
			FreeSitLocator("PortRoyal_tavern", "sit10");
            ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit10");
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //на всякий случай, чтобы геймер не слинял.
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
            NextDiag.TempNode = "First time";
            DialogExit();
		break;

 		case "Step_E6_4":
			dialog.text = DLG_TEXT_Q[30]+
                          DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Step_E6_5";
		break;

 		case "Step_E6_5":
			dialog.text = DLG_TEXT_Q[33]+
                          DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "Step_E6_6";
		break;

 		case "Step_E6_6":
			chrDisableReloadToLocation = false;
    	    npchar.LifeDay = 1; // уберем нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			pchar.questTemp.State = "MorrisWillams_ArrestedToPrison";
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "15");
            ref sld = characterFromID("Morris_Willams");
			LAi_SetStayType(sld);
            ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
            RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
            LAi_SetPlayerType(pchar);
			DialogExit();
		break;

//*********************************** Диалоги Джиллиан Эттербери *************************************
		case "Step_E6_25":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "Step_E6_26";
		break;

        case "Step_E6_26":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "Step_E6_27";
		break;

        case "Step_E6_27":
			dialog.text = DLG_TEXT_Q[40]+
                     DLG_TEXT_Q[41]+
                     DLG_TEXT_Q[42]+
                     DLG_TEXT_Q[43]+
                     DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "Step_E6_28";
		break;

        case "Step_E6_28":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_SeekHusband";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "20");
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1.location = "Jamaica_Grot";
            Pchar.quest.MorrisWillams_HusbandInCave.win_condition = "MorrisWillams_HusbandInCave";
		break;



//**************************** Диалоги бандита в пещере, поиски мужа Джиллиан ****************************
 		case "Step_E6_30":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "Step_E6_31";
		break;

 		case "Step_E6_31":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "MorrisWillams_AftreFightingInCave");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//************************************** Диалоги мужа Джиллиан ***********************************
 		case "Step_E6_32":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "Step_E6_33";
		break;

 		case "Step_E6_33":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "Step_E6_34";
		break;

 		case "Step_E6_34":
			dialog.text = DLG_TEXT_Q[54]+
                          DLG_TEXT_Q[55]+
                          DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "Step_E6_35";
		break;

 		case "Step_E6_35":
			Characters[GetCharacterIndex("Gillian Atterbury")].TempQuest.SavedHusband = 1; // чтоб Джиллиан помнила об услуге...
            AddQuestRecord("Eng_Line_6_MorrisWillams", "21");
            LAi_SetPlayerType(pchar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
            //ChangeCharacterReputation(pchar, 5); TO_DO eddy
            pchar.questTemp.State = "MorrisWillams_AfterFightGoRedmond";
			DialogExit();
		break;

//************************************** Диалоги спасшегося буканьера ***********************************
  		case "Step_E8_1":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "Step_E8_2";
		break;

   		case "Step_E8_2":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "Step_E8_3";
		break;

   		case "Step_E8_3":
			dialog.text = DLG_TEXT_Q[62]+
                          DLG_TEXT_Q[63]+
                          DLG_TEXT_Q[64]+
                          DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "Step_E8_4";
		break;

   		case "Step_E8_4":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "Step_E8_5";
		break;

   		case "Step_E8_5":
			dialog.text = DLG_TEXT_Q[69];
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Step_E8_6";
		break;

   		case "Step_E8_6":
			dialog.text = DLG_TEXT_Q[71]+
                          DLG_TEXT_Q[72]+
                          DLG_TEXT_Q[73];
			link.l1 = DLG_TEXT_Q[74];
			link.l1.go = "Step_E8_7";
		break;

   		case "Step_E8_7":
			dialog.text = DLG_TEXT_Q[75];
			link.l1 = DLG_TEXT_Q[76];
			link.l1.go = "exit";
			pchar.questTemp.State = "ToMansfield_CatchToPardal";
			AddQuestRecord("Eng_Line_8_ToMansfield", "2");
		break;
		
        case "You_baster":
            dialog.text = DLG_TEXT_Q[77];
            link.l1 = DLG_TEXT_Q[78];
            link.l1.go = "exit";
            NextDiag.TempNode = "You_baster";
			pchar.questTemp.jailCanMove = true;
        break;
    }
}
