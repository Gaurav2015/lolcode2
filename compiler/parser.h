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

typedef struct stmt_t lol_stmt;
typedef struct if_stmt lol_if_stmt;
typedef struct expr_t lol_expr;
typedef struct binop_expr_t lol_binop_expr;

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
		lol_if_stmt* istmt;
		lol_while_stmt* wstmt;
		lol_for_stmt* fstmt;
		lol_switch_stmt* sstmt;
		lol_foreach_stmt* festmt;
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
		lol_binop_expr* binop;
	};
};

struct binop_expr_t {
	char op;
	lol_expr* lhs;
	lol_expr* rhs;
};

struct if_stmt {
	lol_expr* cond;
	lol_block* t_block;
	lol_expr** elsifs;
	lol_block** ei_block;
	lol_block* e_block;
};

struct while_stmt {
	lol_expr* cond;
	lol_block* stmts;
};

struct for_stmt {
	lol_expr* start;
	lol_expr* end;
	lol_expr* step;

	lol_block* stmts;
};

struct switch_stmt {
	lol_expr* val;

	HTABLE* switchtable;	
};
#endif
