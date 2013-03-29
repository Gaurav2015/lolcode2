#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE* src;

extern void memerr();
extern void segerr();
extern char* concat(char* dest, char* src);

#endif
