#include "tokenizer.h"
#include <string.h>

#define IS_KEY(x) is_keyword((x), 0, nkwds)

// Implements a binary search algorithm for
// searching all the keywords.
int is_keyword(char* key, int min, int max)
{
	if (max < min)
		return -1;
	else {
		int mid = (max + min) / 2;

		if (strcmp(keywords[mid], key) > 0)
			return is_keyword(key, min, mid - 1);
		else if (strcmp(keywords[mid], key) < 0)
			return is_keyword(key, mid + 1, max);
		else
			return mid;
	}
}

token_t* new_numbar_token(double num)
{
	token_t* token = NEW(token_t);
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
	token_t* token = NEW(token_t);
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
	token_t* token = NEW(token_t);
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
	token_t* token = NEW(token_t);
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
	token_t* token = NEW(token);
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
	tokenlist_t* tokenlist = NEW(tokenlist_t);
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
	
	list->tokens = realloc(list->tokens, sizeof(token_t) * ++tokens->ntokens)
	if (!list->tokens[list->ntokens - 1]) {
		free(list->tokens);
		free(list);
		return;
	}
	
	list->tokens[list->ntokens - 1] = token;
}

tokenlist_t* tokenize_lexitems(lexitemlist_t* lilist)
{
	tokenlist_t* tlist = new_tokenlist();

	for (int i = 0; i < lilist->nlexitems; i++)
	{
		//Check to see if this is a keyword.
		int keyword = IS_KEY(lilist->lexitems[i]->str);

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
				memerror();
		}

		//If this is a boolean true, then handle it.
		if (strcmp(lilist->lexitems[i]->str, "WIN") == 0)
		{
			if (token = new_bool_token(true))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerror();
		}

		//If this is a boolan false, then handle it.
		if (strcmp(lilist->lexitems[i]->str, "FAIL") == 0)
		{
			if (token = new_bool_token(false))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerror();
		}

		char* endptr = "";
		double dval = strtod(lilist->lexitems[i]->str, &endptr);
		if (*endptr == '\0')
		{
			token_t* token;
			if (token = new_numbar_token(dval))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerror();
		}


		long lval = strtol(lilist->lexitems[i]->str, &endptr, 0);
		if (*endptr == '\0')
		{
			token_t* token;
			if (token = new_numbar_token(lval))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerror();
		}

		//if this is a string, then handle it.
		if (lilist->lexitems[i]->str[0] == '\"')
		{
			token_t* token;
			if (token = new_yarn_token(lilist->lexitems[i]->str))
			{
				add_token(tlist, token);
				continue;
			}
			else
				memerror();
		}

		if (token = new_ident_token(lilist->lexitems[i]->str))
		{
			add_token(tlist, token);
		}
		else
			memerror();
	}
}