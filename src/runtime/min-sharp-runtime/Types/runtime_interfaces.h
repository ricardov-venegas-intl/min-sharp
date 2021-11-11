#pragma once

#include "../min-sharp-runtime.h"
#include "../min-sharp-runtime-function-prototypes.h"

typedef struct
{
	min_sharp_function_1_arguments_type *Add;
} Runtime_AdditionOperator;
#define RUNTIME_ADDITION_OPERATOR_INTERFACE_NAME "Runtime.AdditionOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *Substract;
} Runtime_SubstractionOperator;

#define RUNTIME_SUBSTRACTION_OPERATOR_INTERFACE_NAME "Runtime.SubstractionOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *Multiply;
} Runtime_MultiplicationOperator;

#define RUNTIME_MULTIPLICATION_OPERATOR_INTERFACE_NAME "Runtime.MultiplicationOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *Divide;
} Runtime_DivisionOperator;

#define RUNTIME_DIVISION_OPERATOR_INTERFACE_NAME "Runtime.DivisionOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *Remainder;
} Runtime_RemainderOperator;

#define RUNTIME_REMAINDER_OPERATOR_INTERFACE_NAME "Runtime.RemainderOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *IsEquals;
} Runtime_EqualityOperator;

#define RUNTIME_EQUALITY_OPERATOR_INTERFACE_NAME "Runtime.EqualityOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *IsGreaterThan;
	min_sharp_function_1_arguments_type *IsLowerThan;
} Runtime_RelationalOperator;

#define RUNTIME_RELATIONAL_OPERATOR_INTERFACE_NAME  "Runtime.RelationalOperator"

typedef struct
{
	min_sharp_function_1_arguments_type *Or;
	min_sharp_function_1_arguments_type *And;
	min_sharp_function_0_arguments_type *Not;
} Runtime_BooleanOperator;

#define RUNTIME_BOOLEAN_OPERATOR_INTERFACE_NAME  "Runtime.BooleanOperator"

typedef struct
{
	min_sharp_function_0_arguments_type *GetValue;
} Runtime_ReadOnlyProperty;


typedef struct
{
	min_sharp_function_1_arguments_type *SetValue;
} Runtime_Property;

typedef struct
{
	Runtime_ReadOnlyProperty *Code;
	Runtime_ReadOnlyProperty *Message;
} Runtime_Exception;