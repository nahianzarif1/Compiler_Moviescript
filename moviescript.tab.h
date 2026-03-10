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
     AWARD = 284,
     REVIEW = 285,
     ANALYZE = 286,
     PRINT = 287,
     BUILD_SUSPENSE = 288,
     ENTER_STAGE = 289,
     SUCCESS = 290,
     FAILURE = 291,
     BLOCKBUSTER = 292,
     FLOP = 293,
     AVERAGE = 294,
     RISING = 295,
     ASSIGN = 296,
     PLUS = 297,
     MINUS = 298,
     STAR = 299,
     SLASH = 300,
     GREATER_THAN = 301,
     GREATER_EQUAL = 302,
     LESS_THAN = 303,
     LESS_EQUAL = 304,
     IS = 305,
     IS_NOT = 306,
     IDENTIFIER = 307,
     NUMBER = 308,
     STRING = 309,
     LPAREN = 310,
     RPAREN = 311,
     LBRACE = 312,
     RBRACE = 313,
     COMMA = 314
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
#define AWARD 284
#define REVIEW 285
#define ANALYZE 286
#define PRINT 287
#define BUILD_SUSPENSE 288
#define ENTER_STAGE 289
#define SUCCESS 290
#define FAILURE 291
#define BLOCKBUSTER 292
#define FLOP 293
#define AVERAGE 294
#define RISING 295
#define ASSIGN 296
#define PLUS 297
#define MINUS 298
#define STAR 299
#define SLASH 300
#define GREATER_THAN 301
#define GREATER_EQUAL 302
#define LESS_THAN 303
#define LESS_EQUAL 304
#define IS 305
#define IS_NOT 306
#define IDENTIFIER 307
#define NUMBER 308
#define STRING 309
#define LPAREN 310
#define RPAREN 311
#define LBRACE 312
#define RBRACE 313
#define COMMA 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "moviescript.y"
{
    ASTNode* node;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 172 "moviescript.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

