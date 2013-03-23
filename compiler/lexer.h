#pragma once
#include "main.h"
#include <ctype.h>

#define isvident(x) (isalnum(x) || x >= 0xC0) 

typedef struct lexitem lexitem_t;
typedef struct lexitemlist lexitemlist_t;

struct lexitem
{
	char* image;
	unsigned int line;
};

struct lexitemlist
{
	unsigned int nlexitems;
	lexitem_t** lexitems;
};

extern lexitem_t* new_lexitem(char*, unsigned int);
extern void free_lexitem(lexitem_t*);
extern lexitemlist_t* new_lexitemlist(void);
extern void add_lexitem(lexitemlist_t*, lexitem_t*);
extern void free_lexitemlist(lexitemlist_t*);

extern lexitemlist_t* scan_buffer(char*, unsigned int, char*);
