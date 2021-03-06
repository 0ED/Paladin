#
# Copyright (C) 2013-2014 Tasuku TAKAHASHI All Rights Reserved.
#
# Makefile for Paladin.
# This file is main's Makefile.
# If you install Paladin, type as below.
#
#	make
#	make install
#

# === Variables set ===
TARGET	= pala

# LINK (*.o)
LD		= cc
LDFLAGS	= -W

# COMPILE (*.c)
CC		= cc
CCFLAGS	= -W -O2

# GENERATOR (*.lex and *.yac)
LEX		= flex
YAC		= yacc 

OBJS	= \
	main.o \
	stack.o \
	hashmap.o \
	y.tab.o 
SOURCES	= ${OBJS:%.o=%.c}
DEFS	= defs.h	
REXP	= rexp.lex
LEXC	= lex.yy.c
SYNS	= syns.yac
YACC	= y.tab.c
SRC		= dynamic.pd
DEMODIR	= Demo
TMP		= tmp.txt
EDITER	= vim 
 
#############################################

# Compiler
all: $(TARGET)

$(TARGET): $(YACC) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(DEFS)

$(LEXC): $(REXP) $(DEFS)
	$(LEX) $(REXP)

$(YACC): $(SYNS) $(LEXC) $(DEFS)
	$(YAC) $(SYNS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

# Tasker
clean:
	-rm -f $(TARGET)* $(OBJS) $(LEXC) $(YACC) $(TMP) y.tab.h *\~

install:
	sudo cp $(TARGET) /usr/bin/$(TARGET)
open:
	$(EDITER) $(DEFS) $(REXP) $(SYNS) $(SOURCES)

# Tester
eat: 
	./$(TARGET) $(DEMODIR)/$(SRC) 
talk: 
	./$(TARGET)
01:
	./$(TARGET) $(DEMODIR)/dynamic.pd
02:
	./$(TARGET) $(DEMODIR)/inspect.pd
03:
	./$(TARGET) $(DEMODIR)/error.pd

