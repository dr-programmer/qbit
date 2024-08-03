%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *yytext;
extern int line;

void yyerror(char *s);

struct decl *parser_result;
%}

%code requires {

#include "colors.h"
#include "structures.h"
#include "smart_allocation.h"
#include "complex_numbers.h"

}

%union {
    struct decl *decl;
    char *str;
    struct complex complex;
};

%type <decl> program decl_list decl
%type <str> name
%type <complex> number

%token TOKEN_RANGE

%token TOKEN_SEPARATOR

%token TOKEN_NEXT

%token TOKEN_AND

%token TOKEN_COMPLEX_LITERAL
%token TOKEN_IDENT

%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_MODULUS

%token TOKEN_SQRT
%token TOKEN_TENSOR_PRODUCT

%token TOKEN_LESS
%token TOKEN_GREATER

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

program : decl_list             { parser_result = $1; }
        ;

decl_list
        : decl decl_list        { $$ = $1; /*$1->next = $2;*/ }
        |                       { $$ = 0; }
        ;

decl    : name TOKEN_LPAREN expr TOKEN_RPAREN
                                { $$ = decl_create(); }
        | name TOKEN_LPAREN fields TOKEN_RPAREN
                                { $$ = decl_create(); }
        | TOKEN_LCRBR registers TOKEN_RCRBR circuit
                                { $$ = decl_create(); }
        ;

name    : TOKEN_IDENT
                {
                        char *temp = (char *)smart_allocate(strlen(yytext), sizeof(char));
                        strcpy(temp, yytext);
                        $$ = temp; 
                }
        ;

expr    : algebra               //{ $$ = $1; }
        ;

algebra : algebra TOKEN_PLUS term
                                {  }
        | algebra TOKEN_MINUS term
                                {  }
        | term                  {  }
        ;

term    : term TOKEN_MUL factor {  }
        | term TOKEN_DIV factor {  }
        | term TOKEN_MODULUS factor
                                {  }
        | term TOKEN_TENSOR_PRODUCT factor
                                {  }
        | factor                {  }
        ;

factor  : TOKEN_LPAREN name TOKEN_RPAREN
                                {  }
        | TOKEN_MINUS factor    {  }
        | TOKEN_SQRT factor     {  }
        | number                {  }
        | TOKEN_SEPARATOR number TOKEN_GREATER
                                {  }
        | TOKEN_LESS number TOKEN_SEPARATOR
                                {  }
        | TOKEN_LPAREN expr TOKEN_RPAREN
                                {  }
        ;

number  : TOKEN_COMPLEX_LITERAL
                {
                        unsigned short imaginary = 0;
                        unsigned int len = strlen(yytext);
                        if(yytext[len-1] == 'i') {
                                yytext[len-1] = '\0';
                                imaginary = 1;
                        }
                        float num = atof(yytext);
                        struct complex result = imaginary == 0 
                                                ? complex_create(num, 0) 
                                                : complex_create(0, num)
                                                ;
                        $$ = result; 
                }

fields  : expr next_expr        {  }
        |                       {  }
        ;

next_expr
        : TOKEN_COMMA fields
                                {  }
        | TOKEN_SEPARATOR fields
                                {  }
        |                       {  }
        ;

registers
        : reg registers         {  }
        |                       {  }
        ;

reg     : TOKEN_LCRBR fields TOKEN_RCRBR
                                {  }
        ;

circuit : TOKEN_NEXT expr circuit
                                {  }
        | TOKEN_NEXT expr subsystem circuit
                                {  }
        | TOKEN_NEXT TOKEN_LESS circuit
                                {  }
        | TOKEN_NEXT TOKEN_LESS subsystem circuit
                                {  }
        |                       {  }
        ;

subsystem
        : TOKEN_LSQBR number TOKEN_RSQBR
                                {  }
        | TOKEN_LSQBR range TOKEN_RSQBR
                                {  }
        ;

range   : number TOKEN_RANGE number
                                {  }
        ;

%%

void yyerror(char *s) {
    error_count++;
    fprintf(stderr, RED "Error" RESET \
        MAG" |%s|"RESET"->"YEL"|%s|"RESET" on line %d \n", s, yytext, line);
}