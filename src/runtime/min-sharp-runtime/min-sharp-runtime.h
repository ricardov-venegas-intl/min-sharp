#pragma once

//
// Internal runtime intefaces.
//

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

// Object types
typedef unsigned_int_8 min_sharp_object_type;
static const min_sharp_object_type min_sharp_object_type_primitive_number = 1;
static const min_sharp_object_type min_sharp_object_type_primitive_string = 2;
static const min_sharp_object_type min_sharp_object_type_primitive_boolean = 4;
static const min_sharp_object_type min_sharp_object_type_primitive_datetime = 8;
static const min_sharp_object_type min_sharp_object_type_primitive_function = 16;
static const min_sharp_object_type min_sharp_object_type_object = 32;

// standard return values & standard Function pointer
typedef unsigned_int_32 function_call_result;
#define function_call_result_success (0)
#define function_call_result_fail (-1)

// MinSharp forward object definitions
typedef struct min_sharp_object_struct min_sharp_object;
typedef unsigned short object_flags;
typedef unsigned_int_64 min_sharp_memberid;
typedef struct min_sharp_object_struct min_sharp_object;
typedef struct runtime_iterator_struct runtime_iterator;
typedef struct min_sharp_interface_struct min_sharp_interface;
typedef struct runtime_services_struct runtime_services;

// Iterator
typedef struct runtime_iterator_data_struct runtime_iterator_data;
typedef struct runtime_iterator_struct
{
	function_call_result(*HasNext)(runtime_iterator* this_instance, min_sharp_boolean* hasNext);
	function_call_result(*Next)(runtime_iterator* this_instance, void** next);
	function_call_result(*Release)(runtime_iterator* this_instance);
	runtime_iterator_data* runtime_iterator_data;
} runtime_iterator;

typedef function_call_result(*runtime_iterator_function)(void* target, void* context);


// Esential interfaces
typedef struct min_sharp_interface_intrinsicts_struct
{
	function_call_result(*GetInterfaceName)(min_sharp_interface* this_instance, internal_string *interfaceName);
} min_sharp_interface_intrinsicts;

typedef struct min_sharp_object_intrinsicts_struct
{
	function_call_result(*get_interface)(min_sharp_object* this_instance, runtime_services* runtime, min_sharp_interface** result, internal_string interfaceName);
	function_call_result(*implements_interface)(min_sharp_object* this_instance, runtime_services* runtime,  min_sharp_boolean* result, internal_string interfaceName);
	function_call_result(*garbage_collection_get_flags)(min_sharp_object* this_instance, object_flags* objectFlag);
	function_call_result(*garbage_collection_set_flags)(min_sharp_object* this_instance, object_flags objectFlag);
	function_call_result(*iterate_referenced_objects)(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void *context);
	function_call_result(*get_object_type)(min_sharp_object* this_instance, min_sharp_object_type* object_type_result);
} min_sharp_object_intrinsicts;

typedef struct min_sharp_interface_struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	// other members here;
} min_sharp_interface;

typedef struct min_sharp_object_struct
{
	min_sharp_object_intrinsicts *object_intrinsicts;
} min_sharp_object;

// function definitions 

typedef struct min_sharp_function_struct min_sharp_function;


// Global Initializer
void intialize_runtime(runtime_services** runtime_services_instance);
