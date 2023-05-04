/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "ExprEval.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOMngr.h"
#include "SymTab.h"
#include "Semantics.h"
#include "CodeGen.h"

extern int yylex();	/* The next token function. */
extern char *yytext;   /* The matched token text.  */
extern int yyleng;      /* The token text length.   */
extern int yyparse();
extern int yyerror(char *);
void dumpTable();

extern SymTab *table;

#line 85 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Ident = 258,
    IntLit = 259,
    Int = 260,
    Void = 261,
    Boolean = 262,
    Write = 263,
    WriteLine = 264,
    WriteSpaces = 265,
    Read = 266,
    IF = 267,
    ELSE = 268,
    WHILE = 269,
    FOR = 270,
    EQ = 271,
    LT = 272,
    LEQ = 273,
    GT = 274,
    GEQ = 275,
    NEQ = 276,
    AND = 277,
    OR = 278,
    True = 279,
    False = 280,
    RETURN = 281
  };
#endif
/* Tokens.  */
#define Ident 258
#define IntLit 259
#define Int 260
#define Void 261
#define Boolean 262
#define Write 263
#define WriteLine 264
#define WriteSpaces 265
#define Read 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define EQ 271
#define LT 272
#define LEQ 273
#define GT 274
#define GEQ 275
#define NEQ 276
#define AND 277
#define OR 278
#define True 279
#define False 280
#define RETURN 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "ExprEval.y" /* yacc.c:355  */

	int num;
	long val;
	char * string;
	struct ExprRes * ExprRes;
	struct InstrSeq * InstrSeq;
	struct BExprRes * BExprRes;
	struct BExprResList * BExprResList;
	struct IdentList * IdentList;
	struct varList * varList;
	struct ParamList * ParamList;

#line 190 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 207 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   325

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,    40,     2,     2,
      30,    31,    38,    37,    34,    36,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
       2,    42,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    92,    92,    93,    94,    95,    97,    97,    97,    99,
     101,   101,   101,   105,   105,   105,   106,   106,   106,   107,
     107,   107,   109,   115,   122,   123,   126,   130,   131,   132,
     133,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   149,   150,   151,   152,   155,   156,   157,
     158,   159,   160,   161,   162,   164,   165,   166,   166,   167,
     167,   177,   178,   183,   184,   195,   196,   207,   208,   217,
     228,   239,   250,   261,   272,   283,   284,   285,   288,   299,
     310,   311,   322,   333,   344,   345,   356,   357,   358,   368,
     376,   377,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   398,   405,   411,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,   441,   447,
     448,   449,   457,   465,   473
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Ident", "IntLit", "Int", "Void",
  "Boolean", "Write", "WriteLine", "WriteSpaces", "Read", "IF", "ELSE",
  "WHILE", "FOR", "EQ", "LT", "LEQ", "GT", "GEQ", "NEQ", "AND", "OR",
  "True", "False", "RETURN", "';'", "'['", "']'", "'('", "')'", "'{'",
  "'}'", "','", "'!'", "'-'", "'+'", "'*'", "'/'", "'%'", "'^'", "'='",
  "$accept", "Prog", "Declarations", "Dec", "$@1", "$@2", "$@3", "$@4",
  "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "Stmt", "StmtSeq",
  "BExprList", "ReadList", "ParamList", "LocalList", "ArgList", "BEList",
  "RList", "PList", "LList", "@11", "@12", "AList", "ArgBExpr", "ArgOExpr",
  "ArgAExpr", "ArgRExpr", "ArgExpr", "ArgTerm", "ArgFactor", "ArgNum",
  "IfStmt", "SetStmt", "ESetStmt", "BExpr", "OExpr", "AExpr", "RExpr",
  "Expr", "Term", "Factor", "Num", "Id", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    59,    91,    93,
      40,    41,   123,   125,    44,    33,    45,    43,    42,    47,
      37,    94,    61
};
# endif

#define YYPACT_NINF -212

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-212)))

