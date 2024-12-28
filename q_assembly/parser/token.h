/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Q_ASSEMBLY_PARSER_TOKEN_H_INCLUDED
# define YY_YY_Q_ASSEMBLY_PARSER_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "q_assembly/parser/parser.y"


#include "colors.h"
#include "structures.h"
#include "smart_allocation.h"
#include "complex_numbers.h"


#line 58 "q_assembly/parser/token.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_RANGE = 258,             /* TOKEN_RANGE  */
    TOKEN_SEPARATOR = 259,         /* TOKEN_SEPARATOR  */
    TOKEN_NEXT = 260,              /* TOKEN_NEXT  */
    TOKEN_ALIAS = 261,             /* TOKEN_ALIAS  */
    TOKEN_AND = 262,               /* TOKEN_AND  */
    TOKEN_LOAD = 263,              /* TOKEN_LOAD  */
    TOKEN_COMPLEX_LITERAL = 264,   /* TOKEN_COMPLEX_LITERAL  */
    TOKEN_IDENT = 265,             /* TOKEN_IDENT  */
    TOKEN_STRING_LITERAL = 266,    /* TOKEN_STRING_LITERAL  */
    TOKEN_PLUS = 267,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 268,             /* TOKEN_MINUS  */
    TOKEN_MUL = 269,               /* TOKEN_MUL  */
    TOKEN_DIV = 270,               /* TOKEN_DIV  */
    TOKEN_MODULUS = 271,           /* TOKEN_MODULUS  */
    TOKEN_TENSOR_PRODUCT = 272,    /* TOKEN_TENSOR_PRODUCT  */
    TOKEN_POWER = 273,             /* TOKEN_POWER  */
    TOKEN_TENSOR_PRODUCT_N_TIMES = 274, /* TOKEN_TENSOR_PRODUCT_N_TIMES  */
    TOKEN_SQRT = 275,              /* TOKEN_SQRT  */
    TOKEN_LESS = 276,              /* TOKEN_LESS  */
    TOKEN_GREATER = 277,           /* TOKEN_GREATER  */
    TOKEN_LPAREN = 278,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 279,            /* TOKEN_RPAREN  */
    TOKEN_LCRBR = 280,             /* TOKEN_LCRBR  */
    TOKEN_RCRBR = 281,             /* TOKEN_RCRBR  */
    TOKEN_LSQBR = 282,             /* TOKEN_LSQBR  */
    TOKEN_RSQBR = 283,             /* TOKEN_RSQBR  */
    TOKEN_COMMA = 284,             /* TOKEN_COMMA  */
    TOKEN_COLON = 285,             /* TOKEN_COLON  */
    TOKEN_SEMI = 286,              /* TOKEN_SEMI  */
    TOKEN_ERROR = 287              /* TOKEN_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "q_assembly/parser/parser.y"

    struct decl *decl;
    struct expr *expr;
    char *str;
    struct complex complex;

#line 114 "q_assembly/parser/token.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Q_ASSEMBLY_PARSER_TOKEN_H_INCLUDED  */
