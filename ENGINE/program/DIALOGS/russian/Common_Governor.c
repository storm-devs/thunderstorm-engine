// boal 25/04/04 общий диалог Governor
#include "TEXT\DIALOGS\Common_Governor.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = "fight";
				break;
			} 
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[10] + GetFullName(npchar) +
                              DLG_TEXT_BASE[11] + NationNameGenitive(sti(NPChar.nation))+ DLG_TEXT_BASE[12] + NationKingsName(npchar)+
                              DLG_TEXT_BASE[13] + GetAddress_Form(NPChar) + ".";
				link.l1 = DLG_TEXT_BASE[14] + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[15] + NationNameGenitive(sti(NPChar.nation))+ DLG_TEXT_BASE[16],
                              DLG_TEXT_BASE[17] +GetAddress_Form(NPChar)+"?");
				link.l1 = DLG_TEXT_BASE[18] + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = DLG_TEXT_BASE[19];
				link.l2.go = "quests"; // файл нации
				link.l10 = DLG_TEXT_BASE[20];
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = DLG_TEXT_BASE[22] + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = DLG_TEXT_BASE[23];
			link.l2.go = "quests";
			link.l10 = DLG_TEXT_BASE[24]+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "exit";
		break;
		
		case "work":
            if (!CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) || !CheckAttribute(pchar, "EquipedPatentId"))
			{
    			dialog.text = DLG_TEXT_BASE[27] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[28] + NationKingsName(npchar) + ".";
    			link.l1 = DLG_TEXT_BASE[29]+NationNameGenitive(sti(NPChar.nation))+DLG_TEXT_BASE[30];
    			link.l1.go = "exit";
			}
			else
			{// даем задание
                // звание подрасло
                if (isReadyToNextTitle(sti(NPChar.nation)))
                {
                    Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
                    Items[sti(pchar.EquipedPatentId)].TitulCur = sti(Items[sti(pchar.EquipedPatentId)].TitulCur) + 1;

                    dialog.text = DLG_TEXT_BASE[31]+ ", " + GetAddress_Form(NPChar)+DLG_TEXT_BASE[32] + NationKingsName(npchar) +
                                DLG_TEXT_BASE[33] + GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) +
                                DLG_TEXT_BASE[34] + NationNameGenitive(sti(NPChar.nation)) +".";
        			link.l1 = DLG_TEXT_BASE[35]+NationKingsCrown(npchar) + ".";
        			link.l1.go = "exit";
        			break
                }
                // даем задание
                dialog.text = LinkRandPhrase(DLG_TEXT_BASE[36]+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+"?",
                                             DLG_TEXT_BASE[37] + GetAddress_Form(NPChar)+".",
                                             DLG_TEXT_BASE[38]);

                //GetAddress_Form(NPChar)+DLG_TEXT_BASE[39]+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+DLG_TEXT_BASE[40] + NationKingsName(npchar) + ".";
				if (pchar.questTemp.NationQuest == "")
                {
	    			if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8" || pchar.questTemp.LSC == "over")
					{
						link.l1 = DLG_TEXT_BASE[41];
	    				link.l1.go = "work_1";
						if (!bWorldAlivePause && pchar.questTemp.State == "") //eddy. только, если не проходил линейку.
						{
							link.l1.go = "onlyGenWork_Alter";
						}
					}
					else
					{
						link.l1 = DLG_TEXT_BASE[42];
	    				link.l1.go = "onlyGenWork_2";
					}
    			}
    			else
    			{
    			    if (pchar.questTemp.NationQuest == NPChar.nation)
	                {
		    			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[43], DLG_TEXT_BASE[44]);
		    			link.l1.go = "work_1";
	    			}
	    			else
	    			{// линейкам - фиг
	    			    link.l1 = DLG_TEXT_BASE[45];
	    				link.l1.go = "onlyGenWork_1";
	    			}
    			}

                // Сдача города -->
				if (isHeroOwnCity(false))
				{
				    Link.l2 = DLG_TEXT_BASE[46]+ XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen") +".";
					Link.l2.go = "colony_capture";
				}
                // Сдача города <--
                link.l9 = RandPhraseSimple(DLG_TEXT_BASE[47],
                                           DLG_TEXT_BASE[48]+GetAddress_FormToNPC(NPChar)+DLG_TEXT_BASE[49]);
    			link.l9.go = "exit";
			}
		break;
		
		case "onlyGenWork_1":
			dialog.text = DLG_TEXT_BASE[50]+ NationNameGenitive(sti(pchar.questTemp.NationQuest)) +DLG_TEXT_BASE[51];
			link.l1 = DLG_TEXT_BASE[52];
			link.l1.go = "exit";
		break;

		case "onlyGenWork_2":
			dialog.text = DLG_TEXT_BASE[53] + NationNameGenitive(sti(npchar.nation)) + ".";
			link.l1 = DLG_TEXT_BASE[54];
			link.l1.go = "exit";
		break;

		case "onlyGenWork_Alter":
   			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "exit";
		break;

		/////Награда за захваченную колонию.
		case "colony_capture":
   			dialog.text = DLG_TEXT_BASE[57];
   			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id);
					Link.(attrLoc).go = "CityGive_" + i;
				}
			}
			link.l99 = DLG_TEXT_BASE[58];
			link.l99.go = "exit";
		break;
		
        case "ColonyGive":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            colony_money = TWN_CityCost(colonies[i].id) / 50;  // те *1000 в итоге
            TWN_RealeseForMoney(colonies[i].id, false);
            dialog.text = DLG_TEXT_BASE[59]+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+
                          DLG_TEXT_BASE[60] + colony_money +
                          DLG_TEXT_BASE[61]+NationNameAblative(sti(NPChar.nation))+
                          DLG_TEXT_BASE[62];
            link.l1 = DLG_TEXT_BASE[63] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_BASE[64];
            link.l1.go = "exit";

            ReOpenQuestHeader("Gen_CityCapture");
		    AddQuestRecord("Gen_CityCapture", "t8");
			AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(colonies[i].id));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen"));
		
            AddMoneyToCharacter(PChar, colony_money);
            AddTitleNextRate(sti(NPChar.nation), 1);  // счетчик звания
            ChangeCharacterNationReputation(Pchar, sti(NPChar.nation), 10);
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(colonies[i].id, sti(NPChar.nation));
        break;
	}
}
