%option noyywrap nounput noinput never-interactive
%x COMMENT
%{
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "diagnostic.h"
#include "limits.h"
#include "moviescript.tab.h"
/* Flex emits an internal signed/unsigned buffer comparison. */
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

int line = 1;
static int column = 1;
static int commentLine;
#define YY_USER_ACTION do { \
    yylloc.first_line = line; yylloc.first_column = column; \
    for (size_t i = 0; i < yyleng; ++i) { \
        if (yytext[i] == '\n') { ++line; column = 1; } else ++column; \
    } \
    yylloc.last_line = line; yylloc.last_column = column; \
} while (0);
%}

ID       @[a-zA-Z][a-zA-Z0-9_]*
NUMBER   [0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?
STRING   \"([^\"\\\n]|\\[^\n])*\"

%%
"//"[^\n]*                 ;
"#"[^\n]*                  ;
"/*"                       { commentLine = yylloc.first_line; BEGIN(COMMENT); }
<COMMENT>"*/"              { BEGIN(INITIAL); }
<COMMENT>[^*\n]+           ;
<COMMENT>"*"               ;
<COMMENT>\n                ;
<COMMENT><<EOF>>           { reportError("Lexical Error", commentLine, "unterminated block comment"); BEGIN(INITIAL); return 0; }
"OPENING_CREDITS"          { return OPENING_CREDITS; }
"FINAL_CREDITS"            { return FINAL_CREDITS; }
"SCREENPLAY"               { return SCREENPLAY; }
"ENDSCREENPLAY"            { return ENDSCREENPLAY; }
"CHARACTER"                { return CHARACTER; }
"SCENE"                    { return SCENE; }
"DIALOGUE"                 { return DIALOGUE; }
"RATING"                   { return RATING; }
"BUDGET"                   { return BUDGET; }
"GENRE"                    { return GENRE; }
"STATUS"                   { return STATUS; }
"WHOLE"                    { return WHOLE; }
"SIGNAL"                   { return SIGNAL; }
"SCENE_IF"                 { return SCENE_IF; }
"OTHERWISE"                { return OTHERWISE; }
"FRAME"                    { return FRAME; }
"ENDFRAME"                 { return ENDFRAME; }
"FOR_EACH_SCENE"           { return FOR_EACH_SCENE; }
"IN"                       { return IN; }
"REEL"                     { return REEL; }
"ENDREEL"                  { return ENDREEL; }
"WHILE"                    { return WHILE; }
"TAKE"                     { return TAKE; }
"ENDTAKE"                  { return ENDTAKE; }
"GENRE_COLLECTION"         { return GENRE_COLLECTION; }
"ADD_TO"                   { return ADD_TO; }
"FUNCTION"                 { return FUNCTION; }
"RETURNS"                  { return RETURNS; }
"RETURN"                   { return RETURN; }
"ENDFUNCTION"              { return ENDFUNCTION; }
"AWARD"                    { return AWARD; }
"REVIEW"                   { return REVIEW; }
"ANALYZE"                  { return ANALYZE; }
"PRINT"                    { return PRINT; }
"ASSERT"                   { return ASSERT; }
"BUILD_SUSPENSE"           { return BUILD_SUSPENSE; }
"ENTER_STAGE"              { return ENTER_STAGE; }
"SUCCESS"|"FAILURE"|"BLOCKBUSTER"|"FLOP"|"AVERAGE"|"TRUE"|"FALSE" { yylval.str = msCopy(yytext); return LITERAL; }
"COUNT"|"LENGTH"|"CONTAINS"|"CLAMP" { yylval.str = msCopy(yytext); return BUILTIN; }
"RISING"                   { return RISING; }
"AND"                      { return AND; }
"OR"                       { return OR; }
"NOT"                      { return NOT; }
"<-"                       { return ASSIGN; }
"+"                        { return PLUS; }
"-"                        { return MINUS; }
"*"                        { return STAR; }
"/"                        { return SLASH; }
"%"                        { return MOD; }
"IS_NOT"|"!="              { return IS_NOT; }
"IS"|"=="                  { return IS; }
"GREATER_THAN"|">"         { return GREATER_THAN; }
"GREATER_EQUAL"|">="       { return GREATER_EQUAL; }
"LESS_THAN"|"<"            { return LESS_THAN; }
"LESS_EQUAL"|"<="          { return LESS_EQUAL; }
{ID} {
    if (yyleng > MS_IDENTIFIER_MAX) {
        reportError("Lexical Error", yylloc.first_line, "identifier exceeds %d bytes (including @)", MS_IDENTIFIER_MAX); return INVALID;
    }
    yylval.str = msCopy(yytext); return IDENTIFIER;
}
{NUMBER} {
    if (yyleng > MS_NUMBER_TOKEN_MAX) {
        reportError("Lexical Error", yylloc.first_line, "numeric literal exceeds %d bytes", MS_NUMBER_TOKEN_MAX); return INVALID;
    }
    yylval.str = msCopy(yytext); return NUMBER;
}
{STRING} { yylval.str = msCopy(yytext); return STRING; }
\"([^\"\\\n]|\\[^\n])*\\? { reportError("Lexical Error", yylloc.first_line, "unterminated string"); return INVALID; }
"("                        { return LPAREN; }
")"                        { return RPAREN; }
"{"                        { return LBRACE; }
"}"                        { return RBRACE; }
","                        { return COMMA; }
[ \t\r\n]+                 ;
.                          { reportError("Lexical Error", yylloc.first_line, "unknown token '%s'", yytext); return INVALID; }
<<EOF>>                    { yylloc.first_line = line; yylloc.first_column = column; return 0; }
%%
