/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "defs.h"
#include "y.tab.h"

#define TYPE(operator,result,left,right) \
	if ((operator) == (ADD)) { \
		result = (left) + (right); \
	} \
	else if ((operator) == (SUBTRACT)) { \
		result = (left) - (right); \
	} \
	else if ((operator) == (MULTIPLY)) { \
		result = (left) * (right); \
	} \
	else if ((operator) == (DIVIDE)) { \
		result = (left) / (right); \
	}

/*
 * It start Paladin. 
 * A user can talk with Paladin, or have Paladin eat a source code by mode of Paladin.
 * if you'd like to know about it, show "README.md". Good Luck.
 */
int main(int argumentCount, char* argumentValues[]) {
	linecounter = 1;
	if (argumentCount < 2) {
		is_talk = true;
		talk();
	}
	else {
		is_talk = false;
		eat_code(argumentValues[1]);
	}
	return(EXIT_SUCCESS);
}

/*
 * A user can talk with Paladin.
 */
void talk() {
	char a_line[READLINE_SIZE];
	printf(">> ");
	while (fgets(a_line, sizeof(a_line), stdin) != NULL) {
		yy_scan_string(a_line);
		yyparse();
		printf(">> ");
	}
	return;
}

/*
 * A user can have Paladin eat a source code by mode of Paladin
 */
void eat_code(char *filename) {
	yyin = fopen(filename,"r");
	if(yyin == NULL) {
		fprintf(stderr, "Can't open a input file!\n");
		exit(EXIT_FAILURE);
	}
	yyparse();
	return;
}

/*
 * Syntactic Analysis
 */
Cell *cons(Cell *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = CONS;
	pointer->head = car;
	pointer->tail = cdr;
	return(pointer);
}

/*
 * Syntactic Analysis
 */
Cell *node(int car, Cell *cdr) {
	Cell *pointer;
	int *integer;

	pointer = (Cell *)malloc(sizeof(Cell));
	integer = (int *)malloc(sizeof(int));
	*integer = car;
	pointer->kind = NODE;
	pointer->head = (Cell *)integer;
	pointer->tail = cdr;
	return(pointer);
}

/*
 * Syntactic Analysis
 */
Cell *leaf(int car, char *cdr) {
	Cell *pointer;
	int *integer;

	pointer = (Cell *)malloc(sizeof(Cell));
	integer = (int *)malloc(sizeof(int));
	*integer = car;
	pointer->kind = LEAF;
	pointer->head = (Cell *)integer;
	pointer->tail = (Cell *)strdup(cdr);
	return(pointer);
}

/*
 * Syntactic Analysis
 */
void tree(Cell *pointer) {
	visit(pointer, 1);
}


Variable *hogehoge(int operator, Variable *left, Variable *right) {
	Variable *in_variable = (Variable *)malloc(sizeof(Variable));

	if (left->kind == INTEGER && right->kind == INTEGER) {
		in_variable->kind = INTEGER;
		TYPE(operator, in_variable->integer, left->integer,right->integer);
	}
	else if (left->kind == INTEGER  && right->kind == REAL) {
		in_variable->kind = REAL;
		TYPE(operator, in_variable->real, left->integer, right->real);
	}
	else if (left->kind == REAL && right->kind == INTEGER) {
		in_variable->kind = REAL;
		TYPE(operator, in_variable->real, left->real, right->integer);
	}
	else if (left->kind == REAL && right->kind == REAL) {
		in_variable->kind = REAL;
		TYPE(operator, in_variable->real, left->real, right->real);
	}
	return in_variable;
}


/*
 * syntactic analysis
 */
void visit(Cell *pointer, int level) {
	if (pointer->kind == CONS) {
		visit(pointer->head, level + 1);
		visit(pointer->tail, level + 1);
	}
	else if (pointer->kind == NODE) {
		visit(pointer->tail, level + 1);
		printf("%d\n",*(int *)pointer->head);
		if (*((int *)pointer->head) == EQUAL) {
			Variable *a_variable = pop();
			if (a_variable->kind == INTEGER) {
				printf("%d\n",a_variable->integer);
			}
		}
		else {
			Variable *right = pop();
			Variable *left = pop();
			push(hogehoge(*((int *)pointer->head),left,right));
		}
	}
	else if (pointer->kind == LEAF) {
		Variable *in_variable = (Variable *)malloc(sizeof(Variable));
		if (*((int *)pointer->head) == INTEGER) {
			in_variable->kind = INTEGER;
			in_variable->integer = atoi((char *)pointer->tail);
		}
		else if (*((int *)pointer->head) == REAL) {
			in_variable->kind = REAL;
			in_variable->real = atof((char *)pointer->tail);
		}
		else if (*((int *)pointer->head) == ID) {
		}

		push(in_variable);
	}
	return;
}
