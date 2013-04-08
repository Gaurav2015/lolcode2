/*
   The parser section of the compiler.
   Copyright 2013 Arun Dilipan

   Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
   Arun Dilipan wrote this file. As long as you retain this notice you
   can do whatever you want with this stuff. If we meet some day, and you think
   this stuff is worth it, you can buy me a beer or coffee in return. 
 */

#include "parser.h"

expr* new_dexpr(double d)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->d = d;
	return e;
}

expr* new_lexpr(long l)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->l = l;
	return e;
}

expr* new_sexpr(char* s)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->s = s;
	return e;
}

expr* new_bexpr(bool b)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->b = b;
	return e;
}

expr* new_biexpr(int op, expr* left, expr* right)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}

	binop_expr* binop = malloc(sizeof(binop_expr));
	if (!binop) {
		free(binop);
		free(e);
		memerr();
	}

	binop->lhs = left;
	binop->rhs = right;
	binop->op = op;
	e->binop = binop;
	return e;
}
