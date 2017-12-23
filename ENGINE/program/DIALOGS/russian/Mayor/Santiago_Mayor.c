#include "TEXT\DIALOGS\Mayor\Santiago_Mayor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            //===> Проверка состояния текущего квеста
            if (pchar.questTemp.State == "Sp5LaVegaAttack_toSantiago")
            {
    			dialog.text = DLG_TEXT_MR[10];
    			link.l1 = DLG_TEXT_MR[11];
    			link.l1.go = "Step_S5_1";
            }
            if (pchar.questTemp.State == "Sp5LaVegaAttack_WeWon")
            {
    			dialog.text = DLG_TEXT_MR[12];
    			link.l1 = DLG_TEXT_MR[13];
    			link.l1.go = "Step_S5_6";
            }
            //<=== Проверка состояния текущего квеста
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[14], DLG_TEXT_MR[15]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[16], DLG_TEXT_MR[17]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;

        //********************** Девятый квест англ.линейки: нападение на Сантьяго ************************
        case "EL9_SantiagoAttack":
			dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "Step_E9_1";
			AfterTownBattle();
        break;
        case "Step_E9_1":
            dialog.text = DLG_TEXT_MR[20];
			link.l1 = DLG_TEXT_MR[21];
			link.l1.go = "Step_E9_2";
        break;
        case "Step_E9_2":
            dialog.text = DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Step_E9_3";
        break;
        case "Step_E9_3":
            dialog.text = DLG_TEXT_MR[24];
			link.l1 = DLG_TEXT_MR[25];
			link.l1.go = "Step_E9_4";
        break;
        case "Step_E9_4":
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1); // статистика
			AddQuestRecord("Eng_Line_9_AttackSantiago", "2");
			chrDisableReloadToLocation = false;
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1 = "location";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1.location = "Cuba1";
            Pchar.quest.AttackSantiago_FightWithPardal.win_condition = "AttackSantiago_FightWithPardal";
            // ==> Меняем имя и модель у губера,
            npchar.model = "usurer_3";
            npchar.name 	= DLG_TEXT_MR[26];
        	npchar.lastname = DLG_TEXT_MR[27];
        	SendMessage(npchar, "lss", MSG_CHARACTER_SETMODEL, npchar.model, npchar.model.animation);
        	FaceMaker(npchar);
            // ==> а пленным делаем Альбермаля.
            sld = GetCharacter(NPC_GenerateCharacter("Himenes", "huber_spa", "man", "man", 10, SPAIN, -1, false));
            LAi_SetStayTypeNoGroup(sld);
            sld.name 	= DLG_TEXT_MR[28];
        	sld.lastname = DLG_TEXT_MR[29];
            SetCharacterRemovable(sld, false);
            AddPassenger(pchar, sld, true);
			SetReturn_Gover_Dialog_Exit(NPChar);
            DoReloadCharacterToLocation("Santiago_town",  "reload", "reload3");
            NextDiag.CurrentNode = "Cupture_after";
            chrDisableReloadToLocation = false;
            DialogExit();
        break;
        //********************** Квест №5, Нападение на Ла Вегу. ************************
        case "Step_S5_1":
            dialog.text = DLG_TEXT_MR[30];
			link.l1 = DLG_TEXT_MR[31];
			link.l1.go = "Step_S5_2";
        break;
        case "Step_S5_2":
            dialog.text = DLG_TEXT_MR[32];
			link.l1 = DLG_TEXT_MR[33];
			link.l1.go = "Step_S5_3";
        break;
        case "Step_S5_3":
            dialog.text = DLG_TEXT_MR[34];
			link.l1 = DLG_TEXT_MR[35];
			link.l1.go = "Step_S5_4";
        break;
        case "Step_S5_4":
            dialog.text = DLG_TEXT_MR[36];
			link.l1 = DLG_TEXT_MR[37];
			link.l1.go = "Step_S5_5";
        break;
        case "Step_S5_5":
            dialog.text = DLG_TEXT_MR[38];
			link.l1 = DLG_TEXT_MR[39];
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp5LaVegaAttack_AttackLaVega";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "2");
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1 = "location";
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1.location = "LaVega_ExitTown";
            Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition = "Sp5LaVegaAttack_AttackGoOn";
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry3 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry4 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry5 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry7 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry8 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry10 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry14 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry17 = Rand(7)+1;
            pchar.GenQuestBox.LaVega_townhall.box1.items.cirass4 = 1;
			locations[FindLocation("LaVega_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			sld = characterFromId("Edward Mansfield");
			sld.Default.Crew.Quantity    = 1700;
			sld.Default.Crew.MinQuantity = 1100;
			sld.from_sea = ""; // для захвата с суши
			sld.Default  = "LaVega_townhall";  // чтоб сухопутные города вернули население
			sld.Default.BoardLocation = "LaVega_ExitTown";
        break;
        case "Step_S5_6":
            dialog.text = DLG_TEXT_MR[40];
			link.l1 = DLG_TEXT_MR[41];
			link.l1.go = "Step_S5_7";
        break;
        case "Step_S5_7":
            dialog.text = DLG_TEXT_MR[42];
			link.l1 = DLG_TEXT_MR[43];
			link.l1.go = "exit";
			locations[FindLocation("LaVega_townhall")].models.day.charactersPatch = "SmallResidence_patch";
            AddMoneyToCharacter(pchar, 100000);
            pchar.questTemp.State = "Sp5LaVegaAttack_BackToHavana";
            AddQuestRecord("Spa_Line_5_LaVegaAttack", "4");
        break;
	}
    UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

