/*
	Main part of the program; contains int main.
	Copyright 2013 Arun Dilipan
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return 
*/

#include "lexer.h"

HTABLE* locals;
HTABLE* funcs;

#define READ_ONLY "r"

char** lnames;
unsigned int nlnames; 

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

void strerr()
{
	puts("Error with string.");
	exit(EXIT_FAILURE);
}

char* concat(char* dest, char* src)
{
	char* result = malloc(strlen(dest) + strlen(src) + 1);
	snprintf(result, strlen(dest) + strlen(src) + 1, "%s%s", dest, src);
	return result;
}

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		puts("Not enough arguments.");
		exit(EXIT_SUCCESS);
	} else {
		nlnames = 0;
		char* filename = argv[1];
		src = fopen(filename, READ_ONLY);

		lexitem* l = next_item(filename);
		puts(l->image);
	}
	return 0;
}
