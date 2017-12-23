#include "DIALOGS\russian\Common_Duel.c"
#include "TEXT\DIALOGS\PGG_dialog.h"
void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = DLG_TEXT_BASE[0];
//	link.l1 = DLG_TEXT_BASE[1];
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = DLG_TEXT_BASE[2];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4]);
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = DLG_TEXT_BASE[5];
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = DLG_TEXT_BASE[6] + GetFullName(NPChar) + DLG_TEXT_BASE[7];
		Dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[8], 
			 DLG_TEXT_BASE[9], 
			 DLG_TEXT_BASE[10]) + 
			 PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[11],
					DLG_TEXT_BASE[12],
					DLG_TEXT_BASE[13]), 
				LinkRandPhrase(DLG_TEXT_BASE[14],
					DLG_TEXT_BASE[15],
					DLG_TEXT_BASE[16]));
//		link.l1 = DLG_TEXT_BASE[17] + GetFullName(pchar) + ".";
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[18] + GetFullName(pchar) + ".", 
					DLG_TEXT_BASE[19] + PChar.Ship.Name + DLG_TEXT_BASE[20] + GetFullName(pchar) + "."), 
				RandPhraseSimple(DLG_TEXT_BASE[21] + GetFullName(pchar) + ".", 
					DLG_TEXT_BASE[22] + PChar.Ship.Name + DLG_TEXT_BASE[23] + NationNameGenitive(sti(PChar.nation)) + DLG_TEXT_BASE[24] + GetFullName(pchar) + "."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = DLG_TEXT_BASE[25] + GetFullName(NPChar) + DLG_TEXT_BASE[26];
		link.l1 = RandPhraseSimple(DLG_TEXT_BASE[27], DLG_TEXT_BASE[28]);
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = DLG_TEXT_BASE[29] + GetFullName(NPChar) + DLG_TEXT_BASE[30] + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + ".";
			link.l2 = DLG_TEXT_BASE[31];
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple(DLG_TEXT_BASE[32], DLG_TEXT_BASE[33]);
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = DLG_TEXT_BASE[34];
			link.l7.go = "BT_Quest";
			link.l8 = DLG_TEXT_BASE[35];
			link.l8.go = "outraged";
		}
		link.l9 = DLG_TEXT_BASE[36];
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = DLG_TEXT_BASE[37];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = DLG_TEXT_BASE[40];
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = DLG_TEXT_BASE[41];
			link.l1 = DLG_TEXT_BASE[42];
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple(DLG_TEXT_BASE[43] + GetFullName(pchar) + "?", DLG_TEXT_BASE[44]);
		link.l1 = RandPhraseSimple(DLG_TEXT_BASE[45], DLG_TEXT_BASE[46]);
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[47] + GetFullName(pchar) + DLG_TEXT_BASE[48], DLG_TEXT_BASE[49]);
			Dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[50], 
				 DLG_TEXT_BASE[51], 
				 DLG_TEXT_BASE[52]) + 
				 PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[53],
						DLG_TEXT_BASE[54],
						DLG_TEXT_BASE[55]) + DLG_TEXT_BASE[56], 
					LinkRandPhrase(DLG_TEXT_BASE[57],
						DLG_TEXT_BASE[58],
						DLG_TEXT_BASE[59]) + DLG_TEXT_BASE[60]);
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[61], DLG_TEXT_BASE[62]);
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[63], DLG_TEXT_BASE[64]);
				link.l3 = RandPhraseSimple(DLG_TEXT_BASE[65], DLG_TEXT_BASE[66]);
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple(DLG_TEXT_BASE[67], DLG_TEXT_BASE[68]);
					link.l3.go = "officer";
				}
			}
