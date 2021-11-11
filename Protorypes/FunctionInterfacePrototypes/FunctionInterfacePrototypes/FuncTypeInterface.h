#pragma once
#include "Basics.h"

typedef int (*Func0)(Exception** exceptionResult);
typedef int (*Func1)(Exception** exceptionResult, Object p1);
typedef int (*Func2)(Exception** exceptionResult, Object p1, Object p2);
typedef int (*Func3)(Exception** exceptionResult, Object p1, Object p2, Object p3);
typedef int (*Func4)(Exception** exceptionResult, Object p1, Object p2, Object p3, Object p4);
typedef int (*Func5)(Exception** exceptionResult, Object p1, Object p2, Object p3, Object p4, Object p5);
typedef int (*Func6)(Exception** exceptionResult, Object p1, Object p2, Object p3, Object p4, Object p5, Object p6);
typedef int (*Func7)(Exception** exceptionResult, Object p1, Object p2, Object p3, Object p4, Object p5, Object p6, Object p7);


typedef struct
{
	Func1 Next1;
	Func0 Next0;
} Random2;