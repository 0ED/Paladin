/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_DEFS_H__
#define __INCLUDE_DEFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE	1
#define FALSE	0
#define STACK_MAX 100 
#define READLINE_SIZE 256 

enum {CONS, NODE, LEAF};

typedef struct cell {
	int          kind;
	int			 integer;
	double		 real;
	char		*string;
	struct cell *head;
	struct cell *tail;
} Cell;
typedef struct variables {
	char *name;
	int type;
	struct variables *next;
} Variables;
typedef struct yy_buffer_state *YY_BUFFER_STATE_TMP;

extern char *yytext;
extern int linecounter;
extern FILE *yyin;
double stack[STACK_MAX];
int stack_point;
bool is_talk;

int main(int argumentCount, char* argumentValues[]);
int yylex(void);
void comment(void);
int yyparse(void);
void yyerror(char*);
YY_BUFFER_STATE_TMP yy_scan_string(const char *yy_str);
Cell *cons(Cell *, Cell *);
Cell *node(char *, Cell *);
Cell *leaf(char *, char *);
void tree(Cell *);
Cell *visit(Cell *, int);
void talk();
void eat_code(char *);

#endif /* !__INCLUDE_DEFS_H__*/

