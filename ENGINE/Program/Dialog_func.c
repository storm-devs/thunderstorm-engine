#include "scripts\utils.c"

// boal -->
#define MAX_TITLENEXTRATE   13 // счетчик для званий
#define MAX_TITLE           5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{ 
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
    if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = GetConvertStr("Address_FormSpa", "globals.txt");
		Address_Form.Fra = GetConvertStr("Address_FormFra", "globals.txt");
		Address_Form.Eng = GetConvertStr("Address_FormEng", "globals.txt");
		Address_Form.Hol = GetConvertStr("Address_FormHol", "globals.txt");
		Address_Form.Pir = GetConvertStr("Address_FormPir", "globals.txt");
    }
    else
    {
		Address_Form.Spa = GetConvertStr("Address_FormFSpa", "globals.txt");
		Address_Form.Fra = GetConvertStr("Address_FormFFra", "globals.txt");
		Address_Form.Eng = GetConvertStr("Address_FormFEng", "globals.txt");
		Address_Form.Hol = GetConvertStr("Address_FormFHol", "globals.txt");
		Address_Form.Pir = GetConvertStr("Address_FormFPir", "globals.txt");
	}
	Address_Form.Spa.Title1 = GetConvertStr("Title_1_Spa", "globals.txt");
	Address_Form.Fra.Title1 = GetConvertStr("Title_1_Fra", "globals.txt");
	Address_Form.Eng.Title1 = GetConvertStr("Title_1_Eng", "globals.txt");
	Address_Form.Hol.Title1 = GetConvertStr("Title_1_Hol", "globals.txt");
	Address_Form.Pir.Title1 = GetConvertStr("Title_1_Pir", "globals.txt");

    Address_Form.Spa.Title2 = GetConvertStr("Title_2", "globals.txt");
	Address_Form.Fra.Title2 = GetConvertStr("Title_2", "globals.txt");
	Address_Form.Eng.Title2 = GetConvertStr("Title_2", "globals.txt");
	Address_Form.Hol.Title2 = GetConvertStr("Title_2", "globals.txt");
	Address_Form.Pir.Title2 = GetConvertStr("Title_2", "globals.txt");
	
	Address_Form.Spa.Title3 = GetConvertStr("Title_3", "globals.txt");
	Address_Form.Fra.Title3 = GetConvertStr("Title_3", "globals.txt");
	Address_Form.Eng.Title3 = GetConvertStr("Title_3", "globals.txt");
	Address_Form.Hol.Title3 = GetConvertStr("Title_3", "globals.txt");
	Address_Form.Pir.Title3 = GetConvertStr("Title_3", "globals.txt");

	Address_Form.Spa.Title4 = GetConvertStr("Title_4", "globals.txt");
	Address_Form.Fra.Title4 = GetConvertStr("Title_4", "globals.txt");
	Address_Form.Eng.Title4 = GetConvertStr("Title_4", "globals.txt");
	Address_Form.Hol.Title4 = GetConvertStr("Title_4", "globals.txt");
	Address_Form.Pir.Title4 = GetConvertStr("Title_4", "globals.txt");

	Address_Form.Spa.Title5 = GetConvertStr("Title_5", "globals.txt");
	Address_Form.Fra.Title5 = GetConvertStr("Title_5", "globals.txt");
	Address_Form.Eng.Title5 = GetConvertStr("Title_5", "globals.txt");
	Address_Form.Hol.Title5 = GetConvertStr("Title_5", "globals.txt");
	Address_Form.Pir.Title5 = GetConvertStr("Title_5", "globals.txt");

	Address_Form.Spa.woman = GetConvertStr("Address_FormSpaW", "globals.txt");
	Address_Form.Fra.woman = GetConvertStr("Address_FormFraW", "globals.txt");
	Address_Form.Eng.woman = GetConvertStr("Address_FormEngW", "globals.txt");
	Address_Form.Hol.woman = GetConvertStr("Address_FormHolW", "globals.txt");
	Address_Form.Pir.woman = GetConvertStr("Address_FormPirW", "globals.txt");

	Address_Form.Spa.man = GetConvertStr("Address_FormSpa", "globals.txt");
	Address_Form.Fra.man = GetConvertStr("Address_FormFra", "globals.txt");
	Address_Form.Eng.man = GetConvertStr("Address_FormEng", "globals.txt");
	Address_Form.Hol.man = GetConvertStr("Address_FormHol", "globals.txt");
	Address_Form.Pir.man = GetConvertStr("Address_FormPir", "globals.txt");
}

