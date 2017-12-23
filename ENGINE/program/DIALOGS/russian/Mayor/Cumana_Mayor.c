#include "TEXT\DIALOGS\Mayor\Cumana_Mayor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp8SaveCumana_GoodWork")//квест №8 испанки.
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_MR[10], DLG_TEXT_MR[11]);
				link.l1 = RandPhraseSimple(DLG_TEXT_MR[12], DLG_TEXT_MR[13]);
				link.l1.go = "exit";			
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[14], DLG_TEXT_MR[15]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[16], DLG_TEXT_MR[17]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************	
        //==> Одиннадцатый квест англ.линейки: захват Каракаса и Куманы.
        case "EngLine11Quest_OccupyMein":
			dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
        break;
        case "Step_E10_1":
			dialog.text = DLG_TEXT_MR[20];
			link.l1 = DLG_TEXT_MR[21];
			link.l1.go = "exit";
            AddQuestRecord("Eng_Line_11_OccupyMein", "3");
            pchar.questTemp.Q11_Cumana = 1;
            NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            UpdateRelations();
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка  
        break;
        //==> Шестой квест фр.линейки: захват Куманы с Олоне.
 		case "FraLine6Quest_Attack":
			dialog.text = DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Step_F6_1";
			group_DeleteGroup("Spa_Attack");
			AfterTownBattle();
		break;		
		case "Step_F6_1":
            dialog.text = DLG_TEXT_MR[24];
			link.l1 = DLG_TEXT_MR[25];
            link.l1.go = "Step_F6_2";
        break;
		case "Step_F6_2":
            dialog.text = DLG_TEXT_MR[26];
			link.l1 = DLG_TEXT_MR[27];
            link.l1.go = "Step_F6_3";
        break;
		case "Step_F6_3":
			if (GetQuestPastDayParam("questTemp") < 14)
			{
				dialog.text = DLG_TEXT_MR[28];
				link.l1 = DLG_TEXT_MR[29];
				link.l1.go = "Step_F6_exit";
         		pchar.GenQuestBox.Cumana_TownhallRoom = true;
				pchar.GenQuestBox.Cumana_TownhallRoom.box1.money = 200000;
				LocatorReloadEnterDisable("Cumana_townhall", "reload2", false);
				pchar.questTemp.State = "Fr5Olone_FoundMoney";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[30];
				link.l1 = DLG_TEXT_MR[31];
				link.l1.go = "Step_F6_4";
			}
        break;
		case "Step_F6_4":
            dialog.text = DLG_TEXT_MR[32];
			link.l1 = DLG_TEXT_MR[33];
            link.l1.go = "Step_F6_exit";
			pchar.questTemp.State = "Fr5Olone_WeLate";
        break;
		case "Step_F6_exit":
			for (i=0; i<3; i++)
			{				
				if (i==0)	sld = characterFromID("Olone");
				else	sld = characterFromID("Captain_"+i); 
				RemoveCharacterCompanion(pchar, sld);
				sld.dialog.currentnode = "First time";
				LAi_SetStayType(sld);
				LAi_SetCurHPMax(sld);
				LAi_LoginInCaptureTown(sld, true);
			}
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1.location = "Cumana_town";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition = "Fr6Olone_TalkWithOlone";
			LAi_LocationDisableOfficersGen("Cumana_town", true); //офицеров не пускать
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = "Cupture_after";
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
        break;

	}
    UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

