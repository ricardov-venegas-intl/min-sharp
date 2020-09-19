#include "pch.h"
#include "internal_runtime.h"
#include "type_internals.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

min_sharp_type_info* system_types[8];

min_sharp_type_info* object_type_info;
min_sharp_type_info* string_type_info;
min_sharp_type_info* number_type_info;
min_sharp_type_info* boolean_type_info;
min_sharp_type_info* function_type_info;
min_sharp_type_info* exception_type_info;
min_sharp_type_info* runtime_exception_type_info;
min_sharp_type_info* null_reference_exception_type_info;

const internal_string object_type_name = "Object";
const internal_string string_type_name = "String";
const internal_string number_type_name = "Number";
const internal_string boolean_type_name = "Boolean";
const internal_string function_type_name = "Function";
const internal_string exception_type_name = "Exception";
const internal_string runtime_exception_type_name = "RuntimeException";
const internal_string null_reference_exception_type_name = "NullReferenceException";

const internal_string operator_add_name = "$OperatorAdd";
const internal_string property_message_name = "Message";

function_call_result initialize_types_repository()
{
	function_call_result call_result;

	// Add Object type info
	call_result = (&object_type_info, object_type_name, NULL, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}

	// Add String type info
	call_result = (&string_type_info, string_type_name, object_type_name, 1);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	string_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	string_type_info->members[0].member_name = operator_add_name;
	string_type_info->members[0].member_type = "String";

	// Add Number type info
	call_result = (&number_type_info, number_type_name, object_type_name, 1);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	number_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	number_type_info->members[0].member_name = operator_add_name;
	number_type_info->members[0].member_type = "String";

	// Add Boolean type info
	call_result = (&boolean_type_info, number_type_name, object_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}

	// Add Boolean type info
	call_result = (&function_type_info, function_type_name, object_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}

	// Exception
	call_result = (&exception_type_info, exception_type_name, object_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	exception_type_info->members[0].member_id = calculate_member_id(property_message_name);
	exception_type_info->members[0].member_name = property_message_name;
	exception_type_info->members[0].member_type = string_type_name;

	// Runtime Exception
	call_result = (&runtime_exception_type_info, runtime_exception_type_name, exception_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	runtime_exception_type_info->members[0].member_id = calculate_member_id(property_message_name);
	runtime_exception_type_info->members[0].member_name = property_message_name;
	runtime_exception_type_info->members[0].member_type = string_type_name;

	// Runtime Exception
	call_result = (&runtime_exception_type_info, runtime_exception_type_name, exception_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	runtime_exception_type_info->members[0].member_id = calculate_member_id(property_message_name);
	runtime_exception_type_info->members[0].member_name = property_message_name;
	runtime_exception_type_info->members[0].member_type = string_type_name;

	
	// Null Refernce Exception
	call_result = (&null_reference_exception_type_info, null_reference_exception_type_name, exception_type_name, 0);
	if (call_result != function_call_result_success)
	{
		return function_call_result_fail;
	}
	null_reference_exception_type_info->members[0].member_id = calculate_member_id(property_message_name);
	null_reference_exception_type_info->members[0].member_name = property_message_name;
	null_reference_exception_type_info->members[0].member_type = string_type_name;


	// Add the types to the "repository
	system_types[0] = object_type_info;
	system_types[1] = string_type_info;
	system_types[2] = number_type_info;
	system_types[3] = boolean_type_info;
	system_types[4] = function_type_info;
	system_types[5] = exception_type_info;
	system_types[6] = runtime_exception_type_info;
	system_types[7] = null_reference_exception_type_info;
}



function_call_result allocate_object_type(min_sharp_type_info** type_info, internal_string interface_name, internal_string parent_interface_name, unsigned_int_16 number_of_members)
{
	// Calculate size, min_sharp_type_infoalready contains 1 member
	int_32 type_info_size = sizeof(min_sharp_type_info) + sizeof(min_sharp_member_info) * (number_of_members - 1);
	min_sharp_type_info* result = (min_sharp_type_info*) malloc(type_info_size);
	if (NULL == result)
	{
		return function_call_result_fail;
	}

	memset(result, 0, type_info_size);
	result->number_of_members = number_of_members;
	result->interface_name = interface_name;
	result->parent_interface_name = parent_interface_name;
	return function_call_result_success;
}

//
// Gives a unique member id
// Replace with a atom table 
min_sharp_memberid calculate_member_id(internal_string member_name)
{
	min_sharp_memberid h = 525201411107845655ull;
	for (; *member_name; ++member_name) {
		h ^= *member_name;
		h *= 0x5bd1e9955bd1e995;
		h ^= h >> 47;
	}
	return h;
}

