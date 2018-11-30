#include "TEXT\DIALOGS\Quest\EngLineNpc_1.h"
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
            //Альбермаль, англ.линейка, квест №1
            if (npchar.id == "Albermal")
            {
                dialog.text = DLG_TEXT_Q[2];
                link.l1 = DLG_TEXT_Q[3] + GetFullName(pchar) + DLG_TEXT_Q[4];
                link.l1.go = "Step_E1_1";
            }
            // тюремщик в Кюрасао, квест №4
            if (npchar.id == "Hoverd_Tantum")
            {
    			dialog.text = DLG_TEXT_Q[5];
    			link.l1 = DLG_TEXT_Q[6];
    			link.l1.go = "Step_E4_1";
            }
            // ==> Комендант форта Оранж,  квест №5
            if (npchar.id == "Orange_Comendant")
            {
    			dialog.text = DLG_TEXT_Q[7];
    			link.l1 = DLG_TEXT_Q[8];
    			link.l1.go = "Step_E5_1";
            }
            // ==> Квест №6, Моррис Уильямс
            if (npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[9];
                link.l1 = DLG_TEXT_Q[10];
                link.l1.go = "exit";
            }  
            if (pchar.questTemp.State == "MorrisWillams_GoToMorrisBegin" && npchar.id == "Morris_Willams")
            {
    			dialog.text = DLG_TEXT_Q[11];
    			link.l1 = DLG_TEXT_Q[12];
    			link.l1.go = "Step_E6_20";
            }
            if (pchar.questTemp.State == "MorrisWillams_AfterFirstTalkingWithMorris" && npchar.id == "Morris_Willams")
            {
    			dialog.text = DLG_TEXT_Q[13] + pchar.name + DLG_TEXT_Q[14];
    			link.l1 = DLG_TEXT_Q[15];
    			link.l1.go = "exit";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Morris_Willams")
            {
                LAi_ActorSetSitMode(pchar);
                dialog.text = DLG_TEXT_Q[16];
                link.l1 = DLG_TEXT_Q[17];
                link.l1.go = "Step_E6_2";
            }
            if (pchar.questTemp.State == "MorrisWillams_ModifordPolitic" && npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[18];
                link.l1 = DLG_TEXT_Q[19];
                link.l1.go = "Step_E6_6";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceNotFound" || pchar.questTemp.State == "MorrisWillams_2PinnaceNotFound")
            {
                dialog.text = DLG_TEXT_Q[20];
                link.l1 = DLG_TEXT_Q[21];
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoard" && npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[22];
                link.l1 = DLG_TEXT_Q[23];
                link.l1.go = "Step_E6_10";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceBoardNotFoundMoney" && npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[24];
                link.l1 = DLG_TEXT_Q[25];
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_DieHard" && npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[26];
                link.l1 = DLG_TEXT_Q[27];
                link.l1.go = "Step_E6_11";
            }
            if (pchar.questTemp.State == "MorrisWillams_PinnaceSink" && npchar.id == "Morris_Willams")
            {
                dialog.text = DLG_TEXT_Q[28];
                link.l1 = DLG_TEXT_Q[29];
                link.l1.go = "Step_E6_11";
            }
			// ==> Квест №12, диалоги с полковником Томасом Линчем
            if (pchar.questTemp.State == "ColonelLinch_GoToKingstown")
            {
                dialog.text = DLG_TEXT_Q[30];
                link.l1 = DLG_TEXT_Q[31] + GetFullName(pchar) + ".";
                link.l1.go = "Step_E12_1";
            }

            if (pchar.questTemp.State == "ColonelLinch_ArrestModiford")
            {
                dialog.text = DLG_TEXT_Q[32];
                link.l1 = DLG_TEXT_Q[33];
                link.l1.go = "exit";
            }
        break;

//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
        case "Step_E1_1":
            if (GetQuestPastDayParam("questTemp") < 2)
            {
                dialog.text = DLG_TEXT_Q[34];
                link.l1 = DLG_TEXT_Q[35];
                link.l1.go = "Go_with_Albermal";
                link.l2 = DLG_TEXT_Q[36];
                link.l2.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[37];
				link.l1 = DLG_TEXT_Q[38];
				link.l1.go = "Go_with_Albermal";
				link.l2 = DLG_TEXT_Q[39];
				link.l2.go = "exit";
				ChangeCharacterReputation(pchar, -1);
            }
            NextDiag.TempNode = "Step_E1_1";
        break;

        case "Go_with_Albermal":
            AddQuestRecord("Eng_Line_1_Albermal", "2");
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1          = "location";
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1.location = "Antigua";
			pchar.quest.fight_withSpanish_Albermal.win_condition             = "fight_withSpanish_Albermal";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "in_the_SentJons":
            if (GetQuestPastDayParam("questTemp") < 14)
            {
                dialog.text = DLG_TEXT_Q[40];
                link.l1 = DLG_TEXT_Q[41];
                link.l1.go = "Albermal_go_out";
                pchar.questTemp.State = "Albermal_good_time";
            }
            else
            {
                dialog.text = DLG_TEXT_Q[42];
                link.l1 = DLG_TEXT_Q[43];
                link.l1.go = "Albermal_go_out";
                ChangeCharacterReputation(pchar, -4);
                pchar.questTemp.State = "Albermal_late";
            }
            GiveItem2Character(pchar, "letter_Albermal");
            NextDiag.TempNode = "in_the_SentJons";
        break;

        case "Albermal_go_out":
            AddQuestRecord("Eng_Line_1_Albermal", "4");
            RemovePassenger(pchar, npchar);
            DialogExit();
            // уходит
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload2", "none", "", "", "", 10.0);
            LAi_SetPlayerType(pchar);
    	    NPChar.LifeDay = 1; // уберем нпс на след.день.
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* Диалоги тюремщика по четвертому квесту английки **********************************
 		case "Step_E4_1":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "Step_E4_2";
		break;

 		case "Step_E4_2":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "Step_E4_3";
		break;

 		case "Step_E4_3":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "Step_E4_4";
		break;

 		case "Step_E4_4":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "Step_E4_5";
		break;

 		case "Step_E4_5":
			dialog.text = DLG_TEXT_Q[52]+
                          DLG_TEXT_Q[53];
			link.l1 = DLG_TEXT_Q[54];
			link.l1.go = "Step_E4_6";
		break;

 		case "Step_E4_6":
            DoQuestReloadToLocation("Villemstad_prison", "goto", "goto12", "");
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "7");
            ChangeCharacterReputation(pchar, -1);  // за обман.
            GiveItem2Character(pchar,"blade1");   // себельку герою; и этого бы не давал, но без оружия солдеры не нападают.
            EquipCharacterbyItem(pchar, "blade1");
            pchar.questTemp.State = "Intelligence_Curacao_OutPrison";
			pchar.questTemp.jailCanMove = false; //на всякий случай
			//==> делаем солдат поменьше, а то хрен выберешься 
			for (int i=1; i<=4; i++)
			{
				sld = characterFromId("VillemstadJailSold_"+i);
				if (sld.location.locator != "soldier3")
				{
					ChangeCharacterAddress(sld, "None", "");
				}
			}
			ChangeCharacterAddress(npchar, "None", "");
			DialogExit();
		break;
//*************************************** Диалог коменданта форта Оранж *********************************
        case "Step_E5_1":
            LAi_SetPlayerType(pchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "AttackFortOrange_AfterFightWithCommendant");
            ChangeCharacterHunterScore(pchar, "holhunter", 70);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

//**************************************** Диалоги Морриса Уильямса **************************************
        case "Step_E6_2":
            dialog.text = DLG_TEXT_Q[55];
            link.l1 = DLG_TEXT_Q[56];
            link.l1.go = "Step_E6_3";
        break;

        case "Step_E6_3":
            dialog.text = DLG_TEXT_Q[57];
            link.l1 = DLG_TEXT_Q[58];
            link.l1.go = "Step_E6_4";
        break;

        case "Step_E6_4":
            dialog.text = DLG_TEXT_Q[59];
            link.l1 = DLG_TEXT_Q[60];
            link.l1.go = "Step_E6_5";
        break;

        case "Step_E6_5":
            AddQuestRecord("Eng_Line_6_MorrisWillams", "4");
            pchar.questTemp.State = "MorrisWillams_ToModifordForCoolTalking";
            NextDiag.CurrentNode = "Willams_waiting";
            DialogExit();
        break;

        case "Willams_waiting": // если ГГ подойдет в таверне к Уильямсу до проведения разговора с Мэдифордом
            dialog.text = DLG_TEXT_Q[61];
            link.l1 = DLG_TEXT_Q[62];
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_waiting";
        break;

        case "Step_E6_6":
            dialog.text = DLG_TEXT_Q[63]+
                          DLG_TEXT_Q[64];
            link.l1 = DLG_TEXT_Q[65];
            link.l1.go = "Step_E6_7";
            LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); //открываем выход из города
            LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
        break;

        case "Step_E6_7":
            dialog.text = DLG_TEXT_Q[66];
            link.l1 = DLG_TEXT_Q[67];
            link.l1.go = "Willams_GoogBye";
            link.l2 = DLG_TEXT_Q[68];
            link.l2.go = "Willams_GiveMoney";
            link.l3 = DLG_TEXT_Q[69];
            link.l3.go = "Willams_BackGoods";
        break;
        
        case "Willams_GoogBye":
            dialog.text = DLG_TEXT_Q[70];
            link.l1 = DLG_TEXT_Q[71];
            link.l1.go = "exit";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.Waiting_time = "10";
            pchar.questTemp.CurQuestNumber = "7";
            ChangeCharacterReputation(pchar, -100); 
            AddCharacterExpToSkill(pchar, "Leadership", -350);
            AddCharacterExpToSkill(pchar, "Accuracy", -50);
            AddCharacterExpToSkill(pchar, "Commerce", -150);
            AddCharacterExpToSkill(pchar, "Sneak ", -150);
            AddCharacterExpToSkill(pchar, "Fencing  ", -100);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "6");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            NextDiag.TempNode = "Willams_Fack";
			//слухи
			AddSimpleRumour(DLG_TEXT_Q[72], ENGLAND, 5, 1);
        break;

        case "Willams_Fack":
            dialog.text = DLG_TEXT_Q[73] + GetFullName(pchar) + DLG_TEXT_Q[74];
            link.l1 = DLG_TEXT_Q[75];
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_Fack";
			//слухи
			AddSimpleRumour(DLG_TEXT_Q[76], ENGLAND, 5, 1);
        break;

        case "Willams_GiveMoney":
            dialog.text = DLG_TEXT_Q[77];
            link.l1 = DLG_TEXT_Q[78];
            link.l1.go = "exit";
            NextDiag.TempNode = "Step_E6_7";
            if (sti(pchar.money) >= 140000)
            {
                dialog.text = DLG_TEXT_Q[79];
                link.l1 = DLG_TEXT_Q[80];
                link.l1.go = "exit";
                SaveCurrentQuestDateParam("questTemp");
                pchar.questTemp.State = "empty";
                pchar.questTemp.Waiting_time = "5";
                pchar.questTemp.CurQuestNumber = "7";
                ChangeCharacterReputation(pchar, 20);
                AddCharacterExpToSkill(pchar, "Leadership", 150);
                AddCharacterExpToSkill(pchar, "Commerce", 250);
                AddCharacterExpToSkill(pchar, "Sneak ", 50);
                AddCharacterExpToSkill(pchar, "Defence", 150);
                AddQuestRecord("Eng_Line_6_MorrisWillams", "7");
                CloseQuestHeader("Eng_Line_6_MorrisWillams");
                AddMoneyToCharacter(pchar, -140000);
                NextDiag.TempNode = "Willams_NiceTalking";
				//слухи
				AddSimpleRumour(DLG_TEXT_Q[81], ENGLAND, 5, 1);
            }
        break;

        case "Willams_NiceTalking":
            dialog.text = DLG_TEXT_Q[82] + GetFullName(pchar) + "?";
            link.l1 = DLG_TEXT_Q[83];
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_NiceTalking";
        break;

        case "Willams_BackGoods":
            dialog.text = DLG_TEXT_Q[84]+
                          DLG_TEXT_Q[85];
            link.l1 = DLG_TEXT_Q[86];
            link.l1.go = "Step_E6_8";
        break;
        
        case "Step_E6_8":
            dialog.text = DLG_TEXT_Q[87]+
                          DLG_TEXT_Q[88];
            link.l1 = DLG_TEXT_Q[89];
            link.l1.go = "Step_E6_9";
        break;

        case "Step_E6_9":
            dialog.text = DLG_TEXT_Q[90];
            link.l1 = DLG_TEXT_Q[91];
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
            pchar.questTemp.State = "MorrisWillams_SeekSpanishGoods";
            AddQuestRecord("Eng_Line_6_MorrisWillams", "8");
        break;

        case "Willams_WaitSeek":
            dialog.text = DLG_TEXT_Q[92];
            link.l1 = DLG_TEXT_Q[93];
            link.l1.go = "exit";
            NextDiag.TempNode = "Willams_WaitSeek";
        break;

        case "Step_E6_10":
            dialog.text = DLG_TEXT_Q[94];
            link.l1 = DLG_TEXT_Q[95];
            link.l1.go = "MorrisWillams_NotGiveMoney";
            link.l2 = DLG_TEXT_Q[96];
            link.l2.go = "MorrisWillams_GiveMoney";
            NextDiag.TempNode = "Willams_NiceTalking";
            SaveCurrentQuestDateParam("questTemp");
            pchar.questTemp.State = "empty";
            pchar.questTemp.CurQuestNumber = "7";
        break;

        case "MorrisWillams_NotGiveMoney":
            dialog.text = DLG_TEXT_Q[97];
            link.l1 = DLG_TEXT_Q[98];
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.Waiting_time = "10";
            ChangeCharacterReputation(pchar, -100);
            AddCharacterExpToSkill(pchar, "Leadership", -150);
            AddCharacterExpToSkill(pchar, "Accuracy", -200);
            AddCharacterExpToSkill(pchar, "Commerce", -250);
            AddCharacterExpToSkill(pchar, "Sneak ", -170);
            AddCharacterExpToSkill(pchar, "Fencing  ", -140);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "13");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
			//слухи
			AddSimpleRumour(DLG_TEXT_Q[99], ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GiveMoney":
        if (sti(pchar.money) >= 140000)
        {
            dialog.text = DLG_TEXT_Q[100];
            link.l1 = DLG_TEXT_Q[101];
            link.l1.go = "Step_E6_14";
        }
        else
        {
            dialog.text = DLG_TEXT_Q[102];
            link.l1 = DLG_TEXT_Q[103];
            link.l1.go = "exit";
            NextDiag.TempNode = "MorrisWillams_GiveMoney";
        }
        break;

        case "Step_E6_14":
            dialog.text = DLG_TEXT_Q[104]+
                          DLG_TEXT_Q[105]+
                          DLG_TEXT_Q[106]+
                          DLG_TEXT_Q[107]+
                          DLG_TEXT_Q[108]+
                          DLG_TEXT_Q[109]+
                          DLG_TEXT_Q[110]+
                          DLG_TEXT_Q[111];
            link.l1 = DLG_TEXT_Q[112];
            link.l1.go = "exit";
            pchar.questTemp.Waiting_time = "2";
            ChangeCharacterReputation(pchar, 20);
            AddCharacterExpToSkill(pchar, "Leadership", 250);
            AddCharacterExpToSkill(pchar, "Accuracy", 100);
            AddCharacterExpToSkill(pchar, "Commerce", 250);
            AddCharacterExpToSkill(pchar, "Sneak", 70);
            AddCharacterExpToSkill(pchar, "Fencing", 150);
            AddCharacterExpToSkill(pchar, "Defence", 150);
            AddQuestRecord("Eng_Line_6_MorrisWillams", "14");
            CloseQuestHeader("Eng_Line_6_MorrisWillams");
            AddMoneyToCharacter(pchar, -140000);
            NextDiag.TempNode = "Willams_NiceTalking";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
            Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
			//слухи
			AddSimpleRumour(DLG_TEXT_Q[113], ENGLAND, 5, 1);
        break;

        case "MorrisWillams_GoAway":
			chrDisableReloadToLocation = true;
            LAi_SetActorType(npchar);
            ChangeCharacterAddressGroup(npchar, "PortRoyal_tavern", "tables", "stay8");
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
            NextDiag.CurrentNode = "First time";
            DialogExit();
        break;

        case "Step_E6_11":
            dialog.text = DLG_TEXT_Q[114];
            link.l1 = DLG_TEXT_Q[115];
            link.l1.go = "Step_E6_12";
            link.l2 = DLG_TEXT_Q[116];
            link.l2.go = "Willams_GoogBye";
        break;

        case "Step_E6_12":
            dialog.text = DLG_TEXT_Q[117];
            link.l1 = DLG_TEXT_Q[118];
            link.l1.go = "Step_E6_13";
        break;

        case "Step_E6_13":
            dialog.text = DLG_TEXT_Q[119] + pchar.name + DLG_TEXT_Q[120];
            link.l1 = DLG_TEXT_Q[121];
            link.l1.go = "MorrisWillams_GoAway";
            pchar.questTemp.State = "MorrisWillams_GoToHimselfBussines"
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MorrisWillams_Arrest.win_condition.l1.location = "PortRoyal_tavern";
            Pchar.quest.MorrisWillams_Arrest.win_condition = "MorrisWillams_Arrest";
        break;

        case "Step_E6_20":
			dialog.text = DLG_TEXT_Q[122]+
                          DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "Step_E6_21";
        break;
        case "Step_E6_21":
			dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "Step_E6_22";
        break;
        case "Step_E6_22":
			dialog.text = DLG_TEXT_Q[127]+
                          DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Step_E6_23";
        break;
        case "Step_E6_23":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "Step_E6_24";
        break;
        case "Step_E6_24":
			dialog.text = DLG_TEXT_Q[132]+
                          DLG_TEXT_Q[133];
			link.l1 = DLG_TEXT_Q[134];
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_AfterFirstTalkingWithMorris";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "2");
        break;

//**************************************** Диалоги Томаса Линча **************************************
        case "Step_E12_1":
            dialog.text = DLG_TEXT_Q[135];
            link.l1 = DLG_TEXT_Q[136];
            link.l1.go = "Step_E12_2";
        break;

        case "Step_E12_2":
            dialog.text = DLG_TEXT_Q[137];
            link.l1 = DLG_TEXT_Q[138];
            link.l1.go = "Step_E12_3";
        break;

        case "Step_E12_3":
            dialog.text = DLG_TEXT_Q[139]+
                          DLG_TEXT_Q[140]+
                          DLG_TEXT_Q[141];
            link.l1 = DLG_TEXT_Q[142];
            link.l1.go = "Step_E12_4";
        break;

        case "Step_E12_4":
            dialog.text = DLG_TEXT_Q[143]+
                          DLG_TEXT_Q[144];
            link.l1 = DLG_TEXT_Q[145];
            link.l1.go = "Step_E12_5";
        break;

        case "Step_E12_5":
            dialog.text = DLG_TEXT_Q[146]+
                          DLG_TEXT_Q[147]+
                          DLG_TEXT_Q[148];
            link.l1 = DLG_TEXT_Q[149];
            link.l1.go = "Step_E12_6";
        break;

        case "Step_E12_6":
            dialog.text = DLG_TEXT_Q[150]+
                          DLG_TEXT_Q[151];
            link.l1 = DLG_TEXT_Q[152];
            link.l1.go = "Step_E12_7";
        break;

        case "Step_E12_7":
            dialog.text = DLG_TEXT_Q[153]+
                          DLG_TEXT_Q[154];
            link.l1 = DLG_TEXT_Q[155];
            link.l1.go = "Step_E12_8";
        break;

        case "Step_E12_8":
            dialog.text = DLG_TEXT_Q[156];
            link.l1 = DLG_TEXT_Q[157];
            link.l1.go = "Step_E12_9";

        break;
        
        case "Step_E12_9":
            dialog.text = DLG_TEXT_Q[158]+
                          DLG_TEXT_Q[159]+
                          DLG_TEXT_Q[160];
            link.l1 = DLG_TEXT_Q[161];
            link.l1.go = "Step_E12_10";
        break;

         case "Step_E12_10":
            dialog.text = DLG_TEXT_Q[162]+
                          DLG_TEXT_Q[163]+
                          DLG_TEXT_Q[164];
            link.l1 = DLG_TEXT_Q[165];
            link.l1.go = "Step_E12_11";
        break;

         case "Step_E12_11":
            dialog.text = DLG_TEXT_Q[166];
            link.l1 = DLG_TEXT_Q[167];
            link.l1.go = "Step_E12_12";
        break;
        
         case "Step_E12_12":
            dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
            link.l1.go = "Step_E12_13";
        break;
        
        case "Step_E12_13":
            dialog.text = DLG_TEXT_Q[170] + GetFullName(pchar) + ".";
            link.l1 = DLG_TEXT_Q[171];
            link.l1.go = "Step_E12_14";
        break;

        case "Step_E12_14":
            dialog.text = DLG_TEXT_Q[172]+
                          DLG_TEXT_Q[173];
            link.l1 = DLG_TEXT_Q[174];
            link.l1.go = "exit";
            pchar.questTemp.State = "ColonelLinch_ArrestModiford";
            AddQuestRecord("Eng_Line_12_ColonelLinch", "2");
            LAi_SetPlayerType(pchar);
            LAi_SetStayType(npchar);
            NextDiag.TempNode = "YouMustGo";
        break;

        case "YouMustGo":
            dialog.text = DLG_TEXT_Q[175];
            link.l1 = DLG_TEXT_Q[176];
            link.l1.go = "exit";
            NextDiag.TempNode = "YouMustGo";
        break;
    }
}
