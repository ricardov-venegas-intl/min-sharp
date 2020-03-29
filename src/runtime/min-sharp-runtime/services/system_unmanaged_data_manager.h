#pragma once
#include "min-sharp-runtime.h"
#include "system_services.h"



typedef struct system_unmanaged_data_structure_struct system_unmanaged_data_structure;
typedef struct system_unmanaged_data_structure_data_struct system_unmanaged_data_structure_data;

typedef function_call_result(*enumerate_callback_function)(system_unmanaged_data_structure* this_instance, void* element, void* data_context);
typedef function_call_result(*filter_callback_function)(system_unmanaged_data_structure* this_instance, void* element, void* data_context, min_sharp_boolean *found);

typedef struct system_unmanaged_data_structure_struct
{
	function_call_result(*add_element)(system_unmanaged_data_structure* this_instance, void* new_element);
	function_call_result(*remove_element)(system_unmanaged_data_structure* this_instance, void* element);
	function_call_result(*for_each)(system_unmanaged_data_structure* this_instance, enumerate_callback_function enumerate_function_instance, void* data_context);
	function_call_result(*exists)(system_unmanaged_data_structure* this_instance, void *element, min_sharp_boolean* found);
	function_call_result(*find_first)(system_unmanaged_data_structure* this_instance, filter_callback_function filter_function, void* data_context, void **result, min_sharp_boolean* found);
	system_unmanaged_data_structure_data* data;
} system_unmanaged_data_structure;

typedef struct system_unmanaged_data_manager_struct system_unmanaged_data_manager;
typedef struct system_unmanaged_data_manager_data_struct system_unmanaged_data_manager_data;

typedef struct system_unmanaged_data_manager_struct {
	function_call_result(*create_list)(system_unmanaged_data_manager* this_instance, system_unmanaged_data_structure ** unmanaged_data_structure);
	function_call_result(*release_list)(system_unmanaged_data_manager* this_instance, system_unmanaged_data_structure* unmanaged_data_structure);
	function_call_result(*release)(system_unmanaged_data_manager* this_instance);
	system_unmanaged_data_manager_data* data;
} system_unmanaged_data_manager;

extern function_call_result system_unmanaged_data_manager_factory(system_unmanaged_data_manager** unmanaged_data_manager, system_services* system_services_instance);
