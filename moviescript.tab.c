/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OPENING_CREDITS = 258,
     FINAL_CREDITS = 259,
     SCREENPLAY = 260,
     ENDSCREENPLAY = 261,
     CHARACTER = 262,
     SCENE = 263,
     DIALOGUE = 264,
     RATING = 265,
     BUDGET = 266,
     GENRE = 267,
     STATUS = 268,
     WHOLE = 269,
     SIGNAL = 270,
     SCENE_IF = 271,
     OTHERWISE = 272,
     FRAME = 273,
     ENDFRAME = 274,
     FOR_EACH_SCENE = 275,
     IN = 276,
     REEL = 277,
     ENDREEL = 278,
     WHILE = 279,
     TAKE = 280,
     ENDTAKE = 281,
     GENRE_COLLECTION = 282,
     ADD_TO = 283,
     FUNCTION = 284,
     RETURNS = 285,
     RETURN = 286,
     ENDFUNCTION = 287,
     AWARD = 288,
     REVIEW = 289,
     ANALYZE = 290,
     PRINT = 291,
     BUILD_SUSPENSE = 292,
     ENTER_STAGE = 293,
     SUCCESS = 294,
     FAILURE = 295,
     BLOCKBUSTER = 296,
     FLOP = 297,
     AVERAGE = 298,
     RISING = 299,
     ASSIGN = 300,
     PLUS = 301,
     MINUS = 302,
     STAR = 303,
     SLASH = 304,
     GREATER_THAN = 305,
     GREATER_EQUAL = 306,
     LESS_THAN = 307,
     LESS_EQUAL = 308,
     IS = 309,
     IS_NOT = 310,
     IDENTIFIER = 311,
     NUMBER = 312,
     STRING = 313,
     LPAREN = 314,
     RPAREN = 315,
     LBRACE = 316,
     RBRACE = 317,
     COMMA = 318
   };
#endif
/* Tokens.  */
#define OPENING_CREDITS 258
#define FINAL_CREDITS 259
#define SCREENPLAY 260
#define ENDSCREENPLAY 261
#define CHARACTER 262
#define SCENE 263
#define DIALOGUE 264
#define RATING 265
#define BUDGET 266
#define GENRE 267
#define STATUS 268
#define WHOLE 269
#define SIGNAL 270
#define SCENE_IF 271
#define OTHERWISE 272
#define FRAME 273
#define ENDFRAME 274
#define FOR_EACH_SCENE 275
#define IN 276
#define REEL 277
#define ENDREEL 278
#define WHILE 279
#define TAKE 280
#define ENDTAKE 281
#define GENRE_COLLECTION 282
#define ADD_TO 283
#define FUNCTION 284
#define RETURNS 285
#define RETURN 286
#define ENDFUNCTION 287
#define AWARD 288
#define REVIEW 289
#define ANALYZE 290
#define PRINT 291
#define BUILD_SUSPENSE 292
#define ENTER_STAGE 293
#define SUCCESS 294
#define FAILURE 295
#define BLOCKBUSTER 296
#define FLOP 297
#define AVERAGE 298
#define RISING 299
#define ASSIGN 300
#define PLUS 301
#define MINUS 302
#define STAR 303
#define SLASH 304
#define GREATER_THAN 305
#define GREATER_EQUAL 306
#define LESS_THAN 307
#define LESS_EQUAL 308
#define IS 309
#define IS_NOT 310
#define IDENTIFIER 311
#define NUMBER 312
#define STRING 313
#define LPAREN 314
#define RPAREN 315
#define LBRACE 316
#define RBRACE 317
#define COMMA 318




/* Copy the first part of user declarations.  */
#line 1 "moviescript.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* root = NULL;
extern int line;

