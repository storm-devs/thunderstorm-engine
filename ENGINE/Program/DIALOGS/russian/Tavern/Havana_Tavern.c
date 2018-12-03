#include "TEXT\DIALOGS\Tavern\Havana_Tavern.h"
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
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = DLG_TEXT_TV[10];
				link.l1 = DLG_TEXT_TV[11];
				link.l1.go = "Step_F7_1";
				break;
			}	
			Link.l1.go = "exit";
            if (pchar.questTemp.Ascold == "ToHavanna") // квест Аскольда
            {
    			Link.l1 = DLG_TEXT_TV[12];
    			Link.l1.go = "Step_A1";
            }
		break;
//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_TV[13], DLG_TEXT_TV[14], 
				          DLG_TEXT_TV[15], DLG_TEXT_TV[16], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_TV[17], DLG_TEXT_TV[18], DLG_TEXT_TV[19], DLG_TEXT_TV[20], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = DLG_TEXT_TV[21];
			link.l1 = DLG_TEXT_TV[22];
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = DLG_TEXT_TV[23];
			link.l1 = DLG_TEXT_TV[24];
			link.l1.go = "exit";
        break;
//******************** Квест Аскольда, узнаем о мановарах с ипанским добром ******************
		case "Step_A1":
			dialog.text = DLG_TEXT_TV[25];
			Link.l1 = DLG_TEXT_TV[26];
			Link.l1.go = "Step_A2";
		break;

		case "Step_A2":
			dialog.text = DLG_TEXT_TV[27];
			Link.l1 = DLG_TEXT_TV[28];
			Link.l1.go = "Step_A3";
		break;

		case "Step_A3":
			dialog.text = DLG_TEXT_TV[29];
			Link.l1 = DLG_TEXT_TV[30];
			Link.l1.go = "Step_A4";
		break;

		case "Step_A4":
			dialog.text = DLG_TEXT_TV[31];
			Link.l1 = DLG_TEXT_TV[32];
			Link.l1.go = "Step_A5";
		break;

		case "Step_A5":
			dialog.text = DLG_TEXT_TV[33];
			Link.l1 = DLG_TEXT_TV[34];
			Link.l1.go = "exit";
			pchar.questTemp.Ascold = "SeekInformatorHavanna";
			AddQuestRecord("Ascold", "6");
            ref sld = GetCharacter(NPC_GenerateCharacter("FernandoGonsales", "off_spa_1", "man", "man", 28, SPAIN, -1, true));
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 10);
            LAi_SetStayType(sld);
           	sld.name 	= DLG_TEXT_TV[35];
			sld.lastname 	= DLG_TEXT_TV[36];
			sld.Dialog.Filename = "Quest\AscoldNpc.c";
			ChangeCharacterAddressGroup(sld, "Santiago_houseSp2", "goto", "goto2");
            LAi_LocationFightDisable(&Locations[FindLocation("Santiago_houseSp2")], true);
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

