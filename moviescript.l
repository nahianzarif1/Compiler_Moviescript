%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "moviescript.tab.h"

int line = 1;

static char* ms_strdup(const char* text)
{
    size_t len = strlen(text) + 1;
    char* copy = (char*)malloc(len);
    if (copy != NULL) {
        memcpy(copy, text, len);
    }
    return copy;
}
%}

LOWER      [a-zA-Z]
DIGIT      [0-9]
ID         @{LOWER}({LOWER}|{DIGIT}|_)*
NUMBER     {DIGIT}+(\.{DIGIT}+)?
STRING     \"([^\"\n])*\"

%%

"OPENING_CREDITS"      { return OPENING_CREDITS; }
"FINAL_CREDITS"        { return FINAL_CREDITS; }
"SCREENPLAY"           { return SCREENPLAY; }
"ENDSCREENPLAY"        { return ENDSCREENPLAY; }

"CHARACTER"            { return CHARACTER; }
"SCENE"                { return SCENE; }
"DIALOGUE"             { return DIALOGUE; }
"RATING"               { return RATING; }
"BUDGET"               { return BUDGET; }
"GENRE"                { return GENRE; }
"STATUS"               { return STATUS; }
"WHOLE"                { return WHOLE; }
"SIGNAL"               { return SIGNAL; }

"SCENE_IF"             { return SCENE_IF; }
"OTHERWISE"            { return OTHERWISE; }
"FRAME"                { return FRAME; }
"ENDFRAME"             { return ENDFRAME; }
"FOR_EACH_SCENE"       { return FOR_EACH_SCENE; }
"IN"                   { return IN; }
"REEL"                 { return REEL; }
"ENDREEL"              { return ENDREEL; }
"WHILE"                { return WHILE; }
"TAKE"                 { return TAKE; }
"ENDTAKE"              { return ENDTAKE; }

"GENRE_COLLECTION"     { return GENRE_COLLECTION; }
"ADD_TO"               { return ADD_TO; }

"FUNCTION"             { return FUNCTION; }
"RETURNS"              { return RETURNS; }
"RETURN"               { return RETURN; }
"ENDFUNCTION"          { return ENDFUNCTION; }

"AWARD"                { return AWARD; }
"REVIEW"               { return REVIEW; }
"ANALYZE"              { return ANALYZE; }
"PRINT"                { return PRINT; }
"BUILD_SUSPENSE"       { return BUILD_SUSPENSE; }
"ENTER_STAGE"          { return ENTER_STAGE; }

"SUCCESS"              { return SUCCESS; }
"FAILURE"              { return FAILURE; }
"BLOCKBUSTER"          { return BLOCKBUSTER; }
"FLOP"                 { return FLOP; }
"AVERAGE"              { return AVERAGE; }
"RISING"               { return RISING; }

"<-"                   { return ASSIGN; }
"+"                    { return PLUS; }
"-"                    { return MINUS; }
"*"                    { return STAR; }
"/"                    { return SLASH; }
"IS_NOT"               { return IS_NOT; }
"IS"                   { return IS; }
"GREATER_THAN"         { return GREATER_THAN; }
"GREATER_EQUAL"        { return GREATER_EQUAL; }
"LESS_THAN"            { return LESS_THAN; }
"LESS_EQUAL"           { return LESS_EQUAL; }

{ID}                    { yylval.str = ms_strdup(yytext); return IDENTIFIER; }
{NUMBER}                { yylval.str = ms_strdup(yytext); return NUMBER; }
{STRING}                { yylval.str = ms_strdup(yytext); return STRING; }

"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
","                     { return COMMA; }

\n                      { ++line; }
[ \t\r]+                ;

.                       { fprintf(stderr, "Lexical Error at line %d: unknown token '%s'\n", line, yytext); }

%%

int yywrap(void)
{
    return 1;
}