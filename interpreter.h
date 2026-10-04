#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "ast.h"

int execute(ASTNode* node, unsigned long maxSteps);
#endif
