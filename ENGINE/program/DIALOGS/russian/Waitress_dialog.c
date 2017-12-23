#include "TEXT\DIALOGS\Waitress_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = DLG_TEXT_BASE[0];
					link.l1 = DLG_TEXT_BASE[1];
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = DLG_TEXT_BASE[2];
					link.l1 = DLG_TEXT_BASE[3] + pchar.questTemp.different.FackWaitress.Name + DLG_TEXT_BASE[4];
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = DLG_TEXT_BASE[5];
					link.l1 = DLG_TEXT_BASE[6];
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = DLG_TEXT_BASE[7];
					link.l1 = DLG_TEXT_BASE[8];
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[9];
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[10];
					link.l1 = DLG_TEXT_BASE[11];
					link.l1.go = "exit";
				break;

				case 2:
					dialog.text = DLG_TEXT_BASE[12];
					link.l1 = DLG_TEXT_BASE[13];
					link.l1.go = "exit";
					// boal 27.03.2004 -->
					if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && pchar.questTemp.piratesLine != "Soukins_toPuertoPrincipe" && pchar.questTemp.piratesLine != "Soukins_seekRings" && Pchar.questTemp.CapBloodLine != true /*&& npchar.city != "Villemstad"*/)
					{
						link.l2 = DLG_TEXT_BASE[14];
						link.l2.go = "Love_1";
					}
					// boal 27.03.2004 <--
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[15];
					link.l1 = DLG_TEXT_BASE[16];
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[17];
					link.l1 = DLG_TEXT_BASE[18];
					link.l1.go = "exit";
				break;
			}			
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра поп поиску шпиона
			{
				link.l4 = DLG_TEXT_BASE[19];
				if (pchar.GenQuest.SeekSpy.City == "1")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}			
			link.l9 = DLG_TEXT_BASE[20];
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = DLG_TEXT_BASE[21];
			link.l1 = DLG_TEXT_BASE[22];
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = cRand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterReputation(pchar, -1);
		break;
        case "Love_IDN":
			dialog.text = DLG_TEXT_BASE[23];
			link.l1 = DLG_TEXT_BASE[24];
			link.l1.go = "exit";
		break;
        case "Love_IDN_1":
			dialog.text = DLG_TEXT_BASE[25];
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "Love_IDN_2";
		break;
        case "Love_IDN_2":
			dialog.text = DLG_TEXT_BASE[27];
			link.l1 = DLG_TEXT_BASE[28];
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = DLG_TEXT_BASE[29];
			link.l1 = DLG_TEXT_BASE[30];
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = DLG_TEXT_BASE[31];
			link.l1 = DLG_TEXT_BASE[32];
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = DLG_TEXT_BASE[33];
			link.l1 = DLG_TEXT_BASE[34];
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = DLG_TEXT_BASE[35];
			link.l2 = DLG_TEXT_BASE[36];
			link.l2.go = "exit";
		break;
		//==> eddy. квест мэра, вопросы не замечала ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[37], 
				DLG_TEXT_BASE[38], DLG_TEXT_BASE[39], DLG_TEXT_BASE[40], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[41], DLG_TEXT_BASE[42],
                      DLG_TEXT_BASE[43], DLG_TEXT_BASE[44], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_BASE[45], 
				DLG_TEXT_BASE[46], DLG_TEXT_BASE[47], DLG_TEXT_BASE[48], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[49], DLG_TEXT_BASE[50],
                      DLG_TEXT_BASE[51], DLG_TEXT_BASE[52], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
}
 
