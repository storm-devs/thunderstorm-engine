#include "TEXT\DIALOGS\Quest\Questions.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;	
		case "exit_over":			
			npchar.lifeDay = 0;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;	
		case "good_all":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_Q[0] + NPCharSexPhrase(npchar, "",DLG_TEXT_Q[1]) + DLG_TEXT_Q[2], 
				DLG_TEXT_Q[3], 
				DLG_TEXT_Q[4],
                DLG_TEXT_Q[5], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_Q[6], 
				DLG_TEXT_Q[7],
                DLG_TEXT_Q[8], 
				DLG_TEXT_Q[9], npchar, Dialog.CurrentNode);
			link.l1.go = "Exit";
			NextDiag.TempNode = "good_all";
		break;
		case "All_disagree":
			npchar.lifeDay = 0;
			NextDiag.TempNode = "All_bye";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "All_bye":
			dialog.text = DLG_TEXT_Q[10];
			link.l1 = DLG_TEXT_Q[11];
			link.l1.go = "Exit";
			NextDiag.TempNode = "All_bye";
		break;
		//================================== в Порт оф Спейне ======================================
		case "PortSpein":
			NextDiag.TempNode = "PortSpein";
			dialog.text = DLG_TEXT_Q[12];
			link.l1 = DLG_TEXT_Q[13];
			link.l1.go = "exit_over";			
			link.l2 = DLG_TEXT_Q[14];
			link.l2.go = "PortSpein_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortSpein_1":
			dialog.text = DLG_TEXT_Q[15] +  GetAddress_Form(NPChar) + DLG_TEXT_Q[16];
			link.l1 = DLG_TEXT_Q[17];
			link.l1.go = "PortSpein_2";
		break;
		case "PortSpein_2":
			dialog.text = DLG_TEXT_Q[18];
			link.l1 = DLG_TEXT_Q[19];
			link.l1.go = "PortSpein_3";
		break;
		case "PortSpein_3":
			dialog.text = DLG_TEXT_Q[20];
			link.l1 = DLG_TEXT_Q[21];
			link.l1.go = "PortSpein_4";
			link.l2 = DLG_TEXT_Q[22];
			link.l2.go = "All_disagree";
		break;
		case "PortSpein_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[23] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";	
		break;
		case "PortSpein_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[24];
				link.l1 = DLG_TEXT_Q[25];
				link.l1.go = "PortSpein_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[26];
				link.l1 = DLG_TEXT_Q[27];
				link.l1.go = "PortSpein_5";
				link.l2 = DLG_TEXT_Q[28];
				link.l2.go = "PortSpein_6";
			}
		break;
		case "PortSpein_ok":
			dialog.text = DLG_TEXT_Q[29];
			link.l1 = DLG_TEXT_Q[30];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.LaVega_town = true;
			pchar.GenQuestRandItem.LaVega_town.randitem4 = "blade19";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "PortSpein_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[31] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_6":
			dialog.text = DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "exit";
			NextDiag.TempNode = "PortSpein_again";
		break;
		case "PortSpein_again":
			dialog.text = DLG_TEXT_Q[34];
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "PortSpein_5";
		break;
		//================================== Виллемстад ======================================
		case "Villemstad":
			NextDiag.TempNode = "Villemstad";
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "exit_over";
			link.l2 = DLG_TEXT_Q[38];
			link.l2.go = "Villemstad_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Villemstad_1":
			dialog.text = DLG_TEXT_Q[39];
			link.l1 = DLG_TEXT_Q[40] +  GetAddress_FormToNPC(NPChar) + "?";
			link.l1.go = "Villemstad_2";
		break;
		case "Villemstad_2":
			dialog.text = DLG_TEXT_Q[41];
			link.l1 = DLG_TEXT_Q[42];
			link.l1.go = "Villemstad_3";
		break;
		case "Villemstad_3":
			dialog.text = DLG_TEXT_Q[43];
			link.l1 = DLG_TEXT_Q[44];
			link.l1.go = "Villemstad_4";
		break;
		case "Villemstad_4":
			dialog.text = DLG_TEXT_Q[45]+
				DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47];
			link.l1.go = "Villemstad_5";
			link.l2 = DLG_TEXT_Q[48];
			link.l2.go = "All_disagree";
		break;
		case "Villemstad_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[49] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Villemstad_check";	
		break;
		case "Villemstad_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[50];
				link.l1 = DLG_TEXT_Q[51];
				link.l1.go = "Villemstad_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[52];
				link.l1 = DLG_TEXT_Q[53];
				link.l1.go = "Villemstad_6";
				link.l2 = DLG_TEXT_Q[54];
				link.l2.go = "Villemstad_7";
			}
		break;
		case "Villemstad_ok":
			dialog.text = DLG_TEXT_Q[55];
			link.l1 = DLG_TEXT_Q[56];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.PuertoPrincipe_town = true;
			pchar.GenQuestRandItem.PuertoPrincipe_town.randitem1 = "spyglass3";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "2");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "Villemstad_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[57] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Villemstad_check";
		break;
		case "Villemstad_7":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "exit";
			NextDiag.TempNode = "Villemstad_again";
		break;
		case "Villemstad_again":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61] +  GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Villemstad_6";
		break;
		//================================== Порт-о-Принс ======================================
		case "PortPax":
			NextDiag.TempNode = "PortPax";
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "exit_over";
			link.l2 = DLG_TEXT_Q[64] +  GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "PortPax_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortPax_1":
			dialog.text = DLG_TEXT_Q[65];
			link.l1 = DLG_TEXT_Q[66];
			link.l1.go = "PortPax_2";
		break;
		case "PortPax_2":
			dialog.text = DLG_TEXT_Q[67];
			link.l1 = DLG_TEXT_Q[68] +  GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[69];
			link.l1.go = "PortPax_3";
		break;
		case "PortPax_3":
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "PortPax_4";
		break;
		case "PortPax_4":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "PortPax_5";
			link.l2 = DLG_TEXT_Q[74];
			link.l2.go = "All_disagree";
		break;
		case "PortPax_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[75] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortPax_check";	
		break;
		case "PortPax_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[76];
				link.l1 = DLG_TEXT_Q[77];
				link.l1.go = "PortPax_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[78];
				link.l1 = DLG_TEXT_Q[79];
				link.l1.go = "PortPax_6";
				link.l2 = DLG_TEXT_Q[80];
				link.l2.go = "PortPax_7";
			}
		break;
		case "PortPax_ok":
			dialog.text = DLG_TEXT_Q[81];
			link.l1 = DLG_TEXT_Q[82];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Tortuga_Cave = true;
			pchar.GenQuestRandItem.Tortuga_Cave.randitem1 = "blade24";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "3");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "PortPax_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[83] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortPax_check";
		break;
		case "PortPax_7":
			dialog.text = DLG_TEXT_Q[84];
			link.l1 = DLG_TEXT_Q[85];
			link.l1.go = "exit";
			NextDiag.TempNode = "PortPax_again";
		break;
		case "PortPax_again":
			dialog.text = DLG_TEXT_Q[86];
			link.l1 = DLG_TEXT_Q[87];
			link.l1.go = "PortPax_6";
		break;
		//================================== Сан-Хуан ======================================
		case "SanJuan":
			NextDiag.TempNode = "SanJuan";
			dialog.text = DLG_TEXT_Q[88];
			link.l1 = DLG_TEXT_Q[89];
			link.l1.go = "exit_over";
			link.l2 = DLG_TEXT_Q[90] + GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "SanJuan_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "SanJuan_1":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "SanJuan_2";
		break;
		case "SanJuan_2":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "SanJuan_3";
		break;
		case "SanJuan_3":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "SanJuan_4";
		break;
		case "SanJuan_4":
			dialog.text = DLG_TEXT_Q[97];
			link.l1 = DLG_TEXT_Q[98];
			link.l1.go = "SanJuan_5";
			link.l2 = DLG_TEXT_Q[99];
			link.l2.go = "All_disagree";
		break;
		case "SanJuan_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[100] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";	
		break;
		case "SanJuan_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[101];
				link.l1 = DLG_TEXT_Q[102];
				link.l1.go = "SanJuan_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[103];
				link.l1 = DLG_TEXT_Q[104];
				link.l1.go = "SanJuan_6";
				link.l2 = DLG_TEXT_Q[105];
				link.l2.go = "SanJuan_7";
			}
		break;
		case "SanJuan_ok":
			int iNation = 5;
			for (int i=0; i<4 ; i++)
			{
				if (GetRelation2BaseNation(i) == RELATION_ENEMY)
				{
					iNation = i;
					break;
				}
			}
			if (iNation == 5) iNation = rand(3);
			GiveNationLicence(iNation, 40);
			dialog.text = DLG_TEXT_Q[106] + GetRusNameNationLicence(iNation) + DLG_TEXT_Q[107];
			link.l1 = DLG_TEXT_Q[108] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_Q[109];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
		break;
		case "SanJuan_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[110] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_7":
			dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112];
			link.l1.go = "exit";
			NextDiag.TempNode = "SanJuan_again";
		break;
		case "SanJuan_again":
			dialog.text = DLG_TEXT_Q[113];
			link.l1 = DLG_TEXT_Q[114];
			link.l1.go = "SanJuan_6";
		break;
		//================================== Кумана ======================================
		case "Cumana":
			NextDiag.TempNode = "Cumana";
			dialog.text = DLG_TEXT_Q[115];
			link.l1 = DLG_TEXT_Q[116];
			link.l1.go = "exit_over";			
			link.l2 = DLG_TEXT_Q[117];
			link.l2.go = "Cumana_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Cumana_1":
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "Cumana_2";
		break;
		case "Cumana_2":
			dialog.text = DLG_TEXT_Q[120];
			link.l1 = DLG_TEXT_Q[121];
			link.l1.go = "Cumana_3";
		break;
		case "Cumana_3":
			dialog.text = DLG_TEXT_Q[122];
			link.l1 = DLG_TEXT_Q[123];
			link.l1.go = "Cumana_4";
			link.l2 = DLG_TEXT_Q[124];
			link.l2.go = "All_disagree";
		break;
		case "Cumana_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[125] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";	
		break;
		case "Cumana_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[126];
				link.l1 = DLG_TEXT_Q[127];
				link.l1.go = "Cumana_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[128];
				link.l1 = DLG_TEXT_Q[129];
				link.l1.go = "Cumana_6";
				link.l2 = DLG_TEXT_Q[130];
				link.l2.go = "Cumana_7";
			}
		break;
		case "Cumana_ok":
			dialog.text = DLG_TEXT_Q[131];
			link.l1 = DLG_TEXT_Q[132];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore46 = true;
			pchar.GenQuestRandItem.Shore46.randitem1 = "STATUE1";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "4");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "Cumana_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[133] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_7":
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "exit";
			NextDiag.TempNode = "Cumana_again";
		break;
		case "Cumana_again":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "Cumana_6";
		break;
		//================================== Порт Рояль ======================================
		case "PortRoyal":
			NextDiag.TempNode = "PortRoyal";
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "exit_over";			
			link.l2 = DLG_TEXT_Q[140] + GetAddress_FormToNPC(NPChar) + "?";
			link.l2.go = "PortRoyal_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortRoyal_1":
			dialog.text = DLG_TEXT_Q[141];
			link.l1 = DLG_TEXT_Q[142];
			link.l1.go = "PortRoyal_2";
		break;
		case "PortRoyal_2":
			dialog.text = DLG_TEXT_Q[143];
			link.l1 = DLG_TEXT_Q[144];
			link.l1.go = "PortRoyal_3";
		break;
		case "PortRoyal_3":
			dialog.text = DLG_TEXT_Q[145];
			link.l1 = DLG_TEXT_Q[146];
			link.l1.go = "PortRoyal_4";
			link.l2 = DLG_TEXT_Q[147];
			link.l2.go = "All_disagree";
		break;
		case "PortRoyal_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[148] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";	
		break;
		case "PortRoyal_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[149];
				link.l1 = DLG_TEXT_Q[150];
				link.l1.go = "PortRoyal_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[151];
				link.l1 = DLG_TEXT_Q[152];
				link.l1.go = "PortRoyal_6";
				link.l2 = DLG_TEXT_Q[153];
				link.l2.go = "PortRoyal_7";
			}
		break;
		case "PortRoyal_ok":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore36 = true;
			pchar.GenQuestRandItem.Shore36.randitem2 = "blade20";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "5");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "PortRoyal_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[156] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_7":
			dialog.text = DLG_TEXT_Q[157];
			link.l1 = DLG_TEXT_Q[158];
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_again";
		break;
		case "PortRoyal_again":
			dialog.text = DLG_TEXT_Q[159];
			link.l1 = DLG_TEXT_Q[160];
			link.l1.go = "PortRoyal_6";
		break;
		//================================== Сантьяго ======================================
		case "Santiago":
			NextDiag.TempNode = "Santiago";
			dialog.text = DLG_TEXT_Q[161];
			link.l1 = DLG_TEXT_Q[162];
			link.l1.go = "exit_over";			
			link.l2 = DLG_TEXT_Q[163];
			link.l2.go = "Santiago_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Santiago_1":
			dialog.text = DLG_TEXT_Q[164];
			link.l1 = DLG_TEXT_Q[165];
			link.l1.go = "Santiago_2";
		break;
		case "Santiago_2":
			dialog.text = DLG_TEXT_Q[166];
			link.l1 = DLG_TEXT_Q[167];
			link.l1.go = "Santiago_3";
		break;
		case "Santiago_3":
			dialog.text = DLG_TEXT_Q[168];
			link.l1 = DLG_TEXT_Q[169];
			link.l1.go = "Santiago_4";
			link.l2 = DLG_TEXT_Q[170];
			link.l2.go = "All_disagree";
		break;
		case "Santiago_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[171] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";	
		break;
		case "Santiago_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (GetStrSmallRegister(NullCharacter.questions.(sTemp)) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = DLG_TEXT_Q[172];
				link.l1 = DLG_TEXT_Q[173];
				link.l1.go = "Santiago_ok";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[174];
				link.l1 = DLG_TEXT_Q[175];
				link.l1.go = "Santiago_6";
				link.l2 = DLG_TEXT_Q[176];
				link.l2.go = "Santiago_7";
			}
		break;
		case "Santiago_ok":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Cuba_Grot = true;
			pchar.GenQuestRandItem.Cuba_Grot.randitem1 = "pistol6";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "6");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
		break;
		case "Santiago_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = DLG_TEXT_Q[179] + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_7":
			dialog.text = DLG_TEXT_Q[180];
			link.l1 = DLG_TEXT_Q[181];
			link.l1.go = "exit";
			NextDiag.TempNode = "Santiago_again";
		break;
		case "Santiago_again":
			dialog.text = DLG_TEXT_Q[182];
			link.l1 = DLG_TEXT_Q[183];
			link.l1.go = "Santiago_6";
		break;
	}
}
