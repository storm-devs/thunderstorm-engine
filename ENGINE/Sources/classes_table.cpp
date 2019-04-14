#include "classes_table.h"
#include "../../Common_h/Exs.h"
#include "externs.h"

uint32_t CLASSES_TABLE::GetClassCode(char * class_name)
{
	uint32_t class_code;
	class_code = GetStringCode(class_name);
	if(class_code == INVALID_CLASS_CODE) //if(Exceptions_Mask &_X_NO_CLASS) 
		STORM_THROW(cant find class);
	return class_code;
}

uint32_t CLASSES_TABLE::GetClassModuleID(uint32_t class_code)
{
	CLASS_SEARCH_DATA class_search_data;
	if(!GetStringData(class_code,&class_search_data)) THROW;
	return class_search_data.module_class_id;
}

uint32_t CLASSES_TABLE::GetModuleCode(uint32_t class_code)
{
	CLASS_SEARCH_DATA class_search_data;
	if(!GetStringData(class_code,&class_search_data)) THROW;
	return class_search_data.module_code;
}

CLASS_SEARCH_DATA CLASSES_TABLE::GetClassData(uint32_t class_code)
{
	CLASS_SEARCH_DATA class_search_data;
	if(!GetStringData(class_code,&class_search_data)) THROW;
	return class_search_data;
}