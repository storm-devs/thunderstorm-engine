#include "TEXT\DIALOGS\Store\PortPax_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Azzy.GiveRum"))
            {
        		Link.l1 = DLG_TEXT_STR[9];
        	    Link.l1.go = "Step_Az6";
                if (pchar.questTemp.Azzy.GiveRum == "OK")
                {
            		Link.l1 = DLG_TEXT_STR[10];
            	    Link.l1.go = "Step_Az8";
                }
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
    			Link.l2 = DLG_TEXT_STR[11];
    			Link.l2.go = "Step_Az10";
            }
		break;
		//============================== Êâåñò Àççè ===============================
 		case "Step_Az6":
        	dialog.text = DLG_TEXT_STR[12];
    		link.l1 = DLG_TEXT_STR[13];
    		link.l1.go = "Step_Az7";
		break;

 		case "Step_Az7":
        	dialog.text = DLG_TEXT_STR[14];
    		link.l1 = DLG_TEXT_STR[15];
    		link.l1.go = "Step_Az8";
    		pchar.questTemp.Azzy.GiveRum = "OK";
		break;

 		case "Step_Az8":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[16],
                       DLG_TEXT_STR[17],
                       DLG_TEXT_STR[18],
                       DLG_TEXT_STR[19], "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[20], DLG_TEXT_STR[21], DLG_TEXT_STR[22], DLG_TEXT_STR[23], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az9", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az9":
        	dialog.text = DLG_TEXT_STR[24];
    		link.l1 = DLG_TEXT_STR[25];
    		link.l1.go = "exit";
            AddCharacterGoods(Pchar, GOOD_RUM, 300);
		break;

 		case "Step_Az10":
        	dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[26],
                                    DLG_TEXT_STR[27],
                                    DLG_TEXT_STR[28],
                                    DLG_TEXT_STR[29], "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[30], DLG_TEXT_STR[31], DLG_TEXT_STR[32], DLG_TEXT_STR[33], npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az11", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az11":
        	dialog.text = DLG_TEXT_STR[34];
    		link.l1 = DLG_TEXT_STR[35];
    		link.l1.go = "Step_Az12";
		break;

 		case "Step_Az12":
        	dialog.text = DLG_TEXT_STR[36]+
                          DLG_TEXT_STR[37]+
                          DLG_TEXT_STR[38];
    		link.l1 = DLG_TEXT_STR[39];
    		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

