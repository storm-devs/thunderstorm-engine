#include "TEXT\DIALOGS\Brothel\Tortuga_Brothel.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;     
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[0], DLG_TEXT_BR[1]), DLG_TEXT_BR[2], DLG_TEXT_BR[3],
                          DLG_TEXT_BR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_BR[5], DLG_TEXT_BR[6]), DLG_TEXT_BR[7],
                      DLG_TEXT_BR[8], DLG_TEXT_BR[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> Голл. №3, узнаем о Пеьере Пикардийце.
            if (pchar.questTemp.State == "WormEnglPlans_WormPicarder")
            {
                link.l1 = DLG_TEXT_BR[10];
                link.l1.go = "Step_H3_1";
			}
            // ==> квест Аззи.
            if (CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = DLG_TEXT_BR[11];
    			Link.l1 = DLG_TEXT_BR[12];
    			Link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy" && !CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
            {
                dialog.text = NPCStringReactionRepeat(DLG_TEXT_BR[13], DLG_TEXT_BR[14], DLG_TEXT_BR[15], DLG_TEXT_BR[16], "block", 0, npchar, Dialog.CurrentNode);
    			Link.l1 = HeroStringReactionRepeat(DLG_TEXT_BR[17], DLG_TEXT_BR[18], DLG_TEXT_BR[19], DLG_TEXT_BR[20], npchar, Dialog.CurrentNode);
    			Link.l1.go = DialogGoNodeRepeat("Step_15", "none", "none", "none", npchar, Dialog.CurrentNode);
            }
            if (pchar.questTemp.Azzy == "DestrContract")
            {
                dialog.text = DLG_TEXT_BR[21];
    			Link.l1 = DLG_TEXT_BR[22];
    			Link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Azzy == "2DestrContract")
            {
                dialog.text = DLG_TEXT_BR[23];
    			Link.l1 = DLG_TEXT_BR[24];
    			Link.l1.go = "Step_20";
            }
			//жемчужный генератор Шарпа
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = DLG_TEXT_BR[25] + npchar.name + DLG_TEXT_BR[26];
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
            // <== Проверяем поле состояния квестов.
		break;
		//==>Голландская линейка, квест №3.
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BR[27], DLG_TEXT_BR[28], DLG_TEXT_BR[29], DLG_TEXT_BR[30], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BR[31], DLG_TEXT_BR[32], DLG_TEXT_BR[33], DLG_TEXT_BR[34], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = DLG_TEXT_BR[35];
			link.l1 = DLG_TEXT_BR[36];
			link.l1.go = "exit";
            pchar.questTemp.Talks.Brothel = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "11");
        break;
		//==> Квест Аззи
        case "Step_1":
			dialog.text = DLG_TEXT_BR[37];
			Link.l1 = DLG_TEXT_BR[38] + GetFullName(pchar) + ".";
			Link.l1.go = "Step_2";
		break;
        case "Step_2":
			dialog.text = DLG_TEXT_BR[39];
			Link.l1 = DLG_TEXT_BR[40];
			Link.l1.go = "Step_3";
		break;
        case "Step_3":
			dialog.text = DLG_TEXT_BR[41];
			Link.l1 = DLG_TEXT_BR[42];
			Link.l1.go = "Step_4";
		break;
        case "Step_4":
			dialog.text = DLG_TEXT_BR[43];
			Link.l1 = DLG_TEXT_BR[44];
			Link.l1.go = "Step_5";
		break;
        case "Step_5":
			dialog.text = DLG_TEXT_BR[45]+
                     DLG_TEXT_BR[46];
			Link.l1 = DLG_TEXT_BR[47];
			Link.l1.go = "Step_6";
		break;
        case "Step_6":
			dialog.text = DLG_TEXT_BR[48]+
                     DLG_TEXT_BR[49]+
                     DLG_TEXT_BR[50];
			Link.l1 = DLG_TEXT_BR[51];
			Link.l1.go = "Step_7";
		break;
        case "Step_7":
			dialog.text = DLG_TEXT_BR[52];
			Link.l1 = DLG_TEXT_BR[53];
			Link.l1.go = "Step_8";
		break;
        case "Step_8":
			dialog.text = DLG_TEXT_BR[54]+
                     DLG_TEXT_BR[55]+
                     DLG_TEXT_BR[56]+
                     DLG_TEXT_BR[57]+
                     DLG_TEXT_BR[58];
			Link.l1 = DLG_TEXT_BR[59];
			Link.l1.go = "Step_9";
		break;
        case "Step_9":
			dialog.text = DLG_TEXT_BR[60];
            Link.l1 = DLG_TEXT_BR[61];
			Link.l1.go = "Strength";
            Link.l2 = DLG_TEXT_BR[62];
			Link.l2.go = "Perception";
            Link.l3 = DLG_TEXT_BR[63];
			Link.l3.go = "Agility";
            Link.l4 = DLG_TEXT_BR[64];
			Link.l4.go = "Charisma";
            Link.l5 = DLG_TEXT_BR[65];
			Link.l5.go = "Intellect";
			Link.l6 = DLG_TEXT_BR[66];
			Link.l6.go = "Endurance";
            Link.l7 = DLG_TEXT_BR[67];
			Link.l7.go = "Luck";
		break;
        case "Strength":
			dialog.text =  DLG_TEXT_BR[68];
			Link.l1 = DLG_TEXT_BR[69];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
		break;
        case "Perception":
			dialog.text =  DLG_TEXT_BR[70];
			Link.l1 = DLG_TEXT_BR[71];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_P, 1);
			}
		break;
        case "Endurance":
			dialog.text =  DLG_TEXT_BR[72];
			Link.l1 = DLG_TEXT_BR[73];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
		break;
        case "Charisma":
			dialog.text =  DLG_TEXT_BR[74];
			Link.l1 = DLG_TEXT_BR[75];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_C, 1);
			}
		break;
        case "Intellect":
			dialog.text =  DLG_TEXT_BR[76];
			Link.l1 = DLG_TEXT_BR[77];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_I, 1);
			}
		break;
        case "Agility":
			dialog.text =  DLG_TEXT_BR[78];
			Link.l1 = DLG_TEXT_BR[79];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
		break;
        case "Luck":
			dialog.text =  DLG_TEXT_BR[80];
			Link.l1 = DLG_TEXT_BR[81];
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) == SPECIAL_MAX)
			{
                Link.l1.go = "NotPosblAdd";
			}
			else
			{
			    AddSPECIALValue(pchar, SPECIAL_L, 1);
			}
		break;
        case "Step_10":
			dialog.text =  DLG_TEXT_BR[82];
			Link.l1 = DLG_TEXT_BR[83];
			Link.l1.go = "Step_11";
		break;
        case "Step_11":
			dialog.text =  DLG_TEXT_BR[84];
			Link.l1 = DLG_TEXT_BR[85];
			Link.l1.go = "Step_12";
		break;
        case "Step_12":
			dialog.text =  DLG_TEXT_BR[86];
			Link.l1 = DLG_TEXT_BR[87];
			Link.l1.go = "Step_13";
		break;
        case "Step_13":
			dialog.text =  DLG_TEXT_BR[88];
			Link.l1 = DLG_TEXT_BR[89];
			Link.l1.go = "exit";
			AddDialogExitQuest("Azzy_PlusSkill");
		break;
        case "NotPosblAdd":
			dialog.text =  DLG_TEXT_BR[90];
			Link.l1 = DLG_TEXT_BR[91];
			Link.l1.go = "Step_9";
		break;
        case "Step_15":
			dialog.text =  DLG_TEXT_BR[92];
			Link.l1 = DLG_TEXT_BR[93];
			Link.l1.go = "Step_16";
		break;
        case "Step_16":
			dialog.text =  DLG_TEXT_BR[94];
			Link.l1 = DLG_TEXT_BR[95];
			Link.l1.go = "exit";
		break;
        case "Step_17":
			dialog.text =  DLG_TEXT_BR[96];
			Link.l1 = DLG_TEXT_BR[97];
			Link.l1.go = "Step_18";
		break;
        case "Step_18":
			dialog.text =  DLG_TEXT_BR[98];
			Link.l1 = DLG_TEXT_BR[99];
			Link.l1.go = "Step_19";
		break;
        case "Step_19":
			dialog.text =  DLG_TEXT_BR[100];
			Link.l1 = DLG_TEXT_BR[101];
			Link.l1.go = "Step_20";
		break;
        case "Step_20":
			dialog.text =  DLG_TEXT_BR[102];
            if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
            {
    			Link.l1 = DLG_TEXT_BR[103];
    			Link.l1.go = "Step_22";
            }
            else
            {
    			Link.l1 = DLG_TEXT_BR[104];
    			Link.l1.go = "Step_21";
            }
		break;
        case "Step_21":
			dialog.text =  DLG_TEXT_BR[105];
			Link.l1 = DLG_TEXT_BR[106];
			Link.l1.go = "exit";
			pchar.questTemp.Azzy = "2DestrContract";
		break;
        case "Step_22":
			dialog.text =  DLG_TEXT_BR[107];
			Link.l1 = DLG_TEXT_BR[108];
			Link.l1.go = "Step_23";
		break;
        case "Step_23":
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            pchar.questTemp.Azzy = "3DestrContract";
            DeleteAttribute(pchar, "questTemp.Azzy.Oliver")
            ChangeCharacterAddressGroup(characterFromId("Azzy"), pchar.location, "goto", "goto2");
            DoQuestCheckDelay("Azzy_IsFree", 2.0);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;
		// капитан Шарп, грабеж жемчужных промыслов
		case "SharpPearl_1":
			if (rand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = DLG_TEXT_BR[109] + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = DLG_TEXT_BR[110] + npchar.name + DLG_TEXT_BR[111];
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", DLG_TEXT_BR[112] + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Dat"));
					}
					//запускаем энкаунтер Шарпа на карте
					group_DeleteGroup("Sharp_Group");
					sld = characterFromId("Sharp");
					string sGroup = "Sharp_Group";
					Group_FindOrCreateGroup(sGroup);
					Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
					Group_LockTask(sGroup);
					Group_AddCharacter(sGroup, sld.id);
					Group_SetGroupCommander(sGroup, sld.id);
					sld.mapEnc.type = "trade";
					sld.mapEnc.worldMapShip = "quest_ship";
					sld.mapEnc.Name = DLG_TEXT_BR[113];
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывет Шарп
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City))+3; //дней доехать даем с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo(DLG_TEXT_BR[114] + sColony + DLG_TEXT_BR[115] + pchar.questTemp.Sharp.City);
				}
				else
				{	//чудо, Шарп здесь, в борделе!
					dialog.text = DLG_TEXT_BR[116];
					link.l1 = DLG_TEXT_BR[117] + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BR[118];
				link.l1 = DLG_TEXT_BR[119] + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = DLG_TEXT_BR[120];
			link.l1 = DLG_TEXT_BR[121];
			link.l1.go = "SharpPearl_3";
		break;
		case "SharpPearl_3":
			chrDisableReloadToLocation = true;
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "BrothelSharp";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

