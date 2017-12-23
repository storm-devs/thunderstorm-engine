#include "TEXT\DIALOGS\Usurer\Villemstad_Usurer.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
   	float locx, locy, locz;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[0], DLG_TEXT_USR[1]), DLG_TEXT_USR[2], DLG_TEXT_USR[3],
                          DLG_TEXT_USR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_USR[5], DLG_TEXT_USR[6]), DLG_TEXT_USR[7],
                      DLG_TEXT_USR[8], DLG_TEXT_USR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> англ.линейка квест №4 Разведмиссию в Кюрасао
			if (pchar.questTemp.State == "Intelligence_Curacao_toYozef")
            {
                link.l1 = DLG_TEXT_USR[10];
                link.l1.go = "Step_E4_1";
            }
			if (pchar.questTemp.State == "Intelligence_Curacao_NoMoney_Yozef")
            {
                link.l1 = DLG_TEXT_USR[11];
                link.l1.go = "no_money";
            }
            if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco" )// квест №2 голл. линейки.
            {
                if (!CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
        			dialog.text = DLG_TEXT_USR[12];
        			link.l1 = DLG_TEXT_USR[13];
        			link.l1.go = "Step_S2_1";
                }
                else
                {
                    if (CheckPassengerInCharacter(pchar, "JansenDeFonceicao"))
                    {
                        dialog.text = DLG_TEXT_USR[14];
            			link.l1 = DLG_TEXT_USR[15];
            			link.l1.go = "Step_S2_5";
                    }
                    else
                    {
                        if (pchar.questTemp.State.Usurer != "Ok")
                        {
                            dialog.text = DLG_TEXT_USR[16];
                			link.l1 = DLG_TEXT_USR[17];
                			link.l1.go = "exit";
                        }
                        else
                        {
                            dialog.text = DLG_TEXT_USR[18];
                			link.l1 = DLG_TEXT_USR[19];
                			link.l1.go = "exit";
                        }
                    }
                }
            }
			//пиратка, квест №5
			if (pchar.questTemp.piratesLine == "PL5Hunter_toVillemstad")
            {
				link.l1 = DLG_TEXT_USR[20];
				link.l1.go = "Step_P5_1";
			}
		break;
//********************** Английская линейка, квест №4 DLG_TEXT_USR[21] ************************
		case "Step_E4_1":
			dialog.text = DLG_TEXT_USR[22];
			link.l1 = DLG_TEXT_USR[23];
			link.l1.go = "Step_E4_2";
		break;
		case "Step_E4_2":
			dialog.text = DLG_TEXT_USR[24];
			link.l1 = DLG_TEXT_USR[25];
			link.l1.go = "Step_E4_3";
		break;
		case "Step_E4_3":
			dialog.text = DLG_TEXT_USR[26];
			link.l1 = DLG_TEXT_USR[27];
			link.l1.go = "agree_to_pay";
			link.l2 = DLG_TEXT_USR[28];
			link.l2.go = "no_money_now";
			link.l3 = DLG_TEXT_USR[29];
			link.l3.go = "fack_yozef";
		break;
		case "agree_to_pay":
            if (sti(pchar.money) >= 100000)
            {
        		dialog.text = DLG_TEXT_USR[30]+
                         DLG_TEXT_USR[31];
        		link.l1 = DLG_TEXT_USR[32];
        		link.l1.go = "exit";
        		AddMoneyToCharacter(pchar, -100000);
        		AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "3");
        		pchar.questTemp.State = "Intelligence_Curacao_GaveMoneyYozef"; // заглушка на повторный вывод данного пункта в меню.
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
                Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
                Log_QuestInfo(DLG_TEXT_USR[33]);
            }
            else
            {
        		dialog.text = DLG_TEXT_USR[34];
        		link.l1 = DLG_TEXT_USR[35];
        		link.l1.go = "exit";
        		pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
        		//ChangeCharacterReputation(pchar, -1); TO_DO eddy
            }
		break;
		case "no_money_now":
			dialog.text = DLG_TEXT_USR[36];
			link.l1 = DLG_TEXT_USR[37];
			link.l1.go = "exit";
            if (pchar.questTemp.State != "Intelligence_Curacao_NoMoney_Yozef")
            {
                AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "4");
            }
            pchar.questTemp.State = "Intelligence_Curacao_NoMoney_Yozef";
		break;
		case "no_money":
			dialog.text = DLG_TEXT_USR[38];
			link.l1 = DLG_TEXT_USR[39];
			link.l1.go = "agree_to_pay";
			link.l2 = DLG_TEXT_USR[40];
			link.l2.go = "no_money_now";
			link.l3 = DLG_TEXT_USR[41];
			link.l3.go = "fack_yozef";
		break;
		case "fack_yozef":    // посыл Йозефа с попыткой замочить
			dialog.text = DLG_TEXT_USR[42];
			link.l1 = DLG_TEXT_USR[43];
			link.l1.go = "Step_E4_4";
		break;
		case "Step_E4_4":
			dialog.text = DLG_TEXT_USR[44];
			link.l1 = DLG_TEXT_USR[45];
			link.l1.go = "Step_E4_5"; 
		break;
		case "Step_E4_5":
            pchar.questTemp.State = "Intelligence_Curacao_FightGard";
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
            AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "5");
            LAi_NoRebirthEnable(npchar);
            LAi_group_Register("EnemyFight");
            GetCharacterPos(pchar, &locx, &locy, &locz);
            for (int i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("HolSolder"+i, "sold_hol_"+i, "man", "man", 20, HOLLAND, 0, true));
                FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 40);
            	LAi_SetWarriorType(sld);
                LAi_group_MoveCharacter(sld, "EnemyFight");
               	ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            }
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_SetCheckMinHP(pchar, 10, true, "Intelligence_Curacao_KickYozef");
            LAi_SetPlayerType(pchar);
            LAi_SetFightMode(pchar, true);
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1 = "location";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition.l1.location = "Curacao";
            Pchar.quest.Intelligence_Curacao_GoToShore.win_condition = "Intelligence_Curacao_GoToShore";
			DialogExit();
		break;
