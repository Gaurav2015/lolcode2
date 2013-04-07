/*
	The hashtable used as the locals lookup table
	Copyright 2013 Arun Dilipan.
	
	Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
	Arun Dilipan wrote this file. As long as you retain this notice you
	can do whatever you want with this stuff. If we meet some day, and you think
	this stuff is worth it, you can buy me a beer or coffee in return 
*/

#include "hashtable.h"

const size_t FNV_OFFSET = 14695981039346656037U;
const size_t FNV_PRIME = 1099511628211U;

hsize_t fnvhash(char* s)
{
	hsize_t hash = FNV_OFFSET;
	size_t i;
	for (i = 0; i < strlen(s); ++i) {
		hash ^= s[i];
		hash *= FNV_PRIME;
	}
	return hash;
}

HTABLE* new_htbl(hsize_t size)
{
	HTABLE* tbl;

	if (!(tbl = malloc(sizeof(HTABLE))))
		return NULL;

	if (!(tbl->nodes = calloc(size, sizeof(struct hashnode_t*)))) {
		free(tbl);
		return NULL;
	}

	tbl->size = size;

	return tbl;
}

void free_htbl(HTABLE* tbl)
{
	hsize_t n;
	struct hashnode_t *node, *onode;

	for (n = 0; n < tbl->size; ++n) {
		node = tbl->nodes[n];
		while (node) {
			free(node->key);
			onode = node;
			node = node->next;
			free(onode);
		}
	}

	free(tbl->nodes);
	free(tbl);
}

char* mystrdup(char* s)
{
	if (s == NULL) return NULL;
	char* d = malloc(strlen(s) + 1);
	if (d == NULL) return NULL;
	strcpy(d, s);
	return d;
}

int htbl_put(HTABLE* tbl, char* key, void* data)
{
	struct hashnode_t* node;
	hsize_t hash = fnvhash(key) % tbl->size;
	node = tbl->nodes[hash];
	while(node) {
		if(!strcmp(node->key, key)) {
			node->data = data;
			return 0;
		}
		node = node->next;
	}
	
	if (!(node = malloc(sizeof(struct hashnode_t))))
		return -1;

	if (!(node->key = mystrdup(key))) {
		free(node);
		return -1;
	}

	node->data = data;
	node->next = tbl->nodes[hash];
	tbl->nodes[hash] = node;

	return 0;
}

int htbl_del(HTABLE* tbl, char* key)
{
	struct hashnode_t* node, *pnode = NULL;
	hsize_t hash = fnvhash(key) % tbl->size;

	node = tbl->nodes[hash];
	while(node) {
		if(!strcmp(node->key, key)) {
			free(node->key);
			if(pnode) pnode->next = node->next;
			else tbl->nodes[hash] = node->next;
			free(node);
			return 0;
		}
		pnode = node;
		node = node->next;
	}

	return -1;
}

void* htbl_get(HTABLE* tbl, char* key)
{
	struct hashnode_t *node;
	hsize_t hash = fnvhash(key) % tbl->size;

	node = tbl->nodes[hash];
	while (node) {
		if (!strcmp(node->key, key)) return node->data;
		node = node->next;
	}

	return NULL;
}

int htbl_rsz(HTABLE* tbl, hsize_t size)
{
	HTABLE newtbl;
	hsize_t n;
	struct hashnode_t* node, *next;

	newtbl.size = size;

	if (!(newtbl.nodes = calloc(size, sizeof(struct hashnode_t*))))
		return -1;

	for (n = 0; n < tbl->size; ++n) {
		for (node = tbl->nodes[n]; node; node = next) {
			next = node->next;
			htbl_put(&newtbl, node->key, node->data);
			htbl_del(tbl, node->key);
		}
	}

	free(tbl->nodes);
	tbl->size = newtbl.size;
	tbl->nodes = newtbl.nodes;

	return 0;
}
