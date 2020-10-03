#pragma once
#include "../min-sharp-runtime.h"
#include "runtime_interfaces.h"


typedef struct runtime_number_vtable_struct
{
	min_sharp_object_intrinsicts object_intrinsicts;
	Runtime_AdditionOperator runtime_AdditionOperator;
	Runtime_SubstractionOperator runtime_SubstractionOperator;
	Runtime_MultiplicationOperator runtime_MultiplicationOperator;
	Runtime_DivisionOperator runtime_DivisionOperator;
	Runtime_RemainderOperator runtime_RemainderOperator;
	Runtime_EqualityOperator runtime_EqualityOperator;
	Runtime_RelationalOperator runtime_RelationalOperator;
} runtime_number_vtable;

function_call_result runtime_number_initializer(runtime_services* runtime_services);