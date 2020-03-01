#pragma once
#include "min-sharp-runtime.h"

typedef struct system_services_struct system_services;

typedef struct system_services_struct
{
	function_call_result (*release)(system_services* this_instance);
	function_call_result (*allocate_memory)(void ** result, int size);
	function_call_result (*free_memory)(void *memory);
} system_services;

extern  function_call_result system_services_factory(system_services** result);
