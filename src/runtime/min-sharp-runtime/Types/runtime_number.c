#include "runtime_number.h"
#include "min_sharp-runtime-support.h"
#include "../services/runtime_services.h"
#include "../services/internal/managed_memory_services.h"

#include "decNumber/decNumber.h"

static int const global_runtime_number_vtable_instance_id = 2013816853;

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
	decContext decimalNumberContext; // working context
	interface_map interface_map[number_of_interfaces];
	int vtable_signature;
} runtime_number_vtable;

typedef union vtable_or_object_intrinsicts_union
{
	min_sharp_object_intrinsicts object_intrinsicts;
	runtime_number_vtable vtable;
} vtable_or_object_intrinsicts;

typedef struct min_sharp_number_struct
{
	vtable_or_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	decNumber value;
} min_sharp_number;


static inline function_call_result get_vtable(
	min_sharp_object* this_instance, 
	runtime_number_vtable** result) {

	// object_intrinsictsis the first field on the runtime_number_vtable.
	// the interfaces are defined afterward, followed by the interface map.
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance = ((vtable_or_object_intrinsicts*)this_instance->object_intrinsicts);
	
	CRITICAL_ASSERT(vtable_or_object_intrinsicts_instance->vtable.vtable_signature == global_runtime_number_vtable_instance_id);

	*result = &(vtable_or_object_intrinsicts_instance->vtable);
	return function_call_result_success;
}

static function_call_result number_object_intrinsicts_get_interface(
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
	runtime_number_vtable* vtable;
	fcr = get_vtable(this_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Search the interface name using the value of teh pointers
	for (int i = 0; i < number_of_interfaces; i++)
	{
		if (interface_name == vtable->interface_map[i].interface_name)
		{
			*result = vtable->interface_map[i].interface;
			return function_call_result_success;
		}
	}

	// Search the interface using the value of the name.
	for (int i = 0; i < number_of_interfaces; i++)
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

static function_call_result number_object_intrinsicts_implements_interface(
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

static function_call_result number_object_intrinsicts_garbage_collection_get_flags(
	min_sharp_object* this_instance, 
	object_flags* object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	min_sharp_number* number_object = (min_sharp_number*)this_instance;
	*object_flag = number_object->object_flag;
	return function_call_result_success;
}

static function_call_result number_object_intrinsicts_garbage_collection_set_flags(
	min_sharp_object* this_instance, 
	object_flags object_flag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	min_sharp_number* number_object = (min_sharp_number*)this_instance;
	number_object->object_flag = object_flag;
	return function_call_result_success;
}

static function_call_result number_object_intrinsicts_iterate_referenced_objects(
	min_sharp_object* this_instance, 
	runtime_iterator_function iteration_function, 
	void* context)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != iteration_function);
	return function_call_result_success;
}

static function_call_result number_object_intrinsicts_get_object_type(
	min_sharp_object* this_instance, 
	min_sharp_object_type* object_type_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != object_type_result);

	*object_type_result = min_sharp_object_type_primitive_number;
	return function_call_result_success;
}

