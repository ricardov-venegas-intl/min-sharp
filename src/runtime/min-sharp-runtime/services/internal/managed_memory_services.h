#pragma once
#include "../../min-sharp-runtime.h"
#include "system_services.h"

typedef struct managed_memory_services_struct managed_memory_services;
typedef struct managed_memory_services_data_struct managed_memory_services_data;

const int runtime_managed_object = 7; //111

typedef struct managed_memory_services_struct
{
	function_call_result(*push_scope)(managed_memory_services* this_instance, unsigned_int_16 number_of_elements, min_sharp_object* scope_variables[]);
	function_call_result(*pop_scope)(managed_memory_services* this_instance);
	function_call_result(*allocate_object)(managed_memory_services* this_instance, min_sharp_object** new_object, unsigned_int_16 internal_data_size);
	function_call_result(*collect_garbage)(managed_memory_services* this_instance);
	function_call_result(*get_counters)(managed_memory_services* this_instance, unsigned_int_64 *total_allocated_memory, unsigned_int_64 *total_allocations, unsigned_int_64 *total_deallocations);
	function_call_result(*release)(managed_memory_services* this_instance);
	managed_memory_services_data* data;
} managed_memory_services;

extern function_call_result managed_memory_services_factory(system_services* system_services_instance, managed_memory_services** result);
