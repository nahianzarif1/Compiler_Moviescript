/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "moviescript.y"
{ ASTNode* node; char* str; }
/* Line 1529 of yacc.c.  */
#line 185 "moviescript.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
