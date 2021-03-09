#include "min-sharp-runtime.h"
#include "min_sharp-runtime-support.h"
#include "../min-sharp-runtime-function-prototypes.h"

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

	min_sharp_function_with_capture* min_sharp_function_instance = (min_sharp_function_with_capture*)this_instance;
	*objectFlag = min_sharp_function_instance->min_sharp_function_instance.object_flag;
	return function_call_result_success;
}

static function_call_result garbage_collection_set_flags(min_sharp_object* this_instance, object_flags objectFlag)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	min_sharp_function_with_capture* min_sharp_function_instance = (min_sharp_function_with_capture*)this_instance;
	min_sharp_function_instance->min_sharp_function_instance.object_flag = objectFlag;
	return function_call_result_success;
}

static function_call_result iterate_referenced_objects(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void* context)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);

	min_sharp_function_with_capture* min_sharp_function_instance = (min_sharp_function_with_capture*)this_instance;
	if (min_sharp_null != min_sharp_function_instance->function_captures)
	{
		return iteration_function(min_sharp_function_instance->function_captures, context);
	}
	return function_call_result_success;
}

static function_call_result get_object_type(min_sharp_object* this_instance, min_sharp_object_type* object_type_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	*object_type_result = min_sharp_object_type_primitive_function;
}


