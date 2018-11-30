#include "TEXT\DIALOGS\Quest\LostShipsCity\Waitress.h"
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
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = DLG_TEXT_LSC[0];
				link.l1 = DLG_TEXT_LSC[1]
				link.l1.go = "exit";
				break;
			}
			//после завала Хилла Брюннера
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				dialog.Text = DLG_TEXT_LSC[2];
				link.l4 = DLG_TEXT_LSC[3];
				link.l4.go = "NB_1";
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
				break;
			}
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toArmo_BrunnerDead")
			{
				dialog.Text = DLG_TEXT_LSC[4];
				link.l4 = DLG_TEXT_LSC[5];
				link.l4.go = "NBB_1";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.Text = DLG_TEXT_LSC[6];
					Link.l1 = DLG_TEXT_LSC[7];
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.Text = DLG_TEXT_LSC[8];
					Link.l1 = DLG_TEXT_LSC[9];
					Link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[10];
				Link.l1 = DLG_TEXT_LSC[11] + npchar.name + ".";
				Link.l1.go = "int_quests";
				link.l10 = DLG_TEXT_LSC[12];
				link.l10.go = "exit";
				//рассказываем ей о том, что, возможно, за убийством Хилла стоят касперы
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.Armo"))
				{
					link.l4 = DLG_TEXT_LSC[13];
					link.l4.go = "AboutCasper_1";
				}
				//наводка на первого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 0)
				{
					link.l4 = DLG_TEXT_LSC[14];
					link.l4.go = "Casper1";
				}
				//ждем втогого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = DLG_TEXT_LSC[15];
					link.l4.go = "WaitCasper1";
				}
				//наводка на второго
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = DLG_TEXT_LSC[16];
					link.l4.go = "Casper2";
				}
				//ждем третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = DLG_TEXT_LSC[17];
					link.l4.go = "WaitCasper2";
				}
				//наводка на третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = DLG_TEXT_LSC[18];
					link.l4.go = "Casper3";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 11 && npchar.name == xiDStr("Armo"))
				{
					link.l4 = DLG_TEXT_LSC[19];
					link.l4.go = "CasperLate";
				}
                //опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 15 && npchar.name == xiDStr("Armo"))
				{
					link.l4 = DLG_TEXT_LSC[20];
					link.l4.go = "CasperAllFight"; 
				}
				if (pchar.questTemp.LSC == "seekMillionAndHalf" && npchar.name == xiDStr("Armo") && !CheckAttribute(npchar, "quest.giveMoney"))
				{
					link.l4 = DLG_TEXT_LSC[21];
					link.l4.go = "askMoney";
				}
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toWaitress")
				{
					link.l5 = DLG_TEXT_LSC[22] + npchar.name + DLG_TEXT_LSC[23];
					link.l5.go = "ELTHusb_SF";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = DLG_TEXT_LSC[24];
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[25];
					link.l8.go = "SeekCrew";
				}
			}
		break;
		case "FT_1":
			dialog.text = DLG_TEXT_LSC[26] + GetFullName(npchar) + DLG_TEXT_LSC[27];
			link.l1 = DLG_TEXT_LSC[28] + GetFullName(pchar) + DLG_TEXT_LSC[29];
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = DLG_TEXT_LSC[30];
			link.l1 = DLG_TEXT_LSC[31];
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = DLG_TEXT_LSC[32];
			link.l1 = DLG_TEXT_LSC[33] + npchar.name + DLG_TEXT_LSC[34];
			link.l1.go = "exit";
		break;
		//вопросы
		case "int_quests":
			dialog.text = DLG_TEXT_LSC[35];
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = DLG_TEXT_LSC[36];
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = DLG_TEXT_LSC[37];
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = DLG_TEXT_LSC[38];
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = DLG_TEXT_LSC[39];
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = DLG_TEXT_LSC[40];
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l6 = DLG_TEXT_LSC[41] + npchar.name + DLG_TEXT_LSC[42];
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && npchar.name == xiDStr("Armo"))
			{
				link.l7 = DLG_TEXT_LSC[43];
				link.l7.go = "ansewer_7";
			}
			link.l10 = DLG_TEXT_LSC[44];
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = DLG_TEXT_LSC[45];
			link.l1 = DLG_TEXT_LSC[46];
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = DLG_TEXT_LSC[47];
			link.l1 = DLG_TEXT_LSC[48];
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = DLG_TEXT_LSC[49];
			link.l1 = DLG_TEXT_LSC[50];
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = DLG_TEXT_LSC[51];
			link.l1 = DLG_TEXT_LSC[52];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = DLG_TEXT_LSC[53];
			link.l1 = DLG_TEXT_LSC[54];
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = DLG_TEXT_LSC[55];
			link.l1 = DLG_TEXT_LSC[56];
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = DLG_TEXT_LSC[57];
			link.l1 = DLG_TEXT_LSC[58];
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = DLG_TEXT_LSC[59];
			link.l1 = DLG_TEXT_LSC[60];
			link.l1.go = "int_quests";
		break;
		case "ansewer_5":
			dialog.text = DLG_TEXT_LSC[61];
			link.l1 = DLG_TEXT_LSC[62];
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = DLG_TEXT_LSC[63];
			link.l1 = DLG_TEXT_LSC[64] + npchar.name + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = DLG_TEXT_LSC[65];
			link.l1 = DLG_TEXT_LSC[66];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_7":
			dialog.text = DLG_TEXT_LSC[67];
			link.l1 = DLG_TEXT_LSC[68];
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l7 = true;
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = DLG_TEXT_LSC[69];
			link.l1 = DLG_TEXT_LSC[70];
			link.l1.go = "NB_2";
		break;
		case "NB_2":
			dialog.text = DLG_TEXT_LSC[71];
			link.l1 = DLG_TEXT_LSC[72];
			link.l1.go = "NB_3";
		break;
		case "NBB_1":
			dialog.text = DLG_TEXT_LSC[73];
			link.l1 = DLG_TEXT_LSC[74];
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = DLG_TEXT_LSC[75];
			link.l1 = DLG_TEXT_LSC[76];
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = DLG_TEXT_LSC[77];
			link.l1 = DLG_TEXT_LSC[78];
			link.l1.go = "NB_5";
		break;
		case "NB_5":
			dialog.text = DLG_TEXT_LSC[79];
			link.l1 = DLG_TEXT_LSC[80];
			link.l1.go = "NB_6";
		break;
		case "NB_6":
			dialog.text = DLG_TEXT_LSC[81];
			link.l1 = DLG_TEXT_LSC[82];
			link.l1.go = "NB_7";
		break;
		case "NB_7":
			dialog.text = DLG_TEXT_LSC[83];
			link.l1 = DLG_TEXT_LSC[84];
			link.l1.go = "NB_8";
		break;
		case "NB_8":
			dialog.text = DLG_TEXT_LSC[85];
			link.l1 = DLG_TEXT_LSC[86];
			link.l1.go = "NB_9";
		break;
		case "NB_9":
			dialog.text = DLG_TEXT_LSC[87];
			link.l1 = DLG_TEXT_LSC[88];
			link.l1.go = "NB_10";
		break;
		case "NB_10":
			dialog.text = DLG_TEXT_LSC[89];
			link.l1 = DLG_TEXT_LSC[90];
			link.l1.go = "NB_11";
		break;
		case "NB_11":
			dialog.text = DLG_TEXT_LSC[91];
			link.l1 = DLG_TEXT_LSC[92];
			link.l1.go = "NB_12";
		break;
		case "NB_12":
			dialog.text = DLG_TEXT_LSC[93];
			link.l1 = DLG_TEXT_LSC[94];
			link.l1.go = "NB_13";
		break;
		case "NB_13":
			dialog.text = DLG_TEXT_LSC[95];
			link.l1 = DLG_TEXT_LSC[96];
			link.l1.go = "NB_14";
		break;
		case "NB_14":
			dialog.text = DLG_TEXT_LSC[97];
			link.l1 = DLG_TEXT_LSC[98];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAdmiralBarmenDead";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.LSC.knowMechanic"))
			{
				AddQuestRecord("ISS_MainLine", "26");
				DeleteAttribute(pchar, "questTemp.LSC.knowMechanic");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "25");
			}
		break;

		case "AboutCasper_1":
			dialog.text = DLG_TEXT_LSC[99];
			link.l1 = DLG_TEXT_LSC[100];
			link.l1.go = "AboutCasper_2";
		break;
		case "AboutCasper_2":
			dialog.text = DLG_TEXT_LSC[101];
			link.l1 = DLG_TEXT_LSC[102];
			link.l1.go = "AboutCasper_3";
		break;
		case "AboutCasper_3":
			dialog.text = DLG_TEXT_LSC[103];
			link.l1 = DLG_TEXT_LSC[104];
			link.l1.go = "AboutCasper_4";
		break;
		case "AboutCasper_4":
			dialog.text = DLG_TEXT_LSC[105];
			link.l1 = DLG_TEXT_LSC[106];
			link.l1.go = "AboutCasper_5";
		break;
		case "AboutCasper_5":
			dialog.text = DLG_TEXT_LSC[107];
			link.l1 = DLG_TEXT_LSC[108];
			link.l1.go = "AboutCasper_6";
		break;
		case "AboutCasper_6":
			dialog.text = DLG_TEXT_LSC[109];
			link.l1 = DLG_TEXT_LSC[110];
			link.l1.go = "AboutCasper_7";
		break;
		case "AboutCasper_7":
			dialog.text = DLG_TEXT_LSC[111];
			link.l1 = DLG_TEXT_LSC[112];
			link.l1.go = "AboutCasper_8";
		break;
		case "AboutCasper_8":
			dialog.text = DLG_TEXT_LSC[113];
			link.l1 = DLG_TEXT_LSC[114];
			link.l1.go = "AboutCasper_9";
		break;
		case "AboutCasper_9":
			dialog.text = DLG_TEXT_LSC[115];
			link.l1 = DLG_TEXT_LSC[116];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "33");
			pchar.questTemp.LSC.Armo = 0; //флаг на мочилово касперов. четные - готовность Армо, нечетные - флаг questAction 
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//первый каспер
		case "Casper1":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = DLG_TEXT_LSC[117];
				link.l1 = DLG_TEXT_LSC[118];
				link.l1.go = "Casper1_1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[119];
				link.l1 = DLG_TEXT_LSC[120];
				link.l1.go = "exit";
			}
		break;
		case "Casper1_1":
			dialog.text = DLG_TEXT_LSC[121];
			link.l1 = DLG_TEXT_LSC[122];
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 1; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "34");
		break;

		case "WaitCasper1":
			dialog.text = DLG_TEXT_LSC[123];
			link.l1 = DLG_TEXT_LSC[124];
			link.l1.go = "WaitCasper1_1";
		break;
		case "WaitCasper1_1":
			dialog.text = DLG_TEXT_LSC[125];
			link.l1 = DLG_TEXT_LSC[126];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//второй каспер
		case "Casper2":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = DLG_TEXT_LSC[127];
				link.l1 = DLG_TEXT_LSC[128];
				link.l1.go = "Casper2_1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[129];
				link.l1 = DLG_TEXT_LSC[130];
				link.l1.go = "exit";
			}
		break;
		case "Casper2_1":
			dialog.text = DLG_TEXT_LSC[131];
			link.l1 = DLG_TEXT_LSC[132];
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 3; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "37");
		break;

		case "WaitCasper2":
			dialog.text = DLG_TEXT_LSC[133];
			link.l1 = DLG_TEXT_LSC[134];
			link.l1.go = "WaitCasper2_1";
		break;
		case "WaitCasper2_1":
			dialog.text = DLG_TEXT_LSC[135];
			link.l1 = DLG_TEXT_LSC[136];
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//третий каспер
		case "Casper3":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = DLG_TEXT_LSC[137];
				link.l1 = DLG_TEXT_LSC[138];
				link.l1.go = "Casper3_1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[139];
				link.l1 = DLG_TEXT_LSC[140];
				link.l1.go = "exit";
			}
		break;
		case "Casper3_1":
			dialog.text = DLG_TEXT_LSC[141];
			link.l1 = DLG_TEXT_LSC[142];
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 5; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_MainLine", "38");
		break;
		//прерывания хода квеста Армо
		case "CasperLate":
			dialog.text = DLG_TEXT_LSC[143];
			link.l1 = DLG_TEXT_LSC[144];
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 12; //Отмазала девка
			AddQuestRecord("ISS_MainLine", "35");
		break;
		case "CasperAllFight":
			dialog.text = DLG_TEXT_LSC[145];
			link.l1 = DLG_TEXT_LSC[146];
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
		break;
		//Армо мертва
		case "ArmoIsDead":
			dialog.text = DLG_TEXT_LSC[147];
			link.l1 = DLG_TEXT_LSC[148];
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = DLG_TEXT_LSC[149];
			link.l1 = DLG_TEXT_LSC[150];
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = DLG_TEXT_LSC[151];
			link.l1 = DLG_TEXT_LSC[152];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		//Если Армо жива, то дает денег
		case "askMoney":
			dialog.text = DLG_TEXT_LSC[153];
			link.l1 = DLG_TEXT_LSC[154];
			link.l1.go = "askMoney_1";
		break;
		case "askMoney_1":
			dialog.text = DLG_TEXT_LSC[155];
			link.l1 = DLG_TEXT_LSC[156];
			link.l1.go = "askMoney_2";
		break;
		case "askMoney_2":
			dialog.text = DLG_TEXT_LSC[157];
			link.l1 = DLG_TEXT_LSC[158];
			link.l1.go = "askMoney_3";
		break;
		case "askMoney_3":
			dialog.text = DLG_TEXT_LSC[159];
			link.l1 = DLG_TEXT_LSC[160];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.giveMoney = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[161], 
				DLG_TEXT_LSC[162], 
				DLG_TEXT_LSC[163],
                DLG_TEXT_LSC[164], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[165], 
				DLG_TEXT_LSC[166],
                DLG_TEXT_LSC[167], 
				DLG_TEXT_LSC[168], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = DLG_TEXT_LSC[169];
			link.l1 = DLG_TEXT_LSC[170];
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "48");
			AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[171], 
				DLG_TEXT_LSC[172], 
				DLG_TEXT_LSC[173],
                DLG_TEXT_LSC[174], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[175], 
				DLG_TEXT_LSC[176],
                DLG_TEXT_LSC[177], 
				DLG_TEXT_LSC[178], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			if (npchar.name == xiDStr("Armo"))
			{
				dialog.text = DLG_TEXT_LSC[179];
				link.l1 = DLG_TEXT_LSC[180];
				link.l1.go = "SeekCrew_2";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[181];
				link.l1 = DLG_TEXT_LSC[182];
				link.l1.go = "SeekCrew_2";
			}
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[183];
			link.l1 = DLG_TEXT_LSC[184];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[185];
			link.l1 = DLG_TEXT_LSC[186];
			link.l1.go = "exit";
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = DLG_TEXT_LSC[187];
			link.l1 = DLG_TEXT_LSC[188];
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = DLG_TEXT_LSC[189];
			link.l1 = DLG_TEXT_LSC[190];
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = DLG_TEXT_LSC[191];
			link.l1 = DLG_TEXT_LSC[192];
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = DLG_TEXT_LSC[193];
			link.l1 = DLG_TEXT_LSC[194];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "8");
			pchar.questTemp.LSC.ElisHusband = "toZhilBaru";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
 
