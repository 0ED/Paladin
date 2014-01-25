/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
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

/* if hash number is equal, this List connect next */
typedef struct list {
	char *variable_name;
	Variable *variable;
	struct list *next;
} List;

List *hashtable[HASHSIZE];

int do_hash(char *);
void put_integer(char *, Variable *);
void free_variables(void);
//int main(void);

#endif /* !__INCLUDE_HASHMAP_H__*/

