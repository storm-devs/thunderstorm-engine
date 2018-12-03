#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\MaximTailor.h"
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
			dialog.text = DLG_TEXT_LSC[0];
			link.l1 = DLG_TEXT_LSC[1];
			link.l1.go = "SeekCitizen";
			link.l2 = DLG_TEXT_LSC[2];
			link.l2.go = "int_quests";
			link.l3 = LinkRandPhrase(DLG_TEXT_LSC[3], 
				DLG_TEXT_LSC[4], DLG_TEXT_LSC[5]);
			link.l3.go = "rumours_LSC";
			link.l10 = DLG_TEXT_LSC[6];
			link.l10.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//ищем человека
		case "SeekCitizen":
			dialog.text = DLG_TEXT_LSC[7];
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = DLG_TEXT_LSC[8];
				Link.l1 = DLG_TEXT_LSC[9];
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = DLG_TEXT_LSC[10];
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = DLG_TEXT_LSC[11];
					link.l1 = DLG_TEXT_LSC[12];
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[13];
					Link.l1 = DLG_TEXT_LSC[14];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[15];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + DLG_TEXT_LSC[16];
					Link.l1 = DLG_TEXT_LSC[17];
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = DLG_TEXT_LSC[18];
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = DLG_TEXT_LSC[19];
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = DLG_TEXT_LSC[20];
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
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[21], DLG_TEXT_LSC[22], DLG_TEXT_LSC[23]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[24], DLG_TEXT_LSC[25]);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_LSC[26], DLG_TEXT_LSC[27], DLG_TEXT_LSC[28]);
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[29], DLG_TEXT_LSC[30]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[31], DLG_TEXT_LSC[32], DLG_TEXT_LSC[33]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[34] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[35] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[36], DLG_TEXT_LSC[37] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[38] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[39], DLG_TEXT_LSC[40], DLG_TEXT_LSC[41]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[42] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[43] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[44], DLG_TEXT_LSC[45] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[46], DLG_TEXT_LSC[47]);
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
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[48], DLG_TEXT_LSC[49], DLG_TEXT_LSC[50]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[51] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[52] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[53], DLG_TEXT_LSC[54] + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[55] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[56], DLG_TEXT_LSC[57], DLG_TEXT_LSC[58]);
						}
						else
						{
							dialog.text = LinkRandPhrase(DLG_TEXT_LSC[59] + npchar.quest.seekIdx.where + ".", DLG_TEXT_LSC[60] + npchar.quest.seekIdx.where + DLG_TEXT_LSC[61], DLG_TEXT_LSC[62] + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple(DLG_TEXT_LSC[63], DLG_TEXT_LSC[64]);
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[65];
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[66];
				link.l1.go = "ansewer_1";
			}
			link.l10 = DLG_TEXT_LSC[67];
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[68];
			link.l1 = DLG_TEXT_LSC[69];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		//нерадивый муж Элис Тейлор
		case "InPrison":
			dialog.text = DLG_TEXT_LSC[70];	
			link.l1 = DLG_TEXT_LSC[71];
			link.l1.go = "InPrison_1";
		break;
		case "InPrison_1":
			dialog.text = DLG_TEXT_LSC[72];
			link.l1 = DLG_TEXT_LSC[73];
			link.l1.go = "InPrison_2";
		break;
		case "InPrison_2":
			dialog.text = DLG_TEXT_LSC[74];
			link.l1 = DLG_TEXT_LSC[75];
			link.l1.go = "InPrison_3";
		break;
		case "InPrison_3":
			dialog.text = DLG_TEXT_LSC[76];
			link.l1 = DLG_TEXT_LSC[77];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "2");
			pchar.questTemp.LSC.ElisHusband = "toElis";
			NextDiag.TempNode = "InPrison_wait";
		break;

		case "InPrison_wait":
			dialog.text = DLG_TEXT_LSC[78];
			link.l1 = DLG_TEXT_LSC[79];
			link.l1.go = "exit";
		break;

		case "DontRemember":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[80], 
				DLG_TEXT_LSC[81], 
				DLG_TEXT_LSC[82],
                DLG_TEXT_LSC[83], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[84], 
				DLG_TEXT_LSC[85],
                DLG_TEXT_LSC[86], 
				DLG_TEXT_LSC[87], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("DontRemember_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "DontRemember_1":
			dialog.text = DLG_TEXT_LSC[88];
			link.l1 = DLG_TEXT_LSC[89];
			link.l1.go = "DontRemember_2";
		break;
		case "DontRemember_2":
			dialog.text = DLG_TEXT_LSC[90];
			link.l1 = DLG_TEXT_LSC[91];
			link.l1.go = "DontRemember_3";
		break;
		case "DontRemember_3":
			dialog.text = DLG_TEXT_LSC[92];
			link.l1 = DLG_TEXT_LSC[93];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "6");
			pchar.questTemp.LSC.ElisHusband = "toAdmiral";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
