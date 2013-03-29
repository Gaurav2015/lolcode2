#include "test.h"

int main(int argc, const char *argv[])
{
	if (argc <= 1) {
		printf("Error, no arguments.");
	} else {
		src = fopen(argv[1], "r");
		lexitemlist_t* list = scanbuffer();

		unsigned int i;
		for (i = 0; i < list->nlexitems; i++) {
			puts(list->lexitems[i]->image);		
		}
	}
	return 0;
}
