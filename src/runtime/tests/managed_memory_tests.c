#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/managed_memory_services.h"


typedef struct system_services_struct system_services;

static int number_of_allocations;
static int number_of_deallocations;

static system_services mock_system_services;
static system_services* system_services_instance = min_sharp_null;

static function_call_result free_memory_mock(void* memory)
{
	number_of_deallocations++;
	return system_services_instance->free_memory(memory);
}

static function_call_result allocate_memory_mock(void** result, int size)
{
	number_of_allocations++;
	return system_services_instance->allocate_memory(result, size);
}

static function_call_result release_mock(system_services* this_instance)
{
	return function_call_result_success;
}

static void initialize_mock_system_services()
{
	function_call_result fcr;
	fcr = system_services_factory(&system_services_instance);
	mock_system_services.allocate_memory = &allocate_memory_mock;
	mock_system_services.free_memory = &free_memory_mock;
	mock_system_services.release = &release_mock;
}

static function_call_result build_managed_memory_services(managed_memory_services** managed_memory_services_instance)
{
	function_call_result fcr;


	fcr = managed_memory_services_factory(managed_memory_services_instance, &mock_system_services);
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
	test_assertion(min_sharp_null != managed_memory_services_instance->allocate__primitive_object, 
		"allocate__primitive_object is not null");
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

typedef struct 
{
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
	min_sharp_object_member* members_list_head;
	min_sharp_object_member member1;
} sample_interface1;

typedef struct 
{
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
	min_sharp_object_member* members_list_head;
	min_sharp_object_member member1;
	min_sharp_object_member member2;
	min_sharp_object_member member3;
} sample_interface3;

typedef struct 
{
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
	min_sharp_object_member* members_list_head;
	min_sharp_object_member member1;
	min_sharp_object_member member2;
} sample_interface2;

typedef struct
{
	function_call_result(*__GetInterface)(min_sharp_object** exception, min_sharp_interface** result, internal_string interfaceName);
	min_sharp_object_header* object_header;
	unsigned_int_16 number_of_interfaces;
	min_sharp_interface* interfaces_list_head;
	sample_interface3 interface3;
	sample_interface1 interface1;
	sample_interface2 interface2;
} object1;

static void validate_object(object1* mapped_object)
{
	test_assertion(mapped_object->number_of_interfaces == 3, "mapped_object->number_of_interfaces is 3");
	test_assertion(min_sharp_null == mapped_object->__GetInterface, "__GetInterfaceis null");
	test_assertion(((void*)mapped_object->interfaces_list_head) == (void*)&(mapped_object->interface3),
		"mapped_object->interfaces_list_head == &(mapped_object->interface3");
	test_assertion(min_sharp_null == mapped_object->interface3.member1.value,
		"mapped_object->interface3.member1.value is null");
	test_assertion(0 == mapped_object->interface3.member1.member_id,
		"mapped_object->interface3.member1.member_id is 0");
	test_assertion(min_sharp_null == mapped_object->interface3.member2.value,
		"mapped_object->interface3.member2.value is null");
	test_assertion(1 == mapped_object->interface3.member2.member_id,
		"mapped_object->interface3.member2.member_id is 1");
	test_assertion(min_sharp_null == mapped_object->interface3.member3.value,
		"mapped_object->interface3.member3.value is null");
	test_assertion(2 == mapped_object->interface3.member3.member_id,
		"mapped_object->interface3.member2.member_id is 2");

	test_assertion(min_sharp_null == mapped_object->interface2.member1.value,
		"mapped_object->interface2.member1.value is null");
	test_assertion(0 == mapped_object->interface2.member1.member_id,
		"mapped_object->interface2.member1.member_id is 0");
	test_assertion(min_sharp_null == mapped_object->interface2.member2.value,
		"mapped_object->interface2.member2.value is null");
	test_assertion(1 == mapped_object->interface2.member2.member_id,
		"mapped_object->interface2.member2.member_id is 1");

	test_assertion(min_sharp_null == mapped_object->interface1.member1.value,
		"mapped_object->interface1.member1.value is null");
	test_assertion(0 == mapped_object->interface1.member1.member_id,
		"mapped_object->interface1.member1.member_id is 0");
}

static void managed_memory_services_happy_path()
{
	function_call_result fcr;
	managed_memory_services* managed_memory_services_instance;
	min_sharp_object* scope1[3];
	min_sharp_object* scope2[2];
	unsigned_int_16 object1_interfaces_sized[3];

	start_test("managed_memory_services_resease_test");
	build_managed_memory_services(&managed_memory_services_instance);
	scope1[0] = scope1[1] = scope1[2] = min_sharp_null;
	fcr =managed_memory_services_instance->push_scope(managed_memory_services_instance, 3, scope1);

	object1_interfaces_sized[0] = 3;
	object1_interfaces_sized[1] = 1;
	object1_interfaces_sized[2] = 2;

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	// allocate object
	fcr =managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope1[1]),
		3,
		object1_interfaces_sized
		);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1],"scope1[1] is not null");
	
	//Test allocations/deallocarions
	test_assertion(1 == number_of_allocations, "number_of_allocationsis 1");
	test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");

	// test if mapping is correct
	object1* mapped_object = (object1*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage) 
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		test_assertion(0 == number_of_allocations, "number_of_allocationsis 0");
		test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");

	}


	scope2[0] = scope2[1] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 2, scope2);

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope2[1]),
		3,
		object1_interfaces_sized
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1], "scope1[1] is not null");

	//Test allocations/deallocations
	test_assertion(1 == number_of_allocations, "number_of_allocationsis 1");
	test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");

	// test if mapping is correct
	mapped_object = (object1*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// clear reference to object1
	scope2[1] = min_sharp_null;

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
		//Test allocations/deallocations
		test_assertion(0 == number_of_allocations, "number_of_allocationsis 0");
		test_assertion(1 == number_of_deallocations, "number_of_deallocations 1");

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
	min_sharp_object* scope1[3];
	min_sharp_object* scope2[2];
	unsigned_int_16 object1_interfaces_sized[3];

	start_test("managed_memory_services_gc_on_empty");
	build_managed_memory_services(&managed_memory_services_instance);

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		test_assertion(0 == number_of_allocations, "number_of_allocationsis 0");
		test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");
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

	start_test("managed_memory_services_resease_test");
	build_managed_memory_services(&managed_memory_services_instance);
	scope1[0] = scope1[1] = scope1[2] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 3, scope1);

	object1_interfaces_sized[0] = 3;
	object1_interfaces_sized[1] = 1;
	object1_interfaces_sized[2] = 2;

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope1[1]),
		3,
		object1_interfaces_sized
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1], "scope1[1] is not null");

	//Test allocations/deallocarions
	test_assertion(1 == number_of_allocations, "number_of_allocationsis 1");
	test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");

	// test if mapping is correct
	object1* mapped_object = (object1*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	// remove only instance
	scope1[1] = min_sharp_null;
	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");

		//Test allocations/deallocarions
		test_assertion(0 == number_of_allocations, "number_of_allocationsis 0");
		test_assertion(1 == number_of_deallocations, "number_of_deallocations 0");

	}


	scope2[0] = scope2[1] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 2, scope2);

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope2[1]),
		3,
		object1_interfaces_sized
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope2[1], "scope1[1] is not null");

	//Test allocations/deallocations
	test_assertion(1 == number_of_allocations, "number_of_allocationsis 1");
	test_assertion(0 == number_of_deallocations, "number_of_deallocations 0");

	// test if mapping is correct
	mapped_object = (object1*)scope2[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	// clear reference to object2
	scope2[1] = min_sharp_null;

	// Reset number of allocations/deallocations 
	number_of_allocations = 0;
	number_of_deallocations = 0;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
		//Test allocations/deallocations
		test_assertion(0 == number_of_allocations, "number_of_allocationsis 0");
		test_assertion(1 == number_of_deallocations, "number_of_deallocations 1");

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
	initialize_mock_system_services();
	managed_memory_services_build_and_release_test();
	managed_memory_services_happy_path();
	managed_memory_services_gc_on_empty();
	managed_memory_services_only_object();
	if (min_sharp_null != system_services_instance)
	{
		system_services_instance->release(system_services_instance);
	}
}