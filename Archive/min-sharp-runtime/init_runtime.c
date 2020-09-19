#include "pch.h"
#include "InternalRuntime.h"
#include "TypeInternals.h"
#include <stdlib.h>
#include <malloc.h>

min_sharp_object* runtime_exception;

void init_runtime()
{
	runtime_exception = malloc(sizeof(min_sharp_object));
	if (NULL == runtime_exception)
	{

	}
}