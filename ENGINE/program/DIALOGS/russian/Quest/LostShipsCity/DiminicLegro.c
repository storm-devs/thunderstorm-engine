#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\DiminicLegro.h"
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
					dialog.text = DLG_TEXT_LSC[0] + GetFullName(npchar) + DLG_TEXT_LSC[1];
					link.l1 = DLG_TEXT_LSC[2] + pchar.name + DLG_TEXT_LSC[3] + GetFullName(pchar) + DLG_TEXT_LSC[4];
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[5] + GetFullName(npchar) + DLG_TEXT_LSC[6];
					link.l1 = DLG_TEXT_LSC[7] + pchar.name + DLG_TEXT_LSC[8] + GetFullName(pchar) + DLG_TEXT_LSC[9];
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест отнести бутылочку вина тюремщику. дача квеста
				if (!CheckActiveQuest("TakeVineToPrisoner") && !CheckAttribute(pchar, "questTemp.LSC.LegroHelp"))
				{
					dialog.text = DLG_TEXT_LSC[10];
					link.l1 = DLG_TEXT_LSC[11];
					link.l1.go = "GiveVineBottle";
					break;
				}				
				dialog.text = DLG_TEXT_LSC[12];
				link.l1 = DLG_TEXT_LSC[13];
				link.l1.go = "SeekCitizen";
				link.l2 = DLG_TEXT_LSC[14];
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase(DLG_TEXT_LSC[15], 
					DLG_TEXT_LSC[16], DLG_TEXT_LSC[17]);
				link.l3.go = "rumours_LSC";
				//квест доставки вина тюремщику. после разговора с Бойлом
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toFackDominic")
				{
					link.l7 = DLG_TEXT_LSC[18];
					link.l7.go = "FackDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toArmoDominic")
				{
					link.l7 = DLG_TEXT_LSC[19];
					link.l7.go = "ArmoDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toKeyDominic")
				{
					link.l7 = DLG_TEXT_LSC[20];
					link.l7.go = "KeyDominic";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = DLG_TEXT_LSC[21];
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[22];
					link.l8.go = "SeekCrew";
				}
				link.l10 = DLG_TEXT_LSC[23];
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = DLG_TEXT_LSC[24];
			link.l1 = DLG_TEXT_LSC[25];
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = DLG_TEXT_LSC[26];
			link.l1 = DLG_TEXT_LSC[27];
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[28];
			link.l1 = DLG_TEXT_LSC[29];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[30];
			link.l1 = DLG_TEXT_LSC[31];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[32]+
				DLG_TEXT_LSC[33];
			link.l1 = DLG_TEXT_LSC[34];
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = DLG_TEXT_LSC[35];
			link.l1 = DLG_TEXT_LSC[36];
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = DLG_TEXT_LSC[37];
			link.l1 = DLG_TEXT_LSC[38];
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = DLG_TEXT_LSC[39];
			link.l1 = DLG_TEXT_LSC[40];
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = DLG_TEXT_LSC[41];
			link.l1 = DLG_TEXT_LSC[42];
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[43], DLG_TEXT_LSC[44], DLG_TEXT_LSC[45]);
			link.l1 = DLG_TEXT_LSC[46];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[47];
			link.l1 = DLG_TEXT_LSC[48];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[49], DLG_TEXT_LSC[50], DLG_TEXT_LSC[51]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[52], DLG_TEXT_LSC[53], DLG_TEXT_LSC[54]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[55], DLG_TEXT_LSC[56]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[57], DLG_TEXT_LSC[58], DLG_TEXT_LSC[59]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[60], DLG_TEXT_LSC[61]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[62], DLG_TEXT_LSC[63]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[64];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[65];
				Link.l1 = DLG_TEXT_LSC[66];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[67];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[68];
					link.l1 = DLG_TEXT_LSC[69];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[70];
					Link.l1 = DLG_TEXT_LSC[71];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[72];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[73];
					Link.l1 = DLG_TEXT_LSC[74];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[75];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[76];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[77];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[78], DLG_TEXT_LSC[79], DLG_TEXT_LSC[80]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[81], DLG_TEXT_LSC[82]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[83], DLG_TEXT_LSC[84], DLG_TEXT_LSC[85]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[86], DLG_TEXT_LSC[87]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[88], DLG_TEXT_LSC[89], DLG_TEXT_LSC[90]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[91] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[92] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[93], DLG_TEXT_LSC[94] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[95] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[96], DLG_TEXT_LSC[97], DLG_TEXT_LSC[98]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[99] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[100] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[101], DLG_TEXT_LSC[102] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[103], DLG_TEXT_LSC[104]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[105], DLG_TEXT_LSC[106], DLG_TEXT_LSC[107]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[108] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[109] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[110], DLG_TEXT_LSC[111] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[112] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[113], DLG_TEXT_LSC[114], DLG_TEXT_LSC[115]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[116] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[117] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[118], DLG_TEXT_LSC[119] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[120], DLG_TEXT_LSC[121]);
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[122];
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = DLG_TEXT_LSC[123];
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[124];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[125];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = DLG_TEXT_LSC[126];
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = DLG_TEXT_LSC[127];
				link.l5.go = "ansewer_5";
			}
			link.l10 = DLG_TEXT_LSC[128];
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = DLG_TEXT_LSC[129];
			link.l1 = DLG_TEXT_LSC[130];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[131];
			link.l1 = DLG_TEXT_LSC[132];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[133];
			link.l1 = DLG_TEXT_LSC[134];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[135];
			link.l1 = DLG_TEXT_LSC[136];
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = DLG_TEXT_LSC[137];
			link.l1 = DLG_TEXT_LSC[138];
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[139];
			link.l1 = DLG_TEXT_LSC[140];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = DLG_TEXT_LSC[141];
			link.l1 = DLG_TEXT_LSC[142];
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = DLG_TEXT_LSC[143];
			link.l1 = DLG_TEXT_LSC[144];
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = DLG_TEXT_LSC[145];
			link.l1 = DLG_TEXT_LSC[146];
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[147], 
				DLG_TEXT_LSC[148], 
				DLG_TEXT_LSC[149],
                DLG_TEXT_LSC[150], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[151], 
				DLG_TEXT_LSC[152],
                DLG_TEXT_LSC[153], 
				DLG_TEXT_LSC[154], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[155];
			link.l1 = DLG_TEXT_LSC[156];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[157];
			link.l1 = DLG_TEXT_LSC[158];
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[161];
			link.l1 = DLG_TEXT_LSC[162];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[163];
			link.l1 = DLG_TEXT_LSC[164];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[165];
			link.l1 = DLG_TEXT_LSC[166];
			link.l1.go = "SeekCrew_all";
		break;
		//отнести бутылку вина тюремщику
		case "GiveVineBottle":
			dialog.text = DLG_TEXT_LSC[167];
			link.l1 = DLG_TEXT_LSC[168];
			link.l1.go = "GiveVineBottle_1";
		break;
		case "GiveVineBottle_1":
			dialog.text = DLG_TEXT_LSC[169];
			link.l1 = DLG_TEXT_LSC[170];
			link.l1.go = "GiveVineBottle_not";
			link.l2 = DLG_TEXT_LSC[171];
			link.l2.go = "GiveVineBottle_2";
		break;
		case "GiveVineBottle_not":
			dialog.text = DLG_TEXT_LSC[172];
			link.l1 = DLG_TEXT_LSC[173];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "over";
			CloseQuestHeader("TakeVineToPrisoner");
		break;
		case "GiveVineBottle_2":
			dialog.text = DLG_TEXT_LSC[174];
			link.l1 = DLG_TEXT_LSC[175];			
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toTomasBoil";
			AddQuestRecord("TakeVineToPrisoner", "1");
		break;
		
		case "FackDominic":
			dialog.text = DLG_TEXT_LSC[176];
			link.l1 = DLG_TEXT_LSC[177];
			link.l1.go = "FackDominic_1";
		break;
		case "FackDominic_1":
			dialog.text = DLG_TEXT_LSC[178];
			link.l1 = DLG_TEXT_LSC[179];
			link.l1.go = "FackDominic_2";
		break;
		case "FackDominic_2":
			dialog.text = DLG_TEXT_LSC[180];
			link.l1 = DLG_TEXT_LSC[181];
			link.l1.go = "FackDominic_3";
		break;
		case "FackDominic_3":
			dialog.text = DLG_TEXT_LSC[182];
			link.l1 = DLG_TEXT_LSC[183];
			link.l1.go = "FackDominic_4";
			link.l2 = DLG_TEXT_LSC[184];
			link.l2.go = "GiveVineBottle_not";
		break;
		case "FackDominic_4":
			dialog.text = DLG_TEXT_LSC[185];
			link.l1 = DLG_TEXT_LSC[186];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toSecondToPrison";
			AddQuestRecord("TakeVineToPrisoner", "3");
		break;

		case "ArmoDominic":
			dialog.text = DLG_TEXT_LSC[187];
			link.l1 = DLG_TEXT_LSC[188];
			link.l1.go = "ArmoDominic_1";
		break;
		case "ArmoDominic_1":
			dialog.text = DLG_TEXT_LSC[189];
			link.l1 = DLG_TEXT_LSC[190];
			link.l1.go = "ArmoDominic_2";
		break;
		case "ArmoDominic_2":
			dialog.text = DLG_TEXT_LSC[191];
			link.l1 = DLG_TEXT_LSC[192];
			link.l1.go = "ArmoDominic_3";
		break;
		case "ArmoDominic_3":
			dialog.text = DLG_TEXT_LSC[193];
			link.l1 = DLG_TEXT_LSC[194];
			link.l1.go = "ArmoDominic_4";
		break;
		case "ArmoDominic_4":
			dialog.text = DLG_TEXT_LSC[195];
			link.l1 = DLG_TEXT_LSC[196];
			link.l1.go = "ArmoDominic_5";
		break;
		case "ArmoDominic_5":
			dialog.text = DLG_TEXT_LSC[197];
			link.l1 = DLG_TEXT_LSC[198];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "to3ToPrison";
			AddQuestRecord("TakeVineToPrisoner", "5");
		break;

		case "KeyDominic":
			dialog.text = DLG_TEXT_LSC[199];
			link.l1 = DLG_TEXT_LSC[200];
			link.l1.go = "KeyDominic_1";
		break;
		case "KeyDominic_1":
			dialog.text = DLG_TEXT_LSC[201];
			link.l1 = DLG_TEXT_LSC[202];
			link.l1.go = "KeyDominic_2";
		break;
		case "KeyDominic_2":
			dialog.text = DLG_TEXT_LSC[203];
			link.l1 = DLG_TEXT_LSC[204];
			link.l1.go = "KeyDominic_3";
		break;
		case "KeyDominic_3":
			dialog.text = DLG_TEXT_LSC[205];
			link.l1 = DLG_TEXT_LSC[206];
			link.l1.go = "exit";
			GiveItem2Character(pchar, "key1");
			pchar.questTemp.LSC.LegroHelp = "over";
			AddQuestRecord("TakeVineToPrisoner", "7");
			CloseQuestHeader("TakeVineToPrisoner");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