#define YYTABLE_NINF -20

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     151,     4,     4,     4,    15,   129,   151,  -212,    24,  -212,
      28,  -212,    12,    70,    51,    71,    81,   100,   147,    13,
     129,  -212,   133,  -212,    58,  -212,  -212,   122,   177,   191,
    -212,   198,   197,    49,  -212,    72,     4,    49,    49,     4,
    -212,  -212,  -212,  -212,    49,    49,    72,   202,   207,   209,
    -212,    10,   149,  -212,   193,    -6,  -212,     2,    72,    91,
      49,   228,   142,   142,   231,   142,   205,  -212,   203,    92,
     208,  -212,    65,   212,   213,    49,    29,   214,  -212,  -212,
    -212,    49,    49,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    91,   216,   129,    41,
    -212,  -212,  -212,    91,    91,   106,   220,  -212,   204,   232,
     234,  -212,   165,   174,  -212,   217,   146,   227,  -212,     4,
       4,   226,  -212,   233,  -212,   235,   238,    49,   240,   242,
      72,     4,   230,   239,   243,  -212,   209,  -212,    -4,    -4,
      -4,    -4,    -4,    -4,   149,   149,  -212,  -212,  -212,  -212,
      53,   241,    49,   244,   236,   245,  -212,  -212,   246,    91,
      91,    91,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,    72,    91,  -212,   250,    84,   120,
     248,   249,   253,   251,  -212,  -212,  -212,  -212,    77,  -212,
     129,   129,     4,  -212,  -212,   254,  -212,    49,  -212,  -212,
    -212,   234,  -212,    98,    98,    98,    98,    98,    98,   174,
     174,  -212,  -212,  -212,  -212,    88,   255,   247,   258,   142,
     259,   142,   210,   210,   257,   210,   256,   260,   261,   264,
      38,   265,   262,  -212,  -212,  -212,   266,  -212,   267,  -212,
       4,     4,  -212,  -212,  -212,  -212,  -212,     4,  -212,  -212,
     270,    72,    49,   129,  -212,   142,   142,   172,   192,   129,
     129,   129,  -212,   129,   116,  -212,   263,  -212,  -212,   210,
     271,   210,   287,   272,   273,   274,   275,   268,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,    49,   269,   280,
    -212,   276,   277,   210,   210,  -212,  -212
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,    25,     4,   134,     6,    13,
      10,     1,     0,     0,     0,     0,     0,     0,     0,     0,
      25,     2,    93,    99,     0,     3,     5,     0,     0,     0,
       9,     0,     0,    32,    27,     0,    34,     0,     0,     0,
     130,   117,   118,    23,     0,     0,     0,     0,   104,   106,
     108,   116,   121,   125,   127,   132,    24,     0,     0,    40,
       0,     0,    36,    36,     0,    36,     0,    31,    41,     0,
       0,    33,    43,     0,     0,     0,     0,     0,   109,   129,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,     0,    25,     0,
      90,    76,    77,     0,     0,     0,     0,    39,    61,    63,
      65,    67,    75,    80,    84,    86,    92,     0,     7,     0,
       0,     0,    35,     0,    11,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   105,   107,   110,   111,
     112,   113,   114,   115,   119,   120,   122,   123,   124,   126,
       0,     0,     0,     0,     0,     0,    68,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,   100,     0,    47,    48,
       0,     0,     0,     0,    29,    42,    28,    30,     0,    45,
      25,    25,     0,   133,   131,     0,    96,     0,    87,    26,
      62,    64,    66,    69,    70,    71,    72,    73,    74,    78,
      79,    81,    82,    83,    85,     0,     0,     0,     0,     0,
       0,     0,    38,    38,     0,    38,    44,     0,     0,     0,
       0,     0,     0,    91,    89,     8,    49,    51,    50,    52,
       0,     0,    17,    37,    14,    12,    20,     0,    94,    97,
       0,     0,     0,    25,   101,     0,     0,     0,     0,    25,
      25,    25,    46,    25,     0,   102,     0,    53,    54,    38,
       0,    38,     0,     0,     0,     0,     0,     0,    95,    55,
      57,    56,    59,    18,    15,    21,    98,     0,     0,     0,
     103,     0,     0,    38,    38,    58,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -212,  -212,   286,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,   -11,  -212,  -212,   153,  -202,
     -92,   184,  -125,  -211,  -212,  -212,  -212,   140,   211,  -212,
     152,   -93,    31,    54,    33,   215,  -212,   278,  -212,   -19,
    -212,   237,   -32,   -23,   135,   117,   279,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    27,   177,    31,   182,    29,   260,
      28,   259,    32,   261,    20,    21,    66,    70,   121,   242,
     106,    67,    71,   122,   243,   288,   289,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    22,    23,   229,    68,
      48,    49,    50,    51,    52,    53,    54,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,     8,     9,    10,   151,    24,   189,     7,   237,    56,
     239,   156,    69,    78,    97,    11,     7,    40,    73,    74,
      24,   244,    95,   246,    96,    77,    83,    84,    85,    86,
      87,    88,    89,    90,    98,    99,    72,    41,    42,    76,
      43,   117,    33,    44,   267,   268,    89,    90,    45,    46,
     137,    26,     7,    40,   -16,    30,   134,    58,   -19,   116,
     138,   139,   140,   141,   142,   143,   251,   279,   202,   281,
     154,    60,   150,    41,    42,     7,    40,    89,    90,    44,
     252,    35,   193,   216,    45,    46,    58,   153,    59,    89,
      90,   295,   296,   130,     7,   100,   116,    34,    24,   131,
      60,    36,    44,   116,   116,   116,   226,   188,    46,     7,
     100,    37,   218,    89,    90,   101,   102,   233,   219,   178,
     179,   103,   262,   128,    89,    90,   104,   105,    89,    90,
      38,    72,     7,   195,   168,   169,   103,    12,    13,    14,
      15,    16,   105,    17,    18,   277,    57,   119,   220,   120,
      61,   215,    89,    90,   221,    19,     1,     2,     3,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   174,   116,   175,    39,   232,   227,
     228,   162,   163,   164,   165,   166,   167,    91,    92,    93,
      24,    24,   230,   203,   204,   205,   206,   207,   208,   269,
     270,   168,   169,   211,   212,   213,   214,    62,   146,   147,
     148,   149,   170,   171,   172,   240,   123,   241,   125,   271,
     272,    63,   209,   210,   144,   145,    64,    65,   264,    80,
      81,    82,   118,   265,    94,   124,   126,   127,   159,   129,
     257,   258,   266,   132,   133,   135,   152,    72,   273,   274,
     275,   158,   276,    24,   176,   160,   161,   180,   173,    24,
      24,    24,   190,    24,   181,   184,   183,   186,   290,   187,
     192,   191,   194,   199,   235,   280,   198,   196,   197,   217,
     222,   223,   224,   225,   245,   231,   234,   236,   238,   254,
     247,   282,    25,   248,   249,   250,   278,   253,   291,   200,
     255,   256,   263,   293,   294,   283,   284,   285,   286,   292,
     287,   185,   201,     0,   155,     0,     0,    75,   136,     0,
     157,     0,     0,     0,     0,    79
};

