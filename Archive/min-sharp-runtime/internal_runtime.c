#include "pch.h"
#include "internal_runtime.h"
#include "type_internals.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

// # Initialization externs
extern function_call_result minsharp_runtime_exception();
extern function_call_result initialize_types_repository();

void minsharp_init_runtime()
{
	if (minsharp_runtime_exception() != function_call_result_success)
	{
		abort();
	}
	if (initialize_types_repository() != function_call_result_success)
	{
		abort();
	}
}

// Allocates an internal object
min_sharp_object* internal_allocate_object(min_sharp_type_info typeinfo, int extra_data)
{
	min_sharp_object* result;
	int object_size = sizeof(min_sharp_object) + sizeof(min_sharp_object_member) * typeinfo.number_of_members + extra_data;
	result = malloc(object_size);
	if (NULL == runtime_exception)
	{
		return NULL;
	}
	result->objectInternals.object_flags = 0;
	result->objectInternals.allocated_memory = object_size;
	result->objectInternals.type_info = &typeinfo;
	memset(result->members, 0, sizeof(min_sharp_object_member) * typeinfo.number_of_members + extra_data);
}

typedef struct
{
	min_sharp_object_internals object_internals;
	min_sharp_boolean has_return_value;
	unsigned_int_16 number_of_parameters;
	min_sharp_object* captures;
	min_sharp_function_prototype function_code;
} min_sharp_function;

function_call_result fill_function_with_no_captures(min_sharp_function *function,
	min_sharp_boolean has_return_value, 
	unsigned_int_16 number_of_parameters,
	min_sharp_function_prototype function_code)
{
}

function_call_result min_sharp_internal_object_builder_factory(min_sharp_object** exception, min_sharp_internal_object_builder** internal_object_builder)
{
	min_sharp_internal_object_builder* result;
	result = malloc(sizeof(min_sharp_internal_object_builder));
	if (result == NULL)
	{
		goto exception_thrown;
	}
	result->build_string = NULL;

exception_thrown:
	*exception = runtime_exception;
	return function_call_result_fail;
}