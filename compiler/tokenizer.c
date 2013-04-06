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

token_t* next_token(lexitem* l)
{	
	int key = IS_KEY(l->image);

	if (key != -1)
		return new_keyword_token(key);
	
	if (!strcmp(l->image, "WIN"))
		return new_bool_token(1);
		
	if (!strcmp(l->image, "FAIL"))
		return new_bool_token(0);
	
	char* endptr = "";
	double dval = strtod(l->image, &endptr);
	if (*endptr == '\0')
		return new_numbar_token(dval);
		
	long lval = strtol(l->image, &endptr, 0);
	if (*endptr == '\0')
		return new_numbar_token(lval);
		
	if (l->image[0] == '\"')
		return new_yarn_token(l->image);
	
	return new_ident_token(l->image);
}