// boal -->

string RandSwear()
{
	string ret;
	
	switch (rand(9))
	{
		case 0:
			ret = GetConvertStr("Swear_1", "globals.txt");
		break;

		case 1:
			ret = GetConvertStr("Swear_2", "globals.txt");
		break;

		case 2:
			ret = GetConvertStr("Swear_3", "globals.txt");
		break;

		case 3:
			ret = GetConvertStr("Swear_4", "globals.txt");
		break;

		case 4:
			ret = GetConvertStr("Swear_5", "globals.txt");
		break;

		case 5:
			ret = GetConvertStr("Swear_6", "globals.txt");
		break;

		case 6:
			ret = GetConvertStr("Swear_7", "globals.txt");
		break;

		case 7:
			ret = GetConvertStr("Swear_8", "globals.txt");
		break;	 
		
		case 8:
			ret = GetConvertStr("Swear_9", "globals.txt");
		break;
		
		case 9:
			ret = GetConvertStr("Swear_10", "globals.txt");
		break;
	}
	return ret + " "; // пробел для диалогов
}

//navy --> вынес простые восклицания,
string RandExclamation()
{
    string ret;
	switch(rand(2))
	{
		case 0:
			ret = GetConvertStr("Swear_11", "globals.txt");
		break;

		case 1:
			ret = GetConvertStr("Swear_12", "globals.txt");
		break;

		case 2:
			ret = GetConvertStr("Swear_13", "globals.txt");
		break;
	}
	return ret + " "; // пробел для диалогов
}
//navy <--
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                Выбор фраз для диалога
////////////////////////////////////////////////////////////////////////////////////////////////////////
// boal 13.03.2004 -->
string RandPhraseSimple(string Var1, string Var2);
{
	int RandP;
	RandP = Rand(1);
	switch(RandP)
	{
		case 0:
			return /*"First phrase selected" + */ Var1;
		break;

		case 1:
			return /*"Second phrase selected" + */Var2;
		break;
	}
	return "ERROR";
}
// выбор фразы из трех
string LinkRandPhrase (string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch(RandP)
	{
		case 0:

			return /*"First phrase selected" + */ Var1;

		break;

		case 1:

			return /*"Second phrase selected" + */Var2;

		break;

		case 2:

			return /*"Third phrase selected" + */Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
    switch(sti(Character.nation))
	{
		case ENGLAND:
            return GetConvertStr("NationKingsCrownEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationKingsCrownFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationKingsCrownSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationKingsCrownHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationKingsCrownPir", "globals.txt");
		break;
	}
}
string NationKingsName(ref NPChar)
{
    switch(sti(NPChar.nation))
	{
		case ENGLAND:
            return GetConvertStr("NationKingsNameEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationKingsNameFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationKingsNameSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationKingsNameHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationKingsNamePir", "globals.txt");
		break;
	}
}

string NationNameMan(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return GetConvertStr("NationNameManEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNameManFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNameManSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNameManHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNameManPir", "globals.txt");
		break;
	}
}

string NationNamePeople(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return GetConvertStr("NationNamePeopleEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNamePeopleFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNamePeopleSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNamePeopleHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNamePeoplePir", "globals.txt");
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
    switch(pNation)
	{
  case ENGLAND:
            return GetConvertStr("NationNamePeopleEngAcc", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNamePeopleFraAcc", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNamePeopleSpaAcc", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNamePeopleHolAcc", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNamePeoplePirAcc", "globals.txt");
		break;
	}
}

