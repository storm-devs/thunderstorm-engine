#include "TEXT\DIALOGS\Common_ItemTrader.h"
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
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
			if (npchar.angry.name == "AscoldMerchant") Dialog.CurrentNode = "AngryQuest_AscoldMerchant";
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0], 
					DLG_TEXT_BASE[1], 
					DLG_TEXT_BASE[2]);
				link.l1 = DLG_TEXT_BASE[3];
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
			{
				dialog.text = DLG_TEXT_BASE[4];
				link.l1 = DLG_TEXT_BASE[5];
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город 

			dialog.text = NPCharSexPhrase(npchar, DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
			link.l1 = DLG_TEXT_BASE[8];
			link.l1.go = "Trade_exit";
			
   			link.l2 = DLG_TEXT_BASE[9];
			link.l2.go = "quests";
			//--> eddy. Аскольд, перехват на рендомного перца
			if (pchar.questTemp.Ascold == "Seek_powder")
			{
   				link.l4 = LinkRandPhrase(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]);
				link.l4.go = "AscoldMerchant";
			}
			//<-- eddy. Аскольд, перехват на рендомного перца
			link.l3 = DLG_TEXT_BASE[13];
			link.l3.go = "exit";

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = DLG_TEXT_BASE[14] + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], DLG_TEXT_BASE[15], DLG_TEXT_BASE[16]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[17], DLG_TEXT_BASE[18]);
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		//Квест Аскольда. Базары с уличными торговцами
		case "AscoldMerchant": 
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21]),
                     LinkRandPhrase(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23], DLG_TEXT_BASE[24]),
                     LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[27], DLG_TEXT_BASE[28]),
                                    DLG_TEXT_BASE[29]),
                     LinkRandPhrase(DLG_TEXT_BASE[30], DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]), "quest", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[33],
                                               DLG_TEXT_BASE[34],
                                               DLG_TEXT_BASE[35],
                                               DLG_TEXT_BASE[36], npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("AscoldMerchant_2", "AscoldMerchant_3", "AscoldMerchant_4", "", npchar, Dialog.CurrentNode);
		break;
		
		case "AscoldMerchant_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[37],
                     NPCharSexPhrase(npchar, DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]),
                     NPCharSexPhrase(npchar, DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]));
			Link.l1 = DLG_TEXT_BASE[42];
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_3":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[43], DLG_TEXT_BASE[44]),
                                    DLG_TEXT_BASE[45],
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[46], DLG_TEXT_BASE[47]));
			Link.l1 = DLG_TEXT_BASE[48];
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_4":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, DLG_TEXT_BASE[49], DLG_TEXT_BASE[50]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]),
                                    NPCharSexPhrase(npchar, DLG_TEXT_BASE[53], DLG_TEXT_BASE[54]));
			Link.l1 = NPCharSexPhrase(npchar, DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
			Link.l1.go = "exit";
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryQuest_AscoldMerchant":
            Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[59], DLG_TEXT_BASE[60]);
		    Link.l1.go = "AngryExitAgain";
		    //===>> квест Аскольда, розыск порошка мумии.
            if (pchar.questTemp.Ascold == "Seek_powder" && npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
            {
                Dialog.text =  DLG_TEXT_BASE[61];
    			Link.l1 = DLG_TEXT_BASE[62];
    		    Link.l1.go = "AngStep_1";
            }
            if (CheckAttribute(npchar, "angry.terms")) //мирилка по квесту Аскольда через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms) && pchar.questTemp.Ascold != "Seek_powder")
                {
         			Dialog.text = NPCharSexPhrase(npchar, DLG_TEXT_BASE[63], DLG_TEXT_BASE[64]);
        			Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[65], DLG_TEXT_BASE[66]);
        			Link.l1.go = "First time";
        			CharacterDelAngry(npchar);
                }
            }
    	break;
////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

		case "AngStep_1":
            Dialog.text = DLG_TEXT_BASE[67];
            if (sti(pchar.money) >= 1000)
            {
    			Link.l1 = DLG_TEXT_BASE[68];
    		    Link.l1.go = "AngryExitAgain";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    CharacterDelAngry(npchar);
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");
            }
            else
            {
    			Link.l1 = DLG_TEXT_BASE[69];
    		    Link.l1.go = "AngryExitAgain";
            }
    	break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
