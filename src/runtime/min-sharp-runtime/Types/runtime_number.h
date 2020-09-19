#pragma once
#include "../min-sharp-runtime.h"
#include "runtime_interfaces.h"


typedef struct runtime_number_vtable_struct
{
	function_call_result(*__GetInterface)(min_sharp_object** exception, min_sharp_interface** result, internal_string interfaceName);
	unsigned_int_16 number_of_interfaces;
	Runtime_AdditionOperator runtime_AdditionOperator;
	Runtime_SubstractionOperator runtime_SubstractionOperator;
	Runtime_MultiplicationOperator runtime_MultiplicationOperator;
	Runtime_DivisionOperator runtime_DivisionOperator;
	Runtime_RemainderOperator runtime_RemainderOperator;
	Runtime_EqualityOperator runtime_EqualityOperator;
	Runtime_RelationalOperator runtime_RelationalOperator;
} runtime_number_vtable;
