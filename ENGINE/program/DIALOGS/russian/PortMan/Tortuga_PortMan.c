#include "TEXT\DIALOGS\PortMan\Tortuga_PortMan.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[0], DLG_TEXT_PRT[1] + GetAddress_Form(NPChar) + "?"), DLG_TEXT_PRT[2] + GetAddress_Form(NPChar) + "...", DLG_TEXT_PRT[3],
                          DLG_TEXT_PRT[4], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(DLG_TEXT_PRT[5], DLG_TEXT_PRT[6]), DLG_TEXT_PRT[7],
                      DLG_TEXT_PRT[8], DLG_TEXT_PRT[9], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> квест №7 голл.линейки, догнать похитителей депеши
            if (pchar.questTemp.State == "DelivLettTortuga_toPortMan")
            {
    			link.l1 = DLG_TEXT_PRT[10];
    			link.l1.go = "Step_H7_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_toTotuga")
            {
                link.l1 = DLG_TEXT_PRT[11];
                link.l1.go = "Step_S6_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_waitMessanger")
            {
                link.l1 = DLG_TEXT_PRT[12];
                link.l1.go = "Step_S6_6";
            }
            if (pchar.questTemp.State == "Fr4SoleiRoyal_toPortMan")
            {
                link.l1 = DLG_TEXT_PRT[13];
                link.l1.go = "Step_F4_1";
            }
		break;

//************************************* Голл. линейка, квест №7, доставка депеши *******************************
		case "Step_H7_1":
            dialog.text = DLG_TEXT_PRT[14];
			link.l1 = DLG_TEXT_PRT[15];
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
            dialog.text = DLG_TEXT_PRT[16]+
                          DLG_TEXT_PRT[17];
			link.l1 = DLG_TEXT_PRT[18];
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
            dialog.text = DLG_TEXT_PRT[19];
			link.l1 = DLG_TEXT_PRT[20];
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
            dialog.text = DLG_TEXT_PRT[21];
			link.l1 = DLG_TEXT_PRT[22];
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "5");
			pchar.questTemp.State = "DelivLettTortuga_NotFoundLetter";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1.location = "PuertoRico";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition = "DelivLettTortuga_AttackBrig";
            SetTimerCondition("DelivLettTortuga_BrigTimeOver", 0, 0, 5, false);
		break;
//************************************* Испанская линейка, квест №6, перехват вестового *******************************
		case "Step_S6_1":
            dialog.text = NPCStringReactionRepeat(DLG_TEXT_PRT[23],
                          DLG_TEXT_PRT[24], DLG_TEXT_PRT[25], DLG_TEXT_PRT[26], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_PRT[27],
                     DLG_TEXT_PRT[28], DLG_TEXT_PRT[29], DLG_TEXT_PRT[30], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_2":
            dialog.text = DLG_TEXT_PRT[31];
			link.l1 = DLG_TEXT_PRT[32];
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
            dialog.text = DLG_TEXT_PRT[33];
			link.l1 = DLG_TEXT_PRT[34];
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
            dialog.text = DLG_TEXT_PRT[35];
			link.l1 = DLG_TEXT_PRT[36];
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
            dialog.text = DLG_TEXT_PRT[37];
			link.l1 = DLG_TEXT_PRT[38];
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "2");
            pchar.questTemp.State = "Sp6TakeMess_waitMessanger";
            if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
            {
                SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7)+1, false);
                DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
            }
            else
            {
                pchar.questTemp.State.Sp6Ok = 1;
            }
		break;
 		case "Step_S6_6":
            dialog.text = DLG_TEXT_PRT[39];
			link.l1 = DLG_TEXT_PRT[40];
			link.l1.go = "exit";
		break;
//************************************* Французская линейка, квест №4, Солей Руаяль *******************************
 		case "Step_F4_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = DLG_TEXT_PRT[41];
    			link.l1 = DLG_TEXT_PRT[42];
    			link.l1.go = "Step_F4_2";
            }
            else
            {
                dialog.text = DLG_TEXT_PRT[43];
    			link.l1 = DLG_TEXT_PRT[44];
    			link.l1.go = "exit";
            }
		break;	
 		case "Step_F4_2":
    		pchar.questTemp.State = "Fr4SoleiRoyal_toBasTer";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "2");
			ref sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			sld.Ship.Name = DLG_TEXT_PRT[45];
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");	
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);	
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1.location = "Dominica";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition = "Fr4SoleiRoyal_Fight";
			DialogExit();
		break;	

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

