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

    printf("\n===== AST =====\n");
    printAST(root,0);

    printf("\n===== Semantic Analysis =====\n");
    semanticCheck(root);

    printf("\n===== INTERMEDIATE CODE =====\n");
    generateIR(root);

    printf("\n===== CONTROL FLOW GRAPH =====\n");
    generateCFG(root);

    printf("\n===== Symbol Table =====\n");
    printSymbolTable();

    printf("\n===== Interpreter Output =====\n");
    execute(root);

    return 0;
}