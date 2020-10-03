#pragma once
#include "../min-sharp-runtime.h"
#include "runtime_interfaces.h"

typedef struct runtime_number_vtable_struct runtime_number_vtable;
typedef struct runtime_number_factory_struct runtime_number_factory;

typedef struct runtime_number_factory_struct
{
	runtime_number_vtable *numbers_vtable;
	function_call_result(*build_number)(runtime_number_factory* this_instance, runtime_services* runtime, min_sharp_object** returned_exception, min_sharp_object** returned_result);
	function_call_result(*release)(runtime_number_factory* this_instance, runtime_services* runtime);
} runtime_number_factory;

function_call_result runtime_number_factory_initializer(runtime_services* runtime_services, runtime_number_factory** min_sharp_number_factory_result);