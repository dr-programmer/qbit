/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "q_assembly/parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *yytext;
extern int line;

void yyerror(char *s);

struct decl *parser_result;

extern char *global_name_of_starting_file;

#line 87 "q_assembly/parser/parser.y.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "token.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_RANGE = 3,                /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_SEPARATOR = 4,            /* TOKEN_SEPARATOR  */
  YYSYMBOL_TOKEN_NEXT = 5,                 /* TOKEN_NEXT  */
  YYSYMBOL_TOKEN_AND = 6,                  /* TOKEN_AND  */
  YYSYMBOL_TOKEN_LOAD = 7,                 /* TOKEN_LOAD  */
  YYSYMBOL_TOKEN_COMPLEX_LITERAL = 8,      /* TOKEN_COMPLEX_LITERAL  */
  YYSYMBOL_TOKEN_IDENT = 9,                /* TOKEN_IDENT  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 10,      /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_PLUS = 11,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 12,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MUL = 13,                 /* TOKEN_MUL  */
  YYSYMBOL_TOKEN_DIV = 14,                 /* TOKEN_DIV  */
  YYSYMBOL_TOKEN_MODULUS = 15,             /* TOKEN_MODULUS  */
  YYSYMBOL_TOKEN_TENSOR_PRODUCT = 16,      /* TOKEN_TENSOR_PRODUCT  */
  YYSYMBOL_TOKEN_POWER = 17,               /* TOKEN_POWER  */
  YYSYMBOL_TOKEN_TENSOR_PRODUCT_N_TIMES = 18, /* TOKEN_TENSOR_PRODUCT_N_TIMES  */
  YYSYMBOL_TOKEN_SQRT = 19,                /* TOKEN_SQRT  */
  YYSYMBOL_TOKEN_LESS = 20,                /* TOKEN_LESS  */
  YYSYMBOL_TOKEN_GREATER = 21,             /* TOKEN_GREATER  */
  YYSYMBOL_TOKEN_LPAREN = 22,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 23,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LCRBR = 24,               /* TOKEN_LCRBR  */
  YYSYMBOL_TOKEN_RCRBR = 25,               /* TOKEN_RCRBR  */
  YYSYMBOL_TOKEN_LSQBR = 26,               /* TOKEN_LSQBR  */
  YYSYMBOL_TOKEN_RSQBR = 27,               /* TOKEN_RSQBR  */
  YYSYMBOL_TOKEN_COMMA = 28,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_COLON = 29,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMI = 30,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_ERROR = 31,               /* TOKEN_ERROR  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_decl_list = 34,                 /* decl_list  */
  YYSYMBOL_decl = 35,                      /* decl  */
  YYSYMBOL_name = 36,                      /* name  */
  YYSYMBOL_expr = 37,                      /* expr  */
  YYSYMBOL_algebra = 38,                   /* algebra  */
  YYSYMBOL_term = 39,                      /* term  */
  YYSYMBOL_difactor = 40,                  /* difactor  */
  YYSYMBOL_factor = 41,                    /* factor  */
  YYSYMBOL_number = 42,                    /* number  */
  YYSYMBOL_fields = 43,                    /* fields  */
  YYSYMBOL_next_expr = 44,                 /* next_expr  */
  YYSYMBOL_registers = 45,                 /* registers  */
  YYSYMBOL_reg = 46,                       /* reg  */
  YYSYMBOL_circuit = 47,                   /* circuit  */
  YYSYMBOL_c_step = 48,                    /* c_step  */
  YYSYMBOL_subsystem = 49,                 /* subsystem  */
  YYSYMBOL_range = 50,                     /* range  */
  YYSYMBOL_concurrent_gate = 51,           /* concurrent_gate  */
  YYSYMBOL_string = 52                     /* string  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   84

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    87,    88,    91,    93,    95,   102,   110,
     113,   115,   117,   120,   122,   124,   126,   128,   131,   133,
     142,   145,   147,   157,   158,   159,   168,   177,   181,   199,
     205,   209,   211,   213,   217,   218,   221,   225,   227,   230,
     231,   240,   241,   253,   255,   259,   264,   265,   268
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_RANGE",
  "TOKEN_SEPARATOR", "TOKEN_NEXT", "TOKEN_AND", "TOKEN_LOAD",
  "TOKEN_COMPLEX_LITERAL", "TOKEN_IDENT", "TOKEN_STRING_LITERAL",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_MUL", "TOKEN_DIV", "TOKEN_MODULUS",
  "TOKEN_TENSOR_PRODUCT", "TOKEN_POWER", "TOKEN_TENSOR_PRODUCT_N_TIMES",
  "TOKEN_SQRT", "TOKEN_LESS", "TOKEN_GREATER", "TOKEN_LPAREN",
  "TOKEN_RPAREN", "TOKEN_LCRBR", "TOKEN_RCRBR", "TOKEN_LSQBR",
  "TOKEN_RSQBR", "TOKEN_COMMA", "TOKEN_COLON", "TOKEN_SEMI", "TOKEN_ERROR",
  "$accept", "program", "decl_list", "decl", "name", "expr", "algebra",
  "term", "difactor", "factor", "number", "fields", "next_expr",
  "registers", "reg", "circuit", "c_step", "subsystem", "range",
  "concurrent_gate", "string", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-23)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      34,    -7,   -23,    -4,    23,   -23,    34,     7,    27,    32,
      13,    -4,   -23,   -23,    32,   -23,    16,    37,   -23,    32,
      32,    37,     2,     0,    14,     3,    -5,   -23,   -23,    17,
      41,   -23,    24,   -23,    39,   -23,   -23,    51,    40,    47,
      32,    32,   -23,    32,    32,    32,    32,    32,    32,    32,
      32,   -23,    53,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,     3,     3,    -5,    -5,    -5,    -5,   -23,   -23,     1,
      36,    41,    32,    58,    58,   -23,     4,    44,    53,   -23,
     -23,    32,   -23,   -23,   -23,   -23
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     8,    35,     0,     2,     4,     0,     0,    30,
       0,    35,     1,     3,    30,    48,     0,     0,    28,     0,
       0,     0,     0,    33,     9,    12,    17,    20,    24,     0,
      38,    34,     0,     7,     0,    22,    23,     0,     0,     0,
      30,    30,    29,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     6,     5,    25,    26,    21,    27,    32,
      31,    10,    11,    13,    14,    15,    16,    18,    19,    41,
      39,    38,     0,    47,    47,    37,     0,     0,     0,    42,
      40,     0,    43,    44,    46,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -23,   -23,    68,   -23,    54,   -22,   -23,     5,    21,   -17,
     -16,    -6,   -23,    66,   -23,     8,     6,    10,   -23,     9,
     -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    23,    24,    25,    26,    27,
      28,    29,    42,    10,    11,    53,    71,    73,    77,    79,
      16
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      39,    34,    35,    36,    40,    37,    17,    81,    32,    18,
      18,     2,    49,    50,    19,     8,    45,    46,    47,    48,
       9,    20,    21,    12,    22,    43,    44,    72,    41,    14,
      70,    82,    67,    68,    59,    60,    17,    15,    30,    33,
      18,     1,    51,     2,    19,    18,    52,    54,    61,    62,
      76,    20,    21,    37,    22,    56,    70,    17,     3,    85,
      55,    18,    72,    57,    78,    19,    63,    64,    65,    66,
      58,    83,    20,    69,    13,    22,    38,    31,     0,    75,
      74,     0,     0,    80,    84
};

static const yytype_int8 yycheck[] =
{
      22,    17,    19,    20,     4,    21,     4,     3,    14,     8,
       8,     9,    17,    18,    12,    22,    13,    14,    15,    16,
      24,    19,    20,     0,    22,    11,    12,    26,    28,    22,
      52,    27,    49,    50,    40,    41,     4,    10,    25,    23,
       8,     7,    25,     9,    12,     8,     5,    23,    43,    44,
      72,    19,    20,    69,    22,     4,    78,     4,    24,    81,
      21,     8,    26,    23,     6,    12,    45,    46,    47,    48,
      23,    27,    19,    20,     6,    22,    22,    11,    -1,    71,
      70,    -1,    -1,    74,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    24,    33,    34,    35,    36,    22,    24,
      45,    46,     0,    34,    22,    10,    52,     4,     8,    12,
      19,    20,    22,    37,    38,    39,    40,    41,    42,    43,
      25,    45,    43,    23,    42,    41,    41,    42,    36,    37,
       4,    28,    44,    11,    12,    13,    14,    15,    16,    17,
      18,    25,     5,    47,    23,    21,     4,    23,    23,    43,
      43,    39,    39,    40,    40,    40,    40,    41,    41,    20,
      37,    48,    26,    49,    49,    47,    37,    50,     6,    51,
      51,     3,    27,    27,    48,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    37,
      38,    38,    38,    39,    39,    39,    39,    39,    40,    40,
      40,    41,    41,    41,    41,    41,    41,    41,    42,    43,
      43,    44,    44,    44,    45,    45,    46,    47,    47,    48,
      48,    48,    48,    49,    49,    50,    51,    51,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     4,     4,     4,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     2,     2,     1,     3,     3,     3,     1,     2,
       0,     2,     2,     0,     2,     0,     3,     3,     0,     1,
       3,     1,     3,     3,     3,     3,     2,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: decl_list  */
