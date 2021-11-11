#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/internal/system_unmanaged_data_manager.h"


void test_system_unmanaged_data_manager_factory()
{
	function_call_result fcr;
	system_services *system_services_instance;
	system_unmanaged_data_manager* unmanaged_data_manager;

	start_test("system_list_factory_test");

	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory");
	test_assertion(min_sharp_null != system_services_instance, "system_services_instance not null");

	if (min_sharp_null != system_services_instance)
	{
		fcr = system_unmanaged_data_manager_factory(&unmanaged_data_manager, system_services_instance);
		test_assertion(fcr == function_call_result_success, "system_unmanaged_data_manager_factory");
		test_assertion(min_sharp_null != unmanaged_data_manager, "unmanaged_data_manager not null");
		if (min_sharp_null != unmanaged_data_manager)
		{
			test_assertion(min_sharp_null != unmanaged_data_manager->create_list, "create_list not null");
			test_assertion(min_sharp_null != unmanaged_data_manager->release, "release not null");
			test_assertion(min_sharp_null != unmanaged_data_manager->release_list, "release_list not null");
			if (min_sharp_null != unmanaged_data_manager->release)
			{
				fcr = unmanaged_data_manager->release(unmanaged_data_manager);
				test_assertion(fcr == function_call_result_success, "unmanaged_data_manager->release");
			}
		}
	}
	end_test();
}

function_call_result enumerate_ints(system_unmanaged_data_structure* this_instance, void* element, void* data_context)
{
	int* current = (int*)element;
	int* context = (int*)data_context;
	test_assertion(*current == *context, "element == context");

	*context = *context + 1;
	return function_call_result_success;
}

function_call_result find_bigger(system_unmanaged_data_structure* this_instance, void* element, void* data_context, min_sharp_boolean* found)
{

	int* current = (int*)element;
	int* context = (int*)data_context;

	*found = *current > *context;
	return function_call_result_success;

}
void test_list_add_remove_exists_foreach(system_unmanaged_data_structure* list)
{
	function_call_result fcr;

	int a, b, c;
	min_sharp_boolean found;
	a = 1;
	b = 2;
	c = 3;
	fcr = list->add_element(list, &a);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &a, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_true == found, "list->exists(true)");

	fcr = list->exists(list, &b, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_false == found, "list->exists(false)");

	fcr = list->add_element(list, &b);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &b, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_true == found, "list->exists(true)");

	//remove the tail
	fcr = list->remove_element(list, &b);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &b, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_false == found, "list->exists(true)");

	fcr = list->exists(list, &a, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_true == found, "list->exists(true)");

	fcr = list->add_element(list, &c);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &c, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_true == found, "list->exists(true)");

	fcr = list->remove_element(list, &a);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &a, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_false == found, "list->exists(true)");

	fcr = list->remove_element(list, &c);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->exists(list, &c, &found);
	test_assertion(function_call_result_success == fcr, "list->exists");
	test_assertion(min_sharp_false == found, "list->exists(true)");

	fcr = list->add_element(list, &a);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->add_element(list, &b);
	test_assertion(fcr == function_call_result_success, "list->add_element");

	fcr = list->add_element(list, &c);
	test_assertion(fcr == function_call_result_success, "list->add_element");
	int context = a;
	fcr = list->for_each(list, enumerate_ints, &context);
	test_assertion(fcr == function_call_result_success, "list->for_each");	

	int *result= min_sharp_null;
	context = 2;
	found = min_sharp_false;
	fcr = list->find_first(list, find_bigger, &context, &result, & found);
	test_assertion(fcr == function_call_result_success, "list->find_first");
	test_assertion(3 == *result, "list->find_first(result)");
	test_assertion(min_sharp_true == found, "list->find_first(found)");

	result = min_sharp_null;
	context = 5;
	fcr = list->find_first(list, find_bigger, &context, &result, &found);
	test_assertion(fcr == function_call_result_success, "list->find_first");
	test_assertion(min_sharp_false == found, "list->find_first(found)");
	test_assertion(min_sharp_null == result, "list->find_first(result)(Not Modified)");

}

void test_list_operations()
{
	function_call_result fcr;
	system_services* system_services_instance;
	system_unmanaged_data_manager* unmanaged_data_manager;

	start_test("test_list_operations");

	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory");
	test_assertion(min_sharp_null != system_services_instance, "system_services_instance not null");

	if (min_sharp_null != system_services_instance)
	{
		fcr = system_unmanaged_data_manager_factory(&unmanaged_data_manager, system_services_instance);
		test_assertion(fcr == function_call_result_success, "system_unmanaged_data_manager_factory");
		test_assertion(min_sharp_null != unmanaged_data_manager, "unmanaged_data_manager not null");
		if (min_sharp_null != unmanaged_data_manager)
		{
			system_unmanaged_data_structure* list;
			fcr = unmanaged_data_manager->create_list(unmanaged_data_manager, &list);
			test_assertion(fcr == function_call_result_success, "unmanaged_data_manager->create_list");
			test_assertion(min_sharp_null != list, "list not null");

			test_list_add_remove_exists_foreach(list);

			fcr = unmanaged_data_manager->release_list(unmanaged_data_manager, list);
			test_assertion(fcr == function_call_result_success, "unmanaged_data_manager->release_list");

			fcr = unmanaged_data_manager->release(unmanaged_data_manager);
			test_assertion(fcr == function_call_result_success, "unmanaged_data_manager->release");
		}
	}
	end_test();
}

void system_list_tests()
{
	test_system_unmanaged_data_manager_factory();
	test_list_operations();
}