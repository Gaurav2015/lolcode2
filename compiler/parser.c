/*
   The parser section of the compiler.
   Copyright 2013 Arun Dilipan

   Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
   Arun Dilipan wrote this file. As long as you retain this notice you
   can do whatever you want with this stuff. If we meet some day, and you think
   this stuff is worth it, you can buy me a beer or coffee in return. 
 */

#include "parser.h"

lol_expr* new_dexpr(double d)
{
	lol_expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->d = d;
	return e;
}

lol_expr* new_lexpr(long l)
{
	lol_expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->l = l;
	return e;
}

lol_expr* new_sexpr(char* s)
{
	lol_expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->s = s;
	return e;
}

lol_expr* new_bexpr(bool b)
{
	lol_expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}
	e->b = b;
	return e;
}

lol_expr* new_biexpr(int op, lol_expr* left, lol_expr* right)
{
	lol_expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		memerr();
	}

	lol_binop_expr* binop = malloc(sizeof(lol_binop_expr));
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

lol_stmt* new_ifstmt(lol_expr* cond, lol_stmt** then, lol_expr** elsifs, lol_expr** elsifthens,
				  	 lol_stmts* elsestmts)
{
	//Finish up stuff here
}