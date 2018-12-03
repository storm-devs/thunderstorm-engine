#ifndef _CLASSES_TABLE_H_
#define _CLASSES_TABLE_H_

#include "strings_list.h"

#define INVALID_CLASS_CODE			INVALID_ORDINAL_NUMBER

typedef struct 
{
	long  module_code;
	long  module_class_id;
	uint32_t real_class_id;
} CLASS_SEARCH_DATA;

class CLASSES_TABLE : public STRINGS_LIST
{
public:
	CLASSES_TABLE(){};
	~CLASSES_TABLE(){};
	uint32_t GetClassCode(char * class_name);
	uint32_t GetModuleCode(uint32_t class_code);
	uint32_t GetClassModuleID(uint32_t class_code);
	CLASS_SEARCH_DATA GetClassData(uint32_t class_code);

};
#endif