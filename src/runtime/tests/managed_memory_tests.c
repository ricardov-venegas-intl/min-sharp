#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/managed_memory_services.h"


static system_services* system_services_instance = min_sharp_null;

static min_sharp_interface_intrinsicts test_min_sharp_interface_intrinsicts;

typedef struct sample_interface_prototype_struct
{
	min_sharp_interface_intrinsicts* type_info;
	system_services* system_services_instance;
	unsigned_int_16 number_of_members;
	min_sharp_object members[];
} sample_interface_prototype;

typedef struct
{
	min_sharp_interface_intrinsicts* type_info;
	system_services* system_services_instance;
	unsigned_int_16 number_of_members;
	min_sharp_object *member1;
} sample_interface1;

typedef struct
{
	min_sharp_interface_intrinsicts* type_info;
	system_services* system_services_instance;
	unsigned_int_16 number_of_members;
	min_sharp_object *member1;
	min_sharp_object *member2;
	min_sharp_object *member3;
} sample_interface3;

typedef struct
{
	min_sharp_interface_intrinsicts* type_info;
	system_services* system_services_instance;
	unsigned_int_16 number_of_members;
	min_sharp_object *member1;
	min_sharp_object *member2;
} sample_interface2;

typedef struct interface_iterator_data_struct
{
	sample_interface_prototype* sample_interface_prototype;
	unsigned_int_16 current;
	system_services* system_services_instance;
} interface_iterator_data;

function_call_result member_iterator_HasNext(runtime_iterator* this_instance, min_sharp_boolean* hasNext)
{
	interface_iterator_data* data = (interface_iterator_data*)this_instance->runtime_iterator_data;

	*hasNext = (data->current <= (data->sample_interface_prototype->number_of_members));
	return function_call_result_success;
}

function_call_result member_iterator_Next(runtime_iterator* this_instance, void** next)
{
	interface_iterator_data* data = (interface_iterator_data*)this_instance->runtime_iterator_data;

	*next = &(data->sample_interface_prototype->members[data->current]);
	data->current++;
	return function_call_result_success;
}

function_call_result member_iterator_Release(runtime_iterator* this_instance)
{
	interface_iterator_data* data = (interface_iterator_data*)this_instance->runtime_iterator_data;
	system_services* system_services_instance = data->system_services_instance;

	system_services_instance->free_memory(system_services_instance, data);
	system_services_instance->free_memory(system_services_instance, this_instance);
	return function_call_result_success;
}

function_call_result member_iterator_factory(system_services* system_services_instance, sample_interface_prototype* target, runtime_iterator** new_iterator)
{
	function_call_result fcr;
	interface_iterator_data* data;
	runtime_iterator *iterator;

	fcr = system_services_instance->allocate_memory(system_services_instance, &data, sizeof(data));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	data->current = 0;
	data->sample_interface_prototype = target;
	data->system_services_instance = system_services_instance;

	system_services_instance->allocate_memory(system_services_instance, &iterator, sizeof(runtime_iterator));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	iterator->HasNext = member_iterator_HasNext;
	iterator->Next = member_iterator_Next;
	iterator->Release = member_iterator_Release;
	iterator->runtime_iterator_data = (void*)data;

	*new_iterator = iterator;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}

function_call_result GetMemberIterator(min_sharp_interface* this_instance, runtime_iterator** iterator)
{
	function_call_result fcr;

	sample_interface_prototype* interface_prototype = (sample_interface_prototype*) this_instance;
	fcr = member_iterator_factory(interface_prototype->system_services_instance, interface_prototype, iterator);
	return fcr;
}

typedef struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	system_services* system_services_instance;
	object_flags objectFlag;
	unsigned_int_16 number_of_interfaces;
	sample_interface3 interface3;
	sample_interface1 interface1;
	sample_interface2 interface2;
} test_object;

typedef struct object_iterator_data_struct
{
	test_object* target_object;
	unsigned_int_16 current;
	system_services* system_services_instance;
} object_iterator_data;

function_call_result object_iterator_HasNext(runtime_iterator* this_instance, min_sharp_boolean* hasNext)
{
	object_iterator_data* data = (object_iterator_data*)this_instance->runtime_iterator_data;

	*hasNext = (data->current <= 2);
	return function_call_result_success;
}


