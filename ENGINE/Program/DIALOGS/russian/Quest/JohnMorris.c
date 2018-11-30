#include "TEXT\DIALOGS\Quest\JohnMorris.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = DLG_TEXT_Q[2];
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			dialog.text = LinkRandPhrase(GetFullName(pchar) + DLG_TEXT_Q[3],
                                         RandSwear() + DLG_TEXT_Q[4] + GetFullName(pchar) + DLG_TEXT_Q[5],
                                         DLG_TEXT_Q[6]+ GetFullName(pchar)+ DLG_TEXT_Q[7]);
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[8], DLG_TEXT_Q[9]);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = DLG_TEXT_Q[10];
				link.l1.go = "SharpPearl_1";
			}
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = DLG_TEXT_Q[13];
			link.l1 = DLG_TEXT_Q[14];
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
 		case "EngLine_quests":
            dialog.text = DLG_TEXT_Q[15];
			link.l1 = DLG_TEXT_Q[16];
			link.l1.go = "exit";
			switch (pchar.questTemp.State)   // Доступ к квестам
            {
	     		case "go_talks_with_pirates":
	    			dialog.text = DLG_TEXT_Q[17];
	    			link.l1 = DLG_TEXT_Q[18];
	    			link.l1.go = "Step_1";
	      		break;
            }
		break;

 		case "Step_1":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "Step_2";
  		break;
  		
 		case "Step_2":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "Step_3";
  		break;
  		
 		case "Step_3":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "Step_4";
  		break;
  		
 		case "Step_4":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "exit";
			
            AddQuestRecord("Eng_Line_2_Talking", "5");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "Step_5";
  		break;

 		case "Step_5":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = DLG_TEXT_Q[29];
    			link.l1 = DLG_TEXT_Q[30];
    			link.l1.go = "Step_6";
            }
            else
            {
    			dialog.text = DLG_TEXT_Q[31];
    			link.l1 = DLG_TEXT_Q[32];
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
            
  		break;

 		case "Step_6":
			AddQuestRecord("Eng_Line_3_Morgan", "5");
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortSpein_houseF2", "goto", "goto3");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 6, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Morris = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // Если геймеру вдруг захочется еще пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris") && !IsCompanion(characterFromID("John Morris")))
    		{
            	dialog.text = DLG_TEXT_Q[35]+
                              DLG_TEXT_Q[36];
            }
            else
            {
            	dialog.text = DLG_TEXT_Q[37];
            }
			link.l1 = DLG_TEXT_Q[38];
			link.l1.go = "Step_7";
        break;

	 	case "Step_7":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40];
			link.l1.go = "Step_8";
        break;
        
	 	case "Step_8":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;

		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = DLG_TEXT_Q[41];
            link.l1 = DLG_TEXT_Q[42] + GetFullName(pchar) + DLG_TEXT_Q[43];
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = DLG_TEXT_Q[44];
            link.l1 = DLG_TEXT_Q[45];
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = DLG_TEXT_Q[46];
            link.l1 = DLG_TEXT_Q[47];
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = DLG_TEXT_Q[48];
            link.l1 = DLG_TEXT_Q[49];
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = DLG_TEXT_Q[50];
            link.l1 = DLG_TEXT_Q[51];
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = DLG_TEXT_Q[52];
            link.l1 = DLG_TEXT_Q[53];
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = DLG_TEXT_Q[54];
            link.l1 = DLG_TEXT_Q[55];
            link.l1.go = "Step_F8_7";
        break;
        case "Step_F8_7":
            dialog.text = DLG_TEXT_Q[56];
            link.l1 = DLG_TEXT_Q[57];
            link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "6");
			NextDiag.TempNode = "Step_F8_Result";
			// ==> открываем дверь таверны Порт Рояля - там кэп Гей.
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_tavern_upstairs")], false);
            ref sld = GetCharacter(NPC_GenerateCharacter("CaptainGay", "bocman", "man", "man", 40, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 40, 100, 90, "blade34", "pistol5", 150);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
        	sld.name 	= DLG_TEXT_Q[58];
        	sld.lastname 	= DLG_TEXT_Q[59];
			sld.items.ShipsJournal = 1;
			sld.money = 65720;
			sld.items.potion4 = 4;
			sld.items.potionrum = 1;
			sld.items.potionwine = 2;
			sld.items.sculMa2 = 1;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 15;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetStayType(sld); 
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "goto", "goto1");
		break;
        case "Step_F8_Result":
            dialog.text = DLG_TEXT_Q[60];
			if (CheckCharacterItem(pchar, "ShipsJournal"))
			{
				link.l1 = DLG_TEXT_Q[61];
				link.l1.go = "Step_F8_8";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[62];
				link.l1.go = "exit";
			}
        break;
        case "Step_F8_8":
            dialog.text = DLG_TEXT_Q[63];
            link.l1 = DLG_TEXT_Q[64];
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "7");
            TakeItemFromCharacter(pchar, "ShipsJournal");
        break;

		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;


	}
}
