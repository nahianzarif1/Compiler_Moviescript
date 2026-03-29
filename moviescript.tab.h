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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "moviescript.y"
{
    ASTNode* node;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 180 "moviescript.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