//********************** Испанская линейка, квест №2 DLG_TEXT_USR[46] ************************
		case "Step_S2_1":
			dialog.text = DLG_TEXT_USR[47];
			link.l1 = DLG_TEXT_USR[48];
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = DLG_TEXT_USR[49];
			link.l1 = DLG_TEXT_USR[50];
			link.l1.go = "Step_S2_3";
			link.l2 = DLG_TEXT_USR[51];
			link.l2.go = "Step_S2_4";
		break;
		case "Step_S2_3":
			dialog.text = DLG_TEXT_USR[52];
			link.l1 = DLG_TEXT_USR[53];
			link.l1.go = "Step_S2_fihgt";
		break;
		case "Step_S2_fihgt":
			bDisableFastReload = false; 
            AddQuestRecord("Spa_Line_2_Inquisition", "4");
            LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], false);
            LAi_NoRebirthEnable(npchar);
            LAi_SetImmortal(npchar, false);
            LAi_SetActorType(npchar);
            LAi_ActorAfraid(npchar, pchar, false);
            sld = GetCharacter(NPC_GenerateCharacter("Andrew", "shipowner_7", "man", "man", 35, HOLLAND, 10, true));
            FantomMakeCoolFighter(sld, 35, 80, 60, BLADE_LONG, "pistol3", 70);
        	LAi_SetWarriorType(sld);
			LAi_NoRebirthEnable(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
            GetCharacterPos(pchar, &locx, &locy, &locz);
           	ChangeCharacterAddressGroup(sld, "Villemstad_bank", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			Pchar.quest.Inquisition_afterFightAndrew.win_condition.l1 = "MapEnter";
            Pchar.quest.Inquisition_afterFightAndrew.win_condition = "Inquisition_afterFightAndrew";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Step_S2_4":
			dialog.text = DLG_TEXT_USR[54];
			link.l1 = DLG_TEXT_USR[55];
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "5");
			pchar.questTemp.State.Usurer = 1;
		break;
		case "Step_S2_5":
			dialog.text = DLG_TEXT_USR[56];
			link.l1 = DLG_TEXT_USR[57];
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = DLG_TEXT_USR[58];
			link.l1 = DLG_TEXT_USR[59];
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = DLG_TEXT_USR[60];
			link.l1 = DLG_TEXT_USR[61];
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
            AddQuestRecord("Spa_Line_2_Inquisition", "10");
			ReleasePrisoner(characterFromId("JansenDeFonceicao"));
            AddMoneyToCharacter(pchar, 50000);
            pchar.questTemp.State.Usurer = "Ok"; //бабки получены
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
//********************** Пиратская линейка, квест №5 ОГЗ ************************
		case "Step_P5_1":
			dialog.text = DLG_TEXT_USR[62];
			link.l1 = DLG_TEXT_USR[63];
			link.l1.go = "Step_P5_2";
		break;	
		case "Step_P5_2":
			dialog.text = DLG_TEXT_USR[64];
			link.l1 = DLG_TEXT_USR[65];
			link.l1.go = "Step_P5_3";
		break;
		case "Step_P5_3":
			pchar.questTemp.piratesLine.Q5.city_1 = GetQuestNationsCity(ENGLAND); 
			dialog.text = DLG_TEXT_USR[66] + XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Dat") + DLG_TEXT_USR[67];
			link.l1 = DLG_TEXT_USR[68];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "2");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandByCityName(pchar.questTemp.piratesLine.Q5.city_1) + "Dat"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirst";
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