static const yytype_int16 yycheck[] =
{
      19,     1,     2,     3,    96,     5,   131,     3,   219,    20,
     221,   104,    35,    45,    12,     0,     3,     4,    37,    38,
      20,   223,    28,   225,    30,    44,    16,    17,    18,    19,
      20,    21,    36,    37,    32,    58,    36,    24,    25,    39,
      27,    60,    30,    30,   255,   256,    36,    37,    35,    36,
      82,    27,     3,     4,    30,    27,    75,    28,    30,    59,
      83,    84,    85,    86,    87,    88,    28,   269,   161,   271,
      29,    42,    95,    24,    25,     3,     4,    36,    37,    30,
      42,    30,    29,   175,    35,    36,    28,    98,    30,    36,
      37,   293,   294,    28,     3,     4,    96,    27,    98,    34,
      42,    30,    30,   103,   104,   105,    29,   130,    36,     3,
       4,    30,    28,    36,    37,    24,    25,    29,    34,   119,
     120,    30,   247,    31,    36,    37,    35,    36,    36,    37,
      30,   131,     3,   152,    36,    37,    30,     8,     9,    10,
      11,    12,    36,    14,    15,    29,    13,     5,    28,     7,
      28,   174,    36,    37,    34,    26,     5,     6,     7,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,    28,   175,    30,    30,   197,   190,
     191,    16,    17,    18,    19,    20,    21,    38,    39,    40,
     190,   191,   192,   162,   163,   164,   165,   166,   167,    27,
      28,    36,    37,   170,   171,   172,   173,    30,    91,    92,
      93,    94,    38,    39,    40,     5,    63,     7,    65,    27,
      28,    30,   168,   169,    89,    90,    28,    30,   251,    27,
      23,    22,     4,   252,    41,     4,    31,    34,    34,    31,
     240,   241,   253,    31,    31,    31,    30,   247,   259,   260,
     261,    31,   263,   253,    27,    23,    22,    31,    41,   259,
     260,   261,    32,   263,    31,    27,    31,    27,   287,    27,
      27,    32,    31,    27,    27,     4,    31,    33,    42,    29,
      32,    32,    29,    32,    27,    31,    31,    29,    29,    27,
      34,     4,     6,    33,    33,    31,    33,    32,    29,   159,
      34,    34,    32,    27,    27,    33,    33,    33,    33,    29,
      42,   127,   160,    -1,   103,    -1,    -1,    39,    81,    -1,
     105,    -1,    -1,    -1,    -1,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,    44,    45,    46,     3,    90,    90,
      90,     0,     8,     9,    10,    11,    12,    14,    15,    26,
      57,    58,    79,    80,    90,    45,    27,    47,    53,    51,
      27,    49,    55,    30,    27,    30,    30,    30,    30,    30,
       4,    24,    25,    27,    30,    35,    36,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    58,    13,    28,    30,
      42,    28,    30,    30,    28,    30,    59,    64,    82,    86,
      60,    65,    90,    82,    82,    80,    90,    82,    85,    89,
      27,    23,    22,    16,    17,    18,    19,    20,    21,    36,
      37,    38,    39,    40,    41,    28,    30,    12,    32,    86,
       4,    24,    25,    30,    35,    36,    63,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    90,    82,     4,     5,
       7,    61,    66,    61,     4,    61,    31,    34,    31,    31,
      28,    34,    31,    31,    82,    31,    84,    85,    86,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    88,    88,
      86,    63,    30,    58,    29,    71,    74,    78,    31,    34,
      23,    22,    16,    17,    18,    19,    20,    21,    36,    37,
      38,    39,    40,    41,    28,    30,    27,    48,    90,    90,
      31,    31,    50,    31,    27,    64,    27,    27,    86,    65,
      32,    32,    27,    29,    31,    82,    33,    42,    31,    27,
      70,    73,    74,    75,    75,    75,    75,    75,    75,    76,
      76,    77,    77,    77,    77,    86,    63,    29,    28,    34,
      28,    34,    32,    32,    29,    32,    29,    58,    58,    81,
      90,    31,    82,    29,    31,    27,    29,    66,    29,    66,
       5,     7,    62,    67,    62,    27,    62,    34,    33,    33,
      31,    28,    42,    32,    27,    34,    34,    90,    90,    54,
      52,    56,    65,    32,    86,    82,    58,    66,    66,    27,
      28,    27,    28,    58,    58,    58,    58,    29,    33,    62,
       4,    62,     4,    33,    33,    33,    33,    42,    68,    69,
      82,    29,    29,    27,    27,    62,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    47,    48,    46,    46,
      49,    50,    46,    51,    52,    46,    53,    54,    46,    55,
      56,    46,    57,    57,    58,    58,    57,    57,    57,    57,
      57,    59,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    67,    69,
      67,    70,    70,    71,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    75,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    78,
      78,    78,    78,    57,    79,    79,    57,    57,    57,    57,
      80,    80,    81,    81,    82,    83,    83,    84,    84,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      86,    86,    87,    87,    87,    87,    88,    88,    89,    89,
      89,    89,    89,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     3,     0,     0,     8,     3,
       0,     0,     8,     0,     0,    11,     0,     0,    11,     0,
       0,    11,     3,     2,     2,     0,     5,     2,     5,     5,
       5,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     3,     1,     4,     3,     6,     2,     2,     4,
       4,     4,     4,     6,     6,     4,     4,     0,     8,     0,
       8,     1,     3,     1,     3,     1,     3,     1,     2,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     3,     3,
       1,     3,     3,     3,     1,     3,     1,     3,     2,     4,
       1,     4,     1,     1,     7,     9,     5,     7,    10,     1,
       4,     7,     3,     6,     1,     3,     1,     3,     1,     2,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     3,     2,
       1,     4,     1,     4,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 92 "ExprEval.y" /* yacc.c:1646  */
    {Finish((yyvsp[0].InstrSeq));}
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 93 "ExprEval.y" /* yacc.c:1646  */
    {}
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 94 "ExprEval.y" /* yacc.c:1646  */
    {}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 95 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[-1].string)); enterSize(0, 0);}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 97 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[0].string));}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 97 "ExprEval.y" /* yacc.c:1646  */
    {enterSize(atoi(yytext), 1);}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 97 "ExprEval.y" /* yacc.c:1646  */
    {}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 99 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[-1].string)); enterSize(1, 0);}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 101 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[0].string));}
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 101 "ExprEval.y" /* yacc.c:1646  */
    {enterSize(atoi(yytext), 2);}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 101 "ExprEval.y" /* yacc.c:1646  */
    {}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 105 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[0].string)); makeFunction(0);}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 105 "ExprEval.y" /* yacc.c:1646  */
    {makeTable((yyvsp[-3].varList), (yyvsp[0].varList), (yyvsp[-6].string));}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 105 "ExprEval.y" /* yacc.c:1646  */
    {addBody((yyvsp[-9].string), (yyvsp[-1].InstrSeq));}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 106 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[0].string)); makeFunction(1);}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 106 "ExprEval.y" /* yacc.c:1646  */
    {makeTable((yyvsp[-3].varList), (yyvsp[0].varList), (yyvsp[-6].string));}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 106 "ExprEval.y" /* yacc.c:1646  */
    {addBody((yyvsp[-9].string), (yyvsp[-1].InstrSeq));}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 107 "ExprEval.y" /* yacc.c:1646  */
    {enterName(table, (yyvsp[0].string)); makeFunction(2);}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 107 "ExprEval.y" /* yacc.c:1646  */
    {makeTable((yyvsp[-3].varList), (yyvsp[0].varList), (yyvsp[-6].string));}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 107 "ExprEval.y" /* yacc.c:1646  */
    {addBody((yyvsp[-9].string), (yyvsp[-1].InstrSeq));}
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 109 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[-1].BExprRes)->Expr && !((yyvsp[-1].BExprRes)->Expr->isBoolean)){
																				(yyval.InstrSeq) = doIntReturn((yyvsp[-1].BExprRes)->Expr);
																			 }else{
																				(yyval.InstrSeq) = doBoolReturn((yyvsp[-1].BExprRes));
																			 }
																			}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 115 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doVoidReturn();}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 122 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = AppendSeq((yyvsp[-1].InstrSeq), (yyvsp[0].InstrSeq));}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 123 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = NULL;}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 126 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = getVoidFunction((yyvsp[-4].string), (yyvsp[-2].ParamList));}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 130 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doPrintLine();}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 131 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doPrintSpaces((yyvsp[-2].ExprRes));}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 132 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doPrint((yyvsp[-2].BExprResList));}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 133 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doRead((yyvsp[-2].IdentList));}
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 136 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprResList) = (yyvsp[0].BExprResList);}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 137 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprResList) = NULL;}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 138 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = (yyvsp[0].IdentList);}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 139 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = NULL;}
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 140 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = (yyvsp[0].varList);}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 141 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = NULL;}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 142 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = (yyvsp[0].varList);}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 143 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = NULL;}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 144 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 145 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = NULL;}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 146 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprResList) = AppendExpr((yyvsp[0].BExprRes), NULL);}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 147 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprResList) = AppendExpr((yyvsp[-2].BExprRes), (yyvsp[0].BExprResList));}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 149 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = AppendRead((yyvsp[0].string), NULL, NULL);}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 150 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = AppendRead((yyvsp[-3].string), (yyvsp[-1].ExprRes), NULL);}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 151 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = AppendRead((yyvsp[-2].string), NULL, (yyvsp[0].IdentList));}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 152 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.IdentList) = AppendRead((yyvsp[-5].string), (yyvsp[-3].ExprRes), (yyvsp[0].IdentList));}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 155 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[0].string), 0, NULL, 0, 0);}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 156 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[0].string), 1, NULL, 0, 1);}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 157 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), -1, NULL, 0, 0);}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 158 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), -2, NULL, 0, 1);}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 159 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), 0, (yyvsp[0].varList), 0, 0);}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 160 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), 1, (yyvsp[0].varList), 0, 1);}
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 161 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-4].string), -1, (yyvsp[0].varList), 0, 0);}
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 162 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-4].string), -2, (yyvsp[0].varList), 0, 1);}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 164 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), 0, (yyvsp[0].varList), 0, 0);}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 165 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-2].string), 1, (yyvsp[0].varList), 0, 1);}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 166 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.num) = atoi(yytext);}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 166 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-6].string), (yyvsp[-3].num), (yyvsp[0].varList), 1, 0);}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 167 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.num) = atoi(yytext);}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 167 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.varList) = AppendVar((yyvsp[-6].string), (yyvsp[-3].num), (yyvsp[0].varList), 1, 1);}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 177 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 178 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList); (yyval.ParamList)->Next = (yyvsp[0].ParamList);}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 183 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 184 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->boolean = doImmBExpr((yyval.ParamList)->value, 1);
																			 }
																			 if((yyvsp[0].ParamList)->value){
																				(yyvsp[0].ParamList)->boolean = doImmBExpr((yyvsp[0].ParamList)->value, 1);
																			 }
																			 (yyval.ParamList)->boolean = doOr((yyval.ParamList)->boolean, (yyvsp[0].ParamList)->boolean);
																			 (yyval.ParamList)->value = NULL;
																			 (yyval.ParamList)->type = 1;
																			}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 195 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 196 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->boolean = doImmBExpr((yyval.ParamList)->value, 1);
																			 }
																			 if((yyvsp[0].ParamList)->value){
																				(yyvsp[0].ParamList)->boolean = doImmBExpr((yyvsp[0].ParamList)->value, 1);
																			 }
																			 (yyval.ParamList)->boolean = doAnd((yyval.ParamList)->boolean, (yyvsp[0].ParamList)->boolean);
																			 (yyval.ParamList)->value = NULL;
																			 (yyval.ParamList)->type = 1;
																			}
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 207 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 208 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->boolean = doNot(doImmBExpr((yyval.ParamList)->value, 1));
																			 }else{
																				(yyval.ParamList)->boolean = doNot((yyval.ParamList)->boolean);
																			 }
																			 (yyval.ParamList)->value = NULL;
																			 (yyval.ParamList)->type = 1;
																			}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 217 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "eq");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 228 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "lt");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 239 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "leq");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 250 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "gt");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 261 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "geq");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 272 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyvsp[-2].ParamList)->value && (yyvsp[0].ParamList)->value){
																				(yyval.ParamList)->boolean = doBExpr((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "neq");
																				(yyval.ParamList)->value = NULL;
																				(yyval.ParamList)->type = 1;
																			 }else{
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Relational expression is missing value(s).");
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 283 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 284 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(NULL, doImmBExpr(doIntLit("1"), 1), 1);}
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 285 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(NULL, doImmBExpr(doIntLit("0"), 1), 1);}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 288 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doOp((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "sub");
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Subtraction with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 299 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doOp((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "add");
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Addition with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 310 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 311 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doOp((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "mul");
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Multiplication with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 322 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doDivOrMod((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "division");
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Division with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 333 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doDivOrMod((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value, "mod");
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Modulus with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 344 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 345 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-2].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doPow((yyvsp[-2].ParamList)->value, (yyvsp[0].ParamList)->value);
																			 }
																			 if((yyvsp[-2].ParamList)->type !=0 || (yyvsp[0].ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Exponentiation with a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			 free((yyvsp[0].ParamList));
																			}
#line 2138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 356 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);}
#line 2144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 357 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[-1].ParamList);}
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 358 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = (yyvsp[0].ParamList);
																			 if((yyval.ParamList)->value){
																				(yyval.ParamList)->value = doNeg((yyvsp[0].ParamList)->value);
																			 }
																			 if((yyval.ParamList)->type != 0){
																				writeIndicator(getCurrentColumnNum());
																				writeMessage("Negation on a non-integer.");
																				(yyval.ParamList)->type = 0;
																			 }
																			}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 368 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(getIntFunction((yyvsp[-3].string), (yyvsp[-1].ParamList)), NULL, 0);
																			 if(!findName(table, (yyvsp[-3].string)) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
																			 }else if(((struct Attribute *) getCurrentAttr(table))->functType < 2){
																				(yyval.ParamList)->type = 0;
																			 }else{
																				(yyval.ParamList)->type = 1;
																			 }
																			}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 376 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(doIntLit(yytext), NULL, 0);}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 377 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(doRval((yyvsp[-3].string), (yyvsp[-1].ExprRes), getType((yyvsp[-3].string))), NULL, 0);
																			 if(getType((yyvsp[-3].string)) == -1){
																				(yyval.ParamList)->type = 0;
																			 }else if(getType((yyvsp[-3].string)) == -2){
																				(yyval.ParamList)->type = 1;
																			 }
																			}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 384 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ParamList) = newPList(getArg((yyvsp[0].string)), NULL, getType((yyvsp[0].string)));}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 385 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = finishIf((yyvsp[0].BExprRes));}
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 386 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doIf((yyvsp[-4].BExprRes), (yyvsp[-1].InstrSeq));}
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 387 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doElseIf((yyvsp[-8].BExprRes), (yyvsp[-4].BExprRes), (yyvsp[-1].InstrSeq));}
#line 2220 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 388 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doElse((yyvsp[-4].BExprRes), (yyvsp[-1].InstrSeq));}
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 389 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doWhile((yyvsp[-4].BExprRes), (yyvsp[-1].InstrSeq));}
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 390 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = doFor((yyvsp[-7].InstrSeq), (yyvsp[-6].BExprRes), (yyvsp[-4].InstrSeq), (yyvsp[-1].InstrSeq));}
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 391 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.InstrSeq) = (yyvsp[0].InstrSeq);}
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 392 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[-1].BExprRes)->Expr){
																				(yyval.InstrSeq) = doAssign((yyvsp[-3].string), (yyvsp[-1].BExprRes)->Expr, NULL, 0);
																			 }else{
																				(yyval.InstrSeq) = doAssign((yyvsp[-3].string), getBooleanVal((yyvsp[-1].BExprRes)), NULL, 1);
																			 }
																			}
