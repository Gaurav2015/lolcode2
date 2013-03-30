/*
	Creates lex items that are passed to the tokenizer.
	Copyright 2013 Arun Dilipan
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return. 
*/

#ifndef _LEXER_H_
#define _LEXER_H_

#define str(X)	_Generic((X), long: lstr, \
							  double: dstr, \
							  bool: bstr)(X)

#include "main.h"

typedef struct lexitem_t lexitem;
typedef struct lexitemlist_t lexitemlist;

struct lexitem_t {
	char* image;
	char* fname;
	unsigned int line;
};

struct lexitemlist_t {
	lexitem** items;
	unsigned int nitems;
};

extern lexitemlist* scanbuffer(char*);

#endif
