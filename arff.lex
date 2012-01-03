%option noyywrap
%option yylineno

%{

#include <string>
#include <iostream>
#include <typeinfo>

#include <mocs/config.h>
#include "arff.tab.h"

#define YY_NO_UNPUT 1
#define YY_NEVER_INTERACTIVE 1

extern YYSTYPE arff_lval;

%}

RELATION	@relation
ATTRIBUTE	@attribute
DATA		@data
REAL		real
INTEGER		integer
COMA		,
OPEN		\{
CLOSE		\}
STRING		[A-Za-z0-9_\.\-+\?'&/<>=]+
OPEN_INT	\[
CLOSE_INT	\]

SP			[\t\r\n\b ]+
COM			%[^\n]*\n

%%

{RELATION}		{ return RELATION; }
{ATTRIBUTE}		{ return ATTRIBUTE; }
{DATA}			{ return DATA; }
{REAL}			{ return REAL; }
{INTEGER}		{ return INTEGER; }
{COMA}			{ return COMA; }
{OPEN}			{ return OPEN; }
{CLOSE}			{ return CLOSE; }
{STRING}		{ arff_lval=arff_text; return STRING; }
{OPEN_INT}		{ return OPEN_INT; }
{CLOSE_INT}		{ return CLOSE_INT; }

{SP}
{COM}
