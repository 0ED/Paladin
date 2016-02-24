/*
 * Paladin.
 * Copyright (C) 2013-2014 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "stack.h"

/*
 * It makes stack.
 */
Stack *
new_stack() 
{
	Stack *self = (Stack *)malloc(sizeof(Stack));

	if (self == NULL) 
	{
		fprintf(stderr,"low memory.\n");
	}
	else 
	{
		self->data = (Data *)malloc(sizeof(Data)); 
		self->push = (void *)&push;
		self->pop = (void *)&pop;
		self->is_empty = (void *)&is_empty;
	}

	return self;
}

/*
 * It's free used stack.
 * but, function pointer doesn't free, because it uses to another object.
 */
void 
free_stack(Stack *a_stack) 
{
	free(a_stack->data); 
	a_stack->data = NULL;
	a_stack->push = NULL;
	a_stack->pop = NULL;
	a_stack->is_empty = NULL;
	free(a_stack); 
	a_stack = NULL;

	return;
}

/*
 * It's push dynamic variable. 
 */
void 
push(Stack *self, Variable *a_variable)
{
	Data *a_data = (Data *)malloc(sizeof(Data));
    a_data->variable = a_variable;
	a_data->next = self->data;
	self->data = a_data;
	return;
}

/*
 * It's pop dynamic variable.
 * and then free Unnecessary pointer.
 */
Variable *
pop(Stack *self) 
{
	Data *a_data = self->data;
	Variable *a_variable = self->data->variable;
	self->data = self->data->next;
	free(a_data);
	return(a_variable);
}

/*
 * Whether the data is empty.
 */
int 
is_empty(Stack *self)
{
	return(self->data == NULL);
}

/* 
 * Example.
 * This main function of example is very dirty and crazy. I'm sorry.
 */
/*
int main(void) 
{
	Variable *in_variable = (Variable *)malloc(sizeof(Variable));
	in_variable->kind = 1;
	in_variable->integer = 52;
	Variable *in_variable27 = (Variable *)malloc(sizeof(Variable));
	in_variable27->kind = 1;
	in_variable27->integer = 27;

	Stack *a_stack = new_stack();
	a_stack->push(a_stack, in_variable);
	a_stack->push(a_stack, in_variable27);

	Variable *out_variable = a_stack->pop(a_stack);
	if (out_variable->kind == 1)
	{
		printf("%d\n", out_variable->integer);
	}
	out_variable = a_stack->pop(a_stack);
	if (out_variable->kind == 1)
	{
		printf("%d\n", out_variable->integer);
	}
	free_stack(a_stack);


	Variable *in_variable2 = (Variable *)malloc(sizeof(Variable));
	in_variable2->kind = 1;
	in_variable2->integer = 128;

	Stack *a_stack2 = new_stack();
	a_stack2->push(a_stack2, in_variable2);

	Variable *out_variable2 = a_stack2->pop(a_stack2);
	if (out_variable2->kind == 1)
	{
		printf("%d\n", out_variable2->integer);
	}
	free_stack(a_stack2);

	return(EXIT_SUCCESS);
}
*/
