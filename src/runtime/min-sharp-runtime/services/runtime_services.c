#include "runtime_services.h"
#include "min_sharp-runtime-support.h"
#include "internal/system_services.h"
#include "services\internal\managed_memory_services.h"
#include "Types/runtime_number.h"
#include <string.h>

typedef struct runtime_services_data_struct {
	system_services* system_services_instance;
	managed_memory_services *managed_memory_services_instance;
	type_initializer number_initializer;
	int number_object_size;
	void* number_initializer_data;
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
static function_call_result system_argument_exception(runtime_services* runtime, min_sharp_object** returnedExcption, internal_string argument_name)
{
	CRITICAL_ASSERT(min_sharp_null != runtime);

	goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result system_argument_null_exception(runtime_services* this_instance, min_sharp_object** returnedExcption, internal_string argument_name)
{
	goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

// strings
static function_call_result are_strings_equal_case_insentitive(runtime_services* runtime, min_sharp_boolean* result, internal_string string1, internal_string string2, unsigned_int_32 max_string_size)
{
	CRITICAL_ASSERT(min_sharp_null != runtime);
	if (min_sharp_null == result)
	{
		goto fail;
	}

	if (min_sharp_null == string1 || min_sharp_null == string2)
	{
		*result = (string1 == string2);
		return function_call_result_success;
	}

	int are_different = _strnicmp(string1, string2, max_string_size);
	*result = !are_different;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result push_scope(runtime_services* this_instance, unsigned_int_16 number_of_elements, min_sharp_object* scope_variables[])
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	managed_memory_services* managed_memory_services_instance = this_instance->data->managed_memory_services_instance;

	function_call_result fcr;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, number_of_elements, scope_variables);
	if (function_call_result_fail == fcr) 
	{
		goto fail;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result pop_scope (runtime_services* this_instance)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	managed_memory_services* managed_memory_services_instance = this_instance->data->managed_memory_services_instance;

	function_call_result fcr;
	fcr = managed_memory_services_instance->pop_scope(managed_memory_services_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	return function_call_result_success;


fail:
	return function_call_result_fail;
}

static function_call_result allocate_object(runtime_services* this_instance, min_sharp_object** new_object, unsigned_int_16 internal_data_size)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	managed_memory_services* managed_memory_services_instance = this_instance->data->managed_memory_services_instance;

	function_call_result fcr;
	fcr = managed_memory_services_instance->allocate_object(managed_memory_services_instance, new_object, internal_data_size);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

fail:
	return function_call_result_fail;
}

static function_call_result collect_garbage(runtime_services* this_instance)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	managed_memory_services* managed_memory_services_instance = this_instance->data->managed_memory_services_instance;

	function_call_result fcr;
	fcr = managed_memory_services_instance->collect_garbage(managed_memory_services_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result build_number(runtime_services* this_instance, min_sharp_object** returned_exception, min_sharp_object** returned_result)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != returned_result);
	CRITICAL_ASSERT(min_sharp_null != returned_exception);

	function_call_result fcr;
	min_sharp_object* new_number;
	managed_memory_services* managed_memory_services_instance = this_instance->data->managed_memory_services_instance;

	fcr = managed_memory_services_instance->allocate_object(managed_memory_services_instance, (min_sharp_object**)&new_number, sizeof(this_instance->data->number_object_size));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	fcr = this_instance->data->number_initializer(new_number, this_instance->data->number_initializer_data);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	*returned_result = (min_sharp_object*)new_number;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result register_number_initializer(
	runtime_services* this_instance, 
	int number_object_size, 
	type_initializer number_initializer, 
	void* number_initializer_data)
{
	CRITICAL_ASSERT(min_sharp_null != this_instance);
	CRITICAL_ASSERT(min_sharp_null != number_initializer);

	this_instance->data->number_initializer = number_initializer;
	this_instance->data->number_object_size = number_object_size;
	this_instance->data->number_initializer_data = number_initializer_data;
	return function_call_result_success;
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


function_call_result runtime_services_factory(
	system_services* system_services_instance, 
	managed_memory_services *managed_memory_services_instance, 
	runtime_services** result)
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
	data->number_initializer = min_sharp_null;
	data->number_initializer_data = min_sharp_null;
	data->number_object_size = 0;

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
	
	new_instance->push_scope = push_scope;
	new_instance->pop_scope = pop_scope;
	new_instance->allocate_object = allocate_object;
	new_instance->collect_garbage = collect_garbage;

	*result = new_instance;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}