#include "TEXT\DIALOGS\Quest\LeifEricson.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ƒиалог первый - перва€ встреча
		case "First time":
            if (pchar.questTemp.Ascold == "Ascold_MummyIsLive")
            {
            	dialog.text = DLG_TEXT_Q[0];
        		link.l1 = environment.date.year + DLG_TEXT_Q[1];
        		link.l1.go = "Step_8";
            }
            if (pchar.questTemp.Ascold == "Ascold_BodyChange")
            {
            	dialog.text = DLG_TEXT_Q[2];
        		link.l1 = DLG_TEXT_Q[3];
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_SkelSlave")
            {
            	dialog.text = DLG_TEXT_Q[4];
        		link.l1 = DLG_TEXT_Q[5];
        		link.l1.go = "Step_27";
            }
            if (pchar.questTemp.Ascold == "Ascold_ImMummy")
            {
            	dialog.text = DLG_TEXT_Q[6];
        		link.l1 = DLG_TEXT_Q[7];
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_MummyFoundItems")
            {
            	dialog.text = DLG_TEXT_Q[8];
                if  (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
                {
                	link.l1 = DLG_TEXT_Q[9];
            		link.l1.go = "Step_29";
                }
                else
                {
                	link.l1 = DLG_TEXT_Q[10];
            		link.l1.go = "Step_30";
                }
            }
            if (pchar.questTemp.Ascold == "Ascold_BackMyBody")
            {
            	dialog.text = DLG_TEXT_Q[11];
        		link.l1 = DLG_TEXT_Q[12];
        		link.l1.go = "Step_31";
            }
            if (pchar.questTemp.Ascold == "Ascold_ReturnToAscold")
            {
            	dialog.text = DLG_TEXT_Q[13];
        		link.l1 = DLG_TEXT_Q[14];
        		link.l1.go = "exit";
            }
		break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_8":
        	dialog.text = DLG_TEXT_Q[15]+
                          DLG_TEXT_Q[16];
    		link.l1 = DLG_TEXT_Q[17];
    		link.l1.go = "Step_9";
		break;

        case "Step_9":
        	dialog.text = DLG_TEXT_Q[18];
    		link.l1 = DLG_TEXT_Q[19] + GetFullName(pchar) + DLG_TEXT_Q[20];
    		link.l1.go = "Step_10";
    		link.l2 = DLG_TEXT_Q[21];
    		link.l2.go = "ToDeath";
		break;

        case "ToDeath":
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    		LAi_SetPlayerType(pchar);
		    LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			LAi_SetFightMode(pchar, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_10":
        	dialog.text = DLG_TEXT_Q[22];
    		link.l1 = DLG_TEXT_Q[23];
    		link.l1.go = "Step_11";
		break;

        case "Step_11":
        	dialog.text = DLG_TEXT_Q[24];
    		link.l1 = DLG_TEXT_Q[25];
    		link.l1.go = "Step_12";
		break;

        case "Step_12":
        	dialog.text = DLG_TEXT_Q[26];
    		link.l1 = DLG_TEXT_Q[27];
    		link.l1.go = "Step_13";
		break;

        case "Step_13":
        	dialog.text = DLG_TEXT_Q[28]+
                          DLG_TEXT_Q[29];
    		link.l1 = DLG_TEXT_Q[30];
    		link.l1.go = "Step_14";
		break;

        case "Step_14":
        	dialog.text = DLG_TEXT_Q[31]+
                          DLG_TEXT_Q[32];
    		link.l1 = DLG_TEXT_Q[33];
    		link.l1.go = "Step_15";
		break;

        case "Step_15":
        	dialog.text = DLG_TEXT_Q[34];
    		link.l1 = DLG_TEXT_Q[35];
    		link.l1.go = "Step_16";
		break;

        case "Step_16":
        	dialog.text = DLG_TEXT_Q[36]+
                          DLG_TEXT_Q[37];
    		link.l1 = DLG_TEXT_Q[38];
    		link.l1.go = "Step_17";
		break;

        case "Step_17":
        	dialog.text = DLG_TEXT_Q[39]+
                          DLG_TEXT_Q[40]+
                          DLG_TEXT_Q[41]+
                          DLG_TEXT_Q[42];
    		link.l1 = DLG_TEXT_Q[43];
    		link.l1.go = "Step_18";
		break;

        case "Step_18":
        	dialog.text = DLG_TEXT_Q[44]+
                          DLG_TEXT_Q[45];
    		link.l1 = DLG_TEXT_Q[46];
    		link.l1.go = "Step_19";
		break;

        case "Step_19":
        	dialog.text = DLG_TEXT_Q[47]+
                          DLG_TEXT_Q[48]+
                          DLG_TEXT_Q[49];
    		link.l1 = DLG_TEXT_Q[50];
    		link.l1.go = "Step_20";
		break;

        case "Step_20":
        	dialog.text = DLG_TEXT_Q[51];
    		link.l1 = DLG_TEXT_Q[52];
    		link.l1.go = "Step_21";
		break;

        case "Step_21":
        	dialog.text = DLG_TEXT_Q[53];
    		link.l1 = DLG_TEXT_Q[54];
    		link.l1.go = "Step_22";
		break;

        case "Step_22":
        	dialog.text = DLG_TEXT_Q[55];
    		link.l1 = DLG_TEXT_Q[56];
    		link.l1.go = "Step_23";
    		link.l2 = DLG_TEXT_Q[57];
    		link.l2.go = "ToDeath";
		break;

        case "Step_23":
        	dialog.text = DLG_TEXT_Q[58]+
                          DLG_TEXT_Q[59];
    		link.l1 = DLG_TEXT_Q[60];
    		link.l1.go = "Step_24";
		break;

        case "Step_24":
        	dialog.text = DLG_TEXT_Q[61]+
                          DLG_TEXT_Q[62];
    		link.l1 = DLG_TEXT_Q[63];
    		link.l1.go = "Body_Change";
		break;

        case "Body_Change":
			LAi_SetPlayerType(pchar);
            bDisableCharacterMenu = true; //закрываем ‘2
            // ==> мен€ем модели
            Pchar.questTemp.Ascold.heroFaceId    = pchar.FaceId;
            Pchar.questTemp.Ascold.heroAnimation = pchar.model.animation;
			Pchar.questTemp.Ascold.reputation    = pchar.reputation;
			Pchar.questTemp.Ascold.nation		 = pchar.nation;
			Pchar.questTemp.Ascold.relation      = GetNationRelation2MainCharacter(FRANCE);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            npchar.model = pchar.model;
			npchar.model.animation = pchar.model.animation;			
            FaceMaker(npchar);
            SetNewModelToChar(npchar);
            pchar.model = "Mummy";
            pchar.model.animation = "man";
            pchar.FaceId = 207; //муми€
            FaceMaker(pchar);
            SetNewModelToChar(pchar);
            pchar.questTemp.Ascold = "Ascold_BodyChange";
    		LAi_SetCitizenType(npchar);
            //==> убираем офицеров
            for (i=1; i<=3; i++)
            {
                string officers = "Fellows.Passengers.Officers."+"id"+i;
                if(CheckAttribute(pchar, officers))
                {
                     RemoveOfficersIndex(pchar, sti(pchar.(officers)));
                }
            }
            //<== убираем офицеров
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_25":
        	dialog.text = DLG_TEXT_Q[64];
    		link.l1 = DLG_TEXT_Q[65];
    		link.l1.go = "Step_26";
		break;

        case "Step_26":
        	dialog.text = DLG_TEXT_Q[66];
    		link.l1 = "...";
    		link.l1.go = "exit";
            for (i=1; i<=6; i++)
            {
				sld = GetCharacter(NPC_GenerateCharacter("MySkel"+i, "Skel"+(rand(3)+1), "skeleton", "man", 30, PIRATE, 0, true));	
				FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);  
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+(rand(2)+1));
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
            }
            pchar.questTemp.Ascold = "Ascold_SkelSlave";
		break;
		
        case "Step_27":
        	dialog.text = DLG_TEXT_Q[67]+
                          DLG_TEXT_Q[68];
    		link.l1 = DLG_TEXT_Q[69];
    		link.l1.go = "Step_28";
		break;

        case "Step_28":
            PChar.GenQuest.CrewSkelMode = true; //команда - скелеты 
  		    chrDisableReloadToLocation = false; // открыть выход из локации.
            pchar.questTemp.Ascold = "Ascold_ImMummy";
            //==> потом вернуть
            Pchar.location.from_sea.save = Pchar.location.from_sea;
            Pchar.location.from_sea = "none";
            Pchar.Ship.Crew.Quantity.save = Pchar.Ship.Crew.Quantity;
            Pchar.Ship.Crew.Quantity = 1000;
            Pchar.GenQuest.HunterScore2Pause = 1; //Ќ«√ не начисл€ютс€
			Pchar.GenQuest.ReputationNotChange = 1; //репутацию не мен€ть
            ChangeCharacterAddress(characterFromID("Ascold"), "None", "");
            //<== потом вернуть
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1 = "location";
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1.location = "BasTer_ExitTown";
            Pchar.quest.Ascold_MummyFightTown.win_condition = "Ascold_MummyFightTown";

            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Step_29":
            DeleteAttribute(PChar, "GenQuest.CrewSkelMode"); // команда-скелеты в нормальное сост.
            bDisableCharacterMenu = false; //открываем ‘2
            bDisableLandEncounters = false;
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            //==> вертаем
            Pchar.location.from_sea = Pchar.location.from_sea.save;
            DeleteAttribute(PChar, "location.from_sea.save");
            Pchar.Ship.Crew.Quantity = Pchar.Ship.Crew.Quantity.save;
            DeleteAttribute(PChar, "Ship.Crew.Quantity.save");

            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Ascold")], "BasTer_houseSp1", "goto", "goto1");
           	LAi_SetStayTypeNoGroup(characterFromID("Ascold"));
           	SetLocationCapturedState("BasTer_town", false);
            // ==> возвращаем модели
            pchar.model = npchar.model;
            pchar.model.animation = Pchar.questTemp.Ascold.heroAnimation;
            pchar.FaceId          = Pchar.questTemp.Ascold.heroFaceId;
			pchar.reputation	  = Pchar.questTemp.Ascold.reputation;
			pchar.nation		  = Pchar.questTemp.Ascold.nation;
			SetNationRelation2MainCharacter(FRANCE, sti(Pchar.questTemp.Ascold.relation));
            FaceMaker(pchar);
            SetNewModelToChar(pchar);
            npchar.model = "Mummy";
			npchar.model.animation = "man";
            FaceMaker(npchar);
            SetNewModelToChar(npchar);
            DeleteAttribute(PChar, "questTemp.Ascold.heroFaceId");
            DeleteAttribute(PChar, "questTemp.Ascold.heroAnimation");
            DeleteAttribute(PChar, "questTemp.Ascold.reputation");
			DeleteAttribute(PChar, "questTemp.Ascold.relation");
			DeleteAttribute(PChar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(PChar, "GenQuest.ReputationNotChange"); //вертаем смену репы
            chrDisableReloadToLocation = true; // закрыть выход из локации.
            pchar.questTemp.Ascold = "Ascold_BackMyBody";
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Step_30":
        	dialog.text = DLG_TEXT_Q[70];
    		link.l1 = DLG_TEXT_Q[71];
    		link.l1.go = "exit";
		break;

        case "Step_31":
        	dialog.text = DLG_TEXT_Q[72];
    		link.l1 = DLG_TEXT_Q[73];
    		link.l1.go = "exit";
    		chrDisableReloadToLocation = false; // открыть выход из локации.
			bDisableFastReload = false; 
    		pchar.questTemp.Ascold = "Ascold_ReturnToAscold";
    		characters[GetCharacterIndex("Ascold")].dialog.currentnode = "AfterAttackMummy";
		break;
	}
}


