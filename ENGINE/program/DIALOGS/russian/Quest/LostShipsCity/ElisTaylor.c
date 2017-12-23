#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\ElisTaylor.h"
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
					dialog.text = DLG_TEXT_LSC[0] + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + DLG_TEXT_LSC[1];
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[2] + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + DLG_TEXT_LSC[3];
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[4];
				link.l1 = DLG_TEXT_LSC[5];
				link.l1.go = "SeekCitizen";
				link.l2 = DLG_TEXT_LSC[6];
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase(DLG_TEXT_LSC[7], 
					DLG_TEXT_LSC[8], DLG_TEXT_LSC[9]);
				link.l3.go = "rumours_LSC";
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
				{
					link.l7 = DLG_TEXT_LSC[10];
					link.l7.go = "ELTHusb_begin";
				}	
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = DLG_TEXT_LSC[11];
					link.l7.go = "ELTHusb_toElis";
				}	
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElisGood")
				{
					link.l7 = DLG_TEXT_LSC[12];
					link.l7.go = "ELTHusb_good";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = DLG_TEXT_LSC[13];
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[14];
					link.l8.go = "SeekCrew";
				}
				link.l10 = DLG_TEXT_LSC[15];
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = DLG_TEXT_LSC[16];
			link.l1 = DLG_TEXT_LSC[17];
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[18];
			link.l1 = DLG_TEXT_LSC[19];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[20];
			link.l1 = DLG_TEXT_LSC[21];
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[22], DLG_TEXT_LSC[23], DLG_TEXT_LSC[24]);
			link.l1 = DLG_TEXT_LSC[25];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[26];
			link.l1 = DLG_TEXT_LSC[27];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[28], DLG_TEXT_LSC[29], DLG_TEXT_LSC[30]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[31], DLG_TEXT_LSC[32], DLG_TEXT_LSC[33]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[34], DLG_TEXT_LSC[35]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[36], DLG_TEXT_LSC[37], DLG_TEXT_LSC[38]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[39], DLG_TEXT_LSC[40]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[41], DLG_TEXT_LSC[42]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[43];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[44];
				Link.l1 = DLG_TEXT_LSC[45];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[46];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[47];
					link.l1 = DLG_TEXT_LSC[48];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[49];
					Link.l1 = DLG_TEXT_LSC[50];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[51];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[52];
					Link.l1 = DLG_TEXT_LSC[53];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[54];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[55];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[56];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[57], DLG_TEXT_LSC[58], DLG_TEXT_LSC[59]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[60], DLG_TEXT_LSC[61]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[62], DLG_TEXT_LSC[63], DLG_TEXT_LSC[64]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[65], DLG_TEXT_LSC[66]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[67], DLG_TEXT_LSC[68], DLG_TEXT_LSC[69]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[70] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[71] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[72], DLG_TEXT_LSC[73] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[74] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[75], DLG_TEXT_LSC[76], DLG_TEXT_LSC[77]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[78] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[79] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[80], DLG_TEXT_LSC[81] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[82], DLG_TEXT_LSC[83]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[84], DLG_TEXT_LSC[85], DLG_TEXT_LSC[86]);
						}
						else
						{
								dialog.text = LinkRandPhrase(DLG_TEXT_LSC[87] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[88] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[89], DLG_TEXT_LSC[90] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[91] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[92], DLG_TEXT_LSC[93], DLG_TEXT_LSC[94]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[95] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[96] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[97], DLG_TEXT_LSC[98] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[99], DLG_TEXT_LSC[100]);
					link.l1.go = "exit";
				}
			}
		break;		
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[101];
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[102];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[103];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = DLG_TEXT_LSC[104];
				link.l3.go = "ansewer_3";
			}
			link.l10 = DLG_TEXT_LSC[105];
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[106];
			link.l1 = DLG_TEXT_LSC[107];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[108];
			link.l1 = DLG_TEXT_LSC[109];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
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
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[114];
			link.l1 = DLG_TEXT_LSC[115];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[116], 
				DLG_TEXT_LSC[117], 
				DLG_TEXT_LSC[118],
                DLG_TEXT_LSC[119], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[120], 
				DLG_TEXT_LSC[121],
                DLG_TEXT_LSC[122], 
				DLG_TEXT_LSC[123], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[124];
			link.l1 = DLG_TEXT_LSC[125];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[126];
			link.l1 = DLG_TEXT_LSC[127];
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = DLG_TEXT_LSC[128];
			link.l1 = DLG_TEXT_LSC[129];
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.balls = true;
			AddQuestRecord("ISS_MainLine", "49");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = DLG_TEXT_LSC[130];
			link.l1 =DLG_TEXT_LSC[131];
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[132];
			link.l1 = DLG_TEXT_LSC[133];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[134];
			link.l1 = DLG_TEXT_LSC[135];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[136];
			link.l1 = DLG_TEXT_LSC[137];
			link.l1.go = "SeekCrew_all";
		break;
		//вызволение мужа
		case "ELTHusb_begin":
			dialog.text = DLG_TEXT_LSC[138];
			link.l1 = DLG_TEXT_LSC[139];
			link.l1.go = "ELTHusb_begin_1";
		break;
		case "ELTHusb_begin_1":
			dialog.text = DLG_TEXT_LSC[140];
			link.l1 = DLG_TEXT_LSC[141];
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = DLG_TEXT_LSC[142];
			link.l1 = DLG_TEXT_LSC[143];
			link.l1.go = "ELTHusb_begin_3";
		break;
		case "ELTHusb_begin_3":
			dialog.text = DLG_TEXT_LSC[144];
			link.l1 = DLG_TEXT_LSC[145];
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = DLG_TEXT_LSC[146];
			link.l2.go = "ELTHusb_begin_disagree";
		break;
		case "ELTHusb_begin_disagree":
			dialog.text = DLG_TEXT_LSC[147];
			link.l1 = DLG_TEXT_LSC[148];
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
		break;
		case "ELTHusb_begin_4":
			dialog.text = DLG_TEXT_LSC[149];
			link.l1 = DLG_TEXT_LSC[150];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "5");
			pchar.questTemp.LSC.ElisHusband = "seekFreeMotod";
			sld = characterFromId("MaximTailor");
			sld.dialog.currentnode = "DontRemember";
		break;

		case "ELTHusb_toElis":
			dialog.text = DLG_TEXT_LSC[151];
			link.l1 = DLG_TEXT_LSC[152];
			link.l1.go = "ELTHusb_toElis_1";
		break;
		case "ELTHusb_toElis_1":
			dialog.text = DLG_TEXT_LSC[153];
			link.l1 = DLG_TEXT_LSC[154];
			link.l1.go = "ELTHusb_toElis_2";
		break;
		case "ELTHusb_toElis_2":
			dialog.text = DLG_TEXT_LSC[155];
			link.l1 = DLG_TEXT_LSC[156];
			link.l1.go = "ELTHusb_toElis_3";
		break;
		case "ELTHusb_toElis_3":
			dialog.text = DLG_TEXT_LSC[157];
			link.l1 = DLG_TEXT_LSC[158];
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = DLG_TEXT_LSC[159];
			link.l2.go = "ELTHusb_begin_disagree";
		break;

		case "ELTHusb_good":
			dialog.text = DLG_TEXT_LSC[160];
			link.l1 = DLG_TEXT_LSC[161];
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = DLG_TEXT_LSC[162];
			link.l1 = DLG_TEXT_LSC[163];
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = DLG_TEXT_LSC[164];
			link.l1 = DLG_TEXT_LSC[165];
			link.l1.go = "ELTHusb_good_3";
			GiveItem2Character(pchar, "key1");
		break;
		case "ELTHusb_good_3":
			dialog.text = DLG_TEXT_LSC[166];
			link.l1 = DLG_TEXT_LSC[167];
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
			SetTimerFunction("LSC_ElisHusbandSet", 0, 0, 1);
		break;

	}
	NextDiag.PrevNode = NodeName;
}