#line 83 "q_assembly/parser/parser.y"
                                { parser_result = (yyvsp[0].decl); }
#line 1181 "q_assembly/parser/parser.y.c"
    break;

  case 3: /* decl_list: decl decl_list  */
#line 87 "q_assembly/parser/parser.y"
                                { (yyval.decl) = (yyvsp[-1].decl); (yyvsp[-1].decl)->next = (yyvsp[0].decl); }
#line 1187 "q_assembly/parser/parser.y.c"
    break;

  case 4: /* decl_list: %empty  */
#line 88 "q_assembly/parser/parser.y"
                                { (yyval.decl) = 0; }
#line 1193 "q_assembly/parser/parser.y.c"
    break;

  case 5: /* decl: name TOKEN_LPAREN fields TOKEN_RPAREN  */
#line 92 "q_assembly/parser/parser.y"
                                { (yyval.decl) = decl_create((yyvsp[-3].str), (yyvsp[-1].expr), 0, 0, line); }
#line 1199 "q_assembly/parser/parser.y.c"
    break;

  case 6: /* decl: TOKEN_LCRBR registers TOKEN_RCRBR circuit  */
#line 94 "q_assembly/parser/parser.y"
                                { (yyval.decl) = decl_create(0, (yyvsp[-2].expr), (yyvsp[0].expr), 0, line); }
