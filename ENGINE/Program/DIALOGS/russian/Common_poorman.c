#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Common_poorman.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Poorman\" + NPChar.City + "_Poorman.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0], 
						DLG_TEXT_BASE[1], 
						DLG_TEXT_BASE[2]);
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]);
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг 
				//зачарованный город -->
				if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
				{
					dialog.text = DLG_TEXT_BASE[6];
					link.l1 = DLG_TEXT_BASE[7];
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
				{
					dialog.text = DLG_TEXT_BASE[8];
					link.l1 = DLG_TEXT_BASE[9];
					link.l1.go = "exit";
					break;
				}
				//<-- зачарованный город 
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[10] + GetFullName(npchar) + DLG_TEXT_BASE[11], 
					DLG_TEXT_BASE[12] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[13] + GetFullName(npchar) + ".", 
					DLG_TEXT_BASE[14] + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + DLG_TEXT_BASE[15]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]);
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}			
			else
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[18], 
						DLG_TEXT_BASE[19], 
						DLG_TEXT_BASE[20]);
					link.l1 = LinkRandPhrase(DLG_TEXT_BASE[21], DLG_TEXT_BASE[22], DLG_TEXT_BASE[23]);
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[24], 
					DLG_TEXT_BASE[25], 
					DLG_TEXT_BASE[26],
					DLG_TEXT_BASE[27], "block", 1, npchar, Dialog.CurrentNode);
				//разговарием с нищими о наезде
				if (pchar.questTemp.LSC == "SignOnPoorMurder" || pchar.questTemp.LSC == "PoorIsGood")
				{
					if (CheckAttribute(pchar, "questTemp.LSC.qtyTalk.headPoormanId") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
					{
						link.l1 = DLG_TEXT_BASE[28];
						link.l1.go = "PoorHeadMan"; 
						npchar.quest.talk = true; //больше не говорить
						break;
					}
					if (!CheckAttribute(npchar, "quest.talk"))
					{
						if (!CheckAttribute(pchar, "questTemp.LSC.qtyTalk")) pchar.questTemp.LSC.qtyTalk = 0;
						pchar.questTemp.LSC.qtyTalk = sti(pchar.questTemp.LSC.qtyTalk) + 1; //инкремент на базары по душам
						if (sti(pchar.questTemp.LSC.qtyTalk) > 4) pchar.questTemp.LSC.qtyTalk = 4;
						switch (pchar.questTemp.LSC.qtyTalk)
						{
						case "1":
							link.l1 = DLG_TEXT_BASE[29];
							npchar.quest.talk = true; //больше не говорить
							break;
						case "2":
							link.l1 = DLG_TEXT_BASE[30];
							npchar.quest.talk = true; //больше не говорить
							break;
						case "3":
							link.l1 = DLG_TEXT_BASE[31];
							npchar.quest.talk = true; //больше не говорить
							break;
						case "4":
							link.l1 = DLG_TEXT_BASE[32];
							break;
						}
						link.l1.go = "GoodTalk_" + pchar.questTemp.LSC.qtyTalk;
						break;
					}
				}
				//----------------------------------------------------------------
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[33], 
					DLG_TEXT_BASE[34],
					DLG_TEXT_BASE[35], 
					DLG_TEXT_BASE[36], npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38]);
				link.l2.go = "Whants";
				link.l3 = LinkRandPhrase(DLG_TEXT_BASE[39], 
					DLG_TEXT_BASE[40], DLG_TEXT_BASE[41]);
				link.l3.go = "rumours_poor";
				// --------------- линейка ГПК ---------------
				//нашел письмо в сундуке Виллемстада
				if (pchar.questTemp.LSC == "CanFoundStuvesantKey" && CheckCharacterItem(pchar, "letter_LSC") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = DLG_TEXT_BASE[42];
					link.l1.go = "FoundLetter";
				}
				//базар о том, что нашел причину заказа на нищих
				if (pchar.questTemp.LSC == "readyGoLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = DLG_TEXT_BASE[43];
					link.l1.go = "GoLSC";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[44], 
				DLG_TEXT_BASE[45]);
			link.l1 = DLG_TEXT_BASE[46];
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase(DLG_TEXT_BASE[47] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[48],
					DLG_TEXT_BASE[49] + GetAddress_Form(NPChar) +  DLG_TEXT_BASE[50]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[51], DLG_TEXT_BASE[52]);
				link.l1.go = "exit";
				Link.l2 = DLG_TEXT_BASE[53];
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase(DLG_TEXT_BASE[54], DLG_TEXT_BASE[55] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[56]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = DLG_TEXT_BASE[59] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[60];
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = DLG_TEXT_BASE[61];
				link.l1 = DLG_TEXT_BASE[62];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = DLG_TEXT_BASE[63] + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + DLG_TEXT_BASE[64];
				link.l1 = DLG_TEXT_BASE[65];
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100 && iTemp <= 1000)
			{
				dialog.text = DLG_TEXT_BASE[66] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[67];
				link.l1 = DLG_TEXT_BASE[68];
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = DLG_TEXT_BASE[69] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[70];
				link.l1 = DLG_TEXT_BASE[71];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 5000 && iTemp <= 50000)
			{
				dialog.text = DLG_TEXT_BASE[72] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[73];
				link.l1 = DLG_TEXT_BASE[74];
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 50000 && iTemp <= 100000)
			{
				dialog.text = DLG_TEXT_BASE[75] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[76];
				link.l1 = DLG_TEXT_BASE[77];
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100000)
			{
				dialog.text = DLG_TEXT_BASE[78] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[79] + FindRussianMoneyString(iTemp) + DLG_TEXT_BASE[80];
				link.l1 = DLG_TEXT_BASE[81];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
		break;
		//линейка ГПК, разговоры по душам с нищими после заказа 
		case "GoodTalk_1":
			dialog.text = DLG_TEXT_BASE[82];
			link.l1 = DLG_TEXT_BASE[83];
			link.l1.go = "GoodTalk_1_1";
		break;
		case "GoodTalk_1_1":
			dialog.text = DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "GoodTalk_1_2";
		break;
		case "GoodTalk_1_2":
			dialog.text = DLG_TEXT_BASE[86];
			link.l1 = DLG_TEXT_BASE[87];
			link.l1.go = "GoodTalk_1_3";
		break;
		case "GoodTalk_1_3":
			dialog.text = DLG_TEXT_BASE[88];
			link.l1 = DLG_TEXT_BASE[89];
			link.l1.go = "GoodTalk_1_4";
		break;
		case "GoodTalk_1_4":
			dialog.text = DLG_TEXT_BASE[90];
			link.l1 = DLG_TEXT_BASE[91];
			link.l1.go = "exit";
		break;

		case "GoodTalk_2":
			dialog.text = DLG_TEXT_BASE[92];
			link.l1 = DLG_TEXT_BASE[93];
			link.l1.go = "GoodTalk_2_1";
		break;
		case "GoodTalk_2_1":
			dialog.text = DLG_TEXT_BASE[94];
			link.l1 = DLG_TEXT_BASE[95];
			link.l1.go = "GoodTalk_2_2";
		break;
		case "GoodTalk_2_2":
			dialog.text = DLG_TEXT_BASE[96];
			link.l1 = DLG_TEXT_BASE[97];
			link.l1.go = "GoodTalk_2_3";
		break;
		case "GoodTalk_2_3":
			dialog.text = DLG_TEXT_BASE[98];
			link.l1 = DLG_TEXT_BASE[99];
			link.l1.go = "GoodTalk_2_4";
		break;
		case "GoodTalk_2_4":
			dialog.text = DLG_TEXT_BASE[100];
			link.l1 = DLG_TEXT_BASE[101];
			link.l1.go = "GoodTalk_2_5";
		break;
		case "GoodTalk_2_5":
			dialog.text = DLG_TEXT_BASE[102];
			link.l1 = DLG_TEXT_BASE[103];
			link.l1.go = "exit";
		break;

		case "GoodTalk_3":
			dialog.text = DLG_TEXT_BASE[104];
			link.l1 = DLG_TEXT_BASE[105];
			link.l1.go = "GoodTalk_3_1";
		break;
		case "GoodTalk_3_1":
			dialog.text = DLG_TEXT_BASE[106];
			link.l1 = DLG_TEXT_BASE[107];
			link.l1.go = "GoodTalk_3_2";
		break;
		case "GoodTalk_3_2":
			dialog.text = DLG_TEXT_BASE[108];
			link.l1 = DLG_TEXT_BASE[109];
			link.l1.go = "GoodTalk_3_3";
		break;
		case "GoodTalk_3_3":
			dialog.text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111];
			link.l1.go = "GoodTalk_3_4";
		break;
		case "GoodTalk_3_4":
			pchar.questTemp.LSC.qtyTalk.headPoormanId = GetPoorHeadManId(npchar);
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = DLG_TEXT_BASE[112] + GetFullName(sld) + DLG_TEXT_BASE[113] + XI_ConvertString("Colony" + sld.city + "Dat") + ".";
			link.l1 = DLG_TEXT_BASE[114];
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "3");
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(sld));
		break;

		case "GoodTalk_4":
			dialog.text = DLG_TEXT_BASE[115];
			link.l1 = DLG_TEXT_BASE[116];
			link.l1.go = "GoodTalk_4_1";
		break;
		case "GoodTalk_4_1":
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = DLG_TEXT_BASE[117] + XI_ConvertString("Colony" + sld.city + "Acc") + DLG_TEXT_BASE[118] + GetFullName(sld) + DLG_TEXT_BASE[119];
			link.l1 = DLG_TEXT_BASE[120];
			link.l1.go = "exit";
		break;
		//основной бродяга
		case "PoorHeadMan":
			dialog.text = DLG_TEXT_BASE[121] + GetFullName(pchar) + DLG_TEXT_BASE[122];
			link.l1 = DLG_TEXT_BASE[123];
			link.l1.go = "PoorHeadMan_1";
		break;
		case "PoorHeadMan_1":
			dialog.text = DLG_TEXT_BASE[124];
			link.l1 = DLG_TEXT_BASE[125];
			link.l1.go = "PoorHeadMan_2";
		break;
		case "PoorHeadMan_2":
			dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
			link.l1.go = "PoorHeadMan_3";
		break;
		case "PoorHeadMan_3":
			dialog.text = DLG_TEXT_BASE[128];
			link.l1 = DLG_TEXT_BASE[129];
			link.l1.go = "PoorHeadMan_4";
		break;
		case "PoorHeadMan_4":
			dialog.text = DLG_TEXT_BASE[130]+
				DLG_TEXT_BASE[131];
			link.l1 = DLG_TEXT_BASE[132];
			link.l1.go = "PoorHeadMan_5";
		break;
		case "PoorHeadMan_5":
			dialog.text = DLG_TEXT_BASE[133]+
				DLG_TEXT_BASE[134];
			link.l1 = DLG_TEXT_BASE[135];
			link.l1.go = "PoorHeadMan_6";
		break;
		case "PoorHeadMan_6":
			dialog.text = DLG_TEXT_BASE[136]+
				DLG_TEXT_BASE[137];
			link.l1 = DLG_TEXT_BASE[138];
			link.l1.go = "PoorHeadMan_7";
		break;
		case "PoorHeadMan_7":
			dialog.text = DLG_TEXT_BASE[139];
			link.l1 = DLG_TEXT_BASE[140];
			link.l1.go = "PoorHeadMan_8";
		break;
		case "PoorHeadMan_8":
			dialog.text = DLG_TEXT_BASE[141];
			link.l1 = DLG_TEXT_BASE[142];
			link.l1.go = "PoorHeadMan_9";
		break;
		case "PoorHeadMan_9":
			dialog.text = DLG_TEXT_BASE[143];
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toVillemstadResidence";
			AddQuestRecord("ISS_PoorsMurder", "4");
			//сработает прерывание, чтобы показать геймеру, где нужный сундук
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1 = "locator";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.location = "Villemstad_TownhallRoom";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator_group = "box";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator = "private2";
			pchar.quest.LSC_enterStuvesantBox.function = "LSC_enterStuvesantBox";
		break;
		//базар с основным после нахождения письма
		case "FoundLetter":
			dialog.text = DLG_TEXT_BASE[145];
			link.l1 = DLG_TEXT_BASE[146];
			link.l1.go = "FoundLetter_1";
		break;
		case "FoundLetter_1":
			dialog.text = DLG_TEXT_BASE[147];
			link.l1 = DLG_TEXT_BASE[148];
			link.l1.go = "FoundLetter_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "FoundLetter_2":
			dialog.text = DLG_TEXT_BASE[149];
			link.l1 = DLG_TEXT_BASE[150];
			link.l1.go = "FoundLetter_3";
		break;
		case "FoundLetter_3":
			dialog.text = DLG_TEXT_BASE[151];
			link.l1 = DLG_TEXT_BASE[152];
			link.l1.go = "FoundLetter_4";
		break;
		case "FoundLetter_4":
			dialog.text = DLG_TEXT_BASE[153];
			link.l1 = DLG_TEXT_BASE[154];
			link.l1.go = "FoundLetter_5";
		break;
		case "FoundLetter_5":
			dialog.text = DLG_TEXT_BASE[155];
			link.l1 = DLG_TEXT_BASE[156];
			link.l1.go = "FoundLetter_6";
		break;
		case "FoundLetter_6":
			dialog.text = DLG_TEXT_BASE[157];
			link.l1 = DLG_TEXT_BASE[158];
			link.l1.go = "FoundLetter_7";
		break;
		case "FoundLetter_7":
			dialog.text = DLG_TEXT_BASE[159];
			link.l1 = DLG_TEXT_BASE[160];
			link.l1.go = "FoundLetter_8";
		break;
		case "FoundLetter_8":
			dialog.text = DLG_TEXT_BASE[161];
			link.l1 = DLG_TEXT_BASE[162];
			link.l1.go = "FoundLetter_9";
		break;
		case "FoundLetter_9":
			dialog.text = DLG_TEXT_BASE[163];
			link.l1 = DLG_TEXT_BASE[164];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTalkStuvesant";
			pchar.questTemp.LSC.poorName = GetFullName(npchar));
			AddQuestRecord("ISS_PoorsMurder", "7");
			AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
			//снимаем прерывание на завал нищих, деньги уже не получить
			pchar.quest.ISS_Murder1.over = "yes";
			pchar.quest.ISS_Murder2.over = "yes";
			pchar.quest.ISS_Murder3.over = "yes";
			pchar.quest.ISS_Murder4.over = "yes";
			pchar.quest.ISS_Murder5.over = "yes";
			pchar.quest.ISS_Murder6.over = "yes";
			pchar.quest.ISS_Murder7.over = "yes";
			pchar.quest.ISS_Murder8.over = "yes";
			pchar.quest.ISS_Murder9.over = "yes";
			pchar.quest.ISS_Murder10.over = "yes";
			pchar.quest.ISS_Murder11.over = "yes";
			pchar.quest.ISS_Murder12.over = "yes";
			pchar.quest.ISS_Murder13.over = "yes";
			pchar.quest.ISS_Murder14.over = "yes";
			pchar.quest.ISS_Murder15.over = "yes";
			pchar.quest.ISS_Murder16.over = "yes";
			pchar.quest.ISS_Murder17.over = "yes";
		break;
		//базар с основным после завала Оливера Траста
		case "GoLSC":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[165], 
				DLG_TEXT_BASE[166], 
				DLG_TEXT_BASE[167],
                DLG_TEXT_BASE[168], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[169], 
				DLG_TEXT_BASE[170],
                DLG_TEXT_BASE[171], 
				DLG_TEXT_BASE[172], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GoLSC_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "GoLSC_1":
			dialog.text = DLG_TEXT_BASE[173];
			link.l1 = DLG_TEXT_BASE[174];
			link.l1.go = "GoLSC_2";
		break;
		case "GoLSC_2":
			dialog.text = DLG_TEXT_BASE[175];
			link.l1 = DLG_TEXT_BASE[176];
			link.l1.go = "GoLSC_3";
		break;
		case "GoLSC_3":
			dialog.text = DLG_TEXT_BASE[177];
			link.l1 = DLG_TEXT_BASE[178];
			link.l1.go = "GoLSC_4";
		break;
		case "GoLSC_4":
			dialog.text = DLG_TEXT_BASE[179];
			link.l1 = DLG_TEXT_BASE[180];
			link.l1.go = "GoLSC_5";
		break;
		case "GoLSC_5":
			dialog.text = DLG_TEXT_BASE[181];
			link.l1 = DLG_TEXT_BASE[182];
			link.l1.go = "GoLSC_6";
		break;
		case "GoLSC_6":
			dialog.text = DLG_TEXT_BASE[183];
			link.l1 = DLG_TEXT_BASE[184];
			link.l1.go = "exit";
			ChangeItemName("keyQuestLSC", "itmname_keyQuestLSC_Tizer");
			ChangeItemDescribe("keyQuestLSC", "itmdescr_keyQuestLSC_Tizer");
			sld = ItemsFromID("keyQuestLSC");
			DeleteAttribute(sld, "shown");
			GiveItem2Character(pchar, "keyQuestLSC");			
		break;
	}
}

string GetPoorHeadManId(ref NPChar)
{
    ref ch;
	int n;
    string storeArray[30];	locations[n].private9.key = "key3";
	locations[n].private9.items.jewelry1 = 30;
    int howStore = 0;
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_poorman.c" && NPChar.id != ch.id && !CheckAttribute(ch, "quest.talk"))
		{
            storeArray[howStore] = ch.id;
            howStore++;
		}
    }
    if (howStore == 0) return "none";
    else return storeArray[rand(howStore-1)];
}
