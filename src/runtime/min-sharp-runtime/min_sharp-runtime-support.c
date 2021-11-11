#include "min_sharp-runtime-support.h"
#include <stdlib.h>
#include <stdio.h>
#include <min-sharp-runtime.h>

void abort_with_message(char* message)
{
	puts(message);
	abort();
}