string NationNameAblative(int iNation) //творительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return GetConvertStr("NationNameAblativeEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNameAblativeFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNameAblativeSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNameAblativeHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNameAblativePir", "globals.txt");
		break;
	}
}

string NationNameNominative(int iNation) //именительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return GetConvertStr("NationNameNominativeEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNameNominativeFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNameNominativeSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNameNominativeHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNameNominativePir", "globals.txt");
		break;
	}
}

string NationNameGenitive(int iNation) // родительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return GetConvertStr("NationNameGenitiveEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationNameGenitiveFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationNameGenitiveSpa", "globals.txt");
		break;
		case HOLLAND:
			return GetConvertStr("NationNameGenitiveHol", "globals.txt");
		break;
		case PIRATE:
			return GetConvertStr("NationNameGenitivePir", "globals.txt");
		break;
	}
}

///////Часто будет использоваться поэтому заношу сюда
string NationEuropaTown(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return GetConvertStr("NationEuropaTownEng", "globals.txt");
		break;
		case FRANCE:
            return GetConvertStr("NationEuropaTownFra", "globals.txt");
		break;
		case SPAIN:
            return GetConvertStr("NationEuropaTownSpa", "globals.txt");
		break;
        case PIRATE:
	    	return GetConvertStr("NationEuropaTownPir", "globals.txt");
		break;
		case HOLLAND:
	    	return GetConvertStr("NationEuropaTownHol", "globals.txt");
		break;
	}
}
string GetCityName(string city) // имена городов по аттрибуту char.city
{
    string ret;
    int nFile = LanguageOpenFile("LocLables.txt");
    
	ret = LanguageConvertString(nFile, city + " Town")
	LanguageCloseFile( nFile );
	
	return  ret;
}

string GetPortByCityName(string city) // имена портов по городов по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SanJuan":
            return "SanJuan_town";
		break;
		case "Santiago":
            return "Santiago_town";
		break;
		case "PuertoPrincipe":
            return "PuertoPrincipe_port";
		break;
		case "SentJons":
            return "SentJons_town";
		break;
		case "PortRoyal":
            return "PortRoyal_town";
		break;
		case "FortOrange":
            return "Shore35";
		break;
		case "Villemstad":
            return "Villemstad_town";
		break;
		case "BasTer":
            return "BasTer_town";
		break;
		case "LaVega":
            return "LaVega_port";
		break;
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SantoDomingo":
            return "SantoDomingo_town";
		break;
		case "PortPax":
            return "PortPax_town";
		break;
		case "Pirates":
            return "Pirates_town";
        break;
		case "FortFrance":
            return "FortFrance_town";
		break;
		case "LeFransua":
            return "LeFransua_port";
		break;
		case "Havana":
            return "Havana_town";
		break;
		case "Charles":
            return "Charles_town";
		break;
		case "PortoBello":
            return "PortoBello_town";
		break;
		case "PortSpein":
            return "PortSpein_town";
		break;
		case "Tortuga":
            return "Tortuga_town";
		break;
		case "Marigo":
            return "Marigo_town";
		break;
		case "Panama":
            return "Panama_town";
		break;
		case "Cartahena":
            return "Cartahena_town";
		break;
		case "Maracaibo":
            return "Maracaibo_town";
		break;
		case "Caracas":
            return "Caracas_town";
		break;
		case "Cumana":
            return "Cumana_town";
		break;
		case "SantaCatalina":
            return "SantaCatalina_town";
		break;
		case "Beliz":
            return "Beliz_town";
		break;
	}
	return "";
}


