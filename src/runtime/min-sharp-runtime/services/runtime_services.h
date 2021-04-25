#pragma once

#include "../min-sharp-runtime.h"

//Forward definitions.
typedef struct runtime_services_struct 
	runtime_services;
typedef struct runtime_services_data_struct 
	runtime_services_data;

typedef struct system_services_struct 
	system_services;
typedef struct managed_memory_services_struct 
	managed_memory_services;

typedef function_call_result(*type_initializer)(
	min_sharp_object* new_object, 
	void *initializer_data);


// Object definition
typedef struct runtime_services_struct
{
	// unmanaged_memory
	function_call_result (*allocate_unmanaged_memory)(
		runtime_services* this_instance, 
		void** result, 
		int size);
	function_call_result (*free_unmanaged_memory)(
		runtime_services* this_instance, 
		void* memory);

	// managed memory
	function_call_result (*push_scope)(
		runtime_services* this_instance, 
		unsigned_int_16 number_of_elements, 
		min_sharp_object* scope_variables[]);
	function_call_result (*pop_scope)(
		runtime_services* this_instance);
	function_call_result (*allocate_object)(
		runtime_services* this_instance, 
		min_sharp_object** new_object, 
		unsigned_int_16 internal_data_size);
	function_call_result (*collect_garbage)(
		runtime_services* this_instance);

	// runtime exeception
	function_call_result (*system_argument_exception)(
		runtime_services* this_instance, 
		min_sharp_object** returnedException, 
		internal_string argument_name);
	function_call_result (*system_argument_null_exception)(
		runtime_services* this_instance, 
		min_sharp_object** returnedException, 
		internal_string argument_name);
	function_call_result(*system_exception)(
		runtime_services* this_instance,
		min_sharp_object** returnedException,
		internal_string exception_code,
		internal_string exception_message);

	// strings
	function_call_result (*are_strings_equal_case_insentitive)(
		runtime_services* this_instance, 
		min_sharp_boolean* result, 
		internal_string string1, 
		internal_string string2, 
		unsigned_int_32 max_string_size);


	// Primitives
	function_call_result(*build_function)(
		runtime_services* runtime_services_instance,
		min_sharp_object** returned_exception,
		min_sharp_object** returned_result,
		min_sharp_object* function_captures,
		void* function_implementation);

	function_call_result (*build_number)(
		runtime_services* this_instance, 
		min_sharp_object** returned_exception,
		min_sharp_object** returned_result,
		float_64 value);

	function_call_result(*build_boolean)(
		runtime_services* this_instance,
		min_sharp_object** returned_exception,
		min_sharp_object** returned_result,
		min_sharp_boolean value);

	function_call_result(*build_string)(
		runtime_services* this_instance,
		min_sharp_object** returned_exception,
		min_sharp_object** returned_result,
		internal_string value);

	// Global data management
	function_call_result(*set_global_data)(runtime_services* runtime_services_instance, int data_id, void* data);
	function_call_result(*get_global_data)(runtime_services* runtime_services_instance, int data_id, void** data);

	// Lifetime management
	function_call_result(*release)(
		runtime_services* this_instance);
	
	// Intenal Data/State
	runtime_services_data* data;
} runtime_services;

extern function_call_result runtime_services_factory(
	system_services* system_services_instance, 
	managed_memory_services *managed_memory_services_instance, 
	runtime_services** result);
