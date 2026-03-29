#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char* duplicateString(const char* text)
{
	if (text == NULL) {
		return NULL;
	}

	size_t len = strlen(text) + 1;
	char* copy = (char*)malloc(len);
	if (copy != NULL) {
		memcpy(copy, text, len);
	}
	return copy;
}

ASTNode* createNode(NodeType type, const char* name, const char* value)
{
	return createNodeWithLine(type, name, value, 0);
}

ASTNode* createNodeWithLine(NodeType type, const char* name, const char* value, int line)
{
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	if (node == NULL) {
		fprintf(stderr, "Fatal Error: unable to allocate AST node\n");
		exit(EXIT_FAILURE);
	}

	node->type = type;
	node->name = duplicateString(name);
	node->value = duplicateString(value);
	node->line = line;
	node->left = NULL;
	node->right = NULL;
	node->elseBranch = NULL;
	node->next = NULL;

	return node;
}

void addChild(ASTNode* parent, ASTNode* child)
{
	if (parent == NULL || child == NULL) {
		return;
	}

	if (parent->left == NULL) {
		parent->left = child;
	} else if (parent->right == NULL) {
		parent->right = child;
	} else {
		appendSibling(parent->right, child);
	}
}

void appendSibling(ASTNode* node, ASTNode* sibling)
{
	if (node == NULL || sibling == NULL) {
		return;
	}

	ASTNode* tail = node;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = sibling;
}

void setNodeValue(ASTNode* node, const char* value)
{
	if (node == NULL) {
		return;
	}

	free(node->value);
	node->value = duplicateString(value);
}

static void printIndent(int level)
{
	for (int i = 0; i < level; ++i) {
		printf("  ");
	}
}

const char* nodeTypeName(NodeType type)
{
	switch (type) {
		case NODE_PROGRAM: return "PROGRAM";
		case NODE_SCREENPLAY: return "SCREENPLAY";
		case NODE_STATEMENTS: return "STATEMENTS";
		case NODE_DECL: return "DECLARATION";
		case NODE_ASSIGN: return "ASSIGNMENT";
		case NODE_BINARY_OP: return "BINARY_OP";
		case NODE_IF: return "IF";
		case NODE_CONDITION: return "CONDITION";
		case NODE_WHILE: return "WHILE";
		case NODE_FOR: return "FOREACH";
		case NODE_COLLECTION: return "COLLECTION";
		case NODE_COLLECTION_ADD: return "COLLECTION_ADD";
		case NODE_FUNCTION: return "FUNCTION";
		case NODE_PARAM: return "PARAM";
		case NODE_RETURN: return "RETURN";
		case NODE_CALL: return "CALL";
		case NODE_ACTION: return "ACTION";
		case NODE_VALUE: return "VALUE";
		default: return "UNKNOWN";
	}
}

void printAST(ASTNode* node, int level)
{
	if (node == NULL) {
		return;
	}

	printIndent(level);
	printf("%s", nodeTypeName(node->type));

	if (node->name != NULL) {
		printf(" (%s)", node->name);
	}

	if (node->value != NULL) {
		printf(" = %s", node->value);
	}

	if (node->line > 0) {
		printf(" [line %d]", node->line);
	}

	printf("\n");

	printAST(node->left, level + 1);
	printAST(node->right, level + 1);
	if (node->elseBranch != NULL) {
		printIndent(level + 1);
		printf("ELSE\n");
		printAST(node->elseBranch, level + 2);
	}
	printAST(node->next, level);
}
void freeAST(ASTNode* node)
{
	if (node == NULL) {
		return;
	}

	freeAST(node->left);
	freeAST(node->right);
	freeAST(node->elseBranch);
	freeAST(node->next);
	free(node->name);
	free(node->value);
	free(node);
}