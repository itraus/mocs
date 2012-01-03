%option noyywrap
%option yylineno

%{

#include <string>
#include <iostream>
#include <typeinfo>

#include <mocs/config.h>
#include "params.tab.h"

#define YY_NO_UNPUT 1
#define YY_NEVER_INTERACTIVE 1

extern YYSTYPE params_lval;

%}

SP			[\t\r\n\b ]+
COM			#[^\n]*\n

STRING		[A-Za-z0-9_:,\.\-/@]+
EQUAL		=
SEMICOLON	;

%%

{SP}
{COM}
{STRING}		{ params_lval=params_text; return STRING; }
{EQUAL}			{ return EQUAL; }
{SEMICOLON}		{ params_lval=params_text; return SEMICOLON; }
