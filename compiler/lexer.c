/**
 * @file lexer.c
 * @brief contains lexical analyzing functions used in compiler
 *
 * @author Arun Dilipan
 */

#include "lexer.h"
#include <string.h>
#include <stdio.h>

int nchar[1];

lexitem_t* new_lexitem(char* image, unsigned int line)
{
	lexitem_t* item = malloc(sizeof(lexitem_t));
	if(item == NULL) {
		free(item);
		return NULL;
	}
	item->image = malloc(strlen(image) * sizeof(char));
	if(!(item->image)) {
		free(item->image);
		free(item);
		return NULL;
	}
	strcpy(item->image, image);
	item->line = line;
	return item;
}

void free_lexitem(lexitem_t* item)
{
	free(item->image);
	free(item);
}

lexitemlist_t* new_lexitemlist(void)
{
	lexitemlist_t* list = malloc(sizeof(lexitemlist_t));
	if (list == NULL) {
		free(list);
		return NULL;
	}
	list->nlexitems = 0;
	list->lexitems = NULL;
	return list;
}

void add_lexitem(lexitemlist_t* list, lexitem_t* item)
{
	list->lexitems = realloc(list->lexitems, sizeof(lexitem_t) * (list->nlexitems + 1));
    if (!list->lexitems)
	{
		 free(list->lexitems);
		 free(list);
		 return;
	}
	list->nlexitems++;
	list->lexitems[list->nlexitems] = item;
}

lexitemlist_t* scanbuffer()
{
	int line = 1;
	lexitemlist_t* list = new_lexitemlist();
	if (!list)
	{
		free(list->lexitems);
		free(list);
		return NULL;
	}

	char* image = "";
	
	while ((nchar[0] = fgetc(src)) != EOF)
	{
	    while (isspace(nchar[0]))
		{
			if (nchar[0] == '\n')
				line++;
			nchar[0] = fgetc(src);
		}

		nchar[0] = fgetc(src);
		image = strcat(image, nchar[0]);

		if (nchar[0] == '\"')
		{
			while ((nchar[0] == fgetc(src)) != '\"')
			{
				if (nchar[0] == ':')
				{
					int nextChar = fgetc(src);
					switch (nextChar)
					{
						case ')':
							nchar[0] = '\n';
							image = strcat(image, (const char*)nchar);
							break;
						case '>':
							nchar[0] = '\t';
							image = strcat(image, (const char*)nchar);
							break;
						case '{':
							//Add string interpolation.
							break;
						case '\"':
							nchar[0] = '\"';
							image = strcat(image, (const char*)nchar);
							break;
					}
				}

				image = strcat(image, (const char*)nchar);
			}
		} else
			while (!isspace(nchar[0]))
				image = strcat(image, (const char*)nchar);
			
		lexitem_t* item = new_lexitem(image, line);
		add_lexitem(list, item);
	}

	fclose(src);
	return list;
}

