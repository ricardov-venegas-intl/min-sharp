#include "runtime_services.h"
#include "min_sharp-runtime-support.h"

typedef struct runtime_services_data_struct {
	system_services* system_services_instance;
} runtime_services_data;

// unmanaged_memory
static function_call_result allocate_unmanaged_memory(runtime_services* runtime, void** result, int size)
{
	function_call_result fcr;

	CRITICAL_ASSERT(min_sharp_null != runtime);
	if (min_sharp_null == result)
	{
		goto fail;
	}

	fcr = runtime->data->system_services_instance->allocate_memory(runtime->data->system_services_instance, result, size);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result free_unmanaged_memory(runtime_services* runtime, void* memory)
{
	CRITICAL_ASSERT(min_sharp_null != runtime);
	if (min_sharp_null == memory)
	{
		goto fail;
	}

	function_call_result fcr = runtime->data->system_services_instance->free_memory(runtime->data->system_services_instance, memory);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

// runtime exceptions
static function_call_result system_argument_exception(runtime_services* this_instance, min_sharp_object** returnedExcption, internal_string argument_name)
{
	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result system_argument_null_exception(runtime_services* this_instance, min_sharp_object** returnedExcption, internal_string argument_name)
{
	return function_call_result_success;

fail:
	return function_call_result_fail;

}

// strings
static function_call_result are_strings_equal_case_insentitive(runtime_services* this_instance, min_sharp_boolean* result, internal_string string1, internal_string string2, int max_string_size)
{
	return function_call_result_success;

fail:
	return function_call_result_fail;

}


static function_call_result release(runtime_services* this_instance)
{
	function_call_result fcr;

	CRITICAL_ASSERT(min_sharp_null != this_instance);

	system_services* system_services_instance = this_instance->data->system_services_instance;

	fcr = system_services_instance->free_memory(system_services_instance, this_instance->data);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	fcr = system_services_instance->free_memory(system_services_instance, this_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

function_call_result runtime_services_factory(system_services* system_services_instance, runtime_services** result)
{
	function_call_result fcr;
	runtime_services_data *data;

	CRITICAL_ASSERT(min_sharp_null != system_services_instance);
	CRITICAL_ASSERT(min_sharp_null != result);

	fcr = system_services_instance->allocate_memory(system_services_instance, &data, sizeof(data));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	data->system_services_instance = system_services_instance;

	runtime_services* new_instance;
	fcr = system_services_instance->allocate_memory(system_services_instance, &new_instance, sizeof(new_instance));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	new_instance->release = release;
	new_instance->are_strings_equal_case_insentitive = are_strings_equal_case_insentitive;
	new_instance->allocate_unmanaged_memory = allocate_unmanaged_memory;
	new_instance->free_unmanaged_memory = free_unmanaged_memory;
	new_instance->system_argument_exception = system_argument_exception;
	new_instance->system_argument_null_exception = system_argument_null_exception;

	*result = new_instance;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}