//			link.l4 = DLG_TEXT_BASE[69];
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase(DLG_TEXT_BASE[70], DLG_TEXT_BASE[71]);
			link.l8.go = "outraged";
		}
		link.l9 = DLG_TEXT_BASE[72];
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[75], DLG_TEXT_BASE[76]);
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[77], DLG_TEXT_BASE[78]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80]);
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[81], DLG_TEXT_BASE[82]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[83], DLG_TEXT_BASE[84]);
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[85], DLG_TEXT_BASE[86]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]);
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple(DLG_TEXT_BASE[89] + NPChar.Quest.Officer.Price + DLG_TEXT_BASE[90], 
								DLG_TEXT_BASE[91] + NPChar.Quest.Officer.Price + DLG_TEXT_BASE[92]), 
				LinkRandPhrase(DLG_TEXT_BASE[93] + NPChar.Quest.Officer.Price + DLG_TEXT_BASE[94], 
							DLG_TEXT_BASE[95] + NPChar.Quest.Officer.Price + DLG_TEXT_BASE[96], 
							DLG_TEXT_BASE[97] + NPChar.Quest.Officer.Price + DLG_TEXT_BASE[98]));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[99], DLG_TEXT_BASE[100]), 
				LinkRandPhrase(DLG_TEXT_BASE[101], DLG_TEXT_BASE[102], DLG_TEXT_BASE[103])), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[104], DLG_TEXT_BASE[105]), 
				LinkRandPhrase(DLG_TEXT_BASE[106], DLG_TEXT_BASE[107], DLG_TEXT_BASE[108])), "exit");
		link.l3 = DLG_TEXT_BASE[109];
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = DLG_TEXT_BASE[110];
			link.l1 = DLG_TEXT_BASE[111];
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[112], DLG_TEXT_BASE[113]);
		link.l1 = DLG_TEXT_BASE[114];
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = DLG_TEXT_BASE[115];
		link.l1 = DLG_TEXT_BASE[116];
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[117], DLG_TEXT_BASE[118]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[119], DLG_TEXT_BASE[120]);
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[121], DLG_TEXT_BASE[122]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[123], DLG_TEXT_BASE[124]);
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[125], DLG_TEXT_BASE[126]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[127], DLG_TEXT_BASE[128]);
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
					RandPhraseSimple(DLG_TEXT_BASE[129], DLG_TEXT_BASE[130]), 
					LinkRandPhrase(DLG_TEXT_BASE[131] + GetSexPhrase(DLG_TEXT_BASE[132],DLG_TEXT_BASE[133]) + ".", 
					DLG_TEXT_BASE[134], DLG_TEXT_BASE[135]));
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[136], DLG_TEXT_BASE[137]);
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[138], DLG_TEXT_BASE[139]);
			link.l1 = DLG_TEXT_BASE[140];
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple(DLG_TEXT_BASE[141], DLG_TEXT_BASE[142]), 
					RandPhraseSimple(DLG_TEXT_BASE[143], DLG_TEXT_BASE[144]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[145], DLG_TEXT_BASE[146]),
					RandPhraseSimple(DLG_TEXT_BASE[147], DLG_TEXT_BASE[148]));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[149], DLG_TEXT_BASE[150]),
					RandPhraseSimple(DLG_TEXT_BASE[151], DLG_TEXT_BASE[152]));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[153], DLG_TEXT_BASE[154]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[155], DLG_TEXT_BASE[156]);
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple(DLG_TEXT_BASE[157] + NPChar.Quest.Companion.Price + DLG_TEXT_BASE[158], 
						DLG_TEXT_BASE[159] + NPChar.Quest.Companion.Price + DLG_TEXT_BASE[160]), 
					RandPhraseSimple(DLG_TEXT_BASE[161] + NPChar.Quest.Companion.Price + DLG_TEXT_BASE[162],
						NPChar.Quest.Companion.Price + DLG_TEXT_BASE[163]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[164], DLG_TEXT_BASE[165]),
					RandPhraseSimple(DLG_TEXT_BASE[166], DLG_TEXT_BASE[167]));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[168], DLG_TEXT_BASE[169]),
					RandPhraseSimple(DLG_TEXT_BASE[170], DLG_TEXT_BASE[171]));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = DLG_TEXT_BASE[172];
		link.l1 = DLG_TEXT_BASE[173];
		link.l1.go = "BT_Quest_1";
		link.l2 = DLG_TEXT_BASE[174];
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = DLG_TEXT_BASE[175];
		link.l1 = DLG_TEXT_BASE[176];
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = DLG_TEXT_BASE[177];
		link.l1 = DLG_TEXT_BASE[178];
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = DLG_TEXT_BASE[179];
			link.l1 = DLG_TEXT_BASE[180];
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[181],
									DLG_TEXT_BASE[182]);
		link.l1 = DLG_TEXT_BASE[183];
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = DLG_TEXT_BASE[184];
					link.l1 = DLG_TEXT_BASE[185];
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo(DLG_TEXT_BASE[186]);

						Dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[187], 
							 DLG_TEXT_BASE[188], 
							 DLG_TEXT_BASE[189]) + 
							 PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[190],
									DLG_TEXT_BASE[191],
									DLG_TEXT_BASE[192]), 
								LinkRandPhrase(DLG_TEXT_BASE[193],
									DLG_TEXT_BASE[194],
									DLG_TEXT_BASE[195]));
						link.l1 = DLG_TEXT_BASE[196];
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = DLG_TEXT_BASE[197] + GetFullName(PChar) + DLG_TEXT_BASE[198];
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[199] + GetFullName(pchar) + ".",
						DLG_TEXT_BASE[200] + PChar.Ship.Name + DLG_TEXT_BASE[201] + GetFullName(pchar) + ".") + DLG_TEXT_BASE[202],
					RandPhraseSimple(DLG_TEXT_BASE[203] + GetFullName(pchar) + ".",
						DLG_TEXT_BASE[204] + PChar.Ship.Name + DLG_TEXT_BASE[205] + NationNameGenitive(sti(PChar.nation)) + DLG_TEXT_BASE[206] + GetFullName(pchar) + ".") + DLG_TEXT_BASE[207]);
			//link.l1 = DLG_TEXT_BASE[208];
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = DLG_TEXT_BASE[209] + GetFullName(NPChar) + DLG_TEXT_BASE[210];
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = DLG_TEXT_BASE[211] + GetFullName(NPChar) + DLG_TEXT_BASE[212] + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + NPCharRepPhrase(NPChar, DLG_TEXT_BASE[213], DLG_TEXT_BASE[214]);
		link.l1 = DLG_TEXT_BASE[215];
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		iRnd = rand(3);
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = iRnd;
		PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + rand(2);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = DLG_TEXT_BASE[216] + NPChar.Ship.Name + "'.";
