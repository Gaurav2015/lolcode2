#include "parser.h"

expr* new_dexpr(double d)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		return memerr();
	}
	e->d = d;
	return e;
}

expr* new_lexpr(long l)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		return memerr();
	}
	e->l = l;
	return e;
}

expr* new_sexpr(char* s)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		return memerr();
	}
	e->s = s;
	return e;
}

expr* new_bexpr(bool b)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
		return memerr();
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
