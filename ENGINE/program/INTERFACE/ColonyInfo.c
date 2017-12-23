//  интерфейс смены владельца города
string totalInfo;
string sCity;
int    iNation, iDay;

void InitInterface(string iniName)
{
    StartAboveForm(true);
    // лочим квест и карту
    bQuestCheckProcessFreeze = true;
    
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeId"))
    {
        // режим осады
        sCity    = pchar.GenQuestFort.ColonySiegeId;
		iNation  = sti(pchar.GenQuestFort.ColonySiegeNation);
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeId");
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeNation");
		
		if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeEnd"))
		{// конец осады
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeEnd");
			CalculateEndSiegeCity();
		}
		else
		{
            iDay     = sti(pchar.GenQuestFort.ColonySiegeTime);
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeTime");
			CalculateSiegeCity();
		}
    }
    else
    {
		// режим захвата города, не используется
		sCity    = pchar.GenQuest.CapturedCity;
		iNation  = sti(pchar.GenQuest.CaptureNation);
		CalculateCapturedCity();
	}
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100);//заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                IDoExit(RC_INTERFACE_SALARY_EXIT);
    		}
    	break;
	}
}

void CalculateEndSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	totalInfo = xiStr("MSG_ColonyInfo_1") + GetCityName(sCity) + xiStr("MSG_ColonyInfo_2") + XI_ConvertString(sTemp + "Gen") + ".";

    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	if (!isCityHasFort(sCity)) // сухопутный город
	{
	    totalInfo = xiStr("MSG_ColonyInfo_3")+XI_ConvertString(sTemp + "Gen")+xiStr("MSG_ColonyInfo_4")+GetCityName(sCity)+ xiStr("MSG_ColonyInfo_5") +FindRussianDaysString(iDay)+ xiStr("MSG_ColonyInfo_6");
	}
	else
	{
		totalInfo = xiStr("MSG_ColonyInfo_7") +XI_ConvertString(sTemp + "Gen")+ xiStr("MSG_ColonyInfo_8") +GetCityName(sCity)+ xiStr("MSG_ColonyInfo_5") +FindRussianDaysString(iDay)+ xiStr("MSG_ColonyInfo_6");
	}
    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateCapturedCity()
{

    totalInfo = xiStr("MSG_ColonyInfo_9") + XI_ConvertString("Colony" + sCity) + xiStr("MSG_ColonyInfo_10");

    SetNewGroupPicture("Nat1", "NATIONS",  GetNationNameByType(iNation));
    SetFormatedText("INFO_TEXT",totalInfo);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}