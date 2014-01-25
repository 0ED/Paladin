/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "hashmap.h"

/*
 * It convets character string to hash code by hash function.
 * I use macports opensource as reference.
 */
int do_hash(char *key_string)
{
	int hash_number = 0;
	
	while (*key_string != '\0')
	{
        hash_number += *key_string++;
	}
	
	return (hash_number % HASHSIZE);
}

/*
 * It's release memory using by hastable.
 */
void free_variables(void)
{
    int index;
    List *node, *root;
	
    for (index = 0; index < HASHSIZE; index++)
	{
		node = hashtable[index];
        while (node != NULL)
		{
            root = node->next;
            free(node);
            node = root;
		}
	}
}

/*
 *
 */
void values(void)
{
    int index;
    List *node;
	
    for (index = 0; index < HASHSIZE; index++)
	{
		node = hashtable[index];
        while (node != NULL)
		{
			printf("予約語:%s ハッシュ値:%d:\n", node->variable_name, do_hash(node->variable_name));
			node = node->next;
		}
	}
}

/*
 * It's register variable name and integer to hashtable.
 */
void put_integer(char *variable_name, Variable *a_variable)
{
	int hash_number;
	List *root, *node;
	
	node = (List *)malloc(sizeof(List));
	if (node == NULL)
	{
		fprintf(stderr, "low memory\n");
		exit(EXIT_FAILURE);
	}
	hash_number = do_hash(variable_name);
	node->variable_name = (char *)strdup(variable_name);
	node->variable = a_variable;
	node->next = NULL;
	
	if (hashtable[hash_number] == NULL)
	{
		hashtable[hash_number] = node;
	}
	else
	{
		root = hashtable[hash_number];
		while (root->next != NULL) {
			if (strcmp(root->variable_name,variable_name) == 0) {
				return;
			}
			root = root->next;
		}
		root->next = node;
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
int main(void)
{
	int integer;
	char a_line[256];
	while(true)
	{
		printf(">> ");
		scanf("%s %d", a_line, &integer);
		if (strncmp(a_line, "quit", 4) == 0)
		{
			break;
		}
		printf("%s\n",a_line);
		put_integer(a_line, integer);
	}
	values();
	return 0;
}
*/
