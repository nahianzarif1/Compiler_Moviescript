#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

void foldConstants(ASTNode* node);
void checkIdentifierUsage(ASTNode* node);
void semanticCheck(ASTNode* node);
ASTNode* lookupFunctionNode(const char* name);

#endif