#include "runtime_boolean.h"
#include "min_sharp-runtime-support.h"
#include "../services/runtime_services.h"
#include "../services/internal/managed_memory_services.h"

static int const global_runtime_boolean_vtable_instance_id = 1686378447;

typedef struct interface_map_struct
{
	internal_string interface_name;
	min_sharp_interface* interface;
} interface_map;

#define boolean_of_interfaces 2

typedef struct runtime_boolean_vtable_struct
{
	min_sharp_object_intrinsicts object_intrinsicts;
	Runtime_EqualityOperator runtime_EqualityOperator;
	Runtime_BooleanOperator runtime_BooleanOperator;

	interface_map interface_map[boolean_of_interfaces];
	min_sharp_object* runtime_boolean_false;
	min_sharp_object* runtime_boolean_true;
	int vtable_signature;
} runtime_boolean_vtable;

typedef union vtable_or_object_intrinsicts_union
{
	min_sharp_object_intrinsicts object_intrinsicts;
	runtime_boolean_vtable vtable;
} vtable_or_object_intrinsicts;

typedef struct runtime_boolean_struct
{
	vtable_or_object_intrinsicts* object_intrinsicts;
	min_sharp_boolean value;
} runtime_boolean;


static inline function_call_result get_vtable(
	min_sharp_object* this_instance,
	runtime_boolean_vtable** result) {

	// object_intrinsictsis the first field on the runtime_number_vtable.
	// the interfaces are defined afterward, followed by the interface map.
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance = ((vtable_or_object_intrinsicts*)this_instance->object_intrinsicts);

	CRITICAL_ASSERT(vtable_or_object_intrinsicts_instance->vtable.vtable_signature == global_runtime_boolean_vtable_instance_id);

	*result = &(vtable_or_object_intrinsicts_instance->vtable);
	return function_call_result_success;
}

static function_call_result boolean_object_intrinsicts_get_interface(
	min_sharp_object* this_instance,
	runtime_services* runtime,
	min_sharp_interface** result,
	internal_string interface_name)
{
	function_call_result fcr;

	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result);
	CRITICAL_ASSERT(min_sharp_null != interface_name);

	// Initialize result
	*result = min_sharp_null;

	// Get vtable
	runtime_boolean_vtable* vtable;
	fcr = get_vtable(this_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Search the interface name using the value of teh pointers
	for (int i = 0; i < boolean_of_interfaces; i++)
	{
		if (interface_name == vtable->interface_map[i].interface_name)
		{
			*result = vtable->interface_map[i].interface;
			return function_call_result_success;
		}
	}

	// Search the interface using the value of the name.
	for (int i = 0; i < boolean_of_interfaces; i++)
	{
		min_sharp_boolean are_interface_names_equal;

		fcr = runtime->are_strings_equal_case_insentitive(
			runtime,
			&are_interface_names_equal,
			vtable->interface_map[i].interface_name,
			interface_name,
			sizeof(vtable->interface_map[i].interface_name));
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}

		if (min_sharp_true == are_interface_names_equal)
		{
			*result = vtable->interface_map[i].interface;
			return function_call_result_success;
		}
	}

fail:
	return function_call_result_fail;
}

static function_call_result boolean_object_intrinsicts_implements_interface(
	min_sharp_object* this_instance,
	runtime_services* runtime,
	min_sharp_boolean* result,
	internal_string interface_name)
{
	function_call_result fcr;
	CRITICAL_ASSERT(min_sharp_null != runtime);
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result);
	CRITICAL_ASSERT(min_sharp_null != interface_name);

	runtime_boolean_vtable* vtable = (runtime_boolean_vtable*)this_instance->object_intrinsicts;

	for (int i = 0; i < boolean_of_interfaces; i++)
	{
		if (interface_name == vtable->interface_map[0].interface_name)
		{
			*result = min_sharp_true;
			return function_call_result_success;
		}
	}

	for (int i = 0; i < boolean_of_interfaces; i++)
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


static function_call_result boolean_object_intrinsicts_garbage_collection_get_flags(
	min_sharp_object* this_instance,
	object_flags* object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	runtime_boolean* boolean_object = (runtime_boolean*)this_instance;
	// Always return system
	*object_flag = garbage_collection_flags_system;
	return function_call_result_success;
}

static function_call_result boolean_object_intrinsicts_garbage_collection_set_flags(
	min_sharp_object* this_instance,
	object_flags object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	runtime_boolean* boolean_object = (runtime_boolean*)this_instance;
	return function_call_result_success;
}

static function_call_result boolean_object_intrinsicts_iterate_referenced_objects(
	min_sharp_object* this_instance,
	runtime_iterator_function iteration_function,
	void* context)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != iteration_function);
	return function_call_result_success;
}

