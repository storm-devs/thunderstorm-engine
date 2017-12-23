#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\LeaToors.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

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
					if (npchar.location == "PlutoStoreSmall") dialog.text = DLG_TEXT_LSC[0] + GetFullName(npchar) + ".";
					else dialog.text = DLG_TEXT_LSC[1] + GetFullName(npchar) + ".";					
					link.l1 = DLG_TEXT_LSC[2] + GetFullName(pchar) + DLG_TEXT_LSC[3];
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = DLG_TEXT_LSC[4] + GetFullName(npchar) + ".";
					else dialog.text = DLG_TEXT_LSC[5] + GetFullName(npchar) + ".";
					link.l1 = DLG_TEXT_LSC[6] + GetFullName(pchar) + DLG_TEXT_LSC[7];
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[8];
				link.l1 = DLG_TEXT_LSC[9];
				link.l1.go = "SeekCitizen";
				link.l2 = DLG_TEXT_LSC[10];
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase(DLG_TEXT_LSC[11], 
					DLG_TEXT_LSC[12], DLG_TEXT_LSC[13]);
				link.l3.go = "rumours_LSC";
				//квест со скелетом Декстера
				if (CheckActiveQuest("LSC_findDekster") && !CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
				{
					link.l4 = DLG_TEXT_LSC[14];
					link.l4.go = "LostDecster";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.grapes"))
				{
					link.l8 = DLG_TEXT_LSC[15];
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.grapes") && sti(npchar.quest.grapes))
				{
					link.l8 = DLG_TEXT_LSC[16];
					link.l8.go = "TakeGrapes";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[17];
					link.l8.go = "SeekCrew";
				}
				link.l10 = DLG_TEXT_LSC[18];
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = DLG_TEXT_LSC[19];
			link.l1 = DLG_TEXT_LSC[20];
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[21];
			link.l1 = DLG_TEXT_LSC[22];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[23];
			link.l1 = DLG_TEXT_LSC[24];
			link.l1.go = "exit";
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[25], DLG_TEXT_LSC[26], DLG_TEXT_LSC[27]);
			link.l1 = DLG_TEXT_LSC[28];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[29];
			link.l1 = DLG_TEXT_LSC[30];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[31], DLG_TEXT_LSC[32], DLG_TEXT_LSC[33]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[34], DLG_TEXT_LSC[35], DLG_TEXT_LSC[36]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[37], DLG_TEXT_LSC[38]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[39], DLG_TEXT_LSC[40], DLG_TEXT_LSC[41]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[42], DLG_TEXT_LSC[43]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[44], DLG_TEXT_LSC[45]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[46];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[47];
				Link.l1 = DLG_TEXT_LSC[48];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[49];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[50];
					link.l1 = DLG_TEXT_LSC[51];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[52];
					Link.l1 = DLG_TEXT_LSC[53];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[54];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[55];
					Link.l1 = DLG_TEXT_LSC[56];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[57];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[58];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[59];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[60], DLG_TEXT_LSC[61], DLG_TEXT_LSC[62]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[63], DLG_TEXT_LSC[64]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[65], DLG_TEXT_LSC[66], DLG_TEXT_LSC[67]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[68], DLG_TEXT_LSC[69]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[70], DLG_TEXT_LSC[71], DLG_TEXT_LSC[72]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[73] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[74] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[75], DLG_TEXT_LSC[76] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[77] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[78], DLG_TEXT_LSC[79], DLG_TEXT_LSC[80]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[81] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[82] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[83], DLG_TEXT_LSC[84] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[85], DLG_TEXT_LSC[86]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[87], DLG_TEXT_LSC[88], DLG_TEXT_LSC[89]);
						}
						else
						{
								dialog.text = LinkRandPhrase(DLG_TEXT_LSC[90] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[91] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[92], DLG_TEXT_LSC[93] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[94] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[95], DLG_TEXT_LSC[96], DLG_TEXT_LSC[97]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[98] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[99] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[100], DLG_TEXT_LSC[101] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[102], DLG_TEXT_LSC[103]);
					link.l1.go = "exit";
				}
			}
		break;	
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[104];
			if (!CheckAttribute(NextDiag, NodeName+".l1") && npchar.location == "PlutoStoreSmall")
			{
				link.l1 = DLG_TEXT_LSC[105];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = DLG_TEXT_LSC[106];
				link.l2.go = "ansewer_2";
			}
			link.l10 = DLG_TEXT_LSC[107];
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[108];
			link.l1 = DLG_TEXT_LSC[109];
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = DLG_TEXT_LSC[110];
			link.l1 = DLG_TEXT_LSC[111];
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[112];
			link.l1 = DLG_TEXT_LSC[113];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[114];
			link.l1 = DLG_TEXT_LSC[115];
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = DLG_TEXT_LSC[116];
			link.l1 = DLG_TEXT_LSC[117];
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[118], 
				DLG_TEXT_LSC[119], 
				DLG_TEXT_LSC[120],
                DLG_TEXT_LSC[121], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[122], 
				DLG_TEXT_LSC[123],
                DLG_TEXT_LSC[124], 
				DLG_TEXT_LSC[125], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[126];
			link.l1 = DLG_TEXT_LSC[127];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[128];
			link.l1 = DLG_TEXT_LSC[129];
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = DLG_TEXT_LSC[130];
			link.l1 = DLG_TEXT_LSC[131];
			link.l1.go = "exit";
			npchar.quest.grapes = true;
			AddQuestRecord("ISS_MainLine", "53");
		break;
		//проверка на соль
		case "TakeGrapes":
			dialog.text = DLG_TEXT_LSC[132];
            if (CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) >= 10)
            {				
				link.l1 = DLG_TEXT_LSC[133];
				link.l1.go = "TakeGrapes_yes";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[134];
				link.l1.go = "TakeGrapes_no";
			}
		break;
		case "TakeGrapes_no":
			dialog.text = DLG_TEXT_LSC[135];
			link.l1 = DLG_TEXT_LSC[136];
			link.l1.go = "exit";
		break;
		case "TakeGrapes_yes":
			dialog.text = DLG_TEXT_LSC[137];
			link.l1 = DLG_TEXT_LSC[138];
			link.l1.go = "TakeGrapes_1";
			TakeNItems(pchar, "Mineral10", -10);
		break;
		case "TakeGrapes_1":
			dialog.text = DLG_TEXT_LSC[139];
			link.l1 = DLG_TEXT_LSC[140];
			link.l1.go = "TakeGrapes_2";
		break;
		case "TakeGrapes_2":
			dialog.text = DLG_TEXT_LSC[141];
			link.l1 = DLG_TEXT_LSC[142];
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddQuestRecord("ISS_MainLine", "54");
			npchar.quest.grapes = false;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = DLG_TEXT_LSC[143];
			link.l1 = DLG_TEXT_LSC[144];
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[145];
			link.l1 = DLG_TEXT_LSC[146];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[147];
			link.l1 = DLG_TEXT_LSC[148];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[149];
			link.l1 = DLG_TEXT_LSC[150];
			link.l1.go = "SeekCrew_all";
		break;
		//квест со скелетом Лейтона Декстера
		case "LostDecster":
			dialog.text = DLG_TEXT_LSC[151];
			link.l1 = DLG_TEXT_LSC[152];
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = DLG_TEXT_LSC[153];
			link.l1 = DLG_TEXT_LSC[154];
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = DLG_TEXT_LSC[155];
			link.l1 = DLG_TEXT_LSC[156];
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = DLG_TEXT_LSC[157];
			link.l1 = DLG_TEXT_LSC[158];
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = DLG_TEXT_LSC[161];
			link.l1 = DLG_TEXT_LSC[162];
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = DLG_TEXT_LSC[163];
			link.l1 = DLG_TEXT_LSC[164];
			link.l1.go = "LostDecster_7";
		break;
		case "LostDecster_7":
			dialog.text = DLG_TEXT_LSC[165];
			link.l1 = DLG_TEXT_LSC[166];
			link.l1.go = "LostDecster_8";
		break;
		case "LostDecster_8":
			dialog.text = DLG_TEXT_LSC[167];
			link.l1 = DLG_TEXT_LSC[168];
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "toAdmiral";
			AddQuestRecord("LSC_findDekster", "3");	
		break;
	}
	NextDiag.PrevNode = NodeName;
}
