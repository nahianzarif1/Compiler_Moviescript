%{
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
%}

%locations
%error-verbose
%union { ASTNode* node; char* str; }
%token OPENING_CREDITS FINAL_CREDITS SCREENPLAY ENDSCREENPLAY
%token CHARACTER SCENE DIALOGUE RATING BUDGET GENRE STATUS WHOLE SIGNAL
%token SCENE_IF OTHERWISE FRAME ENDFRAME FOR_EACH_SCENE IN REEL ENDREEL WHILE TAKE ENDTAKE
%token GENRE_COLLECTION ADD_TO FUNCTION RETURNS RETURN ENDFUNCTION
%token AWARD REVIEW ANALYZE PRINT ASSERT BUILD_SUSPENSE ENTER_STAGE RISING
%token ASSIGN PLUS MINUS STAR SLASH MOD GREATER_THAN GREATER_EQUAL LESS_THAN LESS_EQUAL IS IS_NOT AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE COMMA INVALID
%token <str> IDENTIFIER NUMBER STRING LITERAL BUILTIN
%type <node> program screenplay statements statement declaration assignment conditional loop collection action expression primary call
%type <node> function_decl param_list param type_spec return_stmt argument_list string_list params arguments strings
%destructor { free($$); } IDENTIFIER NUMBER STRING LITERAL BUILTIN
%destructor { freeAST($$); } screenplay statements statement declaration assignment conditional loop collection action expression primary call function_decl param_list param type_spec return_stmt argument_list string_list params arguments strings
%destructor { } program
%left OR
%left AND
%right NOT
%nonassoc GREATER_THAN GREATER_EQUAL LESS_THAN LESS_EQUAL IS IS_NOT RISING
%left PLUS MINUS
%left STAR SLASH MOD
%right UMINUS
%%
program : OPENING_CREDITS screenplay FINAL_CREDITS {
    $$ = createNodeWithLine(NODE_PROGRAM, "PROGRAM", NULL, @1.first_line); $$->left = $2; root = $$;
};
screenplay : SCREENPLAY statements ENDSCREENPLAY {
    $$ = createNodeWithLine(NODE_SCREENPLAY, "SCREENPLAY", NULL, @1.first_line); $$->left = $2;
};
statements : /* empty */ { $$ = NULL; }
    | statements statement { if ($1) { appendSibling($1, $2); $$ = $1; } else $$ = $2; }
;
statement : declaration | assignment | conditional | loop | collection | function_decl | return_stmt | action | call;
type_spec : CHARACTER { $$ = createNode(NODE_VALUE, NULL, "CHARACTER"); }
    | SCENE { $$ = createNode(NODE_VALUE, NULL, "SCENE"); }
    | DIALOGUE { $$ = createNode(NODE_VALUE, NULL, "DIALOGUE"); }
    | RATING { $$ = createNode(NODE_VALUE, NULL, "RATING"); }
    | BUDGET { $$ = createNode(NODE_VALUE, NULL, "BUDGET"); }
    | GENRE { $$ = createNode(NODE_VALUE, NULL, "GENRE"); }
    | STATUS { $$ = createNode(NODE_VALUE, NULL, "STATUS"); }
    | WHOLE { $$ = createNode(NODE_VALUE, NULL, "WHOLE"); }
    | SIGNAL { $$ = createNode(NODE_VALUE, NULL, "SIGNAL"); }
;
declaration : type_spec IDENTIFIER {
    $$ = namedNode(NODE_DECL, $2, $1->value, @1.first_line); freeAST($1);
} | type_spec IDENTIFIER ASSIGN expression {
    $$ = namedNode(NODE_DECL, $2, $1->value, @1.first_line); $$->left = $4; freeAST($1);
};
assignment : IDENTIFIER ASSIGN expression {
    $$ = namedNode(NODE_ASSIGN, $1, NULL, @1.first_line); $$->left = $3;
};
function_decl : FUNCTION IDENTIFIER LPAREN param_list RPAREN RETURNS type_spec FRAME statements ENDFRAME ENDFUNCTION {
    $$ = namedNode(NODE_FUNCTION, $2, $7->value, @1.first_line); $$->left = $4; $$->right = $9; freeAST($7);
};
param_list : /* empty */ { $$ = NULL; } | params { $$ = $1; };
params : param { $$ = $1; }
    | params COMMA param { appendSibling($1, $3); $$ = $1; }
;
param : type_spec IDENTIFIER {
    $$ = namedNode(NODE_PARAM, $2, $1->value, @1.first_line); freeAST($1);
};
return_stmt : RETURN expression { $$ = createNodeWithLine(NODE_RETURN, NULL, NULL, @1.first_line); $$->left = $2; };
call : IDENTIFIER LPAREN argument_list RPAREN { $$ = namedNode(NODE_CALL, $1, NULL, @1.first_line); $$->left = $3; };
argument_list : /* empty */ { $$ = NULL; } | arguments { $$ = $1; };
arguments : expression { $$ = $1; }
    | arguments COMMA expression { appendSibling($1, $3); $$ = $1; }
