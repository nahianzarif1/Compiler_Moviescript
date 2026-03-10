%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* root = NULL;
extern int line;

void yyerror(const char *s);
int yylex(void);
%}

%union {
    ASTNode* node;
    char* str;
}

%token OPENING_CREDITS FINAL_CREDITS
%token SCREENPLAY ENDSCREENPLAY

%token CHARACTER SCENE DIALOGUE RATING BUDGET GENRE STATUS
%token WHOLE SIGNAL

%token SCENE_IF OTHERWISE FRAME ENDFRAME
%token FOR_EACH_SCENE IN REEL ENDREEL
%token WHILE TAKE ENDTAKE

%token GENRE_COLLECTION ADD_TO

%token AWARD REVIEW ANALYZE PRINT BUILD_SUSPENSE ENTER_STAGE

%token SUCCESS FAILURE BLOCKBUSTER FLOP AVERAGE
%token RISING

%token ASSIGN
%token PLUS MINUS STAR SLASH
%token GREATER_THAN GREATER_EQUAL LESS_THAN LESS_EQUAL IS IS_NOT

%token <str> IDENTIFIER
%token <str> NUMBER
%token <str> STRING

%token LPAREN RPAREN LBRACE RBRACE COMMA

%type <node> program screenplay statements statement declaration assignment
%type <node> conditional condition loop collection action expression string_list primary

%left PLUS MINUS
%left STAR SLASH

%%

program
    : OPENING_CREDITS screenplay FINAL_CREDITS
      {
	      $$ = createNodeWithLine(NODE_PROGRAM, "PROGRAM", NULL, line);
          addChild($$, $2);
          root = $$;
      }
    ;

screenplay
    : SCREENPLAY statements ENDSCREENPLAY
      {
	      $$ = createNodeWithLine(NODE_SCREENPLAY, "SCREENPLAY", NULL, line);
          addChild($$, $2);
      }
    ;

statements
    : statements statement
      {
          if ($2 != NULL) {
              appendSibling($1, $2);
          }
          $$ = $1;
      }
    | statement
      {
          $$ = $1;
      }
    ;

statement
    : declaration
    | assignment
    | conditional
    | loop
    | collection
    | action
    ;

declaration
    : CHARACTER IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "CHARACTER", line);
      }
    | SCENE IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "SCENE", line);
      }
    | DIALOGUE IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "DIALOGUE", line);
      }
    | RATING IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "RATING", line);
      }
    | BUDGET IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "BUDGET", line);
      }
    | RATING IDENTIFIER ASSIGN expression
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "RATING", line);
          addChild($$, $4);
      }
    | BUDGET IDENTIFIER ASSIGN expression
      {
	      $$ = createNodeWithLine(NODE_DECL, $2, "BUDGET", line);
          addChild($$, $4);
      }
    ;

assignment
    : IDENTIFIER ASSIGN expression
      {
	      $$ = createNodeWithLine(NODE_ASSIGN, $1, NULL, line);
          $$->left = $3;
          if ($3 != NULL && $3->value != NULL) {
              setNodeValue($$, $3->value);
          }
      }
    ;

expression
    : expression PLUS expression
      {
          $$ = createNodeWithLine(NODE_BINARY_OP, "+", NULL, line);
          $$->left = $1;
          $$->right = $3;
      }
    | expression MINUS expression
      {
          $$ = createNodeWithLine(NODE_BINARY_OP, "-", NULL, line);
          $$->left = $1;
          $$->right = $3;
      }
    | expression STAR expression
      {
          $$ = createNodeWithLine(NODE_BINARY_OP, "*", NULL, line);
          $$->left = $1;
          $$->right = $3;
      }
    | expression SLASH expression
      {
          $$ = createNodeWithLine(NODE_BINARY_OP, "/", NULL, line);
          $$->left = $1;
          $$->right = $3;
      }
    | primary
      {
          $$ = $1;
      }
    ;

primary
    : NUMBER
      {
	      $$ = createNodeWithLine(NODE_VALUE, NULL, $1, line);
      }
    | STRING
      {
	      $$ = createNodeWithLine(NODE_VALUE, NULL, $1, line);
      }
    | IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_VALUE, $1, NULL, line);
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
    ;

conditional
    : SCENE_IF LPAREN condition RPAREN FRAME statements ENDFRAME OTHERWISE FRAME statements ENDFRAME
      {
	      $$ = createNodeWithLine(NODE_IF, NULL, NULL, line);
          $$->left = $3;
          $$->right = $6;
          if ($6 != NULL) {
              appendSibling($6, $10);
          } else {
              $$->right = $10;
          }
      }
    ;

condition
    : IDENTIFIER GREATER_THAN NUMBER
      {
	      $$ = createNodeWithLine(NODE_CONDITION, $1, $3, line);
      }
    | IDENTIFIER RISING
      {
	      $$ = createNodeWithLine(NODE_CONDITION, $1, "RISING", line);
      }
    ;

loop
    : WHILE LPAREN condition RPAREN TAKE statements ENDTAKE
      {
	      $$ = createNodeWithLine(NODE_WHILE, NULL, NULL, line);
          $$->left = $3;
          $$->right = $6;
      }
    | FOR_EACH_SCENE IN IDENTIFIER REEL statements ENDREEL
      {
	      $$ = createNodeWithLine(NODE_FOR, $3, NULL, line);
          $$->right = $5;
      }
    ;

collection
    : GENRE_COLLECTION IDENTIFIER ASSIGN LBRACE string_list RBRACE
      {
	      $$ = createNodeWithLine(NODE_COLLECTION, $2, "GENRE_COLLECTION", line);
          $$->left = $5;
      }
    | ADD_TO IDENTIFIER STRING
      {
	      $$ = createNodeWithLine(NODE_COLLECTION_ADD, $2, $3, line);
      }
    ;

string_list
    : STRING
      {
	      $$ = createNodeWithLine(NODE_VALUE, NULL, $1, line);
      }
    | string_list COMMA STRING
      {
	      ASTNode* item = createNodeWithLine(NODE_VALUE, NULL, $3, line);
          appendSibling($1, item);
          $$ = $1;
      }
    ;

action
    : PRINT STRING
      {
	      $$ = createNodeWithLine(NODE_ACTION, "PRINT", $2, line);
      }
    | AWARD STRING
      {
	      $$ = createNodeWithLine(NODE_ACTION, "AWARD", $2, line);
      }
    | REVIEW STRING
      {
	      $$ = createNodeWithLine(NODE_ACTION, "REVIEW", $2, line);
      }
    | ANALYZE IDENTIFIER
      {
	      $$ = createNodeWithLine(NODE_ACTION, "ANALYZE", $2, line);
      }
    | BUILD_SUSPENSE
      {
	      $$ = createNodeWithLine(NODE_ACTION, "BUILD_SUSPENSE", NULL, line);
      }
    | ENTER_STAGE
      {
	      $$ = createNodeWithLine(NODE_ACTION, "ENTER_STAGE", NULL, line);
      }
    ;

%%

void yyerror(const char *s)
{
  fprintf(stderr, "Syntax Error at line %d : unexpected token (%s)\n", line, s);
}