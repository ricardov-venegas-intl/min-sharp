#pragma once
#include "../min-sharp-runtime.h"

function_call_result register_function_type (
	system_services* system_services_instance, 
	runtime_services* runtime_services_instance);

function_call_result function_factory(
	runtime_services* runtime_services_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* function_captures,
	void* function_implementation);

