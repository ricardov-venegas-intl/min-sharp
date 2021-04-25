#pragma once
#include "min-sharp-runtime.h"
#include "services/runtime_services.h"

typedef function_call_result(*min_sharp_function_0_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result);

typedef function_call_result(*min_sharp_function_1_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1);

typedef function_call_result(*min_sharp_function_2_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2);

typedef function_call_result(*min_sharp_function_3_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3);

typedef function_call_result(*min_sharp_function_4_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3,
	min_sharp_object* argument4);

typedef function_call_result(*min_sharp_function_5_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3,
	min_sharp_object* argument4,
	min_sharp_object* argument5);

typedef function_call_result(*min_sharp_function_6_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3,
	min_sharp_object* argument4,
	min_sharp_object* argument5,
	min_sharp_object* argument6);


typedef function_call_result(*min_sharp_function_7_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3,
	min_sharp_object* argument4,
	min_sharp_object* argument5,
	min_sharp_object* argument6,
	min_sharp_object* argument7);

typedef function_call_result(*min_sharp_function_8_arguments)(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2,
	min_sharp_object* argument3,
	min_sharp_object* argument4,
	min_sharp_object* argument5,
	min_sharp_object* argument6,
	min_sharp_object* argument7,
	min_sharp_object* argument8);

typedef struct min_sharp_function_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	union {
		min_sharp_function_0_arguments function_0_arguments;
		min_sharp_function_1_arguments function_1_arguments;
		min_sharp_function_2_arguments function_2_arguments;
		min_sharp_function_3_arguments function_3_arguments;
		min_sharp_function_4_arguments function_4_arguments;
		min_sharp_function_5_arguments function_5_arguments;
		min_sharp_function_6_arguments function_6_arguments;
		min_sharp_function_7_arguments function_7_arguments;
		min_sharp_function_8_arguments function_8_arguments;
	} function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function;


// Auxiliary definitions for strong typed interfaces
typedef struct min_sharp_function_0_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_0_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_0_arguments_type;

typedef struct min_sharp_function_1_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_1_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_1_arguments_type;

typedef struct min_sharp_function_2_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_2_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_2_arguments_type;

typedef struct min_sharp_function_3_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_3_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_3_arguments_type;

typedef struct min_sharp_function_4_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_4_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_4_arguments_type;

typedef struct min_sharp_function_5_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_5_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_5_arguments_type;

typedef struct min_sharp_function_6_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_6_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_6_arguments_type;

typedef struct min_sharp_function_7_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_7_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_7_arguments_type;

typedef struct min_sharp_function_8_arguments_type_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	min_sharp_function_8_arguments function_implementation;
	min_sharp_object* function_captures;
} min_sharp_function_8_arguments_type;

