#include "TEXT\DIALOGS\Quest\PiratesLine_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_Q[0];
			link.l1 = DLG_TEXT_Q[1];
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// -------------------------------------- квест №1 -------------------------------------------------
		//первая встреча с посыльным Моргана в Пуэрто Принсипе
		case "PiratesMan1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = DLG_TEXT_Q[2];
				link.l1 = DLG_TEXT_Q[3];
				link.l1.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[4];
				link.l1 = DLG_TEXT_Q[5];
				link.l1.go = "PiratesManNot_1";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		case "PiratesMan1_1":
			dialog.text = DLG_TEXT_Q[6];
			link.l1 = DLG_TEXT_Q[7];
			link.l1.go = "PiratesMan1_2";
		break;
		case "PiratesMan1_2":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1"; 
			chrDisableReloadToLocation = true; 
			bDisableFastReload = true; 
			FreeSitLocator("PuertoPrincipe_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5", "PuertoPrincipe_tavern", "sit", "sit3", "PiratesLine_toTavern", -1);
		break;

		case "PiratesManNot_1":
			dialog.text = DLG_TEXT_Q[8] + NationNameGenitive(sti(pchar.questTemp.NationQuest)) + DLG_TEXT_Q[9];
			link.l1 = DLG_TEXT_Q[10];
			link.l1.go = "PiratesManNot_2";
		break;
		case "PiratesManNot_2":
			dialog.text = DLG_TEXT_Q[11];
			link.l1 = DLG_TEXT_Q[12];
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_0_Waiting");
            AddQuestRecord("Pir_Line_0_Waiting", "1");
			AddQuestUserData("Pir_Line_0_Waiting", "sNation", NationNameAblative(sti(pchar.questTemp.NationQuest)));
		break;

		case "PiratesManNew1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = DLG_TEXT_Q[13];
				link.l1 = DLG_TEXT_Q[14];
				link.l1.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = DLG_TEXT_Q[15];
				link.l1 = DLG_TEXT_Q[16];
				link.l1.go = "exit";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//разговор в таверне Пуэрто Принсипе
		case "Tavern_1":
			LAi_SetSitType(pchar);
			dialog.text = DLG_TEXT_Q[17];
			link.l1 = DLG_TEXT_Q[18];
			link.l1.go = "Tavern_2";
			npchar.lifeDay = 0;
		break;
		case "Tavern_2":
			dialog.text = DLG_TEXT_Q[19];
			link.l1 = DLG_TEXT_Q[20];
			link.l1.go = "Tavern_3";
			link.l2 = DLG_TEXT_Q[21];
			link.l2.go = "Tavern_over";
		break;
		case "Tavern_3":
			dialog.text = DLG_TEXT_Q[22];
			link.l1 = DLG_TEXT_Q[23];
			link.l1.go = "Tavern_4";
		break;
		case "Tavern_4":
			dialog.text = DLG_TEXT_Q[24];
			link.l1 = DLG_TEXT_Q[25];
			link.l1.go = "Tavern_5";
		break;
		case "Tavern_5":
			dialog.text = DLG_TEXT_Q[26];
			link.l1 = DLG_TEXT_Q[27];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			NextDiag.TempNode = "Tavern_again";
            SetQuestHeader("Pir_Line_1_JohnBolton");
            AddQuestRecord("Pir_Line_1_JohnBolton", "1");
			CloseQuestHeader("Pir_Line_0_Waiting");
			pchar.questTemp.piratesLine = "toJohnBolton";
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2", "officer_4", "man", "man", 20, PIRATE, -1, true));
			sld.name = DLG_TEXT_Q[28];
			sld.lastname = DLG_TEXT_Q[29];
			sld.rank = 20;
			sld.city = "PuertoPrincipe";
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto14";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "JohnBolton";
			sld.greeting = "Gr_MiddPirate";
			sld.talker = 8; //начать диалог
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;

		case "Tavern_again":
			dialog.text = DLG_TEXT_Q[30];
			link.l1 = DLG_TEXT_Q[31];
			link.l1.go = "exit";
			NextDiag.TempNode = "Tavern_again";
		break;
		case "Tavern_over":
			dialog.text = DLG_TEXT_Q[32];
			link.l1 = DLG_TEXT_Q[33];
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.piratesLine = "over";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;
		//базар с Джоном Болтоном в порту Пуэрто Принсипе
		case "JohnBolton":
			dialog.text = DLG_TEXT_Q[34] + GetFullName(pchar) + "?";
			link.l1 = DLG_TEXT_Q[35];
			link.l1.go = "JohnBolton_1";
		break;
		case "JohnBolton_1":
			dialog.text = DLG_TEXT_Q[36];
			link.l1 = DLG_TEXT_Q[37];
			link.l1.go = "JohnBolton_2";
		break;
		case "JohnBolton_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1 = "locator";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.location = "PortRoyal_town";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator_group = "quest";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator = "detector_PQ1";
			pchar.quest.PiratesLine_q1_arrest.function = "PiratesLine_q1_arrest";
			NextDiag.TempNode = "JohnBolton_inWay";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "", 5.0);	
		break;
		case "JohnBolton_inWay":
			dialog.text = DLG_TEXT_Q[38];
			link.l1 = DLG_TEXT_Q[39];
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnBolton_inWay";
		break;
		//базар с арестовывающими солдерами
		case "ArrestInPR":
			dialog.text = DLG_TEXT_Q[40];
			link.l1 = DLG_TEXT_Q[41];
			link.l1.go = "ArrestInPR_1";
		break;
		case "ArrestInPR_1":
			dialog.text = DLG_TEXT_Q[42];
			link.l1 = DLG_TEXT_Q[43];
			link.l1.go = "ArrestInPR_2";
		break;
		case "ArrestInPR_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "3");
			chrDisableReloadToLocation = false; 
			bDisableFastReload = false; 
			LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //закроем дом Моргана
			DialogExit();
			AddDialogExitQuestFunction("PiratesLine_q1_toPrison");
		break;
		// -------------------------------------- квест №2 -------------------------------------------------
		case "EdwardLoy":
			dialog.text = DLG_TEXT_Q[44];
			link.l1 = DLG_TEXT_Q[45];
			link.l1.go = "EdwardLoy_1";
			TakeItemFromCharacter(pchar, "BlackLabel");
		break;
		case "EdwardLoy_1":
			dialog.text = DLG_TEXT_Q[46];
			link.l1 = DLG_TEXT_Q[47] + GetFullName(pchar) + ".";
			link.l1.go = "EdwardLoy_2";
		break;
		case "EdwardLoy_2":
			dialog.text = DLG_TEXT_Q[48];
			link.l1 = DLG_TEXT_Q[49];
			link.l1.go = "EdwardLoy_3";
		break;
		case "EdwardLoy_3":
			dialog.text = DLG_TEXT_Q[50];
			link.l1 = DLG_TEXT_Q[51];
			link.l1.go = "EdwardLoy_4";
			GiveItem2Character(pchar, "BlackLabel");
		break;
		case "EdwardLoy_4":
			dialog.text = DLG_TEXT_Q[52];
			link.l1 = DLG_TEXT_Q[53];
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
			QuestSetCurrentNode("Henry Morgan", "PL_Q2_away_1");
			AddQuestRecord("Pir_Line_2_BlackLabel", "3");
		break;
		case "EdwardLoy_again":
			dialog.text = DLG_TEXT_Q[54];
			link.l1 = DLG_TEXT_Q[55];
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
		break;
		// -------------------------------------- квест №3 -------------------------------------------------
		case "CapGoodly":
			dialog.text = DLG_TEXT_Q[56];
			link.l1 = DLG_TEXT_Q[57];
			link.l1.go = "CapGoodly_1";
		break;
		case "CapGoodly_1":
			dialog.text = DLG_TEXT_Q[58];
			link.l1 = DLG_TEXT_Q[59];
			link.l1.go = "CapGoodly_2";
		break;
		case "CapGoodly_2":
			dialog.text = DLG_TEXT_Q[60];
			link.l1 = DLG_TEXT_Q[61];
			link.l1.go = "CapGoodly_3";
		break;
		case "CapGoodly_3":
			dialog.text = DLG_TEXT_Q[62];
			link.l1 = DLG_TEXT_Q[63];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "13");
			pchar.questTemp.piratesLine = "KillLoy_toCumana";
			npchar.lifeDay = 0;
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
			pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";	
		break;
		//Эдвард Лоу в каюте Морского Волка
		case "SeaWolf":
			dialog.text = DLG_TEXT_Q[64];
			link.l1 = DLG_TEXT_Q[65];
			link.l1.go = "SeaWolf_1";
		break;
		case "SeaWolf_1":
			dialog.text = DLG_TEXT_Q[66];
			link.l1 = DLG_TEXT_Q[67];
			link.l1.go = "SeaWolf_2";
		break;
		case "SeaWolf_2":
			dialog.text = DLG_TEXT_Q[68];
			link.l1 = DLG_TEXT_Q[69];
			link.l1.go = "SeaWolf_3";
		break;
		case "SeaWolf_3":
			dialog.text = DLG_TEXT_Q[70];
			link.l1 = DLG_TEXT_Q[71];
			link.l1.go = "SeaWolf_4";
		break;
		case "SeaWolf_4":
			dialog.text = DLG_TEXT_Q[72];
			link.l1 = DLG_TEXT_Q[73];
			link.l1.go = "SeaWolf_5";
		break;
		case "SeaWolf_5":
			dialog.text = DLG_TEXT_Q[74];
			link.l1 = DLG_TEXT_Q[75];
			link.l1.go = "SeaWolf_6";
		break;
		case "SeaWolf_6":
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		// -------------------------------------- квест №5 -------------------------------------------------
		case "PQ5CapGoodly":
			dialog.text = DLG_TEXT_Q[76];
			link.l1 = DLG_TEXT_Q[77];
			link.l1.go = "PQ5CapGoodly_1";
		break;
		case "PQ5CapGoodly_1":
			dialog.text = DLG_TEXT_Q[78];
			link.l1 = DLG_TEXT_Q[79];
			link.l1.go = "PQ5CapGoodly_2";
		break;
		case "PQ5CapGoodly_2":
			dialog.text = DLG_TEXT_Q[80];
			link.l1 = DLG_TEXT_Q[81];
			link.l1.go = "PQ5CapGoodly_3";
		break;
		case "PQ5CapGoodly_3":
			dialog.text = DLG_TEXT_Q[82];
			link.l1 = DLG_TEXT_Q[83];
			link.l1.go = "PQ5CapGoodly_4";
		break;
		case "PQ5CapGoodly_4":
			dialog.text = DLG_TEXT_Q[84]+
				DLG_TEXT_Q[85];
			link.l1 = DLG_TEXT_Q[86];
			link.l1.go = "PQ5CapGoodly_5";
		break;
		case "PQ5CapGoodly_5":
			dialog.text = DLG_TEXT_Q[87];
			link.l1 = DLG_TEXT_Q[88];
			link.l1.go = "PQ5CapGoodly_6";
		break;
		case "PQ5CapGoodly_6":
			dialog.text = DLG_TEXT_Q[89];
			link.l1 = DLG_TEXT_Q[90];
			link.l1.go = "PQ5CapGoodly_7";
		break;
		case "PQ5CapGoodly_7":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "PL5Hunter_toVillemstad";
			SetQuestHeader("Pir_Line_5_Hunter");
			AddQuestRecord("Pir_Line_5_Hunter", "1");
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "houseS1", "none", "", "", "", -1.0);
			DialogExit();
		break;
		//Эйвори вместо ГГ
		case "PQ5Hero":
			dialog.text = DLG_TEXT_Q[91];
			link.l1 = DLG_TEXT_Q[92];
			link.l1.go = "PQ5Hero_1";
		break;
		case "PQ5Hero_1":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero");
		break;
		//Эйвори в доме на Бермудах
		case "PQ5Aivory":
			dialog.text = DLG_TEXT_Q[93];
			link.l1 = DLG_TEXT_Q[94];
			link.l1.go = "PQ5Aivory_1";
		break;
		case "PQ5Aivory_1":
			dialog.text = DLG_TEXT_Q[95];
			link.l1 = DLG_TEXT_Q[96];
			link.l1.go = "PQ5Aivory_2";
		break;
		case "PQ5Aivory_2":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero2");
		break;
		//Гудли в таверне Порт Рояля
		case "PQ5CapGoodlyEnd":
			dialog.text = DLG_TEXT_Q[97] + GetFullName(pchar) + DLG_TEXT_Q[98];
			link.l1 = DLG_TEXT_Q[99];
			link.l1.go = "PQ5CapGoodlyEnd_1";
		break;
		case "PQ5CapGoodlyEnd_1":
			dialog.text = DLG_TEXT_Q[100];
			link.l1 = DLG_TEXT_Q[101];
			link.l1.go = "PQ5CapGoodlyEnd_2";
			AddMoneyToCharacter(pchar, 15000);
		break;
		case "PQ5CapGoodlyEnd_2":
			dialog.text = DLG_TEXT_Q[102];
			link.l1 = DLG_TEXT_Q[103];
			link.l1.go = "PQ5CapGoodlyEnd_3";
		break;
		case "PQ5CapGoodlyEnd_3":
			dialog.text = DLG_TEXT_Q[104];
			link.l1 = DLG_TEXT_Q[105];
			link.l1.go = "PQ5CapGoodlyEnd_4";
		break;
		case "PQ5CapGoodlyEnd_4":
			dialog.text = DLG_TEXT_Q[106];
			link.l1 = DLG_TEXT_Q[107];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "12");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			QuestSetCurrentNode("Henry Morgan", "PL_Q5_begin");
		break;
		// -------------------------------------- квест №6 -------------------------------------------------
		case "JohnLids":
			dialog.text = DLG_TEXT_Q[108];
			link.l1 = DLG_TEXT_Q[109];
			link.l1.go = "JohnLids_1";
		break;
		case "JohnLids_1":
			dialog.text = DLG_TEXT_Q[110];
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "JohnLids_2";
		break;
		case "JohnLids_2":
			dialog.text = DLG_TEXT_Q[111];
			link.l1 = DLG_TEXT_Q[112] + GetFullName(pchar) +  DLG_TEXT_Q[113];
			link.l1.go = "JohnLids_3";
		break;
		case "JohnLids_3":
			dialog.text = DLG_TEXT_Q[114] + GetFullName(pchar) + DLG_TEXT_Q[115]+
				DLG_TEXT_Q[116];
			link.l1 = DLG_TEXT_Q[117];
			link.l1.go = "JohnLids_4";
		break;
		case "JohnLids_4":
			dialog.text = DLG_TEXT_Q[118];
			link.l1 = DLG_TEXT_Q[119];
			link.l1.go = "JohnLids_5";
		break;
		case "JohnLids_5":
			dialog.text = DLG_TEXT_Q[120]+
				DLG_TEXT_Q[121];
			link.l1 = DLG_TEXT_Q[122];
			link.l1.go = "JohnLids_6";
		break;
		case "JohnLids_6":
			dialog.text = DLG_TEXT_Q[123];
			link.l1 = DLG_TEXT_Q[124];
			link.l1.go = "JohnLids_7";
		break;
		case "JohnLids_7":
			dialog.text = DLG_TEXT_Q[125];
			link.l1 = DLG_TEXT_Q[126];
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "3");
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1 = "location";
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1.location = "Shore7";
			Pchar.quest.PQ6_ShoreBattle.function = "PQ6_ShoreBattle";
		break;
		case "JohnLids_again":
			dialog.text = DLG_TEXT_Q[127];
			link.l1 = DLG_TEXT_Q[128];
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
		break;
		//двойник ГГ
		case "QuestPirateHead":
			dialog.text = DLG_TEXT_Q[129] + GetFullName(pchar) + DLG_TEXT_Q[130];
			link.l1 = DLG_TEXT_Q[131];
			link.l1.go = "QuestPirateHead_1";
		break;
		case "QuestPirateHead_1":
			dialog.text = DLG_TEXT_Q[132];
			link.l1 = DLG_TEXT_Q[133];
			link.l1.go = "QuestPirateHead_2";
		break;
		case "QuestPirateHead_2":
			dialog.text = DLG_TEXT_Q[134];
			link.l1 = DLG_TEXT_Q[135];
			link.l1.go = "QuestPirateHead_3";
		break;
		case "QuestPirateHead_3":
			dialog.text = DLG_TEXT_Q[136];
			link.l1 = DLG_TEXT_Q[137];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PQ6_JungleBattle");
		break;
		// -------------------------------------- квест №7 -------------------------------------------------
		case "FriendLinney":
			dialog.text = DLG_TEXT_Q[138];
			link.l1 = DLG_TEXT_Q[139];
			link.l1.go = "FriendLinney_1";
		break;
		case "FriendLinney_1":
			dialog.text = DLG_TEXT_Q[140];
			link.l1 = DLG_TEXT_Q[141] + GetFullName(pchar) + DLG_TEXT_Q[142];
			link.l1.go = "FriendLinney_2";
		break;
		case "FriendLinney_2":
			dialog.text = DLG_TEXT_Q[143]+
				DLG_TEXT_Q[144];
			link.l1 = DLG_TEXT_Q[145];
			link.l1.go = "FriendLinney_3";
		break;
		case "FriendLinney_3":
			dialog.text = DLG_TEXT_Q[146];
			link.l1 = DLG_TEXT_Q[147];
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			AddQuestRecord("Pir_Line_7_Soukins", "5");
		break;
		case "FriendLinney_again":
			dialog.text = DLG_TEXT_Q[148];
			link.l1 = DLG_TEXT_Q[149];
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
		break;
		//кэп, продавшие шлюп Ласточку
		case "LeonCapitain":
			dialog.text = DLG_TEXT_Q[150];
			link.l1 = DLG_TEXT_Q[151];
			link.l1.go = "LeonCapitain_1";
		break;
		case "LeonCapitain_1":
			dialog.text = DLG_TEXT_Q[152];
			link.l1 = DLG_TEXT_Q[153];
			link.l1.go = "LeonCapitain_2";
		break;
		case "LeonCapitain_2":
			dialog.text = DLG_TEXT_Q[154];
			link.l1 = DLG_TEXT_Q[155];
			link.l1.go = "LeonCapitain_3";
		break;
		case "LeonCapitain_3":
			dialog.text = DLG_TEXT_Q[156];
			link.l1 = DLG_TEXT_Q[157];
			link.l1.go = "LeonCapitain_4";
		break;
		case "LeonCapitain_4":
			dialog.text = DLG_TEXT_Q[158];
			link.l1 = DLG_TEXT_Q[159];
			link.l1.go = "LeonCapitain_5";
		break;
		case "LeonCapitain_5":
			dialog.text = DLG_TEXT_Q[160];
			link.l1 = DLG_TEXT_Q[161];
			link.l1.go = "LeonCapitain_6";
		break;
		case "LeonCapitain_6":
			Map_ReleaseQuestEncounter("LeonCapitain");
			pchar.questTemp.piratesLine = "Soukins_toMorgan";
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_afterLeon");
			AddQuestRecord("Pir_Line_7_Soukins", "7");
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//поход на Панаму, пираты в городе
		case "PQ8_PirInPan":
			dialog.text = DLG_TEXT_Q[162] + pchar.name + DLG_TEXT_Q[163];
			link.l1 = DLG_TEXT_Q[164];
			link.l1.go = "PQ8_PirInPan_1";
		break;
		case "PQ8_PirInPan_1":
			dialog.text = DLG_TEXT_Q[165];
			link.l1 = DLG_TEXT_Q[166];
			link.l1.go = "exit";
		break;
		case "PQ8_RsPirInPan":
			dialog.text = DLG_TEXT_Q[167];
			link.l1 = DLG_TEXT_Q[168];
			link.l1.go = "PQ8_RsPirInPan_1";
		break;
		case "PQ8_RsPirInPan_1":
			dialog.text = DLG_TEXT_Q[169];
			link.l1 = DLG_TEXT_Q[170];
			link.l1.go = "exit";
		break;
		case "PQ8_MPirInPan":
			dialog.text = DLG_TEXT_Q[171];
			link.l1 = DLG_TEXT_Q[172];
			link.l1.go = "PQ8_MPirInPan_1";
		break;
		case "PQ8_MPirInPan_1":
			dialog.text = DLG_TEXT_Q[173];
			link.l1 = DLG_TEXT_Q[174];
			link.l1.go = "exit";
		break;
		//фантом мэра Панамы
		case "PQ8_Mayor":
			dialog.text = DLG_TEXT_Q[175];
			link.l1 = DLG_TEXT_Q[176];
			link.l1.go = "PQ8_Mayor_1";
		break;
		case "PQ8_Mayor_1":
			dialog.text = DLG_TEXT_Q[177];
			link.l1 = DLG_TEXT_Q[178];
			link.l1.go = "PQ8_Mayor_2";
		break;
		case "PQ8_Mayor_2":
			dialog.text = DLG_TEXT_Q[179];
			link.l1 = DLG_TEXT_Q[180];
			link.l1.go = "PQ8_Mayor_3";
		break;
		case "PQ8_Mayor_3":
			dialog.text = DLG_TEXT_Q[181];
			link.l1 = DLG_TEXT_Q[182];
			link.l1.go = "PQ8_Mayor_4";
		break;
		case "PQ8_Mayor_4":
			dialog.text = DLG_TEXT_Q[183];
			link.l1 = DLG_TEXT_Q[184];
			link.l1.go = "PQ8_Mayor_5";
		break;
		case "PQ8_Mayor_5":
			dialog.text = DLG_TEXT_Q[185]+
				DLG_TEXT_Q[186];
			link.l1 = DLG_TEXT_Q[187];
			link.l1.go = "PQ8_Mayor_6";
		break;
		case "PQ8_Mayor_6":
			dialog.text = DLG_TEXT_Q[188];
			link.l1 = DLG_TEXT_Q[189];
			link.l1.go = "PQ8_Mayor_7";
		break;
		case "PQ8_Mayor_7":
			dialog.text = DLG_TEXT_Q[190];
			link.l1 = DLG_TEXT_Q[191];
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "11");
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1 = "location";
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_MorganInPanama_1.function = "PQ8_MorganInPanama_1";
		break;
		//обманутые пиратусы в Панаме
		case "PQ8_FackMorgan":
			dialog.text = LinkRandPhrase(DLG_TEXT_Q[192], DLG_TEXT_Q[193], DLG_TEXT_Q[194]);
			link.l1 = LinkRandPhrase(DLG_TEXT_Q[195], DLG_TEXT_Q[196], DLG_TEXT_Q[197]);
			link.l1.go = "exit";
		break;
		первый подбегающий пират
		case "PL_Q8_QFackMorgan":
			dialog.text = DLG_TEXT_Q[198];
			link.l1 = DLG_TEXT_Q[199];
			link.l1.go = "PL_Q8_QFackMorgan_1";
		break;
		case "PL_Q8_QFackMorgan_1":
			dialog.text = DLG_TEXT_Q[200];
			link.l1 = DLG_TEXT_Q[201];
			link.l1.go = "PL_Q8_QFackMorgan_2";
		break;
		case "PL_Q8_QFackMorgan_2":
			dialog.text = DLG_TEXT_Q[202];
			link.l1 = DLG_TEXT_Q[203];
			link.l1.go = "PL_Q8_QFackMorgan_3";
		break;
		case "PL_Q8_QFackMorgan_3":
			dialog.text = DLG_TEXT_Q[204];
			link.l1 = DLG_TEXT_Q[205];
			link.l1.go = "PL_Q8_QFackMorgan_4";
		break;
		case "PL_Q8_QFackMorgan_4":
			dialog.text = DLG_TEXT_Q[206];
			link.l1 = DLG_TEXT_Q[207];
			link.l1.go = "PL_Q8_QFackMorgan_5";
		break;
		case "PL_Q8_QFackMorgan_5":
			dialog.text = DLG_TEXT_Q[208];
			link.l1 = DLG_TEXT_Q[209];
			link.l1.go = "PL_Q8_QFackMorgan_6";
		break;
		case "PL_Q8_QFackMorgan_6":
			dialog.text = DLG_TEXT_Q[210];
			link.l1 = DLG_TEXT_Q[211];
			link.l1.go = "PL_Q8_QFackMorgan_7";
		break;
		case "PL_Q8_QFackMorgan_7":
			dialog.text = DLG_TEXT_Q[212];
			link.l1 = DLG_TEXT_Q[213];
			link.l1.go = "PL_Q8_QFackMorgan_8";
		break;
		case "PL_Q8_QFackMorgan_8":
			dialog.text = DLG_TEXT_Q[214];
			link.l1 = DLG_TEXT_Q[215];
			link.l1.go = "PL_Q8_QFackMorgan_9";
		break;
		case "PL_Q8_QFackMorgan_9":
			dialog.text = DLG_TEXT_Q[216];
			link.l1 = DLG_TEXT_Q[217];
			link.l1.go = "PL_Q8_QFackMorgan_10";
		break;
		case "PL_Q8_QFackMorgan_10":
			dialog.text = DLG_TEXT_Q[218];
			link.l1 = DLG_TEXT_Q[219];
			link.l1.go = "PL_Q8_QFackMorgan_11";
		break;
		case "PL_Q8_QFackMorgan_11":
			chrDisableReloadToLocation = false;	
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_houseS1")], true);
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30);
			pchar.questTemp.piratesLine = "Panama_backToShip";
			AddQuestRecord("Pir_Line_8_Panama", "13");
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1.location = "Panama_jungle_04";
			Pchar.quest.PL_Q8_backFight_1.function = "PL_Q8_backFight_1";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
