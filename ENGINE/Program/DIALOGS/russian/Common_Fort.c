// boal 25/04/04 общий диалог солдат форта
#include "TEXT\DIALOGS\Common_Fort.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[2], DLG_TEXT_BASE[3]);
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]);
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = DLG_TEXT_BASE[6] + GetRusNameNationLicence(sti(npchar.nation)) + DLG_TEXT_BASE[7];
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple(DLG_TEXT_BASE[8], DLG_TEXT_BASE[9]);
							link.l1 = RandPhraseSimple(DLG_TEXT_BASE[10], DLG_TEXT_BASE[11]);
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = DLG_TEXT_BASE[12] + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l1 = DLG_TEXT_BASE[13] + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + DLG_TEXT_BASE[14] + NationNameGenitive(sti(pchar.nation)) + DLG_TEXT_BASE[15];
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
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = DLG_TEXT_BASE[16];
									link.l1 = DLG_TEXT_BASE[17];
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = DLG_TEXT_BASE[18];
									link.l1 = DLG_TEXT_BASE[19];
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = DLG_TEXT_BASE[20];
									link.l1 = DLG_TEXT_BASE[21];
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = DLG_TEXT_BASE[22];
									link.l1 = DLG_TEXT_BASE[23];
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = DLG_TEXT_BASE[24];
									link.l1 = DLG_TEXT_BASE[25];
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = DLG_TEXT_BASE[26];
									link.l1 = DLG_TEXT_BASE[27];
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = DLG_TEXT_BASE[28];
									link.l1 = DLG_TEXT_BASE[29];
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = DLG_TEXT_BASE[30];
									link.l1 = DLG_TEXT_BASE[31];
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = DLG_TEXT_BASE[32];
									link.l1 = DLG_TEXT_BASE[33];
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = DLG_TEXT_BASE[34];
									link.l1 = DLG_TEXT_BASE[35];
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = DLG_TEXT_BASE[36];
									link.l1 = DLG_TEXT_BASE[37];
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple(DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[40];
							link.l1 = DLG_TEXT_BASE[41];
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = DLG_TEXT_BASE[42];
							link.l1 = DLG_TEXT_BASE[43];
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[44];
							link.l1 = DLG_TEXT_BASE[45];
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = DLG_TEXT_BASE[46];
							link.l1 = DLG_TEXT_BASE[47];
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[48];
							link.l1 = DLG_TEXT_BASE[49];
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[50];
							link.l1 = DLG_TEXT_BASE[51];
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[52];
							link.l1 = DLG_TEXT_BASE[53];
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = DLG_TEXT_BASE[54];
							link.l1 = DLG_TEXT_BASE[55];
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[56];
							link.l1 = DLG_TEXT_BASE[57];
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = DLG_TEXT_BASE[58];
							link.l1 = DLG_TEXT_BASE[59];
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = DLG_TEXT_BASE[60];
							link.l1 = DLG_TEXT_BASE[61];
							link.l1.go = "exit";
						break;
					}
					link.l3 = DLG_TEXT_BASE[62];
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[63], DLG_TEXT_BASE[64] + GetAddress_Form(npchar) + DLG_TEXT_BASE[65]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[66], DLG_TEXT_BASE[67]);
			link.l1.go = "fight";
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80); // враг, которого узнали - потом будет умнее - бонус в скрытность
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[68] + GetAddress_Form(pchar) + ".", DLG_TEXT_BASE[69] + GetAddress_Form(pchar) + DLG_TEXT_BASE[70]);
			link.l1 = DLG_TEXT_BASE[71];
			link.l1.go = "exit";
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = DLG_TEXT_BASE[72];
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74]);
				link.l1.go = "fight";	
				TakeNationLicence(sti(npchar.nation));
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20); // враг, которого узнали - потом будет умнее - бонус в скрытность
			}
			if (iTemp == 0)
			{
				dialog.text = DLG_TEXT_BASE[75];
				link.l1 = DLG_TEXT_BASE[76];
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = DLG_TEXT_BASE[77] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[78] + GetAddress_Form(npchar) + ".";
				link.l1 = DLG_TEXT_BASE[79];
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase(DLG_TEXT_BASE[80] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[81], DLG_TEXT_BASE[82]+GetAddress_Form(npchar)+DLG_TEXT_BASE[83] + FindRussianDaysString(iTemp) + DLG_TEXT_BASE[84], DLG_TEXT_BASE[85] + GetAddress_Form(npchar) + DLG_TEXT_BASE[86]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]);
				link.l1.go = "exit";
			}
		break;

		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[89], DLG_TEXT_BASE[90], DLG_TEXT_BASE[91]);
			link.l1 = LinkRandPhrase(DLG_TEXT_BASE[92], DLG_TEXT_BASE[93], DLG_TEXT_BASE[94]);
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[95], DLG_TEXT_BASE[96], DLG_TEXT_BASE[97]);
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
