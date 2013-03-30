#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE* src;

extern char** lnames;
extern unsigned int nlnames; 

extern void memerr();
extern void segerr();
extern void strerr();
extern char* concat(char* dest, char* src);

#endif
