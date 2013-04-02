/*
	The tokenizer portion of the compiler.
	Copyright 2013 Arun Dilipan 
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return 
*/

#include "tokenizer.h"
#include <string.h>
#define IS_KEY(x) is_keyword((x), 0, nkwds)

// Implements a binary search algorithm for
// searching all the keywords.
int is_keyword(char* key, int min, int max)
{
	while (max >= min) {
		int mid = (min + max) / 2;

		if (strcmp(key, keywords[mid]) < 0)
			max = mid - 1;
		else if (strcmp(key, keywords[mid]) > 0)
			min = mid + 1;
		else
			return mid;
	}

	return -1;
}

token_t* new_numbar_token(double num)
{
	token_t* token = malloc(sizeof(token_t));
	if (!token) {
		free(token);
		return NULL;
	}
	token->type = T_NUMBAR;
	token->d = num;
	return token;
}

token_t* new_yarn_token(char* s)
{
	token_t* token = malloc(sizeof(token_t));
	if (!token) {
		free(token);
		return NULL;
	}
	token->type = T_YARN;
	token->s = s;
	return token;
}

token_t* new_bool_token(bool b)
{
	token_t* token = malloc(sizeof(token_t));
	if(!token) {
		free(token);
		return NULL;
	}
	token->type = T_BOOL;
	token->b = b;
	return token;
}

token_t* new_ident_token(char* ident)
{
	token_t* token = malloc(sizeof(token_t));
	if (!token)
	{
		free(token);
		return NULL;
	}
	token->type = T_IDENT;
	token->ident = ident;
	return token;
}

token_t* new_keyword_token(int key)
{
	token_t* token = malloc(sizeof(token));
	if (!token) {
		free(token);
		return NULL;
	}
	token->type = T_KEYWORD;
	token->keyword = key;
	return token;
}

tokenlist_t* new_tokenlist()
{
	tokenlist_t* tokenlist = malloc(sizeof(tokenlist_t));
	if (!tokenlist) {
		free(tokenlist);
		return NULL;
	}
	tokenlist->tokens = NULL;
	tokenlist->ntokens = 0;
	return tokenlist;
}

//Adds a new token to the token list.
void add_token(tokenlist_t* list, token_t* token)
{
	if (list->ntokens == 0) {
		list->ntokens++;
		list->tokens = malloc(sizeof(token_t*));
		list->tokens[0] = token;
		return;
	}
	
	list->tokens = realloc(list->tokens, sizeof(token_t) * ++list->ntokens);
	if (!list->tokens[list->ntokens - 1]) {
		free(list->tokens);
		free(list);
		return;
	}
	
	list->tokens[list->ntokens - 1] = token;
}

tokenlist_t* tokenize_items(lexitemlist* lilist)
{
	tokenlist_t* tlist = new_tokenlist();

	for (int i = 0; i < lilist->nitems; i++)
	{
		//Check to see if this is a keyword.
		int keyword = IS_KEY(lilist->items[i]->image);

		//If this is a keyword, make a new token.
		if (keyword != -1)
		{
			token_t* token;
			if (token = new_keyword_token(keyword))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr;
		}

		//If this is a boolean true, then handle it.
		if (strcmp(lilist->items[i]->image, "WIN") == 0)
		{
			token_t* token;
			if (token = new_bool_token(true))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr();
		}

		//If this is a boolan false, then handle it.
		if (strcmp(lilist->items[i]->image, "FAIL") == 0)
		{
			token_t* token;
			if (token = new_bool_token(false))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr();
		}

		char* endptr = "";
		double dval = strtod(lilist->items[i]->image, &endptr);
		if (*endptr == '\0')
		{
			token_t* token;
			if (token = new_numbar_token(dval))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr();
		}


		long lval = strtol(lilist->items[i]->image, &endptr, 0);
		if (*endptr == '\0')
		{
			token_t* token;
			if (token = new_numbar_token(lval))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr();
		}

		//if this is a imageing, then handle it.
		if (lilist->items[i]->image[0] == '\"')
		{
			token_t* token;
			if (token = new_yarn_token(lilist->items[i]->image))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerr();
		}

		token_t* token;
		if (token = new_ident_token(lilist->items[i]->image))
		{
			add_token(tlist, token);
		}
		else
			memerr();
	}
}
