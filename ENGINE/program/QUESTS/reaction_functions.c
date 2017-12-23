#include "TEXT\Quests\reaction_functions.h"

ref		sld, rCharacter;
int     iTemp, i; // нужно для вычислений любых целых (нации)
float   locx, locy, locz;
string  sTemp; // любые строки для вычислений
bool    bOk;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==> грабители
void Birglars_fight(string qName)
{
	if (GetCharacterIndex("Berglar" + pchar.quest.(qName).city) != -1)
	{
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);		
		sTemp = "berglar" + pchar.quest.(qName).city;
		pchar.questTemp.tugs.(sTemp) = "over";
		sld = characterFromId("Berglar" + pchar.quest.(qName).city);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	}
}
//освободить флаг на дачу миниквестов
void SmallQuests_free(string qName)
{
	pchar.questTemp.different = "free";
}
//вернуть тип губернаторов обратно в sit после боевки
void MayorSitBack(string qName) 
{
	iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId)
	if (iTemp > 0)
	{
		sld = &characters[iTemp];
		sld.location = Pchar.quest.MayorSitBack.locationName;
		sld.location.group = "sit";
		sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
		LAi_SetHuberTypeNoGroup(sld);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	}
}

void Ascold_fightInsideTemple(string qName)
{
	if (MOD_SKILL_ENEMY_RATE > 5) chrDisableReloadToLocation = true;
	characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Ascold_KilledTemple";
	AddQuestRecord("Ascold", "11");
    //--------------------------- испанцы ------------------------------
	LAi_group_Delete("EnemyFight");
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
 	sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_off", "SpaOfficer3", "man", "man", Rank, SPAIN, -1, true));
    FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);	
	LAi_SetActorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto9");
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==12) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol3", 50);
		DeleteAttribute(sld, "SuperShooter");
		sld.BreakTmplAndFightGroup = true;
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
    }
    for (i=10; i<=13; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	DoQuestFunctionDelay("Ascold_actorSetWarrior", 3.5);
}

void Ascold_actorSetWarrior(string qName)
{
	iTemp = GetCharacterIndex("SpaEnemy_off");
	if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	for (i=1; i<=8; i++)
    {
		iTemp = GetCharacterIndex("SpaEnemy_"+i);	
		if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	}
}

void Ascold_LeifIsDead(string qName)
{
	LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", false);
}

 void Ascold_OpenTheGrave(string qName)
{
	DoReloadCharacterToLocation("Guadeloupe_Cave", "reload", "reload5");
}

void DelivLettTortuga_Digress(string qName)
{
	LAi_ActorAnimation(characterFromId("AntonioDeBarras"), "attack_fast_1", "DelivLettTortuga_2KickPhar", 0.8);
}

void SeekIsabella_exitTown(string qName)
{
    DeleteAttribute(&locations[FindLocation("Beliz_ExitTown")], "DisableEncounters"); //энкаутеры вернем
	DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
}

void Fr2Letter_shore22(string qName)
{
	if (characters[GetCharacterIndex("Bandit_1")].location == "Shore22")
	{
		for (i=1; i<=2; i++)
		{
			sld = characterFromId("Bandit_"+i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		}
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
	}
}

void Isabella_widding(string qName)
{
	pchar.quest.Romantic_Widding_Cancel.over = "yes"; //убираем таймер на вовремя не явлился
	pchar.RomanticQuest = "Widding";
	sld = characterFromID("Isabella");
	LAi_SetActorType(pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);	
}

void FrLine_HoverGoOnPrison()
{	
	pchar.questTemp.jailCanMove = true; //даем возможность выйти из тюрьмы
	LAi_SetPlayerType(pchar);
	pchar.questTemp.State = "Fr2Letter_SeekProblems";	
	AddQuestRecord("Fra_Line_2_DelivLetter", "3");
	RestoreTempRemoveParam(pchar, "items");
	pchar.money = pchar.questTemp.money;
	DeleteAttribute(pchar, "questTemp.money");
	//==> странных типов помещаем в таверну
    LAi_group_Delete("PeaceGroup");
	for (i=1; i<=2; i++)
    {
		sTemp = "sit6";
		if (i==2) sTemp = "sit7";
		sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 20, FRANCE, 5, true));
		FantomMakeCoolFighter(sld, 20, 70, 40, BLADE_NORMAL, "pistol3", 70);
		sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
		LAi_SetSitType(sld);
		LAi_group_MoveCharacter(sld, "PeaceGroup");
		LAi_SetCheckMinHP(sld, sti(sld.chr_ai.hp)-1, false, "Fr2Letter_FightAfterShot");
		ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "sit", sTemp);
	}
	sld = characterFromID("GoverFantom");
	LAi_SetActorType(sld);
    LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 2.0);
	DoQuestFunctionDelay("FrLine_HoverGoOnPrison_2", 2.5);
}

void FrLine_HoverGoOnPrison_2(string qName)
{
	DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto12");
}

void HL5_portManGiveFleuts()
{
    pchar.questTemp.State = "ThreeFleutes_toLaVega";
    for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("Captain_"+i, "trader_"+(rand(15)+1), "man", "man", 15, HOLLAND, -1, true));
        FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
        FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
        sld.Ship.Cargo.Goods.Balls = 18;
        sld.Ship.Cargo.Goods.Grapes = 18;
        sld.Ship.Cargo.Goods.Knippels = 18;
        sld.Ship.Cargo.Goods.Bombs = 18;
        sld.Ship.Cargo.Goods.Weapon = 0;
        sld.Ship.Cargo.Goods.Powder = 50;
		sld.CompanionEnemyEnable = false; 
		sld.Abordage.Enable = false; // НЕЛЬЗЯ!
		SetShipRemovable(sld, false);
		AddCharacterGoods(sld, GOOD_CLOTHES, 5000);
        AddCharacterGoods(sld, GOOD_FRUITS, 200);
        AddCharacterGoods(sld, GOOD_RUM, 900);
        SetCompanionIndex(pchar, -1, sti(sld.index));
        pchar.GenQuest.StoreGoods.StoreIdx = LaVega_STORE;
        pchar.GenQuest.StoreGoods.HL5_ThreeFleutes = true;
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1 = "location";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1.location = "LaVega_town";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition = "ThreeFleutes_TalkIntoLaVega";
    }
}

void SeekShip_Stay(string qName)
{
	sld = &characters[sti(pchar.quest.(qName).Idx)];
	LAi_SetStayType(sld);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  шебека Синяя Птица   начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BlueBird_inCavern(string qName)
{
	pchar.questTemp.BlueBird = "seenCarriers";
	DoQuestCheckDelay("TalkSelf_Quest", 0.2); //диалог сам-на-сам
}

void BlueBird_endCaveDialog()
{
	LAi_SetActorType(pchar);
	LAi_ActorTurnByLocator(pchar, "goto", "goto1");
	string sQuest = "";
	string CarrierName[10];
	CarrierName[0] = "GenresBag1";
	CarrierName[1] = "GenresBag2";
	CarrierName[2] = "GenresBarrel1";
	CarrierName[3] = "GenresBarrel2";
	CarrierName[4] = "GenresBarrelTop1";
	CarrierName[5] = "GenresBarrelTop2";
	CarrierName[6] = "GenresBottle1";
	CarrierName[7] = "GenresBottle2";
	CarrierName[8] = "GenresChest1";
	CarrierName[9] = "GenresChest2";
	for (i=0; i<10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Carrier_" + i, CarrierName[i], "man", "genres", 35, PIRATE, 0, true));
		sld.gotoGroup = "reload";
		sld.gotoLocator = "reload1_back";
		LAi_SetCarrierType(sld);
		ChangeCharacterAddressGroup(sld, "Bermudes_Cavern", "reload", "reload2");
	}
	DoQuestFunctionDelay("BlueBird_endCaveScript", 33.0);
}

void BlueBird_endCaveScript(string qName)
{
	LAi_LocationDisableMonstersGen("Bermudes_Cavern", false); //монстров генерить
	LAi_LocationDisableOfficersGen("Bermudes_Cavern", false); //офицеров пускать
	for (i=0; i<10; i++)
	{
		sld = characterFromId("Carrier_" + i);
		ChangeCharacterAddress(sld, "none", "");
	}
	AddQuestRecord("Xebeca_BlueBird", "6");
	LAi_SetPlayerType(pchar);
	pchar.questTemp.BlueBird = "toSeaBattle";
	pchar.quest.BlueBird_seaBattle.win_condition.l1 = "location";
	pchar.quest.BlueBird_seaBattle.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_seaBattle.function = "BlueBird_seaBattle";	
}

void BlueBird_seaBattle(string qName)
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	sld = GetCharacter(NPC_GenerateCharacter("BlueBirdCapitain", "", "man", "man", 20, PIRATE, 30, true));							
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "BlueBirdCapitain";
	sld.greeting = "CapSinkShip";
	FantomMakeCoolFighter(sld, 20, 80, 70, "blade32", "pistol3", 20);
	FantomMakeCoolSailor(sld, SHIP_XebekVML, REACT_FUNCT[0], CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");

	Group_AddCharacter("BlueBird_Group", "BlueBirdCapitain");			
	Group_SetType("BlueBird_Group", "pirate");
	Group_SetGroupCommander("BlueBird_Group", "BlueBirdCapitain");
	sTemp = "quest_ship_10";
	if (pchar.location.from_sea == "Shore_ship1") sTemp = "quest_ship_8";
	Group_SetAddress("BlueBird_Group", "Bermudes", "quest_ships", sTemp);
	Group_SetTaskAttack("BlueBird_Group", PLAYER_GROUP);

	pchar.quest.BlueBird_over.win_condition.l1 = "NPC_Death";
	pchar.quest.BlueBird_over.win_condition.l1.character = "BlueBirdCapitain";
	pchar.quest.BlueBird_over.function = "BlueBird_over";

	pchar.quest.BlueBird_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.BlueBird_DieHard1.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_DieHard1.function = "BlueBird_DieHard";
	Pchar.quest.BlueBird_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.BlueBird_DieHard2.function = "BlueBird_DieHard";
}

void BlueBird_over(string qName)
{
	pchar.quest.BlueBird_DieHard1.over = "yes";
	pchar.quest.BlueBird_DieHard2.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "7");
	pchar.questTemp.BlueBird = "weWon";
}

void BlueBird_DieHard(string qName)
{
	sld = characterFromId("BlueBirdCapitain");
	sld.lifeDay = 0;
	group_DeleteGroup("BlueBird_Group");
	pchar.quest.BlueBird_over.over = "yes";
	pchar.quest.BlueBird_DieHard1.over = "yes";
	pchar.quest.BlueBird_DieHard2.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "8");
	pchar.questTemp.BlueBird = "DieHard";
}

//возмездие торгашам. нападение на личный флейт торговца
void BlueBird_loginFleut(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.BlueBird") < 10) 
	{
		LAi_group_Delete("EnemyFight");
		group_DeleteGroup("BlueBird_Group");
		sld = GetCharacter(NPC_GenerateCharacter("BlueBirdTrader", "", "man", "man", 20, sti(pchar.questTemp.BlueBird.nation), 30, true));							
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "BlueBirdTrader";
		sld.greeting = "CapSinkShip";		
		SetCaptanModelByEncType(sld, "trade");
		FantomMakeCoolSailor(sld, SHIP_FLEUT, pchar.questTemp.BlueBird.Ship.Name, CANNON_TYPE_CULVERINE_LBS24, 70, 70, 70);
		sld.Ship.Mode = "trade"; //торговец
		sld.DontRansackCaptain = true;
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("BlueBird_Group", "BlueBirdTrader");			
		Group_SetGroupCommander("BlueBird_Group", "BlueBirdTrader");
		Group_SetAddress("BlueBird_Group", pchar.questTemp.BlueBird.Island, "quest_ships", "quest_ship_"+(rand(5)+1));
		Group_SetTaskRunaway("BlueBird_Group", PLAYER_GROUP);
		pchar.questTemp.BlueBird = "attackFleut"; //флаг квеста
		//прерывания на уход из локации
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1.location_type = "town";
		pchar.Quest.BlueBirdFleut_over1.function = "BlueBirdFleut_over";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1.location_type = "seashore";
		pchar.Quest.BlueBirdFleut_over2.function = "BlueBirdFleut_over";
		Pchar.quest.BlueBirdFleut_over3.win_condition.l1 = "MapEnter";
		pchar.Quest.BlueBirdFleut_over3.function = "BlueBirdFleut_over";
		//прерывание на абордаж
    	pchar.quest.BlueBirdFleut_board.win_condition.l1 = "NPC_death";
    	pchar.quest.BlueBirdFleut_board.win_condition.l1.character = "BlueBirdTrader";
    	pchar.quest.BlueBirdFleut_board.function = "BlueBirdFleut_board";
	}
	else
	{
		AddQuestRecord("Xebeca_BlueBird", "11");
		AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	}
}

void BlueBirdFleut_over(string qName)
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	pchar.Quest.BlueBirdFleut_board.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "12");
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	pchar.questTemp.BlueBird = "returnMoney"; //иначе ивент на слухе не сработает
}
//флейт абордирован, задание выполнено
void BlueBirdFleut_board(string qName)
{
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	pchar.questTemp.BlueBird.count = sti(pchar.questTemp.BlueBird.count) + 1; //счетчик потопленных флейтов
	AddQuestRecord("Xebeca_BlueBird", "13");
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	pchar.questTemp.BlueBird = "returnMoney"; //иначе ивент на слухе не сработает
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  шебека Синяя Птица    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Генератор жемчужного промысла Sharp    начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sharp_loginNearIsland(string qName)
{	
	if (GetQuestPastMinutesParam("questTemp.Sharp") < 10) 
	{
		sld = &characters[GetCharacterIndex("Sharp")];
		LAi_SetCurHPMax(sld);
		sld.nation = pchar.nation; //нация Шарпа всегда как у ГГ
		SetCrewQuantityFull(sld);
		DeleteAttribute(sld, "ship.sails");// убрать дыры на парусах
		DeleteAttribute(sld, "ship.blots");
		DeleteAttribute(sld, "ship.masts");// вернуть сбитые мачты
		SetBaseShipData(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		Group_AddCharacter("Sharp_Group", "Sharp");			
		Group_SetGroupCommander("Sharp_Group", "Sharp");
		Group_SetAddress("Sharp_Group", pchar.questTemp.Sharp.Island, "quest_ships", "quest_ship_"+(rand(1)+1));
		Group_SetTaskRunaway("Sharp_Group", PLAYER_GROUP);
		pchar.Quest.Sharp_landOver1.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver1.win_condition.l1.location_type = "town";
		pchar.Quest.Sharp_landOver1.function = "Sharp_Over";
		pchar.Quest.Sharp_landOver2.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver2.win_condition.l1.location_type = "seashore";
		pchar.quest.Sharp_landOver2.function = "Sharp_Over";
	    Pchar.quest.Sharp_mapOver.win_condition.l1 = "MapEnter";
		pchar.quest.Sharp_mapOver.function = "Sharp_Over";
	}
	else
	{
		AddQuestRecord("SharpPearl", "12");
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
		pchar.questTemp.Sharp.brothelChance = rand(10);
	}
}

void Sharp_Over(string qName)
{
	group_DeleteGroup("Sharp_Group");
	pchar.quest.Sharp_landOver1.over = "yes";
	pchar.quest.Sharp_landOver2.over = "yes";
	pchar.quest.Sharp_mapOver.over = "yes";
	//даем запись в СЖ, если не нашел Шарпа
	if (pchar.questTemp.Sharp == "toSharp_going")
	{
		AddQuestRecord("SharpPearl", "4");
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
		pchar.questTemp.Sharp.brothelChance = rand(10);
	}
}

//------------ жемчужный промысел ----------------
void SeaPearl_login(string qName)
{
	characters[GetCharacterIndex("Sharp")].DeckDialogNode = "NewDeckSharp"; //новая нода на палубу Шарпу
	pchar.quest.SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	for (i = 1; i <= iTemp; i++)
	{                
		sTemp = "PearlCapitain_" + i;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "trader_"+(rand(15)+1), "man", "man", 10, PIRATE, 30, true));	
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetBalls(sld, "pirate");
		sld.ShipTaskLock = true;
		sld.Abordage.Enable = false;
		sld.SinkTenPercent = true; //экономия в АИ шипов
		sld.PearlTartane = true; //тартана ловцов жемчуга, можно грабить
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> стравливание
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_LockTask("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.SeaPearl_DieHard1.function = "SeaPearl_DieHard";
	Pchar.quest.SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.SeaPearl_DieHard2.function = "SeaPearl_DieHard";
}

void SeaPearl_Late(string qName)
{	
	pchar.quest.SeaPearl_login.over = "yes";
	AddQuestRecord("SharpPearl", "9");
	AddQuestUserData("SharpPearl", "iDay", FindRussianDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
	AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt"));
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
}

void SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.over = "yes";
	pchar.quest.SeaPearl_DieHard2.over = "yes";
	if (pchar.questTemp.Sharp == "SeaPearl_success")
	{	//успешное нападение
		AddQuestRecord("SharpPearl", "7");
		AddQuestUserData("SharpPearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
		AddQuestUserData("SharpPearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
	}
	else
	{	//неудачное нападение
		AddQuestRecord("SharpPearl", "8");
	}
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	CloseQuestHeader("SharpPearl");
}

void SharpSeekSpy_loginSpy(string qName)
{
	if (rand(1) && !IsDay())
	{
		LAi_group_Delete("EnemyFight");
		AddQuestRecord("SharpPearl_SeekSpy", "3");
		sld = GetCharacter(NPC_GenerateCharacter("Emillio", "pirate_5", "man", "man", 20, SPAIN, 0, true));
		sld.name = REACT_FUNCT[1];
		sld.lastname = REACT_FUNCT[2];
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
		rCharacter = GetCharacter(NPC_GenerateCharacter("QuestMan_5", "pirate_6", "man", "man", 20, SPAIN, 0, true));
		rCharacter.Dialog.Filename = "Quest\ForAll_dialog.c";
		rCharacter.dialog.currentnode = "SharpSeekSpy_fri";
		LAi_SetActorType(rCharacter);
		LAi_group_MoveCharacter(rCharacter, "EnemyFight");
		ChangeCharacterAddressGroup(rCharacter, pchar.location, "goto", "goto6");
		DoQuestCheckDelay("CannotFightCurLocation", 1.0);
		pchar.questTemp.Sharp.SeekSpy = "inDelNorte";
		pchar.quest.SharpSeekSpy_script.win_condition.l1 = "locator";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.location = "Shore55";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator_group = "quest";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator = "SharpSeekSpy";
		pchar.quest.SharpSeekSpy_script.function = "SharpSeekSpy_script";
	}
	else
	{
		SetTimerFunction("SharpSeekSpy_again", 0, 0, 3);
	}
}

void SharpSeekSpy_script(string qName)
{
	if (GetCharacterIndex("Emillio") != -1)
	{
		LAi_ActorTurnToCharacter(characterFromId("QuestMan_5"), pchar);
		sld = characterFromId("Emillio");
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else
	{
		pchar.questTemp.Sharp.SeekSpy = "over";
	}
}

void SharpSeekSpy_again(string qName)
{
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
	pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";	
}

void SharpSeekSpy_caveDialog()
{
	sld = characterFromId("QuestMan_5");
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SharpSeekSpy_fri";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_2()
{
	sld = characterFromId("Emillio");
	sld.dialog.currentnode = "SharpSeekSpy_Emi_1";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_3()
{
	DoQuestCheckDelay("CanFightCurLocation", 0.0);
	sld = characterFromId("Emillio");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	sld = characterFromId("QuestMan_5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    pchar.quest.SharpSeekSpy_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l1.character = "Emillio";
    pchar.quest.SharpSeekSpy_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l2.character = "QuestMan_5";
	pchar.quest.SharpSeekSpy_afterFight.function = "SharpSeekSpy_afterFight";
}

void SharpSeekSpy_afterFight(string qName)
{
	AddQuestRecord("SharpPearl_SeekSpy", "4");
	pchar.questTemp.Sharp.SeekSpy = "alwaysKnow";
	pchar.questTemp.Sharp = "seekSharp"; //можно снова поискать Шарпа
	CloseQuestHeader("SharpPearl");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Генератор жемчужного промысла Sharp   конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void PiratesLine_q1_tavernEnd()
{
	chrDisableReloadToLocation = false; 
	bDisableFastReload = false; 
	LAI_SetPlayerType(pchar);           
    DoReloadCharacterToLocation("PuertoPrincipe_tavern", "tables", "stay3");
    sld = CharacterFromID("QuestPirate1");
    LAI_SetSitType(sld);
}

void PiratesLine_q1_arrest(string qName)
{
	chrDisableReloadToLocation = true; 
	bDisableFastReload = true; 
	//LocatorReloadEnterDisable("Portroyal_town", "houseS1", true); //закроем дом Моргана
	GetCharacterPos(pchar, &locx, &locy, &locz);
    for (i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("QuestSold_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, 0, true));
		sld.City = "PortRoyal";
		//sld.CityType = "soldier";
		sld.BreakTmplAndFightGroup = true; //реагировать на атаку
		sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "ArrestInPR";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, pchar.location, "patrol", "patrol16");
		if (i == 1) LAi_ActorDialog(sld, pchar, "", -1, 0);
		else LAi_ActorFollow(sld, characterFromId("QuestSold_1"), "", -1);
	}	
	sld = characterFromId("QuestPirate2");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));	
	LAi_SetActorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void PiratesLine_q1_toPrison()
{
	sld = characterFromId("QuestPirate2");
	sld.lifeDay = 0;
	ChangeCharacterAddress(sld, "none", "");
	RemovePassenger(pchar, sld);
	DoReloadCharacterToLocation("PortRoyal_prison",  "goto", "goto9");
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], true);
    DoQuestFunctionDelay("PiratesLine_q1_MorganInPrison", 10.0);
    sld = characterFromId("Henry Morgan");
    LAi_SetStayTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto13");
	locations[FindLocation("PortRoyal_fort")].loginNpc = true;
}

void PiratesLine_q1_MorganInPrison(string qName)
{
    sld = characterFromID("Henry Morgan");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "PiratesLine_q1_MorganGoTo", -1);
}

void PiratesLine_q1_MorganEnd()
{
	chrDisableReloadToLocation = false; 
	bDisableFastReload = false; 
	LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //откроем дом Моргана
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], false);
	pchar.questTemp.jailCanMove = true; //чтобы спокойно выйти из тюрьмы
	AddQuestRecord("Pir_Line_1_JohnBolton", "4");
	DoQuestReloadToLocation("PortRoyal_prison", "goto", "goto12", "");
    sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
}
//пиратка, квест №3, поиски Лоу
void PiratesLine_q3_LoyHouse(string qName)
{
	AddQuestRecord("Pir_Line_3_KillLoy", "2");
	pchar.questTemp.piratesLine = "KillLoy_toSeek";
}

void PiratesLine_q3_loginSeaWolf(string qName)
{
	if (GetCompanionQuantity(pchar) <= 1 && sti(RealShips[sti(pchar.ship.type)].basetype) < 4)
	{
		sld = characterFromId("EdwardLoy");
		sld.dialog.currentnode   = "SeaWolf";
		sld.greeting = "CapSinkShip";
		pchar.questTemp.piratesLine = "KillLoy_SeaWolfBattle";
		AddQuestRecord("Pir_Line_3_KillLoy", "15");
		Group_AddCharacter("SW_Group", "EdwardLoy");			
		Group_SetType("SW_Group", "pirate");
		Group_SetGroupCommander("SW_Group", "EdwardLoy");
		sTemp = "quest_ship_" + (rand(4)+5);
		Group_SetAddress("SW_Group", "Cumana", "quest_ships", sTemp);
		Group_SetTaskAttack("SW_Group", PLAYER_GROUP);
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1.location_type = "town";
		pchar.Quest.PiratesLine_q3_over1.function = "PiratesLine_q3_over";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1.location_type = "seashore";
		pchar.quest.PiratesLine_q3_over2.function = "PiratesLine_q3_over";
	}
	else
	{
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1 = "ExitFromLocation";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1.location = "Cumana";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.function = "PiratesLine_q3_SeaWolfAgain";	
	}
}

void PiratesLine_q3_SeaWolfAgain(string qName)
{
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
	pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";	
}

void PiratesLine_q3_over(string qName)
{
	pchar.quest.PiratesLine_q3_over1.over = "yes";
	pchar.quest.PiratesLine_q3_over2.over = "yes";
	if (GetCharacterIndex("EdwardLoy") == -1)
	{
		QuestSetCurrentNode("Henry Morgan", "PL_Q3_GoodWork");
		if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_BRIGSW)
		{
			AddQuestRecord("Pir_Line_3_KillLoy", "17");
			pchar.questTemp.piratesLine = "KillLoy_GoodWork"; //выполнено все, бриг захвачен			
		}
		else
		{
			AddQuestRecord("Pir_Line_3_KillLoy", "18");
			pchar.questTemp.piratesLine = "KillLoy_LoyIsDied"; //Лоу убит, бриг не захвачен
		}
	}
	else
	{
		AddQuestRecord("Pir_Line_3_KillLoy", "16");
		pchar.questTemp.piratesLine = "KillLoy_loose"; //Лоу остался жив, полный провал
		sld = characterFromId("EdwardLoy");
		sld.lifeDay = 0;
		QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
	}
	group_DeleteGroup("SW_Group");
}
//пиратка, квест №4, грабежи жемчужных тартан
void PQ4_SeaPearl_login(string qName)
{
	pchar.quest.PQ4_SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	for (i = 1; i <= iTemp; i++)
	{                
		sTemp = "PearlCapitain_" + i;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "trader_"+(rand(15)+1), "man", "man", 10, PIRATE, 30, true));	
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetBalls(sld, "pirate");
		sld.ShipTaskLock = true;
		sld.Abordage.Enable = false;
		sld.SinkTenPercent = true; //экономия в АИ шипов
		sld.PearlTartane = true; //тартана ловцов жемчуга, можно грабить
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> стравливание
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_LockTask("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.PQ4_SeaPearl_DieHard1.function = "PQ4_SeaPearl_DieHard";
	Pchar.quest.PQ4_SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.PQ4_SeaPearl_DieHard2.function = "PQ4_SeaPearl_DieHard";
}

void PQ4_SeaPearl_Late(string qName)
{	
	pchar.quest.PQ4_SeaPearl_login.over = "yes";
	AddQuestRecord("Pir_Line_4_Pearl", "2");
	pchar.questTemp.piratesLine = "PearlQ4_late";
	sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	QuestSetCurrentNode("Henry Morgan", "PL_Q4_late");
}

void PQ4_SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.over = "yes";
	pchar.quest.PQ4_SeaPearl_DieHard2.over = "yes";
	if (pchar.questTemp.Sharp == "SeaPearl_success")
	{	//успешное нападение
		AddQuestRecord("Pir_Line_4_Pearl", "3");
		AddQuestUserData("Pir_Line_4_Pearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
		AddQuestUserData("Pir_Line_4_Pearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
		pchar.questTemp.piratesLine = "PearlQ4_goodWork";
		QuestSetCurrentNode("Henry Morgan", "PL_Q4_goodWork");
		pchar.questTemp.piratesLine.Qty.SmallPearl = pchar.questTemp.Sharp.PearlAreal.SmallPearlQty;
		pchar.questTemp.piratesLine.Qty.BigPearl = pchar.questTemp.Sharp.PearlAreal.BigPearlQty;
	}
	else
	{	//неудачное нападение
		AddQuestRecord("Pir_Line_4_Pearl", "4");
		pchar.questTemp.piratesLine = "PearlQ4_badWork";
		QuestSetCurrentNode("Henry Morgan", "PL_Q4_badWork");
	}
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	CloseQuestHeader("SharpPearl");
}
//пиратка, квест №5, работа ОЗГа
void PQ5_meetInPortRoyal(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "officer_9", "man", "man", 20, PIRATE, -1, true));
	sld.name = REACT_FUNCT[3];
	sld.lastname = REACT_FUNCT[4];
	sld.rank = 20;
	sld.city = "PortRoyal";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5CapGoodly";
	sld.greeting = "Gr_EvilPirate";
    ChangeCharacterAddressGroup(sld, "PortRoyal_town", "patrol", "patrol16");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ5_inOrryHouse(string qName)
{
	pchar.questTemp.piratesLine = "PL5Hunter_exitReload";
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], true); //закроем боевки
	chrDisableReloadToLocation = true; 
	LAi_group_Delete("EnemyFight");

	sld = GetCharacter(NPC_GenerateCharacter("Aivory", "officer_7", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 100, 100, "blade28", "pistol3", 80);
	sld.name = REACT_FUNCT[5];
	sld.lastname = REACT_FUNCT[6];
	sld.city = "Pirates";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Hero";
	sld.greeting = "Gr_MiddPirate";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto1");

	sld = GetCharacter(NPC_GenerateCharacter("Orry", "officer_15", "man", "man", 27, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 100, 100, "topor2", "pistol3", 50);
	sld.name = REACT_FUNCT[7];
	sld.lastname = REACT_FUNCT[8];
	sld.city = "Pirates";
	sld.money = 51600;
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.DontClearDead = true;  // не убирать труп через 200с
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Orry";
	sld.greeting = "pirat_quest";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto2");

	pchar.quest.PQ5_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l1.character = "Aivory";
	pchar.quest.PQ5_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l2.character = "Orry";
	pchar.quest.PQ5_afterFight.function = "PQ5_afterFight";
}

void PQ5_afterChangeMainHero()
{
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], false);
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();	
	rCharacter = characterFromID("Orry");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	sld = characterFromID("Aivory");
	sld.dialog.currentnode = "PQ5Aivory";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	EndQuestMovie();
}

