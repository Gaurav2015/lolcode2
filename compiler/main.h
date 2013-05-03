/*
	Main part of the program; contains int main.
	Copyright 2013 Arun Dilipan
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return 
*/

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

extern HTABLE* funcs;
extern HTABLE* locals;

typedef struct lol_block_t {
	HTABLE* locals;
	lol_stmt** stmts;
} lol_block;

extern void memerr();
extern void segerr();
extern void strerr();
extern char* concat(char* dest, char* src);

#endif
