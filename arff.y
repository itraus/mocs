%start parser
%token RELATION ATTRIBUTE DATA REAL INTEGER SEMICOLON COMA OPEN CLOSE OPEN_INT CLOSE_INT STRING

%{

#include <string>
#include <cstdlib>
#include <iostream>

#include <mocs/config.h>
#include <mocs/arff.h>

#define YYPARSE_PARAM arff

extern int arff_lineno;

int arff_lex();

int arff_error(char *s) {
	cerr << "arff: " << s << " in line " << arff_lineno << endl;
	assert(false);
	return 0;
}

%}

%%

parser:
	RELATION STRING
	attributes
	DATA
	instances
	;

attributes:
	|
	attributes nominal
	|
	attributes integer
	|
	attributes real
	;

nominal:
	ATTRIBUTE STRING
	{ ((Arff*)arff)->addNominal(); }
	OPEN list_names CLOSE
	{ ((Arff*)arff)->endNominal(); }
	;

integer:
	ATTRIBUTE STRING INTEGER OPEN_INT STRING COMA STRING CLOSE_INT
	{ ((Arff*)arff)->addInteger($5.c_str(),$7.c_str()); }
	;

real:
	ATTRIBUTE STRING REAL
	{ ((Arff*)arff)->addReal(); }
	;

list_names:
	list_names COMA STRING
	{ ((Arff*)arff)->addNominalValue($3.c_str()); }
	|
	STRING
	{ ((Arff*)arff)->addNominalValue($1.c_str()); }
	;

instances:
	instances
	{ ((Arff*)arff)->addInstance(); }
	list_values
	{ ((Arff*)arff)->endInstance(); }
	|
	{ ((Arff*)arff)->addInstance(); }
	list_values
	{ ((Arff*)arff)->endInstance(); }
	;

list_values:
	list_values COMA STRING
	{ ((Arff*)arff)->addValue($3.c_str()); }
	|
	STRING
	{ ((Arff*)arff)->addValue($1.c_str()); }
	;
