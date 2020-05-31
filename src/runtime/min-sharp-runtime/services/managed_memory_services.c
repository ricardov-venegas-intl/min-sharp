#include "managed_memory_services.h"

const unsigned_int_8 garbage_collection_flags_clear = 0; //00
const unsigned_int_8 garbage_collection_flags_reached = 1; //01
const unsigned_int_8 garbage_collection_flags_scanned = 3; //11

const unsigned_int_8 allocation_flags_regular_object = 1;
const unsigned_int_8 allocation_flags_primitive_object = 2; // String, Boolean, Number, Function Code

typedef struct object_node_struct object_node;
typedef struct object_node_struct
{
	unsigned_int_8 garbage_collection_flags;
	unsigned_int_8 allocation_flags;
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
} managed_memory_services_data;



typedef struct min_sharp_interface_struct_mapped {
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
	min_sharp_object_member members[1];
} min_sharp_interface_mapped;

typedef struct min_sharp_object_header_struct_mapped {
	unsigned_int_16 number_of_interfaces;
	min_sharp_interface interfaces[1];
} min_sharp_object_header_mapped;

typedef struct min_sharp_object_struct_mapped {
	function_call_result(*__GetInterface)(min_sharp_object** exception, min_sharp_interface** result, internal_string interfaceName);
	min_sharp_object_header_mapped header;
} min_sharp_object_mapped;


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
	fcr = system_services_instance->allocate_memory(&new_node, sizeof(scope_variables_node));
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
	fcr = system_services_instance->free_memory(old_node);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result allocate_object(managed_memory_services* this_instance, min_sharp_object** new_object, unsigned_int_16 number_of_interfaces, unsigned_int_16 interfaces_sizes[])
{
	function_call_result fcr;
	object_node* new_object_node;
	system_services* system_services_instance;
	if (min_sharp_null  == this_instance 
		|| number_of_interfaces <= 0 
		|| min_sharp_null == interfaces_sizes 
		|| min_sharp_null == new_object)
	{
		goto fail;
	}

	// calculate the allocation size
	int_32 interfaces_allocation_size = 0;
	for(int i = 0; i < number_of_interfaces; i++)
	{
		interfaces_allocation_size += sizeof(min_sharp_interface)
			+ sizeof(min_sharp_object_member) * interfaces_sizes[i];
	}
	int_32 object_allocation_size = sizeof(object_node) 
		+ sizeof(min_sharp_object)
		+ sizeof(min_sharp_object_header)
		+ interfaces_allocation_size;

	// Allocate the object
	system_services_instance = this_instance->data->system_services_instance;
	fcr = system_services_instance->allocate_memory(&new_object_node, object_allocation_size);
	
	// Initialize the object node
	new_object_node->garbage_collection_flags = garbage_collection_flags_clear;
	new_object_node->allocation_flags = allocation_flags_regular_object;
	new_object_node->allocated_memory = object_allocation_size;
	new_object_node->next = this_instance->data->object_list_head;

	// Initialize object allocation variables
	//Calculate the start of the object header
	min_sharp_object_mapped* current_object = (min_sharp_object_mapped*)&(new_object_node->object);
	min_sharp_object_header* object_header = (min_sharp_object_header*)&(current_object->header);

	//Calculate the start of the  first interface
	min_sharp_object_header_mapped* mappedHeader = (min_sharp_object_header_mapped*)object_header;
	min_sharp_interface* current_interface = &(mappedHeader->interfaces[0]);

	//Initialize object
	new_object_node->object.__GetInterface = min_sharp_null;
	object_header->number_of_interfaces = number_of_interfaces;

	// initialize the interfaces
	for (int interface_index = 0; interface_index < number_of_interfaces; interface_index++)
	{
		// This would not happen, but the compiler throws a warning
		if (min_sharp_null == current_interface)
		{
			goto fail;
		}

		// initialize the current interface fields
		current_interface->number_of_members = interfaces_sizes[interface_index];
		current_interface->type_info = min_sharp_null;

		// Initialize the members
		min_sharp_interface_mapped* mapped_interface = (min_sharp_interface_mapped*)current_interface;
		// Calculate the start of the members (where the next inteface starts if it were an array
		min_sharp_object_member* current_member = (min_sharp_object_member*)&(mapped_interface->members[0]);

		for (int member_index = 0; member_index < interfaces_sizes[interface_index]; member_index++)
		{
			// This would not happen, but the compiler throws a warning
			if (min_sharp_null == current_member)
			{
				goto fail;
			}
			current_member->member_id = member_index; // prefiled only for debug and test
			current_member->value = min_sharp_null;
			current_member++;
		}
		// the next interface starts after the last member
		current_interface = (min_sharp_interface*)current_member;
	}

	
	// Add the new object to the list
	this_instance->data->object_list_head = new_object_node;

	*new_object = &(new_object_node->object);
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result allocate__primitive_object(managed_memory_services* this_instance, min_sharp_object** new_object, unsigned_int_16 internal_data_size) {
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
	fcr = system_services_instance->allocate_memory(&new_object_node, object_allocation_size);

	// Initialize the object node
	new_object_node->garbage_collection_flags = garbage_collection_flags_clear;
	new_object_node->allocation_flags = allocation_flags_primitive_object;
	new_object_node->allocated_memory = object_allocation_size;
	new_object_node->next = this_instance->data->object_list_head;

	// Update the allocationlist
	this_instance->data->object_list_head = new_object_node;

	// Initialize object allocation variables
	//Calculate the start of the  first interface
	void* data_start  = (void*)(&(new_object_node->object) + 1);

	//Initialize object
	new_object_node->object.__GetInterface = min_sharp_null;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result get_object_node_from_object(object_node **result, min_sharp_object *object)
{
	if (min_sharp_null == result || min_sharp_null == object)
	{
		goto fail;
	}

	*result = min_sharp_null;

	// move to the end of the object node and then goto the beginning
	object_node* node= ((object_node*)(object + 1)) - 1;

	//validate flags to verify it is an object node
	if (node->allocation_flags != allocation_flags_primitive_object
		&& node->allocation_flags != allocation_flags_regular_object) 
	{
		goto fail;
	}

	if (node->garbage_collection_flags != garbage_collection_flags_clear
		&& node->garbage_collection_flags != garbage_collection_flags_reached
		&& node->garbage_collection_flags != garbage_collection_flags_scanned)
	{
		goto fail;
	}

	*result = node;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}

static function_call_result get_interface_by_index(min_sharp_interface **result, min_sharp_object* object, unsigned_int_16 interface_index)
{
	min_sharp_object_mapped* mapped_object = (min_sharp_object_mapped*)object;
	// verify null and than the index in les than the number of interfaces
	if (min_sharp_null == object 
		|| mapped_object->header.number_of_interfaces <= interface_index)
	{
		goto fail;
	}


	// The current interface starts after the object_header
	min_sharp_object_header_mapped* mapped_header = (min_sharp_object_header_mapped*)&(mapped_object->header);
	min_sharp_interface* current = &(mapped_header->interfaces[0]);
	unsigned_int_16 current_index = 0;
	while (current_index < interface_index)
	{
		min_sharp_interface_mapped* mapped_interface = (min_sharp_interface_mapped*)current;
		// The next inteface starts after the last member (current->number_of_members -1)
		current = (min_sharp_interface*)&(mapped_interface->members[current->number_of_members]);
		current_index++;
	}

	*result = current;
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
			if (garbage_collection_flags_reached == current->garbage_collection_flags)
			{
				if (allocation_flags_regular_object == current->allocation_flags)
				{
					min_sharp_object_mapped* mapped_object = (min_sharp_object_mapped*)&(current->object);
					for (int interface_index = 0;
						interface_index < mapped_object->header.number_of_interfaces;
						interface_index++)
					{
						min_sharp_interface* current_interface;
						fcr = get_interface_by_index(&current_interface, &(current->object), interface_index);
						if (function_call_result_fail == fcr)
						{
							goto fail;
						}
						for (int member_index = 0; 
							member_index < current_interface->number_of_members; 
							member_index++)
						{

							// The members_list_head start where the current interface ends 
							min_sharp_object_member* members_list_head = (min_sharp_object_member*)(current_interface + 1);

							min_sharp_object *object = members_list_head[member_index].value;
							if (min_sharp_null !=  object)
							{
								object_node* reached_object_node;
								fcr = get_object_node_from_object(&reached_object_node, object);
								if (function_call_result_fail == fcr)
								{
									goto fail;
								}
								if (garbage_collection_flags_clear == reached_object_node->garbage_collection_flags)
								{
									reached_object_node->garbage_collection_flags = garbage_collection_flags_reached;
								}
							}
						}
					}
				}
				current->garbage_collection_flags = garbage_collection_flags_scanned;
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
				object_node* node;
				fcr = get_object_node_from_object(&node, current_scope->scope_variables[i]);
				if (function_call_result_fail == fcr)
				{
					goto fail;
				}
				if (node->garbage_collection_flags == garbage_collection_flags_clear)
				{
					node->garbage_collection_flags = garbage_collection_flags_reached;
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
		if (garbage_collection_flags_clear == current_object_node->garbage_collection_flags)
		{
			fcr = system_services_instance->free_memory(current_object_node);
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
		}
		else
		{
			current_object_node->garbage_collection_flags = garbage_collection_flags_clear;
			previous_node = current_object_node;
		}
		current_object_node = next;
	}

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
		fcr = system_services_instance->free_memory(current);
		if (function_call_result_fail == fcr)
			goto fail;
		current = next;
	}

	// free the scopes stack
	scope_variables_node *current_scope = this_instance->data->scope_variables_stack_head;
	while (min_sharp_null != current_scope)
	{
		scope_variables_node* next_scope = current_scope->next_scope;
		fcr = system_services_instance->free_memory(current_scope);
		if (function_call_result_fail == fcr)
			goto fail;
		current_scope = next_scope;
	}

	// free this instace data
	fcr = system_services_instance->free_memory(this_instance->data);
	if (function_call_result_fail == fcr)
		goto fail;

	// free this instace
	fcr = system_services_instance->free_memory(this_instance);
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

	fcr = system_services_instance->allocate_memory(&this_instance, sizeof(managed_memory_services));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	fcr = system_services_instance->allocate_memory(&data, sizeof(managed_memory_services_data));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	data->object_list_head = min_sharp_null;
	data->scope_variables_stack_head = min_sharp_null;
	data->system_services_instance = system_services_instance;
	this_instance->data = data;
	this_instance->push_scope = &push_scope;
	this_instance->pop_scope = &pop_scope;
	this_instance->allocate_object = &allocate_object;
	this_instance->allocate__primitive_object = &allocate__primitive_object;
	this_instance->collect_garbage = &collect_garbage;
	this_instance->release = &release_managed_memory_services;

	*result = this_instance;
	return function_call_result_success;

fail:
	return function_call_result_fail;
}
