#include "TEXT\DIALOGS\Mayor\Beliz_Mayor.h"
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
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple(DLG_TEXT_MR[10], DLG_TEXT_MR[11]);
            link.l1 = RandPhraseSimple(DLG_TEXT_MR[12], DLG_TEXT_MR[13]);
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
       //==> Третий квест англ.линейки: нападение на Белиз.
        case "EngLine3Quest_BelizAttack":
			dialog.text = DLG_TEXT_MR[14];
			link.l1 = DLG_TEXT_MR[15];
			link.l1.go = "Step_E3_1";
			AfterTownBattle();
        break;

        case "Step_E3_1":
            dialog.text = DLG_TEXT_MR[16];
			link.l1 = DLG_TEXT_MR[17];
			link.l1.go = "Step_E3_2";
        break;

        case "Step_E3_2":
            dialog.text = DLG_TEXT_MR[18];
			link.l1 = DLG_TEXT_MR[19];
			link.l1.go = "Step_E3_3";
        break;

        case "Step_E3_3":
            dialog.text = DLG_TEXT_MR[20];
			link.l1 = DLG_TEXT_MR[21];
			link.l1.go = "Step_E3_4";
        break;

        case "Step_E3_4":
            dialog.text = DLG_TEXT_MR[22]+
                          DLG_TEXT_MR[23];
			link.l1 = DLG_TEXT_MR[24];
			link.l1.go = "Step_E3_5";
        break;

        case "Step_E3_5":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Henry Morgan")], true); 
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Jackman")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("John Morris")], true);
            DoReloadCharacterToLocation("Beliz_fort",  "goto", "goto61");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "Beliz_fort", "goto", "goto13");
			LAi_SetStayType(characterFromID("Henry Morgan"));
			characters[GetCharacterIndex("Henry Morgan")].dialog.currentnode = "Gold_found_in_fort";
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))   // Эта фигня нужна для определения, взял ли ГГ этих перцев на дело. Если нет, то и их в форте не будет.
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Beliz_fort", "goto", "goto72");
                LAi_SetStayType(characterFromID("Jackman"));
                characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Gold_found_in_fort";
            }
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
            {
                ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "Beliz_fort", "goto", "goto01");
                LAi_SetStayType(characterFromID("John Morris"));
                characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Gold_found_in_fort";
            }     
            LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], true);
            // ==> Дележ золота. Можно не брать Джекмена и Джона Морриса вообще в эскадру.
            // === Квест будет выполнен, а золото поделено соответственно.
            pchar.questTemp.BelizGoldQty = 3300 / sti(pchar.questTemp.CompanionQuantity);   // Нужно для контроля продаж золота Моргану, чтоб не продавать возможно уже существующее у ГГ золото.
			// грузим ГГ и его эскадру (не квестовые)
            SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.BelizGoldQty));// перегруз
            if (IsCompanion(characterFromID("Henry Morgan")))   {AddCharacterGoodsSimple(characterFromID("Henry Morgan"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("Jackman")))        {AddCharacterGoodsSimple(characterFromID("Jackman"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            if (IsCompanion(characterFromID("John Morris")))    {AddCharacterGoodsSimple(characterFromID("John Morris"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));}
            Log_SetStringToLog(DLG_TEXT_MR[25]);
            InterfaceStates.Buttons.Save.enable = false;
            chrDisableReloadToLocation = true;
        break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