void yyerror(const char *s);
int yylex(void);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "moviescript.y"
{
    ASTNode* node;
    char* str;
}
/* Line 193 of yacc.c.  */
#line 240 "moviescript.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 253 "moviescript.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  135

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    16,    18,    20,    22,
      24,    26,    28,    30,    32,    44,    48,    50,    51,    54,
      56,    58,    60,    62,    64,    66,    68,    70,    72,    75,
      78,    81,    84,    87,    92,    97,   101,   105,   109,   113,
     117,   119,   121,   123,   125,   130,   134,   138,   140,   141,
     153,   157,   160,   168,   175,   182,   186,   188,   192,   195,
     198,   201,   204,   206,   208
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,     3,    66,     4,    -1,     5,    67,     6,
      -1,    67,    68,    -1,    68,    -1,    73,    -1,    74,    -1,
      78,    -1,    80,    -1,    81,    -1,    69,    -1,    84,    -1,
      83,    -1,    29,    56,    59,    70,    60,    30,    72,    18,
      67,    19,    32,    -1,    70,    63,    71,    -1,    71,    -1,
      -1,    72,    56,    -1,     7,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,
      15,    -1,     7,    56,    -1,     8,    56,    -1,     9,    56,
      -1,    10,    56,    -1,    11,    56,    -1,    10,    56,    45,
      75,    -1,    11,    56,    45,    75,    -1,    56,    45,    75,
      -1,    75,    46,    75,    -1,    75,    47,    75,    -1,    75,
      48,    75,    -1,    75,    49,    75,    -1,    76,    -1,    57,
      -1,    58,    -1,    56,    -1,    56,    59,    77,    60,    -1,
      59,    75,    60,    -1,    77,    63,    75,    -1,    75,    -1,
      -1,    16,    59,    79,    60,    18,    67,    19,    17,    18,
      67,    19,    -1,    75,    50,    75,    -1,    56,    44,    -1,
      24,    59,    79,    60,    25,    67,    26,    -1,    20,    21,
      56,    22,    67,    23,    -1,    27,    56,    45,    61,    82,
      62,    -1,    28,    56,    58,    -1,    58,    -1,    82,    63,
      58,    -1,    36,    75,    -1,    33,    58,    -1,    34,    58,
      -1,    35,    56,    -1,    37,    -1,    38,    -1,    31,    75,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    58,    58,    67,    75,    82,    89,    90,    91,    92,
      93,    94,    95,    96,   100,   109,   114,   119,   125,   132,
     134,   136,   138,   140,   142,   144,   146,   148,   153,   157,
     161,   165,   169,   173,   178,   186,   197,   203,   209,   215,
     221,   228,   232,   236,   240,   245,   252,   257,   262,   268,
     278,   284,   292,   298,   306,   311,   318,   322,   331,   336,
     340,   344,   348,   352,   359
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OPENING_CREDITS", "FINAL_CREDITS",
  "SCREENPLAY", "ENDSCREENPLAY", "CHARACTER", "SCENE", "DIALOGUE",
  "RATING", "BUDGET", "GENRE", "STATUS", "WHOLE", "SIGNAL", "SCENE_IF",
  "OTHERWISE", "FRAME", "ENDFRAME", "FOR_EACH_SCENE", "IN", "REEL",
  "ENDREEL", "WHILE", "TAKE", "ENDTAKE", "GENRE_COLLECTION", "ADD_TO",
  "FUNCTION", "RETURNS", "RETURN", "ENDFUNCTION", "AWARD", "REVIEW",
  "ANALYZE", "PRINT", "BUILD_SUSPENSE", "ENTER_STAGE", "SUCCESS",
  "FAILURE", "BLOCKBUSTER", "FLOP", "AVERAGE", "RISING", "ASSIGN", "PLUS",
  "MINUS", "STAR", "SLASH", "GREATER_THAN", "GREATER_EQUAL", "LESS_THAN",
  "LESS_EQUAL", "IS", "IS_NOT", "IDENTIFIER", "NUMBER", "STRING", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "COMMA", "$accept", "program",
  "screenplay", "statements", "statement", "function_decl", "param_list",
  "param", "type_spec", "declaration", "assignment", "expression",
  "primary", "argument_list", "conditional", "condition", "loop",
  "collection", "string_list", "action", "return_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    70,    70,    70,    71,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    74,    75,    75,    75,    75,
      75,    76,    76,    76,    76,    76,    77,    77,    77,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    83,    83,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,    11,     3,     1,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     4,     4,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     4,     3,     3,     1,     0,    11,
       3,     2,     7,     6,     6,     3,     1,     3,     2,     2,
       2,     2,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,    63,     0,     0,     5,    11,     6,     7,
       8,     9,    10,    13,    12,     2,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     0,    43,    41,    42,
       0,    64,    40,    59,    60,    61,    58,     0,     3,     4,
       0,     0,    43,     0,     0,     0,     0,     0,    55,    17,
      48,     0,     0,     0,     0,     0,    35,    33,    34,    51,
       0,     0,     0,     0,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,     0,    16,     0,    47,     0,    45,
      36,    37,    38,    39,    50,     0,     0,     0,    56,     0,
       0,     0,    18,    44,     0,     0,    53,     0,    54,     0,
       0,    15,    46,     0,    52,    57,     0,     0,     0,     0,
       0,     0,     0,    49,    14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     4,    25,    26,    27,    94,    95,    96,    28,
      29,    63,    52,    98,    30,    64,    31,    32,   109,    33,
      34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
       1,    10,    17,   292,    22,   -81,   -13,    -6,    -5,    -4,
      -3,   -19,    34,     2,     4,     6,     7,   -35,    16,    18,
      19,   -35,   -81,   -81,    32,    93,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    33,
      35,   -28,    23,   -28,    37,    25,    26,    27,   -81,   -81,
     -35,   -11,   -81,   -81,   -81,   -81,   -11,   -35,   -81,   -81,
     -35,   -35,   -41,   -36,    24,    65,    28,    30,   -81,    58,
     -35,   -40,   -35,   -35,   -35,   -35,   -11,   -11,   -11,   -81,
     -35,    71,   292,    68,    36,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -44,   -81,    39,   -11,   -21,   -81,
      -2,    -2,   -81,   -81,   -11,   292,   127,   292,   -81,   -30,
      66,    58,   -81,   -81,   -35,   160,   -81,   193,   -81,    49,
      58,   -81,   -11,    80,   -81,   -81,    90,    92,   292,   292,
     226,   259,    79,   -81,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,   -80,   -25,   -81,   -81,     3,    -8,   -81,
     -81,   -16,   -81,   -81,   -81,    72,   -81,   -81,   -81,   -81,
     -81
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      59,    51,   106,    79,     1,    56,    72,    73,    74,    75,
      72,    73,    74,    75,    80,     3,   110,     5,    70,   111,
      99,    47,    48,    49,    50,   115,    35,   117,    62,    48,
      49,    50,   118,   119,    71,    72,    73,    74,    75,   113,
      41,    76,   114,    36,    77,    78,    74,    75,   130,   131,
      37,    38,    39,    40,    97,    42,   100,   101,   102,   103,
      44,    43,    45,    46,   104,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    53,    55,    54,    57,    60,    65,
      61,    59,    67,    68,    81,    69,    70,    82,    83,   105,
      59,    84,    59,   107,   108,   112,   120,   127,   122,    58,
       6,     7,     8,     9,    10,    59,    59,   125,   128,    11,
     129,   134,   126,    12,   121,    66,     0,    13,     0,     0,
      14,    15,    16,     0,    17,     0,    18,    19,    20,    21,
      22,    23,     0,     0,     6,     7,     8,     9,    10,     0,
       0,     0,     0,    11,     0,     0,     0,    12,     0,    24,
     116,    13,     0,     0,    14,    15,    16,     0,    17,     0,
      18,    19,    20,    21,    22,    23,     0,     6,     7,     8,
       9,    10,     0,     0,     0,     0,    11,     0,     0,   123,
      12,     0,     0,    24,    13,     0,     0,    14,    15,    16,
       0,    17,     0,    18,    19,    20,    21,    22,    23,     0,
       6,     7,     8,     9,    10,     0,     0,     0,     0,    11,
       0,     0,     0,    12,     0,     0,    24,    13,     0,   124,
      14,    15,    16,     0,    17,     0,    18,    19,    20,    21,
      22,    23,     0,     6,     7,     8,     9,    10,     0,     0,
       0,     0,    11,     0,     0,   132,    12,     0,     0,    24,
      13,     0,     0,    14,    15,    16,     0,    17,     0,    18,
      19,    20,    21,    22,    23,     0,     6,     7,     8,     9,
      10,     0,     0,     0,     0,    11,     0,     0,   133,    12,
       0,     0,    24,    13,     0,     0,    14,    15,    16,     0,
      17,     0,    18,    19,    20,    21,    22,    23,     0,     6,
       7,     8,     9,    10,     0,     0,     0,     0,    11,     0,
       0,     0,    12,     0,     0,    24,    13,     0,     0,    14,
      15,    16,     0,    17,     0,    18,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24
};

