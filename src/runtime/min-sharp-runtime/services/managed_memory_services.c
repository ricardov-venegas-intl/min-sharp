#include "managed_memory_services.h"

const unsigned_int_8 garbage_collection_flags_clear = 0; //00
const unsigned_int_8 garbage_collection_flags_reached = 1; //01
const unsigned_int_8 garbage_collection_flags_scanned = 3; //11

const unsigned_int_8 allocation_flags_regular_object = 1;
const unsigned_int_8 allocation_flags_primitive_object = 2; // String, Boolean, Number, Function Code

typedef struct object_node_struct object_node;
typedef struct object_node_struct
{
	unsigned_int_16 allocated_memory;
	object_node *next;
	min_sharp_object object;
} object_node;

typedef struct scope_variables_node_struct scope_variables_node;

typedef struct scope_variables_node_struct  {
	unsigned_int_16 number_of_elements;
	min_sharp_object **scope_variables;
	scope_variables_node* next_scope;
} scope_variables_node;

typedef struct managed_memory_services_data_struct { 
	system_services *system_services_instance;
	object_node *object_list_head;
	scope_variables_node *scope_variables_stack_head;
	unsigned_int_64 total_allocated_memory;
	unsigned_int_64 total_allocations;
	unsigned_int_64 total_deallocations;
} managed_memory_services_data;