#line 1205 "q_assembly/parser/parser.y.c"
    break;

  case 7: /* decl: TOKEN_LOAD TOKEN_LPAREN string TOKEN_RPAREN  */
#line 96 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.decl) = decl_create(0, 0, 0, 0, line);
                                        (yyval.decl)->file_name = (yyvsp[-1].str); 
                                }
#line 1214 "q_assembly/parser/parser.y.c"
    break;

  case 8: /* name: TOKEN_IDENT  */
#line 103 "q_assembly/parser/parser.y"
                { 
                        char *temp = (char *)smart_allocate(strlen(yytext), sizeof(char));
                        strcpy(temp, yytext);
                        (yyval.str) = temp; 
                }
#line 1224 "q_assembly/parser/parser.y.c"
    break;

  case 9: /* expr: algebra  */
#line 110 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1230 "q_assembly/parser/parser.y.c"
    break;

  case 10: /* algebra: algebra TOKEN_PLUS term  */
#line 114 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_ADD, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1236 "q_assembly/parser/parser.y.c"
    break;

  case 11: /* algebra: algebra TOKEN_MINUS term  */
#line 116 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_SUB, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1242 "q_assembly/parser/parser.y.c"
    break;

  case 12: /* algebra: term  */
#line 117 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1248 "q_assembly/parser/parser.y.c"
    break;

  case 13: /* term: term TOKEN_MUL difactor  */
#line 121 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_MUL, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1254 "q_assembly/parser/parser.y.c"
    break;

  case 14: /* term: term TOKEN_DIV difactor  */
#line 123 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_DIV, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1260 "q_assembly/parser/parser.y.c"
    break;

  case 15: /* term: term TOKEN_MODULUS difactor  */
#line 125 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_MODULUS, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1266 "q_assembly/parser/parser.y.c"
    break;

  case 16: /* term: term TOKEN_TENSOR_PRODUCT difactor  */
