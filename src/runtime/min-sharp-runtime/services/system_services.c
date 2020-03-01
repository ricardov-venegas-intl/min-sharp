#include "system_services.h"
#include <malloc.h>
#include <memory.h>

function_call_result allocate_memory(void** result, int size)
{
	if (result == min_sharp_null)
	{
		return function_call_result_fail;
	}
	*result = NULL;
	if (size == 0)
	{
		return function_call_result_fail;
	}
	*result = malloc(size);
	if (NULL == *result)
	{
		return function_call_result_fail;
	}
	memset(*result, 0, size);

	return function_call_result_success;
}

function_call_result free_memory(void* memory)
{
	if (NULL == memory)
	{
		return function_call_result_fail;
	}
	free(memory);
	return function_call_result_success;
}

function_call_result release_system_services(system_services* system_services_instance)
{
	// fill with 0 to detect use after free errors
	memset(system_services_instance, 0, sizeof(system_services));
	free(system_services_instance);
	return function_call_result_success;
}

function_call_result system_services_factory(system_services** result)
{
	if (NULL == result)
	{
		return function_call_result_fail;
	}
	*result = NULL;
	*result = (system_services*) malloc(sizeof(system_services));
	if (NULL == *result)
	{
		return function_call_result_fail;
	}
	(*result)->release = &release_system_services;
	(*result)->allocate_memory = &allocate_memory;
	(*result)->free_memory = &free_memory;
	
	return function_call_result_success;
}

