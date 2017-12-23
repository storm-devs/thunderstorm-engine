#include "TEXT\DIALOGS\Brothel\FortFrance_Brothel.h"
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
			// ==> Проверяем поле состояния квестов.
            if (pchar.questTemp.State == "SeekBible_toFFBrothel" && npchar.id == "FortFrance_Hostess") //Голландская линейка, квест №8. узнаем о пирате, который о Библии базарил.
			{
                link.l1 = DLG_TEXT_BR[10];
                link.l1.go = "Step_H8_1";
			}
			if (pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(npchar, "quest.SharpTime") > 7 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]))
			{
				link.l1 = DLG_TEXT_BR[11] + npchar.name + DLG_TEXT_BR[12];
				link.l1.go = "SharpPearl_1";
				SaveCurrentNpcQuestDateParam(npchar, "quest.SharpTime");
			}
            // <== Проверяем поле состояния квестов.
		break;

        case "Step_H8_1":
            dialog.text = DLG_TEXT_BR[13];
            link.l1 = DLG_TEXT_BR[14];
            link.l1.go = "Step_H8_2";
        break;
        case "Step_H8_2":
            dialog.text = DLG_TEXT_BR[15];
            link.l1 = DLG_TEXT_BR[16];
            link.l1.go = "Step_H8_3";
        break;
        case "Step_H8_3":
            dialog.text = DLG_TEXT_BR[17];
            link.l1 = DLG_TEXT_BR[18];
            link.l1.go = "Step_H8_4";
        break;
        case "Step_H8_4":
            dialog.text = DLG_TEXT_BR[19];
            link.l1 = DLG_TEXT_BR[20];
            link.l1.go = "Step_H8_5";
        break;
        case "Step_H8_5":
            dialog.text = DLG_TEXT_BR[21];
            link.l1 = DLG_TEXT_BR[22];
            link.l1.go = "Step_H8_6";
        break;
        case "Step_H8_6":
            dialog.text = DLG_TEXT_BR[23];
            link.l1 = DLG_TEXT_BR[24];
            link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toGirl";
        break;
		// капитан Шарп, грабеж жемчужных промыслов
		case "SharpPearl_1":
			if (rand(1) || bBettaTestMode)
			{
				if (sti(pchar.questTemp.Sharp.brothelChance) < 9)
				{	//футболим геймера в город
					pchar.questTemp.Sharp.City = GetSharpCity();
					pchar.questTemp.Sharp.City.rumour = true; //флаг дачи слуха
					dialog.text = DLG_TEXT_BR[25] + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ".";
					link.l1 = DLG_TEXT_BR[26] + npchar.name + DLG_TEXT_BR[27];
					link.l1.go = "exit";
					pchar.questTemp.Sharp = "toSharp_going"; //в бордели больше не заходить
					ReOpenQuestHeader("SharpPearl");
					AddQuestRecord("SharpPearl", "1");
					AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
					AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
					if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
					{
						AddQuestUserData("SharpPearl", "sAreal", DLG_TEXT_BR[28] + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Dat"));
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
					sld.mapEnc.Name = DLG_TEXT_BR[29];
					string sColony= SelectAnyColony(npchar.city); //колония, откуда плывет Шарп
					int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City))+3; //дней доехать даем с запасом
					Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
					Log_TestInfo(DLG_TEXT_BR[30] + sColony + DLG_TEXT_BR[31] + pchar.questTemp.Sharp.City);
				}
				else
				{	//чудо, Шарп здесь, в борделе!
					dialog.text = DLG_TEXT_BR[32];
					link.l1 = DLG_TEXT_BR[33] + npchar.name + "...";
					link.l1.go = "SharpPearl_2";
				}
			}
			else
			{
				dialog.text = DLG_TEXT_BR[34];
				link.l1 = DLG_TEXT_BR[35] + npchar.name + ".";
				link.l1.go = "exit";
			}
		break;
		case "SharpPearl_2":
			dialog.text = DLG_TEXT_BR[36];
			link.l1 = DLG_TEXT_BR[37];
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

