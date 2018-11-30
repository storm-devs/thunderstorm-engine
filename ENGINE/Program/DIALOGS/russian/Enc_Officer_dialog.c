// BOAL новый диалог офицера и компаньона 21/06/06
#include "TEXT\DIALOGS\Enc_Officer_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    sld;
	string attr;
	int    iTemp, iTax, iFortValue;
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[4];
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = DLG_TEXT_BASE[5];
    			Link.l1.go = "Node_2";
			}
			Link.l2 = DLG_TEXT_BASE[6];
			Link.l2.go = "Exit";			
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = DLG_TEXT_BASE[7];
				link.l2 = DLG_TEXT_BASE[8];
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit")
			{
				dialog.text = DLG_TEXT_BASE[9];
				Link.l1 = DLG_TEXT_BASE[10];
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
			dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]);
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = DLG_TEXT_BASE[13];
	            Link.l2.go = "stay_follow";
            }
			Link.l4 = DLG_TEXT_BASE[14] + NPCharSexPhrase(NPChar, "", DLG_TEXT_BASE[15]) + DLG_TEXT_BASE[16];
			Link.l4.go = "AsYouWish";

            // boal отчет о корабле
            /*if (CheckNPCharQuestAttribute(Npchar, "officertype", XI_ConvertString("treasurer")))
            {
                Link.l8 = DLG_TEXT_BASE[17] + XI_ConvertString("treasurer") + ".";
                Link.l8.go = "QMASTER_1";
            } */
            // по тек локации определим можно ли тут приказать  -->
            if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
                            NPChar.ColonyIdx = iTemp;
							Link.l7 = DLG_TEXT_BASE[18];
                            Link.l7.go = "Gover_Hire";
                        }
                    }
                }
            }
            Link.l9 = DLG_TEXT_BASE[19];
            Link.l9.go = "Exit";
        break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[20],
                           DLG_TEXT_BASE[21],
                           DLG_TEXT_BASE[22]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[23],
			                         DLG_TEXT_BASE[24],
			                         DLG_TEXT_BASE[25]);
			Link.l1.go = "WantToGo_free";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[26],
			                         DLG_TEXT_BASE[27],
			                         DLG_TEXT_BASE[28]);
			Link.l2.go = "WantToGo_Stay";
		break;
		
		case "WantToGo_Stay":
			dialog.text = DLG_TEXT_BASE[29];
			Link.l1 = DLG_TEXT_BASE[30];
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[31],
			                         DLG_TEXT_BASE[32],
			                         DLG_TEXT_BASE[33]);
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay_2":
			dialog.text = DLG_TEXT_BASE[34]+sti(NPChar.rank)*500+DLG_TEXT_BASE[35];
            if (sti(Pchar.money) >= sti(NPChar.rank)*500)
            {
        		Link.l1 = DLG_TEXT_BASE[36];
        		Link.l1.go = "WantToGo_Stay_ForMoney";
			}
			Link.l2 = DLG_TEXT_BASE[37];
        	Link.l2.go = "WantToGo_free";

		break;
		case "WantToGo_Stay_ForMoney":
            Diag.TempNode = "Hired";
            NPChar.greeting           = "Gr_Officer";
            AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
            Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;
		
		case "WantToGo_free":
            Diag.TempNode = "WantToGo_free_Yet";
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();			
				break;
			}
			//navy <--
		    Pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		
		case "WantToGo_free_Yet":
            Diag.TempNode = "WantToGo_free_Yet";
			dialog.text = DLG_TEXT_BASE[38];
			Link.l1 = DLG_TEXT_BASE[39];
			Link.l1.go = "exit";
		break;
		// boal 29.05.04 офицер хочет свалить <--
		
		// пассажир возмущен игроком и сваливает -->
		case "WantToRemove":
            chrDisableReloadToLocation = false;
			if (Npchar.alignment == "good")
            {
			    dialog.text = DLG_TEXT_BASE[40];
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[41];
			}
			Link.l1 = DLG_TEXT_BASE[42];
			Link.l1.go = "WantToGo_free";
		break;
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + DLG_TEXT_BASE[43]+ XI_ConvertString(Npchar.quest.officertype) + DLG_TEXT_BASE[44] + Npchar.quest.officertype_2 + DLG_TEXT_BASE[45],
                                    DLG_TEXT_BASE[46] + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + DLG_TEXT_BASE[47]);
			Link.l1 = DLG_TEXT_BASE[48];
			Link.l1.go = "price";
			Link.l2 = DLG_TEXT_BASE[49];
			Link.l2.go = "ShowParam_exit";
			Link.l3 = DLG_TEXT_BASE[50] + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[53], DLG_TEXT_BASE[54]); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = DLG_TEXT_BASE[55] + XI_ConvertString(Npchar.quest.officertype) + DLG_TEXT_BASE[56];
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = DLG_TEXT_BASE[57];
                Link.l1.go = "price";
			}
			Link.l2 = DLG_TEXT_BASE[58];
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = DLG_TEXT_BASE[59];
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = DLG_TEXT_BASE[60] + Npchar.quest.OfficerPrice + DLG_TEXT_BASE[61];
			Link.l1 = DLG_TEXT_BASE[62];
			Link.l1.go = "trade";
			Link.l2 = DLG_TEXT_BASE[63];
			Link.l2.go = "hire";
			Link.l3 = DLG_TEXT_BASE[64];
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = DLG_TEXT_BASE[65] + Npchar.quest.OfficerPrice + DLG_TEXT_BASE[66];
				Link.l1 = DLG_TEXT_BASE[67];
				Link.l1.go = "hire";				
				Link.l2 = DLG_TEXT_BASE[68];
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[69];
				Link.l1 = DLG_TEXT_BASE[70];
				Link.l1.go = "hire";				
				Link.l2 = DLG_TEXT_BASE[71];
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = DLG_TEXT_BASE[72];
				Link.l1 = DLG_TEXT_BASE[73];
				Link.l1.go = "Exit_hire";								
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[74];
				Link.l1 = DLG_TEXT_BASE[75];
				Link.l1.go = "Exit";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = DLG_TEXT_BASE[76];
			Link.l1 = DLG_TEXT_BASE[77];
			Link.l1.go = "Exit";											
		break;
        
        case "QMASTER_1":
            dialog.text = DLG_TEXT_BASE[78] +
                     FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
                     DLG_TEXT_BASE[79]+GetCrewQuantity(PChar) + DLG_TEXT_BASE[80] + makeint((GetCrewQuantity(PChar)+6) / 10) + DLG_TEXT_BASE[81];
            Link.l1 = DLG_TEXT_BASE[82];
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = DLG_TEXT_BASE[83];
            Link.l1 = DLG_TEXT_BASE[84];
            Link.l1.go = "Boal_Stay";
            Link.l2 = DLG_TEXT_BASE[85];
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = DLG_TEXT_BASE[86];
				Link.l3.go = "TargetDistance";
			}
		break;

		case "TargetDistance":
			dialog.text = DLG_TEXT_BASE[87];
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = DLG_TEXT_BASE[88];
				link.l1 = DLG_TEXT_BASE[89];
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = DLG_TEXT_BASE[90];
				link.l1 = DLG_TEXT_BASE[91];
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = DLG_TEXT_BASE[92];
				link.l1 = DLG_TEXT_BASE[93];
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = DLG_TEXT_BASE[96];
					Link.l1 = DLG_TEXT_BASE[97];
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			dialog.text = DLG_TEXT_BASE[98];
			Link.l1 = DLG_TEXT_BASE[99] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[100], DLG_TEXT_BASE[101]) + ".";
			Link.l1.go = "Exit";								
			Link.l2 = DLG_TEXT_BASE[102];
			Link.l2.go = "Exit_Fire";		
		break;
		
		case "Fired":
		      Diag.TempNode = "Fired";
		      dialog.text = DLG_TEXT_BASE[103] + NPCharSexPhrase(NPChar, "", DLG_TEXT_BASE[104]) + DLG_TEXT_BASE[105];
		      Link.l1 = DLG_TEXT_BASE[106] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[107], DLG_TEXT_BASE[108]) + "!";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "Hired";
		      dialog.text = DLG_TEXT_BASE[109];
		      Link.l1 = DLG_TEXT_BASE[110];
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = DLG_TEXT_BASE[111];
		      Link.l1 = DLG_TEXT_BASE[112];
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = DLG_TEXT_BASE[113];
            Link.l1 = DLG_TEXT_BASE[114];
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = DLG_TEXT_BASE[115];
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
            NPChar.location = attr;
            NPChar.location.group = "goto";
			NPChar.location.locator = "governor1";
			LAi_SetHuberStayTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = DLG_TEXT_BASE[116] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[117];
			}
			else
			{
			    dialog.Text = DLG_TEXT_BASE[118];
			}

            Link.l1 = DLG_TEXT_BASE[119] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[120], DLG_TEXT_BASE[121]) + DLG_TEXT_BASE[122];
        	Link.l1.go = "Gover_Tax";
            Link.l8 = DLG_TEXT_BASE[123] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[124], DLG_TEXT_BASE[125]) + DLG_TEXT_BASE[126];
            Link.l8.go = "Gover_Fire";
			Link.l9 = DLG_TEXT_BASE[127];
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = DLG_TEXT_BASE[128] + FindRussianMoneyString(iFortValue*iTax) + DLG_TEXT_BASE[129] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[130] + NPCharSexPhrase(NPChar, DLG_TEXT_BASE[131], DLG_TEXT_BASE[132]) + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = DLG_TEXT_BASE[133];
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = DLG_TEXT_BASE[134];
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = DLG_TEXT_BASE[135];
            Link.l8 = DLG_TEXT_BASE[136];
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--
	}
}