#line 127 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_TENSOR_PRODUCT, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1272 "q_assembly/parser/parser.y.c"
    break;

  case 17: /* term: difactor  */
#line 128 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1278 "q_assembly/parser/parser.y.c"
    break;

  case 18: /* difactor: difactor TOKEN_POWER factor  */
#line 132 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_POWER, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1284 "q_assembly/parser/parser.y.c"
    break;

  case 19: /* difactor: difactor TOKEN_TENSOR_PRODUCT_N_TIMES factor  */
#line 134 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(
                                                EXPR_TENSOR_PRODUCT_N_TIMES, 
                                                (yyvsp[-2].expr), 
                                                (yyvsp[0].expr), 
                                                line
                                        ); 
                                }
#line 1297 "q_assembly/parser/parser.y.c"
    break;

  case 20: /* difactor: factor  */
#line 142 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1303 "q_assembly/parser/parser.y.c"
    break;

  case 21: /* factor: TOKEN_LPAREN name TOKEN_RPAREN  */
#line 146 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create_name((yyvsp[-1].str), line); }
#line 1309 "q_assembly/parser/parser.y.c"
    break;

  case 22: /* factor: TOKEN_MINUS factor  */
#line 147 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(EXPR_MUL, 
                                                expr_create_complex_literal(
                                                        complex_create(-1, 0), 
                                                        line
                                                ), 
                                                (yyvsp[0].expr), 
                                                line
                                        ); 
                                }
#line 1324 "q_assembly/parser/parser.y.c"
    break;

  case 23: /* factor: TOKEN_SQRT factor  */
#line 157 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_SQRT, 0, (yyvsp[0].expr), line); }
#line 1330 "q_assembly/parser/parser.y.c"
    break;

  case 24: /* factor: number  */
#line 158 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create_complex_literal((yyvsp[0].complex), line); }
#line 1336 "q_assembly/parser/parser.y.c"
    break;

  case 25: /* factor: TOKEN_SEPARATOR number TOKEN_GREATER  */
#line 160 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(
                                                EXPR_KET, 
                                                0, 
                                                expr_create_complex_literal((yyvsp[-1].complex), line), 
                                                line
                                        ); 
                                }
#line 1349 "q_assembly/parser/parser.y.c"
    break;

  case 26: /* factor: TOKEN_LESS number TOKEN_SEPARATOR  */
#line 169 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(
                                                EXPR_BRA, 
                                                expr_create_complex_literal((yyvsp[-1].complex), line), 
                                                0, 
                                                line
                                        ); 
                                }
#line 1362 "q_assembly/parser/parser.y.c"
    break;

  case 27: /* factor: TOKEN_LPAREN expr TOKEN_RPAREN  */
#line 178 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1368 "q_assembly/parser/parser.y.c"
    break;

  case 28: /* number: TOKEN_COMPLEX_LITERAL  */
#line 182 "q_assembly/parser/parser.y"
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
                        (yyval.complex) = result; 
                }
#line 1389 "q_assembly/parser/parser.y.c"
    break;

  case 29: /* fields: expr next_expr  */
#line 199 "q_assembly/parser/parser.y"
                                { 
                                        if((yyvsp[0].expr) == NULL) 
                                                (yyval.expr) = (yyvsp[-1].expr);
                                        else 
                                                (yyval.expr) = expr_create(EXPR_FIELD, (yyvsp[-1].expr), (yyvsp[0].expr), line); 
                                }
#line 1400 "q_assembly/parser/parser.y.c"
    break;

  case 30: /* fields: %empty  */
#line 205 "q_assembly/parser/parser.y"
                                { (yyval.expr) = 0; }
#line 1406 "q_assembly/parser/parser.y.c"
    break;

  case 31: /* next_expr: TOKEN_COMMA fields  */
#line 210 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1412 "q_assembly/parser/parser.y.c"
    break;

  case 32: /* next_expr: TOKEN_SEPARATOR fields  */
#line 212 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1418 "q_assembly/parser/parser.y.c"
    break;

  case 33: /* next_expr: %empty  */
#line 213 "q_assembly/parser/parser.y"
                                { (yyval.expr) = 0; }
#line 1424 "q_assembly/parser/parser.y.c"
    break;

  case 34: /* registers: reg registers  */
