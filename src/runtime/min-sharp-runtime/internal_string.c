#include "pch.h"
#include "internal_runtime.h"
#include "type_internals.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

function_call_result operationAdd(min_sharp_exception** exception, min_sharp_string** result, min_sharp_string* left_operand, min_sharp_string* right_operand)
{
	if (NULL == left_operand || NULL == right_operand)
	{
		minsharp_null_reference_exception(exception, "Invalid Argument");
		return function_call_result_fail;
	}
	int_32 datasize = sizeof(string_data) + left_operand->data.length + right_operand->data.length +1;
	min_sharp_string* result = (min_sharp_string*)internal_allocate_object(string_type_info, datasize);

	return function_call_result_success;
}

min_sharp_string* internal_build_string_constant(internal_string value)
{
	if (NULL == value)
	{
		return NULL;
	}
	unsigned_int_32 string_length = strlen(value);
	min_sharp_string* result;
	unsigned_int_32 datasize = sizeof(string_data) + string_length; // message->data already has the end character
	min_sharp_string* message = (min_sharp_string*)internal_allocate_object(string_type_info, datasize);
	message->members.members.operation_add.member_id = calculate_member_id("_Operation_Add");
	message->members.members.operation_add.value = NULL; // To be replaced
	message->data.length = string_length;
	strcpy(message->data.value, value);
}

function_call_result build_string(min_sharp_object** exception, min_sharp_object** result, internal_string value)
{

}
