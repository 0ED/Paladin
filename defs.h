/*
 * Paladin.
 * Copyright (C) 2014 TasukuTAKAHASHI All Rights Reserved.
 * This file is a part of Paladin.
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
#include "stack.h"
#include "hashmap.h"

#define TRUE	1
#define FALSE	0
#define READLINE_SIZE 256

enum {CONS, NODE, LEAF};

typedef struct cell 
{
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;
typedef struct yy_buffer_state *YY_BUFFER_STATE_TMP;

bool is_talk;
Stack *rpn_stack;
Hashmap *var_hashmap;
extern char *yytext;
extern int linecounter;
extern FILE *yyin;
 
int main(int argumentCount, char* argumentValues[]);
int yylex(void);
void comment(void);
int yyparse(void);
void yyerror(char *);
YY_BUFFER_STATE_TMP yy_scan_string(const char *yy_str);
Cell *cons(Cell *, Cell *);
Cell *node(int, Cell *);
Cell *leaf(int, char *);
void tree(Cell *);
void visit(Cell *, int);
void talk(void);
void eat_code(char *);
Variable *do_four_arithmetic(int, Variable *, Variable *);

#endif /* !__INCLUDE_DEFS_H__ */

