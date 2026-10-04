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
#define YYLSP_NEEDED 1



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
     ASSERT = 292,
     BUILD_SUSPENSE = 293,
     ENTER_STAGE = 294,
     RISING = 295,
     ASSIGN = 296,
     PLUS = 297,
     MINUS = 298,
     STAR = 299,
     SLASH = 300,
     MOD = 301,
     GREATER_THAN = 302,
     GREATER_EQUAL = 303,
     LESS_THAN = 304,
     LESS_EQUAL = 305,
     IS = 306,
     IS_NOT = 307,
     AND = 308,
     OR = 309,
     NOT = 310,
     LPAREN = 311,
     RPAREN = 312,
     LBRACE = 313,
     RBRACE = 314,
     COMMA = 315,
     INVALID = 316,
     IDENTIFIER = 317,
     NUMBER = 318,
     STRING = 319,
     LITERAL = 320,
     BUILTIN = 321,
     UMINUS = 322
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
#define ASSERT 292
#define BUILD_SUSPENSE 293
#define ENTER_STAGE 294
#define RISING 295
#define ASSIGN 296
#define PLUS 297
#define MINUS 298
#define STAR 299
#define SLASH 300
#define MOD 301
#define GREATER_THAN 302
#define GREATER_EQUAL 303
#define LESS_THAN 304
#define LESS_EQUAL 305
#define IS 306
#define IS_NOT 307
#define AND 308
#define OR 309
#define NOT 310
#define LPAREN 311
#define RPAREN 312
#define LBRACE 313
#define RBRACE 314
#define COMMA 315
#define INVALID 316
#define IDENTIFIER 317
#define NUMBER 318
#define STRING 319
#define LITERAL 320
#define BUILTIN 321
#define UMINUS 322




/* Copy the first part of user declarations.  */
#line 1 "moviescript.y"

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "diagnostic.h"
#define YYMALLOC msAlloc
#define YYFREE free

ASTNode* root = NULL;
void yyerror(const char* message);
int yylex(void);

static ASTNode* namedNode(NodeType type, char* name, const char* value, int line)
{
    ASTNode* node = createNodeWithLine(type, name, value, line);
    free(name); return node;
}

