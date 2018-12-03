#ifndef SIMPLE_GEOM_NAME_PARSER
#define SIMPLE_GEOM_NAME_PARSER


#include <string.h>


#define MAX_STRING_SIZE 8192

class GeomNameParser
{

	std::vector<char*> Tokens;
	char NamesString[MAX_STRING_SIZE];

public:
 
	//GeomNameParser () : Tokens(_FL_) {};
	//~GeomNameParser () {};
 
 
 __forceinline const char* GetRandomName (const char* names)
 {
	 Tokenize (names);
	 if (Tokens.size() == 0) return nullptr;

	 return Tokens[(rand () % Tokens.size())];
 }


 __forceinline uint32_t GetTokensCount ()
 {
	 return Tokens.size();
 }

 __forceinline const char* GetTokenByIndex (uint32_t Index)
 {
	 return Tokens[Index];
 }
 
 __forceinline void Tokenize (const char* names)
 {
	Tokens.clear();
	strncpy (NamesString, names, MAX_STRING_SIZE);
  int StrLen = strlen (NamesString);
  if (StrLen > 0 && NamesString[StrLen-1] != ';') 
	  strcat (NamesString, ";");
  StrLen = strlen (NamesString);

  int FromChar = 0;
  for (int n = 0; n < StrLen; n++)
  {
    if (NamesString[n] == ';')
    {
      NamesString[n] = 0;

      char* ModelName = NamesString + FromChar;
      if (ModelName[0] != '\0')
      {
				Tokens.push_back(ModelName);
      }
      FromChar = n+1;
    }
  }
 }
  
};
	

#endif