#line 2255 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 398 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[-1].BExprRes)->Expr){
																				(yyval.InstrSeq) = doAssign((yyvsp[-6].string), (yyvsp[-1].BExprRes)->Expr, (yyvsp[-4].ExprRes), -1);
																			 }else{
																				(yyval.InstrSeq) = doAssign((yyvsp[-6].string), getBooleanVal((yyvsp[-1].BExprRes)), (yyvsp[-4].ExprRes), -2);
																			 }
																			}
#line 2266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 405 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[0].BExprRes)->Expr){
																				(yyval.InstrSeq) = doAssign((yyvsp[-2].string), (yyvsp[0].BExprRes)->Expr, NULL, 0);
																			 }else{
																				(yyval.InstrSeq) = doAssign((yyvsp[-2].string), getBooleanVal((yyvsp[0].BExprRes)), NULL, 1);
																			 }
																			}
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 411 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[0].BExprRes)->Expr){
																				(yyval.InstrSeq) = doAssign((yyvsp[-5].string), (yyvsp[0].BExprRes)->Expr, (yyvsp[-3].ExprRes), -1);
																			 }else{
																				(yyval.InstrSeq) = doAssign((yyvsp[-5].string), getBooleanVal((yyvsp[0].BExprRes)), (yyvsp[-3].ExprRes), -2);
																			 }
																			}
