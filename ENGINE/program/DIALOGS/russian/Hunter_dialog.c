#include "TEXT\DIALOGS\Hunter_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, TempChar;
	aref Link, Diag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Aeaeia ia?aue - ia?aay ano?a?a
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar) + "! "+DLG_TEXT_BASE[0];
			Link.l1 = DLG_TEXT_BASE[1];
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + DLG_TEXT_BASE[2];
			Link.l1 = DLG_TEXT_BASE[3];
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = DLG_TEXT_BASE[4]+ GetFullName(TempChar) + DLG_TEXT_BASE[5];
    			Link.l2.go = "lier";
			}
            Link.l3 = DLG_TEXT_BASE[6];
			Link.l3.go = "battle";
			// to_do
            /*PChar.GenQuest.ToPrisonCmdIdx = GetCharIDXByParam("PrisonCommander", "nation", NPChar.nation);
            if (sti(PChar.GenQuest.ToPrisonCmdIdx) > 0)
            {
                Link.l4 = DLG_TEXT_BASE[7];
    			Link.l4.go = "ToPrison";
            }*/
		break;
		
		/*case "ToPrison":
            AddDialogExitQuest("Hunters_GoToPrison");
            
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // oieuei ICAe, a ia eeaaienaoaee
            {   // caienu a N?
	            AddQuestRecord("HeadHunter", "HeadHunter_GiveUp");
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;  */
        
        case "lier":
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > rand(15) || bBettaTestMode)
            {
                dialog.text = DLG_TEXT_BASE[8]+ GetAddress_Form(NPChar) + ".";
                Link.l1 = DLG_TEXT_BASE[9];
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 30);
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[10];
                Link.l1 = DLG_TEXT_BASE[11];
			    Link.l1.go = "Cost_Head";
			    Link.l2 = DLG_TEXT_BASE[12];
			    Link.l2.go = "battle";
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // oieuei ICAe, a ia eeaaienaoaee
            {   // caienu a N?
	            AddQuestRecord("HeadHunter", "HeadHunter_free");
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Aanu eia y ia?aian n?aa ii anai iaoeyi, i?inoi ia ia?aeiaiiaae
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // oieuei ICAe, a ia eeaaienaoaee
            {   // caienu a N?
	            AddQuestRecord("HeadHunter", "HeadHunter_battle");
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            
            if (CheckAttribute(PChar, "GenQuest.HunterStart")) // oieuei ICAe, a ia eeaaienaoaee
            {   // caienu a N?
	            AddQuestRecord("HeadHunter", "HeadHunter_Buy");
				AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
				AddQuestUserData("HeadHunter", "sLoc", GetLocHunterName());
                DeleteAttribute(PChar, "GenQuest.HunterStart"); 
            }
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = DLG_TEXT_BASE[13] + PChar.HunterCost + DLG_TEXT_BASE[14];
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = DLG_TEXT_BASE[15];
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = DLG_TEXT_BASE[16];
                Link.l1.go = "Cost_Head2";
                Link.l2 = DLG_TEXT_BASE[17];
                Link.l2.go = "battle";
            }
		break;


        case "NoMoney":
			dialog.text = DLG_TEXT_BASE[18];
			Link.l1 = DLG_TEXT_BASE[19];
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = DLG_TEXT_BASE[20];
            Link.l1 = DLG_TEXT_BASE[21];
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = DLG_TEXT_BASE[22]+ GetFullName(TempChar) + DLG_TEXT_BASE[23];
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = DLG_TEXT_BASE[24];
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > rand(15))
            {
                dialog.text = DLG_TEXT_BASE[25]+ GetAddress_Form(NPChar)+".";
                Link.l1 = DLG_TEXT_BASE[26];
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20);
            }
            else
            {
                dialog.text = DLG_TEXT_BASE[27];
			    Link.l1 = DLG_TEXT_BASE[28];
			    Link.l1.go = "battle";
            }
        break;
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";
	
	if(nFile >= 0) 
	{
		if (CheckAttribute(&locations[nLoc],"islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = DLG_TEXT_BASE[29] + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = DLG_TEXT_BASE[30];
			}
		}
		//
        if (CheckAttribute(&locations[nLoc],"fastreload"))
		{
			ret += " (" +LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		//ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile( nFile );
	}
	return ret;	
}
