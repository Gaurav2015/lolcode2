/*
	Parser component of the compiler.
	Copyright 2013 Arun Dilipan
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return 
*/

#ifndef _PARSER_H_
#define _PARSER_H_

#include "main.h"

typedef struct stmt_t stmt;
typedef struct expr_t expr;
typedef struct binop_expr_t binop_expr;

typedef enum {
	T_NUMBR,
	T_NUMBAR,
	T_YARN,
	T_TROOF,
	T_IDENT,
	T_BINOP
} etype_t;

typedef enum {
	S_IF,
	S_WHILE,
	S_SWITCH,
	S_FOR,
	S_FOREACH,
} stype_t;

struct stmt_t {
	stype_t type;

	union {
		//TODO add all stmt node possible.
	};
};

struct expr_t {
	etype_t type;

	union {
		long l;
		double d;
		char* s;
		char* ident;
		bool b;
		binop_expr* binop;
	};
};

struct binop_expr_t {
	char op;
	expr* lhs;
	expr* rhs;
};

#endif
