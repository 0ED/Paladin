/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_DYNAMIC_VARIABLE_HASHMAP_H__
#define __INCLUDE_DYNAMIC_VARIABLE_HASHMAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASHSIZE 52
#define READLINE_SIZE 512

enum { INTEGER, REAL, STRING };

typedef struct variable {
    char *name;
	int type;
	int integer;
	float real;
	char* string;
} Variable;

/* if hash number is equal, this List connect next */
typedef struct list {
	char *variable_name;
	struct list *next;
} List;

List *hashtable[HASHSIZE];

int do_hash(char *);
void put_integer(char *, int);
void free_variables(void);
int main(void);

#endif /* !__INCLUDE_DYNAMIC_VARIABLE_HASHMAP_H__*/

