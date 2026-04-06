#include <stdio.h>

#include "ast.h"
#include "moviescript.tab.h"
#include "semantic.h"
#include "symbol_table.h"
#include "ir.h"
#include "interpreter.h"

extern int yyparse();

extern ASTNode* root;

int main()
{
    initSymbolTable();
    yyparse();
    foldConstants(root);

    printf("\n Interpreter Output \n\n");
    execute(root);

    return 0;
}