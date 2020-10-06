#include "runtime_number.h"
#include "min_sharp-runtime-support.h"
#include "../services/runtime_services.h"

typedef struct min_sharp_number_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	double value;
} min_sharp_number;

typedef struct interface_map_struct
{
	internal_string interface_name;
	min_sharp_interface* interface;
} interface_map;

#define number_of_interfaces 7

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
	interface_map interface_map[number_of_interfaces];
} runtime_number_vtable;



function_call_result number_object_intrinsicts_get_interface(min_sharp_object* this_instance, runtime_services* runtime, min_sharp_interface** result, internal_string interface_name)
{
	function_call_result fcr;
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result);
	CRITICAL_ASSERT(min_sharp_null != interface_name);

	runtime_number_vtable* vtable = (runtime_number_vtable*)this_instance->object_intrinsicts;

	for (int i = 0; i < number_of_interfaces; i++)
	{
		if (interface_name == vtable->interface_map[0].interface_name)
		{
			*result = vtable->interface_map[0].interface;
			return function_call_result_success;
		}
	}

	for (int i = 0; i < number_of_interfaces; i++)
	{
		min_sharp_boolean are_interface_names_equal;

		fcr = runtime->are_strings_equal_case_insentitive(
			runtime,
			&are_interface_names_equal,
			vtable->interface_map[0].interface_name,
			interface_name,
			sizeof(vtable->interface_map[0].interface_name));
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
		if (min_sharp_true == are_interface_names_equal)
		{
			*result = vtable->interface_map[0].interface;
			return function_call_result_success;
		}
	}	

fail:
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_implements_interface(min_sharp_object* this_instance, runtime_services* runtime, min_sharp_boolean* result, internal_string interface_name)
{
	function_call_result fcr;
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result);
	CRITICAL_ASSERT(min_sharp_null != interface_name);

	runtime_number_vtable* vtable = (runtime_number_vtable*)this_instance->object_intrinsicts;

	for (int i = 0; i < number_of_interfaces; i++)
	{
		if (interface_name == vtable->interface_map[0].interface_name)
		{
			*result = min_sharp_true;
			return function_call_result_success;
		}
	}

	for (int i = 0; i < number_of_interfaces; i++)
	{
		min_sharp_boolean are_interface_names_equal;

		fcr = runtime->are_strings_equal_case_insentitive(
			runtime,
			&are_interface_names_equal,
			vtable->interface_map[0].interface_name,
			interface_name,
			sizeof(vtable->interface_map[0].interface_name));
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
		if (min_sharp_true == are_interface_names_equal)
		{
			*result = min_sharp_true;
			return function_call_result_success;
		}
	}

	*result = min_sharp_false;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

function_call_result number_object_intrinsicts_garbage_collection_get_flags(min_sharp_object* this_instance, object_flags* object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	min_sharp_number* number_object = (min_sharp_number*)this_instance;
	*object_flag = number_object->object_flag;
	return function_call_result_success;
}

function_call_result number_object_intrinsicts_garbage_collection_set_flags(min_sharp_object* this_instance, object_flags object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	min_sharp_number* number_object = (min_sharp_number*)this_instance;
	number_object->object_flag = object_flag;
	return function_call_result_success;
}

function_call_result number_object_intrinsicts_iterate_referenced_objects(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void* context)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != iteration_function);
	return function_call_result_success;
}

function_call_result number_object_intrinsicts_get_object_type(min_sharp_object* this_instance, min_sharp_object_type* object_type_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	*object_type_result = min_sharp_object_type_primitive_number;
	return function_call_result_success;
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
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	runtime->free_unmanaged_memory(runtime, this_instance->numbers_vtable);
	runtime->free_unmanaged_memory(runtime, this_instance);

	return function_call_result_success;
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

	runtime_number_vtable->interface_map[0].interface_name = runtime_additionoperator_interface_name;
	runtime_number_vtable->interface_map[0].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_AdditionOperator);
	runtime_number_vtable->interface_map[1].interface_name = runtime_substraction_operator_interface_name;
	runtime_number_vtable->interface_map[1].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_SubstractionOperator);
	runtime_number_vtable->interface_map[2].interface_name = runtime_multiplication_operator_interface_name;
	runtime_number_vtable->interface_map[2].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_MultiplicationOperator);
	runtime_number_vtable->interface_map[3].interface_name = runtime_division_operator_interface_name;
	runtime_number_vtable->interface_map[3].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_DivisionOperator);
	runtime_number_vtable->interface_map[4].interface_name = runtime_remainder_operator_interface_name;
	runtime_number_vtable->interface_map[4].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_RemainderOperator);
	runtime_number_vtable->interface_map[5].interface_name = runtime_equality_operator_interface_name;
	runtime_number_vtable->interface_map[5].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_EqualityOperator);
	runtime_number_vtable->interface_map[6].interface_name = runtime__relational_operator_interface_name;
	runtime_number_vtable->interface_map[6].interface = (min_sharp_interface*)&(runtime_number_vtable->runtime_RelationalOperator);

	runtime_number_factory* runtime_number_factory;	
	runtime_services->allocate_unmanaged_memory(runtime_services, &runtime_number_factory, sizeof(runtime_number_factory));
	runtime_number_factory->release = runtime_number_factory_release;
	runtime_number_factory->build_number = min_sharp_null;
	runtime_number_factory->numbers_vtable = runtime_number_vtable;

	return function_call_result_fail;
}