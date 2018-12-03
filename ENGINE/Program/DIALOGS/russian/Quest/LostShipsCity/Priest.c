#include "TEXT\DIALOGS\Quest\LostShipsCity\Priest.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

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
					dialog.text = DLG_TEXT_LSC[0];
					link.l1 = DLG_TEXT_LSC[1] + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.text = DLG_TEXT_LSC[2];
					link.l1 = DLG_TEXT_LSC[3] + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[4];
    			link.l1 = RandPhraseSimple(DLG_TEXT_LSC[5], DLG_TEXT_LSC[6]);
    			link.l1.go = "donation";
				link.l2 = DLG_TEXT_LSC[7];
				link.l2.go = "SeekCitizen";
				link.l3 = DLG_TEXT_LSC[8];
				link.l3.go = "int_quests";
				квесты
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l4 = DLG_TEXT_LSC[9];
					link.l4.go = "askCandles";
				}
				if (CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek" && CheckCharacterItem(pchar, "mineral3"))
				{
					link.l4 = DLG_TEXT_LSC[10];
					link.l4.go = "takeCandles";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l8 = DLG_TEXT_LSC[11];
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek")
				{
					link.l8 = DLG_TEXT_LSC[12];
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "found")
				{
					link.l8 = DLG_TEXT_LSC[13];
					link.l8.go = "FSeekGoods";
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

		case "FT_1":
			dialog.text = DLG_TEXT_LSC[16];
			Link.l1 = DLG_TEXT_LSC[17];
			Link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[18];
			link.l1 = DLG_TEXT_LSC[19];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[20];
			link.l1 = DLG_TEXT_LSC[21];
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = DLG_TEXT_LSC[22]+
				DLG_TEXT_LSC[23];
			link.l1 = DLG_TEXT_LSC[24];
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = DLG_TEXT_LSC[25];
			link.l1 = DLG_TEXT_LSC[26];
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
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[27], DLG_TEXT_LSC[28], DLG_TEXT_LSC[29]);
			link.l1 = DLG_TEXT_LSC[30];
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = DLG_TEXT_LSC[31];
			link.l1 = DLG_TEXT_LSC[32];
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_LSC[33], DLG_TEXT_LSC[34], DLG_TEXT_LSC[35]);
			link.l1 = LinkRandPhrase(DLG_TEXT_LSC[36], DLG_TEXT_LSC[37], DLG_TEXT_LSC[38]);
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[39];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[40];
				Link.l1 = DLG_TEXT_LSC[41];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[42];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[43];
					link.l1 = DLG_TEXT_LSC[44];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[45];
					Link.l1 = DLG_TEXT_LSC[46];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[47];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[48];
					Link.l1 = DLG_TEXT_LSC[49];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[50];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[51];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[52];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[53], DLG_TEXT_LSC[54], DLG_TEXT_LSC[55]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[56], DLG_TEXT_LSC[57]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[58], DLG_TEXT_LSC[59], DLG_TEXT_LSC[60]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[61], DLG_TEXT_LSC[62]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[63], DLG_TEXT_LSC[64], DLG_TEXT_LSC[65]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[66] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[67] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[68], DLG_TEXT_LSC[69] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[70] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[71], DLG_TEXT_LSC[72], DLG_TEXT_LSC[73]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[74] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[75] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[76], DLG_TEXT_LSC[77] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[78], DLG_TEXT_LSC[79]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[80], DLG_TEXT_LSC[81], DLG_TEXT_LSC[82]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[83] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[84] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[85], DLG_TEXT_LSC[86] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[87] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[88], DLG_TEXT_LSC[89], DLG_TEXT_LSC[90]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[91] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[92] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[93], DLG_TEXT_LSC[94] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[95], DLG_TEXT_LSC[96]);
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[97];
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[98];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[99];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = DLG_TEXT_LSC[100];
				link.l3.go = "ansewer_3";
			}
			link.l10 = DLG_TEXT_LSC[101];
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[102];
			link.l1 = DLG_TEXT_LSC[103];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[104];
			link.l1 = DLG_TEXT_LSC[105];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[106];
			link.l1 = DLG_TEXT_LSC[107];
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[108];
			link.l1 = DLG_TEXT_LSC[109];
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = DLG_TEXT_LSC[110];
			link.l1 = DLG_TEXT_LSC[111];
			link.l1.go = "int_quests";
		break;
		//Исповедь
		case "donation":
			dialog.Text = DLG_TEXT_LSC[112];
			Link.l1 = DLG_TEXT_LSC[113];
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = DLG_TEXT_LSC[114];
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = DLG_TEXT_LSC[115];
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = DLG_TEXT_LSC[116];
				Link.l4.go = "donation paid_5000";
			}
		break;

		case "No donation":
			dialog.Text = DLG_TEXT_LSC[117];
			Link.l1 = DLG_TEXT_LSC[118];
			Link.l1.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = DLG_TEXT_LSC[119];
			Link.l1 = DLG_TEXT_LSC[120];
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = DLG_TEXT_LSC[121];
			Link.l1 = DLG_TEXT_LSC[122];
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = DLG_TEXT_LSC[123];
			Link.l1 = DLG_TEXT_LSC[124];
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		//достать свечки
		case "askCandles":
			dialog.text = DLG_TEXT_LSC[125];
			link.l1 = DLG_TEXT_LSC[126];
			link.l1.go = "askCandles_1";
		break;
		case "askCandles_1":
			dialog.text = DLG_TEXT_LSC[127];
			link.l1 = DLG_TEXT_LSC[128];
			link.l1.go = "askCandles_2";
		break;
		case "askCandles_2":
			dialog.text = DLG_TEXT_LSC[129];
			link.l1 = DLG_TEXT_LSC[130];
			link.l1.go = "exit";
			npchar.quest.takeCandles = "seek";
			npchar.quest.takeCandles.Qty = 0; //кол-во свечей
			AddQuestRecord("ISS_takeCandles", "1");
		break;

		case "takeCandles":
			iTemp = GetCharacterItem(pchar, "mineral3");
			npchar.quest.takeCandles.Qty = sti(npchar.quest.takeCandles.Qty) + iTemp;
			DeleteAttribute(pchar, "items.mineral3");
			if (sti(npchar.quest.takeCandles.Qty) < 400)
			{
				dialog.text = DLG_TEXT_LSC[131] + FindRussianQtyString(iTemp) + DLG_TEXT_LSC[132] + FindRussianQtyString(sti(npchar.quest.takeCandles.Qty)) + DLG_TEXT_LSC[133] + FindRussianQtyString(400 - sti(npchar.quest.takeCandles.Qty)) + ".";
				link.l1 = DLG_TEXT_LSC[134];
				link.l1.go = "exit";
				AddQuestRecord("ISS_takeCandles", "2");
				AddQuestUserData("ISS_takeCandles", "iQty", 400 - sti(npchar.quest.takeCandles.Qty));
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[135];
				link.l1 = DLG_TEXT_LSC[136];
				link.l1.go = "takeCandles_ok";
			}
		break;
		case "takeCandles_ok":
			dialog.text = DLG_TEXT_LSC[137];
			link.l1 = DLG_TEXT_LSC[138];
			link.l1.go = "exit";
			bDisableFastReload = false;
			npchar.quest.takeCandles = "found";
			AddQuestRecord("ISS_takeCandles", "3");
			CloseQuestHeader("ISS_takeCandles");
		break;
		//поиск товаров на корвет не принеся свечи
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[139], 
				DLG_TEXT_LSC[140], 
				DLG_TEXT_LSC[141],
                DLG_TEXT_LSC[142], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[143], 
				DLG_TEXT_LSC[144],
                DLG_TEXT_LSC[145], 
				DLG_TEXT_LSC[146], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[147];
			link.l1 = DLG_TEXT_LSC[148];
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = DLG_TEXT_LSC[149];
			link.l1 = DLG_TEXT_LSC[150];
			link.l1.go = "askCandles";
		break;
		//поиск товаров на корвет не принеся свечи
		case "FSeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[151], 
				DLG_TEXT_LSC[152], 
				DLG_TEXT_LSC[153],
                DLG_TEXT_LSC[154], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[155], 
				DLG_TEXT_LSC[156],
                DLG_TEXT_LSC[157], 
				DLG_TEXT_LSC[158], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FSeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FSeekGoods_1":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "FSeekGoods_2";
		break;
		case "FSeekGoods_2":
			dialog.text = DLG_TEXT_LSC[161];
			link.l1 = DLG_TEXT_LSC[162];
			link.l1.go = "FSeekGoods_3";
		break;
		case "FSeekGoods_3":
			dialog.text = DLG_TEXT_LSC[163];
			link.l1 = DLG_TEXT_LSC[164];
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 50);
			AddQuestRecord("ISS_MainLine", "47");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[165], 
				DLG_TEXT_LSC[166], 
				DLG_TEXT_LSC[167],
                DLG_TEXT_LSC[168], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[169], 
				DLG_TEXT_LSC[170],
                DLG_TEXT_LSC[171], 
				DLG_TEXT_LSC[172], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[173];
			link.l1 = DLG_TEXT_LSC[174];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[175];
			link.l1 = DLG_TEXT_LSC[176];
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
