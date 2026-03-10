#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "symbol_table.h"

static const char* resolveNodeValue(ASTNode* node)
{
	if (node == NULL) {
		return NULL;
	}

	if (node->value != NULL) {
		return node->value;
	}

	if (node->name != NULL) {
		Symbol* symbol = lookupSymbol(node->name);
		if (symbol != NULL && symbol->value[0] != '\0') {
			return symbol->value;
		}
	}

	return NULL;
}

static int evaluateCondition(ASTNode* node)
{
	if (node == NULL) {
		return 0;
	}

	if (node->value != NULL && strcmp(node->value, "RISING") == 0) {
		return 1;
	}

	const char* currentValue = resolveNodeValue(node);
	if (currentValue == NULL || node->value == NULL) {
		return 0;
	}

	return strtod(currentValue, NULL) > strtod(node->value, NULL);
}

static void executeList(ASTNode* node)
{
	ASTNode* current = node;
	while (current != NULL) {
		execute(current);
		current = current->next;
	}
}

void execute(ASTNode* node)
{
if(node==NULL) return;

switch(node->type)
{

case NODE_IF:

if(evaluateCondition(node->left))
executeList(node->right);
else if(node->right && node->right->next)
executeList(node->right->next);

return;

case NODE_WHILE:

while(evaluateCondition(node->left))
executeList(node->right);

return;

case NODE_ACTION:

if(strcmp(node->name,"PRINT")==0)
printf("%s\n",node->value);

else if(strcmp(node->name,"AWARD")==0)
printf("AWARD: %s\n",node->value);

else if(strcmp(node->name,"REVIEW")==0)
printf("REVIEW: %s\n",node->value);

else if(strcmp(node->name,"ANALYZE")==0)
printf("ANALYZE: %s\n",node->value);

else if(strcmp(node->name,"BUILD_SUSPENSE")==0)
printf("Building suspense...\n");

break;

case NODE_ASSIGN:

setValue(node->name,node->value);

break;

default:
break;

}

execute(node->left);
execute(node->right);
execute(node->next);
}