static const yytype_int16 yycheck[] =
{
      25,    17,    82,    44,     3,    21,    46,    47,    48,    49,
      46,    47,    48,    49,    50,     5,    60,     0,    59,    63,
      60,    56,    57,    58,    59,   105,     4,   107,    56,    57,
      58,    59,    62,    63,    50,    46,    47,    48,    49,    60,
      59,    57,    63,    56,    60,    61,    48,    49,   128,   129,
      56,    56,    56,    56,    70,    21,    72,    73,    74,    75,
      56,    59,    56,    56,    80,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    58,    56,    58,    45,    45,    56,
      45,   106,    45,    58,    60,    59,    59,    22,    60,    18,
     115,    61,   117,    25,    58,    56,    30,    17,   114,     6,
       7,     8,     9,    10,    11,   130,   131,    58,    18,    16,
      18,    32,   120,    20,   111,    43,    -1,    24,    -1,    -1,
      27,    28,    29,    -1,    31,    -1,    33,    34,    35,    36,
      37,    38,    -1,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    20,    -1,    56,
      23,    24,    -1,    -1,    27,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    38,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    19,
      20,    -1,    -1,    56,    24,    -1,    -1,    27,    28,    29,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    16,
      -1,    -1,    -1,    20,    -1,    -1,    56,    24,    -1,    26,
      27,    28,    29,    -1,    31,    -1,    33,    34,    35,    36,
      37,    38,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    19,    20,    -1,    -1,    56,
      24,    -1,    -1,    27,    28,    29,    -1,    31,    -1,    33,
      34,    35,    36,    37,    38,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    16,    -1,    -1,    19,    20,
      -1,    -1,    56,    24,    -1,    -1,    27,    28,    29,    -1,
      31,    -1,    33,    34,    35,    36,    37,    38,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    20,    -1,    -1,    56,    24,    -1,    -1,    27,
      28,    29,    -1,    31,    -1,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    65,     5,    66,     0,     7,     8,     9,    10,
      11,    16,    20,    24,    27,    28,    29,    31,    33,    34,
      35,    36,    37,    38,    56,    67,    68,    69,    73,    74,
      78,    80,    81,    83,    84,     4,    56,    56,    56,    56,
      56,    59,    21,    59,    56,    56,    56,    56,    57,    58,
      59,    75,    76,    58,    58,    56,    75,    45,     6,    68,
      45,    45,    56,    75,    79,    56,    79,    45,    58,    59,
      59,    75,    46,    47,    48,    49,    75,    75,    75,    44,
      50,    60,    22,    60,    61,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    70,    71,    72,    75,    77,    60,
      75,    75,    75,    75,    75,    18,    67,    25,    58,    82,
      60,    63,    56,    60,    63,    67,    23,    67,    62,    63,
      30,    71,    75,    19,    26,    58,    72,    17,    18,    18,
      67,    67,    19,    19,    32
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 59 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_PROGRAM, "PROGRAM", NULL, line);
          addChild((yyval.node), (yyvsp[(2) - (3)].node));
          root = (yyval.node);
      ;}
    break;

  case 3:
