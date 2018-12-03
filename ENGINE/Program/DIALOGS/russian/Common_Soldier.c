// boal 25/04/04 общий диалог солдат
#include "TEXT\DIALOGS\Common_Soldier.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]);
					link.l1.go = "fight"; 
					break;
				} 
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]);
				link.l1.go = "fight"; 
				// ==> eddy. Засада, если опознали в инквизиции.
				if (Pchar.location == "Santiago_Incquisitio") StartIncquisitioAttack();
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]);
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = DLG_TEXT_BASE[10] + GetRusNameNationLicence(sti(npchar.nation)) + DLG_TEXT_BASE[11];
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = DLG_TEXT_BASE[12] + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l2 = DLG_TEXT_BASE[13] + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + DLG_TEXT_BASE[14] + NationNameGenitive(sti(pchar.nation)) + DLG_TEXT_BASE[15];
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (20+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[18], DLG_TEXT_BASE[19]);
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = DLG_TEXT_BASE[20] + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l1 = DLG_TEXT_BASE[21] + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + DLG_TEXT_BASE[22] + NationNameGenitive(sti(pchar.nation)) + DLG_TEXT_BASE[23];
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (20+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = DLG_TEXT_BASE[24];
									link.l1 = DLG_TEXT_BASE[25];
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = DLG_TEXT_BASE[26];
									link.l1 = DLG_TEXT_BASE[27];
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = DLG_TEXT_BASE[28];
									link.l1 = DLG_TEXT_BASE[29];
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = DLG_TEXT_BASE[30];
									link.l1 = DLG_TEXT_BASE[31];
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = DLG_TEXT_BASE[32];
									link.l1 = DLG_TEXT_BASE[33];
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = DLG_TEXT_BASE[34];
									link.l1 = DLG_TEXT_BASE[35];
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = DLG_TEXT_BASE[36];
									link.l1 = DLG_TEXT_BASE[37];
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = DLG_TEXT_BASE[38];
									link.l1 = DLG_TEXT_BASE[39];
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = DLG_TEXT_BASE[40];
									link.l1 = DLG_TEXT_BASE[41];
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = DLG_TEXT_BASE[42];
									link.l1 = DLG_TEXT_BASE[43];
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = DLG_TEXT_BASE[44];
									link.l1 = DLG_TEXT_BASE[45];
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple(DLG_TEXT_BASE[46], DLG_TEXT_BASE[47]);
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
						else
						{ // пираты, не наши
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[48], DLG_TEXT_BASE[49]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]);
							link.l1.go = "exit";
							link.l2 = RandPhraseSimple(DLG_TEXT_BASE[52], DLG_TEXT_BASE[53]);
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple(DLG_TEXT_BASE[54] + XI_ConvertString("Colony" + npchar.city)+ DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
							link.l1.go = "fight";
							break;						
						}
					}
					//зачарованный город -->
					if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
					{
						dialog.text = LinkRandPhrase(DLG_TEXT_BASE[59], 
							DLG_TEXT_BASE[60], 
							DLG_TEXT_BASE[61]);
						link.l1 = DLG_TEXT_BASE[62];
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
					{
						dialog.text = DLG_TEXT_BASE[63];
						link.l1 = DLG_TEXT_BASE[64];
						link.l1.go = "exit";
						break;
					}
					//<-- зачарованный город 
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[65];
							link.l1 = DLG_TEXT_BASE[66];
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = DLG_TEXT_BASE[67];
							link.l1 = DLG_TEXT_BASE[68];
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[69];
							link.l1 = DLG_TEXT_BASE[70];
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = DLG_TEXT_BASE[71];
							link.l1 = DLG_TEXT_BASE[72];
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[73];
							link.l1 = DLG_TEXT_BASE[74];
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[75];
							link.l1 = DLG_TEXT_BASE[76];
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[77];
							link.l1 = DLG_TEXT_BASE[78];
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = DLG_TEXT_BASE[79];
							link.l1 = DLG_TEXT_BASE[80];
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[81];
							link.l1 = DLG_TEXT_BASE[82];
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[83];
							link.l1 = DLG_TEXT_BASE[84];
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = DLG_TEXT_BASE[85];
							link.l1 = DLG_TEXT_BASE[86];
							link.l1.go = "exit";
						break;
					}
					link.l3 = DLG_TEXT_BASE[87];
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[88], DLG_TEXT_BASE[89] + GetAddress_Form(npchar) + DLG_TEXT_BASE[90]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[91], DLG_TEXT_BASE[92]);
			link.l1.go = "fight";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80); // враг, которого узнали - потом будет умнее - бонус в скрытность
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[93] + GetAddress_Form(pchar) + ".", DLG_TEXT_BASE[94] + GetAddress_Form(pchar) + DLG_TEXT_BASE[95]);
			link.l1 = DLG_TEXT_BASE[96];
			link.l1.go = "exit";
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = DLG_TEXT_BASE[97];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[98], DLG_TEXT_BASE[99]);
				link.l1.go = "fight";	
				TakeNationLicence(sti(npchar.nation));
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20); // враг, которого узнали - потом будет умнее - бонус в скрытность
			}
			if (iTemp == 0)
			{
				dialog.text = DLG_TEXT_BASE[100];
				link.l1 = DLG_TEXT_BASE[101];
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = DLG_TEXT_BASE[102] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[103] + GetAddress_Form(npchar) + ".";
				link.l1 = DLG_TEXT_BASE[104];
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[105] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[106], DLG_TEXT_BASE[107]+GetAddress_Form(npchar)+DLG_TEXT_BASE[108] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[109], DLG_TEXT_BASE[110] + GetAddress_Form(npchar) + DLG_TEXT_BASE[111]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[112], DLG_TEXT_BASE[113]);
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[114], DLG_TEXT_BASE[115]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[116], DLG_TEXT_BASE[117]);
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[118], DLG_TEXT_BASE[119], DLG_TEXT_BASE[120]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[121], DLG_TEXT_BASE[122]);
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице ==================
		case "SeekSpy_Checking":
			dialog.text = DLG_TEXT_BASE[123] + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], DLG_TEXT_BASE[124], DLG_TEXT_BASE[125]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[126], DLG_TEXT_BASE[127]);
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;

		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[128], DLG_TEXT_BASE[129], DLG_TEXT_BASE[130]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[131], DLG_TEXT_BASE[132], DLG_TEXT_BASE[133]);
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[134], DLG_TEXT_BASE[135], DLG_TEXT_BASE[136]);
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

	}
}