static function_call_result boolean_object_intrinsicts_get_object_type(
	min_sharp_object* this_instance,
	min_sharp_object_type* object_type_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != object_type_result);

	*object_type_result = min_sharp_object_type_primitive_number;
	return function_call_result_success;
}

static function_call_result runtime_boolean_Runtime_EqualityOperator_IsEquals_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
)
{
	CRITICAL_ASSERT(min_sharp_null != runtime_instance);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);

	VALIDATE_ARGUMENT_NOTNULL(runtime_instance, this_function_instance, "this_function");
	VALIDATE_ARGUMENT_NOTNULL(runtime_instance, returned_result, "returned_result");
	VALIDATE_ARGUMENT_NOTNULL(runtime_instance, right_operand, "rightOperand");
	VALIDATE_ARGUMENT_NOTNULL(runtime_instance, right_operand->object_intrinsicts, "rightOperand.object_intrinsicts");
	VALIDATE_ARGUMENT_NOTNULL(runtime_instance, right_operand->object_intrinsicts->get_object_type, "rightOperand.object_intrinsicts.GetObjectType");
	VALIDATE_ARGUMENT_TYPE(runtime_instance, right_operand, min_sharp_object_type_primitive_number, "rightOperand type");

	// Initialize returns
	*returned_exception = min_sharp_null;
	*returned_result = min_sharp_null;

	// Compare
	runtime_boolean* left_value = (runtime_boolean*)this_object_instance;
	runtime_boolean* right_value = (runtime_boolean*)right_operand;

	// Get vtable
	function_call_result fcr;
	runtime_boolean_vtable* vtable;
	fcr = get_vtable(this_object_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	CRITICAL_ASSERT(min_sharp_null != vtable->runtime_boolean_true != min_sharp_null);
	CRITICAL_ASSERT(min_sharp_null != vtable->runtime_boolean_false != min_sharp_null);

	if (left_value->value == right_value->value)
	{
		*returned_result = vtable->runtime_boolean_true;
	}
	else
	{
		*returned_result = vtable->runtime_boolean_false;
	}

	return function_call_result_success;

fail:
	{
		function_call_result fcr;
		fcr = runtime_instance->system_exception(
			runtime_instance,
			returned_exception,
			"Runtime.Error",
			"Error in Boolean:Runtime.EqualityOperator.IsEquals"
		);

		VALIDATE_RETURNED_EXCEPTION();
	}
	return function_call_result_fail;
}

static function_call_result runtime_boolean_Runtime_BooleanOperator_And_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
)
{
	return function_call_result_fail;
}

static function_call_result runtime_boolean_Runtime_BooleanOperator_Or_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
)
{
	return function_call_result_fail;
}


static function_call_result runtime_boolean_Runtime_BooleanOperator_Not_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
)
{
	return function_call_result_fail;
}

function_call_result initialize_boolean_instance(
	runtime_services* runtime_services_instance,
	runtime_boolean_vtable* runtime_boolean_vtable_instance,
	min_sharp_boolean value) 
{

	function_call_result fcr;
	runtime_boolean* new_boolean;

	// If value is true and allocated, return true if allocated
	if (min_sharp_true == value
		&& runtime_boolean_vtable_instance->runtime_boolean_true != min_sharp_null)
	{
		return function_call_result_success;
	}

	// If value is false and allocated, return false if allocated
	if (min_sharp_false == value
		&& runtime_boolean_vtable_instance->runtime_boolean_false != min_sharp_null)
	{
		return function_call_result_success;
	}

	// Allocate
	fcr = runtime_services_instance->allocate_object(
		runtime_services_instance,
		(runtime_boolean**)&new_boolean,
		sizeof(runtime_boolean));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Initialize members
	new_boolean->object_intrinsicts = &(runtime_boolean_vtable_instance->object_intrinsicts);
	new_boolean->value = value;


	// Save allocation for later
	if (min_sharp_true == value)
	{
		runtime_boolean_vtable_instance->runtime_boolean_true = new_boolean;
	}
	else
	{
		runtime_boolean_vtable_instance->runtime_boolean_false = new_boolean;
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

function_call_result boolean_factory(
	runtime_services* runtime_services_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_boolean value)
{
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);
	CRITICAL_ASSERT(min_sharp_null != returned_result);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);

	// Initialize result
	*returned_exception = min_sharp_null;
	*returned_result = min_sharp_null;

	function_call_result fcr;
	runtime_boolean* new_boolean;

	// Get vtable
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance;
	runtime_services_instance->get_global_data(
		runtime_services_instance,
		global_runtime_boolean_vtable_instance_id,
		&vtable_or_object_intrinsicts_instance);

	CRITICAL_ASSERT(min_sharp_null != vtable_or_object_intrinsicts_instance->vtable.runtime_boolean_true != min_sharp_null);
	CRITICAL_ASSERT(min_sharp_null != vtable_or_object_intrinsicts_instance->vtable.runtime_boolean_false != min_sharp_null);

	// If value is true and allocated, return true if allocated
	if (min_sharp_true == value)
	{
		*returned_result = vtable_or_object_intrinsicts_instance->vtable.runtime_boolean_true;
		return function_call_result_success;
	}

	// If value is false and allocated, return false if allocated
	if (min_sharp_false == value)
	{
		*returned_result = vtable_or_object_intrinsicts_instance->vtable.runtime_boolean_false;
		return function_call_result_success;
	}
	
	// It was not true or false
	goto fail;

fail:
	runtime_services_instance->system_exception(
		runtime_services_instance,
		returned_exception,
		"Runtime.Error",
		"Error Building Number");
	VALIDATE_RETURNED_EXCEPTION();

	return function_call_result_fail;
}

