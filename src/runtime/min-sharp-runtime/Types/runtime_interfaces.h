#pragma once

#include "../min-sharp-runtime.h"
#include "../min-sharp-runtime-function-prototypes.h"

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	min_sharp_function_2_arguments_type Add;
} Runtime_AdditionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Substract;
} Runtime_SubstractionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Multiply;
} Runtime_MultiplicationOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Divide;
} Runtime_DivisionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type Remainder;
} Runtime_RemainderOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type IsEquals;
} Runtime_EqualityOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_function_2_arguments_type IsGreaterThan;
	min_sharp_function_2_arguments_type IsLowerThan;
} Runtime_RelationalOperator;


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