#line 2288 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 417 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = (yyvsp[0].BExprRes);}
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 418 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doOr((yyvsp[-2].BExprRes), (yyvsp[0].BExprRes));}
#line 2300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 419 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = (yyvsp[0].BExprRes);}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 420 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doAnd((yyvsp[-2].BExprRes), (yyvsp[0].BExprRes));}
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 421 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = (yyvsp[0].BExprRes);}
#line 2318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 422 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doNot((yyvsp[0].BExprRes));}
#line 2324 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 423 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "eq");}
#line 2330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 424 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "lt");}
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 425 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "leq");}
#line 2342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 426 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "gt");}
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 427 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "geq");}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 428 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doBExpr((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "neq");}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 429 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doImmBExpr((yyvsp[0].ExprRes), 0);}
#line 2366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 430 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doImmBExpr(doIntLit("1"), 1);}
#line 2372 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 431 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.BExprRes) = doImmBExpr(doIntLit("0"), 1);}
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 432 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doOp((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "sub");}
#line 2384 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 433 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doOp((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "add");}
#line 2390 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 434 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = (yyvsp[0].ExprRes);}
#line 2396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 435 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doOp((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "mul");}
#line 2402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 436 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doDivOrMod((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "divide");}
#line 2408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 437 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doDivOrMod((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes), "mod");}
#line 2414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 438 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = (yyvsp[0].ExprRes);}
#line 2420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 439 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doPow((yyvsp[-2].ExprRes), (yyvsp[0].ExprRes));}
#line 2426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 440 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = (yyvsp[0].ExprRes);}
#line 2432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 441 "ExprEval.y" /* yacc.c:1646  */
    {if((yyvsp[-1].BExprRes)->Expr){
																				(yyval.ExprRes) = (yyvsp[-1].BExprRes)->Expr;
																			 }else{
																				(yyval.ExprRes) = getBooleanVal((yyvsp[-1].BExprRes));
																			 }
																			}