string GetIslandByCityName(string city) // имена острова по городу по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba";
		break;
		case "PuertoPrincipe":
            return "Cuba";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola";
		break;
		case "SantoDomingo":
            return "Hispaniola";
		break;
		case "PortPax":
            return "Hispaniola";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "Mein";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Mein";
		break;
		case "Cartahena":
            return "Mein";
		break;
		case "Maracaibo":
            return "Mein";
		break;
		case "Caracas":
            return "Mein";
		break;
		case "Cumana":
            return "Mein";
		break;
		case "SantaCatalina":
            return "Mein";
		break;
		case "Beliz":
            return "Mein";
		break;
		case "Tenotchitlan":
            return "Mein";
		break;
	}
	return "";
}

string GetArealByCityName(string city) // ареал по городу по аттрибуту char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba1";
		break;
		case "PuertoPrincipe":
            return "Cuba1";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola1";
		break;
		case "SantoDomingo":
            return "Hispaniola1";
		break;
		case "PortPax":
            return "Hispaniola2";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba2";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "PortoBello";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Panama";
		break;
		case "Cartahena":
            return "Cartahena";
		break;
		case "Maracaibo":
            return "Maracaibo";
		break;
		case "Caracas":
            return "Caracas";
		break;
		case "Cumana":
            return "Cumana";
		break;
		case "SantaCatalina":
            return "SantaCatalina";
		break;
		case "Beliz":
            return "Beliz";
		break;
		case "Tenotchitlan":
            return "Tenotchitlan";
		break;
	}
	return "";
}

string GiveArealByLocation(ref location)
{
	string sAreal;
	if (CheckAttribute(location, "MustSetReloadBack")) return "none";
	if (CheckAttribute(location, "fastreload")) 
	{
		sAreal = GetArealByCityName(location.fastreload); 
		return sAreal;
	}
	if (CheckAttribute(location, "parent_colony")) 
	{
		sAreal = GetArealByCityName(location.parent_colony); 
		return sAreal;
	}
	if (!CheckAttribute(location, "islandId")) return "none";
	if (location.islandId == "Cuba" || location.islandId == "Hispaniola" || location.islandId == "Mein") 
	{			
		if (!CheckAttribute(location, "islandIdAreal")) return "none";
		sAreal = location.islandIdAreal;
	}
	else sAreal = location.islandId;
	return sAreal;
}

// выбор куда идти  по острову даем город (главный город острова с портом)
string GetCityNameByIsland(string CurIslandId)
{
	string TargetLocation;

	TargetLocation = "None";

	switch (CurIslandId)
	{
    	case "Antigua":
			TargetLocation = "SentJons";
		break;
		case "Bermudes":
			TargetLocation = "Pirates";
		break;
		case "Barbados":
			TargetLocation = "Bridgetown";
		break;
		case "Beliz":
			TargetLocation = "Beliz";
		break;
		case "Cuba1":
			TargetLocation = "Santiago";
		break;
		case "Cuba2":
			TargetLocation = "Havana";
		break;
		case "Cumana":
			TargetLocation = "Cumana";
		break;
		case "Caracas":
			TargetLocation = "Caracas";
		break;
		case "Curacao":
			TargetLocation = "Villemstad";
		break;
		case "Cartahena":
			TargetLocation = "Cartahena";
		break;
		case "Guadeloupe":
			TargetLocation = "BasTer";
		break;
		case "Hispaniola1":
			TargetLocation = "SantoDomingo";
		break;
		case "Hispaniola2":
			TargetLocation = "PortPax";
		break;
		case "Jamaica":
			TargetLocation = "PortRoyal";
		break;
		case "Maracaibo":
			TargetLocation = "Maracaibo";
		break;
		case "Martinique":
			TargetLocation = "FortFrance";
		break;
		case "SentMartin":
			TargetLocation = "Marigo";
		break;
		case "Nevis":
			TargetLocation = "Charles";
		break;
		case "PuertoRico":
			TargetLocation = "SanJuan";
		break;
		case "PortoBello":
			TargetLocation = "PortoBello";
		break;
		case "Pearl":
			TargetLocation = "none";
		break;
		case "Panama":
			TargetLocation = "Panama";
		break;
		case "SantaCatalina":
			TargetLocation = "SantaCatalina";
		break;
		case "Terks":
			TargetLocation = "none";
		break;
		case "Dominica":
			TargetLocation = "none";
		break;
		case "Caiman":
			TargetLocation = "none";
		break;
		case "Tortuga":
			TargetLocation = "Tortuga";
		break;
		case "Trinidad":
			TargetLocation = "PortSpein";
		break;
		case "Tenotchitlan":
			TargetLocation = "none";
		break;
	}
    return TargetLocation;
}

