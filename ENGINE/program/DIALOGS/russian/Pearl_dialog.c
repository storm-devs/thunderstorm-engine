#include "TEXT\DIALOGS\Pearl_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_BASE[0];
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ==> глава поселения
		case "HeadMan":
			NextDiag.TempNode = "HeadMan";
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_BASE[1] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[2]; 
				link.l1 = DLG_TEXT_BASE[3] + GetFullName(pchar) + DLG_TEXT_BASE[4];
				link.l1.go = "HeadMan_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[5], 
					DLG_TEXT_BASE[6], 
					DLG_TEXT_BASE[7],
					DLG_TEXT_BASE[8], "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[9] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[10], 
					DLG_TEXT_BASE[11],
					DLG_TEXT_BASE[12] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[13], 
					DLG_TEXT_BASE[14], npchar, Dialog.CurrentNode);
				link.l1.go = "exit";			
			}
			//-------- жемчужный генератор Шарпа ------------
			if (pchar.questTemp.Sharp != "begin" && pchar.questTemp.Sharp != "over" && pchar.questTemp.Sharp.SeekSpy == "begin")
			{
				link.l2 = DLG_TEXT_BASE[15];
				link.l2.go = "SharpSeekSpy";
			}
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow")
			{
				link.l2 = DLG_TEXT_BASE[16];
				link.l2.go = "SharpSeekSpy_10";
			}
		break;
		// <------- жемчужный генератор Шарпа
		case "SharpSeekSpy":
			dialog.text = DLG_TEXT_BASE[17];
			link.l1 = DLG_TEXT_BASE[18];
			link.l1.go = "SharpSeekSpy_1";
		break;
		case "SharpSeekSpy_1":
			dialog.text = DLG_TEXT_BASE[19];
			link.l1 = DLG_TEXT_BASE[20];
			link.l1.go = "SharpSeekSpy_2";
		break;
		case "SharpSeekSpy_2":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = DLG_TEXT_BASE[22];
			link.l1.go = "SharpSeekSpy_3";
		break;
		case "SharpSeekSpy_3":
			dialog.text = DLG_TEXT_BASE[23];
			link.l1 = DLG_TEXT_BASE[24];
			link.l1.go = "SharpSeekSpy_4";
		break;
		case "SharpSeekSpy_4":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "SharpSeekSpy_5";
		break;
		case "SharpSeekSpy_5":
			dialog.text = DLG_TEXT_BASE[27];
			link.l1 = DLG_TEXT_BASE[28];
			link.l1.go = "SharpSeekSpy_6";
		break;
		case "SharpSeekSpy_6":
			dialog.text = DLG_TEXT_BASE[29];
			link.l1 = DLG_TEXT_BASE[30];
			link.l1.go = "SharpSeekSpy_7";
		break;
		case "SharpSeekSpy_7":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "SharpSeekSpy_8";
			link.l2 = DLG_TEXT_BASE[33];
			link.l2.go = "SharpSeekSpy_8over";
		break;

		case "SharpSeekSpy_8":
			dialog.text = DLG_TEXT_BASE[34];
			link.l1 = DLG_TEXT_BASE[35];
			link.l1.go = "SharpSeekSpy_9";
		break;
		case "SharpSeekSpy_9":
			GiveItem2Character(pchar, "indian11");
			pchar.questTemp.Sharp.SeekSpy = "seekSpy";
            SetQuestHeader("SharpPearl_SeekSpy");
            AddQuestRecord("SharpPearl_SeekSpy", "1");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_8over":
			dialog.text = DLG_TEXT_BASE[36];
			link.l1 = DLG_TEXT_BASE[37];
			link.l1.go = "SharpSeekSpy_8fight";
		break;
		case "SharpSeekSpy_8fight":
			pchar.questTemp.Sharp.SeekSpy = "over";
			LAi_group_Attack(npchar, pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_10":
			dialog.text = DLG_TEXT_BASE[38];
			link.l1 = DLG_TEXT_BASE[39];
			link.l1.go = "SharpSeekSpy_11";
		break;
		case "SharpSeekSpy_11":
			dialog.text = DLG_TEXT_BASE[40];
			link.l1 = DLG_TEXT_BASE[41];
			link.l1.go = "SharpSeekSpy_12";
		break;
		case "SharpSeekSpy_12":
			dialog.text = DLG_TEXT_BASE[42];
			link.l1 = DLG_TEXT_BASE[43];
			link.l1.go = "SharpSeekSpy_13";
		break;
		case "SharpSeekSpy_13":
			dialog.text = DLG_TEXT_BASE[44];
			link.l1 = DLG_TEXT_BASE[45];
			link.l1.go = "exit";
			GiveItem2Character(pchar, "blade23");
			GiveItem2Character(pchar, "pistol5");
			GiveItem2Character(pchar, "cirass5");
			GiveItem2Character(pchar, "topor2");
			pchar.questTemp.Sharp.SeekSpy = "over";
            AddQuestRecord("SharpPearl_SeekSpy", "5");
			CloseQuestHeader("SharpPearl_SeekSpy");
		break;
		// >------- жемчужный генератор Шарпа
		case "HeadMan_1":
			dialog.text = DLG_TEXT_BASE[46];
			link.l1 = DLG_TEXT_BASE[47];
			link.l1.go = "HeadMan_2";
		break;
		case "HeadMan_2":
			dialog.text = DLG_TEXT_BASE[48];
			link.l1 = DLG_TEXT_BASE[49];
			link.l1.go = "HeadMan_3";
		break;
		case "HeadMan_3":
			dialog.text = DLG_TEXT_BASE[50] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[51];
			link.l1 = DLG_TEXT_BASE[52];
			link.l1.go = "HeadMan_4";
		break;
		case "HeadMan_4":
			dialog.text = DLG_TEXT_BASE[53];
			link.l1 = DLG_TEXT_BASE[54];
			link.l1.go = "HeadMan_5";
		break;
		case "HeadMan_5":
			dialog.text = DLG_TEXT_BASE[55] + GetAddress_Form(NPChar) + ".";
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "exit";
		break;
		// ==> часовой у поселения
		case "GuardMan":
			NextDiag.TempNode = "GuardMan";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[57] + GetFullName(npchar) + DLG_TEXT_BASE[58], 
				DLG_TEXT_BASE[59], 
				DLG_TEXT_BASE[60],
                DLG_TEXT_BASE[61], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[62] + GetFullName(pchar) + DLG_TEXT_BASE[63], 
				DLG_TEXT_BASE[64],
                DLG_TEXT_BASE[65], 
				DLG_TEXT_BASE[66], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GuardMan_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "GuardMan_1":
			dialog.text = DLG_TEXT_BASE[67];
			link.l1 = DLG_TEXT_BASE[68];
			link.l1.go = "GuardMan_2";
		break;
		case "GuardMan_2":
			chrDisableReloadToLocation = false;
			npchar.quest.TalkOk = true; //флаг разговор состоялся, все ОК.
			LAi_SetCitizenTypeNoGroup(npchar);
			DialogExit();
		break;

		case "GuardManAllarm":
			dialog.text = DLG_TEXT_BASE[69];
			link.l1 = DLG_TEXT_BASE[70];
			link.l1.go = "GuardManAllarm_1";
		break;
		case "GuardManAllarm_1":
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;
		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[71] + GetFullName(npchar) + DLG_TEXT_BASE[72], 
				DLG_TEXT_BASE[73], 
				DLG_TEXT_BASE[74],
                DLG_TEXT_BASE[75], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[76], 
				DLG_TEXT_BASE[77],
                DLG_TEXT_BASE[78], 
				DLG_TEXT_BASE[79], npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l2 = LinkRandPhrase(DLG_TEXT_BASE[80], 
					DLG_TEXT_BASE[81], 
					DLG_TEXT_BASE[82]);
				link.l2.go = "PearlMan_Sharp_1";
			}
		break;
		case "PearlMan_1":
			dialog.text = DLG_TEXT_BASE[83] + NationNameGenitive(sti(npchar.nation)) + DLG_TEXT_BASE[84];
			link.l1 = DLG_TEXT_BASE[85];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[86];
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = DLG_TEXT_BASE[87];
				link.l1 = DLG_TEXT_BASE[88];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[89];
				link.l1 = DLG_TEXT_BASE[90];
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[91], 
				DLG_TEXT_BASE[92], 
				DLG_TEXT_BASE[93]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[94], DLG_TEXT_BASE[95]);
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[96], 
				DLG_TEXT_BASE[97], 
				DLG_TEXT_BASE[98],
                DLG_TEXT_BASE[99], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[100], 
				DLG_TEXT_BASE[101],
                DLG_TEXT_BASE[102], 
				DLG_TEXT_BASE[103], npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = DLG_TEXT_BASE[104];
			link.l1 = DLG_TEXT_BASE[105];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[106];
			link.l2.go = "IndPearlMan_2";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l3 = DLG_TEXT_BASE[107];
				link.l3.go = "IndPearlMan_Sharp_1";
			}
		break;
		//жемчужный генератор Шарпа, поиски осведомителя
		case "IndPearlMan_Sharp_1":
			dialog.text = DLG_TEXT_BASE[108];
			link.l1 = DLG_TEXT_BASE[109];
			link.l1.go = "IndPearlMan_Sharp_2";
		break;
		case "IndPearlMan_Sharp_2":
			dialog.text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111];
			link.l1.go = "IndPearlMan_Sharp_3";
		break;
		case "IndPearlMan_Sharp_3":
			dialog.text = DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "IndPearlMan_Sharp_4";
		break;
		case "IndPearlMan_Sharp_4":
			dialog.text = DLG_TEXT_BASE[114];
			link.l1 = DLG_TEXT_BASE[115];
			link.l1.go = "IndPearlMan_Sharp_5";
		break;
		case "IndPearlMan_Sharp_5":
			dialog.text = DLG_TEXT_BASE[116];
			link.l1 = DLG_TEXT_BASE[117];
			link.l1.go = "IndPearlMan_Sharp_6";
		break;
		case "IndPearlMan_Sharp_6":
			dialog.text = DLG_TEXT_BASE[118];
			link.l1 = DLG_TEXT_BASE[119];
			link.l1.go = "exit";
			pchar.questTemp.Sharp.SeekSpy = "toLaVega";
            AddQuestRecord("SharpPearl_SeekSpy", "2");
			AddQuestUserData("SharpPearl_SeekSpy", "sName", npchar.name);
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
			pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";	
		break;
		//продажа жемчуга
		case "IndPearlMan_2":
			if (!CheckAttribute(npchar, "quest.pearl")) npchar.quest.pearl = rand(1);
			if (sti(npchar.quest.pearl) == 0 || CheckAttribute(pchar, "quest.PearlToShore_ForSale.id"))
			{
				dialog.text = DLG_TEXT_BASE[120];
				link.l1 = DLG_TEXT_BASE[121];
				link.l1.go = "exit";
			}
			else
			{
				bOk = false;
				int num = FindNearCharacters(npchar, 5.0, -1.0, -1.0, 1.0, false, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						iTemp = chrFindNearCharacters[i].index;
						if (iTemp == GetMainCharacterIndex()) continue;
						sTemp = characters[iTemp].id;
						if (findsubstr(sTemp, "FightMan" , 0) != -1)
						{
							bOk = true;
							break;
						}
					}
				}				
				if (bOk)
				{
					dialog.text = DLG_TEXT_BASE[122];
					link.l1 = DLG_TEXT_BASE[123];
					link.l1.go = "IndPearlMan_4";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[124];
					link.l1 = DLG_TEXT_BASE[125];
					link.l1.go = "IndPearlMan_3";
				}
			}
		break;
		case "IndPearlMan_3":
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "IndPearlMan_Sale";
			LAi_SetActorTypeNoGroup(NPChar);
			if (npchar.location == "Pearl_town_2")
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore51", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			else
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore49", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			pchar.quest.PearlToShore_ForSale.idx = npchar.index;
			npchar.quest.Pearl.bigQty = rand(30) + 10;
			npchar.quest.Pearl.smallQty = rand(60) + 20;
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		case "IndPearlMan_4":
			npchar.LifeDay = 0;
			LAi_group_Attack(NPChar, Pchar);
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			DialogExit();
		break;

		case "IndPearlMan_Sale":
			dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
			link.l1.go = "IndPearlMan_Sale_1";
		break;
		case "IndPearlMan_Sale_1":
			dialog.text = DLG_TEXT_BASE[128];
			link.l1 = DLG_TEXT_BASE[129];
			link.l1.go = "IndPearlMan_Sale_2";
			link.l2 = DLG_TEXT_BASE[130];
			link.l2.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_2":
			dialog.text = npchar.quest.Pearl.bigQty + DLG_TEXT_BASE[131] + npchar.quest.Pearl.smallQty + DLG_TEXT_BASE[132];
			link.l1 = DLG_TEXT_BASE[133];
			link.l1.go = "IndPearlMan_Sale_3";
		break;
		case "IndPearlMan_Sale_3":
			int iTemp = (sti(npchar.quest.Pearl.bigQty)*10) + (sti(npchar.quest.Pearl.smallQty)*5);
			if (sti(pchar.money) >= iTemp)
			{
				dialog.text = DLG_TEXT_BASE[134];
				link.l1 = DLG_TEXT_BASE[135];
				AddMoneyToCharacter(pchar, -iTemp);
				TakeNItems(pchar, "jewelry11", sti(npchar.quest.Pearl.bigQty));
				TakeNItems(pchar, "jewelry12", sti(npchar.quest.Pearl.smallQty)); 
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[136] + iTemp + DLG_TEXT_BASE[137];
				link.l1 = DLG_TEXT_BASE[138];
			}
			link.l1.go = "IndPearlMan_Sale_Out";	
		break;
		case "IndPearlMan_Sale_Out":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DialogExit();
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", -1);
		break;
	}
}
