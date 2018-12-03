// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "TEXT\DIALOGS\Common_Store.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney;
	int iQuantityGoods;
	int iTradeGoods;
	int iTmp;
	
    bool  ok;

	int iTest;
    iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

    if (!CheckAttribute(npchar, "quest.item_date"))
    {
        npchar.quest.item_date = "";
    }
    if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0], DLG_TEXT_BASE[1], DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4], DLG_TEXT_BASE[5]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[6], DLG_TEXT_BASE[7]), 
					RandPhraseSimple(DLG_TEXT_BASE[8] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[9], DLG_TEXT_BASE[10] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[11]));
				link.l1.go = "fight";
				break;
			}
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase(DLG_TEXT_BASE[12] + TimeGreeting() + ".",
                                    DLG_TEXT_BASE[13],
                                    DLG_TEXT_BASE[14] + GetFullName(pchar) + DLG_TEXT_BASE[15]);
                Link.l1 = DLG_TEXT_BASE[16] + NPChar.name + DLG_TEXT_BASE[17];
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
            }
            dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[18]
							+ LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20],DLG_TEXT_BASE[21])+
							+GetFullName(npchar)+  DLG_TEXT_BASE[22],
			                + LinkRandPhrase(DLG_TEXT_BASE[23], DLG_TEXT_BASE[24], DLG_TEXT_BASE[25])
							+ GetAddress_Form(NPChar)+ DLG_TEXT_BASE[26]  + GetFullName(npchar)+
							+ RandPhraseSimple(DLG_TEXT_BASE[27],DLG_TEXT_BASE[28]));
			link.l1 = DLG_TEXT_BASE[29] +RandPhraseSimple(DLG_TEXT_BASE[30],DLG_TEXT_BASE[31])+ DLG_TEXT_BASE[32]+ GetFullName(pchar)+".";
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[33], DLG_TEXT_BASE[34], DLG_TEXT_BASE[35]), 
					LinkRandPhrase(DLG_TEXT_BASE[36], DLG_TEXT_BASE[37], DLG_TEXT_BASE[38]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[39], DLG_TEXT_BASE[40]), 
					RandPhraseSimple(DLG_TEXT_BASE[41] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[42], DLG_TEXT_BASE[43] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[44]));
				link.l1.go = "fight";
				break;
			}
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     		  LinkRandPhrase(DLG_TEXT_BASE[45], DLG_TEXT_BASE[46], DLG_TEXT_BASE[47])
							+ LinkRandPhrase(DLG_TEXT_BASE[48],DLG_TEXT_BASE[49], DLG_TEXT_BASE[50])+ LinkRandPhrase(DLG_TEXT_BASE[51],DLG_TEXT_BASE[52], DLG_TEXT_BASE[53]) + RandPhraseSimple(DLG_TEXT_BASE[54], DLG_TEXT_BASE[55]),
							  LinkRandPhrase(DLG_TEXT_BASE[56],DLG_TEXT_BASE[57], DLG_TEXT_BASE[58])+ "! "+ LinkRandPhrase(DLG_TEXT_BASE[59] ,DLG_TEXT_BASE[60],DLG_TEXT_BASE[61])
							+ LinkRandPhrase(DLG_TEXT_BASE[62],DLG_TEXT_BASE[63],DLG_TEXT_BASE[64])+DLG_TEXT_BASE[65]);
				link.l1 = pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[66],DLG_TEXT_BASE[67],DLG_TEXT_BASE[68])+ DLG_TEXT_BASE[69]
											  + LinkRandPhrase(DLG_TEXT_BASE[70], DLG_TEXT_BASE[71],DLG_TEXT_BASE[72])+ LinkRandPhrase(DLG_TEXT_BASE[73], DLG_TEXT_BASE[74], DLG_TEXT_BASE[75]),
							                    LinkRandPhrase(DLG_TEXT_BASE[76], DLG_TEXT_BASE[77], DLG_TEXT_BASE[78])+LinkRandPhrase(DLG_TEXT_BASE[79], DLG_TEXT_BASE[80], DLG_TEXT_BASE[81])
											  + LinkRandPhrase(DLG_TEXT_BASE[82],DLG_TEXT_BASE[83],DLG_TEXT_BASE[84]));
				link.l1.go = "fight";
				break;
			}*/
   			// проверка награды
			/*if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 40)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     LinkRandPhrase(DLG_TEXT_BASE[85], DLG_TEXT_BASE[86], DLG_TEXT_BASE[87])+GetFullName(pchar)+ DLG_TEXT_BASE[88]
							+ LinkRandPhrase(DLG_TEXT_BASE[89],DLG_TEXT_BASE[90], DLG_TEXT_BASE[91]) +LinkRandPhrase(DLG_TEXT_BASE[92],DLG_TEXT_BASE[93], DLG_TEXT_BASE[94]) + RandPhraseSimple(DLG_TEXT_BASE[95], DLG_TEXT_BASE[96]),
							  LinkRandPhrase(DLG_TEXT_BASE[97],DLG_TEXT_BASE[98], DLG_TEXT_BASE[99])+ DLG_TEXT_BASE[100]+GetFullName(pchar)+ LinkRandPhrase(DLG_TEXT_BASE[101] ,DLG_TEXT_BASE[102],DLG_TEXT_BASE[103])
							+ LinkRandPhrase(DLG_TEXT_BASE[104],DLG_TEXT_BASE[105],DLG_TEXT_BASE[106])+DLG_TEXT_BASE[107]);
				link.l1 =      pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[108],DLG_TEXT_BASE[109],DLG_TEXT_BASE[110])+ DLG_TEXT_BASE[111]
											  + LinkRandPhrase(DLG_TEXT_BASE[112], DLG_TEXT_BASE[113],DLG_TEXT_BASE[114]),
							                    LinkRandPhrase(DLG_TEXT_BASE[115], DLG_TEXT_BASE[116], DLG_TEXT_BASE[117])
											  + LinkRandPhrase(DLG_TEXT_BASE[118],DLG_TEXT_BASE[119],DLG_TEXT_BASE[120]));
				link.l1.go = "fight";
				break;
			}    */
			dialog.text = NPCharRepPhrase(npchar,
			                 pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[121], DLG_TEXT_BASE[122], DLG_TEXT_BASE[123]) +GetFullName(pchar)+"! "
							                 + LinkRandPhrase(DLG_TEXT_BASE[124],DLG_TEXT_BASE[125], DLG_TEXT_BASE[126])
											  + RandPhraseSimple(DLG_TEXT_BASE[127], DLG_TEXT_BASE[128]),
							                LinkRandPhrase(DLG_TEXT_BASE[129], DLG_TEXT_BASE[130], DLG_TEXT_BASE[131]) + DLG_TEXT_BASE[132]
											+ RandPhraseSimple(DLG_TEXT_BASE[133],DLG_TEXT_BASE[134])+DLG_TEXT_BASE[135]+ RandPhraseSimple(DLG_TEXT_BASE[136],DLG_TEXT_BASE[137])
											+ LinkRandPhrase(DLG_TEXT_BASE[138],DLG_TEXT_BASE[139], DLG_TEXT_BASE[140])+RandPhraseSimple(DLG_TEXT_BASE[141], DLG_TEXT_BASE[142])),
							 pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[143],DLG_TEXT_BASE[144],DLG_TEXT_BASE[145]) + GetFullName(pchar)
							 				+ LinkRandPhrase(DLG_TEXT_BASE[146],DLG_TEXT_BASE[147],DLG_TEXT_BASE[148])
											 +LinkRandPhrase(DLG_TEXT_BASE[149],DLG_TEXT_BASE[150], DLG_TEXT_BASE[151]),
							                DLG_TEXT_BASE[152] +GetFullName(pchar)+ LinkRandPhrase(DLG_TEXT_BASE[153],
											DLG_TEXT_BASE[154],DLG_TEXT_BASE[155]) +DLG_TEXT_BASE[156]));

			link.l1 = NPCharRepPhrase(npchar,
			            pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[157], DLG_TEXT_BASE[158],DLG_TEXT_BASE[159])
									  +LinkRandPhrase(DLG_TEXT_BASE[160],DLG_TEXT_BASE[161],DLG_TEXT_BASE[162]) +DLG_TEXT_BASE[163]
									  +LinkRandPhrase(DLG_TEXT_BASE[164],DLG_TEXT_BASE[165], DLG_TEXT_BASE[166]),
						               LinkRandPhrase(DLG_TEXT_BASE[167],DLG_TEXT_BASE[168],DLG_TEXT_BASE[169]) + GetAddress_FormToNPC(NPChar)+" " +GetFullName(Npchar)
									   +RandPhraseSimple(DLG_TEXT_BASE[170],DLG_TEXT_BASE[171])
									   +LinkRandPhrase(DLG_TEXT_BASE[172], DLG_TEXT_BASE[173], DLG_TEXT_BASE[174])+ "."),
						pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[175],DLG_TEXT_BASE[176]) +GetFullName(Npchar)+ "! "
						              +LinkRandPhrase(DLG_TEXT_BASE[177], DLG_TEXT_BASE[178],DLG_TEXT_BASE[179])
						              +RandPhraseSimple(DLG_TEXT_BASE[180],DLG_TEXT_BASE[181]),
						               DLG_TEXT_BASE[182] + GetAddress_FormToNPC(NPChar)+ DLG_TEXT_BASE[183] + LinkRandPhrase(DLG_TEXT_BASE[184],
									    DLG_TEXT_BASE[185], DLG_TEXT_BASE[186])));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[187],DLG_TEXT_BASE[188]) +LinkRandPhrase(DLG_TEXT_BASE[189],
													                                 DLG_TEXT_BASE[190], DLG_TEXT_BASE[191]),
            														LinkRandPhrase(DLG_TEXT_BASE[192], DLG_TEXT_BASE[193],DLG_TEXT_BASE[194])+RandPhraseSimple(DLG_TEXT_BASE[195],DLG_TEXT_BASE[196])
																	+LinkRandPhrase(DLG_TEXT_BASE[197],DLG_TEXT_BASE[198],DLG_TEXT_BASE[199])
																	+RandPhraseSimple(DLG_TEXT_BASE[200],DLG_TEXT_BASE[201])+DLG_TEXT_BASE[202]),
													 pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[203],
													                                 DLG_TEXT_BASE[204]),
                 												DLG_TEXT_BASE[205] +LinkRandPhrase(DLG_TEXT_BASE[206] + NationNameGenitive(sti(NPChar.nation)),DLG_TEXT_BASE[207], DLG_TEXT_BASE[208])
																	+RandPhraseSimple(DLG_TEXT_BASE[209],DLG_TEXT_BASE[210])
																	+RandPhraseSimple(DLG_TEXT_BASE[211],DLG_TEXT_BASE[212]) +DLG_TEXT_BASE[213])),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase(DLG_TEXT_BASE[214],
													                DLG_TEXT_BASE[215] +RandPhraseSimple(DLG_TEXT_BASE[216], DLG_TEXT_BASE[217]
																	+RandPhraseSimple(DLG_TEXT_BASE[218], DLG_TEXT_BASE[219]))),
													 pcharrepphrase(DLG_TEXT_BASE[220],
													                DLG_TEXT_BASE[221] + GetFullName(pchar)+DLG_TEXT_BASE[222])),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple(DLG_TEXT_BASE[223] ,
													   RandPhraseSimple(DLG_TEXT_BASE[224],DLG_TEXT_BASE[225]) +DLG_TEXT_BASE[226])
													   +RandPhraseSimple(DLG_TEXT_BASE[227], DLG_TEXT_BASE[228]),
													 pcharrepphrase(DLG_TEXT_BASE[229] + GetFullName(pchar)+DLG_TEXT_BASE[230],
													                DLG_TEXT_BASE[231] + GetFullName(pchar)+DLG_TEXT_BASE[232])),
												  NPCharRepPhrase(npchar,
												     DLG_TEXT_BASE[233]
													 +LinkRandPhrase(DLG_TEXT_BASE[234],DLG_TEXT_BASE[235],
													 pcharrepphrase(DLG_TEXT_BASE[236],DLG_TEXT_BASE[237])),
													 pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[238],DLG_TEXT_BASE[239])+RandPhraseSimple(DLG_TEXT_BASE[240],DLG_TEXT_BASE[241])
													 +RandPhraseSimple(DLG_TEXT_BASE[242],DLG_TEXT_BASE[243]),
													 DLG_TEXT_BASE[244] + GetFullName(pchar)+DLG_TEXT_BASE[245]
													 +RandPhraseSimple(DLG_TEXT_BASE[246], DLG_TEXT_BASE[247]))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[248],
													               DLG_TEXT_BASE[249]),
													pcharrepphrase(DLG_TEXT_BASE[250] +GetFullName(npchar)+DLG_TEXT_BASE[251],
													               DLG_TEXT_BASE[252] +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[253],
													               DLG_TEXT_BASE[254]),
												    pcharrepphrase(DLG_TEXT_BASE[255],
													               DLG_TEXT_BASE[256] +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[257],
													               DLG_TEXT_BASE[258] +GetFullName(npchar)+ DLG_TEXT_BASE[259]),
												    pcharrepphrase(DLG_TEXT_BASE[260],
													               DLG_TEXT_BASE[261])),
											  DLG_TEXT_BASE[262],
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[263],
													               DLG_TEXT_BASE[264]),
													pcharrepphrase(DLG_TEXT_BASE[265],
													               DLG_TEXT_BASE[266]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[267],
													               DLG_TEXT_BASE[268]),
													pcharrepphrase(DLG_TEXT_BASE[269],
													               DLG_TEXT_BASE[270] +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ DLG_TEXT_BASE[271])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[272],
													               DLG_TEXT_BASE[273]),
													pcharrepphrase(DLG_TEXT_BASE[274],
													               DLG_TEXT_BASE[275] + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ DLG_TEXT_BASE[276])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[277],
													               DLG_TEXT_BASE[278]),
													pcharrepphrase(DLG_TEXT_BASE[279],
													               DLG_TEXT_BASE[280])),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[281],
													               DLG_TEXT_BASE[282]),
													pcharrepphrase(DLG_TEXT_BASE[283],
													               DLG_TEXT_BASE[284])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[285],
													               DLG_TEXT_BASE[286]),
												    pcharrepphrase(DLG_TEXT_BASE[287],
													               DLG_TEXT_BASE[288])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[289],
													               DLG_TEXT_BASE[290]),
													pcharrepphrase(DLG_TEXT_BASE[291],
													               DLG_TEXT_BASE[292])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[293],
													               DLG_TEXT_BASE[294]),
													pcharrepphrase(DLG_TEXT_BASE[295],
													               DLG_TEXT_BASE[296])),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			//--> eddy. Аскольд, базар с рендомным торговцем
			if (pchar.questTemp.Ascold == "Seek_powder" && pchar.questTemp.Ascold.TraderId == npchar.id && !CheckAttribute(Pchar, "RomanticQuest.TalkInShop")) 
			{
				link.l3.go = "AscoldTrader";
			}
			if (pchar.questTemp.Ascold == "PowderWasSeek" && pchar.questTemp.Ascold.TraderId == npchar.id) 
			{
				link.l3.go = "AscoldTrader_WasSeek";
			}
			//<-- eddy. Аскольд, базар с рендомным торговцем
			link.l4 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase(DLG_TEXT_BASE[297],
													               DLG_TEXT_BASE[298]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase(DLG_TEXT_BASE[299],
													               DLG_TEXT_BASE[300]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+DLG_TEXT_BASE[301])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[302],
													               DLG_TEXT_BASE[303]),
													pcharrepphrase(DLG_TEXT_BASE[304],
													               DLG_TEXT_BASE[305])),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[306],
													               DLG_TEXT_BASE[307]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase(DLG_TEXT_BASE[308],
													               DLG_TEXT_BASE[309]+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase(DLG_TEXT_BASE[310] +GetFullName(pchar)+ DLG_TEXT_BASE[311],
													               DLG_TEXT_BASE[312]),
													pcharrepphrase(DLG_TEXT_BASE[313],
													               DLG_TEXT_BASE[314] + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l4.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = DLG_TEXT_BASE[315];
				link.l1 = DLG_TEXT_BASE[316];
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple(DLG_TEXT_BASE[317], DLG_TEXT_BASE[318]);
			link.l1 = pcharrepphrase(LinkRandPhrase(DLG_TEXT_BASE[319],
			                         DLG_TEXT_BASE[320],
									 DLG_TEXT_BASE[321]),
									 LinkRandPhrase(DLG_TEXT_BASE[322],
			                         DLG_TEXT_BASE[323],
									 DLG_TEXT_BASE[324]));
			link.l1.go = "trade_1";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[325],
			                         DLG_TEXT_BASE[326],
									 DLG_TEXT_BASE[327]);
			link.l2.go = "items";
			link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[328],
			                                          DLG_TEXT_BASE[329]),
									 RandPhraseSimple(DLG_TEXT_BASE[330],
									                  DLG_TEXT_BASE[331]));
			link.l3.go = "exit";
		break;

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase(DLG_TEXT_BASE[332],
				                                                     DLG_TEXT_BASE[333]),
													  pcharrepphrase(DLG_TEXT_BASE[334] +GetFullName(pchar)+ DLG_TEXT_BASE[335],
													                 DLG_TEXT_BASE[336]));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[337],
				                                                 DLG_TEXT_BASE[338] +GetFullName(npchar)+ DLG_TEXT_BASE[339]),
												  pcharrepphrase(DLG_TEXT_BASE[340],
												                 DLG_TEXT_BASE[341]));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "business":
			iTest = 0;
    		//квест Синей Птицы, начальный диалог
			if (pchar.questTemp.BlueBird == "begin" && sti(npchar.nation) == GetBaseHeroNation() && sti(npchar.nation) != PIRATE && npchar.city != "Panama")
			{
				dialog.text = RandPhraseSimple(DLG_TEXT_BASE[342], DLG_TEXT_BASE[343]);
				link.l1 = DLG_TEXT_BASE[344]; 
				link.l1.go = "RBlueBird";
				break;
			}			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = DLG_TEXT_BASE[345] + GetFullName(&Characters[iTmp]) + DLG_TEXT_BASE[346];
				link.l1 = DLG_TEXT_BASE[347];
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,DLG_TEXT_BASE[348],DLG_TEXT_BASE[349]);
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			/*if (CheckAttribute(pchar, "CargoQuest.iQuantityGoods"))
    			{
    				int iQuantityShipGoods = pchar.CargoQuest.iQuantityGoods;
    				int iQuestTradeGoods = pchar.CargoQuest.iTradeGoods;
    			}  */
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )//&&  GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
    				{
    					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[350], DLG_TEXT_BASE[351]);
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = DLG_TEXT_BASE[352];
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple(DLG_TEXT_BASE[353],
								                           DLG_TEXT_BASE[354]);
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = DLG_TEXT_BASE[355] +GetAddress_FormToNPC(NPChar)+ DLG_TEXT_BASE[356];
    				link.l1.go = "generate_quest";
    			}
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[357],
	                                                          DLG_TEXT_BASE[358]),
	                                        RandPhraseSimple(DLG_TEXT_BASE[359],
	                                                         DLG_TEXT_BASE[360]));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple(DLG_TEXT_BASE[361] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[362]);
					link.l4.go = "IntelligenceForAll";
				}	
				// ----------------- квест получения Синей Птицы, сдаем квест -----------------
				if (pchar.questTemp.BlueBird == "weWon" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = DLG_TEXT_BASE[363];
					link.l1.go = "RBlueBirdWon";
				}
				if (pchar.questTemp.BlueBird == "DieHard" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = DLG_TEXT_BASE[364];
					link.l1.go = "RBlueBirdDieHard";
				}
				if (pchar.questTemp.BlueBird == "returnMoney" && pchar.questTemp.BlueBird.traiderId == npchar.id && sti(pchar.questTemp.BlueBird.count) > 0)
				{
					if (sti(pchar.questTemp.BlueBird.count) < 5)
					{
						link.l1 = DLG_TEXT_BASE[365];
						link.l1.go = "RBlueBird_retMoney_1";
					}
					else
					{
						link.l1 = DLG_TEXT_BASE[366];
						link.l1.go = "RBlueBird_retMoney_3";
					}
				}
				// ----------------- квест получения Синей Птицы, продолжение -----------------
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[367],
                                                          DLG_TEXT_BASE[368]),
                                        RandPhraseSimple(DLG_TEXT_BASE[369],
                                                         DLG_TEXT_BASE[370]));,

    		    link.l6.go = "rumours_trader";
				// <-- homo
				link.l99 = DLG_TEXT_BASE[371];
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+DLG_TEXT_BASE[372], DLG_TEXT_BASE[373] +GetFullName(npchar)+ DLG_TEXT_BASE[374]), pcharrepphrase(DLG_TEXT_BASE[375], DLG_TEXT_BASE[376]));
                link.l1.go = "exit";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple(DLG_TEXT_BASE[377],
	                                                          DLG_TEXT_BASE[378]),
	                                        RandPhraseSimple(DLG_TEXT_BASE[379],
	                                                         DLG_TEXT_BASE[380]));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple(DLG_TEXT_BASE[381] + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + DLG_TEXT_BASE[382]);
					link.l7.go = "IntelligenceForAll";
				}	
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = DLG_TEXT_BASE[383] + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = DLG_TEXT_BASE[384];
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + DLG_TEXT_BASE[385] + GetFullName(pchar)+ DLG_TEXT_BASE[386] +
                                      RandPhraseSimple(DLG_TEXT_BASE[387],DLG_TEXT_BASE[388]) + DLG_TEXT_BASE[389];
						link.l1 = RandPhraseSimple(DLG_TEXT_BASE[390],
						                           RandSwear()+ DLG_TEXT_BASE[391]+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[392]+GetAddress_Form(NPChar)+DLG_TEXT_BASE[393],DLG_TEXT_BASE[394]);
						link.l1 = DLG_TEXT_BASE[395];
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
    						iTradeGoods = rand(GOOD_BRICK); //Рабы и золото не даем, бомбы и еду - да!!
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[396],DLG_TEXT_BASE[397]+GetFullName(pchar)+DLG_TEXT_BASE[398]);
    							link.l1 = NPCharRepPhrase(npchar, DLG_TEXT_BASE[399],DLG_TEXT_BASE[400]);
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = DLG_TEXT_BASE[456] + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text =  DLG_TEXT_BASE[401] +
                                               GetGoodsNameAlt(iTradeGoods)+ DLG_TEXT_BASE[402] + FindRussianQtyString(iQuantityGoods) + DLG_TEXT_BASE[403] +
                                           sNation + sTemp + DLG_TEXT_BASE[457] +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           DLG_TEXT_BASE[404] +
                                           FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[405];
    							link.l1 = DLG_TEXT_BASE[406];
    							link.l1.go = "exit_trade";
    							link.l2  = DLG_TEXT_BASE[407];
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = DLG_TEXT_BASE[408]+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + DLG_TEXT_BASE[409];
    						link.l1 = DLG_TEXT_BASE[410];
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, DLG_TEXT_BASE[411],DLG_TEXT_BASE[412]);
				link.l1 = NPCharRepPhrase(npchar, DLG_TEXT_BASE[413], DLG_TEXT_BASE[414]);
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + DLG_TEXT_BASE[415];
				link.l1 = DLG_TEXT_BASE[416];
				link.l1.go = "generate_quest_failed";
				link.l9 = DLG_TEXT_BASE[417];
				link.l9.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = DLG_TEXT_BASE[418] +
                GetGoodsNameAlt(iTradeGoods) + DLG_TEXT_BASE[419] + FindRussianQtyString(iQuantityGoods) + DLG_TEXT_BASE[420] +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = DLG_TEXT_BASE[421];
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + DLG_TEXT_BASE[422]+GetAddress_Form(NPChar)+
                              DLG_TEXT_BASE[423] + RandPhraseSimple(DLG_TEXT_BASE[424],DLG_TEXT_BASE[425])+
                              DLG_TEXT_BASE[426];
				link.l1 = RandSwear() + RandPhraseSimple(DLG_TEXT_BASE[427],
                                                         DLG_TEXT_BASE[428]);
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = DLG_TEXT_BASE[429]
                              + FindRussianQtyString(iTmp) + DLG_TEXT_BASE[430];
				link.l9 = RandPhraseSimple(DLG_TEXT_BASE[431],
                                           RandSwear() +DLG_TEXT_BASE[432]);
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[433]+GetFullName(pchar)+".";
				link.l1 = DLG_TEXT_BASE[434];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = DLG_TEXT_BASE[435] + FindRussianMoneyString(iMoney) + DLG_TEXT_BASE[436];
			link.l1 = DLG_TEXT_BASE[437];
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = DLG_TEXT_BASE[438];
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = DLG_TEXT_BASE[439];
			link.l1 = DLG_TEXT_BASE[440];
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = DLG_TEXT_BASE[441] +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ DLG_TEXT_BASE[458] + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = DLG_TEXT_BASE[442];
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +DLG_TEXT_BASE[443];
			link.l1 = DLG_TEXT_BASE[444];
			link.l1.go = "exit";
			link.l2 = DLG_TEXT_BASE[445];
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = DLG_TEXT_BASE[446]
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + DLG_TEXT_BASE[447];
				link.l9 = RandPhraseSimple(DLG_TEXT_BASE[448],
                                           RandSwear() +DLG_TEXT_BASE[449]);
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = DLG_TEXT_BASE[450];
    			link.l1 = DLG_TEXT_BASE[451];
    			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		case "no_quests":
			dialog.text = DLG_TEXT_BASE[452];
			link.l1 = DLG_TEXT_BASE[453];
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			if (pchar.questTemp.Ascold == "canTakeQuest" && pchar.questTemp.Ascold.TraderId == npchar.id)//eddy. Аскольд, начало
			{
				dialog.Text = DLG_TEXT_BASE[454];
				Link.l1 = DLG_TEXT_BASE[455];
				Link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp.Ascold");
				pchar.questTemp.Ascold = "Seek_powder";
				AddQuestRecord("Ascold", "1");
				AddQuestUserData("Ascold", "sName", GetFullName(npchar));
				AddQuestUserData("Ascold", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
			}
			else
			{
				Nextdiag.CurrentNode = Nextdiag.TempNode;
				DialogExit();
			}
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
