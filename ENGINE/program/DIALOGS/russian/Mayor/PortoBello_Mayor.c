#include "TEXT\DIALOGS\Mayor\PortoBello_Mayor.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[0], DLG_TEXT_MR[1]), DLG_TEXT_MR[2], DLG_TEXT_MR[3],
                          DLG_TEXT_MR[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_MR[5], DLG_TEXT_MR[6]), DLG_TEXT_MR[7],
                      DLG_TEXT_MR[8], DLG_TEXT_MR[9] + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp9SaveCumana_toPortoBello")//квест є9 испанки.
			{
				dialog.text = DLG_TEXT_MR[10];
				link.l1 = DLG_TEXT_MR[11] + GetFullName(pchar) + DLG_TEXT_MR[12];
				link.l1.go = "Step_S10_1";			
			}
			if (pchar.questTemp.State == "Sp9SaveCumana_toCompOut")//квест є9 испанки, после того, как 0 компаньонов.
			{
				dialog.text = DLG_TEXT_MR[13];
				link.l1 = DLG_TEXT_MR[14];
				link.l1.go = "Step_S10_5";			
			}
			if (pchar.questTemp.piratesLine == "Panama_toPortoBello")//пиратка, штурм ѕанамы
			{
				dialog.text = "";
				link.l1 = "";
				link.l1.go = "Step_S10_5";
			}
		break;
        //==> ƒев€тый квест исп.линейки: сопроводить четыре золотых галеона.
        case "Step_S10_1":
			dialog.text = DLG_TEXT_MR[15];
			link.l1 = DLG_TEXT_MR[16];
			link.l1.go = "Step_S10_2";
  			TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
        break;
        case "Step_S10_2":
			dialog.text = DLG_TEXT_MR[17];
			link.l1 = DLG_TEXT_MR[18];
			link.l1.go = "Step_S10_3";
        break;
        case "Step_S10_3":
			dialog.text = DLG_TEXT_MR[19];
			link.l1 = DLG_TEXT_MR[20];
			link.l1.go = "Step_S10_4";
        break;
        case "Step_S10_4":
			dialog.text = DLG_TEXT_MR[21]+
				          DLG_TEXT_MR[22];
			link.l1 = DLG_TEXT_MR[23];
			link.l1.go = "Step_S10_5";
        break;
        case "Step_S10_5":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = DLG_TEXT_MR[24];
				link.l1 = DLG_TEXT_MR[25];
				link.l1.go = "exit";
				pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			}
			else
			{
				dialog.text = DLG_TEXT_MR[26];
				link.l1 = DLG_TEXT_MR[27];
				link.l1.go = "Step_S10_6";
			}
        break;
        case "Step_S10_6":
			dialog.text = DLG_TEXT_MR[28];
			link.l1 = DLG_TEXT_MR[29];
			link.l1.go = "Step_S10_7";
        break;
        case "Step_S10_7":
            pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "2");
            ref sld;
            for (int i=1; i<=4; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "trader_"+(rand(15)+1), "man", "man", 15, SPAIN, -1, true));
                FantomMakeCoolSailor(sld, SHIP_GALEON_L, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
                FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
                sld.Ship.Cargo.Goods.Balls = 48;
                sld.Ship.Cargo.Goods.Grapes = 10;
                sld.Ship.Cargo.Goods.Knippels = 48;
                sld.Ship.Cargo.Goods.Bombs = 48;
                sld.Ship.Cargo.Goods.Weapon = 0;
                sld.Ship.Cargo.Goods.Powder = 80;
				sld.Ship.Cargo.Goods.Food = 300;
				sld.Ship.Cargo.Goods.Gold= 1250;
				SetCharacterRemovable(sld, false);
				sld.CompanionEnemyEnable = false; 
				sld.Abordage.Enable = false; // Ќ≈Ћ№«я!
                SetCompanionIndex(pchar, -1, sti(sld.index));
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1 = "location";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1.location = "Caiman";
                Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition = "Sp9SaveCumana_toCaimanBattle";
            }
			DialogExit();
        break;
		//**************************  вестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[30], DLG_TEXT_MR[31]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[32], DLG_TEXT_MR[33]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
        //==> пиратка, штурм ѕанамы
        case "PQ8_MayorPortoBello":
			dialog.text = DLG_TEXT_MR[34];
			link.l1 = DLG_TEXT_MR[35];
			link.l1.go = "Step_P1_1";
			AfterTownBattle();
        break;
        case "Step_P1_1":
			dialog.text = DLG_TEXT_MR[36];
			link.l1 = DLG_TEXT_MR[37];
			link.l1.go = "Step_P1_2";
        break;
        case "Step_P1_2":
			dialog.text = DLG_TEXT_MR[38];
			link.l1 = DLG_TEXT_MR[39];
			link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("PQ8_MorganInPortoBello");
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