;
expression : expression PLUS expression { $$ = binary(NODE_BINARY_OP, "+", $1, $3, @2.first_line); }
    | expression MINUS expression { $$ = binary(NODE_BINARY_OP, "-", $1, $3, @2.first_line); }
    | expression STAR expression { $$ = binary(NODE_BINARY_OP, "*", $1, $3, @2.first_line); }
    | expression SLASH expression { $$ = binary(NODE_BINARY_OP, "/", $1, $3, @2.first_line); }
    | expression MOD expression { $$ = binary(NODE_BINARY_OP, "%", $1, $3, @2.first_line); }
    | expression GREATER_THAN expression { $$ = binary(NODE_CONDITION, ">", $1, $3, @2.first_line); }
    | expression GREATER_EQUAL expression { $$ = binary(NODE_CONDITION, ">=", $1, $3, @2.first_line); }
    | expression LESS_THAN expression { $$ = binary(NODE_CONDITION, "<", $1, $3, @2.first_line); }
    | expression LESS_EQUAL expression { $$ = binary(NODE_CONDITION, "<=", $1, $3, @2.first_line); }
    | expression IS expression { $$ = binary(NODE_CONDITION, "==", $1, $3, @2.first_line); }
    | expression IS_NOT expression { $$ = binary(NODE_CONDITION, "!=", $1, $3, @2.first_line); }
    | expression AND expression { $$ = binary(NODE_BINARY_OP, "AND", $1, $3, @2.first_line); }
    | expression OR expression { $$ = binary(NODE_BINARY_OP, "OR", $1, $3, @2.first_line); }
    | NOT expression { $$ = binary(NODE_UNARY_OP, "NOT", $2, NULL, @1.first_line); }
    | MINUS expression %prec UMINUS { $$ = binary(NODE_UNARY_OP, "-", $2, NULL, @1.first_line); }
    | expression RISING { $$ = binary(NODE_UNARY_OP, "RISING", $1, NULL, @2.first_line); }
    | primary { $$ = $1; }
;
primary : NUMBER { $$ = createNodeWithLine(NODE_VALUE, NULL, $1, @1.first_line); free($1); }
    | STRING { $$ = createNodeWithLine(NODE_VALUE, NULL, $1, @1.first_line); free($1); }
    | LITERAL { $$ = createNodeWithLine(NODE_VALUE, NULL, $1, @1.first_line); free($1); }
    | IDENTIFIER { $$ = namedNode(NODE_VALUE, $1, NULL, @1.first_line); }
    | call { $$ = $1; }
    | BUILTIN LPAREN argument_list RPAREN { $$ = namedNode(NODE_BUILTIN, $1, NULL, @1.first_line); $$->left = $3; }
    | LPAREN expression RPAREN { $$ = $2; }
;
conditional : SCENE_IF LPAREN expression RPAREN FRAME statements ENDFRAME {
    $$ = binary(NODE_IF, NULL, $3, $6, @1.first_line);
} | SCENE_IF LPAREN expression RPAREN FRAME statements ENDFRAME OTHERWISE FRAME statements ENDFRAME {
    $$ = binary(NODE_IF, NULL, $3, $6, @1.first_line); $$->elseBranch = $10;
};
loop : WHILE LPAREN expression RPAREN TAKE statements ENDTAKE {
    $$ = binary(NODE_WHILE, NULL, $3, $6, @1.first_line);
} | FOR_EACH_SCENE IN IDENTIFIER REEL statements ENDREEL {
    $$ = namedNode(NODE_FOR, $3, NULL, @1.first_line); $$->right = $5;
} | FOR_EACH_SCENE IDENTIFIER IN IDENTIFIER REEL statements ENDREEL {
    $$ = namedNode(NODE_FOR, $4, $2, @1.first_line); free($2); $$->right = $6;
};
collection : GENRE_COLLECTION IDENTIFIER ASSIGN LBRACE string_list RBRACE {
    $$ = namedNode(NODE_COLLECTION, $2, "GENRE_COLLECTION", @1.first_line); $$->left = $5;
} | ADD_TO IDENTIFIER expression {
    $$ = namedNode(NODE_COLLECTION_ADD, $2, NULL, @1.first_line); $$->left = $3;
};
string_list : /* empty */ { $$ = NULL; } | strings { $$ = $1; };
strings : STRING { $$ = createNodeWithLine(NODE_VALUE, NULL, $1, @1.first_line); free($1); }
    | strings COMMA STRING {
        ASTNode* item = createNodeWithLine(NODE_VALUE, NULL, $3, @3.first_line); free($3); appendSibling($1, item); $$ = $1;
    }
;
action : PRINT expression { $$ = binary(NODE_ACTION, "PRINT", $2, NULL, @1.first_line); }
    | AWARD expression { $$ = binary(NODE_ACTION, "AWARD", $2, NULL, @1.first_line); }
    | REVIEW expression { $$ = binary(NODE_ACTION, "REVIEW", $2, NULL, @1.first_line); }
    | ANALYZE IDENTIFIER { $$ = namedNode(NODE_ACTION, $2, "ANALYZE", @1.first_line); }
    | ASSERT LPAREN expression COMMA STRING RPAREN {
        $$ = createNodeWithLine(NODE_ACTION, "ASSERT", $5, @1.first_line); free($5); $$->left = $3;
    }
    | BUILD_SUSPENSE { $$ = createNodeWithLine(NODE_ACTION, "BUILD_SUSPENSE", NULL, @1.first_line); }
    | ENTER_STAGE { $$ = createNodeWithLine(NODE_ACTION, "ENTER_STAGE", NULL, @1.first_line); }
;
%%
void yyerror(const char* message)
{
    reportError("Syntax Error", yylloc.first_line, "%s (column %d)", message, yylloc.first_column);
}
