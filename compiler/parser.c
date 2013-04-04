expr* new_nexpr(double* d)
{
	expr* e = malloc(sizeof(expr));
	if (!e) {
		free(e);
	}
	e->d = d;
	return e;
}