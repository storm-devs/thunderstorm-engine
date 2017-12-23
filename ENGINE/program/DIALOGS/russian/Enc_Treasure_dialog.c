//navy
#include "DIALOGS\russian\Common_Duel.c" 
#include "TEXT\DIALOGS\Enc_Treasure_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	aref   item;
	bool   ok;
	
	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	ProcessDuelDialog(NPChar, link, Diag); //navy

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
            dialog.Text = DLG_TEXT_BASE[0];
			Link.l1 = DLG_TEXT_BASE[1];
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = DLG_TEXT_BASE[2];
			Link.l1 = DLG_TEXT_BASE[3];
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = (GetCharacterItem(Pchar, "map_part1")>0)  && (GetCharacterItem(Pchar, "map_part2")>0);
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = DLG_TEXT_BASE[4];
    			Link.l1 = DLG_TEXT_BASE[5];
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = DLG_TEXT_BASE[6];
    			Link.l1 = DLG_TEXT_BASE[7];
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = DLG_TEXT_BASE[8];
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = DLG_TEXT_BASE[9];
			Link.l1 = DLG_TEXT_BASE[10];
			Link.l1.go = "map_treasure_3";
			Link.l2 = DLG_TEXT_BASE[11];
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = DLG_TEXT_BASE[12]+Pchar.GenQuest.TreasureMoney+DLG_TEXT_BASE[13];
			Link.l1 = DLG_TEXT_BASE[14];
			if (sti(Pchar.Money) >= sti(Pchar.GenQuest.TreasureMoney))
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = DLG_TEXT_BASE[15];
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = DLG_TEXT_BASE[16];
			Link.l1 = DLG_TEXT_BASE[17];
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(Pchar.GenQuest.TreasureMoney));
			GiveItem2Character(pchar, "map_full");
			//Items_FindItem("map_full", &item);
			//FillMapForTreasure(item);
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = DLG_TEXT_BASE[18];
			Link.l1 = DLG_TEXT_BASE[19];
			Link.l1.go = "exit";
			ok = (GetCharacterItem(Pchar, "map_part1")>0)  || (GetCharacterItem(Pchar, "map_part2")>0);
            if (GetCharacterItem(Pchar, "map_full") == 0 && !ok)
            {
    			Link.l2 = DLG_TEXT_BASE[20];
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = DLG_TEXT_BASE[21];
			Link.l1 = DLG_TEXT_BASE[22];
			Link.l1.go = "exit";
			Link.l2 = DLG_TEXT_BASE[23];
//			Link.l2.go = "tavern_keeper";
//			Diag.TempNode = "Temp_treasure";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
