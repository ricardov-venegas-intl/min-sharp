#include "pch.h"
#include "internal_runtime.h"
#include "type_internals.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

min_sharp_exception* runtime_exception;
min_sharp_type_info runtime_exception_type;
const internal_string runtime_exception_type_name = "RuntimeException";
const internal_string runtime_exception_message = "Runtime Exception";
const internal_string runtime_null_refrence_exception_type_name = "NullReferenceException";


// Fill the runetinme exception, aborts if failed
function_call_result minsharp_runtime_exception()
{	
	function_call_result call_result = minsharp_runtime_exception(&runtime_exception, runtime_exception_type_name, runtime_exception_message);
	if (call_result != function_call_result_success)
	{
		abort;
	}
	return function_call_result_success;
}

function_call_result minsharp_runtime_exception(min_sharp_exception** new_exception, internal_string exception_type_name, internal_string exception_message)
{
	min_sharp_exception* result;
	runtime_exception_type.interface_name = exception_type_name;
	runtime_exception_type.number_of_members = 1;
	result = internal_allocate_object(runtime_exception_type, 8);
	if (result == NULL)
	{
		return function_call_result_fail;
	}
	runtime_exception->members.members.Message.member_id = calculate_member_id("Message");
	runtime_exception->members.members.Message.value = internal_build_string_constant(exception_message);
	return function_call_result_success;
}

function_call_result minsharp_null_reference_exception(min_sharp_exception** new_exception, internal_string exception_message)
{
	return minsharp_runtime_exception(new_exception, runtime_exception_type_name, exception_message);
}