#line 2443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 447 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doNeg((yyvsp[0].ExprRes));}
#line 2449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 448 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = doIntLit(yytext);}
#line 2455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 449 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.ExprRes) = getIntFunction((yyvsp[-3].string), (yyvsp[-1].ParamList));
																			 if(!findName(table, (yyvsp[-3].string)) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
																			 }else if(((struct Attribute *) getCurrentAttr(table))->functType < 2){
																				(yyval.ExprRes)->isBoolean = 0;
																			 }else{
																				(yyval.ExprRes)->isBoolean = 1;
																			 }
																			}
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 457 "ExprEval.y" /* yacc.c:1646  */
    {if(getType((yyvsp[0].string)) != 1){
																				(yyval.ExprRes) = doRval((yyvsp[0].string), NULL, 0);
																				(yyval.ExprRes)->isBoolean = 0;
																			 }else{
																				(yyval.ExprRes) = doRval((yyvsp[0].string), NULL, 1);
																				(yyval.ExprRes)->isBoolean = 1;
																			 }
																			}
#line 2481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 465 "ExprEval.y" /* yacc.c:1646  */
    {if(getType((yyvsp[-3].string)) != -2){
																				(yyval.ExprRes) = doRval((yyvsp[-3].string), (yyvsp[-1].ExprRes), -1);
																				(yyval.ExprRes)->isBoolean = 0;
																			 }else{
																				(yyval.ExprRes) = doRval((yyvsp[-3].string), (yyvsp[-1].ExprRes), -2);
																				(yyval.ExprRes)->isBoolean = 1;
																			 }
																			}
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 473 "ExprEval.y" /* yacc.c:1646  */
    {(yyval.string) = strdup(yytext);}
#line 2500 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2504 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 474 "ExprEval.y" /* yacc.c:1906  */


int yyerror(char *s){
	writeIndicator(getCurrentColumnNum());
	writeMessage("Illegal Character in YACC.");
	return 1;
}
