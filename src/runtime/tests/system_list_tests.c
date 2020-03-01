#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/system_list.h"


void test_factory()
{
	function_call_result fcr;
	system_services *system_services_instance;
	system_list *list;

	start_test("system_list_factory_test");

	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory");
	test_assertion(min_sharp_null != system_services_instance, "system_services_instance not null");

	if (min_sharp_null != system_services_instance)
	{
		fcr = system_list_factory(&list, system_services_instance);
		test_assertion(fcr == function_call_result_success, "system_list_factory");
		test_assertion(min_sharp_null != list, "list not null");
	}
	end_test();
}


void system_list_tests()
{
	test_factory();
}