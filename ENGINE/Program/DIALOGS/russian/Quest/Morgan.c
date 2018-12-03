#include "TEXT\DIALOGS\Quest\Morgan.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	float locx, locy, locz;
	string sTemp;
	int iTemp;
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
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[0],
                         DLG_TEXT_Q[1], DLG_TEXT_Q[2],
                         DLG_TEXT_Q[3], "repeat", 20, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[4],
                                               DLG_TEXT_Q[5],
                                               DLG_TEXT_Q[6],
                                               DLG_TEXT_Q[7], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = DLG_TEXT_Q[8];
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "I_know_you_good":
			//провека защиты -->
			/*if (GetEngineVersion() != iScriptVersion)
			{
       			dialog.text = DLG_TEXT_Q[9];
				link.l1 = "...";
				link.l1.go = "exit";
				break;
			}*/ 
			//<-- провека защиты
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + DLG_TEXT_Q[10],
                         DLG_TEXT_Q[11], DLG_TEXT_Q[12],
                         DLG_TEXT_Q[13], "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[14],
                                               DLG_TEXT_Q[15],
                                               DLG_TEXT_Q[16],
                                               DLG_TEXT_Q[17], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = DLG_TEXT_Q[18];
				link.l1.go = "SharpPearl_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q4" && GetQuestPastDayParam("questTemp.piratesLine") > 5 && pchar.questTemp.Sharp != "toPearl")
			{
				link.l1 = DLG_TEXT_Q[19];
				link.l1.go = "PL_Q4_1";
			}
			if (pchar.questTemp.piratesLine == "waiting_Q8" && GetQuestPastDayParam("questTemp.piratesLine") > 30)
			{
				link.l1 = DLG_TEXT_Q[20];
				link.l1.go = "PL_Q8_1";
			}
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = DLG_TEXT_Q[21];
			link.l1 = DLG_TEXT_Q[22];
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = DLG_TEXT_Q[23];
			link.l1 = DLG_TEXT_Q[24];
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
 		case "EngLine_quests":
			dialog.text = DLG_TEXT_Q[25];
			link.l1 = DLG_TEXT_Q[26];
			link.l1.go = "Step_1_1";
  		break;

 		case "Step_1_1":
			dialog.text = DLG_TEXT_Q[27];
			link.l1 = DLG_TEXT_Q[28];
			link.l1.go = "Step_1_2";
  		break;
  		
 		case "Step_1_2":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "Step_1_3";
  		break;
  		
 		case "Step_1_3":
			dialog.text = DLG_TEXT_Q[31];
			link.l1 = DLG_TEXT_Q[32];
			link.l1.go = "Step_1_4";
  		break;
  		
 		case "Step_1_4":
			dialog.text = DLG_TEXT_Q[33];
			link.l1 = DLG_TEXT_Q[34];
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_2_Talking", "2");
			AddQuestRecord("Eng_Line_3_Morgan", "1");

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "hot_business":            // начало диалога по третьему квесту англ.линейки
			dialog.text = DLG_TEXT_Q[35];
			link.l1 = DLG_TEXT_Q[36];
			link.l1.go = "Step_3_1";
  		break;

	 	case "Step_3_1":
            if (GetQuestPastDayParam("questTemp") < 27 && pchar.questTemp.CurQuestNumber == "3")
            {
    			dialog.text = DLG_TEXT_Q[37];
    			link.l1 = DLG_TEXT_Q[38];
    			link.l1.go = "Step_3_2";
            }
            else
            {
    			dialog.text = DLG_TEXT_Q[39];
    			link.l1 = DLG_TEXT_Q[40];
    			link.l1.go = "exit";
                AddQuestRecord("Eng_Line_3_Morgan", "8");
                CloseQuestHeader("Eng_Line_3_Morgan");
                NextDiag.TempNode = "First time";
                if (pchar.questTemp.CurQuestNumber == "3")
                {
                    SaveCurrentQuestDateParam("questTemp");
                    pchar.questTemp.Waiting_time = "2";
                    pchar.questTemp.CurQuestNumber = "4";
                }
            }
  		break;

	 	case "Step_3_2":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Step_3_3";
  		break;
  		
	 	case "Step_3_3":
			dialog.text = DLG_TEXT_Q[43]+
                          DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "Step_3_4";
  		break;

	 	case "Step_3_4":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "I_want_attack";
			link.l2 = DLG_TEXT_Q[48];
			link.l2.go = "Step_3_6";
  		break;

	 	case "I_want_attack":    // Идем на испанцев, а может и не идем
            if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
            {
           		dialog.text = DLG_TEXT_Q[49]+
                              DLG_TEXT_Q[50]+
                              DLG_TEXT_Q[51]+
                              DLG_TEXT_Q[52];
    			link.l1 = DLG_TEXT_Q[53];
                link.l1.go = "Step_3_7";
            }
            else
            {
                NextDiag.TempNode = "Step_3_4";
               	dialog.text = DLG_TEXT_Q[54]+
                              DLG_TEXT_Q[55];
    			link.l1 = DLG_TEXT_Q[56];
    			link.l1.go = "exit";
    			link.l2 = DLG_TEXT_Q[57];
    			link.l2.go = "Step_3_6";
             }
  		break;

	 	case "Have_hot_bussines":    // Если геймеру вдруг захочется еще пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Step_3_6":                   // Отказ от предложения Моргана атаковать испанский город.
			dialog.text = DLG_TEXT_Q[60]+
                          DLG_TEXT_Q[61];
			link.l1 = DLG_TEXT_Q[62];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10); 
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
            
            AddQuestRecord("Eng_Line_3_Morgan", "2");
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";       // 2 так, для проформы, чтоб поддержать стандарт
            pchar.questTemp.CurQuestNumber = "4";     // идем на четвертый квест
            NextDiag.TempNode = "First time";
  		break;

	 	case "Step_3_7":                  // Согласие на участие в нападении на Белиз
			AddQuestRecord("Eng_Line_3_Morgan", "3");
            pchar.nation = PIRATE;
            pchar.questTemp.State = "AttackBeliz_GoOn";
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            // ==>  Кол-во компаньонов. Нужно для раздела золота независимо от того, кто остался жив, т.е. в обойме компаньонов(по закону берегового братства).
            pchar.questTemp.CompanionQuantity = "2";
            // ==>  Даем соотв. ноду Джекмену
            characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Lets_go_bussines";
            // ==>  Помещаем Джона Морриса в Бриджтаун и даем соотв. ноду
            characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Lets_go_bussines";
            // ==>  Заводим таймер на прерывание, даем 31 дней.
            SetTimerCondition("time_over_Beliz_attack", 0, 0, 51, false);
            SaveCurrentQuestDateParam("questTemp");
            NextDiag.TempNode = "Have_hot_bussines";
            pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
            // ==> капитулянтская нода губернатору Белиза
			characters[GetCharacterIndex("Beliz_Mayor")].dialog.captureNode = "EngLine3Quest_BelizAttack"; //капитулянтская нода мэра
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
  		break;

	 	case "time_over_Beliz":    // Геймер не успел взять Венесуэлу
			dialog.text = DLG_TEXT_Q[63];
			link.l1 = DLG_TEXT_Q[64];
			link.l1.go = "Step_3_8";
			// выход с палубы
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
        break;

        case "Step_3_8":
			LAi_SetPlayerType(pchar);
            if(IsCompanion(npchar))  {RemoveCharacterCompanion(pchar, npchar);}
            if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}

            QuestToSeaLogin_Prepare(worldMap.playerShipX, worldMap.playerShipZ, worldMap.island);
            if(worldMap.island !=	WDM_NONE_ISLAND)      // если возле острова
            {
                questToSeaLoginer.FromCoast = true;
            }
            else
            {
                questToSeaLoginer.FromCoast = false;
            }
            QuestToSeaLogin_Launch();
            
            Log_SetStringToLog(DLG_TEXT_Q[65]);
            // ==> Возвращаем на место Моргана
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberType(npchar);
            // ==> Возвращаем на место Джекмена
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                LAi_SetHuberType(characterfromID("Jackman"));
				LAi_group_MoveCharacter(characterfromID("Jackman"), "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> Возвращаем на место Джона Морриса
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                LAi_SetHuberType(characterfromID("John Morris"));
				LAi_group_MoveCharacter(characterfromID("John Morris"), "ENGLAND_CITIZENS");
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            AddMoneyToCharacter(pchar, -50000);
            ChangeCharacterReputation(pchar, -20); 
            // нулим опыт в авторитете и удаче
            AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
            AddCharacterSkill(pchar, SKILL_SNEAK, 0);
            
            AddQuestRecord("Eng_Line_3_Morgan", "6");
            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // идем на четвертый квест
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers");  //снятие перка квестового десанта
			// потом подумаем как дать солдат в помошь...
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "Step_3_9";
        break;
        
	 	case "Step_3_9":
            if (!IsCompanion(characterFromID("Henry Morgan")))
            {
                dialog.text = DLG_TEXT_Q[68];
            }
            else
            {
            	dialog.text = DLG_TEXT_Q[69];
            }
			link.l1 = DLG_TEXT_Q[70];
			link.l1.go = "Step_3_10";
        break;

	 	case "Step_3_10":
            if (GetCargoMaxSpace(pchar) >= RecalculateCargoLoad(pchar))
            {
                dialog.text = DLG_TEXT_Q[71]+
                              "Твоя доля золота - " + pchar.Ship.Cargo.Goods.gold + " центнера. Может, продашь часть или даже все? Возьму по 200 монет за единицу веса.";
            }
            else
            {
                dialog.text = DLG_TEXT_Q[72]+
                              "Максимальная грузоподъемность твоего корабля " + GetCargoMaxSpace(pchar) + " центнера, а в трюмах у тебя сейчас " + RecalculateCargoLoad(pchar) + " центнера\n"+
                              "Золота у тебя " + pchar.Ship.Cargo.Goods.gold + " центнера. Может, продашь часть? Возьму по 200 монет за еденицу веса.";
            }
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "out_fort";
			link.l2 = DLG_TEXT_Q[74];
			link.l2.go = "Agree_sale_gold";
			link.l3 = DLG_TEXT_Q[75];
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Think_sale_gold":    // ГГ думает о продаже золота
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "Agree_sale_gold";
			link.l2 = DLG_TEXT_Q[78];
			link.l2.go = "out_fort";
			link.l3 = DLG_TEXT_Q[79];
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
        break;

	 	case "Agree_sale_gold":    // ГГ согласен продать золото
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "sale_gold_25_persent";
			link.l2 = DLG_TEXT_Q[82];
			link.l2.go = "sale_gold_50_persent";
			link.l3 = DLG_TEXT_Q[83];
			link.l3.go = "sale_gold_75_persent";
			link.l4 = DLG_TEXT_Q[84];
			link.l4.go = "sale_gold_all";
			link.l5 = DLG_TEXT_Q[85];
			link.l5.go = "out_fort";
        break;
        
	 	case "sale_gold_25_persent":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.25*200));
        break;

	 	case "sale_gold_50_persent":
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.5));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.50*200));
        break;

	 	case "sale_gold_75_persent":
			dialog.text = DLG_TEXT_Q[90];
			link.l1 = DLG_TEXT_Q[91];
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*0.75*200));
        break;

	 	case "sale_gold_all":
			dialog.text = DLG_TEXT_Q[92];
			link.l1 = DLG_TEXT_Q[93];
			link.l1.go = "out_fort";
   			RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty)*200));
        break;

	 	case "out_fort":
			pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // сброс, если уже откладывали
	        pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";
	        pchar.quest.time_over_Beliz_attack.over = "yes";
	        		
			if(IsCompanion(characterFromID("Jackman")))  {RemoveCharacterCompanion(pchar, characterFromID("Jackman"));}
            if(IsCompanion(characterFromID("John Morris")))  {RemoveCharacterCompanion(pchar, characterFromID("John Morris"));}
            AddQuestRecord("Eng_Line_3_Morgan", "7");
            RemoveCharacterCompanion(pchar, npchar);
            // ==> Возвращаем на место Моргана
            ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
            LAi_SetHuberTypeNoGroup(npchar);
            // ==> Возвращаем на место Джекмена
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
                LAi_SetHuberType(characterfromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
            }
            // ==> Возвращаем на место Джона Морриса
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
                LAi_SetHuberType(characterfromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "I_know_you_good";
            }
            else
            {
               characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
            }
            ChangeCharacterReputation(pchar, 1); 
            AddCharacterExpToSkill(pchar, "Leadership", 20);
            AddCharacterExpToSkill(pchar, "Fencing", 500);
            AddCharacterExpToSkill(pchar, "Pistol", 550);
            AddCharacterExpToSkill(pchar, "Sailing", 550);
            AddCharacterExpToSkill(pchar, "Accuracy", 330);
            AddCharacterExpToSkill(pchar, "Cannons", 150);

            CloseQuestHeader("Eng_Line_3_Morgan");
            pchar.questTemp.Waiting_time = "2";
            pchar.questTemp.CurQuestNumber = "4";     // идем на четвертый квест
            pchar.questTemp.State = "empty";
            DeleteAttribute(pchar, "questTemp.CompanionQuantity");
            DeleteAttribute(pchar, "questTemp.BelizGoldQty");
            DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //дублирование снятия перка квестового десанта
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], false); //вернем боевки
            chrDisableReloadToLocation = false;
            pchar.nation = ENGLAND; // вернем нацию
            InterfaceStates.Buttons.Save.enable = true;   // вернем запись
			DoReloadCharacterToLocation("Beliz_town",  "reload", "gate_back"); //ГГ в город
            NextDiag.CurrentNode = "I_know_you_good";
			DialogExit();
        break;

	 	case "Give_blade":
			dialog.text = GetFullName(pchar) + DLG_TEXT_Q[94];
			link.l1 = DLG_TEXT_Q[95];
			link.l1.go = "Step_9_1";
        break;
        
	 	case "Step_9_1":
			dialog.text = DLG_TEXT_Q[96]+
                          DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
            GiveItem2Character(pchar, "blade27");
            RemoveCharacterEquip(NPChar, BLADE_ITEM_TYPE);
            TakeItemFromCharacter(NPChar, "blade27");
            GiveItem2Character(NPChar, "blade22");
            EquipCharacterByItem(NPChar, "blade22");
        break;
		//********************* Голландская линейка *********************
        case "HolLine3_fromMansfield":
            dialog.text = DLG_TEXT_Q[99];
            link.l1 = DLG_TEXT_Q[100];
            link.l1.go = "Step_H3_1";
        break;
 	 	case "Step_H3_1":
			dialog.text = DLG_TEXT_Q[101];
			link.l1 = DLG_TEXT_Q[102];
			link.l1.go = "Step_H3_2";
        break;
 	 	case "Step_H3_2":
			dialog.text = DLG_TEXT_Q[103];
			link.l1 = DLG_TEXT_Q[104];
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = DLG_TEXT_Q[105];
			link.l1 = DLG_TEXT_Q[106];
			link.l1.go = "Step_H3_NoWork";
			link.l2 = DLG_TEXT_Q[107];
			link.l2.go = "Step_H3_4";
        break;
 	 	case "Step_H3_NoWork":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_SurrenderWorkMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "4");
        break;
 	 	case "Step_H3_4":
			dialog.text = DLG_TEXT_Q[110]+
                          DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "exit";
			NextDiag.TempNode = "HolLine3_aboutWorm";
    		pchar.questTemp.State = "WormEnglPlans_WormPicarder";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "6");
        break;
 	 	case "HolLine3_aboutWorm":
			dialog.text = DLG_TEXT_Q[113];
            if (CheckAttribute(pchar, "questTemp.Talks"))
            {
    			link.l1 = DLG_TEXT_Q[114];
    			link.l1.go = "Step_H3_5";
            }
            else
            {
    			link.l1 = DLG_TEXT_Q[115];
    			link.l1.go = "exit";
            }
        break;
 	 	case "Step_H3_5":
            sTemp = DLG_TEXT_Q[116];
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern")) sTemp = sTemp + DLG_TEXT_Q[117];
            if (CheckAttribute(pchar, "questTemp.Talks.Store")) sTemp = sTemp + DLG_TEXT_Q[118];
            if (CheckAttribute(pchar, "questTemp.Talks.Shipyard")) sTemp = sTemp + DLG_TEXT_Q[119];
            if (CheckAttribute(pchar, "questTemp.Talks.Usurer")) sTemp = sTemp + DLG_TEXT_Q[120];
            if (CheckAttribute(pchar, "questTemp.Talks.Brothel")) sTemp = sTemp + DLG_TEXT_Q[121];
            dialog.text = DLG_TEXT_Q[122];
			link.l1 = sTemp;
			link.l1.go = "Step_H3_6";
        break;
 	 	case "Step_H3_6":
            if (CheckAttribute(pchar, "questTemp.Talks.Tavern") && CheckAttribute(pchar, "questTemp.Talks.Store") && CheckAttribute(pchar, "questTemp.Talks.Shipyard") && CheckAttribute(pchar, "questTemp.Talks.Usurer") && CheckAttribute(pchar, "questTemp.Talks.Brothel"))
 	 	    {
    			dialog.text = DLG_TEXT_Q[123];
    			link.l1 = DLG_TEXT_Q[124];
    			link.l1.go = "Step_H3_10";
 	 	    }
            else
            {
                dialog.text = DLG_TEXT_Q[125];
    			link.l1 = DLG_TEXT_Q[126];
    			link.l1.go = "Step_H3_7";
    			link.l2 = DLG_TEXT_Q[127];
    			link.l2.go = "exit";
    		}
        break;
 	 	case "Step_H3_7":
			dialog.text = DLG_TEXT_Q[128];
			link.l1 = DLG_TEXT_Q[129];
			link.l1.go = "Step_H3_8";
        break;
 	 	case "Step_H3_8":
			dialog.text = DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "Step_H3_9";
        break;
 	 	case "Step_H3_9":
			dialog.text = DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "12");
            DeleteAttribute(pchar, "questTemp.Talks");
        break;
 	 	case "Step_H3_10":
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "Step_H3_11";
        break;
 	 	case "Step_H3_11":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "13");
            DeleteAttribute(pchar, "questTemp.Talks");
            pchar.questTemp.State = "WormEnglPlans_SaveOfficer";
            sld = GetCharacter(NPC_GenerateCharacter("Alan_MacLine", "off_eng_2", "man", "man", 10, ENGLAND, 1, false));
        	sld.name 	= DLG_TEXT_Q[138];
        	sld.lastname = DLG_TEXT_Q[139];
            sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
        	LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Alan_MacLine")], "SentJons_prison", "goto", "goto9");
        break;
        // ==> Квест №6 голландки.
 	 	case "HolLine6_fromStuvesant":
			dialog.text = DLG_TEXT_Q[140];
			link.l1 = DLG_TEXT_Q[141];
			link.l1.go = "Step_H6_1";
        break;
 	 	case "Step_H6_1":
			dialog.text = DLG_TEXT_Q[142];
			link.l1 = DLG_TEXT_Q[143];
			link.l1.go = "Step_H6_2";
        break;
 	 	case "Step_H6_2":
			dialog.text = DLG_TEXT_Q[144];
			link.l1 = DLG_TEXT_Q[145];
			link.l1.go = "Step_H6_3";
        break;
 	 	case "Step_H6_3":
			dialog.text = DLG_TEXT_Q[146];
			link.l1 = DLG_TEXT_Q[147];
			link.l1.go = "Step_H6_4";
        break;
 	 	case "Step_H6_4":
			dialog.text = DLG_TEXT_Q[148];
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "Step_H6_5";
        break;
 	 	case "Step_H6_5":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "2");
            pchar.questTemp.State = "RevengeMansfield_toTavern";
            NextDiag.TempNode = "I_know_you_good";
            LAi_group_MoveCharacter(characterFromID("Santiago_tavernkeeper"), "QuestGroup");
            LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "QuestGroup");
        break;
 	 	case "HolLine6_fromSantiago":
			dialog.text = DLG_TEXT_Q[152];
			link.l1 = DLG_TEXT_Q[153];
			link.l1.go = "Step_H6_6";
        break;
 	 	case "Step_H6_6":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "Step_H6_7";
        break;
 	 	case "Step_H6_7":
			dialog.text = DLG_TEXT_Q[156];
			link.l1 = DLG_TEXT_Q[157];
			link.l1.go = "exit";
            pchar.questTemp.State = "RevengeMansfield_FromMorganWithResult";
            AddQuestRecord("Hol_Line_6_RevengeMansfield", "4");
            NextDiag.TempNode = "I_know_you_good";
        break;
		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = DLG_TEXT_Q[158] + GetFullName(pchar) + DLG_TEXT_Q[159];
            link.l1 = DLG_TEXT_Q[160];
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = DLG_TEXT_Q[161];
            link.l1 = DLG_TEXT_Q[162];
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = DLG_TEXT_Q[163]+
				          DLG_TEXT_Q[164];
            link.l1 = DLG_TEXT_Q[165];
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = DLG_TEXT_Q[166];
            link.l1 = DLG_TEXT_Q[167];
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = DLG_TEXT_Q[168];
            link.l1 = DLG_TEXT_Q[169];
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = DLG_TEXT_Q[170];
            link.l1 = DLG_TEXT_Q[171];
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = DLG_TEXT_Q[172];
			if (sti(pchar.money) >= 250000)
			{
				link.l1 = DLG_TEXT_Q[173];
				link.l1.go = "Step_F8_7";
				AddMoneyToCharacter(pchar, -250000);
			}
			else
			{
				link.l1 = DLG_TEXT_Q[174];
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_F8_6";
			}
        break;
        case "Step_F8_7":
            dialog.text = DLG_TEXT_Q[175];
            link.l1 = DLG_TEXT_Q[176];
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "4");
        break;
		//********************* Пиратская линейка *********************
		//квест №1, диалог в тюрьме
		case "PL_Q1_1":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "PL_Q1_2";
		break;
		case "PL_Q1_2":
			dialog.text = DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "PL_Q1_3";
		break;
		case "PL_Q1_3":
			dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_1";
			AddDialogExitQuestFunction("PiratesLine_q1_MorganEnd");
		break;
		//квест №2, диалог в резиденции Порт Рояля.
		case "PL_Q2_1":
			CloseQuestHeader("Pir_Line_1_JohnBolton");
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "PL_Q2_2";
		break;
		case "PL_Q2_2":
			dialog.text = DLG_TEXT_Q[185];
			link.l1 = DLG_TEXT_Q[186];
			link.l1.go = "exit";
			sld = GetCharacter(NPC_GenerateCharacter("EdwardLoy", "officer_10", "man", "man", 30, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade25", "pistol3", 100);
			FantomMakeCoolSailor(sld, SHIP_BRIGSW, DLG_TEXT_Q[187], CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			sld.name = DLG_TEXT_Q[188];
			sld.lastname = DLG_TEXT_Q[189];
			sld.rank = 30;
			sld.city = "LeFransua";
			sld.location	= "LeFransua_House4";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "EdwardLoy";
			sld.greeting = "Gr_EvilPirate";
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
			LAi_SetWarriorType(sld);
			GiveItem2Character(pchar, "BlackLabel");
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			pchar.questTemp.piratesLine = "BlackLabel_toLaVega";
            SetQuestHeader("Pir_Line_2_BlackLabel");
            AddQuestRecord("Pir_Line_2_BlackLabel", "1");
			NextDiag.TempNode = "PL_Q2_wait";
		break;
		case "PL_Q2_wait":
			dialog.text = DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_wait";
		break;

		case "PL_Q2_away_1":
			dialog.text = DLG_TEXT_Q[192];
			link.l1 = DLG_TEXT_Q[193];
			link.l1.go = "PL_Q2_away_2";
			TakeItemFromCharacter(pchar, "BlackLabel");
			CloseQuestHeader("Pir_Line_2_BlackLabel");
		break;
		case "PL_Q2_away_2":
			dialog.text = DLG_TEXT_Q[194];
			link.l1 = DLG_TEXT_Q[195];
			link.l1.go = "PL_Q2_away_3";
		break;
		case "PL_Q2_away_3":
			dialog.text = DLG_TEXT_Q[196];
			link.l1 = DLG_TEXT_Q[197];
			link.l1.go = "PL_Q2_away_4";
		break;
		case "PL_Q2_away_4":
			dialog.text = DLG_TEXT_Q[198];
			link.l1 = DLG_TEXT_Q[199];
			link.l1.go = "PL_Q2_away_5";
		break;
		case "PL_Q2_away_5":
			dialog.text = DLG_TEXT_Q[200];
			link.l1 = DLG_TEXT_Q[201];
			link.l1.go = "PL_Q2_away_6";
		break;
		case "PL_Q2_away_6":
			dialog.text = DLG_TEXT_Q[202];
			link.l1 = DLG_TEXT_Q[203];
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_3_KillLoy");
            AddQuestRecord("Pir_Line_3_KillLoy", "1");
			NextDiag.TempNode = "PL_Q2_awaywait";
			pchar.questTemp.piratesLine = "KillLoy_toHouse";
			ChangeCharacterAddress(characterFromId("EdwardLoy"), "none", "");
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1.location = "LeFransua_House4";
			pchar.quest.PiratesLine_q3_LoyHouse.function = "PiratesLine_q3_LoyHouse";
		break;
		case "PL_Q2_awaywait":
			dialog.text = DLG_TEXT_Q[204];
			link.l1 = DLG_TEXT_Q[205];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_Q[206];
			link.l2.go = "PL_Q3_notFound";
			NextDiag.TempNode = "PL_Q2_awaywait";
		break;

		case "PL_Q3_notFound":
			dialog.text = DLG_TEXT_Q[207];
			link.l1 = DLG_TEXT_Q[208];
			link.l1.go = "PL_Q3_notFound_1";
		break;
		case "PL_Q3_notFound_1":
			dialog.text = DLG_TEXT_Q[209];
			link.l1 = DLG_TEXT_Q[210];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
		break;

		case "PL_Q3_GoodWork":
			dialog.text = DLG_TEXT_Q[211];
			link.l1 = DLG_TEXT_Q[212];
			link.l1.go = "PL_Q3_GoodWork_1";
		break;
		case "PL_Q3_GoodWork_1":
			dialog.text = DLG_TEXT_Q[213];
			link.l1 = DLG_TEXT_Q[214];
			link.l1.go = "PL_Q3_GoodWork_2";
		break;
		case "PL_Q3_GoodWork_2":
			dialog.text = DLG_TEXT_Q[215];
			link.l1 = DLG_TEXT_Q[216];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
			AddMoneyToCharacter(pchar, 20000);
		break;
		//квест №4, жемчужные тартаны
		case "PL_Q4_1":
			dialog.text = DLG_TEXT_Q[217];
			link.l1 = DLG_TEXT_Q[218];
			link.l1.go = "PL_Q4_2";
		break;
		case "PL_Q4_2":
			dialog.text = DLG_TEXT_Q[219];
			link.l1 = DLG_TEXT_Q[220];
			link.l1.go = "PL_Q4_3";
		break;
		case "PL_Q4_3":
			dialog.text = DLG_TEXT_Q[221];
			link.l1 = DLG_TEXT_Q[222];
			link.l1.go = "PL_Q4_4";
		break;
		case "PL_Q4_4":
			dialog.text = DLG_TEXT_Q[223];
			link.l1 = DLG_TEXT_Q[224];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
			pchar.questTemp.piratesLine = "PearlQ4_toTerks"; //флаг квеста
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			pchar.questTemp.Sharp.PearlAreal.terms = 30; //сроки
			pchar.questTemp.Sharp.PearlAreal.qtyShips = 9; //кол-во тартан ловцов
			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчета
			pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
			SetQuestHeader("Pir_Line_4_Pearl");
			AddQuestRecord("Pir_Line_4_Pearl", "1");
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1.location = "Terks";
			pchar.quest.PQ4_SeaPearl_login.function = "PQ4_SeaPearl_login";
			SetTimerFunction("PQ4_SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));
		break;

		case "PL_Q4_wait":
			dialog.text = DLG_TEXT_Q[225];
			link.l1 = DLG_TEXT_Q[226];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
		break;
		//опоздал
		case "PL_Q4_late":
			dialog.text = DLG_TEXT_Q[227];
			link.l1 = DLG_TEXT_Q[228];
			link.l1.go = "PL_Q4_late_1";
		break;
		case "PL_Q4_late_1":
			dialog.text = DLG_TEXT_Q[229];
			link.l1 = DLG_TEXT_Q[230];
			link.l1.go = "PearlQ4_late_2";
		break;
		case "PearlQ4_late_2":
			dialog.text = DLG_TEXT_Q[231];
			link.l1 = DLG_TEXT_Q[232];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//дача пятого квеста
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		//неудачный наезд
		case "PL_Q4_badWork":
			dialog.text = DLG_TEXT_Q[233];
			link.l1 = DLG_TEXT_Q[234];
			link.l1.go = "PL_Q4_badWork_1";
		break;
		case "PL_Q4_badWork_1":
			dialog.text = DLG_TEXT_Q[235];
			link.l1 = DLG_TEXT_Q[236];
			link.l1.go = "PearlQ4_late_2";
		break;
		//удачный наезд
		case "PL_Q4_goodWork":
			dialog.text = DLG_TEXT_Q[237];
			if (!CheckAttribute(pchar, "items.jewelry12") || !CheckAttribute(pchar, "items.jewelry11"))
			{
				link.l1 = DLG_TEXT_Q[238];
				link.l1.go = "PL_Q4_goodWork_lair";
			}
			else
			{
				link.l1 = DLG_TEXT_Q[239] + pchar.items.jewelry12 + DLG_TEXT_Q[240] + pchar.items.jewelry11 + DLG_TEXT_Q[241];
				link.l1.go = "PL_Q4_goodWork_1";
			}
		break;

		case "PL_Q4_goodWork_lair":
			dialog.text = DLG_TEXT_Q[242];
			link.l1 = DLG_TEXT_Q[243];
			link.l1.go = "PL_Q4_goodWork_lair_1";
		break;
		case "PL_Q4_goodWork_lair_1":
			dialog.text = DLG_TEXT_Q[244];
			link.l1 = DLG_TEXT_Q[245];
			link.l1.go = "fight";
			chrDisableReloadToLocation = true; 
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_1":
			if (sti(pchar.items.jewelry12) < sti(pchar.questTemp.piratesLine.Qty.SmallPearl) || sti(pchar.items.jewelry11) < sti(pchar.questTemp.piratesLine.Qty.BigPearl))
			{
				dialog.text = DLG_TEXT_Q[246] + pchar.questTemp.piratesLine.Qty.SmallPearl + DLG_TEXT_Q[247] + pchar.questTemp.piratesLine.Qty.BigPearl + DLG_TEXT_Q[248];
				link.l1 = DLG_TEXT_Q[249];
				link.l1.go = "PL_Q4_goodWork_2";
			}
			else
			{
				if (sti(pchar.items.jewelry12) >= 1000 && sti(pchar.items.jewelry11) >= 500)
				{
					dialog.text = DLG_TEXT_Q[250];
					link.l1 = DLG_TEXT_Q[251];
					link.l1.go = "PL_Q4_goodWork_3";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[252];
					link.l1 = DLG_TEXT_Q[253];
					link.l1.go = "PL_Q4_goodWork_5";
				}
			}
		break;
		case "PL_Q4_goodWork_2":
			dialog.text = DLG_TEXT_Q[254];
			link.l1 = DLG_TEXT_Q[255];
			link.l1.go = "fight";
			chrDisableReloadToLocation = true; 
			pchar.questTemp.piratesLine = "over";
		break;

		case "PL_Q4_goodWork_3":
			dialog.text = DLG_TEXT_Q[256];
			link.l1 = DLG_TEXT_Q[257];
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -makeint(sti(pchar.items.jewelry12)/2));
			TakeNItems(pchar, "jewelry11", -makeint(sti(pchar.items.jewelry11)/2));
		break;
		case "PL_Q4_goodWork_4":
			dialog.text = DLG_TEXT_Q[258];
			link.l1 = DLG_TEXT_Q[259];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//дача пятого квеста
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
            Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
            Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		case "PL_Q4_goodWork_5":
			dialog.text = DLG_TEXT_Q[260];
			link.l1 = DLG_TEXT_Q[261];
			link.l1.go = "PL_Q4_goodWork_4";
			TakeNItems(pchar, "jewelry12", -sti(pchar.items.jewelry12));
			TakeNItems(pchar, "jewelry11", -sti(pchar.items.jewelry11));
		break;
		//квест №5, ГГ-ОЗГ. базар после дела
		case "PL_Q5_begin":
			dialog.text = DLG_TEXT_Q[262];
			link.l1 = DLG_TEXT_Q[263];
			link.l1.go = "PL_Q5_begin_1";
		break;
		case "PL_Q5_begin_1":
			dialog.text = DLG_TEXT_Q[264];
			link.l1 = DLG_TEXT_Q[265];
			link.l1.go = "PL_Q5_begin_2";
		break;
		case "PL_Q5_begin_2":
			dialog.text = DLG_TEXT_Q[266];
			link.l1 = DLG_TEXT_Q[267];
			link.l1.go = "PL_Q5_begin_3";
		break;
		case "PL_Q5_begin_3":
			dialog.text = DLG_TEXT_Q[268];
			link.l1 = DLG_TEXT_Q[269];
			link.l1.go = "PL_Q5_begin_4";
		break;
		case "PL_Q5_begin_4":
			dialog.text = DLG_TEXT_Q[270];
			link.l1 = DLG_TEXT_Q[271];
			link.l1.go = "PL_Q5_begin_5";
		break;
		case "PL_Q5_begin_5":
			dialog.text = DLG_TEXT_Q[272];
			link.l1 = DLG_TEXT_Q[273];
			link.l1.go = "PL_Q5_begin_6";
		break;
		case "PL_Q5_begin_6":
			dialog.text = DLG_TEXT_Q[274];
			link.l1 = DLG_TEXT_Q[275];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_talking";
			AddDialogExitQuestFunction("PQ5_Morgan_1");
		break;

		case "PL_Q5_talking":
			dialog.text = DLG_TEXT_Q[276] + GetMainCharacterNameDat() + "?";
			link.l1 = DLG_TEXT_Q[277];
			link.l1.go = "PL_Q5_talking_1";
		break;
		case "PL_Q5_talking_1":
			dialog.text = DLG_TEXT_Q[278];
			link.l1 = DLG_TEXT_Q[279];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end";
			AddDialogExitQuestFunction("PQ5_Morgan_4");
		break;

		case "PL_Q5_end":
			dialog.text = DLG_TEXT_Q[280];
			link.l1 = DLG_TEXT_Q[281];
			link.l1.go = "PL_Q5_end_1";
		break;
		case "PL_Q5_end_1":
			dialog.text = DLG_TEXT_Q[282];
			link.l1 = DLG_TEXT_Q[283];
			link.l1.go = "PL_Q5_end_2";
		break;
		case "PL_Q5_end_2":
			dialog.text = DLG_TEXT_Q[284];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
			AddDialogExitQuestFunction("PQ5_Morgan_5");
		break;

		case "PL_Q5_end_3":
			dialog.text = DLG_TEXT_Q[285];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
		break;

		case "PL_Q5_afterFight":
			dialog.text = DLG_TEXT_Q[286];
			link.l1 = DLG_TEXT_Q[287];
			link.l1.go = "PL_Q5_afterFight_1";
		break;
		case "PL_Q5_afterFight_1":
			dialog.text = DLG_TEXT_Q[288];
			link.l1 = DLG_TEXT_Q[289];
			link.l1.go = "PL_Q5_afterFight_2";
		break;
		case "PL_Q5_afterFight_2":
			dialog.text = DLG_TEXT_Q[290];
			link.l1 = DLG_TEXT_Q[291];			
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q6";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_5_Hunter");
			//сразу даем квест №6
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "1");
			QuestSetCurrentNode("Jackman", "PL_Q6"); //даем ноду Джекмену
		break;
		//квест №7, охота на Соукинса
		case "PL_Q7_begin":
			dialog.text = DLG_TEXT_Q[292] + pchar.lastname + DLG_TEXT_Q[293];
			link.l1 = DLG_TEXT_Q[294];
			link.l1.go = "PL_Q7_begin_1";
			CloseQuestHeader("Pir_Line_6_Jackman");
		break;
		case "PL_Q7_begin_1":
			dialog.text = DLG_TEXT_Q[295];
			link.l1 = DLG_TEXT_Q[296];
			link.l1.go = "PL_Q7_begin_2";
		break;
		case "PL_Q7_begin_2":
			dialog.text = DLG_TEXT_Q[297];
			link.l1 = DLG_TEXT_Q[298];
			link.l1.go = "PL_Q7_begin_3";
		break;
		case "PL_Q7_begin_3":
			dialog.text = DLG_TEXT_Q[299];
			link.l1 = DLG_TEXT_Q[300];
			link.l1.go = "PL_Q7_begin_4";
		break;
		case "PL_Q7_begin_4":
			dialog.text = DLG_TEXT_Q[301];
			link.l1 = DLG_TEXT_Q[302];
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_7_Soukins");
            AddQuestRecord("Pir_Line_7_Soukins", "1");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toLaVega";
			SetLocationCapturedState("LaVega_town", false);
		break;

		case "PL_Q7_LaVegaLate":
			dialog.text = DLG_TEXT_Q[303];
			link.l1 = DLG_TEXT_Q[304];
			link.l1.go = "PL_Q7_LaVegaLate_1";
		break;
		case "PL_Q7_LaVegaLate_1":
			dialog.text = DLG_TEXT_Q[305];
			link.l1 = DLG_TEXT_Q[306];
			link.l1.go = "PL_Q7_LaVegaLate_2";
		break;
		case "PL_Q7_LaVegaLate_2":
			dialog.text = DLG_TEXT_Q[307];
			link.l1 = DLG_TEXT_Q[308];
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "4");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
		break;

		case "PL_Q7_LeonNotFound":
			dialog.text = DLG_TEXT_Q[309];
			link.l1 = DLG_TEXT_Q[310];
			link.l1.go = "PL_Q7_LeonNotFound_1";
		break;
		case "PL_Q7_LeonNotFound_1":
			dialog.text = DLG_TEXT_Q[311];
			link.l1 = DLG_TEXT_Q[312];
			link.l1.go = "PL_Q7_LeonNotFound_2";
		break;
		case "PL_Q7_LeonNotFound_2":
			dialog.text = DLG_TEXT_Q[313];
			link.l1 = DLG_TEXT_Q[314];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -3);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_afterLeon":
			dialog.text = DLG_TEXT_Q[315];
			link.l1 = DLG_TEXT_Q[316];
			link.l1.go = "PL_Q7_afterLeon_1";
		break;
		case "PL_Q7_afterLeon_1":
			dialog.text = DLG_TEXT_Q[317];
			link.l1 = DLG_TEXT_Q[318];
			link.l1.go = "PL_Q7_afterLeon_2";
		break;
		case "PL_Q7_afterLeon_2":
			dialog.text = DLG_TEXT_Q[319];
			link.l1 = DLG_TEXT_Q[320];
			link.l1.go = "PL_Q7_afterLeon_3";
		break;
		case "PL_Q7_afterLeon_3":
			dialog.text = DLG_TEXT_Q[321];
			link.l1 = DLG_TEXT_Q[322];
			link.l1.go = "PL_Q7_afterLeon_4";
		break;
		case "PL_Q7_afterLeon_4":
			dialog.text = DLG_TEXT_Q[323];
			link.l1 = DLG_TEXT_Q[324];
			link.l1.go = "PL_Q7_afterLeon_5";
		break;
		case "PL_Q7_afterLeon_5":
			dialog.text = DLG_TEXT_Q[325];
			link.l1 = DLG_TEXT_Q[326];
			link.l1.go = "PL_Q7_afterLeon_6";
		break;
		case "PL_Q7_afterLeon_6":
			dialog.text = DLG_TEXT_Q[327];
			link.l1 = DLG_TEXT_Q[328];
			link.l1.go = "PL_Q7_afterLeon_7";
		break;
		case "PL_Q7_afterLeon_7":
			dialog.text = DLG_TEXT_Q[329];
			link.l1 = DLG_TEXT_Q[330];
			link.l1.go = "PL_Q7_afterLeon_8";
		break;
		case "PL_Q7_afterLeon_8":
			dialog.text = DLG_TEXT_Q[331];
			link.l1 = DLG_TEXT_Q[332];
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_7_Soukins", "8");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toPuertoPrincipe";
			sld = ItemsFromID("OpenBook");
			sld.shown = true;
			sld = ItemsFromID("Ladder");
			sld.shown = true;
			sld.startLocation = "PuertoPrincipe_town";
			sld.startLocator = "item1";
			sld.useLocation = "PuertoPrincipe_town";
			sld.useLocator = "button01";
			//прерывание на вход в резиденцию, не дать осмотреться геймеру
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1 = "location";
            Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1.location = "PuertoPrincipe_townhall";
            Pchar.quest.PQ7_inSoukinsResidence.function = "PQ7_inSoukinsResidence";
		break;

		case "PL_Q7_BadWork":
			dialog.text = DLG_TEXT_Q[333];
			link.l1 = DLG_TEXT_Q[334];
			link.l1.go = "PL_Q7_BadWork_1";
		break;
		case "PL_Q7_BadWork_1":
			dialog.text = DLG_TEXT_Q[335];
			link.l1 = DLG_TEXT_Q[336];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;

		case "PL_Q7_GoodWork":
			dialog.text = DLG_TEXT_Q[337];
			link.l1 = DLG_TEXT_Q[338];
			link.l1.go = "PL_Q7_GoodWork_1";
		break;
		case "PL_Q7_GoodWork_1":
			dialog.text = DLG_TEXT_Q[339];
			link.l1 = DLG_TEXT_Q[340];
			link.l1.go = "PL_Q7_GoodWork_2";
		break;
		case "PL_Q7_GoodWork_2":
			dialog.text = DLG_TEXT_Q[341];
			link.l1 = DLG_TEXT_Q[342];
			link.l1.go = "PL_Q7_GoodWork_3";
		break;
		case "PL_Q7_GoodWork_3":
			dialog.text = DLG_TEXT_Q[343];
			link.l1 = DLG_TEXT_Q[344];
			link.l1.go = "PL_Q7_GoodWork_4";
		break;
		case "PL_Q7_GoodWork_4":
			dialog.text = DLG_TEXT_Q[345];
			link.l1 = DLG_TEXT_Q[346];
			link.l1.go = "PL_Q7_GoodWork_5";
		break;
		case "PL_Q7_GoodWork_5":
			dialog.text = DLG_TEXT_Q[347];
			link.l1 = DLG_TEXT_Q[348];
			link.l1.go = "PL_Q7_GoodWork_6";
		break;
		case "PL_Q7_GoodWork_6":
			dialog.text = DLG_TEXT_Q[349];
			link.l1 = DLG_TEXT_Q[350];
			link.l1.go = "PL_Q7_GoodWork_7";
		break;
		case "PL_Q7_GoodWork_7":
			dialog.text = DLG_TEXT_Q[351];
			link.l1 = DLG_TEXT_Q[352];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, 10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
		break;
		//квест №8, штурм Панамы
		case "PL_Q8_1":
			if (pchar.questTemp.State == "" || pchar.questTemp.State == "EndOfQuestLine")
			{
				dialog.text = DLG_TEXT_Q[353];
				link.l1 = DLG_TEXT_Q[354];
				link.l1.go = "PL_Q8_2";
				pchar.questTemp.State = "EndOfQuestLine"; //если геймер еще не брал нац.линейку, то и не даем ее после штурма Панамы
				bWorldAlivePause = false; // Конец линейки
			}
			else
			{
				dialog.text = DLG_TEXT_Q[355] + NationNamePeopleAcc(sti(pchar.questTemp.NationQuest)) + DLG_TEXT_Q[356];
				link.l1 = DLG_TEXT_Q[357];
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_2":
			dialog.text = DLG_TEXT_Q[358];
			link.l1 = DLG_TEXT_Q[359];
			link.l1.go = "PL_Q8_3";
		break;
		case "PL_Q8_3":
			dialog.text = DLG_TEXT_Q[360];
			link.l1 = DLG_TEXT_Q[361];
			link.l1.go = "PL_Q8_4";
		break;
		case "PL_Q8_4":
			dialog.text = DLG_TEXT_Q[362];
			link.l1 = DLG_TEXT_Q[363];
			link.l1.go = "PL_Q8_5";
		break;
		case "PL_Q8_5":
			dialog.text = DLG_TEXT_Q[364];
			link.l1 = DLG_TEXT_Q[365];
			link.l1.go = "PL_Q8_6";
		break;
		case "PL_Q8_6":
			dialog.text = DLG_TEXT_Q[366];
			link.l1 = DLG_TEXT_Q[367];
			link.l1.go = "PL_Q8_7";
		break;
		case "PL_Q8_7":
			dialog.text = DLG_TEXT_Q[368];
			link.l1 = DLG_TEXT_Q[369];
			link.l1.go = "PL_Q8_8";
		break;
		case "PL_Q8_8":
			dialog.text = DLG_TEXT_Q[370];
			link.l1 = DLG_TEXT_Q[371];
			link.l1.go = "PL_Q8_9";
		break;
		case "PL_Q8_9":
			dialog.text = DLG_TEXT_Q[372];
			link.l1 = DLG_TEXT_Q[373];
			link.l1.go = "PL_Q8_10";
		break;
		case "PL_Q8_10":
			dialog.text = DLG_TEXT_Q[374];
			link.l1 = DLG_TEXT_Q[375];
			link.l1.go = "PL_Q8_11";
		break;
		case "PL_Q8_11":
			dialog.text = DLG_TEXT_Q[376];
			link.l1 = DLG_TEXT_Q[377];
			link.l1.go = "PL_Q8_12";
		break;
		case "PL_Q8_12":
			dialog.text = DLG_TEXT_Q[378];
			link.l1 = DLG_TEXT_Q[379];
			link.l1.go = "PL_Q8_13";
		break;
		case "PL_Q8_13":
			dialog.text = DLG_TEXT_Q[380];
			link.l1 = DLG_TEXT_Q[381];
			link.l1.go = "PL_Q8_14";
		break;
		case "PL_Q8_14":
			dialog.text = DLG_TEXT_Q[382];
			link.l1 = DLG_TEXT_Q[383];
			link.l1.go = "PL_Q8_15";
		break;
		case "PL_Q8_15":
			dialog.text = DLG_TEXT_Q[384];
			link.l1 = DLG_TEXT_Q[385];
			link.l1.go = "PL_Q8_16";
		break;
		case "PL_Q8_16":
			dialog.text = DLG_TEXT_Q[386];
			link.l1 = DLG_TEXT_Q[387];
			link.l1.go = "exit";
            AddQuestRecord("Pir_Line_8_Panama", "1");
			NextDiag.TempNode = "PL_Q8_ready";
			pchar.questTemp.piratesLine = "Panama_toReady";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			SetTimerFunction("PQ8_timeOver", 0, 0, 35);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		break;

		case "PL_Q8_ready":
			if (GetQuestPastDayParam("questTemp.piratesLine") > 20)
			{
				dialog.text = DLG_TEXT_Q[388];
				link.l1 = DLG_TEXT_Q[389];
				link.l1.go = "PL_Q8_ready_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[390];
				link.l1 = DLG_TEXT_Q[391];
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_ready_1":
            if (GetCompanionQuantity(pchar) == 1)
            {
				dialog.text = DLG_TEXT_Q[392];
				link.l1 = DLG_TEXT_Q[393];
				link.l1.go = "PL_Q8_ready_2";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[394] + pchar.name + DLG_TEXT_Q[395];
				link.l1 = DLG_TEXT_Q[396];
				link.l1.go = "exit";
				NextDiag.TempNode = "PL_Q8_ready";
			}
		break;
		case "PL_Q8_ready_2":
			dialog.text = DLG_TEXT_Q[397];
			link.l1 = DLG_TEXT_Q[398];
			link.l1.go = "PL_Q8_ready_3";
		break;
		case "PL_Q8_ready_3":
			dialog.text = DLG_TEXT_Q[399];
			link.l1 = DLG_TEXT_Q[400];
			link.l1.go = "PL_Q8_ready_4";
		break;
		case "PL_Q8_ready_4":
			pchar.quest.PQ8_timeOver.over = "yes"; //снимаем таймер 
			SetTimerFunction("PQ8_PanamaTimerOver", 0, 0, 20); //ставим новый таймер
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1 = "location";
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1.location = "PortoBello";
			pchar.Quest.PQ8_EnterPortoBello.function = "PQ8_EnterPortoBello";
            pchar.questTemp.piratesLine = "Panama_toPortoBello";
			AddQuestRecord("Pir_Line_8_Panama", "4");
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			characters[GetCharacterIndex("PortoBello_Mayor")].dialog.captureNode = "PQ8_MayorPortoBello"; //капитулянтская нода мэра
			//Морган
			FantomMakeCoolSailor(npchar, SHIP_BATTLESHIP, DLG_TEXT_Q[401], CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
            pchar.nation = PIRATE;
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
			//LAi_SetImmortal(NPChar, false);
			NPChar.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(NPChar);
			LAi_RebirthOldName(NPChar); 
			npchar.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
            ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(npchar, false);
			//Джекмен
			sld = characterFromId("Jackman");
			FantomMakeCoolSailor(sld, SHIP_WARSHIP, DLG_TEXT_Q[402], CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
			LAi_SetImmortal(sld, false);
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Джон Моррис
			if (GetCharacterIndex("John Morris") == -1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("John Morris", "bocman", "man", "man", 38, PIRATE, -1, false));
        		sld.name 	= DLG_TEXT_Q[403];
        		sld.lastname = DLG_TEXT_Q[404];
				sld.Dialog.Filename = "Quest\JohnMorris.c";
				sld.greeting = "Gr_HeadPirates";
				FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol4", 150);
           		LAi_SetStayType(sld);
        		LAi_SetLoginTime(sld, 0.0, 24.0);
        		LAi_SetHP(sld, 180.0, 180.0);
			}
			else
			{
				sld = characterFromId("John Morris");
			}
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, DLG_TEXT_Q[405], CANNON_TYPE_CANNON_LBS32, 90, 90, 90);	
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
            LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.  
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Ричард Соукинс
			sld = characterFromId("Richard_Soukins");
			FantomMakeCoolSailor(sld, SHIP_MANOWAR, DLG_TEXT_Q[406], CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 2500;
			LAi_SetImmortal(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_RemoveLoginTime(sld);
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q8_timeOver":
			dialog.text = DLG_TEXT_Q[407];
			link.l1 = DLG_TEXT_Q[408];
			link.l1.go = "PL_Q8_timeOver_1";
			// выход с палубы
			pchar.quest.Munity = "Deads";
            LAi_LockFightMode(Pchar, false);
		break;
		case "PL_Q8_timeOver_1":
			dialog.text = DLG_TEXT_Q[409];
			link.l1 = DLG_TEXT_Q[410];
			link.l1.go = "PL_Q8_timeOver_2";
		break;
		case "PL_Q8_timeOver_2":
			dialog.text = DLG_TEXT_Q[411];
			link.l1 = DLG_TEXT_Q[412];
			link.l1.go = "PL_Q8_timeOver_3";
		break;
		case "PL_Q8_timeOver_3":
			SetTimerFunction("PQ8_openPanama", 0, 0, 40);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
			pchar.questTemp.piratesLine = "over";
			AddQuestRecord("Pir_Line_8_Panama", "3");
			CloseQuestHeader("Pir_Line_8_Panama");
			//возвращаем Моргана
            if(IsCompanion(npchar))  RemoveCharacterCompanion(pchar, npchar);
            //Возвращаем на место Джекмена
			iTemp = GetCharacterIndex("Jackman");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}               
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
			//Джон Моррис
			iTemp = GetCharacterIndex("John Morris");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}   				
				sld = &characters[iTemp];
				sld.lifeDay = 0;
			}
            //Возвращаем на место Соукинса
			iTemp = GetCharacterIndex("Richard_Soukins");
			if (iTemp != -1)
			{
				if(IsCompanion(&characters[iTemp]))  
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}                   
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
                ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
                characters[iTemp].dialog.currentnode = "First time";
            }
            NextDiag.TempNode = "PL_Q8_timeOver_exit";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_timeOver_exit":
			dialog.text = DLG_TEXT_Q[413];
			link.l1 = "...";
			link.l1.go = "PL_Q8_timeOver_exit";
		break;
		//в резиденции взятого Порто Белло
		case "PL_Q8_PBResidence":
			dialog.text = DLG_TEXT_Q[414];
			link.l1 = DLG_TEXT_Q[415];
			link.l1.go = "PL_Q8_PBResidence_1";
		break;
		case "PL_Q8_PBResidence_1":
			dialog.text = DLG_TEXT_Q[416];
			link.l1 = DLG_TEXT_Q[417];
			link.l1.go = "PL_Q8_PBResidence_2";
		break;
		case "PL_Q8_PBResidence_2":
			dialog.text = DLG_TEXT_Q[418];
			link.l1 = DLG_TEXT_Q[419];
			link.l1.go = "PL_Q8_PBResidence_3";
		break;
		case "PL_Q8_PBResidence_3":
			dialog.text = DLG_TEXT_Q[420];
			link.l1 = DLG_TEXT_Q[421];
			link.l1.go = "PL_Q8_PBResidence_4";
		break;
		case "PL_Q8_PBResidence_4":
			dialog.text = DLG_TEXT_Q[422] + pchar.name + DLG_TEXT_Q[423];
			link.l1 = DLG_TEXT_Q[424];
			link.l1.go = "PL_Q8_PBResidence_5";
		break;
		case "PL_Q8_PBResidence_5":
			dialog.text = DLG_TEXT_Q[425];
			link.l1 = DLG_TEXT_Q[426];
			link.l1.go = "PL_Q8_PBResidence_6";
		break;
		case "PL_Q8_PBResidence_6":
			dialog.text = DLG_TEXT_Q[427];
			link.l1 = DLG_TEXT_Q[428];
			link.l1.go = "PL_Q8_PBResidence_7";
		break;
		case "PL_Q8_PBResidence_7":
			if (pchar.location.from_sea == "Shore48")
			{
				dialog.text = DLG_TEXT_Q[429];
				link.l1 = DLG_TEXT_Q[430];
				link.l1.go = "PL_Q8_PBResidence_8";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[431];
				link.l1 = DLG_TEXT_Q[432];
				link.l1.go = "PL_Q8_PBResidence_8";
			}
		break;
		case "PL_Q8_PBResidence_8":
			dialog.text = DLG_TEXT_Q[433];
			link.l1 = DLG_TEXT_Q[434];
			link.l1.go = "PL_Q8_PBResidence_9";
		break;
		case "PL_Q8_PBResidence_9":
			dialog.text = DLG_TEXT_Q[435];
			link.l1 = DLG_TEXT_Q[436];
			link.l1.go = "PL_Q8_PBResidence_10";
		break;
		case "PL_Q8_PBResidence_10":
			dialog.text = DLG_TEXT_Q[437];
			link.l1 = DLG_TEXT_Q[438];
			link.l1.go = "PL_Q8_PBResidence_11";
		break;
		case "PL_Q8_PBResidence_11":
			dialog.text = DLG_TEXT_Q[439];
			link.l1 = DLG_TEXT_Q[440];
			link.l1.go = "PL_Q8_PBResidence_12";
		break;
		case "PL_Q8_PBResidence_12":
			dialog.text = DLG_TEXT_Q[441];
			link.l1 = DLG_TEXT_Q[442];
			link.l1.go = "PL_Q8_PBResidence_13";
		break;
		case "PL_Q8_PBResidence_13":
			dialog.text = DLG_TEXT_Q[443];
			link.l1 = DLG_TEXT_Q[444];
			link.l1.go = "PL_Q8_PBResidence_14";		
		break;
		case "PL_Q8_PBResidence_14":
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false; 
			//bQuestDisableMapEnter = false;
			LocatorReloadEnterDisable("Shore48", "reload1_back", false); //открываем проход в джанглы через бухту
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.PQ8_PBExitResidence.win_condition.l1.location = pchar.location;
            Pchar.quest.PQ8_PBExitResidence.function = "PQ8_PBExitResidence";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_PBResidence_over":
			dialog.text = DLG_TEXT_Q[445];
			link.l1 = DLG_TEXT_Q[446];
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
		break;
		//у ворот Панамы
		case "PL_Q8_ExTPanama":
			if (pchar.questTemp.piratesLine == "Panama_RichardBadWork")
			{
				iTemp = GetCharacterIndex("Richard_Soukins");				
				if (!LAi_IsDead(&characters[iTemp]))
				{
					dialog.text = DLG_TEXT_Q[447];
					link.l1 = DLG_TEXT_Q[448];
					link.l1.go = "PL_Q8_ExTPanama_1";
				}
				else
				{
					dialog.text = DLG_TEXT_Q[449];
					link.l1 = DLG_TEXT_Q[450];
					link.l1.go = "PL_Q8_ExTPanama_7";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_Q[451] + pchar.name + DLG_TEXT_Q[452];
				link.l1 = DLG_TEXT_Q[453];
				link.l1.go = "PL_Q8_ExTPanama_1";
			}
		break;
		case "PL_Q8_ExTPanama_1":
			dialog.text = DLG_TEXT_Q[454];
			link.l1 = DLG_TEXT_Q[455];
			link.l1.go = "PL_Q8_ExTPanama_2";
		break;
		case "PL_Q8_ExTPanama_2":
			dialog.text = DLG_TEXT_Q[456];
			link.l1 = DLG_TEXT_Q[457];
			link.l1.go = "PL_Q8_ExTPanama_3";
		break;
		case "PL_Q8_ExTPanama_3":
			dialog.text = DLG_TEXT_Q[458];
			link.l1 = DLG_TEXT_Q[459];
			link.l1.go = "PL_Q8_ExTPanama_4";
		break;
		case "PL_Q8_ExTPanama_4":
			dialog.text = DLG_TEXT_Q[460];
			link.l1 = DLG_TEXT_Q[461];
			link.l1.go = "PL_Q8_ExTPanama_5";
		break;
		case "PL_Q8_ExTPanama_5":
			dialog.text = DLG_TEXT_Q[462];
			link.l1 = DLG_TEXT_Q[463];
			link.l1.go = "PL_Q8_ExTPanama_6";
		break;
		case "PL_Q8_ExTPanama_6":
			dialog.text = DLG_TEXT_Q[464];
			link.l1 = DLG_TEXT_Q[465];
			link.l1.go = "PL_Q8_ExTPanama_7";
		break;
		case "PL_Q8_ExTPanama_7":
			AddQuestRecord("Pir_Line_8_Panama", "9");
			//characters[GetCharacterIndex("Panama_Mayor")].dialog.captureNode = "PQ8_afterAttack"; //капитулянтская нода мэра
			pchar.quest.PQ8_piratesInPanama.win_condition.l1 = "location";
			pchar.quest.PQ8_piratesInPanama.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_piratesInPanama.function = "PQ8_piratesInPanama";
			NextDiag.TempNode = "PL_Q8_ExTPanama_over";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_ExTPanama_over":
			dialog.text = DLG_TEXT_Q[466];
			link.l1 = DLG_TEXT_Q[467];
			link.l1.go = "exit";
		break;
		case "PL_Q8_ExTPanama_7":
			dialog.text = DLG_TEXT_Q[468];
			link.l1 = DLG_TEXT_Q[469];
			link.l1.go = "PL_Q8_ExTPanama_8";
		break;
		case "PL_Q8_ExTPanama_8":
			dialog.text = DLG_TEXT_Q[470];
			link.l1 = DLG_TEXT_Q[471];
			link.l1.go = "PL_Q8_ExTPanama_9";
		break;
		case "PL_Q8_ExTPanama_9":
			QuestSetCurrentNode("Richard_Soukins", "PQ8_exitTown");
			AddQuestRecord("Pir_Line_8_Panama", "10");
			CloseQuestHeader("Pir_Line_8_Panama");
			LocatorReloadEnterDisable("Panama_ExitTown", "reload4", true); //закроем вход в город
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30); //таймер на открыть все потом.
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в Панаме после выхода ГГ из резиденции
		case "PL_Q8_Panama1":
			dialog.text = DLG_TEXT_Q[472];
			link.l1 = DLG_TEXT_Q[473];
			link.l1.go = "PL_Q8_Panama1_1";
		break;
		case "PL_Q8_Panama1_1":
			dialog.text = DLG_TEXT_Q[474];
			link.l1 = DLG_TEXT_Q[475];
			link.l1.go = "PL_Q8_Panama1_2";
		break;
		case "PL_Q8_Panama1_2":
			dialog.text = DLG_TEXT_Q[476];
			link.l1 = DLG_TEXT_Q[477];
			link.l1.go = "PL_Q8_Panama1_3";
		break;
		case "PL_Q8_Panama1_3":
			dialog.text = DLG_TEXT_Q[478];
			link.l1 = DLG_TEXT_Q[479];
			link.l1.go = "PL_Q8_Panama1_4";
		break;
		case "PL_Q8_Panama1_4":
			sld = characterFromId("FantomMayor");
			sld.lifeDay = 0;
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
			pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload3", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в резиденции Панамы с ключом
		case "PL_Q8_Panama2":
			npchar.quest.locInd = FindLocation(pchar.location);
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.money")) sld.private1.money = 0;
			if (CheckAttribute(sld, "private2.money")) sld.private2.money = 0;	
			dialog.text = DLG_TEXT_Q[480];
			link.l1 = DLG_TEXT_Q[481];
			link.l1.go = "PL_Q8_Panama2_1";
		break;
		case "PL_Q8_Panama2_1":
			dialog.text = DLG_TEXT_Q[482];
			link.l1 = DLG_TEXT_Q[483];
			link.l1.go = "PL_Q8_Panama2_2";
		break;
		case "PL_Q8_Panama2_2":
			dialog.text = DLG_TEXT_Q[484];
			link.l1 = DLG_TEXT_Q[485];
			link.l1.go = "PL_Q8_Panama2_3";
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.items.gold")) DeleteAttribute(sld, "private1.items.gold");
			else AddMoneyToCharacter(pchar, -50000000);
		break;
		case "PL_Q8_Panama2_3":
			dialog.text = DLG_TEXT_Q[486];
			link.l1 = DLG_TEXT_Q[487];
			link.l1.go = "PL_Q8_Panama2_4";
		break;
		case "PL_Q8_Panama2_4":
			dialog.text = DLG_TEXT_Q[488]+
				DLG_TEXT_Q[489];
			link.l1 = DLG_TEXT_Q[490];
			link.l1.go = "PL_Q8_Panama2_5";
		break;
		case "PL_Q8_Panama2_5":
			dialog.text = DLG_TEXT_Q[491];
			link.l1 = DLG_TEXT_Q[492];
			link.l1.go = "PL_Q8_Panama2_6";
		break;
		case "PL_Q8_Panama2_6":
			AddQuestRecord("Pir_Line_8_Panama", "12");
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1.location = "Panama_Fort";
			Pchar.quest.PL_Q8_inPanamaFort2.function = "PL_Q8_inPanamaFort2";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//Морган в Порт Рояле
		case "PL_Q8_afterPanama":
			dialog.text = DLG_TEXT_Q[493] + pchar.name + DLG_TEXT_Q[494];
			link.l1 = DLG_TEXT_Q[495];
			link.l1.go = "PL_Q8_afterPanama_1";
		break;
		case "PL_Q8_afterPanama_1":
			dialog.text = DLG_TEXT_Q[496];
			link.l1 = DLG_TEXT_Q[497];
			link.l1.go = "PL_Q8_afterPanama_2";
		break;
		case "PL_Q8_afterPanama_2":
			dialog.text = DLG_TEXT_Q[498];
			link.l1 = DLG_TEXT_Q[499];
			link.l1.go = "PL_Q8_afterPanama_3";
		break;
		case "PL_Q8_afterPanama_3":
			dialog.text = DLG_TEXT_Q[500]+
				DLG_TEXT_Q[501];
			link.l1 = DLG_TEXT_Q[502];
			link.l1.go = "PL_Q8_afterPanama_4";
		break;
		case "PL_Q8_afterPanama_4":
			dialog.text = DLG_TEXT_Q[503];
			link.l1 = DLG_TEXT_Q[504];
			link.l1.go = "PL_Q8_afterPanama_5";
		break;
		case "PL_Q8_afterPanama_5":
			dialog.text = DLG_TEXT_Q[505];
			link.l1 = DLG_TEXT_Q[506];
			link.l1.go = "PL_Q8_afterPanama_6";
		break;
		case "PL_Q8_afterPanama_6":
			dialog.text = DLG_TEXT_Q[507];
			link.l1 = DLG_TEXT_Q[508];
			link.l1.go = "PL_Q8_afterPanama_7";
		break;
		case "PL_Q8_afterPanama_7":
			dialog.text = DLG_TEXT_Q[509];
			link.l1 = DLG_TEXT_Q[510];
			link.l1.go = "PL_Q8_afterPanama_8";
		break;
		case "PL_Q8_afterPanama_8":
			dialog.text = DLG_TEXT_Q[511];
			link.l1 = DLG_TEXT_Q[512];
			link.l1.go = "PL_Q8_afterPanama_9";
		break;
		case "PL_Q8_afterPanama_9":
			dialog.text = DLG_TEXT_Q[513];
			link.l1 = DLG_TEXT_Q[514];
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "over";
            AddQuestRecord("Pir_Line_8_Panama", "14");
            CloseQuestHeader("Pir_Line_8_Panama");
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(DLG_TEXT_Q[515], DLG_TEXT_Q[516]);
			link.l1 = DLG_TEXT_Q[517];
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_Q[518];
        			link.l1 = DLG_TEXT_Q[519];
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple(DLG_TEXT_Q[520], DLG_TEXT_Q[521]);
			link.l1 = RandPhraseSimple(DLG_TEXT_Q[522], DLG_TEXT_Q[523]);
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 20 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_Q[524];
        			link.l1 = DLG_TEXT_Q[525];
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
			if (Pchar.location == "SentJons_HouseF3")
			{
				DoReloadCharacterToLocation("SentJons_town","reload","houseF3");	
			}
			else
			{
				DoReloadCharacterToLocation("PortRoyal_town","reload","houseS1");	
			}
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

