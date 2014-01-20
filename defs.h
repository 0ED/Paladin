#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE	1
#define FALSE	0
#define STACK_MAX 100 
#define READLINE_SIZE 256 

enum {CONS, NODE, LEAF};

typedef struct cell {
	int          kind;
	struct cell *head;
	struct cell *tail;
} Cell;
typedef struct yy_buffer_state *YY_BUFFER_STATE_TMP;

extern char *yytext;
extern int linecounter;
extern FILE *yyin;
double stack[STACK_MAX];
int stack_point;

int main(int argumentCount, char* argumentValues[]);
int yylex(void);
void comment(void);
int yyparse(void);
void yyerror(char*);
YY_BUFFER_STATE_TMP yy_scan_string(const char *yy_str  );
Cell *cons(Cell *, Cell *);
Cell *node(char *, Cell *);
Cell *leaf(char *, char *);
void tree(Cell *);
void visit(Cell *, int);
void talk();
void eat_code(char *);