void PQ5_afterChangeMainHero2()
{	
	rCharacter = characterFromID("Orry");
	LAi_group_MoveCharacter(rCharacter, "EnemyFight");
	sld = characterFromID("Aivory");			
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(pchar, true);
}

void PQ5_afterFight(string qName)
{
	AddQuestRecord("Pir_Line_5_Hunter", "11");
	AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
	pchar.questTemp.piratesLine = "PL5Hunter_toMorgan";
	chrDisableReloadToLocation = false; 
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1 = "location";
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1.location = "PortRoyal_tavern";
	Pchar.quest.PQ5_inPortPoyalTavern.function = "PQ5_inPortPoyalTavern";
}

void PQ5_inPortPoyalTavern(string qName)
{
	FreeSitLocator("PortRoyal_tavern", "sit3");
	sld = characterFromID("CapGoodly");
	sld.dialog.currentnode = "PQ5CapGoodlyEnd";
	LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit3");
}

void PQ5_Morgan_1()
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto2", "PQ5_Morgan_2", -1.0);
}

void PQ5_Morgan_4()
{
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();	
	rCharacter = characterFromID("CapGoodly");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	sld = characterFromID("Henry Morgan");
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ5_Morgan_5()
{
	LAi_group_Delete("EnemyFight");
	LAi_SetPlayerType(pchar);
	sld = characterFromID("CapGoodly");
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1.character = "CapGoodly";
	pchar.quest.PQ5_Morgan_afterFight.function = "PQ5_Morgan_afterFight";
	LAi_SetFightMode(pchar, true);
}

void PQ5_Morgan_afterFight(string qName)
{
	QuestSetCurrentNode("Henry Morgan", "PL_Q5_afterFight");
	AddQuestRecord("Pir_Line_5_Hunter", "13");
}
//пиратка, квест №6, двойник
void PQ6_ShoreBattle(string qName)
{
    LAi_group_Delete("EnemyFight"); 
	LocatorReloadEnterDisable("Shore7", "boat", true); //закроем выход в море
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//наши
	string sTemp = NationShortName(sti(pchar.nation));
    for (i=1; i<=2; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate_"+i, "pirate_"+(rand(9)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		//sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		//if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto8");
    }
	//враги
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 5); i++)
    {
        iTemp = 15 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate_"+i, "officer_"+(rand(19)+1), "man", "man", iTemp, PIRATE, -1, true));
        FantomMakeCoolFighter(sld, iTemp, 80, 80, BLADE_LONG, "pistol3", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        PlaceCharacter(sld, "goto", PChar.location);
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    Pchar.quest.PQ6_JungleDialog.win_condition.l1 = "location";
    Pchar.quest.PQ6_JungleDialog.win_condition.l1.location = "Common_jungle_01";
    Pchar.quest.PQ6_JungleDialog.function = "PQ6_JungleDialog";
}

void PQ6_JungleDialog(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation("Common_jungle_01")], true);
	chrDisableReloadToLocation = true;
	string sModel = pchar.model;
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirateHead", sModel, "man", pchar.model.animation, 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 90, 90, "topor2", "pistol6", 100);
	sld.name = pchar.name;
	sld.lastname = pchar.lastname;
    sld.dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "QuestPirateHead";
	ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto1");
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ6_JungleBattle()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	//наши
	string sTemp = NationShortName(sti(pchar.nation));
    for (i=1; i<=5; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate2_"+i, "pirate_"+(rand(9)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
	//враги
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 2); i++)
    {
        iTemp = 17 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2_"+i, "officer_"+(rand(19)+1), "man", "man", iTemp, PIRATE, -1, true));
        FantomMakeCoolFighter(sld, iTemp, 90, 90, "topor2", "pistol6", 100);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto2");
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "PQ6_afterBattle");
}
//пиратка, квест №7, мочим Соукинса
void PQ7_FriendLinney(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.piratesLine") < 20)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FriendLinney", "", "man", "man", 20, sti(pchar.nation), 5, true));							
		SetCaptanModelByEncType(sld, "pirate");
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.DeckDialogNode = "FriendLinney";
		FantomMakeCoolFighter(sld, 20, 80, 70, "blade32", "pistol3", 20);
		FantomMakeCoolSailor(sld, SHIP_LUGGER, "", CANNON_TYPE_CULVERINE_LBS16, 70, 70, 70);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.Ship.Mode = "Pirate";
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "DontRansackCaptain");		
		sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
		Group_AddCharacter("FriendLinney_Group", "FriendLinney");			
		Group_SetType("FriendLinney_Group", "pirate");
		Group_SetGroupCommander("FriendLinney_Group", "FriendLinney");
		Group_SetAddress("FriendLinney_Group", "Hispaniola1", "quest_ships", "quest_ship_4");
		Group_SetTaskNone("FriendLinney_Group");
	}
	else
	{
		AddQuestRecord("Pir_Line_7_Soukins", "3");
		pchar.questTemp.piratesLine = "Soukins_LaVegaLate";
		QuestSetCurrentNode("Henry Morgan", "PL_Q7_LaVegaLate");
	}
}

void PQ7_LoginLeon()
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("FriendLinney_Group"); //сносим друга Стива Линнея
	sld = GetCharacter(NPC_GenerateCharacter("LeonCapitain", "", "man", "man", 25, PIRATE, 30, true));							
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "LeonCapitain";
	sld.greeting = "CapSinkShip";
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade32", "pistol6", 50);
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, REACT_FUNCT[9], CANNON_TYPE_CULVERINE_LBS24, 80, 80, 80);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.Ship.Mode = "Pirate";
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");

	string sGroup = "Leon_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 

	sld.mapEnc.type = "warrior";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = REACT_FUNCT[10];
	Map_CreateWarrior("shore33", "LeonCapitain", 30);
}

void PQ7_inSoukinsResidence(string qName)
{
	QuestSetCurrentNode("Henry Morgan", "PL_Q7_BadWork"); //нода, если ничего не сделал
	if (IsLoginTime())
	{
		DoQuestFunctionDelay("PQ7_inSoukinsResidence_2", 1.5);
	}
}

void PQ7_inSoukinsResidence_2(string qName)
{
	LAi_SetActorType(pchar);
	sld = characterFromId("Richard_Soukins");
	QuestSetCurrentNode("Richard_Soukins", "PL_Q7_5");
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ7_loadToRecidence(string qName)
{
	DoQuestReloadToLocation("PuertoPrincipe_townhall", "reload", "reload2", "");
}

void PQ7_setBattleShip(string qName)
{	
	sld = &locations[FindLocation("PuertoPrincipe_townhall")];
	DeleteAttribute(sld, "reload.l2"); //уберем возможность спуститься с лестницы
	if (GetQuestPastMinutesParam("questTemp.piratesLine") > 100)
	{
		pchar.questTemp.piratesLine = "Soukins_battlshipLate";
		AddQuestRecord("Pir_Line_7_Soukins", "10");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("QuestCap_PL7", "SpaOfficer1", "man", "man", 40, SPAIN, -1, true));							
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "QuestCap_PL7";
		sld.DeckDialogNode = "QuestCap_PL7_inDeck";
		sld.greeting = "CapSinkShip";
		FantomMakeCoolFighter(sld, 40, 90, 90, "blade32", "pistol4", 200);
		FantomMakeCoolSailor(sld, SHIP_BATTLESHIP, REACT_FUNCT[11], CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "DontRansackCaptain");
		sld.AlwaysSandbankManeuver = true;
		sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
		sld.DontRansackCaptain = true;
		SetCharacterPerk(sld, "FastReload");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "CannonProfessional");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");

		string sGroup = "Quest_Ship";
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 

		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = REACT_FUNCT[12];
		Map_CreateTraderXZ(1009.22, -992.708, 988.514, 515.407, "QuestCap_PL7", 15);
	}
}

void PQ7_winBattleShip(string qName)
{
	pchar.questTemp.piratesLine = "Soukins_battlshipWin";
	QuestSetCurrentNode("Henry Morgan", "PL_Q7_GoodWork");
	AddQuestRecord("Pir_Line_7_Soukins", "13");
	pchar.quest.PQ7_BattleShip_dieHard.over = "yes";
}

void PQ8_timeOver(string qName) //убираем моргана
{
	pchar.questTemp.piratesLine = "over";
	sld = characterFromId("Henry Morgan");
	ChangeCharacterAddress(sld, "none", "");
	AddQuestRecord("Pir_Line_8_Panama", "2");
	CloseQuestHeader("Pir_Line_8_Panama");
	SetTimerFunction("PQ8_openPanama", 0, 0, 40);
	QuestSetCurrentNode("Oliver_Green", "PL_Q8_over"); //ноду секретарю
}

void PQ8_openPanama(string qName) //откроем Панаму
{
	LocatorReloadEnterDisable("Shore48", "reload1_back", false); 
	LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false);
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "First time";
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
    LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void PQ8_openPanama_2(string qName) //откроем Панаму
{
	sld = characterFromId("Henry Morgan");
	if (pchar.questTemp.piratesLine == "Panama_backToShip") 
	{
		SetTimerFunction("PQ8_openPanama_3", 0, 0, 180);
	}
	else 
	{
		sld.dialog.currentnode = "I_know_you_good";
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		LAi_SetImmortal(sld, true);
		LAi_LoginInCaptureTown(sld, false);
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	//возвращаем Джекмена
	iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}               
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "I_know_you_good";
    }
    //Возвращаем на место Соукинса
	iTemp = GetCharacterIndex("Richard_Soukins");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}                   
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "First time";
    }
	LocatorReloadEnterDisable("Panama_ExitTown", "reload4", false); 
	SetLocationCapturedState("Panama_town", false);
	bDisableLandEncounters = false;
	pchar.quest.PL_Q8_backFight_1.over = "yes"; //на всякий случай
}

void PQ8_openPanama_3(string qName) //Морган после поездки в Лондон
{
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "PL_Q8_afterPanama";
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	LAi_SetImmortal(sld, true);
	LAi_LoginInCaptureTown(sld, false);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void PQ8_PanamaTimerOver(string qName)
{
    if (IsEntity(worldMap))
    {
        if (!bQuestCheckProcessFreeze) // можно показать
		{
	        pchar.quest.PQ8_PanamaTimerOver_01.over = "yes"; // сброс, если уже откладывали
	        pchar.quest.PQ8_PanamaTimerOver_02.over = "yes";
			pchar.quest.PQ8_EnterPortoBello.over = "yes"; //снимаем прерывание на вход
            
            aref arOldMapPos;
			makearef(arOldMapPos, worldMap.old);
            WdmPrepareMapForAbordage(arOldMapPos);
            MakeCloneShipDeck(pchar, true); // подмена палубы
            DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
	        ReloadFromWMtoL_complete();
	        
            sld = characterFromID("Henry Morgan");
            ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
            LAi_SetWarriorType(sld);
	        LAi_warrior_DialogEnable(sld, true);
	        sld.dialog.currentnode = "PL_Q8_timeOver";
   	        // ==> антураж
            for (i=1; i<5; i++)
        	{
                sTemp = "pirate_" + i;
                sld = GetCharacter(NPC_GenerateCharacter(sTemp, sTemp, "man", "man", 15, PIRATE, 1, true));
                sld.dialog.Filename = "Quest\sailors_dialog.c";
	            sld.dialog.currentnode = "Morgan_wait_you";
                LAi_SetWarriorType(sld);
                LAi_warrior_DialogEnable(sld, true);
                LAi_SetLoginTime(sld, 0.0, 24.0);
                LAi_SetHP(sld, 100.0, 100.0);
                ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto"+i);
            }
            pchar.quest.Munity = "";  // признак выхода с палубы (закрыто, а то можно не говорить)
            LAi_LockFightMode(pchar, true);
		}
		else
		{   // отложим до разморозки (пролет табличек)
      		Pchar.quest.PQ8_PanamaTimerOver_01.win_condition.l1 = "MapEnter";
            Pchar.quest.PQ8_PanamaTimerOver_01.function = "PQ8_PanamaTimerOver";
		}
	}
	else
	{   // подождем выхода на карту, раз время прошло, но мы не на ней
		Pchar.quest.PQ8_PanamaTimerOver_02.win_condition.l1 = "MapEnter";
        Pchar.quest.PQ8_PanamaTimerOver_02.function = "PQ8_PanamaTimerOver";
	}
}

void PQ8_EnterPortoBello()
{
	sld = characterFromId("Henry Morgan");
	LAi_SetImmortal(sld, false);
	pchar.quest.PQ8_PanamaTimerOver.over = "yes"; //снимаем таймер 
	//bQuestDisableMapEnter = true;
}

void PQ8_MorganInPortoBello()
{
	chrDisableReloadToLocation = true; 
	DoQuestFunctionDelay("PQ8_MorganInPortoBello_2", 3.0);	
}

void PQ8_MorganInPortoBello_2(string qName)
{	
	sld = characterFromId("Henry Morgan");
	LAi_LoginInCaptureTown(sld, true); 
	LAi_SetCurHPMax(sld);
	sld.dialog.currentNode = "PL_Q8_PBResidence";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PQ8_PBExitResidence(string qName)
{
	iTemp = GetCharacterIndex("Henry Morgan");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("John Morris");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	sld = characterFromId("Richard_Soukins");
	sld.DeckDialogNode = "PL_Q8_deck_2";
	AddQuestRecord("Pir_Line_8_Panama", "5");
	pchar.Quest.PQ8_fromPBport.win_condition.l1 = "EnterToSea";
	pchar.Quest.PQ8_fromPBport.function = "PQ8_fromPBport";
	SetTimerFunction("PQ8_controlShore48", 0, 0, 2);
}

void PQ8_fromPBport(string qName)
{
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1.location_type = "town";
	pchar.Quest.PQ8_controlShore48_1.function = "PQ8_controlShore48";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1.location_type = "seashore";
	pchar.Quest.PQ8_controlShore48_2.function = "PQ8_controlShore48";
}

void PQ8_controlShore48(string qName)
{
	pchar.Quest.PQ8_controlShore48.over = "yes";
	pchar.Quest.PQ8_controlShore48_1.over = "yes";
	pchar.Quest.PQ8_controlShore48_2.over = "yes";
	if (pchar.location == "Shore48")
	{	//ГГ вовремя и на месте -->
		LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], true); //закрываем локацию для боевки
		LocatorReloadEnterDisable("Shore48", "boat", true); //Не даем выходить в море
		chrDisableReloadToLocation = true; 
		bDisableLandEncounters = true; //энкаунтеры не генерим
		pchar.questTemp.piratesLine = "Panama_inShore";
		pchar.questTemp.piratesLine.crewHero = makeint(GetCrewQuantity(pchar) / 100 / 2);	//запомним кол-во десанта от ГГ
		if (sti(pchar.questTemp.piratesLine.crewHero) > 5) pchar.questTemp.piratesLine.crewHero = 5;
		pchar.questTemp.piratesLine.crewRichard = 3;   //запомним кол-во десанта от Соукинса
		//бойцы ГГ. предположительно ГГ имет 3 абордажника.
		SetCrewQuantity(pchar, GetMinCrewQuantity(pchar)); //минимальную команду на шип
		iTemp = sti(pchar.questTemp.piratesLine.crewHero) ; //число обычных солдат ГГ
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHpirate_"+i, "pirate_"+(rand(9)+1), "man", "man", sti(pchar.rank), PIRATE, -1, true));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }	
        for (i=1; i<=iTemp; i++) //мушкетеры ГГ
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHmush_"+i, "mushketer_"+(rand(4)+1), "man", "mushketer", sti(pchar.rank), PIRATE, -1, false));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }
		//бойцы Соукинса
		iTemp = sti(pchar.questTemp.piratesLine.crewRichard) ; //число обычных солдат Соукинса
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSpirate_"+i, "pirate_"+(rand(9)+1), "man", "man", 25, PIRATE, -1, true));
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
        for (i=1; i<=iTemp; i++) //мушкетеры Соукинса
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSmush_"+i, "mushketer_"+(rand(4)+1), "man", "mushketer", 25, PIRATE, -1, false));
            LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			TakeNItems(sld,"potion1", rand(2)+1);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
		//офицеры Соукинса
        for (i=1; i<=3; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSofficer_"+i, "officer_"+(rand(9)+1), "man", "man", 30, PIRATE, -1, true));
            FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol4", 100);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto4");
		}
		//сам Соукинс
		sld = characterFromId("Richard_Soukins");
		sld.dialog.currentNode = "Shore48";
		LAi_SetImmortal(sld, false);
		LAi_NoRebirthEnable(sld);
		GiveItem2Character(sld, "blade23");
		EquipCharacterbyItem(sld, "blade23");
		GiveItem2Character(sld, "pistol4");
		EquipCharacterbyItem(sld, "pistol4");
		TakeNItems(sld,"potion1", 5);
		RemoveCharacterCompanion(pchar, sld); //убираем Соукинса из компаньонов
		ChangeCharacterAddressGroup(sld, "Shore48", "goto", "goto11");	
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
		//прерывание на вход в джанглы
		pchar.Quest.PQ8_jungle_05.win_condition.l1 = "location";
		pchar.Quest.PQ8_jungle_05.win_condition.l1.location = "Panama_jungle_05";
		pchar.Quest.PQ8_jungle_05.function = "PQ8_jungle_05";
	}
	else
	{	//ГГ не успел или не туда зашел -->
		iTemp = GetCharacterIndex("Richard_Soukins");
		if (iTemp != -1)
		{
			if(IsCompanion(&characters[iTemp]))  
			{
				RemoveCharacterCompanion(pchar, &characters[iTemp]);
			}                   
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
        //Возвращаем на место Джекмена
		iTemp = GetCharacterIndex("Jackman");
		if (iTemp != -1)
		{              
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
		AddQuestRecord("Pir_Line_8_Panama", "6");
		CloseQuestHeader("Pir_Line_8_Panama");
		SetTimerFunction("PQ8_openPanama", 0, 0, 40);
		LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
		LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		pchar.questTemp.piratesLine = "over";
	}
}

void PQ8_jungle_05(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=12; i<=18; i++) //max - 21
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==16) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));       
		FantomMakeCoolFighter(sld, sti(pchar.rank), 80, 80, "blade34", "pistol6", 80);
		sld.BreakTmplAndFightGroup = true; 
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 8;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 6;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 3;
	for (i=1; i<=iTemp; i++) //max - 11
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_04.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_04.win_condition.l1.location = "Panama_jungle_04";
	pchar.Quest.PQ8_jungle_04.function = "PQ8_jungle_04";
}