#line 68 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_SCREENPLAY, "SCREENPLAY", NULL, line);
          addChild((yyval.node), (yyvsp[(2) - (3)].node));
      ;}
    break;

  case 4:
#line 76 "moviescript.y"
    {
          if ((yyvsp[(2) - (2)].node) != NULL) {
              appendSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
          }
          (yyval.node) = (yyvsp[(1) - (2)].node);
      ;}
    break;

  case 5:
#line 83 "moviescript.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 14:
#line 101 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_FUNCTION, (yyvsp[(2) - (11)].str), (yyvsp[(7) - (11)].node)->value, line);
          (yyval.node)->left = (yyvsp[(4) - (11)].node);
          (yyval.node)->right = (yyvsp[(9) - (11)].node);
      ;}
    break;

  case 15:
#line 110 "moviescript.y"
    {
          appendSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
          (yyval.node) = (yyvsp[(1) - (3)].node);
      ;}
    break;

  case 16:
#line 115 "moviescript.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 17:
#line 119 "moviescript.y"
    {
          (yyval.node) = NULL;
      ;}
    break;

  case 18:
#line 126 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_PARAM, (yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].node)->value, line);
      ;}
    break;

  case 19:
#line 133 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "CHARACTER", line); ;}
    break;

  case 20:
#line 135 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "SCENE", line); ;}
    break;

  case 21:
