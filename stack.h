/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_STACK__H__
#define __INCLUDE_STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define SAMPLE_LABEL 1

typedef struct value { 
	int          kind;
	int			 integer;
	double		 real;
	char		*string;
} Value;
typedef struct stack {
	Value			*value;
	struct stack	*next;
} Stack;

Stack *_dynamic_stack;

void push(Value *a_value);
Value *pop(void);
int is_empty(void);
// int main(void);

#endif /* !__INCLUDE_STACK_H__*/

