#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/managed_memory_services.h"

static function_call_result build_managed_memory_services(managed_memory_services** managed_memory_services_instance)
{
	function_call_result fcr;

	system_services* system_services_instance = min_sharp_null;

	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory call");
	test_assertion(min_sharp_null != system_services_instance, "system_services_instance not null");

	if (min_sharp_null != system_services_instance)
	{
		fcr = managed_memory_services_factory(managed_memory_services_instance, system_services_instance);
		test_assertion(fcr == function_call_result_success, "managed_memory_services_factory call");
		test_assertion(min_sharp_null != managed_memory_services_instance, "managed_memory_services_instance not null");
	}
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

	// allocate object
	fcr =managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope1[1]),
		3,
		object1_interfaces_sized
		);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1],"scope1[1] is not null");

	// test if mapping is correct
	object1* mapped_object = (object1*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	if (min_sharp_null != managed_memory_services_instance->collect_garbage) 
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
	}


	scope2[0] = scope2[1] = min_sharp_null;
	fcr = managed_memory_services_instance->push_scope(managed_memory_services_instance, 2, scope2);

	// allocate object
	fcr = managed_memory_services_instance->allocate_object(
		managed_memory_services_instance,
		&(scope2[1]),
		3,
		object1_interfaces_sized
	);
	test_assertion(fcr == function_call_result_success, "allocate_object call");
	test_assertion(min_sharp_null != scope1[1], "scope1[1] is not null");

	// test if mapping is correct
	mapped_object = (object1*)scope1[1];
	if (min_sharp_null != mapped_object)
	{
		validate_object(mapped_object);
	}

	scope2[1] = min_sharp_null;

	if (min_sharp_null != managed_memory_services_instance->collect_garbage)
	{
		fcr = managed_memory_services_instance->collect_garbage(
			managed_memory_services_instance);
		test_assertion(fcr == function_call_result_success, "collect_garbage call");
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
	managed_memory_services_build_and_release_test();
	managed_memory_services_happy_path();	
}