#line 137 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "DIALOGUE", line); ;}
    break;

  case 22:
#line 139 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "RATING", line); ;}
    break;

  case 23:
#line 141 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "BUDGET", line); ;}
    break;

  case 24:
#line 143 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "GENRE", line); ;}
    break;

  case 25:
#line 145 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "STATUS", line); ;}
    break;

  case 26:
#line 147 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "WHOLE", line); ;}
    break;

  case 27:
#line 149 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, "SIGNAL", line); ;}
    break;

  case 28:
#line 154 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (2)].str), "CHARACTER", line);
      ;}
    break;

  case 29:
#line 158 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (2)].str), "SCENE", line);
      ;}
    break;

  case 30:
#line 162 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (2)].str), "DIALOGUE", line);
      ;}
    break;

  case 31:
#line 166 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (2)].str), "RATING", line);
      ;}
    break;

  case 32:
#line 170 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (2)].str), "BUDGET", line);
      ;}
    break;

  case 33:
#line 174 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (4)].str), "RATING", line);
          addChild((yyval.node), (yyvsp[(4) - (4)].node));
      ;}
    break;

  case 34:
#line 179 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_DECL, (yyvsp[(2) - (4)].str), "BUDGET", line);
          addChild((yyval.node), (yyvsp[(4) - (4)].node));
      ;}
    break;

  case 35:
#line 187 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ASSIGN, (yyvsp[(1) - (3)].str), NULL, line);
          (yyval.node)->left = (yyvsp[(3) - (3)].node);
          if ((yyvsp[(3) - (3)].node) != NULL && (yyvsp[(3) - (3)].node)->value != NULL) {
              setNodeValue((yyval.node), (yyvsp[(3) - (3)].node)->value);
          }
      ;}
    break;

  case 36:
#line 198 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_BINARY_OP, "+", NULL, line);
          (yyval.node)->left = (yyvsp[(1) - (3)].node);
          (yyval.node)->right = (yyvsp[(3) - (3)].node);
      ;}
    break;

  case 37:
#line 204 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_BINARY_OP, "-", NULL, line);
          (yyval.node)->left = (yyvsp[(1) - (3)].node);
          (yyval.node)->right = (yyvsp[(3) - (3)].node);
      ;}
    break;

  case 38:
#line 210 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_BINARY_OP, "*", NULL, line);
          (yyval.node)->left = (yyvsp[(1) - (3)].node);
          (yyval.node)->right = (yyvsp[(3) - (3)].node);
      ;}
    break;

  case 39:
#line 216 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_BINARY_OP, "/", NULL, line);
          (yyval.node)->left = (yyvsp[(1) - (3)].node);
          (yyval.node)->right = (yyvsp[(3) - (3)].node);
      ;}
    break;

  case 40:
