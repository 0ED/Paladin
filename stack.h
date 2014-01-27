/*
 * Paladin.
 * Copyright (C) 2014 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_STACK_H__
#define __INCLUDE_STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "variable.h"

typedef struct data 
{
	Variable		*variable;
	struct data		*next;
} Data;

typedef struct stack 
{
	Data			*data;
	void 			 (*push)();
	Variable		*(*pop)(); 
	int 			 (*is_empty)();
} Stack;

Stack *new_stack();
void free_stack(Stack *);

void push(Stack *,Variable *);
Variable *pop(Stack *);
int is_empty(Stack *);

#endif /* !__INCLUDE_STACK_H__ */