string TimeGreeting()
{
    if (GetHour() >= 18 && GetHour() < 23)
    {
       return GetConvertStr("TimeGreeting_1", "globals.txt");
    }
    if (GetHour() >= 6 && GetHour() < 12)
    {
       return GetConvertStr("TimeGreeting_2", "globals.txt");
    }
    if (GetHour() >= 12 && GetHour() < 18)
    {
       return GetConvertStr("TimeGreeting_3", "globals.txt");
    }
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return GetConvertStr("TimeGreeting_4", "globals.txt");
    }
    return GetConvertStr("TimeGreeting_5", "globals.txt");
}

// выбор фразы от репутации
string PCharRepPhrase (string bad, string good)
{
	return NPCharRepPhrase(pchar, bad, good);
}
// boal для НПС
string NPCharRepPhrase(ref _pchar, string bad, string good)
{
	if(makeint(_pchar.reputation) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}

////////// поиск нужного перса для диалога
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищем
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

    if (n > 0)
    {
        makeref(rCharacter,Characters[n]);
        return  rCharacter.id;
    }
    return  "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищем
	int n;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
            if (rCharacter.(attr2) == val2)
                return  n;
		}
    }
    return  -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
    ref   rColony; //ищем
	int   n;
	bool  ok;

	for (n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		ok = false;
		if (CheckAttribute(rColony, "Default.BoardLocation2") && rColony.Default.BoardLocation2 == attrPresent1)
		{
		    ok = true;
		}
		if (rColony.Default.BoardLocation == attrPresent1 || ok)
        {
			if (rColony.HeroOwn == true)
			{
			    return  -1;
			}
			
			return GetFortCommanderIdx(rColony.id);
		}
    }
    return  -1;
}
// обращение НПС к ГГ, зависит от нации НПС
string GetAddress_Form(ref NPChar)
{
    string attr = NationShortName(sti(NPChar.nation));
    return address_form.(attr);
}
// обращение ГГ к НПС, зависит от нации НПС и его пола
string GetAddress_FormToNPC(ref NPChar)
{
    string attr  = NationShortName(sti(NPChar.nation));
    string attr2 = NPChar.sex;
    // проверка на скелетов
    if (attr2 != "woman")
    {
        attr2 = "man";
    }
    return address_form.(attr).(attr2);
}
string GetAddress_FormTitle(int nation, int num)
{
    string attr  =  NationShortName(nation);
    string attr2 =  "Title" + num;
    string ret   =  GetConvertStr("Title_0", "globals.txt"); 
    if (CheckAttribute(address_form, attr + "." + attr2))
    {
        ret = address_form.(attr).(attr2);
    }
    return ret;
}

bool isCityHasFort(string _city)
{
    int iTest = FindColony(_city); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		if (!CheckAttribute(rColony, "HasNoFort")) return true;
	}
	return false;
}

string GetCityFrom_Sea(string _city)
{
    int iTest = FindColony(_city); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		return rColony.from_sea;
	}
	return "";
}
// boal <--

// eddy. кто по профессии (только для типовых статиков, не фантомов). sPrefix - приставка для падежей: Gen, Dat..
string GetWorkTypeOfMan(ref NPChar, string sPrefix)
{
	string sCity, sTemp;
	sTemp = "unknown";
	if (CheckAttribute(NPChar, "City")) 
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
	}
	return XI_ConvertString("Who" + sTemp + sPrefix);
}