#include "TEXT\DIALOGS\Mayor\EdwardMansfield.h"
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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_MR[0],
                         DLG_TEXT_MR[1], DLG_TEXT_MR[2],
                         DLG_TEXT_MR[3], "repeat", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_MR[4],
                                               DLG_TEXT_MR[5] + npchar.name + DLG_TEXT_MR[6],
                                               DLG_TEXT_MR[7] + npchar.name + "...",
                                               DLG_TEXT_MR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//********************* Английская линейка *********************
 		case "EngLine_quests":
			dialog.text = DLG_TEXT_MR[9];
			link.l1 = DLG_TEXT_MR[10];
			link.l1.go = "Step_1";
  		break;
 		case "Step_1":
			dialog.text = DLG_TEXT_MR[11];
			link.l1 = DLG_TEXT_MR[12];
			link.l1.go = "Step_2";
  		break;
 		case "Step_2":
			dialog.text = DLG_TEXT_MR[13];
			link.l1 = DLG_TEXT_MR[14];
			link.l1.go = "Step_3";
  		break;
 		case "Step_3":
			dialog.text = DLG_TEXT_MR[15];
			link.l1 = DLG_TEXT_MR[16];
			link.l1.go = "Step_4";
  		break;
 		case "Step_4":
			dialog.text = DLG_TEXT_MR[17];
			link.l1 = DLG_TEXT_MR[18];
			link.l1.go = "Step_5";
  		break;
 		case "Step_5":
			dialog.text = DLG_TEXT_MR[19];
			link.l1 = DLG_TEXT_MR[20];
			link.l1.go = "Step_6";
  		break;
 		case "Step_6":
			dialog.text = DLG_TEXT_MR[21];
			link.l1 = DLG_TEXT_MR[22];
			link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            AddQuestRecord("Eng_Line_2_Talking", "3");

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
			}
  		break;
 		case "No_Mansfield_first_time":
			dialog.text = DLG_TEXT_MR[23];
			link.l1 = DLG_TEXT_MR[24];
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = DLG_TEXT_MR[25];
			link.l1 = DLG_TEXT_MR[26];
			link.l1.go = "exit";
  		break;
		//********************* Голландская линейка *********************
  		case "HolLine3_WormEngPlans":
			dialog.text = DLG_TEXT_MR[27];
			link.l1 = DLG_TEXT_MR[28];
			link.l1.go = "Step_H3_1";
        break;
 		case "Step_H3_1":
			dialog.text = DLG_TEXT_MR[29];
			link.l1 = DLG_TEXT_MR[30];
			link.l1.go = "Step_H3_2";
  		break;
 		case "Step_H3_2":
			dialog.text = DLG_TEXT_MR[31];
			link.l1 = DLG_TEXT_MR[32];
			link.l1.go = "Step_H3_3";
  		break;
 		case "Step_H3_3":
			dialog.text = DLG_TEXT_MR[33];
			link.l1 = DLG_TEXT_MR[34];
			link.l1.go = "Step_H3_4";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
  		break;
 		case "Step_H3_4":
			dialog.text = DLG_TEXT_MR[35];
			link.l1 = DLG_TEXT_MR[36];
			link.l1.go = "Step_H3_5";
  		break;
 		case "Step_H3_5":
			dialog.text = DLG_TEXT_MR[37]+
                          DLG_TEXT_MR[38]+
                          DLG_TEXT_MR[39];
			link.l1 = DLG_TEXT_MR[40];
			link.l1.go = "Step_H3_6";
  		break;
 		case "Step_H3_6":
			dialog.text = DLG_TEXT_MR[41]+
                          DLG_TEXT_MR[42];
			link.l1 = DLG_TEXT_MR[43];
			link.l1.go = "Step_H3_7";
  		break;
 		case "Step_H3_7":
			dialog.text = DLG_TEXT_MR[44]+
                          DLG_TEXT_MR[45];
			link.l1 = DLG_TEXT_MR[46];
			link.l1.go = "Step_H3_8";
  		break;
 		case "Step_H3_8":
			dialog.text = DLG_TEXT_MR[47];
			link.l1 = DLG_TEXT_MR[48];
			link.l1.go = "Step_H3_9";
  		break;
 		case "Step_H3_9":
			dialog.text = DLG_TEXT_MR[49];
			link.l1 = DLG_TEXT_MR[50];
			link.l1.go = "Step_H3_10";
  		break;
 		case "Step_H3_10":
			dialog.text = DLG_TEXT_MR[51];
			link.l1 = DLG_TEXT_MR[52];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_toMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "2");
    		QuestSetCurrentNode("Henry Morgan", "HolLine3_fromMansfield");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            LAi_SetHuberStayType(characterFromId("Henry Morgan"));
          break;


// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[53], DLG_TEXT_MR[54]);
			link.l1 = DLG_TEXT_MR[55];
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = DLG_TEXT_MR[56];
        			link.l1 = DLG_TEXT_MR[57];
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
