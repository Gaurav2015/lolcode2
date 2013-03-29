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

lexitemlist* scanbuffer(char* filename)
{
	unsigned int line = 1;
	lexitemlist* list = new_lexitemlist();
	char* image = "";

	while ((nchar[0] = fgetc(src)) != EOF) {
		while (isspace(nchar[0]) && nchar[0] != EOF) {
			if (nchar[0] == '\n' || (nchar[0] == '\r' && (nchar[0] = fgetc(src)) == '\n'))
				line++;
			nchar[0] = fgetc(src);
		}

		if (nchar[0] == EOF)
			return list;
		
		//TODO fix this if statement right here. This if statement is going bad.
		if (nchar[0] == '\"') {
			image = concat(image, nchar);
			while (nchar[0] != '\"' && nchar[0] != EOF) {
				if (nchar[0] == ':') {
					nchar[0] = fgetc(src);
					switch (nchar[0]) {
						case ':':
							image = concat(image, ":");
							break;
						case ')':
							image = concat(image, "\n");
							break;
						case '>':
							image = concat(image, "\t");
							break;
						case '\"':
							image = concat(image, "\"");
							break;
						default:
							printf("Unrecognized escape @ line %d in file %s: \":%c\"", line, filename, (char)nchar[0]);
							exit(EXIT_FAILURE);
					}
				}
				nchar[0] = fgetc(src);
			}
		} else {
			while (!isspace(nchar[0]) && nchar[0] != EOF) {
				image = concat(image, nchar);
				nchar[0] = fgetc(src);
			}
		}

		add_item(list, new_lexitem(image, filename, line));
		image = "";
	}

	return list;
}