static function_call_result runtime_number_Runtime_AdditionOperator_Add_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
	)
{
	decContext* decimalNumberContext = min_sharp_null;
	
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

	// get vtable/decimalNumberContext
	function_call_result fcr;
	runtime_number_vtable* vtable;
	fcr = get_vtable(this_object_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// get decimalNumberContext
	decimalNumberContext = &(vtable->decimalNumberContext);

	// Calculate result
	min_sharp_number* this_number = (min_sharp_number*)this_object_instance;
	min_sharp_number* right_operand_number = (min_sharp_number*)right_operand;

	decNumber result_value;
	decNumberAdd(
		&result_value, 
		&(this_number->value), 
		&(right_operand_number->value), 
		decimalNumberContext);

	if (decimalNumberContext->status & DEC_Errors) 
	{
		goto fail;
	}

	// Create Number
	min_sharp_number* result_number;
	runtime_instance ->build_number(
		runtime_instance,
		returned_exception,
		(min_sharp_object**)&result_number,
		min_sharp_null);

	*returned_result = (min_sharp_object*) result_number;
	return function_call_result_success;

fail:
	{
		internal_string  exception_error_message = "Error perfoming number addition";
			if (min_sharp_null != decimalNumberContext &&
				decimalNumberContext->status & DEC_Errors)
			{
				decimalNumberContext->status &= DEC_Errors; // keep only errors 
				exception_error_message = decContextStatusToString(decimalNumberContext);
			}

			fcr = runtime_instance->system_exception(
				runtime_instance,
				returned_exception,
				"Runtime.Error",
				exception_error_message
			);

			VALIDATE_RETURNED_EXCEPTION();
	}
	return function_call_result_fail;
}


static function_call_result runtime_number_Runtime_AdditionOperator_Substraction_fn(
	runtime_services* runtime_instance,
	min_sharp_object* this_object_instance,
	min_sharp_function* this_function_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* right_operand
)
{
	decContext* decimalNumberContext = min_sharp_null;

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

	// get vtable/decimalNumberContext
	function_call_result fcr;
	runtime_number_vtable* vtable;
	fcr = get_vtable(this_object_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// get decimalNumberContext
	decimalNumberContext = &(vtable->decimalNumberContext);

	// Calculate result
	min_sharp_number* this_number = (min_sharp_number*)this_object_instance;
	min_sharp_number* right_operand_number = (min_sharp_number*)right_operand;

	decNumber result_value;
	decNumberSubtract(
		&result_value,
		&(this_number->value),
		&(right_operand_number->value),
		decimalNumberContext);

	if (decimalNumberContext->status & DEC_Errors)
	{
		goto fail;
	}

	// Create Number
	min_sharp_number* result_number;
	runtime_instance->build_number(
		runtime_instance,
		returned_exception,
		(min_sharp_object**)&result_number,
		min_sharp_null);

	*returned_result = (min_sharp_object*)result_number;
	return function_call_result_success;

fail:
	{
		internal_string  exception_error_message = "Error perfoming number addition";
		if (min_sharp_null != decimalNumberContext &&
			decimalNumberContext->status & DEC_Errors)
		{
			decimalNumberContext->status &= DEC_Errors; // keep only errors 
			exception_error_message = decContextStatusToString(decimalNumberContext);
		}

		fcr = runtime_instance->system_exception(
			runtime_instance,
			returned_exception,
			"Runtime.Error",
			exception_error_message
		);

		VALIDATE_RETURNED_EXCEPTION();
	}
	return function_call_result_fail;
}

static function_call_result runtime_number_Runtime_EqualityOperator_IsEquals_fn(
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

	function_call_result fcr;
	runtime_number_vtable* vtable;

	// get decimalNumberContext
	fcr = get_vtable(this_object_instance, &vtable);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	decContext* decimalNumberContext = &(vtable->decimalNumberContext);

	// Calculate result
	min_sharp_number* this_number = (min_sharp_number*)this_object_instance;
	min_sharp_number* right_operand_number = (min_sharp_number*)right_operand;

	// add the numbers
	decNumber result_value;

	decNumberCompareTotal(
		&result_value,
		&(this_number->value),
		&(right_operand_number->value),
		decimalNumberContext);
	
	if (decimalNumberContext->status & DEC_Errors)
	{
		goto fail;
	}
	min_sharp_boolean numbers_are_equal = (min_sharp_boolean)decNumberIsZero(&result_value);

	// Create Number
	min_sharp_boolean* result_boolean;
	runtime_instance->build_boolean(
		runtime_instance,
		returned_exception,
		(min_sharp_object**)&result_boolean,
		numbers_are_equal);

	*returned_result = (min_sharp_object*)result_boolean;
	return function_call_result_success;

fail:
	
	runtime_instance->system_exception(
		runtime_instance,
		returned_exception,
		"Runtime.Error",
		"Error Number Is Equal");

	VALIDATE_RETURNED_EXCEPTION();
	return function_call_result_fail;
}

function_call_result number_factory (
	runtime_services* runtime_services_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	internal_string value)
{
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);
	CRITICAL_ASSERT(min_sharp_null != returned_result);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);

	// Initialize result
	*returned_exception = min_sharp_null;
	*returned_result = min_sharp_null;

	function_call_result fcr;
	min_sharp_number *new_number;

	// Get vtable
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance;
	runtime_services_instance->get_global_data(
		runtime_services_instance,
		global_runtime_number_vtable_instance_id,
		&vtable_or_object_intrinsicts_instance);

	// Get decContext
	decContext* decimalNumberContext = &(vtable_or_object_intrinsicts_instance->vtable.decimalNumberContext);

	// Allocate
	fcr = runtime_services_instance->allocate_object(
		runtime_services_instance,
		(min_sharp_object**)&new_number,
		sizeof(min_sharp_number));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Initialize members
	new_number->object_intrinsicts = &(vtable_or_object_intrinsicts_instance->object_intrinsicts);
	new_number->object_flag = 0;
	if (min_sharp_null == value)
	{
		decNumberZero(&(new_number->value));
	}
	else
	{
		decNumberFromString(&(new_number->value), value, decimalNumberContext);
		if (decimalNumberContext->status & DEC_Errors)
		{
			goto fail;
		}
	}
	
	// Set result
	*returned_result = (min_sharp_object*)new_number;

	return function_call_result_success;

fail:
	runtime_services_instance->system_exception(
		runtime_services_instance,
		returned_exception,
		"Runtime.Error",
		"Error Building Number");
	VALIDATE_RETURNED_EXCEPTION();

	return function_call_result_fail;
}