function_call_result register_boolean_type(
	system_services* system_services_instance,
	runtime_services* runtime_services_instance) 
{
	CRITICAL_ASSERT(min_sharp_null != system_services_instance);
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);

	runtime_boolean_vtable* runtime_boolean_vtable_instance;
	function_call_result fcr;
	min_sharp_object* exception;

	fcr = system_services_instance->allocate_memory(
		system_services_instance, 
		&runtime_boolean_vtable_instance,
		sizeof(runtime_boolean_vtable));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill signature
	runtime_boolean_vtable_instance->vtable_signature = global_runtime_boolean_vtable_instance_id;

	// Fill the vtable EqualityOperator.IsEquals
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_boolean_vtable_instance->runtime_EqualityOperator.IsEquals),
		min_sharp_null,
		runtime_boolean_Runtime_EqualityOperator_IsEquals_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the vtable BooleanOperator.And
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_boolean_vtable_instance->runtime_BooleanOperator.And),
		min_sharp_null,
		runtime_boolean_Runtime_BooleanOperator_And_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the vtable BooleanOperator.Or
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_boolean_vtable_instance->runtime_BooleanOperator.Or),
		min_sharp_null,
		runtime_boolean_Runtime_BooleanOperator_Or_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the vtable BooleanOperator.Not
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_boolean_vtable_instance->runtime_BooleanOperator.Not),
		min_sharp_null,
		runtime_boolean_Runtime_BooleanOperator_Not_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the interface map
	runtime_boolean_vtable_instance->object_intrinsicts.get_interface = boolean_object_intrinsicts_get_interface;
	runtime_boolean_vtable_instance->object_intrinsicts.implements_interface = boolean_object_intrinsicts_implements_interface;
	runtime_boolean_vtable_instance->object_intrinsicts.garbage_collection_get_flags = boolean_object_intrinsicts_garbage_collection_get_flags;
	runtime_boolean_vtable_instance->object_intrinsicts.garbage_collection_set_flags = boolean_object_intrinsicts_garbage_collection_set_flags;
	runtime_boolean_vtable_instance->object_intrinsicts.iterate_referenced_objects = boolean_object_intrinsicts_iterate_referenced_objects;
	runtime_boolean_vtable_instance->object_intrinsicts.get_object_type = boolean_object_intrinsicts_get_object_type;

	runtime_boolean_vtable_instance->interface_map[0].interface_name = RUNTIME_EQUALITY_OPERATOR_INTERFACE_NAME;
	runtime_boolean_vtable_instance->interface_map[0].interface = (min_sharp_interface*)&(runtime_boolean_vtable_instance->runtime_EqualityOperator);
	runtime_boolean_vtable_instance->interface_map[1].interface_name = RUNTIME_BOOLEAN_OPERATOR_INTERFACE_NAME;
	runtime_boolean_vtable_instance->interface_map[1].interface = (min_sharp_interface*)&(runtime_boolean_vtable_instance->runtime_BooleanOperator);

	// Save the vtable
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance = runtime_boolean_vtable_instance;
	runtime_services_instance->set_global_data(
		runtime_services_instance, 
		global_runtime_boolean_vtable_instance_id, 
		vtable_or_object_intrinsicts_instance);

	// Initialize True and False
	fcr = initialize_boolean_instance(
		runtime_services_instance,
		runtime_boolean_vtable_instance,
		min_sharp_false);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	fcr = initialize_boolean_instance(
		runtime_services_instance,
		runtime_boolean_vtable_instance,
		min_sharp_true);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Return result
	return function_call_result_success;

fail:
	return function_call_result_fail;
}