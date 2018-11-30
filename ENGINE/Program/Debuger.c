// BOAL нажатие на F12 вызывает этот код. Его можно править с alt-tab в игре, изменения будут сразу
//native string GetHello();
//#libriary "b_engine"

void ActiveINSERTControl()
{
    //DoReloadCharacterToLocation(Pchar.location, "goto", "goto2");
    //DoReloadCharacterToLocation("PlutoStoreSmall", "reload", "reload1");
	//DoReloadCharacterToLocation("SantaFlorentinaShipInside4", "goto", "goto1");
}

void ActiveF4Control()
{
	/*Log_Info("Test F4 button");
    SetRandGeraldSail(pchar, rand(4));*/
}

void ActiveF5Control()
{
	Log_Info("Test F5 button");
}

void ActiveF7Control()
{


}

void ActiveF10Control()
{
	Log_Info("Test F10 button");
    LaunchPsHeroScreen();
    trace("===================RUMOURS=======================");
    for(int i = 0; i < MAX_RUMOURS; i++)
	{
        DumpAttributes(&Rumour[i]);
    	trace("===================");
	}
}

///  статы персонажа в близи
void ActiveF12Control()
{
    ref mainCh = GetMainCharacter();
    
    //Найти ближайшего видимого персонажа в заданном радиусе
    int res = LAi_FindNearestVisCharacter(mainCh, 15);
    if (res != -1)
    {
        ref findCh = GetCharacter(res);
        res = findCh.chr_ai.hp;
        Log_SetStringToLog("" + GetFullName(findCh) +
                           " "+XI_ConvertString("Rank")+" " + findCh.rank + " "+XI_ConvertString("Health")+" "+res + "/" + LAi_GetCharacterMaxHP(findCh));

		if (bBettaTestMode)
        {
            Log_SetStringToLog("Id= " + findCh.id);
            Log_SetStringToLog("Idx= " + findCh.index);
            if (CheckAttribute(findCh, "equip.blade"))
            {
                Log_SetStringToLog("Blade= " + findCh.equip.blade);
            }
            if (CheckAttribute(findCh, "equip.pistol"))
            {
                Log_SetStringToLog("Pistol= " + findCh.equip.pistol);
            }
            Log_SetStringToLog("model= " + findCh.model);
            Log_SetStringToLog("face= " + findCh.faceId);
            Log_SetStringToLog("chr_ai.type= " + findCh.chr_ai.type);
            Log_SetStringToLog("Group= "+findCh.location.group + " locator= " + findCh.location.locator);
            if (CheckAttribute(findCh, "cirassId"))
            {
                Log_SetStringToLog("cirassId= " + sti(findCh.cirassId));
            }
            else
            {
                Log_SetStringToLog("Нет брони");
            }
            if (CheckAttribute(findCh, "chr_ai.FencingType"))
            {
                Log_SetStringToLog("chr_ai.FencingType= " + findCh.chr_ai.FencingType));
            }
            else
            {
                Log_SetStringToLog("Нет FencingType - error");
            }
            /*int dchr_index;
            ref deadCh;
            dchr_index = Dead_FindCloseBody();
            if (dchr_index != -1)
            {
                deadCh = &Dead_Characters[dchr_index];
                Log_SetStringToLog("Dead=" + deadCh.id);
            } */
			Log_SetStringToLog("Нация: " + findCh.nation);
			Log_SetStringToLog("Пол: " + findCh.sex);
			Log_SetStringToLog("Группа: " + findCh.chr_ai.group);
			Log_SetStringToLog("Темплейт: " + findCh.chr_ai.tmpl);
			Log_SetStringToLog("Стейт: " + findCh.chr_ai.tmpl.state);
			dumpattributes(findCh);

            mainCh.SystemInfo.OnlyShowCharacter = true;
			LaunchCharacter(findCh);
        }
        else
        {
            if (MOD_BETTATESTMODE == "Test")
	        {
	            Log_SetStringToLog("Id= " + findCh.id);
	        }
        }
    }
}

///////////////////////////// test //////////////
void TestColonyCommanders()
{
	int iChar;

	string sColony;

	int i;
	float x, y, z;  // boal

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // необитайки
		// зададим базовых мэров городов
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // мэр есть
        	Log_Info("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        	trace("M: " + characters[iChar].id + " L:" + characters[iChar].location +
        	" " + characters[iChar].City + "  " + characters[iChar].nation);
        }

		// добавить проверку на пиратов, у них нет фортов, нафиг им коммандер?
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
			continue;
		}
		iChar = GetCharacterIndex(colonies[i].id + " Fort Commander");
		Log_Info("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
  		trace("F: " + characters[iChar].id + " L:" + characters[iChar].location + " g " + characters[iChar].location.group + " r " + characters[iChar].location.locator +
  		" " + characters[iChar].City + "  " + characters[iChar].nation);
	}
}
// проверка ликвидности товара - цена-вес, что выгоднее - выводим в компил.лог список, строим заполняя трюм товаром по одной пачке
void TestGoodsLiquidity()
{
	int i, j, idx;
	float fMaxCost;
	
	for (i = 0; i< GOODS_QUANTITY; i++)
	{
		SetCharacterGoods(pchar, i, sti(Goods[i].Units));
	}
	trace("======= TestGoodsLiquidity ======== start ");
	for (j = 0; j< GOODS_QUANTITY; j++)
	{
		fMaxCost = 0;
		idx = -1; 
		for (i = 0; i< GOODS_QUANTITY; i++)
		{
			if (GetCargoGoods(pchar, i) > 0)
			{
				if (fMaxCost < stf(Goods[i].Cost)/stf(Goods[i].Weight)) 
				{
					fMaxCost = stf(Goods[i].Cost)/stf(Goods[i].Weight);
					idx = i;
				} 
			}
		}
		if (fMaxCost > 0)
		{
			SetCharacterGoods(pchar, idx, 0);	
			trace(Goods[idx].Name + " = " + fMaxCost);
			Log_info(Goods[idx].Name + " = " + fMaxCost);
		}
	}
	trace("======= TestGoodsLiquidity ======== end ");
}
