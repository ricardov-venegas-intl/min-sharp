#pragma once

#include "../min-sharp-runtime.h"

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Add;
} Runtime_AdditionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Substract;
} Runtime_SubstractionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Multiply;
} Runtime_MultiplicationOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Divide;
} Runtime_DivisionOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Remainder;
} Runtime_RemainderOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object IsEquals;
} Runtime_EqualityOperator;

typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object IsGreaterThan;
	min_sharp_object IsLowerThan;
} Runtime_RelationalOperator;


typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object Or;
	min_sharp_object And;
	min_sharp_object Not;
} Runtime_BooleanOperator;


typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object GetValue;
} Runtime_ReadOnlyProperty;


typedef struct
{
	min_sharp_interface_intrinsicts* min_sharp_interface_intrinsicts;
	unsigned_int_16 number_of_members;
	min_sharp_object SetValue;
} Runtime_Property;

