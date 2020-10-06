#pragma once

#include "../min-sharp-runtime.h"
#include "internal/system_services.h"

//Forward definitions.
typedef struct runtime_services_struct runtime_services;
typedef struct runtime_services_data_struct runtime_services_data;

typedef struct runtime_services_struct
{
	// unmanaged_memory
	function_call_result(*allocate_unmanaged_memory)(runtime_services* this_instance, void** result, int size);
	function_call_result(*free_unmanaged_memory)(runtime_services* this_instance, void* memory);

	// runtime exeception
	function_call_result(*system_argument_exception)(runtime_services* this_instance, min_sharp_object** returnedExcption, internal_string argument_name);
	function_call_result(*system_argument_null_exception)(runtime_services* this_instance, min_sharp_object** returnedExcption, internal_string argument_name);
	
	// strings
	function_call_result(*are_strings_equal_case_insentitive)(runtime_services* this_instance, min_sharp_boolean* result, internal_string string1, internal_string string2, unsigned_int_32 max_string_size);
		
	function_call_result(*release)(runtime_services* this_instance);
	runtime_services_data* data;
} runtime_services;

extern function_call_result runtime_services_factory(system_services* system_services_instance, runtime_services** result);
