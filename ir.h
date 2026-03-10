#ifndef IR_H
#define IR_H

#include "ast.h"

void generateIR(ASTNode* node);
void generateCFG(ASTNode* node);

#endif