static ASTNode* binary(NodeType type, const char* op, ASTNode* a, ASTNode* b, int line)
{
    ASTNode* node = createNodeWithLine(type, op, NULL, line);
    node->left = a; node->right = b; return node;
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "moviescript.y"
{ ASTNode* node; char* str; }
/* Line 193 of yacc.c.  */
#line 257 "moviescript.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 282 "moviescript.tab.c"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   468

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    12,    15,    17,    19,    21,
      23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    47,    49,    51,    54,    59,    63,    75,    76,
      78,    80,    84,    87,    90,    95,    96,    98,   100,   104,
     108,   112,   116,   120,   124,   128,   132,   136,   140,   144,
     148,   152,   156,   159,   162,   165,   167,   169,   171,   173,
     175,   177,   182,   186,   194,   206,   214,   221,   229,   236,
     240,   241,   243,   245,   249,   252,   255,   258,   261,   268,
     270
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,     3,    70,     4,    -1,     5,    71,     6,
      -1,    -1,    71,    72,    -1,    74,    -1,    75,    -1,    86,
      -1,    87,    -1,    88,    -1,    76,    -1,    80,    -1,    91,
      -1,    81,    -1,     7,    -1,     8,    -1,     9,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    15,
      -1,    73,    62,    -1,    73,    62,    41,    84,    -1,    62,
      41,    84,    -1,    29,    62,    56,    77,    57,    30,    73,
      18,    71,    19,    32,    -1,    -1,    78,    -1,    79,    -1,
      78,    60,    79,    -1,    73,    62,    -1,    31,    84,    -1,
      62,    56,    82,    57,    -1,    -1,    83,    -1,    84,    -1,
      83,    60,    84,    -1,    84,    42,    84,    -1,    84,    43,
      84,    -1,    84,    44,    84,    -1,    84,    45,    84,    -1,
      84,    46,    84,    -1,    84,    47,    84,    -1,    84,    48,
      84,    -1,    84,    49,    84,    -1,    84,    50,    84,    -1,
      84,    51,    84,    -1,    84,    52,    84,    -1,    84,    53,
      84,    -1,    84,    54,    84,    -1,    55,    84,    -1,    43,
      84,    -1,    84,    40,    -1,    85,    -1,    63,    -1,    64,
      -1,    65,    -1,    62,    -1,    81,    -1,    66,    56,    82,
      57,    -1,    56,    84,    57,    -1,    16,    56,    84,    57,
      18,    71,    19,    -1,    16,    56,    84,    57,    18,    71,
      19,    17,    18,    71,    19,    -1,    24,    56,    84,    57,
      25,    71,    26,    -1,    20,    21,    62,    22,    71,    23,
      -1,    20,    62,    21,    62,    22,    71,    23,    -1,    27,
      62,    41,    58,    89,    59,    -1,    28,    62,    84,    -1,
      -1,    90,    -1,    64,    -1,    90,    60,    64,    -1,    36,
      84,    -1,    33,    84,    -1,    34,    84,    -1,    35,    62,
      -1,    37,    56,    84,    60,    64,    57,    -1,    38,    -1,
      39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    50,    50,    53,    56,    57,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    70,    72,    75,    78,    81,    81,
      82,    83,    85,    88,    89,    90,    90,    91,    92,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   112,   113,   114,   115,
     116,   117,   118,   120,   122,   125,   127,   129,   132,   134,
     137,   137,   138,   139,   143,   144,   145,   146,   147,   150,
     151
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
  "ANALYZE", "PRINT", "ASSERT", "BUILD_SUSPENSE", "ENTER_STAGE", "RISING",
  "ASSIGN", "PLUS", "MINUS", "STAR", "SLASH", "MOD", "GREATER_THAN",
  "GREATER_EQUAL", "LESS_THAN", "LESS_EQUAL", "IS", "IS_NOT", "AND", "OR",
  "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COMMA", "INVALID",
  "IDENTIFIER", "NUMBER", "STRING", "LITERAL", "BUILTIN", "UMINUS",
  "$accept", "program", "screenplay", "statements", "statement",
  "type_spec", "declaration", "assignment", "function_decl", "param_list",
  "params", "param", "return_stmt", "call", "argument_list", "arguments",
  "expression", "primary", "conditional", "loop", "collection",
  "string_list", "strings", "action", 0
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
     315,   316,   317,   318,   319,   320,   321,   322
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    74,    74,    75,    76,    77,    77,
      78,    78,    79,    80,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    87,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     3,    11,     0,     1,
       1,     3,     2,     2,     4,     0,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     4,     3,     7,    11,     7,     6,     7,     6,     3,
       0,     1,     1,     3,     2,     2,     2,     2,     6,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     2,     3,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,    80,     0,     5,     0,     6,     7,    11,    12,    14,
       8,     9,    10,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    56,    57,    58,     0,    60,
      33,    55,    75,    76,    77,    74,     0,     0,    35,    24,
       0,     0,     0,     0,     0,    69,    28,    53,    52,     0,
      35,    54,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,    36,    37,
       0,     0,     4,     0,     0,    70,     0,     0,    29,    30,
      62,     0,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,     0,    34,     0,    25,     4,
       0,     4,     4,    72,     0,    71,    32,     0,     0,    61,
       0,    38,     0,    66,     0,     0,    68,     0,     0,    31,
      78,    63,    67,    65,    73,     0,     0,     4,     4,     0,
       0,     0,    64,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     4,     6,    33,    34,    35,    36,    37,   107,
     108,   109,    38,    59,    97,    98,    99,    61,    40,    41,
      42,   134,   135,    43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -85
static const yytype_int16 yypact[] =
{
       1,     4,     6,   -85,    10,   -85,    78,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,   -85,   -85,   -41,   -13,
     -40,   -45,   -42,   -39,   -24,   -24,   -24,   -37,   -24,   -29,
     -85,   -85,   -34,   -85,   -28,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -24,   -27,    12,   -24,    -5,   -24,
     -19,   -24,   -24,   -24,   -10,   -85,   -85,   -85,    19,   -85,
     387,   -85,   387,   387,   -85,   387,   -24,   -24,   -24,    35,
     339,    56,    17,   355,    22,   387,    43,   -85,    83,   371,
     -24,   -85,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   317,   387,    24,    23,   387,
     -24,    77,   -85,    74,    72,    36,    37,    44,    48,   -85,
     -85,    46,   -33,   -33,   -85,   -85,   -85,   416,   416,   416,
     416,   416,   416,    83,   402,    54,   -85,   -24,   387,   -85,
     135,   -85,   -85,   -85,    51,    59,   -85,    90,    43,   -85,
      64,   387,   171,   -85,   207,   244,   -85,    58,    43,   -85,
     -85,   120,   -85,   -85,   -85,   123,   134,   -85,   -85,   280,
     316,   124,   -85,   -85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,   -84,   -85,   -66,   -85,   -85,   -85,   -85,
     -85,    27,   -85,    -6,    80,   -85,   -23,   -85,   -85,   -85,
     -85,   -85,   -85,   -85
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      39,    60,    62,    63,     1,    65,     5,    67,    45,     3,
     106,    84,    85,    86,     7,    44,    47,    48,   130,    51,
      49,    70,    68,    50,    73,    64,    75,    66,    77,    78,
      79,    52,    53,    72,    69,    71,    74,    76,    54,    55,
      56,    57,    58,    95,    96,   142,    68,   144,   145,    46,
       9,    10,    11,    12,    13,    14,    15,    16,    17,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   106,   159,   160,    80,   100,   128,   102,   103,
     105,   126,   155,   127,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   129,   131,   132,    19,   136,
     133,   137,    20,   139,   141,    21,    22,    23,   138,    24,
     146,    25,    26,    27,    28,    29,    30,    31,   140,   147,
     148,   150,   154,    81,    39,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    39,   156,    39,    39,
      32,   157,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,   158,    39,    39,    19,   163,     0,   143,    20,
     111,     0,    21,    22,    23,   149,    24,     0,    25,    26,
      27,    28,    29,    30,    31,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
     151,    19,     0,     0,     0,    20,     0,    32,    21,    22,
      23,     0,    24,     0,    25,    26,    27,    28,    29,    30,
      31,     0,     0,     0,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,     0,    19,     0,     0,
     152,    20,     0,    32,    21,    22,    23,     0,    24,     0,
      25,    26,    27,    28,    29,    30,    31,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,     0,     0,     0,    19,     0,     0,     0,    20,    32,
     153,    21,    22,    23,     0,    24,     0,    25,    26,    27,
      28,    29,    30,    31,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,     0,   161,
      19,     0,     0,     0,    20,     0,    32,    21,    22,    23,
       0,    24,     0,    25,    26,    27,    28,    29,    30,    31,
       0,     0,     0,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,   162,    19,     0,     0,     0,
      20,     0,    32,    21,    22,    23,     0,    24,     0,    25,
      26,    27,    28,    29,    30,    31,     0,    81,     0,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,     0,   125,    32,    81,
       0,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     0,    81,   101,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,    81,   104,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     0,    81,   110,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    81,     0,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,     0,    82,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
       6,    24,    25,    26,     3,    28,     0,    41,    21,     5,
      76,    44,    45,    46,     4,    56,    56,    62,   102,    43,
      62,    44,    56,    62,    47,    62,    49,    56,    51,    52,
      53,    55,    56,    21,    62,    62,    41,    56,    62,    63,
      64,    65,    66,    66,    67,   129,    56,   131,   132,    62,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,   138,   157,   158,    56,    41,   100,    22,    62,
      58,    57,   148,    60,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    18,    22,    25,    20,    62,
      64,    57,    24,    57,   127,    27,    28,    29,    60,    31,
      59,    33,    34,    35,    36,    37,    38,    39,    64,    60,
      30,    57,    64,    40,   130,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,   142,    17,   144,   145,
      62,    18,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    18,   159,   160,    20,    32,    -1,    23,    24,
      80,    -1,    27,    28,    29,   138,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    -1,    -1,    -1,    24,    -1,    62,    27,    28,
      29,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    20,    -1,    -1,
      23,    24,    -1,    62,    27,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,    62,
      26,    27,    28,    29,    -1,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    -1,    24,    -1,    62,    27,    28,    29,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    -1,    -1,    -1,
      24,    -1,    62,    27,    28,    29,    -1,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    40,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    60,    62,    40,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    40,    57,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    40,    57,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    40,    57,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    40,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    40,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    69,     5,    70,     0,    71,     4,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    20,
      24,    27,    28,    29,    31,    33,    34,    35,    36,    37,
      38,    39,    62,    72,    73,    74,    75,    76,    80,    81,
      86,    87,    88,    91,    56,    21,    62,    56,    62,    62,
      62,    43,    55,    56,    62,    63,    64,    65,    66,    81,
      84,    85,    84,    84,    62,    84,    56,    41,    56,    62,
      84,    62,    21,    84,    41,    84,    56,    84,    84,    84,
      56,    40,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    84,    84,    82,    83,    84,
      41,    57,    22,    62,    57,    58,    73,    77,    78,    79,
      57,    82,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    60,    57,    60,    84,    18,
      71,    22,    25,    64,    89,    90,    62,    57,    60,    57,
      64,    84,    71,    23,    71,    71,    59,    60,    30,    79,
      57,    19,    23,    26,    64,    73,    17,    18,    18,    71,
      71,    19,    19,    32
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 62: /* "IDENTIFIER" */
#line 39 "moviescript.y"
	{ free((yyvaluep->str)); };
#line 1396 "moviescript.tab.c"
	break;
      case 63: /* "NUMBER" */
#line 39 "moviescript.y"
	{ free((yyvaluep->str)); };
#line 1401 "moviescript.tab.c"
	break;
      case 64: /* "STRING" */
#line 39 "moviescript.y"
	{ free((yyvaluep->str)); };
#line 1406 "moviescript.tab.c"
	break;
      case 65: /* "LITERAL" */
#line 39 "moviescript.y"
	{ free((yyvaluep->str)); };
#line 1411 "moviescript.tab.c"
	break;
      case 66: /* "BUILTIN" */
#line 39 "moviescript.y"
	{ free((yyvaluep->str)); };
#line 1416 "moviescript.tab.c"
	break;
      case 69: /* "program" */
#line 41 "moviescript.y"
	{ };
#line 1421 "moviescript.tab.c"
	break;
      case 70: /* "screenplay" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1426 "moviescript.tab.c"
	break;
      case 71: /* "statements" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1431 "moviescript.tab.c"
	break;
      case 72: /* "statement" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1436 "moviescript.tab.c"
	break;
      case 73: /* "type_spec" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1441 "moviescript.tab.c"
	break;
      case 74: /* "declaration" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1446 "moviescript.tab.c"
	break;
      case 75: /* "assignment" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1451 "moviescript.tab.c"
	break;
      case 76: /* "function_decl" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1456 "moviescript.tab.c"
	break;
      case 77: /* "param_list" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1461 "moviescript.tab.c"
	break;
      case 78: /* "params" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1466 "moviescript.tab.c"
	break;
      case 79: /* "param" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1471 "moviescript.tab.c"
	break;
      case 80: /* "return_stmt" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1476 "moviescript.tab.c"
	break;
      case 81: /* "call" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1481 "moviescript.tab.c"
	break;
      case 82: /* "argument_list" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1486 "moviescript.tab.c"
	break;
      case 83: /* "arguments" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1491 "moviescript.tab.c"
	break;
      case 84: /* "expression" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1496 "moviescript.tab.c"
	break;
      case 85: /* "primary" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1501 "moviescript.tab.c"
	break;
      case 86: /* "conditional" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1506 "moviescript.tab.c"
	break;
      case 87: /* "loop" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1511 "moviescript.tab.c"
	break;
      case 88: /* "collection" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1516 "moviescript.tab.c"
	break;
      case 89: /* "string_list" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1521 "moviescript.tab.c"
	break;
      case 90: /* "strings" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1526 "moviescript.tab.c"
	break;
      case 91: /* "action" */
#line 40 "moviescript.y"
	{ freeAST((yyvaluep->node)); };
#line 1531 "moviescript.tab.c"
	break;

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
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



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

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

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
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 50 "moviescript.y"
    {
    (yyval.node) = createNodeWithLine(NODE_PROGRAM, "PROGRAM", NULL, (yylsp[(1) - (3)]).first_line); (yyval.node)->left = (yyvsp[(2) - (3)].node); root = (yyval.node);
;}
    break;

  case 3:
#line 53 "moviescript.y"
    {
    (yyval.node) = createNodeWithLine(NODE_SCREENPLAY, "SCREENPLAY", NULL, (yylsp[(1) - (3)]).first_line); (yyval.node)->left = (yyvsp[(2) - (3)].node);
;}
    break;

  case 4:
#line 56 "moviescript.y"
    { (yyval.node) = NULL; ;}
    break;

  case 5:
#line 57 "moviescript.y"
    { if ((yyvsp[(1) - (2)].node)) { appendSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node); } else (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 15:
#line 60 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "CHARACTER"); ;}
    break;

  case 16:
#line 61 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "SCENE"); ;}
    break;

  case 17:
#line 62 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "DIALOGUE"); ;}
    break;

  case 18:
#line 63 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "RATING"); ;}
    break;

  case 19:
#line 64 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "BUDGET"); ;}
    break;

  case 20:
#line 65 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "GENRE"); ;}
    break;

  case 21:
#line 66 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "STATUS"); ;}
    break;

  case 22:
#line 67 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "WHOLE"); ;}
    break;

  case 23:
#line 68 "moviescript.y"
    { (yyval.node) = createNode(NODE_VALUE, NULL, "SIGNAL"); ;}
    break;

  case 24:
#line 70 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_DECL, (yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].node)->value, (yylsp[(1) - (2)]).first_line); freeAST((yyvsp[(1) - (2)].node));
;}
    break;

  case 25:
#line 72 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_DECL, (yyvsp[(2) - (4)].str), (yyvsp[(1) - (4)].node)->value, (yylsp[(1) - (4)]).first_line); (yyval.node)->left = (yyvsp[(4) - (4)].node); freeAST((yyvsp[(1) - (4)].node));
;}
    break;

  case 26:
#line 75 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_ASSIGN, (yyvsp[(1) - (3)].str), NULL, (yylsp[(1) - (3)]).first_line); (yyval.node)->left = (yyvsp[(3) - (3)].node);
;}
    break;

  case 27:
