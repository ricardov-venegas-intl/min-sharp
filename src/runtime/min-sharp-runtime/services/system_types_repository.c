#include "pch.h"
#include "system_types_repository.h"
#include "internal_runtime.h"
#include "type_internals.h"
#include <assert.h>
#include <string.h>
#define NUMBER_OF_SYSTEM_TYPES 9

typedef struct system_repository_data_struct
{
	unsigned_int_32 number_of_system_types;
	min_sharp_type_info* system_types[NUMBER_OF_SYSTEM_TYPES];
	system_services* system_services_instance;
} system_repository_data;


const internal_string operator_add_name = "$OperatorAdd";
const internal_string property_message_name = "Message";

// Allocates object type information
function_call_result allocate_object_type(min_sharp_type_info** type_info, internal_string interface_name, internal_string parent_interface_name, unsigned_int_16 number_of_members, system_services* system_services_instance)
{
	function_call_result cr;
	min_sharp_type_info* result;

	// Calculate size, min_sharp_type_infoalready contains 1 member
	int_32 type_info_size = sizeof(min_sharp_type_info) + sizeof(min_sharp_member_info) * (number_of_members - 1);
	cr = system_services_instance->allocate_memory(&result, type_info_size);
	if (function_call_result_fail == cr) 
		goto fail;
	result->number_of_members = number_of_members;
	result->interface_name = interface_name;
	result->parent_interface_name = parent_interface_name;

	*type_info = result;

	return function_call_result_success;
fail:
	return function_call_result_fail;

}

//
// Gives a unique member id
// Replace with a atom table 
min_sharp_memberid calculate_member_id(internal_string member_name)
{
	min_sharp_memberid h = 525201411107845655ull;
	for (; *member_name; ++member_name) {
		h ^= *member_name;
		h *= 0x5bd1e9955bd1e995ull;
		h ^= h >> 47u;
	}
	return h;
}


function_call_result initialize_types_repository(system_repository_data *data)
{
	function_call_result call_result;
	min_sharp_type_info* new_type_info;
	int system_types_counter = 0;

	// Add Object type info
	call_result = allocate_object_type(&new_type_info, object_type_name, NULL, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types[system_types_counter++] = new_type_info;

	// Add String type info
	call_result = allocate_object_type(&new_type_info, string_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	new_type_info->members[0].member_name = operator_add_name;
	new_type_info->members[0].member_type = "String";
	data->system_types[system_types_counter++] = new_type_info;

	// Add Number type info
	call_result = allocate_object_type(&new_type_info, number_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	new_type_info->members[0].member_name = operator_add_name;
	new_type_info->members[0].member_type = "String";
	data->system_types[system_types_counter++] = new_type_info;

	// Add Boolean type info
	call_result = allocate_object_type(&new_type_info, boolean_type_name, object_type_name, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types[system_types_counter++] = new_type_info;

	// Add Boolean type info
	call_result = allocate_object_type(&new_type_info, function_type_name, object_type_name, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types[system_types_counter++] = new_type_info;

	// Exception
	call_result = allocate_object_type(&new_type_info, exception_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types[system_types_counter++] = new_type_info;

	// Runtime Exception
	call_result = allocate_object_type(&new_type_info, runtime_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types[system_types_counter++] = new_type_info;

	// Runtime Exception
	call_result = allocate_object_type(&new_type_info, runtime_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types[system_types_counter++] = new_type_info;
	
	// Null Refernce Exception
	call_result = allocate_object_type(&new_type_info, null_reference_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types[system_types_counter++] = new_type_info;

	assert(NUMBER_OF_SYSTEM_TYPES == system_types_counter);
	data->number_of_system_types = NUMBER_OF_SYSTEM_TYPES;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}


function_call_result get_type_info(system_types_repository* this_instance, min_sharp_type_info** type_info, internal_string type_name)
{
	if (min_sharp_null == this_instance || min_sharp_null == type_info || min_sharp_null == type_name)
		goto fail;

	*type_info = min_sharp_null;
	for (unsigned_int_32 i = 0; i < this_instance->data->number_of_system_types; i++)
	{
		if (_strcmpi(this_instance->data->system_types[i]->interface_name, type_name) == 0)
		{
			*type_info = this_instance->data->system_types[i];
			break;
		}
	}
	if (min_sharp_null == *type_info)
		goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

function_call_result release_system_repository(system_types_repository* this_instance)
{
	function_call_result fcr;

	if (min_sharp_null == this_instance)
		goto fail;
	
	system_services* system_services_instance = this_instance->data->system_services_instance;

	fcr = system_services_instance->free_memory(this_instance->data);
	if (function_call_result_fail == fcr)
		goto fail;

	fcr = system_services_instance->free_memory(this_instance);
	if (function_call_result_fail == fcr)
		goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}


function_call_result system_repository_factory(system_types_repository** repository, system_services* system_services_instance)
{
	system_types_repository *result;
	function_call_result fcr;
	// Validate arguments
	if (min_sharp_null == repository || min_sharp_null == system_services_instance)
		goto fail;

	// Allocate struct
	*repository = min_sharp_null;
	fcr = system_services_instance->allocate_memory(&result, sizeof(system_types_repository));
	if (function_call_result_fail == fcr)
		goto fail;
	fcr = system_services_instance->allocate_memory(&(result->data), sizeof(system_repository_data));
	if (function_call_result_fail == fcr)
		goto fail;

	// Set Struct members
	result->get_type_info = &get_type_info;
	result->release = &release_system_repository;
	result->data->system_services_instance = system_services_instance;

	// Initialize system types data
	initialize_types_repository(result->data);

	// set result value
	*repository = result;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}