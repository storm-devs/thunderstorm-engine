#include "TEXT\DIALOGS\Mayor\FortOrange_Mayor.h"
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
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeMayor": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
                    link.l2 = DLG_TEXT_MR[10];
                    link.l2.go = "Step_H2_1";
                break;
                
            }
             // <== Проверяем поле состояния квестов.
		break;
		
        case "Step_H2_1":
			dialog.text = DLG_TEXT_MR[11]+
                          DLG_TEXT_MR[12];
			link.l1 = DLG_TEXT_MR[13];
			link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "Trust");
            BackItemDescribe("Trust");
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "2");
			pchar.questTemp.State = "TakeFoodCuracao_toOrangeStore";
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE;
        	pchar.GenQuest.StoreGoods.HL2_DiscountPrices = true;
		break;

        case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
            dialog.text = DLG_TEXT_MR[14];
            link.l2 = DLG_TEXT_MR[15];
            link.l2.go = "Step_H4_1";
        break;
        
        case "Step_H4_1":
			dialog.text = DLG_TEXT_MR[16];
			link.l1 = DLG_TEXT_MR[17];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

