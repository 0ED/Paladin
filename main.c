#include "defs.h"

int main(int argumentCount, char* argumentValues[]) {
	linecounter = 1;
	if (argumentCount < 2) {
		talk();
	}
	else {
		eat_code(argumentValues[1]);
	}
	return(EXIT_SUCCESS);
}

void talk() {
	char a_line[READLINE_SIZE];
	while (fgets(a_line, sizeof a_line, stdin) != NULL) {
		yy_scan_string(a_line);
		yyparse();
	}
	return;
}

void eat_code(char *filename) {
	yyin = fopen(filename,"r");
	if(yyin == NULL) {
		fprintf(stderr, "Can't open a input file!\n");
		exit(EXIT_FAILURE);
	}
	yyparse();
	return;
}

Cell *cons(Cell *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = CONS;
	pointer->head = car;
	pointer->tail = cdr;
	return(pointer);
}

Cell *node(char *car, Cell *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = NODE;
	pointer->head = (Cell *)strdup(car);
	pointer->tail = cdr;
	return(pointer);
}

Cell *leaf(char *car, char *cdr) {
	Cell *pointer;

	pointer = (Cell *)malloc(sizeof(Cell));
	pointer->kind = LEAF;
	pointer->head = (Cell *)strdup(car);
	pointer->tail = (Cell *)strdup(cdr);
	return(pointer);
}

void tree(Cell *pointer) {
	visit(pointer, 1);
	printf("\n");
}

void visit(Cell *pointer, int level) {
	int count;

	printf("\n");
	for (count = 0; count < level; count++) {
		printf("    ");
	}
	if (pointer->kind == CONS) {
		printf("cons(");
		visit(pointer->head, level + 1);
		visit(pointer->tail, level + 1);
		printf(")");
	}
	if (pointer->kind == NODE) {
		printf("node(");
		printf("%s ", (char *)pointer->head);
		visit(pointer->tail, level + 1);
		printf(")");
	}
	if (pointer->kind == LEAF) {
		printf("leaf(");
		printf("%s ", (char *)pointer->head);
		printf("%s", (char *)pointer->tail);
		printf(")");
	}
	return;
}
