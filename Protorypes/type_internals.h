#pragma once
#include "min-sharp-runtime.h"

static const object_flags new_object = 0;
static const object_flags constant_object = 4;


// Function instance object
typedef struct
{
	min_sharp_boolean has_return_value;
	unsigned_int_16 number_of_parameters;
	min_sharp_object* captures;
	min_sharp_function_prototype function_code;
} min_sharp_function;


typedef struct
{
	int length;
	char value[1];
} string_data;

// String Value object
typedef struct {
	union
	{
		min_sharp_object_member members_array[1];
		struct  
		{
			min_sharp_object_member operation_add;
		} members;
	} members;
	string_data data;
} min_sharp_string;

// Number value object
typedef struct {
	min_sharp_object_member members[1];
	struct
	{
		double value;
	} data;
} min_sharp_number;

// boolean value object
typedef struct min_sharp_boolean_struct {
	min_sharp_object_member members[1];
	struct
	{
		int value;
	} data;
} min_sharp_boolean_object;

typedef struct {
	union
	{
		min_sharp_object_member members_array[1];
		struct 
		{
			min_sharp_object_member Message;
		} members;
	} members;
} min_sharp_exception;

typedef struct {
	function_call_result(*build_string)(min_sharp_object** exception, min_sharp_object **result, internal_string value);
	function_call_result(*build_number)(min_sharp_object** exception, min_sharp_object** result, double value);
	function_call_result(*build_boolean)(min_sharp_object** exception, min_sharp_object** result, min_sharp_boolean value);
	function_call_result(*build_object)(min_sharp_object** exception, min_sharp_object** result, int number_of_members);
	function_call_result(*build_function)(min_sharp_object** exception, min_sharp_object** result, int has_return_value, int number_of_members, min_sharp_object* captures, min_sharp_function_prototype function);
} min_sharp_internal_object_builder;

