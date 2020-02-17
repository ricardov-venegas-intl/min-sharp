#pragma once

// # Standard types
typedef long int_64;
typedef int int_32;
typedef short int_16;
typedef char int_8;
typedef unsigned long unsigned_int_64;
typedef unsigned int unsigned_int_32;
typedef unsigned short unsigned_int_16;
typedef unsigned char unsigned_int_8;
typedef const char* internal_string;
typedef unsigned char min_sharp_boolean;
const min_sharp_boolean min_sharp_true = 1;
const min_sharp_boolean min_sharp_false = 0;

// # MinSharp object definitions
typedef struct __min_sharp_object min_sharp_object;
typedef unsigned short object_flags;
const object_flags new_object = 0;
const object_flags constant_object = 4;
typedef unsigned_int_64 min_sharp_memberid;

// member info
typedef struct
{
	min_sharp_memberid member_id;
	internal_string member_name;
	internal_string member_type;
} min_sharp_member_info;

// type info
typedef struct
{
	unsigned_int_16 number_of_members;
	internal_string interface_name;
	internal_string parent_interface_name;
	min_sharp_member_info members[1];
} min_sharp_type_info;

// min_sharp_object_internals: Used for garbage collection, allocation, and reflection.
// It if the first member on all object
typedef struct 
{
	unsigned_int_16 object_flags;
	unsigned_int_16 allocated_memory;
	min_sharp_type_info* type_info;
} min_sharp_object_internals;

// standard return values & standard Function pointer
typedef unsigned_int_32 function_call_result;
const int function_call_result_success = 0;
const int function_call_result_fail = 0xF0F0;
typedef function_call_result(*min_sharp_function_prototype)(min_sharp_object** exception);

// Function instance object
typedef struct
{
	min_sharp_object_internals object_internals;
	min_sharp_boolean has_return_value;
	unsigned_int_16 number_of_parameters;
	min_sharp_object* captures;
	min_sharp_function_prototype function_code;
} min_sharp_function;

// Object member
typedef struct
{
	min_sharp_memberid member_id;
	min_sharp_object* value;
} min_sharp_object_member;

typedef struct {
	min_sharp_object_internals objectInternals;
	min_sharp_object_member members[1];
} min_sharp_object;

typedef struct
{
	int length;
	char value[1];
} string_data;

// String Value object
typedef struct {
	min_sharp_object_internals object_internals;
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
	min_sharp_object_internals object_internals;
	min_sharp_object_member members[1];
	struct
	{
		double value;
	} data;
} min_sharp_number;

// boolean value object
typedef struct {
	min_sharp_object_internals object_internals;
	min_sharp_object_member members[1];
	struct
	{
		int value;
	} data;
} min_sharp_boolean;

typedef struct {
	min_sharp_object_internals object_internals;
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
	function_call_result(*build_boolean)(min_sharp_object** exception, min_sharp_object** result, int value);
	function_call_result(*build_object)(min_sharp_object** exception, min_sharp_object** result, int number_of_members);
	function_call_result(*build_function)(min_sharp_object** exception, min_sharp_object** result, int has_return_value, int number_of_members, min_sharp_object* captures, min_sharp_function_prototype function);
} min_sharp_internal_object_builder;

