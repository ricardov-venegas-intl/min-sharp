#include "runtime_complex_object.h"


typedef struct min_sharp_interface_struct_mapped {
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
	min_sharp_object_member members[1];
} min_sharp_interface_mapped;

typedef struct min_sharp_object_header_struct_mapped {
	unsigned_int_8 garbage_collection_flags;
	unsigned_int_16 number_of_interfaces;
	min_sharp_interface interfaces[1];
} min_sharp_object_header_mapped;

typedef struct min_sharp_object_struct_mapped {
	min_sharp_object_intrinsicts* object_intrinsicts;
	min_sharp_object_header_mapped header;
} min_sharp_object_mapped;

static function_call_result get_interface_by_index(min_sharp_interface** result, min_sharp_object* object, unsigned_int_16 interface_index)
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


static function_call_result GarbageCollectionVisitMembersIfFlagClear(min_sharp_object* this_instance, min_sharp_object** exception, unsigned_int_8 objectFlag)
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

			min_sharp_object_mapped* object = (min_sharp_object_mapped *) members_list_head[member_index].value;
			if (min_sharp_null != object)
			{
				if (garbage_collection_flags_clear == object->header.garbage_collection_flags)
				{
					object->header.garbage_collection_flags = objectFlag;
				}
			}
		}
	}

	return function_call_result_success;

fail:
	return function_call_result_fail;
}
