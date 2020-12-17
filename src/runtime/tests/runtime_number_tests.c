#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/Types/runtime_number.h"


void test_runtime_number_build()
{
	function_call_result fcr;

	start_test("test_runtime_number_build");

	runtime_services* runtime_services_instance = min_sharp_null;
	initialize_runtime(&runtime_services_instance);

	min_sharp_object new_number;
	min_sharp_object exception;
	fcr = runtime_services_instance->build_number(runtime_services_instance, &exception, &new_number);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");

	end_test();
}

void runtime_number_tests()
{
	test_runtime_number_build();
}