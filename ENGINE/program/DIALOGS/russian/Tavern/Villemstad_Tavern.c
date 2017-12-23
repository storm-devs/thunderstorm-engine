#include "TEXT\DIALOGS\Tavern\Villemstad_Tavern.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[0]+ GetCityName(npchar.city) +DLG_TEXT_TV[1],
                          DLG_TEXT_TV[2], DLG_TEXT_TV[3],
                          DLG_TEXT_TV[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[5] + NPChar.name + DLG_TEXT_TV[6], DLG_TEXT_TV[7],
                      DLG_TEXT_TV[8], DLG_TEXT_TV[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch(pchar.questTemp.State)
			{
			case "Intelligence_Curacao_tavern":
				link.l1 = DLG_TEXT_TV[10];
				link.l1.go = "Step_E4_1";
				break;
			case "Intelligence_Curacao_dWant_pay_tavern":
				dialog.text = DLG_TEXT_TV[11];
				link.l1 = DLG_TEXT_TV[12];
				link.l1.go = "E4_OK_pay";
				link.l2 = DLG_TEXT_TV[13];
				link.l2.go = "E4_dWant_pay";
				break;
			case "Intelligence_Curacao_NoMoney_tavern":
				dialog.text = DLG_TEXT_TV[14];
				link.l1 = DLG_TEXT_TV[15];
				link.l1.go = "E4_OK_pay";
				break;
			case "Inquisition_toCuracao":
				dialog.text = DLG_TEXT_TV[16];
				link.l1 = DLG_TEXT_TV[17];
				link.l1.go = "Step_S2_1";
				break;
			case "Inquisition_afterFrancisco":
				dialog.text = DLG_TEXT_TV[18];
				link.l1 = DLG_TEXT_TV[19];
				link.l1.go = "Step_S2_1";
				break;
			case "Fr2Letter_SeekProblems":
				dialog.text = DLG_TEXT_TV[20];
				link.l1 = DLG_TEXT_TV[21];
				link.l1.go = "Step_F2_1";
				break;
			}
			if (pchar.questTemp.LSC == "toVillemstadTavern")
			{
				dialog.text = DLG_TEXT_TV[22];
				link.l1 = DLG_TEXT_TV[23];
				link.l1.go = "MasterKeys";
			}
			if (pchar.questTemp.LSC == "toMasterKeysNoMoney")
			{
				dialog.text = DLG_TEXT_TV[24];
				link.l1 = DLG_TEXT_TV[25];
				link.l1.go = "MasterKeysNM";
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				dialog.text = DLG_TEXT_TV[26];
				link.l1 = DLG_TEXT_TV[27];
				link.l1.go = "TizerFind";
			}
            // <== Проверяем поле состояния квестов.
 		break;
//*************************** Квест №4 английки, разведка в Кюрасао ***************************
 		case "Step_E4_1":
    		dialog.text = DLG_TEXT_TV[28];
    		link.l1 = DLG_TEXT_TV[29];
    		link.l1.go = "Step_E4_2";
 		break;
 		case "Step_E4_2":
    		dialog.text = DLG_TEXT_TV[30];
    		link.l1 = DLG_TEXT_TV[31];
    		link.l1.go = "E4_dWant_pay";
    		link.l2 = DLG_TEXT_TV[32];
    		link.l2.go = "E4_OK_pay";
 		break;
 		case "E4_dWant_pay":
    		dialog.text = DLG_TEXT_TV[33];
    		link.l1 = DLG_TEXT_TV[34];
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Intelligence_Curacao_dWant_pay_tavern";
 		break;
 		case "E4_OK_pay":
            if (sti(pchar.money) >= 1000)
            {
        		dialog.text = DLG_TEXT_TV[35]+
                         DLG_TEXT_TV[36]+
                         DLG_TEXT_TV[37];
        		link.l1 = DLG_TEXT_TV[38];
        		link.l1.go = "Step_E4_3";
            }
            else
            {
        		dialog.text = DLG_TEXT_TV[39];
        		link.l1 = DLG_TEXT_TV[40];
        		link.l1.go = "exit";
        		pchar.questTemp.State = "Intelligence_Curacao_NoMoney_tavern";
        		//ChangeCharacterReputation(pchar, -1); TO_DO eddy
            }
 		break;
 		case "Step_E4_3":
    		dialog.text = DLG_TEXT_TV[41];
    		link.l1 = DLG_TEXT_TV[42];
    		link.l1.go = "Step_E4_4";
 		break;
 		case "Step_E4_4":
    		dialog.text = DLG_TEXT_TV[43];
    		link.l1 = DLG_TEXT_TV[44];
    		link.l1.go = "exit";
    		pchar.questTemp.State = "Intelligence_Curacao_toYozef";
    		AddMoneyToCharacter(pchar, -1000);
    		AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "2");
 		break;
//*************************** Квест №2 испанки, задания Инквизиции ***************************
 		case "Step_S2_1":
    		dialog.text =  NPCStringReactionRepeat(DLG_TEXT_TV[45],
            DLG_TEXT_TV[46], DLG_TEXT_TV[47], DLG_TEXT_TV[48], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[49], DLG_TEXT_TV[50], DLG_TEXT_TV[51], DLG_TEXT_TV[52], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_S2_2":
    		dialog.text = DLG_TEXT_TV[53];
    		link.l1 = DLG_TEXT_TV[54];
    		link.l1.go = "exit";
 		break;
//*************************** Квест №2 фр.линейки, доставка письма Стэвезанту ***************************
 		case "Step_F2_1":
    		dialog.text =  NPCStringReactionRepeat(DLG_TEXT_TV[55],
            DLG_TEXT_TV[56], DLG_TEXT_TV[57], DLG_TEXT_TV[58], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[59], DLG_TEXT_TV[60], DLG_TEXT_TV[61], DLG_TEXT_TV[62], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_F2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_F2_2":
    		dialog.text = DLG_TEXT_TV[63]+
				          DLG_TEXT_TV[64];
    		link.l1 = DLG_TEXT_TV[65];
    		link.l1.go = "exit";
 		break;
//*************************** ГПК, Мастер Ключей ***************************
		case "MasterKeys":
			dialog.text = DLG_TEXT_TV[66];
			link.l1 = DLG_TEXT_TV[67];
			link.l1.go = "MasterKeys_1";
		break;
		case "MasterKeys_1":
			dialog.text = DLG_TEXT_TV[68];
			link.l1 = DLG_TEXT_TV[69];
			link.l1.go = "MasterKeys_2";
		break;
		case "MasterKeys_2":
			dialog.text = DLG_TEXT_TV[70];
			link.l1 = DLG_TEXT_TV[71];
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toMasterKeys";
		break;

		case "MasterKeysNM":
			dialog.text = DLG_TEXT_TV[72];
			link.l1 = DLG_TEXT_TV[73];
			link.l1.go = "exit";
			if (!LAi_CheckLocatorFree("sit", "sit1"))
			{
				FreeSitLocator("Villemstad_tavern", "sit1");
			}
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("GiveKeyMan")], "Villemstad_tavern", "sit", "sit1");
		break;
		//ищем Тизера
		case "TizerFind":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[74], 
				DLG_TEXT_TV[75], 
				DLG_TEXT_TV[76],
                DLG_TEXT_TV[77], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[78], 
				DLG_TEXT_TV[79],
                DLG_TEXT_TV[80], 
				DLG_TEXT_TV[81], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TizerFind_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TizerFind_1":
			dialog.text = DLG_TEXT_TV[82];
			link.l1 = DLG_TEXT_TV[83];
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = DLG_TEXT_TV[84];
			link.l1 = DLG_TEXT_TV[85];
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = DLG_TEXT_TV[86];
			link.l1 = DLG_TEXT_TV[87];
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = DLG_TEXT_TV[88];
			link.l1 = DLG_TEXT_TV[89];
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = DLG_TEXT_TV[90];
			link.l1 = DLG_TEXT_TV[91];
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = DLG_TEXT_TV[92];
			link.l1 = DLG_TEXT_TV[93];
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = DLG_TEXT_TV[94];
			link.l1 = DLG_TEXT_TV[95];
			link.l1.go = "TizerFind_8";
		break;
		case "TizerFind_8":
			dialog.text = DLG_TEXT_TV[96];
			link.l1 = DLG_TEXT_TV[97];
			link.l1.go = "TizerFind_9";
		break;
		case "TizerFind_9":
			dialog.text = DLG_TEXT_TV[98];
			link.l1 = DLG_TEXT_TV[99];
			link.l1.go = "TizerFind_10";
		break;
		case "TizerFind_10":
			dialog.text = DLG_TEXT_TV[100];
			link.l1 = DLG_TEXT_TV[101];
			link.l1.go = "TizerFind_11";
		break;
		case "TizerFind_11":
			dialog.text = DLG_TEXT_TV[102];
			link.l1 = DLG_TEXT_TV[103];
			link.l1.go = "TizerFind_12";
		break;
		case "TizerFind_12":
			dialog.text = DLG_TEXT_TV[104];
			link.l1 = DLG_TEXT_TV[105];
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "8");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

