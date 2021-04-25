#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/Types/runtime_number.h"

typedef struct min_sharp_number_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	double value;
} min_sharp_number;

void test_runtime_number_build()
{
	function_call_result fcr;

	start_test("test_runtime_number_build");

	runtime_services* runtime_services_instance = min_sharp_null;
	initialize_runtime(&runtime_services_instance);

	min_sharp_number *new_number;
	min_sharp_object *exception;
	fcr = runtime_services_instance->build_number(runtime_services_instance, &exception, (min_sharp_object **) &new_number, 0.0);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(new_number->value == 0.0, "new_number->value == 0.0");

	end_test();
}


void test_runtime_number_add_zero_plus_zero()
{
	function_call_result fcr;

	start_test("test_runtime_number_add_zero_plus_zero");

	runtime_services* runtime_services_instance = min_sharp_null;
	initialize_runtime(&runtime_services_instance);

	// Create left number
	min_sharp_object* exception;
	min_sharp_number* left_number;
	fcr = runtime_services_instance->build_number(
		runtime_services_instance, 
		&exception, 
		(min_sharp_object**)&left_number,
		0.0);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(left_number->value == 0.0, "exception->value == 0.0");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");

	// Right NUmber
	min_sharp_number* right_number;
	fcr = runtime_services_instance->build_number(
		runtime_services_instance, 
		&exception, 
		(min_sharp_object**)&right_number,
		0.0);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(right_number->value == 0.0, "right_number->value == 0.0");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");

	min_sharp_number* result_number;
	
	// Perform Add Operation
	Runtime_AdditionOperator* additionOperatorInterface;
	fcr = left_number->object_intrinsicts->get_interface(
		(min_sharp_object *)left_number,
		runtime_services_instance, 
		(min_sharp_interface**)&additionOperatorInterface, 
		RUNTIME_ADDITION_OPERATOR_INTERFACE_NAME);
	test_assertion(fcr == function_call_result_success, "new_number1->object_intrinsicts->get_interface call");

	fcr = additionOperatorInterface->Add->function_implementation(
		runtime_services_instance,
		(min_sharp_object*)left_number,
		(min_sharp_function *) &(additionOperatorInterface->Add),
		&exception,
		(min_sharp_object**) &result_number,
		(min_sharp_object*) right_number);
	test_assertion(fcr == function_call_result_success, "additionOperatorInterface->Add.function_implementation call");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");
	test_assertion(min_sharp_null != result_number, "min_sharp_null != new_number3");

	// Verify result
	if (min_sharp_null != result_number)
	{
		test_assertion(result_number->value == 0.0, "result_number->value == 0.0");
	}	

	end_test();
}

void runtime_number_tests()
{
	test_runtime_number_build();
	test_runtime_number_add_zero_plus_zero();
}