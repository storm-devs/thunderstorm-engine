#include "TEXT\DIALOGS\Tavern\Tortuga_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[0]+ GetCityName(npchar.city) +DLG_TEXT_TV[1],
                          DLG_TEXT_TV[2], DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[5] + NPChar.name + DLG_TEXT_TV[6], DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> Проверяем поле состояния квестов.
            switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
                    link.l1 = DLG_TEXT_TV[10];
                    link.l1.go = "Step_H3_1";
                break;
                case "DelivLettTortuga_toStranger": //Голландская линейка, квест №7. узнаем о ожидающем ГГ человеке.
                    link.l1 = DLG_TEXT_TV[11];
                    link.l1.go = "Step_H7_1";
                break;
                case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. пытаемся узнать, кто был грабитель.
                    link.l1 = DLG_TEXT_TV[12];
                    link.l1.go = "Step_H7_2";
                break;
                case "SeekBible_toTavern": //Голландская линейка, квест №8. узнаем, где Лоран де Граф.
                    link.l1 = DLG_TEXT_TV[13];
                    link.l1.go = "Step_H8_1";
                break;
                case "TakeRockBras_toTortuga": //Испанская линейка, квест №3. узнаем, где Рок Бразилец.
                    link.l1 = DLG_TEXT_TV[14];
                    link.l1.go = "Step_S3_1";
                break;
                case "Sp4Detection_toTortuga": //Испанская линейка, квест №4. узнаем о донне Анне.
                    link.l1 = DLG_TEXT_TV[15];
                    link.l1.go = "Step_S4_1";
                break;
                case "Sp6TakeMess_toTotuga": //Испанская линейка, квест №6. узнаем о вестовом
                    link.l1 = DLG_TEXT_TV[16];
                    link.l1.go = "Step_S6_1";
                break;
                case "Sp6TakeMess_waitMessanger": //Испанская линейка, квест №6. узнаем о вестовом
                    link.l1 = DLG_TEXT_TV[17];
                    link.l1.go = "Step_S6_1";
                break;
            }
            // <== Проверяем поле состояния квестов.
        break;
//===================================== Голл. линейка, квест №3 =========================================
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[18], DLG_TEXT_TV[19], 
				          DLG_TEXT_TV[20], DLG_TEXT_TV[21], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[22], DLG_TEXT_TV[23], DLG_TEXT_TV[24], DLG_TEXT_TV[25], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = DLG_TEXT_TV[26];
			link.l1 = DLG_TEXT_TV[27];
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = DLG_TEXT_TV[28];
			link.l1 = DLG_TEXT_TV[29];
			link.l1.go = "exit";
            pchar.questTemp.Talks.Tavern = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "7");
        break;
//============================ Голл. линейка, квест №7. узнаем о ожидающем ГГ челе =======================
 	 	case "Step_H7_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[30], DLG_TEXT_TV[31], DLG_TEXT_TV[32], DLG_TEXT_TV[33], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[34], DLG_TEXT_TV[35], DLG_TEXT_TV[36], DLG_TEXT_TV[37], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H7_2":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[38], DLG_TEXT_TV[39], DLG_TEXT_TV[40], DLG_TEXT_TV[41], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[42], DLG_TEXT_TV[43], DLG_TEXT_TV[44], DLG_TEXT_TV[45], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H7_3", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_H7_3":
			dialog.text = DLG_TEXT_TV[46];
			link.l1 = DLG_TEXT_TV[47];
			link.l1.go = "Step_H7_4";
        break;
  	 	case "Step_H7_4":
			dialog.text = DLG_TEXT_TV[48];
			link.l1 = DLG_TEXT_TV[49];
			link.l1.go = "exit";
        break;
