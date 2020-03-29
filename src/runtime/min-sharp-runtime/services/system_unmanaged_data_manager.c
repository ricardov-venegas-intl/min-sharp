#include "system_unmanaged_data_manager.h"

#pragma warning(push)
#pragma warning(disable: 4090)

// system_unmanaged_data_structure_data
typedef struct system_unmanaged_data_manager_data_struct
{
	system_services* system_services_instance;
} system_unmanaged_data_manager_data;

// Node Structure
typedef struct system_unmanaged_list_node_struct system_unmanaged_list_node;
typedef struct system_unmanaged_list_node_struct
{
	system_unmanaged_list_node* next_node;
	system_unmanaged_list_node* previous_node;
	void* data;
} system_unmanaged_list_node;

// List structure
typedef struct system_unmanaged_data_list_data_struct 
{
	system_services* system_services_instance;
	system_unmanaged_list_node* head;
	system_unmanaged_list_node* tail;
} system_unmanaged_data_list_data;

static function_call_result list_add_element(system_unmanaged_data_structure* this_instance, void* new_element)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == new_element)
		goto fail;


	system_unmanaged_data_list_data* list_data = (system_unmanaged_data_list_data*)this_instance->data;
	system_services* system_services_instance = list_data->system_services_instance;

	system_unmanaged_list_node* new_node;
	fcr = system_services_instance->allocate_memory(&new_node, sizeof(system_unmanaged_list_node));
	if (function_call_result_fail == fcr)
		goto fail;

	new_node->data = new_element;

	if (min_sharp_null == list_data->head)
	{
		new_node->next_node = min_sharp_null;
		new_node->previous_node = min_sharp_null;
		list_data->head = new_node;
		list_data->tail = new_node;
	}
	else
	{
		new_node->next_node = min_sharp_null;
		new_node->previous_node = list_data->tail;
		list_data->tail->next_node = new_node;
		list_data->tail = new_node;
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result list_remove_element(system_unmanaged_data_structure* this_instance, void* element)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == element)
		goto fail;

	system_unmanaged_data_list_data* list_data = (system_unmanaged_data_list_data*)this_instance->data;

	if (min_sharp_null == list_data->head)
		goto fail;

	system_unmanaged_list_node* current_node = list_data->head;
	system_unmanaged_list_node* next_node = current_node->next_node;
	system_unmanaged_list_node* previous_node = min_sharp_null;
	min_sharp_boolean element_found = min_sharp_false;

	while (min_sharp_null != current_node)
	{
		if (current_node->data == element)

		{
			if (min_sharp_null != previous_node)
			{
				previous_node->next_node = current_node->next_node;
			}
			if (min_sharp_null != next_node)
			{
				next_node->previous_node = previous_node;
			}
			if (list_data->head == current_node)
			{
				list_data->head = next_node;
			}
			if (list_data->tail == current_node)
			{
				list_data->tail = previous_node;
			}

			system_unmanaged_list_node* node_to_delete = current_node;
			previous_node = current_node->previous_node;
			current_node = current_node->next_node;
			next_node =  (min_sharp_null != current_node) ?current_node->next_node: min_sharp_null;

			// delete old current
			fcr = list_data->system_services_instance->free_memory(node_to_delete);
			if (function_call_result_fail == fcr)
				goto fail;
			
		}
		else
		{
			previous_node = current_node;
			next_node = current_node->next_node;
			current_node = previous_node->next_node;
		}
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result list_for_each(system_unmanaged_data_structure* this_instance, enumerate_callback_function enumerate_function_instance, void* data_context)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == enumerate_function_instance)
		goto fail;

	system_unmanaged_data_list_data* list_data = (system_unmanaged_data_list_data*)this_instance->data;
	system_unmanaged_list_node* current_node = list_data->head;
	system_unmanaged_list_node* next_node = min_sharp_null;
	min_sharp_boolean element_found = min_sharp_false;

	while (min_sharp_null != current_node)
	{
		next_node = current_node->next_node;
		fcr = enumerate_function_instance(this_instance, current_node->data, data_context);
		if (function_call_result_fail == fcr)
			goto fail;
		current_node = next_node;
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result list_find_first(system_unmanaged_data_structure* this_instance, filter_callback_function filter_function, void* data_context, void** result, min_sharp_boolean* found)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == filter_function)
		goto fail;
	if (min_sharp_null == result)
		goto fail;

	*result = min_sharp_null;
	system_unmanaged_data_list_data*  list_data = (system_unmanaged_data_list_data*)this_instance->data;
	system_unmanaged_list_node* current_node = list_data->head;
	system_unmanaged_list_node* next_node = min_sharp_null;
	min_sharp_boolean element_found = min_sharp_false;

	while (min_sharp_null != current_node)
	{
		next_node = current_node->next_node;
		fcr = filter_function(this_instance, current_node->data, data_context, &element_found);
		if (function_call_result_fail == fcr)
			goto fail;
		if (min_sharp_true == element_found)
		{
			*result = current_node->data;
			*found = min_sharp_true;
			return function_call_result_success;
		}
		current_node = next_node;
	}
	*found = min_sharp_false;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result list_exists(system_unmanaged_data_structure* this_instance, void* element, min_sharp_boolean* found)
{
	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == element)
		goto fail;

	*found = min_sharp_false;
	system_unmanaged_data_list_data* list_data = (system_unmanaged_data_list_data*)this_instance->data;
	system_unmanaged_list_node* current_node = list_data->head;
	system_unmanaged_list_node* next_node = min_sharp_null;
	min_sharp_boolean element_found = min_sharp_false;

	while (min_sharp_null != current_node)
	{
		next_node = current_node->next_node;
		if (current_node->data == element)
		{
			*found = min_sharp_true;
			return function_call_result_success;
		}
		current_node = next_node;
	}
	*found = min_sharp_false;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result release_list(system_unmanaged_data_manager* this_instance, system_unmanaged_data_structure* unmanaged_data_structure)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == unmanaged_data_structure)
		goto fail;

	system_services* system_services_instance = this_instance->data->system_services_instance;

	system_unmanaged_data_list_data* data = (system_unmanaged_data_list_data*) unmanaged_data_structure->data;
	system_unmanaged_list_node* current_node = data->head;
	system_unmanaged_list_node* next_node = min_sharp_null;

	while (min_sharp_null != current_node)
	{
		next_node = current_node->next_node;
		fcr = system_services_instance->free_memory(current_node);
		if (function_call_result_fail == fcr)
			goto fail;
		current_node = next_node;
	}

	fcr = system_services_instance->free_memory(unmanaged_data_structure->data);
	if (function_call_result_fail == fcr)
		goto fail;

	fcr = system_services_instance->free_memory(unmanaged_data_structure);
	if (function_call_result_fail == fcr)
		goto fail;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result create_list(system_unmanaged_data_manager* this_instance, system_unmanaged_data_structure** unmanaged_data_structure)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;
	if (min_sharp_null == unmanaged_data_structure)
		goto fail;

	// Get the system_services_instance
	system_services* system_services_instance = this_instance->data->system_services_instance;

	system_unmanaged_data_structure* result;
	*unmanaged_data_structure = min_sharp_null;

	fcr = system_services_instance->allocate_memory(&result, sizeof(system_unmanaged_data_structure));
	if (function_call_result_fail == fcr)
		goto fail;

	system_unmanaged_data_list_data *list_data;
	fcr = system_services_instance->allocate_memory(&list_data, sizeof(system_unmanaged_data_list_data));
	if (function_call_result_fail == fcr)
		goto fail;

	result->add_element = list_add_element;
	result->exists = list_exists;
	result->find_first = list_find_first;
	result->for_each = list_for_each;
	result->remove_element = list_remove_element;
	list_data->head = min_sharp_null;
	list_data->tail = min_sharp_null;
	list_data->system_services_instance = this_instance->data->system_services_instance;
	result->data = (system_unmanaged_data_structure_data*) list_data;

	(*unmanaged_data_structure) = result;
	return function_call_result_success;
