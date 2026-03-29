#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "symbol_table.h"

typedef struct FunctionEntry {
	char name[64];
	ASTNode* node;
	struct FunctionEntry* next;
} FunctionEntry;

typedef struct LocalValue {
	char name[64];
	char value[128];
	struct LocalValue* next;
} LocalValue;

static FunctionEntry* functionTable = NULL;
static LocalValue* localStack = NULL;

static void pushLocalValue(const char* name, const char* value)
{
	LocalValue* entry = (LocalValue*)malloc(sizeof(LocalValue));
	if (entry == NULL) {
		return;
	}
	strncpy(entry->name, name, sizeof(entry->name) - 1);
	entry->name[sizeof(entry->name) - 1] = '\0';
	strncpy(entry->value, value != NULL ? value : "", sizeof(entry->value) - 1);
	entry->value[sizeof(entry->value) - 1] = '\0';
	entry->next = localStack;
	localStack = entry;
}

static void popLocalScope(int count)
{
	for (int i = 0; i < count && localStack != NULL; ++i) {
		LocalValue* next = localStack->next;
		free(localStack);
		localStack = next;
	}
}

static const char* lookupLocalValue(const char* name)
{
	LocalValue* current = localStack;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current->value;
		}
		current = current->next;
	}
	return NULL;
}

