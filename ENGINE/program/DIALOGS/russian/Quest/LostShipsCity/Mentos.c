#include "TEXT\DIALOGS\Quest\LostShipsCity\Mentos.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";			
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[0] + GetFullName(npchar) + DLG_TEXT_LSC[1], 
						DLG_TEXT_LSC[2] + GetFullName(npchar) + DLG_TEXT_LSC[3],
						DLG_TEXT_LSC[4] + GetFullName(npchar) + DLG_TEXT_LSC[5]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[6] + GetFullName(pchar) + DLG_TEXT_LSC[7], DLG_TEXT_LSC[8] + GetFullName(pchar) + DLG_TEXT_LSC[9]);
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[10] + GetFullName(npchar) + DLG_TEXT_LSC[11], 
						DLG_TEXT_LSC[12] + GetFullName(npchar) + DLG_TEXT_LSC[13],
						DLG_TEXT_LSC[14] + GetFullName(npchar) + DLG_TEXT_LSC[15]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[16] + GetFullName(pchar) + DLG_TEXT_LSC[17], DLG_TEXT_LSC[18] + GetFullName(pchar) + DLG_TEXT_LSC[19]);
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_LSC[20], DLG_TEXT_LSC[21], DLG_TEXT_LSC[22]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[23], DLG_TEXT_LSC[24]);
				link.l1.go = "SeekCitizen";
				link.l2 = RandPhraseSimple(DLG_TEXT_LSC[25], DLG_TEXT_LSC[26]);
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.additional.powder") && sti(pchar.questTemp.LSC.additional.powder))
				{
					link.l8 = DLG_TEXT_LSC[27];
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && !CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = DLG_TEXT_LSC[28];
					link.l8.go = "SeekCrew";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = DLG_TEXT_LSC[29];
					link.l8.go = "SeekCrew2";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = DLG_TEXT_LSC[30];
					link.l8.go = "SeekCrew3";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = DLG_TEXT_LSC[31];
					link.l8.go = "SeekCrew4";
				}
				link.l10 = DLG_TEXT_LSC[32];
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[33], 
				DLG_TEXT_LSC[34], 
				DLG_TEXT_LSC[35])
			link.l1 = RandPhraseSimple(DLG_TEXT_LSC[36], DLG_TEXT_LSC[37]);
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[38], DLG_TEXT_LSC[39], DLG_TEXT_LSC[40]);
			link.l1 = DLG_TEXT_LSC[41];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[42];
			link.l1 = DLG_TEXT_LSC[43];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[44], DLG_TEXT_LSC[45], DLG_TEXT_LSC[46]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[47], DLG_TEXT_LSC[48], DLG_TEXT_LSC[49]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[50], DLG_TEXT_LSC[51]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[52], DLG_TEXT_LSC[53], DLG_TEXT_LSC[54]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[55], DLG_TEXT_LSC[56]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[57], DLG_TEXT_LSC[58]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[59];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[60];
				Link.l1 = DLG_TEXT_LSC[61];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[62];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[63];
					link.l1 = DLG_TEXT_LSC[64];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[65];
					Link.l1 = DLG_TEXT_LSC[66];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[67];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[68];
					Link.l1 = DLG_TEXT_LSC[69];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[70];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[71];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[72];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[73], DLG_TEXT_LSC[74], DLG_TEXT_LSC[75]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[76], DLG_TEXT_LSC[77]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[78], DLG_TEXT_LSC[79], DLG_TEXT_LSC[80]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[81], DLG_TEXT_LSC[82]);
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[83], DLG_TEXT_LSC[84], DLG_TEXT_LSC[85]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[86] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[87] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[88], DLG_TEXT_LSC[89] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[90] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[91], DLG_TEXT_LSC[92], DLG_TEXT_LSC[93]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[94] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[95] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[96], DLG_TEXT_LSC[97] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[98], DLG_TEXT_LSC[99]);
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")  
					{						
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[100], DLG_TEXT_LSC[101], DLG_TEXT_LSC[102]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[103] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[104] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[105], DLG_TEXT_LSC[106] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[107] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[108], DLG_TEXT_LSC[109], DLG_TEXT_LSC[110]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[111] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[112] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[113], DLG_TEXT_LSC[114] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[115], DLG_TEXT_LSC[116]);
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[117], DLG_TEXT_LSC[118], DLG_TEXT_LSC[119]);
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[120], DLG_TEXT_LSC[121], DLG_TEXT_LSC[122]);
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = LinkRandPhrase(DLG_TEXT_LSC[123], DLG_TEXT_LSC[124], DLG_TEXT_LSC[125]);
				link.l2.go = "ansewer_2";
			}
			link.l10 = RandPhraseSimple(DLG_TEXT_LSC[126], DLG_TEXT_LSC[127]);
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[128], 
				DLG_TEXT_LSC[129], 
				DLG_TEXT_LSC[130]);
			link.l1 = RandPhraseSimple(DLG_TEXT_LSC[131], DLG_TEXT_LSC[132]);
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[133], 
				DLG_TEXT_LSC[134], 
				DLG_TEXT_LSC[135]);
			link.l1 = RandPhraseSimple(DLG_TEXT_LSC[136], DLG_TEXT_LSC[137]);
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//диалог перед боем на Веласко
		case "OffNarval":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[138], DLG_TEXT_LSC[139], DLG_TEXT_LSC[140]);
			link.l1 = DLG_TEXT_LSC[141];
			link.l1.go = "exit";
		break;
		//диалог после боем на Веласко
		case "AffterFightN":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[142], DLG_TEXT_LSC[143], DLG_TEXT_LSC[144]);
			link.l1 = DLG_TEXT_LSC[145];
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[146], 
				DLG_TEXT_LSC[147], 
				DLG_TEXT_LSC[148],
                DLG_TEXT_LSC[149], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[150], 
				DLG_TEXT_LSC[151],
                DLG_TEXT_LSC[152], 
				DLG_TEXT_LSC[153], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[154];
			link.l1 = DLG_TEXT_LSC[155];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[156];
			link.l1 = DLG_TEXT_LSC[157];
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = DLG_TEXT_LSC[158];
			link.l1 = DLG_TEXT_LSC[159];
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = DLG_TEXT_LSC[160];
			link.l1 = DLG_TEXT_LSC[161];
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_WEAPON, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 200);
			AddQuestRecord("ISS_MainLine", "58");
			pchar.questTemp.LSC.additional.powder = false;
		break;
		//поиски команды на корвет
		case "SeekCrew":
			dialog.text = DLG_TEXT_LSC[162];
			link.l1 = DLG_TEXT_LSC[163];
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[164];
			link.l1 = DLG_TEXT_LSC[165];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[166];
			link.l1 = DLG_TEXT_LSC[167];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[168];
			link.l1 = DLG_TEXT_LSC[169];
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.LSC.crew.ment_6 = true; 
			npchar.quest.LSCofficer = true; 
			AddQuestRecord("ISS_MainLine", "61");
		break;

		case "SeekCrew2":
			dialog.text = DLG_TEXT_LSC[170];
			link.l1 = DLG_TEXT_LSC[171];
			link.l1.go = "exit";
		break;

		case "SeekCrew3":
			dialog.text = DLG_TEXT_LSC[172];
			link.l1 = DLG_TEXT_LSC[173];
			link.l1.go = "exit";
		break;

		case "SeekCrew4":
			dialog.text = DLG_TEXT_LSC[174];
			link.l1 = DLG_TEXT_LSC[175];
			link.l1.go = "SeekCrew4_1";
		break;
		case "SeekCrew4_1":
			dialog.text = DLG_TEXT_LSC[176];
			link.l1 = DLG_TEXT_LSC[177];
			link.l1.go = "SeekCrew4_2";
		break;
		case "SeekCrew4_2":
			dialog.text = DLG_TEXT_LSC[178];
			link.l1 = DLG_TEXT_LSC[179];
			link.l1.go = "SeekCrew4_3";
		break;
		case "SeekCrew4_3":
			dialog.text = DLG_TEXT_LSC[180];
			link.l1 = DLG_TEXT_LSC[181];
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.quest.LSCofficer = true; 
			AddQuestRecord("ISS_MainLine", "68");
		break;
		//финальный разговор мента_6 перед посадкой на корвет
		case "MentOffIsLife":
			dialog.text = DLG_TEXT_LSC[182];
			link.l1 = DLG_TEXT_LSC[183];
			link.l1.go = "MentOffIsLife_1";
		break;
		case "MentOffIsLife_1":
			Npchar.quest.OfficerPrice = (rand(4)+1)*1000;
			dialog.text = DLG_TEXT_LSC[184];
			link.l1 = DLG_TEXT_LSC[185];
			link.l1.go = "MentOffIsLife_2";
		break;
		case "MentOffIsLife_2":
			dialog.text = DLG_TEXT_LSC[186];
			link.l1 = DLG_TEXT_LSC[187];
			link.l1.go = "MentOffIsLife_3";
		break;
		case "MentOffIsLife_3":
			dialog.text = DLG_TEXT_LSC[188];
			link.l1 = DLG_TEXT_LSC[189];
			link.l1.go = "MentOffIsLife_4";
		break;
		case "MentOffIsLife_4":
			dialog.text = DLG_TEXT_LSC[190];
			link.l1 = DLG_TEXT_LSC[191];
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
			AddQuestRecord("ISS_MainLine", "66");
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "Gr_questOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
	}
	NextDiag.PrevNode = NodeName;
}
