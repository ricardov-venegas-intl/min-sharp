#pragma once
#include "min-sharp-runtime.h"
#include "system_services.h"

typedef struct system_list_struct system_list;
typedef struct system_list_data_struct system_list_data;

typedef function_call_result(*enumerate_callback_function)(system_list* this_instance, void* element);
typedef function_call_result(*filter_callback_function)(system_list* this_instance, void* element, min_sharp_boolean *found);

typedef struct system_list_struct
{
	function_call_result(*add_element)(system_list* this_instance, void* new_element);
	function_call_result(*remove_element)(system_list* this_instance, void* new_element);
	function_call_result(*for_each)(system_list* this_instance, enumerate_callback_function enumerate_function_instance);
	function_call_result(*exists)(system_list* this_instance, filter_callback_function filter_function);
	function_call_result(*find_first)(system_list* this_instance, filter_callback_function filter_function, void **result);
	function_call_result(*release)(system_list* this_instance);
	system_list_data* data;
} system_list;

extern function_call_result system_list_factory(system_list** list, system_services* system_services_instance);