fail:
	return function_call_result_fail;
}

static function_call_result release(system_unmanaged_data_manager* this_instance)
{
	function_call_result fcr;

	// Verify arguments
	if (min_sharp_null == this_instance)
		goto fail;

	// Get the system_services_instance
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

function_call_result system_unmanaged_data_manager_factory(system_unmanaged_data_manager** unmanaged_data_manager, system_services* system_services_instance)
{
	function_call_result fcr;
	// Verify arguments
	if (min_sharp_null == unmanaged_data_manager)
		goto fail;
	if (min_sharp_null == system_services_instance)
		goto fail;

	system_unmanaged_data_manager* result = min_sharp_null;
	*unmanaged_data_manager = min_sharp_null;
	// Allocate unmanaged memory (system_unmanaged_data_manager & system_unmanaged_data_manager_data)
	fcr = system_services_instance->allocate_memory(&result, sizeof(system_unmanaged_data_manager));
	if (function_call_result_fail == fcr)
		goto fail;
	fcr = system_services_instance->allocate_memory(&(result->data), sizeof(system_unmanaged_data_manager_data));
	if (function_call_result_fail == fcr)
		goto fail;
	
	// Fill the struct
	result->data->system_services_instance = system_services_instance;
	result->release = release;
	result->create_list = create_list;
	result->release_list = release_list;

	*unmanaged_data_manager = result;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

#pragma warning(pop)