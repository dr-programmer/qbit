%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *yytext;
extern int line;

void yyerror(char *s);

struct decl *parser_result;

extern char *global_name_of_starting_file;
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
%type <expr> expr algebra term difactor factor fields next_expr registers reg circuit c_step
%type <expr> c_alias subsystem range concurrent_gate
%type <str> name string
%type <complex> number

%token TOKEN_RANGE

%token TOKEN_SEPARATOR

%token TOKEN_NEXT
%token TOKEN_ALIAS

%token TOKEN_AND

%token TOKEN_LOAD

%token TOKEN_COMPLEX_LITERAL
%token TOKEN_IDENT
%token TOKEN_STRING_LITERAL

%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_MODULUS

%token TOKEN_TENSOR_PRODUCT
%token TOKEN_POWER
%token TOKEN_TENSOR_PRODUCT_N_TIMES

%token TOKEN_SQRT

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

decl    : name TOKEN_LPAREN fields TOKEN_RPAREN
                                { $$ = decl_create($1, $3, 0, 0, line); }
        | TOKEN_LCRBR registers TOKEN_RCRBR circuit
                                { $$ = decl_create(0, $2, $4, 0, line); }
        | TOKEN_LOAD TOKEN_LPAREN string TOKEN_RPAREN
                                { 
                                        $$ = decl_create(0, 0, 0, 0, line);
                                        $$->file_name = $3; 
                                }
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

term    : term TOKEN_MUL difactor
                                { $$ = expr_create(EXPR_MUL, $1, $3, line); }
        | term TOKEN_DIV difactor
                                { $$ = expr_create(EXPR_DIV, $1, $3, line); }
        | term TOKEN_MODULUS difactor
                                { $$ = expr_create(EXPR_MODULUS, $1, $3, line); }
        | term TOKEN_TENSOR_PRODUCT difactor
                                { $$ = expr_create(EXPR_TENSOR_PRODUCT, $1, $3, line); }
        | difactor              { $$ = $1; }
        ;

difactor: difactor TOKEN_POWER factor
                                { $$ = expr_create(EXPR_POWER, $1, $3, line); }
        | difactor TOKEN_TENSOR_PRODUCT_N_TIMES factor
                                { 
                                        $$ = expr_create(
                                                EXPR_TENSOR_PRODUCT_N_TIMES, 
                                                $1, 
                                                $3, 
                                                line
                                        ); 
                                }
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
                        float num;
                        if(!imaginary || len != 1) num = atof(yytext);
                        else num = 1;
                        struct complex result = imaginary == 0 
                                                ? complex_create(num, 0) 
                                                : complex_create(0, num)
                                                ;
                        $$ = result; 
                }

fields  : expr next_expr        { 
                                        if($2 == NULL) 
                                                $$ = $1;
                                        else 
                                                $$ = expr_create(EXPR_FIELD, $1, $2, line); 
                                }
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
        | TOKEN_ALIAS c_alias circuit
                                { $$ = expr_create(EXPR_CIRCUIT_ALIAS, $2, $3, line); }
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
        : TOKEN_LSQBR expr TOKEN_RSQBR
                                { $$ = $2; }
        | TOKEN_LSQBR range TOKEN_RSQBR
                                { $$ = $2; }
        ;

range   : expr TOKEN_RANGE expr
                                { $$ = expr_create(EXPR_RANGE, $1, $3, line); }
        ;

concurrent_gate
        : TOKEN_AND c_step      { $$ = $2; }
        |                       { $$ = 0; }
        ;

c_alias : name                  { 
                                        $$ = expr_create(EXPR_ALIAS, 0, 0, line);
                                        $$->name = $1;
                                        $$->declaration = decl_create($1, 0, 0, 0, line);
                                        $$->declaration->value = 
                                                        expr_create(EXPR_DUMMY, 0, 0, line);
                                        $$->declaration->value->name = "$alias"; 
                                }
        | name subsystem        { 
                                        $$ = expr_create(EXPR_ALIAS, 0, $2, line);
                                        $$->name = $1;
                                        $$->declaration = decl_create($1, 0, 0, 0, line);
                                        $$->declaration->value = 
                                                        expr_create(EXPR_DUMMY, 0, 0, line);
                                        $$->declaration->value->name = "$alias[]"; 
                                }
        ;

string  : TOKEN_STRING_LITERAL  { 
                                        char *temp = (char *)
                                                smart_allocate(strlen(yytext), sizeof(char));
                                        strcpy(temp, yytext+1);
                                        temp[strlen(temp)-1] = '\0';
                                        $$ = temp; 
                                }

%%

void yyerror(char *s) {
    error_count++;
    fprintf(stderr, BLU "%s" RESET ": ", global_name_of_starting_file);
    fprintf(stderr, RED "Error" RESET \
        MAG" |%s|"RESET"->"YEL"|%s|"RESET" on line %d \n", s, yytext, line);
}