void PQ8_jungle_04(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=13; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==14) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));      
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 100);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	for (i=14; i<=17; i++) //индейцы
    {
        if (i==14 || i==16) sTemp = "indsair2";
		else sTemp = "indsar1";
		sld = GetCharacter(NPC_GenerateCharacter("IndEnemy_"+i, "indsair2", "man", "man", Rank, SPAIN, -1, true)); //to_do анимация
		FantomMakeCoolFighter(sld, Rank, 90, 90, "topor2", "", 5);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_03.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_03.win_condition.l1.location = "Panama_jungle_03";
	pchar.Quest.PQ8_jungle_03.function = "PQ8_jungle_03";
}

void PQ8_jungle_03(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=16; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==13) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		sld.BreakTmplAndFightGroup = true; 
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_ExitTown.win_condition.l1 = "location";
	pchar.Quest.PQ8_ExitTown.win_condition.l1.location = "Panama_ExitTown";
	pchar.Quest.PQ8_ExitTown.function = "PQ8_ExitTown";
}

void PQ8_ExitTown(string qName)
{ 
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(LAi_IsDead(&characters[iTemp]))
	{	//Соукинс мертв, задание выполнено
		AddQuestRecord("Pir_Line_8_Panama", "7");	
		pchar.questTemp.piratesLine = "Panama_RichardGoodWork";
	}
	else
	{	//Соукинс жив, задание провалено
		AddQuestRecord("Pir_Line_8_Panama", "8");	
		pchar.questTemp.piratesLine = "Panama_RichardBadWork";
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
	}
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inExitTown";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc15");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc16");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc17");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc18");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+(i+10));
		}
	}
    //--------------------------- люди Моргана ------------------------------
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMpirate_"+i, "pirate_"+(rand(9)+1), "man", "man", 25, PIRATE, 10, true));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc20");
	}
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMmush_"+i, "mushketer_"+(rand(4)+1), "man", "mushketer", 25, PIRATE, 10, false));
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc19");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=11; i<=15; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==12) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
    for (i=1; i<=10; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_ExitTown_afterFight");
}

void PQ8_piratesInPanama(string qName)
{
	DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured"); //Порто Белло можно себе
	//фантома мэра Панамы - резиденцию
	rCharacter = characterFromId("Panama_Mayor");
	sld = GetCharacter(NPC_GenerateCharacter("FantomMayor", rCharacter.model, "man", "man", sti(rCharacter.rank), sti(rCharacter.nation), -1, false));
	sld.quest.type = "hovernor";
	sld.City = "Panama";
	sld.location = "Panama_TownhallRoom";
	sld.greeting = "spa_gov_common";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
    sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.Dialog.CurrentNode = "PQ8_Mayor";
	LAi_SetStayType(sld);
	LAi_LoginInCaptureTown(sld, true);
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    //--------------------------- люди Моргана ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
}	

void PQ8_MorganInPanama_1(string qName)
{
	chrDisableReloadToLocation = true;
	//делаем видимым ключ
	sld = ItemsFromID("keyPanama");
	sld.shown = true; 
	sld.startLocation = "Panama_prison";
	sld.startLocator = "item1";
	BackItemDescribe("keyPanama");
	BackItemName("keyPanama");
	//Моргана в город и на диалог
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentNode = "PL_Q8_Panama1";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_ResEnterBox(string qName)
{
	if (CheckCharacterItem(pchar, "keyPanama"))
    {
		TakeItemFromCharacter(pchar, "keyPanama");
		chrDisableReloadToLocation = true;
		sld = characterFromId("Henry Morgan");
		sld.dialog.currentNode = "PL_Q8_Panama2";		
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1 = "ExitFromLocation";
        Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1.location = pchar.location;
        Pchar.quest.PL_Q8_ResEnterBox_2.function = "PL_Q8_ResEnterBox_2";
	}
}

void PL_Q8_ResEnterBox_2(string qName)
{
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
	pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
}

void PL_Q8_inPanamaFort2(string qName)
{
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1 = "location";
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1.location = "Panama_town";
	Pchar.quest.PL_Q8_inPanamaPirates_1.function = "PL_Q8_inPanamaPirates_1";
}

void PL_Q8_inPanamaPirates_1(string qName)
{
	chrDisableReloadToLocation = true;	
	//--------------------------- меняем ноды у оставшихся пиратов ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    //--------------------------- люди Моргана ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}	
	//разговорный пират
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirate", "pirate_"+(rand(9)+1), "man", "man", 25, PIRATE, 0, true));
	sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentNode = "PL_Q8_QFackMorgan";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_backFight_1(string qName) 
{
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+1);
		if (i==2) sTemp = "off_spa_2";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, 12, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc1");
    }
    for (i=1; i<=4; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(2)+1), "man", "mushketer", Rank, SPAIN, 12, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc3");
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------- Переспать с официанткой ---------------------
void WaitressFack_null(string qName) //нулим квест официантки
{
	pchar.questTemp.different = "free";
	pchar.quest.WaitressFack_inRoom.over = "yes"; 
	DeleteAttribute(pchar, "questTemp.different.FackWaitress");
}

void WaitressFack_inRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("WaitressFack_Enter", 10.0 + frand(10.0));
}

void WaitressFack_Enter(string qName)
{	
	LAi_group_Delete("EnemyFight"); 
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	if (pchar.questTemp.different.FackWaitress.Kick == "0")
	{	//подстава
		iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter("BerglarWairessQuest", "officer_"+(rand(19)+1), "man", "man", iTemp, PIRATE, -1, true));
		FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
		sld.dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "WaitressBerglar";	
		sld.greeting = "Enc_Raiders"; 
 		//меняем обличие официантки
		rCharacter = characterFromId(locations[reload_location_index].fastreload + "_waitress");
		rCharacter.model = "girl_" + (rand(7)+1);
		SetRandomNameToCharacter(rCharacter);
		FaceMaker(rCharacter);  
	}
	else
	{
        sld = characterFromId("WairessQuest");
	}
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void WaitressFack_outRoom()
{
	// ==> Забираем клинки, пистоли и деньги.
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
    {             
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    }
    pchar.money = 0;
    // <== Забираем клинки, пистоли и деньги.
	AddCharacterExpToSkill(pchar, "Pistol", 100);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1.0);
	DoQuestCheckDelay("OpenTheDoors", 10.0);
	pchar.questTemp.different = "FackWaitress_noMoney"; //флаг ограбили
}

void WaitressFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingLight", 30);
	AddCharacterExpToSkill(pchar, "Fencing", 30);
	AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
	LAi_SetFightMode(pchar, true);
	pchar.questTemp.different = "FackWaitress_fighted"; //флаг пришлось подраться
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.WaitressFack_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.WaitressFack_afterFight.win_condition.l1.character = "BerglarWairessQuest";
	pchar.quest.WaitressFack_afterFight.win_condition = "OpenTheDoors";
}

void WaitressFack_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "FackWaitress_facking"; 
}

// ----------------- Пожертвование хозяйки борделя ---------------------
void HostessChurch_null(string qName) //нулим квест 
{
	//если квест еще взят, то деньги считай прикарманены
	if (characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch == "taken") 
	{
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "baster";
	}
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.HostessChurch");
}

// ----------------- Украсть чертежи на верфи ---------------------
void ShipyardsMap_returnCFN(string qName) 
{
	string  sName;
	aref	arDis, arRld;
	int location_index = FindLocation(pchar.questTemp.different.ShipyardsMap.city + "_town");
    makearef(arRld, Locations[location_index].reload);
    int		Qty = GetAttributesNum(arRld);
    for (int a=0; a<Qty; a++)
    {
    	arDis = GetAttributeN(arRld, a);
		sName = arDis.go;
    	if (findsubstr(sName, "_shipyard" , 0) != -1)
    	{
			arDis.close_for_night = true;
			break;
    	}
    }
	LocatorReloadEnterDisable(pchar.questTemp.different.ShipyardsMap.city + "_shipyard", "reload2", false);
}

// ----------------- Найти кольцо мэра в борделе ---------------------
void TakeMayorsRing_null(string qName) //нулим квест 
{
	pchar.questTemp.different = "free";
	if (CheckCharacterItem(pchar, "MayorsRing"))
    {
		TakeItemFromCharacter(pchar, "MayorsRing");
		AddQuestRecord("SeekMayorsRing", "4");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		ChangeCharacterReputation(pchar, -3);
	}
	else
	{
		if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
		{
			AddQuestRecord("SeekMayorsRing", "5");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			ChangeCharacterReputation(pchar, -5);
		}
	}
	DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
}

// ----------------- Развод на секс хозяйки борделя ---------------------
void SexWithHostess_null(string qName) //нулим квест 
{
	if (pchar.questTemp.different.HostessSex == "toRoom")
	{
		sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
		LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
	}
	LAi_SetOwnerTypeNoGroup(sld);
	sld.dialog.currentnode = "First time";
	sld.quest.NotGoneToSex = true; //не пришел. Секса больше не будет
	DeleteAttribute(pchar, "questTemp.different.HostessSex");
	pchar.questTemp.different = "free";
}

void SexWithHostess_goToRoom()  
{
	chrDisableReloadToLocation = true;
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", pchar.questTemp.different.HostessSex.city + "_Brothel_room", "goto", "goto3", "OpenTheDoors", -1);
	pchar.quest.SexWithHostess_inRoom.win_condition.l1 = "location";
	pchar.quest.SexWithHostess_inRoom.win_condition.l1.location = pchar.questTemp.different.HostessSex.city + "_Brothel_room";
	pchar.quest.SexWithHostess_inRoom.function = "SexWithHostess_inRoom";
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", false);
}

void SexWithHostess_inRoom(string qName)
{
	DoQuestFunctionDelay("SexWithHostess_inRoom_2", 1.5);
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
}

void SexWithHostess_inRoom_2(string qName)
{
	sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	sld.dialog.currentnode = "Hostess_inSexRoom";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SexWithHostess_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "HostessSex";
}

// ----------------- Миниквесты портмана  ---------------------
void SetCapitainFromCityToSea(string qName) //помещаем в море кэпа, который сейчас ошивается в городе
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.location	= "none";
		sld.location.group = "";
		sld.location.locator = "";
		//в морскую группу кэпа
		string sGroup = "PorpmansShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectNotEnemyColony(sld); //определим колонию, куда отправится кэп
		sld.quest.stepsQty = sti(sld.quest.stepsQty) + 1; //количество выходов в море
		//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
		sTemp = GetArealByCityName(sld.city);
		sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушел в другой город
		AddSimpleRumourEx(LinkRandPhrase(REACT_FUNCT[13] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[14] + GetFullName(sld) + REACT_FUNCT[15] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[16] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[17] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[18] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[19] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + REACT_FUNCT[20]), 
			sld.city, iTemp, 1, "PortmansBook_DeliveryToCap", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 5;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SetRobberFromSeaToMap(string qName) //помещаем в море кэпа-вора, который счас стоит на рейде в порту
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушел в другой город
		AddSimpleRumourEx(LinkRandPhrase(REACT_FUNCT[21] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[22] + GetFullName(sld) + REACT_FUNCT[23] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[24] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[25] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[26] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[27] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + REACT_FUNCT[28]), 
			sld.city, iTemp, 1, "Portmans_SeekShip_rum", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")].id + "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SeekShip_checkAbordage(string qName) //кэп-вор успешно абордирован
{	
	//смотрим, взят корабль себе или потоплен
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	bOk = false;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(pchar, i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			if (sld.ship.name == rCharacter.quest.PortmansSeekShip.shipName && 
				RealShips[sti(sld.ship.type)].BaseName == rCharacter.quest.PortmansSeekShip.shipTapeName &&
				RealShips[sti(sld.Ship.Type)].basetype == rCharacter.quest.PortmansSeekShip.shipTape)
			{
				bOk = true;
			}
		}
	}	
	//решение по результатам проверки
	sld = characterFromId(pchar.quest.(qName).CapId);
	sTemp = "SeekShip_checkSink" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на утонул
	if (bOk)
	{		
		rCharacter.quest = "SeekShip_success"; //флаг успешного взятия на абордаж
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "5");
	}
	else
	{
		rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "9");
	}
}

void SeekShip_checkSink(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId);
	rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
	sTemp = rCharacter.id + "Portmans_SeekShip";
	AddQuestRecordEx(sTemp, "Portmans_SeekShip", "8");
	sTemp = "SeekShip_checkAbordage" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
}

// ----------------- ночной сторож в церкви ---------------------
void ChurchNightGuard_exitFromLoc(string qName)
{
	DeleteAttribute(pchar, "PostEventQuest.questDelay.ChurchNightGuard_timerInChurch"); //снимаем таймер на отработку действия
	if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0) pchar.questTemp.different.Church_NightGuard.NightQty = 1;
	else pchar.questTemp.different.Church_NightGuard.NightQty = sti(pchar.questTemp.different.Church_NightGuard.NightQty) + GetQuestPastDayParam("questTemp.different.Church_NightGuard");
	if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
	{
		sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "4");
	}
	else
	{
		if (GetTime() > 6.0 && GetTime() < 23.99)
		{
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //перезапишем дату
		}
		else
		{
			sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTemp, "Church_NightGuard", "3");
			CloseQuestHeader(sTemp);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard"); //снимаем флаг
			ChangeCharacterReputation(pchar, -20);
		}
	}
}

void ChurchNightGuard_timerInChurch(string qName)
{
	int iRank, num;
	if (pchar.questTemp.different.Church_NightGuard.chance == pchar.questTemp.different.Church_NightGuard.NightQty)
	{	//грабители лезут
		pchar.quest.ChurchNightGuard_exitFromLoc.over = "yes"; //снимаем прерывание на выход из локации
		pchar.questTemp.different.Church_NightGuard.NightQty = 3; //присвоим максимум дней дежурства
		pchar.questTemp.different.Church_NightGuard.fight = true; //флаг боевки
        chrDisableReloadToLocation = true; // закрыть выход из локации.
		sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "5");		
        LAi_group_Delete("EnemyFight");
		//--> генерим ранг 
		num = rand(2)+1;
		if (sti(pchar.rank) > 6) 
		{
			if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
			else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
		}
		else  
		{	//казуалам зеленый свет на начало игры
			if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
			else 
			{
				iRank = 1;
				num = 1;
			}
		}	
		//<-- генерим ранг 		
		for (i=1; i<=num; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+10), "man", "man", iRank, PIRATE, 0, true));
			SetFantomParamFromRank(sld, iRank, true);         
			LAi_SetWarriorType(sld); 
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, "EnemyFight");
            ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
        }
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "ChurchBerglar";
        LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	}
	else
	{	//нету никого
        SetLaunchFrameFormParam(REACT_FUNCT[29], "ChurchNightGuard_timerInChurch_2", 0, 3);
        LaunchFrameForm();
        RecalculateJumpTable();
	}
}
// ----------------- поиск кэпов, дача квеста горожанином ---------------------
void SCQ_seekCapIsDeath(string qName)
{	
	string sTitle;
	sld = characterFromId(pchar.quest.(qName).CapId); //капитан
	rCharacter = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)]; //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	DeleteAttribute(NullCharacter, "capitainBase." + sld.id);
	//<-- чистим базу нпс-кэпов
	if (rCharacter.quest.SeekCap == "manSlave")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
	}
	if (sld.quest.SeekCap == "womanRevengeFight") //проверим флаг боя на улице, уже можно валить
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
	}
	if (sld.quest.SeekCap == "womanHasband" || rCharacter.quest.SeekCap == "manRapeWife" || sld.quest.SeekCap == "manFriend" || sld.quest.SeekCap == "womanRevenge" || rCharacter.quest.SeekCap == "womanPirates")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "4");
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		CloseQuestHeader(sTitle);
		//снимаем горожанку-маньячку
		if (sld.quest.SeekCap == "womanRevenge")
		{
			rCharacter.lifeDay = 0;
		}
	}
}
//смерть квестодателя закрывает и чистит квест
void SCQ_CitizenIsDeath(string qName)
{
	sld = characterFromId(pchar.quest.(qName).CapId); //капитан	
	sld.lifeDay = 0;
	rCharacter = characterFromId(pchar.quest.(qName).CitizenId); //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	DeleteAttribute(NullCharacter, "capitainBase." + sld.id);
	//<-- чистим базу нпс-кэпов
	Map_ReleaseQuestEncounter(sld.id);
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	sTemp = "SecondTimer_" + sld.id;
	pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
	sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
	string sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
	CloseQuestHeader(sTitle);
}