static function_call_result push_scope(managed_memory_services* this_instance, unsigned_int_16 number_of_elements, min_sharp_object* scope_variables[])
{
	function_call_result fcr;
	scope_variables_node *new_node;
	system_services* system_services_instance;

	if (min_sharp_null == this_instance || min_sharp_null == scope_variables)
	{
		goto fail;
	}

	// Allocate memory
	system_services_instance = this_instance->data->system_services_instance;
	fcr = system_services_instance->allocate_memory(system_services_instance, &new_node, sizeof(scope_variables_node));
	if (function_call_result_fail == fcr)
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

	if (min_sharp_null == this_instance)
	{
		goto fail;
	}

	if (min_sharp_null == this_instance->data->scope_variables_stack_head)
	{
		goto fail;
	}

	//remove the top of the stack
	old_node = this_instance->data->scope_variables_stack_head;
	this_instance->data->scope_variables_stack_head = old_node->next_scope;

	// deallocate the node memory
	system_services_instance = this_instance->data->system_services_instance;
	fcr = system_services_instance->free_memory(system_services_instance, old_node);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result allocate_object(managed_memory_services* this_instance, min_sharp_object** new_object, unsigned_int_16 internal_data_size) {
	function_call_result fcr;
	object_node* new_object_node;
	system_services* system_services_instance;
	if (min_sharp_null == this_instance 		
		|| min_sharp_null == new_object
		|| internal_data_size <= 0)
	{
		goto fail;
	}

	// Calculate allocation size
	int_32 object_allocation_size = 
		sizeof(object_node)
		+ sizeof(min_sharp_object)
		+ internal_data_size;


	// Allocate the object
	system_services_instance = this_instance->data->system_services_instance;
	fcr = system_services_instance->allocate_memory(system_services_instance , &new_object_node, object_allocation_size);

	// Initialize the object node
	new_object_node->allocated_memory = object_allocation_size;
	new_object_node->next = this_instance->data->object_list_head;

	// Update the allocationlist
	this_instance->data->object_list_head = new_object_node;

	// Initialize object allocation variables
	//Calculate the start of the  first interface
	void* data_start  = (void*)(&(new_object_node->object) + 1);

	//Initialize object
	new_object_node->object.object_intrinsicts = min_sharp_null;
	*new_object = &(new_object_node->object);
	
	// Update counters
	(this_instance->data->total_allocations)++;
	(this_instance->data->total_allocated_memory) += object_allocation_size;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result mark_referenced_objects_as_reached(min_sharp_object* child_object, void * context)
{
	function_call_result fcr;
	
	if (min_sharp_null != child_object)
	{
		if (min_sharp_null == child_object->object_intrinsicts)
		{
			goto fail;
		}

		fcr = child_object->object_intrinsicts->GarbagoCollectionSetFlags(child_object, garbage_collection_flags_reached);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}

	}

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result scall_all_object_nodes(object_node* object_list_head)
{
	function_call_result fcr;
	if (min_sharp_null == object_list_head)
	{
		goto fail;
	}
	min_sharp_boolean new_object_reached = min_sharp_false;

	do 
	{
		object_node* current = object_list_head;
		new_object_reached = min_sharp_false;
		while (min_sharp_null != current)
		{
			object_node* next = current->next;
			min_sharp_object* current_object = &(current ->object);
			object_flags current_object_flags;
			
			if (min_sharp_null == current_object->object_intrinsicts)
			{
				goto fail;
			}
			fcr = current_object->object_intrinsicts->GarbagoCollectionGetFlags(current_object, &current_object_flags);
			if (function_call_result_fail == fcr)
			{
				goto fail;
			}

			if (garbage_collection_flags_reached == current_object_flags)
			{
				// Mark all members of all interfaces as reached
				fcr = current_object->object_intrinsicts->IterateReferencedObjects(current_object, mark_referenced_objects_as_reached, min_sharp_null);
				if (function_call_result_fail == fcr)
				{
					goto fail;
				}

				// Mark current object as scanned
				fcr = current_object->object_intrinsicts->GarbagoCollectionSetFlags(current_object, garbage_collection_flags_scanned);
				if (function_call_result_fail == fcr)
				{
					goto fail;
				}
				new_object_reached = min_sharp_true;
			}
			current = next;
		}
	} while (min_sharp_true == new_object_reached);

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result collect_garbage(managed_memory_services* this_instance)
{
	function_call_result fcr;

	if (min_sharp_null == this_instance)
	{
		goto fail;
	}

	// mark all object in the scopes
	scope_variables_node* current_scope = this_instance->data->scope_variables_stack_head;
	while (min_sharp_null != current_scope)
	{
		scope_variables_node* next_scope = current_scope->next_scope;
		for (int i = 0; i < current_scope->number_of_elements; i++)
		{
			if (min_sharp_null != current_scope->scope_variables[i])
			{
				min_sharp_object *current_object = current_scope->scope_variables[i];
				object_flags current_object_flags;
				if (min_sharp_null == current_object->object_intrinsicts)
				{
					goto fail;
				}

				fcr = current_object->object_intrinsicts->GarbagoCollectionGetFlags(current_object, &current_object_flags);
				if (function_call_result_fail == fcr)
				{
					goto fail;
				}

				if (garbage_collection_flags_clear == current_object_flags)
				{
					fcr = current_object->object_intrinsicts->GarbagoCollectionSetFlags(current_object, garbage_collection_flags_reached);
					if (function_call_result_fail == fcr)
					{
						goto fail;
					}
				}
			}
		}
		current_scope = next_scope;
	}

	//scan all objects if there are objects allocated
	if (min_sharp_null != this_instance->data->object_list_head)
	{
		fcr = scall_all_object_nodes(this_instance->data->object_list_head);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}

	// free unmarked objects
	system_services* system_services_instance = this_instance->data->system_services_instance;
	object_node* current_object_node = this_instance->data->object_list_head;
	object_node* previous_node = min_sharp_null;
	while (min_sharp_null != current_object_node)
	{
		object_node* next = current_object_node->next;
		min_sharp_object* current_object = &(current_object_node->object);
		object_flags current_object_flags;
		fcr = current_object->object_intrinsicts->GarbagoCollectionGetFlags(current_object, &current_object_flags);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}

		if (garbage_collection_flags_clear == current_object_flags)
		{
			fcr = system_services_instance->free_memory(system_services_instance, current_object_node);
			if (function_call_result_fail == fcr)
			{
				goto fail;
			}
			if (min_sharp_null == previous_node)
			{
				this_instance->data->object_list_head = next;
			}
			else
			{
				previous_node->next = next;
			}
			this_instance->data->total_deallocations++;
		}
		else
		{
			fcr = current_object->object_intrinsicts->GarbagoCollectionSetFlags(current_object, garbage_collection_flags_clear);
			if (function_call_result_fail == fcr)
			{
				goto fail;
			}

			previous_node = current_object_node;
		}
		current_object_node = next;
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result get_counters(managed_memory_services* this_instance, unsigned_int_64* total_allocated_memory, unsigned_int_64* total_allocations, unsigned_int_64* total_deallocations)
{
	if (min_sharp_null == this_instance 
		|| min_sharp_null == total_allocated_memory 
		|| min_sharp_null == total_allocations 
		|| min_sharp_null == total_deallocations)
	{
		goto fail;
	}

	*total_allocated_memory = this_instance->data->total_allocated_memory;
	*total_allocations = this_instance->data->total_allocations;
	*total_deallocations = this_instance->data->total_deallocations;
	return function_call_result_success;

fail:
	return function_call_result_fail;

}

static function_call_result release_managed_memory_services(managed_memory_services* this_instance)
{
	function_call_result fcr;

	if (min_sharp_null == this_instance)
		goto fail;

	system_services* system_services_instance = this_instance->data->system_services_instance;

	// Free all managed objects
	object_node *current = this_instance->data->object_list_head;
	while (min_sharp_null !=  current)
	{
		object_node* next = current->next;
		fcr = system_services_instance->free_memory(system_services_instance, current);
		if (function_call_result_fail == fcr)
			goto fail;
		current = next;
	}

	// free the scopes stack
	scope_variables_node *current_scope = this_instance->data->scope_variables_stack_head;
	while (min_sharp_null != current_scope)
	{
		scope_variables_node* next_scope = current_scope->next_scope;
		fcr = system_services_instance->free_memory(system_services_instance, current_scope);
		if (function_call_result_fail == fcr)
			goto fail;
		current_scope = next_scope;
	}

	// free this instace data
	fcr = system_services_instance->free_memory(system_services_instance, this_instance->data);
	if (function_call_result_fail == fcr)
		goto fail;

	// free this instace
	fcr = system_services_instance->free_memory(system_services_instance, this_instance);
	if (function_call_result_fail == fcr)
		goto fail;

	return function_call_result_success;

fail:
	return function_call_result_fail;

}



function_call_result managed_memory_services_factory(managed_memory_services** result, system_services* system_services_instance)
{
	function_call_result fcr;
	managed_memory_services *this_instance;
	managed_memory_services_data *data;

	if (min_sharp_null == result || min_sharp_null == system_services_instance)
	{
		goto fail;
	}

	fcr = system_services_instance->allocate_memory(system_services_instance , &this_instance, sizeof(managed_memory_services));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	fcr = system_services_instance->allocate_memory(system_services_instance , &data, sizeof(managed_memory_services_data));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	data->object_list_head = min_sharp_null;
	data->scope_variables_stack_head = min_sharp_null;
	data->system_services_instance = system_services_instance;
	data->total_allocated_memory = 0;
	data->total_allocations = 0;
	data->total_deallocations = 0;
	this_instance->data = data;
	this_instance->push_scope = &push_scope;
	this_instance->pop_scope = &pop_scope;
	this_instance->allocate_object = &allocate_object;
	this_instance->collect_garbage = &collect_garbage;
	this_instance->get_counters = &get_counters;
	this_instance->release = &release_managed_memory_services;
	*result = this_instance;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}
