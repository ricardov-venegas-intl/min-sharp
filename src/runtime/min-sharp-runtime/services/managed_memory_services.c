#include "managed_memory_services.h"

static typedef struct object_node_struct object_node;
static typedef struct object_node_struct
{
	unsigned_int_16 object_flags;
	unsigned_int_16 allocated_memory;
	object_node next*;
	int_32 object_memory[1];
} object_node;

static typedef struct scope_variables_node_struct scope_variables_node;

typedef struct scope_variables_node_struct  {
	int_32 number_of_elements;
	void* scope_variables[];
	scope_variables_node* next_scope;
} scope_variables_node;

typedef struct managed_memory_services_data_struct { 
	system_services *system_services_instance;
	object_node *object_list_head;
	scope_variables *scope_variables_stack_head;
} managed_memory_services_data;


static function_call_result push_scope(managed_memory_services* this_instance, int_32 number_of_elements, void* scope_variables[])
{
	function_call_result fcr;
	scope_variables_node *new_node;
	system_services* system_services_instance;

	if (this_instance == min_sharp_null || system_services_instance == min_sharp_null || scope_variables== min_sharp_null)
	{
		goto fail;
	}

	// Allocate memory
	system_services_instance = this_instance->data->system_services_instance;
	fcr = system_services_instance->allocate_memory(&new_node, sizeof(scope_variables_node));
	if (fcr == function_call_result_fail)
	{
		goto fail;
	}

	// Initialize node
	new_node->next_scope = this_instance->data->scope_variables_stack_head;
	new_node->scope_variables = scope_variables;
	new_node->number_of_elements = number_of_elements;

	//Update stack
	this_instance->data->scope_variables_stack_head = new_node;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result pop_scope(managed_memory_services* this_instance)
{
	function_call_result fcr;
	scope_variables_node *old_node;
	system_services* system_services_instance;

	if (this_instance == min_sharp_null)
	{
		goto fail;
	}

	if (this_instance->data->scope_variables_stack_head == min_sharp_null)
	{
		goto fail;
	}

	//remove the top of the stack
	old_node = this_instance->data->scope_variables_stack_head;
	this_instance->data->scope_variables_stack_head = old_node->next_scope;

	// deallocate the node memory
	system_services_instance = this_instance->data->system_services_instance;
	system_services_instance->free_memory(old_node);

	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result(*allocate_object)(managed_memory_services* this_instance, int_32 size)
{
	function_call_result fcr;
	object_node* new_object_node;
	system_services* system_services_instance;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

function_call_result managed_memory_services_factory(managed_memory_services** result, system_services* system_services_instance)
{
	function_call_result fcr;
	managed_memory_services *this_instance;
	managed_memory_services_data *data;

	if (result == min_sharp_null || system_services_instance == min_sharp_null)
	{
		goto fail;
	}

	fcr = system_services_instance->allocate_memory(&this_instance, sizeof(managed_memory_services));
	if (fcr == function_call_result_fail)
	{
		goto fail;
	}
	fcr = system_services_instance->allocate_memory(&data, sizeof(managed_memory_services_data));
	if (fcr == function_call_result_fail)
	{
		goto fail;
	}
	data->object_list_head = min_sharp_null;
	data->scope_variables_stack = min_sharp_null;
	data->system_services_instance = system_services_instance;
	this_instance->data = data;
	this_instance->push_scope = &push_scope;
	this_instance->pop_scope = &pop_scope;

	*result = this_instance;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}
