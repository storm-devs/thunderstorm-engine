#include "TEXT\DIALOGS\MayorQuests_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[0] + GetFullName(npchar) + DLG_TEXT_BASE[1],
				DLG_TEXT_BASE[2] + GetFullName(npchar) + DLG_TEXT_BASE[3],
				DLG_TEXT_BASE[4] + GetFullName(npchar) + DLG_TEXT_BASE[5]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[6] + GetFullName(npchar) + DLG_TEXT_BASE[7] + sTemp + DLG_TEXT_BASE[8],
				DLG_TEXT_BASE[9] + sTemp + " ?!", 
				DLG_TEXT_BASE[10] + GetFullName(npchar) + DLG_TEXT_BASE[11] + sTemp + DLG_TEXT_BASE[12]);
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[13],
				DLG_TEXT_BASE[14],
				DLG_TEXT_BASE[15]);
			Link.l1 = LinkRandPhrase(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17], DLG_TEXT_BASE[18]);
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21]);
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[22],
				DLG_TEXT_BASE[23],
				DLG_TEXT_BASE[24]);
			Link.l1 = DLG_TEXT_BASE[25];
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашел, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- поиски лазутчика в коммонах ----------------------
		case "SeekSpy_house":
			chrDisableReloadToLocation = false;
			dialog.text = DLG_TEXT_BASE[26] + GetAddress_Form(PChar) + "?";
			Link.l1 = DLG_TEXT_BASE[27];
			Link.l1.go = "SeekSpy_1";	
		break;
		case "SeekSpy_1":
			dialog.text = DLG_TEXT_BASE[28];
			Link.l1 = DLG_TEXT_BASE[29];
			Link.l1.go = "SeekSpy_2";	
		break;
		case "SeekSpy_2":
			dialog.text = DLG_TEXT_BASE[30];
			Link.l1 = DLG_TEXT_BASE[31];
			Link.l1.go = "SeekSpy_3";	
		break;
		case "SeekSpy_3":
			dialog.text = DLG_TEXT_BASE[32];
			Link.l1 = DLG_TEXT_BASE[33];
			Link.l1.go = "SeekSpy_fight";	
		break;
		case "SeekSpy_fight":
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SeekSpy_Afrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- поиски лазутчика на улице ----------------------
		case "SeekSpy_street":
			Diag.TempNode = "SeekSpy_street";
            dialog.Text = NPCharRepPhrase(npchar,
		            PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[34]+GetFullName(Pchar)
                    +DLG_TEXT_BASE[35], DLG_TEXT_BASE[36]
                    + Pchar.name, DLG_TEXT_BASE[37]
                        +GetFullName(Pchar))
                                    +LinkRandPhrase(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39], DLG_TEXT_BASE[40])
                                    +LinkRandPhrase(DLG_TEXT_BASE[41], DLG_TEXT_BASE[42], DLG_TEXT_BASE[43]),
                                    LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[44], DLG_TEXT_BASE[45]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[46])+GetFullName(Pchar)
                                    +LinkRandPhrase(DLG_TEXT_BASE[47], DLG_TEXT_BASE[48], DLG_TEXT_BASE[49])
                                    ),
                                    
                    PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[52])
                                    +GetFullName(Pchar)
                                    +LinkRandPhrase(DLG_TEXT_BASE[53]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[54])+DLG_TEXT_BASE[55],
                                                        DLG_TEXT_BASE[56]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[57])+DLG_TEXT_BASE[58], DLG_TEXT_BASE[59])
                                    +LinkRandPhrase(DLG_TEXT_BASE[60], DLG_TEXT_BASE[61], DLG_TEXT_BASE[62]+NPCharSexPhrase(NPChar, DLG_TEXT_BASE[63], DLG_TEXT_BASE[64])),
                                    LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[65] + GetFullName(Pchar) + DLG_TEXT_BASE[66],
                                    DLG_TEXT_BASE[67] + GetFullName(Pchar) + DLG_TEXT_BASE[68],
                                    DLG_TEXT_BASE[69] + GetAddress_Form(NPChar) + " " + Pchar.lastname + DLG_TEXT_BASE[70]))
                                    );                  
                        
	   		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[71], DLG_TEXT_BASE[72]),
                                    RandPhraseSimple(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74]));
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[75], DLG_TEXT_BASE[76]);
			link.l2.go = "exit";//(перессылка в файл города)
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[77] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					DLG_TEXT_BASE[78] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[79], 
					DLG_TEXT_BASE[80] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[81]), 
					LinkRandPhrase(DLG_TEXT_BASE[82] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					DLG_TEXT_BASE[83] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[84], 
					DLG_TEXT_BASE[85] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[86]));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			link.l5 = PCharRepPhrase(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]);
			link.l5.go = "new question";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[89]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[90])+DLG_TEXT_BASE[91], DLG_TEXT_BASE[92], DLG_TEXT_BASE[93] + PChar.name + "?"),
                                        LinkRandPhrase(DLG_TEXT_BASE[94], DLG_TEXT_BASE[95]+PChar.name+DLG_TEXT_BASE[96], DLG_TEXT_BASE[97])),
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[98]+ GetAddress_Form(NPChar) + "?", DLG_TEXT_BASE[99], DLG_TEXT_BASE[100]),
                                        LinkRandPhrase(DLG_TEXT_BASE[101]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[102])+DLG_TEXT_BASE[103] + GetAddress_Form(NPChar) + " " + PChar.lastname + DLG_TEXT_BASE[104],
                                                        DLG_TEXT_BASE[105] + GetAddress_Form(NPChar) + "?",
                                                        DLG_TEXT_BASE[106]))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase (DLG_TEXT_BASE[107],
                                    DLG_TEXT_BASE[108],
                                    DLG_TEXT_BASE[109]);
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[110], DLG_TEXT_BASE[111], DLG_TEXT_BASE[112]);
			link.l2.go = "exit";  //(перессылка в файл города)
			link.l3 = DLG_TEXT_BASE[113];
			link.l3.go = "colony";
            link.l4 = RandPhraseSimple(DLG_TEXT_BASE[114], DLG_TEXT_BASE[115]);
			link.l4.go = "exit";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[116], DLG_TEXT_BASE[117]),
                                        RandPhraseSimple(DLG_TEXT_BASE[118], DLG_TEXT_BASE[119]));
			link.l5.go = "exit";
		break;
		
		case "colony":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[120],
                           DLG_TEXT_BASE[121], DLG_TEXT_BASE[122]);
            switch(Rand(1))
			{
				case 0:
					link.l1 = DLG_TEXT_BASE[123];
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = DLG_TEXT_BASE[124];
					link.l1.go = "fort";
				break;
            }
			link.l2 = DLG_TEXT_BASE[125];
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = DLG_TEXT_BASE[126];
			link.l1 = DLG_TEXT_BASE[127];
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = DLG_TEXT_BASE[128];
			link.l1 = DLG_TEXT_BASE[129];
		    link.l1.go = "exit";
		break;
		//==> поймал засланца
		case "SitySpy":
			dialog.text = DLG_TEXT_BASE[130];
			link.l1 = DLG_TEXT_BASE[131];
		    link.l1.go = "SitySpy_1";
		break;
		case "SitySpy_1":
			dialog.text = DLG_TEXT_BASE[132],
			link.l1 = DLG_TEXT_BASE[133] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!";
			link.l1.go = "SitySpy_3";
		break;
		case "SitySpy_3":
            dialog.text = DLG_TEXT_BASE[134];
			link.l1 = DLG_TEXT_BASE[135];
		    link.l1.go = "SitySpy_4";
		break;
		case "SitySpy_4":
            dialog.text = DLG_TEXT_BASE[136];
			link.l1 = DLG_TEXT_BASE[137];
		    link.l1.go = "SitySpy_5";
		break;
		case "SitySpy_5":
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			AddQuestRecord("MayorsQuestsList", "5");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// слухи
			AddSimpleRumour(RandPhraseSimple(DLG_TEXT_BASE[138] + sTemp + DLG_TEXT_BASE[139] + GetMainCharacterNameGen() + DLG_TEXT_BASE[140], 
				DLG_TEXT_BASE[141] + GetMainCharacterNameGen() + DLG_TEXT_BASE[142]), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);			
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			pchar.GenQuest.SeekSpy = "FoundSpy"; //флаг нашел шпиона
			DeleteAttribute(pchar, "GenQuest.SeekSpy.City"); //не опрашивать более в городе
			LocatorReloadEnterDisable(pchar.location, "gate_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload1_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//----------------- найти и уничтожить пирата в море ----------------------
		case "DestroyPirate_Abordage": //абордаж
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate.wasTalkInDeck"))
			{
				dialog.text = DLG_TEXT_BASE[143];
				Link.l1 = DLG_TEXT_BASE[144];
				Link.l1.go = "DP_Abordage_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[145];
				Link.l1 = DLG_TEXT_BASE[146] + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + DLG_TEXT_BASE[147];
				Link.l1.go = "DP_Abordage_2";
			}
		break;
		case "DP_Abordage_1":
			dialog.text = DLG_TEXT_BASE[148];
			Link.l1 = DLG_TEXT_BASE[149];
			Link.l1.go = "DP_Abordage_fight";	
		break;
		case "DP_Abordage_2":
			dialog.text = DLG_TEXT_BASE[150];
			Link.l1 = DLG_TEXT_BASE[151];
			Link.l1.go = "DP_Abordage_fight";	
		break;
 		case "DP_Abordage_fight":
			LAi_SetCurHP(npchar, rand(sti(npchar.chr_ai.hp_max)) + 5);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
		break;
		//разговор на палубе
		case "DestroyPirate_Deck":
			pchar.GenQuest.DestroyPirate.wasTalkInDeck = true; //флаг на палубный базар
			dialog.text = DLG_TEXT_BASE[152];
			Link.l1 = DLG_TEXT_BASE[153] + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + DLG_TEXT_BASE[154];
			Link.l1.go = "DestroyPirate_1";	
		break;
		case "DestroyPirate_1":
			dialog.text = DLG_TEXT_BASE[155];
			Link.l1 = DLG_TEXT_BASE[156];
			Link.l1.go = "DestroyPirate_2";	
		break;
		case "DestroyPirate_2":
			dialog.text = DLG_TEXT_BASE[157];
			Link.l1 = DLG_TEXT_BASE[158];
			Link.l1.go = "DestroyPirate_3";	
		break;
		case "DestroyPirate_3":
			dialog.text = DLG_TEXT_BASE[159];
			Link.l1 = DLG_TEXT_BASE[160];
			Link.l1.go = "DestroyPirate_4";	
		break;
		case "DestroyPirate_4":
			int lngFileID;
			if (pchar.GenQuest.DestroyPirate.fortPlace == "1")
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = DLG_TEXT_BASE[161] + sTemp + DLG_TEXT_BASE[162] + XI_ConvertString("Colony"+sld.city+"Dat") + 
					DLG_TEXT_BASE[163];
				Link.l1 = DLG_TEXT_BASE[164];
				Link.l1.go = "DestroyPirate_5";					
				break;
			}
			if (GetCompanionQuantity(pchar) == 1 && makeint(pchar.GenQuest.DestroyPirate.shipState) > 1)
			{
				dialog.text = DLG_TEXT_BASE[165];
				Link.l1 = DLG_TEXT_BASE[166];
				Link.l1.go = "DP_WithoutFight";	
				Link.l2 = DLG_TEXT_BASE[167];
				Link.l2.go = "DP_FightInDeck";	
			}
			else
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = DLG_TEXT_BASE[168] + sTemp + DLG_TEXT_BASE[169] + XI_ConvertString("Colony"+sld.city+"Dat") + 
					DLG_TEXT_BASE[170];
				Link.l1 = DLG_TEXT_BASE[171];
				Link.l1.go = "DestroyPirate_5";	
			}
		break;
		case "DestroyPirate_5":
			dialog.text = DLG_TEXT_BASE[172];
			Link.l1 = DLG_TEXT_BASE[173];
			Link.l1.go = "DP_toShore";	
			Link.l2 = DLG_TEXT_BASE[174];
			Link.l2.go = "DP_FightInDeck";	
		break;

		case "DP_toShore":
			dialog.text = DLG_TEXT_BASE[175];
			Link.l1 = DLG_TEXT_BASE[176];
			Link.l1.go = "exit";
			AddDialogExitQuest("DestroyPirate_toShore");
		break;

		case "DP_WithoutFight":
			dialog.text = DLG_TEXT_BASE[177];
			Link.l1 = DLG_TEXT_BASE[178];
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
			AddDialogExitQuest("DestroyPirate_WithoutFight");
		break;
		case "DP_WithoutFight_again":
			dialog.text = DLG_TEXT_BASE[179];
			Link.l1 = DLG_TEXT_BASE[180];
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
		break;

		case "DP_FightInDeck":
			dialog.text = DLG_TEXT_BASE[181];
			Link.l1 = DLG_TEXT_BASE[182];
			Link.l1.go = "DP_FightInDeck_1";
		break;
		case "DP_FightInDeck_1":
			pchar.GenQuest.DestroyPirate.FightAfterDeck = true; //после резни на палубе - драка в море
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "DestroyPirate_FightInDeck", 3.5);
			DialogExit();			
		break;


	}
}
