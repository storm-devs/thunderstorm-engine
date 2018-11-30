#include "TEXT\DIALOGS\Common_Duel.h"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple(DLG_TEXT_DUEL[0], DLG_TEXT_DUEL[1]), 
				RandPhraseSimple(DLG_TEXT_DUEL[2] + GetAddress_Form(NPChar) + DLG_TEXT_DUEL[3], DLG_TEXT_DUEL[4]));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple(DLG_TEXT_DUEL[5], DLG_TEXT_DUEL[5]), 
				RandPhraseSimple(DLG_TEXT_DUEL[6], DLG_TEXT_DUEL[7])), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple(DLG_TEXT_DUEL[8], DLG_TEXT_DUEL[9]), 
				RandPhraseSimple(DLG_TEXT_DUEL[10], DLG_TEXT_DUEL[11] + GetAddress_FormToNPC(NPChar) + DLG_TEXT_DUEL[12])), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,  
				RandPhraseSimple(DLG_TEXT_DUEL[13], DLG_TEXT_DUEL[14]), 
				RandPhraseSimple(DLG_TEXT_DUEL[15], DLG_TEXT_DUEL[16]));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple(DLG_TEXT_DUEL[17], DLG_TEXT_DUEL[18]), 
				RandPhraseSimple(DLG_TEXT_DUEL[19], DLG_TEXT_DUEL[20])), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple(DLG_TEXT_DUEL[21], DLG_TEXT_DUEL[22]), 
				RandPhraseSimple(DLG_TEXT_DUEL[23], DLG_TEXT_DUEL[24])), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = DLG_TEXT_DUEL[25];
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = DLG_TEXT_DUEL[26];
			}
			link.l1 = RandSwear() + DLG_TEXT_DUEL[27];
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[28], DLG_TEXT_DUEL[29]);
			link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[30], DLG_TEXT_DUEL[31]);
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[32], DLG_TEXT_DUEL[33]);
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[34], 
			DLG_TEXT_DUEL[35]);
		link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[36], DLG_TEXT_DUEL[37]);
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + DLG_TEXT_DUEL[38], 
				DLG_TEXT_DUEL[39]);
			link.l2 = RandPhraseSimple(DLG_TEXT_DUEL[40], DLG_TEXT_DUEL[41]);
			link.l2.go = "sea_duel";
		}
		link.l3 = DLG_TEXT_DUEL[42];
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[43], DLG_TEXT_DUEL[44]);
		link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[45], DLG_TEXT_DUEL[46]);
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = DLG_TEXT_DUEL[47];
			link.l1 = DLG_TEXT_DUEL[48];

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple(DLG_TEXT_DUEL[49], DLG_TEXT_DUEL[50]);
		link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[51] + iHour + DLG_TEXT_DUEL[52],
			DLG_TEXT_DUEL[53] + iHour + DLG_TEXT_DUEL[54]);
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple(DLG_TEXT_DUEL[55], DLG_TEXT_DUEL[56]);
		link.l2.go = "fight_right_now";
		link.l3 = DLG_TEXT_DUEL[57];
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple(DLG_TEXT_DUEL[58] + pchar.questTemp.Duel.WaitTime + DLG_TEXT_DUEL[59], 
				DLG_TEXT_DUEL[60] + pchar.questTemp.Duel.WaitTime + DLG_TEXT_DUEL[61]);
			link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[62], DLG_TEXT_DUEL[63]);
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple(DLG_TEXT_DUEL[64], DLG_TEXT_DUEL[65]);
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение DLG_TEXT_DUEL[66] рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[67], DLG_TEXT_DUEL[68]);
		link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[69], DLG_TEXT_DUEL[70]);
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[71], DLG_TEXT_DUEL[72]);
			link.l1 = RandPhraseSimple(DLG_TEXT_DUEL[73], DLG_TEXT_DUEL[74]);
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдем выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = DLG_TEXT_DUEL[75];
		link.l1 = DLG_TEXT_DUEL[76];
		link.l1.go = "fight_right_now";
		link.l2 = DLG_TEXT_DUEL[77];
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_DUEL[78], 
				DLG_TEXT_DUEL[79]);
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple(DLG_TEXT_DUEL[80], DLG_TEXT_DUEL[81]), 
				RandPhraseSimple(DLG_TEXT_DUEL[82], DLG_TEXT_DUEL[83]));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple(DLG_TEXT_DUEL[84], DLG_TEXT_DUEL[85]), 
				RandPhraseSimple(DLG_TEXT_DUEL[86], DLG_TEXT_DUEL[87]));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple(DLG_TEXT_DUEL[88], DLG_TEXT_DUEL[89]), 
				RandPhraseSimple(DLG_TEXT_DUEL[90], DLG_TEXT_DUEL[91]));
		link.l1 = DLG_TEXT_DUEL[92];
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple(DLG_TEXT_DUEL[93], DLG_TEXT_DUEL[94]),
				RandPhraseSimple(DLG_TEXT_DUEL[95], DLG_TEXT_DUEL[96]));
		link.l1 = DLG_TEXT_DUEL[97];
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
