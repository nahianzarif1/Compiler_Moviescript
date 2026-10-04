#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "ast.h"

int semanticCheck(ASTNode* node);
void foldConstants(ASTNode* node);
ASTNode* lookupFunctionNode(const char* name);
void freeFunctionTable(void);
#endif