//============================ Голл. линейка, квест №8. узнаем о Лоране де Графе =======================
  	 	case "Step_H8_1":
			dialog.text = DLG_TEXT_TV[50];
			link.l1 = DLG_TEXT_TV[51];
			link.l1.go = "Step_H8_2";
        break;
  	 	case "Step_H8_2":
			dialog.text = DLG_TEXT_TV[52];
			link.l1 = DLG_TEXT_TV[53];
			link.l1.go = "Step_H8_3";
        break;
  	 	case "Step_H8_3":
			dialog.text = DLG_TEXT_TV[54];
			link.l1 = DLG_TEXT_TV[55];
			link.l1.go = "Step_H8_4";
        break;
   	 	case "Step_H8_4":
			dialog.text = DLG_TEXT_TV[56];
			link.l1 = DLG_TEXT_TV[57];
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toDeGraf";
            AddQuestRecord("Hol_Line_8_SeekBible", "5");
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1 = "location";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1.location = "Cartahena";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition = "SeekBible_SaveDeGraf";
        break;
//============================ Исп. линейка, квест №3. узнаем о Роке Бразильце =======================
  	 	case "Step_S3_1":
			dialog.text = DLG_TEXT_TV[58];
			link.l1 = DLG_TEXT_TV[59];
			link.l1.go = "Step_S3_2";
        break;
  	 	case "Step_S3_2":
			dialog.text = DLG_TEXT_TV[60];
			link.l1 = DLG_TEXT_TV[61];
			link.l1.go = "Step_S3_3";
        break;
  	 	case "Step_S3_3":
			dialog.text = DLG_TEXT_TV[62];
			link.l1 = DLG_TEXT_TV[63];
			link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "2");
			pchar.quest.TakeRockBras_toRock.win_condition.l1 = "location";
			pchar.quest.TakeRockBras_toRock.win_condition.l1.location = "Maracaibo";
			pchar.quest.TakeRockBras_toRock.win_condition = "TakeRockBras_toRock";
        break;
//============================ Испанская линейка, квест №4. узнаем о донне Анне. =======================
  	 	case "Step_S4_1":
			dialog.text = DLG_TEXT_TV[64];
			link.l1 = DLG_TEXT_TV[65];
			link.l1.go = "Step_S4_2";
        break;
  	 	case "Step_S4_2":
			dialog.text = DLG_TEXT_TV[66];
			link.l1 = DLG_TEXT_TV[67];
			link.l1.go = "Step_S4_3";
        break;
  	 	case "Step_S4_3":
			dialog.text = DLG_TEXT_TV[68];
			link.l1 = DLG_TEXT_TV[69];
			link.l1.go = "Step_S4_4";
        break;
  	 	case "Step_S4_4":
			dialog.text = DLG_TEXT_TV[70];
			link.l1 = DLG_TEXT_TV[71];
			link.l1.go = "Step_S4_5";
        break;
  	 	case "Step_S4_5":
			dialog.text = DLG_TEXT_TV[72];
			link.l1 = DLG_TEXT_TV[73];
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toDEstre";
            AddQuestRecord("Spa_Line_4_MirderDetection", "5");
        break;
//============================ Испанская линейка, квест №6. перехватить вестового. =======================
  	 	case "Step_S6_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[74],
                          DLG_TEXT_TV[75], DLG_TEXT_TV[76],
                          DLG_TEXT_TV[77], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[78],
                      DLG_TEXT_TV[79], DLG_TEXT_TV[80], DLG_TEXT_TV[81], npchar, Dialog.CurrentNode);
			link.l1.go =  DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_S6_2":
			dialog.text = DLG_TEXT_TV[82];
			link.l1 = DLG_TEXT_TV[83];
			link.l1.go = "Step_S6_3";
        break;
  	 	case "Step_S6_3":
			dialog.text = DLG_TEXT_TV[84];
			link.l1 = DLG_TEXT_TV[85];
			link.l1.go = "exit";
			pchar.questTemp.State.Open = 1;
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            AddMoneyToCharacter(pchar, -100);
            if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
            {
                SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7)+1, false);
                DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
            }
            else
            {
                pchar.questTemp.State.Sp6Ok = 1;
            }
        break;        
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

