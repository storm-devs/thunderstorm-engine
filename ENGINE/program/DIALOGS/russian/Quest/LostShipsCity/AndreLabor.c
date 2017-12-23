#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\AndreLabor.h"
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
					link.l1 = DLG_TEXT_LSC[2] + GetFullName(pchar) + DLG_TEXT_LSC[3] + npchar.lastname + DLG_TEXT_LSC[4];
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = DLG_TEXT_LSC[5] + GetFullName(npchar) + ".";
					link.l1 = GetFullName(pchar) + DLG_TEXT_LSC[6] + npchar.lastname + DLG_TEXT_LSC[7];
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
				link.l4 = DLG_TEXT_LSC[14];
				link.l4.go = "exit";
				if (pchar.questTemp.LSC == "toAndreLabor")
				{
					link.l5 = DLG_TEXT_LSC[15];
					link.l5.go = "Tizer_1";
				}

			}
		break;
		case "FS_1":
			dialog.text = DLG_TEXT_LSC[16];
			link.l1 = DLG_TEXT_LSC[17];
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[18];
			link.l1 = DLG_TEXT_LSC[19];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[20]+
				DLG_TEXT_LSC[21];			
			link.l1 = DLG_TEXT_LSC[22];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[23];
			link.l1 = DLG_TEXT_LSC[24];
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = DLG_TEXT_LSC[25];
			link.l1 = DLG_TEXT_LSC[26];
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = DLG_TEXT_LSC[27];
			link.l1 = DLG_TEXT_LSC[28] + npchar + DLG_TEXT_LSC[29];
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение √√ в сундуках
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[30], DLG_TEXT_LSC[31], DLG_TEXT_LSC[32]);
			link.l1 = DLG_TEXT_LSC[33];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[34];
			link.l1 = DLG_TEXT_LSC[35];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[36], DLG_TEXT_LSC[37], DLG_TEXT_LSC[38]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[39], DLG_TEXT_LSC[40], DLG_TEXT_LSC[41]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[42], DLG_TEXT_LSC[43]);
				link.l1 = LinkRandPhrase(DLG_TEXT_LSC[44], DLG_TEXT_LSC[45], DLG_TEXT_LSC[46]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_LSC[47], DLG_TEXT_LSC[48]);
				link.l1 = RandPhraseSimple(DLG_TEXT_LSC[49], DLG_TEXT_LSC[50]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;


		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[51];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[52];
				Link.l1 = DLG_TEXT_LSC[53];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[54];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[55];
					link.l1 = DLG_TEXT_LSC[56];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[57];
					Link.l1 = DLG_TEXT_LSC[58];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[59];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[60];
					Link.l1 = DLG_TEXT_LSC[61];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[62];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[63];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[64];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[65], DLG_TEXT_LSC[66], DLG_TEXT_LSC[67]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[68], DLG_TEXT_LSC[69]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[70], DLG_TEXT_LSC[71], DLG_TEXT_LSC[72]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[73], DLG_TEXT_LSC[74]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[75], DLG_TEXT_LSC[76], DLG_TEXT_LSC[77]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[78] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[79] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[80], DLG_TEXT_LSC[81] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[82] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[83], DLG_TEXT_LSC[84], DLG_TEXT_LSC[85]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[86] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[87] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[88], DLG_TEXT_LSC[89] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[90], DLG_TEXT_LSC[91]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[92], DLG_TEXT_LSC[93], DLG_TEXT_LSC[94]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[95] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[96] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[97], DLG_TEXT_LSC[98] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[99] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[100], DLG_TEXT_LSC[101], DLG_TEXT_LSC[102]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[103] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[104] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[105], DLG_TEXT_LSC[106] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[107]+GetAddress_FormToNPC(NPChar)+".", DLG_TEXT_LSC[108]);
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[109];
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = DLG_TEXT_LSC[110];
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[111];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[112];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = DLG_TEXT_LSC[113];
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = DLG_TEXT_LSC[114];
				link.l4.go = "ansewer_4";
			}
			link.l10 = DLG_TEXT_LSC[115];
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = DLG_TEXT_LSC[116];
			link.l1 = DLG_TEXT_LSC[117];
			link.l1.go = "ansewer_5_1";
		break;
		case "ansewer_5_1":
			dialog.text = DLG_TEXT_LSC[118];
			link.l1 = DLG_TEXT_LSC[119];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[120];
			link.l1 = DLG_TEXT_LSC[121];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[122];
			link.l1 = DLG_TEXT_LSC[123];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[124];
			link.l1 = DLG_TEXT_LSC[125];
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[126];
			link.l1 = DLG_TEXT_LSC[127];
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = DLG_TEXT_LSC[128];
			link.l1 = DLG_TEXT_LSC[129];
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = DLG_TEXT_LSC[130];
			link.l1 = DLG_TEXT_LSC[131];
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4_1":
			dialog.text = DLG_TEXT_LSC[132];
			link.l1 = DLG_TEXT_LSC[133];
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = DLG_TEXT_LSC[134];
			link.l1 = DLG_TEXT_LSC[135];
			link.l1.go = "int_quests";
		break;
		//квестовые диалоги
		case "Tizer_1":
			dialog.text = DLG_TEXT_LSC[136];
			link.l1 = DLG_TEXT_LSC[137];
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = DLG_TEXT_LSC[138];
			link.l1 = DLG_TEXT_LSC[139];
			link.l1.go = "Tizer_3";
		break;
		case "Tizer_3":
			dialog.text = DLG_TEXT_LSC[140];
			link.l1 = DLG_TEXT_LSC[141];
			link.l1.go = "Tizer_4";
		break;
		case "Tizer_4":
			dialog.text = DLG_TEXT_LSC[142];
			link.l1 = DLG_TEXT_LSC[143];
			link.l1.go = "Tizer_5";
		break;
		case "Tizer_5":
			dialog.text = DLG_TEXT_LSC[144];
			link.l1 = DLG_TEXT_LSC[145];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "8");
			pchar.questTemp.LSC = "toProtector";
			pchar.quest.LSC_enterToProtector.win_condition.l1 = "location";
			pchar.quest.LSC_enterToProtector.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_enterToProtector.function = "LSC_enterToProtector";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
