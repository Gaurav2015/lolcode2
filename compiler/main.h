#pragma once
#include <stdio.h>
#include <llvm-c/Core.h>
#include <stdlib.h>

FILE* in;

void memerror()
{
	puts("Ran out of memory.\n");
	exit(1);
}
