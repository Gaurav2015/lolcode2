/*
   Creates lex items that are passed to the tokenizer.
   Copyright 2013 Arun Dilipan

   Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
   Arun Dilipan wrote this file. As long as you retain this notice you
   can do whatever you want with this stuff. If we meet some day, and you think
   this stuff is worth it, you can buy me a beer or coffee in return. 
 */

#include "lexer.h"

char nchar[1];
unsigned int line = 1;

char* lstr(long l)
{
	const size_t n = snprintf(NULL, 0, "%ld", l);
	char* buf = malloc(n+1);
	snprintf(buf, n+1, "%ld", l);
	return buf;
}

char* dstr(double d)
{
	const size_t n = snprintf(NULL, 0, "%lf", d);
	char* buf = malloc(n+1);
	snprintf(buf, n+1, "%lf", d);
	return buf;
}

char* bstr(bool b)
{
	return b ? "WIN" : "FAIL";
}

char* sstr(char* s)
{
	char* result = malloc(strlen(s) - 1);
	int i;
	for (i = 1; i < strlen(s) - 1; i++)
		result[i-1] = s[i];
	return result;
}

lexitem* new_lexitem(char* image, char* fname, unsigned int line)
{
	lexitem* item = malloc(sizeof(lexitem));
	if (item == NULL) 
		memerr();
	item->image = image;
	item->fname = fname;
	item->line = line;
	return item;
}

lexitemlist* new_lexitemlist()
{
	lexitemlist* list = malloc(sizeof(lexitemlist));
	if (list == NULL)
		memerr();
	list->items = NULL;
	list->nitems = 0;
	return list;
}

void add_item(lexitemlist* list, lexitem* item)
{
	if (!list->nitems)
		list->items = malloc(++list->nitems * sizeof(lexitem*));
	else
		list->items = realloc(list->items, ++list->nitems * sizeof(lexitem*));

	list->items[list->nitems - 1] = item;
}

char* get_exprkey(expr* e)
{
	switch (e->type) {
		case T_NUMBR:
			return lstr(e->l);
		case T_NUMBAR:
			return dstr(e->d);
		case T_YARN:
			return sstr(e->s);
		case T_TROOF:
			return bstr(e->b);
		default:
			strerr();
			return NULL;
	}
}

char* interpolate()
{
	char* result = "";

	while ((nchar[0] = fgetc(src)) != '}') {
		if (nchar[0] == '\"' || nchar[0] == EOF)
			strerr();

		result = concat(result, nchar);
	}

	expr* e;
	if ((e = htbl_get(locals, result)) != NULL)
		return get_exprkey(e);
	else {
		printf("variable %s doesn\'t exist.\n", result);
		exit(1);
		return NULL;
	}
}

lexitem* next_item(char* filename)
{
	char* image = "";

	while (isspace((nchar[0] = fgetc(src))) && nchar[0] != EOF) {
		if (nchar[0] == '\n' || (nchar[0] == '\r' && (nchar[0] = fgetc(src)) == '\n'))
			line++;
	}

	if (nchar[0] == EOF) {
		return NULL;
	}

	if (nchar[0] == '\"') {
		image = concat(image, nchar);
		nchar[0] = fgetc(src);
		while (nchar[0] != '\"' && nchar[0] != EOF) {
			if (nchar[0] == ':') {
				nchar[0] = fgetc(src);
				switch (nchar[0]) {
					case ':':
						image = concat(image, ":");
						nchar[0] = fgetc(src);
						continue;
					case ')':
						image = concat(image, "\n");
						nchar[0] = fgetc(src);							
						continue;
					case '>':
						image = concat(image, "\t");
						nchar[0] = fgetc(src);
						continue;
					case '\"':
						image = concat(image, "\"");
						nchar[0] = fgetc(src);
						continue;
					case '{':
						image = concat(image, interpolate());
						nchar[0] = fgetc(src);
						continue;
					default:
						printf("Unrecognized escape @ line %d in file %s: \":%c\"", line, filename, (char)nchar[0]);
						exit(EXIT_FAILURE);
				}
			}
			image = concat(image, nchar);
			nchar[0] = fgetc(src);
		}
		image = concat(image, nchar);
	} else {
		while (!isspace(nchar[0]) && nchar[0] != EOF) {
			image = concat(image, nchar);
			nchar[0] = fgetc(src);
		}
	}

	return new_lexitem(image, filename, line);
}

/* lexitemlist* scanbuffer(char* filename) */
/* { */
/* 	line = 1; */
/* 	lexitemlist* list = new_lexitemlist(); */
/* 	char* image = ""; */
/*  */
/* 	while ((nchar[0] = fgetc(src)) != EOF) { */
/* 		while (isspace(nchar[0]) && nchar[0] != EOF) { */
/* 			if (nchar[0] == '\n' || (nchar[0] == '\r' && (nchar[0] = fgetc(src)) == '\n')) */
/* 				line++; */
/* 			nchar[0] = fgetc(src); */
/* 		} */
/*  */
/* 		if (nchar[0] == EOF) */
/* 			return list; */
/*  */
/* 		if (nchar[0] == '\"') { */
/* 			image = concat(image, nchar); */
/* 			nchar[0] = fgetc(src); */
/* 			while (nchar[0] != '\"' && nchar[0] != EOF) { */
/* 				if (nchar[0] == ':') { */
/* 					nchar[0] = fgetc(src); */
/* 					switch (nchar[0]) { */
/* 						case ':': */
/* 							image = concat(image, ":"); */
/* 							nchar[0] = fgetc(src); */
/* 							continue; */
/* 						case ')': */
/* 							image = concat(image, "\n"); */
/* 							nchar[0] = fgetc(src);							 */
/* 							continue; */
/* 						case '>': */
/* 							image = concat(image, "\t"); */
/* 							nchar[0] = fgetc(src); */
/* 							continue; */
/* 						case '\"': */
/* 							image = concat(image, "\""); */
/* 							nchar[0] = fgetc(src); */
/* 							continue; */
/* 						case '{': */
/* 							image = concat(image, interpolate()); */
/* 							nchar[0] = fgetc(src); */
/* 							continue; */
/* 						default: */
/* 							printf("Unrecognized escape @ line %d in file %s: \":%c\"", line, filename, (char)nchar[0]); */
/* 							exit(EXIT_FAILURE); */
/* 					} */
/* 				} */
/* 				image = concat(image, nchar); */
/* 				nchar[0] = fgetc(src); */
/* 			} */
/* 			image = concat(image, nchar); */
/* 		} else { */
/* 			while (!isspace(nchar[0]) && nchar[0] != EOF) { */
/* 				image = concat(image, nchar); */
/* 				nchar[0] = fgetc(src); */
/* 			} */
/* 		} */
/*  */
/* 		add_item(list, new_lexitem(image, filename, line)); */
/* 		image = ""; */
/* 	} */
/*  */
/* 	return list; */
/* } */
