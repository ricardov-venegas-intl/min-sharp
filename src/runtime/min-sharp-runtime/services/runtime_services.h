#pragma once

#include "../min-sharp-runtime.h"
#include "system_services.h"

typedef struct runtime_services_struct runtime_services;

typedef struct runtime_services_data_struct runtime_services_data;

typedef struct runtime_services_struct
{
	function_call_result(*__PushScope)(runtime_services* this_instance, int_32 number_of_element, void* local_variables[]);
	function_call_result(*__PopScope)(runtime_services* this_instance);
	function_call_result(*__Clone)(runtime_services* this_instance, runtime_services** cloned_instance);
	function_call_result(*__CollectGarbage)(runtime_services* this_instance, runtime_services** cloned_instance);
	function_call_result(*BuildObject)(runtime_services* this_instance, internal_string* type_name, min_sharp_object **new_object);
	function_call_result(*BuildObjectFromFactory)(runtime_services* this_instance, internal_string* type_name, min_sharp_object factory, min_sharp_object** new_object);
	function_call_result(*RegisterFactory)(runtime_services* this_instance, internal_string* type_name, min_sharp_object factory);
	function_call_result(*allocate_unmanaged_memory)(runtime_services* this_instance, void** result, int size);
	function_call_result(*free_unmanaged_memory)(runtime_services* this_instance, void* memory);
	function_call_result(*release)(runtime_services* this_instance);
	runtime_services_data* data;
} runtime_services;

extern function_call_result runtime_services_factory(runtime_services **result, system_services *system_services_instance);
