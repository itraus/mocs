%start parser
%token STRING EQUAL SEMICOLON

%{

#include <string>
#include <iostream>

#include <mocs/config.h>
#include <mocs/params.h>

#define YYPARSE_PARAM params

extern int params_lineno;

int params_lex();

int params_error(char *s) {
	cerr << "params: " << s << " in line " << params_lineno << endl;
	assert(false);
	return 0;
}

%}

%%

parser:
	|
	parser
	STRING
	EQUAL
	STRING
	{ ((Params*)params)->put(strdup($2.c_str()),strdup($4.c_str())); }
	SEMICOLON
	;
