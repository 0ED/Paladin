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
 * It's push dynamic value. 
 */
void push(Value *a_value)
{
	Stack *a_stack = (Stack *)malloc(sizeof(Stack));
    a_stack->value = a_value;
	a_stack->next = _dynamic_stack;
	_dynamic_stack = a_stack;
	return;
}

/*
 * It's pop dynamic value.
 * and then free Unnecessary pointer.
 */
Value *pop(void)
{
	Stack *a_stack = _dynamic_stack;
	Value *a_value = _dynamic_stack->value;
	printf("%p\n",_dynamic_stack->next);
	_dynamic_stack = _dynamic_stack->next;
	free(a_stack);
	return(a_value);
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
	Value *inValue = (Value *)malloc(sizeof(Value)); 
	inValue->kind = SAMPLE_LABEL;
	inValue->integer = 52;
	push(inValue);
	
	Value *outValue = pop();
	if (outValue->kind == SAMPLE_LABEL) 
	{
		printf("%d\n", outValue->integer);
	}
	return(EXIT_SUCCESS);
}
*/
