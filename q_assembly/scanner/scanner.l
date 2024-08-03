%{
#include "token.h"

int line = 1;
%}

DIGITS [0-9]
LETTERS [a-zA-Z]

%x multiline_comment

%%

(" "|\t)
"\n"        {line++;}
\-\>        {return TOKEN_NEXT;}
\+          {return TOKEN_PLUS;}
\-          {return TOKEN_MINUS;}
\*          {return TOKEN_MUL;}
\/          {return TOKEN_DIV;}
\%          {return TOKEN_MODULUS;}
\#          {return TOKEN_SQRT;}
\@          {return TOKEN_TENSOR_PRODUCT;}
\&\&        {return TOKEN_AND;}
\<\?        {BEGIN(multiline_comment);}
<multiline_comment>[^\?]*
<multiline_comment>\?+[^\?\>]*
<multiline_comment>\?\>     {BEGIN(INITIAL);}
\?\?.*"\n"
"<"         {return TOKEN_LESS;}
>           {return TOKEN_GREATER;}
\.{3}       {return TOKEN_RANGE;}
\|          {return TOKEN_SEPARATOR;}
{DIGITS}+(\.{DIGITS}+)?i?   {return TOKEN_COMPLEX_LITERAL;}
({LETTERS}|_)({LETTERS}|{DIGITS}|_)*  {return TOKEN_IDENT;}
\(          {return TOKEN_LPAREN;}
\)          {return TOKEN_RPAREN;}
\{          {return TOKEN_LCRBR;}
\}          {return TOKEN_RCRBR;}
\[          {return TOKEN_LSQBR;}
\]          {return TOKEN_RSQBR;}
,           {return TOKEN_COMMA;}
:           {return TOKEN_COLON;}
;           {return TOKEN_SEMI;}
.           {return TOKEN_ERROR;}

%%

int yywrap() {return 1;}