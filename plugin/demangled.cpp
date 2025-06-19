#include <stdio.h>
#include "libmacros.h"

DEMANGLE const char* name()
{
	return "demangled";
}

DEMANGLE void action(void)
{
	printf("Demangling in action.\n");
}
