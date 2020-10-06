#pragma once

#include "../min-sharp-runtime.h"
#include "../min-sharp-runtime-function-prototypes.h"

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	min_sharp_function_2_arguments_type Add;
} Runtime_AdditionOperator;
const internal_string runtime_additionoperator_interface_name = "Runtime.AdditionOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Substract;
} Runtime_SubstractionOperator;

const internal_string runtime_substraction_operator_interface_name = "Runtime.SubstractionOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Multiply;
} Runtime_MultiplicationOperator;

const internal_string runtime_multiplication_operator_interface_name = "Runtime.MultiplicationOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Divide;
} Runtime_DivisionOperator;

const internal_string runtime_division_operator_interface_name = "Runtime.DivisionOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Remainder;
} Runtime_RemainderOperator;

const internal_string runtime_remainder_operator_interface_name = "Runtime.RemainderOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type IsEquals;
} Runtime_EqualityOperator;

const internal_string runtime_equality_operator_interface_name = "Runtime.EqualityOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type IsGreaterThan;
	min_sharp_function_2_arguments_type IsLowerThan;
} Runtime_RelationalOperator;

const internal_string runtime__relational_operator_interface_name = "Runtime.RelationalOperator";

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Or;
	min_sharp_function_2_arguments_type And;
	min_sharp_function_1_arguments_type Not;
} Runtime_BooleanOperator;


typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_0_arguments_type GetValue;
} Runtime_ReadOnlyProperty;


typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_1_arguments_type SetValue;
} Runtime_Property;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	Runtime_ReadOnlyProperty Code;
	Runtime_ReadOnlyProperty Message;
} Runtime_Exception;