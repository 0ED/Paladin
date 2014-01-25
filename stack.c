/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "stack.h"

/*
 * It's push dynamic variable. 
 */
void push(Variable *a_variable)
{
	Stack *a_stack = (Stack *)malloc(sizeof(Stack));
    a_stack->variable = a_variable;
	a_stack->next = _dynamic_stack;
	_dynamic_stack = a_stack;
	return;
}

/*
 * It's pop dynamic variable.
 * and then free Unnecessary pointer.
 */
Variable *pop(void)
{
	Stack *a_stack = _dynamic_stack;
	Variable *a_variable = _dynamic_stack->variable;
	_dynamic_stack = _dynamic_stack->next;
	free(a_stack);
	return(a_variable);
}

/*
 * Whether the _dynamic_stack is empty.
 */
int is_empty(void)
{
	return(_dynamic_stack == NULL);
}

/* Example. 
int main(void) 
{
	Variable *in_variable = (Variable *)malloc(sizeof(Variable));
	in_variable->kind = SAMPLE_LABEL;
	in_variable->integer = 52;
	push(in_variable);
	
	Variable *out_variable = pop();
	if (out_variable->kind == SAMPLE_LABEL)
	{
		printf("%d\n", out_variable->integer);
	}
	return(EXIT_SUCCESS);
}
*/
