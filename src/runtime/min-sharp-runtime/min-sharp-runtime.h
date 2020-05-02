// min-sharp-runtime.h : Include file for standard system include files,
// or project specific include files.

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
static const min_sharp_boolean min_sharp_true = 1;
static const min_sharp_boolean min_sharp_false = 0;
#define min_sharp_null ((void*) 0)

// standard return values & standard Function pointer
typedef unsigned_int_32 function_call_result;
#define function_call_result_success (0)
#define function_call_result_fail (-1)

// # MinSharp object definitions
typedef struct min_sharp_object_struct min_sharp_object;

typedef unsigned short object_flags;
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
} min_sharp_object_internals;

// Object member
typedef struct
{
	min_sharp_memberid member_id;
	min_sharp_object* value;
} min_sharp_object_member;

typedef struct min_sharp_interface_struct {
	min_sharp_type_info* type_info;
	min_sharp_object_member members[1];
} min_sharp_interface;


typedef struct min_sharp_object_struct {
	min_sharp_object_internals objectInternals;
	function_call_result (*__GetInterface)(min_sharp_object** exception, min_sharp_interface** result, internal_string interfaceName);
	min_sharp_interface interfaces[1];
} min_sharp_object;

typedef function_call_result(*min_sharp_function_prototype)(min_sharp_object** exception, min_sharp_object targetObject);
