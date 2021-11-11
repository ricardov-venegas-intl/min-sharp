#include "min-sharp-runtime.h"
#include "min_sharp-runtime-support.h"
#include "services/internal/system_unmanaged_data_manager.h"

#include "../min-sharp-runtime-function-prototypes.h"

static int const global_function_object_intrinsicts_id = 766624544;

static function_call_result function_get_interface(
	min_sharp_object* this_instance, 
	runtime_services* runtime, 
	min_sharp_interface** result, 
	internal_string interfaceName)
{
	return function_call_result_fail;
}

static function_call_result function_implements_interface(
	min_sharp_object* this_instance, 
	runtime_services* runtime, 
	min_sharp_boolean* result, 
	internal_string interfaceName)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != result)

	*result = min_sharp_false;
	return function_call_result_success;
}

static function_call_result function_garbage_collection_get_flags(min_sharp_object* this_instance, object_flags* objectFlag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != objectFlag);

	min_sharp_function* min_sharp_function_instance = (min_sharp_function*)this_instance;
	*objectFlag = min_sharp_function_instance->object_flag;
	return function_call_result_success;
}

static function_call_result function_garbage_collection_set_flags(min_sharp_object* this_instance, object_flags objectFlag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	min_sharp_function* min_sharp_function_instance = (min_sharp_function*)this_instance;
	min_sharp_function_instance->object_flag = objectFlag;
	return function_call_result_success;
}

static function_call_result function_iterate_referenced_objects(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void* context)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	min_sharp_function* min_sharp_function_instance = (min_sharp_function*)this_instance;
	if (min_sharp_null != min_sharp_function_instance->function_captures)
	{
		return iteration_function(min_sharp_function_instance->function_captures, context);
	}
	return function_call_result_success;
}

static function_call_result function_get_object_type(min_sharp_object* this_instance, min_sharp_object_type* object_type_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	*object_type_result = min_sharp_object_type_primitive_function;
	return function_call_result_success;
}

function_call_result register_function_type(system_services* system_services_instance, runtime_services* runtime_services_instance) 
{
	CRITICAL_ASSERT(min_sharp_null != system_services_instance);
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);

	function_call_result fcr;
	min_sharp_object_intrinsicts* global_function_object_intrinsicts;

	fcr = system_services_instance->allocate_memory(system_services_instance, &global_function_object_intrinsicts, sizeof(min_sharp_object_intrinsicts));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	global_function_object_intrinsicts->garbage_collection_get_flags = function_garbage_collection_get_flags;
	global_function_object_intrinsicts->garbage_collection_set_flags = function_garbage_collection_set_flags;
	global_function_object_intrinsicts->get_interface = function_get_interface;
	global_function_object_intrinsicts->get_object_type = function_get_object_type;
	global_function_object_intrinsicts->iterate_referenced_objects = function_iterate_referenced_objects;
	
	runtime_services_instance->set_global_data(runtime_services_instance, global_function_object_intrinsicts_id, global_function_object_intrinsicts);

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

function_call_result function_factory(
	runtime_services* runtime_services_instance,
	min_sharp_object** returned_exception,
	min_sharp_object** returned_result,
	min_sharp_object* function_captures,
	void* function_implementation)
{
	CRITICAL_ASSERT(min_sharp_null != runtime_services_instance);
	CRITICAL_ASSERT(min_sharp_null != returned_result);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);
	CRITICAL_ASSERT(min_sharp_null != function_implementation);

	function_call_result fcr;
	min_sharp_function* new_function_object;

	// Allocate object
	fcr = runtime_services_instance->allocate_object(
		runtime_services_instance,
		&((min_sharp_object *)new_function_object),
		sizeof(min_sharp_function));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Initialize members
	min_sharp_object_intrinsicts* global_function_object_intrinsicts;
	runtime_services_instance->get_global_data(runtime_services_instance, global_function_object_intrinsicts_id, &global_function_object_intrinsicts);
	new_function_object->object_intrinsicts = global_function_object_intrinsicts;
	new_function_object->function_captures = function_captures;
	new_function_object->function_implementation.function_0_arguments = ( min_sharp_function_0_arguments) function_implementation;
	new_function_object->object_flag = 0;

	*returned_result = (min_sharp_object*)new_function_object;
	*returned_exception = min_sharp_null;

	return function_call_result_success;

fail:
	*returned_result = min_sharp_null;
	runtime_services_instance->system_exception(
		runtime_services_instance,
		returned_exception,
		"Runtime.Error",
		"Error Building Function Object");
	return function_call_result_fail;
}