void CitizCapFromSeaToMap(string qName) //помещаем на карту кэпа, разыскиваемого горожанами
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId)
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.nation = sld.quest.nation;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation)); 
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг искомого кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		//на карту
		iTemp = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушел в другой город
		AddSimpleRumourEx(LinkRandPhrase(REACT_FUNCT[30] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[31] + GetFullName(sld) + REACT_FUNCT[32] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[33] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[34] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ".", 
			REACT_FUNCT[35] + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + REACT_FUNCT[36] + XI_ConvertString("Colony"+sld.quest.targetCity+"Acc") + ". " + GetFullName(sld) + REACT_FUNCT[37]), 
			sld.city, iTemp, 1, "Citiz_SeekCap_rum", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = sld.quest.cribCity + "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//меняем сроки проверки по Id кэпа в базе нпс-кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

//после боевки в каюте. для всех квестов по поисков кэпов ситезанами
void CitizSeekCap_afterCabinFight(string qName)
{	
	sld = GetCharacter(NPC_GenerateCharacter(pchar.quest.(qName).label + "_" + pchar.quest.(qName).WifeCity, pchar.quest.(qName).model, "woman", "towngirl", 5, pchar.quest.(qName).nation, -1, false));
	sld.name = pchar.quest.(qName).WifeName;
	sld.lastname = pchar.quest.(qName).WifeLastname;
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = pchar.quest.(qName).label + "_Board";
	sld.quest.SeekCap = pchar.quest.(qName).label;
	sld.quest.cribCity = pchar.quest.(qName).WifeCity;
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

//кораблик с капитаном, который имеет мушкет несчастного мушкетера
void SetMushketFromSeaToMap(string qName)
{
	sld = characterFromId("MushketCap");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = REACT_FUNCT[38];
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//бриг Даниэль
void SetDanielleFromSeaToMap(string qName)
{
	sld = characterFromId("Danielle");
	//в морскую группу кэпа
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = REACT_FUNCT[39];
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка ГПК           начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void ISS_MurderSignExecute(string qName)
{
	pchar.questTemp.LSC.killCost = sti(pchar.questTemp.LSC.killCost)-1;
	pchar.questTemp.LSC = "PoorMurderBegin";
	if (sti(pchar.questTemp.LSC.killCost) <= 0)
	{
		pchar.questTemp.LSC = "PoorMurderExecute";
		DeleteAttribute(pchar, "questTemp.LSC.killCost");
		SetQuestHeader("ISS_PoorsMurder");
		AddQuestRecord("ISS_PoorsMurder", "2");
	}
}

void LSC_enterStuvesantBox(string qName)
{
	AddQuestRecord("ISS_PoorsMurder", "5");
	pchar.questTemp.LSC = "toVillemstadTavern";
	//посадим воришку в таверну
	FreeSitLocator("Villemstad_tavern", "sit1");
	sld = GetCharacter(NPC_GenerateCharacter("GiveKeyMan", "shipowner_10", "man", "man", 10, HOLLAND, -1, false));
	sld.name = REACT_FUNCT[40];
	sld.lastname = REACT_FUNCT[41];
	sld.city = "Villemstad";
	sld.location	= "Villemstad_tavern";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode   = "GiveKeyMan";
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
}

void LSC_openMasterHouse(string qName)
{	
	LocatorReloadEnterDisable("Villemstad_town", "houseSp5", false);
	//делаем видимым ключ
	sld = ItemsFromID("keyQuestLSC");
	sld.shown = true; 
	pchar.quest.LSC_enterMasterHouse.win_condition.l1 = "location";
	pchar.quest.LSC_enterMasterHouse.win_condition.l1.location = "Villemstad_houseSp5";
	pchar.quest.LSC_enterMasterHouse.function = "LSC_enterMasterHouse";	
}

void LSC_enterMasterHouse(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], true);
	//ставим Мастера Ключей
	sld = characterFromId("GiveKeyMan");
	sld.dialog.currentnode = "GiveKeyManInside";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp5", "barmen", "bar1");
    LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar("GiveKeyMan", "", 0.0, 1.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void LSC_enterSoldiers()
{	
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight"); 
	pchar.questTemp.LSC = "CanFoundStuvesantKey";
	sld = characterFromId("GiveKeyMan"); 
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
	int iNum = sti((2+MOD_SKILL_ENEMY_RATE)/2);
	for (i=1; i<=iNum; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("MKSold"+i, "sold_hol_"+(rand(7)+1), "man", "man", iTemp, HOLLAND, 0, true));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld); 
		//LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("MKOfficer", "off_hol_2", "man", "man", iTemp, HOLLAND, 0, true));
	SetFantomParamFromRank(sld, iTemp, true);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "MK_HollOfficer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void FirstLoginLostShipsCity(string qName) //первоначальная генерация нпс в ГПК
{
	//начальные настройки
	pchar.questTemp.LSC = "AdmiralIsWaiting";
	bDisableFastReload = true; //закроем фастрелоады
	//из письма делаем посление Тизера Дэна -->
	TakeItemFromCharacter(pchar, "letter_LSC");
	ChangeItemName("letter_LSC", "itmname_letter_LSC_2");
	ChangeItemDescribe("letter_LSC", "itmdescr_letter_LSC_2");
	i = FindLocation("LostShipsCity_town");
	locations[i].private11.items.letter_LSC = 1;
	//восстанавливаем флаги и пр. в игре вне ГПК
	CloseQuestHeader("ISS_PoorsMurder");
	sld = characterFromId("hol_guber"); //чтобы мог переезжать
	DeleteAttribute(sld, "notMoveAble");
	DeleteAttribute(&colonies[FindColony("Villemstad")], "notCaptured"); //Виллемстад можно себе
	LAi_group_Delete("TmpEnemy"); //группа граждан ГПК
	LAi_group_Delete(LAI_GROUP_TmpEnemy); //группа граждан которых можно валить безнаказанно
	//группы кланов -->
	LAi_group_Delete("PearlGroup_1"); //для кланов заюзаем пока группы жемчужников
	LAi_group_Register("PearlGroup_1");
	LAi_group_SetRelation("PearlGroup_1", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius("PearlGroup_1", 50);
	LAi_group_SetHearRadius("PearlGroup_1", 20);
	LAi_group_SetSayRadius("PearlGroup_1", 20);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	LAi_group_Delete("PearlGroup_2");
	LAi_group_Register("PearlGroup_2");
	LAi_group_SetRelation("PearlGroup_2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius("PearlGroup_2", 50);
	LAi_group_SetHearRadius("PearlGroup_2", 20);
	LAi_group_SetSayRadius("PearlGroup_2", 20);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
	//<-- группы кланов
	//снять шторм с острова ГПК
	reload_cur_island_index = FindIsland("LostShipsCity"); //to_do, в релиз убрать
	DeleteAttribute(&Islands[reload_cur_island_index], "alwaysStorm");
	DeleteAttribute(&Islands[reload_cur_island_index], "storm");
	DeleteAttribute(&Islands[reload_cur_island_index], "tornado");
	DeleteAttribute(&Islands[reload_cur_island_index], "QuestlockWeather");
	DeleteAttribute(&Islands[reload_cur_island_index], "MaxSeaHeight");
	//сносим все корабли и компаньонов
	int cn;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (i == 0)
			{	//снимаем корабль ГГ
				DeleteAttribute(pchar, "ship");
				pchar.ship.name = "";
				pchar.ship.type = SHIP_NOTUSED;
				SetCharacterShipLocation(pchar, "");
			}
			else
			{
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeDay = 0;
				LAi_KillCharacter(sld);
				i--;
			}
		}
	}
	//сносим всех пассажиров и офицеров
	for (i=0; i<=PASSENGERS_MAX; i++)
	{
		cn = GetPassenger(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			LAi_KillCharacter(sld);
			i--;
		}
	}
	//адмирала на стрем, чтобы ГГ долго не гулял
	PChar.quest.LSC_stormTimer_1.win_condition.l1            = "Timer";
	PChar.quest.LSC_stormTimer_1.win_condition.l1.date.hour  = 23;
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.function = "LSC_stormTimer_1";
	//Начальные слухи
	AddSimpleRumourCityTip(REACT_FUNCT[42], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[43], "LostShipsCity", 10, 1, "LSC", "");

	//мэр-адмирал
	sld = GetCharacter(NPC_GenerateCharacter("LSCMayor", "capitan_2", "man", "man", 50, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 50, 90, 90, "blade33", "pistol4", 200);
	sld.name = REACT_FUNCT[44];
	sld.lastname = REACT_FUNCT[45];
	sld.city = "LostShipsCity";
	sld.location = "SanAugustineResidence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_0";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mayor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mayor"; //тип нпс
	sld.greeting = "Gr_Kapper";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.standUp.exitDisable = true;   //залочить выход в случае драки
	sld.watchBoxes.exitDisable = true; //залочить выход в случае драки
	//sld.talker = true; //начать диалог
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №1
	sld = GetCharacter(NPC_GenerateCharacter("Ment_1", "officer_13", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol4", 100);
	sld.name = REACT_FUNCT[46];
	sld.lastname = REACT_FUNCT[47];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto9"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_1"; 
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №2
	sld = GetCharacter(NPC_GenerateCharacter("Ment_2", "off_fra_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade25", "pistol4", 100);
	sld.name = REACT_FUNCT[48];
	sld.lastname = REACT_FUNCT[49];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_2"; 
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 2; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №3
	sld = GetCharacter(NPC_GenerateCharacter("Ment_3", "sold_hol_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade22", "pistol4", 100);
	sld.name = REACT_FUNCT[50];
	sld.lastname = REACT_FUNCT[51];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto11"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_3"; 
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №4
	sld = GetCharacter(NPC_GenerateCharacter("Ment_4", "off_spa_2", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade24", "pistol4", 100);
	sld.name = REACT_FUNCT[52];
	sld.lastname = REACT_FUNCT[53];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_4";  
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №5
	sld = GetCharacter(NPC_GenerateCharacter("Ment_5", "officer_8", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade33", "pistol4", 100);
	sld.name = REACT_FUNCT[54];
	sld.lastname = REACT_FUNCT[55];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_5"; 
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №6
	sld = GetCharacter(NPC_GenerateCharacter("Ment_6", "Dragoon_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "topor2", "pistol4", 100);
	sld.name = REACT_FUNCT[56];
	sld.lastname = REACT_FUNCT[57];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_6"; 
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	sld.greeting = "pirat_common";
	SetSPECIAL(sld, 10, 4, 9, 6, 8, 9, 7);
	SetSelfSkill(sld, 100, 100, 100, 30, 90);
	SetShipSkill(sld, 10, 10, 5, 20, 20, 30, 10, 10, 60);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Rush");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Sliding");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ таверна ------------------------ 
	//тавернщик
	sld = GetCharacter(NPC_GenerateCharacter("LSCBarmen", "barmen_8", "man", "man", 20, PIRATE, -1, false));
	sld.name = REACT_FUNCT[58];
	sld.lastname = REACT_FUNCT[59];
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Barmen.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //тип нпс
	sld.greeting = "Gr_Barmen";
	LAi_SetBarmanType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	//официантка
	sld = GetCharacter(NPC_GenerateCharacter("LSCwaitress", "CitizenWom_1", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = xiDStr("Armo");
	sld.lastname = REACT_FUNCT[61];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	sld.dialog.filename   = "Quest\LostShipsCity\Waitress.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //тип нпс
	sld.greeting = "Armo_Dulin";
	LAi_SetWaitressType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ внешние горожане ------------------------	
	// внешний горожанин Педро Хуртадо
	sld = GetCharacter(NPC_GenerateCharacter("PedroHurtado", "usurer_2", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[62];
	sld.lastname = REACT_FUNCT[63];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto06_1"; 
	sld.location.baseShip = "06"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 2; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\PedroHurtado.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Жиль Бару
	sld = GetCharacter(NPC_GenerateCharacter("ZhilBaru", "trader_16", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[64];
	sld.lastname = REACT_FUNCT[65];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto07_1"; 
	sld.location.baseShip = "07"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 1; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ZhilBaru.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Тристан Борчер
	sld = GetCharacter(NPC_GenerateCharacter("TristanBorcher", "shipowner_13", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[66];
	sld.lastname = REACT_FUNCT[67];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto09_1"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\TristanBorcher.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Ройел Хааг
	sld = GetCharacter(NPC_GenerateCharacter("RoyelHaag", "trader_11", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[68];
	sld.lastname = REACT_FUNCT[69];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14_1"; 
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\RoyelHaag.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Доминик Легро
	sld = GetCharacter(NPC_GenerateCharacter("DominicLegro", "trader_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[70];
	sld.lastname = REACT_FUNCT[71];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15_1"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\DiminicLegro.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Джорж Стоукс
	sld = GetCharacter(NPC_GenerateCharacter("JorgeStouks", "barmen_5", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[72];
	sld.lastname = REACT_FUNCT[73];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto08_1"; 
	sld.location.baseShip = "08"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\JorgeStouks.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_JorgeStouks";
	sld.talker = true; //начать диалог
	LAi_RemoveLoginTime(sld);	
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");
	ChangeCharacterAddress(sld, "LostShipsCity_town", "goto16_3");

	// ------------------------ внешние горожане в таверне ------------------------
	// в таверне Генри Фолдер
	sld = GetCharacter(NPC_GenerateCharacter("HenryFolder", "barmen_14", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[74];
	sld.lastname = REACT_FUNCT[75];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit2"; 
	sld.location.baseShip = "03"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto03_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\HenryFolder.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Феликс Мендоза
	sld = GetCharacter(NPC_GenerateCharacter("FelixMendoza", "shipowner_1", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[76];
	sld.lastname = REACT_FUNCT[77];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit3"; 
	sld.location.baseShip = "10"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto10_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\FelixMendoza.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Роджер Воулер
	sld = GetCharacter(NPC_GenerateCharacter("RodgerWoyler", "usurer_5", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[78];
	sld.lastname = REACT_FUNCT[79];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit5"; 
	sld.location.baseShip = "12"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto12_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\RodgerWoyler.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Андрэ Лабор
	sld = GetCharacter(NPC_GenerateCharacter("AndreLabor", "shipowner_15", "man", "man", 15, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 15, 60, 60, "blade20", "pistol2", 10);
	sld.name = REACT_FUNCT[80];
	sld.lastname = REACT_FUNCT[81];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit9"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto15_2"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\AndreLabor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Стефан Клейн
	sld = GetCharacter(NPC_GenerateCharacter("StefanKleyn", "shipowner_6", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[82];
	sld.lastname = REACT_FUNCT[83];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit8"; 
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto14_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\StefanKleyn.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Томас Фланн
	sld = GetCharacter(NPC_GenerateCharacter("ThomasFlann", "citiz_1", "man", "man", 10, PIRATE, -1, false));
	sld.name = REACT_FUNCT[84];
	sld.lastname = REACT_FUNCT[85];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit6"; 
	sld.location.baseShip = "02"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto02_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ThomasFlann.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Пабло Барадес
	sld = GetCharacter(NPC_GenerateCharacter("PabloBarades", "officer_20", "man", "man", 10, PIRATE, -1, true));
	sld.name = REACT_FUNCT[86];
	sld.lastname = REACT_FUNCT[87];
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit14"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto09_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\PabloBarades.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ внешние горожане в церкви ------------------------
	// падре
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Priest", "priest_3", "man", "man", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[88];
	sld.lastname = REACT_FUNCT[89];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Priest.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "priest"; //тип нпс
	sld.greeting = "Gr_padre";
	LAi_SetPriestType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");		
	
	// в церкви Сандра Гомес
	sld = GetCharacter(NPC_GenerateCharacter("SandraGomes", "girl_4", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[90];
	sld.lastname = REACT_FUNCT[91];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 
	sld.location.baseShip = "04"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto04_3"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\SandraGomes.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в церкви Моника Райт
	sld = GetCharacter(NPC_GenerateCharacter("MonikaRight", "girl_5", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[92];
	sld.lastname = REACT_FUNCT[93];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; 
	sld.location.baseShip = "08"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto08_3"; 
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\MonikaRight.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ магазин ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Trader", "trader_5", "man", "man", 20, PIRATE, -1, true));
	sld.name = REACT_FUNCT[94];
	sld.lastname = REACT_FUNCT[95];
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "EsmeraldaStoreBig";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Trader.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "trader"; //тип нпс
	sld.greeting = "tra_common";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	

	// ------------------------ Тюрьма ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_PrisonerHead", "Hobart", "man", "man", 40, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 40, 87, 87, "blade32", "pistol4", 100);
	sld.name = REACT_FUNCT[96];
	sld.lastname = REACT_FUNCT[97];
	sld.rank = 40;
	sld.city = "LostShipsCity";
	sld.location = "TartarusPrison";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "prisonerHead";
	sld.cityTape = "prisonerHead"; //тип нпс
	sld.greeting = "pirat_common";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.location.days = 2; //передвижения через .. дней
	//sld.talker = true; //начать диалог
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	SaveCurrentNpcQuestDateParam(sld, "location");

	// тюремщик №1
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Prisoner1", "SoldierEnglish_1", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol3", 100);
	sld.name = REACT_FUNCT[98];
	sld.lastname = REACT_FUNCT[99];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "Prisoner";
	sld.cityTape = "prisoner"; //тип нпс
	sld.greeting = "pirat_common";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.location.hours = 4; //передвижения через .. часов
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ Банкир ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Usurer", "trader_9", "man", "man", 30, PIRATE, -1, true));
	sld.name = REACT_FUNCT[100];
	sld.lastname = REACT_FUNCT[101];
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "CarolineBank";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Usurer.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "usurer"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetImmortal(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	

	// ------------------------ Механик ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("Mechanic", "Mechanic", "man", "man", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[102];
	sld.lastname = REACT_FUNCT[103];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.dialog.filename   = "Quest\LostShipsCity\Mechanic.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mechanic"; //тип нпс
	sld.greeting = "Gr_Master";
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");

	// ------------------------ внутренние горожане ------------------------
	// внутреняя горожанка Элис Тейлор
	sld = GetCharacter(NPC_GenerateCharacter("ElisTaylor", "girl_3", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[104];
	sld.lastname = REACT_FUNCT[105];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "CeresSmithy";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "03"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto03_0"; 
	sld.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ElisTaylor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Орели Бертин
	sld = GetCharacter(NPC_GenerateCharacter("OreliBertin", "girl_6", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[106];
	sld.lastname = REACT_FUNCT[107];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FurieShipInside2";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "06"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto06_0"; 
	sld.location.baseLocation = "FurieShipInside2"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\OreliBertin.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Леа Тоорс
	sld = GetCharacter(NPC_GenerateCharacter("LeaToors", "girl_7", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[108];
	sld.lastname = REACT_FUNCT[109];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "PlutoStoreSmall";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto09_0"; 
	sld.location.baseLocation = "PlutoStoreSmall"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\LeaToors.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Элиза Кальво
	sld = GetCharacter(NPC_GenerateCharacter("ElizaCalvo", "girl_8", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[110];
	sld.lastname = REACT_FUNCT[111];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "SantaFlorentinaShipInside4";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto14_0"; 
	sld.location.baseLocation = "SantaFlorentinaShipInside4"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ElizaCalvo.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Сесиль Галард
	sld = GetCharacter(NPC_GenerateCharacter("SesilGalard", "BaynesWife", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = REACT_FUNCT[112];
	sld.lastname = REACT_FUNCT[113];
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "AvaShipInside3";
	sld.location.group = "barmen";
	sld.location.locator = "stay"; 
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto15_0"; 
	sld.location.baseLocation = "AvaShipInside3"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\SesilGalard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_SesilGalard";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	SaveCurrentNpcQuestDateParam(sld, "location");

	//------------------- Клан Нарвал -------------------
	// нарвал главарь
	sld = GetCharacter(NPC_GenerateCharacter("Narval_head", "capitan_3", "man", "man", 35, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol4", 200);
	sld.name = REACT_FUNCT[114];
	sld.lastname = REACT_FUNCT[115];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto1"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	SaveCurrentNpcQuestDateParam(sld, "location"); //главе клана сделаем перемещения
	// нарвал №1
	sld = GetCharacter(NPC_GenerateCharacter("Narval_1", "officer_18", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade21", "pistol6", 10);
	sld.name = REACT_FUNCT[116];
	sld.lastname = REACT_FUNCT[117];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №2
	sld = GetCharacter(NPC_GenerateCharacter("Narval_2", "officer_12", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 26, 80, 80, "blade34", "pistol3", 150);
	sld.name = REACT_FUNCT[118];
	sld.lastname = REACT_FUNCT[119];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №3
	sld = GetCharacter(NPC_GenerateCharacter("Narval_3", "trader_2", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 24, 70, 70, "blade25", "pistol5", 50);
	sld.name = REACT_FUNCT[120];
	sld.lastname = REACT_FUNCT[121];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №4
	sld = GetCharacter(NPC_GenerateCharacter("Narval_4", "pirate_7", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 85, 85, "blade33", "pistol6", 150);
	sld.name = REACT_FUNCT[122];
	sld.lastname = REACT_FUNCT[123];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto5"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №5
	sld = GetCharacter(NPC_GenerateCharacter("Narval_5", "pirate_3", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 100);
	sld.name = REACT_FUNCT[124];
	sld.lastname = REACT_FUNCT[125];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto6"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №6
	sld = GetCharacter(NPC_GenerateCharacter("Narval_6", "pirate_4", "man", "man", 22, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 22, 65, 65, "blade22", "pistol6", 10);
	sld.name = REACT_FUNCT[126];
	sld.lastname = REACT_FUNCT[127];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto7"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");
	// нарвал №7
	sld = GetCharacter(NPC_GenerateCharacter("Narval_7", "officer_14", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 85, 85, "blade23", "pistol4", 150);
	sld.name = REACT_FUNCT[128];
	sld.lastname = REACT_FUNCT[129];
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Narval.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_1");

	//------------------- Клан Каспер -------------------
	// каспер главарь
	sld = GetCharacter(NPC_GenerateCharacter("Casper_head", "shipowner_7", "man", "man", 35, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol5", 200);
	sld.name = REACT_FUNCT[130];
	sld.lastname = REACT_FUNCT[131];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//SaveCurrentNpcQuestDateParam(sld, "location"); //главе клана сделаем перемещения
	//каспер №1
	sld = GetCharacter(NPC_GenerateCharacter("Casper_1", "pirate_9", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "topor2", "pistol3", 100);
	sld.name = REACT_FUNCT[132];
	sld.lastname = REACT_FUNCT[133];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №2
	sld = GetCharacter(NPC_GenerateCharacter("Casper_2", "pirate_8", "man", "man", 21, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 21, 80, 80, "blade26", "pistol6", 120);
	sld.name = REACT_FUNCT[134];
	sld.lastname = REACT_FUNCT[135];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto6"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №3
	sld = GetCharacter(NPC_GenerateCharacter("Casper_3", "pirate_10", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade34", "pistol4", 150);
	sld.name = REACT_FUNCT[136];
	sld.lastname = REACT_FUNCT[137];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto5"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №4
	sld = GetCharacter(NPC_GenerateCharacter("Casper_4", "pirate_2", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade23", "pistol3", 100);
	sld.name = REACT_FUNCT[138];
	sld.lastname = REACT_FUNCT[139];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto7"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №5
	sld = GetCharacter(NPC_GenerateCharacter("Casper_5", "officer_10", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 130);
	sld.name = REACT_FUNCT[140];
	sld.lastname = REACT_FUNCT[141];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto13"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №6
	sld = GetCharacter(NPC_GenerateCharacter("Casper_6", "officer_1", "man", "man", 29, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 29, 80, 80, "blade25", "pistol4", 100);
	sld.name = REACT_FUNCT[142];
	sld.lastname = REACT_FUNCT[143];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto1" //; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №7
	sld = GetCharacter(NPC_GenerateCharacter("Casper_7", "officer_2", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade34", "pistol6", 150);
	sld.name = REACT_FUNCT[144];
	sld.lastname = REACT_FUNCT[145];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №8
	sld = GetCharacter(NPC_GenerateCharacter("Casper_8", "officer_17", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade26", "pistol4", 150);
	sld.name = REACT_FUNCT[146];
	sld.lastname = REACT_FUNCT[147];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; // 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №9
	sld = GetCharacter(NPC_GenerateCharacter("Casper_9", "officer_5", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade28", "pistol6", 150);
	sld.name = REACT_FUNCT[148];
	sld.lastname = REACT_FUNCT[149];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto10"; //
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №10
	sld = GetCharacter(NPC_GenerateCharacter("Casper_10", "officer_6", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade28", "pistol3", 150);
	sld.name = REACT_FUNCT[150];
	sld.lastname = REACT_FUNCT[151];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto11"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	//каспер №11
	sld = GetCharacter(NPC_GenerateCharacter("Casper_11", "officer_20", "man", "man", 27, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade28", "pistol4", 250);
	sld.name = REACT_FUNCT[152];
	sld.lastname = REACT_FUNCT[153];
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto12"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
}

//снять шторм
void LSC_stormTimer_1(string qName)
{
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			DeleteAttribute(&locations[i], "alwaysStorm");
			DeleteAttribute(&locations[i], "storm");
			DeleteAttribute(&locations[i], "tornado");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");
		}
	}
	//адмирал ловит ГГ, если тот еще не явился к нему
	if (pchar.questTemp.LSC == "AdmiralIsWaiting")
	{
		pchar.quest.LSC_admiralOwnFind.win_condition.l1 = "location";
		pchar.quest.LSC_admiralOwnFind.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_admiralOwnFind.function = "LSC_admiralOwnFind";
	}
}

void LSC_admiralOwnFind(string qName)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("LSC_admiralOwnFind_1", 1+rand(2));
}

void LSC_admiralOwnFind_1(string qName)
{
	sld = characterFromId("LSCMayor");
	sld.dialog.currentnode = "FoundHero";
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void LSC_admiralTakeAll()
{
	chrDisableReloadToLocation = false;
	//установим типовые ключи -->
	sld = ItemsFromID("key1");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key2");
	sld.shown = true;
	sld.startLocation = "VelascoShipInside1";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key3");
	sld.shown = true;
	sld.startLocation = "EsmeraldaStoreBig";
	sld.startLocator = "item1";
	//откроем кланы
	ref rLoc = &locations[FindLocation("LostShipsCity_town")];
	DeleteAttribute(rLoc, "reload.l61.disable");
	DeleteAttribute(rLoc, "reload.l70.disable");
	DeleteAttribute(rLoc, "reload.l72.disable");
	pchar.questTemp.LSC = "AfterAdmiral";
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);	
	//сносим все предметы, кроме квестовых -->
    aref arItems;
	string sName;
    makearef(arItems, pchar.items);
    int	Qty = GetAttributesNum(arItems);
    for (int a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			pchar.questTemp.items.(sName) = pchar.items.(sName);
		}
    }
	DeleteAttribute(pchar, "items");
	pchar.items = "";
	makearef(arItems, pchar.questTemp.items);
    Qty = GetAttributesNum(arItems);
    for (a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(pchar, sName, sti(arItems.(sName)));
    }
	DeleteAttribute(pchar, "questTemp.items");
	//<-- сносим все предметы, кроме квестовых	
	//проверим, не залезал и ГГ в сундучок Тизера -->
	int iLoc = FindLocation("LostShipsCity_town");
	if (CheckAttribute(&locations[iLoc], "private11.equip"))
	{
		DeleteAttribute(&locations[iLoc], "private11.money"); //если залезал, то заберем денюжки, хи-хи...
	}
	//<-- проверим, не залезал и ГГ в сундучок Тизера
	AddQuestRecord("ISS_MainLine", "3");
	//------->>> пул нужных слухов для наводок на квесты		AddSimpleRumourCityTip("", "LostShipsCity", 10, 1, "LSC", "");
	//освобождение мужа Элис Тейлор
	LSC_beginElisHusband();	
	AddSimpleRumourCityTip(REACT_FUNCT[154], "LostShipsCity", 10, 1, "LSC", "LSC_rumourElisHusband");
	//квест со скелетом Лейтона Декстера
	AddSimpleRumourCityTip(REACT_FUNCT[155], "LostShipsCity", 10, 1, "LSC", "LSC_rumourLostDecster");
	//наводка на Доминика Легро с вином
	AddSimpleRumourCityTip(REACT_FUNCT[156], "LostShipsCity", 10, 1, "LSC", "");
}

void LSC_returnBarmen(string qName)
{
	pchar.questTemp.LSC = "toWineCellarLate";
	sld = characterFromId("LSCBarmen");
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");
}

void LSC_returnBarmen_2(string qName)
{
	sld = characterFromId("LSCBarmen");
	LAi_CharacterEnableDialog(sld);
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");
}

void LSC_enterToProtector(string qName)
{
    chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true); 
    DoQuestFunctionDelay("LSC_enterToProtector_1", 7.0);
}

void LSC_enterToProtector_1(string qName)
{
	LAi_group_Delete("EnemyFight"); 
    sld = GetCharacter(NPC_GenerateCharacter("LSCQuestMent", "off_hol_2", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade28", "pistol3", 50);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestMent";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_KillOneNarval(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true); 
    DoQuestFunctionDelay("LSC_KillOneNarval_1", 3.0 + frand(4.0));
}

void LSC_KillOneNarval_1(string qName)
{
	LAi_group_Delete("EnemyFight"); 
    sld = GetCharacter(NPC_GenerateCharacter("LSCQuestNarval", "officer_16", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade28", "pistol4", 150);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestNarval";
	ChangeItemName("DOjeronRing", "itmname_DOjeronRingNarval");
	ChangeItemDescribe("DOjeronRing", "itmdescr_DOjeronRingNarval");
	ref itm;
	itm = ItemsFromID("DOjeronRing");
	itm.picIndex = 12;
	itm.picTexture = "ITEMS_4";
	GiveItem2Character(sld, "DOjeronRing");
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.DontClearDead = true;  // не убирать труп через 200с
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void NavalEnterOfficers(string qName)
{
	int idxMent;
	string sOffName;
	chrDisableReloadToLocation = true;
	for (i=1 ; i<=3; i++)
	{
		idxMent = GetCharacterIndex("Ment_" + i);
		if (idxMent != -1)
		{
			ChangeCharacterAddressGroup(&characters[idxMent], "VelascoShipInside1", "officers", "officer_"+i);
			characters[idxMent].Dialog.CurrentNode = "AffterFightN";
			LAi_SetWarriorType(&characters[idxMent]);
			LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER);
		}
	}
	LAi_group_SetCheck("PearlGroup_1", "NarvalDestroyed");
	LAi_SetImmortal(characterFromId("Narval_head"), false);
}

void NavalExitVelasco(string qName)
{
	int idxMent;
	string sOffName;
	for (i=1 ; i<=3; i++)
	{
		idxMent = GetCharacterIndex("Ment_" + i);
		if (idxMent != -1)
		{
			sld = &characters[idxMent];
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
			sld.Dialog.CurrentNode = "First time";
			sld.cityTape = "ment"; //тип нпс
			LAi_SetLSCoutTypeNoGroup(sld);
		}
	}
	//распространим слухи
	AddSimpleRumourCityTip(REACT_FUNCT[157], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[158], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[159], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[160], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[161], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[162], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[163], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[164], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[165], "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[166], "LostShipsCity", 10, 1, "LSC", "");
}

void LSC_scriptInterception(string qName)
{
	if (pchar.location == "FleuronTavern")
	{
		LAi_SetActorType(pchar);
		sld = characterFromId("LSCMayor");
		sld.Dialog.CurrentNode = "Interception";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
		LAi_ActorGoToLocator(sld, "quest", "stay1", "LSC_EnterComplite_1", -1);
		sld = characterFromId("Casper_head");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_ActorGoToLocator(sld, "quest", "stay2", "LSC_EnterComplite_2", -1);		
	}
	else
	{
		pchar.questTemp.LSC = "InterceptionLate";
		AddQuestRecord("ISS_MainLine", "19");
	}
}

void LCS_EndScriptInterception()
{
    //на место камеру и пр.
	SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar)
    locCameraFollow();
    EndQuestMovie(); 
	//разводим адмирала и каспера
	sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1.0);
	sld = characterFromId("Casper_head");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1.0);	
	//прерывание на возврат адмирала и каспера на места
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_EndScriptInterception_2.function = "LCS_EndScriptInterception_2";
	if (pchar.questTemp.LSC == "InterceptionOk")
		AddQuestRecord("ISS_MainLine", "22");
	else
		AddQuestRecord("ISS_MainLine", "20");

}

void LCS_EndScriptInterception_2(string qName)
{
	sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	sld.location.going = "toTavern"; //посадим в таверну, ведь он туда пошел
	SaveCurrentNpcQuestDateParam(sld, "location");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");	
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");

	sld = characterFromId("Casper_head");
	sld.Dialog.CurrentNode = "First time";
	//LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto1");
}

void LSC_changeBarmen(string qName)
{
	if (pchar.location != "FleuronTavern") 
	{
		pchar.questTemp.LSC = "barmenIsDead";
		sld = characterFromId("LSCBarmen");
        sld.name = REACT_FUNCT[167];
        sld.lastname = REACT_FUNCT[168];
		sld.model = "barmen_2";
        SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
		AddSimpleRumourCityTip(REACT_FUNCT[169], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[170], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[171], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[172], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[173], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[174], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
		AddSimpleRumourCityTip(REACT_FUNCT[175], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	}
	else
	{
		pchar.quest.LSC_changeBarmen_2.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_changeBarmen_2.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_changeBarmen_2.function = "LSC_changeBarmen_2";
	}
}

void LSC_changeBarmen_2(string qName)
{
	pchar.questTemp.LSC = "barmenIsDead";
	sld = characterFromId("LSCBarmen");
    sld.name = REACT_FUNCT[176];
    sld.lastname = REACT_FUNCT[177];
	sld.model = "barmen_2";
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
	AddSimpleRumourCityTip(REACT_FUNCT[178], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[179], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[180], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[181], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[182], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[183], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
	AddSimpleRumourCityTip(REACT_FUNCT[184], "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
}

void LSC_SaveSesilGalard(string qName)
{
	if (pchar.location.locator == "reload1") sTemp = "goto5";
	else sTemp = "goto4";
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = characterFromId("SesilGalard");
	sld.dialog.currentnode = "HelpMe";
	sld.greeting = "Enc_RapersGirl_1";
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  sTemp);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_SaveSesilGalard_2()
{	
	LAi_SetFightMode(pchar, true);
	LAi_LocationFightDisable(loadedLocation, false);
	//Сесилия
	sld = characterFromID("SesilGalard");
	LAi_SetActorTypeNoGroup(sld);
	if (pchar.location.locator == "reload1") 
	{		
		LAi_ActorRunToLocator(sld, "barmen", "bar2", "LSC_SesilAfraid", -1);	
	}
	else 
	{
		LAi_ActorRunToLocator(sld, "barmen", "stay", "LSC_SesilAfraid", -1);	
	}
	//клановцы
	LAi_group_Delete("EnemyFight");
	iTemp = 10+MOD_SKILL_ENEMY_RATE*2;
    for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("LSCBandit"+i, "officer_"+(i+3), "man", "man", iTemp, PIRATE, 0, true));
        FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        LAi_SetWarriorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
        if (i == 2)
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
		else
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "start"+i);
    }
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetCheck("EnemyFight", "LSC_SesilAfterFight");
}
//вход к касперам на Сан Габриэль
void LSC_enterCasper(string qName)
{	
	//если тюремщик Томас Бойл с нами
	iTemp = GetCharacterIndex("LSC_Prisoner1");
	if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic") 
	{
		characters[iTemp].reactionOnFightModeOn = true; //среагировать на обнаженку оружия
		characters[iTemp].lifeDay = 0;
		LAi_warrior_DialogEnable(&characters[iTemp], true);
		LAi_group_SetCheck("PearlGroup_2", "LSC_PrisonerAfterFight");
	}
	//касперы
	iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic") 
	{
		chrDisableReloadToLocation = true;
		LAi_group_SetCheck("PearlGroup_2", "OpenTheDoors");
		AddSimpleRumourCityTip(REACT_FUNCT[185], "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(REACT_FUNCT[186], "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(REACT_FUNCT[187], "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(REACT_FUNCT[188], "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(REACT_FUNCT[189], "LostShipsCity", 10, 1, "LSC", "");
	}
	//откроем возможность попасть к механику.
	LocatorReloadEnterDisable("SanGabrielMechanic", "reload2", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload55", false);
	pchar.questTemp.LSC = "toSeekMechanikCanMove";
	DeleteAttribute(pchar, "questTemp.LSC.Armo");
}
//прерывание на завал каспера от Армо
void LSC_KillOneCasper(string qName)
{
	pchar.quest.LSC_checkCasperDead.over = "yes"; 
	if (sti(pchar.questTemp.LSC.Armo) < 5)
	{		
		iTemp = sti(pchar.quest.(qName).casperIdx);
		pchar.questTemp.LSC.Armo = sti(pchar.questTemp.LSC.Armo) + 1; //на следующего...
		pchar.questTemp.LSC.Armo.waiting = true;
		AddQuestRecord("ISS_MainLine", "36");
		AddQuestUserData("ISS_MainLine", "sName", GetFullName(&characters[iTemp]));
		AddSimpleRumourCityTip(REACT_FUNCT[190], "LostShipsCity", 2, 1, "LSC", "");
		AddSimpleRumourCityTip(REACT_FUNCT[191], "LostShipsCity", 2, 1, "LSC", "");
	}
	else
	{	//засада после третьего каспера
		DoQuestFunctionDelay("LSC_KillOneCasper_3", 4.0);
		chrDisableReloadToLocation = true;
	}
}

void LSC_KillOneCasper_3(string qName)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Casper_6");
	sld.dialog.currentnode = "FackYou";
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator("reload", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}
//таймер завален ли каспер от Армо
void LSC_checkCasperDead(string qName)
{
	pchar.quest.LSC_KillOneCasper.over = "yes"; 
	iTemp = sti(pchar.quest.(qName).casperIdx);
	if (!LAi_IsDead(&characters[iTemp]))
	{
		pchar.questTemp.LSC.Armo = 11; //профукал каспера
		sld = &characters[iTemp];
		sld.dialog.currentnode   = "First time";
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PearlGroup_2");
		ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto9");
	}
}

void LSC_3CarperAttackArmo()
{
	LAi_SetFightMode(pchar, true);
	chrDisableReloadToLocation = false;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//меняем убитую Армо
	sld = characterFromId("LSCwaitress");
    sld.dialog.currentnode = "ArmoIsDead";
	sld.name = REACT_FUNCT[192];
    sld.lastname = xiDStr("Prescott");
	sld.model = "Girl_2";
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
    AddSimpleRumourCityTip(REACT_FUNCT[194], "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip(REACT_FUNCT[195], "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip(REACT_FUNCT[196], "LostShipsCity", 10, 1, "LSC", "");
	//первый каспер
	sld = characterFromId("Casper_6");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	LAi_SetWarriorTypeNoGroup(sld);
	//второй
	sld = characterFromId("Casper_7");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	//третий
	sld = characterFromId("Casper_8");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	AddQuestRecord("ISS_MainLine", "39");
}

void LSC_underwaterDeathTimer(string qName)
{
	GameOver("sea");
}

//начать малый шторм
void LSC_SmallStormIsBegin()
{
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			locations[i].alwaysStorm = true; //живем в штормах
			if (locations[i].id == "LostShipsCity_town")
			{
				locations[i].alwaysStorm.WaveHeigh = true; //поднять уровень воды до 2.5 для низкого волнения
			}
			locations[i].storm = true;
			locations[i].tornado = true;			
		}
	}
	//пустим слух о шторме
	AddSimpleRumourCityTip(REACT_FUNCT[197], "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[198], "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[199], "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[200], "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(REACT_FUNCT[201], "LostShipsCity", 5, 1, "LSC", "");
	//расставим нпс на свои места, штормовые. ограничиваем хождение по городу
	LAi_group_Delete("EnemyFight");
	for(i=0; i<MAX_CHARACTERS; i++)
	{	
		makeref(sld, characters[i]);
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
		{	
			if (sld.cityTape == "mayor")
			{
				//LAi_SetImmortal(sld, false);
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMove";  //не перемещаться более
				LAi_SetHuberType(sld); //садим за стол
				LAi_group_MoveCharacter(sld, "EnemyFight");	
				ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
			}
			if (sld.cityTape == "ment")
			{
				if (sld.id == "Ment_6")
				{
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //не перемещаться более
					LAi_SetLSCoutTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
				}
				else
				{
					sTemp = sld.id;
					sTemp = "goto" + strcut(sTemp, 5, 5);
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //не перемещаться более
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", sTemp);
				}				
			}
			if (sld.cityTape == "citizenHome")
			{
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMove";  //не перемещаться более
				LAi_SetOwnerTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
			}
			if (sld.cityTape == "prisonerHead" || sld.cityTape == "prisoner")
			{
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
		}
	}
}

void LSC_afterArestMachanic(string qName)
{
	sld = &characters[sti(pchar.questTemp.LSC.lastManId)];
	LAi_SetStayTypeNoGroup(sld);			
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "barmen",  "stay");
	sld = characterFromId("Mechanic");
	ChangeCharacterAddress(sld, "none", "");
	DeleteAttribute(pchar, "questTemp.LSC.lastManId");
}

void LSC_fightEnterResidence(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	//отравляем наверх
	string sLocator;
	iTemp = GetCharacterIndex("Ment_1")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//------------------------
	iTemp = GetCharacterIndex("Ment_2")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//------------------------
	iTemp = GetCharacterIndex("Ment_3")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_CharacterReincarnation(sld, false, false);
		LAi_SetLSCoutTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
		LAi_warrior_DialogEnable(sld, false);
	}
	//в резиденции
	iTemp = GetCharacterIndex("Ment_4")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_SetWarriorTypeNoGroup(sld); 
		LAi_warrior_DialogEnable(sld, false);
		LAi_warrior_SetStay(sld, true);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto2");
	}
	iTemp = GetCharacterIndex("Ment_5")
	if (iTemp != -1)
	{
		sld = &characters[iTemp];
		LAi_SetWarriorTypeNoGroup(sld); 
		LAi_warrior_DialogEnable(sld, false);
		LAi_warrior_SetStay(sld, true);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto3");
	}	
	sld = characterFromId("LSCMayor");
	sld.dialog.currentnode = "fightTalking";
	LAi_SetImmortal(sld, false);
	LAi_SetActorTypeNoGroup(sld); 
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto10");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void LSC_figtInResidence()
{
	sld = characterFromId("Ment_6");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	LAi_SetWarriorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
    pchar.quest.LSC_figtInResidence_1.win_condition.l1 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l1.character = "LSCMayor";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2.character = "Ment_4";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3.character = "Ment_5";
    pchar.quest.LSC_figtInResidence_1.function= "LSC_figtInResidence_1";
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void LSC_figtInResidence_1(string qName)
{
	sld = characterFromId("Ment_6");
	if (!CharacterIsDead(sld))
	{
		sld.dialog.currentnode = "MentOffIsLife";
		LAi_SetActorTypeNoGroup(sld); 
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	}
	else
	{
		AddQuestRecord("ISS_MainLine", "65");
		chrDisableReloadToLocation = false;
	}
	pchar.quest.LSC_enterToPrison.win_condition.l1 = "location";
	pchar.quest.LSC_enterToPrison.win_condition.l1.location = "TartarusPrison";
	pchar.quest.LSC_enterToPrison.function = "LSC_enterToPrison";

}

void LSC_enterToPrison(string qName)
{
	chrDisableReloadToLocation = true;
	sld = characterFromId("Mechanic");
	sld.dialog.currentnode = "inPrison";
	LAi_SetImmortal(sld, true);
	LAi_SetGroundSitType(sld);
	ChangeCharacterAddressGroup(sld, "TartarusPrison", "quest", "prison3");
}

//начать большой шторм
void LSC_BigStormIsBegin()
{
	bDisableFastReload = true; 
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (locations[i].id == "LostShipsCity_town")
		{	//закрываем релоады
			locations[i].notCrateFoam = true; //не рисовать пену
			DeleteAttribute(&locations[i], "reload.l2.disable"); //открываем выход с ГПК
			locations[i].reload.l231.disable = true;
			for(int n=3; n<=73; n++)
			{	
				sTemp = "l" + n;
				locations[i].reload.(sTemp).disable = true; 
			}
			DeleteAttribute(&locations[i], "reload.l2.disable"); //откроем выход из ГПК
			locations[i].locators_radius.reload.reload2_back = 16.0;
			pchar.location.from_sea = "LostShipsCity_town";
			//второй патч ГПК
			locations[i].models.day.charactersPatch = "LostShipsCity_patch_end";
			locations[i].models.night.charactersPatch = "LostShipsCity_patch_end";	
			//погода
			DeleteAttribute(&locations[i], "alwaysStorm");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");		
			locations[i].alwaysStorm_2 = true; //живем в штормах
			locations[i].alwaysStorm_2.WaveHeigh = true; //поднять уровень воды до 2.5 для низкого волнения
			locations[i].storm = true;
			locations[i].tornado = true;
		}
	}
	//снять шторм с острова ГПК
	i = FindIsland("LostShipsCity");
	Islands[i].reload.l2.emerge = "reload2_back";
	Islands[i].reload_enable = false;
	Islands[i].visible = true;
	Islands[i].reload_enable = false;
	Islands[i].alwaysStorm = true; //живем в штормах
	Islands[i].storm = true;
	Islands[i].tornado = true;
	//прерывание на удаление острова ГПК и снятие шторма с ареала
	pchar.quest.LSC_closeLine.win_condition.l1 = "location";
	pchar.quest.LSC_closeLine.win_condition.l1.location = "LostShipsCity";
	pchar.quest.LSC_closeLine.function = "LSC_closeLine";
	SetTimerFunction("LSC_takeStormIsland", 0, 0, 10);
}

void LSC_closeLine(string qName)
{
	AddQuestRecord("ISS_MainLine", "69");
	CloseQuestHeader("ISS_MainLine");
	CloseQuestHeader("TakeVineToPrisoner");
	CloseQuestHeader("LSC_findDekster");
	CloseQuestHeader("ISS_ElisHusband");
	CloseQuestHeader("ISS_takeStoreMoney");
	CloseQuestHeader("ISS_takeCandles");
	bQuestDisableMapEnter = false;
	bDisableFastReload = false; 
	TakeItemFromCharacter(pchar, "keyPanama");
	//проверим наличие займа у банкира ГПК
	sld = characterFromId("LSC_Usurer");
	if (CheckAttribute(sld, "quest.loan.qtyMoney") && sti(sld.quest.loan.qtyMoney) > 0)
	{	
		SetTimerFunction("LSC_climeUsurer", 0, 3 + rand(3), 0);
		pchar.questTemp.LSC_climeUsurer.qtyMoney = sti(sld.quest.loan.qtyMoney) * 5; //сколько денег к возврату
	}
	//убираем жителей ГПК из игры
	for(i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			sld.lifeDay = 0;	
	}
}

void LSC_takeStormIsland(string qName)
{	
	i = FindIsland("LostShipsCity");
	Islands[i].reload_enable = false;
	Islands[i].visible = false;
	DeleteAttribute(&Islands[i], "alwaysStorm");
	DeleteAttribute(&Islands[i], "storm");
	DeleteAttribute(&Islands[i], "tornado");
	DeleteAttribute(&Islands[i], "QuestlockWeather");
	DeleteAttribute(&Islands[i], "MaxSeaHeight");
}

//------------ посетить жилые помещения магазина ----------->>>>>>
void LCS_SetPedroHurtado(string qName)
{
	sld = characterFromId("PedroHurtado");
	sld.cityTape = "quest"; //тип нпс
	DeleteAttribute(sld, "location.going");
	LAi_SetLoginTime(sld, 10.0, 19.00);
	LAi_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto04_6");
}

void LSC_PedroRunOpenDoor()
{
	sld = characterFromId("PedroHurtado");
	sld.BreakTmplAndFight = true;
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "reload", "reload48", "LSC_PedroOpenedDoor", -1.0);
}

void LSC_Click(string qName)
{	
	PlaySound("interface\key.wav");
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);
	chrDisableReloadToLocation = true;
}

void LSC_PedroGoWaiting()
{
	sld = characterFromId("PedroHurtado");
	LAi_RemoveLoginTime(sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto04_6");
	chrDisableReloadToLocation = false;
	pchar.quest.LSC_EnterStoreBig.win_condition.l1 = "locator";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.location = "EsmeraldaStoreBig";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator = "reload2";
	pchar.quest.LSC_EnterStoreBig.function = "LSC_EnterStoreBig";
}

void LSC_EnterStoreBig(string qName)
{	
	//охрана
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");
	iTemp = 8+MOD_SKILL_ENEMY_RATE*2;
    for (i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("LSCStBandit"+i, "officer_"+(i+10), "man", "man", iTemp, PIRATE, 0, true));
        FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        LAi_SetWarriorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
		ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest"+i);
    }
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_HeroOutFromStory.function = "LCS_HeroOutFromStory";
}

void LCS_HeroOutFromStory(string qName)
{
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true);
	sld = characterFromId("PedroHurtado");	
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	AddSimpleRumourCityTip(REACT_FUNCT[202], "LostShipsCity", 10, 1, "LSC", "");
}
//<<<<<<-------- посетить жилые помещения магазина ----------------

//------------ должок ростовщика ГПК ----------->>>>>>
void LSC_climeUsurer(string qName)
{
	pchar.quest.LSC_climeUsurer_2.win_condition.l1 = "Location_Type";
	pchar.quest.LSC_climeUsurer_2.win_condition.l1.location_type = "shop";
	pchar.quest.LSC_climeUsurer_2.function = "LSC_climeUsurer_2";	
}

void LSC_climeUsurer_2(string qName)
{
	chrDisableReloadToLocation = true;
	sld = characterFromId(loadedLocation.fastreload + "_trader");
	LAi_CharacterDisableDialog(sld);
	//запишем данные для возврата в локацию
	pchar.questTemp.LSC_climeUsurer.idx = sld.id;
	pchar.questTemp.LSC_climeUsurer.location = pchar.location;
	pchar.questTemp.LSC_climeUsurer.group = pchar.location.group;
	pchar.questTemp.LSC_climeUsurer.locator = pchar.location.locator;
	DoQuestFunctionDelay("LSC_climeUsurer_3", 3.5);
}

void LSC_climeUsurer_3(string qName)
{
 	//перемещаем ГГ
	DoQuestReloadToLocation("Temple_Skulls", "goto", "goto1", "");	
	DoQuestFunctionDelay("LSC_climeUsurer_4", 10.0);
	//вернем хозяину магазина возможность диалога
	sld = characterFromId(pchar.questTemp.LSC_climeUsurer.idx);
	LAi_CharacterEnableDialog(sld);
}

void LSC_climeUsurer_4(string qName)
{
	//ставим бога мертвых	
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "pistol5", 3000);
	sld.name = REACT_FUNCT[203];
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "ClimeUsurer";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Temple_Skulls", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);	
}

void ClimeUsurer_haveMoney()
{
	DoQuestFunctionDelay("ClimeUsurer_haveMoney_1", 1.0);	
}

void ClimeUsurer_haveMoney_1(string qName)
{
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&locations[FindLocation("Temple_Skulls")], false);
	DoQuestReloadToLocation(pchar.questTemp.LSC_climeUsurer.location, pchar.questTemp.LSC_climeUsurer.group, pchar.questTemp.LSC_climeUsurer.locator, "");	
	DeleteAttribute(pchar, "questTemp.LSC_climeUsurer");
}

void ClimeUsurer_noMoney()
{
	LAi_LocationFightDisable(loadedLocation, false);
	sld = characterFromId("DeadmansGod");
	ChangeCharacterAddress(sld, "none", "");
	//если Аззи в дружбанах, то выручает ГГ
	if (pchar.questTemp.Azzy == "over")
	{
		DoQuestFunctionDelay("LSC_climeUsurer_Azzy", 30.0);
	}
}

void LSC_climeUsurer_Azzy(string qName)
{
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, 0, false));
	sld.name = REACT_FUNCT[204];
	sld.lastname = REACT_FUNCT[205];
	sld.Dialog.Filename = "Quest\Azzy_dialog.c";
	sld.dialog.currentnode = "ClimeUsurer";
	GiveItem2Character(sld, "blade28");// сабля Моргана
	sld.equip.blade = "blade28";
	sld.rank 	= 100;
	sld.reputation = "0";
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetHP(sld, 10000.0, 10000.0);
	sld.greeting = "Gr_Azzy";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}
//<<<<<<-------- должок ростовщика ГПК ----------------

//------------ освободить мужа Элис Тейлор ----------->>>>>>
void LSC_ElisHusbandSet(string qName)
{
	sld = characterFromId("MaximTailor");
	sld.dialog.currentnode = "First time";
	sld.watchBoxes = true;
	GiveItem2Character(sld, "blade15");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "blade15");
 	EquipCharacterbyItem(sld, "pistol2");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "goto", "goto1");
}
//<<<<<<-------- освободить мужа Элис Тейлор ----------------

//------------ квест скелета Лейтона Декстера ----------->>>>>>
void LSC_admiralFoundOwnKey(string qName)
{
	sld = ItemsFromID("keyPanama");
	sld.shown = false;
	AddQuestRecord("LSC_findDekster", "11");
	CloseQuestHeader("LSC_findDekster");
	pchar.questTemp.LSC.lostDecster = "over";
}
//<<<<<<-------- квест скелета Лейтона Декстера ----------------

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка ГПК           конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка Теночтитлана          начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//перец, что сваливает из Тено
void Teno_startInShore(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("QuestMan_Shore", "shipowner_1", "man", "man", 100, PIRATE, 0, false));
	sld.name = REACT_FUNCT[206];
	sld.lastname = REACT_FUNCT[207];
	sld.dialog.filename   = "Quest\Tenochtitlan\ForAll_Teno.c";
	sld.dialog.currentnode   = "Shore53";
	ChangeCharacterAddressGroup(sld, "Shore53", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

void Teno_startInShore_2()
{
	pchar.questTemp.Teno = "toMontesuma"; //флаг квеста
	sld = characterFromId("QuestMan_Shore");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "CanFightCurLocation", 10.0);
	//Ставим вождя
	sld = GetCharacter(NPC_GenerateCharacter("Montesuma", "Aztec", "man", "man", 50, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 70, 100, 100, "toporAZ", "", 300);
	sld.name = REACT_FUNCT[208];
	sld.lastname = "";
	sld.location = "Tenochtitlan";
	sld.location.group = "quest";
	sld.location.locator = "quest2";
	sld.dialog.filename   = "Quest\Tenochtitlan\Montesuma.c";
	sld.dialog.currentnode   = "First time";
	sld.greeting = "Gr_Montesuma";
	sld.reactionOnFightModeOn = true; 
	sld.BreakTmplAndFight = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	//GiveItem2Character(sld, "Totem_15");
	LAi_group_MoveCharacter(sld, "MontesumaGroup");
	//ставим прерывание на вход в Теночтитлан
	pchar.quest.Teno_createAztecTwin.win_condition.l1 = "location";
	pchar.quest.Teno_createAztecTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_createAztecTwin.function = "Teno_createAztecTwin";

	pchar.quest.Teno_talkWithTwin.win_condition.l1 = "locator";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator_group = "teleport";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator = "fire20";
	pchar.quest.Teno_talkWithTwin.function = "Teno_talkWithTwin";
	//открываем квест в СЖ
	SetQuestHeader("Tenochtitlan");
	AddQuestRecord("Tenochtitlan", "1");
}

//ставим ацтеков граждан
void Teno_createAztecTwin(string qName)
{
	//генерим близнецов
	sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_1", "AztecCitizen1", "man", "man", 15, PIRATE, -1, false));
	sld.name = REACT_FUNCT[209];
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT";
	sld.greeting = "cit_common";
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");  
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto23");
	
	sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_2", "AztecCitizen2", "man", "man", 15, PIRATE, -1, false));
	sld.name = REACT_FUNCT[210];
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT2";
	sld.greeting = "cit_common";
	LAi_SetLoginTime(sld, 7.0, 20.0);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto14");
	//Монтесуму на ГГ
	sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

void Teno_talkWithTwin(string qName)
{
	sld = characterFromId("AztecCitizen_1");
	LAi_ActorDialog(sld, pchar, "", 2.5, 0);
}

void Teno_MontesumaGoQuest1()
{
	AddQuestRecord("Tenochtitlan", "2");
	sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest1", "Teno_MontesumaArrived", -1);
}

void Teno_fightInTemple()
{
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	sld = characterFromId("DeadmansGod");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_SetCheckMinHP(sld, 5.0, true, "Teno_youWinFight");
}

void Teno_exitFromTeno(string qName)
{
	sld = characterFromId("Montesuma");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
}

void Teno_clearGroups(string qName)
{
	LAi_group_Delete("AztecCitizenGroup");
	LAi_group_Delete("MontesumaGroup");
	ChangeItemDescribe("SkullAztec", "itmdescr_SkullAztecAdd");
	AddQuestRecord("Tenochtitlan", "6");
	CloseQuestHeader("Tenochtitlan");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка Теночтитлана         конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Зачарованный город        начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void MC_startInCaracas(string qName)
{
	if (GetHour() > 9.0 && GetHour() < 20.0 && !LAi_IsCapturedLocation)
	{
		pchar.questTemp.MC = "toCaracas"; //флаг квеста	
		bDisableFastReload = true;
		iTemp = FindLocation("Caracas_town");
		DeleteAttribute(&locations[iTemp], "citizens"); //уберем горожан
		DeleteAttribute(&locations[iTemp], "carrier");	//уберем грузчиков 
		DeleteAttribute(&locations[iTemp], "questSeekCap");	//уберем квестодателя
		//закроем выходы из города
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l2.disable = true;
		locations[iTemp].reload.l3.disable = true;
		locations[iTemp].reload.l4.disable = true;
		locations[iTemp].reload.l41.disable = true;
		locations[iTemp].reload.l5.disable = true;
		locations[iTemp].reload.l6.disable = true;
		locations[iTemp].reload.l7.disable = true;
		locations[iTemp].reload.l8.disable = true;
		locations[iTemp].reload.l10.disable = true;
		locations[iTemp].reload.gate.disable = true;
		//очистим таверну
		iTemp = FindLocation("Caracas_tavern");
		DeleteAttribute(&locations[iTemp], "habitues"); //уберем в таверне наполнение нпс
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l4.disable = true;
		sld = characterFromId("Caracas_waitress"); //официантку тоже
		ChangeCharacterAddress(sld, "none", "");	
		//ставим горожан
		for (i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CaracasCit_"+i, "citiz_"+i, "man", "man", 10, SPAIN, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasMan"; 
			sld.greeting = "cit_common";
			sld.BreakTmplAndFightGroup = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Caracas_town", "quest", "MCquest"+i);
		}
	}
	else
	{
		pchar.quest.MC_startAgain.win_condition.l1 = "MapEnter";
		pchar.quest.MC_startAgain.function = "MC_startAgain";
	}
}

void MC_startAgain(string qName)
{
	pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
	pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
	pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
}

void MC_endCaracas()
{
	bDisableFastReload = false;
	pchar.questTemp.MC = "toMaracaibo"; //флаг квеста	
	//вернем город
	iTemp = FindLocation("Caracas_town");
	locations[iTemp].citizens = true; 
	locations[iTemp].carrier = true; 
	locations[iTemp].questSeekCap = 8; 
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");	
	DeleteAttribute(&locations[iTemp], "reload.l2.disable");
	DeleteAttribute(&locations[iTemp], "reload.l3.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	DeleteAttribute(&locations[iTemp], "reload.l41.disable");
	DeleteAttribute(&locations[iTemp], "reload.l5.disable");
	DeleteAttribute(&locations[iTemp], "reload.l6.disable");
	DeleteAttribute(&locations[iTemp], "reload.l7.disable");
	DeleteAttribute(&locations[iTemp], "reload.l8.disable");
	DeleteAttribute(&locations[iTemp], "reload.l10.disable");
	DeleteAttribute(&locations[iTemp], "reload.gate.disable");
	DeleteAttribute(&locations[iTemp], "hidden_effects");
	//вернем таверну
	iTemp = FindLocation("Caracas_tavern");
	locations[iTemp].habitues = true;
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	sld = characterFromId("Caracas_waitress"); //официантку тоже
	sld.location = "Caracas_tavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	SetQuestHeader("MagicCity");
	AddQuestRecord("MagicCity", "1");
	pchar.quest.MC_DesMoinesInShore.win_condition.l1 = "location";
	pchar.quest.MC_DesMoinesInShore.win_condition.l1.location = "Shore_ship3";
	pchar.quest.MC_DesMoinesInShore.function = "MC_DesMoinesInShore";
}

void MC_DesMoinesInShore(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_group_Delete("EnemyFight");
    for (i=1; i<=MOD_SKILL_ENEMY_RATE; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("ShoreGuard"+i, "officer_"+(i+10), "man", "man", 20, PIRATE, 0, true));
        FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);
		sld.dialog.filename = "Quest\MagicCity.c";
		sld.dialog.currentnode = "ShoreGuard";
		sld.BreakTmplAndFightGroup = true; 
		sld.reactionOnFightModeOn = true; 
        LAi_SetActorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
		PlaceCharacter(sld, "goto", "random_free");
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Зачарованный город     eddy     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка капитана Блада --     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Blood_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.CapBloodLine.stat = "Begining";
    Pchar.BaseNation = ENGLAND;
    //fix перков флагов
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
    SetCharacterPerk(Pchar, "FlagEng");
    Flag_ENGLAND();
    //Подготовка Барбадоса
    int n = FindLocation("Bridgetown_town");
    DeleteAttribute(&locations[n], "questSeekCap");
    DeleteAttribute(&locations[n], "houseEnc");
    locations[n].notCloseCommonHouse = true;
    n = FindLocation("Bridgetown_tavern"); //homo fix
    DeleteAttribute(&locations[n], "habitues");
    //Обираем до нитки
    RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
    RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
    RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
    DeleteAttribute(Pchar, "items");
//    DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    //GiveItem2Character(Pchar, "unarmed");
    //EquipCharacterByItem(Pchar, "unarmed");
    TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
    SetCharacterPerk(Pchar, "Doctor1");
	
	//Эндрю Бэйнс
    sld = GetCharacter(NPC_GenerateCharacter("Beyns", "trader_8", "man", "man", 7, ENGLAND, 1, false));
    sld.name = REACT_FUNCT[211];
    sld.lastname = REACT_FUNCT[212];
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "cit_common";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto12");
	
    //==============//Джереми Питт//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Pitt", "Pitt", "man", "man", 1, ENGLAND, -1, false)); //TO_DO анимацию вернуть по готовности модельки
    sld.name 	= REACT_FUNCT[213];
    sld.lastname 	= REACT_FUNCT[214];
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_YoungMan";
//                  P I R  A T E  S
    SetSPECIAL(sld, 5,9,7,5,10,7,4);
    sld.rank = 12;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
    InitStartParam(sld);
    //SetRandSPECIAL(sld);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 40, 25);
    //int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn
    SetShipSkill(sld, 45, 30, 25, 25, 50, 25, 25, 25, 30);
	//SetCharacterPerk(sld, "FastReload");
	//SetCharacterPerk(sld, "HullDamageUp");
	//SetCharacterPerk(sld, "SailsDamageUp");
	//SetCharacterPerk(sld, "CrewDamageUp");
	//SetCharacterPerk(sld, "CriticalShoot");
	//SetCharacterPerk(sld, "LongRangeShoot");
    //SetCharacterPerk(sld, "CannonProfessional");
	//SetCharacterPerk(sld, "ShipDefenseProfessional");
	
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "SandbankManeuver");

	
	//SetCharacterPerk(sld, "SwordplayProfessional");
	//SetCharacterPerk(sld, "AdvancedDefense");
	//SetCharacterPerk(sld, "CriticalHit");
	//SetCharacterPerk(sld, "Sliding");
    SetFantomHP(sld);
    SetEnergyToCharacter(sld);
   	LAi_SetImmortal(sld, true);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto1");
	
	pchar.quest.CureLordMovie.win_condition.l1 = "locator";
	pchar.quest.CureLordMovie.win_condition.l1.location = "EstateBadroom1";
	pchar.quest.CureLordMovie.win_condition.l1.locator_group = "quest";
	pchar.quest.CureLordMovie.win_condition.l1.locator = "quest1";
	pchar.quest.CureLordMovie.function = "CureLord";

}

void CureLord(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "EstateBadroom1", "reload", "reload1");
    sld.dialog.currentnode = "EBStep_1";
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);

}

void CureLordMovie()
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	ChangeShowIntarface();
    LAi_SetActorTypeNoGroup(Pchar);
    LAi_ActorGoToLocator(Pchar, "goto", "goto6", "CureLordMovie_Con1", 10.0);
}

void CureLordMovie_Con1()
{
    LAi_ActorTurnToLocator(Pchar, "goto", "goto7");
    LAi_ActorAnimation(Pchar, "Barman_idle", "CureLordMovie_Con2", 5);
}

void CureLordMovie_Con2()
{
    LAi_Fade("CureLordMovie_Con3", "");
}

void CureLordMovie_Con3()
{

    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    sld.dialog.currentnode = "EBStep_2";
//   	sld.talker = 10;
//    LAi_SetActorTypeNoGroup(sld);
//	LAi_ActorDialog(sld, pchar, "",  2, 0);
    ChangeCharacterAddressGroup(sld, "EstateOffice", "goto", "goto6");
    LAi_SetStayTypeNoGroup(sld);
    DoReloadCharacterToLocation("EstateOffice", "goto", "goto3");
    EndQuestMovie();
   	ChangeShowIntarface();
    LAi_SetPlayerType(Pchar);
    InterfaceStates.Buttons.Save.enable = true;

}

void BloodGetBlade(string qName)
{
    LAi_SetCheckMinHP(Pchar, 1, true, "CapBlood_CheckMinHP");
   	LAi_SetImmortal(pchar, false);
}

void DragunInvansion()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Pitt")];
    sld.dialog.currentnode = "PStep_5";
    ChangeCharacterAddressGroup(sld, "EstateOffice", "reload", "reload1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "",  -1, 0);
}

void DragunInvansion2()
{
    pchar.quest.BloodGetBlade.win_condition.l1 = "item";
    pchar.quest.BloodGetBlade.win_condition.l1.item= "blade2";
    pchar.quest.BloodGetBlade.function = "BloodGetBlade";
    pchar.quest.DragunInvansion.win_condition.l1          = "location";
    pchar.quest.DragunInvansion.win_condition.l1.location = "Estate";
    pchar.quest.DragunInvansion.function                  = "_DragunInvansion3";

}

void _DragunInvansion3(string qName)
{
    chrDisableReloadToLocation = true; // закрыть выход из локации
    DoQuestFunctionDelay("DragunInvansion3", 60.0);
}

void DragunInvansion3(string qName)
{
    ref ch, sld;
    LAi_LocationFightDisable(loadedLocation, true);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
    LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix

	ch = GetCharacter(NPC_GenerateCharacter("CapGobart", "Hobart", "man", "man", 10, ENGLAND, 0, false));
    ch.name 	= REACT_FUNCT[215];
    ch.lastname 	= REACT_FUNCT[216];
    ch.Dialog.CurrentNode = "First time";
    ch.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    ch.greeting = "soldier_arest";
    ch.location = "none";
    FantomMakeCoolFighter(ch, 25, 70, 70, "blade22", "pistol2", 20);
    LAi_SetImmortal(ch, true);
    ch.BreakTmplAndFightGroup = true; //fix
    LAi_group_MoveCharacter(ch, "TmpEnemy");
    //LAi_group_MoveCharacter(ch, "EnemyFight");
    ChangeCharacterAddressGroup(ch, "Estate", "goto", "goto1");
    LAi_SetActorTypeNoGroup(ch);
	LAi_ActorDialog(ch, pchar, "", 7, 0);

    for (int i=0 ; i<=4; i++)
    {
    	// генерим c сопровождение
		sTemp = "SoldierEnglish_1";
		if (i == 1) sTemp = "Dragoon_1"; 
        sld = GetCharacter(NPC_GenerateCharacter(("Dragun_"+i), sTemp, "man", "man", 2, ENGLAND, 0, false));
        sld.location = "none";
        sld.BreakTmplAndFightGroup = true;
        SetSPECIAL(sld, 8,10,9,3,6,10,4);
        InitStartParam(sld);
        SetEnergyToCharacter(sld);
        LAi_SetImmortal(sld, true); // потом снимаем
        //LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
        GiveItem2Character(sld, "blade4");
    	EquipCharacterByItem(sld, "blade4");
	    sld.Dialog.CurrentNode = "Draguns_0";
        sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
        LAi_group_MoveCharacter(sld, "TmpEnemy");
        //LAi_group_MoveCharacter(sld, "EnemyFight");
    	ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload1");
        LAi_SetActorTypeNoGroup(sld);
    	if(i < 3)
    	{
        	if( i > 1 )
        	{
            	GiveItem2Character(sld, "pistol2");
            	EquipCharacterByItem(sld, "pistol2");
            	TakeNItems(sld, "bullet", 30);
            }
            LAi_ActorFollow(sld, ch, "", -1);
        }
        if(i == 3)LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 20);
        if(i == 4)LAi_ActorRunToLocation(sld, "reload", "reload5", "none", "", "", "", 20);
     }

}

void DragunInvansion4()
{
 	StartQuestMovie(true, true, true);
	locCameraToPos(18.241, 13, 0.35, false); 
	ref ch, sld;
    LAi_LockFightMode(pchar, false);
    LAi_LocationFightDisable(loadedLocation, false);
    ch = &characters[GetCharacterIndex("Pitt")];
    ChangeCharacterAddressGroup(ch, "Estate", "reload", "reload5");
    LAi_SetActorType(ch);
    LAi_ActorGoToLocator(ch, "goto", "goto5", "", -1);
    
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
    LAi_SetActorType(sld);
    LAi_ActorFollow(sld, ch, "", -1);

    for (i=1; i<5; i++)
    {
        sld = &characters[GetCharacterIndex("Dragun_"+i)];
        //LAi_group_MoveCharacter(sld, "TmpEnemy");
        if(i == 3 || i == 4)
        {
            ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorFollow(sld, ch, "", -1);
        }
        else
        {
            //LAi_SetStayTypeNoGroup(sld);
            //LAi_SetWarriorType(sld);
            //LAi_SetGuardianType(sld);
        }
    }

}

void CapGobartAttack(string qName)
{
    ref sld;
    int numdead = 0;
    for (i=1; i<=2; i++)
    {
        sld = characterFromID("Dragun_"+i);
        if (CharacterIsDead(sld))
        {
            numdead++;
        }
    }
    if(numdead == 2)
    {
        sld = characterFromID("CapGobart");
        //LAi_group_MoveCharacter(sld, "TmpEnemy");
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
}
/////////////////////////////////////////////////////////////////////////
void Blood_StartGame_End(string qName)
{
    ref sld;
    chrDisableReloadToLocation = true;
    InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;
    sld = characterFromID("Dragun_0");
    LAi_RemoveCheckMinHP(sld);
    pchar.quest.CapGobartAttack_1.over = "yes";
    pchar.quest.CapGobartAttack_2.over = "yes";

	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;

    Pchar.model="blood_bomj";
	DoQuestFunctionDelay("CapBloodLineInit", 0.1);
}


void CapBloodLineInit(string qName)
{
    //Возвращаем все после плена
    LAi_SetCurHPMax(Pchar);
    LAi_SetPlayerType(Pchar);
    //Рабство
    LAi_SetImmortal(Pchar, false);
    DeleteAttribute(Pchar, "items");
    DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    /*GiveItem2Character(Pchar, "unarmed");
    EquipCharacterByItem(Pchar, "unarmed");*/
    Pchar.money = 0;
    // Cтид
    sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = REACT_FUNCT[217];
    sld.lastname = REACT_FUNCT[218];
    // Первый квест
	Environment.date.month = 4;
    SetCurrentTime(23, 1);
    pchar.quest.onPlantation.win_condition.l1          = "location";
    pchar.quest.onPlantation.win_condition.l1.location = "BridgeTown_Plantation";
    pchar.quest.onPlantation.function                  = "CapBloodLine_q1";
    //DoReloadCharacterToLocation("BridgeTown_Plantation", "patrol", "patrol12");

    //квест ночной, поэтому так вот               //to_do
    int n= FindLocation("Bridgetown_town");  // не забыть вернуть
    locations[n].reload.l3.close_for_night = false;
    //для энкаунтеров в джанглах
    bDisableLandEncounters = true;

	PostVideoAndQuest("slave", 100, "move_slave_2");
}

void CapBloodLine_firstEnterHome(string qName)
{	
	sld = characterFromID("Pitt");
	sld.Dialog.CurrentNode = "PStep_7";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "Plantation_S1", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
	Pchar.questTemp.CapBloodLine.statcrew = "";	
}


void CapBloodLine_q1(string qName)
{

    ref sld;
    LAi_LocationFightDisable(loadedLocation, true);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    chrDisableReloadToLocation = true; // закрыть выход из локации
    bDisableFastReload = true; // закрыть переходы.
    Pchar.questTemp.CapBUnarmed = true; //ГГ сабля не положена

    //Бишоп на плантациях                              //off_eng_1
   	sld = GetCharacter(NPC_GenerateCharacter("Bishop", "trader_2", "man", "man", 1, ENGLAND, 3, false));
    sld.name 	= REACT_FUNCT[219];
    sld.lastname 	= REACT_FUNCT[220];
    sld.Dialog.CurrentNode = "First Bishop";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Bishop";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	LAi_SetImmortal(sld, true);

    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "reload", "houseSp1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

    //Джереми Питт
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS1_3");
    //Оружейник
	sld = GetCharacter(NPC_GenerateCharacter("Griffin", "shipowner_11", "man", "man", 10, ENGLAND, 3, false));
	sld.name = REACT_FUNCT[221];
	sld.lastname = REACT_FUNCT[222];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Master";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto","goto1");
	LAi_SetImmortal(sld, true);
    //Рыбак
	sld = GetCharacter(NPC_GenerateCharacter("Hells", "shipowner_9", "man", "man", 10, PIRATE, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.name = REACT_FUNCT[223];
	sld.lastname = REACT_FUNCT[224];
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
	sld.greeting = "Gr_Fisher";
	AddMoneyToCharacter(sld, 2000);
	FantomMakeCoolFighter(sld, 7, 25, 50, "topor1", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    LAi_SetOwnerTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto","goto4");
	//Контра
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Smuggler", "Pirate_4", "man", "man", 10, ENGLAND, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Smuggler Agent";
	LAi_SetSitTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit2");

    //алкаши в таверне
    int i=rand(2)
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Habitue", "citiz_"+(rand(11)+1), "man", "man", 10, ENGLAND, 3, false));
	sld.greeting = "Gr_Tavern_Mate";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front" + (i+1);
    LAi_SetCitizenType(sld);
    LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base"+(1+i));

    //==============//Натаниэль   Хагторп//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Hugtorp", "officer_16", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= REACT_FUNCT[225];
    sld.lastname 	= REACT_FUNCT[226];
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 20, 40, 35, 30, 30);
    //int _ld, int _cr,  ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 45, 30, 25, 25, 20, 25, 35, 30, 20);
   	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "Brander");
	SetCharacterPerk(sld, "Troopers");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
   	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS2_1");
   	
    //==============//Николас Дайк//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Dieke", "officer_19", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= REACT_FUNCT[227];
    sld.lastname 	= REACT_FUNCT[228];
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 30, 30);
    //                ld, cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 30, 35, 20, 20, 20, 45, 25, 35, 20);
   	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "LightRepair");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "EnergyPlus");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseF1_1");
	
	
    //==============//Нед Огл//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Ogl", "Chard3a", "man", "man", 10, ENGLAND, -1, false)); 
    sld.name 	= REACT_FUNCT[229];
    sld.lastname 	= REACT_FUNCT[230];
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Ogl";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    LAi_SetStayTypeNoGroup(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
	SetSPECIAL(sld, 8, 9, 5, 5, 9, 5, 7);
    //int           _fl,  f,  fh, p,  fr
    SetSelfSkill(sld, 20, 30, 20, 35, 30);
    //int            ld,  cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 20, 10, 50, 40, 15, 20, 20, 20, 20);
   	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "SharedExperience");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Plantation_S2", "barmen", "stay");
	
    //==============//Кинжал для Блада//==============
    sld = GetCharacter(NPC_GenerateCharacter("Slave_Quest", "shipowner_6", "man", "man", 7, ENGLAND, 2, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Dialog.CurrentNode = "SLQStep_0";
    sld.greeting = "Gr_slave";
    sld.talker = 10;
    sld.CityType = "citizen";
	sld.city = "BridgeTown";
	LAi_SetLoginTime(sld, 6.0, 22.99);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto12");
	LAi_SetCitizenType(sld);
    LAi_group_MoveCharacter(sld, sTemp);

    //раскидаем квестовых нпс по локациям
	SetQuestsCharacters();

    // первый заход в город
    pchar.quest.CapBloodLine_q1_1.win_condition.l1          = "location";
    pchar.quest.CapBloodLine_q1_1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodLine_q1_1.function                  = "_PrepareBridgeTown";

}

void ChangePIRATES()
{
	pchar.SystemInfo.ChangePIRATES = true;
	LaunchCharacter(pchar);
}

void _PrepareBridgeTown(string qName)
{
    DoQuestFunctionDelay("PrepareBridgeTown", 1.0);
}
void PrepareBridgeTown(string qName)
{
    trace("PrepareBridgeTown");
    //меняем город под рабство
    ChangeBridgeTownDialogs(false);
    //солдат на страже у резиденции
    ref sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.Dialog.CurrentNode = "First Guard";
    sld.protector = true;
    sld.protector.CheckAlways = 1 ;
    LAi_RemoveLoginTime(sld);
    LoginCharacter(sld, "BridgeTown_town");
    //Нэтталл
    LoginNettl("");
    //закроем резиденцию до поры
    LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true); //fix
    LocatorReloadEnterDisable("BridgeTown_fort", "reload2", true); //fix
    //уберем пьянь из таверны
    //int n = FindLocation("Bridgetown_tavern");
    //locations[n].habitues = 0;
    //контрик нужен
    sld = &characters[GetCharacterIndex("Bridgetown_Smuggler")]
    LoginCharacter(sld, "Bridgetown_tavern");

}

void DetectBlades()
{
    if (Pchar.questTemp.CapBloodLine == true && Pchar.questTemp.CapBUnarmed == true)
    {
        string sweapon = FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE);
        //Log_Info(REACT_FUNCT[231]+sweapon);
        bool bblades = ( sweapon != "unarmed") && (sweapon != "blade5" ) && (sweapon!= "");
        bool bguns = (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "");
        if(bblades || bguns)
        {
            pchar.quest.CapBloodDetectBlades1.win_condition.l1          = "location";
            pchar.quest.CapBloodDetectBlades1.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.CapBloodDetectBlades1.function                  = "TakeBlades";
            
            pchar.quest.CapBloodDetectBlades2.win_condition.l1          = "location";
            pchar.quest.CapBloodDetectBlades2.win_condition.l1.location = "BridgeTown_Plantation";
            pchar.quest.CapBloodDetectBlades2.function                  = "TakeBlades";
        }
        if(sweapon == "")
        {
            /*sweapon = "unarmed";
            GiveItem2Character(Pchar, "unarmed");
            EquipCharacterByItem(Pchar, sweapon);*/
        }
        else
        {
            EquipCharacterByItem(Pchar,GetCharacterEquipByGroup(Pchar, BLADE_ITEM_TYPE));
        }
    }
}

void TakeBlades(string qName)
{
    sld = GetCharacter(NPC_GenerateCharacter("SolderTakeBlades", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "soldier_arest";
    sld.location = "none";
    sld.BreakTmplAndFight = true;
    //SetFantomParamHunter(sld); //крутые парни
    SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
    pchar.quest.SolderTakeBladesDie.win_condition.l1 = "NPC_death";
    pchar.quest.SolderTakeBladesDie.win_condition.l1.character = "SolderTakeBlades";
   	pchar.quest.SolderTakeBladesDie.function = "SolderTakeBladesDie";
	//Log_Info(REACT_FUNCT[232]);

}

void SolderTakeBladesDie(string qName)
{
    chrDisableReloadToLocation = false;
}


//Меняет всем дилоги
void ChangeBridgeTownDialogs(bool restore)
{
    ref sld;
    int num, cur;
    num = 0;
    cur = rand(3)+1;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        //солдаты
        if (CheckAttribute(sld, "city") && sld.city == "Bridgetown")
        {
            if(CheckAttribute(sld, "CityType") && sld.CityType == "soldier")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_Soldier.c";
                }
                sld.lifeDay = 3;
            }
            //горожане
            if(CheckAttribute(sld, "CityType") && sld.CityType == "citizen")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    if(sld.location.group == "merchant")
                    {   //торговцы
                        num++;
                        if(num == cur) // для квеста по добычи оружия метим одного продовца
                        {
                            sld.quest.bGoodMerch = true;
                        }

                    }
                }
                else
                {
                    if(sld.location.group == "merchant")
                    {   //торговцы
                        sld.dialog.filename = "Common_ItemTrader.c";
                    }
                    else
                    {   //обычные
                        sld.dialog.filename = "Common_citizen.c";
                    }
                }
                sld.lifeDay = 3;
            }
            //нищие
            if(sld.id == "Bridgetown_Poorman")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_poorman.c";
                }
            }

            //квестовые
            if(sld.id == "QuestCitiz_Bridgetown")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    sld.Dialog.CurrentNode = "First time";
                }
                else
                {
                    sld.dialog.filename = "Quest\ForAll_dialog.c";
                }
            }
        }

	}
}

void LoginNettl(string qName)
{

        Pchar.questTemp.CapBloodLine.TalkWithNettl = false;          //10//3
		sld = GetCharacter(NPC_GenerateCharacter("Nettl", "shipowner_2", "man", "man", 7, ENGLAND, 3, false));
        sld.name = REACT_FUNCT[233];
        sld.lastname = REACT_FUNCT[234];
		sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
		sld.dialog.currentnode = "First time";
		sld.city = "Bridgetown_town";
		sld.greeting = "Gr_Tavern_Mate";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
		//SetFantomParamFromRank(sld, Rank, true);
		LAi_SetCitizenType(sld);
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
		LAi_group_MoveCharacter(sld, sTemp);
		sld.talker = 10;
		PlaceCharacter(sld, "goto", "random");
}

void CapBloodLine_q1_Late(string qName)
{
    InterfaceStates.Buttons.Save.enable = false;
  //  SetLaunchFrameFormParam(REACT_FUNCT[235]+ NewStr() +
  //  REACT_FUNCT[236]+ NewStr() +
  //  REACT_FUNCT[237]+ NewStr() +
  //  REACT_FUNCT[238]+ NewStr() +
  //  REACT_FUNCT[239]+ NewStr() +
  //  REACT_FUNCT[240], "", 0.1, 7.0);
//	LaunchFrameForm();
 //   PostEvent("LAi_event_GameOver", 15000, "s", "land");
    //PostEvent(GAME_OVER_EVENT, 15000);
    GameOver("blood");
}

void CapBloodLine_q1_End(string qName)
{
   AddQuestRecord("CapBloodLine_q1", "6");
   Pchar.questTemp.CapBloodLine.stat = "CureMisStid_Complite";
}

void CapBloodLine_q1_Complited(string qName)
{
    ref sld
    trace("CapBloodLine_q1_Complited!!!");
    pchar.quest.CapBloodLineTimer_1.over = "yes";
    sld = &characters[GetCharacterIndex("MisStid")];
//    sld.lifeDay = 0;
    sld.location = "none";
    sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.Dialog.CurrentNode = "First time";
    
    int n= FindLocation("Bridgetown_town");
    locations[n].reload.l3.close_for_night = true;//закрываем резиденцию
    AddQuestRecord("CapBloodLine_q1", "7");
    CloseQuestHeader("CapBloodLine_q1");
    //LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 12, 0); // прошло время
    SetCurrentTime(7, 0); // должно быть 2-е число 7 часов
    bQuestCheckProcessFreeze = false;
    SetLaunchFrameFormParam(REACT_FUNCT[241], "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Bridgetown_tavern", "reload","reload2", "");
	LaunchFrameForm();
	CapBloodLine_q2();
}

void CapBloodLine_q2()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.dialog.currentnode = "First time";
    Pchar.questTemp.CapBloodLine.stat = "WakerOffer";
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern_upstairs", "goto","goto1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "", 2.0, 0);
    AddQuestRecord("CapBloodLine_q2", "2");
    AddQuestRecord("CapBloodLine_q2", "3");
    
    //сроки 10 часов
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 17;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

}

void Spain_spyDie(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Spain_spy")];
    LAi_KillCharacter(sld);
}

void LoginSpain_spy(string qName)
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "shipowner_13", "man", "man", 7, SPAIN, 2, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = REACT_FUNCT[242];
    sld.lastname = REACT_FUNCT[243];
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
    //SetFantomParamHunter(sld); //крутые парни
    FantomMakeCoolFighter(sld, 7, 30, 50, "blade10", "", 20);
    TakeItemFromCharacter(sld, "spyglass3");
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void SpainSpyAttack(string qName)
{
    LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 0, 10); // прошло время
    bQuestCheckProcessFreeze = false;
    AddQuestRecord("WeaponsForEscape", "8");
    LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);
}

void _DeadSolder(string qName)
{
    PlaySound("People Fight\Death_NPC_04.WAV");
    DoQuestFunctionDelay("DeadSolder", 1.0);
}

void DeadSolder(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("CPBQuest_Solder")];
    TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
    GiveItem2Character(sld, "blade7");
    LAi_KillCharacter(sld);
}

void FindMsStid_ring(string qName)
{
    AddQuestRecord("WeaponsForEscape", "14");
}



void LoginWinterwood()
{
    ref sld, ch, itm;
	sld = GetCharacter(NPC_GenerateCharacter("Winterwood", "officer_20", "man", "man", 10, PIRATE, 3, false));
	sld.name = REACT_FUNCT[244];
	sld.lastname = REACT_FUNCT[245];
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.greeting = "pirat_common";
    FantomMakeCoolFighter(sld, 7, 25, 20, "blade10", "pistol3", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    GiveItem2Character(sld, "DOjeronRing"); //палец to_do
    itm = ItemsFromID("DOjeronRing");
	itm.picIndex = 15;
    itm.picTexture = "ITEMS_13";
    ChangeItemDescribe("DOjeronRing", "itmdescr_HugtorpRing");
    ChangeItemName("DOjeronRing", "itmname_HugtorpRing");
    AddMoneyToCharacter(sld, 1000);
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
    LAi_SetCitizenType(sld);
    
    string sQuest = "WinterwoodDuel";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "WinterwoodDie";

    if(!rand(1))
    {
   	    LAi_SetSitTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit4");
    }
    else
    {
   	    LAi_SetStayTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_Brothel_room", "goto","goto3");
        
		ch = GetCharacter(NPC_GenerateCharacter("Qhorse", "horse07", "woman", "towngirl", 10, ENGLAND, 1, false));
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(ch, sTemp);
        LAi_SetActorTypeNoGroup(ch);
		LAi_ActorAfraid(ch, Pchar, false);
		ChangeCharacterAddressGroup(ch, "Bridgetown_Brothel_room", "goto","goto1");
		
        int n= FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = false;
        
    }
}

void WinterwoodDuel(string qName)
{
	pchar.quest.Winterwood2Place.win_condition.l1 = "Location";
	pchar.quest.Winterwood2Place.win_condition.l1.location = "Bridgetown_ExitTown";
	pchar.quest.Winterwood2Place.function = "Winterwood2Place";
}

void Winterwood2Place(string qName)
{
    ref sld;
    sld = characterFromID("Winterwood");
   	sld.Dialog.CurrentNode = "talk_off_town";
    if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); // чтоб не было ругани с нацией
		DeleteAttribute(sld, "CityType");
	}
   	ChangeCharacterAddressGroup(sld, "Bridgetown_ExitTown", "goto","goto1");
   	LAi_SetStayTypeNoGroup(sld);
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void Winterwood_Prepare_Fight()
{
	int i, idx;
	ref npchar, rLoc;

	npchar = characterFromID("Winterwood");
	makeref(rLoc, Locations[FindLoadedLocation()]);

	if (CheckAttribute(rLoc, "type") && rLoc.type == "tavern")
	{
		if (PChar.chr_ai.type == LAI_TYPE_SIT)
		{
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
		}
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
		PChar.Quest.Duel_Fight_Right_Now.function = "Winterwood_Fight_Right_Now";

		LocationMakeClone(pchar.location);
		Locations[FindLocation("Clone_location")].image = "loading\tavern_fight.tga";
		DoReloadCharacterToLocation("Clone_location", pchar.location.group, pchar.location.locator);
		PlaceCharacter(npchar, "goto", "Clone_location")
	}
	else
	{
		DoQuestFunctionDelay("Winterwood_Fight_Right_Now", 0.5);
	}
	LAi_SetWarriorType(npchar);
	LAi_group_MoveCharacter(npchar, "DUEL_FIGHTER");
}

void Winterwood_Fight_Right_Now(string qName)
{
	bool bOk = false;
	ref sld = &Locations[FindLocation(pchar.location)];

	//запоминаем запрет на оружие в локации
	if (CheckAttribute(sld, "noFight"))
	{
		bOk = sti(sld.noFight);
	}
	if (bOk)
	{
		LAi_LocationFightDisable(sld, !bOk);
		pchar.questTemp.LocFightEnable = bOk;
	}
	//достать саблю
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DUEL_FIGHTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DUEL_FIGHTER", LAI_GROUP_PLAYER, true);
	chrDisableReloadToLocation = true;
}

void WinterwoodDie(string qName)
{
    if (CheckAttribute(PChar, "quest.Winterwood2Place")) Pchar.quest.Winterwood2Place.over = "yes";
    if (CheckAttribute(PChar, "quest.CapBloodLineTimer_3")) Pchar.quest.CapBloodLineTimer_3.over = "yes";

	//восстанавливаем запрет на оружие, если был
	if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
	{
		sld = &Locations[FindLocation(pchar.location)];
		LAi_LocationFightDisable(sld, true);
		DeleteAttribute(pchar, "questTemp.LocFightEnable");
	}

	//если в локации клоне, то объясняем куда все делись
	if (CheckAttribute(pchar, "questTemp.LocationClone") && sti(pchar.questTemp.LocationClone))
	{
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	}

	//убрать оружие
	DoQuestCheckDelay("hide_weapon", 2.0);
	chrDisableReloadToLocation = false;
    AddQuestRecord("HugtorpTrouble", "3");
}

void MoneyForDieke(string qName)
{
    sld = characterFromID("Dieke");
    sld.Dialog.CurrentNode = "DKStep_3";
    AddQuestRecord("DiekeQuest", "4")
}

void CapBloodLine_q2_Late(string qName)
{
    InterfaceStates.Buttons.Save.enable = false;
    GameOver("blood");
}

void CapBloodLine_q2_Complited()
{
    ref sld;
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    AddQuestRecord("CapBloodLine_q2", "6");
    int n= FindLocation("Bridgetown_tavern");
    locations[n].reload.l2.disable = false;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.Dialog.CurrentNode = "WStep_11";
    LAi_SetStayTypeNoGroup(sld);
    
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 12, 0); // прошло время
    Environment.date.day = 3;
    SetCurrentTime(7, 0); // должно быть 3-е число 7 часов
    bQuestCheckProcessFreeze = false;
    
    //Шпион
    sld = GetCharacter(NPC_GenerateCharacter("MoneySpy", "shipowner_5", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade9", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    sld.quest.meeting = 0;
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    sld.talker = 10; //fix
   	ChangeCharacterAddressGroup(sld, "CommonDoubleFlourHouse_1", "barmen", "stay");
    
    //Властелин рыб
    sld = GetCharacter(NPC_GenerateCharacter("Fisherman", "shipowner_8", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.name = REACT_FUNCT[246];
    sld.lastname = REACT_FUNCT[247];
	sld.greeting = "Gr_Fisher";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front4";//fix
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetSitType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base4"); //fix
    
    //Жак Соловей
    sld = GetCharacter(NPC_GenerateCharacter("Jack", "pirate_5", "man", "man", 10, ENGLAND, 1, false));
    sld.name = REACT_FUNCT[248];
    sld.lastname = REACT_FUNCT[249];
    sld.greeting = "Gr_Solovey";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade7", "", 10);
    sld.dialog.currentnode = "JSTStep_0";
    sld.talker = 10;
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetStayType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    //LAi_SetOwnerTypeNoGroup(sld);
   	ChangeCharacterAddressGroup(sld, "Bridgetown_Store", "goto", "goto1");
   	sld = characterFromID("Bridgetown_trader");
   	LAi_SetLoginTime(sld, 0.0, 1.0);
   	
    //сроки
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 15;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

    SetLaunchFrameFormParam(REACT_FUNCT[250], "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Plantation_S1", "goto", "goto1", "");
   	LaunchFrameForm();
}

void QUsurerLate(string qName)
{
    ChangeCharacterHunterScore(PChar, "enghunter", 30);
}

void LoginMainer()
{

        Pchar.questTemp.CapBloodLine.ShipForJack = false;
		sld = GetCharacter(NPC_GenerateCharacter("Mainer", "officer_1", "man", "man", 7, ENGLAND, 3, false));
        sld.name = REACT_FUNCT[251];
        sld.lastname = REACT_FUNCT[252];
		sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		sld.dialog.currentnode = "MNStep_0";
		sld.city = "Bridgetown_town";
		//sld.greeting = "Gr_Tavern_Mate";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
		//SetFantomParamFromRank(sld, Rank, true);
		LAi_SetCitizenType(sld);
		sTemp = GetNationNameByType(ENGLAND) + "_citizens";
		LAi_group_MoveCharacter(sld, sTemp);
	//	sld.talker = 10;
        ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "reload1");
}

void CapBloodLine_q3_Complited()
{
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    pchar.quest.CapBloodEscape1.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape1.function                  = "ReturnToPlantation1";

    //pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
    //pchar.quest.CapBloodEscape2.win_condition.l1.location = "BridgeTown_Plantation";
    //pchar.quest.CapBloodEscape.function                  = "ReturnToPlantation2";

}

void ReturnToPlantation1(string qName)
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("SolderTakeBlades", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "STBStep_2";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
    sld.BreakTmplAndFightGroup = true;
    SetFantomParamHunter(sld); //крутые парни
	LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"));
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;

}

void ReturnToPlantation2(string qName)
{
    ref sld;
    sld = characterFromID("Hugtorp");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	
    sld = characterFromID("Pitt");
    ChangeCharacterAddressGroup(sld, "None", "", "");
	chrDisableReloadToLocation = true;
}

void ReturnToPlantation3()
{
    ref sld;
    SetLocationCapturedState("BridgeTown_Plantation", true);
    string sTemp = "TmpEnemy";
   	LAi_group_SetHearRadius(sTemp, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(sTemp, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(sTemp, LAI_GROUP_GRD_LOOK - 1);
    LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0);

    SetShipInBridgetown(); // Готовим Бриджтаун
    Pchar.questTemp.CapBUnarmed = false;

    sld = characterFromID("Hugtorp");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.talker = 10;
    sld.Dialog.CurrentNode = "HTStep_18"; //to_do
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest3");

    sld = characterFromID("Ogl");
    LAi_LoginInCaptureTown(sld, true);
    sld.Dialog.CurrentNode = "HTStep_18";  //to_do
    LAi_SetStayTypeNoGroup(sld);
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest4");

    sld = characterFromID("Dieke");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.Dialog.CurrentNode = "HTStep_18";  //to_do
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest5");
    
    sld = characterFromID("Pitt");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetActorType(sld);
    LAi_ActorSetLayMode(sld);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit2");

    worldMap.date.day = 4;
    Environment.date.day = 4;
    SetCurrentTime(0, 0);

    int n = FindLocation("BridgeTown_Plantation");
    DeleteAttribute(&locations[n], "citizens");
    DeleteAttribute(&locations[n], "carrier");
    
    DoReloadCharacterToLocation("BridgeTown_Plantation", "reload", "reload1_back");
    SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
    
    for (int i=0; i < 7; i++)
	{
        if(i < 2)
        {
            sld = GetCharacter(NPC_GenerateCharacter("PittGuard_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
            SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
            LAi_LoginInCaptureTown(sld, true);
            LAi_SetActorType(sld);
            LAi_SetStayType(sld); // послабление
            LAi_group_MoveCharacter(sld, sTemp);
    		//LAi_SetGuardianTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit"+(2*i+1));
        }
        else
        {
            int iChar = NPC_GeneratePhantomCharacter("soldier", ENGLAND, MAN, 2);
            sld = &characters[iChar];
    		SetNPCModelUniq(sld, "soldier", MAN);
    		sld.City = "Bridgetown";
            sld.CityType = "soldier";
            SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
            LAi_LoginInCaptureTown(sld, true);
           	LAi_SetWarriorType(sld);
    		LAi_SetPatrolType(sld);
            LAi_group_MoveCharacter(sld, sTemp);
    		PlaceCharacter(sld, "patrol", "random_free");
        }
        LAi_SetLoginTime(sld, 0.0, 24.0);
        sld.greeting = "soldier_common";
        sld.dialog.filename = "Common_Soldier.c";
        sld.dialog.currentnode = "first time";
	}

    //pchar.GenQuestBox.BridgeTown_Plantation.stay = true; fix
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.blade7 = 1;
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.potion1 = 3;
    
   	pchar.quest.CapBloodEscape3.win_condition.l1 = "locator";
	pchar.quest.CapBloodEscape3.win_condition.l1.location = "BridgeTown_Plantation";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator = "detector1";
	pchar.quest.CapBloodEscape3.function = "ReturnToPlantation4";
    
    chrDisableReloadToLocation = true;

    //int n = FindLocation("BridgeTown_Plantation");
    //DeleteAttribute(&locations[n], "citizens");

}

void ReturnToPlantation4(string qName)
{
    ref sld;
    string sTemp = "TmpEnemy";
   	LAi_group_SetHearRadius(sTemp, 3); // послабление
   	LAi_group_SetSayRadius(sTemp, 4);
   	LAi_group_SetLookRadius(sTemp, 5);
    for (i = 0 ; i < 2; i++)
    {
        sld = characterFromID("PittGuard_"+i);
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "PStep_11";
    LAi_SetGroundSitTypeNoGroup(sld);
    SetLocationCapturedState("Bridgetown_town", true);
    pchar.quest.CapBloodEscape4.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape4.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape4.function                  = "StillShip";
}

void StillShip(string qName)
{
    //SetCurrentTime(2, 0);

    ref chr,sld ;
    aref st;
    int iNation = SPAIN;
	string slai_group, locatorName, sType, slocator;

    slai_group = "TmpEnemy";
   	LAi_group_SetHearRadius(slai_group, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(slai_group, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(slai_group, LAI_GROUP_GRD_LOOK - 1);
   	//LAi_group_SetRelation(slai_group, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0);
    
	for (i=0; i < 11; i++)
	{
        chr = GetCharacter(NPC_GenerateCharacter("SpaSolder_"+i, "sold_spa_"+(rand(7)+1), "man", "man", sti(pchar.rank)+rand(2)+1, SPAIN, 1, false));
		chr.City = "Bridgetown";
        chr.CityType = "soldier";
        SetFantomParamFromRank(chr, sti(pchar.rank)+rand(2)+1, true); // бравые орлы
		LAi_LoginInCaptureTown(chr, true);
        LAi_SetLoginTime(chr, 0.0, 24.0);
       	LAi_SetWarriorType(chr);
		LAi_SetPatrolType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
		chr.greeting = "soldier_common";
		slocator = PlaceCharacter(chr, "patrol", "random_free");
		while( slocator == "patrol13")  // слишком близко к воротам
		{
            slocator = PlaceCharacter(chr, "patrol", "random_free");
		}
        chr.dialog.filename = "Common_Soldier.c";
        chr.dialog.currentnode = "first time";
	}
	sld = GetCharacter(NPC_GenerateCharacter("SpaRaider", "off_spa_2", "man", "man", 10, SPAIN, 1, false));
    FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 25, 20, "blade30", "pistol2", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
    sld.BreakTmplAndFight = true;
	LAi_LoginInCaptureTown(sld, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, slai_group);
	sld.greeting = "soldier_common";
    sld.dialog.filename = "Common_Soldier.c";
    sld.dialog.currentnode = "first time";
	sld.City = "Bridgetown";
    sld.CityType = "soldier";
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "houseF2");
    
    string sQuest = "SaveArabelaService";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "SaveArabelaService";
    
	chr = GetCharacter(NPC_GenerateCharacter("ArabelaService", "Girl_8", "woman", "towngirl", 10, ENGLAND, 1, false));
	chr.greeting = "Enc_RapersGirl_1";
    chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    chr.dialog.currentnode = "ASStep_0";
//    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
    LAi_SetActorType(chr);
   	LAi_LoginInCaptureTown(chr, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    ChangeCharacterAddressGroup(chr, "Bridgetown_town", "officers", "houseH1_2");

    
	LAi_ActorRunToLocator(chr, "officers", "gate1_3", "SaveArabelaServiceAfraid", 5);
    LAi_ActorFollow(sld, chr, "", -1);
    
   	pchar.quest.CapBloodEscape5.win_condition.l1 = "locator";
	pchar.quest.CapBloodEscape5.win_condition.l1.location = "Bridgetown_town";
	pchar.quest.CapBloodEscape5.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodEscape5.win_condition.l1.locator = "quest11";
	pchar.quest.CapBloodEscape5.function = "ShipGuardsAlarm";
	
	ShipGuards();
	
	Pchar.questTemp.CapBloodLine.SpainInBridgetown = false;
	Pchar.questTemp.CapBloodLine.withCrew = false;
	
	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", true);
	LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", true);
	
    Colonies[FindColony("Bridgetown")].DontSetShipInPort = true;
    sld = characterFromID("Bridgetown Fort Commander");
    sld.Fort.Mode = FORT_DEAD;
	// data of frot die
	sld.Fort.DieTime.Year = GetDataYear();
	sld.Fort.DieTime.Month = GetDataMonth();
	sld.Fort.DieTime.Day = GetDataDay();
	sld.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(sld.index));

}

void ShipGuards()
{
    ref chr,sld;
    string slai_group = "EnemyFight";
    int iChar;
   	string model[6];

    	// ==> рабы массовка
		model[0] = "shipowner_1";
		model[1] = "shipowner_6";
		model[2] = "shipowner_9";
		model[3] = "shipowner_10";
		model[4] = "pirate_1";
		model[5] = "pirate_8";


    LAi_group_Delete(slai_group); // fix
	for (int i=0; i <= 9; i++)
	{

        if(i <= 6)
        {

            chr = GetCharacter(NPC_GenerateCharacter("ShipGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 10, SPAIN, 1, false));
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
            LAi_SetImmortal(chr, true); //homo в одиночку ГГ не справится ;-)
    		LAi_LoginInCaptureTown(chr, true);
            LAi_SetLoginTime(chr, 0.0, 24.0);
    		LAi_SetActorTypeNoGroup(chr);
    		LAi_ActorStay(chr);
    		LAi_group_MoveCharacter(chr, slai_group);
    		ChangeCharacterAddressGroup(chr, "Bridgetown_town", "rld", "aloc"+i);
		}
		else
		{
            sld = GetCharacter(NPC_GenerateCharacter("FreeSlave_"+(i-6), model[rand(5)], "man", "man", 10, SPAIN, 1, false));
            SetFantomParamFromRank(sld, sti(pchar.rank)+makeint(2*MOD_SKILL_ENEMY_RATE/3), true); // бравые орлы
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            LAi_LoginInCaptureTown(sld, true);
            LAi_SetActorType(sld);
    		LAi_ActorStay(sld);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest"+i);
        }
    }
    sld = GetCharacter(NPC_GenerateCharacter("SpaFirstMate", "off_spa_1", "man", "man", 12, SPAIN, 1, false));
    FantomMakeCoolFighter(sld, 12, 30, 30, "blade30", "pistol3", 10);
	LAi_LoginInCaptureTown(sld, true);
	//LAi_group_MoveCharacter(sld, slai_group); fix
    LAi_SetWarriorType(sld);
    ChangeCharacterAddressGroup(sld, "Cabin", "rld", "aloc0");
    pchar.quest.SpaFirstMateDie.win_condition.l1 = "NPC_death";
    pchar.quest.SpaFirstMateDie.win_condition.l1.character = "SpaFirstMate";
   	pchar.quest.SpaFirstMateDie.function = "SpaFirstMateDie";


}

void SaveArabelaService(string qName)
{
    ref sld;
    sld = characterFromID("ArabelaService");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	sld = characterFromID("Hugtorp");
	sld.talker = 10;
}

void CapBloodOfficers()
{
    string offName;
    ref sld;
    Pchar.questTemp.CapBloodLine.withCrew = true;
    for (int i=1 ; i <= 6; i++)
    {

        if(i > 3) offName ="FreeSlave_"+(i-3);
        switch(i)
        {
            case 1:
                offName ="Hugtorp";
            break;
            
            case 2:
                offName ="Dieke";
            break;
            
            case 3:
                offName ="Ogl";
            break;
        }
        sld = characterFromID(offName);
        LAi_SetImmortal(sld, false);
        sld.DontClearDead = true;  // не убирать труп
        sld.BreakTmplAndFight = true;
        LAi_SetActorType(sld);
        LAi_ActorFollow(sld, pchar, "", -1);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        sld.Dialog.CurrentNode = "HTStep_22b";  //

        
    }
}
void ShipGuardsDie()
{
    ref sld;
    chrDisableReloadToLocation = false;
    LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", false);
    sld = characterFromID("SpaFirstMate");
    LAi_group_MoveCharacter(sld, "EnemyFight");
}

void ShipGuardsAlarm(string qName)
{
    chrDisableReloadToLocation = true; // закрыть выход из локации
    LAi_group_SetCheck("EnemyFight", "ShipGuardsDie");
    DoQuestFunctionDelay("AttakShip", 2.0);
}

void AttakShip(string qName)
{
    string offName;
    ref sld;
    int iChar;
    for (int i=0 ; i <= 9; i++)
    {
        offName = "ShipGuard_"+i;
        switch(i)
        {
            case 7:
                offName ="Hugtorp";
            break;

            case 8:
                offName ="Dieke";
            break;

            case 9:
                offName ="Ogl";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar]
       	    LAi_SetWarriorTypeNoGroup(sld);
       	    if(Pchar.questTemp.CapBloodLine.withCrew) LAi_SetImmortal(sld, false);
        }
    }
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); // Чтобы не кидались назад в город
    
}

void SpaFirstMateDie(string qName)
{
    string offName;
    ref sld;
    int iChar;
    for (int i=0; i < 13; i++)
	{

       offName = "SpaSolder_"+i;
        switch(i)
        {
            case 11:
                offName ="SpaRaider";
            break;

            case 12:
                offName ="ArabelaService";
            break;

        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.lifeDay = 0;
        }
    }
    pchar.quest.CapBloodEscape6.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape6.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape6.function                  = "QOfficersRecruit";
    AddQuestRecord("EscapeFormBarbados", "5");
    CloseQuestHeader("EscapeFormBarbados");
    ShipGuardsDie();
}

void QOfficersRecruit(string qName)
{
    string offName, sNode;
    ref sld;
    int iChar;
    for (int i=0 ; i <= 3; i++)
    {
        offName = "ShipGuard_"+i;
        switch(i)
        {
            case 0:
                offName ="Pitt";
                sNode = "PStep_16";
            break;
            
            case 1:
                offName ="Hugtorp";
                sNode = "HTStep_24";
            break;

            case 2:
                offName ="Dieke";
                sNode = "DKStep_5";
            break;

            case 3:
                offName ="Ogl";
                sNode = "OGLStep_11";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.loyality = MAX_LOYALITY; //fix лояльности квестовых
            LAi_SetImmortal(sld, false);//fix бессмертного Питта
       	    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "rld", "aloc"+(i+1));
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "quest", "quest11");
            sld.dialog.currentnode = sNode;
            if (offName =="Pitt") LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
            else LAi_SetStayTypeNoGroup(sld);

        }
    }
    //chrDisableReloadToLocation = true;

}

void CapBloodLaspEpisode(string qName)
{
    RestoreBridgetown();
}

void SpaCrewAtack()
{
    int hcrew,iChar,i;
    ref chref;
    
    chref = characterFromID("Pitt");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";

    string sGroup = "SpaCrew";
    Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"war");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);

	//Ship_SetTaskAbordage(SECONDARY_TASK, sti(chref.index), sti(Pchar.index)); // fix PRIMARY_TASK
	//chref.Ship_SetTaskAbordage = true; // запомним, чтоб не сбивать
	//chref.ShipTaskLock = true;

    for (i=0; i<2; i++)
    {
        iChar = NPC_GenerateCharacter("SpaBoat_"+i, "off_spa_2", "man", "man", 7, SPAIN, 1, true));
        makeref(chref, Characters[iChar]);
        chref.Ship.Mode = "war";
        chref.Ship.Type = GenerateShip(SHIP_LUGGER, 1);
        SetRandomNameToCharacter(chref);
        SetRandomNameToShip(chref);
        

        SetBaseShipData(chref);
        hcrew = GetMaxCrewQuantity(chref);
        SetCrewQuantityOverMax(chref, 150);

        DeleteAttribute(chref,"ship.sails");
        DeleteAttribute(chref,"ship.masts");
        DeleteAttribute(chref,"ship.blots");

        Fantom_SetCannons(chref, "war");
        Fantom_SetBalls(chref, "war");
        SetFantomParamHunter(chref); //крутые парни
        SetCaptanModelByEncType(sld, "war");//
        Group_AddCharacter(sGroup, chref.id);
        if (i == 0) Group_SetGroupCommander(sGroup, chref.id);
    }
    Group_SetAddress(sGroup, "Barbados", "IslandShips1", "ship_3");
}

void OglAdd()
{
    ref chref;
    chref = characterFromID("Ogl");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Enc_Officer_dialog.c";
	chref.greeting = "Gr_questOfficer";
}

////////////////////////////////////////////////////////////////////////////////////////////
void RestoreBridgetown()
{
        ref rColony;
        Pchar.questTemp.CapBloodLine = false;
        Pchar.model="Blood5";
        //Губернатор
        ref sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
        sld.Dialog.Filename = "Common_Mayor.c";
        sld.Dialog.CurrentNode = "First time";
        //город
        int n = FindLocation("Bridgetown_town");  // не забыть вернуть
        locations[n].reload.l3.close_for_night = true;
        locations[n].questSeekCap = 6;
        locations[n].houseEnc = true;
        //Таверна пьянь
        n = FindLocation("Bridgetown_tavern");
        locations[n].habitues = 1;
        DeleteAttribute(&locations[n], "notCloseCommonHouse");
        //Диалоги горожан
        ChangeBridgeTownDialogs(true);
        bDisableLandEncounters = false;
        chrDisableReloadToLocation = false;
        bDisableFastReload = false;
        Pchar.questTemp.CapBUnarmed = false;
        //сундуки почистим
        //if (CheckAttribute(PChar, "GenQuestBox.CommonStoneHouse")) DeleteAttribute(PChar, "GenQuestBox.CommonStoneHouse");
        n = FindLocation("CommonStoneHouse");
        locations[n].models.day.locators = "StoneHouse_locators";
        locations[n].models.night.locators = "StoneHouse_Nlocators";
        //Плантации
        n = FindLocation("BridgeTown_Plantation");
       	locations[n].citizens = true;
    	locations[n].carrier = true;
    	//
    	SetLocationCapturedState("Bridgetown_town", false);
    	SetLocationCapturedState("BridgeTown_Plantation", false);
    	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", false);
    	LocatorReloadEnterDisable("BridgeTown_town", "reload1_back", false);
	    LocatorReloadEnterDisable("BridgeTown_fort", "reload2", false); //fix

        LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//fix полностью открываем резиденцию
        LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
        LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);

    	//Торговца вернуть
    	sld = characterFromID("Bridgetown_trader");
   	    LAi_RemoveLoginTime(sld);
    	
        makeref(rColony, Colonies[FindColony("Bridgetown")]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
        RemoveShipFromBridgetown();
        //группы потереть
        LAi_group_Delete("EnemyFight");
        LAi_group_Delete("TmpEnemy");

        //прерывания снять
        if (CheckAttribute(PChar, "quest.CureLordMovie")) Pchar.quest.CureLordMovie.over = "yes";
        if (CheckAttribute(PChar, "quest.DragunInvansion")) Pchar.quest.DragunInvansion.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLine_q1_1")) Pchar.quest.CapBloodLine_q1_1.over = "yes";
        if (CheckAttribute(PChar, "quest.onPlantation")) Pchar.quest.onPlantation.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodDetectBlades1")) Pchar.quest.CapBloodDetectBlades1.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodDetectBlades2")) Pchar.quest.CapBloodDetectBlades2.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLineTimer_1")) Pchar.quest.CapBloodLineTimer_1.over = "yes";
        if (CheckAttribute(PChar, "quest.CureMisStid")) Pchar.quest.CureMisStid.over = "yes";
        if (CheckAttribute(PChar, "quest.PrepareToEscape2")) Pchar.quest.PrepareToEscape2.over = "yes";
        if (CheckAttribute(PChar, "quest.PrepareToEscape3")) Pchar.quest.PrepareToEscape3.over = "yes";
        if (CheckAttribute(PChar, "quest.WinterwoodDuel")) Pchar.quest.WinterwoodDuel.over = "yes";
        if (CheckAttribute(PChar, "quest.MoneyForDieke")) Pchar.quest.MoneyForDieke.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodLineTimer_2")) Pchar.quest.CapBloodLineTimer_2.over = "yes";
        if (CheckAttribute(PChar, "quest.QUsurer")) Pchar.quest.QUsurer.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape1")) Pchar.quest.CapBloodEscape1.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape2")) Pchar.quest.CapBloodEscape2.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape3")) Pchar.quest.CapBloodEscape3.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape4")) Pchar.quest.CapBloodEscape4.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape5")) Pchar.quest.CapBloodEscape5.over = "yes";
        if (CheckAttribute(PChar, "quest.CapBloodEscape6")) Pchar.quest.CapBloodEscape6.over = "yes";
        if (CheckAttribute(PChar, "quest.SolderTakeBladesDie")) Pchar.quest.SolderTakeBladesDie.over = "yes";
        LAi_group_RemoveCheck("EnemyFight");
        //Квесты закрыть
        CloseQuestHeader("FishermanQuest");
        CloseQuestHeader("UsurerQuest");
        CloseQuestHeader("PirateQuest");

}
