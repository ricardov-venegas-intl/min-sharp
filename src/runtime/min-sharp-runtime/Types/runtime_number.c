#include "runtime_number.h"
#include "min_sharp-runtime-support.h"
#include "../services/runtime_services.h"

typedef struct min_sharp_number_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags objectFlag;
	double value;
} min_sharp_number;


typedef struct runtime_number_vtable_struct
{
	min_sharp_object_intrinsicts object_intrinsicts;
	Runtime_AdditionOperator runtime_AdditionOperator;
	Runtime_SubstractionOperator runtime_SubstractionOperator;
	Runtime_MultiplicationOperator runtime_MultiplicationOperator;
	Runtime_DivisionOperator runtime_DivisionOperator;
	Runtime_RemainderOperator runtime_RemainderOperator;
	Runtime_EqualityOperator runtime_EqualityOperator;
	Runtime_RelationalOperator runtime_RelationalOperator;
} runtime_number_vtable;

function_call_result number_object_intrinsicts_get_interface(min_sharp_object* this_instance, runtime_services* runtime, min_sharp_interface** result, internal_string interface_name)
{
	function_call_result fcr;
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result);
	CRITICAL_ASSERT(min_sharp_null != interface_name);

	runtime_number_vtable* vtable = (runtime_number_vtable*)this_instance->object_intrinsicts;

	// compare first interface name as a pointer
	if (runtime_additionoperator_interface_name == interface_name)
	{
		*result = (min_sharp_interface*) &vtable->runtime_AdditionOperator;
		return function_call_result_success;
	}
	else if (runtime_substraction_operator_interface_name == interface_name)
	{
		*result = (min_sharp_interface*)&vtable->runtime_SubstractionOperator;
		return function_call_result_success;
	}
	else if (runtime_multiplication_operator_interface_name == interface_name)
	{
		*result = (min_sharp_interface*)&vtable->runtime_MultiplicationOperator;
		return function_call_result_success;
	}
	
	

	// Compare first interface name as a string
	min_sharp_boolean are_interface_names_equal;

	fcr = runtime->are_strings_equal_case_insentitive(
		runtime, 
		&are_interface_names_equal,
		runtime_additionoperator_interface_name,
		interface_name,
		sizeof(runtime_additionoperator_interface_name));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	if (min_sharp_true == are_interface_names_equal)
	{
		*result = (min_sharp_interface*)&vtable->runtime_AdditionOperator;
		return function_call_result_success;
	}

	fcr = runtime->are_strings_equal_case_insentitive(
		runtime,
		&are_interface_names_equal,
		runtime_substraction_operator_interface_name,
		interface_name,
		sizeof(runtime_substraction_operator_interface_name));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	if (min_sharp_true == are_interface_names_equal)
	{
		*result = (min_sharp_interface*)&vtable->runtime_SubstractionOperator;
		return function_call_result_success;
	}

	fcr = runtime->are_strings_equal_case_insentitive(
		runtime,
		&are_interface_names_equal,
		runtime_multiplication_operator_interface_name,
		interface_name,
		sizeof(runtime_multiplication_operator_interface_name));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	if (min_sharp_true == are_interface_names_equal)
	{
		*result = (min_sharp_interface*)&vtable->runtime_MultiplicationOperator;
		return function_call_result_success;
	}
fail:
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_implements_interface(min_sharp_object* this_instance, min_sharp_boolean* result, internal_string interfaceName)
{
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_garbage_collection_get_flags(min_sharp_object* this_instance, object_flags* objectFlag)
{
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_garbage_collection_set_flags(min_sharp_object* this_instance, object_flags objectFlag)
{
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_iterate_referenced_objects(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void* context)
{
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_get_object_type(min_sharp_object* this_instance, min_sharp_object_type* object_type_result)
{
	return function_call_result_fail;
}



static function_call_result runtime_number_Runtime_AdditionOperator_add_fn(
	min_sharp_function* this_function,
	runtime_services* runtime,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* argument1,
	min_sharp_object* argument2)
{
	function_call_result fcr;
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);

	VALIDATE_ARGUMENT_NOTNULL(this_function, "this_function");
	VALIDATE_ARGUMENT_NOTNULL(returned_result, "returned_result");
	VALIDATE_ARGUMENT_NOTNULL(argument1, "argument1");
	VALIDATE_ARGUMENT_NOTNULL(argument1->object_intrinsicts, "argument1.object_intrinsicts");
	VALIDATE_ARGUMENT_NOTNULL(argument1->object_intrinsicts->get_object_type, "argument1.object_intrinsicts.GetObjectType");
	VALIDATE_ARGUMENT_NOTNULL(argument2, "argument2");
	VALIDATE_ARGUMENT_NOTNULL(argument2->object_intrinsicts, "argument2.object_intrinsicts");
	VALIDATE_ARGUMENT_NOTNULL(argument2->object_intrinsicts->get_object_type, "argument2.object_intrinsicts.GetObjectType");

	VALIDATE_ARGUMENT_TYPE(argument1, min_sharp_object_type_primitive_number, "argument1");
	VALIDATE_ARGUMENT_TYPE(argument2, min_sharp_object_type_primitive_number, "argument2");

	min_sharp_number* argument1_number = (min_sharp_number*)argument1;
	min_sharp_number* argument2_number = (min_sharp_number*)argument2;
	return function_call_result_success;

fail:
	VALIDATE_RETURNED_EXCEPTION();
	return function_call_result_fail;
}

static function_call_result runtime_number_factory_release(runtime_number_factory* this_instance, runtime_services* runtime)
{
	return function_call_result_fail;
}

function_call_result runtime_number_factory_initializer(runtime_services *runtime_services, runtime_number_factory ** min_sharp_number_factory_result)
{
	CRITICAL_ASSERT(min_sharp_null != runtime_services);
	CRITICAL_ASSERT(min_sharp_null != min_sharp_number_factory_result);

	runtime_number_vtable* runtime_number_vtable;
	runtime_services->allocate_unmanaged_memory(runtime_services, &runtime_number_vtable, sizeof(runtime_number_vtable));
	runtime_number_vtable->object_intrinsicts.get_interface = number_object_intrinsicts_get_interface;
	runtime_number_vtable->object_intrinsicts.implements_interface = number_object_intrinsicts_implements_interface;
	runtime_number_vtable->object_intrinsicts.garbage_collection_get_flags = number_object_intrinsicts_garbage_collection_get_flags;
	runtime_number_vtable->object_intrinsicts.garbage_collection_set_flags = number_object_intrinsicts_garbage_collection_set_flags;
	runtime_number_vtable->object_intrinsicts.iterate_referenced_objects = number_object_intrinsicts_iterate_referenced_objects;
	runtime_number_vtable->object_intrinsicts.get_object_type = number_object_intrinsicts_get_object_type;


	runtime_number_factory* runtime_number_factory;	
	runtime_services->allocate_unmanaged_memory(runtime_services, &runtime_number_factory, sizeof(runtime_number_factory));
	runtime_number_factory->release = runtime_number_factory_release;
	runtime_number_factory->build_number = min_sharp_null;
	runtime_number_factory->numbers_vtable = runtime_number_vtable;

	return function_call_result_fail;
}