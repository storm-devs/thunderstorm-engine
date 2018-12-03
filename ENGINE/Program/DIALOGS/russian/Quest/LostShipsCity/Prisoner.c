#include "TEXT\DIALOGS\Quest\LostShipsCity\Prisoner.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	float   locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "prisonerHead":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_LSC[0];
				link.l1 = DLG_TEXT_LSC[1] + GetFullName(pchar) + ".";
				link.l1.go = "FTH_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[2];
				link.l1 = DLG_TEXT_LSC[3];
				link.l1.go = "Exit";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l6 = DLG_TEXT_LSC[4];
						link.l6.go = "LostDecsterHead";
					}
				}
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = DLG_TEXT_LSC[5];
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "seekFreeMotod")
				{
					link.l7 = DLG_TEXT_LSC[6];
					link.l7.go = "ELTHusb_SF";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
				{
					link.l7 = DLG_TEXT_LSC[7];
					link.l7.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = DLG_TEXT_LSC[8];
					link.l8.go = "SeekCrew";
				}
			}			
			NextDiag.TempNode = "prisonerHead";
		break;
		case "FTH_1":
			dialog.text = DLG_TEXT_LSC[9];
			link.l1 = DLG_TEXT_LSC[10];
			link.l1.go = "FTH_2";
		break;
		case "FTH_2":
			dialog.text = DLG_TEXT_LSC[11];
			link.l1 = DLG_TEXT_LSC[12];
			link.l1.go = "FTH_3";
		break;
		case "FTH_3":
			dialog.text = DLG_TEXT_LSC[13];
			link.l1 = DLG_TEXT_LSC[14];
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "prisoner":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = DLG_TEXT_LSC[15] + GetFullName(npchar) + ".";
				link.l1 = DLG_TEXT_LSC[16] + GetFullName(pchar) + ".";
				link.l1.go = "FTP_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[17];
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && npchar.chr_ai.type == LAI_TYPE_SIT && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{				
						link.l1 = DLG_TEXT_LSC[18];
						link.l1.go = "LostDecster";
					}
				}	
				//квест с вином от Доминика Легро
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && CheckCharacterItem(pchar, "potionwine"))
				{
					link.l2 = DLG_TEXT_LSC[19];
					link.l2.go = "WineLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toSecondToPrison")
				{
					link.l2 = DLG_TEXT_LSC[20];
					link.l2.go = "SecondLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "to3ToPrison")
				{
					link.l2 = DLG_TEXT_LSC[21];
					link.l2.go = "LastLegro";
				}
				//помощь тюремщика в наезде на касперов, если Армо убита
				iTemp = GetCharacterIndex("LSCwaitress");
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && CheckAttribute(pchar, "questTemp.LSC.LegroHelp.Armo") && iTemp != -1 && characters[iTemp].name != DLG_TEXT_LSC[22] && pchar.questTemp.LSC == "toSeekMechanik")
				{
					link.l3 = DLG_TEXT_LSC[23];
					link.l3.go = "ArmoIsDead";
				}
				link.l10 = DLG_TEXT_LSC[24];
				link.l10.go = "Exit";
			}			
			NextDiag.TempNode = "prisoner";
		break;
		case "FTP_1":
			dialog.text = DLG_TEXT_LSC[25];
			link.l1 = DLG_TEXT_LSC[26];
			link.l1.go = "exit";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[27], 
				DLG_TEXT_LSC[28], 
				DLG_TEXT_LSC[29],
                DLG_TEXT_LSC[30], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[31], 
				DLG_TEXT_LSC[32],
                DLG_TEXT_LSC[33], 
				DLG_TEXT_LSC[34], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = DLG_TEXT_LSC[35];
			link.l1 = DLG_TEXT_LSC[36];
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = DLG_TEXT_LSC[37];
			link.l1 = DLG_TEXT_LSC[38];
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = DLG_TEXT_LSC[39];
			link.l1 = DLG_TEXT_LSC[40];
			link.l1.go = "exit";
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[41], 
				DLG_TEXT_LSC[42], 
				DLG_TEXT_LSC[43],
                DLG_TEXT_LSC[44], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[45], 
				DLG_TEXT_LSC[46],
                DLG_TEXT_LSC[47], 
				DLG_TEXT_LSC[48], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = DLG_TEXT_LSC[49];
			link.l1 = DLG_TEXT_LSC[50];
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = DLG_TEXT_LSC[51];
			link.l1 = DLG_TEXT_LSC[52];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "3");
		break;

		case "ELTHusb_SF":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_LSC[53], 
				DLG_TEXT_LSC[54], 
				DLG_TEXT_LSC[55],
                DLG_TEXT_LSC[56], "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_LSC[57], 
				DLG_TEXT_LSC[58],
                DLG_TEXT_LSC[59], 
				DLG_TEXT_LSC[60], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_SF_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_SF_1":
			dialog.text = DLG_TEXT_LSC[61];
			link.l1 = DLG_TEXT_LSC[62];
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "4");
		break;

		case "LostDecsterHead":
			dialog.text = DLG_TEXT_LSC[63];
			link.l1 = DLG_TEXT_LSC[64];
			link.l1.go = "LostDecsterHead_1";
		break;
		case "LostDecsterHead_1":
			dialog.text = DLG_TEXT_LSC[65];
			link.l1 = DLG_TEXT_LSC[66];
			link.l1.go = "LostDecsterHead_2";
		break;
		case "LostDecsterHead_2":
			dialog.text = DLG_TEXT_LSC[67];
			link.l1 = DLG_TEXT_LSC[68];
			link.l1.go = "LostDecsterHead_3";
		break;
		case "LostDecsterHead_3":
			dialog.text = DLG_TEXT_LSC[69];
			link.l1 = DLG_TEXT_LSC[70];
			link.l1.go = "exit";
			npchar.quest.decster = true; //не повторять базар
		break;

		case "LostDecster":
			dialog.text = DLG_TEXT_LSC[71];
			link.l1 = DLG_TEXT_LSC[72];
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = DLG_TEXT_LSC[73];
			link.l1 = DLG_TEXT_LSC[74];
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "4");	
			npchar.quest.decster = true; //не повторять базар
		break;
		//вино от Доминика Легро
		case "WineLogro":
			dialog.text = DLG_TEXT_LSC[75];
			link.l1 = DLG_TEXT_LSC[76];
			link.l1.go = "WineLogro_1";
		break;
		case "WineLogro_1":
			dialog.text = DLG_TEXT_LSC[77];
			link.l1 = DLG_TEXT_LSC[78];
			link.l1.go = "WineLogro_2";
			TakeItemFromCharacter(pchar, "potionwine");
		break;
		case "WineLogro_2":
			dialog.text = DLG_TEXT_LSC[79];
			link.l1 = DLG_TEXT_LSC[80];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toFackDominic";
			AddQuestRecord("TakeVineToPrisoner", "2");
		break;

		case "SecondLogro":
			dialog.text = DLG_TEXT_LSC[81];
			link.l1 = DLG_TEXT_LSC[82];
			link.l1.go = "SecondLogro_1";
		break;
		case "SecondLogro_1":
			dialog.text = DLG_TEXT_LSC[83];
			link.l1 = DLG_TEXT_LSC[84];
			link.l1.go = "SecondLogro_2";
		break;
		case "SecondLogro_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name == xiDStr("Armo"))
			{
				dialog.text = DLG_TEXT_LSC[85];
				link.l1 = DLG_TEXT_LSC[86];
				link.l1.go = "SecondLogro_3";
				pchar.questTemp.LSC.LegroHelp.Armo = true; //флаг на то, что квест пошел с участием Армо
			}
			else
			{
				dialog.text = DLG_TEXT_LSC[87];
				link.l1 = DLG_TEXT_LSC[88];
				link.l1.go = "LastLegroAdd";
			}
		break;
		case "SecondLogro_3":
			dialog.text = DLG_TEXT_LSC[89];
			link.l1 = DLG_TEXT_LSC[90];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoDominic";
			AddQuestRecord("TakeVineToPrisoner", "4");
		break;

		case "LastLegro":
			dialog.text = DLG_TEXT_LSC[91];
			link.l1 = DLG_TEXT_LSC[92];
			link.l1.go = "LastLegro_1";
		break;
		case "LastLegro_1":
			dialog.text = DLG_TEXT_LSC[93];
			link.l1 = DLG_TEXT_LSC[94];
			link.l1.go = "LastLegro_2";
		break;
		case "LastLegro_2":
			dialog.text = DLG_TEXT_LSC[95];
			link.l1 = DLG_TEXT_LSC[96];
			link.l1.go = "LastLegro_3";
		break;
		case "LastLegro_3":
			dialog.text = DLG_TEXT_LSC[97];
			link.l1 = DLG_TEXT_LSC[98];
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toKeyDominic";
			AddQuestRecord("TakeVineToPrisoner", "6");
		break;

		case "LastLegroAdd":
			dialog.text = DLG_TEXT_LSC[99];
			link.l1 = DLG_TEXT_LSC[100];
			link.l1.go = "LastLegro_3";
		break;
		//если Армо убита, то тюремщик может помочь в наезде на касперов
		case "ArmoIsDead":
			dialog.text = DLG_TEXT_LSC[101];
			link.l1 = DLG_TEXT_LSC[102];
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = DLG_TEXT_LSC[103];
			link.l1 = DLG_TEXT_LSC[104];
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = DLG_TEXT_LSC[105];
			link.l1 = DLG_TEXT_LSC[106];
			link.l1.go = "ArmoIsDead_3";
		break;
		case "ArmoIsDead_3":
			dialog.text = DLG_TEXT_LSC[107];
			link.l1 = DLG_TEXT_LSC[108];
			link.l1.go = "ArmoIsDead_4";
		break;
		case "ArmoIsDead_4":
			dialog.text = DLG_TEXT_LSC[109];
			link.l1 = DLG_TEXT_LSC[110];
			link.l1.go = "ArmoIsDead_5";
		break;
		case "ArmoIsDead_5":
			dialog.text = DLG_TEXT_LSC[111];
			link.l1 = DLG_TEXT_LSC[112];
			link.l1.go = "ArmoIsDead_6";
		break;
		case "ArmoIsDead_6":
			dialog.text = DLG_TEXT_LSC[113];
			link.l1 = DLG_TEXT_LSC[114];
			link.l1.go = "ArmoIsDead_7";
		break;
		case "ArmoIsDead_7":			
			if (npchar.chr_ai.type == LAI_TYPE_SIT)
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);	
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			sld.dialog.currentnode = "AfterFightCasper";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("ISS_MainLine", "70");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "AfterFightCasper":
			dialog.text = DLG_TEXT_LSC[115];
			link.l1 = DLG_TEXT_LSC[116];
			link.l1.go = "AfterFightCasper_1";
		break;
		case "AfterFightCasper_1":
			dialog.text = DLG_TEXT_LSC[117];
			link.l1 = DLG_TEXT_LSC[118];
			link.l1.go = "AfterFightCasper_2";
		break;
		case "AfterFightCasper_2":
			dialog.text = DLG_TEXT_LSC[119];
			link.l1 = DLG_TEXT_LSC[120];
			link.l1.go = "AfterFightCasper_3";
		break;
		case "AfterFightCasper_3":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