function_call_result register_number_type(
	system_services* system_services_instance, 
	runtime_services* runtime_services_instance) {
	CRITICAL_ASSERT(min_sharp_null != system_services_instance);
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);

	runtime_number_vtable *runtime_number_vtable_instance;
	function_call_result fcr;
	min_sharp_object *exception;

	fcr = system_services_instance->allocate_memory(
		system_services_instance, &runtime_number_vtable_instance, 
		sizeof(runtime_number_vtable));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill signature
	runtime_number_vtable_instance->vtable_signature = global_runtime_number_vtable_instance_id;

	// Fill the vtable Add
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**) &(runtime_number_vtable_instance->runtime_AdditionOperator.Add),
		min_sharp_null,
		runtime_number_Runtime_AdditionOperator_Add_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the vtable Is Equals
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_number_vtable_instance->runtime_EqualityOperator.IsEquals),
		min_sharp_null,
		runtime_number_Runtime_EqualityOperator_IsEquals_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Fill the vtable Is Substract
	fcr = runtime_services_instance->build_function(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&(runtime_number_vtable_instance->runtime_SubstractionOperator.Substract),
		min_sharp_null,
		runtime_number_Runtime_AdditionOperator_Substraction_fn
	);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	
	// Fill the interface map
	runtime_number_vtable_instance->object_intrinsicts.get_interface = number_object_intrinsicts_get_interface;
	runtime_number_vtable_instance->object_intrinsicts.implements_interface = number_object_intrinsicts_implements_interface;
	runtime_number_vtable_instance->object_intrinsicts.garbage_collection_get_flags = number_object_intrinsicts_garbage_collection_get_flags;
	runtime_number_vtable_instance->object_intrinsicts.garbage_collection_set_flags = number_object_intrinsicts_garbage_collection_set_flags;
	runtime_number_vtable_instance->object_intrinsicts.iterate_referenced_objects = number_object_intrinsicts_iterate_referenced_objects;
	runtime_number_vtable_instance->object_intrinsicts.get_object_type = number_object_intrinsicts_get_object_type;

	runtime_number_vtable_instance->interface_map[0].interface_name = RUNTIME_ADDITION_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[0].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_AdditionOperator);
	runtime_number_vtable_instance->interface_map[1].interface_name = RUNTIME_SUBSTRACTION_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[1].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_SubstractionOperator);
	runtime_number_vtable_instance->interface_map[2].interface_name = RUNTIME_MULTIPLICATION_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[2].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_MultiplicationOperator);
	runtime_number_vtable_instance->interface_map[3].interface_name = RUNTIME_DIVISION_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[3].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_DivisionOperator);
	runtime_number_vtable_instance->interface_map[4].interface_name = RUNTIME_REMAINDER_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[4].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_RemainderOperator);
	runtime_number_vtable_instance->interface_map[5].interface_name = RUNTIME_EQUALITY_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[5].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_EqualityOperator);
	runtime_number_vtable_instance->interface_map[6].interface_name = RUNTIME_RELATIONAL_OPERATOR_INTERFACE_NAME;
	runtime_number_vtable_instance->interface_map[6].interface = (min_sharp_interface*)&(runtime_number_vtable_instance->runtime_RelationalOperator);

	// Initialize 	decimalNumberContext
	decContextDefault(
		&(runtime_number_vtable_instance->decimalNumberContext), 
		DEC_INIT_BASE); // initialize

	// Save the vtable
	vtable_or_object_intrinsicts* vtable_or_object_intrinsicts_instance = runtime_number_vtable_instance;
	runtime_services_instance->set_global_data(runtime_services_instance, global_runtime_number_vtable_instance_id, vtable_or_object_intrinsicts_instance);

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

