#include "test.h"
#include "../min-sharp-runtime/services/internal/system_services.h"
#include <malloc.h>


void system_services_factory_test()
{
	int cr;
	system_services* system_services_instance;

	start_test("system_services_factory_test");

	cr = system_services_factory(&system_services_instance);
	test_assertion(cr == function_call_result_success, "system_services_factory");
	test_assertion(NULL != system_services_instance, "system_services_instance not null");

	if (NULL != system_services_instance)
	{
		test_assertion(NULL != system_services_instance->release, "system_services_instance->release not null");
		test_assertion(NULL != system_services_instance->allocate_memory, "system_services_instance->allocate_memory not null");
		test_assertion(NULL != system_services_instance->free_memory, "system_services_instance not null");
		if (NULL != system_services_instance->release)
		{
			cr = system_services_instance->release(system_services_instance);
			test_assertion(function_call_result_success == cr, "system_services_instance->release sucessfull");
		}
	}
	end_test();
}

void system_services_memory_allocation_tests()
{
	int cr;
	void* memory= NULL;

	start_test("system_services_memory_allocation_tests");
	system_services* system_services_instance;

	cr = system_services_factory(&system_services_instance);
	test_assertion(cr == function_call_result_success, "system_services_factory");
	test_assertion(NULL != system_services_instance, "system_services_instance not null");

	if (NULL != system_services_instance)
	{
		cr = system_services_instance->allocate_memory(system_services_instance, &memory, 1);
		test_assertion(function_call_result_success == cr, "system_services_instance->allocate_memory successfull");
		test_assertion(NULL != memory, "one byte allocated");

		cr = system_services_instance->free_memory(system_services_instance, memory);
		test_assertion(function_call_result_success == cr, "system_services_instance->free_memory Successfull");

		cr = system_services_instance->allocate_memory(system_services_instance, &memory, 0);
		test_assertion(function_call_result_fail == cr, "zero byte not allocated (failed)");
		test_assertion(NULL == memory, "zero byte not allocated");
		cr = system_services_instance->free_memory(system_services_instance, memory);
		test_assertion(function_call_result_fail == cr, "system_services_instance->free_memory Successfull");

		cr = system_services_instance->allocate_memory(system_services_instance, &memory, 1024);
		test_assertion(function_call_result_success == cr, "system_services_instance->allocate_memory successfull");
		test_assertion(NULL != memory, "one Kbyte allocated");
		cr = system_services_instance->free_memory(system_services_instance, memory);
		test_assertion(function_call_result_success == cr, "system_services_instance->free_memory Successfull");

		cr = system_services_instance->release(system_services_instance);
		test_assertion(function_call_result_success == cr, "system_services_instance->release Successfull");
	}
	end_test();
}

void system_services_tests()
{
	system_services_factory_test();
	system_services_memory_allocation_tests();
}
