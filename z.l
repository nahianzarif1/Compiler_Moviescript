%{
#include <stdio.h>
#include <stdlib.h>
%}


DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
NUMBER      {DIGIT}+(\.{DIGIT}+)?
STRING      \"([^\"\n])*\"


%%


"CHARACTER"     { printf("KEYWORD_CHARACTER\n"); }
"SCENE"         { printf("KEYWORD_SCENE\n"); }
"DIALOGUE"      { printf("KEYWORD_DIALOGUE\n"); }
"RATING"        { printf("KEYWORD_RATING\n"); }
"BUDGET"        { printf("KEYWORD_BUDGET\n"); }
"GENRE"         { printf("KEYWORD_GENRE\n"); }
"LISTEN"        { printf("KEYWORD_LISTEN\n"); }


"WHOLE"             { printf("TYPE_WHOLE\n"); }
"SIGNAL"            { printf("TYPE_SIGNAL\n"); }


"<-"            { printf("ASSIGN_OP\n"); }
"->"            { printf("FLOW_OP\n"); }

"WHILE"                 { printf("KW_WHILE\n"); }
"TAKE"                  { printf("KW_TAKE\n"); }
"ENDTAKE"               { printf("KW_ENDTAKE\n"); }


"ADD"               { printf("OP_ADD\n"); }
"SUBTRACT"          { printf("OP_SUBTRACT\n"); }
"MULTIPLY"          { printf("OP_MULTIPLY\n"); }
"DIVIDE"            { printf("OP_DIVIDE\n"); }

"IS_NOT"            { printf("OP_NOT_EQUAL\n"); }
"IS"                { printf("OP_EQUAL\n"); }
"GREATER_EQUAL"     { printf("OP_GREATER_EQUAL\n"); }
"GREATER_THAN"      { printf("OP_GREATER_THAN\n"); }
"LESS_THAN"         { printf("OP_LESS_THAN\n"); }


"@"{ID}         { printf("IDENTIFIER (%s)\n", yytext); }


{NUMBER}        { printf("NUMBER (%s)\n", yytext); }
{STRING}        { printf("STRING (%s)\n", yytext); }

[\t\n]+        ;   /* Ignore whitespace */


.               { printf("UNKNOWN (%s)\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
