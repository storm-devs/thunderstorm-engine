#include "TEXT\DIALOGS\Mayor\Jackman.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "BlueBird_1") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[0],
                         DLG_TEXT_MR[1], DLG_TEXT_MR[2],
                         DLG_TEXT_MR[3], "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[4],
                                               DLG_TEXT_MR[5],
                                               DLG_TEXT_MR[6],
                                               DLG_TEXT_MR[7], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			//поиски шебеки Синяя Птица
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_MR[8];
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = DLG_TEXT_MR[9];
				link.l1.go = "BlueBird_6";
			}
			//жемчужный генератор Шарпа
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = DLG_TEXT_MR[10];
				link.l1.go = "SharpPearl_1";
			}
			//пиратскся линейка начало
			if (pchar.questTemp.piratesLine == "begin")
			{
				link.l1 = DLG_TEXT_MR[11];
				link.l1.go = "PL_Q1_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = DLG_TEXT_MR[12];
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{				
				dialog.text = DLG_TEXT_MR[13];
				link.l1 = DLG_TEXT_MR[14];
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = DLG_TEXT_MR[15];
				link.l1 = DLG_TEXT_MR[16];
				link.l1.go = "PL_SEAWOLF";				
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = DLG_TEXT_MR[17] + pchar.name + DLG_TEXT_MR[18];
				link.l1 = DLG_TEXT_MR[19];
				link.l1.go = "PL_Q8";				
			}
			//поиски супер-мушкета
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = DLG_TEXT_MR[20];
				link.l1.go = "Mushket";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + DLG_TEXT_MR[21],
                         DLG_TEXT_MR[22], DLG_TEXT_MR[23],
                         DLG_TEXT_MR[24], "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[25],
                                               DLG_TEXT_MR[26],
                                               DLG_TEXT_MR[27],
                                               DLG_TEXT_MR[28], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			//поиски шебеки Синяя Птица
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_MR[29];
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = DLG_TEXT_MR[30];
				link.l1.go = "BlueBird_6";
			}
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = DLG_TEXT_MR[31];
				link.l1.go = "SharpPearl_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = DLG_TEXT_MR[32];
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{				
				dialog.text = DLG_TEXT_MR[33];
				link.l1 = DLG_TEXT_MR[34];
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = DLG_TEXT_MR[35];
				link.l1 = DLG_TEXT_MR[36];
				link.l1.go = "PL_SEAWOLF";				
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = DLG_TEXT_MR[37] + pchar.name + DLG_TEXT_MR[38];
				link.l1 = DLG_TEXT_MR[39];
				link.l1.go = "PL_Q8";				
			}
			//поиски супер-мушкета
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = DLG_TEXT_MR[20];
				link.l1.go = "Mushket";
			}
		break;
		//********************* пиратка, направление на квест №1 *********************
		case "PL_Q1_1":
			dialog.text = DLG_TEXT_MR[40];
			link.l1 = DLG_TEXT_MR[41];
			link.l1.go = "PL_Q1_2";
		break;
		case "PL_Q1_2":
			dialog.text = DLG_TEXT_MR[42];
			link.l1 = DLG_TEXT_MR[43];
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "toFirstQuest";
			AddQuestRecord("Pir_Line_0_Waiting", "2");
		break;
		//********************* пиратка, квест №3, поиски Лоу *********************
		case "PL_Q3_1":
			dialog.text = DLG_TEXT_MR[44];
			link.l1 = DLG_TEXT_MR[45];
			link.l1.go = "PL_Q3_fight";
		break;
		case "PL_Q3_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("QuestPir_"+i, "pirate_"+i, "man", "man", 100, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 100, 100, 100, "topor2", "pistol3", 100);
            	LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, true);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
            }
            LAi_group_SetLookRadius("PIRATE_CITIZENS", 100);
            LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("PIRATE_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q3_2":
			dialog.text = DLG_TEXT_MR[46];
			link.l1 = DLG_TEXT_MR[47];
			link.l1.go = "PL_Q3_3";	
		break;
		case "PL_Q3_3":
			dialog.text = DLG_TEXT_MR[48];
			link.l1 = DLG_TEXT_MR[49];
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = DLG_TEXT_MR[50];
			link.l1 = DLG_TEXT_MR[51];
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = DLG_TEXT_MR[52]+
				DLG_TEXT_MR[53]+
				DLG_TEXT_MR[54];
			link.l1 = DLG_TEXT_MR[55];
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = DLG_TEXT_MR[56];
			link.l1 = DLG_TEXT_MR[57];
			link.l1.go = "PL_Q3_7";
		break;
		case "PL_Q3_7":
			dialog.text = DLG_TEXT_MR[58]+
				DLG_TEXT_MR[59]+
				DLG_TEXT_MR[60]+
				DLG_TEXT_MR[61];
			link.l1 = DLG_TEXT_MR[62];
			link.l1.go = "PL_Q3_8";
		break;
		case "PL_Q3_8":
			dialog.text = DLG_TEXT_MR[63];
			link.l1 = DLG_TEXT_MR[64];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Pir_Line_3_KillLoy", "12");
			pchar.questTemp.piratesLine = "KillLoy_2toTavernAgain";
		break;
		//после поисков Лоу
		case "PL_SEAWOLF":
			NextDiag.TempNode = "I_know_you_good";
			npchar.quest.PQ3 = true;
			int chComp;
			bool bOk = false;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
				chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "BrigSW1")
        		{	
					bOk = true;
					break;
				}
			}
			if (bOk)
			{
				dialog.text = DLG_TEXT_MR[65];
				link.l1 = DLG_TEXT_MR[66];
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "19");	
			}
			else
			{
				dialog.text = DLG_TEXT_MR[67];
				link.l1 = DLG_TEXT_MR[68];
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, 20000);
				AddQuestRecord("Pir_Line_3_KillLoy", "20");	
			}
		break;
		//********************* пиратка, квест №6. двойник *********************
		case "PL_Q6":
			dialog.text = DLG_TEXT_MR[69];
			link.l1 = DLG_TEXT_MR[70];
			link.l1.go = "PL_Q6_1";
		break;
		case "PL_Q6_1":
			dialog.text = DLG_TEXT_MR[71];
			link.l1 = DLG_TEXT_MR[72];
			link.l1.go = "PL_Q6_2";
		break;
		case "PL_Q6_2":
			dialog.text = DLG_TEXT_MR[73];
			link.l1 = DLG_TEXT_MR[74];
			link.l1.go = "PL_Q6_3";
		break;
		case "PL_Q6_3":
			dialog.text = DLG_TEXT_MR[75];
			link.l1 = DLG_TEXT_MR[76];
			link.l1.go = "PL_Q6_4";
		break;
		case "PL_Q6_4":
			dialog.text = DLG_TEXT_MR[77];
			link.l1 = DLG_TEXT_MR[78];
			link.l1.go = "PL_Q6_5";
		break;
		case "PL_Q6_5":
			dialog.text = DLG_TEXT_MR[79];
			link.l1 = DLG_TEXT_MR[80];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "2");
			pchar.questTemp.piratesLine = "PL6Brother_toSantaCatalina";
			//ставим Джона Лидса в залив Косумель
			sld = GetCharacter(NPC_GenerateCharacter("JohnLids", "officer_10", "man", "man", 30, sti(pchar.nation), -1, true));	
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, DLG_TEXT_MR[81], CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			sld.name = DLG_TEXT_MR[82];
			sld.lastname = DLG_TEXT_MR[83];
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "First time";	        
			sld.DeckDialogNode = "JohnLids";		
			sld.Abordage.Enable = false;
			sld.AnalizeShips = true; 
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Ship.Mode = "Pirate";
			sld.greeting = "Gr_MiddPirate";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			Group_AddCharacter("LidsGroup", "JohnLids");
			Group_SetGroupCommander("LidsGroup", "JohnLids");			
			Group_SetAddress("LidsGroup", "Beliz", "quest_ships", "Quest_ship_11");
			Group_SetTaskNone("LidsGroup");
		break;

		case "PL_Q6_after":
			dialog.text = DLG_TEXT_MR[84];
			link.l1 = DLG_TEXT_MR[85];
			link.l1.go = "PL_Q6_after_1";
		break;
		case "PL_Q6_after_1":
			dialog.text = DLG_TEXT_MR[86];
			link.l1 = DLG_TEXT_MR[87];
			link.l1.go = "PL_Q6_after_2";
		break;
		case "PL_Q6_after_2":
			dialog.text = DLG_TEXT_MR[88];
			link.l1 = DLG_TEXT_MR[89];
			link.l1.go = "PL_Q6_after_3";
		break;
		case "PL_Q6_after_3":
			dialog.text = DLG_TEXT_MR[90];
			link.l1 = DLG_TEXT_MR[91];
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "5");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_begin");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		break;


		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = DLG_TEXT_MR[92];
			link.l1 = DLG_TEXT_MR[93];
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = DLG_TEXT_MR[94];
			link.l1 = DLG_TEXT_MR[95];
			link.l1.go = "exit";
		break;

        //********************** поиски Синей птицы ***********************
        case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[96], 
				DLG_TEXT_MR[97], 
				DLG_TEXT_MR[98],
                DLG_TEXT_MR[99], "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[100], 
				DLG_TEXT_MR[101],
                DLG_TEXT_MR[102], 
				DLG_TEXT_MR[103], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
  		break;
		case "BlueBird_2":
			dialog.text = DLG_TEXT_MR[104];
			link.l1 = DLG_TEXT_MR[105];
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = DLG_TEXT_MR[106];
			link.l1 = DLG_TEXT_MR[107];
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = DLG_TEXT_MR[108];
			link.l1 = DLG_TEXT_MR[109];
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = DLG_TEXT_MR[110];
			link.l1 = DLG_TEXT_MR[111];
			link.l1.go = "exit";
		break;

		case "BlueBird_6":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[112], 
				DLG_TEXT_MR[113], 
				DLG_TEXT_MR[114],
                DLG_TEXT_MR[115], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[116], 
				DLG_TEXT_MR[117],
                DLG_TEXT_MR[118], 
				DLG_TEXT_MR[119], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
        //********************** Английская линейка ***********************
 		case "EngLine_quests":
			dialog.text = DLG_TEXT_MR[120];
			link.l1 = DLG_TEXT_MR[121];
			link.l1.go = "Step_1";
  		break;

 		case "Step_1":
			dialog.text = DLG_TEXT_MR[122];
			link.l1 = DLG_TEXT_MR[123];
			link.l1.go = "Step_2";
  		break;
  		
 		case "Step_2":
			dialog.text = DLG_TEXT_MR[124];
			link.l1 = DLG_TEXT_MR[125];
			link.l1.go = "Step_3";
  		break;
  		
 		case "Step_3":
			dialog.text = DLG_TEXT_MR[126];
			link.l1 = DLG_TEXT_MR[127];
			link.l1.go = "Step_4";
  		break;
  		
 		case "Step_4":
			dialog.text = DLG_TEXT_MR[128];
			link.l1 = DLG_TEXT_MR[129];
			link.l1.go = "Step_5";
  		break;
  		
 		case "Step_5":
			dialog.text = DLG_TEXT_MR[130];
			link.l1 = DLG_TEXT_MR[131];
			link.l1.go = "exit";
			
            AddQuestRecord("Eng_Line_2_Talking", "4");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = DLG_TEXT_MR[132];
			link.l1 = DLG_TEXT_MR[133];
			link.l1.go = "Step_6";
  		break;

 		case "Step_6":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = DLG_TEXT_MR[134];
    			link.l1 = DLG_TEXT_MR[135];
    			link.l1.go = "Step_7";
            }
            else
            {
    			dialog.text = DLG_TEXT_MR[136];
    			link.l1 = DLG_TEXT_MR[137];
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
  		break;

 		case "Step_7":
			AddQuestRecord("Eng_Line_3_Morgan", "4");
            LAi_SetActorType(npchar);
            LAi_ActorSetStayMode(npchar);
            ChangeCharacterAddressGroup(npchar, "Pirates_townhall", "goto", "governor1");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 10, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Jackman = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // Если геймеру вдруг захочется еще пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = DLG_TEXT_MR[138];
            link.l1 = DLG_TEXT_MR[139];
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman") && !IsCompanion(characterFromID("Jackman")))
    		{
            	dialog.text = DLG_TEXT_MR[140]+
                              DLG_TEXT_MR[141]+
                              DLG_TEXT_MR[142];
            }
            else
            {
    			dialog.text = DLG_TEXT_MR[143]+
                              DLG_TEXT_MR[144];
            }
            link.l1 = DLG_TEXT_MR[145];
			link.l1.go = "Step_8";
        break;

	 	case "Step_8":
			dialog.text = DLG_TEXT_MR[146] + pchar.name + " " + pchar.lastname + DLG_TEXT_MR[147]+
                          DLG_TEXT_MR[148];
			link.l1 = DLG_TEXT_MR[149];
			link.l1.go = "Step_9";
        break;

	 	case "Step_9":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;
        //********************** Голландская линейка ***********************
 		case "HolLine8_quest":
			dialog.text = DLG_TEXT_MR[150];
			link.l1 = DLG_TEXT_MR[151];
			link.l1.go = "Step_H8_1";
  		break;
 		case "Step_H8_1":
			dialog.text = DLG_TEXT_MR[152];
			link.l1 = DLG_TEXT_MR[153];
			link.l1.go = "Step_H8_2";
  		break;
 		case "Step_H8_2":
			dialog.text = DLG_TEXT_MR[154];
			link.l1 = DLG_TEXT_MR[155];
			link.l1.go = "Step_H8_3";
  		break;
 		case "Step_H8_3":
			dialog.text = DLG_TEXT_MR[156];
			link.l1 = DLG_TEXT_MR[157];
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "3");
			pchar.questTemp.State = "SeekBible_toFFBrothel";
			NextDiag.TempNode = "First time";
  		break;
		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = DLG_TEXT_MR[158] + GetFullName(pchar) + DLG_TEXT_MR[159];
            link.l1 = DLG_TEXT_MR[160];
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = DLG_TEXT_MR[161];
            link.l1 = DLG_TEXT_MR[162];
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "5");
        break;
		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = DLG_TEXT_MR[163];
			link.l1 = DLG_TEXT_MR[164];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = DLG_TEXT_MR[165];
			link.l1 = DLG_TEXT_MR[166];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8":
			dialog.text = DLG_TEXT_MR[167];
			link.l1 = DLG_TEXT_MR[168];
			link.l1.go = "PL_Q8_1";
		break;
		case "PL_Q8_1":
			dialog.text = DLG_TEXT_MR[169];
			link.l1 = DLG_TEXT_MR[170];
			link.l1.go = "PL_Q8_2";
		break;
		case "PL_Q8_2":
			dialog.text = DLG_TEXT_MR[171];
			link.l1 = DLG_TEXT_MR[172];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_inEngland";
		break;
		//поиски супер-мушкета
		case "Mushket":
			dialog.text = DLG_TEXT_MR[173];
			link.l1 = DLG_TEXT_MR[174];
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = DLG_TEXT_MR[175];
			link.l1 = DLG_TEXT_MR[176];
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = DLG_TEXT_MR[177];
			link.l1 = DLG_TEXT_MR[178];
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "2");
		break;
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[179], DLG_TEXT_MR[180]);
			link.l1 = DLG_TEXT_MR[181];
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[182];
        			link.l1 = DLG_TEXT_MR[183];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[184], DLG_TEXT_MR[185]);
			link.l1 = RandPhraseSimple(DLG_TEXT_MR[186], DLG_TEXT_MR[187]);
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[188];
        			link.l1 = DLG_TEXT_MR[189];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Pirates_town","reload","reload3");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
