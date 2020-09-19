#include "TypeInternals.h";
#include "InternalRuntime.h"

#include <malloc.h>
 
functionCallResult min_sharp__internal_builder_factory(min_sharp_object** exception, min_sharp__internal_builder** result)
{
    min_sharp__internal_builder* result;
    result = malloc(sizeof(min_sharp__internal_builder));
    if (result == NULL)
    {
        *exception = runtime_exception;
    }
 
    exception_thrown:
    return functionCallResultFail;
}