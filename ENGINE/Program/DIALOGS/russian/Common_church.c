// boal 25/04/04 общий диалог церковь
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_church.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				Dialog.Text = DLG_TEXT_BASE[10];
				link.l1 = DLG_TEXT_BASE[11];
				link.l1.go = "node_3";
				Link.l2 = DLG_TEXT_BASE[12];
				Link.l2.go = "node_2";
			}
			else
			{
				Dialog.Text = DLG_TEXT_BASE[13];
				Link.l1 = DLG_TEXT_BASE[14];
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = DLG_TEXT_BASE[15];
			link.l1 = DLG_TEXT_BASE[16];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = DLG_TEXT_BASE[17];
			//зачарованный город -->
  			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				link.l1 = DLG_TEXT_BASE[18];
				link.l1.go = "MC_CaracasChirch";
				break;
			}
  			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = DLG_TEXT_BASE[19];
				link.l1 = DLG_TEXT_BASE[20];
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город 
			//homo Ћинейка Ѕлада
            if (Pchar.questTemp.CapBloodLine != true)
            {
    			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[21], DLG_TEXT_BASE[22]);
    			link.l1.go = "donation";
    			link.l2 = RandPhraseSimple(DLG_TEXT_BASE[23],DLG_TEXT_BASE[24]+RandPhraseSimple(DLG_TEXT_BASE[25], DLG_TEXT_BASE[26]));
    			link.l2.go = "ispoved";
    			link.l3 = RandPhraseSimple(DLG_TEXT_BASE[27] + RandPhraseSimple(DLG_TEXT_BASE[28], DLG_TEXT_BASE[29]),
                                           DLG_TEXT_BASE[30] + RandPhraseSimple(DLG_TEXT_BASE[31], DLG_TEXT_BASE[32]));
    			link.l3.go = "work";//"quest lines";
            }

			link.l6 = DLG_TEXT_BASE[33];
			link.l6.go = "exit";
		break;

		case "donation":
			dialog.Text = DLG_TEXT_BASE[34];
			Link.l1 = DLG_TEXT_BASE[35];
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = DLG_TEXT_BASE[36];
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = DLG_TEXT_BASE[37];
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = DLG_TEXT_BASE[38];
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвовани€ хоз€йки бордел€
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = DLG_TEXT_BASE[39];
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвовани€ хоз€йки бордел€
		break;

		case "No donation":
			dialog.Text = DLG_TEXT_BASE[40];
			Link.l1 = DLG_TEXT_BASE[41];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[42];
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = DLG_TEXT_BASE[43];
			Link.l1 = DLG_TEXT_BASE[44];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[45];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = DLG_TEXT_BASE[46];
            Link.l1 = DLG_TEXT_BASE[47];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[48];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = DLG_TEXT_BASE[49];
            Link.l1 = DLG_TEXT_BASE[50];
			Link.l1.go = "node_3";
			Link.l2 = DLG_TEXT_BASE[51];
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[54];
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = DLG_TEXT_BASE[55];
			link.l1 = DLG_TEXT_BASE[56];
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = DLG_TEXT_BASE[57] + NationNameGenitive(sti(NPChar.nation)) + "?";
			link.l1 = DLG_TEXT_BASE[58];
			link.l1.go = "ispoved_3";
			link.l2 = DLG_TEXT_BASE[59];
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = DLG_TEXT_BASE[60];
			link.l1 = DLG_TEXT_BASE[61];
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = DLG_TEXT_BASE[62];
			link.l1 = DLG_TEXT_BASE[63];
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
			dialog.text = DLG_TEXT_BASE[64];
			link.l1 = DLG_TEXT_BASE[65];
			link.l1.go = "quests"; // ссылка к Ќѕ—
            link.l2 = RandPhraseSimple(DLG_TEXT_BASE[66] + NationNameGenitive(sti(NPChar.nation)) + ".",
                                        DLG_TEXT_BASE[67]);
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple(DLG_TEXT_BASE[68], DLG_TEXT_BASE[69]) + DLG_TEXT_BASE[70]; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = DLG_TEXT_BASE[71];
                link.l4.go = "healthAdd_1";
            }
            //==> ¬ставка Ёдди, квест јззи, возможность сдачи лампы.
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
                link.l6 = DLG_TEXT_BASE[72];
                link.l6.go = "GiveLamp";
            }
			//<== ¬ставка Ёдди, квест јззи возможность сдачи лампы.
			//квест мэра - на св€зь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74]) + DLG_TEXT_BASE[75] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//==> успокоить нечисть в пещерах
			if (CheckAttribute(npchar, "DestroyGhost") && npchar.DestroyGhost == "GoodResult")
			{
				switch (npchar.quest.DestroyGhost.label)
				{
					if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[76]) sTemp = DLG_TEXT_BASE[77];
					if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[78]) sTemp = DLG_TEXT_BASE[79];
					if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[80]) sTemp = DLG_TEXT_BASE[81];
				}
				link.l5 = DLG_TEXT_BASE[82] + sTemp + DLG_TEXT_BASE[83];
                link.l5.go = "GhostShip_S1";
			}
			//==> ночной сторож в церкви
			if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different.Church_NightGuard == npchar.location)
			{
	            link.l8 = RandPhraseSimple(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85]) + DLG_TEXT_BASE[86];
	            link.l8.go = "NightGuard_result";
            }
			//<== ночной сторож в церкви
			link.l99 = DLG_TEXT_BASE[87];
			link.l99.go = "exit";
		break;

		case "prihod":
			//упокоение нечисти
			if (rand(2)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.DestroyGhost") && GetNpcQuestPastDayWOInit(npchar, "Ghost") > 7)
			{
                dialog.text = DLG_TEXT_BASE[88];
        		link.l1 = RandPhraseSimple(DLG_TEXT_BASE[89],
                                            DLG_TEXT_BASE[90]);
        		link.l1.go = "DestroyGhost_1";
				SaveCurrentNpcQuestDateParam(npchar, "Ghost");
				break;
			}
			//караулить церковь ночью
			if (rand(4)==1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.GuardNightChurch") && !CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && GetNpcQuestPastDayWOInit(npchar, "NightChurch") > 60 && GetHour() < 23)
			{
                dialog.text = DLG_TEXT_BASE[91];
        		link.l1 = DLG_TEXT_BASE[92];
				link.l1.go = "NightChurch_1";
				SaveCurrentNpcQuestDateParam(npchar, "NightChurch");
				break;
			}
            dialog.text = DLG_TEXT_BASE[93];
    		link.l1 = DLG_TEXT_BASE[94];
    		link.l1.go = "exit";
		break;
		//--->> успокоить нечисть
		case "DestroyGhost_1":
			npchar.quest.DestroyGhost = "toCave"; //личный флаг св€щенника на вз€тый квест
			//получим пещеру дл€ чистки
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			npchar.quest.DestroyGhost.locationId = GetAttributeName(aPlace_2); //Id целевой пещеры
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
            npchar.quest.DestroyGhost.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземель€ дл€ диалогов
			switch (npchar.quest.DestroyGhost.label)
			{
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[95]) sTemp = DLG_TEXT_BASE[96];
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[97]) sTemp = DLG_TEXT_BASE[98];
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[99]) sTemp = DLG_TEXT_BASE[100];
			}
			dialog.text = DLG_TEXT_BASE[101] + sTemp + DLG_TEXT_BASE[102];
			link.l1 = DLG_TEXT_BASE[103];
			link.l1.go = "DestroyGhost_2";
		break;
		case "DestroyGhost_2":
			dialog.text = DLG_TEXT_BASE[104];
			link.l1 = DLG_TEXT_BASE[105];
			link.l1.go = "DestroyGhost_3";
			link.l2 = DLG_TEXT_BASE[106];
			link.l2.go = "DestroyGhost_out";
		break;
		case "DestroyGhost_out":
			dialog.text = DLG_TEXT_BASE[107];
			link.l1 = DLG_TEXT_BASE[108];
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DestroyGhost");
			ChangeCharacterReputation(pchar, -3);
		break;
		case "DestroyGhost_3":
			dialog.text = DLG_TEXT_BASE[109];
			link.l1 = DLG_TEXT_BASE[110];
			link.l1.go = "exit";
			pchar.questTemp.different = "DestroyGhost";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			//флаг квеста на локацию, сюда же пишем индекс дающего св€щенника
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sld.DestroyGhost = npchar.index; 
			sTitle = sld.id + "Church_DestroyGhost";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "1");
			AddQuestUserDataForTitle(sTitle, "sLocation", GetStrSmallRegister(npchar.quest.DestroyGhost.label));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sLocation", npchar.quest.DestroyGhost.label);
		break;

		case "GhostShip_S1":
			dialog.text = DLG_TEXT_BASE[111] + NationNameGenitive(sti(NPChar.nation)) + DLG_TEXT_BASE[112];
			link.l1 = DLG_TEXT_BASE[113];
			link.l1.go = "GhostShip_S2";
		break;
		case "GhostShip_S2":
			dialog.text = DLG_TEXT_BASE[114];
			link.l1 = DLG_TEXT_BASE[115];
			link.l1.go = "exit";
			switch (npchar.quest.DestroyGhost.label)
			{
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[116]) sTemp = DLG_TEXT_BASE[117];
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[118]) sTemp = DLG_TEXT_BASE[118];
				if (npchar.quest.DestroyGhost.label == DLG_TEXT_BASE[119]) sTemp = DLG_TEXT_BASE[119];
			}
			AddSimpleRumourCity(LinkRandPhrase(DLG_TEXT_BASE[120] + GetFullName(npchar) + DLG_TEXT_BASE[121] + sTemp + DLG_TEXT_BASE[122], 
				DLG_TEXT_BASE[123] + sTemp + DLG_TEXT_BASE[124], 
				DLG_TEXT_BASE[125] + sTemp + DLG_TEXT_BASE[126]), npchar.city, 10, 1, "");
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sTitle = sld.id + "Church_DestroyGhost";
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.DestroyGhost");
		break;
        //<<--- успокоить нечисть
		//--->> ночной сторож
		case "NightChurch_1":
			dialog.text = DLG_TEXT_BASE[127];
			link.l1 = DLG_TEXT_BASE[128];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[129];
			link.l2.go = "NightChurch_2";
		break;
		case "NightChurch_2":
			dialog.text = DLG_TEXT_BASE[130];
			link.l1 = DLG_TEXT_BASE[131];
			link.l1.go = "NightChurch_3";
		break;
		case "NightChurch_3":
			dialog.text = DLG_TEXT_BASE[132];
			link.l1 = DLG_TEXT_BASE[133];
			link.l1.go = "exit";
			pchar.questTemp.different = "Church_NightGuard";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			pchar.questTemp.different.Church_NightGuard = npchar.location; //флаг срабатывани€ нул€ часов
			pchar.questTemp.different.Church_NightGuard.NightQty = 0; //кол-вот отработанных ночей
			pchar.questTemp.different.Church_NightGuard.chance = rand(3); //рендом на по€вление грабителей
			pchar.questTemp.different.Church_NightGuard.fight = false; //флаг боевки
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //запишем дату
			sTitle = npchar.location + "Church_NightGuard";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_NightGuard", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "NightGuard_result":
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0)
			{
				dialog.text = DLG_TEXT_BASE[134];
				link.l1 = DLG_TEXT_BASE[135];
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) > 0 && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				dialog.text = DLG_TEXT_BASE[136];
				link.l1 = DLG_TEXT_BASE[137];
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
			{
				if (sti(pchar.questTemp.different.Church_NightGuard.fight))
				{
					dialog.text = DLG_TEXT_BASE[138];
					link.l1 = DLG_TEXT_BASE[139];
					link.l1.go = "NightGuard_fight";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[140];
					link.l1 = DLG_TEXT_BASE[141];
					link.l1.go = "NightGuard_noLook";
				}
			}
		break;

		case "NightGuard_noLook":
			dialog.text = DLG_TEXT_BASE[142] + NationNameAblative(sti(npchar.nation)) + DLG_TEXT_BASE[143];
			link.l1 = DLG_TEXT_BASE[144];
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddSimpleRumourCity(LinkRandPhrase(DLG_TEXT_BASE[145], 
				DLG_TEXT_BASE[146], 
				DLG_TEXT_BASE[147] + GetFullName(npchar) + DLG_TEXT_BASE[148]), npchar.city, 10, 1, "");
		break;
		case "NightGuard_fight":
			dialog.text = DLG_TEXT_BASE[149] + NationNameAblative(sti(npchar.nation)) + DLG_TEXT_BASE[150];
			link.l1 = DLG_TEXT_BASE[151];
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddCharacterMaxHealth(pchar, 2);
			AddSimpleRumourCity(LinkRandPhrase(DLG_TEXT_BASE[152], 
				DLG_TEXT_BASE[153], 
				DLG_TEXT_BASE[154] + GetFullName(npchar) + DLG_TEXT_BASE[155]), npchar.city, 10, 1, "");
		break;

		//<<--- ночной сторож

        case "healthAdd_1":
            if (GetHealthMaxNum(pchar) == 6) // отлично
            {
                dialog.text = DLG_TEXT_BASE[156] + GetHealthNameMaxSmall(pchar) + DLG_TEXT_BASE[157];
    			link.l1 = DLG_TEXT_BASE[158];
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = DLG_TEXT_BASE[159] + GetHealthNameMaxSmall(pchar) + DLG_TEXT_BASE[160];
    			link.l1 = DLG_TEXT_BASE[161];
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = DLG_TEXT_BASE[162];
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = DLG_TEXT_BASE[163];
			link.l1 = DLG_TEXT_BASE[164];
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = DLG_TEXT_BASE[165];
			link.l1 = DLG_TEXT_BASE[166];
			link.l1.go = "healthAdd_3";
			link.l2 = DLG_TEXT_BASE[167];
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = DLG_TEXT_BASE[168];
    			link.l1 = pcharrepphrase(DLG_TEXT_BASE[169], DLG_TEXT_BASE[170]);
    			link.l1.go = "healthAdd_4";
    			link.l2 = DLG_TEXT_BASE[171];
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[172];
    			link.l1    = DLG_TEXT_BASE[173]+RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]);
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = DLG_TEXT_BASE[176];
			link.l1 = pcharrepphrase(DLG_TEXT_BASE[177], DLG_TEXT_BASE[178]);
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = DLG_TEXT_BASE[179];
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не провер€ть, тк €вно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = DLG_TEXT_BASE[180];
			link.l1 = DLG_TEXT_BASE[181];
			link.l1.go = "exit";
		break;
		// диалог дл€ капелата из тюр€ги
		case "Prison_Temp":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = DLG_TEXT_BASE[182];
			link.l1 = DLG_TEXT_BASE[183];
			link.l1.go = "Exit";
		break;

		case "Prison_Cell":
            NextDiag.TempNode = "Prison_Temp";
			dialog.text = DLG_TEXT_BASE[184];
			link.l1 = DLG_TEXT_BASE[185];
			link.l1.go = "Prison_Cell_Info";
			link.l2 = DLG_TEXT_BASE[186];
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = DLG_TEXT_BASE[187];
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info":
			dialog.text = DLG_TEXT_BASE[188];
			link.l1 = DLG_TEXT_BASE[189];
			link.l1.go = "Prison_Cell_Info_2";
			link.l2 = DLG_TEXT_BASE[190];
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = DLG_TEXT_BASE[191];
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info_2":
			dialog.text = DLG_TEXT_BASE[192];
			link.l2 = DLG_TEXT_BASE[193];
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = DLG_TEXT_BASE[194];
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_None":
			dialog.text = DLG_TEXT_BASE[195];
			link.l1 = DLG_TEXT_BASE[196];
			link.l1.go = "Prison_Cell_death";//"Exit";
			//AddDialogExitQuest("MoveToPrison_Cell");
		break;

		case "Prison_Cell_Talk":
			dialog.text = DLG_TEXT_BASE[197];
			link.l2 = DLG_TEXT_BASE[198];
			link.l2.go = "Prison_Cell_Talk_2";
			link.l3 = DLG_TEXT_BASE[199];
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Talk_2":
			dialog.text = DLG_TEXT_BASE[200];
			link.l1 = DLG_TEXT_BASE[201];
			link.l1.go = "Prison_Cell_death";
		break;

		case "Prison_Cell_death":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   			sld = &Characters[sti(PChar.GenQuest.ToPrisonCmdIdx)];
			// to_do DeathExecutionStart(Pchar, sti(sld.nation));
		break;
		//квест пожертвовани€ хоз€йки бордел€
		case "HostessChurch":
			dialog.text = DLG_TEXT_BASE[202];
			link.l1 = DLG_TEXT_BASE[203];
			link.l1.go = "HostessChurch_call";
			link.l2 = DLG_TEXT_BASE[204];
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = DLG_TEXT_BASE[205];
					link.l1 = DLG_TEXT_BASE[206];
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[207];
					link.l1 = DLG_TEXT_BASE[208];
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = DLG_TEXT_BASE[209];
					link.l1 = DLG_TEXT_BASE[210];
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = DLG_TEXT_BASE[211];
					link.l1 = DLG_TEXT_BASE[212];
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = DLG_TEXT_BASE[213];
				link.l1 = DLG_TEXT_BASE[214];
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[215];
				link.l1 = DLG_TEXT_BASE[216];
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = DLG_TEXT_BASE[217];
			link.l1 = DLG_TEXT_BASE[218];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачна€ или неудачна€ попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_ok_1":
			dialog.text = DLG_TEXT_BASE[219];
			link.l1 = DLG_TEXT_BASE[220];
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачна€ или неудачна€ попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_bad":
			dialog.text = DLG_TEXT_BASE[221];
			link.l1 = DLG_TEXT_BASE[222];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачна€ или неудачна€ попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_1":
			dialog.text = DLG_TEXT_BASE[223];
			link.l1 = DLG_TEXT_BASE[224];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачна€ или неудачна€ попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_2":
			dialog.text = DLG_TEXT_BASE[225];
			link.l1 = DLG_TEXT_BASE[226];
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачна€ или неудачна€ попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		//зачарованный город. базар падре в  аракасе
		case "MC_CaracasChirch":
			dialog.text = DLG_TEXT_BASE[227];
			link.l1 = DLG_TEXT_BASE[228];
			link.l1.go = "MC_CaracasChirch_1";
		break;
		case "MC_CaracasChirch_1":
			dialog.text = DLG_TEXT_BASE[229];
			link.l1 = DLG_TEXT_BASE[230];
			link.l1.go = "exit";
			pchar.questTemp.MC = "toCaracasTavern";
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("CaracasCit_"+i);
				sld.lifeDay = 0;
			}
			//дым от костра
			locations[FindLocation("Caracas_town")].hidden_effects = true;
		break;

	}
}