#line 222 "moviescript.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 41:
#line 229 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), line);
      ;}
    break;

  case 42:
#line 233 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), line);
      ;}
    break;

  case 43:
#line 237 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_VALUE, (yyvsp[(1) - (1)].str), NULL, line);
      ;}
    break;

  case 44:
#line 241 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_CALL, (yyvsp[(1) - (4)].str), NULL, line);
          (yyval.node)->left = (yyvsp[(3) - (4)].node);
      ;}
    break;

  case 45:
#line 246 "moviescript.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 46:
#line 253 "moviescript.y"
    {
          appendSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
          (yyval.node) = (yyvsp[(1) - (3)].node);
      ;}
    break;

  case 47:
#line 258 "moviescript.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 48:
#line 262 "moviescript.y"
    {
          (yyval.node) = NULL;
      ;}
    break;

  case 49:
#line 269 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_IF, NULL, NULL, line);
          (yyval.node)->left = (yyvsp[(3) - (11)].node);
          (yyval.node)->right = (yyvsp[(6) - (11)].node);
      (yyval.node)->elseBranch = (yyvsp[(10) - (11)].node);
      ;}
    break;

  case 50:
#line 279 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_CONDITION, ">", NULL, line);
          (yyval.node)->left = (yyvsp[(1) - (3)].node);
          (yyval.node)->right = (yyvsp[(3) - (3)].node);
      ;}
    break;

  case 51:
#line 285 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_CONDITION, "RISING", NULL, line);
          (yyval.node)->left = createNodeWithLine(NODE_VALUE, (yyvsp[(1) - (2)].str), NULL, line);
      ;}
    break;

  case 52:
#line 293 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_WHILE, NULL, NULL, line);
          (yyval.node)->left = (yyvsp[(3) - (7)].node);
          (yyval.node)->right = (yyvsp[(6) - (7)].node);
      ;}
    break;

  case 53:
#line 299 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_FOR, (yyvsp[(3) - (6)].str), NULL, line);
          (yyval.node)->right = (yyvsp[(5) - (6)].node);
      ;}
    break;

  case 54:
#line 307 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_COLLECTION, (yyvsp[(2) - (6)].str), "GENRE_COLLECTION", line);
          (yyval.node)->left = (yyvsp[(5) - (6)].node);
      ;}
    break;

  case 55:
#line 312 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_COLLECTION_ADD, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str), line);
      ;}
    break;

  case 56:
#line 319 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), line);
      ;}
    break;

  case 57:
#line 323 "moviescript.y"
    {
	      ASTNode* item = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(3) - (3)].str), line);
          appendSibling((yyvsp[(1) - (3)].node), item);
          (yyval.node) = (yyvsp[(1) - (3)].node);
      ;}
    break;

  case 58:
#line 332 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "PRINT", NULL, line);
          (yyval.node)->left = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 59:
#line 337 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "AWARD", (yyvsp[(2) - (2)].str), line);
      ;}
    break;

  case 60:
#line 341 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "REVIEW", (yyvsp[(2) - (2)].str), line);
      ;}
    break;

  case 61:
#line 345 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "ANALYZE", (yyvsp[(2) - (2)].str), line);
      ;}
    break;

  case 62:
#line 349 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "BUILD_SUSPENSE", NULL, line);
      ;}
    break;

  case 63:
#line 353 "moviescript.y"
    {
	      (yyval.node) = createNodeWithLine(NODE_ACTION, "ENTER_STAGE", NULL, line);
      ;}
    break;

  case 64:
#line 360 "moviescript.y"
    {
          (yyval.node) = createNodeWithLine(NODE_RETURN, NULL, NULL, line);
          (yyval.node)->left = (yyvsp[(2) - (2)].node);
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2019 "moviescript.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 366 "moviescript.y"


void yyerror(const char *s)
{
  fprintf(stderr, "Syntax Error at line %d : unexpected token (%s)\n", line, s);
}
