/*
 * Paladin.
 * Copyright (C) 2014 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "hashmap.h"

/*
 * It makes hashmap.
 */
Hashmap *
new_hashmap(void)
{
	int index;
	Hashmap *self = (Hashmap *)malloc(sizeof(Hashmap));

	if (self == NULL) 
	{
		fprintf(stderr,"low memory.\n");
	}
	else 
	{
		for (index = 0; index < HASHSIZE; index++)
		{
			self->hashtable[index] = NULL;
		}
		self->do_hash = (void *)&do_hash;
		self->put = (void *)&put;
	}
	return self;
}

/*
 * It's release memory using by hastable.
 */
void 
free_hashmap(Hashmap *a_hashmap)
{
    int index;
    Variables *node, *root;
	
    for (index = 0; index < HASHSIZE; index++)
	{
		node = a_hashmap->hashtable[index];
        while (node != NULL)
		{
            root = node->next;
            free(node);
            node = root;
		}
		root = NULL;
	}
	free(a_hashmap);
	a_hashmap = NULL;

	return;
}

/*
 * It convets character string to hash code by hash function.
 * I use macports opensource as reference.
 */
int 
do_hash(char *key_string)
{
	int hash_number = 0;
	
	while (*key_string != '\0')
	{
        hash_number += *key_string++;
	}
	
	return (hash_number % HASHSIZE);
}

/*
 * It shows values in all hashtable.
 */
void 
show_hashtable(Hashmap *a_hashmap)
{
    int index;
    Variables *node;
	
    for (index = 0; index < HASHSIZE; index++)
	{
		node = a_hashmap->hashtable[index];
        while (node != NULL)
		{
			printf("予約語:%s ハッシュ値:%d:\n", node->variable_name, do_hash(node->variable_name));
			node = node->next;
		}
	}
}

/*
 * It registers variable name and integer to hashtable.
 */
void 
put(Hashmap *self, char *variable_name, Variable *a_variable)
{
	int hash_number;
	Variables *root, *node;
	
	node = (Variables *)malloc(sizeof(Variables));
	if (node == NULL)
	{
		fprintf(stderr, "low memory\n");
		exit(EXIT_FAILURE);
	}
	hash_number = self->do_hash(variable_name);
	node->variable_name = (char *)strdup(variable_name);
	node->variable = a_variable;
	node->next = NULL;
	
	if (self->hashtable[hash_number] == NULL)
	{
		self->hashtable[hash_number] = node;
	}
	else
	{
		root = self->hashtable[hash_number];
		while (root != NULL) 
		{
			if (strcmp(root->variable_name, variable_name) == 0) 
			{
				return;
			}
			root = root->next;
		}
		root = node;
		node->next = NULL;
	}
	
	return;
}

/*
 * Example program of hashmap.
 * I'm sorry. This main function is dirty and crazy.
 * "scanf" is not nice.
 */
/*
int 
main(void)
{
	int integer;
	char a_line[256];
	Hashmap *a_hashmap = new_hashmap();

	while(1)
	{
		printf(">> ");
		scanf("%s %d", a_line, &integer);
		if (strncmp(a_line, "quit", 4) == 0)
		{
			break;
		}
		Variable *a_variable = (Variable *)malloc(sizeof(Variable));
		a_variable->integer = integer;
		a_hashmap->put(a_hashmap, a_line, a_variable);
	}
	show_hashtable(a_hashmap);
	free_hashmap(a_hashmap);

	return 0;
}
*/


