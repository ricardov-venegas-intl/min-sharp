#include "pch.h"
#include "system_types_repository.h"
#include "type_internals.h"
#include <assert.h>
#include <string.h>

typedef struct system_repository_data_struct
{
	system_unmanaged_data_structure* system_types_list;
	system_services* system_services_instance;
} system_repository_data;

function_call_result find_type(system_unmanaged_data_structure* this_instance, void* element, void* data_context, min_sharp_boolean* found);

const internal_string operator_add_name = "$OperatorAdd";
const internal_string property_message_name = "Message";

// Allocates object type information
static function_call_result allocate_object_type(min_sharp_type_info** type_info, internal_string interface_name, internal_string parent_interface_name, unsigned_int_16 number_of_members, system_services* system_services_instance)
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

#pragma warning(disable:4305 4293 4305)
// Gives a unique member id
// Replace with a atom table 
static min_sharp_memberid calculate_member_id(internal_string member_name)
{
	min_sharp_memberid h = 525201411107845655ull;
	for (; *member_name; ++member_name) {
		h ^= *member_name;
		h *= 0x5bd1e9955bd1e995ull;
		h ^= h >> 47u;
	}
	return h;
}
#pragma warning(default:4305 4293 4305)

static function_call_result register_type_info(system_types_repository* this_instance, min_sharp_type_info* type_info, internal_string type_name)
{
	function_call_result fcr;
	min_sharp_boolean found = min_sharp_false;
	min_sharp_type_info* previous_type_info;

	if (min_sharp_null == this_instance || min_sharp_null == type_info || min_sharp_null == type_name)
		goto fail;

	//Verify that the type doen't exist already
	fcr = this_instance->data->system_types_list->find_first(this_instance->data->system_types_list, find_type, (void *) type_name, (void **) &previous_type_info, &found);
	if (function_call_result_fail == fcr)
		goto fail;

	if (min_sharp_true == found)
		goto fail;

	fcr = this_instance->data->system_types_list->add_element(this_instance->data->system_types_list, type_info);
	if (function_call_result_fail == fcr)
		goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result initialize_types_repository(system_repository_data *data)
{
	function_call_result call_result;
	min_sharp_type_info* new_type_info;
	int system_types_counter = 0;

	// Add Object type info
	call_result = allocate_object_type(&new_type_info, object_type_name, NULL, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Add String type info
	call_result = allocate_object_type(&new_type_info, string_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	new_type_info->members[0].member_name = operator_add_name;
	new_type_info->members[0].member_type = "String";
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Add Number type info
	call_result = allocate_object_type(&new_type_info, number_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(operator_add_name);
	new_type_info->members[0].member_name = operator_add_name;
	new_type_info->members[0].member_type = "String";
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Add Boolean type info
	call_result = allocate_object_type(&new_type_info, boolean_type_name, object_type_name, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Add Boolean type info
	call_result = allocate_object_type(&new_type_info, function_type_name, object_type_name, 0, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Exception
	call_result = allocate_object_type(&new_type_info, exception_type_name, object_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Runtime Exception
	call_result = allocate_object_type(&new_type_info, runtime_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Runtime Exception
	call_result = allocate_object_type(&new_type_info, runtime_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	// Null Refernce Exception
	call_result = allocate_object_type(&new_type_info, null_reference_exception_type_name, exception_type_name, 1, data->system_services_instance);
	if (function_call_result_success != call_result)
		goto fail;

	new_type_info->members[0].member_id = calculate_member_id(property_message_name);
	new_type_info->members[0].member_name = property_message_name;
	new_type_info->members[0].member_type = string_type_name;
	data->system_types_list->add_element(data->system_types_list, new_type_info);

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result find_type(system_unmanaged_data_structure* this_instance, void* element, void* data_context, min_sharp_boolean* found)
{
	if (min_sharp_null == this_instance || min_sharp_null == element || min_sharp_null == data_context || min_sharp_null == found)
		goto fail;

	min_sharp_type_info* current = (min_sharp_type_info*)element;
	internal_string type_name = (internal_string)data_context;

	*found = (_strcmpi(current->interface_name, type_name) == 0);
	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result get_type_info(system_types_repository* this_instance, min_sharp_type_info** type_info, internal_string type_name)
{
	if (min_sharp_null == this_instance || min_sharp_null == type_info || min_sharp_null == type_name)
		goto fail;

	function_call_result fcr;
	*type_info = min_sharp_null;
	min_sharp_boolean found = min_sharp_false;

	fcr = this_instance->data->system_types_list->find_first(this_instance->data->system_types_list, find_type, (void *)type_name, (void **) type_info, &found);
	if (function_call_result_fail == fcr)
		goto fail;

	if (min_sharp_false == found)
		goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result free_type_info(system_unmanaged_data_structure* this_instance, void* element, void* data_context)
{
	if (min_sharp_null == this_instance || min_sharp_null == element || min_sharp_null == data_context)
		goto fail;

	function_call_result fcr;
	min_sharp_type_info* current = (min_sharp_type_info*)element;
	system_types_repository* respository = (system_types_repository*)data_context;

	fcr = respository->data->system_services_instance->free_memory(current);
	if (function_call_result_fail == fcr)
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

	fcr = this_instance->data->system_types_list->for_each(this_instance->data->system_types_list, free_type_info, this_instance);
	if (function_call_result_fail == fcr)
		goto fail;

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


function_call_result system_repository_factory(system_types_repository** repository, system_services* system_services_instance, system_unmanaged_data_manager* unmanaged_data_manager)
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
		goto fail_free_repository;

	// Set Struct members
	result->get_type_info = &get_type_info;
	result->register_type_info = &register_type_info;
	result->release = &release_system_repository;
	result->data->system_services_instance = system_services_instance;

	fcr = unmanaged_data_manager->create_list(unmanaged_data_manager, &(result->data->system_types_list));
	if (function_call_result_fail == fcr)
		goto fail;

	// Initialize system types data
	initialize_types_repository(result->data);

	// set result value
	*repository = result;

	return function_call_result_success;

fail_free_repository:
	system_services_instance->free_memory(result);

fail:
	return function_call_result_fail;
}