static FunctionEntry* lookupFunction(const char* name)
{
	FunctionEntry* current = functionTable;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

static void registerFunctions(ASTNode* node)
{
	if (node == NULL) {
		return;
	}

	if (node->type == NODE_FUNCTION && node->name != NULL) {
		FunctionEntry* entry = (FunctionEntry*)malloc(sizeof(FunctionEntry));
		if (entry != NULL) {
			strncpy(entry->name, node->name, sizeof(entry->name) - 1);
			entry->name[sizeof(entry->name) - 1] = '\0';
			entry->node = node;
			entry->next = functionTable;
			functionTable = entry;
		}
	}

	registerFunctions(node->left);
	registerFunctions(node->right);
	registerFunctions(node->elseBranch);
	registerFunctions(node->next);
}

static const char* resolveNodeValue(ASTNode* node)
{
	if (node == NULL) {
		return NULL;
	}

	if (node->value != NULL) {
		return node->value;
	}

	if (node->name != NULL) {
		const char* localValue = lookupLocalValue(node->name);
		if (localValue != NULL) {
			return localValue;
		}
		Symbol* symbol = lookupSymbol(node->name);
		if (symbol != NULL && symbol->value[0] != '\0') {
			return symbol->value;
		}
	}

	return NULL;
}

static int isNumericLiteral(const char* text)
{
	if (text == NULL || *text == '\0') {
		return 0;
	}

	int seenDot = 0;
	for (const char* p = text; *p != '\0'; ++p) {
		if (*p == '.') {
			if (seenDot) {
				return 0;
			}
			seenDot = 1;
		} else if (*p < '0' || *p > '9') {
			return 0;
		}
	}
	return 1;
}

static double evaluateNumeric(ASTNode* node, int* ok)
{
	if (node == NULL) {
		*ok = 0;
		return 0.0;
	}

	if (node->type == NODE_VALUE) {
		const char* value = resolveNodeValue(node);
		if (value != NULL && isNumericLiteral(value)) {
			*ok = 1;
			return strtod(value, NULL);
		}
		*ok = 0;
		return 0.0;
	}

	if (node->type == NODE_BINARY_OP) {
		int leftOk = 0;
		int rightOk = 0;
		double left = evaluateNumeric(node->left, &leftOk);
		double right = evaluateNumeric(node->right, &rightOk);
		if (!leftOk || !rightOk || node->name == NULL) {
			*ok = 0;
			return 0.0;
		}
		*ok = 1;
		if (strcmp(node->name, "+") == 0) {
			return left + right;
		}
		if (strcmp(node->name, "-") == 0) {
			return left - right;
		}
		if (strcmp(node->name, "*") == 0) {
			return left * right;
		}
		if (strcmp(node->name, "/") == 0) {
			return right != 0.0 ? left / right : 0.0;
		}
		*ok = 0;
		return 0.0;
	}

	if (node->type == NODE_CALL && node->name != NULL) {
		FunctionEntry* function = lookupFunction(node->name);
		if (function == NULL || function->node == NULL) {
			*ok = 0;
			return 0.0;
		}
		const char* value = NULL;
		ASTNode* args = node->left;
		ASTNode* params = function->node->left;
		int pushCount = 0;
		params = function->node->left;
		while (params != NULL) {
			const char* argValue = resolveNodeValue(args);
			if (argValue == NULL && args != NULL) {
				int argOk = 0;
				double argNum = evaluateNumeric(args, &argOk);
				if (argOk) {
					char buffer[64];
					snprintf(buffer, sizeof(buffer), "%.6f", argNum);
					pushLocalValue(params->name, buffer);
					pushCount++;
				} else {
					pushLocalValue(params->name, "");
					pushCount++;
				}
			} else {
				pushLocalValue(params->name, argValue != NULL ? argValue : "");
				pushCount++;
			}
			params = params->next;
			if (args != NULL) {
				args = args->next;
			}
		}
		ASTNode* returnNode = function->node->right;
		while (returnNode != NULL && returnNode->type != NODE_RETURN) {
			returnNode = returnNode->next;
		}
		if (returnNode != NULL && returnNode->left != NULL) {
			value = resolveNodeValue(returnNode->left);
			if (value == NULL) {
				int returnOk = 0;
				double returnNum = evaluateNumeric(returnNode->left, &returnOk);
				if (returnOk) {
					value = NULL;
					popLocalScope(pushCount);
					*ok = 1;
					return returnNum;
				}
			}
		}
		popLocalScope(pushCount);
		if (value != NULL && isNumericLiteral(value)) {
			*ok = 1;
			return strtod(value, NULL);
		}
		*ok = 0;
		return 0.0;
	}

	*ok = 0;
	return 0.0;
}

static int evaluateCondition(ASTNode* node)
{
	if (node == NULL) {
		return 0;
	}

	if (node->name != NULL && strcmp(node->name, "RISING") == 0) {
		return 1;
	}

	int leftOk = 0;
	int rightOk = 0;
	double leftValue = evaluateNumeric(node->left, &leftOk);
	double rightValue = evaluateNumeric(node->right, &rightOk);
	if (!leftOk || !rightOk) {
		return 0;
	}

	return leftValue > rightValue;
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

if(functionTable == NULL)
{
	registerFunctions(node);
}

if (node->type == NODE_PROGRAM) {
	executeList(node->left);
	return;
}

if (node->type == NODE_SCREENPLAY) {
	executeList(node->left);
	return;
}

switch(node->type)
{

case NODE_IF:

if(evaluateCondition(node->left))
executeList(node->right);
else if(node->elseBranch)
executeList(node->elseBranch);
return;

case NODE_WHILE:

while(evaluateCondition(node->left))
executeList(node->right);
return;

case NODE_FOR:

executeList(node->right);
return;

case NODE_FUNCTION:
return;

case NODE_RETURN:
return;

case NODE_CALL:
{
	int ok = 0;
	(void) evaluateNumeric(node, &ok);
	break;
}

case NODE_ACTION:

if(strcmp(node->name,"PRINT")==0)
{
	if (node->left != NULL) {
		int ok = 0;
		double numeric = evaluateNumeric(node->left, &ok);
		if (ok) {
			printf("%g\n", numeric);
		} else {
			const char* value = resolveNodeValue(node->left);
			if (value != NULL) {
				printf("%s\n", value);
			}
		}
	} else if (node->value != NULL) {
		printf("%s\n", node->value);
	}
}

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

if(node->left)
{
	int ok = 0;
	double numeric = evaluateNumeric(node->left, &ok);
	if(ok)
	{
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "%.6f", numeric);
		for (int i = (int)strlen(buffer) - 1; i > 0 && buffer[i] == '0'; --i) {
			buffer[i] = '\0';
		}
		if (buffer[strlen(buffer) - 1] == '.') {
			buffer[strlen(buffer) - 1] = '\0';
		}
		setValue(node->name, buffer);
	}
	else if(node->value)
	{
		setValue(node->name,node->value);
	}
}
else if(node->value)
{
	setValue(node->name,node->value);
}

break;

case NODE_DECL:

if(node->left)
{
	int ok = 0;
	double numeric = evaluateNumeric(node->left, &ok);
	if(ok)
	{
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "%.6f", numeric);
		for (int i = (int)strlen(buffer) - 1; i > 0 && buffer[i] == '0'; --i) {
			buffer[i] = '\0';
		}
		if (buffer[strlen(buffer) - 1] == '.') {
			buffer[strlen(buffer) - 1] = '\0';
		}
		setValue(node->name, buffer);
	}
	else if(node->left->value)
	{
		setValue(node->name,node->left->value);
	}
}

break;

default:
break;

}

execute(node->left);
execute(node->right);
if (node->elseBranch != NULL) {
	execute(node->elseBranch);
}
}