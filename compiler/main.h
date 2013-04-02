#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "parser.h"

FILE* src;

extern HTABLE* locals;
extern HTABLE* funcs;

extern void memerr();
extern void segerr();
extern void strerr();
extern char* concat(char* dest, char* src);

#endif
