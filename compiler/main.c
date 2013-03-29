#include "lexer.h"

#define READ_ONLY "r"

void memerr()
{
	puts("Ran out of memory.");
	exit(EXIT_FAILURE);
}

void segerr()
{
	puts("Trying to dereference null pointer.");
	exit(EXIT_FAILURE);
}

char* concat(char* dest, char* src)
{
	char* result = malloc(strlen(dest) + strlen(src) + 1);
	snprintf(result, strlen(dest) + strlen(src) + 1, "%s%s", dest, src);
	return result;
}

int main(int argc, const char *argv[])
{
	if (argc <= 1) {
		puts("Not enough arguments.");
		exit(EXIT_SUCCESS);
	} else {
		char* filename = argv[1];
		src = fopen(filename, READ_ONLY);

		lexitemlist* l = scanbuffer(filename);
		for (int i = 0; i < l->nitems; ++i)
		{
			puts(l->items[i]->image);
		}
	}
	return 0;
}
