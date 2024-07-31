%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

extern int yylex();
extern char *yytext;
extern int line;

void yyerror(char *s);

%}

%union {

};

%token TOKEN_SUBSCRIPT

%token TOKEN_AND

%token TOKEN_COMPLEX_LITERAL
%token TOKEN_IDENT

%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_MODULUS

%token TOKEN_LESS

%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LCRBR
%token TOKEN_RCRBR
%token TOKEN_LSQBR
%token TOKEN_RSQBR

%token TOKEN_COMMA
%token TOKEN_COLON
%token TOKEN_SEMI

%token TOKEN_ERROR

%%

program : 
        ;

%%

void yyerror(char *s) {
    //error_count++;
    fprintf(stderr, RED "Error" RESET \
        MAG" |%s|"RESET"->"YEL"|%s|"RESET" on line %d \n", s, yytext, line);
}