#line 217 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_REGISTER, (yyvsp[-1].expr), (yyvsp[0].expr), line); }
#line 1430 "q_assembly/parser/parser.y.c"
    break;

  case 35: /* registers: %empty  */
#line 218 "q_assembly/parser/parser.y"
                                { (yyval.expr) = 0; }
#line 1436 "q_assembly/parser/parser.y.c"
    break;

  case 36: /* reg: TOKEN_LCRBR fields TOKEN_RCRBR  */
#line 222 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1442 "q_assembly/parser/parser.y.c"
    break;

  case 37: /* circuit: TOKEN_NEXT c_step circuit  */
#line 226 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_CIRCUIT_STEP, (yyvsp[-1].expr), (yyvsp[0].expr), line); }
#line 1448 "q_assembly/parser/parser.y.c"
    break;

  case 38: /* circuit: %empty  */
#line 227 "q_assembly/parser/parser.y"
                                { (yyval.expr) = 0; }
#line 1454 "q_assembly/parser/parser.y.c"
    break;

  case 39: /* c_step: expr  */
#line 230 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_APPLY_GATE, (yyvsp[0].expr), 0, line); }
#line 1460 "q_assembly/parser/parser.y.c"
    break;

  case 40: /* c_step: expr subsystem concurrent_gate  */
#line 232 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(
                                                EXPR_AND, 
                                                expr_create(EXPR_APPLY_GATE, (yyvsp[-2].expr), (yyvsp[-1].expr), line), 
                                                (yyvsp[0].expr), 
                                                line
                                        ); 
                                }
#line 1473 "q_assembly/parser/parser.y.c"
    break;

  case 41: /* c_step: TOKEN_LESS  */
#line 240 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_MEASURE, 0, 0, line); }
#line 1479 "q_assembly/parser/parser.y.c"
    break;

  case 42: /* c_step: TOKEN_LESS subsystem concurrent_gate  */
#line 242 "q_assembly/parser/parser.y"
                                { 
                                        (yyval.expr) = expr_create(
                                                EXPR_AND, 
                                                expr_create(EXPR_MEASURE, 0, (yyvsp[-1].expr), line), 
                                                (yyvsp[0].expr), 
                                                line
                                        ); 
                                }
#line 1492 "q_assembly/parser/parser.y.c"
    break;

  case 43: /* subsystem: TOKEN_LSQBR expr TOKEN_RSQBR  */
#line 254 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1498 "q_assembly/parser/parser.y.c"
    break;

  case 44: /* subsystem: TOKEN_LSQBR range TOKEN_RSQBR  */
#line 256 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1504 "q_assembly/parser/parser.y.c"
    break;

  case 45: /* range: expr TOKEN_RANGE expr  */
#line 260 "q_assembly/parser/parser.y"
                                { (yyval.expr) = expr_create(EXPR_RANGE, (yyvsp[-2].expr), (yyvsp[0].expr), line); }
#line 1510 "q_assembly/parser/parser.y.c"
    break;

  case 46: /* concurrent_gate: TOKEN_AND c_step  */
#line 264 "q_assembly/parser/parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1516 "q_assembly/parser/parser.y.c"
    break;

  case 47: /* concurrent_gate: %empty  */
#line 265 "q_assembly/parser/parser.y"
                                { (yyval.expr) = 0; }
#line 1522 "q_assembly/parser/parser.y.c"
    break;

  case 48: /* string: TOKEN_STRING_LITERAL  */
#line 268 "q_assembly/parser/parser.y"
                                { 
                                        char *temp = (char *)
                                                smart_allocate(strlen(yytext), sizeof(char));
                                        strcpy(temp, yytext+1);
                                        temp[strlen(temp)-1] = '\0';
                                        (yyval.str) = temp; 
                                }
#line 1534 "q_assembly/parser/parser.y.c"
    break;


#line 1538 "q_assembly/parser/parser.y.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 276 "q_assembly/parser/parser.y"


void yyerror(char *s) {
    error_count++;
    fprintf(stderr, BLU "%s" RESET ": ", global_name_of_starting_file);
    fprintf(stderr, RED "Error" RESET \
        MAG" |%s|"RESET"->"YEL"|%s|"RESET" on line %d \n", s, yytext, line);
}
