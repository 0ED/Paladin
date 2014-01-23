/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#include "defs.h"

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
Cell *node(char *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = NODE;
	pointer->head = (Cell *)strdup(car);
	pointer->tail = cdr;
	return(pointer);
}

/*
 * Syntactic Analysis
 */
Cell *leaf(char *car, char *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = LEAF;
	pointer->head = (Cell *)strdup(car);
	pointer->tail = (Cell *)strdup(cdr);
	return(pointer);
}

/*
 * Syntactic Analysis
 */
void tree(Cell *pointer) {
	visit(pointer, 1);
}

/*
 * Syntactic Analysis
 */
Cell *visit(Cell *pointer, int level) {
	if (pointer->kind == CONS) {
		visit(pointer->head, level + 1);
		visit(pointer->tail, level + 1);
		return(pointer); //need pointer of head & talk
	}
	else if (pointer->kind == NODE) {
		Cell *node = visit(pointer->tail, level + 1);
		if (strcmp((char *)pointer->head, "=") == 0) {
			printf("\n");
		}
		/*
		else if ((int)operator == '+') {
			cons->integer = atoi((char *)cons->head) + atoi((char *)cons->tail);
			return(cons);
		}
		else if ((int)operator == '-') {
			cons->integer = atoi((char *)cons->head) - atoi((char *)cons->tail);
			return(cons);
		}
		else if ((int)operator == '*') {
			cons->integer = atoi((char *)cons->head) *  atoi((char *)cons->tail);
			return(cons);
		}
		else if ((int)operator == '/') {
			cons->integer = atoi((char *)cons->head) / atoi((char *)cons->tail);
			return(cons);
		}
		else {
			return(NULL);
		}
		*/
		return(pointer);
	}
	else if (pointer->kind == LEAF) {
		printf("%s %s\n", (char *)pointer->head, (char *)pointer->tail);
		if (strcmp((char *)pointer->head,"INTEGER") == 0) {
			pointer->integer = atoi((char *)pointer->tail); 
		}
		else if (strcmp((char *)pointer->head,"REAL") == 0) {
			pointer->real = atoi((char *)pointer->tail); 
		}
		/* 
		else if (strcmp((char *)pointer->head,"") == 0) {
			pointer->integer = atoi((char *)pointer->tail); 
		}
		*/
		return(pointer);
	}
	else {
		return(NULL);
	}
}