#line 78 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_FUNCTION, (yyvsp[(2) - (11)].str), (yyvsp[(7) - (11)].node)->value, (yylsp[(1) - (11)]).first_line); (yyval.node)->left = (yyvsp[(4) - (11)].node); (yyval.node)->right = (yyvsp[(9) - (11)].node); freeAST((yyvsp[(7) - (11)].node));
;}
    break;

  case 28:
#line 81 "moviescript.y"
    { (yyval.node) = NULL; ;}
    break;

  case 29:
#line 81 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 30:
#line 82 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 31:
#line 83 "moviescript.y"
    { appendSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node) = (yyvsp[(1) - (3)].node); ;}
    break;

  case 32:
#line 85 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_PARAM, (yyvsp[(2) - (2)].str), (yyvsp[(1) - (2)].node)->value, (yylsp[(1) - (2)]).first_line); freeAST((yyvsp[(1) - (2)].node));
;}
    break;

  case 33:
#line 88 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_RETURN, NULL, NULL, (yylsp[(1) - (2)]).first_line); (yyval.node)->left = (yyvsp[(2) - (2)].node); ;}
    break;

  case 34:
#line 89 "moviescript.y"
    { (yyval.node) = namedNode(NODE_CALL, (yyvsp[(1) - (4)].str), NULL, (yylsp[(1) - (4)]).first_line); (yyval.node)->left = (yyvsp[(3) - (4)].node); ;}
    break;

  case 35:
#line 90 "moviescript.y"
    { (yyval.node) = NULL; ;}
    break;

  case 36:
#line 90 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 37:
#line 91 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 38:
#line 92 "moviescript.y"
    { appendSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node) = (yyvsp[(1) - (3)].node); ;}
    break;

  case 39:
#line 94 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "+", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 40:
#line 95 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "-", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 41:
#line 96 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "*", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 42:
#line 97 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "/", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 43:
#line 98 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "%", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 44:
#line 99 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, ">", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 45:
#line 100 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, ">=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 46:
#line 101 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, "<", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 47:
#line 102 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, "<=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 48:
#line 103 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, "==", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 49:
#line 104 "moviescript.y"
    { (yyval.node) = binary(NODE_CONDITION, "!=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 50:
#line 105 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "AND", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 51:
#line 106 "moviescript.y"
    { (yyval.node) = binary(NODE_BINARY_OP, "OR", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), (yylsp[(2) - (3)]).first_line); ;}
    break;

  case 52:
#line 107 "moviescript.y"
    { (yyval.node) = binary(NODE_UNARY_OP, "NOT", (yyvsp[(2) - (2)].node), NULL, (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 53:
#line 108 "moviescript.y"
    { (yyval.node) = binary(NODE_UNARY_OP, "-", (yyvsp[(2) - (2)].node), NULL, (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 54:
#line 109 "moviescript.y"
    { (yyval.node) = binary(NODE_UNARY_OP, "RISING", (yyvsp[(1) - (2)].node), NULL, (yylsp[(2) - (2)]).first_line); ;}
    break;

  case 55:
#line 110 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 56:
#line 112 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 57:
#line 113 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 58:
#line 114 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 59:
#line 115 "moviescript.y"
    { (yyval.node) = namedNode(NODE_VALUE, (yyvsp[(1) - (1)].str), NULL, (yylsp[(1) - (1)]).first_line); ;}
    break;

  case 60:
#line 116 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 61:
#line 117 "moviescript.y"
    { (yyval.node) = namedNode(NODE_BUILTIN, (yyvsp[(1) - (4)].str), NULL, (yylsp[(1) - (4)]).first_line); (yyval.node)->left = (yyvsp[(3) - (4)].node); ;}
    break;

  case 62:
#line 118 "moviescript.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 63:
#line 120 "moviescript.y"
    {
    (yyval.node) = binary(NODE_IF, NULL, (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node), (yylsp[(1) - (7)]).first_line);
;}
    break;

  case 64:
#line 122 "moviescript.y"
    {
    (yyval.node) = binary(NODE_IF, NULL, (yyvsp[(3) - (11)].node), (yyvsp[(6) - (11)].node), (yylsp[(1) - (11)]).first_line); (yyval.node)->elseBranch = (yyvsp[(10) - (11)].node);
;}
    break;

  case 65:
#line 125 "moviescript.y"
    {
    (yyval.node) = binary(NODE_WHILE, NULL, (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node), (yylsp[(1) - (7)]).first_line);
;}
    break;

  case 66:
#line 127 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_FOR, (yyvsp[(3) - (6)].str), NULL, (yylsp[(1) - (6)]).first_line); (yyval.node)->right = (yyvsp[(5) - (6)].node);
;}
    break;

  case 67:
#line 129 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_FOR, (yyvsp[(4) - (7)].str), (yyvsp[(2) - (7)].str), (yylsp[(1) - (7)]).first_line); free((yyvsp[(2) - (7)].str)); (yyval.node)->right = (yyvsp[(6) - (7)].node);
;}
    break;

  case 68:
#line 132 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_COLLECTION, (yyvsp[(2) - (6)].str), "GENRE_COLLECTION", (yylsp[(1) - (6)]).first_line); (yyval.node)->left = (yyvsp[(5) - (6)].node);
;}
    break;

  case 69:
#line 134 "moviescript.y"
    {
    (yyval.node) = namedNode(NODE_COLLECTION_ADD, (yyvsp[(2) - (3)].str), NULL, (yylsp[(1) - (3)]).first_line); (yyval.node)->left = (yyvsp[(3) - (3)].node);
;}
    break;

  case 70:
#line 137 "moviescript.y"
    { (yyval.node) = NULL; ;}
    break;

  case 71:
#line 137 "moviescript.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 72:
#line 138 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(1) - (1)].str), (yylsp[(1) - (1)]).first_line); free((yyvsp[(1) - (1)].str)); ;}
    break;

  case 73:
#line 139 "moviescript.y"
    {
        ASTNode* item = createNodeWithLine(NODE_VALUE, NULL, (yyvsp[(3) - (3)].str), (yylsp[(3) - (3)]).first_line); free((yyvsp[(3) - (3)].str)); appendSibling((yyvsp[(1) - (3)].node), item); (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 74:
#line 143 "moviescript.y"
    { (yyval.node) = binary(NODE_ACTION, "PRINT", (yyvsp[(2) - (2)].node), NULL, (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 75:
#line 144 "moviescript.y"
    { (yyval.node) = binary(NODE_ACTION, "AWARD", (yyvsp[(2) - (2)].node), NULL, (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 76:
#line 145 "moviescript.y"
    { (yyval.node) = binary(NODE_ACTION, "REVIEW", (yyvsp[(2) - (2)].node), NULL, (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 77:
#line 146 "moviescript.y"
    { (yyval.node) = namedNode(NODE_ACTION, (yyvsp[(2) - (2)].str), "ANALYZE", (yylsp[(1) - (2)]).first_line); ;}
    break;

  case 78:
#line 147 "moviescript.y"
    {
        (yyval.node) = createNodeWithLine(NODE_ACTION, "ASSERT", (yyvsp[(5) - (6)].str), (yylsp[(1) - (6)]).first_line); free((yyvsp[(5) - (6)].str)); (yyval.node)->left = (yyvsp[(3) - (6)].node);
    ;}
    break;

  case 79:
#line 150 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_ACTION, "BUILD_SUSPENSE", NULL, (yylsp[(1) - (1)]).first_line); ;}
    break;

  case 80:
#line 151 "moviescript.y"
    { (yyval.node) = createNodeWithLine(NODE_ACTION, "ENTER_STAGE", NULL, (yylsp[(1) - (1)]).first_line); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2237 "moviescript.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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


#line 153 "moviescript.y"

void yyerror(const char* message)
{
    reportError("Syntax Error", yylloc.first_line, "%s (column %d)", message, yylloc.first_column);
}
