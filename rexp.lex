%{
int linecounter = 1;
%}
%option nounput
%%
"quit"					{ exit(EXIT_SUCCESS); } 
"print"					{ return(PRINT); }
[a-zA-Z_][a-zA-Z0-9_]*	{ return(ID); }
[0-9]+					{ return(INTEGER); }
[0-9]*"."[0-9]+			{ return(REAL); }
\".*\"					{ return(WQUOTED); }
\'.*\'					{ return(SQUOTED); }
";"						{ return(SEMICOLON); }
","						{ return(COMMA); }
"="						{ return(EQUAL); }
"+"						{ return(ADD); }
"-"						{ return(SUBTRACT); }
"*"						{ return(MULTIPLY); }
"/"						{ return(DIVIDE); }
"("						{ return(LPAR); }
")"						{ return(RPAR); }
"\n"					{ if (!is_talk) { linecounter++; } return(NEWLINE); }
"\r\n"					{ if (!is_talk) { linecounter++; } return(NEWLINE); }
"\r"					{ if (!is_talk) { linecounter++; } return(NEWLINE); }
" "|"\t"				{ }
"/*"					{ comment(); }
.						{ return(UNKNOWN); }
%%
int yywrap(void) {
	return(1);
}
void comment(void) {
	int boolean, first, second;

	boolean = TRUE;
	first = input();
	while (first != EOF && boolean) {
		second = input();
		if (first == '*' && second == '/') {
			boolean = FALSE;
		} else if (first == '\r' && second == '\n') {
			linecounter++;
			first = input();
		} else {
			if (first == '\r' || first == '\n') {
				linecounter++;
			}
			first = second;
		}
	}
	if (first == EOF) {
		fprintf(stderr, "eof in comment\n");
	}
}