function_call_result IterateReferencedObjects(min_sharp_object* this_instance, runtime_iterator_function iteration_function, void* context)
{
	function_call_result fcr;
	test_object* current_object = (test_object*) this_instance;

	if (min_sharp_null != current_object->interface3.member1)
	{
		fcr = iteration_function((void*)(current_object->interface3.member1), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}

	if (min_sharp_null != current_object->interface3.member2)
	{
		fcr = iteration_function((void*)(current_object->interface3.member2), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}

	if (min_sharp_null != current_object->interface3.member3)
	{
		fcr = iteration_function((void*)(current_object->interface3.member3), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}
	if (min_sharp_null != current_object->interface1.member1)
	{
		fcr = iteration_function((void*)(current_object->interface1.member1), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}

	if (min_sharp_null != current_object->interface2.member1)
	{
		fcr = iteration_function((void*)(current_object->interface2.member1), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}

	if (min_sharp_null != current_object->interface2.member2)
	{
		fcr = iteration_function((void*)(current_object->interface2.member2), context);
		if (function_call_result_fail == fcr)
		{
			goto fail;
		}
	}
	return function_call_result_success;

fail:
	return function_call_result_fail;
}


function_call_result GarbagoCollectionGetFlags(min_sharp_object* this_instance, object_flags* objectFlag)
{
	test_object* target = (test_object*)this_instance;
	*objectFlag = (target->objectFlag);
	return function_call_result_success;
}

function_call_result GarbagoCollectionSetFlags(min_sharp_object* this_instance, object_flags objectFlag)
{
	test_object* target = (test_object*)this_instance;
	target->objectFlag = objectFlag;
	return function_call_result_success;
}

function_call_result test_object_Initializer(system_services* system_services_instance, test_object* result_object)
{
	function_call_result fcr;
	min_sharp_object_intrinsicts* object_intrinsicts;

	fcr = system_services_instance->allocate_memory(system_services_instance , &object_intrinsicts, sizeof(min_sharp_object_intrinsicts));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	object_intrinsicts->garbage_collection_get_flags = GarbagoCollectionGetFlags;
	object_intrinsicts->garbage_collection_set_flags = GarbagoCollectionSetFlags;
	object_intrinsicts->iterate_referenced_objects = IterateReferencedObjects;
	object_intrinsicts->get_interface = min_sharp_null;
	object_intrinsicts->implements_interface = min_sharp_null;

	result_object->object_intrinsicts = object_intrinsicts;

	min_sharp_interface_intrinsicts*  shared_interface_intrinsicts;
	fcr = system_services_instance->allocate_memory(system_services_instance, &shared_interface_intrinsicts, sizeof(min_sharp_interface_intrinsicts));
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}
	shared_interface_intrinsicts->GetInterfaceName = min_sharp_null;

	result_object->number_of_interfaces = 3;
	result_object->system_services_instance = system_services_instance;
	result_object->interface1.system_services_instance = system_services_instance;
	result_object->interface1.number_of_members = 1;
	result_object->interface1.type_info = shared_interface_intrinsicts;
	result_object->interface1.member1 = min_sharp_null;

	result_object->interface2.system_services_instance = system_services_instance;
	result_object->interface2.number_of_members = 2;
	result_object->interface2.type_info = shared_interface_intrinsicts;
	result_object->interface2.member1 = min_sharp_null;
	result_object->interface2.member2 = min_sharp_null;

	result_object->interface3.system_services_instance = system_services_instance;
	result_object->interface3.number_of_members = 3;
	result_object->interface3.type_info = shared_interface_intrinsicts;
	result_object->interface3.member1 = min_sharp_null;
	result_object->interface3.member2 = min_sharp_null;
	result_object->interface3.member3 = min_sharp_null;

	return function_call_result_success;

fail:
	return function_call_result_fail;
}


static function_call_result build_managed_memory_services(managed_memory_services** managed_memory_services_instance)
{
	function_call_result fcr;

	fcr = managed_memory_services_factory(managed_memory_services_instance, system_services_instance);
	test_assertion(fcr == function_call_result_success, "managed_memory_services_factory call");
	test_assertion(min_sharp_null != managed_memory_services_instance, "managed_memory_services_instance not null");

	return fcr;
}

static void managed_memory_services_build_and_release_test()
{
	function_call_result fcr;
	managed_memory_services* managed_memory_services_instance;

	start_test("managed_memory_services_resease_test");
	build_managed_memory_services(&managed_memory_services_instance);

	test_assertion(min_sharp_null != managed_memory_services_instance->allocate_object, 
		"allocate_object is not null");
	test_assertion(min_sharp_null != managed_memory_services_instance->collect_garbage, 
		"collect_garbage is not null");
	test_assertion(min_sharp_null != managed_memory_services_instance->data, 
		"data is not null");
	test_assertion(min_sharp_null != managed_memory_services_instance->pop_scope, 
		"pop_scope is not null");
	test_assertion(min_sharp_null != managed_memory_services_instance->push_scope, 
		"push_scope is not null");
	test_assertion(min_sharp_null != managed_memory_services_instance->release, 
		"release is not null");
	if (min_sharp_null != managed_memory_services_instance->release)
	{
		fcr = managed_memory_services_instance->release(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success,
			"managed_memory_services_instance->release call");
	}
	end_test();
}

static void validate_object(test_object* mapped_object)
{
	test_assertion(mapped_object->number_of_interfaces == 3, "mapped_object->number_of_interfaces is 3");
	test_assertion(min_sharp_null == mapped_object->interface3.member1,
		"mapped_object->interface3.member1.value is null");
	test_assertion(min_sharp_null == mapped_object->interface3.member2,
		"mapped_object->interface3.member2.value is null");
	test_assertion(min_sharp_null == mapped_object->interface3.member3,
		"mapped_object->interface3.member3.value is null");

	test_assertion(min_sharp_null == mapped_object->interface2.member1,
		"mapped_object->interface2.member1.value is null");
	test_assertion(min_sharp_null == mapped_object->interface2.member2,
		"mapped_object->interface2.member2.value is null");

	test_assertion(min_sharp_null == mapped_object->interface1.member1,
		"mapped_object->interface1.member1.value is null");
}

static void managed_memory_services_happy_path()
{
	function_call_result fcr;
	managed_memory_services* managed_memory_services_instance;
	min_sharp_object* scope1[3];
	min_sharp_object* scope2[2];
	unsigned_int_64 total_allocated_memory, total_allocations, total_deallocations;

	start_test("managed_memory_services_resease_test");
	build_managed_memory_services(&managed_memory_services_instance);
	scope1[0] = scope1[1] = scope1[2] = min_sharp_null;
	fcr =managed_memory_services_instance->push_scope(managed_memory_services_instance, 3, scope1);

	// allocate object
	fcr =managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope1[1]),
		sizeof(test_object)		
		);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1],"scope1[1] is not null");
	test_object_Initializer(system_services_instance, (test_object *) scope1[1]);

	//Test allocations/deallocarions
	fcr =managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
	test_assertion(fcr == function_call_result_success, "get_counters call");
	test_assertion(1 == total_allocations, "number_of_allocationsis 1");
	test_assertion(0 == total_deallocations, "number_of_deallocations 0");
	test_assertion(1 * sizeof(test_object) < total_allocated_memory, "allocated memory 1");

	// test if mapping is correct
	test_object* mapped_object = (test_object*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}
	else
	{
		test_assertion(min_sharp_null != mapped_object, "min_sharp_null != mapped_object");
		return;
	}

	if (min_sharp_null != managed_memory_services_instance->collect_garbage) 
	{
		fcr = managed_memory_services_instance->collect_garbage(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(1 == total_allocations, "number_of_allocationsis 1");
		test_assertion(0 == total_deallocations, "number_of_deallocations 0");
		test_assertion(1 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	// allocate object, and store reference in object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(mapped_object->interface1.member1),
		sizeof(test_object)
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != mapped_object->interface1.member1, "scope1[1] is not null");
	test_object_Initializer(system_services_instance, (test_object*)mapped_object->interface1.member1);

	//Test allocations/deallocarions
	fcr = managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
	test_assertion(fcr == function_call_result_success, "get_counters call");
	test_assertion(2 == total_allocations, "number_of_allocationsis 1");
	test_assertion(0 == total_deallocations, "number_of_deallocations 0");
	test_assertion(2 * sizeof(test_object) < total_allocated_memory, "allocated memory 1");

	// test if mapping is correct
	if (min_sharp_null != mapped_object->interface1.member1)
	{
		validate_object((test_object *)mapped_object->interface1.member1);
	}

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(2 == total_allocations, "number_of_allocationsis 1");
		test_assertion(0 == total_deallocations, "number_of_deallocations 0");
		test_assertion(2 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	scope2[0] = scope2[1] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 2, scope2);

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope2[1]),
		sizeof(test_object)
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1], "scope1[1] is not null");
	test_object_Initializer(system_services_instance, (test_object*) scope2[1]);

	//Test allocations/deallocations
	managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
	test_assertion(3 == total_allocations, "number_of_allocationsis 1");
	test_assertion(0 == total_deallocations, "number_of_deallocations 0");
	test_assertion(3 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");

	// test if mapping is correct
	mapped_object = (test_object*)scope2[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// clear reference to object1, and with that object 2
	scope1[1] = min_sharp_null;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
		//Test allocations/deallocations
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(3 == total_allocations, "number_of_allocationsis 1");
		test_assertion(2 == total_deallocations, "number_of_deallocations 0");
		test_assertion(3 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	fcr = managed_memory_services_instance->pop_scope(managed_memory_services_instance);
	fcr = managed_memory_services_instance->pop_scope(managed_memory_services_instance);

	if (min_sharp_null != managed_memory_services_instance->release)
	{
		fcr = managed_memory_services_instance->release(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success,
			"managed_memory_services_instance->release call");
	}

	end_test();
}


static void managed_memory_services_gc_on_empty()
{
	function_call_result fcr;
	managed_memory_services* managed_memory_services_instance;
	unsigned_int_64 total_allocated_memory, total_allocations, total_deallocations;

	start_test("managed_memory_services_gc_on_empty");
	build_managed_memory_services(&managed_memory_services_instance);

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(0 == total_allocations, "number_of_allocationsis 1");
		test_assertion(0 == total_deallocations, "number_of_deallocations 0");
		test_assertion(0 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	end_test();
}


static void managed_memory_services_only_object()
{
	function_call_result fcr;
	managed_memory_services* managed_memory_services_instance;
	min_sharp_object* scope1[3];
	min_sharp_object* scope2[2];
	unsigned_int_16 object1_interfaces_sized[3];
	unsigned_int_64 total_allocated_memory, total_allocations, total_deallocations;

	start_test("managed_memory_services_resease_test");
	build_managed_memory_services(&managed_memory_services_instance);
	scope1[0] = scope1[1] = scope1[2] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 3, scope1);

	object1_interfaces_sized[0] = 3;
	object1_interfaces_sized[1] = 1;
	object1_interfaces_sized[2] = 2;

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope1[1]),
		sizeof(test_object));
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1], "scope1[1] is not null");
	test_object_Initializer(system_services_instance, (test_object*) scope1[1]);

	//Test allocations/deallocarions
	managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
	test_assertion(1 == total_allocations, "number_of_allocationsis 1");
	test_assertion(0 == total_deallocations, "number_of_deallocations 0");
	test_assertion(1 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");

	// test if mapping is correct
	test_object* mapped_object = (test_object*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// remove only instance
	scope1[1] = min_sharp_null;
	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(1 == total_allocations, "number_of_allocationsis 1");
		test_assertion(1 == total_deallocations, "number_of_deallocations 0");
		test_assertion(1 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	scope2[0] = scope2[1] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 2, scope2);

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope2[1]),
		sizeof(test_object));
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope2[1], "scope1[1] is not null");
	test_object_Initializer(system_services_instance, (test_object*) scope2[1]);

	//Test allocations/deallocations
	managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
	test_assertion(2 == total_allocations, "number_of_allocationsis 1");
	test_assertion(1 == total_deallocations, "number_of_deallocations 0");
	test_assertion(2 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");

	// test if mapping is correct
	mapped_object = (test_object*)scope2[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// clear reference to object2
	scope2[1] = min_sharp_null;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
		//Test allocations/deallocations
		managed_memory_services_instance->get_counters(managed_memory_services_instance, &total_allocated_memory, &total_allocations, &total_deallocations);
		test_assertion(2 == total_allocations, "number_of_allocationsis 1");
		test_assertion(2 == total_deallocations, "number_of_deallocations 0");
		test_assertion(2 * sizeof(test_object) <= total_allocated_memory, "allocated memory 1");
	}

	fcr = managed_memory_services_instance->pop_scope(managed_memory_services_instance);
	fcr = managed_memory_services_instance->pop_scope(managed_memory_services_instance);

	if (min_sharp_null != managed_memory_services_instance->release)
	{
		fcr = managed_memory_services_instance->release(managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success,
			"managed_memory_services_instance->release call");
	}

	end_test();
}


void managed_memory_services_tests()
{
	system_services_factory(&system_services_instance);
	managed_memory_services_build_and_release_test();
	managed_memory_services_happy_path();
	managed_memory_services_gc_on_empty();
	managed_memory_services_only_object();
	if (min_sharp_null != system_services_instance)
	{
		system_services_instance->release(system_services_instance);
	}
}