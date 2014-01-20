TARGET	= pala

# LINK (*.o)
LD	= cc
LDFLAGS	= -W

# COMPILE (*.c)
CC	= cc
CCFLAGS	= -W -O2

# GENERATOR (*.lex and *.yac)
LEX	= flex
YAC	= yacc

OBJS	= y.tab.o main.o
DEFS	= defs.h
REXP	= rexp.lex
LEXC	= lex.yy.c
SYNS	= syns.yac
YACC	= y.tab.c
SRC	= src.pd
DEMODIR	= Demo
TMP	= tmp.txt
OPEN	= vim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(DEFS)

$(LEXC): $(REXP) $(DEFS)
	$(LEX) $(REXP)

$(YACC): $(SYNS) $(LEXC) $(DEFS)
	$(YAC) $(SYNS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET)* $(OBJS) $(LEXC) $(YACC) $(TMP) *\~

eat: all
	./$(TARGET) $(DEMODIR)/$(SRC) > $(TMP)
	cat $(TMP)
talk: all
	./$(TARGET)
install:
	sudo cp $(TARGET) /usr/bin/$(TARGET)
open:
	$(OPEN) $(DEFS) $(REXP) $(SYNS)

