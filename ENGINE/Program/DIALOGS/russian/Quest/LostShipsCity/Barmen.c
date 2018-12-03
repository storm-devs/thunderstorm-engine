#include "DIALOGS\russian\Rumours\Common_rumours.c"
#include "TEXT\DIALOGS\Quest\LostShipsCity\Barmen.h"
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = DLG_TEXT_LSC[0];
				link.l1 = DLG_TEXT_LSC[1]
				link.l1.go = "exit";
				break;
			}

			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = DLG_TEXT_LSC[2] + GetFullName(npchar) + DLG_TEXT_LSC[3];
					link.l1 = DLG_TEXT_LSC[4] + GetFullName(pchar) + DLG_TEXT_LSC[5];
					link.l1.go = "FS_1";
				}
				else				
				{
					dialog.Text = DLG_TEXT_LSC[6] + GetFullName(npchar) + DLG_TEXT_LSC[7];
					Link.l1 = DLG_TEXT_LSC[8] + npchar.name + DLG_TEXT_LSC[9] + GetFullName(pchar) + ".";
					Link.l1.go = "First time";
				}
			}
			else
			{
				//базар в винном погребе
				if (pchar.questTemp.LSC == "toWineCellarGone" && npchar.location.locator == "stay1")
				{
					dialog.Text = DLG_TEXT_LSC[10];
					link.l4 = DLG_TEXT_LSC[11];
					link.l4.go = "TizerCellar";
					PChar.quest.LSC_returnBarmen.over = "yes"; //снимаем таймер на опоздание, разговор состоялся
					break;
				}	
				//после завала Хилла Брюннера
				if (pchar.questTemp.LSC == "barmenIsDead" && !CheckAttribute(npchar, "quest.HillNB_1"))
				{
					dialog.Text = DLG_TEXT_LSC[12];
					link.l4 = DLG_TEXT_LSC[13];
					link.l4.go = "NB_1";
					pchar.questTemp.LSC = "barmenIsDeadYouKnow";
					break;
				}
				if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toAdmiralBarmenDead")
				{
					if (!CheckAttribute(npchar, "quest.HillNBB_1"))
					{
						dialog.Text = DLG_TEXT_LSC[14];
						link.l4 = DLG_TEXT_LSC[15];
						link.l4.go = "NBB_1";
						break;
					}
				}
				//убийство Армо
				sld = characterFromId("LSCwaitress");
				if (sld.lastname == xiDStr("Prescott") && !CheckAttribute(npchar, "quest.Armo"))
				{
					dialog.Text = DLG_TEXT_LSC[16];
					link.l4 = DLG_TEXT_LSC[17];
					link.l4.go = "ADied_1";
					npchar.quest.Armo = true;
					break;
				}
				//==> штатый диалог
				dialog.Text = LinkRandPhrase(DLG_TEXT_LSC[18] + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    DLG_TEXT_LSC[19],
                                    DLG_TEXT_LSC[20]);
				Link.l1 = DLG_TEXT_LSC[21];
				Link.l1.go = "int_quests";
				link.l2 = DLG_TEXT_LSC[22];
				link.l2.go = "room";
				link.l3 = LinkRandPhrase(DLG_TEXT_LSC[23], 
					DLG_TEXT_LSC[24], DLG_TEXT_LSC[25]);
				link.l3.go = "rumours_LSC";
				Link.l4 = DLG_TEXT_LSC[26] + NPChar.name + DLG_TEXT_LSC[27];
				Link.l4.go = "exit";
				//==>> квесты
				if (pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 3)
				{
					link.l4 = DLG_TEXT_LSC[28];
					link.l4.go = "Tizer";
				}
				if (pchar.questTemp.LSC == "toWineCellarLate")
				{
					link.l4 = DLG_TEXT_LSC[29];
					link.l4.go = "TizerCellarLate";
				}
				if (pchar.questTemp.LSC == "toDiffindoor" && CheckCharacterItem(pchar, "letter_LSC"))
				{
					link.l4 = DLG_TEXT_LSC[30];
					link.l4.go = "TizerCellarOk_1";
				}
				if (pchar.questTemp.LSC == "afterFightInProtector")
				{
					link.l4 = DLG_TEXT_LSC[31];
					link.l4.go = "AfterProtector_1";
				}
				if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
				{
					link.l4 = DLG_TEXT_LSC[32];
					link.l4.go = "NarvalRing_1";
				}
				if (pchar.questTemp.LSC == "toTavernNarvalDestroyed")
				{
					link.l4 = DLG_TEXT_LSC[33];
					link.l4.go = "AfterNarvalDesrt_1";
				}
				if (pchar.questTemp.LSC == "waitInterception" && GetQuestPastDayParam("questTemp.LSC") > 2 && GetHour() < 20)
				{
					link.l4 = DLG_TEXT_LSC[34];
					link.l4.go = "Interception";
				}
				if (pchar.questTemp.LSC == "InterceptionLate")
				{
					link.l4 = DLG_TEXT_LSC[35];
					link.l4.go = "InterceptionLate";
				}
				if (pchar.questTemp.LSC == "InterceptionYouSeen")
				{
					link.l4 = DLG_TEXT_LSC[36];
					link.l4.go = "InterceptionYouSeen";
				}
				if (pchar.questTemp.LSC == "waitInterceptionResult")
				{
					link.l4 = DLG_TEXT_LSC[37];
					link.l4.go = "Result";
				}
				if (pchar.questTemp.LSC == "InterceptionOk")
				{
					link.l4 = DLG_TEXT_LSC[38];
					link.l4.go = "InterceptionOk";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = DLG_TEXT_LSC[39];
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[40];
					link.l8.go = "SeekCrew";
				}
			}
		break;

		case "FS_1":
			dialog.text = DLG_TEXT_LSC[41];
			link.l1 = DLG_TEXT_LSC[42];
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = DLG_TEXT_LSC[43];
			link.l1 = DLG_TEXT_LSC[44];
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//крутим время
		case "room":
   			if (chrDisableReloadToLocation) //кто-то должен подойти к ГГ.
			{
				dialog.text = DLG_TEXT_LSC[45];
				link.l1 = DLG_TEXT_LSC[46];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_LSC[47];
			if(!isDay())
			{
				link.l1 = DLG_TEXT_LSC[48];
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[49];
				link.l1.go = "hall_night_wait";
				link.l2 = DLG_TEXT_LSC[50];
				link.l2.go = "hall_day_wait";
			}
			link.l3 = DLG_TEXT_LSC[51];
			link.l3.go = "exit";
		break;
		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[52];
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = DLG_TEXT_LSC[53];
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[54];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[55];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = DLG_TEXT_LSC[56];
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = DLG_TEXT_LSC[57];
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = DLG_TEXT_LSC[58];
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && pchar.questTemp.LSC == "AdmiralIsWaiting" && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l7 = DLG_TEXT_LSC[59];
				link.l7.go = "ansewer_7";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l8"))
			{
				link.l8 = DLG_TEXT_LSC[60];
				link.l8.go = "ansewer_8";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l9"))
			{
				link.l9 = DLG_TEXT_LSC[61];
				link.l9.go = "ansewer_9";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l10"))
			{
				link.l10 = DLG_TEXT_LSC[62];
				link.l10.go = "ansewer_10";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l11"))
			{
				link.l11 = DLG_TEXT_LSC[63];
				link.l11.go = "ansewer_11";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l12") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l12 = DLG_TEXT_LSC[64];
				link.l12.go = "ansewer_12";
			}
			link.l20 = DLG_TEXT_LSC[65];
			link.l20.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = DLG_TEXT_LSC[66];
			link.l1 = DLG_TEXT_LSC[67];
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = DLG_TEXT_LSC[68];
			link.l1 = DLG_TEXT_LSC[69];
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = DLG_TEXT_LSC[70];
			link.l1 = DLG_TEXT_LSC[71];
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[72];
			link.l1 = DLG_TEXT_LSC[73];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[74];
			link.l1 = DLG_TEXT_LSC[75];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[76];
			link.l1 = DLG_TEXT_LSC[77];
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[78];
			link.l1 = DLG_TEXT_LSC[79];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = DLG_TEXT_LSC[80];
			link.l1 = DLG_TEXT_LSC[81];
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = DLG_TEXT_LSC[82];
			link.l1 = DLG_TEXT_LSC[83];
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = DLG_TEXT_LSC[84];
			link.l1 = DLG_TEXT_LSC[85];
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = DLG_TEXT_LSC[86];
			link.l1 = DLG_TEXT_LSC[87];
			link.l1.go = "ansewer_4_4";
		break;
		case "ansewer_4_4":
			dialog.text = DLG_TEXT_LSC[88];
			link.l1 = DLG_TEXT_LSC[89];
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = DLG_TEXT_LSC[90];
			link.l1 = DLG_TEXT_LSC[91];
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = DLG_TEXT_LSC[92];
			link.l1 = DLG_TEXT_LSC[93];
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = DLG_TEXT_LSC[94];
			link.l1 = DLG_TEXT_LSC[95];
			link.l1.go = "ansewer_6_3";
		break;
		case "ansewer_6_3":
			dialog.text = DLG_TEXT_LSC[96];
			link.l1 = DLG_TEXT_LSC[97];
			link.l1.go = "ansewer_6_4";
		break;
		case "ansewer_6_4":
			dialog.text = DLG_TEXT_LSC[98];
			link.l1 = DLG_TEXT_LSC[99];
			link.l1.go = "ansewer_6_5";
		break;
		case "ansewer_6_5":
			dialog.text = DLG_TEXT_LSC[100];
			link.l1 = DLG_TEXT_LSC[101];
			link.l1.go = "ansewer_6_6";
		break;
		case "ansewer_6_6":
			dialog.text = DLG_TEXT_LSC[102];
			link.l1 = DLG_TEXT_LSC[103];
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "4");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		case "ansewer_7":
			dialog.text = DLG_TEXT_LSC[104];
			link.l1 = DLG_TEXT_LSC[105];
			link.l1.go = "ansewer_7_1";
			NextDiag.(NodePrevName).l7 = true;
		break;
		case "ansewer_7_1":
			dialog.text = DLG_TEXT_LSC[106];
			link.l1 = DLG_TEXT_LSC[107];
			link.l1.go = "ansewer_7_2";
		break;
		case "ansewer_7_2":
			dialog.text = DLG_TEXT_LSC[108];
			link.l1 = DLG_TEXT_LSC[109];
			link.l1.go = "int_quests";
		break;
		case "ansewer_8":
			dialog.text = DLG_TEXT_LSC[110];
			link.l1 = DLG_TEXT_LSC[111];
			link.l1.go = "ansewer_8_1";
			NextDiag.(NodePrevName).l8 = true;
		break;
		case "ansewer_8_1":
			dialog.text = DLG_TEXT_LSC[112];
			link.l1 = DLG_TEXT_LSC[113];
			link.l1.go = "ansewer_8_2";
		break;
		case "ansewer_8_2":
			dialog.text = DLG_TEXT_LSC[114];
			link.l1 = DLG_TEXT_LSC[115];
			link.l1.go = "ansewer_8_3";
		break;
		case "ansewer_8_3":
			dialog.text = DLG_TEXT_LSC[116];
			link.l1 = DLG_TEXT_LSC[117];
			link.l1.go = "ansewer_8_4";
		break;
		case "ansewer_8_4":
			dialog.text = DLG_TEXT_LSC[118];
			link.l1 = DLG_TEXT_LSC[119];
			link.l1.go = "int_quests";
		break;
		case "ansewer_9":
			dialog.text = DLG_TEXT_LSC[120];
			link.l1 = DLG_TEXT_LSC[121];
			link.l1.go = "ansewer_9_1";
			NextDiag.(NodePrevName).l9 = true;
		break;
		case "ansewer_9_1":
			dialog.text = DLG_TEXT_LSC[122]+
				DLG_TEXT_LSC[123];
			link.l1 = DLG_TEXT_LSC[124];
			link.l1.go = "int_quests";
		break;
		case "ansewer_10":
			dialog.text = DLG_TEXT_LSC[125];
			link.l1 = DLG_TEXT_LSC[126];
			link.l1.go = "ansewer_10_1";
			NextDiag.(NodePrevName).l10 = true;
		break;
		case "ansewer_10_1":
			dialog.text = DLG_TEXT_LSC[127];
			link.l1 = DLG_TEXT_LSC[128];
			link.l1.go = "int_quests";
		break;
		case "ansewer_11":
			dialog.text = DLG_TEXT_LSC[129];
			link.l1 = DLG_TEXT_LSC[130];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l11 = true;
		break;
		case "ansewer_12":
			dialog.text = DLG_TEXT_LSC[131];
			link.l1 = DLG_TEXT_LSC[132];
			link.l1.go = "ansewer_12_1";
			NextDiag.(NodePrevName).l12 = true;
		break;
		case "ansewer_12_1":
			dialog.text = DLG_TEXT_LSC[133];
			link.l1 = DLG_TEXT_LSC[134];
			link.l1.go = "ansewer_12_2";
		break;
		case "ansewer_12_2":
			dialog.text = DLG_TEXT_LSC[135];
			link.l1 = DLG_TEXT_LSC[136] + npchar.name + ".";
			link.l1.go = "int_quests";
		break;

		// ------------------ квесты ------------------
		//бармен забивает стрелу в винном погребе
		case "Tizer":
			dialog.text = DLG_TEXT_LSC[137];
			link.l1 = DLG_TEXT_LSC[138];
			link.l1.go = "Tizer_1";
		break;
		case "Tizer_1":
			dialog.text = DLG_TEXT_LSC[139];
			link.l1 = DLG_TEXT_LSC[140];
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = DLG_TEXT_LSC[141];
			link.l1 = DLG_TEXT_LSC[142];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			AddQuestRecord("ISS_MainLine", "5");
		break;
		//бармен ругается, что ГГ не пришел в погреб
		case "TizerCellarLate":
			dialog.text = DLG_TEXT_LSC[143];
			link.l1 = DLG_TEXT_LSC[144];
			link.l1.go = "TizerCellarLate_1";
		break;
		case "TizerCellarLate_1":
			dialog.text = DLG_TEXT_LSC[145];
			link.l1 = DLG_TEXT_LSC[146];
			link.l1.go = "TizerCellarLate_2";
		break;
		case "TizerCellarLate_2":
			dialog.text = DLG_TEXT_LSC[147];
			link.l1 = DLG_TEXT_LSC[148];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
		break;
		//базар с барменом в погребе
		case "TizerCellar":
			dialog.text = DLG_TEXT_LSC[149];
			link.l1 = DLG_TEXT_LSC[150];
			link.l1.go = "TizerCellar_1";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.LSC_returnBarmen_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_returnBarmen_2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_returnBarmen_2.function = "LSC_returnBarmen_2";
		break;
		case "TizerCellar_1":
			dialog.text = DLG_TEXT_LSC[151];
			link.l1 = DLG_TEXT_LSC[152];
			link.l1.go = "TizerCellar_2";
		break;
		case "TizerCellar_2":
			dialog.text = DLG_TEXT_LSC[153];
			link.l1 = DLG_TEXT_LSC[154];
			link.l1.go = "TizerCellar_3";
		break;
		case "TizerCellar_3":
			dialog.text = DLG_TEXT_LSC[155];
			link.l1 = DLG_TEXT_LSC[156];
			link.l1.go = "TizerCellar_4";
		break;
		case "TizerCellar_4":
			dialog.text = DLG_TEXT_LSC[157];
			link.l1 = DLG_TEXT_LSC[158];
			link.l1.go = "TizerCellar_5";
		break;
		case "TizerCellar_5":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "TizerCellar_6";
		break;
		case "TizerCellar_6":
			dialog.text = DLG_TEXT_LSC[161];
			link.l1 = DLG_TEXT_LSC[162];
			link.l1.go = "TizerCellar_7";
		break;
		case "TizerCellar_7":
			dialog.text = DLG_TEXT_LSC[163];
			if (CheckCharacterItem(pchar, "letter_LSC"))
			{
				link.l1 = DLG_TEXT_LSC[164];
				link.l1.go = "TizerCellarOk_1";
			}
			else
			{
				link.l1 = DLG_TEXT_LSC[165];
				link.l1.go = "TizerCellar_8";
			}
		break;
		case "TizerCellar_8":
			dialog.text = DLG_TEXT_LSC[166];
			link.l1 = DLG_TEXT_LSC[167];
			link.l1.go = "TizerCellar_9";
		break;
		case "TizerCellar_9":
			dialog.text = DLG_TEXT_LSC[168];
			link.l1 = DLG_TEXT_LSC[169];
			link.l1.go = "TizerCellar_10";
		break;
		case "TizerCellar_10":
			dialog.text = DLG_TEXT_LSC[170];
			link.l1 = DLG_TEXT_LSC[171];
			link.l1.go = "TizerCellar_11";
		break;
		case "TizerCellar_11":
			dialog.text = DLG_TEXT_LSC[172];
			link.l1 = DLG_TEXT_LSC[173];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "6");
			pchar.questTemp.LSC = "toDiffindoor"; //флаг линейки ГПК
		break;

		case "TizerCellarOk_1":
			dialog.text = DLG_TEXT_LSC[174];
			link.l1 = DLG_TEXT_LSC[175];
			link.l1.go = "TizerCellarOk_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "TizerCellarOk_2":
			dialog.text = DLG_TEXT_LSC[176];
			link.l1 = DLG_TEXT_LSC[177];
			link.l1.go = "TizerCellarOk_3";
		break;
		case "TizerCellarOk_3":
			dialog.text = DLG_TEXT_LSC[178];
			link.l1 = DLG_TEXT_LSC[179];
			link.l1.go = "TizerCellarOk_4";
		break;
		case "TizerCellarOk_4":
			dialog.text = DLG_TEXT_LSC[180];
			link.l1 = DLG_TEXT_LSC[181];
			link.l1.go = "TizerCellarOk_5";
		break;
		case "TizerCellarOk_5":
			dialog.text = DLG_TEXT_LSC[182];
			link.l1 = DLG_TEXT_LSC[183];
			link.l1.go = "TizerCellarOk_6";
		break;
		case "TizerCellarOk_6":
			dialog.text = DLG_TEXT_LSC[184];
			link.l1 = DLG_TEXT_LSC[185];
			link.l1.go = "TizerCellarOk_7";
		break;
		case "TizerCellarOk_7":
			dialog.text = DLG_TEXT_LSC[186];
			link.l1 = DLG_TEXT_LSC[187];
			link.l1.go = "TizerCellarOk_8";
		break;
		case "TizerCellarOk_8":
			dialog.text = DLG_TEXT_LSC[188];
			link.l1 = DLG_TEXT_LSC[189];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAndreLabor"; //флаг линейки ГПК
			AddQuestRecord("ISS_MainLine", "7");
			pchar.questTemp.LSC.checkBoxes = true; //шмалять по открытым сундукам ежесуточно
		break;

		case "AfterProtector_1":
			dialog.text = DLG_TEXT_LSC[190];
			link.l1 = DLG_TEXT_LSC[191];
			link.l1.go = "AfterProtector_2";
		break;
		case "AfterProtector_2":
			dialog.text = DLG_TEXT_LSC[192];
			link.l1 = DLG_TEXT_LSC[193];
			link.l1.go = "AfterProtector_3";
		break;
		case "AfterProtector_3":
			dialog.text = DLG_TEXT_LSC[194];
			link.l1 = DLG_TEXT_LSC[195];
			link.l1.go = "AfterProtector_4";
		break;
		case "AfterProtector_4":
			dialog.text = DLG_TEXT_LSC[196];
			link.l1 = DLG_TEXT_LSC[197];
			link.l1.go = "AfterProtector_5";
		break;
		case "AfterProtector_5":
			dialog.text = DLG_TEXT_LSC[198];
			link.l1 = DLG_TEXT_LSC[199];
			link.l1.go = "AfterProtector_6";
		break;
		case "AfterProtector_6":
			dialog.text = DLG_TEXT_LSC[200];
			link.l1 = DLG_TEXT_LSC[201];
			link.l1.go = "AfterProtector_7";
		break;
		case "AfterProtector_7":
			dialog.text = DLG_TEXT_LSC[202];
			link.l1 = DLG_TEXT_LSC[203];
			link.l1.go = "AfterProtector_8";
		break;
		case "AfterProtector_8":
			dialog.text = DLG_TEXT_LSC[204];
			link.l1 = DLG_TEXT_LSC[205];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "10");
			pchar.questTemp.LSC = "toKillOneNarval";
			pchar.quest.LSC_KillOneNarval.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_KillOneNarval.function = "LSC_KillOneNarval";
		break;

		case "NarvalRing_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[206], 
				DLG_TEXT_LSC[207], 
				DLG_TEXT_LSC[208],
                DLG_TEXT_LSC[209], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[210], 
				DLG_TEXT_LSC[211],
                DLG_TEXT_LSC[212], 
				DLG_TEXT_LSC[213], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	
		case "AfterNarvalDesrt_1":
			dialog.text = DLG_TEXT_LSC[214];
			link.l1 = DLG_TEXT_LSC[215];
			link.l1.go = "AfterNarvalDesrt_2";
		break;
		case "AfterNarvalDesrt_2":
			dialog.text = DLG_TEXT_LSC[216];
			link.l1 = DLG_TEXT_LSC[217];
			link.l1.go = "AfterNarvalDesrt_3";
		break;
		case "AfterNarvalDesrt_3":
			dialog.text = DLG_TEXT_LSC[218];
			link.l1 = DLG_TEXT_LSC[219];
			link.l1.go = "AfterNarvalDesrt_4";
		break;
		case "AfterNarvalDesrt_4":
			dialog.text = DLG_TEXT_LSC[220];
			link.l1 = DLG_TEXT_LSC[221];
			link.l1.go = "AfterNarvalDesrt_5";
		break;
		case "AfterNarvalDesrt_5":
			dialog.text = DLG_TEXT_LSC[222];
			link.l1 = DLG_TEXT_LSC[223];
			link.l1.go = "AfterNarvalDesrt_6";
		break;
		case "AfterNarvalDesrt_6":
			dialog.text = DLG_TEXT_LSC[224];
			link.l1 = DLG_TEXT_LSC[225];
			link.l1.go = "AfterNarvalDesrt_7";
		break;
		case "AfterNarvalDesrt_7":
			dialog.text = DLG_TEXT_LSC[226];
			link.l1 = DLG_TEXT_LSC[227];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterception";
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
			AddQuestRecord("ISS_MainLine", "17");
		break;

		case "Interception":
			dialog.text = DLG_TEXT_LSC[228];
			link.l1 = DLG_TEXT_LSC[229];
			link.l1.go = "Interception_1";
		break;
		case "Interception_1":
			dialog.text = DLG_TEXT_LSC[230];
			link.l1 = DLG_TEXT_LSC[231];
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			dialog.text = DLG_TEXT_LSC[232];
			link.l1 = DLG_TEXT_LSC[233];
			link.l1.go = "Interception_3";
		break;
		case "Interception_3":
			dialog.text = DLG_TEXT_LSC[234];
			link.l1 = DLG_TEXT_LSC[235];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toInterception";
			pchar.questTemp.LSC.itemState = false; //флаг нахождения в локаторе итем в таверне
			AddQuestRecord("ISS_MainLine", "18");
		break;

		case "InterceptionLate":
			dialog.text = DLG_TEXT_LSC[236];
			link.l1 = DLG_TEXT_LSC[237];
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionYouSeen":
			dialog.text = DLG_TEXT_LSC[238];
			link.l1 = DLG_TEXT_LSC[239];
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionBadWork_1":
			dialog.text = DLG_TEXT_LSC[240];
			link.l1 = DLG_TEXT_LSC[241];
			link.l1.go = "InterceptionBadWork_2";
		break;
		case "InterceptionBadWork_2":
			dialog.text = DLG_TEXT_LSC[242];
			link.l1 = DLG_TEXT_LSC[243];
			link.l1.go = "InterceptionBadWork_3";
		break;
		case "InterceptionBadWork_3":
			dialog.text = DLG_TEXT_LSC[244];
			link.l1 = DLG_TEXT_LSC[245];
			link.l1.go = "InterceptionBadWork_4";
		break;
		case "InterceptionBadWork_4":
			dialog.text = DLG_TEXT_LSC[246];
			link.l1 = DLG_TEXT_LSC[247];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "21");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 15);
		break;

		case "Result":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[248], 
				DLG_TEXT_LSC[249], 
				DLG_TEXT_LSC[250],
                DLG_TEXT_LSC[251], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[252], 
				DLG_TEXT_LSC[253],
                DLG_TEXT_LSC[254], 
				DLG_TEXT_LSC[255], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "InterceptionOk":
			sld = characterFromId("LSCMayor");
			if (sld.location == "FleuronTavern")
				dialog.text = DLG_TEXT_LSC[256];
			else
				dialog.text = DLG_TEXT_LSC[257];
			link.l1 = DLG_TEXT_LSC[258];
			link.l1.go = "InterceptionOk_1";
		break;
		case "InterceptionOk_1":
			dialog.text = DLG_TEXT_LSC[259];
			link.l1 = DLG_TEXT_LSC[260];
			link.l1.go = "InterceptionOk_2";
		break;
		case "InterceptionOk_2":
			dialog.text = DLG_TEXT_LSC[261];
			link.l1 = DLG_TEXT_LSC[262];
			link.l1.go = "InterceptionOk_4";
		break;
		case "InterceptionOk_4":
			dialog.text = DLG_TEXT_LSC[263];
			link.l1 = DLG_TEXT_LSC[264];
			link.l1.go = "InterceptionOk_5";
		break;
		case "InterceptionOk_5":
			dialog.text = DLG_TEXT_LSC[265];
			link.l1 = DLG_TEXT_LSC[266];
			link.l1.go = "InterceptionOk_6";
		break;
		case "InterceptionOk_6":
			dialog.text = DLG_TEXT_LSC[267];
			link.l1 = DLG_TEXT_LSC[268];
			link.l1.go = "InterceptionOk_7";
		break;
		case "InterceptionOk_7":
			dialog.text = DLG_TEXT_LSC[269];
			link.l1 = DLG_TEXT_LSC[270];
			link.l1.go = "InterceptionOk_8";
		break;
		case "InterceptionOk_8":
			dialog.text = DLG_TEXT_LSC[271];
			link.l1 = DLG_TEXT_LSC[272];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "23");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 3);
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = DLG_TEXT_LSC[273];
			link.l1 = DLG_TEXT_LSC[274];
			link.l1.go = "NB_2";
			npchar.quest.HillNB_1 = true;
		break;
		case "NB_2":
			dialog.text = DLG_TEXT_LSC[275];
			link.l1 = DLG_TEXT_LSC[276];
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = DLG_TEXT_LSC[277];
			link.l1 = DLG_TEXT_LSC[278];
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = DLG_TEXT_LSC[279];
			link.l1 = DLG_TEXT_LSC[280];
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow")
			{
				pchar.questTemp.LSC = "toArmo_BrunnerDead";
			}
			AddQuestRecord("ISS_MainLine", "24");
		break;

		case "NBB_1":
			dialog.text = DLG_TEXT_LSC[281];
			link.l1 = DLG_TEXT_LSC[282];
			link.l1.go = "NBB_2";
			npchar.quest.HillNBB_1 = true;
		break;
		case "NBB_2":
			dialog.text = DLG_TEXT_LSC[283];
			link.l1 = DLG_TEXT_LSC[284];
			link.l1.go = "NB_3";
		break;
		//базар по убийству Армо
		case "ADied_1":
			dialog.text = DLG_TEXT_LSC[285];
			link.l1 = DLG_TEXT_LSC[286];
			link.l1.go = "ADied_2";
		break;
		case "ADied_2":
			dialog.text = DLG_TEXT_LSC[287];
			link.l1 = DLG_TEXT_LSC[288];
			link.l1.go = "ADied_3";
		break;
		case "ADied_3":
			dialog.text = DLG_TEXT_LSC[289];
			link.l1 = DLG_TEXT_LSC[290];
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[291], 
				DLG_TEXT_LSC[292], 
				DLG_TEXT_LSC[293],
                DLG_TEXT_LSC[294], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[295], 
				DLG_TEXT_LSC[296],
                DLG_TEXT_LSC[297], 
				DLG_TEXT_LSC[298], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[299];
			link.l1 = DLG_TEXT_LSC[300];
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[301], 
				DLG_TEXT_LSC[302], 
				DLG_TEXT_LSC[303],
                DLG_TEXT_LSC[304], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[305], 
				DLG_TEXT_LSC[306],
                DLG_TEXT_LSC[307], 
				DLG_TEXT_LSC[308], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[309];
			link.l1 = DLG_TEXT_LSC[310];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[311];
			link.l1 = DLG_TEXT_LSC[312];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[313];
			link.l1 = DLG_TEXT_LSC[314];
			link.l1.go = "exit";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
