#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/services/system_types_repository.h"
#include <string.h>

extern function_call_result initialize_types_repository();


void test_type(system_types_repository* system_types_repository_instance, internal_string type_name)
{
	function_call_result fcr;
	min_sharp_type_info* type_info;

	fcr = system_types_repository_instance->get_type_info(system_types_repository_instance, &type_info, type_name);
	test_assertion(fcr == function_call_result_success, "get_type_info(object_type)");
	test_assertion(min_sharp_null != type_info, "type_info not null");
	if (min_sharp_null != type_info)
	{
		test_assertion(_strcmpi(type_info->interface_name, type_name) == 0, "type_info->interface_name name match");
	}

}

void system_types_respository_tests()
{

	function_call_result fcr;
	start_test("system_types_respository_tests");
	system_services* system_services_instance;
	system_types_repository* system_types_repository_instance;

	fcr = system_services_factory(&system_services_instance);
	test_assertion(fcr == function_call_result_success, "system_services_factory");
	test_assertion(min_sharp_null != system_services_instance, "system_services_instance not null");

	if (min_sharp_null != system_services_instance)
	{
		fcr = system_repository_factory(&system_types_repository_instance, system_services_instance);
		test_assertion(function_call_result_success == fcr, "system_repository_factory");
		test_assertion(min_sharp_null != system_types_repository_instance, "system_types_repository_instance not null");

		if (min_sharp_null != system_types_repository_instance)
		{
			test_type(system_types_repository_instance, object_type_name);
			test_type(system_types_repository_instance, string_type_name);
			test_type(system_types_repository_instance, number_type_name);
			test_type(system_types_repository_instance, boolean_type_name);
			test_type(system_types_repository_instance, function_type_name);
			test_type(system_types_repository_instance, exception_type_name);
			test_type(system_types_repository_instance, runtime_exception_type_name);
			test_type(system_types_repository_instance, null_reference_exception_type_name);
			fcr = system_services_instance->release(system_services_instance);
			test_assertion(function_call_result_success == fcr, "system_services_instance->release(system_services_instance)");
		}
	}
	end_test();
}

