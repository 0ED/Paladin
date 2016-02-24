/*
 * Paladin.
 * Copyright (C) 2013-2014 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_HASHMAP_H__
#define __INCLUDE_HASHMAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.h"

#define HASHSIZE 52

/* 
 * if hash number is equal, this Variables connect to next
 */
typedef struct variables
{
	char			*variable_name;
	Variable		*variable;
	struct variables *next;
} Variables;

typedef struct hashmap
{
	Variables		*hashtable[HASHSIZE];
	int 			 (*do_hash)();
	void			 (*put)(); 
	Variable		*(*get)(); 
} Hashmap;

int do_hash(char *);
void put(Hashmap *, char *, Variable *);
Variable *get(Hashmap *,char *);

Hashmap *new_hashmap(void);
void free_hashmap(Hashmap *);
void show_hashtable(Hashmap *);
//int main(void);

#endif /* !__INCLUDE_HASHMAP_H__ */

