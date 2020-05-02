#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/runtime_services.h"

void test_runtime_services_factory()
{
	function_call_result fcr;
	runtime_services *runtime_services_instance = min_sharp_null;
	system_services *system_services_instance = min_sharp_null;


	start_test("system_list_factory_test");
	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory call");
	test_assertion(min_sharp_null != runtime_services_instance, "system_services_instance not null");

	fcr = runtime_services_factory(&runtime_services_instance, system_services_instance);
	test_assertion(fcr == function_call_result_success, "runtime_services_factory call");
	test_assertion(min_sharp_null != runtime_services_instance, "runtime_services_instance not null");

	end_test();
}

void runtime_services_tests()
{
	test_runtime_services_factory();
}