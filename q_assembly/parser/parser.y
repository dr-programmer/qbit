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
    struct expr *expr;
    char *str;
    struct complex complex;
};

%type <decl> program decl_list decl
%type <expr> expr algebra term factor fields next_expr registers reg circuit c_step
%type <expr> subsystem range concurrent_gate
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
        : decl decl_list        { $$ = $1; $1->next = $2; }
        |                       { $$ = 0; }
        ;

decl    : name TOKEN_LPAREN expr TOKEN_RPAREN
                                { $$ = decl_create($1, $3, 0, 0, line); }
        | name TOKEN_LPAREN fields TOKEN_RPAREN
                                { $$ = decl_create($1, $3, 0, 0, line); }
        | TOKEN_LCRBR registers TOKEN_RCRBR circuit
                                { $$ = decl_create(0, $2, $4, 0, line); }
        ;

name    : TOKEN_IDENT
                {
                        char *temp = (char *)smart_allocate(strlen(yytext), sizeof(char));
                        strcpy(temp, yytext);
                        $$ = temp; 
                }
        ;

expr    : algebra               { $$ = $1; }
        ;

algebra : algebra TOKEN_PLUS term
                                { $$ = expr_create(EXPR_ADD, $1, $3, line); }
        | algebra TOKEN_MINUS term
                                { $$ = expr_create(EXPR_SUB, $1, $3, line); }
        | term                  { $$ = $1; }
        ;

term    : term TOKEN_MUL factor { $$ = expr_create(EXPR_MUL, $1, $3, line); }
        | term TOKEN_DIV factor { $$ = expr_create(EXPR_DIV, $1, $3, line); }
        | term TOKEN_MODULUS factor
                                { $$ = expr_create(EXPR_MODULUS, $1, $3, line); }
        | term TOKEN_TENSOR_PRODUCT factor
                                { $$ = expr_create(EXPR_TENSOR_PRODUCT, $1, $3, line); }
        | factor                { $$ = $1; }
        ;

factor  : TOKEN_LPAREN name TOKEN_RPAREN
                                { $$ = expr_create_name($2, line); }
        | TOKEN_MINUS factor    { 
                                        $$ = expr_create(EXPR_MUL, 
                                                expr_create_complex_literal(
                                                        complex_create(-1, 0), 
                                                        line
                                                ), 
                                                $2, 
                                                line
                                        ); 
                                }
        | TOKEN_SQRT factor     { $$ = expr_create(EXPR_SQRT, 0, $2, line); }
        | number                { $$ = expr_create_complex_literal($1, line); }
        | TOKEN_SEPARATOR number TOKEN_GREATER
                                { 
                                        $$ = expr_create(
                                                EXPR_KET, 
                                                0, 
                                                expr_create_complex_literal($2, line), 
                                                line
                                        ); 
                                }
        | TOKEN_LESS number TOKEN_SEPARATOR
                                { 
                                        $$ = expr_create(
                                                EXPR_BRA, 
                                                expr_create_complex_literal($2, line), 
                                                0, 
                                                line
                                        ); 
                                }
        | TOKEN_LPAREN expr TOKEN_RPAREN
                                { $$ = $2; }
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

fields  : expr next_expr        { $$ = expr_create(EXPR_FIELD, $1, $2, line); }
        |                       { $$ = 0; }
        ;

next_expr
        : TOKEN_COMMA fields
                                { $$ = $2; }
        | TOKEN_SEPARATOR fields
                                { $$ = $2; }
        |                       { $$ = 0; }
        ;

registers
        : reg registers         { $$ = expr_create(EXPR_REGISTER, $1, $2, line); }
        |                       { $$ = 0; }
        ;

reg     : TOKEN_LCRBR fields TOKEN_RCRBR
                                { $$ = $2; }
        ;

circuit : TOKEN_NEXT c_step circuit
                                { $$ = expr_create(EXPR_CIRCUIT_STEP, $2, $3, line); }
        |                       { $$ = 0; }
        ;

c_step  : expr                  { $$ = expr_create(EXPR_APPLY_GATE, $1, 0, line); }
        | expr subsystem concurrent_gate
                                { 
                                        $$ = expr_create(
                                                EXPR_AND, 
                                                expr_create(EXPR_APPLY_GATE, $1, $2, line), 
                                                $3, 
                                                line
                                        ); 
                                }
        | TOKEN_LESS            { $$ = expr_create(EXPR_MEASURE, 0, 0, line); }
        | TOKEN_LESS subsystem concurrent_gate
                                {
                                        $$ = expr_create(
                                                EXPR_AND, 
                                                expr_create(EXPR_MEASURE, 0, $2, line), 
                                                $3, 
                                                line
                                        ); 
                                }
        ;

subsystem
        : TOKEN_LSQBR number TOKEN_RSQBR
                                { $$ = expr_create_complex_literal($2, line); }
        | TOKEN_LSQBR range TOKEN_RSQBR
                                { $$ = $2; }
        ;

range   : number TOKEN_RANGE number
                                { 
                                        $$ = expr_create(
                                                EXPR_RANGE, 
                                                expr_create_complex_literal($1, line), 
                                                expr_create_complex_literal($3, line), 
                                                line
                                        ); 
                                }
        ;

concurrent_gate
        : TOKEN_AND c_step      { $$ = $2; }
        |                       { $$ = 0; }
        ;

%%

void yyerror(char *s) {
    error_count++;
    fprintf(stderr, RED "Error" RESET \
        MAG" |%s|"RESET"->"YEL"|%s|"RESET" on line %d \n", s, yytext, line);
}