#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef size_t hsize_t;

typedef struct htbl
{
	hsize_t size;
	struct hashnode_t** nodes;
} HTABLE;

struct hashnode_t
{
	char* key;
	void* data;
	struct hashnode_t* next;
};

extern HTABLE* new_htbl(hsize_t size);
extern void free_htbl(HTABLE* tbl);
extern int htbl_put(HTABLE* tbl, char* key, void* data);
extern int htbl_del(HTABLE* tbl, char* key);
extern void* htbl_get(HTABLE* tbl, char* key);
extern int htbl_rsz(HTABLE* tbl, hsize_t size);

#endif
