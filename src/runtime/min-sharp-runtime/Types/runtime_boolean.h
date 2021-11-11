#pragma once

#include "runtime_interfaces.h"
#include "../min-sharp-runtime.h"
#include "../services/runtime_services.h"
#include "../services/internal/system_services.h"

// Forward declarations.
function_call_result register_boolean_type(
	system_services* system_services_instance,
	runtime_services* runtime_services_instance);

function_call_result boolean_factory(
	runtime_services* runtime_services_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_boolean value);

