#include "main.h"
#include "test.h"
#include "../min-sharp-runtime/Types/runtime_number.h"
#include <Types/decNumber/decNumber.h>

typedef struct min_sharp_number_struct
{
	min_sharp_object_intrinsicts* object_intrinsicts;
	object_flags object_flag;
	decNumber value;
} min_sharp_number;



void test_runtime_number_build()
{
	function_call_result fcr;

	start_test("test_runtime_number_build");

	runtime_services* runtime_services_instance = min_sharp_null;
	initialize_runtime(&runtime_services_instance);

	min_sharp_number *new_number;
	min_sharp_object *exception;
	fcr = runtime_services_instance->build_number(runtime_services_instance, &exception, (min_sharp_object **) &new_number, "1.0");
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	//TODO: Re-impleted assertion
	//test_assertion(new_number->value == "0.0", "new_number->value == 0.0");

	end_test();
}

void test_add_operation(
	internal_string left_operand, 
	internal_string right_operand,
	internal_string expected_result)
{
	function_call_result fcr;
	min_sharp_object* exception;
	min_sharp_number* left_number;
	min_sharp_number* right_number;
	min_sharp_number* expected_result_number;

	// Initialize runtime
	runtime_services* runtime_services_instance = min_sharp_null;
	initialize_runtime(&runtime_services_instance);

	// Create left number
	fcr = runtime_services_instance->build_number(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&left_number,
		left_operand);

	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");

	// Right Number
	fcr = runtime_services_instance->build_number(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&right_number,
		right_operand);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");

	// expected result Number
	fcr = runtime_services_instance->build_number(
		runtime_services_instance,
		&exception,
		(min_sharp_object**)&expected_result_number,
		expected_result);
	test_assertion(fcr == function_call_result_success, "runtime_services_instance->build_number call");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");


	// Perform Add Operation: Get Interface
	Runtime_AdditionOperator* additionOperatorInterface;
	fcr = left_number->object_intrinsicts->get_interface(
		(min_sharp_object*)left_number,
		runtime_services_instance,
		(min_sharp_interface**)&additionOperatorInterface,
		RUNTIME_ADDITION_OPERATOR_INTERFACE_NAME);
	test_assertion(fcr == function_call_result_success, "new_number1->object_intrinsicts->get_interface call");

	// Perform Add Operation: Execute_add
	min_sharp_number* result_number;
	fcr = additionOperatorInterface->Add->function_implementation(
		runtime_services_instance,
		(min_sharp_object*)left_number,
		(min_sharp_function*)&(additionOperatorInterface->Add),
		&exception,
		(min_sharp_object**)&result_number,
		(min_sharp_object*)right_number);
	test_assertion(fcr == function_call_result_success, "additionOperatorInterface->Add.function_implementation call");
	test_assertion(min_sharp_null == exception, "min_sharp_null == exception");
	test_assertion(min_sharp_null != result_number, "min_sharp_null != new_number3");

	// Verify result
	if (min_sharp_null != result_number)
	{
		Runtime_EqualityOperator* equalityOperatorInterface;
		fcr = expected_result_number->object_intrinsicts->get_interface(
			(min_sharp_object*)expected_result_number,
			runtime_services_instance,
			(min_sharp_interface**)&equalityOperatorInterface,
			RUNTIME_EQUALITY_OPERATOR_INTERFACE_NAME);
		test_assertion(fcr == function_call_result_success, 
			"new_number1->object_intrinsicts->get_interface call");

		// TODO: Fix when boolean is implemented
		min_sharp_object number_are_equal;
		equalityOperatorInterface->IsEquals->function_implementation(
			runtime_services_instance,
			expected_result_number,
			equalityOperatorInterface->IsEquals,
			(min_sharp_object**)&result_number,
			&number_are_equal,
			(min_sharp_object*)result_number);
	}

	runtime_services_instance->release(runtime_services_instance);
}

void test_runtime_number_add_zero_plus_zero()
{
	function_call_result fcr;

	start_test("test_runtime_number_add_zero_plus_zero");
	test_add_operation("0.0", "0.0", "0.0");
	end_test();
 }

void test_runtime_number_add_zero_plus_anything()
{
	function_call_result fcr;

	start_test("test_runtime_number_add_zero_plus_anything");
	test_add_operation("0.0", "1.0", "1.0");
	test_add_operation("0.0", "1111.11", "1111.11");
	test_add_operation("0.0", "0.000000011", "0.000000011");
	test_add_operation("0.0", "9999999999", "9999999999");
	
	test_add_operation("0.0", "-1.0", "-1.0");
	test_add_operation("0.0", "-1111.11", "-1111.11");
	test_add_operation("0.0", "-0.000000011", "-0.000000011");
	test_add_operation("0.0", "-9999999999.0", "-9999999999.0");

	test_add_operation("1.0", "0.0", "1.0");
	test_add_operation("1111.11", "0.0", "1111.11");
	test_add_operation("0.000000011", "0.0", "0.000000011");
	test_add_operation("9999999999.0", "0.0", "9999999999.0");

	test_add_operation("-1.", "0.0", "-1.0");
	test_add_operation("-1111.11", "0.0", "-1111.11");
	test_add_operation("-0.000000011", "0.0", "-0.000000011");
	test_add_operation("-9999999999.0", "0.0", "-9999999999.0");

	end_test();
}

void test_runtime_number_add_negative_numbers()
{
	function_call_result fcr;

	start_test("test_runtime_number_add_zero_plus_anything");
	test_add_operation("-1.0", "1.0", "1.0");
	test_add_operation("-1111.11", "1111.11", "1.0");
	test_add_operation("-0.000000011", "0.000000011", "0.0000000");
	test_add_operation("-9999999999.0", "9999999999.0", "1.0");

	test_add_operation("1.0", "-2.0", "-1.0");
	test_add_operation("-1.0", "2.0", "1.0");
	test_add_operation("-1.0", "-1.0", "-2.0");

	test_add_operation("1.75", "-2.0", "-.25");
	test_add_operation("-1.75", "2.0", ".25");

	test_add_operation("-1.0", "-9.0", "-10.00");

	end_test();
}

void test_runtime_number_add_positive_numbers()
{
	function_call_result fcr;

	start_test("test_runtime_number_add_zero_plus_anything");
	test_add_operation("1.0", "1.0", "2.0");
	test_add_operation("1111.11", "1111.11", "2222.1");
	test_add_operation("0.0000011", "0.0000011", "0.0000022");
	test_add_operation("9999999999.0", "9999999999.0", "19999999998.0");

	test_add_operation("1.75", "2.0", "3.25");
	test_add_operation("1.0", "2.75", "3.25");
	test_add_operation("1.0", "9.0", "10.00");

	end_test();
}

void runtime_number_tests()
{
	test_runtime_number_build();
	test_runtime_number_add_zero_plus_zero();
	test_runtime_number_add_zero_plus_anything();
	test_runtime_number_add_negative_numbers();
	test_runtime_number_add_positive_numbers();
}