//			link.l1 = DLG_TEXT_BASE[217];
			Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[218], 
								DLG_TEXT_BASE[219]), 
							RandPhraseSimple(DLG_TEXT_BASE[220], 
							DLG_TEXT_BASE[221])) + 
						RandPhraseSimple(DLG_TEXT_BASE[222] + NPChar.Ship.Name + DLG_TEXT_BASE[223], DLG_TEXT_BASE[224] + NPChar.Ship.Name + DLG_TEXT_BASE[225]);
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[226], 
								DLG_TEXT_BASE[227]), 
							RandPhraseSimple(DLG_TEXT_BASE[228], 
								DLG_TEXT_BASE[229]));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = DLG_TEXT_BASE[230] + NPChar.Ship.Name + DLG_TEXT_BASE[231];
			link.l1 = DLG_TEXT_BASE[232];
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[233], 
					RandSwear() + DLG_TEXT_BASE[234]), 
				RandPhraseSimple(DLG_TEXT_BASE[235], 
					DLG_TEXT_BASE[236]));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[237], 
					DLG_TEXT_BASE[238]), 
				RandPhraseSimple(DLG_TEXT_BASE[239], 
					DLG_TEXT_BASE[240]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[241], 
					DLG_TEXT_BASE[242]), 
				RandPhraseSimple(DLG_TEXT_BASE[243], 
					DLG_TEXT_BASE[244]));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[245], 
					DLG_TEXT_BASE[246]), 
				RandPhraseSimple(DLG_TEXT_BASE[247], 
					DLG_TEXT_BASE[248] + GetFullName(NPChar) + DLG_TEXT_BASE[249]));
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[250], 
					DLG_TEXT_BASE[251]), 
				RandPhraseSimple(DLG_TEXT_BASE[252], 
					DLG_TEXT_BASE[253]));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = DLG_TEXT_BASE[254];
		link.l1 = DLG_TEXT_BASE[255];
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[256], 
					DLG_TEXT_BASE[257]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[258], 
					DLG_TEXT_BASE[259]);
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = DLG_TEXT_BASE[260];
//			link.l1 = DLG_TEXT_BASE[261];
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[262], 
					DLG_TEXT_BASE[263]) + 
					DLG_TEXT_BASE[264];
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[265], 
					DLG_TEXT_BASE[266]);
		}
		else
		{
			Dialog.Text = DLG_TEXT_BASE[267];
			link.l1 = DLG_TEXT_BASE[268];
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple(DLG_TEXT_BASE[269], 
					DLG_TEXT_BASE[270]);
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[271], 
					DLG_TEXT_BASE[272]), 
				RandPhraseSimple(DLG_TEXT_BASE[273], 
					DLG_TEXT_BASE[274]));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[275], 
					DLG_TEXT_BASE[276]), 
				RandPhraseSimple(DLG_TEXT_BASE[277], 
					DLG_TEXT_BASE[278]));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = DLG_TEXT_BASE[279];
			link.l1 = DLG_TEXT_BASE[280];
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = DLG_TEXT_BASE[281] + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + DLG_TEXT_BASE[282];
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += DLG_TEXT_BASE[283];
			PChar.GenQuest.PGG_Quest.Goods.Text = DLG_TEXT_BASE[284];
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "Gen");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	DLG_TEXT_BASE[285] + sLoc + DLG_TEXT_BASE[286] + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + DLG_TEXT_BASE[287];
		}
		else
		{
			sTmp += DLG_TEXT_BASE[288] + sLoc + DLG_TEXT_BASE[289] + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + 
				DLG_TEXT_BASE[290];
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[291], 
					DLG_TEXT_BASE[292]), 
				RandPhraseSimple(DLG_TEXT_BASE[293], 
					DLG_TEXT_BASE[294]));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[295] + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + DLG_TEXT_BASE[296], 
					DLG_TEXT_BASE[297]), 
				RandPhraseSimple(DLG_TEXT_BASE[298] + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + DLG_TEXT_BASE[299], 
					DLG_TEXT_BASE[300] + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = DLG_TEXT_BASE[301];
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = DLG_TEXT_BASE[302] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + DLG_TEXT_BASE[303];
			Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[304] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + DLG_TEXT_BASE[305], 
						DLG_TEXT_BASE[306] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + DLG_TEXT_BASE[307]), 
					RandPhraseSimple(DLG_TEXT_BASE[308] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + DLG_TEXT_BASE[309], 
						DLG_TEXT_BASE[310] + PChar.Name + DLG_TEXT_BASE[311] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "."));
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[312], DLG_TEXT_BASE[313]);
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = DLG_TEXT_BASE[314];
			link.l1 = DLG_TEXT_BASE[315] + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + DLG_TEXT_BASE[316];
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = DLG_TEXT_BASE[317];
		link.l1 = DLG_TEXT_BASE[318];
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + DLG_TEXT_BASE[319]+ RandPhraseSimple(DLG_TEXT_BASE[320], DLG_TEXT_BASE[321]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[322], 
					DLG_TEXT_BASE[323]), 
				RandPhraseSimple(DLG_TEXT_BASE[324], 
					DLG_TEXT_BASE[325]));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[326], 
					DLG_TEXT_BASE[327]), 
				RandPhraseSimple(DLG_TEXT_BASE[328], 
					DLG_TEXT_BASE[329]));
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[330] + GetFullName(PChar) + DLG_TEXT_BASE[331], 
					DLG_TEXT_BASE[332]), 
				RandPhraseSimple(DLG_TEXT_BASE[333], 
					DLG_TEXT_BASE[334]));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[335], 
					DLG_TEXT_BASE[336]), 
				RandPhraseSimple(DLG_TEXT_BASE[337], 
					DLG_TEXT_BASE[338]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[339] + GetFullName(NPChar) + "!!!", 
					DLG_TEXT_BASE[340]), 
				RandPhraseSimple(DLG_TEXT_BASE[341], 
					DLG_TEXT_BASE[342]));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = DLG_TEXT_BASE[343] + GetFullName(PChar) + DLG_TEXT_BASE[344];
		Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[345] + GetFullName(PChar) + DLG_TEXT_BASE[346], 
					DLG_TEXT_BASE[347] + GetFullName(PChar) + DLG_TEXT_BASE[348]), 
				RandPhraseSimple(DLG_TEXT_BASE[349] + GetFullName(PChar) + ".", 
					DLG_TEXT_BASE[350]))
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[351], 
					DLG_TEXT_BASE[352]), 
				RandPhraseSimple(DLG_TEXT_BASE[353], 
					DLG_TEXT_BASE[354]));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = DLG_TEXT_BASE[355] + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + ".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[356] + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + DLG_TEXT_BASE[357], 
						DLG_TEXT_BASE[358] + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + DLG_TEXT_BASE[359]), 
					RandPhraseSimple(DLG_TEXT_BASE[360] + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + DLG_TEXT_BASE[361], 
						DLG_TEXT_BASE[362] + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + DLG_TEXT_BASE[363]));
			link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[364], 
						DLG_TEXT_BASE[365]), 
					RandPhraseSimple(DLG_TEXT_BASE[366], 
						DLG_TEXT_BASE[367]));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[368], 
								DLG_TEXT_BASE[369]), 
							RandPhraseSimple(DLG_TEXT_BASE[370], 
								DLG_TEXT_BASE[371]));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = DLG_TEXT_BASE[372];
			link.l1 = DLG_TEXT_BASE[373];
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = DLG_TEXT_BASE[374] + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + DLG_TEXT_BASE[375];
			Dialog.Text = PCharRepPhrase(DLG_TEXT_BASE[376] + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", 
					DLG_TEXT_BASE[377] + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text + PCharRepPhrase(DLG_TEXT_BASE[378], DLG_TEXT_BASE[379]);
			}
			else
			{
				Dialog.Text = Dialog.Text + DLG_TEXT_BASE[380];
			}
			Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
			link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[381], DLG_TEXT_BASE[382]), 
					RandPhraseSimple(DLG_TEXT_BASE[383], DLG_TEXT_BASE[384]));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[385], 
						DLG_TEXT_BASE[386]), 
					RandPhraseSimple(DLG_TEXT_BASE[387], 
						DLG_TEXT_BASE[388]));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[389], 
					DLG_TEXT_BASE[390]), 
				RandPhraseSimple(DLG_TEXT_BASE[391], 
					DLG_TEXT_BASE[392]));
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[393], DLG_TEXT_BASE[394]), 
				RandPhraseSimple(DLG_TEXT_BASE[395], 
					DLG_TEXT_BASE[396]));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[397], 
						DLG_TEXT_BASE[398]), 
					RandPhraseSimple(DLG_TEXT_BASE[399], 
						DLG_TEXT_BASE[400] + GetFullName(PChar) + DLG_TEXT_BASE[401]));
			link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[402], 
						DLG_TEXT_BASE[403] + GetFullName(PChar) + "! "), 
					RandPhraseSimple(DLG_TEXT_BASE[404], 
						DLG_TEXT_BASE[405]));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = DLG_TEXT_BASE[406];
		link.l1 = DLG_TEXT_BASE[407];
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = DLG_TEXT_BASE[408];
		link.l1 = DLG_TEXT_BASE[409];
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase(DLG_TEXT_BASE[410] + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", DLG_TEXT_BASE[411] + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text + DLG_TEXT_BASE[412];
		}
		else
		{
			Dialog.Text = Dialog.Text + DLG_TEXT_BASE[413];
		}
		Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[414], DLG_TEXT_BASE[415]), 
			RandPhraseSimple(DLG_TEXT_BASE[416], DLG_TEXT_BASE[417]));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
