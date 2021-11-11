#pragma once
#include "Basics.h"


typedef struct {
	int seed;
} Captures;

typedef struct {
	Captures* captures;
	int numberOfParameters;
} CallContext;

typedef struct {
	Captures* captures;
	Object p1;
	int returnValue;
} RandomNext1CallContext;

typedef struct {
	Captures* captures;
	int returnValue;
} RandomNext0CallContext;



typedef int (*stdFunction)(Exception **exceptionResult, CallContext *randomContext);

typedef struct
{
	stdFunction Next1;
	stdFunction Next0;
} Random;